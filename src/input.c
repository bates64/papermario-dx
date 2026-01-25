#include "common.h"
#include "nu/nusys.h"

OSContPad ContPadData;
BSS s16 StickExtremeX;
BSS s16 StickExtremeY;
BSS s16 StickRetriggerStateX;
BSS s16 StickRetriggerStateY;

void reset_input_state(void) {
    gGameStatusPtr->curButtons[0] = 0;
    gGameStatusPtr->pressedButtons[0] = 0;
    gGameStatusPtr->heldButtons[0] = 0;
    gGameStatusPtr->stickX[0] = 0;
    gGameStatusPtr->stickY[0] = 0;
    gGameStatusPtr->prevButtons[0] = 0;
    gGameStatusPtr->holdRepeatInterval[0] = 4;
    gGameStatusPtr->holdDelayTime[0] = 15;
    gGameStatusPtr->holdRepeatCounter = 0;
    gGameStatusPtr->holdDelayCounter = 0;
}

void clear_input(void) {
    reset_input_state();
    StickExtremeX = 0;
    StickExtremeY = 0;
    StickRetriggerStateX = 0;
    StickRetriggerStateY = 0;
}

void update_input(void) {
    OSContPad* contData = &ContPadData;
    s16 handleInput = FALSE;
    s16 cond1;
    s32 buttons;
    s16 stickX;
    s16 stickY;

    if (gGameStatusPtr->contBitPattern & 1) {
        handleInput = TRUE;
        nuContDataGet(contData, 0);
    }

    if (gGameStatusPtr->demoState != DEMO_STATE_NONE) {
        if (gGameStatusPtr->demoState < DEMO_STATE_CHANGE_MAP
            && (contData->button & (BUTTON_A | BUTTON_B | BUTTON_Z | BUTTON_START))
            && handleInput
        ) {
            gGameStatusPtr->demoState = DEMO_STATE_CHANGE_MAP;
        }
        contData->button = gGameStatusPtr->demoButtonInput;
        contData->stick_x = gGameStatusPtr->demoStickX;
        contData->stick_y = gGameStatusPtr->demoStickY;
        handleInput = TRUE;
    }

    if (!handleInput) {
        return;
    }

    stickX = contData->stick_x;
    stickY = contData->stick_y;
    if (stickX > 0) {
        stickX -= 4;
        if (stickX < 0) {
            stickX = 0;
        }
    }
    if (stickX < 0) {
        stickX += 4;
        if (stickX > 0) {
            stickX = 0;
        }
    }

    if (stickY > 0) {
        stickY -= 4;
        if (stickY < 0) {
            stickY = 0;
        }
    }
    if (stickY < 0) {
        stickY += 4;
        if (stickY > 0) {
            stickY = 0;
        }
    }

    gGameStatusPtr->stickX[0] = stickX;
    gGameStatusPtr->stickY[0] = stickY;

    buttons = contData->button;
    cond1 = FALSE;
    if (stickX > 0x20) {
        cond1 = TRUE;
        buttons |= BUTTON_STICK_RIGHT;
        if (!(gGameStatusPtr->prevButtons[0] & BUTTON_STICK_RIGHT)) {
            StickExtremeX = stickX;
        } else if (StickRetriggerStateX == 0) {
            if (StickExtremeX < stickX) {
                StickExtremeX = stickX;
            }
        } else {
            if (StickExtremeX > stickX) {
                StickExtremeX = stickX;
            }
        }
    }

    if (stickX < -0x20) {
        cond1 = TRUE;
        buttons |= BUTTON_STICK_LEFT;
        if (!(gGameStatusPtr->prevButtons[0] & BUTTON_STICK_LEFT)) {
            StickExtremeX = stickX;
        } else if (StickRetriggerStateX == 0) {
            if (StickExtremeX > stickX) {
                StickExtremeX = stickX;
            }
        } else {
            if (StickExtremeX < stickX)
            {
                StickExtremeX = stickX;
            }
        }
    }

    if (!cond1) {
        StickRetriggerStateX = 0;
        StickExtremeX = stickX;
    }

    cond1 = FALSE;
    if (stickY > 0x20) {
        cond1 = TRUE;
        buttons |= BUTTON_STICK_UP;
        if (!(gGameStatusPtr->prevButtons[0] & BUTTON_STICK_UP)) {
            StickExtremeY = stickY;
        } else if (StickRetriggerStateY == 0) {
            if (StickExtremeY < stickY) {
                StickExtremeY = stickY;
            }
        } else {
            if (StickExtremeY > stickY) {
                StickExtremeY = stickY;
            }
        }
    }

    if (stickY < -0x20) {
        cond1 = TRUE;
        buttons |= BUTTON_STICK_DOWN;
        if (!(gGameStatusPtr->prevButtons[0] & BUTTON_STICK_DOWN)) {
            StickExtremeY = stickY;
        } else if (StickRetriggerStateY == 0) {
            if (StickExtremeY > stickY) {
                StickExtremeY = stickY;
            }
        } else {
            if (StickExtremeY < stickY) {
                StickExtremeY = stickY;
            }
        }
    }

    if (!cond1) {
        StickRetriggerStateY = 0;
        StickExtremeY = stickY;
    }

    if (stickX > 0x20) {
        if (StickRetriggerStateX == 1 && stickX - StickExtremeX > 0x10) {
            buttons &= ~BUTTON_STICK_RIGHT;
            StickRetriggerStateX = 0;
        }
        if (StickExtremeX - stickX > 0x10) {
            StickRetriggerStateX = 1;
        }
    }

    if (stickX < -0x20) {
        if (StickRetriggerStateX == 1 && StickExtremeX - stickX > 0x10) {
            buttons &= ~BUTTON_STICK_LEFT;
            StickRetriggerStateX = 0;
        }
        if (stickX - StickExtremeX > 0x10) {
            StickRetriggerStateX = 1;
        }
    }

    if (stickY > 0x20) {
        if (StickRetriggerStateY == 1 && stickY - StickExtremeY > 0x10) {
            buttons &= ~BUTTON_STICK_UP;
            StickRetriggerStateY = 0;
        }
        if (StickExtremeY - stickY > 0x10) {
            StickRetriggerStateY = 1;
        }
    }

    if (stickY < -0x20) {
        if (StickRetriggerStateY == 1 && StickExtremeY - stickY > 0x10) {
            buttons &= ~BUTTON_STICK_DOWN;
            StickRetriggerStateY = 0;
        }
        if (stickY - StickExtremeY > 0x10) {
            StickRetriggerStateY = 1;
        }
    }

    gGameStatusPtr->curButtons[0] = buttons;
    gGameStatusPtr->pressedButtons[0] = gGameStatusPtr->curButtons[0] ^ gGameStatusPtr->prevButtons[0];
    gGameStatusPtr->pressedButtons[0] &= gGameStatusPtr->curButtons[0];

    if (gGameStatusPtr->curButtons[0] == 0) {
        gGameStatusPtr->heldButtons[0] = 0;
    } else if (gGameStatusPtr->prevButtons[0] != gGameStatusPtr->curButtons[0]) {
        gGameStatusPtr->heldButtons[0] = gGameStatusPtr->curButtons[0];
        gGameStatusPtr->holdRepeatCounter = -1;
        gGameStatusPtr->heldButtons[0] = gGameStatusPtr->curButtons[0] ^ gGameStatusPtr->prevButtons[0];
        gGameStatusPtr->heldButtons[0] &= gGameStatusPtr->curButtons[0];
        gGameStatusPtr->holdDelayCounter = gGameStatusPtr->holdDelayTime[0];
    } else {
        if (gGameStatusPtr->holdRepeatCounter >= 0) {
            gGameStatusPtr->holdRepeatCounter--;
            if (gGameStatusPtr->holdRepeatCounter != 0) {
                gGameStatusPtr->heldButtons[0] = 0;
            } else {
                gGameStatusPtr->heldButtons[0] = gGameStatusPtr->curButtons[0];
                gGameStatusPtr->holdRepeatCounter = gGameStatusPtr->holdRepeatInterval[0];
            }
        } else {
            gGameStatusPtr->holdDelayCounter--;
            if (gGameStatusPtr->holdDelayCounter != 0) {
                gGameStatusPtr->heldButtons[0] = 0;
            } else {
                gGameStatusPtr->heldButtons[0] = gGameStatusPtr->curButtons[0];
                gGameStatusPtr->holdRepeatCounter = gGameStatusPtr->holdRepeatInterval[0];
            }
        }
    }

    gGameStatusPtr->prevButtons[0] = gGameStatusPtr->curButtons[0];
}
