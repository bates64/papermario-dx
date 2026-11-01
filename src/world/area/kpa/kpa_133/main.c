#include "kpa_133.h"
#include "world/area/kpa/kpa_134.h"
#include "world/area/kpa/kpa_51.h"
#include "effects.h"

EvtScript EVS_ExitDoors_kpa_51_1 =
    EVT_EXIT_DOUBLE_DOOR($WaterPuzzleHall, $kpa_51.LeftWaterPuzzle, COLLIDER_ttw, MODEL_o486, MODEL_o485);
EvtScript EVS_ExitWalk_kpa_134_0 = EVT_EXIT_WALK(40, $RightPuzzleLow, $kpa_134.LeftPuzzleLow);
EvtScript EVS_ExitWalk_kpa_134_2 = EVT_EXIT_WALK(40, $RightPuzzleMid, $kpa_134.LeftPuzzleMid);
EvtScript EVS_ExitWalk_kpa_134_3 = EVT_EXIT_WALK(40, $RightPuzzleHigh, $kpa_134.LeftPuzzleHigh);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitDoors_kpa_51_1, TRIGGER_WALL_PRESS_A, COLLIDER_ttw, 1, 0)
    BindTrigger(EVS_ExitWalk_kpa_134_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    BindTrigger(EVS_ExitWalk_kpa_134_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie2, 1, 0)
    BindTrigger(EVS_ExitWalk_kpa_134_3, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliae, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($WaterPuzzleHall.index)
            Set(LVar0, $WaterPuzzleHall.index)
            Set(LVar2, MODEL_o486)
            Set(LVar3, MODEL_o485)
            Exec(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq($RightPuzzleLow.index)
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
        CaseEq($RightPuzzleMid.index)
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
        CaseEq($RightPuzzleHigh.index)
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
    EndSwitch
    Return
    End
};

BombTrigger BombPos_Wall = {
    .pos = $BombPos_Wall.pos,
    .diameter = 2.0f * $BombPos_Wall.radius,
};

EvtScript EVS_BlastWall = {
    PlayEffect(EFFECT_BOMBETTE_BREAKING, 0, $BombetteBreakingPos_1.pos.x, $BombetteBreakingPos_1.pos.y, $BombetteBreakingPos_1.pos.z, 10, 30)
    SetGroup(EVT_GROUP_NEVER_PAUSE)
    SuspendGroup(EVT_GROUP_FLAG_INTERACT)
    Call(EnableModel, MODEL_o235, true)
    Loop(10)
        Call(EnableModel, MODEL_o477, true)
        Call(EnableModel, MODEL_o476, true)
        Wait(1)
        Call(EnableModel, MODEL_o477, false)
        Call(EnableModel, MODEL_o476, false)
        Wait(1)
    EndLoop
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_ttae, COLLIDER_FLAGS_UPPER_MASK)
    Set(GF_KPA133_Item_BombedWall, true)
    ResumeGroup(EVT_GROUP_FLAG_INTERACT)
    Unbind
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_BOWSERS_CASTLE)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(MakeNpcs, true, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    IfEq(GF_KPA133_Item_BombedWall, false)
        Call(EnableModel, MODEL_o235, false)
        BindTrigger(EVS_BlastWall, TRIGGER_POINT_BOMB, BombPos_Wall, 1, 0)
    Else
        Call(EnableModel, MODEL_o477, false)
        Call(EnableModel, MODEL_o476, false)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_ttae, COLLIDER_FLAGS_UPPER_MASK)
    EndIf
    Exec(EVS_SetWaterLevel)
    BindTrigger(EVS_OnHitSwitch, TRIGGER_AREA_FLAG_SET, AF_KPA133_HitWaterSwitch, 1, 0)
    // water edge
    Call(SetTexPanner, MODEL_s_sui, TEX_PANNER_1)
    Call(SetTexPanner, MODEL_sui, TEX_PANNER_1)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_1)
        TEX_PAN_PARAMS_STEP( -100,  100,   70,  -70)
        TEX_PAN_PARAMS_FREQ(    1,    1,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
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
