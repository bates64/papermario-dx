#include "pra_02.h"

#include "../common/Reflection.inc.c"
#include "../common/Reflection.data.inc.c"
#include "../common/GlassShimmer.inc.c"

EvtScript EVS_UpdateShiftingWallPos = {
    Call(TranslateGroup, MODEL_g293, 0, 250, 0)
    Call(TranslateGroup, MODEL_g291, 0, MV_WallPosOffset, 0)
    Return
    End
};

s32 NearLeftDoorModelsL[] = { MODEL_o772, MODEL_o844, -1 };
s32 NearLeftDoorModelsR[] = { MODEL_o768, MODEL_o846, -1 };
s32 FarLeftDoorModelsL[] = { MODEL_o859, -1 };
s32 FarLeftDoorModelsR[] = { MODEL_o861, -1 };
s32 BothLeftDoorModelsL[] = { MODEL_o772, MODEL_o844, MODEL_o859, -1 };
s32 BothLeftDoorModelsR[] = { MODEL_o768, MODEL_o846, MODEL_o861, -1 };

s32 FarBlueDoorModelsL[] = { MODEL_o1162, -1 };
s32 FarBlueDoorModelsR[] = { MODEL_o1160, -1 };
s32 FarRedDoorModelsL[] = { MODEL_o952, -1 };
s32 FarRedDoorModelsR[] = { MODEL_o950, -1 };

s32 NearBlueDoorModelsL[] = { MODEL_o1156, -1 };
s32 NearBlueDoorModelsR[] = { MODEL_o1158, -1 };
s32 NearRedDoorModelsL[] = { MODEL_o946, -1 };
s32 NearRedDoorModelsR[] = { MODEL_o948, -1 };

s32 BothBlueDoorModelsL[] = { MODEL_o1156, MODEL_o1162, -1 };
s32 BothBlueDoorModelsR[] = { MODEL_o1158, MODEL_o1160, -1 };
s32 BothRedDoorModelsL[] = { MODEL_o946, MODEL_o952, -1 };
s32 BothRedDoorModelsR[] = { MODEL_o948, MODEL_o950, -1 };

s32 NearCenterDoorModels[] = { MODEL_o847, -1 };
s32 FarCenterDoorModels[] = { MODEL_o774, -1 };
s32 EmptyModelList[] = { -1 };

EvtScript EVS_ExitDoors_pra_01_1 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
    Set(LVar0, pra_02_ENTRY_0)
    Set(LVar1, 24)
    IfEq(GF_PRA_BrokeIllusion, false)
        Set(LVar2, Ref(BothLeftDoorModelsL))
        Set(LVar3, Ref(BothLeftDoorModelsR))
    Else
        Set(LVar2, Ref(NearLeftDoorModelsL))
        Set(LVar3, Ref(NearLeftDoorModelsR))
    EndIf
    Exec(BaseExitDoor)
    Wait(17)
    Call(GotoMap, Ref("pra_01"), pra_01_ENTRY_1)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitDoors_pra_03_0 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
    Set(LVar0, pra_02_ENTRY_1)
    Set(LVar1, 56)
    IfEq(GF_PRA_BrokeIllusion, false)
        Set(LVar2, Ref(NearCenterDoorModels))
        Set(LVar3, Ref(FarCenterDoorModels))
    Else
        Set(LVar2, Ref(NearCenterDoorModels))
        Set(LVar3, Ref(EmptyModelList))
    EndIf
    Exec(BaseExitDoor)
    Wait(17)
    Call(GotoMap, Ref("pra_03"), pra_03_ENTRY_0)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitDoors_pra_16_0 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
    Set(LVar0, pra_02_ENTRY_2)
    Set(LVar1, 36)
    IfEq(GF_PRA_BrokeIllusion, false)
        Set(LVar2, Ref(BothRedDoorModelsL))
        Set(LVar3, Ref(BothRedDoorModelsR))
    Else
        Set(LVar2, Ref(NearRedDoorModelsL))
        Set(LVar3, Ref(NearRedDoorModelsR))
    EndIf
    Exec(BaseExitDoor)
    Wait(17)
    Call(GotoMap, Ref("pra_16"), pra_16_ENTRY_0)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitDoors_pra_13_0 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
    Set(LVar0, pra_02_ENTRY_2)
    Set(LVar1, 36)
    IfEq(GF_PRA_BrokeIllusion, false)
        Set(LVar2, Ref(BothBlueDoorModelsL))
        Set(LVar3, Ref(BothBlueDoorModelsR))
    Else
        Set(LVar2, Ref(NearBlueDoorModelsL))
        Set(LVar3, Ref(NearBlueDoorModelsR))
    EndIf
    Exec(BaseExitDoor)
    Wait(17)
    Call(GotoMap, Ref("pra_13"), pra_13_ENTRY_0)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitDoors_pra_16_3 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
    Set(LVar0, pra_02_ENTRY_3)
    Set(LVar1, 32)
    IfEq(GF_PRA_BrokeIllusion, false)
        Set(LVar2, Ref(BothRedDoorModelsL))
        Set(LVar3, Ref(BothRedDoorModelsR))
    Else
        Set(LVar2, Ref(FarRedDoorModelsL))
        Set(LVar3, Ref(FarRedDoorModelsR))
    EndIf
    Exec(BaseExitDoor)
    Wait(17)
    Call(GotoMap, Ref("pra_16"), pra_16_ENTRY_3)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitDoors_pra_13_3 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
    Set(LVar0, pra_02_ENTRY_3)
    Set(LVar1, 32)
    IfEq(GF_PRA_BrokeIllusion, false)
        Set(LVar2, Ref(BothBlueDoorModelsL))
        Set(LVar3, Ref(BothBlueDoorModelsR))
    Else
        Set(LVar2, Ref(FarBlueDoorModelsL))
        Set(LVar3, Ref(FarBlueDoorModelsR))
    EndIf
    Exec(BaseExitDoor)
    Wait(17)
    Call(GotoMap, Ref("pra_13"), pra_13_ENTRY_3)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitDoors_pra_04_0 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
    Set(LVar0, pra_02_ENTRY_4)
    Set(LVar1, 51)
    IfEq(GF_PRA_BrokeIllusion, false)
        Set(LVar2, Ref(NearCenterDoorModels))
        Set(LVar3, Ref(FarCenterDoorModels))
    Else
        Set(LVar2, Ref(EmptyModelList))
        Set(LVar3, Ref(FarCenterDoorModels))
    EndIf
    Exec(BaseExitDoor)
    Wait(17)
    Call(GotoMap, Ref("pra_04"), pra_04_ENTRY_0)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitDoors_pra_01_2 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
    Set(LVar0, pra_02_ENTRY_5)
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
    Call(GotoMap, Ref("pra_01"), pra_01_ENTRY_2)
    Wait(100)
    Return
    End
};

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitDoors_pra_01_1), TRIGGER_WALL_PRESS_A, COLLIDER_deilittsw, 1, 0)
    BindTrigger(Ref(EVS_ExitDoors_pra_03_0), TRIGGER_WALL_PRESS_A, COLLIDER_deilittssw, 1, 0)
    IfEq(GF_PRA02_DoorColorToggle, false)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilittse2, COLLIDER_FLAGS_UPPER_MASK)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilittne2, COLLIDER_FLAGS_UPPER_MASK)
    Else
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilittse, COLLIDER_FLAGS_UPPER_MASK)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilittne, COLLIDER_FLAGS_UPPER_MASK)
    EndIf
    IfEq(GF_PRA02_UnlockedRedDoor, true)
        BindTrigger(Ref(EVS_ExitDoors_pra_16_0), TRIGGER_WALL_PRESS_A, COLLIDER_deilittse, 1, 0)
        BindTrigger(Ref(EVS_ExitDoors_pra_16_3), TRIGGER_WALL_PRESS_A, COLLIDER_deilittne, 1, 0)
    EndIf
    IfEq(GF_PRA02_UnlockedBlueDoor, true)
        BindTrigger(Ref(EVS_ExitDoors_pra_13_0), TRIGGER_WALL_PRESS_A, COLLIDER_deilittse2, 1, 0)
        BindTrigger(Ref(EVS_ExitDoors_pra_13_3), TRIGGER_WALL_PRESS_A, COLLIDER_deilittne2, 1, 0)
    EndIf
    BindTrigger(Ref(EVS_ExitDoors_pra_04_0), TRIGGER_WALL_PRESS_A, COLLIDER_deilittnnw, 1, 0)
    BindTrigger(Ref(EVS_ExitDoors_pra_01_2), TRIGGER_WALL_PRESS_A, COLLIDER_deilittnw, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(pra_02_ENTRY_0)
            Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
            IfEq(GF_PRA02_Visited, false)
                Set(GF_PRA02_Visited, true)
                Set(GB_StoryProgress, STORY_CH7_ARRIVED_AT_CRYSTAL_PALACE)
            EndIf
            IfEq(GF_PRA_BrokeIllusion, false)
                Set(LVar2, Ref(BothLeftDoorModelsL))
                Set(LVar3, Ref(BothLeftDoorModelsR))
            Else
                Set(LVar2, Ref(NearLeftDoorModelsL))
                Set(LVar3, Ref(NearLeftDoorModelsR))
            EndIf
        CaseEq(pra_02_ENTRY_1)
            Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
            IfEq(GF_PRA_BrokeIllusion, false)
                Set(LVar2, Ref(NearCenterDoorModels))
                Set(LVar3, Ref(FarCenterDoorModels))
            Else
                Set(LVar2, Ref(NearCenterDoorModels))
                Set(LVar3, Ref(EmptyModelList))
            EndIf
        CaseEq(pra_02_ENTRY_2)
            Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
            IfEq(GF_PRA02_DoorColorToggle, false)
                IfEq(GF_PRA_BrokeIllusion, false)
                    Set(LVar2, Ref(BothRedDoorModelsL))
                    Set(LVar3, Ref(BothRedDoorModelsR))
                Else
                    Set(LVar2, Ref(NearRedDoorModelsL))
                    Set(LVar3, Ref(NearRedDoorModelsR))
                EndIf
            Else
                IfEq(GF_PRA_BrokeIllusion, false)
                    Set(LVar2, Ref(BothBlueDoorModelsL))
                    Set(LVar3, Ref(BothBlueDoorModelsR))
                Else
                    Set(LVar2, Ref(NearBlueDoorModelsL))
                    Set(LVar3, Ref(NearBlueDoorModelsR))
                EndIf
            EndIf
        CaseEq(pra_02_ENTRY_3)
            Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
            IfEq(GF_PRA02_DoorColorToggle, false)
                IfEq(GF_PRA_BrokeIllusion, false)
                    Set(LVar2, Ref(BothRedDoorModelsL))
                    Set(LVar3, Ref(BothRedDoorModelsR))
                Else
                    Set(LVar2, Ref(FarRedDoorModelsL))
                    Set(LVar3, Ref(FarRedDoorModelsR))
                EndIf
            Else
                IfEq(GF_PRA_BrokeIllusion, false)
                    Set(LVar2, Ref(BothBlueDoorModelsL))
                    Set(LVar3, Ref(BothBlueDoorModelsR))
                Else
                    Set(LVar2, Ref(FarBlueDoorModelsL))
                    Set(LVar3, Ref(FarBlueDoorModelsR))
                EndIf
            EndIf
        CaseEq(pra_02_ENTRY_4)
            Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
            IfEq(GF_PRA_BrokeIllusion, false)
                Set(LVar2, Ref(NearCenterDoorModels))
                Set(LVar3, Ref(FarCenterDoorModels))
            Else
                Set(LVar2, Ref(EmptyModelList))
                Set(LVar3, Ref(FarCenterDoorModels))
            EndIf
        CaseEq(pra_02_ENTRY_5)
            Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
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
    IfEq(GF_PRA02_DoorColorToggle, false)
        Set(MV_WallPosOffset, 0)
        Call(SetGroupVisibility, MODEL_g308, MODEL_GROUP_HIDDEN)
    Else
        Set(MV_WallPosOffset, -250)
        Call(SetGroupVisibility, MODEL_g307, MODEL_GROUP_HIDDEN)
    EndIf
    Exec(EVS_UpdateShiftingWallPos)
    BindTrigger(Ref(EVS_ManagePoundableSwitch), TRIGGER_FLOOR_TOUCH, COLLIDER_o1342, 1, 0)
    BindTrigger(Ref(EVS_ManagePoundableSwitch), TRIGGER_FLOOR_TOUCH, COLLIDER_o1344, 1, 0)
    Set(LVar0, MODEL_o549)
    Set(LVar1, MODEL_o549)
    Set(LVar2, TEX_PANNER_0)
    Exec(EVS_GlassShimmer)
    Set(LVar0, REFLECTION_WALL_ONLY)
    Set(LVar1, GF_PRA_BrokeIllusion)
    Exec(EVS_SetupReflections)
    Exec(EVS_EnterMap)
    Wait(1)
    Exec(EVS_SetupMusic)
    Return
    End
};
