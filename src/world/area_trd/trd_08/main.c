#include "trd_08.h"

extern EvtScript N(EVS_SetupMusic);
extern EvtScript N(EVS_MakeEntities);
extern NpcGroupList N(DefaultNPCs);

#include "world/common/atomic/TexturePan.inc.c"

EvtScript N(EVS_ExitWalk_trd_07_1) = EVT_EXIT_WALK(60, trd_08_ENTRY_0, "trd_07", trd_07_ENTRY_1);

EvtScript N(EVS_BindExitTriggers) = {
    BindTrigger(Ref(N(EVS_ExitWalk_trd_07_1)), TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_KOOPA_BROS_FORTRESS)
    Call(SetSpriteShading, SHADING_NONE)
    SetUP_CAMERA_ALT_NO_LEAD()
    Call(MakeNpcs, true, Ref(N(DefaultNPCs)))
    ExecWait(N(EVS_MakeEntities))
    Exec(N(EVS_SetupMusic))
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_tte, COLLIDER_FLAGS_UPPER_MASK)
    Call(EnableModel, MODEL_o36, false)
    Set(LVar0, Ref(N(EVS_BindExitTriggers)))
    Exec(EnterWalk)
    Wait(1)
    Call(EnableTexPanning, MODEL_suimen, true)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_1)
        TEX_PAN_PARAMS_STEP(  100,    0, -100,    0)
        TEX_PAN_PARAMS_FREQ(    1,    0,    1,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    Return
    End
};
