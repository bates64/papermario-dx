#include "jan_05.h"
#include "world/area/jan/jan_03.h"
#include "world/area/jan/jan_04.h"
#include "world/area/jan/jan_06.h"
#include "world/area/jan/jan_08.h"

EvtScript EVS_ExitWalk_jan_03_1 = EVT_EXIT_WALK(60, $YoshisVillage, $jan_03.Jan05);
EvtScript EVS_ExitWalk_jan_08_1 = EVT_EXIT_WALK(60, $Jan08, $jan_08.Jan05);
EvtScript EVS_ExitWalk_jan_04_0 = EVT_EXIT_WALK(60, $Jan04, $jan_04.Jan05);
EvtScript EVS_ExitWalk_jan_06_0 = EVT_EXIT_WALK(60, $Jan06, $jan_06.Jan05);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_jan_08_1, TRIGGER_FLOOR_ABOVE, COLLIDER_o227, 1, 0)
    BindTrigger(EVS_ExitWalk_jan_03_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deilise, 1, 0)
    BindTrigger(EVS_ExitWalk_jan_04_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    BindTrigger(EVS_ExitWalk_jan_06_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilin, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Call(MakeNpcs, false, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupLogs)
    Exec(EVS_SetupTrees)
    Exec(EVS_SetupBushes)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o75, SURFACE_TYPE_DOCK_WALL)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o77, SURFACE_TYPE_DOCK_WALL)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o75, COLLIDER_FLAG_DOCK_WALL)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o77, COLLIDER_FLAG_DOCK_WALL)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o1, SURFACE_TYPE_WATER)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_deiliw, SURFACE_TYPE_WATER)
    Exec(EVS_SetupTrees)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitn, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilite, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitse, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitw, COLLIDER_FLAGS_UPPER_MASK)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Exec(EVS_SetupMusic)
    Call(MakeTransformGroup, MODEL_g25)
    // water surface
    Call(SetTexPanner, MODEL_o101, TEX_PANNER_1)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_1)
        TEX_PAN_PARAMS_STEP(  -80,  140,   80, -100)
        TEX_PAN_PARAMS_FREQ(    1,    1,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Return
    End
};
