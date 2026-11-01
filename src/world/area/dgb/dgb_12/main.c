#include "dgb_12.h"
#include "world/area/dgb/dgb_09.h"

EvtScript EVS_ExitDoor_dgb_09_2 = EVT_EXIT_SINGLE_DOOR_SET_SOUNDS(
    $Dgb09, $dgb_09.Dgb12, COLLIDER_deilits, MODEL_o158, DOOR_SWING_IN, DOOR_SOUNDS_BASIC
);

EvtScript EVS_EnterMap = {
    Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($Dgb09.index)
            Set(LVar2, MODEL_o158)
            Set(LVar3, DOOR_SWING_IN)
            ExecWait(EnterSingleDoor)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_TUBBAS_MANOR)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupSpikes)
    Exec(EVS_SetupMusic)
    BindTrigger(EVS_ExitDoor_dgb_09_2, TRIGGER_WALL_PRESS_A, COLLIDER_deilits, 1, 0)
    Exec(EVS_EnterMap)
    Return
    End
};
