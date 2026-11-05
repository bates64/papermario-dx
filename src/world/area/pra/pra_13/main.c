#include "pra_13.h"
#include "world/area/pra/pra_02.h"
#include "world/area/pra/pra_14.h"
#include "effects.h"

#include "../common/Reflection.inc.c"
#include "../common/Reflection.data.inc.c"

#include "../common/GlassShimmer.inc.c"

s32 NearLeftDoorModelsL[] = { MODEL_o772, MODEL_o844, -1 };
s32 NearLeftDoorModelsR[] = { MODEL_o768, MODEL_o846, -1 };

s32 FarLeftDoorModelsL[] = { MODEL_o859, MODEL_o860, -1 };
s32 FarLeftDoorModelsR[] = { MODEL_o861, MODEL_o862, -1 };

s32 BothLeftDoorModelsL[] = { MODEL_o772, MODEL_o844, MODEL_o859, MODEL_o860, -1 };
s32 BothLeftDoorModelsR[] = { MODEL_o768, MODEL_o846, MODEL_o861, MODEL_o862, -1 };

EvtScript EVS_ExitDoors_pra_02_2 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
    Set(LVar0, 0)
    Set(LVar1, 20)
    IfEq(GF_PRA_BrokeIllusion, false)
        Set(LVar2, BothLeftDoorModelsL)
        Set(LVar3, BothLeftDoorModelsR)
    Else
        Set(LVar2, NearLeftDoorModelsL)
        Set(LVar3, NearLeftDoorModelsR)
    EndIf
    Exec(BaseExitDoor)
    Wait(17)
    Call(GotoMap, $pra_02.MirrorHallSouth)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitWalk_pra_14_0 = EVT_EXIT_WALK(60, $BlueMirrorHall2South, $pra_14.BlueMirrorHall1South);
EvtScript EVS_ExitWalk_pra_14_1 = EVT_EXIT_WALK(60, $BlueMirrorHall2North, $pra_14.BlueMirrorHall1North);

EvtScript EVS_ExitDoors_pra_02_3 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
    Set(LVar0, 3)
    Set(LVar1, 24)
    IfEq(GF_PRA_BrokeIllusion, false)
        Set(LVar2, BothLeftDoorModelsL)
        Set(LVar3, BothLeftDoorModelsR)
    Else
        Set(LVar2, FarLeftDoorModelsL)
        Set(LVar3, FarLeftDoorModelsR)
    EndIf
    Exec(BaseExitDoor)
    Wait(17)
    Call(GotoMap, $pra_02.MirrorHallNorth)
    Wait(100)
    Return
    End
};

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitDoors_pra_02_2, TRIGGER_WALL_PRESS_A, COLLIDER_deilittsw, 1, 0)
    BindTrigger(EVS_ExitWalk_pra_14_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilise, 1, 0)
    BindTrigger(EVS_ExitWalk_pra_14_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiline, 1, 0)
    BindTrigger(EVS_ExitDoors_pra_02_3, TRIGGER_WALL_PRESS_A, COLLIDER_deilittnw, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($EntryHallSouth.index)
            Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
            IfEq(GF_PRA_BrokeIllusion, false)
                Set(LVar2, BothLeftDoorModelsL)
                Set(LVar3, BothLeftDoorModelsR)
            Else
                Set(LVar2, NearLeftDoorModelsL)
                Set(LVar3, NearLeftDoorModelsR)
            EndIf
            ExecWait(BaseEnterDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq($BlueMirrorHall2South.index)
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
        CaseEq($BlueMirrorHall2North.index)
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
        CaseEq($EntryHallNorth.index)
            Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
            IfEq(GF_PRA_BrokeIllusion, false)
                Set(LVar2, BothLeftDoorModelsL)
                Set(LVar3, BothLeftDoorModelsR)
            Else
                Set(LVar2, FarLeftDoorModelsL)
                Set(LVar3, FarLeftDoorModelsR)
            EndIf
            ExecWait(BaseEnterDoor)
            Exec(EVS_BindExitTriggers)
    EndSwitch
    Return
    End
};

BombTrigger BombPos_NearWall = {
    .pos = $BombPos_NearWall.pos,
    .diameter = 2.0f * $BombPos_NearWall.radius,
};

BombTrigger BombPos_FarWall = {
    .pos = $BombPos_FarWall.pos,
    .diameter = 2.0f * $BombPos_FarWall.radius,
};

EvtScript EVS_BlastWall_Near = {
    PlayEffect(EFFECT_BOMBETTE_BREAKING, 0, $BombetteBreakingPos_1.pos.x, $BombetteBreakingPos_1.pos.y, $BombetteBreakingPos_1.pos.z, 10, 30)
    Call(EnableModel, MODEL_g260, false)
    Call(EnableModel, MODEL_g265, false)
    Call(EnableModel, MODEL_o952, true)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilittse, COLLIDER_FLAGS_UPPER_MASK)
    Set(GF_PRA13_BombedWallA, true)
    Set(GF_PRA_BrokeIllusion, true)
    Unbind
    Return
    End
};

EvtScript EVS_BlastWall_Far = {
    PlayEffect(EFFECT_BOMBETTE_BREAKING, 0, $BombetteBreakingPos_2.pos.x, $BombetteBreakingPos_2.pos.y, $BombetteBreakingPos_2.pos.z, 10, 30)
    Call(EnableModel, MODEL_g289, false)
    Call(EnableModel, MODEL_g290, false)
    Call(EnableModel, MODEL_o1009, true)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilittne, COLLIDER_FLAGS_UPPER_MASK)
    Set(GF_PRA13_BombedWallB, true)
    Unbind
    Return
    End
};

EvtScript EVS_Main = {
    Call(MakeNpcs, true, DefaultNPCs)
    Set(LVar0, MODEL_o945)
    Set(LVar1, MODEL_o947)
    Set(LVar2, 0)
    Exec(EVS_GlassShimmer)
    Set(LVar0, REFLECTION_FLOOR_WALL)
    Set(LVar1, GF_PRA_BrokeIllusion)
    Exec(EVS_SetupReflections)
    Exec(EVS_EnterMap)
    Wait(1)
    Exec(EVS_SetupMusic)
    IfEq(GF_PRA13_BombedWallA, false)
        BindTrigger(EVS_BlastWall_Near, TRIGGER_POINT_BOMB, BombPos_NearWall, 1, 0)
        Call(EnableModel, MODEL_o952, false)
    Else
        Call(EnableModel, MODEL_g260, false)
        Call(EnableModel, MODEL_g265, false)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilittse, COLLIDER_FLAGS_UPPER_MASK)
    EndIf
    IfEq(GF_PRA13_BombedWallB, false)
        BindTrigger(EVS_BlastWall_Far, TRIGGER_POINT_BOMB, BombPos_FarWall, 1, 0)
        Call(EnableModel, MODEL_o1009, false)
    Else
        Call(EnableModel, MODEL_g289, false)
        Call(EnableModel, MODEL_g290, false)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilittne, COLLIDER_FLAGS_UPPER_MASK)
    EndIf
    Return
    End
};
