#include "jan_15.h"
#include "world/area/jan/jan_14.h"
#include "world/area/jan/jan_16.h"

EvtScript EVS_ExitWalk_jan_16 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(UseExitHeading, 60, $Jan16.index)
    Exec(ExitWalk)
    IfLt(GB_StoryProgress, STORY_CH5_REACHED_RAPHAELS_TREE)
        Call(GotoMap, $jan_16.Jan15FirstVisit)
    Else
        Call(GotoMap, $jan_16.Jan15)
    EndIf
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitWalk_jan_14_1 = EVT_EXIT_WALK(60, $Jan14, $jan_14.Jan15);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_jan_14_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
    BindTrigger(EVS_ExitWalk_jan_16, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_JADE_JUNGLE)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(MakeNpcs, false, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupTrees)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilits, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilite, COLLIDER_FLAGS_UPPER_MASK)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Call(SetMusic, 0, SONG_DEEP_JUNGLE, 0, VOL_LEVEL_FULL)
    Call(PlayAmbientSounds, AMBIENT_JUNGLE)
    Return
    End
};
