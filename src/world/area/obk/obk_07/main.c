#include "obk_07.h"

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Set(LVar2, MODEL_door_1)
    Set(LVar4, MODEL_door1b)
    Set(LVar3, DOOR_SWING_OUT)
    ExecWait(EnterSplitSingleDoor)
    Return
    End
};

EvtScript EVS_ExitDoors_obk_01_3 = EVT_EXIT_SPLIT_SINGLE_DOOR(obk_07_ENTRY_0, "obk_01", obk_01_ENTRY_3,
    COLLIDER_tt1, MODEL_door_1, MODEL_door1b, DOOR_SWING_OUT);

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_BOOS_MANSION)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, false, Ref(DefaultNPCs))
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupFireplace)
    Exec(EVS_SetupPhonograph)
    BindTrigger(Ref(EVS_ExitDoors_obk_01_3), TRIGGER_WALL_PRESS_A, COLLIDER_tt1, 1, 0)
    Exec(EVS_EnterMap)
    Exec(EVS_SetupMusic)
    Call(SetTexPanner, MODEL_ma, TEX_PANNER_2)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_2)
        TEX_PAN_PARAMS_STEP(   0,    0,  300,  100)
        TEX_PAN_PARAMS_FREQ(   0,    0,    1,    1)
        TEX_PAN_PARAMS_INIT(   0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Call(SetTexPanner, MODEL_m2, TEX_PANNER_0)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_0)
        TEX_PAN_PARAMS_STEP( 300,  100,    0,    0)
        TEX_PAN_PARAMS_FREQ(   1,    1,    0,    0)
        TEX_PAN_PARAMS_INIT(   0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Return
    End
};
