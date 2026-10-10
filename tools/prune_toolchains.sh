#!/usr/bin/env bash
# Deletes published toolchains that no mod should need any more. It keeps the
# toolchains of every dx-* release and of the newest commits on main, deletes
# every other commit's record of its toolchains, then deletes the toolchains
# no remaining record names.
#
# Toolchains uploaded in the last day are always kept: another job may have
# uploaded one and not yet recorded which commit it's for.
#
# Run it from a clone of dx, with S3_ENDPOINT and AWS credentials set. Set
# DRY_RUN=1 to only print what it would delete.
set -euo pipefail

KEEP_MAIN=50
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

git fetch --quiet --depth="$KEEP_MAIN" origin "+refs/heads/main:refs/prune/main" "+refs/tags/dx-*:refs/tags/dx-*"
keep=$(
  git rev-list --first-parent -n "$KEEP_MAIN" refs/prune/main
  git tag --list "dx-*" | while read -r tag; do git rev-parse "$tag^{commit}"; done
)
if [ -z "$keep" ]; then
  echo "Found no commits to keep, so deleting nothing." >&2
  exit 1
fi

for commit in $(aws s3 ls "$BUCKET/commits/" | awk '$1 == "PRE" { sub("/$", "", $2); print $2 }'); do
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
