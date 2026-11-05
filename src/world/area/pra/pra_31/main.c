#include "pra_31.h"
#include "world/area/pra/pra_34.h"
#include "world/area/pra/pra_40.h"

s32 NearLeftDoorModelsL[] = { MODEL_o772, -1 };
s32 NearLeftDoorModelsR[] = { MODEL_o768, -1 };
s32 RightDoorModelsL[] = { MODEL_o955, -1 };
s32 RightDoorModelsR[] = { MODEL_o957, -1 };
s32 FarLeftDoorModelsL[] = { MODEL_o859, -1 };
s32 FarLeftDoorModelsR[] = { MODEL_o861, -1 };

EvtScript EVS_ExitDoors_pra_34_1 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Set(LVar0, $MirrorHoleRoomSouth.index)
    Set(LVar1, COLLIDER_deilittsw)
    Set(LVar2, NearLeftDoorModelsL)
    Set(LVar3, NearLeftDoorModelsR)
    Exec(BaseExitDoor)
    Wait(17)
    Call(GotoMap, $pra_34.DinoPuzzleRoomSouth)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitDoors_pra_40_0 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Set(LVar0, $BossAntechamber.index)
    Set(LVar1, COLLIDER_deilitte)
    Set(LVar2, RightDoorModelsL)
    Set(LVar3, RightDoorModelsR)
    Exec(BaseExitDoor)
    Wait(17)
    Call(GotoMap, $pra_40.DinoPuzzleRoom)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitDoors_pra_34_2 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Set(LVar0, $MirrorHoleRoomNorth.index)
    Set(LVar1, COLLIDER_deilittnw)
    Set(LVar2, FarLeftDoorModelsL)
    Set(LVar3, FarLeftDoorModelsR)
    Exec(BaseExitDoor)
    Wait(17)
    Call(GotoMap, $pra_34.DinoPuzzleRoomNorth)
    Wait(100)
    Return
    End
};

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitDoors_pra_34_1, TRIGGER_WALL_PRESS_A, COLLIDER_deilittsw, 1, 0)
    BindTrigger(EVS_ExitDoors_pra_40_0, TRIGGER_WALL_PRESS_A, COLLIDER_deilitte, 1, 0)
    BindTrigger(EVS_ExitDoors_pra_34_2, TRIGGER_WALL_PRESS_A, COLLIDER_deilittnw, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($MirrorHoleRoomSouth.index)
            Set(LVar2, NearLeftDoorModelsL)
            Set(LVar3, NearLeftDoorModelsR)
        CaseEq($BossAntechamber.index)
            Set(LVar2, RightDoorModelsL)
            Set(LVar3, RightDoorModelsR)
        CaseEq($MirrorHoleRoomNorth.index)
            Set(LVar2, FarLeftDoorModelsL)
            Set(LVar3, FarLeftDoorModelsR)
    EndSwitch
    ExecWait(BaseEnterDoor)
    Exec(EVS_BindExitTriggers)
    Return
    End
};

EvtScript EVS_Main = {
    Call(MakeNpcs, true, DefaultNPCs)
    ExecWait(EVS_SetupPuzzle)
    Exec(EVS_SetupMusic)
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
