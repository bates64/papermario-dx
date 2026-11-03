#include "pra_20.h"
#include "world/area/pra/pra_19.h"
#include "world/area/pra/pra_21.h"
#include "world/area/pra/pra_22.h"
#include "world/area/pra/pra_29.h"

#include "../common/Reflection.inc.c"
#include "../common/Reflection.data.inc.c"
#include "../common/GlassShimmer.inc.c"

s32 NearSingleDoorModels[] = { MODEL_o999, MODEL_o1000, -1 };
s32 FarSingleDoorModels[] = { MODEL_o997, MODEL_o998, -1 };

s32 NearRightDoorModelsL[] = { MODEL_o874, MODEL_o875, -1 };
s32 NearRightDoorModelsR[] = { MODEL_o876, MODEL_o877, -1 };

s32 BackRightDoorModelsL[] = { MODEL_o880, MODEL_o881, -1 };
s32 BackRightDoorModelsR[] = { MODEL_o878, MODEL_o879, -1 };

s32 BothRightDoorModelsL[] = { MODEL_o874, MODEL_o875, MODEL_o880, MODEL_o881, -1 };
s32 BothRightDoorModelsR[] = { MODEL_o876, MODEL_o877, MODEL_o878, MODEL_o879, -1 };

s32 ModelListNone[] = { -1 };

EvtScript EVS_ExitWalk_pra_19_1 = EVT_EXIT_WALK(60, $ReflectionMimicRoom, $pra_19.MirroredDoorRoom);

EvtScript EVS_ExitDoor_pra_21_0 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Set(LVar0, $HugeStatueRoom.index)
    Set(LVar1, COLLIDER_deilittssw)
    IfEq(GF_PRA_BrokeIllusion, false)
        Set(LVar2, NearSingleDoorModels)
        Set(LVar3, FarSingleDoorModels)
    Else
        Set(LVar2, NearSingleDoorModels)
        Set(LVar3, ModelListNone)
    EndIf
    Exec(BaseExitDoor)
    Wait(17)
    Call(GotoMap, $pra_21.MirroredDoorRoom)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitDoors_pra_29_0 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Set(LVar0, $HiddenBridgeRoomSouth.index)
    Set(LVar1, COLLIDER_deilittse)
    IfEq(GF_PRA_BrokeIllusion, false)
        Set(LVar2, BothRightDoorModelsL)
        Set(LVar3, BothRightDoorModelsR)
    Else
        Set(LVar2, NearRightDoorModelsL)
        Set(LVar3, NearRightDoorModelsR)
    EndIf
    Exec(BaseExitDoor)
    Wait(17)
    Call(GotoMap, $pra_29.MirroredDoorRoomSouth)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitDoors_pra_29_3 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Set(LVar0, $HiddenBridgeRoomNorth.index)
    Set(LVar1, COLLIDER_deilittne)
    IfEq(GF_PRA_BrokeIllusion, false)
        Set(LVar2, BothRightDoorModelsL)
        Set(LVar3, BothRightDoorModelsR)
    Else
        Set(LVar2, BackRightDoorModelsL)
        Set(LVar3, BackRightDoorModelsR)
    EndIf
    Exec(BaseExitDoor)
    Wait(17)
    Call(GotoMap, $pra_29.MirroredDoorRoomNorth)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitDoor_pra_22_0 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Set(LVar0, $SmallStatueRoom.index)
    Set(LVar1, COLLIDER_deilittnnw)
    IfEq(GF_PRA_BrokeIllusion, false)
        Set(LVar2, NearSingleDoorModels)
        Set(LVar3, FarSingleDoorModels)
    Else
        Set(LVar2, ModelListNone)
        Set(LVar3, FarSingleDoorModels)
    EndIf
    Exec(BaseExitDoor)
    Wait(17)
    Call(GotoMap, $pra_22.MirroredDoorRoom)
    Wait(100)
    Return
    End
};

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_pra_19_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deilisw, 1, 0)
    BindTrigger(EVS_ExitDoor_pra_21_0, TRIGGER_WALL_PRESS_A, COLLIDER_deilittssw, 1, 0)
    BindTrigger(EVS_ExitDoors_pra_29_0, TRIGGER_WALL_PRESS_A, COLLIDER_deilittse, 1, 0)
    BindTrigger(EVS_ExitDoors_pra_29_3, TRIGGER_WALL_PRESS_A, COLLIDER_deilittne, 1, 0)
    BindTrigger(EVS_ExitDoor_pra_22_0, TRIGGER_WALL_PRESS_A, COLLIDER_deilittnnw, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($ReflectionMimicRoom.index)
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
        CaseEq($HugeStatueRoom.index)
            IfEq(GF_PRA_BrokeIllusion, false)
                Set(LVar2, NearSingleDoorModels)
                Set(LVar3, FarSingleDoorModels)
            Else
                Set(LVar2, NearSingleDoorModels)
                Set(LVar3, ModelListNone)
            EndIf
            ExecWait(BaseEnterDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq($HiddenBridgeRoomSouth.index)
            IfEq(GF_PRA_BrokeIllusion, false)
                Set(LVar2, BothRightDoorModelsL)
                Set(LVar3, BothRightDoorModelsR)
            Else
                Set(LVar2, NearRightDoorModelsL)
                Set(LVar3, NearRightDoorModelsR)
            EndIf
            ExecWait(BaseEnterDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq($HiddenBridgeRoomNorth.index)
            IfEq(GF_PRA_BrokeIllusion, false)
                Set(LVar2, BothRightDoorModelsL)
                Set(LVar3, BothRightDoorModelsR)
            Else
                Set(LVar2, BackRightDoorModelsL)
                Set(LVar3, BackRightDoorModelsR)
            EndIf
            ExecWait(BaseEnterDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq($SmallStatueRoom.index)
            IfEq(GF_PRA_BrokeIllusion, false)
                Set(LVar2, NearSingleDoorModels)
                Set(LVar3, FarSingleDoorModels)
            Else
                Set(LVar2, FarSingleDoorModels)
                Set(LVar3, ModelListNone)
            EndIf
            ExecWait(BaseEnterDoor)
            Exec(EVS_BindExitTriggers)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_CRYSTAL_PALACE)
    EVT_SETUP_CAMERA_NO_LEAD(24, 24, 40)
    Exec(EVS_SetupMusic)
    Call(EnableModel, MODEL_o981, false)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o1019, COLLIDER_FLAGS_UPPER_MASK)
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
