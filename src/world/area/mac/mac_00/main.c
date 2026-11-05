#include "mac_00.h"
#include "world/area/kmr/kmr_10.h"
#include "world/area/kmr/kmr_20.h"
#include "world/area/mac/mac_01.h"
#include "world/area/tik/tik_19.h"

#include "world/common/entity/Pipe.inc.c"

API_CALLABLE(DummyColliderFunction) {
    Bytecode* args = script->ptrReadPos;
    f32 x, y, z;

    get_collider_center(evt_get_variable(script, *args++), &x, &y, &z);
    return ApiStatus_DONE2;
}

API_CALLABLE(DummyInitFunction) {
    return ApiStatus_DONE2;
}

EvtScript EVS_ExitWalk_kmr_10_1 = EVT_EXIT_WALK(60, $GoombaRoad, $kmr_10.ToadTown);
EvtScript EVS_ExitWalk_mac_01_0 = EVT_EXIT_WALK(60, $PlazaDistrict, $mac_01.GateDistrict);

EvtScript EVS_GotoMap_tik_19_9 = {
    Call(GotoMap, $tik_19.GateDistrict)
    Wait(100)
    Return
    End
};

EvtScript EVS_GotoMap_kmr_20_4 = {
    Call(GotoMap, $kmr_20.ToadTown)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitPipe_tik_19_9 = EVT_EXIT_PIPE_VERTICAL($PondPipe, COLLIDER_deilit, EVS_GotoMap_tik_19_9);
EvtScript EVS_ExitPipe_kmr_20_4 = EVT_EXIT_PIPE_VERTICAL($MariosHouse, COLLIDER_deilim, EVS_GotoMap_kmr_20_4);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_mac_01_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    BindTrigger(EVS_ExitPipe_kmr_20_4, TRIGGER_FLOOR_ABOVE, COLLIDER_deilim, 1, 0)
    IfGe(GB_StoryProgress, STORY_EPILOGUE)
        Return
    EndIf
    BindTrigger(EVS_ExitWalk_kmr_10_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deilinw, 1, 0)
    BindTrigger(EVS_ExitPipe_tik_19_9, TRIGGER_FLOOR_TOUCH, COLLIDER_deilit, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseOrEq($PondPipe.index)
        CaseOrEq($MariosHouse.index)
            EVT_ENTER_PIPE_VERTICAL(EVS_BindExitTriggers)
        EndCaseGroup
        CaseEq($Intro.index)
            Exec(EVS_Scene_Intro)
        CaseEq($Epilogue.index)
            ExecWait(EVS_Scene_BeginEpilogue)
            Exec(EVS_BindExitTriggers)
        CaseDefault
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
#if VERSION_PAL
    Call(GetLanguage, LVar0)
    Call(SetModelTexVariant, MODEL_mushroom_kingdom, LVar0)
#endif
    IfGe(GB_StoryProgress, STORY_CH0_KAMMY_RETURNED_TO_BOWSER)
        Set(GF_MAP_ToadTown, true)
    EndIf
    Call(SetRenderMode, MODEL_minka1_yuka, RENDER_MODE_SURFACE_XLU_ZB_ZUPD)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_dummy, COLLIDER_FLAGS_UPPER_MASK)
    Switch(GB_StoryProgress)
        CaseEq(STORY_INTRO)
            Call(MakeNpcs, false, IntroNPCs)
        CaseGe(STORY_EPILOGUE)
            Call(MakeNpcs, false, EpilogueNPCs)
        CaseDefault
            Call(MakeNpcs, false, DefaultNPCs)
    EndSwitch
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupRooms)
    Exec(EVS_SetupShop)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_water, SURFACE_TYPE_WATER)
    Exec(EVS_SetupWaterCustomGfx)
    Call(SetTexPanner, MODEL_water, TEX_PANNER_1)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_1)
        TEX_PAN_PARAMS_STEP(    0,    0,    0,  120)
        TEX_PAN_PARAMS_FREQ(    0,    1,    0,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_op_1, SURFACE_TYPE_DOCK_WALL)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_op2, SURFACE_TYPE_DOCK_WALL)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_op3, SURFACE_TYPE_DOCK_WALL)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_op_1, COLLIDER_FLAG_DOCK_WALL)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_op2, COLLIDER_FLAG_DOCK_WALL)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_op3, COLLIDER_FLAG_DOCK_WALL)
    Call(DummyColliderFunction, COLLIDER_op_1)
    Call(DummyColliderFunction, COLLIDER_op2)
    Call(DummyColliderFunction, COLLIDER_op3)
    Call(GetDemoState, LVar0)
    IfNe(LVar0, DEMO_STATE_NONE)
        EVT_ENTER_PIPE_VERTICAL(EVS_BindExitTriggers)
        ExecWait(EVS_SetupDemo)
        Return
    EndIf
    Exec(EVS_SetupMusic)
    IfEq(GB_StoryProgress, STORY_CH0_KAMMY_RETURNED_TO_BOWSER)
        Set(GB_StoryProgress, STORY_CH0_ARRIVED_AT_TOAD_TOWN)
        Exec(EVS_Scene_ToadTownGreeting)
    EndIf
    Exec(EVS_EnterMap)
    Wait(1)
    Call(DummyInitFunction)
    Return
    End
};
