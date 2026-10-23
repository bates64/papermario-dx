#!/usr/bin/env bash
# Deletes published toolchains that no mod should need any more, then writes
# index.txt, which the download scripts use to find a mod's toolchain.
#
# It keeps the toolchains of every dx-* release, of main's newest commit, and of
# each older commit on main until KEEP_DAYS after the commit that replaced it
# landed, so a mod that merged main has that long to merge something newer. A
# commit landed when its first toolchain record was uploaded, or, if CI failed
# for it, at its commit date. It deletes every other commit's record of its
# toolchains, then the toolchains no remaining record names. Toolchains uploaded
# in the last day are always kept: another job may have uploaded one and not yet
# recorded which commit it's for.
#
# Each line of the index is either `commit <commit> <file> <hash>`, for each
# toolchain a remaining record names, or `release <tag> <commit>`, for each
# release.
#
# Run it from a clone of dx, with S3_ENDPOINT and AWS credentials set. Set
# DRY_RUN=1 to print what it would delete instead of deleting it. It writes the
# index either way, since the download scripts can't work without it; after a
# dry run, the index also lists the commits it would have deleted.
set -euo pipefail

KEEP_DAYS=90
BUCKET="s3://starhaven/papermario-dx"

aws() {
  command aws --endpoint-url "$S3_ENDPOINT" "$@"
}

delete() {
  if [ "${DRY_RUN:-0}" = 1 ]; then
    echo "Would delete ${*: -1}"
  else
    aws s3 rm --quiet "$@"
  fi
}

# Only commits are needed, so skipping trees keeps main's whole history small.
unshallow=()
if [ "$(git rev-parse --is-shallow-repository)" = true ]; then
  unshallow=(--unshallow)
fi
git fetch --quiet --filter=tree:0 "${unshallow[@]}" origin "+refs/heads/main:refs/prune/main" "+refs/tags/dx-*:refs/tags/dx-*"

# Each published commit and when its first record was uploaded, as Unix time.
landed=$(aws s3 ls --recursive "$BUCKET/commits/" | TZ=UTC awk '{
  split($1, d, "-"); split($2, t, ":"); split($4, path, "/")
  time = mktime(d[1] " " d[2] " " d[3] " " t[1] " " t[2] " " t[3])
  if (!(path[3] in first) || time < first[path[3]]) first[path[3]] = time
} END { for (commit in first) print commit, first[commit] }')

keep=$(
  git log --first-parent --format="%H %ct" refs/prune/main | awk -v cutoff="$(date -u -d "$KEEP_DAYS days ago" +%s)" '
    NR == FNR { landed[$1] = $2; next }
    FNR == 1 || replaced_at >= cutoff { print $1 }
    { replaced_at = ($1 in landed) ? landed[$1] : $2 }
  ' <(echo "$landed") -
  git tag --list "dx-*" | while read -r tag; do git rev-parse "$tag^{commit}"; done
)
if [ -z "$keep" ]; then
  echo "Found no commits to keep, so deleting nothing." >&2
  exit 1
fi

for commit in $(cut -d " " -f 1 <<<"$landed"); do
  if ! grep -qx "$commit" <<<"$keep"; then
    delete --recursive "$BUCKET/commits/$commit/"
  fi
done

records=$(mktemp -d)
aws s3 cp --quiet --recursive "$BUCKET/commits/" "$records"
used=$(for commit in $keep; do [ -d "$records/$commit" ] && cat "$records/$commit"/*; done | sort -u)
if [ -z "$used" ]; then
  echo "Found no toolchains in use, so deleting none." >&2
  exit 1
fi

cutoff=$(date -u -d "1 day ago" +%Y-%m-%d)
aws s3 ls "$BUCKET/toolchains/" | while read -r day _ _ name; do
  hash=${name%%.*}
  if [[ "$day" < "$cutoff" ]] && ! grep -qx "$hash" <<<"$used"; then
    delete "$BUCKET/toolchains/$name"
  fi
done

index=$(
  for dir in "$records"/*/; do
    commit=$(basename "$dir")
    for record in "$dir"*; do
      echo "commit $commit ${record##*/} $(cat "$record")"
    done
  done
  git tag --list "dx-*" | while read -r tag; do
    commit=$(git rev-parse "$tag^{commit}")
    if [ -d "$records/$commit" ]; then
      echo "release $tag $commit"
    fi
  done
)
echo "$index" | aws s3 cp --quiet - "$BUCKET/index.txt" --content-type text/plain --cache-control no-cache
