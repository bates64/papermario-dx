#include "pra_18.h"

#include "../common/Reflection.inc.c"
#include "../common/Reflection.data.inc.c"

#include "../common/GlassShimmer.inc.c"

s32 NearRightDoorModelsL[] = { MODEL_o772, -1 };
s32 NearRightDoorModelsR[] = { MODEL_o768, -1 };
s32 FarRightDoorModelsL[]  = { MODEL_o859, -1 };
s32 FarRightDoorModelsR[]  = { MODEL_o861, -1 };
s32 BothRightDoorModelsL[] = { MODEL_o772, MODEL_o859, -1 };
s32 BothRightDoorModelsR[] = { MODEL_o768, MODEL_o861, -1 };

s32 LeftDoorModelsL[] = { MODEL_o995, MODEL_o996, -1 };
s32 LeftDoorModelsR[] = { MODEL_o997, MODEL_o998, -1 };

EvtScript EVS_ExitDoors_pra_16_1 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Set(LVar0, pra_18_ENTRY_0)
    Set(LVar1, COLLIDER_deilittsw)
    IfEq(GF_PRA_BrokeIllusion, false)
        Set(LVar2, Ref(BothRightDoorModelsL))
        Set(LVar3, Ref(BothRightDoorModelsR))
    Else
        Set(LVar2, Ref(NearRightDoorModelsL))
        Set(LVar3, Ref(NearRightDoorModelsR))
    EndIf
    Exec(BaseExitDoor)
    Wait(17)
    Call(GotoMap, Ref("pra_16"), pra_16_ENTRY_1)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitDoors_pra_33_1 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Set(LVar0, pra_18_ENTRY_1)
    Set(LVar1, COLLIDER_deilittne)
    Set(LVar2, Ref(LeftDoorModelsL))
    Set(LVar3, Ref(LeftDoorModelsR))
    Exec(BaseExitDoor)
    Wait(17)
    Call(GotoMap, Ref("pra_33"), pra_33_ENTRY_1)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitDoors_pra_16_2 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Set(LVar0, pra_18_ENTRY_2)
    Set(LVar1, COLLIDER_deilittnw)
    IfEq(GF_PRA_BrokeIllusion, false)
        Set(LVar2, Ref(BothRightDoorModelsL))
        Set(LVar3, Ref(BothRightDoorModelsR))
    Else
        Set(LVar2, Ref(FarRightDoorModelsL))
        Set(LVar3, Ref(FarRightDoorModelsR))
    EndIf
    Exec(BaseExitDoor)
    Wait(17)
    Call(GotoMap, Ref("pra_16"), pra_16_ENTRY_2)
    Wait(100)
    Return
    End
};

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitDoors_pra_16_1), TRIGGER_WALL_PRESS_A, COLLIDER_deilittsw, 1, 0)
    IfGe(GB_StoryProgress, STORY_CH7_DEFEATED_CLUBBAS)
        BindTrigger(Ref(EVS_ExitDoors_pra_33_1), TRIGGER_WALL_PRESS_A, COLLIDER_deilittne, 1, 0)
    EndIf
    BindTrigger(Ref(EVS_ExitDoors_pra_16_2), TRIGGER_WALL_PRESS_A, COLLIDER_deilittnw, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(pra_18_ENTRY_0)
            IfEq(GF_PRA_BrokeIllusion, false)
                Set(LVar2, Ref(BothRightDoorModelsL))
                Set(LVar3, Ref(BothRightDoorModelsR))
            Else
                Set(LVar2, Ref(NearRightDoorModelsL))
                Set(LVar3, Ref(NearRightDoorModelsR))
            EndIf
        CaseEq(pra_18_ENTRY_1)
            Set(LVar2, Ref(LeftDoorModelsL))
            Set(LVar3, Ref(LeftDoorModelsR))
        CaseEq(pra_18_ENTRY_2)
            IfEq(GF_PRA_BrokeIllusion, false)
                Set(LVar2, Ref(BothRightDoorModelsL))
                Set(LVar3, Ref(BothRightDoorModelsR))
            Else
                Set(LVar2, Ref(FarRightDoorModelsL))
                Set(LVar3, Ref(FarRightDoorModelsR))
            EndIf
    EndSwitch
    ExecWait(BaseEnterDoor)
    Exec(EVS_BindExitTriggers)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_CRYSTAL_PALACE)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(24, 24, 40)
    Call(MakeNpcs, true, Ref(DefaultNPCs))
    Exec(EVS_SetupMusic)
    IfGe(GB_StoryProgress, STORY_CH7_DEFEATED_CLUBBAS)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o1174, COLLIDER_FLAGS_UPPER_MASK)
        Call(SetGroupVisibility, MODEL_g298, MODEL_GROUP_HIDDEN)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o1175, COLLIDER_FLAGS_UPPER_MASK)
        Call(SetGroupVisibility, MODEL_g296, MODEL_GROUP_HIDDEN)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o1176, COLLIDER_FLAGS_UPPER_MASK)
        Call(SetGroupVisibility, MODEL_g297, MODEL_GROUP_HIDDEN)
    Else
        Switch(GB_PRA18_ClubbasDefeated)
            CaseEq(1)
                Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o1176, COLLIDER_FLAGS_UPPER_MASK)
                Call(SetGroupVisibility, MODEL_g297, MODEL_GROUP_HIDDEN)
            CaseEq(2)
                Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o1175, COLLIDER_FLAGS_UPPER_MASK)
                Call(SetGroupVisibility, MODEL_g296, MODEL_GROUP_HIDDEN)
                Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o1176, COLLIDER_FLAGS_UPPER_MASK)
                Call(SetGroupVisibility, MODEL_g297, MODEL_GROUP_HIDDEN)
        EndSwitch
    EndIf
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
