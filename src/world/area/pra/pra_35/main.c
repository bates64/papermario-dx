#include "pra_35.h"
#include "world/area/pra/pra_19.h"
#include "world/area/pra/pra_33.h"

#include "../common/GlassShimmer.inc.c"

#include "../common/Reflection.inc.c"
#include "../common/Reflection.data.inc.c"

s32 LeftDoorModelsL[] = { MODEL_o772, MODEL_o844, -1 };
s32 LeftDoorModelsR[] = { MODEL_o768, MODEL_o846, -1 };

s32 RightDoorModelsL[] = { MODEL_o861, MODEL_o862, -1 };
s32 RightDoorModelsR[] = { MODEL_o859, MODEL_o860, -1 };

EvtScript EVS_ExitWalk_pra_33_0 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Set(LVar0, $TurnstyleRoomSouth.index)
    Set(LVar1, COLLIDER_deilittsw)
    Set(LVar2, LeftDoorModelsL)
    Set(LVar3, LeftDoorModelsR)
    Exec(BaseExitDoor)
    Wait(17)
    Call(GotoMap, $pra_33.TripleDipRoomSouth)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitWalk_pra_19_0 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Set(LVar0, $ReflectionMimicRoom.index)
    Set(LVar1, COLLIDER_deilittsw)
    Set(LVar2, RightDoorModelsL)
    Set(LVar3, RightDoorModelsR)
    Exec(BaseExitDoor)
    Wait(17)
    Call(GotoMap, $pra_19.TripleDipRoom)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitWalk_pra_33_2 = EVT_EXIT_WALK(60, $TurnstyleRoomNorth, $pra_33.TripleDipRoomNorth);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_pra_33_0, TRIGGER_WALL_PRESS_A, COLLIDER_deilittsw, 1, 0)
    BindTrigger(EVS_ExitWalk_pra_19_0, TRIGGER_WALL_PRESS_A, COLLIDER_deilittse, 1, 0)
    BindTrigger(EVS_ExitWalk_pra_33_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deilinw, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($TurnstyleRoomSouth.index)
            Set(LVar2, LeftDoorModelsL)
            Set(LVar3, LeftDoorModelsR)
            ExecWait(BaseEnterDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq($ReflectionMimicRoom.index)
            Set(LVar2, RightDoorModelsL)
            Set(LVar3, RightDoorModelsR)
            ExecWait(BaseEnterDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq($TurnstyleRoomNorth.index)
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

EvtScript EVS_BlastBombableWall = {
    Call(EnableGroup, MODEL_g297, false)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilittnw, COLLIDER_FLAGS_UPPER_MASK)
    Unbind
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_CRYSTAL_PALACE)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(24, 24, 40)
    Call(MakeNpcs, true, DefaultNPCs)
    Set(LVar0, 64)
    Set(LVar1, 65)
    Set(LVar2, 0)
    Exec(EVS_GlassShimmer)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_EnterMap)
    Wait(1)
    IfEq(GF_PRA33_BombedWall, false)
        BindTrigger(EVS_BlastBombableWall, TRIGGER_POINT_BOMB, BombPos_Wall, 1, 0)
    Else
        Call(EnableGroup, MODEL_g297, false)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilittnw, COLLIDER_FLAGS_UPPER_MASK)
    EndIf
    Set(LVar0, 0)
    Set(LVar1, GF_PRA_BrokeIllusion)
    Exec(EVS_SetupReflections)
    Exec(EVS_SetupMusic)
    Return
    End
};
