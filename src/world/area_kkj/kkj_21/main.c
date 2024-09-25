#include "kkj_21.h"

EvtScript N(EVS_ExitDoor_kkj_10_2) = EVT_EXIT_SINGLE_DOOR(kkj_21_ENTRY_0, "kkj_10", kkj_10_ENTRY_2,
    COLLIDER_tte, MODEL_o57, DOOR_SWING_IN);

EvtScript N(EVS_EnterMap) = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(kkj_21_ENTRY_0)
            Set(LVar2, MODEL_o57)
            Set(LVar3, DOOR_SWING_IN)
            ExecWait(EnterSingleDoor)
    EndSwitch
    Return
    End
};

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_PEACHS_CASTLE)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
    BindTrigger(Ref(N(EVS_ExitDoor_kkj_10_2)), TRIGGER_WALL_PRESS_A, COLLIDER_tte, 1, 0)
    Exec(N(EVS_EnterMap))
    Wait(1)
    Return
    End
};
