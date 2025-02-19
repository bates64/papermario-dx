# Paper Mario DX

[![Release](https://img.shields.io/github/v/release/bates64/papermario-dx)][releases]
[![Download](https://img.shields.io/github/downloads/bates64/papermario-dx/total)][download]
![Build Status](https://img.shields.io/github/actions/workflow/status/bates64/papermario-dx/build.yaml)

This is a fork of the [Paper Mario decompilation][papermario-repo] which provides a flexible, easy-to-use base for creating romhacks.

To get started, **[read the introduction](https://pmdx.bates64.com/md_manual_2introduction.html)**!

[discord]: https://discord.gg/star-haven
[discord-badge]: https://img.shields.io/discord/279322074412089344?color=%237289DA&logo=discord&logoColor=ffffff
[papermario-repo]: https://github.com/pmret/papermario
[releases]: https://github.com/bates64/papermario-dx/releases
[download]: https://github.com/bates64/papermario-dx/releases/download/latest/papermario.bps

### Features

- Modern toolchain with C++ support
- Compatible with [Star Rod](https://github.com/z64a/star-rod) and [Mamar](https://mamar.bates64.com)
- Debug/cheat menu (`DX_DEBUG_MENU`; press D-Pad Left)
- Print logs to the screen with `debug_printf` and `DebugPrintf`
- Better crash screens: backtraces, file names, line numbers
- Quick-launch into the world or a battle (`DX_QUICK_LAUNCH`, `DX_QUICK_LAUNCH_BATTLE`)
- Assertions display an error message instead of freezing
- Performance profiler (`DX_PROFILER`; press L + D-Pad Up)
- Actor HP max increased to 32767 (from 127)
- Badge BP costs can be negative, giving the player BP
- Save file versioning and migration
- Bugfixes and code quality improvements

And more!
