#include "nok_15.h"
#include "world/area/nok/nok_14.h"
#include "world/area/trd/trd_00.h"
#include "effects.h"

#include "world/common/entity/Pipe.inc.c"

EvtScript EVS_ExitWalk_nok_14_1 = EVT_EXIT_WALK(60, $Nok14, $nok_14.Nok15);
EvtScript EVS_ExitWalk_trd_00_0 = EVT_EXIT_WALK(60, $KoopaBrosFortress, $trd_00.PleasantPath);
EvtScript EVS_ExitWalk_trd_00_4 = EVT_EXIT_WALK(60, $KoopaBrosFortressUpper, $trd_00.PleasantPathUpper);

BombTrigger BombPos_Wall = {
    .pos = $BombPos_Wall.pos,
    .diameter = 2.0f * $BombPos_Wall.radius,
};

EvtScript EVS_BlastWall = {
    PlayEffect(EFFECT_BOMBETTE_BREAKING, 0, $BombetteBreakingPos_1.pos.x, $BombetteBreakingPos_1.pos.y, $BombetteBreakingPos_1.pos.z, 10, 30)
    Set(GF_NOK15_BombedWall, true)
    Call(EnableModel, MODEL_bomb_ato, true)
    Call(EnableModel, MODEL_bomb_1, false)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_tt1, COLLIDER_FLAGS_UPPER_MASK)
    Unbind
    Return
    End
};

EvtScript EVS_SetupTexPan = {
    // flowers
    Call(SetTexPanner, MODEL_suimen1, TEX_PANNER_1)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_1)
        TEX_PAN_PARAMS_STEP( -100,    0,  600,    0)
        TEX_PAN_PARAMS_FREQ(    1,    0,    1,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    // water
    Call(SetTexPanner, MODEL_kabemizu1, TEX_PANNER_2)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_2)
        TEX_PAN_PARAMS_STEP( -100,    0,  400,    0)
        TEX_PAN_PARAMS_FREQ(    1,    0,    1,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Return
    End
};

EvtScript EVS_GotoMap_nok_15_4 = {
    Call(GotoMap, $UpperPipe)
    Wait(100)
    Return
    End
};

EvtScript EVS_GotoMap_nok_15_3 = {
    Call(GotoMap, $LowerPipe)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitPipe = {
    Set(LVarA, LVar0)
    Set(LVarB, LVar1)
    Set(LVarC, LVar2)
    ExecWait(EVS_Pipe_ExitVertical)
    Return
    End
};

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_nok_14_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    BindTrigger(EVS_ExitWalk_trd_00_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deili2, 1, 0)
    BindTrigger(EVS_ExitWalk_trd_00_4, TRIGGER_FLOOR_ABOVE, COLLIDER_deili3, 1, 0)
    Set(LVar0, $LowerPipe.index)
    Set(LVar1, COLLIDER_o680)
    Set(LVar2, EVS_GotoMap_nok_15_4)
    BindTrigger(EVS_ExitPipe, TRIGGER_FLOOR_TOUCH, LVar1, 1, 0)
    Set(LVar0, $UpperPipe.index)
    Set(LVar1, COLLIDER_o679)
    Set(LVar2, EVS_GotoMap_nok_15_3)
    BindTrigger(EVS_ExitPipe, TRIGGER_FLOOR_TOUCH, LVar1, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Call(MakeNpcs, false, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupFoliage)
    Exec(EVS_SetupTexPan)
    IfEq(GF_NOK15_BombedWall, false)
        Call(EnableModel, MODEL_bomb_ato, false)
        BindTrigger(EVS_BlastWall, TRIGGER_POINT_BOMB, BombPos_Wall, 1, 0)
    Else
        Call(EnableModel, MODEL_bomb_1, false)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_tt1, COLLIDER_FLAGS_UPPER_MASK)
    EndIf
    Exec(EVS_SetupMusic)
    Call(GetEntryID, LVar0)
    IfLe(LVar0, $KoopaBrosFortressUpper.index)
        Set(LVar0, EVS_BindExitTriggers)
        Exec(EnterWalk)
    Else
        Set(LVarA, EVS_BindExitTriggers)
        Exec(EVS_Pipe_EnterVertical)
    EndIf
    Wait(1)
    Return
    End
};
