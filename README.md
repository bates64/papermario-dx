# Paper Mario Deluxe

[![Discord Channel][discord-badge]][discord]

This is a fork of the [Paper Mario decompilation](papermario-repo) which aims to provide a strong foundation for mods/romhacks.

To get started, see [INSTALL](INSTALL.md).

Configuration is located in [src/dx/config.h](src/dx/config.h).

Changes:

- US release only (no JP, PAL, or iQue - none of these are near 100% yet)
- Shiftable builds by default
- `DX_DEBUG_MENU` - Enables a debug menu. Navigate with the D-pad (D-L for back, D-R for open, D-U/D-D for up/down).
- `DX_SKIP_LOGOS` - Skips the logos at the start of the game.
- `DX_SKIP_TITLE` - Skips the title screen and file select, loading the first savefile automatically.
- `DX_FULL_VIEWPORT` - Disables letterboxing of the viewport and resizes HUD elements to accomodate. This is a work in progress: the HUD can be a bit weird and the background is not scaled.

[discord]: https://discord.gg/urUm3VG
[discord-badge]: https://img.shields.io/discord/279322074412089344?color=%237289DA&logo=discord&logoColor=ffffff

[papermario-repo]: https://github.com/pmret/papermario
