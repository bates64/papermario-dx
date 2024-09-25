#include "dx/debug_menu.h"
#if DX_DEBUG_MENU || defined(DX_QUICK_LAUNCH_BATTLE)
#include "game_modes.h"
#include "battle/battle.h"
#include "hud_element.h"
#include "qsort.h"

// layout

const s32 MainMenuPosX    = 26;
const s32 MainMenuPosY    = 60;

const s32 RowHeight       = 15;
const s32 BottomRowY      = 222;

const s32 SubmenuPosX     = 140;
const s32 SubmenuPosY     = MainMenuPosY;

const s32 SubBoxPosX      = SubmenuPosX - 10;
const s32 SubBoxPosY      = SubmenuPosY - 4;

// which menu or submenu is open, only one is displayed at a time
// pressing ACCEPT (R) or CANCEL (L) usually moves between these states
enum DebugMenuStates {
    DBM_NONE,
    DBM_MAIN_MENU,
    DBM_QUICK_SAVE,
    DBM_SELECT_AREA,
        DBM_SELECT_MAP,
        DBM_SELECT_ENTRY,
    DBM_SELECT_BATTLE,
    DBM_SET_STORY,
    DBM_SOUND_PLAYER,
        DBM_SELECT_SOUND,
    DBM_EDIT_PARTNERS,
    DBM_EDIT_INVENTORY,
        DBM_INV_EDIT_ITEMS,
        DBM_INV_EDIT_BADGES,
        DBM_INV_EDIT_KEYS,
        DBM_INV_EDIT_GEAR,
        DBM_INV_EDIT_STATS,
        DBM_INV_EDIT_COINS,
        DBM_INV_EDIT_STAR_POINTS,
        DBM_INV_EDIT_STAR_PIECES,
    DBM_EDIT_MEMORY,
    DBM_VIEW_COLLISION,
    DBM_CHEAT_MENU,
};

s32 DebugMenuState = DBM_NONE;
b32 DebugStateChanged = FALSE;

const s32 DefaultColor = MSG_PAL_WHITE;
const s32 HoverColor   = MSG_PAL_GREEN;
const s32 SelectColor  = MSG_PAL_PURPLE;
s32 HighlightColor;

// data grabbed during map or battle load

char LastMapName[16];
char LastStageName[16];
s32 LastMapEntry;
s32 LastBattleID;

void dx_debug_set_map_info(char* mapName, s32 entryID) {
    strcpy(LastMapName, mapName);
    LastMapEntry = entryID;
}

void dx_debug_set_battle_info(s32 battleID, char* stageName) {
    s32 len = strlen(stageName);

    strcpy(LastStageName, stageName);
    if (len > 6) {
        // trim "_shape" from name
        LastStageName[len - 6] = '\0';
    }
    LastBattleID = battleID;
}

// input

u32 DebugButtonsCur;
u32 DebugButtonsPrev;
u32 DebugButtonsPress;
u32 DebugButtonsHold;
u32 DebugButtonsRelease;

typedef struct DebugHold {
    s16 delay;
    u16 triggers;
} DebugHold;

DebugHold DebugHoldU = { 0 };
DebugHold DebugHoldD = { 0 };
DebugHold DebugHoldL = { 0 };
DebugHold DebugHoldR = { 0 };

#define PRESSED(but) (DebugButtonsPress & (but))
#define RELEASED(but) (DebugButtonsRelease & (but))
#define HELD(but) (DebugButtonsHold & (but))

#define INIT_HOLD_RATE 6 // slight start-up delay
#define SLOW_HOLD_RATE 4
#define FAST_HOLD_RATE 2

void dx_debug_update_hold_frames(DebugHold* hold, u32 but) {
    if (PRESSED(but)) {
        hold->delay = INIT_HOLD_RATE;
        hold->triggers = 0;
    } else if (HELD(but)) {
        hold->delay--;
        if (hold->delay < 0) {
            hold->triggers++;

            if (hold->triggers < 5) {
                hold->delay = SLOW_HOLD_RATE;
            } else if (hold->triggers < 15) {
                hold->delay = FAST_HOLD_RATE;
            } else {
                hold->delay = 1;
            }
        }
    } else {
        hold->delay = 999;
        hold->triggers = 0;
    }
}

void dx_debug_update_buttons() {
    DebugButtonsPrev = DebugButtonsCur;
    DebugButtonsCur = gGameStatus.curButtons[0];
    DebugButtonsHold = DebugButtonsCur & DebugButtonsPrev;
    DebugButtonsPress = DebugButtonsCur & (DebugButtonsCur ^ DebugButtonsPrev);
    DebugButtonsRelease = DebugButtonsPrev & (DebugButtonsCur ^ DebugButtonsPrev);

    dx_debug_update_hold_frames(&DebugHoldU, BUTTON_D_UP);
    dx_debug_update_hold_frames(&DebugHoldD, BUTTON_D_DOWN);
    dx_debug_update_hold_frames(&DebugHoldL, BUTTON_D_LEFT);
    dx_debug_update_hold_frames(&DebugHoldR, BUTTON_D_RIGHT);
};

#define NAV_UP    (PRESSED(BUTTON_D_UP)    || DebugHoldU.delay == 0)
#define NAV_DOWN  (PRESSED(BUTTON_D_DOWN)  || DebugHoldD.delay == 0)
#define NAV_LEFT  (PRESSED(BUTTON_D_LEFT)  || DebugHoldL.delay == 0)
#define NAV_RIGHT (PRESSED(BUTTON_D_RIGHT) || DebugHoldR.delay == 0)

// utility functions for drawing menus

void dx_debug_draw_box(s32 posX, s32 posY, s32 sizeX, s32 sizeY, int style, s32 opacity) {
    draw_box(0, (WindowStyle)style, posX, posY, 0, sizeX, sizeY, opacity,
        0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, NULL, 0, NULL, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
}

void dx_debug_draw_ascii(char* text, s32 color, s32 posX, s32 posY) {
    char buf[128] = {
        MSG_CHAR_READ_FUNCTION, MSG_READ_FUNC_SIZE, 12, 12
    };
    dx_string_to_msg(&buf[4], text);
    draw_msg((s32)buf, posX, posY, 255, color, 0);
}

void dx_debug_draw_ascii_with_effect(char* text, s32 color, s32 posX, s32 posY, s32 effect) {
    char buf[128] = {
        MSG_CHAR_READ_FUNCTION, MSG_READ_FUNC_SIZE, 12, 12
    };
    dx_string_to_msg(&buf[4], text);
    draw_msg((s32)buf, posX, posY, 255, color, effect);
}

void dx_debug_draw_msg(s32 msgID, s32 color, s32 alpha, s32 posX, s32 posY) {
    char buf[128] = {
        MSG_CHAR_READ_FUNCTION, MSG_READ_FUNC_SIZE, 12, 12
    };
    dma_load_msg(msgID, &buf[4]);
    draw_msg((s32)buf, posX, posY, alpha, color, 0);
}

void dx_debug_draw_number(s32 number, char* fmt, s32 color, s32 alpha, s32 posX, s32 posY) {
    char fmtBuf[16];
    char buf[16] = {
        MSG_CHAR_READ_FUNCTION, MSG_READ_FUNC_SIZE, 12, 12
    };
    sprintf(fmtBuf, fmt, number);
    dx_string_to_msg(&buf[4], fmtBuf);
    draw_msg((s32)buf, posX, posY, alpha, color, 0);
}

// efficiently renders an number with (optionally) a digit highlighted using a single draw_msg call
void dx_debug_draw_editable_number(s32 number, char* fmt, s32 selectedDigit, b32 hasSelected, s32 posX, s32 posY) {
    char msgBuf[32] = {
        MSG_CHAR_READ_FUNCTION, MSG_READ_FUNC_SIZE, 12, 12,
        MSG_CHAR_READ_FUNCTION, MSG_READ_FUNC_SPACING, 8
    };
    s32 pos = 7; // writePos to msgBuf

    char fmtBuf[16];
    s32 len = sprintf(fmtBuf, fmt, number);
    s32 idx; // readPos from fmtBuf

    for (idx = 0; idx < len; idx++) {
        if (hasSelected && selectedDigit == idx) {
            msgBuf[pos++] = MSG_CHAR_READ_FUNCTION;
            msgBuf[pos++] = MSG_READ_FUNC_SAVE_COLOR;
            msgBuf[pos++] = MSG_CHAR_READ_FUNCTION;
            msgBuf[pos++] = MSG_READ_FUNC_COLOR;
            msgBuf[pos++] = HighlightColor;
        }
        msgBuf[pos++] = dx_ascii_char_to_msg(fmtBuf[idx]);
        if (hasSelected && selectedDigit == idx) {
            msgBuf[pos++] = MSG_CHAR_READ_FUNCTION;
            msgBuf[pos++] = MSG_READ_FUNC_RESTORE_COLOR;
        }
    }
    msgBuf[pos] = MSG_CHAR_READ_END;

    if (hasSelected && selectedDigit == -1) {
        draw_msg((s32)msgBuf, posX, posY, 255, HighlightColor, 0);
    } else {
        draw_msg((s32)msgBuf, posX, posY, 255, DefaultColor, 0);
    }
}

// utility functions for menu navigation

s32 dx_debug_clamp(s32 v, s32 min, s32 max) {
  const s32 u = v < min ? min : v;
  return u > max ? max : u;
}

s32 dx_debug_wrap(s32 v, s32 min, s32 max) {
  const s32 u = v < min ? v + (max - min + 1) : v;
  return u > max ? u - (max - min + 1) : u;
}

// range from [min, max] with min < max
s32 dx_debug_menu_nav_1D_vertical(s32 cur, s32 min, s32 max, b32 flip) {
    if (NAV_UP) {
        if(flip) {
            cur++;
        } else {
            cur--;
        }
    }
    if (NAV_DOWN) {
        if(flip) {
            cur--;
        } else {
            cur++;
        }
    }
    // wrap
    if (cur < min) {
        cur += (1 + max - min);
    }
    if (cur > max) {
        cur -= (1 + max - min);
    }
    return cur;
}

// range from [min, max] with min < max
s32 dx_debug_menu_nav_1D_horizontal(s32 cur, s32 min, s32 max, b32 flip) {
    if (NAV_LEFT) {
        if(flip) {
            cur++;
        } else {
            cur--;
        }
    }
    if (NAV_RIGHT) {
        if(flip) {
            cur--;
        } else {
            cur++;
        }
    }
    // wrap
    if (cur < min) {
        cur += (1 + max - min);
    }
    if (cur > max) {
        cur -= (1 + max - min);
    }
    return cur;
}

s32 dx_debug_menu_nav_2D(s32 cur, s32 max, s32 nrows) {
    s32 ncols = max / nrows;
    if ((max % nrows) != 0) {
        ncols++;
    }

    if (NAV_UP) {
        cur--;
        if (cur < 0) {
            cur += nrows;
        }
        else if (cur % nrows == nrows - 1) {
            cur += nrows;
        }
        while (cur >= max) {
            cur--;
        }
    }
    if (NAV_DOWN) {
        cur++;
        if (cur >= max) {
            cur = (cur / nrows) * nrows;
        }
        else if (cur % nrows == 0) {
            cur -= nrows;
        }
    }
    if (NAV_LEFT) {
        cur -= nrows;
        if (cur < 0) {
            cur += (nrows * ncols);
            while (cur >= max) {
                cur -= nrows;
            }
        }
    }
    if (NAV_RIGHT) {
        cur += nrows;
        if (cur >= max) {
            cur -= (nrows * ncols);
            while (cur < 0) {
                cur += nrows;
            }
        }
    }
    return cur;
}

// utility functions for number input fields

typedef struct DebugEditableNumber {
    b8 isHex;
    s8 pos;
    s8 size;
    s8 digits[];
} DebugEditableNumber;

void dx_debug_nav_editable_num(DebugEditableNumber* num) {
    s32 max = num->isHex ? 0xF : 9;

    if (num->size > 1) {
        num->pos = dx_debug_menu_nav_1D_horizontal(num->pos, 0, num->size - 1, FALSE);
    }
    num->digits[num->pos] = dx_debug_menu_nav_1D_vertical(num->digits[num->pos], 0, max, TRUE);
}

void dx_debug_draw_editable_num(DebugEditableNumber* num, s32 posX, s32 posY) {
    char* fmt = num->isHex ? "%X" : "%d";
    s32 idx;

    for (idx = 0; idx < num->size; idx++) {
        s32 color = (num->pos == idx) ? HighlightColor : DefaultColor;
        dx_debug_draw_number(num->digits[idx], fmt, color, 255, posX + (7 * idx), posY);
    }
}

s32 dx_debug_get_editable_num(DebugEditableNumber* num) {
    s32 idx;
    s32 out = 0;

    if (num->isHex) {
        for (idx = 0; idx < num->size; idx++) {
            out <<= 4;
            out |= (num->digits[idx] & 0xF);
        }
    } else {
        for (idx = 0; idx < num->size; idx++) {
            out *= 10;
            out += num->digits[idx];
        }
    }

    return out;
}

void dx_debug_set_editable_num(DebugEditableNumber* num, s32 in) {
    s32 idx;

    if (num->isHex) {
        for (idx = num->size - 1; idx >= 0; idx--) {
            num->digits[idx] = (in & 0xF);
            in >>= 4;
        }
    } else {
        for (idx = num->size - 1; idx >= 0; idx--) {
            num->digits[idx] = in % 10;
            in /= 10;
        }
    }
}

// menus

void dx_debug_draw_main_menu();

b32 dx_debug_menu_is_open() {
    return DebugMenuState != DBM_NONE;
}

void dx_debug_exec_full_restore() {
    gPlayerData.curHP = gPlayerData.curMaxHP;
    gPlayerData.curFP = gPlayerData.curMaxFP;
    gPlayerData.starPower = gPlayerData.maxStarPower * SP_PER_BAR;
    sfx_play_sound(SOUND_UNUSED_STAR_SPIRIT_APPEARS);
}

typedef struct DebugMenuEntry {
    char* text;
    void (*onSelect)();
    s32 nextState;
} DebugMenuEntry;

DebugMenuEntry DebugMainMenu[] = {
    { "Full Restore",   dx_debug_exec_full_restore },
    { "Save/Load",      NULL, DBM_QUICK_SAVE },
    { "Map Select",     NULL, DBM_SELECT_AREA },
    { "Battle Select",  NULL, DBM_SELECT_BATTLE },
    { "Set Story Byte", NULL, DBM_SET_STORY },
    { "Sound Player",   NULL, DBM_SOUND_PLAYER },
    { "Edit Partners",  NULL, DBM_EDIT_PARTNERS },
    { "Edit Inventory", NULL, DBM_EDIT_INVENTORY },
//  { "Edit Memory",    NULL, DBM_EDIT_MEMORY },
    { "View Collision", NULL, DBM_VIEW_COLLISION },
    { "Cheats",         NULL, DBM_CHEAT_MENU },
};
s32 MainMenuPos = 0;

// position of the blue box containing the main menu options
const s32 MainBoxPosX     = MainMenuPosX - 10;
const s32 MainBoxPosY     = MainMenuPosY - 4;
const s32 MainBoxWidth    = 96;
const s32 MainBoxHeight   = ARRAY_COUNT(DebugMainMenu) * RowHeight + 8;

f32 ArrowAnimOffset = 0;
f32 DebugArrowPhase = 0.0f;
#define DEBUG_ARROW_ANIM_RATE 6

void dx_debug_menu_main() {
    s32 initialMenuState = DebugMenuState;

    dx_debug_update_buttons();

    HighlightColor = HELD(BUTTON_R) ? SelectColor : HoverColor;

    DebugArrowPhase += DEBUG_ARROW_ANIM_RATE;
    if (DebugArrowPhase >= 360.0f) {
        DebugArrowPhase -= 360.0f;
    }
    ArrowAnimOffset = cos_deg(DebugArrowPhase);

    dx_debug_update_banner();

    // check input for menu open/close
    if (DebugMenuState == DBM_NONE) {
        if (PRESSED(BUTTON_D_LEFT)) {
            DebugMenuState = DBM_MAIN_MENU;
        }
    } else if (DebugMenuState == DBM_MAIN_MENU) {
        if (PRESSED(BUTTON_D_LEFT | BUTTON_L)) {
            DebugMenuState = DBM_NONE;
        }
    }

    if (DebugMenuState != DBM_NONE) {
        // main menu is always drawn if the debug menu is open at all
        dx_debug_draw_main_menu();

        switch(DebugMenuState) {
            case DBM_MAIN_MENU:
                dx_debug_update_main_menu();
                break;
            case DBM_QUICK_SAVE:
                dx_debug_update_quick_save();
                break;
            case DBM_SELECT_AREA:
                dx_debug_update_select_area();
                break;
            case DBM_SELECT_MAP:
                dx_debug_update_select_map();
                break;
            case DBM_SELECT_ENTRY:
                dx_debug_update_select_entry();
                break;
            case DBM_SELECT_BATTLE:
                dx_debug_update_select_battle();
                break;
            case DBM_SET_STORY:
                dx_debug_update_edit_progress();
                break;
            case DBM_SOUND_PLAYER:
                dx_debug_update_sound_player();
                break;
            case DBM_SELECT_SOUND:
                dx_debug_update_select_sound();
                break;
            case DBM_EDIT_PARTNERS:
                dx_debug_update_edit_partners();
                break;
            case DBM_EDIT_INVENTORY:
                dx_debug_update_edit_inventory();
                break;
            case DBM_INV_EDIT_ITEMS:
                dx_debug_update_edit_items();
                break;
            case DBM_INV_EDIT_BADGES:
                dx_debug_update_edit_items();
                break;
            case DBM_INV_EDIT_KEYS:
                dx_debug_update_edit_items();
                break;
            case DBM_INV_EDIT_GEAR:
                dx_debug_update_edit_gear();
                break;
            case DBM_INV_EDIT_STATS:
                dx_debug_update_edit_stats();
                break;
            case DBM_INV_EDIT_COINS:
                dx_debug_update_edit_coins();
                break;
            case DBM_INV_EDIT_STAR_POINTS:
                dx_debug_update_edit_star_points();
                break;
            case DBM_INV_EDIT_STAR_PIECES:
                dx_debug_update_edit_star_pieces();
                break;
            case DBM_EDIT_MEMORY:
                break;
            case DBM_VIEW_COLLISION:
                dx_debug_update_view_collision();
                break;
            case DBM_CHEAT_MENU:
                dx_debug_update_cheat_menu();
                break;
        }
    }

    DebugStateChanged = (initialMenuState != DebugMenuState);
}

void dx_debug_update_main_menu() {
    MainMenuPos = dx_debug_menu_nav_1D_vertical(MainMenuPos, 0, ARRAY_COUNT(DebugMainMenu) - 1, FALSE);
    if (RELEASED(BUTTON_R | BUTTON_D_RIGHT)) {
        if (DebugMainMenu[MainMenuPos].onSelect != NULL) {
            DebugMainMenu[MainMenuPos].onSelect();
        } else {
            DebugMenuState = DebugMainMenu[MainMenuPos].nextState;
        }
    }
}

void dx_debug_draw_main_menu() {
    s32 idx;

    dx_debug_draw_box(MainBoxPosX, MainBoxPosY, MainBoxWidth, MainBoxHeight, WINDOW_STYLE_4, 192);

    for (idx = 0; idx < ARRAY_COUNT(DebugMainMenu); idx++) {
        s32 color = DefaultColor;
        if (MainMenuPos == idx) {
            color = (DebugMenuState == DBM_MAIN_MENU) ? HighlightColor : HoverColor;
        }
        dx_debug_draw_ascii(DebugMainMenu[idx].text, color, MainMenuPosX, MainMenuPosY + idx * RowHeight);
    }
}

// ----------------------------------------------------------------------------
// quick save
// only restores previous player position on maps with save points, otherwise enters through most recent entry

void dx_debug_exec_quick_save() {
    sfx_play_sound(SOUND_MENU_SHOW_CHOICE);
    gGameStatusPtr->savedPos.x = gPlayerStatusPtr->pos.x;
    gGameStatusPtr->savedPos.y = gPlayerStatusPtr->pos.y;
    gGameStatusPtr->savedPos.z = gPlayerStatusPtr->pos.z;
    fio_save_game(gGameStatusPtr->saveSlot);
    DebugMenuState = DBM_MAIN_MENU;
}

void dx_debug_exec_quick_load() {
    fio_load_game(gGameStatus.saveSlot);
    set_map_transition_effect(TRANSITION_STANDARD);
    set_game_mode(GAME_MODE_ENTER_WORLD);
    DebugMenuState = DBM_MAIN_MENU;
}

DebugMenuEntry DebugQuickSaveMenu[] = {
    { "Cancel", NULL, DBM_MAIN_MENU },
    { "Quick Save", dx_debug_exec_quick_save },
    { "Quick Load", dx_debug_exec_quick_load },
};
s32 QuickSaveMenuPos = 0;

void dx_debug_update_quick_save() {
    s32 idx;

    // handle input
    QuickSaveMenuPos = dx_debug_menu_nav_1D_vertical(QuickSaveMenuPos, 0, ARRAY_COUNT(DebugQuickSaveMenu) - 1, FALSE);
    if (RELEASED(BUTTON_L)) {
        DebugMenuState = DBM_MAIN_MENU;
    } else if (RELEASED(BUTTON_R)) {
        if (DebugQuickSaveMenu[QuickSaveMenuPos].onSelect != NULL) {
            DebugQuickSaveMenu[QuickSaveMenuPos].onSelect();
        } else {
            DebugMenuState = DebugQuickSaveMenu[QuickSaveMenuPos].nextState;
        }
    }

    // draw
    dx_debug_draw_box(SubBoxPosX, SubBoxPosY + RowHeight, 75, ARRAY_COUNT(DebugQuickSaveMenu) * RowHeight + 8, WINDOW_STYLE_20, 192);

    for (idx = 0; idx < ARRAY_COUNT(DebugQuickSaveMenu); idx++) {
        s32 color = (QuickSaveMenuPos == idx) ? HighlightColor : DefaultColor;
        dx_debug_draw_ascii(DebugQuickSaveMenu[idx].text, color, SubmenuPosX, SubmenuPosY + (idx + 1) * RowHeight);
    }
}

// ----------------------------------------------------------------------------
// map select

s32 SelectAreaMenuPos = 0;
s32 SelectMapMenuPos = 0;
s32 SelectedEntryValue = 0;

const s32 AreaSizeX = 30;
const s32 MapSizeX = 50;

void dx_debug_update_select_area() {
    s32 i, j, idx;
    s32 nrows, ncols;
    s32 numAreas = ARRAY_COUNT(gAreas) - 1;
    s32 prev = SelectAreaMenuPos;

    // select optimal shape for the menu based on numAreas
    // maximum supported size is 9 x 5 (45 areas)

    if (numAreas <= 6) {
        nrows = numAreas;
        ncols = 1;
    } else if (numAreas <= 12) {
        nrows = 6;
        ncols = 2;
    } else if (numAreas <= 18) {
        nrows = 6;
        ncols = 3;
    } else if (numAreas <= 24) {
        nrows = 6;
        ncols = 4;
    } else if (numAreas <= 30) {
        nrows = 6;
        ncols = 5;
    } else if (numAreas <= 35) {
        nrows = 7;
        ncols = 5;
    } else if (numAreas <= 40) {
        nrows = 8;
        ncols = 5;
    } else {
        nrows = 9;
        ncols = 5;
    }

    // handle input

    SelectAreaMenuPos = dx_debug_menu_nav_2D(SelectAreaMenuPos, numAreas, nrows);
    if (SelectAreaMenuPos != prev) {
        SelectMapMenuPos = 0;
        SelectedEntryValue = 0;
    }
    if (RELEASED(BUTTON_L)) {
        DebugMenuState = DBM_MAIN_MENU;
    } else if (RELEASED(BUTTON_R)) {
        DebugMenuState = DBM_SELECT_MAP;
    }

    // draw

    dx_debug_draw_box(SubBoxPosX, SubBoxPosY + RowHeight, AreaSizeX * ncols + 8, RowHeight * nrows + 8, WINDOW_STYLE_20, 192);

    idx = 0;
    for (i = 0; i < ncols; i++) {
        for (j = 0; j < nrows; j++) {
            if (idx < numAreas) {
                s32 color = (SelectAreaMenuPos == idx) ? HighlightColor : DefaultColor;
                char* name = &(gAreas[idx].id)[5]; // trim "area_" prefix
                dx_debug_draw_ascii(name, color, SubmenuPosX + i * AreaSizeX, SubmenuPosY + (j + 1) * RowHeight);
            }
            idx++;
        }
    }
}

void dx_debug_update_select_map() {
    s32 i, j, idx;
    s32 numRows, numCols;
    s32 curCol, maxCol, startCol;
    MapConfig* maps = gAreas[SelectAreaMenuPos].maps;
    s32 numMaps = gAreas[SelectAreaMenuPos].mapCount;
    s32 prev = SelectMapMenuPos;

    // select optimal shape for the menu based on numMaps

    if (numMaps <= 6) {
        numRows = numMaps;
        numCols = 1;
    } else if (numMaps <= 12) {
        numRows = 6;
        numCols = 2;
    } else {
        numRows = 6;
        numCols = 3;
    }

    // handle input

    SelectMapMenuPos = dx_debug_menu_nav_2D(SelectMapMenuPos, numMaps, numRows);
    if (SelectMapMenuPos != prev) {
        SelectedEntryValue = 0;
    }
    if (RELEASED(BUTTON_L)) {
        DebugMenuState = DBM_SELECT_AREA;
    } else if (RELEASED(BUTTON_R)) {
        DebugMenuState = DBM_SELECT_ENTRY;
    }

    // draw

    curCol = SelectMapMenuPos / numRows;
    maxCol = numMaps / numRows;

    if (maxCol > 2) {
        dx_debug_draw_box(SubBoxPosX, SubBoxPosY + RowHeight, MapSizeX * numCols + 8, RowHeight * (numRows + 1) + 8, WINDOW_STYLE_20, 192);
    } else {
        dx_debug_draw_box(SubBoxPosX, SubBoxPosY + RowHeight, MapSizeX * numCols + 8, RowHeight * numRows + 8, WINDOW_STYLE_20, 192);
    }

    if (maxCol < 3) {
        startCol = 0;
    } else if (curCol == 0) {
        startCol = 0;
    } else if (curCol == maxCol) {
        startCol = maxCol - 2;
    } else {
        startCol = curCol - 1;
    }

    idx = numRows * startCol;
    for (i = startCol; i <= startCol + 2; i++) {
        for (j = 0; j < numRows; j++) {
            if (idx < numMaps) {
                s32 color = (SelectMapMenuPos == idx) ? HighlightColor : DefaultColor;
                char* name = maps[idx].id;
                dx_debug_draw_ascii(name, color, SubmenuPosX + (i - startCol) * MapSizeX, SubmenuPosY + (j + 1) * RowHeight);
            }
            idx++;
        }
    }

    if (maxCol > 2) {
        // left arrow
        if (curCol > 1) {
            char msgLeftArrow[] = {
                MSG_CHAR_LEFT, MSG_CHAR_READ_END
            };
            draw_msg((s32)msgLeftArrow, SubmenuPosX - 2 - round(3.0f * ArrowAnimOffset), SubmenuPosY + 104, 255, DefaultColor, 0);
        }
        // right arrow
        if (curCol < maxCol - 1) {
            char msgRightArrow[] = {
                MSG_CHAR_RIGHT, MSG_CHAR_READ_END
            };
            draw_msg((s32)msgRightArrow, SubmenuPosX + 128 + round(3.0f * ArrowAnimOffset), SubmenuPosY + 104, 255, DefaultColor, 0);
        }
    }
}

void dx_debug_update_select_entry() {
    s32 idx, areaID, mapID;
    MapConfig map = gAreas[SelectAreaMenuPos].maps[SelectMapMenuPos];

    // handle input
    if (RELEASED(BUTTON_L)) {
        DebugMenuState = DBM_SELECT_MAP;
    } else if (RELEASED(BUTTON_R)) {
        gGameStatusPtr->areaID = SelectAreaMenuPos;
        gGameStatusPtr->mapID = SelectMapMenuPos;
        gGameStatusPtr->entryID = SelectedEntryValue;
        set_map_transition_effect(TRANSITION_STANDARD);
        set_game_mode(GAME_MODE_CHANGE_MAP);
        play_ambient_sounds(AMBIENT_SILENCE, 1);
        DebugMenuState = DBM_NONE;
    }

    if (NAV_UP) {
        SelectedEntryValue++;
    }
    if (NAV_DOWN) {
        SelectedEntryValue--;
    }

    if (SelectedEntryValue < 0) {
        SelectedEntryValue = 0;
    }
    if (SelectedEntryValue > 0x7F) {
        SelectedEntryValue = 0x7F;
    }

    // draw
    dx_debug_draw_box(SubBoxPosX, SubBoxPosY + RowHeight, 80, 2 * RowHeight + 8, WINDOW_STYLE_20, 192);

    for (idx = 0; idx < ARRAY_COUNT(DebugQuickSaveMenu); idx++) {
        char fmtBuf[16];
        dx_debug_draw_ascii(map.id, DefaultColor, SubmenuPosX, SubmenuPosY + RowHeight);
        dx_debug_draw_ascii("Entry:", DefaultColor, SubmenuPosX, SubmenuPosY + 2 * RowHeight);
        sprintf(fmtBuf, "%2X", SelectedEntryValue);
        dx_debug_draw_ascii(fmtBuf, HighlightColor, SubmenuPosX + 40, SubmenuPosY + 2 * RowHeight);
    }
}

// ----------------------------------------------------------------------------
// battle select

enum DebugBattleValues {
    DEBUG_BATTLE_AREA_TENS,
    DEBUG_BATTLE_AREA_ONES,
    DEBUG_BATTLE_FORMATION_TENS,
    DEBUG_BATTLE_FORMATION_ONES,
    DEBUG_BATTLE_STAGE,
};

s32 DebugBattleNum[] = {
    [DEBUG_BATTLE_AREA_TENS]        0,
    [DEBUG_BATTLE_AREA_ONES]        0,
    [DEBUG_BATTLE_FORMATION_TENS]   0,
    [DEBUG_BATTLE_FORMATION_ONES]   0,
    [DEBUG_BATTLE_STAGE]            -1,
};

s32 BattleDigitOffsets[] = {
    [DEBUG_BATTLE_AREA_TENS]        10,
    [DEBUG_BATTLE_AREA_ONES]        17,
    [DEBUG_BATTLE_FORMATION_TENS]   35,
    [DEBUG_BATTLE_FORMATION_ONES]   42,
    [DEBUG_BATTLE_STAGE]            63,
};

s32 DebugBattleColumn = 0;

EnemyDrops DebugDummyDrops = NO_DROPS;

Enemy DebugDummyEnemy = {
    .npcID = DX_DEBUG_DUMMY_ID,
    .drops = &DebugDummyDrops,
};

Encounter DebugDummyEncounter = {
    .encounterID = DX_DEBUG_DUMMY_ID,
    .enemy = &DebugDummyEnemy,
    .count = 0,
    .battle = 0,
    .stage = 0,
};

void dx_debug_begin_battle_with_IDs(s16 battle, s16 stage) {
    EncounterStatus* es = &gCurrentEncounter;

    DebugDummyEncounter.battle = battle;
    DebugDummyEncounter.stage = stage;

    es->curEncounter = &DebugDummyEncounter;
    es->curEnemy = &DebugDummyEnemy;
    es->hitType = ENCOUNTER_TRIGGER_NONE;
    es->firstStrikeType = FIRST_STRIKE_NONE;
    es->forbidFleeing = FALSE;
    es->scriptedBattle = TRUE;
    es->songID = -1;
    es->unk_18 = -1;
    es->fadeOutAmount = 0;
    es->unk_94 = 0;

    disable_player_input();
    partner_disable_input();

    gEncounterState = ENCOUNTER_STATE_PRE_BATTLE;
    gEncounterSubState = ENCOUNTER_SUBSTATE_PRE_BATTLE_INIT;
    D_8009A678 = 1;
}

void dx_debug_begin_battle() {
    s16 battle = (DebugBattleNum[DEBUG_BATTLE_AREA_TENS] & 0xF) << 12
        | (DebugBattleNum[DEBUG_BATTLE_AREA_ONES] & 0xF) << 8
        | (DebugBattleNum[DEBUG_BATTLE_FORMATION_TENS] & 0xF) << 4
        | (DebugBattleNum[DEBUG_BATTLE_FORMATION_ONES] & 0xF);
    s16 stage = DebugBattleNum[DEBUG_BATTLE_STAGE] & 0xFFFF;

    dx_debug_begin_battle_with_IDs(battle, stage);
}

void dx_debug_update_select_battle() {
    s32 idx;
    char fmtBuf[16];
    s32 maxAreaTens = ARRAY_COUNT(gBattleAreas) >> 4;

    // handle input
    if (RELEASED(BUTTON_L)) {
        DebugMenuState = DBM_MAIN_MENU;
    } else if (RELEASED(BUTTON_R)) {
        dx_debug_begin_battle();
        DebugMenuState = DBM_NONE;
    }

    DebugBattleColumn = dx_debug_menu_nav_1D_horizontal(DebugBattleColumn, 0, 4, FALSE);
    if (NAV_UP) {
        s32 value = DebugBattleNum[DebugBattleColumn] + 1;
        if (DebugBattleColumn == DEBUG_BATTLE_STAGE) {
            value = dx_debug_clamp(value, -1, 0x7F);
        } else if (DebugBattleColumn == DEBUG_BATTLE_AREA_TENS) {
            value = dx_debug_wrap(value, 0, maxAreaTens);
        } else {
            value = dx_debug_wrap(value, 0, 0xF);
        }
        DebugBattleNum[DebugBattleColumn] = value;
    }
    if (NAV_DOWN) {
        s32 value = DebugBattleNum[DebugBattleColumn] - 1;
        if (DebugBattleColumn == DEBUG_BATTLE_STAGE) {
            value = dx_debug_clamp(value, -1, 0x7F);
        } else if (DebugBattleColumn == DEBUG_BATTLE_AREA_TENS) {
            value = dx_debug_wrap(value, 0, maxAreaTens);
        } else {
            value = dx_debug_wrap(value, 0, 0xF);
        }
        DebugBattleNum[DebugBattleColumn] = value;
    }

    // draw
    dx_debug_draw_box(SubBoxPosX, SubBoxPosY + RowHeight, 104, 2 * RowHeight + 8, WINDOW_STYLE_20, 192);
    dx_debug_draw_ascii("Start Battle:", DefaultColor, SubmenuPosX, SubmenuPosY + 1 * RowHeight);
    dx_debug_draw_ascii("-", DefaultColor, SubmenuPosX + 26, SubmenuPosY + 2 * RowHeight);
    dx_debug_draw_ascii("(", DefaultColor, SubmenuPosX + 55, SubmenuPosY + 2 * RowHeight);
    dx_debug_draw_ascii(")", DefaultColor, SubmenuPosX + 77, SubmenuPosY + 2 * RowHeight);

    for (idx = 0; idx < 5; idx++) {
        s32 color = (DebugBattleColumn == idx) ? HighlightColor : DefaultColor;
        s32 offset = BattleDigitOffsets[idx];
        char* fmt = (idx == 4) ? "%02X" : "%X";

        dx_debug_draw_number(DebugBattleNum[idx] & 0xFF, fmt, color, 255, SubmenuPosX + offset, SubmenuPosY + 2 * RowHeight);
    }
}

// ----------------------------------------------------------------------------
// set story byte

DebugEditableNumber DebugStoryProgress = {
    .isHex = TRUE,
    .digits = { 0, 0 },
    .size = 2,
    .pos = 0,
};

void dx_debug_update_edit_progress() {
    if (DebugStateChanged) {
        s32 val = evt_get_variable(NULL, GB_StoryProgress);
        dx_debug_set_editable_num(&DebugStoryProgress, val);
    }

    // handle input
    if (RELEASED(BUTTON_L)) {
        DebugMenuState = DBM_MAIN_MENU;
    } else if (RELEASED(BUTTON_R)) {
        s32 val = dx_debug_get_editable_num(&DebugStoryProgress);
        evt_set_variable(NULL, GB_StoryProgress, val);
        sfx_play_sound(SOUND_MENU_BADGE_EQUIP);
    }

    dx_debug_nav_editable_num(&DebugStoryProgress);

    // draw
    dx_debug_draw_box(SubBoxPosX, SubBoxPosY + RowHeight, 104, 2 * RowHeight + 8, WINDOW_STYLE_20, 192);
    dx_debug_draw_ascii("Set Progress:", DefaultColor, SubmenuPosX, SubmenuPosY + RowHeight);
    dx_debug_draw_editable_num(&DebugStoryProgress, SubmenuPosX + 35, SubmenuPosY + 2 * RowHeight);
}

// ----------------------------------------------------------------------------
// sound player

DebugMenuEntry DebugSoundPlayerMenu[] = {
    { "Play Sound", NULL, DBM_SELECT_SOUND },
    { "Stop Sound", NULL, DBM_SELECT_SOUND },
};
s32 SoundPlayerMenuPos = 0;

void dx_debug_draw_sound_player(b32 activeMenu) {
    s32 idx;

    dx_debug_draw_box(SubBoxPosX, SubBoxPosY + RowHeight, 75, ARRAY_COUNT(DebugSoundPlayerMenu) * RowHeight + 8, WINDOW_STYLE_20, 192);

    for (idx = 0; idx < ARRAY_COUNT(DebugSoundPlayerMenu); idx++) {
        s32 color;
        if (activeMenu) {
            color = (SoundPlayerMenuPos == idx) ? HighlightColor : DefaultColor;
        } else {
            color = (SoundPlayerMenuPos == idx) ? HoverColor : DefaultColor;
        }
        dx_debug_draw_ascii(DebugSoundPlayerMenu[idx].text, color, SubmenuPosX, SubmenuPosY + (idx + 1) * RowHeight);
    }
}

void dx_debug_update_sound_player() {
    // handle input
    SoundPlayerMenuPos = dx_debug_menu_nav_1D_vertical(SoundPlayerMenuPos, 0, ARRAY_COUNT(DebugSoundPlayerMenu) - 1, FALSE);
    if (RELEASED(BUTTON_L)) {
        DebugMenuState = DBM_MAIN_MENU;
    } else if (RELEASED(BUTTON_R)) {
        DebugMenuState = DBM_SELECT_SOUND;
    }

    dx_debug_draw_sound_player(TRUE);
}

DebugEditableNumber DebugSoundID = {
    .isHex = TRUE,
    .digits = { 0, 0, 0, 0 },
    .size = 4,
    .pos = 0,
};

void dx_debug_update_select_sound() {
    // handle input
    if (RELEASED(BUTTON_L)) {
        DebugMenuState = DBM_SOUND_PLAYER;
    } else if (RELEASED(BUTTON_R)) {
        if (SoundPlayerMenuPos == 0) {
            sfx_play_sound(dx_debug_get_editable_num(&DebugSoundID) & 0xFFFF);
        } else {
            sfx_stop_sound(dx_debug_get_editable_num(&DebugSoundID) & 0xFFFF);
        }
    }

    dx_debug_nav_editable_num(&DebugSoundID);

    dx_debug_draw_sound_player(FALSE);
    dx_debug_draw_box(SubBoxPosX, SubBoxPosY + (4 * RowHeight), 75, 2 * RowHeight + 8, WINDOW_STYLE_20, 192);
    dx_debug_draw_ascii("Sound ID:", DefaultColor, SubmenuPosX, SubmenuPosY + 4 * RowHeight);
    dx_debug_draw_editable_num(&DebugSoundID, SubmenuPosX, SubmenuPosY + 5 * RowHeight);
}

// ----------------------------------------------------------------------------
// edit partners

s8 DebugPartnerLevels[ARRAY_COUNT(gPlayerData.partners)];
s32 SelectPartnerMenuPos = 1;

void dx_debug_update_edit_partners() {
    s32 idx;

    if (DebugStateChanged) {
        for (idx = 1; idx < ARRAY_COUNT(gPlayerData.partners); idx++) {
            DebugPartnerLevels[idx] = gPlayerData.partners[idx].enabled + gPlayerData.partners[idx].level - 1;
        }
    }

    // handle input
    SelectPartnerMenuPos = dx_debug_menu_nav_1D_vertical(SelectPartnerMenuPos, 1, ARRAY_COUNT(gPlayerData.partners) - 1, FALSE);
    DebugPartnerLevels[SelectPartnerMenuPos] = dx_debug_menu_nav_1D_horizontal(DebugPartnerLevels[SelectPartnerMenuPos], -1, 2, FALSE);
    if (RELEASED(BUTTON_L)) {
        DebugMenuState = DBM_MAIN_MENU;
    } else if (RELEASED(BUTTON_R)) {
        for (idx = 1; idx < ARRAY_COUNT(gPlayerData.partners); idx++) {
            s32 val = DebugPartnerLevels[idx];
            if (val >= 0) {
                gPlayerData.partners[idx].enabled = TRUE;
                gPlayerData.partners[idx].level = val;
            } else {
                gPlayerData.partners[idx].enabled = FALSE;
                gPlayerData.partners[idx].level = 0;
            }
        }
        sfx_play_sound(SOUND_MENU_BADGE_EQUIP);
    }

    // draw
    dx_debug_draw_box(SubBoxPosX, SubBoxPosY, 120, 14 * 11 + 8, WINDOW_STYLE_20, 192);

    for (idx = 1; idx < ARRAY_COUNT(gPlayerData.partners); idx++) {
        b32 isSelected = (SelectPartnerMenuPos == idx);
        s32 color = isSelected ? HighlightColor : DefaultColor;
        s32 posY = SubmenuPosY + (idx - 1) * 14;
        s32 level = DebugPartnerLevels[idx];
        s32 alpha = (isSelected || level >= 0) ? 254 : 120;

        if (level < 0) {
            dx_debug_draw_number(level, "%d", color, alpha, SubmenuPosX - 3, posY);
        } else {
            dx_debug_draw_number(level, "%d", color, alpha, SubmenuPosX + 3, posY);
        }

        dx_debug_draw_msg(gPartnerPopupProperties[idx].nameMsg, color, alpha, SubmenuPosX + 15, posY);

        if (level == 1) {
            char msg[] = { MSG_CHAR_CIRCLE, MSG_CHAR_READ_END };
            draw_msg((s32)msg, SubmenuPosX + 82, posY - 1, 255, MSG_PAL_BLUE, 0);
        } else if (level == 2) {
            char msg[] = { MSG_CHAR_CIRCLE, MSG_CHAR_CIRCLE, MSG_CHAR_READ_END };
            draw_msg((s32)msg, SubmenuPosX + 82, posY - 1, 255, MSG_PAL_BLUE, 0);
        }
    }
}

// ----------------------------------------------------------------------------
// edit inventory

DebugMenuEntry DebugInventoryMenu[] = {
    { "Items", NULL, DBM_INV_EDIT_ITEMS },
    { "Badges", NULL, DBM_INV_EDIT_BADGES },
    { "Key Items", NULL, DBM_INV_EDIT_KEYS },
    { "Equipment", NULL, DBM_INV_EDIT_GEAR },
    { "Stats", NULL, DBM_INV_EDIT_STATS },
    { "Coins", NULL, DBM_INV_EDIT_COINS },
    { "Star Points", NULL, DBM_INV_EDIT_STAR_POINTS },
    { "Star Pieces", NULL, DBM_INV_EDIT_STAR_PIECES },
};
s32 InventoryMenuPos = 0;

void dx_debug_update_edit_inventory() {
    s32 idx;

    // handle input
    InventoryMenuPos = dx_debug_menu_nav_1D_vertical(InventoryMenuPos, 0, ARRAY_COUNT(DebugInventoryMenu) - 1, FALSE);
    if (RELEASED(BUTTON_L)) {
        DebugMenuState = DBM_MAIN_MENU;
    } else if (RELEASED(BUTTON_R)) {
        if (DebugInventoryMenu[InventoryMenuPos].onSelect != NULL) {
            DebugInventoryMenu[InventoryMenuPos].onSelect();
        } else {
            DebugMenuState = DebugInventoryMenu[InventoryMenuPos].nextState;
        }
    }

    // draw
    dx_debug_draw_box(SubBoxPosX, SubBoxPosY + RowHeight, 75, ARRAY_COUNT(DebugInventoryMenu) * RowHeight + 8, WINDOW_STYLE_20, 192);

    for (idx = 0; idx < ARRAY_COUNT(DebugInventoryMenu); idx++) {
        s32 color = (InventoryMenuPos == idx) ? HighlightColor : DefaultColor;
        dx_debug_draw_ascii(DebugInventoryMenu[idx].text, color, SubmenuPosX, SubmenuPosY + (idx + 1) * RowHeight);
    }
}

b32 DebugEditingItem = FALSE;

#define _MAX_INV_SIZE(a,b,c) MAX(MAX(ARRAY_COUNT(a), ARRAY_COUNT(b)), ARRAY_COUNT(c))
s8 DebugItemDigits[_MAX_INV_SIZE(gPlayerData.invItems, gPlayerData.keyItems, gPlayerData.badges)][3];

typedef struct DebugItemsMenu {
    s16 pos;
    s16 startPos;
    s8 col;
} DebugItemsMenu;

DebugItemsMenu DebugItems = {
    .pos = 0,
    .startPos = 0,
    .col = 0,
};

DebugItemsMenu DebugKeys = {
    .pos = 0,
    .startPos = 0,
    .col = 0,
};

DebugItemsMenu DebugBadges = {
    .pos = 0,
    .startPos = 0,
    .col = 0,
};

void dx_debug_set_item_id(s32 idx, s16 itemID) {
    s32 j;

    for (j = 2; j >= 0; j--) {
        DebugItemDigits[idx][j] = (itemID & 0xF);
        itemID >>= 4;
    }
}

s16 dx_debug_get_item_id(s32 idx) {
    s32 j;
    s16 val = 0;

    for (j = 0; j < 3; j++) {
        val <<= 4;
        val |= (DebugItemDigits[idx][j] & 0xF);
    }
    return val;
}

void dx_debug_update_edit_items() {
    DebugItemsMenu* menu;
    s16* invItems;
    s32 invSize;
    s32 i, j;

    switch (DebugMenuState) {
        case DBM_INV_EDIT_ITEMS:
            menu = &DebugItems;
            invItems = gPlayerData.invItems;
            invSize = ARRAY_COUNT(gPlayerData.invItems);
            break;
        case DBM_INV_EDIT_KEYS:
            menu = &DebugKeys;
            invItems = gPlayerData.keyItems;
            invSize = ARRAY_COUNT(gPlayerData.keyItems);
            break;
        case DBM_INV_EDIT_BADGES:
            menu = &DebugBadges;
            invItems = gPlayerData.badges;
            invSize = ARRAY_COUNT(gPlayerData.badges);
            break;
    }

    if (DebugStateChanged) {
        for (i = 0; i < invSize; i++) {
            dx_debug_set_item_id(i, invItems[i]);
        }
    }

    if (RELEASED(BUTTON_L)) {
        if (DebugEditingItem) {
            DebugEditingItem = FALSE;
        } else {
            DebugMenuState = DBM_EDIT_INVENTORY;
        }
    } else if (RELEASED(BUTTON_R)) {
        if (!DebugEditingItem) {
            DebugEditingItem = TRUE;
        } else {
            for (i = 0; i < invSize; i++) {
                invItems[i] = dx_debug_get_item_id(i);
            }
            sfx_play_sound(SOUND_MENU_BADGE_EQUIP);
        }
    }

    if (DebugEditingItem) {
        s32 digit;
        menu->col = dx_debug_menu_nav_1D_horizontal(menu->col, 0, 2, FALSE);
        digit = DebugItemDigits[menu->pos][menu->col];
        digit = dx_debug_menu_nav_1D_vertical(digit, 0, 0xF, TRUE);
        DebugItemDigits[menu->pos][menu->col] = digit;
    } else {
        if (NAV_UP) {
            menu->pos--;
            if (menu->pos < 0) {
                menu->pos = invSize - 1;
                menu->startPos = menu->pos - 9;
            } else {
                menu->startPos = MIN(menu->startPos, menu->pos);
            }
        }
        if (NAV_DOWN) {
            menu->pos++;
            if (menu->pos >= invSize) {
                menu->pos = 0;
                menu->startPos = 0;
            } else {
                menu->startPos = MAX(menu->startPos, menu->pos - 9);
            }
        }
    }

    // draw
    dx_debug_draw_box(SubBoxPosX, SubBoxPosY, 160, 10 * RowHeight + 8, WINDOW_STYLE_20, 192);

    for (i = menu->startPos; i <= menu->startPos + 9; i++) {
        s32 posY = SubmenuPosY + (i - menu->startPos) * RowHeight;
        s32 itemID = dx_debug_get_item_id(i);
        b32 isSelectedRow = (menu->pos == i);

        if (DebugEditingItem) {
            dx_debug_draw_editable_number(i, "%02X", -1, FALSE, SubmenuPosX, posY);
            dx_debug_draw_editable_number(itemID, "%03X", menu->col, isSelectedRow, SubmenuPosX + 20, posY);
        } else {
            dx_debug_draw_editable_number(i, "%02X", -1, isSelectedRow, SubmenuPosX, posY);
            dx_debug_draw_editable_number(itemID, "%03X", -1, FALSE, SubmenuPosX + 20, posY);
        }

        s32 itemMsg = MSG_NONE;
        if (itemID > 0 && itemID < NUM_ITEMS) {
            itemMsg = gItemTable[itemID].nameMsg;
        }
        if (itemMsg != MSG_NONE) {
            dx_debug_draw_msg(itemMsg, DefaultColor, 255, SubmenuPosX + 50, posY);
        } else {
            char msgBuf[] = {
                MSG_CHAR_READ_FUNCTION, MSG_READ_FUNC_SIZE, 12, 12,
                MSG_CHAR_LOWER_E, MSG_CHAR_LOWER_M, MSG_CHAR_LOWER_P, MSG_CHAR_LOWER_T, MSG_CHAR_LOWER_Y,
                MSG_CHAR_READ_END,
            };
            draw_msg((s32)msgBuf, SubmenuPosX + 50, posY, 255, DefaultColor, 0);
        }
    }

    // up arrow
    if (menu->startPos > 0) {
        char msgArrow[] = {
            MSG_CHAR_UP, MSG_CHAR_READ_END
        };
        draw_msg((s32)msgArrow, SubmenuPosX + 132, SubmenuPosY + round(3.0f * ArrowAnimOffset), 255, DefaultColor, 0);
    }
    // down arrow
    if (menu->startPos + 10 < invSize) {
        char msgArrow[] = {
            MSG_CHAR_DOWN, MSG_CHAR_READ_END
        };
        draw_msg((s32)msgArrow, SubmenuPosX + 132, SubmenuPosY + 134 - round(3.0f * ArrowAnimOffset), 255, DefaultColor, 0);
    }
}

enum {
    DEBUG_GEAR_BOOTS,
    DEBUG_GEAR_HAMMER,
    DEBUG_GEAR_LUCKY_STAR,
    DEBUG_GEAR_STAR_BEAM,
};

s32 DebugGearValues[] = {
    [DEBUG_GEAR_BOOTS]          0,
    [DEBUG_GEAR_HAMMER]         0,
    [DEBUG_GEAR_LUCKY_STAR]     0,
    [DEBUG_GEAR_STAR_BEAM]      0,
};
s32 DebugGearPos = 0;

void dx_debug_update_edit_gear() {
    s32 idx;
    s32 val, dx;

    if (DebugStateChanged) {
        DebugGearValues[DEBUG_GEAR_BOOTS] = gPlayerData.bootsLevel;
        DebugGearValues[DEBUG_GEAR_HAMMER] = gPlayerData.hammerLevel;
        DebugGearValues[DEBUG_GEAR_LUCKY_STAR] = gPlayerData.hasActionCommands;
        DebugGearValues[DEBUG_GEAR_STAR_BEAM] = gPlayerData.starBeamLevel;
    }

    if (RELEASED(BUTTON_L)) {
        DebugMenuState = DBM_EDIT_INVENTORY;
    } else if (RELEASED(BUTTON_R)) {
        gPlayerData.bootsLevel = DebugGearValues[DEBUG_GEAR_BOOTS];
        gPlayerData.hammerLevel = DebugGearValues[DEBUG_GEAR_HAMMER];
        gPlayerData.hasActionCommands = DebugGearValues[DEBUG_GEAR_LUCKY_STAR];
        gPlayerData.starBeamLevel = DebugGearValues[DEBUG_GEAR_STAR_BEAM];

        //TODO functions do not exist yet
        /*
        if (gPlayerData.hasActionCommands && !has_key_item(ITEM_LUCKY_STAR)) {
            add_key_item(ITEM_LUCKY_STAR);
        }
        if (!gPlayerData.hasActionCommands && has_key_item(ITEM_LUCKY_STAR)) {
            remove_key_item(ITEM_LUCKY_STAR);
        }
        */

        sfx_play_sound(SOUND_MENU_BADGE_EQUIP);
    }

    DebugGearPos = dx_debug_menu_nav_1D_vertical(DebugGearPos, 0, ARRAY_COUNT(DebugGearValues) - 1, FALSE);

    dx = 0;
    if (NAV_RIGHT) {
        dx++;
    }
    if (NAV_LEFT) {
        dx--;
    }
    if (dx != 0) {
        s32 min = 0;
        s32 max = 0;

        switch (DebugGearPos) {
            case DEBUG_GEAR_BOOTS:
                min = -1;
                max = 2;
                break;
            case DEBUG_GEAR_HAMMER:
                min = -1;
                max = 2;
                break;
            case DEBUG_GEAR_LUCKY_STAR:
                min = 0;
                max = 1;
                break;
            case DEBUG_GEAR_STAR_BEAM:
                min = 0;
                max = 2;
                break;
        }

        DebugGearValues[DebugGearPos] = dx_debug_clamp(DebugGearValues[DebugGearPos] + dx, min, max);
    }

    // draw
    dx_debug_draw_box(SubBoxPosX, SubBoxPosY + RowHeight, 95, 5 * RowHeight + 8, WINDOW_STYLE_20, 192);
    dx_debug_draw_ascii("Gear:", DefaultColor, SubmenuPosX, SubmenuPosY + RowHeight);
    dx_debug_draw_ascii("Boots", DefaultColor, SubmenuPosX, SubmenuPosY + 2 * RowHeight);
    dx_debug_draw_ascii("Hammer", DefaultColor, SubmenuPosX, SubmenuPosY + 3 * RowHeight);
    dx_debug_draw_ascii("Lucky Star", DefaultColor, SubmenuPosX, SubmenuPosY + 4 * RowHeight);
    dx_debug_draw_ascii("Star Beam", DefaultColor, SubmenuPosX, SubmenuPosY + 5 * RowHeight);

    for (idx = 0; idx < ARRAY_COUNT(DebugGearValues); idx++) {
        s32 color = (DebugGearPos == idx) ? HighlightColor : DefaultColor;
        dx_debug_draw_number(DebugGearValues[idx], "%2d", color, 255, SubmenuPosX + 63, SubmenuPosY + (idx + 2) * RowHeight);
    }
}

enum {
    DEBUG_STAT_HP,
    DEBUG_STAT_FP,
    DEBUG_STAT_BP,
    DEBUG_STAT_LEVEL,
    DEBUG_STAT_SPIRITS,
};

s32 DebugStatValues[] = {
    [DEBUG_STAT_HP]         0,
    [DEBUG_STAT_FP]         0,
    [DEBUG_STAT_BP]         0,
    [DEBUG_STAT_LEVEL]      0,
    [DEBUG_STAT_SPIRITS]    0,
};
s32 DebugStatPos = 0;

void dx_debug_update_edit_stats() {
    s32 idx;
    s32 val, dx;

    if (DebugStateChanged) {
        DebugStatValues[DEBUG_STAT_HP] = gPlayerData.hardMaxHP;
        DebugStatValues[DEBUG_STAT_FP] = gPlayerData.hardMaxFP;
        DebugStatValues[DEBUG_STAT_BP] = gPlayerData.maxBP;
        DebugStatValues[DEBUG_STAT_LEVEL] = gPlayerData.level;
        DebugStatValues[DEBUG_STAT_SPIRITS] = gPlayerData.maxStarPower;
    }

    if (RELEASED(BUTTON_L)) {
        DebugMenuState = DBM_EDIT_INVENTORY;
    } else if (RELEASED(BUTTON_R)) {
        gPlayerData.curHP = gPlayerData.curMaxHP = gPlayerData.hardMaxHP = DebugStatValues[DEBUG_STAT_HP];
        gPlayerData.curFP = gPlayerData.curMaxFP = gPlayerData.hardMaxFP = DebugStatValues[DEBUG_STAT_FP];
        gPlayerData.maxBP = DebugStatValues[DEBUG_STAT_BP];
        gPlayerData.level = DebugStatValues[DEBUG_STAT_LEVEL];
        gPlayerData.maxStarPower = DebugStatValues[DEBUG_STAT_SPIRITS];
        gPlayerData.starPower = gPlayerData.maxStarPower * SP_PER_BAR;
        sfx_play_sound(SOUND_MENU_BADGE_EQUIP);
    }

    DebugStatPos = dx_debug_menu_nav_1D_vertical(DebugStatPos, 0, ARRAY_COUNT(DebugStatValues) - 1, FALSE);

    dx = 0;
    if (NAV_RIGHT) {
        dx++;
    }
    if (NAV_LEFT) {
        dx--;
    }
    if (dx != 0) {
        switch (DebugStatPos) {
            case DEBUG_STAT_HP:
                val = DebugStatValues[DEBUG_STAT_HP] + 5 * dx;
                DebugStatValues[DEBUG_STAT_HP] = dx_debug_clamp(val, 5, 50);
                break;
            case DEBUG_STAT_FP:
                val = DebugStatValues[DEBUG_STAT_FP] + 5 * dx;
                DebugStatValues[DEBUG_STAT_FP] = dx_debug_clamp(val, 0, 50);
                break;
            case DEBUG_STAT_BP:
                val = DebugStatValues[DEBUG_STAT_BP] + 3 * dx;
                DebugStatValues[DEBUG_STAT_BP] = dx_debug_clamp(val, 3, 30);
                break;
            case DEBUG_STAT_LEVEL:
                val = DebugStatValues[DEBUG_STAT_LEVEL] + dx;
                DebugStatValues[DEBUG_STAT_LEVEL] = dx_debug_clamp(val, 1, 27);
                break;
            case DEBUG_STAT_SPIRITS:
                val = DebugStatValues[DEBUG_STAT_SPIRITS] + dx;
                DebugStatValues[DEBUG_STAT_SPIRITS] = dx_debug_clamp(val, 0, 7);
                break;
        }
    }

    // draw
    dx_debug_draw_box(SubBoxPosX, SubBoxPosY + RowHeight, 88, 6 * RowHeight + 8, WINDOW_STYLE_20, 192);
    dx_debug_draw_ascii("Stats:", DefaultColor, SubmenuPosX, SubmenuPosY + RowHeight);
    dx_debug_draw_ascii("Max HP", DefaultColor, SubmenuPosX, SubmenuPosY + 2 * RowHeight);
    dx_debug_draw_ascii("Max FP", DefaultColor, SubmenuPosX, SubmenuPosY + 3 * RowHeight);
    dx_debug_draw_ascii("Max BP", DefaultColor, SubmenuPosX, SubmenuPosY + 4 * RowHeight);
    dx_debug_draw_ascii("Level", DefaultColor, SubmenuPosX, SubmenuPosY + 5 * RowHeight);
    dx_debug_draw_ascii("Spirits", DefaultColor, SubmenuPosX, SubmenuPosY + 6 * RowHeight);

    for (idx = 0; idx < ARRAY_COUNT(DebugStatValues); idx++) {
        s32 color = (DebugStatPos == idx) ? HighlightColor : DefaultColor;
        dx_debug_draw_number(DebugStatValues[idx], "%2d", color, 255, SubmenuPosX + 55, SubmenuPosY + (idx + 2) * RowHeight);
    }
}

DebugEditableNumber DebugCoins = {
    .isHex = FALSE,
    .digits = { 0, 0, 0 },
    .size = 3,
    .pos = 0,
};

void dx_debug_update_edit_coins() {
    if (DebugStateChanged) {
        dx_debug_set_editable_num(&DebugCoins, gPlayerData.coins);
    }

    // handle input
    if (RELEASED(BUTTON_L)) {
        DebugMenuState = DBM_EDIT_INVENTORY;
    } else if (RELEASED(BUTTON_R)) {
        gPlayerData.coins = dx_debug_get_editable_num(&DebugCoins);
        open_status_bar_quickly();
        sfx_play_sound(SOUND_COIN_PICKUP);
    }
    dx_debug_nav_editable_num(&DebugCoins);

    // draw
    dx_debug_draw_box(SubBoxPosX, SubBoxPosY + RowHeight, 50, 2 * RowHeight + 8, WINDOW_STYLE_20, 192);
    dx_debug_draw_ascii("Coins:", DefaultColor, SubmenuPosX, SubmenuPosY + RowHeight);
    dx_debug_draw_editable_num(&DebugCoins, SubmenuPosX, SubmenuPosY + 2 * RowHeight);
}

DebugEditableNumber DebugStarPoints = {
    .isHex = FALSE,
    .digits = { 0, 0 },
    .size = 2,
    .pos = 0,
};

void dx_debug_update_edit_star_points() {
    if (DebugStateChanged) {
        dx_debug_set_editable_num(&DebugStarPoints, gPlayerData.starPoints);
    }

    // handle input
    if (RELEASED(BUTTON_L)) {
        DebugMenuState = DBM_EDIT_INVENTORY;
    } else if (RELEASED(BUTTON_R)) {
        gPlayerData.starPoints = dx_debug_get_editable_num(&DebugStarPoints);
        open_status_bar_quickly();
        sfx_play_sound(SOUND_STAR_POINT_PICKUP);
    }
    dx_debug_nav_editable_num(&DebugStarPoints);

    // draw
    dx_debug_draw_box(SubBoxPosX, SubBoxPosY + RowHeight, 86, 2 * RowHeight + 8, WINDOW_STYLE_20, 192);
    dx_debug_draw_ascii("Star Points:", DefaultColor, SubmenuPosX, SubmenuPosY + RowHeight);
    dx_debug_draw_editable_num(&DebugStarPoints, SubmenuPosX, SubmenuPosY + 2 * RowHeight);
}

DebugEditableNumber DebugStarPieces = {
    .isHex = FALSE,
    .digits = { 0, 0, 0 },
    .size = 3,
    .pos = 0,
};

void dx_debug_update_edit_star_pieces() {
    if (DebugStateChanged) {
        dx_debug_set_editable_num(&DebugStarPieces, gPlayerData.starPieces);
    }

    // handle input
    if (RELEASED(BUTTON_L)) {
        DebugMenuState = DBM_EDIT_INVENTORY;
    } else if (RELEASED(BUTTON_R)) {
        gPlayerData.starPieces = dx_debug_get_editable_num(&DebugStarPieces);
        open_status_bar_quickly();
        sfx_play_sound(SOUND_STAR_PIECE_BOUNCE);
    }
    dx_debug_nav_editable_num(&DebugStarPieces);

    // clamp maximum
    if (dx_debug_get_editable_num(&DebugStarPieces) > 255) {
        dx_debug_set_editable_num(&DebugStarPieces, 255);
    }

    // draw
    dx_debug_draw_box(SubBoxPosX, SubBoxPosY + RowHeight, 86, 2 * RowHeight + 8, WINDOW_STYLE_20, 192);
    dx_debug_draw_ascii("Star Pieces:", DefaultColor, SubmenuPosX, SubmenuPosY + RowHeight);
    dx_debug_draw_editable_num(&DebugStarPieces, SubmenuPosX, SubmenuPosY + 2 * RowHeight);
}

// ----------------------------------------------------------------------------
// view collision

typedef struct DebugCollisionEntry {
    char* text;
    s32 state;
} DebugCollisionEntry;

enum {
    DBC_SHOW_COLLISION,
    DBC_CULL_BACK,
    DBC_SHOW_DISABLED,
    DBC_HIDE_MODELS,
    DBC_EXTRUDE_FACES,
    DBC_HIGHLIGHT_FLOOR,
    DBC_HIGHLIGHT_WALL,
    DBC_FADE_DIST,
};

DebugCollisionEntry DebugCollisionMenu[] = {
    [DBC_SHOW_COLLISION]  { "Show Collision",  FALSE },
    [DBC_CULL_BACK]       { "Cull Back",       TRUE },
    [DBC_SHOW_DISABLED]   { "Show Disabled",   TRUE },
    [DBC_HIDE_MODELS]     { "Hide Models",     FALSE },
    [DBC_EXTRUDE_FACES]   { "Extrude Faces",   FALSE },
    [DBC_HIGHLIGHT_FLOOR] { "Highlight Floor", FALSE },
    [DBC_HIGHLIGHT_WALL]  { "Highlight Wall",  FALSE },
    [DBC_FADE_DIST]       { "Near Fade Dist",  1 },
};

s32 DebugCollisionPos = 0;

void dx_debug_update_view_collision() {
    s32 idx;

    // handle input
    if (RELEASED(BUTTON_L)) {
        DebugMenuState = DBM_MAIN_MENU;
    }

    if (DebugCollisionPos != DBC_FADE_DIST) {
        if (NAV_LEFT || NAV_RIGHT) {
            DebugCollisionMenu[DebugCollisionPos].state = !DebugCollisionMenu[DebugCollisionPos].state;
        }
    } else {
        s32 fadeDist = DebugCollisionMenu[DebugCollisionPos].state;
        fadeDist = dx_debug_menu_nav_1D_horizontal(fadeDist, 0, 9, FALSE);
        DebugCollisionMenu[DebugCollisionPos].state = fadeDist;
    }
    DebugCollisionPos = dx_debug_menu_nav_1D_vertical(DebugCollisionPos, 0, ARRAY_COUNT(DebugCollisionMenu) - 1, FALSE);

    // draw
    dx_debug_draw_box(SubBoxPosX, SubBoxPosY + RowHeight, 120, 8 * RowHeight + 8, WINDOW_STYLE_20, 192);

    for (idx = 0; idx < ARRAY_COUNT(DebugCollisionMenu); idx++) {
        s32 color = (DebugCollisionPos == idx) ? HighlightColor : DefaultColor;
        if (idx != DBC_FADE_DIST) {
            char* onoff = DebugCollisionMenu[idx].state ? "On" : "Off";
            dx_debug_draw_ascii(onoff, color, SubmenuPosX, SubmenuPosY + (idx + 1) * RowHeight);
        } else {
            s32 fadeDist = DebugCollisionMenu[idx].state;
            dx_debug_draw_number(fadeDist, "%d", color, 255, SubmenuPosX, SubmenuPosY + (idx + 1) * RowHeight);
        }
        dx_debug_draw_ascii(DebugCollisionMenu[idx].text, DefaultColor, SubmenuPosX + 28, SubmenuPosY + (idx + 1) * RowHeight);
    }
}

void dx_debug_add_collision_vtx(Vtx_t* vtxBuffer, Vec3f* vert, Vec3f* normal, s32 r, s32 g, s32 b, s32 a) {
    if (DebugCollisionMenu[DBC_EXTRUDE_FACES].state) {
        vtxBuffer->ob[0] = vert->x + normal->x;
        vtxBuffer->ob[1] = vert->y + normal->y;
        vtxBuffer->ob[2] = vert->z + normal->z;
    } else {
        vtxBuffer->ob[0] = vert->x;
        vtxBuffer->ob[1] = vert->y;
        vtxBuffer->ob[2] = vert->z;
    }
    vtxBuffer->tc[0] = 0;
    vtxBuffer->tc[1] = 0;
    vtxBuffer->cn[0] = r;
    vtxBuffer->cn[1] = g;
    vtxBuffer->cn[2] = b;
    vtxBuffer->cn[3] = a;
}

#define MAX_DEBUG_TRIS 1024

typedef struct DebugTriangle {
    ColliderTriangle* tri;
    s16 depth;
    s16 colliderID;
} DebugTriangle;

DebugTriangle DebugTris[MAX_DEBUG_TRIS];
s32 DebugTriPos;

Vtx_t DebugVtxBuf[3 * MAX_DEBUG_TRIS];
s32 DebugVtxPos;

void dx_debug_draw_collision() {
    DebugTriangle temp;
    s32 rdpBufPos;
    b32 culling;
    s32 fadeDist;
    s32 i, j;
    s32 dist;

    Camera* camera = &gCameras[gCurrentCameraID];

    if (!DebugCollisionMenu[DBC_SHOW_COLLISION].state) {
        return;
    }

    // find all collider trianges
    DebugTriPos = 0;
    for (i = 0; i < gCollisionData.numColliders; i++) {
        Collider* collider = &gCollisionData.colliderList[i];

        if (collider->flags & COLLIDER_FLAG_IGNORE_PLAYER && !DebugCollisionMenu[DBC_SHOW_DISABLED].state) {
            continue;
        }

        for (j = 0; j < collider->numTriangles; j++) {
            if (DebugTriPos < MAX_DEBUG_TRIS) {
                ColliderTriangle* tri = &collider->triangleTable[j];
                f32 outX, outY, outZ, outW;
                f32 cX = (tri->v1->x + tri->v2->x + tri->v3->x) / 3;
                f32 cY = (tri->v1->y + tri->v2->y + tri->v3->y) / 3;
                f32 cZ = (tri->v1->z + tri->v2->z + tri->v3->z) / 3;

                transform_point(camera->mtxPerspective, cX, cY, cZ, 1.0f, &outX, &outY, &outZ, &outW);

                if (outZ < -100) {
                    // dont draw triangles sufficiently far behind the camera
                    DebugTriPos--;
                } else {
                    DebugTris[DebugTriPos].tri = tri;
                    DebugTris[DebugTriPos].depth = outZ;
                    DebugTris[DebugTriPos].colliderID = i;
                }
            }
            DebugTriPos++;
        }
    }

    ASSERT(DebugTriPos < MAX_DEBUG_TRIS)

    // sort triangles by depth
#define LESS(i, j) DebugTris[i].depth > DebugTris[j].depth
#define SWAP(i, j) temp = DebugTris[i], DebugTris[i] = DebugTris[j], DebugTris[j] = temp
    QSORT(DebugTriPos, LESS, SWAP);

    gDPPipeSync(gMainGfxPos++);
    gDPSetCycleType(gMainGfxPos++, G_CYC_1CYCLE);
    gDPSetRenderMode(gMainGfxPos++, G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2);
    gDPSetCombineMode(gMainGfxPos++, G_CC_SHADE, G_CC_SHADE);
    gSPTexture(gMainGfxPos++, 0x0080, 0x0080, 0, G_TX_RENDERTILE, G_OFF);
    gSPClearGeometryMode(gMainGfxPos++, G_LIGHTING | G_CULL_BACK);

    if (DebugCollisionMenu[DBC_CULL_BACK].state) {
        gSPSetGeometryMode(gMainGfxPos++, G_CULL_BACK | G_SHADING_SMOOTH);
        culling = TRUE;
    } else {
        gSPSetGeometryMode(gMainGfxPos++, G_SHADING_SMOOTH);
        culling = FALSE;
    }

    DebugVtxPos = 0;
    rdpBufPos = 0;

    // build the display list and fill DebugVtxBuf at the same time
    for (i = 0; i < DebugTriPos; i++) {
        DebugTriangle* debugTri = &DebugTris[i];
        ColliderTriangle* tri = debugTri->tri;
        s32 r, g, b, a;

        b32 highlight = FALSE;
        if (DebugCollisionMenu[DBC_HIGHLIGHT_FLOOR].state && debugTri->colliderID == gCollisionStatus.curFloor) {
            highlight = TRUE;
        }
        if (DebugCollisionMenu[DBC_HIGHLIGHT_WALL].state && debugTri->colliderID == gCollisionStatus.curWall) {
            highlight = TRUE;
        }

        if (rdpBufPos == 0) {
            // always load vertices 30 at a time
            gSPVertex(gMainGfxPos++, &DebugVtxBuf[DebugVtxPos], 30, 0);
        }

        // manage culling state for two-sided triangles
        if (DebugCollisionMenu[DBC_CULL_BACK].state) {
            if (!tri->oneSided && culling) {
                gDPPipeSync(gMainGfxPos++);
                gSPClearGeometryMode(gMainGfxPos++, G_CULL_BACK);
                culling = FALSE;
            } else if (tri->oneSided && !culling) {
                gDPPipeSync(gMainGfxPos++);
                gSPSetGeometryMode(gMainGfxPos++, G_CULL_BACK);
                culling = TRUE;
            }
        }

        // would be more efficient to pack these into gSP2Triangles ad hoc
        // but it becomes difficult to manage once RDP state changes enter the mix due to two-sided triangles
        gSP1Triangle(gMainGfxPos++, rdpBufPos, rdpBufPos + 1, rdpBufPos + 2, 0);

        // update rdp buffer pos for next triangle draw
        rdpBufPos += 3;
        if (rdpBufPos == 30) {
            rdpBufPos = 0;
        }

        if (highlight) {
            r = g = b = 196;
        } else {
            r = round(fabs(tri->normal.x) * 245.0);
            g = round(fabs(tri->normal.y) * 245.0);
            b = round(fabs(tri->normal.z) * 245.0);
        }
        a = 180;

        // fade triangles too close to the camera
        fadeDist = DebugCollisionMenu[DBC_FADE_DIST].state;
        if(fadeDist > 0) {
            dist = debugTri->depth - (fadeDist - 1) * 25;
            if (dist < 20) {
                // from a=20 at d=40 to a=0 at d=-100
                a = dx_debug_clamp((dist + 100) / 6, 0, 20);
            } else {
                a = dx_debug_clamp(dist, 20, 180);
            }
        }

        // build vertices for this triangle
        dx_debug_add_collision_vtx(&DebugVtxBuf[DebugVtxPos++], tri->v1, &tri->normal, r, g, b, a);
        dx_debug_add_collision_vtx(&DebugVtxBuf[DebugVtxPos++], tri->v2, &tri->normal, r, g, b, a);
        dx_debug_add_collision_vtx(&DebugVtxBuf[DebugVtxPos++], tri->v3, &tri->normal, r, g, b, a);
    }

    // done
    gDPPipeSync(gMainGfxPos++);
}

b32 dx_debug_should_hide_models() {
    return DebugCollisionMenu[DBC_HIDE_MODELS].state;
}

// ----------------------------------------------------------------------------
// cheat menu

typedef struct DebugCheatEntry {
    char* text;
    b32 enabled;
} DebugCheatEntry;

DebugCheatEntry DebugCheatMenu[] = {
    [DEBUG_CHEAT_GOD_MODE]      { "God Mode",   FALSE },
    [DEBUG_CHEAT_SPEED_MODE]    { "Speed Mode", FALSE },
    [DEBUG_CHEAT_FLY]           { "Fly With L", FALSE },
    [DEBUG_CHEAT_HIGH_JUMP]     { "High Jump", FALSE },
    [DEBUG_CHEAT_IGNORE_WALLS]  { "Ignore Walls", FALSE },
};

s32 DebugCheatPos = 0;

void dx_debug_update_cheat_menu() {
    s32 idx;

    // handle input
    if (RELEASED(BUTTON_L)) {
        DebugMenuState = DBM_MAIN_MENU;
    }
     if (NAV_LEFT || NAV_RIGHT) {
        DebugCheatMenu[DebugCheatPos].enabled = !DebugCheatMenu[DebugCheatPos].enabled;

        // actions to execute on state change
        switch (DebugCheatPos) {
            case DEBUG_CHEAT_GOD_MODE:
            case DEBUG_CHEAT_FLY:
            case DEBUG_CHEAT_HIGH_JUMP:
            case DEBUG_CHEAT_IGNORE_WALLS:
                break;
            case DEBUG_CHEAT_SPEED_MODE:
                if (!DebugCheatMenu[DebugCheatPos].enabled) {
                    gPlayerStatus.walkSpeed = 2.0f;
                    gPlayerStatus.runSpeed = 4.0f;
                    gGameStatusPtr->debugEnemyContact = DEBUG_CONTACT_NONE;
                } else {
                    gPlayerStatus.walkSpeed = 6.0f;
                    gPlayerStatus.runSpeed = 12.0f;
                    gGameStatusPtr->debugEnemyContact = DEBUG_CONTACT_CANT_TOUCH;
                }
                break;
        }

    }
    DebugCheatPos = dx_debug_menu_nav_1D_vertical(DebugCheatPos, 0, ARRAY_COUNT(DebugCheatMenu) - 1, FALSE);

    // draw
    dx_debug_draw_box(SubBoxPosX, SubBoxPosY + RowHeight, 120, ARRAY_COUNT(DebugCheatMenu) * RowHeight + 8, WINDOW_STYLE_20, 192);

    for (idx = 0; idx < ARRAY_COUNT(DebugCheatMenu); idx++) {
        s32 color = (DebugCheatPos == idx) ? HighlightColor : DefaultColor;
        char* onoff = DebugCheatMenu[idx].enabled ? "On" : "Off";

        dx_debug_draw_ascii(onoff, color, SubmenuPosX, SubmenuPosY + (idx + 1) * RowHeight);
        dx_debug_draw_ascii(DebugCheatMenu[idx].text, DefaultColor, SubmenuPosX + 28, SubmenuPosY + (idx + 1) * RowHeight);
    }
}

b32 dx_debug_is_cheat_enabled(DebugCheat cheat) {
    return DebugCheatMenu[cheat].enabled;
}

// ----------------------------------------------------------------------------
// banner info

void dx_debug_update_banner() {
    char fmtBuf[128];
    s32 effect;

    if (gGameStatus.isBattle == 0) {
        sprintf(fmtBuf, "Map: %7s (%X)", LastMapName, LastMapEntry);
        dx_debug_draw_ascii(fmtBuf, DefaultColor, 220, BottomRowY);

        dx_debug_draw_ascii("Pos:", DefaultColor, 20, BottomRowY);

        effect = dx_debug_is_cheat_enabled(DEBUG_CHEAT_SPEED_MODE) ? DRAW_MSG_STYLE_RAINBOW : 0;

        sprintf(fmtBuf, "%5d", round(gPlayerStatus.pos.x));
        dx_debug_draw_ascii_with_effect(fmtBuf, DefaultColor, 48, BottomRowY, effect);

        sprintf(fmtBuf, "%5d", round(gPlayerStatus.pos.y));
        dx_debug_draw_ascii_with_effect(fmtBuf, DefaultColor, 80, BottomRowY, effect);

        sprintf(fmtBuf, "%5d", round(gPlayerStatus.pos.z));
        dx_debug_draw_ascii_with_effect(fmtBuf, DefaultColor, 112, BottomRowY, effect);

        if (dx_debug_is_cheat_enabled(DEBUG_CHEAT_GOD_MODE)) {
            dx_debug_draw_ascii("(GOD MODE)", MSG_PAL_YELLOW, 151, BottomRowY);
        }
    } else {
        s32 areaID = (LastBattleID >> 24) & 0xFF;
        s32 battleID = (LastBattleID >> 16) & 0xFF;
        s32 stageID = LastBattleID & 0xFFFF;

        sprintf(fmtBuf, "Battle:  %02X-%02X (%X)", areaID, battleID, stageID);
        dx_debug_draw_ascii(fmtBuf, DefaultColor, 200, BottomRowY);

        sprintf(fmtBuf, "Stage:  %-15s", LastStageName);
        dx_debug_draw_ascii(fmtBuf, DefaultColor, 20, BottomRowY);

        if (dx_debug_is_cheat_enabled(DEBUG_CHEAT_GOD_MODE)) {
            dx_debug_draw_ascii("(GOD MODE)", MSG_PAL_YELLOW, 128, BottomRowY);
        }
    }
}

// ----------------------------------------------------------------------------
// console printing

#define DEBUG_CONSOLE_DEFAULT_TIMELEFT 60
#define DEBUG_CONSOLE_MSG_BUF_SIZE 85

typedef struct DebugConsoleLine {
    u32 hash;
    s32 timeLeft;
    u8 buf[DEBUG_CONSOLE_MSG_BUF_SIZE];
} DebugConsoleLine;

DebugConsoleLine DebugConsoleLine0 = { 0 };
DebugConsoleLine DebugConsoleLine1 = { 0 };
DebugConsoleLine DebugConsoleLine2 = { 0 };
DebugConsoleLine DebugConsoleLine3 = { 0 };
DebugConsoleLine DebugConsoleLine4 = { 0 };
DebugConsoleLine DebugConsoleLine5 = { 0 };
DebugConsoleLine DebugConsoleLine6 = { 0 };
DebugConsoleLine DebugConsoleLine7 = { 0 };

DebugConsoleLine *DebugConsole[8] = {
    &DebugConsoleLine0,
    &DebugConsoleLine1,
    &DebugConsoleLine2,
    &DebugConsoleLine3,
    &DebugConsoleLine4,
    &DebugConsoleLine5,
    &DebugConsoleLine6,
    &DebugConsoleLine7,
};

u32 dx_debug_hash_location(char* filename, s32 line) {
    u32 hash = 5381;
    s32 c;

    while (c = *filename++) {
        hash = ((hash << 5) + hash) + c;
    }

    hash = ((hash << 5) + hash) + line;

    return hash;
}

static char *proutSprintf(char *dst, const char *src, size_t count) {
    return (char *)memcpy((u8 *)dst, (u8 *)src, count) + count;
}

void dx_hashed_debug_printf(char* filename, s32 line, char* fmt, ...) {
    char fmtBuf[128];
    va_list args;
    va_start(args, fmt);
    s32 len = _Printf(&proutSprintf, fmtBuf, fmt, args);
    if (len >= 0) {
        fmtBuf[len] = 0;
    }
    ASSERT(len < 85);

    u32 hash = dx_debug_hash_location(filename, line);
    s32 matchedLine = -1;
    s32 idx;

    // find a line with the matching hash
    for (idx = 0; idx < ARRAY_COUNT(DebugConsole); idx++) {
        if (DebugConsole[idx]->hash == hash) {
            matchedLine = idx;
            break;
        }
    }

    // find the oldest line
    if (matchedLine == -1) {
        s32 minTimeLeft = DEBUG_CONSOLE_DEFAULT_TIMELEFT;

        for (idx = 0; idx < ARRAY_COUNT(DebugConsole); idx++) {
            if (DebugConsole[idx]->timeLeft == 0) {
                matchedLine = idx;
                break;
            }
            if (DebugConsole[idx]->timeLeft < minTimeLeft) {
                minTimeLeft = DebugConsole[idx]->timeLeft;
                matchedLine = idx;
            }
        }
    }

    // update the ConsoleLine entry
    if (matchedLine != -1) {
        DebugConsole[matchedLine]->buf[0] = MSG_CHAR_READ_FUNCTION;
        DebugConsole[matchedLine]->buf[1] = MSG_READ_FUNC_SIZE;
        DebugConsole[matchedLine]->buf[2] = 12;
        DebugConsole[matchedLine]->buf[3] = 12;

        dx_string_to_msg(&DebugConsole[matchedLine]->buf[4], fmtBuf);

        DebugConsole[matchedLine]->hash = hash;
        DebugConsole[matchedLine]->timeLeft = DEBUG_CONSOLE_DEFAULT_TIMELEFT;
    }
}

API_CALLABLE(_dxDebugIntPrintf) {
    Bytecode* args = script->ptrReadPos;
    s32 i[8];
    s32 nargs = 0;
    s32 idx;

    char* filename = *args++;
    s32 line = *args++;
    char* fmt = *args++;

    for (idx = 0; idx < 8; idx++) {
        s32 var = *args++;
        if (var == 0) {
            break;
        }
        i[idx] = evt_get_variable(script, var);
        nargs++;
    }

    switch (nargs) {
        case 0: dx_hashed_debug_printf(filename, line, fmt); break;
        case 1: dx_hashed_debug_printf(filename, line, fmt, i[0]); break;
        case 2: dx_hashed_debug_printf(filename, line, fmt, i[0], i[1]); break;
        case 3: dx_hashed_debug_printf(filename, line, fmt, i[0], i[1], i[2]); break;
        case 4: dx_hashed_debug_printf(filename, line, fmt, i[0], i[1], i[2], i[3]); break;
        case 5: dx_hashed_debug_printf(filename, line, fmt, i[0], i[1], i[2], i[3], i[4]); break;
        case 6: dx_hashed_debug_printf(filename, line, fmt, i[0], i[1], i[2], i[3], i[4], i[5]); break;
        case 7: dx_hashed_debug_printf(filename, line, fmt, i[0], i[1], i[2], i[3], i[4], i[5], i[6]); break;
    }

    return ApiStatus_DONE2;
}

API_CALLABLE(_dxDebugFloatPrintf) {
    Bytecode* args = script->ptrReadPos;
    f32 f[8];
    s32 nargs = 0;
    s32 idx;

    char* filename = *args++;
    s32 line = *args++;
    char* fmt = *args++;

    for (idx = 0; idx < 8; idx++) {
        s32 var = *args++;
        if (var == 0) {
            break;
        }
        f[idx] = evt_get_float_variable(script, var);
        nargs++;
    }

    switch (nargs) {
        case 0: dx_hashed_debug_printf(filename, line, fmt); break;
        case 1: dx_hashed_debug_printf(filename, line, fmt, f[0]); break;
        case 2: dx_hashed_debug_printf(filename, line, fmt, f[0], f[1]); break;
        case 3: dx_hashed_debug_printf(filename, line, fmt, f[0], f[1], f[2]); break;
        case 4: dx_hashed_debug_printf(filename, line, fmt, f[0], f[1], f[2], f[3]); break;
        case 5: dx_hashed_debug_printf(filename, line, fmt, f[0], f[1], f[2], f[3], f[4]); break;
        case 6: dx_hashed_debug_printf(filename, line, fmt, f[0], f[1], f[2], f[3], f[4], f[5]); break;
        case 7: dx_hashed_debug_printf(filename, line, fmt, f[0], f[1], f[2], f[3], f[4], f[5], f[6]); break;
    }

    return ApiStatus_DONE2;
}

void dx_debug_console_main() {
    DebugConsoleLine* temp;
    s32 idx;

#define LESS(i, j) DebugConsole[i]->timeLeft > DebugConsole[j]->timeLeft
#define SWAP(i, j) temp = DebugConsole[i], DebugConsole[i] = DebugConsole[j], DebugConsole[j] = temp
    QSORT(ARRAY_COUNT(DebugConsole), LESS, SWAP);

    for (idx = 0; idx < ARRAY_COUNT(DebugConsole); idx++) {
        s32 timeLeft = DebugConsole[idx]->timeLeft;

        if (timeLeft > 0) {
            s32 alpha = 254;
            if (timeLeft < 20) {
                alpha = round(254 * (timeLeft / 20.0f));
            }

            draw_msg(DebugConsole[idx]->buf, 32, 200 - 15 * idx, alpha, DefaultColor, 0);
            DebugConsole[idx]->timeLeft--;
        }
    }
}

#endif
