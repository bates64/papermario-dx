#include "jan_06.h"
#include "world/area/jan/jan_05.h"
#include "world/area/jan/jan_07.h"
#include "world/area/jan/jan_09.h"
#include "world/area/jan/jan_12.h"

EvtScript EVS_ExitWalk_jan_05_3 = EVT_EXIT_WALK(60, $Jan05, $jan_05.Jan06);
EvtScript EVS_ExitWalk_jan_07_0 = EVT_EXIT_WALK(60, $Jan07, $jan_07.Jan06);
EvtScript EVS_ExitWalk_jan_12_0 = EVT_EXIT_WALK(60, $Jan12, $jan_12.Jan06);
EvtScript EVS_ExitWalk_jan_09_1 = EVT_EXIT_WALK(60, $Jan09, $jan_09.Jan06);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_jan_05_3, TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
    BindTrigger(EVS_ExitWalk_jan_07_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    BindTrigger(EVS_ExitWalk_jan_12_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilin, 1, 0)
    BindTrigger(EVS_ExitWalk_jan_09_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    Return
    End
};

EvtScript EVS_InitRavenStatueObjects = {
    IfLt(GB_StoryProgress, STORY_CH5_MOVED_RAVEN_STATUE)
        Call(TranslateModel, MODEL_o55, 0, 0, 0)
        Call(TranslateModel, MODEL_o56, 0, 0, 0)
        Call(TranslateModel, MODEL_o57, 0, 0, 0)
        Call(TranslateModel, MODEL_o58, 0, 0, 0)
        Call(TranslateModel, MODEL_o146, 0, 0, 0)
        Call(TranslateModel, MODEL_o147, 0, 0, 0)
        Call(TranslateModel, MODEL_o148, 0, 0, 0)
        Call(TranslateModel, MODEL_o151, 0, 0, 0)
        Call(TranslateModel, MODEL_o162, 0, 0, 0)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o180, COLLIDER_FLAGS_UPPER_MASK)
    Else
        Call(TranslateModel, MODEL_o55, -100, 0, 0)
        Call(TranslateModel, MODEL_o56, -100, 0, 0)
        Call(TranslateModel, MODEL_o57, -100, 0, 0)
        Call(TranslateModel, MODEL_o58, -100, 0, 0)
        Call(TranslateModel, MODEL_o146, -100, 0, 0)
        Call(TranslateModel, MODEL_o147, -100, 0, 0)
        Call(TranslateModel, MODEL_o148, -100, 0, 0)
        Call(TranslateModel, MODEL_o151, -100, 0, 0)
        Call(TranslateModel, MODEL_o162, -100, 0, 0)
        Call(RotateModel, MODEL_o55, 0, 0, 1, 0)
        Call(RotateModel, MODEL_o56, 0, 0, 1, 0)
        Call(RotateModel, MODEL_o57, 0, 0, 1, 0)
        Call(RotateModel, MODEL_o146, 0, 0, 1, 0)
        Call(RotateModel, MODEL_o147, 0, 0, 1, 0)
        Call(RotateModel, MODEL_o148, 0, 0, 1, 0)
        Call(RotateModel, MODEL_o151, 0, 0, 1, 0)
        Call(RotateModel, MODEL_o162, 0, 0, 1, 0)
        Call(MakeMarkerEntity, $Item_JadeRaven_1)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o166, COLLIDER_FLAGS_UPPER_MASK)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o247, COLLIDER_FLAGS_UPPER_MASK)
    EndIf
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_JADE_JUNGLE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(SetZoneEnabled, ZONE_o59, false)
    Exec(EVS_InitRavenStatueObjects)
    Call(MakeNpcs, false, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o69, SURFACE_TYPE_DOCK_WALL)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o71, SURFACE_TYPE_DOCK_WALL)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o74, SURFACE_TYPE_DOCK_WALL)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o69, COLLIDER_FLAG_DOCK_WALL)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o71, COLLIDER_FLAG_DOCK_WALL)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o74, COLLIDER_FLAG_DOCK_WALL)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o1, SURFACE_TYPE_WATER)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o257, SURFACE_TYPE_WATER)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o258, SURFACE_TYPE_WATER)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o259, SURFACE_TYPE_WATER)
    Exec(EVS_SetupStatue)
    Exec(EVS_SetupTrees)
    Exec(EVS_SetupBushes)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilits, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitn, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitw, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilite, COLLIDER_FLAGS_UPPER_MASK)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Exec(EVS_SetupLogs)
    Call(SetMusic, 0, SONG_JADE_JUNGLE, 0, VOL_LEVEL_FULL)
    Call(ClearAmbientSounds, 250)
    Call(MakeTransformGroup, MODEL_g14)
    // water surface
    Call(SetTexPanner, MODEL_o61, TEX_PANNER_1)
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
