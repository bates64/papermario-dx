#ifndef DX
#define DX

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
#define NEW_GAME_MAP_ID "nok_11"

/// Entry to use when starting a new game.
#define NEW_GAME_ENTRY_ID nok_11_ENTRY_0

/// Story progress when starting a new game.
#define NEW_GAME_STORY_PROGRESS STORY_CH1_MADE_FIRST_BRIDGE

/// Enables the profiler, which shows lots of performance info on screen.
/// Press L + D-Pad Up to show/hide the profiler.
#define USE_PROFILER 1

#define GIVE_ALL_PARTNERS 1

/// Skip laggy blur operations when opening the pause menu on emulator
#define DX_PAUSE_LAG_FIX 1

#endif
