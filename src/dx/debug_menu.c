#include "dx/debug_menu.h"
#if DX_DEBUG_MENU

#include "common.h"
#include "gcc/string.h"

void dx_debug_menu_cb_gotomap(void* arg);
void dx_debug_menu_cb_fullrestore(void* arg);
void dx_debug_menu_cb_playerequipment(void* arg);
void dx_debug_menu_cb_partners (void* arg);

struct dx_debug_menu_item {
    char* name;
    void (*callback)(void* arg);
    void* callbackArg;
} dx_rootDebugMenuItems[] = {
    { "Go to map", dx_debug_menu_cb_gotomap },
    { "Full Restore", dx_debug_menu_cb_fullrestore },
    { "Equipment", dx_debug_menu_cb_playerequipment },
    { "Partners", dx_debug_menu_cb_partners },
    { NULL, NULL },
    {},
};

struct dx_debug_menu {
    char* title;
    s32 selectedIndex;
    s32 scrollY;
    s32 targetScrollY;
    struct dx_debug_menu_item* items; // zero-terminated

    struct dx_debug_menu* previous; // linked list
} dx_debugMenu = {
    .title = "Debug menu",
    .selectedIndex = 0,
    .scrollY = 0,
    .targetScrollY = 0,
    .items = dx_rootDebugMenuItems,
    .previous = NULL,
};

int dx_debug_menu_isVisible = FALSE;

u8 dx_ascii_char_to_msg(u8 in) {
    switch (in) {
        case '\0': return MSG_CHAR_READ_END;
        case ' ': return MSG_CHAR_READ_SPACE;
        case '\n': return MSG_CHAR_READ_ENDL;
        default:
            if (in < 0x20) {
                return MSG_CHAR_NOTE;
            }
            return in - 0x20;
    }
}

u8* dx_string_to_msg(u8* msg, const u8* str) {
    while (*str) {
        *msg++ = dx_ascii_char_to_msg(*str++);
    }

    *msg = MSG_CHAR_READ_END;
    return msg;
}

void dx_debug_menu_draw_contents(void* arg0, s32 baseX, s32 baseY, s32 width, s32 height, s32 opacity, s32 darkening) {
    char msgbuf[0x100];
    s32 x = baseX + 6;
    s32 y = baseY + 6;
    struct dx_debug_menu_item* item = dx_debugMenu.items;

    gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, baseX, baseY, baseX+width, baseY+height);

    while (item && item->name != NULL) {
        s32 isSelected = item == &dx_debugMenu.items[dx_debugMenu.selectedIndex];

        dx_string_to_msg(msgbuf, item->name);
        draw_msg((s32)msgbuf, x, y - dx_debugMenu.scrollY, 255, isSelected, 0);
        y += 16;

        if (isSelected) {
            // Scroll to us if we're not visible
            if (y - dx_debugMenu.scrollY > baseY + height - 16) {
                dx_debugMenu.targetScrollY = y - height + 16;
            }
            if (y - dx_debugMenu.scrollY < baseY + 16) {
                dx_debugMenu.targetScrollY = y - 16;
            }

            // Handle pick
            if (gGameStatus.pressedButtons[0] & BUTTON_D_RIGHT) {
                if (item->callback) item->callback(item->callbackArg);
            }
        }

        item++;
    }
}

void dx_render_debug_menu(void) {
    s32 x = 4;
    s32 y = 24;
    s32 width = 130;
    s32 height = 150;
    char msgbuf[0x100];

    // Don't render if the menu isn't visible
    if (!dx_debug_menu_isVisible) {
        if (gGameStatus.pressedButtons[0] & BUTTON_D_RIGHT) {
            dx_debug_menu_isVisible = TRUE;
        }

        return;
    }

    // Handle selection movement
    if (gGameStatus.heldButtons[0] & BUTTON_D_UP) {
        dx_debugMenu.selectedIndex--;
        if (dx_debugMenu.selectedIndex < 0) {
            dx_debugMenu.selectedIndex = 0;
        }
    }
    if (gGameStatus.heldButtons[0] & BUTTON_D_DOWN) {
        dx_debugMenu.selectedIndex++;
        if (dx_debugMenu.items && dx_debugMenu.items[dx_debugMenu.selectedIndex].name == NULL) {
            dx_debugMenu.selectedIndex--;
        }
    }
    if (gGameStatus.pressedButtons[0] & BUTTON_D_LEFT) {
        if (dx_debugMenu.previous) {
            dx_debug_menu_pop();
        } else {
            dx_debug_menu_isVisible = FALSE;
            return;
        }
    }

    // Animate scroll position
    dx_debugMenu.scrollY -= (dx_debugMenu.scrollY - dx_debugMenu.targetScrollY) / 6;

    // Items box
    draw_box(
        DRAW_FLAG_ANIMATED_BACKGROUND, (WindowStyle)WINDOW_STYLE_3,
        x, y, 0,
        width, height,
        255, 0,
        1.0f, 1.0f,
        0.0f, 0.0f, 0.0f,
        (void*)dx_debug_menu_draw_contents, NULL,
        NULL,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        NULL
    );

    // Title box
    draw_box(
        0, (WindowStyle)WINDOW_STYLE_8,
        x + 16, y - 12, 0,
        width - 32, 18,
        255, 0,
        1.0f, 1.0f,
        0.0f, 0.0f, 0.0f,
        NULL, NULL,
        NULL,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        NULL
    );
    dx_string_to_msg(msgbuf, dx_debugMenu.title);
    draw_msg((s32)msgbuf, x + 20, y - 12, 255, 0, 0);
}

void dx_debug_menu_push(void) {
    struct dx_debug_menu* previous = general_heap_malloc(sizeof(struct dx_debug_menu));
    memcpy(previous, &dx_debugMenu, sizeof(struct dx_debug_menu));

    dx_debugMenu.title = "Untitled menu";
    dx_debugMenu.selectedIndex = 0;
    dx_debugMenu.scrollY = 0;
    dx_debugMenu.targetScrollY = 0;
    dx_debugMenu.items = NULL;
    dx_debugMenu.previous = previous;
}

void dx_debug_menu_close(void) {
    while (dx_debugMenu.previous != NULL) {
        dx_debug_menu_pop();
    }
    dx_debug_menu_isVisible = FALSE;
}

void dx_debug_menu_pop(void) {
    struct dx_debug_menu* previous = dx_debugMenu.previous;

    if (previous == NULL) {
        return;
    }

    // Free the items
    if (dx_debugMenu.items != NULL) {
        general_heap_free(dx_debugMenu.items);
    }

    // Restore the previous menu
    memcpy(&dx_debugMenu, previous, sizeof(struct dx_debug_menu));
    general_heap_free(previous);
}

// Callack for when you pick a map on the "Go to map" menu
// Actually loads the map
void dx_debug_menu_cb_gotomap_execute(void* arg) {
    MapConfig* map = arg;

    // Get area/map id pair
    s16 areaID;
    s16 mapID;
    get_map_IDs_by_name(map->id, &areaID, &mapID);

    // Go there
    gGameStatusPtr->areaID = areaID;
    gGameStatusPtr->mapID = mapID;
    gGameStatusPtr->entryID = 0;
    set_map_transition_effect(0);
    set_game_mode(GAME_MODE_UNUSED);

    // Stop ambient sounds
    play_ambient_sounds(AMBIENT_SILENCE, 1);

    dx_debug_menu_close();
}

// Callback for when you pick an area on the "Go to map" menu
// Lists the maps in that area
void dx_debug_menu_cb_gotomap_area(void* arg) {
    AreaConfig* area = arg;
    struct dx_debug_menu_item* items;
    s32 i;

    items = general_heap_malloc((area->mapCount + 1) * sizeof(struct dx_debug_menu_item));
    if (items == NULL) {
        return;
    }

    for (i = 0; i < area->mapCount; i++) {
        if (area->maps[i].id == NULL) {
            continue;
        }
        items[i].name = area->maps[i].id;
        items[i].callback = dx_debug_menu_cb_gotomap_execute;
        items[i].callbackArg = &area->maps[i];
    }

    items[i].name = NULL;
    items[i].callback = NULL;

    dx_debug_menu_push();
    dx_debugMenu.title = "Go to map";
    dx_debugMenu.items = items;
}

// Callback for the "Go to map" option
// Lists the areas
void dx_debug_menu_cb_gotomap(void* arg) {
    s32 numAreas;
    struct dx_debug_menu_item* items;
    s32 i;

    // Count the number of areas (it's a zero-terminated list)
    numAreas = 0;
    while (gAreas[numAreas].name != NULL) {
        numAreas++;
    }

    // Allocate the items list with space for the terminator
    items = general_heap_malloc((numAreas + 1) * sizeof(struct dx_debug_menu_item));
    if (items == NULL) {
        return;
    }
    for (i = 0; i < numAreas; i++) {
        if (gAreas[i].name == NULL) {
            continue;
        }
        items[i].name = gAreas[i].id;
        items[i].callback = dx_debug_menu_cb_gotomap_area;
        items[i].callbackArg = &gAreas[i];
    }

    // Terminator
    items[numAreas].name = NULL;
    items[numAreas].callback = NULL;

    // Push new menu
    dx_debug_menu_push();
    dx_debugMenu.title = "Go to map";
    dx_debugMenu.items = items;
}

void dx_debug_menu_cb_fullrestore(void* arg) {
    recover_hp(-1);
    recover_fp(-1);
}

void dx_debug_menu_cb_increasejump(void* args);
void dx_debug_menu_cb_decreasejump(void* args);

void dx_debug_menu_cb_increasehammer(void* args);
void dx_debug_menu_cb_decreasehammer(void* args);

void dx_debug_menu_cb_playerequipment(void* arg) {
    struct dx_debug_menu_item* items;

    dx_debug_menu_push();
    dx_debugMenu.title = "Equipment";
    items = general_heap_malloc(5 * sizeof(struct dx_debug_menu_item));
    dx_debugMenu.items = items;
    items[0].name = "Increase Jump";
    items[0].callback = dx_debug_menu_cb_increasejump;
    items[1].name = "Decrease Jump";
    items[1].callback = dx_debug_menu_cb_decreasejump;
    items[2].name = "Increase Hammer";
    items[2].callback = dx_debug_menu_cb_increasehammer;
    items[3].name = "Decrease Hammer";
    items[3].callback = dx_debug_menu_cb_decreasehammer;
}


void dx_debug_menu_cb_increasejump(void* args){
    if (gPlayerData.bootsLevel < 2) {
        gPlayerData.bootsLevel++;
    }
}

void dx_debug_menu_cb_decreasejump(void* args){
    if (gPlayerData.bootsLevel > 0) {
        gPlayerData.bootsLevel--;
    }
}

void dx_debug_menu_cb_increasehammer(void* args){
    if (gPlayerData.hammerLevel < 2) {
        gPlayerData.hammerLevel++;
    }
}

void dx_debug_menu_cb_decreasehammer(void* args){
    if (gPlayerData.hammerLevel > -1) {
        gPlayerData.hammerLevel--;
    }
}

u8 cb_currentpartner = 0;

void dx_debug_menu_cb_partnerincreaselevel(void* args){
    if(gPlayerData.partners[*(u8*)args].level < 2 ) {
        gPlayerData.partners[*(u8*)args].level++;
    }
}
void dx_debug_menu_cb_partnerdecreaselevel(void* args){
    if(gPlayerData.partners[*(u8*)args].level > 0 ) {
        gPlayerData.partners[*(u8*)args].level--;
    }
}

void dx_debug_menu_cb_partnerenable(void* args){
    if(gPlayerData.partners[*(u8*)args].enabled != 1 ) {
        gPlayerData.partners[*(u8*)args].enabled = 1;
    }
}

void dx_debug_menu_cb_partnerdisable(void* args){
    if(gPlayerData.partners[*(u8*)args].enabled != 0 ) {
        gPlayerData.partners[*(u8*)args].enabled = 0;
    }
}

void dx_debug_menu_cb_partnermenu(void* args){
    struct dx_debug_menu_item* items;
        dx_debug_menu_push();
         cb_currentpartner = *(u8*)args; //current partner in the menu
    dx_debugMenu.title = "partner options";
    items = general_heap_malloc(5 * sizeof(struct dx_debug_menu_item));
    dx_debugMenu.items = items;
    items[0].name = "Increase Level";
    items[0].callback = dx_debug_menu_cb_partnerincreaselevel;
    items[0].callbackArg = &cb_currentpartner;
    items[1].name = "Decrease Level";
    items[1].callback = dx_debug_menu_cb_partnerdecreaselevel;
    items[1].callbackArg = &cb_currentpartner;
    items[2].name = "Enable Partner";
    items[2].callback = dx_debug_menu_cb_partnerenable;
    items[2].callbackArg = &cb_currentpartner;
    items[3].name = "Disable Partner";
    items[3].callback = dx_debug_menu_cb_partnerdisable;
    items[3].callbackArg = &cb_currentpartner;
    items[4].name = NULL;
}
u8 selectedpartner[] = {PARTNER_GOOMBARIO, PARTNER_KOOPER, PARTNER_BOMBETTE, PARTNER_PARAKARRY, PARTNER_GOOMPA, PARTNER_WATT, PARTNER_SUSHIE, PARTNER_LAKILESTER, PARTNER_BOW, PARTNER_GOOMBARIA, PARTNER_TWINK}; // partner enums
void dx_debug_menu_cb_partners(void* arg){
        struct dx_debug_menu_item* items;

    dx_debug_menu_push();
    dx_debugMenu.title = "Give Partners";
    items = general_heap_malloc(12 * sizeof(struct dx_debug_menu_item));
    dx_debugMenu.items = items;
    items[0].name = "Goombario";
    items[0].callback = dx_debug_menu_cb_partnermenu;
    items[0].callbackArg = &selectedpartner[0];
    items[1].name = "Kooper";
    items[1].callback = dx_debug_menu_cb_partnermenu;
    items[1].callbackArg = &selectedpartner[1];
    items[2].name = "Bombette";
    items[2].callback = dx_debug_menu_cb_partnermenu;
    items[2].callbackArg = &selectedpartner[2];
    items[3].name = "Parakarry";
    items[3].callback = dx_debug_menu_cb_partnermenu;
    items[3].callbackArg = &selectedpartner[3];
    items[4].name = "Goompa";
    items[4].callback = dx_debug_menu_cb_partnermenu;
    items[4].callbackArg = &selectedpartner[4];
    items[5].name = "Watt";
    items[5].callback = dx_debug_menu_cb_partnermenu;
    items[5].callbackArg = &selectedpartner[5];
    items[6].name = "Sushie";
    items[6].callback = dx_debug_menu_cb_partnermenu;
    items[6].callbackArg = &selectedpartner[6];
    items[7].name = "Lakilester";
    items[7].callback = dx_debug_menu_cb_partnermenu;
    items[7].callbackArg = &selectedpartner[7];
    items[8].name = "Bow";
    items[8].callback = dx_debug_menu_cb_partnermenu;
    items[8].callbackArg = &selectedpartner[8];
    items[9].name = "Goombaria";
    items[9].callback = dx_debug_menu_cb_partnermenu;
    items[9].callbackArg = &selectedpartner[9];
    items[10].name = "Twink";
    items[10].callback = dx_debug_menu_cb_partnermenu;
    items[10].callbackArg = &selectedpartner[10];
    items[11].name = NULL;

}
#endif
