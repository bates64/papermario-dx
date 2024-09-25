#include "dgb_06.h"

EvtScript N(EVS_ExitDoor_dgb_04_1) = EVT_EXIT_SINGLE_DOOR_SET_SOUNDS(dgb_06_ENTRY_0, "dgb_04", dgb_04_ENTRY_1,
    COLLIDER_deilittw, MODEL_o161, DOOR_SWING_IN, DOOR_SOUNDS_BASIC);

EvtScript N(EVS_EnterMap) = {
    Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(dgb_06_ENTRY_0)
            Set(LVar2, MODEL_o161)
            Set(LVar3, DOOR_SWING_IN)
            ExecWait(EnterSingleDoor)
    EndSwitch
    Return
    End
};

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_TUBBAS_MANOR)
    Call(SetSpriteShading, SHADING_DGB_06)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, TRUE, Ref(N(DefaultNPCs)))
    ExecWait(N(EVS_MakeEntities))
    IfEq(GF_DGB05_BoardedFloor, FALSE)
        Call(EnableGroup, MODEL_g52, FALSE)
    Else
        Call(EnableGroup, MODEL_g53, FALSE)
    EndIf
    BindTrigger(Ref(N(EVS_ExitDoor_dgb_04_1)), TRIGGER_WALL_PRESS_A, COLLIDER_deilittw, 1, 0)
    Exec(N(EVS_SetupMusic))
    Exec(N(EVS_EnterMap))
    Return
    End
};
