#include "dgb_12.h"

EvtScript N(EVS_ExitDoor_dgb_09_2) = EVT_EXIT_SINGLE_DOOR_SET_SOUNDS(dgb_12_ENTRY_0, "dgb_09", dgb_09_ENTRY_2,
    COLLIDER_deilits, MODEL_o158, DOOR_SWING_IN, DOOR_SOUNDS_BASIC);

EvtScript N(EVS_EnterMap) = {
    Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(dgb_12_ENTRY_0)
            Set(LVar2, MODEL_o158)
            Set(LVar3, DOOR_SWING_IN)
            ExecWait(EnterSingleDoor)
    EndSwitch
    Return
    End
};

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_TUBBAS_MANOR)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    ExecWait(N(EVS_MakeEntities))
    Exec(N(EVS_SetupSpikes))
    Exec(N(EVS_SetupMusic))
    BindTrigger(Ref(N(EVS_ExitDoor_dgb_09_2)), TRIGGER_WALL_PRESS_A, COLLIDER_deilits, 1, 0)
    Exec(N(EVS_EnterMap))
    Return
    End
};
