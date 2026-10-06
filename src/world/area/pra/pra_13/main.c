#include "pra_13.h"
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
        Set(LVar2, Ref(BothLeftDoorModelsL))
        Set(LVar3, Ref(BothLeftDoorModelsR))
    Else
        Set(LVar2, Ref(NearLeftDoorModelsL))
        Set(LVar3, Ref(NearLeftDoorModelsR))
    EndIf
    Exec(BaseExitDoor)
    Wait(17)
    Call(GotoMap, Ref("pra_02"), pra_02_ENTRY_2)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitWalk_pra_14_0 = EVT_EXIT_WALK(60, pra_13_ENTRY_1, "pra_14", pra_14_ENTRY_0);
EvtScript EVS_ExitWalk_pra_14_1 = EVT_EXIT_WALK(60, pra_13_ENTRY_2, "pra_14", pra_14_ENTRY_1);

EvtScript EVS_ExitDoors_pra_02_3 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
    Set(LVar0, 3)
    Set(LVar1, 24)
    IfEq(GF_PRA_BrokeIllusion, false)
        Set(LVar2, Ref(BothLeftDoorModelsL))
        Set(LVar3, Ref(BothLeftDoorModelsR))
    Else
        Set(LVar2, Ref(FarLeftDoorModelsL))
        Set(LVar3, Ref(FarLeftDoorModelsR))
    EndIf
    Exec(BaseExitDoor)
    Wait(17)
    Call(GotoMap, Ref("pra_02"), pra_02_ENTRY_3)
    Wait(100)
    Return
    End
};

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitDoors_pra_02_2), TRIGGER_WALL_PRESS_A, COLLIDER_deilittsw, 1, 0)
    BindTrigger(Ref(EVS_ExitWalk_pra_14_0), TRIGGER_FLOOR_ABOVE, COLLIDER_deilise, 1, 0)
    BindTrigger(Ref(EVS_ExitWalk_pra_14_1), TRIGGER_FLOOR_ABOVE, COLLIDER_deiline, 1, 0)
    BindTrigger(Ref(EVS_ExitDoors_pra_02_3), TRIGGER_WALL_PRESS_A, COLLIDER_deilittnw, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(pra_13_ENTRY_0)
            Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
            IfEq(GF_PRA_BrokeIllusion, false)
                Set(LVar2, Ref(BothLeftDoorModelsL))
                Set(LVar3, Ref(BothLeftDoorModelsR))
            Else
                Set(LVar2, Ref(NearLeftDoorModelsL))
                Set(LVar3, Ref(NearLeftDoorModelsR))
            EndIf
            ExecWait(BaseEnterDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq(pra_13_ENTRY_1)
            Set(LVar0, Ref(EVS_BindExitTriggers))
            Exec(EnterWalk)
        CaseEq(pra_13_ENTRY_2)
            Set(LVar0, Ref(EVS_BindExitTriggers))
            Exec(EnterWalk)
        CaseEq(pra_13_ENTRY_3)
            Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
            IfEq(GF_PRA_BrokeIllusion, false)
                Set(LVar2, Ref(BothLeftDoorModelsL))
                Set(LVar3, Ref(BothLeftDoorModelsR))
            Else
                Set(LVar2, Ref(FarLeftDoorModelsL))
                Set(LVar3, Ref(FarLeftDoorModelsR))
            EndIf
            ExecWait(BaseEnterDoor)
            Exec(EVS_BindExitTriggers)
    EndSwitch
    Return
    End
};

BombTrigger BombPos_NearWall = {
    .pos = { 487.0f, 0.0f, 80.0f },
    .diameter = 0.0f
};

BombTrigger BombPos_FarWall = {
    .pos = { 487.0f, 0.0f, -80.0f },
    .diameter = 0.0f
};

EvtScript EVS_BlastWall_Near = {
    PlayEffect(EFFECT_BOMBETTE_BREAKING, 0, 50, 34, 1, 10, 30)
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
    PlayEffect(EFFECT_BOMBETTE_BREAKING, 0, 65, 34, 1, 10, 30)
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
    Set(GB_WorldLocation, LOCATION_CRYSTAL_PALACE)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(24, 24, 40)
    Call(MakeNpcs, true, Ref(DefaultNPCs))
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
        BindTrigger(Ref(EVS_BlastWall_Near), TRIGGER_POINT_BOMB, Ref(BombPos_NearWall), 1, 0)
        Call(EnableModel, MODEL_o952, false)
    Else
        Call(EnableModel, MODEL_g260, false)
        Call(EnableModel, MODEL_g265, false)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilittse, COLLIDER_FLAGS_UPPER_MASK)
    EndIf
    IfEq(GF_PRA13_BombedWallB, false)
        BindTrigger(Ref(EVS_BlastWall_Far), TRIGGER_POINT_BOMB, Ref(BombPos_FarWall), 1, 0)
        Call(EnableModel, MODEL_o1009, false)
    Else
        Call(EnableModel, MODEL_g289, false)
        Call(EnableModel, MODEL_g290, false)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilittne, COLLIDER_FLAGS_UPPER_MASK)
    EndIf
    Return
    End
};
