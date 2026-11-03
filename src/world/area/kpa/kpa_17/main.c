#include "kpa_17.h"
#include "world/area/kpa/kpa_10.h"
#include "world/area/kpa/kpa_11.h"

EvtScript EVS_ExitWalk_kpa_1X_2 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(UseExitHeading, 60, $OutsideJail.index)
    Exec(ExitWalk)
    IfEq(GF_KPA16_ShutOffLava, false)
        Call(GotoMap, $kpa_11.LowerJail)
    Else
        Call(GotoMap, $kpa_10.LowerJail)
    EndIf
    Wait(100)
    Return
    End
};

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_kpa_1X_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    IfEq(LVar0, $FallIntoCell.index)
        Exec(EVS_BindExitTriggers)
        Exec(EVS_Scene_FallIntoCell)
    Else
        Set(LVar0, EVS_BindExitTriggers)
        Exec(EnterWalk)
    EndIf
    Return
    End
};

BombTrigger BombPos_Wall = {
    .pos = $BombPos_Wall.pos,
    .diameter = 2.0f * $BombPos_Wall.radius,
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_BOWSERS_CASTLE)
    Set(AB_KPA17_DialogueState_Toad1, 0)
    Set(AB_KPA17_DialogueState_Toad2, 0)
    Set(AB_KPA17_DialogueState_ToadGuard, 0)
    Set(AB_KPA17_DialogueState_ToadMinister, 0)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, true, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    IfEq(GF_KPA17_BombedWall, false)
        BindTrigger(EVS_BlastWall, TRIGGER_POINT_BOMB, BombPos_Wall, 1, 0)
    Else
        Call(SetGroupVisibility, MODEL_g296, MODEL_GROUP_HIDDEN)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitte, COLLIDER_FLAGS_UPPER_MASK)
    EndIf
    Exec(EVS_SetupMusic)
    Exec(EVS_EnterMap)
    Return
    End
};
