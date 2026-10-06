#include "end_01.h"
#include "effects.h"

extern HeapNode heap_spriteHead;

extern b32 SpriteUseGeneralHeap;
extern ParadeNpcInfo ParadeNpcsTable[];

extern EvtScript EVS_ParadePhase_Wizards;
extern EvtScript EVS_ParadePhase_ShyGuyDancing;
extern EvtScript EVS_ParadePhase_ShyGuyFormation;
extern EvtScript EVS_ParadePhase_Toads1;
extern EvtScript EVS_ParadePhase_MarioPeach;
extern EvtScript EVS_ParadePhase_Toads2;
extern EvtScript EVS_MarioPeachExit;
extern EvtScript EVS_ParadePhase_StarSpirits;
extern EvtScript EVS_ParadePhase_SkatingPenguins;
extern EvtScript EVS_ParadePhase_Opera;
extern EvtScript EVS_ParadePhase_MayorPenguin;

extern EvtScript EVS_InitCredits;
extern EvtScript EVS_ShowCredits_Jobs;
extern EvtScript EVS_ShowCredits_Names;

API_CALLABLE(CreateParadeNPC) {
    Bytecode* args = script->ptrReadPos;
    s32 npcID = evt_get_variable(script, *args++);
    ParadeNpcInfo* npcInfo = &ParadeNpcsTable[npcID];
    NpcBlueprint bp;
    Npc* npc;

    bp.flags = NPC_FLAG_IGNORE_CHAR_COLLISION;
    bp.initialAnim = npcInfo->initialAnim;
    bp.onUpdate = nullptr;
    bp.onRender = nullptr;

    SpriteUseGeneralHeap = true;

    npc = get_npc_by_index(create_standard_npc(&bp, npcInfo->animList));
    npc->npcID = npcID;
    npc->flags &= ~NPC_FLAG_PARTNER;
    npc->pos.x = npcInfo->pos.x;
    npc->pos.y = npcInfo->pos.y;
    npc->pos.z = npcInfo->pos.z;
    set_npc_yaw(npc, npcInfo->yaw);
    return ApiStatus_DONE2;
}

API_CALLABLE(ParadeSpriteHeapMalloc) {
    Bytecode* args = script->ptrReadPos;
    s32 heapSize = evt_get_variable(script, *args++);
    s32 outVar = *args++;

    evt_set_variable(script, outVar, (s32) _heap_malloc(&heap_spriteHead, heapSize));
    return ApiStatus_DONE2;
}

API_CALLABLE(ParadeSpriteHeapFree) {
    Bytecode* args = script->ptrReadPos;
    s32 pointer = *args++;

    _heap_free(&heap_spriteHead, (void*) evt_get_variable(script, pointer));
    return ApiStatus_DONE2;
}

API_CALLABLE(UpdateCameraScroll) {
    Camera* camera = &gCameras[gCurrentCameraID];

    camera->panActive = true;
    camera->movePos.x += PARADE_SCROLL_RATE / DT;
    return ApiStatus_DONE2;
}

API_CALLABLE(AddScrollToNpcPos) {
    Bytecode* args = script->ptrReadPos;
    Npc** npc = (Npc**)&script->functionTempPtr[1];

    if (isInitialCall) {
        *npc = get_npc_unsafe(evt_get_variable(script, *args++));
    }

    (*npc)->pos.x += PARADE_SCROLL_RATE / DT;

    return ApiStatus_BLOCK;
}

// unused
API_CALLABLE(WaitForConfirmInput) {
    if (gGameStatusPtr->pressedButtons[0] & (BUTTON_A | BUTTON_START)) {
        return ApiStatus_DONE2;
    } else {
        return ApiStatus_BLOCK;
    }
}

EvtScript EVS_SetupInitialCamera = {
    Call(UseSettingsFrom, CAM_DEFAULT, PARADE_START, 0, 0)
    Call(SetPanTarget, CAM_DEFAULT, PARADE_START, 0, 0)
    Call(SetCamSpeed, CAM_DEFAULT, Float(90.0))
    Call(PanToTarget, CAM_DEFAULT, 0, true)
    Return
    End
};

EvtScript EVS_UpdateScrollPos = {
    Call(SetPanTarget, CAM_DEFAULT, Float(PARADE_START), 0, 0)
    SetF(LVar1, Float(0.0))
    Loop(0)
        Call(UpdateCameraScroll)
        Call(TranslateGroup, MODEL_bg, LVar1, 0, 0)
        AddF(LVar1, Float(PARADE_SCROLL_RATE / DT))
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript EVS_UpdateTexPan_Ground = {
    Call(EnableTexPanning, MODEL_o145, true)
    Call(EnableTexPanning, MODEL_o146, true)
    Call(EnableTexPanning, MODEL_j2, true)
    Call(EnableTexPanning, MODEL_o152, true)
    Call(EnableTexPanning, MODEL_o153, true)
    Call(EnableTexPanning, MODEL_o154, true)
    Call(EnableTexPanning, MODEL_o166, true)
    Call(EnableTexPanning, MODEL_o157, true)
    Call(EnableTexPanning, MODEL_o159, true)
    Call(EnableTexPanning, MODEL_o160, true)
    Call(EnableTexPanning, MODEL_o161, true)
    Call(EnableTexPanning, MODEL_o162, true)
    Call(EnableTexPanning, MODEL_o195, true)
    Call(EnableTexPanning, MODEL_o196, true)
    Call(EnableTexPanning, MODEL_o197, true)
    Call(EnableTexPanning, MODEL_o198, true)
    Call(EnableTexPanning, MODEL_o260, true)
    Call(EnableTexPanning, MODEL_o201, true)
    Call(EnableTexPanning, MODEL_o202, true)
    Call(EnableTexPanning, MODEL_o203, true)
    Call(EnableTexPanning, MODEL_o204, true)
    Call(EnableTexPanning, MODEL_o275, true)
    Call(EnableTexPanning, MODEL_o276, true)
    Call(EnableTexPanning, MODEL_o277, true)
    Call(EnableTexPanning, MODEL_o278, true)
    Thread
        Set(LVar0, 0)
        Set(LVar1, 0)
        Loop(0)
            Add(LVar0, 150)
            IfGt(LVar0, 0x20000)
                Add(LVar0, -0x20000)
            EndIf
            Call(SetTexPanOffset, TEX_PANNER_1, TEX_PANNER_MAIN, LVar0, 0)
            Wait(1)
        EndLoop
    EndThread
    Return
    End
};

EvtScript EVS_OffsetNpcScroll = {
    Call(AddScrollToNpcPos, LVar0)
    Return
    End
};

AnimID LimitAnims_Eldstar[] = {
    ANIM_BattleEldstar_Idle,
    ANIM_LIST_END
};

AnimID LimitAnims_Mamar[] = {
    ANIM_BattleMamar_Idle,
    ANIM_LIST_END
};

AnimID LimitAnims_Skolar[] = {
    ANIM_BattleSkolar_Idle,
    ANIM_LIST_END
};

AnimID LimitAnims_Muskular[] = {
    ANIM_BattleMuskular_Idle,
    ANIM_LIST_END
};

AnimID LimitAnims_Misstar[] = {
    ANIM_BattleMisstar_Still,
    ANIM_LIST_END
};

AnimID LimitAnims_Klevar[] = {
    ANIM_BattleKlevar_Idle,
    ANIM_LIST_END
};

AnimID LimitAnims_Kalmar[] = {
    ANIM_BattleKalmar_Idle,
    ANIM_LIST_END
};

AnimID LimitAnims_PyroGuy[] = {
    ANIM_PyroGuy_Run,
    ANIM_LIST_END
};

AnimID LimitAnims_ShyGuy[] = {
    ANIM_ShyGuy_Red_Dash,
    ANIM_ShyGuy_Red_Crashed,
    ANIM_ShyGuy_Red_Idle,
    ANIM_LIST_END
};

ParadeNpcInfo ParadeNpcsTable[] = {
    [NPC_Eldstar] {
        .initialAnim = ANIM_BattleEldstar_Idle,
        .animList = LimitAnims_Eldstar,
        .pos = { -3135.0f, 210.0f, -120.0f },
        .yaw = 270.0f
    },
    [NPC_Mamar] {
        .initialAnim = ANIM_BattleMamar_Idle,
        .animList = LimitAnims_Mamar,
        .pos = { -3195.0f, 200.0f, -120.0f },
        .yaw = 270.0f
    },
    [NPC_Skolar] {
        .initialAnim = ANIM_BattleSkolar_Idle,
        .animList = LimitAnims_Skolar,
        .pos = { -3075.0f, 195.0f, -120.0f },
        .yaw = 270.0f
    },
    [NPC_Muskular] {
        .initialAnim = ANIM_BattleMuskular_Idle,
        .animList = LimitAnims_Muskular,
        .pos = { -3045.0f, 148.0f, -104.0f },
        .yaw = 270.0f
    },
    [NPC_Misstar] {
        .initialAnim = ANIM_BattleMisstar_Still,
        .animList = LimitAnims_Misstar,
        .pos = { -3105.0f, 158.0f, -104.0f },
        .yaw = 270.0f
    },
    [NPC_Klevar] {
        .initialAnim = ANIM_BattleKlevar_Idle,
        .animList = LimitAnims_Klevar,
        .pos = { -3165.0f, 158.0f, -104.0f },
        .yaw = 270.0f
    },
    [NPC_Kalmar] {
        .initialAnim = ANIM_BattleKalmar_Idle,
        .animList = LimitAnims_Kalmar,
        .pos = { -3225.0f, 148.0f, -104.0f },
        .yaw = 270.0f
    },
    [NPC_PenguinSkater1] {
        .initialAnim = ANIM_ParadeIceShow_Violin_SkateStill,
        .pos = { -2700.0f, 0.0f, -37.0f },
        .yaw = 270.0f
    },
    [NPC_PenguinSkater2] {
        .initialAnim = ANIM_ParadeIceShow_Violin_SkateStill,
        .pos = { -2700.0f, 0.0f, 37.0f },
        .yaw = 270.0f
    },
    [NPC_PenguinMayor] {
        .initialAnim = ANIM_ParadeIceShow_Violin_ShadeMayorWalk,
        .pos = { -2650.0f, 0.0f, -77.0f },
        .yaw = 270.0f
    },
    [NPC_PenguinMayorWife] {
        .initialAnim = ANIM_ParadeIceShow_Violin_ShadeMayorWifeWalk,
        .pos = { -2610.0f, 0.0f, -77.0f },
        .yaw = 270.0f
    },
    [NPC_ViolinPlayer1] {
        .initialAnim = ANIM_ParadeIceShow_Violin_ViolinPlay,
        .pos = { -2555.0f, 5.0f, 30.0f },
        .yaw = 270.0f
    },
    [NPC_ViolinPlayer2] {
        .initialAnim = ANIM_ParadeIceShow_Violin_ViolinPlayUpright,
        .pos = { -2527.0f, 5.0f, 35.0f },
        .yaw = 270.0f
    },
    [NPC_ViolinPlayer3] {
        .initialAnim = ANIM_ParadeIceShow_Violin_ViolinPlay,
        .pos = { -2495.0f, 5.0f, 30.0f },
        .yaw = 90.0f
    },
    [NPC_Conductor] {
        .initialAnim = ANIM_Musician_Poet_Dark_ConductSlow,
        .pos = { -2624.0f, 20.0f, 0.0f },
        .yaw = 90.0f
    },
    [NPC_Singer] {
        .initialAnim = ANIM_ParadeIceShow_Violin_ShadeDivaIdle,
        .pos = { -2529.0f, 0.0f, 0.0f },
        .yaw = 270.0f
    },
    [NPC_AmayzeDayzee1] {
        .initialAnim = ANIM_Dayzee_Amazy_Walk,
        .pos = { -2210.0f, 0.0f, -20.0f },
        .yaw = 270.0f
    },
    [NPC_AmayzeDayzee2] {
        .initialAnim = ANIM_Dayzee_Amazy_Walk,
        .pos = { -2210.0f, 0.0f, 20.0f },
        .yaw = 270.0f
    },
    [NPC_Merle] {
        .initialAnim = ANIM_ParadeWizard_Merle_MerleGather,
        .pos = { -2025.0f, 20.0f, 28.0f },
        .yaw = 270.0f
    },
    [NPC_Merlee] {
        .initialAnim = ANIM_ParadeWizard_Merle_MerleeGather,
        .pos = { -1995.0f, 20.0f, 20.0f },
        .yaw = 270.0f
    },
    [NPC_Merlon] {
        .initialAnim = ANIM_ParadeWizard_Merle_MerlonGather,
        .pos = { -2055.0f, 20.0f, 35.0f },
        .yaw = 270.0f
    },
    [NPC_Merluvlee] {
        .initialAnim = ANIM_ParadeWizard_Merle_MerluvleeGather,
        .pos = { -2085.0f, 20.0f, 28.0f },
        .yaw = 270.0f
    },
    [NPC_Merlow] {
        .initialAnim = ANIM_ParadeWizard_Merle_MerlowGather,
        .pos = { -2110.0f, 20.0f, 20.0f },
        .yaw = 270.0f
    },
    [NPC_Merlar] {
        .initialAnim = ANIM_ParadeWizard_Merle_MerlarGather,
        .pos = { -1980.0f, 60.0f, 20.0f },
        .yaw = 270.0f
    },
    [NPC_SunSad] {
        .initialAnim = ANIM_Sun_TalkSad,
        .pos = { 0.0f, -500.0f, 0.0f },
        .yaw = 90.0f
    },
    [NPC_SunHappy] {
        .initialAnim = ANIM_Sun_FireTalkSad,
        .pos = { 0.0f, -500.0f, 0.0f },
        .yaw = 90.0f
    },
    [NPC_Bubulb1] {
        .initialAnim = ANIM_Bubulb_Pink_DarkWalk,
        .pos = { -1850.0f, 0.0f, -20.0f },
        .yaw = 270.0f
    },
    [NPC_Bubulb2] {
        .initialAnim = ANIM_Bubulb_Pink_DarkWalk,
        .pos = { -1850.0f, 0.0f, 20.0f },
        .yaw = 270.0f
    },
    [NPC_ShyGuyMarshall] {
        .initialAnim = ANIM_ParadeShyGuy_MarshallWalk,
        .pos = { -1548.0f, 0.0f, 0.0f },
        .yaw = 270.0f
    },
    [NPC_GeneralGuy] {
        .initialAnim = ANIM_ParadeShyGuy_GeneralPoint,
        .pos = { -1448.0f, 57.0f, -25.0f },
        .yaw = 270.0f
    },
    [NPC_BackupDancer1] {
        .initialAnim = ANIM_ParadeShyGuy_StackHold,
        .pos = { -1483.0f, 24.0f, -40.0f },
        .yaw = 90.0f
    },
    [NPC_BackupDancer2] {
        .initialAnim = ANIM_ParadeShyGuy_StackHold,
        .pos = { -1413.0f, 24.0f, -40.0f },
        .yaw = 270.0f
    },
    [NPC_GrooveGuy1] {
        .initialAnim = ANIM_ParadeShyGuy_GroovePivot,
        .pos = { -1468.0f, 24.0f, -5.0f },
        .yaw = 270.0f
    },
    [NPC_GrooveGuy2] {
        .initialAnim = ANIM_ParadeShyGuy_GroovePivot,
        .pos = { -1458.0f, 24.0f, -5.0f },
        .yaw = 270.0f
    },
    [NPC_GrooveGuy3] {
        .initialAnim = ANIM_ParadeShyGuy_GroovePivot,
        .pos = { -1438.0f, 24.0f, -5.0f },
        .yaw = 90.0f
    },
    [NPC_GrooveGuy4] {
        .initialAnim = ANIM_ParadeShyGuy_GroovePivot,
        .pos = { -1428.0f, 24.0f, -5.0f },
        .yaw = 90.0f
    },
    [NPC_PyroGuy1] {
        .initialAnim = ANIM_PyroGuy_Run,
        .animList = LimitAnims_PyroGuy,
        .pos = { 0.0f, -500.0f, 0.0f },
        .yaw = 90.0f
    },
    [NPC_PyroGuy2] {
        .initialAnim = ANIM_PyroGuy_Run,
        .animList = LimitAnims_PyroGuy,
        .pos = { 0.0f, -500.0f, 0.0f },
        .yaw = 270.0f
    },
    [NPC_ShyGuyFormation11] {
        .initialAnim = ANIM_ParadeShyGuy_ShadeWalk,
        .pos = { -1048.0f, 0.0f, -30.0f },
        .yaw = 270.0f
    },
    [NPC_ShyGuyFormation12] {
        .initialAnim = ANIM_ParadeShyGuy_ShadeWalk,
        .pos = { -1048.0f, 0.0f, 0.0f },
        .yaw = 270.0f
    },
    [NPC_ShyGuyFormation13] {
        .initialAnim = ANIM_ParadeShyGuy_ShadeWalk,
        .pos = { -1048.0f, 0.0f, 30.0f },
        .yaw = 270.0f
    },
    [NPC_ShyGuyFormation21] {
        .initialAnim = ANIM_ParadeShyGuy_ShadeWalk,
        .pos = { -1018.0f, 0.0f, -30.0f },
        .yaw = 270.0f
    },
    [NPC_ShyGuyFormation22] {
        .initialAnim = ANIM_ParadeShyGuy_ShadeWalk,
        .pos = { -1018.0f, 0.0f, 0.0f },
        .yaw = 270.0f
    },
    [NPC_ShyGuyFormation23] {
        .initialAnim = ANIM_ParadeShyGuy_ShadeWalk,
        .pos = { -1018.0f, 0.0f, 30.0f },
        .yaw = 270.0f
    },
    [NPC_ShyGuyFormation31] {
        .initialAnim = ANIM_ParadeShyGuy_ShadeWalk,
        .pos = { -988.0f, 0.0f, -30.0f },
        .yaw = 270.0f
    },
    [NPC_ShyGuyFormation32] {
        .initialAnim = ANIM_ParadeShyGuy_ShadeWalk,
        .pos = { -988.0f, 0.0f, 0.0f },
        .yaw = 270.0f
    },
    [NPC_ShyGuyFormation33] {
        .initialAnim = ANIM_ParadeShyGuy_ShadeWalk,
        .pos = { -988.0f, 0.0f, 30.0f },
        .yaw = 270.0f
    },
    [NPC_ShyGuyFormation41] {
        .initialAnim = ANIM_ParadeShyGuy_ShadeWalk,
        .pos = { -958.0f, 0.0f, -30.0f },
        .yaw = 270.0f
    },
    [NPC_ShyGuyFormation42] {
        .initialAnim = ANIM_ParadeShyGuy_ShadeWalk,
        .pos = { -958.0f, 0.0f, 0.0f },
        .yaw = 270.0f
    },
    [NPC_ShyGuyFormation43] {
        .initialAnim = ANIM_ParadeShyGuy_ShadeWalk,
        .pos = { -958.0f, 0.0f, 30.0f },
        .yaw = 270.0f
    },
    [NPC_Pratfaller] {
        .initialAnim = ANIM_ShyGuy_Red_Dash,
        .animList = LimitAnims_ShyGuy,
        .pos = { -788.0f, 0.0f, 0.0f },
        .yaw = 270.0f
    },
    [NPC_HornPlayer1] {
        .initialAnim = ANIM_ParadeHorn_Walk,
        .pos = { -689.0f, 0.0f, -20.0f },
        .yaw = 270.0f
    },
    [NPC_HornPlayer2] {
        .initialAnim = ANIM_ParadeHorn_Walk,
        .pos = { -689.0f, 0.0f, 20.0f },
        .yaw = 270.0f
    },
    [NPC_Drummer1] {
        .initialAnim = ANIM_ParadeDrummer_Walk,
        .pos = { -639.0f, 0.0f, -20.0f },
        .yaw = 270.0f
    },
    [NPC_Drummer2] {
        .initialAnim = ANIM_ParadeDrummer_Walk,
        .pos = { -639.0f, 0.0f, 20.0f },
        .yaw = 270.0f
    },
    [NPC_StandardBearer1] {
        .initialAnim = ANIM_ParadeBanner_Walk,
        .pos = { -589.0f, 0.0f, -20.0f },
        .yaw = 270.0f
    },
    [NPC_StandardBearer2] {
        .initialAnim = ANIM_ParadeBanner_Walk,
        .pos = { -589.0f, 0.0f, 20.0f },
        .yaw = 270.0f
    },
    [NPC_Mario] {
        .initialAnim = ANIM_ParadeMario_Wave,
        .pos = { -329.0f, 37.0f, 0.0f },
        .yaw = 270.0f
    },
    [NPC_Peach] {
        .initialAnim = ANIM_ParadePeach_ShadeWaveSlow,
        .pos = { -289.0f, 37.0f, 0.0f },
        .yaw = 270.0f
    },
    [NPC_Twink] {
        .initialAnim = ANIM_ParadeTwink_Idle,
        .pos = { -389.0f, 120.0f, 0.0f },
        .yaw = 90.0f
    },
    [NPC_Twirler1] {
        .initialAnim = ANIM_ParadeTwirler_Walk,
        .pos = { -109.0f, 0.0f, 0.0f },
        .yaw = 270.0f
    },
    [NPC_Twirler2] {
        .initialAnim = ANIM_ParadeTwirler_Walk,
        .pos = { -69.0f, 0.0f, 0.0f },
        .yaw = 270.0f
    },
    [NPC_Twirler3] {
        .initialAnim = ANIM_ParadeTwirler_Walk,
        .pos = { -29.0f, 0.0f, 0.0f },
        .yaw = 270.0f
    },
    [NPC_Baton1] {
        .initialAnim = ANIM_ParadeTwirler_BatonSpin,
        .pos = { 0.0f, -500.0f, 0.0f },
        .yaw = 270.0f
    },
    [NPC_Baton2] {
        .initialAnim = ANIM_ParadeTwirler_BatonSpin,
        .pos = { 0.0f, -500.0f, 0.0f },
        .yaw = 270.0f
    },
    [NPC_Baton3] {
        .initialAnim = ANIM_ParadeTwirler_BatonSpin,
        .pos = { 0.0f, -500.0f, 0.0f },
        .yaw = 270.0f
    },
    [NPC_StandardBearer3] {
        .initialAnim = ANIM_ParadeBanner_Walk,
        .pos = { 41.0f, 0.0f, -20.0f },
        .yaw = 270.0f
    },
    [NPC_StandardBearer4] {
        .initialAnim = ANIM_ParadeBanner_Walk,
        .pos = { 41.0f, 0.0f, 20.0f },
        .yaw = 270.0f
    },
};

EvtScript EVS_ManageNpcPool = {
    Call(CreateParadeNPC, NPC_Eldstar)
    Call(CreateParadeNPC, NPC_Mamar)
    Call(CreateParadeNPC, NPC_Skolar)
    Call(CreateParadeNPC, NPC_Muskular)
    Call(CreateParadeNPC, NPC_Misstar)
    Call(CreateParadeNPC, NPC_Klevar)
    Call(CreateParadeNPC, NPC_Kalmar)
    Call(CreateParadeNPC, NPC_PenguinMayor)
    Call(CreateParadeNPC, NPC_PenguinMayorWife)
    Call(CreateParadeNPC, NPC_PenguinSkater1)
    Call(CreateParadeNPC, NPC_PenguinSkater2)
    Call(CreateParadeNPC, NPC_ViolinPlayer1)
    Call(CreateParadeNPC, NPC_ViolinPlayer2)
    Call(CreateParadeNPC, NPC_ViolinPlayer3)
    Call(CreateParadeNPC, NPC_Conductor)
    Call(CreateParadeNPC, NPC_Singer)
    Call(ParadeSpriteHeapMalloc, 0x13400, LVar0)
    Call(CreateParadeNPC, NPC_AmayzeDayzee1)
    Call(CreateParadeNPC, NPC_AmayzeDayzee2)
    Call(ParadeSpriteHeapFree, LVar0)
    Loop(0)
        Wait(1)
        Call(GetCamPosition, CAM_DEFAULT, LVar0, LVar1, LVar2)
        IfGt(LVar0, PARADE_PHASE_WIZARDS + 100)
            BreakLoop
        EndIf
    EndLoop
    Call(DeleteNpc, NPC_Eldstar)
    Call(DeleteNpc, NPC_Mamar)
    Call(DeleteNpc, NPC_Skolar)
    Call(DeleteNpc, NPC_Muskular)
    Call(DeleteNpc, NPC_Misstar)
    Call(DeleteNpc, NPC_Klevar)
    Call(DeleteNpc, NPC_Kalmar)
    Call(DeleteNpc, NPC_PenguinMayor)
    Call(DeleteNpc, NPC_PenguinMayorWife)
    Call(DeleteNpc, NPC_PenguinSkater1)
    Call(DeleteNpc, NPC_PenguinSkater2)
    Call(DeleteNpc, NPC_ViolinPlayer1)
    Call(DeleteNpc, NPC_ViolinPlayer2)
    Call(DeleteNpc, NPC_ViolinPlayer3)
    Call(DeleteNpc, NPC_Conductor)
    Call(DeleteNpc, NPC_Singer)
    Wait(1)
    Call(CreateParadeNPC, NPC_Merle)
    Call(CreateParadeNPC, NPC_Merlee)
    Call(CreateParadeNPC, NPC_Merlon)
    Call(CreateParadeNPC, NPC_Merluvlee)
    Call(CreateParadeNPC, NPC_Merlow)
    Call(CreateParadeNPC, NPC_Merlar)
    Call(CreateParadeNPC, NPC_SunSad)
    Call(CreateParadeNPC, NPC_SunHappy)
    Call(CreateParadeNPC, NPC_Bubulb1)
    Call(CreateParadeNPC, NPC_Bubulb2)
    Loop(0)
        Wait(1)
        Call(GetCamPosition, CAM_DEFAULT, LVar0, LVar1, LVar2)
        IfGt(LVar0, PARADE_PHASE_SHYGUY_DANCE)
            BreakLoop
        EndIf
    EndLoop
    Call(DeleteNpc, NPC_AmayzeDayzee1)
    Call(DeleteNpc, NPC_AmayzeDayzee2)
    Wait(1)
    Call(ParadeSpriteHeapMalloc, 0x4700, LVar0)
    Call(CreateParadeNPC, NPC_PyroGuy1)
    Call(CreateParadeNPC, NPC_PyroGuy2)
    Call(CreateParadeNPC, NPC_Pratfaller)
    Call(CreateParadeNPC, NPC_ShyGuyMarshall)
    Call(CreateParadeNPC, NPC_GeneralGuy)
    Call(CreateParadeNPC, NPC_BackupDancer1)
    Call(CreateParadeNPC, NPC_BackupDancer2)
    Call(CreateParadeNPC, NPC_GrooveGuy1)
    Call(CreateParadeNPC, NPC_GrooveGuy2)
    Call(CreateParadeNPC, NPC_GrooveGuy3)
    Call(CreateParadeNPC, NPC_GrooveGuy4)
    Call(CreateParadeNPC, NPC_ShyGuyFormation11)
    Call(CreateParadeNPC, NPC_ShyGuyFormation12)
    Call(CreateParadeNPC, NPC_ShyGuyFormation13)
    Call(CreateParadeNPC, NPC_ShyGuyFormation21)
    Call(CreateParadeNPC, NPC_ShyGuyFormation22)
    Call(CreateParadeNPC, NPC_ShyGuyFormation23)
    Call(CreateParadeNPC, NPC_ShyGuyFormation31)
    Call(CreateParadeNPC, NPC_ShyGuyFormation32)
    Call(CreateParadeNPC, NPC_ShyGuyFormation33)
    Call(CreateParadeNPC, NPC_ShyGuyFormation41)
    Call(CreateParadeNPC, NPC_ShyGuyFormation42)
    Call(CreateParadeNPC, NPC_ShyGuyFormation43)
    Call(ParadeSpriteHeapFree, LVar0)
    Loop(0)
        Wait(1)
        Call(GetCamPosition, CAM_DEFAULT, LVar0, LVar1, LVar2)
        IfGt(LVar0, PARADE_PHASE_TOADS)
            BreakLoop
        EndIf
    EndLoop
    Call(DeleteNpc, NPC_Merle)
    Call(DeleteNpc, NPC_Merlee)
    Call(DeleteNpc, NPC_Merlon)
    Call(DeleteNpc, NPC_Merluvlee)
    Call(DeleteNpc, NPC_Merlow)
    Call(DeleteNpc, NPC_Merlar)
    Call(DeleteNpc, NPC_SunSad)
    Call(DeleteNpc, NPC_SunHappy)
    Call(DeleteNpc, NPC_Bubulb1)
    Call(DeleteNpc, NPC_Bubulb2)
    Wait(1)
    Call(CreateParadeNPC, NPC_HornPlayer1)
    Call(CreateParadeNPC, NPC_HornPlayer2)
    Call(CreateParadeNPC, NPC_Drummer1)
    Call(CreateParadeNPC, NPC_Drummer2)
    Call(CreateParadeNPC, NPC_StandardBearer1)
    Call(CreateParadeNPC, NPC_StandardBearer2)
    Loop(0)
        Wait(1)
        Call(GetCamPosition, CAM_DEFAULT, LVar0, LVar1, LVar2)
        IfGt(LVar0, PARADE_PHASE_PEACH)
            BreakLoop
        EndIf
    EndLoop
    Call(DeleteNpc, NPC_PyroGuy1)
    Call(DeleteNpc, NPC_PyroGuy2)
    Call(DeleteNpc, NPC_Pratfaller)
    Call(DeleteNpc, NPC_ShyGuyMarshall)
    Call(DeleteNpc, NPC_GeneralGuy)
    Call(DeleteNpc, NPC_BackupDancer1)
    Call(DeleteNpc, NPC_BackupDancer2)
    Call(DeleteNpc, NPC_GrooveGuy1)
    Call(DeleteNpc, NPC_GrooveGuy2)
    Call(DeleteNpc, NPC_GrooveGuy3)
    Call(DeleteNpc, NPC_GrooveGuy4)
    Call(DeleteNpc, NPC_ShyGuyFormation11)
    Call(DeleteNpc, NPC_ShyGuyFormation12)
    Call(DeleteNpc, NPC_ShyGuyFormation13)
    Call(DeleteNpc, NPC_ShyGuyFormation21)
    Call(DeleteNpc, NPC_ShyGuyFormation22)
    Call(DeleteNpc, NPC_ShyGuyFormation23)
    Call(DeleteNpc, NPC_ShyGuyFormation31)
    Call(DeleteNpc, NPC_ShyGuyFormation32)
    Call(DeleteNpc, NPC_ShyGuyFormation33)
    Call(DeleteNpc, NPC_ShyGuyFormation41)
    Call(DeleteNpc, NPC_ShyGuyFormation42)
    Call(DeleteNpc, NPC_ShyGuyFormation43)
    Wait(1)
    Call(CreateParadeNPC, NPC_Mario)
    Call(CreateParadeNPC, NPC_Peach)
    Call(CreateParadeNPC, NPC_Twink)
    Call(CreateParadeNPC, NPC_Twirler1)
    Call(CreateParadeNPC, NPC_Twirler2)
    Call(CreateParadeNPC, NPC_Twirler3)
    Call(CreateParadeNPC, NPC_Baton1)
    Call(CreateParadeNPC, NPC_Baton2)
    Call(CreateParadeNPC, NPC_Baton3)
    Call(CreateParadeNPC, NPC_StandardBearer3)
    Call(CreateParadeNPC, NPC_StandardBearer4)
    Return
    End
};

EvtScript EVS_ParadePhase_PlayCredits = {
    Wait(60)
    Exec(EVS_InitCredits)
    Exec(EVS_ShowCredits_Jobs)
    Exec(EVS_ShowCredits_Names)
    Return
    End
};

EvtScript EVS_ManageParade = {
    Call(DisablePlayerInput, true)
    Call(DisablePlayerPhysics, true)
    Call(SetMusic, 0, SONG_PARADE_NIGHT, 0, VOL_LEVEL_FULL)
    Exec(EVS_SetupInitialCamera)
    Exec(EVS_ManageNpcPool)
    ExecGetID(LVarA, EVS_ParadePhase_StarSpirits)
    Loop(0)
        Wait(1)
        IsScriptRunning(LVarA, LVar0)
        IfEq(LVar0, 0)
            BreakLoop
        EndIf
    EndLoop
    Exec(EVS_ParadePhase_PlayCredits)
    ExecGetID(LVarA, EVS_UpdateScrollPos)
    ExecGetID(LVarB, EVS_UpdateTexPan_Ground)
    Loop(0)
        Wait(1)
        Call(GetCamPosition, CAM_DEFAULT, LVar0, LVar1, LVar2)
        IfGt(LVar0, PARADE_PHASE_SKATERS)
            BreakLoop
        EndIf
    EndLoop
    Exec(EVS_ParadePhase_SkatingPenguins)
    Loop(0)
        Wait(1)
        Call(GetCamPosition, CAM_DEFAULT, LVar0, LVar1, LVar2)
        IfGt(LVar0, PARADE_PHASE_MAYOR)
            BreakLoop
        EndIf
    EndLoop
    Exec(EVS_ParadePhase_MayorPenguin)
    Loop(0)
        Wait(1)
        Call(GetCamPosition, CAM_DEFAULT, LVar0, LVar1, LVar2)
        IfGt(LVar0, PARADE_PHASE_OPERA)
            BreakLoop
        EndIf
    EndLoop
    Exec(EVS_ParadePhase_Opera)
    Loop(0)
        Wait(1)
        Call(GetCamPosition, CAM_DEFAULT, LVar0, LVar1, LVar2)
        IfGt(LVar0, PARADE_PHASE_WIZARDS)
            BreakLoop
        EndIf
    EndLoop
    Exec(EVS_ParadePhase_Wizards)
    Loop(0)
        Wait(1)
        Call(GetCamPosition, CAM_DEFAULT, LVar0, LVar1, LVar2)
        IfGt(LVar0, PARADE_PHASE_SHYGUY_DANCE)
            BreakLoop
        EndIf
    EndLoop
    Exec(EVS_ParadePhase_ShyGuyDancing)
    Loop(0)
        Wait(1)
        Call(GetCamPosition, CAM_DEFAULT, LVar0, LVar1, LVar2)
        IfGt(LVar0, PARADE_PHASE_SHYGUY_MARCH)
            BreakLoop
        EndIf
    EndLoop
    Exec(EVS_ParadePhase_ShyGuyFormation)
    Loop(0)
        Wait(1)
        Call(GetCamPosition, CAM_DEFAULT, LVar0, LVar1, LVar2)
        IfGt(LVar0, PARADE_PHASE_TOADS)
            BreakLoop
        EndIf
    EndLoop
    Exec(EVS_ParadePhase_Toads1)
    Loop(0)
        Wait(1)
        Call(GetCamPosition, CAM_DEFAULT, LVar0, LVar1, LVar2)
        IfGt(LVar0, PARADE_PHASE_PEACH)
            BreakLoop
        EndIf
    EndLoop
    ExecGetID(LVarC, EVS_ParadePhase_MarioPeach)
    Loop(0)
        Wait(1)
        Call(GetCamPosition, CAM_DEFAULT, LVar0, LVar1, LVar2)
        IfGt(LVar0, PARADE_PHASE_EXIT)
            BreakLoop
        EndIf
    EndLoop
    KillScript(LVarA)
    KillScript(LVarB)
    Loop(0)
        Wait(1)
        IsScriptRunning(LVarC, LVar0)
        IfEq(LVar0, 0)
            BreakLoop
        EndIf
    EndLoop
    Exec(EVS_ParadePhase_Toads2)
    Wait(150)
    Exec(EVS_MarioPeachExit)
    Wait(200)
    Call(GotoMap, Ref("kmr_30"), kmr_30_ENTRY_0)
    Wait(100)
    Return
    End
};
