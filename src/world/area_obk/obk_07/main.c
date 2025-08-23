#include "obk_07.h"

#include "world/common/atomic/TexturePan.inc.c"

EvtScript N(EVS_EnterMap) = {
    Call(GetEntryID, LVar0)
    Set(LVar2, MODEL_door_1)
    Set(LVar4, MODEL_door1b)
    Set(LVar3, DOOR_SWING_OUT)
    ExecWait(EnterSplitSingleDoor)
    Return
    End
};

EvtScript N(EVS_ExitDoors_obk_01_3) = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Set(LVar0, obk_07_ENTRY_0)
    Set(LVar1, COLLIDER_tt1)
    Set(LVar2, MODEL_door_1)
    Set(LVar4, MODEL_door1b)
    Set(LVar3, DOOR_SWING_OUT)
    Exec(ExitSplitSingleDoor)
    Wait(17)
    Call(GotoMap, Ref("obk_01"), obk_01_ENTRY_3)
    Wait(100)
    Return
    End
};

EvtScript N(EVS_TexPan_Fog) = {
    Thread
        Call(EnableTexPanning, MODEL_ma, true)
        Set(LVar0, 0)
        Set(LVar1, 0)
        Loop(0)
            Call(SetTexPanOffset, 2, 1, LVar0, LVar1)
            Add(LVar0, 300)
            Add(LVar1, 100)
            Wait(1)
        EndLoop
    EndThread
    Call(SetTexPanner, MODEL_m2, 0)
    Set(LVar0, 0)
    Set(LVar1, 0)
    Loop(0)
        Add(LVar0, 300)
        Add(LVar1, 100)
        Call(SetTexPanOffset, 0, 0, LVar0, LVar1)
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_BOOS_MANSION)
    Call(SetSpriteShading, SHADING_NONE)
    SetUP_CAMERA_NO_LEAD()
    Call(MakeNpcs, false, Ref(N(DefaultNPCs)))
    ExecWait(N(EVS_MakeEntities))
    Exec(N(EVS_SetupFireplace))
    Exec(N(EVS_SetupPhonograph))
    BindTrigger(Ref(N(EVS_ExitDoors_obk_01_3)), TRIGGER_WALL_PRESS_A, COLLIDER_tt1, 1, 0)
    Exec(N(EVS_EnterMap))
    Exec(N(EVS_SetupMusic))
    Call(SetTexPanner, MODEL_ma, TEX_PANNER_2)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_2)
        TEX_PAN_PARAMS_STEP(   0,    0,  300,  100)
        TEX_PAN_PARAMS_FREQ(   0,    0,    1,    1)
        TEX_PAN_PARAMS_INIT(   0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    Call(SetTexPanner, MODEL_m2, TEX_PANNER_0)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_0)
        TEX_PAN_PARAMS_STEP( 300,  100,    0,    0)
        TEX_PAN_PARAMS_FREQ(   1,    1,    0,    0)
        TEX_PAN_PARAMS_INIT(   0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    Return
    End
};
