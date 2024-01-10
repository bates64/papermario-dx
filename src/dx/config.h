#ifndef DX
#define DX

/// Enables the debug menu.
#define DX_DEBUG_MENU 1

/// Skips logos (Nintendo, Intelligent Systems, etc.).
#define DX_SKIP_LOGOS 1

/// Skips the title screen.
#define DX_SKIP_TITLE 1

/// Skips the file select.
/// If a save file exists, the game will load it automatically, otherwise it will start a new game.
#define DX_SKIP_FILE_SELECT 1

/// Map to load when starting a new game.
#define NEW_GAME_MAP_ID "kmr_20"

/// Entry to use when starting a new game.
#define NEW_GAME_ENTRY_ID kmr_20_ENTRY_0

/// Story progress when starting a new game.
#define NEW_GAME_STORY_PROGRESS STORY_INTRO

/// Enables the profiler, which shows lots of performance info on screen.
/// Press L + D-Pad Up to show/hide the profiler.
#define USE_PROFILER 1

#endif
