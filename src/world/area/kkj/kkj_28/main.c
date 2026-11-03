#include "kkj_28.h"
#include "world/area/kkj/kkj_10.h"

EvtScript EVS_ExitDoor_kkj_10_2 =
    EVT_EXIT_SINGLE_DOOR($EntryHall, $kkj_10.QuizRoom, COLLIDER_tte, MODEL_o162, DOOR_SWING_IN);

EvtScript EVS_EnterMap = {
    Set(LVar2, MODEL_o162)
    Set(LVar3, DOOR_SWING_IN)
    ExecWait(EnterSingleDoor)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_PEACHS_CASTLE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(EnableGroup, MODEL_g40, false)
    Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
    BindTrigger(EVS_ExitDoor_kkj_10_2, TRIGGER_WALL_PRESS_A, COLLIDER_tte, 1, 0)
    Exec(EVS_EnterMap)
    Return
    End
};
