#!/usr/bin/env python3
"""Writes the header a map's code includes as map.xml.h, or a stage's as stage.xml.h.

It gives the IDs of the geometry's models, colliders, and zones, from the
headers Star Rod writes beside the compiled geometry. If the map has a
features.json, it also gives each of its markers as a constant named after it
with a `$` in front, such as `$Goompa`, and its Entry markers as `$Entries`;
see the Markers page of the manual. GCC leaves out the markers a file of the
map's code doesn't use. It also gives the map's sprite shading, with its Light
markers as its lights, as MAP_SPRITE_SHADING, or nullptr if the map has none.

With --entries, it also writes the header other maps include to send the
player to this map's entries, such as world/area/kmr/kmr_03.h, which gives them
as fields of `$kmr_03`.

A header is only rewritten when its text changes, so editing a marker rebuilds
only the code that includes it.

A map that borrows another's geometry passes - as the geometry name, and includes that geometry's IDs itself.

Usage: source_header.py <out> <geometry name, such as w_kmr_02, or -> [features.json [--entries <out> <map name>]]
"""

import json
import re
import sys

IDENTIFIER = re.compile(r"[A-Za-z_][A-Za-z0-9_]*")


class MarkerError(Exception):
    pass


def f32(value) -> str:
    return f"{float(value)!r}f"


def vec3f(values) -> str:
    return "{ " + ", ".join(f32(v) for v in values) + " }"


def vec3i(values) -> str:
    return "{ " + ", ".join(str(int(v)) for v in values) + " }"


def define(type_name: str, name: str, fields: list) -> list:
    return [f'MARKER_CONST {type_name} ${name} __asm__("marker.{name}") = {{', *(f"    {f}," for f in fields), "};"]


def position_lines(marker) -> list:
    return define("PositionMarker", marker["name"], [f".pos = {vec3f(marker['pos'])}", f".yaw = {f32(marker['yaw'])}"])


def entry_fields(marker, map_name: str, index: int) -> list:
    return [
        f'.map = "{map_name}"',
        f".pos = {vec3f(marker['pos'])}",
        f".yaw = {f32(marker['yaw'])}",
        f".index = {index}",
    ]


def speed_override(settings) -> str:
    if settings.get("overrideSpeed"):
        return f"OVERRIDE_MOVEMENT_SPEED({float(settings['speed'])!r})"
    return "NO_OVERRIDE_MOVEMENT_SPEED"


def shape(settings) -> str:
    return "SHAPE_CYLINDER" if settings.get("useCircle") else "SHAPE_RECT"


def detect_fields(npc) -> list:
    detect = npc.get("detect", {})
    if detect.get("useCircle"):
        size = [detect.get("radius", 0)] + ([detect["height"]] if detect.get("height") else [])
    else:
        size = [detect.get("sizeX", 0), detect.get("sizeZ", 0)]
    return [
        f".detectPos = {vec3i(detect.get('center', [0, 0, 0]))}",
        f".detectSize = {{ {', '.join(str(int(v)) for v in size)} }}",
        f".detectShape = {shape(detect)}",
        f".isFlying = {'true' if npc.get('flying') else 'false'}",
    ]


def territory(npc) -> str:
    move_type = npc.get("moveType", "Stationary")
    if move_type == "Wander":
        wander = npc["wander"]
        if wander.get("useCircle"):
            size = f"{{ {int(wander.get('radius', 0))} }}"
        else:
            size = f"{{ {int(wander.get('sizeX', 0))}, {int(wander.get('sizeZ', 0))} }}"
        fields = [
            f".centerPos = {vec3i(wander.get('center', [0, 0, 0]))}",
            f".wanderSize = {size}",
            f".moveSpeedOverride = {speed_override(wander)}",
            f".wanderShape = {shape(wander)}",
            *detect_fields(npc),
        ]
        return "{ .wander = { " + ", ".join(fields) + " } }"
    if move_type == "Patrol":
        patrol = npc["patrol"]
        points = patrol.get("points", [])
        fields = [
            f".numPoints = {len(points)}",
            ".points = { " + ", ".join(vec3i(p) for p in points) + " }",
            f".moveSpeedOverride = {speed_override(patrol)}",
            *detect_fields(npc),
        ]
        return "{ .patrol = { " + ", ".join(fields) + " } }"
    return "{}"


def npc_lines(marker) -> list:
    npc = marker.get("npcComp", {})
    return define(
        "NpcMarker",
        marker["name"],
        [f".pos = {vec3f(marker['pos'])}", f".yaw = {f32(marker['yaw'])}", f".territory = {territory(npc)}"],
    )


ITEM_BLOCKS = {"YellowBlock", "HiddenYellowBlock", "RedBlock", "HiddenRedBlock"}
SWITCHES = {"BlueSwitch", "HugeBlueSwitch"}


def entity_lines(marker, markers_by_name) -> tuple:
    """The marker's definition, and the declarations it needs of the names it refers to."""
    entity = marker.get("entityComp", {})
    kind = entity["type"]
    args = []
    flag_kind = "NONE"
    flag = None
    externs = []

    def get(key):
        return entity.get(key)

    if kind == "Item":
        args = [get("itemName"), get("spawnMode")]
        flag = get("gameFlagName") or "0"
    elif kind in ITEM_BLOCKS:
        args = [get("itemName")]
        flag_kind, flag = "BLOCK", get("gameFlagName")
    elif kind == "MulticoinBlock":
        flag_kind, flag = "BLOCK", get("gameFlagName")
    elif kind == "HeartBlock":
        args = [str(get("style"))] if get("style") is not None else []
    elif kind in ("Chest", "GiantChest"):
        args = [get("itemName") or "ITEM_NONE"]
        flag_kind, flag = "CHEST", get("gameFlagName")
    elif kind == "HiddenPanel":
        args = [get("modelName")]
        flag_kind, flag = "PANEL", get("gameFlagName")
    elif kind == "WoodenCrate":
        args = [get("itemName")]
        flag_kind, flag = "CRATE", get("gameFlagName")
    elif kind in SWITCHES:
        args = [str(get("index"))] if get("index") is not None else []
        if get("areaFlagName"):
            flag_kind, flag = "SWITCH", f"EVT_INDEX_OF_AREA_FLAG({get('areaFlagName')})"
    elif kind == "SimpleSpring":
        args = [str(get("launchDist"))]
    elif kind == "ArrowSign":
        args = [str(get("angle"))]
    elif kind == "BlueWarpPipe":
        args = [get("entryName"), get("scriptName"), f"EVT_INDEX_OF_GAME_FLAG({get('gameFlagName')})"]
        externs.append(f"extern EvtScript {get('scriptName')};")
    elif kind == "Tweester":
        args = [get("pathsName")]
        externs.append(f"extern TweesterPath* {get('pathsName')}[];")
    elif kind == "SpinningFlower":
        if get("targetName"):
            target = get("targetName")
            if target not in markers_by_name:
                raise MarkerError(f"{marker['name']} targets {target}, which isn't a marker")
            args = [f"${target}.pos.x", f"${target}.pos.y", f"${target}.pos.z"]
    if flag_kind != "NONE" and flag is None:
        flag_kind = "NONE"

    script = get("scriptName") if kind not in ("BlueWarpPipe",) else None
    if script:
        externs.append(f"extern EvtScript {script};")

    fields = [f".pos = {vec3f(marker['pos'])}", f".yaw = {f32(marker['yaw'])}"]
    fields.append(".blueprint = nullptr" if kind == "Item" else f".blueprint = &Entity_{kind}")
    if args:
        # an argument can be a pointer, such as a warp pipe's script
        fields.append(".args = { " + ", ".join(f"(s32) {a}" for a in args) + " }")
    if script:
        fields.append(f".script = &{script}")
    if flag is not None:
        fields.append(f".flag = {flag}")
    fields.append(f".flagKind = ENTITY_MARKER_FLAG_{flag_kind}")
    return define("EntityMarker", marker["name"], fields), externs


def volume_lines(marker) -> list:
    vol = marker.get("volComp", {})
    name = marker["name"]
    if marker["type"] == "Sphere":
        return define("SphereMarker", name, [f".pos = {vec3f(marker['pos'])}", f".radius = {f32(vol.get('radius', 0))}"])
    if marker["type"] == "Cylinder":
        return define(
            "CylinderMarker",
            name,
            [
                f".pos = {vec3f(marker['pos'])}",
                f".radius = {f32(vol.get('radius', 0))}",
                f".height = {f32(vol.get('height', 0))}",
            ],
        )
    return define(
        "VolumeMarker",
        name,
        [f".min = {vec3f(vol.get('minPos', marker['pos']))}", f".max = {vec3f(vol.get('maxPos', marker['pos']))}"],
    )


def c_bool(value) -> str:
    return "true" if value else "false"


def camera_settings(zone) -> str:
    """A CameraControlSettings initializer, laid out the way Star Rod compiles a camera zone's settings."""
    (ax, ay, az), (bx, by, bz), (cx, _, cz) = zone["posA"], zone["posB"], zone["posC"]
    if zone["type"] == 4:
        points = f".two = {{ {', '.join(f32(v) for v in (ax, ay, az, bx, by, bz))} }}"
    else:
        points = f".three = {{ {', '.join(f32(v) for v in (ax, cx, az, bx, cz, bz))} }}"
    return (
        f"{{ .type = {int(zone['type'])}, .boomLength = {f32(zone['boomLength'])}, .boomPitch = {f32(zone['boomPitch'])}, "
        f".points = {{ {points} }}, .viewPitch = {f32(zone['viewPitch'])}, .flag = {c_bool(zone.get('flag'))} }}"
    )


def cam_target_lines(marker) -> list:
    comp = marker["camTargetComp"]
    fields = [
        f".pos = {vec3f(marker['pos'])}",
        f".useZone = {c_bool(comp.get('useZone'))}",
        f".overrideDist = {c_bool(comp.get('overrideDist'))}",
        f".overrideAngles = {c_bool(comp.get('overrideAngles'))}",
        f".pan = {c_bool(comp.get('generatePan'))}",
        f".boomLength = {f32(comp.get('boomLength', 0))}",
        f".boomPitch = {f32(comp.get('boomPitch', 0))}",
        f".viewPitch = {f32(comp.get('viewPitch', 0))}",
        f".panSpeed = {f32(comp.get('moveSpeed', 0))}",
    ]
    if not comp.get("useZone"):
        fields.append(f".settings = {camera_settings(comp['cameraZone'])}")
    return define("CamTargetMarker", marker["name"], fields)


def path_lines(marker) -> tuple:
    """The path's definition, and the names it gives its points."""
    path = marker["name"]
    comp = marker["pathComp"]
    points = comp["waypoints"]
    names = comp.get("names") or [None] * len(points)
    # without edges, a path is a line, each point leading to the one after it
    edges = comp.get("edges") or [[i + 1] if i + 1 < len(points) else [] for i in range(len(points))]

    next_indices = []
    point_lines = []
    for i, (x, y, z) in enumerate(points):
        point_lines.append(
            f"    {{ .pos = {{ {x}, {y}, {z} }}, .nextCount = {len(edges[i])}, .next = ${path}_next + {len(next_indices)} }},"
        )
        next_indices += edges[i]
    lines = [
        f'MARKER_CONST u16 ${path}_next[] __asm__("marker.{path}_next") = {{ {", ".join(str(j) for j in next_indices)} }};',
        f'MARKER_CONST PathMarkerPoint ${path}_points[] __asm__("marker.{path}_points") = {{',
        *point_lines,
        "};",
        *define("PathMarker", path, [f".count = {len(points)}", f".points = ${path}_points"]),
    ]

    named = [(i, name) for i, name in enumerate(names) if name is not None]
    if named:
        lines.append("enum {")
        lines += [f"    ${path}_{name} = {i}," for i, name in named]
        lines.append("};")

    return lines, [f"{path}_{name}" for _, name in named]


LIGHT_FALLOFF = {
    "uniform": [],
    "linear": ["LIGHT_SOURCE_LINEAR_FALLOFF"],
    "quadratic": ["LIGHT_SOURCE_QUADRATIC_FALLOFF"],
}

NO_SPRITE_SHADING = "#define MAP_SPRITE_SHADING nullptr"


def shading_lines(features, lights: list) -> list:
    """The definition of the map's sprite shading, from its base color, its edge offset, and its Light markers."""
    if len(lights) > 7:
        raise MarkerError(f"sprite shading can have at most 7 lights, but the map has {len(lights)} Light markers")

    sources = []
    for light in lights:
        comp = light["lightComp"]
        flags = " | ".join(["LIGHT_SOURCE_ENABLED", *LIGHT_FALLOFF[comp["mode"]]])
        rgb = ", ".join(str(int(c)) for c in comp["rgb"])
        sources.append(
            f"{{ .flags = {flags}, .rgb = {{ {rgb} }}, .pos = {vec3f(light['pos'])}, .falloff = {f32(comp['falloff'])} }}"
        )

    ambient = ", ".join(str(int(c)) for c in features["shadingBaseColor"])
    fields = [
        ".sources = { " + ", ".join(sources) + " }",
        f".ambientColor = {{ {ambient} }}",
        f".ambientPower = {int(features['shadingOffset'])}",
    ]
    # a named object rather than a compound literal, since C++ can't take a compound literal's address
    return [
        'static const SpriteShadingProfile MapSpriteShading __asm__("map.SpriteShading") = {',
        *(f"    {f}," for f in fields),
        "};",
        "#define MAP_SPRITE_SHADING (&MapSpriteShading)",
    ]


def marker_lines(features, map_name: str) -> tuple:
    """The definitions of a map's markers and sprite shading for its own code, and the definition of its entries for other maps'."""
    names = {}

    def claim(name: str, owner: str):
        if not IDENTIFIER.fullmatch(name):
            raise MarkerError(f"{owner} can't be named '{name}': use letters, numbers, and underscores, starting with a letter")
        if name in names:
            raise MarkerError(f"{owner} and {names[name]} are both named ${name}: rename one in the map editor")
        names[name] = owner

    markers = [m for m in features.get("markers", []) if m["type"] not in ("Root", "Group")]
    markers_by_name = {m["name"]: m for m in markers}
    for marker in markers:
        claim(marker["name"], f"marker {marker['name']}")
    claim("Entries", "the entry list")

    lines = []
    externs = []
    if features.get("hasSpriteShading"):
        lines += shading_lines(features, [m for m in markers if m["type"] == "Light"])
    else:
        lines.append(NO_SPRITE_SHADING)
    entries = [m for m in markers if m["type"] == "Entry"]
    # entries first, since an entity such as a warp pipe can refer to one
    for marker in entries + [m for m in markers if m["type"] != "Entry"]:
        kind = marker["type"]
        if kind == "Position":
            lines += position_lines(marker)
        elif kind == "Entry":
            lines += define("EntryMarker", marker["name"], entry_fields(marker, map_name, entries.index(marker)))
        elif kind == "NPC":
            lines += npc_lines(marker)
        elif kind == "Entity":
            entity, needs = entity_lines(marker, markers_by_name)
            lines += entity
            externs += needs
        elif kind in ("Sphere", "Cylinder", "Volume"):
            lines += volume_lines(marker)
        elif kind == "CamTarget":
            lines += cam_target_lines(marker)
        elif kind == "Path":
            path, point_names = path_lines(marker)
            for point in point_names:
                claim(point, f"a point of path {marker['name']}")
            lines += path

    if entries:
        lines.append('static EntryList $Entries __asm__("marker.Entries") = {')
        lines += [f"    {{ {', '.join(f32(v) for v in [*m['pos'], m['yaw']])} }}," for m in entries]
        lines.append("};")

    entry_header = []
    if entries:
        fields = " ".join(f"EntryMarker {m['name']};" for m in entries)
        entry_header = [
            f'MARKER_CONST struct {{ {fields} }} ${map_name} __asm__("marker.{map_name}") = {{',
            *(f"    .{m['name']} = {{ {', '.join(entry_fields(m, map_name, i))} }}," for i, m in enumerate(entries)),
            "};",
        ]

    if any(m["type"] == "Entity" for m in markers):
        externs.insert(0, '#include "entity.h"')
    return list(dict.fromkeys(externs)) + lines, entry_header


def write_if_changed(path: str, lines: list):
    text = "\n".join(lines) + "\n"
    try:
        with open(path) as f:
            if f.read() == text:
                return
    except FileNotFoundError:
        pass
    with open(path, "w") as f:
        f.write(text)


def main(argv: list) -> int:
    out, name, *rest = argv
    features = rest[0] if rest else None
    entries_out = map_name = None
    if "--entries" in rest:
        i = rest.index("--entries")
        entries_out, map_name = rest[i + 1], rest[i + 2]

    lines = ["#pragma once"]
    if name != "-":
        lines += [f'#include "mapfs/{name}_shape.h"', f'#include "mapfs/{name}_hit.h"']
    entry_header = []
    if not features:
        lines.append(NO_SPRITE_SHADING)
    else:
        try:
            marker_text, entry_header = marker_lines(json.load(open(features)), map_name or name)
        except MarkerError as e:
            print(f"{features}: error: {e}", file=sys.stderr)
            return 1
        lines += marker_text

    write_if_changed(out, lines)
    if entries_out:
        write_if_changed(entries_out, ["#pragma once", *entry_header])
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
