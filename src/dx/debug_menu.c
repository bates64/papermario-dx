#include "dx/debug_menu.h"
#if DX_DEBUG_MENU

#include "common.h"

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
    char strbuf[0x100];
    sprintf(strbuf, "Hello, world!");
    dx_string_to_msg(msgbuf, strbuf);
    draw_msg((s32)msgbuf, baseX + 6, baseY + 6, 255, 0, 0);
}

void dx_render_debug_menu(void) {
    // Toggle menu visibility with the L button
    if (gGameStatus.pressedButtons[0] & BUTTON_L) {
        dx_debug_menu_isVisible = !dx_debug_menu_isVisible;
    }

    // Don't render if the menu isn't visible
    if (!dx_debug_menu_isVisible) {
        return;
    }

    draw_box(
        DRAW_FLAG_ANIMATED_BACKGROUND, (WindowStyle)WINDOW_STYLE_3,
        4, 4, 0,
        130, 150,
        255, 0,
        1.0f, 1.0f,
        0.0f, 0.0f, 0.0f,
        dx_debug_menu_draw_contents, NULL,
        NULL,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        NULL
    );
}

#endif
