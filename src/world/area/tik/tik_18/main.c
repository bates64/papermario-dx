#include "tik_18.h"

EvtScript EVS_ExitWalk_tik_06_1 = EVT_EXIT_WALK(60, tik_18_ENTRY_0, "tik_06", tik_06_ENTRY_1);
EvtScript EVS_ExitWalk_tik_02_0 = EVT_EXIT_WALK(60, tik_18_ENTRY_1, "tik_02", tik_02_ENTRY_0);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitWalk_tik_06_1), TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(Ref(EVS_ExitWalk_tik_02_0), TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_TOAD_TOWN_TUNNELS)
    Call(SetSpriteShading, SHADING_TIK_18)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, true, Ref(DefaultNPCs))
    ExecWait(EVS_MakeEntities)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o44, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o45, COLLIDER_FLAGS_UPPER_MASK)
    Exec(EVS_SetupDrips)
    Exec(EVS_SetupMusic)
    Call(PlaySound, SOUND_LOOP_TIK18_WATER)
    Call(SetTexPanner, MODEL_nagare, TEX_PANNER_1)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_1)
        TEX_PAN_PARAMS_STEP(   50,  200,  110,  500)
        TEX_PAN_PARAMS_FREQ(    1,    1,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Call(SetTexPanner, MODEL_mizu, TEX_PANNER_2)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_2)
        TEX_PAN_PARAMS_STEP(    0, -200, -100, -500)
        TEX_PAN_PARAMS_FREQ(    1,    1,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Call(SetTexPanner, MODEL_mizu2, TEX_PANNER_3)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_3)
        TEX_PAN_PARAMS_STEP(    0, -250, -100, -500)
        TEX_PAN_PARAMS_FREQ(    1,    1,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Set(LVar0, Ref(EVS_BindExitTriggers))
    Exec(EnterWalk)
    Wait(1)
    Return
    End
};
