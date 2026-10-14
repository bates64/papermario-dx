# Changelog

## Unreleased

- The `include` directory has been merged into `src`. If your mod adds headers to `include`, move them to `src`.
- Deleted junk files near the end of the ROM. This saves 1.82 MB of ROM space. The following files were removed:
  - `copy_1942C40.bin`
  - `pad_1B82208.bin`
  - `copy_1B8220C.bin`
  - `unk_1C84D30.bin`
  - `copy_1E00000.bin`
  - `copy_27FEE22.bin`
- Overlays are stored more efficiently, saving 0.91 MB of ROM space.
- Formatting a `.c`, `.h`, `.cpp` or `.hpp` file fixes its struct offset and size comments, once the project has been built.
- The debug Sound Player now includes a named Music browser with play/stop and
  paging controls. Its catalog follows the generated song IDs. Existing sound
  effect controls are available under Sound.

## 2026-10-12

This is the first release of Paper Mario DX.
