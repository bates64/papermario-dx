#include "pra_33.h"
#include "world/area/pra/pra_18.h"
#include "world/area/pra/pra_35.h"
#include "effects.h"

#include "../common/Reflection.inc.c"
#include "../common/Reflection.data.inc.c"
#include "../common/GlassShimmer.inc.c"

s32 RightDoorModelsL[] = { MODEL_o874, -1 };
s32 RightDoorModelsR[] = { MODEL_o876, -1 };

s32 LeftDoorModelsL[] = { MODEL_o859, -1 };
s32 LeftDoorModelsR[] = { MODEL_o861, -1 };

EvtScript EVS_ExitDoors_pra_35_0 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Set(LVar0, $TripleDipRoomSouth.index)
    Set(LVar1, COLLIDER_deilittse)
    Set(LVar2, RightDoorModelsL)
    Set(LVar3, RightDoorModelsR)
    Exec(BaseExitDoor)
    Wait(17)
    Call(GotoMap, $pra_35.TurnstyleRoomSouth)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitDoors_pra_18_1 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Set(LVar0, $BridgeMirrorHall.index)
    Set(LVar1, COLLIDER_deilittnw)
    Set(LVar2, LeftDoorModelsL)
    Set(LVar3, LeftDoorModelsR)
    Exec(BaseExitDoor)
    Wait(17)
    Call(GotoMap, $pra_18.TurnstyleRoom)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitWalk_pra_35_2 = EVT_EXIT_WALK(60, $TripleDipRoomNorth, $pra_35.TurnstyleRoomNorth);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitDoors_pra_35_0, TRIGGER_WALL_PRESS_A, COLLIDER_deilittse, 1, 0)
    BindTrigger(EVS_ExitDoors_pra_18_1, TRIGGER_WALL_PRESS_A, COLLIDER_deilittnw, 1, 0)
    BindTrigger(EVS_ExitWalk_pra_35_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deiline, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($TripleDipRoomSouth.index)
            Set(LVar2, RightDoorModelsL)
            Set(LVar3, RightDoorModelsR)
            ExecWait(BaseEnterDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq($BridgeMirrorHall.index)
            Set(LVar2, LeftDoorModelsL)
            Set(LVar3, LeftDoorModelsR)
            ExecWait(BaseEnterDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq($TripleDipRoomNorth.index)
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
    EndSwitch
    Return
    End
};

BombTrigger BombPos_Wall = {
    .pos = $BombPos_Wall.pos,
    .diameter = 2.0f * $BombPos_Wall.radius,
};

EvtScript EVS_BlastWall = {
    Set(GF_PRA33_BombedWall, true)
    PlayEffect(EFFECT_BOMBETTE_BREAKING, 0, $BombetteBreakingPos_1.pos.x, $BombetteBreakingPos_1.pos.y, $BombetteBreakingPos_1.pos.z, 10, 30)
    Call(EnableGroup, MODEL_g267, false)
    Call(EnableGroup, MODEL_g270, true)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilittne, COLLIDER_FLAGS_UPPER_MASK)
    Unbind
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_CRYSTAL_PALACE)
    EVT_SETUP_CAMERA_NO_LEAD(24, 24, 40)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    IfEq(GF_PRA33_BombedWall, false)
        BindTrigger(EVS_BlastWall, TRIGGER_POINT_BOMB, BombPos_Wall, 1, 0)
        Call(EnableGroup, MODEL_g270, false)
    Else
        Call(EnableGroup, MODEL_g267, false)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilittne, COLLIDER_FLAGS_UPPER_MASK)
    EndIf
    Set(LVar0, MODEL_o945)
    Set(LVar1, MODEL_o987)
    Set(LVar2, TEX_PANNER_0)
    Exec(EVS_GlassShimmer)
    Set(LVar0, REFLECTION_WALL_ONLY)
    Set(LVar1, GF_PRA_BrokeIllusion)
    Exec(EVS_SetupReflections)
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
