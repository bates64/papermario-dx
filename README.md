# Paper Mario DX

[![Discord Channel][discord-badge]][discord]

This is a fork of the [Paper Mario decompilation](papermario-repo) which provides a nice base for modding.

To get started, see [docs.starhaven.dev](https://docs.starhaven.dev/tools/decomp/setup.html).

[discord]: https://discord.gg/urUm3VG
[discord-badge]: https://img.shields.io/discord/279322074412089344?color=%237289DA&logo=discord&logoColor=ffffff
[papermario-repo]: https://github.com/pmret/papermario

## List of changes

- US release only (no JP, PAL, or iQue - none of these are near 100% yet).
- Default configure flags: `--shift --modern-gcc --non-matching --ccache` and `AVOID_UB`
- Backtrace (call stack) on crash screen including file names and line numbers.
    - You can call [`debug_backtrace()`](src/dx/backtrace.h) to print a backtrace in any function.
    - Failed assertions (`ASSERT`) will trigger the crash screen and print a backtrace instead of hanging.
    - Backtraces provide filenames and line numbers for files with debug symbols (pass `--debug` to configure to enable for all files).
- `assets/star_rod_build` directory for Star Rod to write assets to.
- Fixed many bugs / incorrect behaviour.
- Skip compiling or linking dead code.
- Link with [libgcc_vr4300] to provide compiler intrinsics.
- Enemy HP is now a `s16`, increasing the cap to 32767.
- Additional features can be configured in [src/dx/config.h](src/dx/config.h).

[libgcc_vr4300]: https://github.com/Decompollaborate/libgcc_vr4300
