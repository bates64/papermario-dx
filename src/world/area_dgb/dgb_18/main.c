#include "dgb_18.h"

EvtScript N(EVS_ExitDoors_dgb_01_6) = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(dgb_18_ENTRY_0, "dgb_01", dgb_01_ENTRY_6,
    COLLIDER_deilittw, MODEL_o140, MODEL_o141, DOOR_SOUNDS_CREAKY);

EvtScript N(EVS_EnterMap) = {
    Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(dgb_18_ENTRY_0)
            Set(LVar2, MODEL_o140)
            Set(LVar3, MODEL_o141)
            ExecWait(EnterDoubleDoor)
    EndSwitch
    Return
    End
};

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_TUBBAS_MANOR)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, TRUE, Ref(N(DefaultNPCs)))
    ExecWait(N(EVS_MakeEntities))
    Exec(N(EVS_SetupMusic))
    BindTrigger(Ref(N(EVS_ExitDoors_dgb_01_6)), TRIGGER_WALL_PRESS_A, COLLIDER_deilittw, 1, 0)
    Exec(N(EVS_EnterMap))
    Return
    End
};
