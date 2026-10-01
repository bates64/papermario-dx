// Follow the resolved audio catalog, including mod additions and deletions.
// Included by debug_menu.c after the shared menu drawing/input helpers.
typedef struct DebugMusicEntry {
    s32 songID;
    const char* name;
} DebugMusicEntry;

static const DebugMusicEntry DebugMusicSongs[] = {
#include "audio/debug_music_catalog.h"
};

#define DEBUG_MUSIC_VISIBLE_ROWS 9
static s32 DebugMusicPos = 0;
static s32 DebugMusicStart = 0;

void dx_debug_update_select_music() {
    s32 count = ARRAY_COUNT(DebugMusicSongs);
    s32 row;
    char fmtBuf[48];

    if (DebugStateChanged) {
        DebugMusicPos = MAX(0, MIN(DebugMusicPos, count - 1));
        DebugMusicStart = MAX(0, MIN(DebugMusicStart, count - DEBUG_MUSIC_VISIBLE_ROWS));
    }
    DebugMusicPos = dx_debug_menu_nav_1D_vertical(DebugMusicPos, 0, count - 1, false);
    if (NAV_LEFT) {
        DebugMusicPos = MAX(0, DebugMusicPos - DEBUG_MUSIC_VISIBLE_ROWS);
    } else if (NAV_RIGHT) {
        DebugMusicPos = MIN(count - 1, DebugMusicPos + DEBUG_MUSIC_VISIBLE_ROWS);
    }
    if (DebugMusicPos < DebugMusicStart) {
        DebugMusicStart = DebugMusicPos;
    } else if (DebugMusicPos >= DebugMusicStart + DEBUG_MUSIC_VISIBLE_ROWS) {
        DebugMusicStart = DebugMusicPos - DEBUG_MUSIC_VISIBLE_ROWS + 1;
    }

    if (RELEASED(BUTTON_L)) {
        DebugMenuState = DBM_SOUND_PLAYER;
        return;
    } else if (RELEASED(BUTTON_Z)) {
        bgm_set_song(0, AU_SONG_NONE, 0, 0, VOL_LEVEL_FULL);
    } else if (RELEASED(BUTTON_R)) {
        // Use the normal BGM transition, without touching the battle's saved song.
        bgm_set_song(0, DebugMusicSongs[DebugMusicPos].songID, 0, 0, VOL_LEVEL_FULL);
    }

    dx_debug_draw_box(16, 26, 288, 205, WINDOW_STYLE_20, 240);
    sprintf(fmtBuf, "Music   %ld / %ld", DebugMusicPos + 1, count);
    dx_debug_draw_ascii(fmtBuf, MSG_PAL_YELLOW, 26, 32);
    for (row = 0; row < DEBUG_MUSIC_VISIBLE_ROWS && DebugMusicStart + row < count; row++) {
        s32 index = DebugMusicStart + row;
        s32 color = index == DebugMusicPos ? HighlightColor : DefaultColor;

        sprintf(fmtBuf, "%02lX", DebugMusicSongs[index].songID);
        dx_debug_draw_ascii(fmtBuf, color, 26, 51 + row * RowHeight);
        dx_debug_draw_ascii(DebugMusicSongs[index].name, color, 50, 51 + row * RowHeight);
    }
    if (!gGameStatusPtr->musicEnabled) {
        dx_debug_draw_ascii("Music is disabled", MSG_PAL_YELLOW, 26, 188);
    } else if (gMusicControlData[0].requestedSongID < 0) {
        dx_debug_draw_ascii("Stopped", HoverColor, 26, 188);
    } else {
        sprintf(fmtBuf, "Selected song: %02lX", gMusicControlData[0].requestedSongID);
        dx_debug_draw_ascii(fmtBuf, HoverColor, 26, 188);
    }
    dx_debug_draw_ascii("R Play   Z Stop   L Back", DefaultColor, 26, 203);
    dx_debug_draw_ascii("Left/Right Page", DefaultColor, 26, 217);
}
