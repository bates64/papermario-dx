# Changelog

## Unreleased

## 2026-11-06.1

Fixed Star Rod on Linux, where its map and sprite editors failed to start. ([Alex](https://starhaven.dev/bates64.com))

## 2026-11-06

### Refer to map markers in C ([Alex](https://starhaven.dev/bates64.com))

A map's code reads the markers you place in the map editor by name, with a `$` in front, such as `$Goomba`. See [the docs](https://docs.starhaven.dev/papermario-dx/world/markers/) for more information.

A Camera Target marker sets up the camera with `UseCamTarget`, such as `Call(UseCamTarget, CAM_DEFAULT, $Shore)`.

Entries are Entry markers too, and replace the enum in `entrances.h`. To send the player to another map's entry, include that map's header and pass the entry:

```c
#include "world/area/kmr/kmr_03.h"

Call(GotoMap, $kmr_03.Front)
```

To update:
- Replace entry constants such as `kmr_03_ENTRY_0` with entry markers such as `$kmr_03.Front`, including in exit macros. In `dx/config.h`, `NEW_GAME_ENTRY` replaces `NEW_GAME_MAP_ID` and `NEW_GAME_ENTRY_ID`.
- If one of your maps has no markers, open it in the map editor and add an Entry marker for each entry in its entry list, in the same order.

### Each map has its own sprite shading ([Alex](https://starhaven.dev/bates64.com))

Sprite shading is set for each map instead of in a shared list of profiles, and applies when the map loads. Place its lights as Light markers, then turn it on and set its colors under **Lighting** in the map's settings, which show when nothing is selected. See [the docs](https://docs.starhaven.dev/papermario-dx/world/markers/#light) for more information.

To update:
- Replace `Call(SetSpriteShading, SHADING_...)` with Light markers and the map's **Lighting** settings. In a battle stage, also call `SetSpriteShading` with `MAP_SPRITE_SHADING` in its pre-battle script.
- Delete `Call(SetSpriteShading, SHADING_NONE)`.

### `Ref` and `Float` are deprecated ([Alex](https://starhaven.dev/bates64.com))

EVT commands take structs and decimal numbers without `Ref` and `Float`:

```c
Call(MakeShopOwner, Owner)           // was Ref(Owner)
Call(SetNpcJumpscale, NPC_SELF, 2.5) // was Float(2.5)
```

`Float` is still needed for decimal numbers in C arrays that a script reads with `UseFBuf`. A variable that isn't a struct or an array, such as an `s32`, passes its value, so pass its address with `&`, such as `UseBuf(&BlowingBubbles)`.

### `OVL_DEF_MAP` is deprecated ([Alex](https://starhaven.dev/bates64.com))

A map needs no `OVL_DEF_MAP`. The game starts the map's `EVS_Main`, takes its entries from its Entry markers, and takes its background, tattle, song variation, and reverb from its settings in the map editor.

The game also sets up the map's location, camera, and fog from its settings as the map loads, before its `EVS_Main` starts. To see a map's settings, open it in the map editor and select nothing. See [Map settings](https://docs.starhaven.dev/papermario-dx/world/create-a-map/#map-settings).

A map with `OVL_DEF_MAP` still works, but the build warns about it. To update a map, set its background, tattle, and reverb in its settings, then delete the `OVL_DEF_MAP`, and rename its main EVT script to `EVS_Main` if it has another name. To set its location, camera, and fog in its settings too, delete the lines in `EVS_Main` that set them, such as `EVT_SETUP_CAMERA_NO_LEAD(...)`.

## 2026-10-25

### Maps and stages can use any texture (Clover and [Alex](https://starhaven.dev/bates64.com))

Every texture is now in one shared pool, so a map or battle stage can use textures from any area, and each texture is in the ROM only once. The texture archives in `mapfs/tex` only group textures, and Star Rod's map editor has a dropdown to pick which texture archive to browse.

To update a mod:

- Delete `.texture` from battle stages, `.textureArchive` from maps, and any code that sets `wMapTexName`.
- Rename any textures that share a name, even across texture archives.
- Delete the texture archive offset and size from calls to `load_data_for_models` and `mdl_load_all_textures`.
- Replace `get_asset_offset` with `load_asset_by_name`.
- Delete calls to `load_texture_variants`.

### Map object names must be unique C identifiers ([Alex](https://starhaven.dev/bates64.com))

The names of models, colliders, zones, and markers must be unique within a map and valid C identifiers. Star Rod renames any that aren't. When two objects share a name, the last one in its tree keeps it and the others get a suffix such as `_1`. Spaces and other characters become underscores.

If a map had duplicate names or names with spaces, check the code that refers to them after building.

## 2026-10-22

### Icon files replace `Icons.xml` ([Alex](https://starhaven.dev/bates64.com))

Every PNG in `icon/` is now an [icon](https://docs.starhaven.dev/papermario-dx/graphics/icons/), so to add one, add a PNG there. No need to list it in an XML table.

### Audio files replace the XML tables ([Alex](https://starhaven.dev/bates64.com))

Each sound effect, song, ambient sound, and bank is its own file, with no need to list them in XML tables. A file's name becomes its constant, so `audio/sfx/shop_bell.xml` becomes `SOUND_SHOP_BELL`.

If your mod adds or changes audio, update it:

- Give each sound effect its own file in `audio/sfx/`, and each envelope its own file in `audio/sfx/envelopes/`. Then delete your copies of the old XML tables.
- Rename each song and ambient sound file after its sound in snake case, such as `audio/songs/meadow_theme.bgm`.
- If a song's entry had `bk1`, `bk2`, or `bk3`, open the song in Mamar and choose its instruments again, so that Mamar saves the banks in the `.bgm` file.
- Replace raw sound, song, and ambient sound numbers with their constants, and `AMBIENT_SEA` with `AMBIENT_BEACH`.

If the build then fails, [Fix audio build errors](https://docs.starhaven.dev/papermario-dx/audio/troubleshooting/) explains each message.

### Fixed typos in names ([Alex](https://starhaven.dev/bates64.com))

Fixed some typos in enum variants and struct field names.
To update your mod, open a terminal in your mod's folder, such as with **Help > Open Terminal** in Diorama64, and run:

```sh
python3 tools/rename.py tools/renames/8_typos.txt
```

On Windows, run `python` instead of `python3`.

### Fixed `USE_PROFILER` ([Alex](https://starhaven.dev/bates64.com))

`USE_PROFILER` in `dx/config.h` had no effect: the profiler was built in whether it was `0` or `1`. This is fixed, so the default of `0` turns the profiler off. To keep using the profiler, set `USE_PROFILER` to `1`.

## 2026-10-15.1

Fixed build errors on some Windows machines where a broken version of `tar` was installed. ([Alex](https://starhaven.dev/bates64.com))

## 2026-10-15

### `include/` merged into `src/` ([Alex](https://starhaven.dev/bates64.com))

The `include/` directory has been merged into `src/`, so headers now sit next to the sources that use them. Move any headers in `include/` into `src/`.

### Music browser in the debug menu ([Brando](https://starhaven.dev/brando.tngl.sh))

The [debug menu](https://docs.starhaven.dev/papermario-dx/testing/debug-menu/)'s Sound Player now has a **Music** browser that lists songs by name, with play, stop, and paging controls. Sound effect controls have moved under **Sound**.

![The Music browser over Toad Town, listing songs 15 to 1D by name with Ruins Basement selected](https://pds.starhaven.dev/xrpc/com.atproto.sync.getBlob?did=did:plc:tjgdahiw3u2djgnigyqeummg&cid=bafkreibe5finte2zhit3gkzi7hv7a5fprxuwlfl7rqtt3egbfpblqmbki4)

### Changes to the optimization level ([Alex](https://starhaven.dev/bates64.com))

Code now uses `-Os` (optimize for size) instead of `-O2`, with tighter limits on inlining and loop unrolling. Smaller code fits better in the N64's small instruction cache, which makes the engine a few percent faster per frame. Mod code is compiled the same way and might show warnings it didn't before.

### ROM space savings ([Alex](https://starhaven.dev/bates64.com))

Three changes free about 3.6 MB of ROM space:

- The optimization level change makes code about 0.92 MB smaller.
- Removing leftover copies and padding near the end of the ROM frees 1.82 MB.
- Sizing each overlay directory to fit its overlays frees 0.91 MB.

### Formatter corrects struct offset comments ([Alex](https://starhaven.dev/bates64.com))

Formatting a file now corrects struct offset and size comments, such as `/* 0x04 */` and `// size = 0x0C`, that no longer match the compiler.

### Other changes

- In `layout.yaml`, a segment whose class starts at another segment's end, through `follows` or `vram_symbol`, must now be listed after that segment. ([Alex](https://starhaven.dev/bates64.com))
- `snprintf` is now available. ([Alex](https://starhaven.dev/bates64.com))

## 2026-10-12.2

Fixed build errors on some Windows machines where a broken version of `tar` was installed. ([Alex](https://starhaven.dev/bates64.com))

## 2026-10-12.1

Fixed Star Rod on Linux. ([Alex](https://starhaven.dev/bates64.com))

## 2026-10-12

This is the first release of Paper Mario DX.
