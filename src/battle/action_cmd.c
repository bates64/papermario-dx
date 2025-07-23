#include <dlfcn.h>
#include "common.h"

u8 mashMeter_bgColors[15] = {
     33,  33, 117,
     29,  35, 163,
     70,  12, 180,
    107,   0, 120,
    115,  13,  19,
};

u8 mashMeter_fillColors[15] = {
      0, 228, 134,
     46, 180, 242,
    117, 112, 255,
    243,   4, 188,
    247,  13,   5,
};

u8 mashMeter_cutOffColors[15] = {
     45,  56, 210,
     84,  40, 209,
    125,  44, 181,
    161,  27,  85,
    255, 255, 255,
};

Difficulty1D actionCmdTableJump = { 7, 6, 5, 4, 3, 2, 1, 0 };
Difficulty1D actionCmdTableHammer = { 11, 10, 9, 8, 7, 6, 5, 4 };
Difficulty1D actionCmdTableFlee = { 130, 120, 110, 100, 90, 80, 70, 60 };
Difficulty1D actionCmdTableBreakFree = { 130, 120, 110, 100, 90, 80, 70, 60 };
Difficulty1D actionCmdTableWhirlwind = { 130, 120, 110, 100, 90, 80, 70, 60 };
Difficulty1D actionCmdTableStopLeech = { 130, 120, 110, 100, 90, 80, 70, 60 };
Difficulty1D actionCmdTable07 = { 130, 120, 110, 100, 90, 80, 70, 60 };
Difficulty1D actionCmdTableDizzyShell = { 130, 120, 110, 100, 90, 80, 70, 60 };
Difficulty1D actionCmdTableFireShell = { 130, 120, 110, 100, 90, 80, 70, 60 };
Difficulty1D actionCmdTable0A = { 130, 120, 110, 100, 90, 80, 70, 60 };
Difficulty1D actionCmdTableBomb = { 130, 120, 110, 100, 90, 80, 70, 60 };
Difficulty1D actionCmdTableBodySlam = { 9, 8, 7, 6, 5, 4, 3, 2 };
Difficulty1D actionCmdTableAirLift = { 130, 120, 110, 100, 90, 80, 70, 60 };
Difficulty1D actionCmdTableAirRaid = { 130, 120, 110, 100, 90, 80, 70, 60 };
Difficulty1D actionCmdTableSquirt = { 130, 120, 110, 100, 90, 80, 70, 60 };
Difficulty1D actionCmdTablePowerShock = { 130, 120, 110, 100, 90, 80, 70, 60 };
Difficulty1D actionCmdTableMegaShock = { 130, 120, 110, 100, 90, 80, 70, 60 };
Difficulty1D actionCmdTableSmack = { 130, 120, 110, 100, 90, 80, 70, 60 };
Difficulty1D actionCmdTableSpinySurge = { 130, 120, 110, 100, 90, 80, 70, 60 };
Difficulty1D actionCmdTableHurricane = { 130, 120, 110, 100, 90, 80, 70, 60 };
Difficulty1D actionCmdTableSpook = { 130, 120, 110, 100, 90, 80, 70, 60 };
Difficulty2D actionCmdTableWaterBlock = { {6, 3}, {5, 3}, {4, 3}, {2, 3}, {1, 3}, {0, 3}, {0, 2}, {0, 1} };
Difficulty1D actionCmdTableTidalWave = { 130, 120, 110, 100, 90, 80, 70, 60 };

BSS s32 MashMeterSmoothDivisor;
BSS s32 D_8029FBC4_pad[3];
// TODO move to actor_api
BSS s32 IsGroupHeal;
BSS s8 ApplyingBuff;
BSS s32 D_8029FBD8_pad[2];

#include "battle/action_cmd.h"

BSS ActionCommandStatus gActionCommandStatus;

API_CALLABLE(LoadActionCommand) {
    Bytecode* args = script->ptrReadPos;
    const char* cmd = (const char*)evt_get_variable(script, *args++);

    // Free any currently loaded action command
    action_command_free();

    // Load the new action command
    char path[64];
    snprintf(path, sizeof(path), "rom:/battle/action_cmd/%s.dso", cmd);
    gActionCommandStatus.overlay.handle = dlopen(path, RTLD_LOCAL);
    ASSERT_MSG(gActionCommandStatus.overlay.handle, "Failed to load action command %s", cmd);

    gActionCommandStatus.overlay.init = dlsym(gActionCommandStatus.overlay.handle, "init");
    ASSERT_MSG(gActionCommandStatus.overlay.init, "Action command %s lacks init function", cmd);
    gActionCommandStatus.overlay.start = dlsym(gActionCommandStatus.overlay.handle, "start");
    ASSERT_MSG(gActionCommandStatus.overlay.start, "Action command %s lacks start function", cmd);
    gActionCommandStatus.overlay.update = dlsym(gActionCommandStatus.overlay.handle, "update");
    ASSERT_MSG(gActionCommandStatus.overlay.update, "Action command %s lacks update function", cmd);
    gActionCommandStatus.overlay.draw = dlsym(gActionCommandStatus.overlay.handle, "draw");
    ASSERT_MSG(gActionCommandStatus.overlay.draw, "Action command %s lacks draw function", cmd);
    gActionCommandStatus.overlay.free = dlsym(gActionCommandStatus.overlay.handle, "free");
    ASSERT_MSG(gActionCommandStatus.overlay.free, "Action command %s lacks free function", cmd);

    return ApiStatus_DONE2;
}

API_CALLABLE(InitActionCommand) {
    if (gActionCommandStatus.overlay.init) {
        return gActionCommandStatus.overlay.init(script, isInitialCall);
    } else {
        PANIC_MSG("No action command loaded");
    }
}

API_CALLABLE(StartActionCommand) {
    if (gActionCommandStatus.overlay.start) {
        return gActionCommandStatus.overlay.start(script, isInitialCall);
    } else {
        PANIC_MSG("No action command loaded");
    }
}

s32 adjust_action_command_difficulty(s32 difficultyLevel) {
    if (!(gBattleStatus.flags1 & BS_FLAGS1_PARTNER_ACTING)) {
        difficultyLevel -= is_ability_active(ABILITY_DODGE_MASTER) * 3;
    }

    if (difficultyLevel < 0) {
        difficultyLevel = 0;
    }
    if (difficultyLevel > 7) {
        difficultyLevel = 7;
    }

    return difficultyLevel;
}

void draw_mash_meter(s32 posX, s32 posY, s32 fillValue, s32 colorMode) {
    ActionCommandStatus* acs = &gActionCommandStatus;
    s32 maxCutOff;
    s32 i;
    s32 cutOff;
    s32 width;
    s32 offsetX;
    s32 filledWidth;
    s32 r, g, b;

    if (!acs->showHud) {
        return;
    }

    posX -= 28;
    posY -= 4;

    maxCutOff = acs->mashMeterCutoffs[acs->mashMeterNumIntervals];

    if (fillValue < 0) {
        fillValue = 0;
    }

    width = 0;
    for (i = 0; i < acs->mashMeterNumIntervals; i++) {
        cutOff = acs->mashMeterCutoffs[i + 1];
        if (cutOff > fillValue) {
            cutOff = fillValue;
        }

        width = (cutOff * 60 / maxCutOff) * 100;
        if (fillValue == cutOff) {
            break;
        }
    }

    //difference between current and previous filled value
    offsetX = width - acs->meterFillWidth;
    if (abs(offsetX) >= MashMeterSmoothDivisor * 100) {
        acs->meterFillWidth += offsetX / MashMeterSmoothDivisor;
    } else {
        acs->meterFillWidth = width;
    }

    offsetX = 0;
    for (i = 0; i < acs->mashMeterNumIntervals; i++) {
        cutOff = acs->mashMeterCutoffs[i + 1];
        width = (cutOff * 60 / maxCutOff) - offsetX;
        r = mashMeter_bgColors[3 * i + 0];
        g = mashMeter_bgColors[3 * i + 1];
        b = mashMeter_bgColors[3 * i + 2];
        startup_draw_prim_rect_COPY(posX + offsetX, posY, posX + offsetX + width, posY + 5, r, g, b, 255);
        if (i < acs->mashMeterNumIntervals - 1) {
            r = mashMeter_cutOffColors[3 * i + 0];
            g = mashMeter_cutOffColors[3 * i + 1];
            b = mashMeter_cutOffColors[3 * i + 2];
            startup_draw_prim_rect_COPY(posX + offsetX + width - 1, posY, posX + offsetX + width, posY + 5, r, g, b, 255);
            offsetX += width;
        } else {
            break;
        }
    }

    offsetX = 0;
    for (i = 0; i < acs->mashMeterNumIntervals; i++) {
        if (colorMode == 0) {
            r = mashMeter_fillColors[3 * i + 0];
            g = mashMeter_fillColors[3 * i + 1];
            b = mashMeter_fillColors[3 * i + 2];
        } else if (colorMode > 0) {
            r = 224;
            g = 63;
            b = 0;
        } else if (gGameStatusPtr->frameCounter % 2 != 0){
            r = mashMeter_fillColors[3 * i + 0];
            g = mashMeter_fillColors[3 * i + 1];
            b = mashMeter_fillColors[3 * i + 2];
        } else {
            r = 250;
            g = 175;
            b = 0;
        }

        cutOff = acs->mashMeterCutoffs[i + 1];
        if (cutOff > fillValue) {
            cutOff = fillValue;
        }

        filledWidth = cutOff * 60 / maxCutOff - offsetX;
        width = acs->meterFillWidth / 100 - offsetX;

        if (width < 0) {
            break;
        }
        if (filledWidth == 0) {
            filledWidth = width;
        } else if (cutOff == fillValue) {
            filledWidth = width;
        } else if (width > filledWidth) {
            width = filledWidth;
        }

        startup_draw_prim_rect_COPY(posX + offsetX, posY, posX + offsetX + width, posY + 5, r, g, b, 255);
        offsetX += filledWidth;
        if (i >= acs->mashMeterNumIntervals - 1) {
            break;
        }
    }
}

void draw_mash_meter_multicolor(s32 posX, s32 posY, s32 fillValue) {
    MashMeterSmoothDivisor = 2;
    draw_mash_meter(posX, posY, fillValue, MASH_METER_MODE_MULTI_COLOR);
}

void draw_mash_meter_multicolor_with_divisor(s32 posX, s32 posY, s32 fillValue, s32 divisor) {
    MashMeterSmoothDivisor = divisor;
    draw_mash_meter(posX, posY, fillValue, MASH_METER_MODE_MULTI_COLOR);
}

void draw_mash_meter_mode(s32 posX, s32 posY, s32 fillValue, s32 colorMode) {
    MashMeterSmoothDivisor = 2;
    draw_mash_meter(posX, posY, fillValue, colorMode);
}

void draw_mash_meter_mode_with_divisor(s32 posX, s32 posY, s32 fillValue, s32 divisor, s32 colorMode) {
    MashMeterSmoothDivisor = divisor;
    draw_mash_meter(posX, posY, fillValue, colorMode);
}

void draw_mash_meter_blink(s32 posX, s32 posY, s32 fillValue) {
    MashMeterSmoothDivisor = 2;
    draw_mash_meter(posX, posY, fillValue, MASH_METER_MODE_BLINK);
}

void draw_mash_meter_blink_with_divisor(s32 posX, s32 posY, s32 fillValue, s32 divisor) {
    MashMeterSmoothDivisor = divisor;
    draw_mash_meter(posX, posY, fillValue, MASH_METER_MODE_BLINK);
}

void action_command_init_status(void) {
    ActionCommandStatus* acs = &gActionCommandStatus;

    acs->autoSucceed = FALSE;
    acs->berserkerEnabled = FALSE;

    if (!(gBattleStatus.flags1 & BS_FLAGS1_PARTNER_ACTING)) {
        if (is_ability_active(ABILITY_RIGHT_ON)) {
            acs->autoSucceed = TRUE;
        }

        if (is_ability_active(ABILITY_BERSERKER)) {
            acs->showHud = FALSE;
            acs->berserkerEnabled = TRUE;

            if (rand_int(100) < 25) {
                acs->autoSucceed = TRUE;
            }
        }
    }

    if (gGameStatusPtr->demoBattleFlags & DEMO_BTL_FLAG_ENABLED) {
        acs->autoSucceed = TRUE;
    }

    if (gBattleStatus.flags1 & BS_FLAGS1_AUTO_SUCCEED_ACTION) {
        acs->autoSucceed = TRUE;
        acs->showHud = FALSE;
    }
}

void action_command_update(void) {
    if (gBattleStatus.flags1 & BS_FLAGS1_FREE_ACTION_COMMAND) {
        action_command_free();
    }
    if (gActionCommandStatus.overlay.update) {
        gActionCommandStatus.overlay.update();
    }
}

void action_command_draw(void) {
    if (gActionCommandStatus.overlay.draw) {
        gActionCommandStatus.overlay.draw();
    }
}

void action_command_free(void) {
    ActionCommandStatus* acs = &gActionCommandStatus;

    if (gActionCommandStatus.overlay.free) {
        gActionCommandStatus.overlay.free();
    }
    if (dlclose(acs->overlay.handle)) {
        PANIC_MSG("dlclose failed: %s", dlerror());
    }
    memset(&acs->overlay, 0, sizeof(acs->overlay));
    acs->actionCommandID = ACTION_COMMAND_NONE;

    gBattleStatus.flags1 &= ~BS_FLAGS1_2000;
    gBattleStatus.flags1 &= ~BS_FLAGS1_FREE_ACTION_COMMAND;
    gBattleStatus.flags1 &= ~BS_FLAGS1_4000;
    close_action_command_instruction_popup();
    btl_set_popup_duration(POPUP_MSG_OFF);
}

void create_action_command_ui_worker(void) {
    ActionCommandStatus* actionCmdStatus = &gActionCommandStatus;
    actionCmdStatus->workerID = create_worker_frontUI(action_command_update, action_command_draw);
    actionCmdStatus->actionCommandID = ACTION_COMMAND_NONE;
}

s32 check_block_input(s32 buttonMask) {
    BattleStatus* battleStatus = &gBattleStatus;
    PlayerData* playerData = &gPlayerData;
    ActionCommandStatus* acs = &gActionCommandStatus;
    s32 mashWindow;
    s32 blockWindow;
    s32 block;
    s32 mash = FALSE;
    s32 bufferPos;
    s32 i;
    s32 ignoreWindow;

    battleStatus->blockResult = BLOCK_RESULT_FAIL;

    if (battleStatus->actionCommandMode == AC_MODE_TUTORIAL_BLOCK && (battleStatus->flags1 & BS_FLAGS1_TUTORIAL_BATTLE)) {
        battleStatus->blockResult = BLOCK_RESULT_SUCCESS;
        return TRUE;
    }

    if (battleStatus->actionCommandMode == AC_MODE_NOT_LEARNED || (gGameStatusPtr->demoBattleFlags & DEMO_BTL_FLAG_ENABLED)) {
        return FALSE;
    }

    if (playerData->hitsTaken < 9999) {
        playerData->hitsTaken++;
        acs->hitsTakenIsMax = FALSE;
    } else {
        acs->hitsTakenIsMax = TRUE;
    }

    block = FALSE;
    blockWindow = 3;
    mashWindow = 10;

    if (!(gBattleStatus.flags1 & BS_FLAGS1_PARTNER_ACTING) && is_ability_active(ABILITY_DODGE_MASTER)) {
        blockWindow = 5;
    }

    // Pre-window mashing check
    bufferPos = battleStatus->inputBufferPos;
    bufferPos -= mashWindow + blockWindow;

    if (bufferPos < 0) {
        bufferPos += ARRAY_COUNT(battleStatus->pushInputBuffer);
    }
    for (i = 0; i < mashWindow; i++) {
        if (bufferPos >= ARRAY_COUNT(battleStatus->pushInputBuffer)) {
            bufferPos -= ARRAY_COUNT(battleStatus->pushInputBuffer);
        }

        if (battleStatus->pushInputBuffer[bufferPos] & buttonMask) {
            mash = TRUE;
            break;
        }
        bufferPos++;
    }

    // Block check
    bufferPos = battleStatus->inputBufferPos;
    bufferPos -= blockWindow;
    if (bufferPos < 0) {
        bufferPos += ARRAY_COUNT(battleStatus->pushInputBuffer);
    }
    for (i = 0; i < blockWindow; i++) {
        if (bufferPos >= ARRAY_COUNT(battleStatus->pushInputBuffer)) {
            bufferPos -= ARRAY_COUNT(battleStatus->pushInputBuffer);
        }

        if (battleStatus->pushInputBuffer[bufferPos] & buttonMask) {
            battleStatus->blockResult = BLOCK_RESULT_SUCCESS;
            block = TRUE;
            break;
        }
        bufferPos++;
    }

    if (mash) {
        battleStatus->blockResult = BLOCK_RESULT_EARLY;
        block = FALSE;
    }

    // Ignore inputs until another mash window has passed, so check_block_input() can be called in quick succession
    if (block == TRUE) {
        bufferPos = battleStatus->inputBufferPos;
        bufferPos -= mashWindow + blockWindow;
        if (bufferPos < 0) {
            bufferPos += ARRAY_COUNT(battleStatus->pushInputBuffer);
        }

        for (i = 0; i < mashWindow + blockWindow; i++) {
            if (bufferPos >= ARRAY_COUNT(battleStatus->pushInputBuffer)) {
                bufferPos -= ARRAY_COUNT(battleStatus->pushInputBuffer);
            }
            battleStatus->pushInputBuffer[bufferPos] = 0;
            bufferPos++;
        }
    }
    if (block && !acs->hitsTakenIsMax) {
        playerData->hitsBlocked++;
    }

    return block;
}

void increment_action_command_attempt_count(void) {
    PlayerData* playerData = &gPlayerData;
    ActionCommandStatus *acs = &gActionCommandStatus;

    if (!acs->autoSucceed) {
        if (playerData->actionCommandAttempts < 9999) {
            playerData->actionCommandAttempts++;
            acs->hitsTakenIsMax = FALSE;
        } else {
            acs->hitsTakenIsMax = TRUE;
        }
    }
}

void increment_action_command_success_count(void) {
    PlayerData* playerData = &gPlayerData;

    if (!gActionCommandStatus.autoSucceed && gActionCommandStatus.hitsTakenIsMax) {
        playerData->actionCommandSuccesses++;
    }
}

API_CALLABLE(SetActionDifficultyTable) {
    gBattleStatus.actionCmdDifficultyTable = (s32*) evt_get_variable(script, *script->ptrReadPos);
    return ApiStatus_DONE2;
}

API_CALLABLE(SetupMashMeter) {
    Bytecode* args = script->ptrReadPos;
    gActionCommandStatus.mashMeterNumIntervals = evt_get_variable(script, *args++);
    gActionCommandStatus.mashMeterCutoffs[1] = evt_get_variable(script, *args++);
    gActionCommandStatus.mashMeterCutoffs[2] = evt_get_variable(script, *args++);
    gActionCommandStatus.mashMeterCutoffs[3] = evt_get_variable(script, *args++);
    gActionCommandStatus.mashMeterCutoffs[4] = evt_get_variable(script, *args++);
    gActionCommandStatus.mashMeterCutoffs[5] = evt_get_variable(script, *args++);
    gActionCommandStatus.mashMeterCutoffs[0] = gActionCommandStatus.mashMeterCutoffs[1] / 2;
    return ApiStatus_DONE2;
}

API_CALLABLE(GetSmashActionQuality) {
    evt_set_variable(script, *script->ptrReadPos, gBattleStatus.actionQuality);
    return ApiStatus_DONE2;
}

API_CALLABLE(SetActionSuccess) {
    gBattleStatus.actionQuality = evt_get_variable(script, *script->ptrReadPos);
    return ApiStatus_DONE2;
}

API_CALLABLE(SetActionCommandMode) {
    gBattleStatus.actionCommandMode = evt_get_variable(script, *script->ptrReadPos);
    return ApiStatus_DONE2;
}

API_CALLABLE(GetActionCommandMode) {
    evt_set_variable(script, *script->ptrReadPos, gBattleStatus.actionCommandMode);
    return ApiStatus_DONE2;
}

API_CALLABLE(SetActionHudPrepareTime) {
    gActionCommandStatus.hudPrepareTime = evt_get_variable(script, *script->ptrReadPos);
    return ApiStatus_DONE2;
}

API_CALLABLE(GetCommandAutoSuccess) {
    evt_set_variable(script, *script->ptrReadPos, gActionCommandStatus.autoSucceed);
    return ApiStatus_DONE2;
}

API_CALLABLE(SetCommandAutoSuccess) {
    ActionCommandStatus* acs = &gActionCommandStatus;

    if (evt_get_variable(script, *script->ptrReadPos) != 0) {
        acs->autoSucceed = TRUE;
    } else {
        acs->autoSucceed = FALSE;
    }
    return ApiStatus_DONE2;
}

API_CALLABLE(func_802693F0) {
    gBattleStatus.flags1 &= ~BS_FLAGS1_4000;
    return ApiStatus_DONE2;
}

API_CALLABLE(InterruptActionCommand) {
    ActionCommandStatus* acs = &gActionCommandStatus;

    if (isInitialCall) {
        // TODO(decouple): add overlay function that defines interrupt behaviour
        switch (acs->actionCommandID) {
            case ACTION_COMMAND_WHIRLWIND:
            case ACTION_COMMAND_STOP_LEECH:
                return ApiStatus_DONE2;
            default:
                action_command_free();
                return ApiStatus_BLOCK;
        }
    }

    sfx_stop_sound(SOUND_LOOP_CHARGE_METER);
    close_action_command_instruction_popup();

    return ApiStatus_DONE2;
}

API_CALLABLE(InterruptLeechActionCommand) {
    if (isInitialCall) {
        action_command_free();
        return ApiStatus_BLOCK;
    }

    close_action_command_instruction_popup();
    return ApiStatus_DONE2;
}

API_CALLABLE(ShowActionHud) {
    ActionCommandStatus* acs = &gActionCommandStatus;

    if (evt_get_variable(script, *script->ptrReadPos) == 0) {
        acs->showHud = FALSE;
    } else {
        acs->showHud = TRUE;
    }
    return ApiStatus_DONE2;
}

API_CALLABLE(GetMashActionQuality) {
    evt_set_variable(script, *script->ptrReadPos, gBattleStatus.actionQuality);
    return ApiStatus_DONE2;
}

API_CALLABLE(GetJumpActionQuality) {
    evt_set_variable(script, *script->ptrReadPos, gBattleStatus.actionResult);
    return ApiStatus_DONE2;
}

API_CALLABLE(SetActionResult) {
    gBattleStatus.actionResult = evt_get_variable(script, *script->ptrReadPos);
    return ApiStatus_DONE2;
}

API_CALLABLE(GetBlockResult) {
    evt_set_variable(script, *script->ptrReadPos, gBattleStatus.blockResult);
    return ApiStatus_DONE2;
}

API_CALLABLE(GetActionProgress) {
    evt_set_variable(script, *script->ptrReadPos, gBattleStatus.actionProgress);
    return ApiStatus_DONE2;
}

API_CALLABLE(SetActionProgress) {
    gBattleStatus.actionProgress = evt_get_variable(script, *script->ptrReadPos);
    return ApiStatus_DONE2;
}

API_CALLABLE(GetActionResultTier) {
    evt_set_variable(script, *script->ptrReadPos, gBattleStatus.resultTier);
    return ApiStatus_DONE2;
}

API_CALLABLE(SetActionResultTier) {
    gBattleStatus.resultTier = evt_get_variable(script, *script->ptrReadPos);
    return ApiStatus_DONE2;
}
