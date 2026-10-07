# Rewrites every Mach-O file in a toolchain directory (as assembled by
# default.nix) so that none of them refer to /nix/store, and they find their
# libraries relative to their own location instead, wherever the toolchain
# ends up installed.
#
# Usage: SIGNING_UTILS=<file defining signIfRequired> bash relocate-darwin.sh <dir>
#
# OTOOL and INSTALL_NAME_TOOL name the tools to use, so this can also be run
# with LLVM's equivalents.
set -euo pipefail

otool=${OTOOL:-otool}
install_name_tool=${INSTALL_NAME_TOOL:-install_name_tool}
# shellcheck source=/dev/null
. "$SIGNING_UTILS"

cd "$1"

# Each Mach-O load command, as "<command>\t<path>".
load_commands() {
  "$otool" -l "$1" | awk '
    /^ *cmd / { cmd = $2 }
    (/^ *name / && cmd ~ /_DYLIB$/) || (/^ *path / && cmd == "LC_RPATH") {
      sub(/^ *(name|path) /, ""); sub(/ \(offset [0-9]+\)$/, "")
      print cmd "\t" $0
    }' | sort -u
}

# Each Mach-O file, as "<path>\t<kind>", where kind is "executable" for
# executables and empty for libraries and bundles.
files=$(find store python -type f -print0 | xargs -0 file -0 \
  | sed -n 's/\x0: *Mach-O.*executable.*/\texecutable/p; s/\x0: *Mach-O.*/\t/p' | sort)
changed=0
while IFS=$'\t' read -r f kind; do
  cmds=$(load_commands "$f")
  dir=$(dirname "$f")
  args=()
  rpaths=()
  uses_rpath=
  while IFS=$'\t' read -r cmd path; do
    case "$cmd:$path" in
      LC_ID_DYLIB:/nix/store/*)
        args+=(-id "@rpath/${path##*/}")
        ;;
      LC_ID_DYLIB:*) ;;
      LC_RPATH:/nix/store/*)
        args+=(-delete_rpath "$path")
        ;;
      LC_RPATH:*)
        rpaths+=("$path")
        ;;
      *:/nix/store/*)
        # Mach-O load commands embed each dependency's full path (unlike
        # ELF's bare DT_NEEDED names). Prefer the flattened lib/, but only
        # when the name there is this exact library, since the closure can
        # hold more than one build of a library under the same name.
        copy=store/${path#/nix/store/}
        if [ ! -e "$copy" ]; then
          echo "relocate-darwin: $f depends on $path, which isn't in the toolchain" >&2
          exit 1
        fi
        flat=lib/${path##*/}
        if [ -e "$flat" ] && [ "$(realpath "$flat")" = "$(realpath "$copy")" ]; then
          args+=(-change "$path" "@rpath/${path##*/}")
          uses_rpath=1
        else
          args+=(-change "$path" "@loader_path/$(realpath -s --relative-to="$dir" "$copy")")
        fi
        ;;
      *:@rpath/*)
        uses_rpath=1
        ;;
    esac
  done <<< "$cmds"

  # dyld resolves @loader_path from the file's real location. The
  # @executable_path entry covers executables run through the bin/
  # symlinks, in case it's taken from the symlink instead. Libraries don't
  # get it: dyld already searches the rpaths of the executable that loads
  # them, and some have too little header space left to fit it. Files that
  # need no other change already find their @rpath libraries.
  if [ -n "$uses_rpath" ] && [ ${#args[@]} -gt 0 ]; then
    new_rpaths=("@loader_path/$(realpath -s --relative-to="$dir" lib)")
    [ "$kind" = executable ] && new_rpaths+=("@executable_path/../lib")
    for rpath in "${new_rpaths[@]}"; do
      case " ${rpaths[*]-} " in
        *" $rpath "*) ;;
        *) args+=(-add_rpath "$rpath") ;;
      esac
    done
  fi

  # This fails if the file's header has too little free space for the
  # rewritten load commands, which has to be fixed in the package that
  # built it (such as by linking with -headerpad_max_install_names).
  if [ ${#args[@]} -gt 0 ]; then
    "$install_name_tool" "${args[@]}" "$f"
    signIfRequired "$f"
    changed=$((changed + 1))
  fi
done <<< "$files"

echo "relocate-darwin: rewrote $changed Mach-O files"
