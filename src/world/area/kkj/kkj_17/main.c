#include "kkj_17.h"
#include "world/area/kkj/kkj_11.h"

EvtScript EVS_ExitDoors_kkj_11_5 =
    EVT_EXIT_SINGLE_DOOR($UpperHall, $kkj_11.Storeroom, COLLIDER_ttw, MODEL_o2, DOOR_SWING_OUT);

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($UpperHall.index)
            Set(LVar2, MODEL_o2)
            Set(LVar3, DOOR_SWING_OUT)
            ExecWait(EnterSingleDoor)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_PEACHS_CASTLE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMagicChest)
    Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
    BindTrigger(EVS_ExitDoors_kkj_11_5, TRIGGER_WALL_PRESS_A, COLLIDER_ttw, 1, 0)
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
