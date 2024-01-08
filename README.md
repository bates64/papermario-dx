# Paper Mario DX

[![Discord Channel][discord-badge]][discord]

This is a fork of the [Paper Mario decompilation](papermario-repo) which aims to provide a strong foundation for mods/romhacks.

To get started, see [SETUP](SETUP.md).

Configuration is located in [src/dx/config.h](src/dx/config.h).

[discord]: https://discord.gg/urUm3VG
[discord-badge]: https://img.shields.io/discord/279322074412089344?color=%237289DA&logo=discord&logoColor=ffffff
[papermario-repo]: https://github.com/pmret/papermario

## List of changes

- US release only (no JP, PAL, or iQue - none of these are near 100% yet).
- Default configure flags: `--shift --debug --modern-gcc --non-matching` and `AVOID_UB`
- Backtrace (call stack) on crash screen including file names and line numbers.
    - You can call [`debug_backtrace()`](src/dx/backtrace.h) to print a backtrace in any function.
    - Failed assertions (`ASSERT`) will trigger the crash screen and print a backtrace instead of hanging.
- `assets/star_rod_build` directory for Star Rod to write assets to.
- Fixed many bugs / incorrect behaviour (e.g. ).
- Additional features configured in [src/dx/config.h](src/dx/config.h):
    - `DX_DEBUG_MENU` - Enables a debug menu. Navigate with the D-pad (D-L for back, D-R for open, D-U/D-D for up/down).
    - `DX_SKIP_LOGOS` - Skips the logos at the start of the game.
    - `DX_SKIP_TITLE` - Skips the title screen and file select, loading the first savefile automatically.

## How do I modify assets?

Assets dumped from the game are placed in `assets/us/`. You should not modify the dumped assets directly. Instead, any files you modify should be placed in `assets/dx/`, which will override the dumped assets when the game is built. When searching for an asset, `./configure` looks under `assets/dx/` first, then `/assets/us/`. You can change this behaviour by modifying the `asset_stack` in `ver/us/splat.yaml`.

**Whenever you add a new file you must run `./configure` again to update the build.**

## Does it support Star Rod?

Yes! Star Rod enables you to visually edit maps and sprites.

To use Star Rod, when prompted to select a directory for your mod, select the `papermario-dx` directory.
Star Rod will write assets to `assets/star_rod_build/`. If you add a new file to `assets/star_rod_build/`, you must run `./configure` again to add it to the build.

## How do I add new C files?

(Note: this will be made easier in the future.)

To add a new C file to the build, you should add it as a `c` subsegment as part of a `code` segment in `ver/us/splat.yaml`. This file describes how to dump and build the ROM. When adding files not in the original game, make sure you set the ROM address as `auto` so that splat won't attempt to dump it.

[See splat's documentation for more information.](https://github.com/ethteck/splat/wiki/Segments)

Whenever `splat.yaml` is modified, you must run `./configure` again to update the build.

## How do I add new maps?

(Note: this will be made easier in the future.)

There are three steps to adding a new map.

1. Creating C files and assets for the map
2. Adding the C files and assets to the build
3. Telling the game where to find the map

### Creating C files and assets for the map

C files for maps are located in `src/world/area_XXX/XXX_YY`, where XXX is the area identifier and YY is the map identifier within the area. For example, the map `src/world/area_kmr/kmr_00` is the 'Goomba Region - Forest Clearing' map.

As an example, we'll add a new map to the `area_tst` region. We'll create a new directory `src/world/area_tst/tst_14`, with two files in it:

- `src/world/area_tst/tst_14/tst_14.c`
```c
#include "tst_14.h"

extern EvtScript N(EVS_Main);
extern EvtScript N(EVS_MakeEntities);

EntryList N(Entrances) = {
    { 0.0, 0.0, 0.0, 0.0 },
};

MapSettings N(settings) = {
    .main = &N(EVS_Main),
    .entryList = &N(Entrances),
    .entryCount = ENTRY_COUNT(N(Entrances)),
};

EvtScript N(EVS_Main) = {
    EVT_SET(GB_WorldLocation, LOCATION_TESTING)
    EVT_CALL(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT()
    EVT_RETURN
    EVT_END
};
```
- `src/world/area_tst/tst_14/tst_14.h`
```c
/// @file tst_01.h
/// @brief Testing - Custom Map Example

#include "common.h"
#include "map.h"

#include "../tst.h"
#include "mapfs/tst_14_shape.h"
#include "mapfs/tst_14_hit.h"

#define NAMESPACE tst_14
```

Notice that the header file is including `mapfs/tst_14_shape.h` and `mapfs/tst_14_hit.h`. These are the map's shape model and collision data, respectively. We'll create these files next, using Star Rod.

Create a new directory `assets/dx/mapfs/`. Then, with Star Rod, create a new map `assets/dx/mapfs/tst_14.xml`, and use the "Build Collision" and "Build Geometry" options in the toolbar to generate the hit and shape data. The resulting files will be written to `assets/star_rod_build/mapfs/tst_14_{shape|hit}.bin`.

How to use Star Rod is out of scope for this tutorial.

### Adding the C files and assets to the build

Now that we have the C files and assets for the map, we need to add them to the build. This is done in `ver/us/splat.yaml`.

Add a new segment to the bottom of the file (or after the segment with `name: tst_13` if you want to keep the maps in order):

```yaml
segments:
  # ...
  - name: tst_14
    dir: world/area_tst/tst_14
    type: code
    start: auto
    vram: 0x80240000
    subsegments:
    - [auto, c, tst_14]
    - [auto]
```

This will add the `tst_14` segment to the build. The `dir` argument specifies the directory where the C files are located. The `start` argument is set to `auto`, which means that the segment's address in ROM will be determined automatically. The `vram` argument specifies the address in VRAM where the segment will be loaded, which, for maps, is always `0x80240000`.

To add the new assets `tst_14_shape` and `tst_14_hit`, to the build, add these two lines to `tools/splat_ext/map_data.yaml`:
```yaml
- tst_14_shape
- tst_14_hit
```

**Whenever `splat.yaml` or `map_data.yaml` is modified, you must run `./configure` again to update the build.**

### Telling the game where to find the map

Now that the map is in the build, we need to tell the game that the map exists. This is done in `src/world/world.c`.

Make the following change:
```diff
/// Debug
#include "area_tst/tst.h"
MapConfig tst_maps[] = {
    { MAP(tst_01), .bgName = "nok_bg" },
    { MAP(tst_02), .bgName = "nok_bg" },
    { MAP(tst_03), .bgName = "nok_bg" },
    { MAP(tst_04), .bgName = "nok_bg" },
    { MAP(tst_10), .bgName = "nok_bg" },
    { MAP(tst_11), .bgName = "nok_bg" },
    { MAP(tst_12), .bgName = "nok_bg" },
    { MAP(tst_13), .bgName = "nok_bg" },
+   { MAP(tst_14), .bgName = "nok_bg" },
    { MAP(tst_20), .bgName = "nok_bg" },
};
```

Notice that we include `src/world/area_tst/tst.h`. This file declares the `MapSettings` struct for each map in the area. We'll modify this file next to add the line:

```
extern MapSettings tst_14_settings;
```

This will allow the `MAP` macro in `world.c` to work.

Finally, we can build the ROM with `ninja` and use the debug menu to load our new `tst_14` map!
