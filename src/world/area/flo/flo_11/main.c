#include "flo_11.h"
#include "world/area/flo/flo_12.h"
#include "world/area/flo/flo_23.h"
#include "effects.h"

#include "../common/FlowerSpawnRegion.inc.c"

#include "world/common/entity/Pipe.inc.c"

EvtScript EVS_ExitWalk_flo_23_1 = EVT_EXIT_WALK(60, $Flo23, $flo_23.Flo11);
EvtScript EVS_ExitWalk_flo_12_0 = EVT_EXIT_WALK(60, $Flo12, $flo_12.Flo11);

// template for GotoMap exits used with pipes in the maze
#define EVT_GOTO_MAP(entry) \
{ \
    SetGroup(EVT_GROUP_EXIT_MAP) \
    Call(GotoMap, entry) \
    Wait(100) \
    Return \
    End \
}

// template for binding the event for the generic EVS_OnEnterPipe
#define EVT_SETUP_PIPE(entry, collider, exitScript) \
    Set(LVar0, entry) \
    Set(LVar1, collider) \
    Set(LVar2, exitScript) \
    BindTrigger(EVS_OnEnterPipe, TRIGGER_FLOOR_TOUCH, LVar1, 1, 0)

EvtScript EVS_GotoMap_flo_11_5 = EVT_GOTO_MAP($Entry5);
EvtScript EVS_GotoMap_flo_11_6 = EVT_GOTO_MAP($Entry6);
EvtScript EVS_GotoMap_flo_11_7 = EVT_GOTO_MAP($Entry7);
EvtScript EVS_GotoMap_flo_11_2 = EVT_GOTO_MAP($Entry2);
EvtScript EVS_GotoMap_flo_11_3 = EVT_GOTO_MAP($Entry3);
EvtScript EVS_GotoMap_flo_11_4 = EVT_GOTO_MAP($Entry4);

EvtScript EVS_OnEnterPipe = {
    Set(LVarA, LVar0)
    Set(LVarB, LVar1)
    Set(LVarC, LVar2)
    ExecWait(EVS_Pipe_ExitVertical)
    Return
    End
};

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_flo_12_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_flo_23_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    EVT_SETUP_PIPE($Entry2.index, COLLIDER_o91, EVS_GotoMap_flo_11_5) // link 2 <--> 5
    EVT_SETUP_PIPE($Entry3.index, COLLIDER_o92, EVS_GotoMap_flo_11_6) // link 3 <--> 6
    EVT_SETUP_PIPE($Entry4.index, COLLIDER_o93, EVS_GotoMap_flo_11_7) // link 4 <--> 7
    EVT_SETUP_PIPE($Entry5.index, COLLIDER_o94, EVS_GotoMap_flo_11_2) // link 2 <--> 5
    EVT_SETUP_PIPE($Entry6.index, COLLIDER_o95, EVS_GotoMap_flo_11_3) // link 3 <--> 6
    EVT_SETUP_PIPE($Entry7.index, COLLIDER_o96, EVS_GotoMap_flo_11_4) // link 4 <--> 7
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_FLOWER_FIELDS)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, false, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitw, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilite, COLLIDER_FLAGS_UPPER_MASK)
    Call(GetEntryID, LVar0)
    IfLe(LVar0, $Flo12.index)
        Set(LVar0, EVS_BindExitTriggers)
        Exec(EnterWalk)
        Exec(EVS_Scene_LakituAmbush)
        Wait(1)
    Else
        Set(LVarA, EVS_BindExitTriggers)
        Exec(EVS_Pipe_EnterVertical)
        Wait(1)
    EndIf
    ExecWait(EVS_SetupMusic)
    IfGe(GB_StoryProgress, STORY_CH6_DESTROYED_PUFF_PUFF_MACHINE)
        Call(SpawnSunEffect, FX_SUN_FROM_LEFT)
    EndIf
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o90, SURFACE_TYPE_HEDGES)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o104, SURFACE_TYPE_HEDGES)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o105, SURFACE_TYPE_HEDGES)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o109, SURFACE_TYPE_HEDGES)
    Return
    End
};
