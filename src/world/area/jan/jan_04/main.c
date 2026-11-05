#include "jan_04.h"
#include "world/area/jan/jan_05.h"
#include "world/area/kmr/kmr_24.h"

EvtScript EVS_GotoMap_kmr_24_0 = {
    Call(FadeOutMusic, 0, 1500)
    Call(GotoMapSpecial, $kmr_24.Entry0, TRANSITION_MARIO_WHITE)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitWalk_jan_05_2 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(UseExitHeading, 60, $Jan05.index)
    Exec(ExitWalk)
    Call(GotoMap, $jan_05.Jan04)
    Wait(100)
    Return
    End
};

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_jan_05_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($Jan05.index)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitw, COLLIDER_FLAGS_UPPER_MASK)
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
        CaseRange($MtLavalava.index, $TreasureChest.index)
            Exec(EVS_Scene_TreasureChest)
        CaseEq($Epilogue.index)
            Exec(EVS_Scene_Epilogue)
        CaseEq($Entry4.index)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($Jan05.index)
            Call(MakeNpcs, false, DefaultNPCs)
        CaseEq($Epilogue.index)
            Call(MakeNpcs, false, EpilogueNPCs)
    EndSwitch
    Exec(EVS_MakeEntities)
    Exec(EVS_SetupTrees)
    Exec(EVS_SetupBushes)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o52, SURFACE_TYPE_DOCK_WALL)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o53, SURFACE_TYPE_DOCK_WALL)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o54, SURFACE_TYPE_DOCK_WALL)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o52, COLLIDER_FLAG_DOCK_WALL)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o53, COLLIDER_FLAG_DOCK_WALL)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o54, COLLIDER_FLAG_DOCK_WALL)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o1, SURFACE_TYPE_WATER)
    Call(MakeTransformGroup, MODEL_g12)
    // water surface
    Call(SetTexPanner, MODEL_o61, TEX_PANNER_1)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_1)
        TEX_PAN_PARAMS_STEP(  -80,  140,   80, -100)
        TEX_PAN_PARAMS_FREQ(    1,    1,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Call(GetDemoState, LVar0)
    IfNe(LVar0, DEMO_STATE_NONE)
        ExecWait(EVS_PlayDemoScene)
        Return
    EndIf
    Exec(EVS_EnterMap)
    Wait(1)
    Exec(EVS_SetupMusic)
    Return
    End
};
