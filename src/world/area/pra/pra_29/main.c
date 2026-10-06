#include "pra_29.h"

#include "../common/Reflection.inc.c"
#include "../common/Reflection.data.inc.c"

#include "../common/GlassShimmer.inc.c"

s32 NearLeftDoorModelsL[] = { MODEL_o772, -1 };
s32 NearLeftDoorModelsR[] = { MODEL_o768, -1 };
s32 FarLeftDoorModelsL[]  = { MODEL_o859, -1 };
s32 FarLeftDoorModelsR[]  = { MODEL_o861, -1 };
s32 BothLeftDoorModelsL[] = { MODEL_o772, MODEL_o859, -1 };
s32 BothLeftDoorModelsR[] = { MODEL_o768, MODEL_o861, -1 };

s32 NearRightDoorModelsL[] = { MODEL_o995, -1 };
s32 NearRightDoorModelsR[] = { MODEL_o997, -1 };
s32 FarRightDoorModelsL[]  = { MODEL_o1096, -1 };
s32 FarRightDoorModelsR[]  = { MODEL_o1094, -1 };
s32 BothRightDoorModelsL[] = { MODEL_o995, MODEL_o1096, -1 };
s32 BothRightDoorModelsR[] = { MODEL_o997, MODEL_o1094, -1 };

EvtScript EVS_ExitDoors_pra_20_2 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Set(LVar0, pra_29_ENTRY_0)
    Set(LVar1, COLLIDER_deilittsw)
    IfEq(GF_PRA_BrokeIllusion, false)
        Set(LVar2, Ref(BothLeftDoorModelsL))
        Set(LVar3, Ref(BothLeftDoorModelsR))
    Else
        Set(LVar2, Ref(NearLeftDoorModelsL))
        Set(LVar3, Ref(NearLeftDoorModelsR))
    EndIf
    Exec(BaseExitDoor)
    Wait(17)
    Call(GotoMap, Ref("pra_20"), pra_20_ENTRY_2)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitDoors_pra_34_0 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Set(LVar0, pra_29_ENTRY_1)
    Set(LVar1, COLLIDER_deilittse)
    IfEq(GF_PRA_BrokeIllusion, false)
        Set(LVar2, Ref(BothRightDoorModelsL))
        Set(LVar3, Ref(BothRightDoorModelsR))
    Else
        Set(LVar2, Ref(NearRightDoorModelsL))
        Set(LVar3, Ref(NearRightDoorModelsR))
    EndIf
    Exec(BaseExitDoor)
    Wait(17)
    Call(GotoMap, Ref("pra_34"), pra_34_ENTRY_0)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitDoors_pra_34_3 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Set(LVar0, pra_29_ENTRY_2)
    Set(LVar1, COLLIDER_deilittne)
    IfEq(GF_PRA_BrokeIllusion, false)
        Set(LVar2, Ref(BothRightDoorModelsL))
        Set(LVar3, Ref(BothRightDoorModelsR))
    Else
        Set(LVar2, Ref(FarRightDoorModelsL))
        Set(LVar3, Ref(FarRightDoorModelsR))
    EndIf
    Exec(BaseExitDoor)
    Wait(17)
    Call(GotoMap, Ref("pra_34"), pra_34_ENTRY_3)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitDoors_pra_20_3 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Set(LVar0, pra_29_ENTRY_3)
    Set(LVar1, COLLIDER_deilittnw)
    IfEq(GF_PRA_BrokeIllusion, false)
        Set(LVar2, Ref(BothLeftDoorModelsL))
        Set(LVar3, Ref(BothLeftDoorModelsR))
    Else
        Set(LVar2, Ref(FarLeftDoorModelsL))
        Set(LVar3, Ref(FarLeftDoorModelsR))
    EndIf
    Exec(BaseExitDoor)
    Wait(17)
    Call(GotoMap, Ref("pra_20"), pra_20_ENTRY_3)
    Wait(100)
    Return
    End
};

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitDoors_pra_20_2), TRIGGER_WALL_PRESS_A, COLLIDER_deilittsw, 1, 0)
    BindTrigger(Ref(EVS_ExitDoors_pra_34_0), TRIGGER_WALL_PRESS_A, COLLIDER_deilittse, 1, 0)
    BindTrigger(Ref(EVS_ExitDoors_pra_34_3), TRIGGER_WALL_PRESS_A, COLLIDER_deilittne, 1, 0)
    BindTrigger(Ref(EVS_ExitDoors_pra_20_3), TRIGGER_WALL_PRESS_A, COLLIDER_deilittnw, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(pra_29_ENTRY_0)
            IfEq(GF_PRA_BrokeIllusion, false)
                Set(LVar2, Ref(BothLeftDoorModelsL))
                Set(LVar3, Ref(BothLeftDoorModelsR))
            Else
                Set(LVar2, Ref(NearLeftDoorModelsL))
                Set(LVar3, Ref(NearLeftDoorModelsR))
            EndIf
        CaseEq(pra_29_ENTRY_1)
            IfEq(GF_PRA_BrokeIllusion, false)
                Set(LVar2, Ref(BothRightDoorModelsL))
                Set(LVar3, Ref(BothRightDoorModelsR))
            Else
                Set(LVar2, Ref(NearRightDoorModelsL))
                Set(LVar3, Ref(NearRightDoorModelsR))
            EndIf
        CaseEq(pra_29_ENTRY_2)
            IfEq(GF_PRA_BrokeIllusion, false)
                Set(LVar2, Ref(BothRightDoorModelsL))
                Set(LVar3, Ref(BothRightDoorModelsR))
            Else
                Set(LVar2, Ref(FarRightDoorModelsL))
                Set(LVar3, Ref(FarRightDoorModelsR))
            EndIf
        CaseEq(pra_29_ENTRY_3)
            IfEq(GF_PRA_BrokeIllusion, false)
                Set(LVar2, Ref(BothLeftDoorModelsL))
                Set(LVar3, Ref(BothLeftDoorModelsR))
            Else
                Set(LVar2, Ref(FarLeftDoorModelsL))
                Set(LVar3, Ref(FarLeftDoorModelsR))
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
    EVT_SETUP_CAMERA_DEFAULT(24, 24, 40)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    Exec(EVS_SetupBridge)
    Set(LVar0, MODEL_o945)
    Set(LVar1, MODEL_o945)
    Set(LVar2, TEX_PANNER_0)
    Exec(EVS_GlassShimmer)
    Set(LVar0, REFLECTION_WALL_ONLY)
    IfGe(GB_StoryProgress, STORY_CH7_EXTENDED_PALACE_BRIDGE)
        Set(LVar1, true)
    Else
        Set(LVar1, false)
    EndIf
    Exec(EVS_SetupReflections)
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
