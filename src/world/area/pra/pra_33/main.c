#include "pra_33.h"
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
    Set(LVar0, pra_33_ENTRY_0)
    Set(LVar1, COLLIDER_deilittse)
    Set(LVar2, Ref(RightDoorModelsL))
    Set(LVar3, Ref(RightDoorModelsR))
    Exec(BaseExitDoor)
    Wait(17)
    Call(GotoMap, Ref("pra_35"), pra_35_ENTRY_0)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitDoors_pra_18_1 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Set(LVar0, pra_33_ENTRY_1)
    Set(LVar1, COLLIDER_deilittnw)
    Set(LVar2, Ref(LeftDoorModelsL))
    Set(LVar3, Ref(LeftDoorModelsR))
    Exec(BaseExitDoor)
    Wait(17)
    Call(GotoMap, Ref("pra_18"), pra_18_ENTRY_1)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitWalk_pra_35_2 = EVT_EXIT_WALK(60, pra_33_ENTRY_2, "pra_35", pra_35_ENTRY_2);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitDoors_pra_35_0), TRIGGER_WALL_PRESS_A, COLLIDER_deilittse, 1, 0)
    BindTrigger(Ref(EVS_ExitDoors_pra_18_1), TRIGGER_WALL_PRESS_A, COLLIDER_deilittnw, 1, 0)
    BindTrigger(Ref(EVS_ExitWalk_pra_35_2), TRIGGER_FLOOR_ABOVE, COLLIDER_deiline, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(pra_33_ENTRY_0)
            Set(LVar2, Ref(RightDoorModelsL))
            Set(LVar3, Ref(RightDoorModelsR))
            ExecWait(BaseEnterDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq(pra_33_ENTRY_1)
            Set(LVar2, Ref(LeftDoorModelsL))
            Set(LVar3, Ref(LeftDoorModelsR))
            ExecWait(BaseEnterDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq(pra_33_ENTRY_2)
            Set(LVar0, Ref(EVS_BindExitTriggers))
            Exec(EnterWalk)
    EndSwitch
    Return
    End
};

BombTrigger BombPos_Wall = {
    .pos = { 487.0f, 0.0f, -80.0f },
    .diameter = 0.0f
};

EvtScript EVS_BlastWall = {
    Set(GF_PRA33_BombedWall, true)
    PlayEffect(EFFECT_BOMBETTE_BREAKING, 0, 2, 34, 1, 10, 30)
    Call(EnableGroup, MODEL_g267, false)
    Call(EnableGroup, MODEL_g270, true)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilittne, COLLIDER_FLAGS_UPPER_MASK)
    Unbind
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_CRYSTAL_PALACE)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(24, 24, 40)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    IfEq(GF_PRA33_BombedWall, false)
        BindTrigger(Ref(EVS_BlastWall), TRIGGER_POINT_BOMB, Ref(BombPos_Wall), 1, 0)
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
