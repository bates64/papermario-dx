#include "kpa_17.h"

EvtScript EVS_ExitWalk_kpa_1X_2 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(UseExitHeading, 60, kpa_17_ENTRY_1)
    Exec(ExitWalk)
    IfEq(GF_KPA16_ShutOffLava, false)
        Call(GotoMap, Ref("kpa_11"), kpa_11_ENTRY_2)
    Else
        Call(GotoMap, Ref("kpa_10"), kpa_10_ENTRY_2)
    EndIf
    Wait(100)
    Return
    End
};

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitWalk_kpa_1X_2), TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    IfEq(LVar0, kpa_17_ENTRY_0)
        Exec(EVS_BindExitTriggers)
        Exec(EVS_Scene_FallIntoCell)
    Else
        Set(LVar0, Ref(EVS_BindExitTriggers))
        Exec(EnterWalk)
    EndIf
    Return
    End
};

BombTrigger BombPos_Wall = {
    .pos = { 1186.0f, 30.0f, -562.0f },
    .diameter = 0.0f
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_BOWSERS_CASTLE)
    Set(AB_KPA17_DialogueState_Toad1, 0)
    Set(AB_KPA17_DialogueState_Toad2, 0)
    Set(AB_KPA17_DialogueState_ToadGuard, 0)
    Set(AB_KPA17_DialogueState_ToadMinister, 0)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, true, Ref(DefaultNPCs))
    ExecWait(EVS_MakeEntities)
    IfEq(GF_KPA17_BombedWall, false)
        BindTrigger(Ref(EVS_BlastWall), TRIGGER_POINT_BOMB, Ref(BombPos_Wall), 1, 0)
    Else
        Call(SetGroupVisibility, MODEL_g296, MODEL_GROUP_HIDDEN)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitte, COLLIDER_FLAGS_UPPER_MASK)
    EndIf
    Exec(EVS_SetupMusic)
    Exec(EVS_EnterMap)
    Return
    End
};
