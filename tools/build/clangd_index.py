"""Download and configure a pre-built clangd index from GitHub releases."""

import shutil
import subprocess
import urllib.request
import urllib.error
from pathlib import Path

from rewrite_index_paths import rewrite_paths


def exec_shell(command, cwd=None):
    ret = subprocess.run(command, cwd=cwd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    return ret.stdout


def resolve_dx_tag(root: Path):
    """Find the nearest dx-* tag (current commit or ancestor) and the commit
    hash it points to, preferring jj if this is a jj repo and falling back to
    git. Returns (None, None) if neither is available or no tag is found."""
    if (root / ".jj").is_dir() and shutil.which("jj"):
        revset = 'latest(tags(glob:"dx-*") & ::@)'
        tag = exec_shell(["jj", "log", "-r", revset, "--no-graph", "-T", 'self.tags().join("\n")'], cwd=root).strip().splitlines()
        tag = tag[0] if tag else ""
        tag_hash = exec_shell(["jj", "log", "-r", revset, "--no-graph", "-T", "commit_id"], cwd=root).strip()
    elif shutil.which("git"):
        tag = exec_shell(["git", "describe", "--tags", "--abbrev=0", "--match", "dx-*"], cwd=root).strip()
        tag_hash = exec_shell(["git", "rev-parse", f"{tag}^{{}}"], cwd=root).strip() if tag else ""
    else:
        return None, None

    return (tag, tag_hash) if tag else (None, None)


def fetch_clangd_index(root: Path):
    """Fetch the clangd index for the nearest dx-* tag and configure .clangd."""
    tag, tag_hash = resolve_dx_tag(root)
    if not tag:
        return

    dx_dir = root / ".dx"
    dx_dir.mkdir(exist_ok=True)
    idx_path = dx_dir / "papermario-dx.idx"
    tag_file = dx_dir / "configure-tag"

    # Check if we already have the index for this tag
    need_download = True
    if idx_path.exists() and tag_file.exists():
        current_tag = tag_file.read_text().strip()
        if current_tag == tag_hash:
            need_download = False

    if need_download:
        repo = "bates64/papermario-dx"
        url = f"https://github.com/{repo}/releases/download/{tag}/papermario-dx.idx"
        print(f"configure: downloading clangd index for {tag}...")
        try:
            urllib.request.urlretrieve(url, str(idx_path))
            # Rewrite $$ROOT$$ paths in the RIFF string table
            abs_root = str(root.resolve())
            idx_bytes = idx_path.read_bytes()
            idx_bytes = rewrite_paths(
                idx_bytes,
                b"$$ROOT$$",
                abs_root.encode(),
            )
            idx_path.write_bytes(idx_bytes)
            tag_file.write_text(tag_hash + "\n")
            print("configure: clangd index downloaded")
        except urllib.error.HTTPError as e:
            print(f"configure: clangd index not available for {tag} ({e.code}), skipping")
        except Exception as e:
            print(f"configure: failed to download clangd index: {e}")

    # Update .clangd config with index path
    if idx_path.exists():
        _update_clangd_config(root, idx_path)


def _update_clangd_config(root: Path, idx_path: Path):
    """Add or update the Index.External section in .clangd."""
    clangd_path = root / ".clangd"
    abs_idx = str(idx_path.resolve())
    abs_root = str(root.resolve()) + "/"

    default_header = (
        "CompileFlags:\n"
        "  Add: -Wno-unknown-warning-option\n"
        "  Remove: [-m*, -f*, -g*]\n"
        "InlayHints:\n"
        "  Designators: No\n"
    )

    # Read existing config, preserving other sections
    existing_lines = []
    if clangd_path.exists():
        with open(clangd_path, "r", encoding="utf-8") as f:
            existing_lines = f.readlines()

    if not existing_lines:
        existing_lines = [l + "\n" for l in default_header.splitlines()]

    # Remove any existing Index section
    filtered = []
    in_index = False
    for line in existing_lines:
        if line.rstrip() == "Index:":
            in_index = True
            continue
        if in_index and (line.startswith("  ") or line.startswith("\t")):
            continue
        in_index = False
        filtered.append(line)

    # Append Index.External section
    if filtered and not filtered[-1].endswith("\n"):
        filtered.append("\n")
    filtered.append("Index:\n")
    filtered.append("  External:\n")
    filtered.append(f"    File: {abs_idx}\n")
    filtered.append(f"    MountPoint: {abs_root}\n")

    with open(clangd_path, "w", encoding="utf-8") as f:
        f.writelines(filtered)
