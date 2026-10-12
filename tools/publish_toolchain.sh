#!/bin/sh
# Publishes a toolchain build to the S3 bucket and records it as the one
# for the current commit. Run from the repository, with the bucket's
# credentials in the environment.
#
# Usage: tools/publish_toolchain.sh FILE KEY EXTENSION
#   FILE       the built archive
#   KEY        the name the commit lists it under, such as linux-x86_64.tar.xz
#   EXTENSION  the archive's file extension, such as tar.xz
set -eu

file="$1"
key="$2"
ext="$3"

endpoint="${S3_ENDPOINT:-https://fsn1.your-objectstorage.com}"
bucket="s3://starhaven/papermario-dx"

hash=$(sha256sum "$file" | cut -d' ' -f1)
# A toolchain that hasn't changed since the last commit is stored once.
if ! aws s3api head-object --bucket starhaven --key "papermario-dx/toolchains/$hash.$ext" --endpoint-url "$endpoint" >/dev/null 2>&1; then
  aws s3 cp "$file" "$bucket/toolchains/$hash.$ext" --endpoint-url "$endpoint"
fi
# For a tag, the pipeline's revision is the tag rather than the commit it
# points at.
commit=$(git rev-parse HEAD)
echo "$hash" | aws s3 cp - "$bucket/commits/$commit/$key" --endpoint-url "$endpoint"
echo "Published $key for $commit as $hash"
