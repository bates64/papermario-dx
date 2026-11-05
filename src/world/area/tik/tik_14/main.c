#include "tik_14.h"
#include "world/area/tik/tik_15.h"
#include "world/area/tik/tik_21.h"

#include "world/common/entity/Pipe.inc.c"

EvtScript EVS_ExitWalk_tik_15_0 = EVT_EXIT_WALK(60, $RipCheatosHome, $tik_15.RipCheatoAntechamber);

EvtScript EVS_GotoMap_tik_21_2 = {
    Call(GotoMap, $tik_21.RipCheatoAntechamber)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitPipe_tik_21_2 = EVT_EXIT_PIPE_HORIZONTAL($HiddenBlocksRoom, COLLIDER_o47, EVS_GotoMap_tik_21_2);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitPipe_tik_21_2, TRIGGER_WALL_PUSH, COLLIDER_o47, 1, 0)
    BindTrigger(EVS_ExitWalk_tik_15_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_CLEAR_BITS, COLLIDER_o47, COLLIDER_FLAGS_UPPER_MASK)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($HiddenBlocksRoom.index)
            EVT_ENTER_PIPE_HORIZONTAL(COLLIDER_o47, EVS_BindExitTriggers)
        CaseEq($RipCheatosHome.index)
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Exec(EVS_SetupMusic)
    Exec(EVS_SetupDrips)
    ExecWait(EVS_MakeEntities)
    Call(SetTexPanner, MODEL_mizu, TEX_PANNER_2)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_2)
        TEX_PAN_PARAMS_STEP(    0, -200, -100, -500)
        TEX_PAN_PARAMS_FREQ(    1,    1,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o47, COLLIDER_FLAGS_UPPER_MASK)
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
