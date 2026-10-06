#include "pra_16.h"

#include "../common/Reflection.inc.c"
#include "../common/Reflection.data.inc.c"
#include "../common/GlassShimmer.inc.c"

// doors on right wall
s32 NearRightDoorModelsL[] = { MODEL_o772, MODEL_o844, -1 };
s32 NearRightDoorModelsR[] = { MODEL_o768, MODEL_o846, -1 };
s32 FarRightDoorModelsL[]  = { MODEL_o859, MODEL_o860, -1 };
s32 FarRightDoorModelsR[]  = { MODEL_o861, MODEL_o862, -1 };
s32 BothRightDoorModelsL[] = { MODEL_o772, MODEL_o844, MODEL_o859, MODEL_o860, -1 };
s32 BothRightDoorModelsR[] = { MODEL_o768, MODEL_o846, MODEL_o861, MODEL_o862, -1 };

// doors on left wall
s32 NearLeftDoorModelsL[] = { MODEL_o874, MODEL_o875, -1 };
s32 NearLeftDoorModelsR[] = { MODEL_o876, MODEL_o877, -1 };
s32 FarLeftDoorModelsL[]  = { MODEL_o880, MODEL_o881, -1 };
s32 FarLeftDoorModelsR[]  = { MODEL_o878, MODEL_o879, -1 };
s32 BothLeftDoorModelsL[] = { MODEL_o874, MODEL_o875, MODEL_o880, MODEL_o881, -1 };
s32 BothLeftDoorModelsR[] = { MODEL_o876, MODEL_o877, MODEL_o878, MODEL_o879, -1 };

EvtScript EVS_ExitDoors_pra_02_2 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
    Set(LVar0, pra_16_ENTRY_0)
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
    Call(GotoMap, Ref("pra_02"), pra_02_ENTRY_2)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitDoors_pra_18_0 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
    Set(LVar0, pra_16_ENTRY_1)
    Set(LVar1, COLLIDER_deilittse)
    IfEq(GF_PRA_BrokeIllusion, false)
        Set(LVar2, Ref(BothLeftDoorModelsL))
        Set(LVar3, Ref(BothLeftDoorModelsR))
    Else
        Set(LVar2, Ref(NearLeftDoorModelsL))
        Set(LVar3, Ref(NearLeftDoorModelsR))
    EndIf
    Exec(BaseExitDoor)
    Wait(17)
    Call(GotoMap, Ref("pra_18"), pra_18_ENTRY_0)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitDoors_pra_18_2 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
    Set(LVar0, pra_16_ENTRY_2)
    Set(LVar1, COLLIDER_deilittne)
    IfEq(GF_PRA_BrokeIllusion, false)
        Set(LVar2, Ref(BothLeftDoorModelsL))
        Set(LVar3, Ref(BothLeftDoorModelsR))
    Else
        Set(LVar2, Ref(FarLeftDoorModelsL))
        Set(LVar3, Ref(FarLeftDoorModelsR))
    EndIf
    Exec(BaseExitDoor)
    Wait(17)
    Call(GotoMap, Ref("pra_18"), pra_18_ENTRY_2)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitDoors_pra_02_3 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
    Set(LVar0, pra_16_ENTRY_3)
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
    Call(GotoMap, Ref("pra_02"), pra_02_ENTRY_3)
    Wait(100)
    Return
    End
};

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitDoors_pra_02_2), TRIGGER_WALL_PRESS_A, COLLIDER_deilittsw, 1, 0)
    BindTrigger(Ref(EVS_ExitDoors_pra_18_0), TRIGGER_WALL_PRESS_A, COLLIDER_deilittse, 1, 0)
    BindTrigger(Ref(EVS_ExitDoors_pra_18_2), TRIGGER_WALL_PRESS_A, COLLIDER_deilittne, 1, 0)
    BindTrigger(Ref(EVS_ExitDoors_pra_02_3), TRIGGER_WALL_PRESS_A, COLLIDER_deilittnw, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(pra_16_ENTRY_0)
            Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
            IfEq(GF_PRA_BrokeIllusion, false)
                Set(LVar2, Ref(BothRightDoorModelsL))
                Set(LVar3, Ref(BothRightDoorModelsR))
            Else
                Set(LVar2, Ref(NearRightDoorModelsL))
                Set(LVar3, Ref(NearRightDoorModelsR))
            EndIf
        CaseEq(pra_16_ENTRY_1)
            Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
            IfEq(GF_PRA_BrokeIllusion, false)
                Set(LVar2, Ref(BothLeftDoorModelsL))
                Set(LVar3, Ref(BothLeftDoorModelsR))
            Else
                Set(LVar2, Ref(NearLeftDoorModelsL))
                Set(LVar3, Ref(NearLeftDoorModelsR))
            EndIf
        CaseEq(pra_16_ENTRY_2)
            Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
            IfEq(GF_PRA_BrokeIllusion, false)
                Set(LVar2, Ref(BothLeftDoorModelsL))
                Set(LVar3, Ref(BothLeftDoorModelsR))
            Else
                Set(LVar2, Ref(FarLeftDoorModelsL))
                Set(LVar3, Ref(FarLeftDoorModelsR))
            EndIf
        CaseEq(pra_16_ENTRY_3)
            Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
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
