# Changelog

<!-- Format based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/) -->

## [Nightly]

First versioned release. The following changes are relative to [vanilla Paper Mario].

### Added

- DX settings can be configured in [src/dx/config.h](src/dx/config.h):
    - Quick launch into first save file on boot with `DX_QUICK_LAUNCH`.
    - Change 'First Play' map with `NEW_GAME_MAP_ID`.
    - Adjust the title screen with `DX_SKIP_LOGOS`, `DX_SKIP_STORY`, `DX_SKIP_DEMO`.
    - Debug/cheat menu, disable with `DX_DEBUG_MENU`.
    - Profiler, enable with `USE_PROFILER`.
- Abstracted memory overlay API with `ovl_load`. Supports maps and actors, with more overlay types to come in future releases.
- Backtrace (call stack) on crash screen including file names and line numbers.
    - You can call `debug_backtrace` to print a backtrace in any function.
    - Failed assertions (`ASSERT`) will trigger the crash screen and print a backtrace instead of hanging.
    - Backtraces provide filenames and line numbers for files with debug symbols.
- `assets/star_rod_build` directory for Star Rod to write assets to.
- Link with [libgcc_vr4300] to provide compiler intrinsics.
- EVT script instructions `ExecOnActor` and `ExecWaitOnActor`, which are similar to `Exec` and `ExecWait` but execute the script as a specific actor.
- EVT API function `DoesActorExport` to query whether an actor's overlay exports a symbol.

### Changed

- Modern compiler toolchain (GCC).
- Enemy max HP increased to 32767.
- Badges can cost negative BP.
- Message file improvements:
    - Messages are automatically discovered at `assets/*/msg/*.msg`.
    - You can now override a message using its name, e.g. `#message:0C:(CH1_0000)`.
    - It is now an error to have duplicate message names or IDs (within the same layer of the asset stack).

### Removed

- US is the only supported version for now (no JP, PAL, or iQue).
- Removed dead (unused) code.

### Fixed

- Fixed lag spike due to blur effect when pausing in certain emulators, disable with `DX_PAUSE_LAG_FIX`.
- Fixed many bugs / incorrect behaviour.

[libgcc_vr4300]: https://github.com/Decompollaborate/libgcc_vr4300
[vanilla Paper Mario]: https://github.com/pmret/papermario

[nightly]: https://github.com/bates64/papermario-dx/compare/v26.04...dx-nightly
