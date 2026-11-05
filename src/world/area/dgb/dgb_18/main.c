#include "dgb_18.h"
#include "world/area/dgb/dgb_01.h"

EvtScript EVS_ExitDoors_dgb_01_6 = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(
    $Dgb01, $dgb_01.Dgb18, COLLIDER_deilittw, MODEL_o140, MODEL_o141, DOOR_SOUNDS_CREAKY
);

EvtScript EVS_EnterMap = {
    Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($Dgb01.index)
            Set(LVar2, MODEL_o140)
            Set(LVar3, MODEL_o141)
            ExecWait(EnterDoubleDoor)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Call(MakeNpcs, true, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    BindTrigger(EVS_ExitDoors_dgb_01_6, TRIGGER_WALL_PRESS_A, COLLIDER_deilittw, 1, 0)
    Exec(EVS_EnterMap)
    Return
    End
};
