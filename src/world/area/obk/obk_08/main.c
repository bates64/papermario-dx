#include "obk_08.h"

#include "world/common/atomic/TexturePan.inc.c"

EvtScript N(EVS_EnterMap) = {
    Call(GetEntryID, LVar0)
    Set(LVar2, MODEL_door1)
    Set(LVar4, MODEL_door1b)
    Set(LVar3, DOOR_SWING_OUT)
    ExecWait(EnterSplitSingleDoor)
    Return
    End
};

EvtScript N(EVS_ExitMap_obk_01_4) = EVT_EXIT_SPLIT_SINGLE_DOOR(obk_08_ENTRY_0, "obk_01", obk_01_ENTRY_4,
    COLLIDER_tt1, MODEL_door1, MODEL_door1b, DOOR_SWING_OUT);

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_BOOS_MANSION)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, false, Ref(N(DefaultNPCs)))
    ExecWait(N(EVS_MakeEntities))
    Set(AF_OBK08_KeepAwayStarted, false)
    Exec(N(EVS_SetupCabinets))
    Exec(N(EVS_ManageWindows))
    BindTrigger(Ref(N(EVS_ExitMap_obk_01_4)), TRIGGER_WALL_PRESS_A, COLLIDER_tt1, 1, 0)
    Exec(N(EVS_EnterMap))
    Exec(N(EVS_SetupMusic))
    Call(SetTexPanner, MODEL_moku1, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_moku2, TEX_PANNER_0)
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
