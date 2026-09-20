#!/usr/bin/env python3

import json
import os
import re
import shutil
import subprocess
import sys
from functools import lru_cache
from glob import glob
from pathlib import Path
from typing import Dict, List, Set, Tuple, Union

import ninja_syntax

if sys.platform == 'win32':
    import ntfsutils.junction

import assets
import linker
from action_data import actions_from_yaml
from effect_data import effects_from_yaml
from layout import Layout
from segments import SegmentMap

# Everything configure reads to decide what build.ninja should contain. The
# generator rule reruns configure when any of these change; a module missing
# here would leave build.ninja stale after an edit to it.
CONFIGURE_MODULES = [
    "configure.py",
    "action_data.py",
    "assets.py",
    "effect_data.py",
    "layout.py",
    "linker.py",
    "raster.py",
    "segments.py",
]

# Configuration:
VERSIONS = ["us"]

# Paths:
ROOT = Path(__file__).parent.parent.parent
if ROOT.is_absolute():
    ROOT = ROOT.relative_to(Path.cwd())

BUILD_TOOLS = Path("tools/build")

if shutil.which("n64crc"):
    CRC_TOOL = "n64crc"
else:
    CRC_TOOL = f"{BUILD_TOOLS}/rom/n64crc"

SOURCE_DIRS = ["src", "include", "assets"]

# Serialized overlay type indices. These must match OverlayType in
# src/dx/overlay.h.
OVL_TYPE_EFFECT = 0
OVL_TYPE_MAP = 1
OVL_TYPE_ACTION = 2
OVL_TYPE_PARTNER = 3
OVL_TYPE_ACTOR = 4
OVL_TYPE_BATTLE_PARTNER = 5
OVL_TYPE_ACTION_CMD = 6
OVL_TYPE_BATTLE_SCRIPT = 7
OVL_TYPE_BATTLE_MENU = 8
OVL_TYPE_ENTITY = 9

BATTLE_MENU_SOURCES = (
    "battle/menus/btl_states_menus.c",
    "battle/menus/menu_moves.c",
    "battle/menus/menu_strats.c",
    "battle/states/menu_player.c",
    "battle/states/menu_partner.c",
    "battle/states/menu_peach.c",
    "battle/states/menu_twink.c",
    "battle/states/select_target.c",
)


def _walk_source_file_list():
    """Returns a sorted list of all files and directories under SOURCE_DIRS."""
    file_list = []
    for top in SOURCE_DIRS:
        top_path = ROOT / top
        if not top_path.exists():
            continue
        for dirpath, dirnames, filenames in os.walk(top_path):
            dirnames.sort()
            rel = (
                Path(dirpath).relative_to(ROOT)
                if Path(dirpath).is_absolute()
                else Path(dirpath)
            )
            file_list.append(str(rel) + "/")
            for f in sorted(filenames):
                file_list.append(str(rel / f))
    return file_list


PIGMENT64 = "pigment64"
CRUNCH64 = "crunch64"

RUST_TOOLS = [
    (PIGMENT64, "pigment64", "0.4.2"),
    (CRUNCH64, "crunch64-cli", "0.3.1"),
]


def posix(path) -> str:
    """Return path as string with forward slashes for cross-platform build.ninja compatibility."""
    return str(path).replace("\\", "/")


# Files a hand-authored asset layer may hold that no build rule reads.
IGNORED_ASSET_NAMES = {".gitkeep", ".DS_Store", "Thumbs.db"}


def _repo_paths(entries) -> List[str]:
    """Ninja build entries as repo-relative POSIX strings, dropping ninja vars."""
    if not entries:
        return []
    if isinstance(entries, (str, Path)):
        entries = [entries]
    paths = []
    for entry in entries:
        text = str(entry)
        if not text or text.startswith("$"):
            continue
        paths.append(posix(os.path.relpath(text, ROOT)))
    return paths


def configure_input_paths(versions: List[str]) -> List[str]:
    """Every file configure reads to decide what build.ninja should contain."""
    paths = [posix(BUILD_TOOLS / module) for module in CONFIGURE_MODULES]
    for version in versions:
        paths.append(f"ver/{version}/layout.yaml")
        paths.append(f"ver/{version}/splat.yaml")
    paths.extend(
        [
            "src/registry/actions.yaml",
            "src/registry/effects.yaml",
        ]
    )
    return paths


def evt_validation_output_path(obj_path: Path) -> Path:
    parts = obj_path.parts
    build_index = parts.index("build")
    return Path(*parts[:build_index], "evtcheck", *parts[build_index + 1:])


def evt_validation_stamp_path(obj_path: Path) -> str:
    return posix(evt_validation_output_path(obj_path).with_suffix(".validate_evt.stamp"))


def evt_validation_display_path(obj_path: Path) -> str:
    return posix(evt_validation_output_path(obj_path).with_suffix(""))


class NinjaWriter(ninja_syntax.Writer):
    """A ninja writer that remembers every path it is told to read or write, and can emit validations.

    configure builds build.ninja by scanning the assets/ tree with a different
    glob per subsystem, so a file that no glob matches is left out with no
    error. Recording each input and output lets check_asset_coverage report
    assets that no rule consumes.

    A validation is a target that ninja builds whenever the requesting edge is
    part of the build, but that nothing waits on. ninja_syntax has no parameter
    for them, so they go through order_only behind the `|@` separator, which
    Writer.build passes through untouched.
    """

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.consumed_paths: Set[str] = set()
        self.produced_paths: Set[str] = set()

    def build(
        self,
        outputs,
        rule,
        inputs=None,
        implicit=None,
        order_only=None,
        variables=None,
        implicit_outputs=None,
        validations: List[str] = [],
    ):
        for group in (inputs, implicit, order_only):
            self.consumed_paths.update(_repo_paths(group))
        for group in (outputs, implicit_outputs):
            self.produced_paths.update(_repo_paths(group))
        if validations:
            order_only = list(order_only or []) + ["|@"] + validations
        return super().build(
            outputs, rule, inputs, implicit, order_only, variables, implicit_outputs
        )


def exec_shell(command: List[str]) -> str:
    ret = subprocess.run(
        command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True
    )
    return ret.stdout


def write_ninja_rules(
    ninja: NinjaWriter,
    cpp: str,
    extra_cppflags: str,
    extra_cflags: str,
    extra_cxxflags: str,
    use_ccache: bool,
    shift: bool,
    debug: bool,
):
    # platform-specific

    ccache = ""

    if use_ccache:
        ccache = "ccache "
        try:
            subprocess.call(
                ["ccache"], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL
            )
        except FileNotFoundError:
            ccache = ""

    cross = "mips-linux-gnu-"
    cc_modern = f"{cross}gcc"
    cxx_modern = f"{cross}g++"

    BFDNAME = "elf32-tradbigmips"

    CPPFLAGS_COMMON = (
        "-Iver/$version/include -Iver/$version/build/include -Iinclude -Isrc -Iassets/$version -D_FINALROM "
        "-DVERSION=$version -DF3DEX_GBI_2 -D_MIPS_SZLONG=32"
    )

    CPPFLAGS = CPPFLAGS_COMMON

    modern_flags = "-c -G0 -O2 -g1 -gdwarf -gas-loc-support -ffast-math -fno-unsafe-math-optimizations -fdiagnostics-color=always -funsigned-char -mgp32 -mfp32 -mabi=32 -mfix4300 -march=vr4300 -mno-gpopt -mno-abicalls -fno-pic -fno-exceptions -fno-stack-protector -fno-toplevel-reorder -fno-zero-initialized-in-bss -Wno-builtin-declaration-mismatch"
    cflags_modern = f"{modern_flags} {extra_cflags}"
    cxxflags_modern = f"{modern_flags} {extra_cxxflags}"

    ninja.variable("python", f'"{sys.executable}"')

    ld_args = f"-T ver/$version/build/undefined_syms.txt -T ver/$version/undefined_syms_auto.txt -T ver/$version/undefined_funcs_auto.txt -Map $mapfile --no-check-sections --whole-archive -T $in -o $out"
    ld = (
        f"{cross}ld"
        if not "PAPERMARIO_LD" in os.environ
        else os.environ["PAPERMARIO_LD"]
    )

    ninja.rule(
        "ld",
        description="Linking engine",
        command=f"{ld} {ld_args}",
    )

    ninja.rule(
        "shape_ld",
        description="Linking map shape $out",
        command=f"{ld} -T src/map_shape.ld $in -o $out",
    )

    ninja.rule(
        "shape_objcopy",
        description="Extracting map shape binary $out",
        command=f"{cross}objcopy $in $out -O binary",
    )

    z64_debug_flags = ""
    if debug:
        z64_debug_flags = " -gS -R .data -R .note -R .eh_frame -R .gnu.attributes -R .comment -R .options"
    ninja.rule(
        "z64",
        description="Creating engine ROM without overlays",
        command=f"$python {BUILD_TOOLS}/make_rom.py {cross} {CRC_TOOL} $in $out{z64_debug_flags}",
        pool="console",
    )

    ninja.rule(
        "z64_ique",
        description="Creating iQue ROM",
        command=f"{cross}objcopy $in $out -O binary{z64_debug_flags}",
    )

    ninja.rule(
        "sha1sum",
        description="Verifying checksum",
        command=f"$python -c \"open('$out','w', encoding='utf-8').close()\"",
    )

    ninja.rule(
        "cpp",
        description="Preprocessing $in",
        command=f"{cpp} $in {extra_cppflags} -P -o $out",
    )

    ninja.rule(
        "cc_modern",
        description="Compiling $in",
        command=f"{ccache}{cc_modern} {cflags_modern} $cflags {CPPFLAGS} {extra_cppflags} $cppflags -include common.h -D_LANGUAGE_C -Werror=implicit -Werror=old-style-declaration -Werror=missing-parameter-type -Wno-error=int-conversion -Wno-error=incompatible-pointer-types -MD -MF $out.d $in -o $out",
        depfile="$out.d",
        deps="gcc",
    )

    ninja.rule(
        "cxx_modern",
        description="Compiling $in",
        command=f"{ccache}{cxx_modern} {cxxflags_modern} $cflags {CPPFLAGS} {extra_cppflags} $cppflags -include common.hpp -std=c++20 -D_LANGUAGE_C_PLUS_PLUS -MD -MF $out.d $in -o $out",
        depfile="$out.d",
        deps="gcc",
    )

    ninja.rule(
        "evt_validate_obj",
        description="Validating scripts in $evt_target",
        command=f"$python {BUILD_TOOLS}/evt_validate_obj.py --effects-yaml src/registry/effects.yaml --object-list $out.rsp --out $out",
        rspfile="$out.rsp",
        rspfile_content="$in_newline",
    )

    ninja.rule(
        "dead_cc_fix",
        description="Fixing dead code symbols in $in",
        command=f"{cross}objcopy --redefine-sym sqrtf=dead_sqrtf $in $out",
    )

    ninja.rule(
        "bin",
        description="Extracting binary data from $in",
        command=f"{cross}objcopy -I binary -O {BFDNAME} --set-section-alignment .data=8 $in $out",
    )

    ninja.rule(
        "cp",
        description="Copying $in to $out",
        command=f"cp $in $out",
    )

    ninja.rule(
        "as",
        description="Assembling $in",
        command=f"{cross}gcc -c -x assembler-with-cpp -fno-pic -mno-abicalls {CPPFLAGS} {extra_cppflags} $cppflags -EB -march=vr4300 -mtune=vr4300 $in -o $out",
    )

    ninja.rule(
        "img",
        description="Converting $in to $img_type image",
        command=f"$python {BUILD_TOOLS}/img/build.py $img_type $in $out $img_flags",
    )

    ninja.rule(
        "pigment",
        description="Converting $in to $img_type image",
        command=f"{PIGMENT64} to-bin $img_flags -f $img_type -o $out $in",
    )

    ninja.rule(
        "img_header",
        description="Generating header for image $in",
        command=f'$python {BUILD_TOOLS}/img/header.py $in $out "$c_name"',
    )

    ninja.rule(
        "effect_stub",
        description="Generating $out",
        command=f"$python {BUILD_TOOLS}/effect_stub.py $kind $stub_name $stub_index $out",
    )

    ninja.rule(
        "yay0",
        description="Compressing $in",
        command=f"crunch64 compress yay0 $in $out",
    )

    ninja.rule(
        "npc_sprite",
        description="Building sprite $sprite_name",
        command=f"$python {BUILD_TOOLS}/sprite/npc_sprite.py $out $sprite_name $asset_stack",
    )

    ninja.rule(
        "sprites",
        description="Packing sprites",
        command=f"$python {BUILD_TOOLS}/sprite/sprites.py $out $header_out $build_dir $asset_stack",
    )

    ninja.rule(
        "sprite_header",
        description="Generating header for sprite $sprite_name",
        command=f"$python {BUILD_TOOLS}/sprite/header.py $out $sprite_name $sprite_id $asset_stack",
    )

    ninja.rule(
        "msg",
        description="Building messages in $in",
        command=f"$python {BUILD_TOOLS}/msg/parse_compile.py $version $in $out",
    )

    ninja.rule(
        "icons",
        description="Building icons",
        command=f"$python {BUILD_TOOLS}/icons.py $out $header_path $asset_stack",
    )

    ninja.rule(
        "move_data",
        description="Generating move data",
        command=f"$python {BUILD_TOOLS}/move_data.py $out $in",
    )

    ninja.rule(
        "item_data",
        description="Generating item data",
        command=f"$python {BUILD_TOOLS}/item_data.py $out $in $asset_stack",
    )

    ninja.rule(
        "action_data",
        description="Generating player action data",
        command=(
            f"$python {BUILD_TOOLS}/action_data.py "
            "$out_data $out_enum $actions_yaml"
        ),
    )

    ninja.rule(
        "actor_types",
        description="Generating actor types",
        command=f"$python {BUILD_TOOLS}/actor_types.py $out $in",
    )

    ninja.rule(
        "gen_areas",
        description="Generating area/map tables",
        command=f"$python {BUILD_TOOLS}/gen_areas.py $out $src_dir --asset-stack $asset_stack",
    )

    ninja.rule(
        "world_map",
        description="Generating world map",
        command=f"$python {BUILD_TOOLS}/world_map.py $in $out",
    )

    ninja.rule(
        "recipes",
        description="Generating recipes",
        command=f"$python {BUILD_TOOLS}/recipes.py $in $out",
    )

    ninja.rule(
        "msg_combine",
        description="Combining messages",
        command=f"$python {BUILD_TOOLS}/msg/combine.py $out --layer-sizes $layer_sizes $in",
    )

    ninja.rule(
        "mapfs",
        description="Building map filesystem",
        command=f"$python {BUILD_TOOLS}/mapfs/combine.py vanilla $out $out.rsp",
        rspfile="$out.rsp",
        rspfile_content="$in_newline",
    )

    ninja.rule(
        "tex",
        description="Building texture $tex_name",
        command=f"$python {BUILD_TOOLS}/mapfs/tex.py $out $tex_name $asset_stack",
    )

    ninja.rule(
        "pack_title_data",
        description="Packing title screen data",
        command=f"$python {BUILD_TOOLS}/mapfs/pack_title_data.py $version $out $in",
    )

    ninja.rule(
        "map_header",
        description="Generating map header for $in",
        command=f"$python {BUILD_TOOLS}/mapfs/map_header.py $in $out",
    )

    ninja.rule(
        "charset",
        description="Building charset",
        command=f"$python {BUILD_TOOLS}/pm_charset.py $out $out.rsp",
        rspfile="$out.rsp",
        rspfile_content="$in_newline",
    )

    ninja.rule(
        "charset_palettes",
        description="Building charset palettes",
        command=f"$python {BUILD_TOOLS}/pm_charset_palettes.py $out $out.rsp",
        rspfile="$out.rsp",
        rspfile_content="$in_newline",
    )

    ninja.rule(
        "sprite_shading_profiles",
        description="Building sprite shading profiles",
        command=f"$python {BUILD_TOOLS}/sprite/sprite_shading_profiles.py $in $out $header_path",
    )

    ninja.rule(
        "imgfx_data",
        description="Generating image effects data",
        command=f"$python {BUILD_TOOLS}/imgfx/imgfx_data.py $in $out",
    )

    ninja.rule(
        "shape",
        description="Converting map shape $in",
        command=f"$python {BUILD_TOOLS}/mapfs/shape.py $in $out",
    )

    ninja.rule(
        "effect_data",
        description="Generating effect data",
        command=f"$python {BUILD_TOOLS}/effects.py $in_yaml $out_dir",
    )

    ninja.rule(
        "pm_sbn",
        description="Packing audio",
        command=f"$python {BUILD_TOOLS}/audio/sbn.py $out $asset_stack",
    )

    ninja.rule(
        "flips",
        description="Creating patch file",
        command=f"$python -c \"import subprocess;subprocess.run(['flips','$baserom','$in','$out'])\"",
    )

    ninja.rule(
        "check_segment_sizes",
        description="Checking segment sizes",
        command=f"$python {BUILD_TOOLS}/check_segment_sizes.py $in $data $out",
    )

    ninja.rule(
        "syms",
        description="Reading engine symbols for overlays",
        command=f"$python {BUILD_TOOLS}/overlay.py gen-syms $elf $out $symbol_files",
        restat=True,
    )

    ninja.rule(
        "ovl_link_convert",
        description="Linking overlay $ovl_src",
        command=f"$python {BUILD_TOOLS}/overlay.py link $syms $out $link_addr $force_export $max_loaded_size $require_resolved $in",
    )

    ninja.rule(
        "ovl_apply",
        description="Applying overlays",
        command=f"$python {BUILD_TOOLS}/overlay.py apply-all $in $out $syms $manifest",
    )


def write_ninja_for_tools(ninja: NinjaWriter):
    if CRC_TOOL != "n64crc":
        ninja.rule(
            "cc_tool",
            description="Building tool $out",
            command=f"cc -w $in -O3 -o $out",
        )
        ninja.build(CRC_TOOL, "cc_tool", f"{BUILD_TOOLS}/rom/n64crc.c")


class Configure:
    def __init__(self, version: str):
        self.version = version
        self.version_path = ROOT / f"ver/{version}"

    def dump_stamp(self) -> Path:
        return self.build_path() / "assets_dumped.stamp"

    def load(self) -> None:
        """Read the version's configuration and scan what it points at."""
        self.layout = Layout(self.version_path / "layout.yaml")
        self.asset_stack: List[str] = self.layout.asset_stack
        self.sources_config = SegmentMap(self.layout, ROOT / "src")
        self.all_sources = self.sources_config.scan()
        self.sources = {
            segment: [
                source
                for source in sources
                if not self.is_overlay_source_path(source)
            ]
            for segment, sources in self.all_sources.items()
        }

    def dump(self, assets: bool, code: bool) -> None:
        """Split the assets out of the baserom.

        This is all splat is needed for, and only until the assets are on disk,
        so configure skips it once they have been dumped.
        """
        import splat.scripts.split as split

        modes = ["ld"]
        if assets:
            modes.extend(
                [
                    "bin",
                    "rodatabin",
                    "textbin",
                    "yay0",
                    "img",
                    "vtx",
                    "vtx_common",
                    "gfx",
                    "gfx_common",
                    "pm_map_data",
                    "pm_icons",
                    "pm_msg",
                    "pm_sprites",
                    "pm_charset",
                    "pm_charset_palettes",
                    "pm_effect_loads",
                    "pm_sprite_shading_profiles",
                    "pm_imgfx_data",
                    "pm_sbn",
                ]
            )
        if code:
            modes.extend(["code", "c", "data", "rodata"])

        splat_files = [Path(self.version_path / "splat.yaml")]

        split.main(
            splat_files,
            modes,
            verbose=False,
        )
        self.dump_stamp().parent.mkdir(parents=True, exist_ok=True)
        self.dump_stamp().write_text("")

    @staticmethod
    def source_relative_path(path: Path) -> Union[Path, None]:
        try:
            return Path(path).resolve().relative_to((ROOT / "src").resolve())
        except ValueError:
            return None

    @classmethod
    def is_effect_source_path(cls, path: Path) -> bool:
        relative = cls.source_relative_path(path)
        return (
            relative is not None
            and relative.parent == Path("effects")
            and relative.suffix in (".c", ".cpp")
        )

    @classmethod
    def is_world_action_source_path(cls, path: Path) -> bool:
        relative = cls.source_relative_path(path)
        return (
            relative is not None
            and relative.parent == Path("world/action")
            and relative.suffix in (".c", ".cpp")
        )

    @classmethod
    def is_battle_menu_source_path(cls, path: Path) -> bool:
        relative = cls.source_relative_path(path)
        return relative is not None and posix(relative) in BATTLE_MENU_SOURCES

    @classmethod
    def is_entity_overlay_source_path(cls, path: Path) -> bool:
        relative = cls.source_relative_path(path)
        if relative is None or relative.parts[:1] != ("entity",):
            return False
        entity_relative = Path(*relative.parts[1:])
        return (
            relative.suffix in (".c", ".cpp")
            and "model" not in entity_relative.parts
            and entity_relative.name not in ("Shadow.c", "blueprints.inc.c")
        )

    @classmethod
    def is_overlay_source_path(cls, path: Path) -> bool:
        """Whether a source is linked into an overlay instead of the main ELF."""
        relative = cls.source_relative_path(path)
        if relative is None:
            return False
        parts = relative.parts
        return (
            cls.is_effect_source_path(path)
            or cls.is_world_action_source_path(path)
            or cls.is_battle_menu_source_path(path)
            or cls.is_entity_overlay_source_path(path)
            or parts[:2] in (
                ("world", "partner"),
                ("battle", "partner"),
                ("battle", "action_cmd"),
                ("battle", "move"),
                ("battle", "actor"),
            )
            or parts[:2] == ("world", "area") and len(parts) >= 5
        )

    def textures(self) -> Dict[Path, Path]:
        """Every standalone texture, keyed by its path relative to the assets root.

        Directories that are packed into a blob are skipped whole: they hold
        thousands of images that feed a packer rather than being textures in
        their own right.
        """
        packed = self.layout.packed_dirs
        found: Dict[str, Path] = {}
        for layer in reversed(self.asset_stack):
            root = ROOT / "assets" / layer
            if not root.is_dir():
                continue
            base = str(root)
            for directory, subdirectories, filenames in os.walk(base):
                relative = os.path.relpath(directory, base)
                prefix = "" if relative == "." else relative.replace(os.sep, "/") + "/"
                subdirectories[:] = [
                    name for name in subdirectories if prefix + name not in packed
                ]
                for filename in filenames:
                    if filename.endswith(".png"):
                        found[prefix + filename] = Path(directory) / filename
        return {Path(name): found[name] for name in sorted(found)}

    def register_asset(self, object_path: Path) -> None:
        """Record an object so the linker script can place it in its segment."""
        segment = self.layout.segment_of_asset(
            Path(posix(object_path)[len(posix(self.build_path())) + 1 :])
        )
        if segment is not None:
            self.asset_objects.setdefault(segment, []).append(object_path)

    def write_effect_stub_rules(self, build) -> None:
        """Generate the resident dispatcher and trampolines for effect overlays."""
        effects_yaml = Path("src/registry/effects.yaml")
        effects = effects_from_yaml(ROOT / effects_yaml)
        stubs = [("dispatch", "dispatch", 0)] + [
            ("load", effect.name, index)
            for index, effect in enumerate(effects)
            if not effect.empty
        ]

        stub_tool = Path(BUILD_TOOLS / "effect_stub.py")
        for kind, name, index in stubs:
            source = self.build_path() / "asm/effects" / (name + ".s")
            build(
                source,
                [effects_yaml],
                "effect_stub",
                variables={
                    "kind": kind,
                    "stub_name": name,
                    "stub_index": str(index),
                },
                implicit_deps=[stub_tool, BUILD_TOOLS / "effect_data.py"],
            )
            obj = self.build_path() / "asm/effects" / (name + ".s.o")
            build(
                obj,
                [source],
                "as",
                variables={"cppflags": f"-DVERSION_{self.version.upper()}"},
            )
            self.register_asset(obj)

    def write_blob_rules(self, build) -> None:
        """Link the assets that are copied into the ROM as they are.

        Each is named in layout.yaml; the ones that are not on disk are
        produced by a packer and built elsewhere.
        """
        recipes = {".bin": "bin", ".a": "cp", ".s": "as"}
        for asset, _segment in sorted(self.layout.asset_files.items()):
            source = self.resolve_asset_path(Path(asset))
            task = recipes.get(source.suffix)
            if task is None or not (ROOT / source).is_file():
                continue
            obj = self.build_path() / (asset + ".o")
            build(obj, [source], task)
            self.register_asset(obj)

    def imgfx_animations(self) -> List[Path]:
        """The image effect animations, across the asset stack."""
        found: Dict[str, Path] = {}
        for layer in reversed(self.asset_stack):
            for source in (ROOT / "assets" / layer / "imgfx").glob("*.json"):
                found[source.name] = source.relative_to(ROOT)
        return [found[name] for name in sorted(found)]

    def write_packer_rules(self, build, ninja, skip_outputs) -> None:
        """Pack the assets that become one blob in the ROM."""
        version_assets = Path("assets") / self.version
        asset_stack = ",".join(self.asset_stack)

        def packed(name: str, task: str, inputs, object_name=None, **kwargs):
            """A packer writes a blob, which is then wrapped as an object."""
            blob = self.build_path() / version_assets / name
            build(blob, inputs, task, **kwargs)
            obj = self.build_path() / version_assets / (object_name or (name + ".o"))
            build(obj, [blob], "bin")
            self.register_asset(obj)

        icon_header = posix(self.build_path() / "include" / "icon_offsets.h")
        packed(
            "icons.bin",
            "icons",
            [version_assets / "icon/Icons.xml"],
            variables={"header_path": icon_header, "asset_stack": asset_stack},
            implicit_outputs=[icon_header],
            asset_deps=["icon"],
        )

        shading_header = posix(
            self.build_path() / "include/sprite/sprite_shading_profiles.h"
        )
        packed(
            "sprite_shading_profiles.bin",
            "sprite_shading_profiles",
            [version_assets / "sprite/sprite_shading_profiles.json"],
            variables={"header_path": shading_header},
            implicit_outputs=[shading_header],
        )

        audio = version_assets / "audio"
        packed(
            "audio.sbn",
            "pm_sbn",
            [audio],
            variables={"asset_stack": asset_stack},
            asset_deps=[audio],
        )

        # Each animation is reached by name from a table in the engine, so the
        # order these are emitted in only decides where they sit.
        imgfx_c = version_assets / "imgfx" / "imgfx_data.c"
        build(imgfx_c, self.imgfx_animations(), "imgfx_data")
        imgfx_obj = self.build_path() / (posix(imgfx_c) + ".o")
        build(
            imgfx_obj,
            [imgfx_c],
            "cc_modern",
            variables={
                "cflags": "",
                "cppflags": f"-DVERSION_{self.version.upper()} -DMODERN_COMPILER",
            },
        )
        self.register_asset(imgfx_obj)

        self.write_sprite_rules(build, packed, version_assets, asset_stack)
        self.write_message_rules(build, ninja, skip_outputs, version_assets)

    def write_sprite_rules(self, build, packed, version_assets, asset_stack) -> None:
        """Compress each NPC sprite, then pack them with the player's."""
        import re

        names = re.findall(
            r'<Sprite name="([^"]+)"',
            (ROOT / self.resolve_asset_path(version_assets / "sprite/npc.xml")).read_text(),
        )
        sprite_dir = self.build_path() / version_assets / "sprite"
        compressed = []
        for sprite_id, name in enumerate(names, 1):
            source = version_assets / "sprite/npc" / name
            raw = sprite_dir / "npc" / (name + ".bin")
            packed_sprite = raw.with_suffix(".Yay0")
            compressed.append(packed_sprite)
            build(
                raw,
                [source],
                "npc_sprite",
                variables={"sprite_name": name, "asset_stack": asset_stack},
                asset_deps=[posix(source)],
            )
            build(packed_sprite, [raw], "yay0")
            build(
                self.build_path() / "include/sprite/npc" / (name + ".h"),
                [source, packed_sprite],
                "sprite_header",
                variables={
                    "sprite_name": name,
                    "sprite_id": str(sprite_id),
                    "asset_stack": asset_stack,
                },
            )

        player_header = posix(self.build_path() / "include/sprite/player.h")
        packed(
            "sprite/sprites.bin",
            "sprites",
            [version_assets / "sprite", *compressed],
            object_name="sprite/sprites.o",
            variables={
                "header_out": player_header,
                "build_dir": posix(sprite_dir),
                "asset_stack": asset_stack,
            },
            implicit_outputs=[player_header],
            asset_deps=["sprite/player"],
        )

    def write_message_rules(self, build, ninja, skip_outputs, version_assets) -> None:
        """Compile each message file, then combine them in asset stack order."""
        blob = self.build_path() / version_assets / "msg"
        message_bins = []
        layer_sizes = []
        for layer in reversed(self.asset_stack):
            directory = Path("assets") / layer / "msg"
            count = 0
            if directory.exists():
                for source in sorted(directory.glob("*.msg")):
                    bin_path = blob / f"{len(message_bins):02X}.bin"
                    message_bins.append(bin_path)
                    skip_outputs.add(posix(bin_path))
                    ninja.build(
                        outputs=[posix(bin_path)],
                        rule="msg",
                        inputs=[posix(source)],
                        variables={"version": self.version},
                    )
                    count += 1
            layer_sizes.append(str(count))

        build(
            [
                Path(posix(blob) + ".bin"),
                self.build_path() / "include" / "message_ids.h",
            ],
            message_bins,
            "msg_combine",
            variables={"layer_sizes": ",".join(layer_sizes)},
        )
        obj = Path(posix(blob) + ".o")
        build(obj, [Path(posix(blob) + ".bin")], "bin")
        self.register_asset(obj)

    def mapfs_contents(self) -> List[Path]:
        """Everything the map filesystem holds, found by looking for it.

        The filesystem is looked up by name at runtime, so the order here only
        decides where things sit in the ROM. Adding a map means adding its
        files; nothing else has to be told about it.
        """
        mapfs = Path("assets") / self.version / "mapfs"

        def names(directory: str, pattern: str) -> List[str]:
            found = set()
            for layer in self.asset_stack:
                found.update(
                    path.name
                    for path in (ROOT / "assets" / layer / "mapfs" / directory).glob(
                        pattern
                    )
                )
            return sorted(found)

        contents = []
        for shape in names("geom", "*_shape.bin"):
            name = shape[: -len("_shape.bin")]
            # The shape is rebuilt before packing; the collision is packed as is.
            contents.append(mapfs / "geom" / f"{name}_shape_built.bin")
            contents.append(mapfs / "geom" / f"{name}_hit.bin")
        contents += [mapfs / "tex" / f"{n[:-5]}.bin" for n in names("tex", "*_tex.json")]
        contents += [mapfs / "bg" / n for n in names("bg", "*_bg.png")]
        contents.append(mapfs / "title_data.bin")
        contents += [mapfs / "party" / n for n in names("party", "*.png")]
        return contents

    def write_mapfs_rules(self, build, c_maps) -> None:
        """Build the map filesystem."""
        src_paths = self.mapfs_contents()

        seg_name = "mapfs"
        object_path = self.build_path() / "assets" / self.version / "mapfs.dat.o"
        # flat list of (uncompressed path, compressed? path) pairs
        bin_yay0s: List[Path] = []
        src_dir = Path("assets/x") / seg_name

        for path in src_paths:
            name = path.stem
            out_dir = object_path.with_suffix("").with_suffix("")
            bin_path = out_dir / f"{name}.bin"

            if name.startswith("party_"):
                compress = True
                build(
                    bin_path,
                    [path],
                    "img",
                    variables={
                        "img_type": "party",
                        "img_flags": "",
                    },
                )
            elif path.suffixes[-2:] == [".raw", ".dat"]:
                compress = False
                bin_path = path
            elif name == "title_data":
                compress = True

                logotype_path = out_dir / "title_logotype.bin"
                copyright_path = out_dir / "title_copyright.bin"
                copyright_pal_path = out_dir / "title_copyright.pal"  # jp only
                press_start_path = out_dir / "title_press_start.bin"

                build(
                    logotype_path,
                    [src_dir / "title/logotype.png"],
                    "pigment",
                    variables={
                        "img_type": "rgba32",
                        "img_flags": "",
                    },
                )
                build(
                    press_start_path,
                    [src_dir / "title/press_start.png"],
                    "pigment",
                    variables={
                        "img_type": "ia8",
                        "img_flags": "",
                    },
                )

                if self.version == "jp":
                    build(
                        copyright_path,
                        [src_dir / "title/copyright.png"],
                        "pigment",
                        variables={
                            "img_type": "ci4",
                            "img_flags": "",
                        },
                    )
                    build(
                        copyright_pal_path,
                        [src_dir / "title/copyright.png"],
                        "pigment",
                        variables={
                            "img_type": "palette",
                            "img_flags": "",
                        },
                    )
                    imgs = [
                        logotype_path,
                        copyright_path,
                        press_start_path,
                        copyright_pal_path,
                    ]
                else:
                    build(
                        copyright_path,
                        [src_dir / "title/copyright.png"],
                        "pigment",
                        variables={
                            "img_type": "ia8",
                            "img_flags": "",
                        },
                    )
                    imgs = [logotype_path, copyright_path, press_start_path]

                build(bin_path, imgs, "pack_title_data")
            elif name.endswith("_bg"):
                compress = True
                build(
                    bin_path,
                    [path],
                    "img",
                    variables={
                        "img_type": "bg",
                        "img_flags": "",
                    },
                    # The builder picks up <name>.<n>.png as further palettes.
                    implicit_deps=sorted(
                        (ROOT / path.parent).glob(path.name.split(".")[0] + ".*.png")
                    ),
                )
            elif name.endswith("_tex"):
                compress = False
                tex_dir = path.parent / name
                build(
                    bin_path,
                    [tex_dir, path.parent / (name + ".json")],
                    "tex",
                    variables={
                        "tex_name": name,
                        "asset_stack": ",".join(self.asset_stack),
                    },
                    asset_deps=[f"mapfs/tex/{name}"],
                )
            elif name.endswith("_shape_built"):
                base_name = name[:-6]
                map_name = base_name[:-6]
                raw_bin_path = self.resolve_asset_path(
                    f"assets/x/mapfs/geom/{base_name}.bin"
                )
                bin_path = bin_path.parent / "geom" / (base_name + ".bin")

                if c_maps:
                    # raw bin -> c -> o -> elf -> objcopy -> final bin file
                    c_file_path = (
                        bin_path.parent / "geom" / base_name
                    ).with_suffix(".c")
                    o_path = bin_path.parent / "geom" / (base_name + ".o")
                    elf_path = bin_path.parent / "geom" / (base_name + ".elf")

                    build(c_file_path, [raw_bin_path], "shape")
                    build(
                        o_path,
                        [c_file_path],
                        "cc_modern",
                        variables={
                            "cflags": "",
                            "cppflags": f"-DVERSION_{self.version.upper()}",
                        },
                    )
                    build(elf_path, [o_path], "shape_ld")
                    build(bin_path, [elf_path], "shape_objcopy")
                else:
                    build(bin_path, [raw_bin_path], "cp")

                xml_path = self.resolve_asset_path(
                    f"assets/x/mapfs/geom/{map_name}.xml"
                )
                if xml_path.exists():
                    build(
                        self.build_path()
                        / "include/mapfs"
                        / (base_name + ".h"),
                        [xml_path],
                        "map_header",
                    )

                compress = True
                out_dir = out_dir / "geom"
            elif name.endswith("_hit"):
                base_name = name
                map_name = base_name[:-4]
                raw_bin_path = self.resolve_asset_path(
                    f"assets/x/mapfs/geom/{base_name}.bin"
                )

                # TEMP: star rod compatiblity
                old_raw_bin_path = self.resolve_asset_path(
                    f"assets/x/mapfs/{base_name}.bin"
                )
                if old_raw_bin_path.is_file():
                    raw_bin_path = old_raw_bin_path

                bin_path = bin_path.parent / "geom" / (base_name + ".bin")
                build(bin_path, [raw_bin_path], "cp")

                xml_path = self.resolve_asset_path(
                    f"assets/x/mapfs/geom/{map_name}.xml"
                )
                if xml_path.exists():
                    build(
                        self.build_path()
                        / "include/mapfs"
                        / (base_name + ".h"),
                        [xml_path],
                        "map_header",
                    )
            else:
                compress = True
                bin_path = path

            if compress:
                yay0_path = out_dir / f"{name}.Yay0"
                build(yay0_path, [bin_path], "yay0")
            else:
                yay0_path = bin_path

            bin_yay0s.append(bin_path)
            bin_yay0s.append(yay0_path)

        # combine
        build(object_path.with_suffix(""), bin_yay0s, "mapfs")
        build(object_path, [object_path.with_suffix("")], "bin")

        self.register_asset(object_path)

    def charset_sources(self, directory: str) -> List[Path]:
        """The images of one font, across the asset stack."""
        found: Dict[str, Path] = {}
        for layer in reversed(self.asset_stack):
            root = ROOT / "assets" / layer / "charset" / directory
            if root.is_dir():
                for source in root.glob("*.png"):
                    found[source.name] = source.relative_to(ROOT)
        return [found[name] for name in sorted(found)]

    def write_charset_rules(self, build) -> None:
        """Pack each font's glyphs and palettes into the files the text engine reads.

        The .dat files are included raw by the character set source rather than
        linked, so no object is built for them.
        """
        charset = Path("assets") / self.version / "charset"
        for name in self.layout.charsets:
            glyphs = []
            for source in self.charset_sources(name):
                raster = self.build_path() / "charset" / name / (source.stem + ".bin")
                build(
                    raster,
                    [source],
                    "pigment",
                    variables={"img_type": "ci4", "img_flags": ""},
                )
                glyphs.append(raster)
            build(self.build_path() / charset / (name + ".dat"), glyphs, "charset")

            palettes = []
            for source in self.charset_sources(f"{name}/palette"):
                raster = (
                    self.build_path()
                    / "charset"
                    / name
                    / "palette"
                    / (source.stem + ".bin")
                )
                build(
                    raster,
                    [source],
                    "pigment",
                    variables={"img_type": "palette", "img_flags": ""},
                )
                palettes.append(raster)
            build(
                self.build_path() / charset / name / "palette.dat",
                palettes,
                "charset_palettes",
            )

    def write_texture_rules(self, build) -> None:
        """Convert each texture to the binary and header the game includes."""
        symbols = assets.include_symbols(ROOT / "src")
        wanted_palettes = assets.included_palettes(ROOT / "src")
        for relative, png in self.textures().items():
            texture = assets.Texture(png.relative_to(ROOT), self.asset_stack)
            stem = relative.with_suffix("")
            asset_path = Path("assets") / self.version / relative

            # A texture with a segment of its own is linked, so its object sits
            # beside the asset; the rest are included into C and do not.
            linked = self.layout.segment_of_asset(
                asset_path.with_suffix(".png.o")
            ) is not None
            out_dir = self.build_path() / (asset_path.parent if linked else stem.parent)

            # A dotted name carries a variant palette for the image it is named
            # after, and contributes nothing else.
            variant = "." in stem.name
            if not variant:
                build(
                    out_dir / (stem.name + ".png.bin"),
                    [png.relative_to(ROOT)],
                    "pigment",
                    variables={
                        "img_type": texture.format,
                        "img_flags": texture.flags(),
                    },
                )
                build(
                    self.build_path() / "include" / stem.parent / (stem.name + ".png.h"),
                    [png.relative_to(ROOT)],
                    "img_header",
                    variables={"c_name": symbols.get(relative.as_posix(), "")},
                )
                if linked:
                    obj = out_dir / (stem.name + ".png.o")
                    build(obj, [out_dir / (stem.name + ".png.bin")], "bin")
                    self.register_asset(obj)
            needs_palette = (
                relative.as_posix() in wanted_palettes
                or self.layout.segment_of_asset(
                    asset_path.with_suffix(".pal.o")
                )
                is not None
            )
            if texture.png.palette_size is not None and needs_palette:
                build(
                    out_dir / (stem.name + ".pal.bin"),
                    [png.relative_to(ROOT)],
                    "pigment",
                    variables={"img_type": "palette", "img_flags": ""},
                )
                if linked:
                    obj = out_dir / (stem.name + ".pal.o")
                    build(obj, [out_dir / (stem.name + ".pal.bin")], "bin")
                    self.register_asset(obj)

    def source_object(self, src_path: Path) -> Path:
        return self.build_path() / (str(src_path) + ".o")

    def build_segments(self) -> List["linker.Segment"]:
        """Segments in ROM order, with their objects.

        layout.yaml supplies the segments and their addresses, segments.py the
        source objects. splat supplies only the asset objects it splits.
        """
        declared = {seg.name for seg in self.layout.segments}
        # Objects are placed by iterating the layout, so a segment name nothing
        # declares would drop its objects out of the ROM without a diagnostic.
        undeclared = sorted(
            (set(self.sources) | set(self.asset_objects)) - declared
        )
        if undeclared:
            raise SystemExit(
                f"configure: {self.version}/layout.yaml declares no segment named "
                + ", ".join(undeclared)
            )

        build_prefix = posix(self.build_path()) + "/"
        roots = (f"assets/{self.version}/", "src/", f"ver/{self.version}/")
        label = lambda obj: linker.data_label(obj, build_prefix, roots)
        assets = {
            segment: [(posix(o), label(posix(o))) for o in sorted(objects, key=posix)]
            for segment, objects in self.asset_objects.items()
        }

        segments = []
        for seg in self.layout.segments:
            objects = [
                (posix(self.source_object(p)), label(posix(self.source_object(p))))
                for p in self.sources.get(seg.name, [])
            ] + assets.get(seg.name, [])
            segments.append(
                linker.Segment(
                    seg.name,
                    seg.vram_expr,
                    seg.subalign,
                    objects,
                    seg.vram_class and seg.vram_class.name,
                )
            )
        empty = [segment.name for segment in segments if not segment.objects]
        if empty:
            raise SystemExit(
                f"configure: {self.version}/layout.yaml declares empty segments: "
                + ", ".join(empty)
                + "; runtime overlays must not be listed as resident segments"
            )
        return segments

    def source_cflags(self, src: Path, segment: str, non_matching: bool) -> str:
        parts = src.parts
        libultra = "nusys" in parts or "os" in parts
        cflags = self.sources_config.cflags(src)
        if cflags is None:
            cflags = "" if libultra else "-fforce-addr"
        if libultra:
            cflags += (
                " -Wno-maybe-uninitialized -Wno-inline -Wno-pointer-to-int-cast"
                " -Wno-strict-aliasing -Wno-pointer-sign"
            )
        if "gcc" in parts:
            cflags += " -Wno-pointer-sign"
        # Effects are TLB mapped, so they must not call memset and friends.
        if "effects" in parts:
            cflags += " -fno-tree-loop-distribute-patterns"
        if non_matching or segment not in ("main", "engine1", "engine2"):
            cflags += " -fno-common"
        return cflags.strip()

    def build_path(self) -> Path:
        return Path(f"ver/{self.version}/build")

    def undefined_syms_path(self) -> Path:
        return self.build_path() / "undefined_syms.txt"

    def elf_path(self) -> Path:
        # TODO: read basename and build_path from splat.yaml
        return Path(f"ver/{self.version}/build/papermario.elf")

    def base_rom_path(self) -> Path:
        return Path(f"ver/{self.version}/build/papermario_base.z64")

    def rom_path(self) -> Path:
        return Path(f"ver/{self.version}/build/papermario.z64")

    def rom_ok_path(self) -> Path:
        return self.elf_path().with_suffix(".ok")

    def patch_path(self) -> Path:
        return self.elf_path().with_suffix(".bps")

    def baserom_path(self) -> Path:
        return Path(f"ver/{self.version}/baserom.z64")

    def linker_script_path(self) -> Path:
        # TODO: read from splat.yaml
        return Path(f"ver/{self.version}/papermario.ld")

    def map_path(self) -> Path:
        return self.elf_path().with_suffix(".map")

    def syms_path(self) -> Path:
        return self.build_path() / "syms.pkl"

    def resolve_src_paths(self, src_paths: List[Path]) -> List[str]:
        out = []

        for path in src_paths:
            path = self.resolve_asset_path(path)

            if path is not None:
                if path.is_dir():
                    out.extend(sorted(posix(p) for p in glob(str(path) + "/**/*", recursive=True)))
                else:
                    out.append(posix(path))

        return out

    # Given a directory relative to assets/, return a list of all assets in the directory
    # for all layers of the asset stack
    def get_asset_list(self, asset_dir: str) -> List[str]:
        ret: Dict[Path, Path] = {}

        for stack_dir in self.asset_stack:
            path_stem = f"assets/{stack_dir}/{asset_dir}"

            for p in Path(path_stem).glob("**/*"):
                glob_part = p.relative_to(path_stem)
                if glob_part not in ret:
                    ret[glob_part] = p

        return sorted(posix(v) for v in ret.values())

    @lru_cache(maxsize=None)
    def resolve_asset_path(self, path: Path) -> Path:
        # Remove nonsense
        path = Path(os.path.normpath(path))

        parts = list(path.parts)

        if parts[0] != "assets":
            return path

        for asset_dir in self.asset_stack:
            parts[1] = asset_dir
            new_path = Path("/".join(parts))
            if new_path.exists():
                return new_path

        return path

    def _sidecar_target_consumed(
        self, sidecar: Path, layer: str, consumed_assets: Set[str]
    ) -> bool:
        """Whether the asset a `.meta` sidecar annotates is itself built.

        A sidecar carries no pixels, so it never reaches ninja; it earns its
        place only by describing an asset that some rule reads. The asset can
        live in a different layer than the sidecar, so resolve it through the
        stack.
        """
        rel = Path(os.path.relpath(str(sidecar), ROOT / "assets" / layer))
        if sidecar.name == assets.DIRECTORY_SIDECAR:
            directory = rel.parent.as_posix()
            directory = "" if directory == "." else directory + "/"
            prefixes = tuple(f"assets/{name}/{directory}" for name in self.asset_stack)
            return any(path.startswith(prefixes) for path in consumed_assets)
        target = rel.as_posix()[: -len(assets.SIDECAR_SUFFIX)]
        resolved = self.resolve_asset_path(Path("assets") / layer / target)
        return posix(os.path.relpath(str(resolved), ROOT)) in consumed_assets

    def check_asset_coverage(
        self, consumed: Set[str], produced: Set[str]
    ) -> List[str]:
        """Files under a hand-authored asset layer that no build rule reads.

        The last asset_stack layer is split from the baserom and checked by
        tools/build/check_assets.py; the earlier layers are hand-authored, so a
        file there that nothing builds is a mistake rather than leftover dump.
        """
        consumed_assets = {p for p in consumed if p.startswith("assets/")}
        produced_assets = {p for p in produced if p.startswith("assets/")}

        orphans: List[str] = []
        for layer in self.asset_stack[:-1]:
            root = ROOT / "assets" / layer
            if not root.is_dir():
                continue
            for directory, _subdirs, filenames in os.walk(root):
                for filename in sorted(filenames):
                    path = Path(directory) / filename
                    rel = posix(os.path.relpath(str(path), ROOT))
                    if filename in IGNORED_ASSET_NAMES:
                        continue
                    if filename.endswith((".inc.c", ".inc.cpp")):
                        continue
                    if rel in consumed_assets or rel in produced_assets:
                        continue
                    if filename.endswith(assets.SIDECAR_SUFFIX) and (
                        self._sidecar_target_consumed(path, layer, consumed_assets)
                    ):
                        continue
                    orphans.append(rel)
        return sorted(orphans)

    def write_ninja(
        self,
        ninja: NinjaWriter,
        skip_outputs: Set[str],
        non_matching: bool,
        c_maps: bool = False,
        evt_validation: bool = True,
    ) -> List[str]:

        built_objects = set()
        evt_validation_stamps = []
        generated_code = []
        inc_img_bins = []
        precompiled_header_path = Path("include/common.h.gch")
        cxx_precompiled_header_path = Path("include/common.hpp.gch")

        def build(
            object_paths: Union[Path, List[Path]],
            src_paths: List[Path],
            task: str,
            variables: Dict[str, str] = {},
            implicit_outputs: List[str] = [],
            asset_deps: List[str] = [],
            implicit_deps: List[str] = [],
        ):
            if not isinstance(object_paths, list):
                object_paths = [object_paths]

            object_strs = [posix(obj) for obj in object_paths]
            needs_build = False

            for object_path in object_paths:
                obj_posix = posix(object_path)
                if object_path.suffixes[-1] == ".o":
                    built_objects.add(obj_posix)
                elif object_path.suffix.endswith(".h") or object_path.suffix.endswith(
                    ".c"
                ):
                    generated_code.append(obj_posix)
                elif object_path.name.endswith(
                    (".png.bin", ".pal.bin", ".dat")
                ):
                    inc_img_bins.append(obj_posix)

                # don't rebuild objects if we've already seen all of them
                if obj_posix not in skip_outputs:
                    needs_build = True

            for i_output in implicit_outputs:
                if i_output.endswith(".h"):
                    generated_code.append(posix(i_output))

            if needs_build:
                skip_outputs.update(object_strs)

                implicit = [posix(dep) for dep in implicit_deps]
                order_only = []

                if task in ["cc", "cxx", "cc_modern", "cxx_modern"]:
                    order_only.append("generated_code_" + self.version)
                    order_only.append("inc_img_bins_" + self.version)
                    if object_paths[0].suffixes[-1] != ".gch":
                        if task == "cc_modern":
                            implicit.append(posix(precompiled_header_path))
                        elif task == "cxx_modern":
                            implicit.append(posix(cxx_precompiled_header_path))

                inputs = self.resolve_src_paths(src_paths)
                for dir in asset_deps:
                    inputs.extend(self.get_asset_list(dir))

                evt_objects = []
                if evt_validation and task in ["cc_modern", "cxx_modern"]:
                    evt_objects = [
                        obj for obj in object_paths if obj.suffixes[-1] == ".o"
                    ]
                evt_stamps = [evt_validation_stamp_path(obj) for obj in evt_objects]
                evt_validation_stamps.extend(evt_stamps)

                ninja.build(
                    outputs=object_strs,  # $out
                    rule=task,
                    inputs=inputs,  # $in
                    implicit=implicit,
                    order_only=order_only,
                    variables={"version": self.version, **variables},
                    implicit_outputs=implicit_outputs,
                    validations=evt_stamps,
                )

                for object_path, evt_validation_stamp in zip(evt_objects, evt_stamps):
                    if len(src_paths) == 1:
                        evt_target = posix(src_paths[0])
                    else:
                        evt_target = evt_validation_display_path(object_path)
                    ninja.build(
                        evt_validation_stamp,
                        "evt_validate_obj",
                        [posix(object_path)],
                        implicit=[
                            posix(BUILD_TOOLS / "evt_validate_obj.py"),
                            posix(BUILD_TOOLS / "effect_data.py"),
                            "src/registry/effects.yaml",
                        ],
                        variables={"evt_target": evt_target},
                    )

        # Effect data includes
        effect_yaml = ROOT / "src/registry/effects.yaml"
        effect_data_outdir = ROOT / "assets" / version / "effects"
        effect_defs_path = effect_data_outdir / "effect_defs.h"
        effect_table_path = effect_data_outdir / "effect_table.c"

        build(
            [effect_defs_path, effect_table_path],
            [
                effect_yaml,
                BUILD_TOOLS / "effects.py",
                BUILD_TOOLS / "effect_data.py",
            ],
            "effect_data",
            variables={
                "in_yaml": posix(effect_yaml),
                "out_dir": posix(effect_data_outdir),
            },
        )

        build(
            self.build_path() / "include/world_map.inc.c",
            [Path("src/world_map.xml")],
            "world_map",
        )

        # gen_areas counts a directory as a map once it holds a source file to
        # compile, so the stamp records that rather than just which directories
        # exist: otherwise adding the first source to one leaves the table stale.
        gen_areas_stamp = self.build_path() / "gen_areas.stamp"
        area_dirs = []
        for area_root in [ROOT / "src" / "world" / "area"] + [
            ROOT / "assets" / d / "world" / "area" for d in self.asset_stack
        ]:
            if area_root.is_dir():
                for area_dir in sorted(area_root.iterdir()):
                    if area_dir.is_dir():
                        for map_dir in sorted(area_dir.iterdir()):
                            if map_dir.is_dir() and any(
                                f.suffix in (".c", ".cpp")
                                and not f.name.endswith((".inc.c", ".inc.cpp"))
                                for f in map_dir.iterdir()
                            ):
                                area_dirs.append(str(map_dir.relative_to(ROOT)))
        gen_areas_stamp.parent.mkdir(parents=True, exist_ok=True)
        gen_areas_stamp.write_text("\n".join(area_dirs) + "\n")
        build(
            self.build_path() / "include/world/gAreas.inc.c",
            [Path(BUILD_TOOLS / "gen_areas.py"), gen_areas_stamp],
            "gen_areas",
            variables={
                "src_dir": "src/world",
                "asset_stack": ",".join(self.asset_stack),
            },
        )

        if self.version == "jp":
            build(
                self.build_path() / "include/recipes.inc.c",
                [Path("src/registry/recipes_jp.yaml")],
                "recipes",
            )
        else:
            build(
                self.build_path() / "include/recipes.inc.c",
                [Path("src/registry/recipes.yaml")],
                "recipes",
            )

        build(
            [
                self.build_path() / "include/move_data.inc.c",
                self.build_path() / "include/move_enum.h",
            ],
            [Path("src/registry/moves.yaml")],
            "move_data",
        )

        build(
            [
                self.build_path() / "include/item_data.inc.c",
                self.build_path() / "include/item_enum.h",
            ],
            [Path("src/registry/items.yaml")],
            "item_data",
            variables={
                "asset_stack": ",".join(self.asset_stack),
            },
        )

        action_data_path = self.build_path() / "include/action_data.inc.c"
        action_enum_path = self.build_path() / "include/action_state_enum.h"
        build(
            [action_data_path, action_enum_path],
            [
                Path("src/registry/actions.yaml"),
                BUILD_TOOLS / "action_data.py",
            ],
            "action_data",
            variables={
                "out_data": posix(action_data_path),
                "out_enum": posix(action_enum_path),
                "actions_yaml": "src/registry/actions.yaml",
            },
        )

        if self.version == "jp":
            build(
                [
                    self.build_path() / "include/battle/actor_types.inc.c",
                    self.build_path() / "include/battle/actor_types.h",
                ],
                [
                    Path("src/registry/actors_jp.yaml"),
                ],
                "actor_types",
            )
        else:
            build(
                [
                    self.build_path() / "include/battle/actor_types.inc.c",
                    self.build_path() / "include/battle/actor_types.h",
                ],
                [
                    Path("src/registry/actors.yaml"),
                ],
                "actor_types",
            )

        build([precompiled_header_path], [Path("include/common.h")], "cc_modern")
        build([cxx_precompiled_header_path], [Path("include/common.hpp")], "cxx_modern")

        self.asset_objects: Dict[str, List[Path]] = {}
        self.write_effect_stub_rules(build)
        self.write_blob_rules(build)
        self.write_packer_rules(build, ninja, skip_outputs)
        self.write_mapfs_rules(build, c_maps)
        self.write_charset_rules(build)
        self.write_texture_rules(build)

        # Every asset object is registered by now, so the segments are complete.
        segments = self.build_segments()
        linker.write_script(
            ROOT / self.linker_script_path(),
            segments,
            self.layout.follows,
            self.layout.class_vrams,
        )
        linker.write_symbol_header(
            ROOT / self.build_path() / "include/ld_addrs.h", segments
        )

        # Compile everything the filesystem scan found.
        for segment, src_paths in self.sources.items():
            for src in src_paths:
                if src.suffix == ".s":
                    build(
                        self.source_object(src),
                        [src],
                        "as",
                        variables={"cppflags": f"-DVERSION_{self.version.upper()}"},
                    )
                    continue
                build(
                    self.source_object(src),
                    [src],
                    "cxx_modern" if src.suffix == ".cpp" else "cc_modern",
                    variables={
                        "cflags": self.source_cflags(src, segment, non_matching),
                        "cppflags": f"-DVERSION_{self.version.upper()} -DMODERN_COMPILER",
                    },
                )


        # Run undefined_syms through cpp
        ninja.build(
            posix(self.undefined_syms_path()),
            "cpp",
            posix(self.version_path / "undefined_syms.txt"),
        )

        # Build elf, z64, ok
        additional_objects = [posix(self.undefined_syms_path())]

        ninja.build(
            posix(self.elf_path()),
            "ld",
            posix(self.linker_script_path()),
            implicit=sorted(built_objects) + additional_objects,
            variables={"version": self.version, "mapfile": posix(self.map_path())},
        )

        if self.version == "ique":
            ninja.build(
                posix(self.base_rom_path()),
                "z64_ique",
                posix(self.elf_path()),
                variables={"version": self.version},
            )
        else:
            ninja.build(
                posix(self.base_rom_path()),
                "z64",
                posix(self.elf_path()),
                implicit=[CRC_TOOL] if CRC_TOOL != "n64crc" else [],
                variables={"version": self.version},
            )

        if not non_matching:
            ninja.build(
                posix(self.rom_ok_path()),
                "sha1sum",
                f"ver/{self.version}/checksum.sha1",
                implicit=[posix(self.base_rom_path())],
            )
        else:
            ninja.build(
                posix(self.rom_ok_path()),
                "check_segment_sizes",
                posix(self.elf_path()),
                variables={
                    "data": json.dumps(
                        json.dumps(self.get_segment_max_sizes(), separators=(",", ":"))
                    )
                },
                implicit=[posix(self.base_rom_path())],
            )

        ninja.build(
            posix(self.patch_path()),
            "flips",
            posix(self.rom_path()),
            variables={"baserom": posix(self.baserom_path())},
        )

        ninja.build(
            posix(self.syms_path()),
            "syms",
            posix(self.elf_path()),
            implicit=[
                posix(self.version_path / "symbol_addrs.txt"),
                posix(BUILD_TOOLS / "overlay.py"),
            ],
            variables={
                "elf": posix(self.elf_path()),
                "symbol_files": posix(self.version_path / "symbol_addrs.txt"),
            },
        )

        ninja.build("generated_code_" + self.version, "phony", generated_code)
        ninja.build("inc_img_bins_" + self.version, "phony", inc_img_bins)
        return evt_validation_stamps

    def get_segment_max_sizes(self):
        return {
            seg.name: seg.max_size
            for seg in self.layout.segments
            if seg.max_size is not None
        }

    def find_overlays(self) -> List[Tuple[str, Path, List[Path], int]]:
        overlay_types = [
            (OVL_TYPE_EFFECT, "effects/*.c", ""),
            (OVL_TYPE_MAP, "world/area/*/*/", ""),
            (OVL_TYPE_ACTION, "world/action/*.c", ""),
            (OVL_TYPE_PARTNER, "world/partner/*.c", "world_partner_"),
            (OVL_TYPE_ACTOR, "battle/actor/*", ""),
            (OVL_TYPE_BATTLE_PARTNER, "battle/partner/*.c", ""),
            (OVL_TYPE_ACTION_CMD, "battle/action_cmd/*.c", ""),
            (OVL_TYPE_BATTLE_SCRIPT, "battle/move/hammer/*.c", "battle_move_"),
            (OVL_TYPE_BATTLE_SCRIPT, "battle/move/item/*.c", ""),
            (OVL_TYPE_BATTLE_SCRIPT, "battle/move/jump/*.c", "battle_move_"),
            (OVL_TYPE_BATTLE_SCRIPT, "battle/move/star_power/*.c", "battle_move_"),
            (OVL_TYPE_ENTITY, "entity/**/*.c", ""),
        ]

        # Collect overlays keyed by (type_index, name). Later entries in the
        # asset stack override earlier ones; src/ is the lowest-priority layer.
        found: Dict[Tuple[int, str], Tuple[str, Path, List[Path], int]] = {}

        search_dirs = [ROOT / "src"] + [
            ROOT / "assets" / d for d in reversed(self.asset_stack)
        ]
        for search_dir in search_dirs:
            if not search_dir.exists():
                continue
            for type_index, glob_str, name_prefix in overlay_types:
                for match in sorted(
                    search_dir.glob(glob_str, case_sensitive=True),
                    key=lambda p: p.as_posix(),
                ):
                    if match.name.endswith(".inc.c") or match.name.endswith(".inc.cpp"):
                        continue
                    if type_index == OVL_TYPE_EFFECT and match.name == "effect_table.c":
                        continue
                    if type_index == OVL_TYPE_ENTITY and not self.is_entity_overlay_source_path(match):
                        continue
                    if type_index == OVL_TYPE_ENTITY and match.name == "ShatteringBlock_common.c":
                        continue
                    # Skip asset directories that contain no compilable source files
                    # (only .inc.c/.inc.cpp), so they don't shadow src/ overlays
                    if match.is_dir() and not any(
                        f.suffix in (".c", ".cpp")
                        and not f.name.endswith(".inc.c")
                        and not f.name.endswith(".inc.cpp")
                        for f in match.iterdir()
                    ):
                        continue
                    if match.is_dir():
                        sources = [
                            path for path in sorted(match.iterdir())
                            if path.suffix in (".c", ".cpp")
                            and not path.name.endswith((".inc.c", ".inc.cpp"))
                        ]
                    else:
                        sources = [match]
                    if (
                        type_index == OVL_TYPE_BATTLE_SCRIPT
                        and match.name == "attack.c"
                        and match.parent.name in ("hammer", "jump")
                    ):
                        name = f"battle_move_{match.parent.name}_attack"
                    else:
                        name = name_prefix + match.stem
                    found[(type_index, name)] = (
                        name,
                        match,
                        sources,
                        type_index,
                    )

        shattering_key = (OVL_TYPE_ENTITY, "ShatteringBlock")
        if shattering_key in found:
            name, source, sources, type_index = found[shattering_key]
            sources.append(ROOT / "src/entity/ShatteringBlock_common.c")

        # The battle menu is one cohesive overlay assembled from sources that
        # historically straddled the btl_states_menus segment and resident battle
        # code. Resolve each file independently so a higher-priority asset layer
        # can override only the files it supplies.
        menu_sources = []
        for relative_path in BATTLE_MENU_SOURCES:
            source = None
            for stack_dir in self.asset_stack:
                candidate = ROOT / "assets" / stack_dir / relative_path
                if candidate.is_file():
                    source = candidate
                    break
            if source is None:
                candidate = ROOT / "src" / relative_path
                if candidate.is_file():
                    source = candidate
            if source is None:
                raise FileNotFoundError(
                    f"missing battle-menu overlay source: {relative_path}"
                )
            menu_sources.append(source)

        found[(OVL_TYPE_BATTLE_MENU, "battle_menu")] = (
            "battle_menu",
            menu_sources[0],
            menu_sources,
            OVL_TYPE_BATTLE_MENU,
        )

        return sorted(found.values(), key=lambda x: (x[3], x[0]))

    def effect_cflags(self, src_path: Path) -> str:
        """Return the cflags attached to an effect in layout.yaml."""
        cflags = self.sources_config.cflags(Path(src_path)) or "-fforce-addr"
        return cflags.replace("gcc_modern", "").replace("gcc_272", "").strip()

    def write_overlays(
        self, ninja: NinjaWriter, evt_validation: bool = True
    ) -> Tuple[str, List[str]]:
        """Write overlay build statements and return the ROM path and EVT validation stamps."""
        import json

        overlays = self.find_overlays()
        effects = effects_from_yaml(ROOT / "src/registry/effects.yaml")
        actions = actions_from_yaml(ROOT / "src/registry/actions.yaml")
        effect_names = [effect.name for effect in effects if not effect.empty]
        duplicate_effects = sorted(
            name for name in set(effect_names) if effect_names.count(name) > 1
        )
        effect_sources = {
            name for name, _, _, type_index in overlays
            if type_index == OVL_TYPE_EFFECT
        }
        missing_effects = sorted(set(effect_names) - effect_sources)
        orphan_effects = sorted(effect_sources - set(effect_names))
        action_sources = {
            name for name, _, _, type_index in overlays
            if type_index == OVL_TYPE_ACTION
        }
        action_overlays = {action.overlay for action in actions}
        missing_action_overlays = sorted(action_overlays - action_sources)
        orphan_action_overlays = sorted(action_sources - action_overlays)

        errors = []
        if duplicate_effects:
            errors.append("duplicate effect names: " + ", ".join(duplicate_effects))
        if missing_effects:
            errors.append("effects without source overlays: " + ", ".join(missing_effects))
        if orphan_effects:
            errors.append("effect overlays missing from effects.yaml: " + ", ".join(orphan_effects))
        if missing_action_overlays:
            errors.append(
                "actions referencing missing overlays: "
                + ", ".join(missing_action_overlays)
            )
        if orphan_action_overlays:
            errors.append(
                "action overlays missing from actions.yaml: "
                + ", ".join(orphan_action_overlays)
            )
        if errors:
            raise ValueError("invalid overlay configuration\n  " + "\n  ".join(errors))

        c_precompiled_header_path = Path("include/common.h.gch")
        cxx_precompiled_header_path = Path("include/common.hpp.gch")

        manifest_entries = []
        evt_validation_stamps = []
        implicit_deps = [posix(self.syms_path())]
        if CRC_TOOL != "n64crc":
            implicit_deps.append(CRC_TOOL)

        for name, src_path, c_files, type_index in overlays:
            build_dir = self.build_path() / "ovl" / str(type_index) / name
            ovl_path = build_dir / f"{name}.ovl"
            debug_syms_path = build_dir / f"{name}.ovl.debug_syms"
            objects = []
            overlay_evt_validation_stamps = []
            for c_file in c_files:
                if c_file.suffix == ".cpp":
                    task = "cxx_modern"
                    pch = cxx_precompiled_header_path
                else:
                    task = "cc_modern"
                    pch = c_precompiled_header_path
                obj_path = build_dir / (c_file.name + ".o")
                evt_stamps = (
                    [evt_validation_stamp_path(obj_path)] if evt_validation else []
                )
                evt_validation_stamps.extend(evt_stamps)
                overlay_evt_validation_stamps.extend(evt_stamps)
                cflags = "-fno-common -fvisibility=hidden"
                if type_index == OVL_TYPE_EFFECT:
                    effect_cflags = self.effect_cflags(c_file)
                    if effect_cflags:
                        cflags = f"{effect_cflags} {cflags}"
                ninja.build(
                    posix(obj_path),
                    task,
                    posix(c_file),
                    implicit=[posix(pch)],
                    order_only=[
                        "generated_code_" + self.version,
                        "inc_img_bins_" + self.version,
                    ],
                    variables={
                        "version": self.version,
                        "cflags": cflags,
                        "cppflags": f"-DVERSION_{self.version.upper()} -DMODERN_COMPILER",
                    },
                    validations=evt_stamps,
                )
                for evt_validation_stamp in evt_stamps:
                    ninja.build(
                        evt_validation_stamp,
                        "evt_validate_obj",
                        [posix(obj_path)],
                        implicit=[
                            posix(BUILD_TOOLS / "evt_validate_obj.py"),
                            posix(BUILD_TOOLS / "effect_data.py"),
                            "src/registry/effects.yaml",
                        ],
                        variables={"evt_target": posix(c_file)},
                    )
                objects.append(posix(obj_path))

            if len(objects) == 0:
                continue

            link_addr = "0x80000000"
            if type_index == OVL_TYPE_MAP:
                link_addr = "0x80240000"

            force_export = ""
            max_loaded_size = ""
            require_resolved = ""
            if type_index == OVL_TYPE_EFFECT:
                force_export = f"--force-export {name}_main"
                max_loaded_size = "--max-loaded-size 0x1000"
                require_resolved = "--require-resolved"
            elif type_index == OVL_TYPE_MAP:
                max_loaded_size = "--max-loaded-size 0x27FF0"
                require_resolved = "--require-resolved"
            elif type_index == OVL_TYPE_ACTION:
                require_resolved = "--require-resolved"
            elif type_index == OVL_TYPE_PARTNER:
                force_export = "--force-export gWorldPartner"
                require_resolved = "--require-resolved"
            elif type_index == OVL_TYPE_BATTLE_PARTNER:
                force_export = "--force-export gBattlePartner"
                max_loaded_size = "--max-loaded-size 0x5000"
                require_resolved = "--require-resolved"
            elif type_index == OVL_TYPE_ACTION_CMD:
                force_export = "--force-export gActionCommand"
                max_loaded_size = "--max-loaded-size 0x3000"
                require_resolved = "--require-resolved"
            elif type_index == OVL_TYPE_BATTLE_SCRIPT:
                force_export = "--force-export gBattleScriptModule"
                max_loaded_size = "--max-loaded-size 0x4000"
                require_resolved = "--require-resolved"
            elif type_index == OVL_TYPE_BATTLE_MENU:
                force_export = "--force-export gBattleMenu"
                max_loaded_size = "--max-loaded-size 0x10000"
                require_resolved = "--require-resolved"
            elif type_index == OVL_TYPE_ENTITY:
                require_resolved = "--require-resolved"
            elif type_index == OVL_TYPE_ACTOR:
                require_resolved = "--require-resolved"

            overlay_link_deps = [
                posix(self.syms_path()),
                posix(BUILD_TOOLS / "overlay.py"),
            ] + overlay_evt_validation_stamps
            ninja.build(
                posix(ovl_path),
                "ovl_link_convert",
                objects,
                implicit=overlay_link_deps,
                implicit_outputs=[posix(debug_syms_path)],
                variables={
                    "syms": posix(self.syms_path()),
                    "link_addr": link_addr,
                    "ovl_src": posix(src_path.relative_to(ROOT)),
                    "force_export": force_export,
                    "max_loaded_size": max_loaded_size,
                    "require_resolved": require_resolved,
                },
            )

            manifest_entries.append(
                {
                    "name": name,
                    "type_index": type_index,
                    "ovl": posix(ovl_path),
                    "debug_syms": posix(debug_syms_path),
                }
            )
            implicit_deps.append(posix(ovl_path))

        manifest_path = self.build_path() / "ovl" / "manifest.json"
        manifest_path.parent.mkdir(parents=True, exist_ok=True)
        with open(manifest_path, "w", encoding="utf-8") as f:
            json.dump(manifest_entries, f)

        implicit_deps.append(posix(BUILD_TOOLS / "overlay.py"))
        ninja.build(
            posix(self.rom_path()),
            "ovl_apply",
            posix(self.base_rom_path()),
            implicit=implicit_deps,
            variables={
                "syms": posix(self.syms_path()),
                "manifest": posix(manifest_path),
            },
        )
        return posix(self.rom_path()), evt_validation_stamps

    def make_current(self, ninja: NinjaWriter):
        current = Path("ver/current")

        try:
            current.unlink()
        except Exception:
            pass

        if sys.platform == 'win32':
            # symlinks require admin on windows so we create a junction instead
            ntfsutils.junction.create("ver/" + self.version, current)
        else:
            current.symlink_to(self.version)

        ninja.build("ver/current/build/papermario.z64", "phony", posix(self.rom_path()))


if __name__ == "__main__":
    from argparse import ArgumentParser

    parser = ArgumentParser(description="Paper Mario build.ninja generator")
    parser.add_argument(
        "version",
        nargs="*",
        default=[],
        choices=[*VERSIONS, []],
        help="Version(s) to configure for. Most tools will operate on the first-provided only. Supported versions: "
        + ",".join(VERSIONS),
    )
    parser.add_argument("--cpp", help="GNU C preprocessor command")
    parser.add_argument(
        "-c",
        "--clean",
        action="store_true",
        help="Delete assets and previously-built files",
    )
    parser.add_argument(
        "--splat", default="tools/splat", help="Path to splat tool to use"
    )
    parser.add_argument(
        "--split-code", action="store_true", help="Re-split code segments to asm files"
    )
    parser.add_argument(
        "--no-split-assets",
        action="store_true",
        help="Don't split assets from the baserom(s)",
    )
    parser.add_argument(
        "-d", "--debug", action="store_true", help="Generate debugging information"
    )
    parser.add_argument(
        "-N",
        "--no-non-matching",
        action="store_true",
        help="Compile nonmatching code. Combine with --debug for more detailed debug info",
    )
    parser.add_argument(
        "--no-shift",
        action="store_true",
        help="Build a shiftable version of the game (non-matching)",
    )
    parser.add_argument(
        "--no-modern-gcc",
        action="store_true",
        help="Use modern GCC instead of the original compiler",
    )
    parser.add_argument("--no-ccache", action="store_true", help="Use ccache")
    parser.add_argument(
        "--dump",
        action="store_true",
        help="Re-split the assets out of the baserom before configuring",
    )
    parser.add_argument(
        "--incremental",
        action="store_true",
        help="Exit early if no source files were added or deleted (used by generator rule)",
    )
    parser.add_argument(
        "--c-maps",
        action="store_true",
        help="Convert map binaries to C as part of the build process",
    )
    parser.add_argument(
        "--no-evt-validation",
        action="store_true",
        help="Disable static EvtScript bytecode validation",
    )
    args = parser.parse_args()
    args.shift = not args.no_shift
    args.non_matching = not args.no_non_matching
    args.ccache = not args.no_ccache
    args.evt_validation = not args.no_evt_validation

    if args.incremental:
        stamp = ROOT / "build" / "source_files.stamp"
        file_list = _walk_source_file_list()
        new_content = "\n".join(file_list) + "\n"
        if stamp.exists() and stamp.read_text() == new_content:
            build_ninja = ROOT / "build.ninja"
            configure_inputs = [ROOT / p for p in configure_input_paths(VERSIONS)]
            newest_config_input = max(
                p.stat().st_mtime_ns for p in configure_inputs if p.exists()
            )
            if (
                build_ninja.exists()
                and build_ninja.stat().st_mtime_ns >= newest_config_input
            ):
                # Generated files can refresh source-directory mtimes after
                # build.ninja is written. If the source list and real configure
                # inputs are unchanged, refresh the manifest timestamp so ninja
                # does not rebuild it until hitting its 100-try dirty limit.
                os.utime(build_ninja, None)
                exit(0)

    version_err_msg = ""
    missing_tools = []
    version_old_tools = []
    for tool, crate_name, req_version in RUST_TOOLS:
        try:
            version = exec_shell([tool, "--version"]).split(" ")[1].strip()

            if version < req_version:
                version_err_msg += f"error: {tool} version {req_version} or newer is required, system version is {version}"
                version_old_tools.append(crate_name)
        except (FileNotFoundError, PermissionError):
            missing_tools.append(crate_name)

    if version_old_tools or missing_tools:
        if version_err_msg:
            print(version_err_msg)
        if missing_tools:
            print(
                f"error: cannot find required Rust tool(s): {', '.join(missing_tools)}"
            )
        print()
        print(
            "To install/update dependencies, obtain cargo:\n\tcurl https://sh.rustup.rs -sSf | sh"
        )
        print(f"and then run:")
        for tool in missing_tools:
            print(f"\tcargo install {tool}")
        for tool in version_old_tools:
            print(f"\tcargo install {tool}")
        exit(1)

    # default version behaviour is to only do those that exist
    if len(args.version) > 0:
        versions = args.version
    else:
        versions = []

        for version in VERSIONS:
            rom = ROOT / f"ver/{version}/baserom.z64"

            print(f"configure: looking for baserom {rom.relative_to(ROOT)}", end="")

            if rom.exists():
                print("...found")
                versions.append(version)
            else:
                print("...missing")

        if len(versions) == 0:
            print("error: no baseroms found")
            exit(1)

    if args.clean:
        print("configure: cleaning...")

        exec_shell(["ninja", "-t", "clean"])

        for version in versions:
            shutil.rmtree(ROOT / f"assets/{version}", ignore_errors=True)
            shutil.rmtree(ROOT / f"ver/{version}/assets", ignore_errors=True)
            shutil.rmtree(ROOT / f"ver/{version}/build", ignore_errors=True)
            try:
                os.remove(ROOT / f"ver/{version}/.splat_cache")
            except OSError:
                pass

    args.debug = True

    extra_cflags = ""
    extra_cxxflags = ""
    extra_cppflags = ""
    if args.non_matching:
        extra_cppflags += " -DNON_MATCHING"

        if args.debug:
            # extra_cflags += " -ggdb3"
            extra_cppflags += " -DDEBUG"  # e.g. affects ASSERT macro

    if args.shift:
        extra_cppflags += " -DSHIFT"

    common_warning_flags = " -Wall -Wno-unused-variable -Wno-unused-but-set-variable -Wno-narrowing -Winline -Wreturn-type"
    extra_cflags += common_warning_flags
    extra_cxxflags += common_warning_flags

    # Warnings made into errors by default in GCC 14
    # https://gcc.gnu.org/gcc-14/porting_to.html#warnings-as-errors
    extra_cflags += " --warn-missing-parameter-type -Wincompatible-pointer-types -Wint-conversion"

    # add splat to python import path
    sys.path.insert(0, str((ROOT / args.splat / "src").resolve()))

    # The manifest is written as configure goes, so a run that gives up part
    # way through would leave a truncated build.ninja that ninja would happily
    # use. Build it beside the real one and move it into place only on success.
    build_ninja_path = ROOT / "build.ninja"
    partial_build_ninja = build_ninja_path.with_suffix(".ninja.partial")
    ninja = NinjaWriter(
        open(str(partial_build_ninja), "w", encoding="utf-8"), width=120
    )

    non_matching = args.non_matching or True or args.shift

    write_ninja_rules(
        ninja,
        args.cpp or "mips-linux-gnu-cpp",
        extra_cppflags,
        extra_cflags,
        extra_cxxflags,
        args.ccache,
        args.shift,
        args.debug,
    )
    write_ninja_for_tools(ninja)

    skip_files: Set[str] = set()
    all: List[str] = []
    evt_validation_stamps: List[str] = []
    first_configure = None

    for version in versions:
        print(f"configure: configuring version {version}")

        if version == "ique" and not args.non_matching and sys.platform == "darwin":
            print(
                "configure: refusing to build iQue Player version on macOS because EGCS compiler is not available (use --non-matching to use default compiler)"
            )
            continue

        configure = Configure(version)

        if not first_configure:
            first_configure = configure

        # include tools/splat_ext in the python path
        sys.path.append(str((ROOT / "tools/splat_ext").resolve()))

        configure.load()
        if args.dump or not configure.dump_stamp().exists():
            configure.dump(not args.no_split_assets, args.split_code)
        evt_validation_stamps.extend(
            configure.write_ninja(
                ninja, skip_files, non_matching, args.c_maps, args.evt_validation
            )
        )

        overlay_rom, overlay_evt_validation_stamps = configure.write_overlays(
            ninja, args.evt_validation
        )
        evt_validation_stamps.extend(overlay_evt_validation_stamps)

        all.append(posix(configure.rom_ok_path()))
        all.append(posix(configure.syms_path()))
        all.append(overlay_rom)

    assert first_configure, "no versions configured"
    first_configure.make_current(ninja)

    orphans = first_configure.check_asset_coverage(
        ninja.consumed_paths, ninja.produced_paths
    )
    if orphans:
        print(
            "configure: no build rule uses these files, so nothing would put them "
            "in the ROM:\n"
        )
        for orphan in orphans:
            print(f"  {orphan}")
        print(
            "\nCheck that each file has a supported extension and sits in a directory "
            "the build expects it in. Remove any file that isn't meant to be built."
        )
        ninja.close()
        partial_build_ninja.unlink()
        raise SystemExit(1)

    ninja.build("evt_script_validation", "phony", evt_validation_stamps)
    all.append("evt_script_validation")
    ninja.build("all", "phony", all)
    ninja.default("all")

    # Fetch pre-built clangd index from the matching dx-* GitHub release.
    try:
        from clangd_index import fetch_clangd_index

        fetch_clangd_index(ROOT)
    except Exception:
        pass

    # Generator rule: re-run configure.py when inputs change.
    argv = list(sys.argv)
    if "--clean" in argv:
        argv.remove("--clean")
    if "--incremental" not in argv:
        argv.append("--incremental")
    ninja.rule(
        "configure",
        description="Reconfiguring build.ninja",
        command=f'"{sys.executable}" {" ".join(argv)}',
        generator=True,
        pool="console",
    )

    configure_deps = configure_input_paths(versions)

    for top in ["src", "include", "assets"]:
        for dirpath, dirnames, _ in os.walk(ROOT / top):
            configure_deps.append(
                str(
                    Path(dirpath).relative_to(ROOT)
                    if Path(dirpath).is_absolute()
                    else dirpath
                )
            )

    ninja.build(
        "build.ninja",
        "configure",
        str(BUILD_TOOLS / "configure.py"),
        implicit=configure_deps,
    )

    ninja.close()
    os.replace(partial_build_ninja, build_ninja_path)

    # Generate compile_commands.json with MIPS cross-compiler flags stripped,
    # so clangd and clang-tidy can parse the compile commands.
    try:
        compdb = subprocess.run(
            ["ninja", "-t", "compdb"],
            capture_output=True,
            text=True,
        )
        if compdb.returncode == 0:
            entries = json.loads(compdb.stdout)
            strip_re = re.compile(r"^(-m\S+|-f\S+|-g\S+|-G\d+|--warn-\S+)$")
            cross_cc_re = re.compile(r"^(ccache\s+)?mips-linux-gnu-g(cc|\+\+)(?=\s)")
            for entry in entries:
                entry["command"] = cross_cc_re.sub(r"\1cc", entry["command"])
                parts = entry["command"].split()
                entry["command"] = " ".join(p for p in parts if not strip_re.match(p))
            (ROOT / "compile_commands.json").write_text(
                json.dumps(entries, indent=2) + "\n"
            )
    except FileNotFoundError:
        pass  # ninja not installed

    # Write the source file stamp after all work (including splat which may produce
    # files under assets/) so the stamp reflects the final state.
    stamp = ROOT / "build" / "source_files.stamp"
    stamp.parent.mkdir(parents=True, exist_ok=True)
    stamp.write_text("\n".join(_walk_source_file_list()) + "\n")
