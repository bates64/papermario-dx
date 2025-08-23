#include "obk_03.h"

EvtScript N(EVS_ExitDoor_obk_02_1) = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Set(LVar0, obk_03_ENTRY_0)
    Set(LVar1, COLLIDER_tt2)
    Set(LVar2, MODEL_door_2_1)
    Set(LVar4, MODEL_door_2_2)
    Set(LVar3, DOOR_SWING_IN)
    Exec(ExitSplitSingleDoor)
    Wait(17)
    Call(GotoMap, Ref("obk_02"), obk_02_ENTRY_1)
    Wait(100)
    Return
    End
};

EvtScript N(EVS_ExitDoor_obk_04_0) = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Set(LVar0, obk_03_ENTRY_1)
    Set(LVar1, COLLIDER_tt1)
    Set(LVar2, MODEL_door_1)
    Set(LVar4, MODEL_o494)
    Set(LVar3, DOOR_SWING_OUT)
    Exec(ExitSplitSingleDoor)
    Wait(17)
    Call(GotoMap, Ref("obk_04"), obk_04_ENTRY_0)
    Wait(100)
    Return
    End
};

EvtScript N(EVS_EnterMap) = {
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

EvtScript N(EVS_SetupTexPan) = {
    // spooky fog
    Call(SetTexPanner, MODEL_m2, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_m4, TEX_PANNER_0)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_0)
        TEX_PAN_PARAMS_STEP(  300,  100,    0,    0)
        TEX_PAN_PARAMS_FREQ(    1,    1,    0,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    Return
    End
};

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_BOOS_MANSION)
    Call(SetSpriteShading, SHADING_NONE)
    SetUP_CAMERA_NO_LEAD()
    Call(MakeNpcs, false, Ref(N(DefaultNPCs)))
    ExecWait(N(EVS_MakeEntities))
    Exec(N(EVS_SetupStairs))
    Exec(N(EVS_SetupRockingChair))
    ExecWait(N(EVS_SetupShop))
    Exec(N(EVS_SetupTexPan))
    Exec(N(EVS_SetupMusic))
    BindTrigger(Ref(N(EVS_ExitDoor_obk_04_0)), TRIGGER_WALL_PRESS_A, COLLIDER_tt1, 1, 0)
    BindTrigger(Ref(N(EVS_ExitDoor_obk_02_1)), TRIGGER_WALL_PRESS_A, COLLIDER_tt2, 1, 0)
    Exec(N(EVS_EnterMap))
    Return
    End
};
