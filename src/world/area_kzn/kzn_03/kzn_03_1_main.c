#include "kzn_03.h"
#include "entity.h"

#include "world/common/atomic/TexturePan.inc.c"

EvtScript N(EVS_ExitWalk_kzn_02_1) = EVT_EXIT_WALK(60, kzn_03_ENTRY_0, "kzn_02", kzn_02_ENTRY_1);
EvtScript N(EVS_ExitWalk_kzn_04_0) = EVT_EXIT_WALK(60, kzn_03_ENTRY_1, "kzn_04", kzn_04_ENTRY_0);
EvtScript N(EVS_ExitWalk_kzn_09_0) = EVT_EXIT_WALK(60, kzn_03_ENTRY_2, "kzn_09", kzn_09_ENTRY_0);
EvtScript N(EVS_ExitWalk_kzn_05_1) = EVT_EXIT_WALK(60, kzn_03_ENTRY_3, "kzn_05", kzn_05_ENTRY_1);
EvtScript N(EVS_ExitWalk_kzn_09_2) = EVT_EXIT_WALK(60, kzn_03_ENTRY_4, "kzn_09", kzn_09_ENTRY_2);

EvtScript N(EVS_BindTriggers) = {
    BindTrigger(Ref(N(EVS_ExitWalk_kzn_02_1)), TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    BindTrigger(Ref(N(EVS_ExitWalk_kzn_04_0)), TRIGGER_FLOOR_ABOVE, COLLIDER_deili2, 1, 0)
    BindTrigger(Ref(N(EVS_ExitWalk_kzn_09_0)), TRIGGER_FLOOR_ABOVE, COLLIDER_deili3, 1, 0)
    BindTrigger(Ref(N(EVS_ExitWalk_kzn_05_1)), TRIGGER_FLOOR_ABOVE, COLLIDER_deili4, 1, 0)
    BindTrigger(Ref(N(EVS_ExitWalk_kzn_09_2)), TRIGGER_FLOOR_ABOVE, COLLIDER_deili5, 1, 0)
    Return
    End
};

EvtScript N(EVS_SetupTexPan) = {
    // lava surfaces
    Call(SetTexPanner, MODEL_o112, TEX_PANNER_1)
    Call(SetTexPanner, MODEL_o151, TEX_PANNER_1)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_1)
        TEX_PAN_PARAMS_STEP(  400,    0,  800,    0)
        TEX_PAN_PARAMS_FREQ(    1,    0,    1,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    // leaking lava
    Call(SetTexPanner, MODEL_toro, TEX_PANNER_5)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_5)
        TEX_PAN_PARAMS_STEP(  300, -500,    0,    0)
        TEX_PAN_PARAMS_FREQ(    1,    1,    0,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    // lava bubbles
    Call(SetTexPanner, MODEL_poko, TEX_PANNER_D)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_D)
        TEX_PAN_PARAMS_MAX(0x80000000)
        TEX_PAN_PARAMS_STEP(0x8000,  0,    0,    0)
        TEX_PAN_PARAMS_FREQ(   6,    0,    0,    0)
        TEX_PAN_PARAMS_INIT(   0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    // smoke
    Call(SetTexPanner, MODEL_kem1, TEX_PANNER_3)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_3)
        TEX_PAN_PARAMS_STEP( -200,    0,  600, -400)
        TEX_PAN_PARAMS_FREQ(    1,    0,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    Call(SetTexPanner, MODEL_kem2, TEX_PANNER_4)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_4)
        TEX_PAN_PARAMS_STEP( 500,    0,    0, -400)
        TEX_PAN_PARAMS_FREQ(   1,    0,    0,    1)
        TEX_PAN_PARAMS_INIT(   0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    Return
    End
};

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_MT_LAVALAVA)
    Call(SetSpriteShading, SHADING_KZN_03)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(MakeNpcs, TRUE, Ref(N(DefaultNPCs)))
    ExecWait(N(EVS_MakeEntities))
    Call(GetLoadType, LVar1)
    IfEq(LVar1, LOAD_FROM_FILE_SELECT)
        Exec(EnterSavePoint)
        Exec(N(EVS_BindTriggers))
    Else
        Set(LVar0, Ref(N(EVS_BindTriggers)))
        Exec(EnterWalk)
    EndIf
    Wait(1)
    Call(SetMusicTrack, 0, SONG_MT_LAVALAVA, 0, 8)
    Call(PlayAmbientSounds, AMBIENT_LAVA_1)
    Exec(N(EVS_SetupTexPan))
    ExecWait(N(EVS_SetupZiplines))
    Return
    End
};
