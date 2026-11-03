#include "osr_02.h"
#include "world/area/kkj/kkj_10.h"
#include "world/area/kpa/kpa_121.h"
#include "effects.h"

EvtScript EVS_ExitDoor_kpa_121_1 = EVT_EXIT_SINGLE_DOOR_SET_SOUNDS(
    $BowsersCastle, $kpa_121.PeachsCastle, COLLIDER_tt1, MODEL_o570, DOOR_SWING_IN, DOOR_SOUNDS_METAL
);

EvtScript EVS_ExitDoor_kkj_10_0 = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(
    $PeachsCastle, $kkj_10.CastleEntrance, COLLIDER_tt2, MODEL_d2, MODEL_d1, DOOR_SOUNDS_LARGE
);

EvtScript EVS_KeepPeachFromBowsersCastle = {
    Call(DisablePlayerInput, true)
    Call(DisablePartnerAI, true)
    Call(SpeakToPlayer, NPC_PARTNER, ANIM_Twink_Talk, ANIM_Twink_Idle, 0, MSG_Peach_0180)
    Call(EnablePartnerAI)
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript EVS_BindExitTriggers = {
    IfEq(GB_StoryProgress, STORY_CH6_BEGAN_PEACH_MISSION)
        BindTrigger(EVS_KeepPeachFromBowsersCastle, TRIGGER_WALL_PRESS_A, COLLIDER_tt1, 1, 0)
    Else
        BindTrigger(EVS_ExitDoor_kpa_121_1, TRIGGER_WALL_PRESS_A, COLLIDER_tt1, 1, 0)
    EndIf
    BindTrigger(EVS_ExitDoor_kkj_10_0, TRIGGER_WALL_PRESS_A, COLLIDER_tt2, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetLoadType, LVar1)
    IfEq(LVar1, LOAD_FROM_FILE_SELECT)
        Exec(EnterSavePoint)
        Exec(EVS_BindExitTriggers)
        Return
    EndIf
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($BowsersCastle.index)
            Call(UseDoorSounds, DOOR_SOUNDS_METAL)
            Set(LVar2, MODEL_o570)
            Set(LVar3, DOOR_SWING_IN)
            ExecWait(EnterSingleDoor)
        CaseEq($PeachsCastle.index)
            Call(UseDoorSounds, DOOR_SOUNDS_LARGE)
            Set(LVar2, MODEL_d2)
            Set(LVar3, MODEL_d1)
            ExecWait(EnterDoubleDoor)
        CaseEq(2)
            Exec(EVS_Scene_ReturnStarRod)
    EndSwitch
    Exec(EVS_BindExitTriggers)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_PEACHS_CASTLE)
    IfGt(GB_StoryProgress, STORY_CH8_REACHED_BOWSERS_CASTLE)
        Set(GF_MAP_PeachsCastle, true)
    EndIf
    Call(SetSpriteShading, $SpriteShading)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    IfEq(GB_StoryProgress, STORY_CH6_BEGAN_PEACH_MISSION)
        Call(SetAvailableDisguise, PEACH_DISGUISE_CLUBBA)
        Call(MakeNpcs, false, PeachNPCs)
    EndIf
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(2)
            Call(MakeNpcs, false, DefaultNPCs)
    EndSwitch
    ExecWait(EVS_MakeEntities)
    IfEq(GF_KKJ25_Defeated_Bowser, false)
        PlayEffect(EFFECT_FLAME, FX_FLAME_PINK, -269.16895, 50.0, 100.22, 1, LVar0)
        PlayEffect(EFFECT_FLAME, FX_FLAME_PINK, -2.6025392, 50.0, 161.583, 1, LVar0)
        PlayEffect(EFFECT_FLAME, FX_FLAME_PINK, 182.146, 50.0, 158.033, 1, LVar0)
        PlayEffect(EFFECT_FLAME, FX_FLAME_PINK, 346.938, 50.0, 31.861, 1, LVar0)
        PlayEffect(EFFECT_FLAME, FX_FLAME_PINK, 291.045, 86.206, -191.08205, 1, LVar0)
        PlayEffect(EFFECT_FLAME, FX_FLAME_PINK, -105.39165, 70.0, -203.115235, 1, LVar0)
        PlayEffect(EFFECT_FLAME, FX_FLAME_PINK, -52.5, 70.0, -233.73735, 1, LVar0)
        PlayEffect(EFFECT_FLAME, FX_FLAME_PINK, 52.5, 70.0, -233.73735, 1, LVar0)
        PlayEffect(EFFECT_FLAME, FX_FLAME_PINK, 108.229, 70.0, -200.6, 1, LVar0)
    Else
        Call(EnableGroup, MODEL_g116, false)
    EndIf
    IfGe(GB_StoryProgress, STORY_CH8_REACHED_BOWSERS_CASTLE)
        Call(FadeOutMusic, 0, 500)
    EndIf
    Exec(EVS_EnterMap)
    Wait(1)
    IfEq(GB_StoryProgress, STORY_CH8_REACHED_BOWSERS_CASTLE)
        Set(GB_StoryProgress, STORY_CH8_REACHED_PEACHS_CASTLE)
    EndIf
    Return
    End
};
