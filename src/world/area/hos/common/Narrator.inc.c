#include "common.h"

#define INTRO_MSG_BLANK -1

enum {
    INTRO_MSG_STATE_APPEAR    = 0,
    INTRO_MSG_STATE_SHOWING   = 1,
    INTRO_MSG_STATE_VANISH    = 2,
    INTRO_MSG_STATE_DONE      = 3,
    INTRO_MSG_STATE_BLANK     = 4,
};

typedef struct IntroMessage {
    /* 00 */ s32 messageID;
    /* 04 */ s32 duration;
} IntroMessage; // size: 0x8

u32 IntroMessageState = 0; // mode
s32 IntroMessageAlpha = 0; // alpha related
IntroMessage* CurMessageList = nullptr;

void UpdateIntroMessages(IntroMessage** introMessageLists) {
    u8 type;
    f32 zoom1;
    f32 zoom2;
    s32 messageID;
    s32 opacity;
    s32 yOffset;
    static s32 IntroMessageDelay;

    if (CurMessageList == nullptr) {
        CurMessageList = introMessageLists[IntroMessageIdx];
    }

    switch (IntroMessageState) {
        case INTRO_MSG_STATE_APPEAR:
            if (CurMessageList->messageID == INTRO_MSG_BLANK) {
                IntroMessageState = INTRO_MSG_STATE_BLANK;
                IntroMessageDelay = CurMessageList->duration;
            } else {
                IntroMessageAlpha += 10;
                if (IntroMessageAlpha > 255) {
                    IntroMessageAlpha = 255;
                    IntroMessageState = INTRO_MSG_STATE_SHOWING;
                    IntroMessageDelay = CurMessageList->duration;
                }
            }
            break;
        case INTRO_MSG_STATE_SHOWING:
            if (IntroMessageDelay == 0) {
                IntroMessageState = INTRO_MSG_STATE_VANISH;
            } else {
                IntroMessageDelay--;
            }
            break;
        case INTRO_MSG_STATE_VANISH:
            IntroMessageAlpha -= 10;
            if (IntroMessageAlpha < 0) {
                IntroMessageAlpha = 0;
                CurMessageList++;
                if (CurMessageList->messageID == MSG_NONE) {
                    IntroMessageState = INTRO_MSG_STATE_DONE;
                } else {
                    IntroMessageState = INTRO_MSG_STATE_APPEAR;
                }
            }
            break;
        case INTRO_MSG_STATE_DONE:
            break;
        case INTRO_MSG_STATE_BLANK:
            if (IntroMessageDelay != 0) {
                IntroMessageDelay--;
                break;
            }
            CurMessageList++;
            if (CurMessageList->messageID == MSG_NONE) {
                IntroMessageState = INTRO_MSG_STATE_DONE;
            } else {
                IntroMessageState = INTRO_MSG_STATE_APPEAR;
            }
            break;
    }
    get_screen_overlay_params(SCREEN_LAYER_BACK, &type, &zoom1);
    get_screen_overlay_params(SCREEN_LAYER_FRONT, &type, &zoom2);
    opacity = ((IntroMessageAlpha * (255.0f - zoom1) * (255.0f - zoom2)) / 255.0f) / 255.0f;
    if (opacity > 0) {
        messageID = CurMessageList->messageID;
        if (messageID != 0) {
#if VERSION_JP
            draw_msg(CurMessageList->messageID, 0, 200, opacity, -1, 0);
#else
            yOffset = 0;
            if (get_msg_lines(messageID) >= 2) {
                yOffset = -7;
            }
            draw_msg(CurMessageList->messageID, 0, yOffset + 196, opacity, -1, 0);
#endif
        }
    }
}

API_CALLABLE(SetCurtainCallback) {
    Bytecode* args = script->ptrReadPos;

    set_curtain_draw_callback((VoidCallback) evt_get_variable(script, *args++));
    return ApiStatus_DONE2;
}
