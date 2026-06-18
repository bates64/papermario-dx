#include "obk_04.h"

enum {
    RING_STATE_INIT                 = 0,
    RING_STATE_BOO_FLY_DELAY        = 1,
    RING_STATE_BOO_FLY_TO_RING      = 2,
    RING_STATE_DESCEND_DELAY        = 10,
    RING_STATE_DESCEND              = 11,
    RING_STATE_CLOCKWISE            = 12,
    RING_STATE_COUNTER_CLOCKWISE    = 13,
    RING_STATE_SPIRAL_IN            = 14,
    RING_STATE_SPIRAL_OUT           = 15,
    RING_STATE_STOPPED              = 100,
};

#include "world/common/npc/Boo/idle.inc.c"

API_CALLABLE(N(InitHiddenBoo)) {
    Npc* npc = get_npc_unsafe(script->owner2.npcID);
    npc->userData.keepAwayData = heap_malloc(sizeof(s32));
    npc->userData.keepAwayData->isStarted = false;

    npc->planarFlyDist = 125.0f; // default ring radius
    npc->yaw = 0.0f;
    npc->pos.x = 0.0f;
    npc->pos.y = -875.0f;
    npc->pos.z = 0.0f;
    npc->duration = 60;
    script->functionTemp[1] = RING_STATE_INIT;
    return ApiStatus_DONE2;
}

// change render mode of Boos as they pass behind the leader.
// swapping their render mode like this is a workaround to get them properly z-sorted.
void N(ApplyRingBooRenderHack)(Npc* npc) {
    if (npc->yaw > 340.0f || npc->yaw < 20.0f) {
        // behind the leader
        npc->renderMode = RENDER_MODE_ALPHATEST;
        npc->imgfxFlags = 0;
        npc_set_imgfx_params(npc, IMGFX_CLEAR, 0, 0, 0, 0, 0);
    } else {
        npc->renderMode = RENDER_MODE_SURFACE_XLU_LAYER2;
        npc_set_imgfx_params(npc, IMGFX_SET_ALPHA, gPlayerStatusPtr->curAlpha, 255, 0, 0, npc->imgfxFlags);
        npc->imgfxArg1 = 255;
    }
}

void N(ApplyBooRenderHacks)(void) {
    N(ApplyRingBooRenderHack)(get_npc_unsafe(NPC_KeepAwayBoo1));
    N(ApplyRingBooRenderHack)(get_npc_unsafe(NPC_KeepAwayBoo2));
    N(ApplyRingBooRenderHack)(get_npc_unsafe(NPC_KeepAwayBoo3));
    N(ApplyRingBooRenderHack)(get_npc_unsafe(NPC_KeepAwayBoo4));
    N(ApplyRingBooRenderHack)(get_npc_unsafe(NPC_KeepAwayBoo5));
    N(ApplyRingBooRenderHack)(get_npc_unsafe(NPC_KeepAwayBoo6));
    N(ApplyRingBooRenderHack)(get_npc_unsafe(NPC_KeepAwayBoo7));
    N(ApplyRingBooRenderHack)(get_npc_unsafe(NPC_KeepAwayBoo8));
}

void N(ClearBooRenderHacks)(void) {
    get_npc_unsafe(NPC_KeepAwayBoo1)->imgfxFlags = 0;
    get_npc_unsafe(NPC_KeepAwayBoo2)->imgfxFlags = 0;
    get_npc_unsafe(NPC_KeepAwayBoo3)->imgfxFlags = 0;
    get_npc_unsafe(NPC_KeepAwayBoo4)->imgfxFlags = 0;
    get_npc_unsafe(NPC_KeepAwayBoo5)->imgfxFlags = 0;
    get_npc_unsafe(NPC_KeepAwayBoo6)->imgfxFlags = 0;
    get_npc_unsafe(NPC_KeepAwayBoo7)->imgfxFlags = 0;
    get_npc_unsafe(NPC_KeepAwayBoo8)->imgfxFlags = 0;
}

s32 N(SetRingMovement)(s32 prev) {
    s32 ret = RING_STATE_CLOCKWISE;

    switch (prev) {
        case KEEP_AWAY_CLOCKWISE:
            ret = RING_STATE_CLOCKWISE;
            break;
        case KEEP_AWAY_STOP:
            ret = RING_STATE_STOPPED;
            break;
        case KEEP_AWAY_COUNTER_CLOCKWISE:
            ret = RING_STATE_COUNTER_CLOCKWISE;
            break;
        case KEEP_AWAY_SPIRAL:
            ret = RING_STATE_SPIRAL_IN;
            break;
    }
    return ret;
}

API_CALLABLE(N(UpdateHiddenBoo)) {
    Npc* hiddenBoo = get_npc_unsafe(script->owner2.npcID);

    switch (script->functionTemp[1]) {
        case RING_STATE_INIT:
            if (evt_get_variable(script, MV_KeepAwayStarted)) {
                hiddenBoo->userData.keepAwayData->isStarted = true;
                script->functionTemp[1] = RING_STATE_DESCEND_DELAY;
            }
            break;
        case RING_STATE_BOO_FLY_DELAY:
            break;
        case RING_STATE_DESCEND_DELAY:
            hiddenBoo->yaw = clamp_angle(hiddenBoo->yaw + 2.0f);
            hiddenBoo->duration--;
            if (hiddenBoo->duration == 0) {
                script->functionTemp[1] = RING_STATE_DESCEND;
            }
            break;
        case RING_STATE_DESCEND:
            if (hiddenBoo->pos.y <= -920.0f) {
                N(ApplyBooRenderHacks)();
            }
            hiddenBoo->yaw = clamp_angle(hiddenBoo->yaw + 2.0f);
            hiddenBoo->pos.y -= 0.5f;
            if (hiddenBoo->pos.y <= -988.0f) {
                evt_set_variable(script, MV_KeepAwayRingReady, true);
                N(ClearBooRenderHacks)();
                script->functionTemp[1] = RING_STATE_CLOCKWISE;
            }
            break;
        case RING_STATE_CLOCKWISE:
            script->functionTemp[1] = N(SetRingMovement)(evt_get_variable(script, MV_KeepAwayMovement));
            hiddenBoo->yaw = clamp_angle(hiddenBoo->yaw + 2.0f);
            break;
        case RING_STATE_COUNTER_CLOCKWISE:
            script->functionTemp[1] = N(SetRingMovement)(evt_get_variable(script, MV_KeepAwayMovement));
            hiddenBoo->yaw = clamp_angle(hiddenBoo->yaw - 2.0f);
            break;
        case RING_STATE_SPIRAL_IN:
            evt_set_variable(script, MV_KeepAwayMovement, KEEP_AWAY_CLOCKWISE);
            hiddenBoo->duration++;
            if (hiddenBoo->duration == 50) {
                script->functionTemp[1] = RING_STATE_SPIRAL_OUT;
            }
            hiddenBoo->planarFlyDist -= 2.0f;
            hiddenBoo->yaw = clamp_angle(hiddenBoo->yaw + 2.0f);
            break;
        case RING_STATE_SPIRAL_OUT:
            hiddenBoo->duration--;
            if (hiddenBoo->duration == 0) {
                script->functionTemp[1] = RING_STATE_CLOCKWISE;
            }
            hiddenBoo->planarFlyDist += 2.0f;
            hiddenBoo->yaw = clamp_angle(hiddenBoo->yaw + 2.0f);
            break;
        case RING_STATE_STOPPED:
            script->functionTemp[1] = N(SetRingMovement)(evt_get_variable(script, MV_KeepAwayMovement));
            break;
    }

    return ApiStatus_DONE2;
}

API_CALLABLE(N(InitKeepAwayBoo)) {
    Npc* leaderBoo = get_npc_unsafe(script->owner2.npcID);

    leaderBoo->userData.controlNpc = get_npc_unsafe(NPC_HiddenBoo);
    script->functionTemp[2] = script->owner2.npcID * 45; // starting yaw
    leaderBoo->flags |= NPC_FLAG_IGNORE_CAMERA_FOR_YAW;
    script->functionTemp[1] = RING_STATE_INIT;
    return ApiStatus_DONE2;
}

// the update script for one of the keep-away boos in the ring
API_CALLABLE(N(UpdateKeepAwayBoo)) {
    Npc* npc = get_npc_unsafe(script->owner2.npcID);
    Npc* controller = npc->userData.controlNpc;
    f32 posX, posY, posZ, yaw;
    f32 interpAlpha;

    switch (script->functionTemp[1]) {
        case RING_STATE_INIT:
            npc->yaw = clamp_angle(script->functionTemp[2] + controller->yaw);
            if (controller->userData.keepAwayData->isStarted) {
                script->functionTemp[1] = RING_STATE_BOO_FLY_DELAY;
                npc->duration = rand_int(20) + 10;
            }
            break;
        case RING_STATE_BOO_FLY_DELAY:
            yaw = clamp_angle(script->functionTemp[2] + controller->yaw);
            npc->yaw = yaw;
            npc->duration--;
            if (npc->duration == 0) {
                sfx_play_sound_at_position(SOUND_SEQ_BOO_VANISH, SOUND_SPACE_DEFAULT, npc->pos.x, npc->pos.y, npc->pos.z);
                script->functionTemp[1] = RING_STATE_BOO_FLY_TO_RING;
                npc->duration = 0;
                npc->moveToPos.x = npc->pos.x;
                npc->moveToPos.y = npc->pos.y;
                npc->moveToPos.z = npc->pos.z;
            }
            break;
        case RING_STATE_BOO_FLY_TO_RING:
            // here `moveToPos` is original position
            yaw = clamp_angle(script->functionTemp[2] + controller->yaw);
            npc->yaw = yaw;
            npc->pos.x = controller->pos.x;
            npc->pos.z = controller->pos.z;
            npc_move_heading(npc, controller->planarFlyDist, yaw);

            interpAlpha = (40.0f - npc->duration) / 40.0f;

            posX = npc->pos.x;
            posY = controller->pos.y - NPC_DISPOSE_POS_Y;
            posZ = npc->pos.z;

            npc->pos.x = posX - (posX - npc->moveToPos.x) * SQ(interpAlpha);
            npc->pos.y = posY - (posY - npc->moveToPos.y) * CUBE(interpAlpha);
            npc->pos.z = posZ - (posZ - npc->moveToPos.z) * SQ(interpAlpha);
            npc->duration++;
            if (npc->duration == 40) {
                script->functionTemp[1] = RING_STATE_CLOCKWISE;
            }
            break;
        // at this stage, the movement of the ring is controlled by MV_KeepAwayMovement
        case RING_STATE_CLOCKWISE:
        case RING_STATE_COUNTER_CLOCKWISE:
        case RING_STATE_SPIRAL_IN:
            yaw = clamp_angle(script->functionTemp[2] + controller->yaw);
            npc->yaw = yaw;
            script->functionTemp[1] = N(SetRingMovement)(evt_get_variable(script, MV_KeepAwayMovement));
            npc->pos.x = controller->pos.x;
            npc->pos.z = controller->pos.z;
            npc_move_heading(npc, controller->planarFlyDist, yaw);
            npc->pos.y = controller->pos.y - NPC_DISPOSE_POS_Y;
            break;
        case RING_STATE_STOPPED:
            script->functionTemp[1] = N(SetRingMovement)(evt_get_variable(script, MV_KeepAwayMovement));
            break;
    }

    return ApiStatus_DONE2;
}

EvtScript N(EVS_NpcIdle_HiddenBoo) = {
    Wait(4)
    Call(N(InitHiddenBoo))
    Label(10)
        Call(N(UpdateHiddenBoo))
        Wait(1)
        Goto(10)
    Return
    End
};

EvtScript N(EVS_NpcIdle_KeepAwayBoo) = {
    Wait(5)
    Call(N(InitKeepAwayBoo))
    Label(10)
        Call(N(UpdateKeepAwayBoo))
        Wait(1)
        Goto(10)
    Return
    End
};

EvtScript N(EVS_OnHit_KeepAwayBoo) = {
    IfEq(MV_ThrowTargetNpc, LVar0)
        Set(MV_KeepAwayResult, KEEP_AWAY_RIGHT)
    Else
        Set(MV_KeepAwayResult, KEEP_AWAY_WRONG)
    EndIf
    Thread
        Call(SetNpcAnimation, NPC_SELF, ANIM_Boo_Cower)
        Wait(30)
        Call(SetNpcAnimation, NPC_SELF, ANIM_Boo_Idle)
    EndThread
    Return
    End
};

EvtScript N(EVS_NpcHit_KeepAwayBoo1) = {
    Call(GetOwnerEncounterTrigger, LVar0)
    Switch(LVar0)
        CaseEq(ENCOUNTER_TRIGGER_HAMMER)
            Set(LVar0, NPC_KeepAwayBoo1)
            ExecWait(N(EVS_OnHit_KeepAwayBoo))
        CaseEq(ENCOUNTER_TRIGGER_JUMP)
            Set(LVar0, NPC_KeepAwayBoo1)
            ExecWait(N(EVS_OnHit_KeepAwayBoo))
        EndCaseGroup
    EndSwitch
    Return
    End
};

EvtScript N(EVS_NpcHit_KeepAwayBoo2) = {
    Call(GetOwnerEncounterTrigger, LVar0)
    Switch(LVar0)
        CaseEq(ENCOUNTER_TRIGGER_HAMMER)
            Set(LVar0, NPC_KeepAwayBoo2)
            ExecWait(N(EVS_OnHit_KeepAwayBoo))
        CaseEq(ENCOUNTER_TRIGGER_JUMP)
            Set(LVar0, NPC_KeepAwayBoo2)
            ExecWait(N(EVS_OnHit_KeepAwayBoo))
        EndCaseGroup
    EndSwitch
    Return
    End
};

EvtScript N(EVS_NpcHit_KeepAwayBoo3) = {
    Call(GetOwnerEncounterTrigger, LVar0)
    Switch(LVar0)
        CaseEq(ENCOUNTER_TRIGGER_HAMMER)
            Set(LVar0, NPC_KeepAwayBoo3)
            ExecWait(N(EVS_OnHit_KeepAwayBoo))
        CaseEq(ENCOUNTER_TRIGGER_JUMP)
            Set(LVar0, NPC_KeepAwayBoo3)
            ExecWait(N(EVS_OnHit_KeepAwayBoo))
        EndCaseGroup
    EndSwitch
    Return
    End
};

EvtScript N(EVS_NpcHit_KeepAwayBoo4) = {
    Call(GetOwnerEncounterTrigger, LVar0)
    Switch(LVar0)
        CaseEq(ENCOUNTER_TRIGGER_HAMMER)
            Set(LVar0, NPC_KeepAwayBoo4)
            ExecWait(N(EVS_OnHit_KeepAwayBoo))
        CaseEq(ENCOUNTER_TRIGGER_JUMP)
            Set(LVar0, NPC_KeepAwayBoo4)
            ExecWait(N(EVS_OnHit_KeepAwayBoo))
        EndCaseGroup
    EndSwitch
    Return
    End
};

EvtScript N(EVS_NpcHit_KeepAwayBoo5) = {
    Call(GetOwnerEncounterTrigger, LVar0)
    Switch(LVar0)
        CaseEq(ENCOUNTER_TRIGGER_HAMMER)
            Set(LVar0, NPC_KeepAwayBoo5)
            ExecWait(N(EVS_OnHit_KeepAwayBoo))
        CaseEq(ENCOUNTER_TRIGGER_JUMP)
            Set(LVar0, NPC_KeepAwayBoo5)
            ExecWait(N(EVS_OnHit_KeepAwayBoo))
        EndCaseGroup
    EndSwitch
    Return
    End
};

EvtScript N(EVS_NpcHit_KeepAwayBoo6) = {
    Call(GetOwnerEncounterTrigger, LVar0)
    Switch(LVar0)
        CaseEq(ENCOUNTER_TRIGGER_HAMMER)
            Set(LVar0, NPC_KeepAwayBoo6)
            ExecWait(N(EVS_OnHit_KeepAwayBoo))
        CaseEq(ENCOUNTER_TRIGGER_JUMP)
            Set(LVar0, NPC_KeepAwayBoo6)
            ExecWait(N(EVS_OnHit_KeepAwayBoo))
        EndCaseGroup
    EndSwitch
    Return
    End
};

EvtScript N(EVS_NpcHit_KeepAwayBoo7) = {
    Call(GetOwnerEncounterTrigger, LVar0)
    Switch(LVar0)
        CaseEq(ENCOUNTER_TRIGGER_HAMMER)
            Set(LVar0, NPC_KeepAwayBoo7)
            ExecWait(N(EVS_OnHit_KeepAwayBoo))
        CaseEq(ENCOUNTER_TRIGGER_JUMP)
            Set(LVar0, NPC_KeepAwayBoo7)
            ExecWait(N(EVS_OnHit_KeepAwayBoo))
        EndCaseGroup
    EndSwitch
    Return
    End
};

EvtScript N(EVS_NpcHit_KeepAwayBoo8) = {
    Call(GetOwnerEncounterTrigger, LVar0)
    Switch(LVar0)
        CaseEq(ENCOUNTER_TRIGGER_HAMMER)
            Set(LVar0, NPC_KeepAwayBoo8)
            ExecWait(N(EVS_OnHit_KeepAwayBoo))
        CaseEq(ENCOUNTER_TRIGGER_JUMP)
            Set(LVar0, NPC_KeepAwayBoo8)
            ExecWait(N(EVS_OnHit_KeepAwayBoo))
        EndCaseGroup
    EndSwitch
    Return
    End
};

EvtScript N(EVS_NpcInit_HiddenBoo) = {
    Call(BindNpcIdle, NPC_SELF, Ref(N(EVS_NpcIdle_HiddenBoo)))
    IfGe(GB_StoryProgress, STORY_CH3_GOT_SUPER_BOOTS)
        Call(RemoveNpc, NPC_SELF)
    EndIf
    Return
    End
};

EvtScript N(EVS_NpcInit_KeepAwayBoo1) = {
    Call(BindNpcIdle, NPC_SELF, Ref(N(EVS_NpcIdle_KeepAwayBoo)))
    Call(BindNpcHit, NPC_SELF, Ref(N(EVS_NpcHit_KeepAwayBoo1)))
    IfGe(GB_StoryProgress, STORY_CH3_GOT_SUPER_BOOTS)
        Call(RemoveNpc, NPC_SELF)
    EndIf
    Return
    End
};

EvtScript N(EVS_NpcInit_KeepAwayBoo2) = {
    Call(BindNpcIdle, NPC_SELF, Ref(N(EVS_NpcIdle_KeepAwayBoo)))
    Call(BindNpcHit, NPC_SELF, Ref(N(EVS_NpcHit_KeepAwayBoo2)))
    IfGe(GB_StoryProgress, STORY_CH3_GOT_SUPER_BOOTS)
        Call(RemoveNpc, NPC_SELF)
    EndIf
    Return
    End
};

EvtScript N(EVS_NpcInit_KeepAwayBoo3) = {
    Call(BindNpcIdle, NPC_SELF, Ref(N(EVS_NpcIdle_KeepAwayBoo)))
    Call(BindNpcHit, NPC_SELF, Ref(N(EVS_NpcHit_KeepAwayBoo3)))
    IfGe(GB_StoryProgress, STORY_CH3_GOT_SUPER_BOOTS)
        Call(RemoveNpc, NPC_SELF)
    EndIf
    Return
    End
};

EvtScript N(EVS_NpcInit_KeepAwayBoo4) = {
    Call(BindNpcIdle, NPC_SELF, Ref(N(EVS_NpcIdle_KeepAwayBoo)))
    Call(BindNpcHit, NPC_SELF, Ref(N(EVS_NpcHit_KeepAwayBoo4)))
    IfGe(GB_StoryProgress, STORY_CH3_GOT_SUPER_BOOTS)
        Call(RemoveNpc, NPC_SELF)
    EndIf
    Return
    End
};

EvtScript N(EVS_NpcInit_KeepAwayBoo5) = {
    Call(BindNpcIdle, NPC_SELF, Ref(N(EVS_NpcIdle_KeepAwayBoo)))
    Call(BindNpcHit, NPC_SELF, Ref(N(EVS_NpcHit_KeepAwayBoo5)))
    IfGe(GB_StoryProgress, STORY_CH3_GOT_SUPER_BOOTS)
        Call(RemoveNpc, NPC_SELF)
    EndIf
    Return
    End
};

EvtScript N(EVS_NpcInit_KeepAwayBoo6) = {
    Call(BindNpcIdle, NPC_SELF, Ref(N(EVS_NpcIdle_KeepAwayBoo)))
    Call(BindNpcHit, NPC_SELF, Ref(N(EVS_NpcHit_KeepAwayBoo6)))
    IfGe(GB_StoryProgress, STORY_CH3_GOT_SUPER_BOOTS)
        Call(RemoveNpc, NPC_SELF)
    EndIf
    Return
    End
};

EvtScript N(EVS_NpcInit_KeepAwayBoo7) = {
    Call(BindNpcIdle, NPC_SELF, Ref(N(EVS_NpcIdle_KeepAwayBoo)))
    Call(BindNpcHit, NPC_SELF, Ref(N(EVS_NpcHit_KeepAwayBoo7)))
    IfGe(GB_StoryProgress, STORY_CH3_GOT_SUPER_BOOTS)
        Call(RemoveNpc, NPC_SELF)
    EndIf
    Return
    End
};

EvtScript N(EVS_NpcInit_KeepAwayBoo8) = {
    Call(BindNpcIdle, NPC_SELF, Ref(N(EVS_NpcIdle_KeepAwayBoo)))
    Call(BindNpcHit, NPC_SELF, Ref(N(EVS_NpcHit_KeepAwayBoo8)))
    IfGe(GB_StoryProgress, STORY_CH3_GOT_SUPER_BOOTS)
        Call(RemoveNpc, NPC_SELF)
    EndIf
    Return
    End
};

NpcData N(NpcData_HiddenBoo) = {
    .id = NPC_HiddenBoo,
    .pos = { NPC_DISPOSE_LOCATION },
    .yaw = 0,
    .init = &N(EVS_NpcInit_HiddenBoo),
    .settings = &N(NpcSettings_Boo),
    .flags = ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_SKIP_BATTLE | ENEMY_FLAG_ACTIVE_WHILE_OFFSCREEN | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_PARTNER,
    .drops = NO_DROPS,
    .animations = NORMAL_BOO_ANIMS,
};

NpcData N(NpcData_KeepAwayBoo1) = {
    .id = NPC_KeepAwayBoo1,
    .pos = { 176.0f, 0.0f, -173.0f },
    .yaw = 270,
    .init = &N(EVS_NpcInit_KeepAwayBoo1),
    .settings = &N(NpcSettings_Boo),
    .flags = ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_SKIP_BATTLE | ENEMY_FLAG_ACTIVE_WHILE_OFFSCREEN | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_PARTNER,
    .drops = NO_DROPS,
    .animations = NORMAL_BOO_ANIMS,
};

NpcData N(NpcData_KeepAwayBoo2) = {
    .id = NPC_KeepAwayBoo2,
    .pos = { 176.0f, 0.0f, -173.0f },
    .yaw = 270,
    .init = &N(EVS_NpcInit_KeepAwayBoo2),
    .settings = &N(NpcSettings_Boo),
    .flags = ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_SKIP_BATTLE | ENEMY_FLAG_ACTIVE_WHILE_OFFSCREEN | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_PARTNER,
    .drops = NO_DROPS,
    .animations = NORMAL_BOO_ANIMS,
};

NpcData N(NpcData_KeepAwayBoo3) = {
    .id = NPC_KeepAwayBoo3,
    .pos = { 176.0f, 0.0f, -173.0f },
    .yaw = 270,
    .init = &N(EVS_NpcInit_KeepAwayBoo3),
    .settings = &N(NpcSettings_Boo),
    .flags = ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_SKIP_BATTLE | ENEMY_FLAG_ACTIVE_WHILE_OFFSCREEN | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_PARTNER,
    .drops = NO_DROPS,
    .animations = NORMAL_BOO_ANIMS,
};

NpcData N(NpcData_KeepAwayBoo4) = {
    .id = NPC_KeepAwayBoo4,
    .pos = { 176.0f, 0.0f, -173.0f },
    .yaw = 270,
    .init = &N(EVS_NpcInit_KeepAwayBoo4),
    .settings = &N(NpcSettings_Boo),
    .flags = ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_SKIP_BATTLE | ENEMY_FLAG_ACTIVE_WHILE_OFFSCREEN | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_PARTNER,
    .drops = NO_DROPS,
    .animations = NORMAL_BOO_ANIMS,
};

NpcData N(NpcData_KeepAwayBoo5) = {
    .id = NPC_KeepAwayBoo5,
    .pos = { 176.0f, 0.0f, -173.0f },
    .yaw = 270,
    .init = &N(EVS_NpcInit_KeepAwayBoo5),
    .settings = &N(NpcSettings_Boo),
    .flags = ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_SKIP_BATTLE | ENEMY_FLAG_ACTIVE_WHILE_OFFSCREEN | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_PARTNER,
    .drops = NO_DROPS,
    .animations = NORMAL_BOO_ANIMS,
};

NpcData N(NpcData_KeepAwayBoo6) = {
    .id = NPC_KeepAwayBoo6,
    .pos = { 176.0f, 0.0f, -173.0f },
    .yaw = 270,
    .init = &N(EVS_NpcInit_KeepAwayBoo6),
    .settings = &N(NpcSettings_Boo),
    .flags = ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_SKIP_BATTLE | ENEMY_FLAG_ACTIVE_WHILE_OFFSCREEN | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_PARTNER,
    .drops = NO_DROPS,
    .animations = NORMAL_BOO_ANIMS,
};

NpcData N(NpcData_KeepAwayBoo7) = {
    .id = NPC_KeepAwayBoo7,
    .pos = { 176.0f, 0.0f, -173.0f },
    .yaw = 270,
    .init = &N(EVS_NpcInit_KeepAwayBoo7),
    .settings = &N(NpcSettings_Boo),
    .flags = ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_SKIP_BATTLE | ENEMY_FLAG_ACTIVE_WHILE_OFFSCREEN | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_PARTNER,
    .drops = NO_DROPS,
    .animations = NORMAL_BOO_ANIMS,
};

NpcData N(NpcData_KeepAwayBoo8) = {
    .id = NPC_KeepAwayBoo8,
    .pos = { 176.0f, 0.0f, -173.0f },
    .yaw = 270,
    .init = &N(EVS_NpcInit_KeepAwayBoo8),
    .settings = &N(NpcSettings_Boo),
    .flags = ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_SKIP_BATTLE | ENEMY_FLAG_ACTIVE_WHILE_OFFSCREEN | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_PARTNER,
    .drops = NO_DROPS,
    .animations = NORMAL_BOO_ANIMS,
};

EvtScript N(EVS_NpcInit_Boo_10) = {
    Return
    End
};

EvtScript N(EVS_NpcInit_Boo_11) = {
    Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_HAS_SHADOW, true)
    Return
    End
};

EvtScript N(EVS_NpcInteract_TutorialBoo) = {
    IfEq(GF_OBK04_HiddenPanel, false)
        Call(SpeakToPlayer, NPC_TutorialBoo, ANIM_Boo_Talk, ANIM_Boo_Idle, 0, MSG_CH3_003F)
    Else
        IfEq(GF_OBK04_HeardAboutHiddenPanels, false)
            Call(SpeakToPlayer, NPC_TutorialBoo, ANIM_Boo_Talk, ANIM_Boo_Idle, 0, MSG_CH3_0040)
            Set(GF_OBK04_HeardAboutHiddenPanels, true)
        Else
            Call(SpeakToPlayer, NPC_TutorialBoo, ANIM_Boo_Talk, ANIM_Boo_Idle, 0, MSG_CH3_0041)
        EndIf
    EndIf
    Return
    End
};

EvtScript N(EVS_NpcInit_TutorialBoo) = {
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_TutorialBoo)))
    IfGe(GB_StoryProgress, STORY_CH3_GOT_SUPER_BOOTS)
        Call(SetNpcPos, NPC_TutorialBoo, -160, 10, -175)
    EndIf
    Return
    End
};

NpcData N(NpcData_KeepAwayExtras)[] = {
    {
        .id = NPC_LeaderBoo,
        .pos = { NPC_DISPOSE_LOCATION },
        .yaw = 270,
        .init = &N(EVS_NpcInit_Boo_10),
        .settings = &N(NpcSettings_Boo),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION,
        .drops = NO_DROPS,
        .animations = NORMAL_BOO_ANIMS,
    },
    {
        .id = NPC_DummyBoo,
        .pos = { NPC_DISPOSE_LOCATION },
        .yaw = 0,
        .init = &N(EVS_NpcInit_Boo_11),
        .settings = &N(NpcSettings_Boo),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_HAS_NO_SPRITE,
        .drops = NO_DROPS,
        .animations = NORMAL_BOO_ANIMS,
    },
};

NpcData N(NpcData_TutorialBoo) = {
    .id = NPC_TutorialBoo,
    .pos = { NPC_DISPOSE_LOCATION },
    .yaw = 0,
    .init = &N(EVS_NpcInit_TutorialBoo),
    .settings = &N(NpcSettings_Boo),
    .flags = BASE_PASSIVE_FLAGS,
    .drops = NO_DROPS,
    .animations = NORMAL_BOO_ANIMS,
    .tattle = MSG_NpcTattle_OBK_BootsTutor,
};

NpcGroupList N(DefaultNPCs) = {
    NPC_GROUP(N(NpcData_HiddenBoo)),
    NPC_GROUP(N(NpcData_KeepAwayBoo1)),
    NPC_GROUP(N(NpcData_KeepAwayBoo2)),
    NPC_GROUP(N(NpcData_KeepAwayBoo3)),
    NPC_GROUP(N(NpcData_KeepAwayBoo4)),
    NPC_GROUP(N(NpcData_KeepAwayBoo5)),
    NPC_GROUP(N(NpcData_KeepAwayBoo6)),
    NPC_GROUP(N(NpcData_KeepAwayBoo7)),
    NPC_GROUP(N(NpcData_KeepAwayBoo8)),
    NPC_GROUP(N(NpcData_KeepAwayExtras)),
    NPC_GROUP(N(NpcData_TutorialBoo)),
    {}
};
