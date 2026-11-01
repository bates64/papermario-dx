#include "kpa_134.h"
#include "world/area/kpa/kpa_130.h"
#include "world/area/kpa/kpa_133.h"
#include "effects.h"

EvtScript EVS_ExitWalk_kpa_133_1 = EVT_EXIT_WALK(40, $LeftPuzzleLow, $kpa_133.RightPuzzleLow);
EvtScript EVS_ExitDoors_kpa_130_0 =
    EVT_EXIT_DOUBLE_DOOR($BillBlasterHall, $kpa_130.RightWaterPuzzle, COLLIDER_nno, MODEL_o408, MODEL_o409);
EvtScript EVS_ExitWalk_kpa_133_2 = EVT_EXIT_WALK(40, $LeftPuzzleMid, $kpa_133.RightPuzzleMid);
EvtScript EVS_ExitWalk_kpa_133_3 = EVT_EXIT_WALK(40, $LeftPuzzleHigh, $kpa_133.RightPuzzleHigh);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_kpa_133_1, TRIGGER_FLOOR_ABOVE, COLLIDER_exitw, 1, 0)
    BindTrigger(EVS_ExitWalk_kpa_133_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deilite, 1, 0)
    BindTrigger(EVS_ExitWalk_kpa_133_3, TRIGGER_FLOOR_ABOVE, COLLIDER_g98, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($LeftPuzzleLow.index)
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
        CaseEq($BillBlasterHall.index)
            Set(LVar0, 1)
            Set(LVar2, MODEL_o408)
            Set(LVar3, MODEL_o409)
            Exec(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq($LeftPuzzleMid.index)
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
        CaseEq($LeftPuzzleHigh.index)
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_BOWSERS_CASTLE)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(MakeNpcs, true, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupChains)
    IfEq(GF_KPA134_BlueSwitch, false)
        BindTrigger(EVS_FlipWallPanels, TRIGGER_AREA_FLAG_SET, AF_KPA134_HitWaterSwitch, 1, 0)
    Else
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o383, COLLIDER_FLAGS_UPPER_MASK)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o384, COLLIDER_FLAGS_UPPER_MASK)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_sikake, COLLIDER_FLAGS_UPPER_MASK)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitw, COLLIDER_FLAGS_UPPER_MASK)
        Call(EnableModel, MODEL_o384, false)
        Call(EnableModel, MODEL_o383, false)
        Call(EnableModel, MODEL_o378, false)
        Call(EnableModel, MODEL_o379, false)
        Call(EnableModel, MODEL_o380, false)
        Call(EnableModel, MODEL_o381, false)
        Call(EnableModel, MODEL_o382, false)
        Call(EnableModel, MODEL_o377, false)
        Call(EnableModel, MODEL_o376, false)
        Call(EnableModel, MODEL_o375, false)
        Call(EnableModel, MODEL_o374, false)
        Call(EnableModel, MODEL_o373, false)
        Call(EnableModel, MODEL_o372, false)
        Call(EnableModel, MODEL_o371, false)
    EndIf
    IfEq(GF_KPA133_Item_BombedWall, true)
        Call(EnableModel, MODEL_o503, false)
        Call(EnableModel, MODEL_o502, false)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o358, COLLIDER_FLAGS_UPPER_MASK)
    Else
        Call(EnableModel, MODEL_o400, false)
    EndIf
    // water edge
    Call(SetTexPanner, MODEL_s_sui, TEX_PANNER_1)
    Call(SetTexPanner, MODEL_o385, TEX_PANNER_1)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_1)
        TEX_PAN_PARAMS_STEP( -100,  100,   70,  -70)
        TEX_PAN_PARAMS_FREQ(    1,    1,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    // water falling
    Call(SetTexPanner, MODEL_o388, TEX_PANNER_2)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_2)
        TEX_PAN_PARAMS_STEP( 1000, 4000,    0,    0)
        TEX_PAN_PARAMS_FREQ(    1,    1,    0,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    // water spreading
    Call(SetTexPanner, MODEL_o389, TEX_PANNER_3)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_3)
        TEX_PAN_PARAMS_STEP(    0, -1500,    0,    0)
        TEX_PAN_PARAMS_FREQ(    0,     1,    0,    0)
        TEX_PAN_PARAMS_INIT(    0,     0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    // water surface
    Call(SetTexPanner, MODEL_move, TEX_PANNER_4)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_4)
        TEX_PAN_PARAMS_STEP(  200, -100,   20,  -20)
        TEX_PAN_PARAMS_FREQ(    1,    1,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Exec(EVS_SetupMusic)
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
