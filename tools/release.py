#!/usr/bin/env python3
"""Releases the current commit as the next Paper Mario DX release.

On main, a release is named for the day it's made, such as dx-2026-10-07, or
for the next free day if that day already has one. On a release/2026-10-07
branch, it's that release's next patch, such as dx-2026-10-07.1.

The changelog's Unreleased section becomes the release's section, headed with
its name without the dx- prefix, such as 2026-10-07, under a new, empty
Unreleased section. This is committed, and the commit is tagged with the
release's name. The tag's message is the release notes: its subject is the
release's name, and its body is the release's section of the changelog.
"""

import argparse
import datetime
import re
import subprocess
import sys
from pathlib import Path

CHANGELOG = Path(__file__).parent.parent / "manual" / "changelog.md"
UNRELEASED = "## Unreleased\n"


def git(*args: str, input: str | None = None) -> str:
    return subprocess.run(["git", *args], check=True, stdout=subprocess.PIPE, text=True, input=input).stdout


def next_tag(branch: str, tags: set[str]) -> str:
    if branch == "main":
        day = datetime.datetime.now(datetime.timezone.utc).date()
        while f"dx-{day}" in tags:
            day += datetime.timedelta(days=1)
        return f"dx-{day}"

    match = re.fullmatch(r"release/(\d{4}-\d{2}-\d{2})", branch)
    if not match:
        sys.exit(f"Can't release from {branch}. Run this on main, or on a release/YYYY-MM-DD branch for a patch.")
    release = f"dx-{match[1]}"
    if release not in tags:
        sys.exit(f"{branch} has no {release} tag to patch.")
    patch = 1
    while f"{release}.{patch}" in tags:
        patch += 1
    return f"{release}.{patch}"


def split_changelog(changelog: str) -> tuple[str, str, str]:
    """Splits the changelog into what's before, in, and after the Unreleased section."""
    start = changelog.find(UNRELEASED)
    if start == -1:
        sys.exit(f"{CHANGELOG} has no {UNRELEASED.strip()} section.")
    body_start = start + len(UNRELEASED)
    end = changelog.find("\n## ", body_start)
    end = len(changelog) if end == -1 else end + 1
    return changelog[:start], changelog[body_start:end], changelog[end:]


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--branch", required=True, help="the branch being released: main, or release/YYYY-MM-DD")
    parser.add_argument("--dry-run", action="store_true", help="print the tag and its notes without releasing")
    args = parser.parse_args()

    existing = git("tag", "--points-at", "HEAD", "--list", "dx-*").split()
    if existing:
        sys.exit(f"This commit is already released as {existing[0]}.")

    tags = set(git("tag", "--list", "dx-*").split())
    tag = next_tag(args.branch, tags)
    before, section, after = split_changelog(CHANGELOG.read_text())
    section = section.strip()
    if not section:
        section = "The first release." if not tags else "No changes are listed for this release."
    version = tag.removeprefix("dx-")
    message = f"Paper Mario DX {version}\n\n{section}\n"
    if args.dry_run:
        print(tag)
        print()
        print(message, end="")
        return

    CHANGELOG.write_text(f"{before}{UNRELEASED}\n## {version}\n\n{section}\n\n{after}".rstrip("\n") + "\n")
    git("commit", "--quiet", "--message", f"release {tag}", "--", str(CHANGELOG))
    git("tag", "--annotate", "--cleanup=verbatim", "--file=-", tag, input=message)
    print(tag)


if __name__ == "__main__":
    main()
