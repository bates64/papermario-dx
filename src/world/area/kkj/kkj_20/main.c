#include "kkj_20.h"
#include "world/area/kkj/kkj_10.h"

EvtScript EVS_ExitDoor_kkj_10_4 =
    EVT_EXIT_SINGLE_DOOR($EntryHall, $kkj_10.GuestRoom, COLLIDER_ttw, MODEL_o9, DOOR_SWING_IN);

EvtScript EVS_EnterMap = {
    Set(LVar0, $EntryHall.index)
    Set(LVar2, MODEL_o9)
    Set(LVar3, DOOR_SWING_IN)
    ExecWait(EnterSingleDoor)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_PEACHS_CASTLE)
    Call(SetSpriteShading, SHADING_KKJ_20)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, false, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
    BindTrigger(EVS_ExitDoor_kkj_10_4, TRIGGER_WALL_PRESS_A, COLLIDER_ttw, 1, 0)
    Exec(EVS_EnterMap)
    Return
    End
};
