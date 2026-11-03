#include "kpa_32.h"
#include "world/area/kpa/kpa_51.h"
#include "world/area/kpa/kpa_81.h"
#include "world/area/kpa/kpa_90.h"
#include "world/area/kpa/kpa_96.h"

EvtScript EVS_ExitDoors_kpa_81_2 =
    EVT_EXIT_DOUBLE_DOOR($GuardDoor1, $kpa_81.LowerGrandHall, COLLIDER_ttw, MODEL_b4_doa, MODEL_o1256);
EvtScript EVS_ExitWalk_kpa_90_0 = EVT_EXIT_WALK(60, $EastJailStairs, $kpa_90.LowerGrandHall);
EvtScript EVS_ExitDoors_kpa_51_0 =
    EVT_EXIT_DOUBLE_DOOR($WaterPuzzleHall, $kpa_51.LowerGrandHall, COLLIDER_tte, MODEL_o1258, MODEL_o1257);
EvtScript EVS_ExitDoors_kpa_96_0 =
    EVT_EXIT_DOUBLE_DOOR($ItemShop, $kpa_96.LowerGrandHall, COLLIDER_tt4, MODEL_o1248, MODEL_o1254);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitDoors_kpa_81_2, TRIGGER_WALL_PRESS_A, COLLIDER_ttw, 1, 0)
    BindTrigger(EVS_ExitWalk_kpa_90_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deili3, 1, 0)
    BindTrigger(EVS_ExitDoors_kpa_51_0, TRIGGER_WALL_PRESS_A, COLLIDER_tte, 1, 0)
    BindTrigger(EVS_ExitDoors_kpa_96_0, TRIGGER_WALL_PRESS_A, COLLIDER_tt4, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetLoadType, LVar0)
    IfEq(LVar0, LOAD_FROM_FILE_SELECT)
        Exec(EnterSavePoint)
        Exec(EVS_BindExitTriggers)
        Return
    EndIf
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($GuardDoor1.index)
            Set(LVar0, $GuardDoor1.index)
            Set(LVar2, MODEL_o1256)
            Set(LVar3, MODEL_b4_doa)
            Exec(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq($EastJailStairs.index)
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
        CaseEq($WaterPuzzleHall.index)
            Set(LVar0, 2)
            Set(LVar2, MODEL_o1258)
            Set(LVar3, MODEL_o1257)
            Exec(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq($ItemShop.index)
            Set(LVar0, 3)
            Set(LVar2, MODEL_o1248)
            Set(LVar3, MODEL_o1254)
            Exec(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_BOWSERS_CASTLE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_EnterMap)
    Wait(1)
    Exec(EVS_SetupMusic)
    Call(SetTexPanner, MODEL_o1287, TEX_PANNER_1)
    Call(SetTexPanner, MODEL_o1289, TEX_PANNER_1)
    Call(SetTexPanner, MODEL_o1293, TEX_PANNER_1)
    Call(SetTexPanner, MODEL_o1295, TEX_PANNER_1)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_1)
        TEX_PAN_PARAMS_STEP(   20,   20,  -20,  -20)
        TEX_PAN_PARAMS_FREQ(    1,    1,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_2)
        TEX_PAN_PARAMS_STEP(   20,   20,  -20,  -20)
        TEX_PAN_PARAMS_FREQ(    1,    1,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_3)
        TEX_PAN_PARAMS_STEP(   20,   20,  -20,  -20)
        TEX_PAN_PARAMS_FREQ(    1,    1,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_4)
        TEX_PAN_PARAMS_STEP(   20,   20,  -20,  -20)
        TEX_PAN_PARAMS_FREQ(    1,    1,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Thread
        Loop(0)
            Call(ScaleModel, MODEL_o1287, 1.02, 1, 1.02)
            Call(ScaleModel, MODEL_o1289, 1.02, 1, 1.02)
            Call(ScaleModel, MODEL_o1293, 1.02, 1, 1.02)
            Call(ScaleModel, MODEL_o1295, 1.02, 1, 1.02)
            Wait(10)
            Call(ScaleModel, MODEL_o1287, 1.0, 1, 1.0)
            Call(ScaleModel, MODEL_o1289, 1.0, 1, 1.0)
            Call(ScaleModel, MODEL_o1293, 1.0, 1, 1.0)
            Call(ScaleModel, MODEL_o1295, 1.0, 1, 1.0)
            Wait(10)
            Call(ScaleModel, MODEL_o1287, 0.98, 1, 0.98)
            Call(ScaleModel, MODEL_o1289, 0.98, 1, 0.98)
            Call(ScaleModel, MODEL_o1293, 0.98, 1, 0.98)
            Call(ScaleModel, MODEL_o1295, 0.98, 1, 0.98)
            Wait(10)
        EndLoop
    EndThread
    Return
    End
};
