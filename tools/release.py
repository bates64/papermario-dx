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

A patch's section also goes into main's changelog, just above the release it
patches. Main listed the patch's notes under Unreleased when its fixes landed
there, so this removes them from that section. It's committed on the local main
branch as a merge of the patch that keeps main's files otherwise as they are,
since main already has the patch's fixes. That makes the patch part of the next
release's history, so a mod updating from the patch merges only what's changed
since it.
"""

import argparse
import datetime
import re
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).parent.parent
CHANGELOG = ROOT / "manual" / "changelog.md"
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


def add_patch_to_main_changelog(changelog: str, version: str, section: str) -> str:
    """Puts a patch's section above the release it patches, or that release's
    latest patch, and removes the patch's lines from the Unreleased section."""
    before, unreleased, after = split_changelog(changelog)

    lines = unreleased.splitlines()
    for line in section.splitlines():
        if not line.strip():
            continue
        if line in lines:
            lines.remove(line)
        else:
            print(f"warning: main's Unreleased section doesn't list this, so it stays as it is: {line}", file=sys.stderr)
    unreleased = re.sub(r"\n{3,}", "\n\n", "\n".join(lines)).strip()
    unreleased = f"\n{unreleased}\n\n" if unreleased else "\n"

    patched = re.escape(version.split(".")[0])
    match = re.search(rf"^## {patched}(\.\d+)?$", after, re.MULTILINE)
    if not match:
        sys.exit(f"main's {CHANGELOG.name} has no section for {version.split('.')[0]}.")
    after = f"{after[:match.start()]}## {version}\n\n{section}\n\n{after[match.start():]}"
    return f"{before}{UNRELEASED}{unreleased}{after}"


def commit_patch_to_main(tag: str, section: str):
    with tempfile.TemporaryDirectory() as tmp:
        worktree = Path(tmp) / "main"
        git("worktree", "add", "--quiet", str(worktree), "main")
        try:
            git("-C", str(worktree), "merge", "--quiet", "--no-commit", "--strategy=ours", tag)
            changelog = worktree / CHANGELOG.relative_to(ROOT)
            changelog.write_text(add_patch_to_main_changelog(changelog.read_text(), tag.removeprefix("dx-"), section))
            git("-C", str(worktree), "add", "--", str(changelog))
            git("-C", str(worktree), "commit", "--quiet", "--message", f"merge {tag} into main")
        finally:
            git("worktree", "remove", "--force", str(worktree))


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
    if args.branch != "main":
        commit_patch_to_main(tag, section)
    print(tag)


if __name__ == "__main__":
    main()
