#include "jan_00.h"
#include "npc.h"
#include "effects.h"
#include "entity.h"

extern EvtScript EVS_80241C10;
extern NpcGroupList DefaultNPCs;
extern EvtScript EVS_MakeEntities;

extern EvtScript EVS_SetupWhale;
extern EvtScript EVS_SetupFoliage;

EvtScript EVS_ExitWalk_jan_01_0 = EVT_EXIT_WALK(60, jan_00_ENTRY_1, "jan_01", jan_01_ENTRY_0);
EvtScript EVS_ExitWalk_jan_08_0 = EVT_EXIT_WALK(60, jan_00_ENTRY_2, "jan_08", jan_08_ENTRY_0);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitWalk_jan_01_0), TRIGGER_FLOOR_ABOVE, COLLIDER_deilise, 1, 0)
    BindTrigger(Ref(EVS_ExitWalk_jan_08_0), TRIGGER_FLOOR_ABOVE, COLLIDER_deiline, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_JADE_JUNGLE)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Set(GF_MAP_JadeJungle, true)
    Call(MakeNpcs, false, Ref(DefaultNPCs))
    ExecWait(EVS_MakeEntities)
    // waves
    Call(SetTexPanner, MODEL_o135, TEX_PANNER_1)
    Call(SetTexPanner, MODEL_o142, TEX_PANNER_1)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_1)
        TEX_PAN_PARAMS_STEP(    0,  400,    0,    0)
        TEX_PAN_PARAMS_FREQ(    0,    1,    0,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    // water surface
    Call(SetTexPanner, MODEL_o52, TEX_PANNER_3)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_3)
        TEX_PAN_PARAMS_STEP( -100,  200,    0,    0)
        TEX_PAN_PARAMS_FREQ(    1,    1,    0,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Exec(EVS_SetupWhale)
    Exec(EVS_SetupFoliage)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitne, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitse, COLLIDER_FLAGS_UPPER_MASK)
    Call(GetEntryID, LVar0)
    IfEq(LVar0, jan_00_ENTRY_0)
        Exec(EVS_BindExitTriggers)
    Else
        Set(LVar0, Ref(EVS_BindExitTriggers))
        Exec(EnterWalk)
    EndIf
    Call(SpawnSunEffect, FX_SUN_FROM_LEFT)
    ExecWait(EVS_80241C10)
    Call(PlaySound, SOUND_LOOP_JAN_BEACH_WAVES)
    Return
    End
};
