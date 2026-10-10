"""Download the pre-built clangd index published for dx's commits."""

import shutil
import subprocess
import urllib.parse
import urllib.request
import urllib.error
from pathlib import Path, PurePath

from rewrite_index_paths import rewrite_paths

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


def published_index(dx_dir: Path) -> list[list[str]]:
    """The lines of the index of published toolchains, each split into words.

    The last copy downloaded is kept for configuring offline. See
    tools/index_toolchains.sh for its format.
    """
    index_path = dx_dir / "index.txt"
    try:
        with urllib.request.urlopen(f"{S3_BASE}/index.txt") as response:
            index_path.write_bytes(response.read())
    except urllib.error.URLError:
        pass
    if not index_path.exists():
        return []
    return [line.split() for line in index_path.read_text().splitlines()]


def history(root: Path) -> list[str]:
    """The current history's commits, newest first."""
    if (root / ".jj").is_dir() and shutil.which("jj"):
        return exec_shell(["jj", "log", "--no-graph", "-r", "::@", "-T", 'commit_id ++ "\n"'], cwd=root).split()
    if shutil.which("git"):
        return exec_shell(["git", "rev-list", "--topo-order", "HEAD"], cwd=root).split()
    return []


def fetch_clangd_index(root: Path):
    """Download the clangd index for the newest published commit in the current history, if it's newer.

    Mirrors tools/unix/download_toolchain.sh.
    """
    dx_dir = root / ".dx"
    dx_dir.mkdir(exist_ok=True)
    published = {
        words[1]: words[3] for words in published_index(dx_dir) if words[:1] == ["commit"] and words[2] == "clangd-index"
    }
    commit = next((commit for commit in history(root) if commit in published), None)
    if not commit:
        return
    index_hash = published[commit]

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
