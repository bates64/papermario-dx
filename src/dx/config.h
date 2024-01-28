#ifndef DX
#define DX

/// Version string that appears on the file select menu.
/// Comment out this definition to prevent it from being shown.
#define DX_MOD_VERSION_STRING "New Mod 1.0.0"

/// Enables the debug menu.
#define DX_DEBUG_MENU 1

/// Loads last used save file
#define DX_QUICK_LAUNCH 0

/// Skips logos (Nintendo, Intelligent Systems, etc.).
#define DX_SKIP_LOGOS 1

/// Skips the introductory storybook.
#define DX_SKIP_STORY 1

/// Skips the demo reel playing while waiting for the player to 'Press Start'.
#define DX_SKIP_DEMO 1

/// Map to load when starting a new game.
#define NEW_GAME_MAP_ID "kmr_20"

/// Entry to use when starting a new game.
#define NEW_GAME_ENTRY_ID kmr_20_ENTRY_0

/// Story progress when starting a new game.
#define NEW_GAME_STORY_PROGRESS STORY_INTRO

/// Enables the profiler, which shows lots of performance info on screen.
/// Press L + D-Pad Up to show/hide the profiler.
#define USE_PROFILER 1

/// Skip laggy blur operations when opening the pause menu on emulator
#define DX_PAUSE_LAG_FIX 1

#endif
