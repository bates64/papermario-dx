#include "obk_03.h"

EvtScript EVS_ExitDoor_obk_02_1 = EVT_EXIT_SPLIT_SINGLE_DOOR(obk_03_ENTRY_0, "obk_02", obk_02_ENTRY_1,
    COLLIDER_tt2, MODEL_door_2_1, MODEL_door_2_2, DOOR_SWING_IN);

EvtScript EVS_ExitDoor_obk_04_0 = EVT_EXIT_SPLIT_SINGLE_DOOR(obk_03_ENTRY_1, "obk_04", obk_04_ENTRY_0,
    COLLIDER_tt1, MODEL_door_1, MODEL_o494, DOOR_SWING_OUT);

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(obk_03_ENTRY_0)
            Set(LVar2, MODEL_door_2_1)
            Set(LVar4, MODEL_door_2_2)
            Set(LVar3, DOOR_SWING_IN)
            ExecWait(EnterSplitSingleDoor)
        CaseEq(obk_03_ENTRY_1)
            Set(LVar2, MODEL_door_1)
            Set(LVar4, MODEL_o494)
            Set(LVar3, DOOR_SWING_OUT)
            ExecWait(EnterSplitSingleDoor)
    EndSwitch
    Return
    End
};

EvtScript EVS_SetupTexPan = {
    // spooky fog
    Call(SetTexPanner, MODEL_m2, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_m4, TEX_PANNER_0)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_0)
        TEX_PAN_PARAMS_STEP(  300,  100,    0,    0)
        TEX_PAN_PARAMS_FREQ(    1,    1,    0,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_BOOS_MANSION)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, false, Ref(DefaultNPCs))
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupStairs)
    Exec(EVS_SetupRockingChair)
    ExecWait(EVS_SetupShop)
    Exec(EVS_SetupTexPan)
    Exec(EVS_SetupMusic)
    BindTrigger(Ref(EVS_ExitDoor_obk_04_0), TRIGGER_WALL_PRESS_A, COLLIDER_tt1, 1, 0)
    BindTrigger(Ref(EVS_ExitDoor_obk_02_1), TRIGGER_WALL_PRESS_A, COLLIDER_tt2, 1, 0)
    Exec(EVS_EnterMap)
    Return
    End
};
