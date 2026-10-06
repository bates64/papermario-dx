#include "pra_34.h"

#include "../common/Reflection.inc.c"
#include "../common/Reflection.data.inc.c"

#include "../common/GlassShimmer.inc.c"

s32 NearLeftDoorModelsL[] = { MODEL_o1012, MODEL_o1013, -1 };
s32 NearLeftDoorModelsR[] = { MODEL_o1014, MODEL_o1015, -1 };
s32 FarLeftDoorModelsL[]  = { MODEL_o1010, MODEL_o1011, -1 };
s32 FarLeftDoorModelsR[]  = { MODEL_o1008, MODEL_o1009, -1 };
s32 BothLeftDoorModelsL[] = { MODEL_o1012, MODEL_o1013, MODEL_o1010, MODEL_o1011, -1 };
s32 BothLeftDoorModelsR[] = { MODEL_o1014, MODEL_o1015, MODEL_o1008, MODEL_o1009, -1 };

s32 NearRightDoorModelsL[] = { MODEL_o874, MODEL_o875, -1 };
s32 NearRightDoorModelsR[] = { MODEL_o876, MODEL_o877, -1 };
s32 FarRightDoorModelsL[]  = { MODEL_o880, MODEL_o881, -1 };
s32 FarRightDoorModelsR[]  = { MODEL_o878, MODEL_o879, -1 };
s32 BothRightDoorModelsL[] = { MODEL_o874, MODEL_o875, MODEL_o880, MODEL_o881, -1 };
s32 BothRightDoorModelsR[] = { MODEL_o876, MODEL_o877, MODEL_o878, MODEL_o879, -1 };

EvtScript EVS_ExitDoors_pra_29_1 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Set(LVar0, pra_34_ENTRY_0)
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
    Call(GotoMap, Ref("pra_29"), pra_29_ENTRY_1)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitDoors_pra_31_0 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Set(LVar0, pra_34_ENTRY_1)
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
    Call(GotoMap, Ref("pra_31"), pra_31_ENTRY_0)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitDoors_pra_31_2 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Set(LVar0, pra_34_ENTRY_2)
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
    Call(GotoMap, Ref("pra_31"), pra_31_ENTRY_2)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitDoors_pra_29_2 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Set(LVar0, pra_34_ENTRY_3)
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
    Call(GotoMap, Ref("pra_29"), pra_29_ENTRY_2)
    Wait(100)
    Return
    End
};

ITEM_LIST(PalaceKeyList, ITEM_CRYSTAL_PALACE_KEY);

EvtScript EVS_UnlockPrompt_Doors = {
    SetGroup(EVT_GROUP_NEVER_PAUSE)
    SuspendGroup(EVT_GROUP_FLAG_INTERACT)
    Call(ShowKeyChoicePopup)
    IfEq(LVar0, ITEM_CHOICE_NONE)
        Call(ShowMessageAtScreenPos, MSG_Menus_00D8, 160, 40)
        Call(CloseChoicePopup)
        ResumeGroup(EVT_GROUP_FLAG_INTERACT)
        Return
    EndIf
    IfEq(LVar0, ITEM_CHOICE_CANCELED)
        Call(CloseChoicePopup)
        ResumeGroup(EVT_GROUP_FLAG_INTERACT)
        Return
    EndIf
    Call(RemoveKeyItemAt, LVar1)
    Call(CloseChoicePopup)
    Set(GF_PRA34_UnlockedDoor, true)
    Call(GetEntityPosition, MV_FarPadlockEntityID, LVar0, LVar1, LVar2)
    Call(PlaySoundAt, SOUND_USE_KEY, SOUND_SPACE_DEFAULT, LVar0, LVar1, LVar2)
    Call(GetEntityPosition, MV_NearPadlockEntityID, LVar0, LVar1, LVar2)
    Call(PlaySoundAt, SOUND_USE_KEY, SOUND_SPACE_DEFAULT, LVar0, LVar1, LVar2)
    Call(SetEntityUsed, MV_FarPadlockEntityID)
    Call(SetEntityUsed, MV_NearPadlockEntityID)
    ResumeGroup(EVT_GROUP_FLAG_INTERACT)
    Unbind
    Return
    End
};

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitDoors_pra_29_1), TRIGGER_WALL_PRESS_A, COLLIDER_deilittsw, 1, 0)
    BindTrigger(Ref(EVS_ExitDoors_pra_29_2), TRIGGER_WALL_PRESS_A, COLLIDER_deilittnw, 1, 0)
    IfEq(GF_PRA34_UnlockedDoor, false)
        BindPadlock(Ref(EVS_UnlockPrompt_Doors), TRIGGER_WALL_PRESS_A, EVT_ENTITY_INDEX(0), Ref(PalaceKeyList), 0, 1)
        BindPadlock(Ref(EVS_UnlockPrompt_Doors), TRIGGER_WALL_PRESS_A, EVT_ENTITY_INDEX(1), Ref(PalaceKeyList), 0, 1)
    Else
        BindTrigger(Ref(EVS_ExitDoors_pra_31_0), TRIGGER_WALL_PRESS_A, COLLIDER_deilittse, 1, 0)
        BindTrigger(Ref(EVS_ExitDoors_pra_31_2), TRIGGER_WALL_PRESS_A, COLLIDER_deilittne, 1, 0)
    EndIf
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(pra_34_ENTRY_0)
            IfEq(GF_PRA_BrokeIllusion, false)
                Set(LVar2, Ref(BothLeftDoorModelsL))
                Set(LVar3, Ref(BothLeftDoorModelsR))
            Else
                Set(LVar2, Ref(NearLeftDoorModelsL))
                Set(LVar3, Ref(NearLeftDoorModelsR))
            EndIf
        CaseEq(pra_34_ENTRY_1)
            IfEq(GF_PRA_BrokeIllusion, false)
                Set(LVar2, Ref(BothRightDoorModelsL))
                Set(LVar3, Ref(BothRightDoorModelsR))
            Else
                Set(LVar2, Ref(NearRightDoorModelsL))
                Set(LVar3, Ref(NearRightDoorModelsR))
            EndIf
        CaseEq(pra_34_ENTRY_2)
            IfEq(GF_PRA_BrokeIllusion, false)
                Set(LVar2, Ref(BothRightDoorModelsL))
                Set(LVar3, Ref(BothRightDoorModelsR))
            Else
                Set(LVar2, Ref(FarRightDoorModelsL))
                Set(LVar3, Ref(FarRightDoorModelsR))
            EndIf
        CaseEq(pra_34_ENTRY_3)
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
    EVT_SETUP_CAMERA_NO_LEAD(24, 24, 40)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    Set(LVar0, MODEL_o945)
    Set(LVar1, MODEL_o947)
    Set(LVar2, TEX_PANNER_0)
    Exec(EVS_GlassShimmer)
    Set(LVar0, REFLECTION_FLOOR_WALL)
    Set(LVar1, GF_PRA_BrokeIllusion)
    Exec(EVS_SetupReflections)
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
