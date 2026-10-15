# Changelog

## Unreleased

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

## 2026-10-12.1

Fixed Star Rod on Linux. ([Alex](https://starhaven.dev/bates64.com))

## 2026-10-12

This is the first release of Paper Mario DX.
