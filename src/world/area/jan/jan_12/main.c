#include "jan_12.h"

EvtScript EVS_ExitWalk_jan_13_0 = EVT_EXIT_WALK(60, jan_12_ENTRY_1, "jan_13", jan_13_ENTRY_0);
EvtScript EVS_ExitWalk_jan_06_2 = EVT_EXIT_WALK(60, jan_12_ENTRY_0, "jan_06", jan_06_ENTRY_2);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitWalk_jan_06_2), TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
    BindTrigger(Ref(EVS_ExitWalk_jan_13_0), TRIGGER_FLOOR_ABOVE, COLLIDER_deilin, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_JADE_JUNGLE)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(MakeNpcs, false, Ref(DefaultNPCs))
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupVines)
    Exec(EVS_SetupTrees)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilits, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitn, COLLIDER_FLAGS_UPPER_MASK)
    Set(LVar0, Ref(EVS_BindExitTriggers))
    Exec(EnterWalk)
    Call(SetMusic, 0, SONG_DEEP_JUNGLE, 0, VOL_LEVEL_FULL)
    Call(PlayAmbientSounds, AMBIENT_JUNGLE)
    Return
    End
};
