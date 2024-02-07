#include "kkj_17.h"

EvtScript N(EVS_ExitDoors_kkj_11_5) = EVT_EXIT_SINGLE_DOOR(kkj_17_ENTRY_0, "kkj_11", kkj_11_ENTRY_5,
    COLLIDER_ttw, MODEL_o2, DOOR_SWING_OUT);

EvtScript N(EVS_EnterMap) = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(kkj_17_ENTRY_0)
            Set(LVar2, MODEL_o2)
            Set(LVar3, DOOR_SWING_OUT)
            ExecWait(EnterSingleDoor)
    EndSwitch
    Return
    End
};

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_PEACHS_CASTLE)
    Call(SetSpriteShading, SHADING_KKJ_17)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    ExecWait(N(EVS_MakeEntities))
    Exec(N(EVS_SetupMagicChest))
    Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
    BindTrigger(Ref(N(EVS_ExitDoors_kkj_11_5)), TRIGGER_WALL_PRESS_A, COLLIDER_ttw, 1, 0)
    Exec(N(EVS_EnterMap))
    Wait(1)
    Return
    End
};
