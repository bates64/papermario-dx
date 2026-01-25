#include "kkj_20.h"

EvtScript N(EVS_ExitDoor_kkj_10_4) = EVT_EXIT_SINGLE_DOOR(kkj_20_ENTRY_0, "kkj_10", kkj_10_ENTRY_4,
    COLLIDER_ttw, MODEL_o9, DOOR_SWING_IN);

EvtScript N(EVS_EnterMap) = {
    Set(LVar0, kkj_20_ENTRY_0)
    Set(LVar2, MODEL_o9)
    Set(LVar3, DOOR_SWING_IN)
    ExecWait(EnterSingleDoor)
    Return
    End
};

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_PEACHS_CASTLE)
    Call(SetSpriteShading, SHADING_KKJ_20)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, FALSE, Ref(N(DefaultNPCs)))
    ExecWait(N(EVS_MakeEntities))
    Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
    BindTrigger(Ref(N(EVS_ExitDoor_kkj_10_4)), TRIGGER_WALL_PRESS_A, COLLIDER_ttw, 1, 0)
    Exec(N(EVS_EnterMap))
    Return
    End
};
