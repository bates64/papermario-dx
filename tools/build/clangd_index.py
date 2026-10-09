"""Download the pre-built clangd index published for dx's main branch."""

import shutil
import subprocess
import urllib.parse
import urllib.request
import urllib.error
from pathlib import Path, PurePath

from rewrite_index_paths import rewrite_paths

CANONICAL_URL = "https://github.com/bates64/papermario-dx.git"
S3_BASE = "https://fsn1.your-objectstorage.com/starhaven/papermario-dx"


def exec_shell(command, cwd=None):
    ret = subprocess.run(command, cwd=cwd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    return ret.stdout


def uri_path(path: PurePath) -> str:
    """The path part of the file:// URI clangd writes for an absolute path.

    Windows paths like C:\\dx become /C:/dx, and anything other than letters,
    digits, and -_.~/: is percent-encoded.
    """
    posix = path.as_posix()
    if not posix.startswith("/"):
        posix = "/" + posix
    return urllib.parse.quote(posix, safe="/:")


def candidate_commits(root: Path):
    """Commits that might have a published index, newest first.

    Indexes are only published for commits on dx's main branch and for dx
    release tags, so this starts from the newest of them in the current
    history and walks back up to 20 commits, in case CI failed for some of
    them. Mirrors tools/unix/download_toolchain.sh.
    """
    if (root / ".jj").is_dir() and shutil.which("jj"):
        remotes = exec_shell(["jj", "git", "remote", "list"], cwd=root).splitlines()
        remote = next((r.split()[0] for r in remotes if "bates64/papermario-dx" in r), None)
        revset = "@"
        if remote:
            exec_shell(
                ["jj", "git", "fetch", "--quiet", "--remote", f"exact:{remote}", "--branch", "main", "--tag", "dx-*"],
                cwd=root,
            )
            revset = (
                f'heads(::@ & ::(remote_bookmarks(exact:"main", exact:"{remote}")'
                f' | remote_tags(glob:"dx-*", exact:"{remote}")))'
            )
        return exec_shell(
            ["jj", "log", "--no-graph", "-r", f"ancestors({revset}, 20)", "-T", 'commit_id ++ "\n"'], cwd=root
        ).split()
    if shutil.which("git"):
        base = current = exec_shell(["git", "rev-parse", "HEAD"], cwd=root).strip()
        exec_shell(["git", "fetch", "--quiet", CANONICAL_URL, "main", "+refs/tags/dx-*:refs/tags/dx-*"], cwd=root)
        main = exec_shell(["git", "rev-parse", "FETCH_HEAD"], cwd=root).strip()
        if main:
            base = exec_shell(["git", "merge-base", base, main], cwd=root).strip() or base
        release = exec_shell(["git", "describe", "--tags", "--match", "dx-*", "--abbrev=0", current], cwd=root).split()
        return exec_shell(["git", "log", "--topo-order", "--format=%H", "-n", "20", base, *release], cwd=root).split()
    return []


def fetch_clangd_index(root: Path):
    """Download the clangd index for the nearest published commit, if it's newer."""
    index_hash = None
    for commit in candidate_commits(root):
        try:
            with urllib.request.urlopen(f"{S3_BASE}/commits/{commit}/clangd-index") as response:
                index_hash = response.read().decode().strip()
            break
        except urllib.error.HTTPError:
            continue
    if not index_hash:
        return

    dx_dir = root / ".dx"
    dx_dir.mkdir(exist_ok=True)
    idx_path = dx_dir / "papermario-dx.idx"
    hash_file = dx_dir / "clangd-index-hash"

    if idx_path.exists() and hash_file.exists() and hash_file.read_text().strip() == index_hash:
        return

    print(f"configure: downloading clangd index for commit {commit}...")
    try:
        with urllib.request.urlopen(f"{S3_BASE}/toolchains/{index_hash}.idx") as response:
            idx_bytes = response.read()
        # The index refers to files by URIs like file://$$ROOT$$/src/main.c.
        idx_bytes = rewrite_paths(idx_bytes, b"file://$$ROOT$$", b"file://" + uri_path(root.resolve()).encode())
        idx_path.write_bytes(idx_bytes)
        hash_file.write_text(index_hash + "\n")
        print("configure: clangd index downloaded")
    except Exception as e:
        print(f"configure: failed to download clangd index: {e}")
