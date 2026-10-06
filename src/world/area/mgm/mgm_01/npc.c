#include "mgm_01.h"
#include "hud_element.h"
#include "effects.h"
#include "entity.h"

#define SCOREKEEPER_ENEMY_IDX 0
#define BROKEN_BLOCKS_VAR_IDX 2
#define TOTAL_BLOCKS_VAR_IDX 4
#define JUMP_DATA_VAR_IDX 5

#define PLAY_COST 10
#define NUM_BLOCKS 11

typedef enum JumpGamePanelType {
    PANEL_1_COIN    = 0,
    PANEL_5_COINS   = 1,
    PANEL_TIMES_5   = 2,
    PANEL_BOWSER    = 3
} JumpGamePanelType;

typedef enum JumpGamePanelState {
    PANEL_STATE_INIT            = 0,
    PANEL_STATE_START_ANIM      = 1,
    PANEL_STATE_EMERGE_INIT     = 2,
    PANEL_STATE_EMERGE_UPDATE   = 3,
    PANEL_STATE_HOLD_INIT       = 4,
    PANEL_STATE_HOLD_UPDATE     = 5,
    PANEL_STATE_TO_TALLY_INIT   = 6,
    PANEL_STATE_TO_TALLY_UPDATE = 7,
    PANEL_STATE_STOP_ANIM       = 8,
    PANEL_STATE_DONE            = 9
} JumpGamePanelState;

// the panels found by breaking brick blocks
typedef struct JumpGamePanel {
    /* 0x00 */ JumpGamePanelState state;
    /* 0x04 */ s32 modelID;
    /* 0x08 */ JumpGamePanelType type;
    /* 0x0C */ s32 blockPosIndex;
    /* 0x10 */ s32 tallyPosIndex;
    /* 0x14 */ s32 entityIndex;
    /* 0x18 */ s32 lerpElapsed;
    /* 0x1C */ s32 lerpDuration;
    /* 0x20 */ Vec3f curPos;
    /* 0x2C */ Vec3f startPos;
    /* 0x38 */ Vec3f endPos;
    /* 0x44 */ f32 curAngle;
    /* 0x48 */ f32 startAngle;
    /* 0x4C */ f32 endAngle;
    /* 0x50 */ f32 curScale;
    /* 0x54 */ f32 startScale;
    /* 0x58 */ f32 endScale;
} JumpGamePanel; /* size = 5C */

typedef struct JumpGameData {
    /* 0x000 */ s32 workerID;
    /* 0x004 */ HudElemID hudElemID;
    /* 0x008 */ PAD(4);
    /* 0x00C */ s32 curScore;
    /* 0x010 */ s32 targetScore;
    /* 0x014 */ s32 scoreWindowPosX;
    /* 0x018 */ s32 scoreWindowPosY; // unused -- posY is hard-coded while drawing the box
    /* 0x01C */ s32 type[NUM_BLOCKS];
    /* 0x048 */ s32 breakHistory[NUM_BLOCKS];
    /* 0x074 */ JumpGamePanel panels[NUM_BLOCKS];
} JumpGameData; /* size = 0x468 */

extern s32 MessagePlural;
extern s32 MessageSingular;

extern s8 BlockPosX[NUM_BLOCKS];
extern s8 BlockPosY[NUM_BLOCKS];
extern s8 BlockPosZ[NUM_BLOCKS];

extern f32 TallyPosX[NUM_BLOCKS];
extern f32 TallyPosY[NUM_BLOCKS];

extern s32 PanelModelIDs[NUM_BLOCKS];
extern JumpGamePanelType PanelTypes[NUM_BLOCKS];
extern JumpGamePanelType InitialConfigurations[4][NUM_BLOCKS];

extern EvtScript EVS_OnBreakBlock_0;
extern EvtScript EVS_OnBreakBlock_1;
extern EvtScript EVS_OnBreakBlock_2;
extern EvtScript EVS_OnBreakBlock_3;
extern EvtScript EVS_OnBreakBlock_4;
extern EvtScript EVS_OnBreakBlock_5;
extern EvtScript EVS_OnBreakBlock_6;
extern EvtScript EVS_OnBreakBlock_7;
extern EvtScript EVS_OnBreakBlock_8;
extern EvtScript EVS_OnBreakBlock_9;
extern EvtScript EVS_OnBreakBlock_10;

extern EvtScript EVS_InitializePanels;

void appendGfx_score_display (void* renderData) {
    Enemy* scorekeeper = get_enemy(SCOREKEEPER_ENEMY_IDX);
    JumpGameData* data = (JumpGameData*)scorekeeper->varTable[JUMP_DATA_VAR_IDX];
    HudElemID hid;
    s32 diff;

    if (scorekeeper->varTable[BROKEN_BLOCKS_VAR_IDX] == -1) {
        if (data->scoreWindowPosX < SCREEN_WIDTH + 1) {
            data->scoreWindowPosX += 10;
            if (data->scoreWindowPosX > SCREEN_WIDTH + 1) {
                data->scoreWindowPosX = SCREEN_WIDTH + 1;
            }
        }
    } else {
        if (data->scoreWindowPosX > 220) {
            data->scoreWindowPosX -= 10;
            if (data->scoreWindowPosX < 220) {
                data->scoreWindowPosX = 220;
            }
        }
    }

    if (data->scoreWindowPosX < SCREEN_WIDTH + 1) {
        draw_box(0, WINDOW_STYLE_9, data->scoreWindowPosX, 28, 0, 72, 20, 255, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, nullptr, nullptr, nullptr, SCREEN_WIDTH, SCREEN_HEIGHT, nullptr);
        hid = data->hudElemID;
        hud_element_set_render_pos(hid, data->scoreWindowPosX + 15, 39);
        hud_element_draw_clipped(hid);
        if (data->curScore > data->targetScore) {
            data->curScore = data->targetScore;
        } else if (data->curScore < data->targetScore) {
            diff = data->targetScore - data->curScore;
            if (diff > 100) {
                data->curScore += 40;
            } else if (diff > 75) {
                data->curScore += 35;
            } else if (diff > 50) {
                data->curScore += 30;
            } else if (diff > 30) {
                data->curScore += 20;
            } else if (diff > 20) {
                data->curScore += 10;
            } else if (diff > 10) {
                data->curScore += 5;
            } else if (diff > 5) {
                data->curScore += 2;
            } else {
                data->curScore++;
            }
            sfx_play_sound_with_params(SOUND_COIN_PICKUP, 0, 0x40, 0x32);

        }
        draw_number(data->curScore, data->scoreWindowPosX + 63, 32, DRAW_NUMBER_CHARSET_THIN, MSG_PAL_WHITE, 255, DRAW_NUMBER_STYLE_MONOSPACE | DRAW_NUMBER_STYLE_ALIGN_RIGHT);
    }
}

void worker_render_score(void) {
    RenderTask task;

    task.renderMode = RENDER_MODE_CLOUD_NO_ZCMP;
    task.appendGfxArg = 0;
    task.appendGfx = &appendGfx_score_display;
    task.dist = 0;

    queue_render_task(&task);
}

API_CALLABLE(DisableMenus) {
    gOverrideFlags |= GLOBAL_OVERRIDES_DISABLE_MENUS;
    status_bar_ignore_changes();
    close_status_bar();
    return ApiStatus_DONE2;
}

API_CALLABLE(EnableMenus) {
    gOverrideFlags &= ~GLOBAL_OVERRIDES_DISABLE_MENUS;
    return ApiStatus_DONE2;
}

API_CALLABLE(GetPanelInfo) {
    JumpGameData* data = (JumpGameData*)get_enemy(SCOREKEEPER_ENEMY_IDX)->varTable[JUMP_DATA_VAR_IDX];
    Bytecode* args = script->ptrReadPos;
    s32 index = evt_get_variable(script, *args++);

    evt_set_variable(script, LVar0, data->panels[index].state);
    evt_set_variable(script, LVar1, data->panels[index].modelID);
    evt_set_variable(script, LVar2, data->panels[index].type);
    evt_set_variable(script, LVar3, data->panels[index].tallyPosIndex);

    return ApiStatus_DONE2;
}

API_CALLABLE(SetPanelState) {
    JumpGameData* data = (JumpGameData*)get_enemy(SCOREKEEPER_ENEMY_IDX)->varTable[JUMP_DATA_VAR_IDX];
    Bytecode* args = script->ptrReadPos;
    s32 index = evt_get_variable(script, *args++);
    s32 value = evt_get_variable(script, *args++);

    data->panels[index].state = value;

    return ApiStatus_DONE2;
}

API_CALLABLE(InitPanelEmergeFromBlock) {
    JumpGameData* data = (JumpGameData*)get_enemy(SCOREKEEPER_ENEMY_IDX)->varTable[JUMP_DATA_VAR_IDX];
    Bytecode* args = script->ptrReadPos;
    s32 index = evt_get_variable(script, *args++);
    s32 blockPosIndex;

    data->panels[index].lerpElapsed = 0;
    data->panels[index].lerpDuration = 5;

    blockPosIndex = data->panels[index].blockPosIndex;

    data->panels[index].curPos.x = BlockPosX[blockPosIndex];
    data->panels[index].curPos.y = BlockPosY[blockPosIndex] + 15.0;
    data->panels[index].curPos.z = BlockPosZ[blockPosIndex] + 12;

    data->panels[index].startPos.x = data->panels[index].curPos.x;
    data->panels[index].startPos.y = data->panels[index].curPos.y;
    data->panels[index].startPos.z = data->panels[index].curPos.z;

    data->panels[index].endPos.x = data->panels[index].curPos.x;
    data->panels[index].endPos.y = data->panels[index].curPos.y + 35.0;
    data->panels[index].endPos.z = data->panels[index].curPos.z;

    data->panels[index].curAngle = 0;

    data->panels[index].endScale = 2.0;
    data->panels[index].curScale = 1.0;
    data->panels[index].startScale = 1.0;

    return ApiStatus_DONE2;
}

API_CALLABLE(UpdatePanelEmergeFromBlock) {
    JumpGameData* data = (JumpGameData*)get_enemy(SCOREKEEPER_ENEMY_IDX)->varTable[JUMP_DATA_VAR_IDX];
    Bytecode* args = script->ptrReadPos;
    s32 index = evt_get_variable(script, *args++);

    data->panels[index].curPos.x = update_lerp(EASING_QUADRATIC_OUT,
        data->panels[index].startPos.x, data->panels[index].endPos.x,
        data->panels[index].lerpElapsed, data->panels[index].lerpDuration);

    data->panels[index].curPos.y = update_lerp(EASING_QUADRATIC_OUT,
        data->panels[index].startPos.y, data->panels[index].endPos.y,
        data->panels[index].lerpElapsed, data->panels[index].lerpDuration);

    data->panels[index].curPos.z = update_lerp(EASING_QUADRATIC_OUT,
        data->panels[index].startPos.z, data->panels[index].endPos.z,
        data->panels[index].lerpElapsed, data->panels[index].lerpDuration);

    data->panels[index].curScale = update_lerp(EASING_LINEAR,
        data->panels[index].startScale, data->panels[index].endScale,
        data->panels[index].lerpElapsed, data->panels[index].lerpDuration);

    data->panels[index].lerpElapsed++;

    if (data->panels[index].lerpElapsed >= data->panels[index].lerpDuration) {
        evt_set_variable(script, LVar3, true);
    } else {
        evt_set_variable(script, LVar3, false);
    }

    return ApiStatus_DONE2;
}

API_CALLABLE(InitPanelHoldAboveBlock) {
    JumpGameData* data = (JumpGameData*)get_enemy(SCOREKEEPER_ENEMY_IDX)->varTable[JUMP_DATA_VAR_IDX];
    Bytecode* args = script->ptrReadPos;
    s32 index = evt_get_variable(script, *args++);

    data->panels[index].lerpElapsed = 0;
    data->panels[index].lerpDuration = 10;

    return ApiStatus_DONE2;
}

API_CALLABLE(UpdatetPanelHoldAboveBlock) {
    JumpGameData* data = (JumpGameData*)get_enemy(SCOREKEEPER_ENEMY_IDX)->varTable[JUMP_DATA_VAR_IDX];
    Bytecode* args = script->ptrReadPos;
    s32 index = evt_get_variable(script, *args++);

    data->panels[index].lerpElapsed++;
    if (data->panels[index].lerpElapsed >= data->panels[index].lerpDuration) {
        evt_set_variable(script, LVar3, true);
    } else {
        evt_set_variable(script, LVar3, false);
    }

    return ApiStatus_DONE2;
}

API_CALLABLE(InitPanelMoveToTally) {
    JumpGameData* data = (JumpGameData*)get_enemy(SCOREKEEPER_ENEMY_IDX)->varTable[JUMP_DATA_VAR_IDX];
    Bytecode* args = script->ptrReadPos;
    s32 index = evt_get_variable(script, *args++);
    f32 dist;

    data->panels[index].lerpElapsed = 0;
    data->panels[index].curAngle = 0;
    data->panels[index].startAngle = 0;
    data->panels[index].startPos.x = data->panels[index].curPos.x;
    data->panels[index].startPos.y = data->panels[index].curPos.y;
    data->panels[index].startPos.z = data->panels[index].curPos.z;
    data->panels[index].startScale = data->panels[index].curScale;

    if (data->panels[index].type != PANEL_BOWSER) {
        data->panels[index].endPos.x = TallyPosX[data->panels[index].tallyPosIndex];
        data->panels[index].endPos.y = TallyPosY[data->panels[index].tallyPosIndex];
        data->panels[index].endPos.z = 110.0f;
        data->panels[index].endAngle = 360.0f;
        data->panels[index].endScale = 1.0f;
    } else {
        data->panels[index].endPos.x = 0;
        data->panels[index].endPos.y = 100.0f;
        data->panels[index].endPos.z = 120.0f;
        data->panels[index].endAngle = 720.0f;
        data->panels[index].endScale = 4.0f;
    }

    dist = dist3D(
        data->panels[index].startPos.x, data->panels[index].startPos.y, data->panels[index].startPos.z,
        data->panels[index].endPos.x, data->panels[index].endPos.y, data->panels[index].endPos.z);
    if (data->panels[index].type != PANEL_BOWSER) {
        data->panels[index].lerpDuration = (dist * 0.125) + 0.5;
    } else {
        data->panels[index].lerpDuration = (dist / 5.0) + 0.5;
    }

    return ApiStatus_DONE2;
}

API_CALLABLE(UpdatePanelMoveToTally) {
    JumpGameData* data = (JumpGameData*)get_enemy(SCOREKEEPER_ENEMY_IDX)->varTable[JUMP_DATA_VAR_IDX];
    Bytecode* args = script->ptrReadPos;
    s32 index = evt_get_variable(script, *args++);

    data->panels[index].lerpElapsed++;

    data->panels[index].curPos.x = update_lerp(EASING_QUADRATIC_OUT,
        data->panels[index].startPos.x, data->panels[index].endPos.x,
        data->panels[index].lerpElapsed, data->panels[index].lerpDuration);

    data->panels[index].curPos.y = update_lerp(EASING_QUADRATIC_OUT,
        data->panels[index].startPos.y, data->panels[index].endPos.y,
        data->panels[index].lerpElapsed, data->panels[index].lerpDuration);

    data->panels[index].curPos.z = update_lerp(EASING_LINEAR,
        data->panels[index].startPos.z, data->panels[index].endPos.z,
        data->panels[index].lerpElapsed, data->panels[index].lerpDuration);

    data->panels[index].curAngle = update_lerp(EASING_LINEAR,
        data->panels[index].startAngle, data->panels[index].endAngle,
        data->panels[index].lerpElapsed, data->panels[index].lerpDuration);

    data->panels[index].curScale = update_lerp(EASING_LINEAR,
        data->panels[index].startScale, data->panels[index].endScale,
        data->panels[index].lerpElapsed, data->panels[index].lerpDuration);

    if (data->panels[index].lerpElapsed >= data->panels[index].lerpDuration) {
        evt_set_variable(script, LVar3, true);
    } else {
        evt_set_variable(script, LVar3, false);
    }

    return ApiStatus_DONE2;
}

API_CALLABLE(EndPanelAnimation) {
    JumpGameData* data = (JumpGameData*)get_enemy(SCOREKEEPER_ENEMY_IDX)->varTable[JUMP_DATA_VAR_IDX];
    Bytecode* args = script->ptrReadPos;
    s32 index = evt_get_variable(script, *args++);

    data->panels[index].curAngle = 0;

    return ApiStatus_DONE2;
}

API_CALLABLE(UpdateRecords) {
    JumpGameData* data = (JumpGameData*)get_enemy(SCOREKEEPER_ENEMY_IDX)->varTable[JUMP_DATA_VAR_IDX];
    PlayerData* player = &gPlayerData;

    player->jumpGameTotal += data->curScore;
    if (player->jumpGameTotal > 99999) {
        player->jumpGameTotal = 99999;
    }
    if (player->jumpGameRecord < data->curScore) {
        player->jumpGameRecord = data->curScore;
    }
    set_message_int_var(data->curScore, 0);

    return ApiStatus_DONE2;
}

API_CALLABLE(GiveCoinWinnings) {
    JumpGameData* data = (JumpGameData*)get_enemy(SCOREKEEPER_ENEMY_IDX)->varTable[JUMP_DATA_VAR_IDX];
    s32 coinsLeft = data->curScore;
    s32 increment;

    if (coinsLeft > 100) {
        increment = 40;
    } else if (coinsLeft > 75) {
        increment = 35;
    } else if (coinsLeft > 50) {
        increment = 30;
    } else if (coinsLeft > 30) {
        increment = 10;
    } else if (coinsLeft > 20) {
        increment = 5;
    } else if (coinsLeft > 10) {
        increment = 2;
    } else {
        increment = 1;
    }

    data->curScore -= increment;
    add_coins(increment);
    data->targetScore = data->curScore;
    sfx_play_sound(SOUND_COIN_PICKUP);

    if (data->curScore > 0) {
        return ApiStatus_BLOCK;
    } else {
        return ApiStatus_DONE2;
    }
}

API_CALLABLE(DoubleScore) {
    JumpGameData* data = (JumpGameData*)get_enemy(SCOREKEEPER_ENEMY_IDX)->varTable[JUMP_DATA_VAR_IDX];
    s32 score = 2 * data->curScore;
    data->curScore = score;
    data->targetScore = score;

    return ApiStatus_DONE2;
}

API_CALLABLE(EndBowserPanelAnimation) {
    JumpGameData* data = (JumpGameData*)get_enemy(SCOREKEEPER_ENEMY_IDX)->varTable[JUMP_DATA_VAR_IDX];
    s32 i;

    for (i = 0; i < ARRAY_COUNT(data->panels); i++) {
        if (data->panels[i].type == PANEL_BOWSER && data->panels[i].state == PANEL_STATE_DONE)
            break;
    }

    data->panels[i].curPos.x = TallyPosX[data->panels[i].tallyPosIndex];
    data->panels[i].curPos.y = TallyPosY[data->panels[i].tallyPosIndex];
    data->panels[i].curPos.z = 110.0f;

    evt_set_variable(script, LVar1, data->panels[i].modelID);
    evt_set_float_variable(script, LVar5, data->panels[i].curPos.x);
    evt_set_float_variable(script, LVar6, data->panels[i].curPos.y);
    evt_set_float_variable(script, LVar7, data->panels[i].curPos.z);

    return ApiStatus_DONE2;
}

API_CALLABLE(GetPanelPos) {
    JumpGameData* data = (JumpGameData*)get_enemy(SCOREKEEPER_ENEMY_IDX)->varTable[JUMP_DATA_VAR_IDX];
    Bytecode* args = script->ptrReadPos;
    s32 index = evt_get_variable(script, *args++);

    evt_set_float_variable(script, LVar5, data->panels[index].curPos.x);
    evt_set_float_variable(script, LVar6, data->panels[index].curPos.y);
    evt_set_float_variable(script, LVar7, data->panels[index].curPos.z);
    evt_set_float_variable(script, LVar8, data->panels[index].curAngle);
    evt_set_float_variable(script, LVar9, data->panels[index].curScale);

    return ApiStatus_DONE2;
}

API_CALLABLE(DestroyBlockEntities) {
    JumpGameData* data = (JumpGameData*)get_enemy(SCOREKEEPER_ENEMY_IDX)->varTable[JUMP_DATA_VAR_IDX];
    s32 i;

    for (i = 0; i < ARRAY_COUNT(data->panels); i++) {
        if (data->panels[i].entityIndex >= 0) {
            fx_walking_dust(1, BlockPosX[i], BlockPosY[i] + 13, BlockPosZ[i] + 5, 0, 0);
            delete_entity(data->panels[i].entityIndex);
        }
    }

    sfx_play_sound_with_params(SOUND_KOOPER_SHELL_KICK, 0x50, 0, 0);

    return ApiStatus_DONE2;
}

API_CALLABLE(OnBreakBlock) {
    Enemy* scorekeeper = get_enemy(SCOREKEEPER_ENEMY_IDX);
    JumpGameData* data = (JumpGameData*)scorekeeper->varTable[JUMP_DATA_VAR_IDX];
    Bytecode* args = script->ptrReadPos;
    s32 index = evt_get_variable(script, *args++);
    s32 blockType = data->type[index];
    s32 historyPos = scorekeeper->varTable[BROKEN_BLOCKS_VAR_IDX];
    s32 coins = 0;
    s32 i;

    data->breakHistory[historyPos] = blockType;
    data->panels[index].entityIndex = -1;

    for (i = 0; i < historyPos + 1; i++) {
        switch (data->breakHistory[i]) {
            case PANEL_1_COIN:  coins += 1; break;
            case PANEL_5_COINS: coins += 5; break;
            case PANEL_TIMES_5: coins *= 5; break;
            case PANEL_BOWSER:  sfx_play_sound(SOUND_MENU_ERROR); coins = 0; break;
        }
    }

    data->targetScore = coins;

    for (i = 0; i < ARRAY_COUNT(data->panels); i++) {
        if (blockType == data->panels[i].type && data->panels[i].state == PANEL_STATE_START_ANIM) {
                data->panels[i].state = PANEL_STATE_EMERGE_INIT;
                data->panels[i].blockPosIndex = index;
                data->panels[i].tallyPosIndex = historyPos;
                break;
        }
    }

    scorekeeper->varTable[BROKEN_BLOCKS_VAR_IDX]++;

    return ApiStatus_DONE2;
}

API_CALLABLE(CreateBlockEntities) {
    JumpGameData* data = get_enemy(SCOREKEEPER_ENEMY_IDX)->varTablePtr[JUMP_DATA_VAR_IDX];
    s32 entityIndex;
    s32 initialConfiguration;
    s32 indexA, indexB;
    s32 curBlockIdx;
    s32 temp;
    s32 i;

    EvtScript* scriptArray[] = {
        &EVS_OnBreakBlock_0, &EVS_OnBreakBlock_1, &EVS_OnBreakBlock_2, &EVS_OnBreakBlock_3,
        &EVS_OnBreakBlock_4, &EVS_OnBreakBlock_5, &EVS_OnBreakBlock_6, &EVS_OnBreakBlock_7,
        &EVS_OnBreakBlock_8, &EVS_OnBreakBlock_9, &EVS_OnBreakBlock_10
    };

    if (isInitialCall) {
        // choose one of four initial configurations at random
        initialConfiguration = rand_int(1000) % ARRAY_COUNT(InitialConfigurations);
        for (i = 0; i < NUM_BLOCKS; i++) {
            data->type[i] = InitialConfigurations[initialConfiguration][i];
        }

        // randomly swap 1000 pairs
        for (i = 0; i < 1000; i++) {
            indexA = rand_int(10000) % NUM_BLOCKS;
            indexB = rand_int(10000) % NUM_BLOCKS;

            if (indexA != indexB) {
                temp = data->type[indexB];
                data->type[indexB] = data->type[indexA];
                data->type[indexA] = temp;
            }
        }

        script->functionTemp[0] = 0;
        script->functionTemp[1] = 0;
    }

    script->functionTemp[0]--;
    if (script->functionTemp[0] <= 0) {
        curBlockIdx = script->functionTemp[1];
        entityIndex = create_entity(&Entity_BrickBlock,
            BlockPosX[curBlockIdx],
            BlockPosY[curBlockIdx],
            BlockPosZ[curBlockIdx],
            0, 0, 0, 0, MAKE_ENTITY_END);
        data->panels[curBlockIdx].entityIndex = entityIndex;
        get_entity_by_index(entityIndex)->script.source = scriptArray[curBlockIdx];
        fx_sparkles(FX_SPARKLES_3,
            BlockPosX[curBlockIdx],
            BlockPosY[curBlockIdx] + 13,
            BlockPosZ[curBlockIdx] + 5,
            23.0f);
        sfx_play_sound(SOUND_HEART_PICKUP);
        script->functionTemp[0] = 3;
        script->functionTemp[1]++;
    }

    if (script->functionTemp[1] < NUM_BLOCKS) {
        return ApiStatus_BLOCK;
    } else {
        return ApiStatus_DONE2;
    }
}

API_CALLABLE(TakeCoinCost) {
    PlayerData* playerData = &gPlayerData;

    if (isInitialCall) {
        playerData->jumpGamePlays++;
        script->functionTemp[0] = 0;
    }
    add_coins(-1);
    sfx_play_sound(SOUND_COIN_PICKUP);

    script->functionTemp[0]++;

    if (script->functionTemp[0] == PLAY_COST) {
        return ApiStatus_DONE2;
    } else {
        return ApiStatus_BLOCK;
    }
}

API_CALLABLE(InitializePanels) {
    JumpGameData* data = get_enemy(SCOREKEEPER_ENEMY_IDX)->varTablePtr[JUMP_DATA_VAR_IDX];
    s32 i;

    data->curScore = 0;
    data->targetScore = 0;

    for (i = 0; i < ARRAY_COUNT(data->panels); i++) {
        data->panels[i].state = PANEL_STATE_INIT;
        data->panels[i].modelID = PanelModelIDs[i];
        data->panels[i].type = PanelTypes[i];
        data->panels[i].tallyPosIndex = -1;
    }

    return ApiStatus_DONE2;
}

API_CALLABLE(CreateMinigame) {
    Enemy* scorekeeper = get_enemy(SCOREKEEPER_ENEMY_IDX);
    JumpGameData* data = general_heap_malloc(sizeof(*data));
    HudElemID hid;

    scorekeeper->varTablePtr[JUMP_DATA_VAR_IDX] = data;
    data->workerID = create_worker_scene(nullptr, &worker_render_score);

    hid = hud_element_create(HES_StatusCoin);
    data->hudElemID = hid;
    hud_element_set_flags(data->hudElemID, HUD_ELEMENT_FLAG_MANUAL_RENDER);
    hud_element_set_tint(data->hudElemID, 255, 255, 255);

    data->scoreWindowPosX = SCREEN_WIDTH + 1;
    data->scoreWindowPosY = 28;
    status_bar_ignore_changes();
    close_status_bar();

    return ApiStatus_DONE2;
}

API_CALLABLE(DestroyMinigame) {
    JumpGameData* data = get_enemy(SCOREKEEPER_ENEMY_IDX)->varTablePtr[JUMP_DATA_VAR_IDX];

    free_worker(data->workerID);
    hud_element_free(data->hudElemID);

    return ApiStatus_DONE2;
}

API_CALLABLE(GetCoinCount) {
    evt_set_variable(script, LVarA, gPlayerData.coins);
    return ApiStatus_DONE2;
}

API_CALLABLE(SetMsgVars_BlocksRemaining) {
    Enemy* scorekeeper = get_enemy(SCOREKEEPER_ENEMY_IDX);
    s32 remaining = (scorekeeper->varTable[TOTAL_BLOCKS_VAR_IDX] - scorekeeper->varTable[BROKEN_BLOCKS_VAR_IDX]) + 1;

    set_message_int_var(remaining, 0);
#if VERSION_PAL
    evt_set_variable(script, LVarD, remaining);
#else
    set_message_text_var((remaining == 1) ? (s32)&MessageSingular : (s32)&MessagePlural, 1);
#endif

    return ApiStatus_DONE2;
}

API_CALLABLE(HideCoinCounter) {
    hide_coin_counter_immediately();
    return ApiStatus_DONE2;
}

#include "world/common/npc/Toad/idle.inc.c"

s8 BlockPosX[NUM_BLOCKS] = {
    -125, -100, -75, -50, -25, 0, 25, 50, 75, 100, 125
};

s8 BlockPosY[NUM_BLOCKS] = {
    56, 60, 56, 60, 56, 60, 56, 60, 56, 60, 56
};

s8 BlockPosZ[NUM_BLOCKS] = {
    30, -30, 30, -30, 30, -30, 30, -30, 30, -30, 30
};

f32 TallyPosX[NUM_BLOCKS] = {
    -105.0, -80.0, -55.0, -30.0, -5.0, -105.0, -80.0, -55.0,
    -30.0, -5.0, 20.0
};

f32 TallyPosY[NUM_BLOCKS] = {
    157.0, 157.0, 157.0, 157.0, 157.0, 133.0, 133.0, 133.0,
    133.0, 133.0, 133.0,
};

s32 PanelModelIDs[NUM_BLOCKS] = {
    19, 17, 15, 13, 22, 24, 26, 29,
    31, 34, 36
};

JumpGamePanelType PanelTypes[NUM_BLOCKS] = {
    PANEL_1_COIN, PANEL_1_COIN, PANEL_1_COIN, PANEL_1_COIN,
    PANEL_5_COINS, PANEL_5_COINS, PANEL_5_COINS,
    PANEL_TIMES_5, PANEL_TIMES_5,
    PANEL_BOWSER, PANEL_BOWSER
};

JumpGamePanelType InitialConfigurations[4][NUM_BLOCKS] = {
    { 0, 2, 0, 1, 3, 1, 0, 1, 0, 3, 2 },
    { 3, 0, 1, 2, 0, 2, 0, 1, 1, 3, 0 },
    { 1, 3, 0, 0, 1, 2, 3, 0, 1, 2, 0 },
    { 0, 0, 2, 1, 3, 3, 1, 1, 2, 0, 0 },
};

EvtScript EVS_ManageMinigame = {
    Label(0)
        Set(LVarA, 0)
        Set(LVarB, 0)
        Call(GetNpcVar, NPC_Toad, 4, LVarC)
        Loop(11)
            Call(GetPanelInfo, LVarA)
            Switch(LVar0)
                CaseEq(0)
                    Call(EnableModel, LVar1, false)
                    Call(SetPanelState, LVarA, 1)
                CaseEq(2)
                    Call(DisablePlayerInput, true)
                    Call(InitPanelEmergeFromBlock, LVarA)
                    Call(EnableModel, LVar1, true)
                    Call(SetPanelState, LVarA, 3)
                CaseEq(4)
                    IfNe(LVar2, 3)
                        IfLt(LVar3, LVarC)
                            Call(DisablePlayerInput, false)
                        EndIf
                    EndIf
                    Call(InitPanelHoldAboveBlock, LVarA)
                    Call(SetPanelState, LVarA, 5)
                CaseEq(6)
                    Call(InitPanelMoveToTally, LVarA)
                    Call(SetPanelState, LVarA, 7)
                CaseEq(8)
                    Call(EndPanelAnimation, LVarA)
                    Call(SetPanelState, LVarA, 9)
            EndSwitch
            Switch(LVar0)
                CaseEq(3)
                    Call(UpdatePanelEmergeFromBlock, LVarA)
                    IfEq(LVar3, 1)
                        Call(SetPanelState, LVarA, 4)
                    EndIf
                CaseEq(5)
                    Call(UpdatetPanelHoldAboveBlock, LVarA)
                    IfEq(LVar3, 1)
                        Call(SetPanelState, LVarA, 6)
                    EndIf
                CaseEq(7)
                    Call(UpdatePanelMoveToTally, LVarA)
                    IfEq(LVar3, 1)
                        Call(SetPanelState, LVarA, 8)
                    EndIf
                CaseEq(9)
                    IfEq(LVar2, 3)
                        Set(LVarB, 1)
                    Else
                        IfEq(LVar3, LVarC)
                            Set(LVarB, 2)
                        EndIf
                    EndIf
            EndSwitch
            IfGe(LVar0, 2)
                Call(GetPanelPos, LVarA)
                Call(TranslateModel, LVar1, LVar5, LVar6, LVar7)
                Call(RotateModel, LVar1, LVar8, Float(0.0), Float(1.0), Float(0.0))
                Call(ScaleModel, LVar1, LVar9, LVar9, Float(1.0))
            EndIf
            Add(LVarA, 1)
        EndLoop
        IfNe(LVarB, 0)
            Goto(99)
        EndIf
        Wait(1)
        Goto(0)
    Label(99)
    Call(EnableMenus)
    Thread
        Wait(15)
        Call(PopSong)
    EndThread
    Switch(LVarB)
        CaseEq(1)
            Call(PlaySoundWithVolume, SOUND_BOMBETTE_BLAST_LV2, 0)
            Wait(10)
            Call(PlaySoundWithVolume, SOUND_BOMBETTE_BLAST_LV2, 0)
            Wait(10)
            Call(EndBowserPanelAnimation)
            Call(TranslateModel, LVar1, LVar5, LVar6, LVar7)
            Wait(15)
            Call(SpeakToPlayer, NPC_Toad, ANIM_Toad_Red_Talk, ANIM_Toad_Red_Idle, 0, MSG_MGM_0034)
        CaseEq(2)
            Switch(LVarC)
                CaseEq(4)
                    Call(UpdateRecords)
                    Call(SpeakToPlayer, NPC_Toad, ANIM_Toad_Red_Talk, ANIM_Toad_Red_Idle, 0, MSG_MGM_0035)
                CaseEq(6)
                    Call(UpdateRecords)
                    Call(SpeakToPlayer, NPC_Toad, ANIM_Toad_Red_Talk, ANIM_Toad_Red_Idle, 0, MSG_MGM_0036)
                CaseEq(8)
                    Call(SpeakToPlayer, NPC_Toad, ANIM_Toad_Red_Talk, ANIM_Toad_Red_Idle, 0, MSG_MGM_0037)
                    Call(DoubleScore)
                    Call(PlaySoundWithVolume, SOUND_LUCKY, 0)
                    Wait(30)
                    Call(UpdateRecords)
                    Call(SpeakToPlayer, NPC_Toad, ANIM_Toad_Red_Talk, ANIM_Toad_Red_Idle, 0, MSG_MGM_0038)
            EndSwitch
            Call(ShowCoinCounter, true)
            Wait(10)
            Call(GiveCoinWinnings)
            Wait(15)
            Call(ShowCoinCounter, false)
            Wait(5)
            Call(SpeakToPlayer, NPC_Toad, ANIM_Toad_Red_Talk, ANIM_Toad_Red_Idle, 0, MSG_MGM_003A)
    EndSwitch
    Wait(10)
    Call(DestroyBlockEntities)
    Exec(EVS_InitializePanels)
    Wait(1)
    Call(DisablePlayerInput, false)
    Goto(0)
    Return
    End
};

EvtScript EVS_OnBreakBlock_0 = {
    Call(OnBreakBlock, 0)
    Return
    End
};

EvtScript EVS_OnBreakBlock_1 = {
    Call(OnBreakBlock, 1)
    Return
    End
};

EvtScript EVS_OnBreakBlock_2 = {
    Call(OnBreakBlock, 2)
    Return
    End
};

EvtScript EVS_OnBreakBlock_3 = {
    Call(OnBreakBlock, 3)
    Return
    End
};

EvtScript EVS_OnBreakBlock_4 = {
    Call(OnBreakBlock, 4)
    Return
    End
};

EvtScript EVS_OnBreakBlock_5 = {
    Call(OnBreakBlock, 5)
    Return
    End
};

EvtScript EVS_OnBreakBlock_6 = {
    Call(OnBreakBlock, 6)
    Return
    End
};

EvtScript EVS_OnBreakBlock_7 = {
    Call(OnBreakBlock, 7)
    Return
    End
};

EvtScript EVS_OnBreakBlock_8 = {
    Call(OnBreakBlock, 8)
    Return
    End
};

EvtScript EVS_OnBreakBlock_9 = {
    Call(OnBreakBlock, 9)
    Return
    End
};

EvtScript EVS_OnBreakBlock_10 = {
    Call(OnBreakBlock, 10)
    Return
    End
};

EvtScript EVS_InitializePanels = {
    Call(SetNpcVar, NPC_Toad, 2, -1)
    Call(InitializePanels)
    Return
    End
};

EvtScript EVS_802424A4 = {
    Call(CreateMinigame)
    Exec(EVS_InitializePanels)
    Exec(EVS_ManageMinigame)
    Return
    End
};

EvtScript EVS_DestroyMinigame = {
    Call(DestroyMinigame)
    Return
    End
};

EvtScript EVS_NpcInteract_Toad = {
    Call(GetSelfVar, 1, LVar0)
    IfEq(LVar0, 0)
        Call(SetSelfVar, 1, 1)
    EndIf
    Call(GetSelfVar, 2, LVar0)
    IfEq(LVar0, -1)
        IfEq(GF_MGM_Met_JumpAttack, false)
            Call(SetMsgImgs_Panels)
            Call(SpeakToPlayer, NPC_Toad, ANIM_Toad_Red_Talk, ANIM_Toad_Red_Idle, 0, MSG_MGM_002D)
            Set(GF_MGM_Met_JumpAttack, true)
        Else
            Call(SpeakToPlayer, NPC_Toad, ANIM_Toad_Red_Talk, ANIM_Toad_Red_Idle, 0, MSG_MGM_002E)
        EndIf
        Call(ShowCoinCounter, true)
        Call(GetCoinCount)
        IfLt(LVarA, 10)
            Call(ContinueSpeech, NPC_Toad, ANIM_Toad_Red_Talk, ANIM_Toad_Red_Idle, 0, MSG_MGM_0039)
            Call(HideCoinCounter)
            Wait(12)
            Exec(EVS_DestroyMinigame)
            Call(GotoMap, Ref("mgm_00"), mgm_00_ENTRY_1)
            Wait(100)
            Return
        EndIf
        Call(ShowChoice, MSG_Choice_004E)
        IfEq(LVar0, 3)
            Call(HideCoinCounter)
            Wait(5)
            Call(ContinueSpeech, NPC_Toad, ANIM_Toad_Red_Talk, ANIM_Toad_Red_Idle, 0, MSG_MGM_0032)
            Exec(EVS_DestroyMinigame)
            Call(GotoMap, Ref("mgm_00"), mgm_00_ENTRY_1)
            Wait(100)
            Return
        EndIf
        Call(GetSelfVar, 6, LVar1)
        IfLt(LVar1, 100)
            Add(LVar1, 1)
            Call(SetSelfVar, 6, LVar1)
        EndIf
        Thread
            Call(TakeCoinCost)
        EndThread
        Switch(LVar0)
            CaseEq(0)
                Call(SetNpcVar, NPC_Toad, 4, 4)
                Call(ContinueSpeech, NPC_Toad, ANIM_Toad_Red_Talk, ANIM_Toad_Red_Idle, 0, MSG_MGM_002F)
            CaseEq(1)
                Call(SetNpcVar, NPC_Toad, 4, 6)
                Call(ContinueSpeech, NPC_Toad, ANIM_Toad_Red_Talk, ANIM_Toad_Red_Idle, 0, MSG_MGM_0030)
            CaseEq(2)
                Call(SetNpcVar, NPC_Toad, 4, 8)
                Call(ContinueSpeech, NPC_Toad, ANIM_Toad_Red_Talk, ANIM_Toad_Red_Idle, 0, MSG_MGM_0031)
            CaseEq(3)
        EndSwitch
        Call(HideCoinCounter)
        Call(EndSpeech, NPC_Toad, ANIM_Toad_Red_Talk, ANIM_Toad_Red_Idle, 5)
        Wait(5)
        Call(CreateBlockEntities)
        Wait(10)
        Call(EndSpeech, NPC_Toad, ANIM_Toad_Red_Talk, ANIM_Toad_Red_Idle, 5)
        Call(PushSong, SONG_PLAYROOM, 0)
        Wait(10)
        Call(EndSpeech, NPC_Toad, ANIM_Toad_Red_Talk, ANIM_Toad_Red_Idle, 5)
        Call(DisableMenus)
        Call(SetNpcVar, NPC_Toad, 3, -1)
        Call(SetNpcVar, NPC_Toad, 2, 0)
        Wait(1)
    Else
        Call(SetMsgVars_BlocksRemaining)
#if VERSION_PAL
        IfEq(LocalVar(13), 1)
            Call(SpeakToPlayer, 0, ANIM_Toad_Red_Talk, ANIM_Toad_Red_Idle, 0, MSG_PAL_MGM_0036)
        Else
            Call(SpeakToPlayer, 0, ANIM_Toad_Red_Talk, ANIM_Toad_Red_Idle, 0, MSG_MGM_0033)
        EndIf
#else
        Call(SpeakToPlayer, NPC_Toad, ANIM_Toad_Red_Talk, ANIM_Toad_Red_Idle, 0, MSG_MGM_0033)
#endif
    EndIf
    Return
    End
};

EvtScript EVS_NpcInit_Toad = {
    Call(SetNpcPos, NPC_SELF, 75, -1, 100)
    Call(InterpNpcYaw, NPC_SELF, 270, 0)
    Call(SetNpcVar, NPC_Toad, 2, -1)
    Call(SetNpcVar, NPC_Toad, 1, 0)
    Call(SetNpcVar, NPC_Toad, 6, 0)
    Call(BindNpcInteract, NPC_SELF, Ref(EVS_NpcInteract_Toad))
    Return
    End
};

NpcData NpcData_Toad = {
    .id = NPC_Toad,
    .pos = { 0.0f, 0.0f, -20.0f },
    .yaw = 270,
    .init = &EVS_NpcInit_Toad,
    .settings = &NpcSettings_Toad,
    .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = NO_DROPS,
    .animations = TOAD_RED_ANIMS,
    .tattle = MSG_NpcTattle_MGM_JumpAttackGuide,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Toad),
    {}
};
