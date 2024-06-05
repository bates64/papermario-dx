#include "flo_11.h"
#include "effects.h"

#include "../common/FlowerSpawnRegion.inc.c"

#include "world/common/entity/Pipe.inc.c"

API_CALLABLE(N(SpawnSunEffect)) {
    fx_sun(FX_SUN_FROM_LEFT, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    return ApiStatus_DONE2;
}

EvtScript N(EVS_ExitWalk_flo_23_1) = EVT_EXIT_WALK(60, flo_11_ENTRY_0, "flo_23", flo_23_ENTRY_1);
EvtScript N(EVS_ExitWalk_flo_12_0) = EVT_EXIT_WALK(60, flo_11_ENTRY_1, "flo_12", flo_12_ENTRY_0);

// template for GotoMap exits used with pipes in the maze
#define EVT_GOTO_MAP(mapName, entry) \
{ \
    SetGroup(EVT_GROUP_1B) \
    Call(GotoMap, Ref(mapName), entry) \
    Wait(100) \
    Return \
    End \
}

// template for binding the event for the generic EVS_OnEnterPipe
#define EVT_SETUP_PIPE(entry, collider, exitScript) \
    Set(LVar0, entry) \
    Set(LVar1, collider) \
    Set(LVar2, Ref(exitScript)) \
    BindTrigger(Ref(N(EVS_OnEnterPipe)), TRIGGER_FLOOR_TOUCH, LVar1, 1, 0)

EvtScript N(EVS_GotoMap_flo_11_5) = EVT_GOTO_MAP("flo_11", flo_11_ENTRY_5);
EvtScript N(EVS_GotoMap_flo_11_6) = EVT_GOTO_MAP("flo_11", flo_11_ENTRY_6);
EvtScript N(EVS_GotoMap_flo_11_7) = EVT_GOTO_MAP("flo_11", flo_11_ENTRY_7);
EvtScript N(EVS_GotoMap_flo_11_2) = EVT_GOTO_MAP("flo_11", flo_11_ENTRY_2);
EvtScript N(EVS_GotoMap_flo_11_3) = EVT_GOTO_MAP("flo_11", flo_11_ENTRY_3);
EvtScript N(EVS_GotoMap_flo_11_4) = EVT_GOTO_MAP("flo_11", flo_11_ENTRY_4);

EvtScript N(EVS_OnEnterPipe) = {
    Set(LVarA, LVar0)
    Set(LVarB, LVar1)
    Set(LVarC, LVar2)
    ExecWait(N(EVS_Pipe_ExitVertical))
    Return
    End
};

EvtScript N(EVS_BindExitTriggers) = {
    BindTrigger(Ref(N(EVS_ExitWalk_flo_12_0)), TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(Ref(N(EVS_ExitWalk_flo_23_1)), TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    EVT_SETUP_PIPE(flo_11_ENTRY_2, COLLIDER_o91, N(EVS_GotoMap_flo_11_5)) // link 2 <--> 5
    EVT_SETUP_PIPE(flo_11_ENTRY_3, COLLIDER_o92, N(EVS_GotoMap_flo_11_6)) // link 3 <--> 6
    EVT_SETUP_PIPE(flo_11_ENTRY_4, COLLIDER_o93, N(EVS_GotoMap_flo_11_7)) // link 4 <--> 7
    EVT_SETUP_PIPE(flo_11_ENTRY_5, COLLIDER_o94, N(EVS_GotoMap_flo_11_2)) // link 2 <--> 5
    EVT_SETUP_PIPE(flo_11_ENTRY_6, COLLIDER_o95, N(EVS_GotoMap_flo_11_3)) // link 3 <--> 6
    EVT_SETUP_PIPE(flo_11_ENTRY_7, COLLIDER_o96, N(EVS_GotoMap_flo_11_4)) // link 4 <--> 7
    Return
    End
};

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_FLOWER_FIELDS)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, FALSE, Ref(N(DefaultNPCs)))
    ExecWait(N(EVS_MakeEntities))
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitw, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilite, COLLIDER_FLAGS_UPPER_MASK)
    Call(GetEntryID, LVar0)
    IfLe(LVar0, flo_11_ENTRY_1)
        Set(LVar0, Ref(N(EVS_BindExitTriggers)))
        Exec(EnterWalk)
        Exec(N(EVS_Scene_LakituAmbush))
        Wait(1)
    Else
        Set(LVarA, Ref(N(EVS_BindExitTriggers)))
        Exec(N(EVS_Pipe_EnterVertical))
        Wait(1)
    EndIf
    ExecWait(N(EVS_SetupMusic))
    IfGe(GB_StoryProgress, STORY_CH6_DESTROYED_PUFF_PUFF_MACHINE)
        Call(N(SpawnSunEffect))
    EndIf
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o90, SURFACE_TYPE_HEDGES)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o104, SURFACE_TYPE_HEDGES)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o105, SURFACE_TYPE_HEDGES)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o109, SURFACE_TYPE_HEDGES)
    Return
    End
};
