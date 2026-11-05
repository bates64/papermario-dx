#include "jan_13.h"
#include "world/area/jan/jan_12.h"
#include "world/area/jan/jan_14.h"

EvtScript EVS_ExitWalk_jan_14_0 = EVT_EXIT_WALK(60, $Jan14, $jan_14.Jan13);
EvtScript EVS_ExitWalk_jan_12_1 = EVT_EXIT_WALK(60, $Jan12, $jan_12.Jan13);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_jan_12_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
    BindTrigger(EVS_ExitWalk_jan_14_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilin, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Exec(EVS_MakeEntities)
    Exec(EVS_SetupPuzzle)
    Exec(EVS_SetupTrees)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilits, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitn, COLLIDER_FLAGS_UPPER_MASK)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Call(SetMusic, 0, SONG_DEEP_JUNGLE, 0, VOL_LEVEL_FULL)
    Call(PlayAmbientSounds, AMBIENT_JUNGLE)
    Return
    End
};
