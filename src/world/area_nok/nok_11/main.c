#include "nok_11.h"

#include "world/common/atomic/TexturePan.inc.c"

EvtScript N(EVS_ExitWalk_mac_01_1) = {
    IfEq(GB_KootFavor_State, KOOT_FAVOR_STATE_2)
        Set(GF_KootFavor_LeftKoopaArea, true)
    EndIf
    Call(UseExitHeading, 60, nok_11_ENTRY_0)
    Exec(ExitWalk)
    Call(GotoMap, Ref("mac_01"), mac_01_ENTRY_1)
    Wait(100)
    Return
    End
};

EvtScript N(EVS_ExitWalk_nok_12_0) = EVT_EXIT_WALK_NOK(60, nok_11_ENTRY_1, "nok_12", nok_12_ENTRY_0);

EvtScript N(EVS_SetupTexPan) = {
    // flowers
    Call(SetTexPanner, MODEL_hana2, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_hana3, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_hana4, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_hana5, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_hana6, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_hana7, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_hana8, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_hana9, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_hana10, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_hanahana, TEX_PANNER_0)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_0)
        TEX_PAN_PARAMS_MAX(0x8000)
        TEX_PAN_PARAMS_STEP(0x4000,    0,    0,    0)
        TEX_PAN_PARAMS_FREQ(    12,    0,    0,    0)
        TEX_PAN_PARAMS_INIT(     0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    // water
    Call(SetTexPanner, MODEL_suimen1, TEX_PANNER_1)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_1)
        TEX_PAN_PARAMS_STEP( -100,    0,  600,    0)
        TEX_PAN_PARAMS_FREQ(    1,    0,    1,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    Call(SetTexPanner, MODEL_kabemizu, TEX_PANNER_2)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_2)
        TEX_PAN_PARAMS_STEP( -100,    0,  400,    0)
        TEX_PAN_PARAMS_FREQ(    1,    0,    1,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    Return
    End
};

EvtScript N(EVS_BindExitTriggers) = {
    BindTrigger(Ref(N(EVS_ExitWalk_mac_01_1)), TRIGGER_FLOOR_ABOVE, COLLIDER_deiri1, 1, 0)
    BindTrigger(Ref(N(EVS_ExitWalk_nok_12_0)), TRIGGER_FLOOR_ABOVE, COLLIDER_deili2, 1, 0)
    Return
    End
};

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_PLEASANT_PATH)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT()
    Set(GF_MAP_PleasantPath, true)
    IfEq(GB_StoryProgress, STORY_CH1_STAR_SPRIT_DEPARTED)
        Call(MakeNpcs, false, Ref(N(JrTroopaNPCs)))
    Else
        IfGe(GB_StoryProgress, STORY_CH5_RETURNED_TO_TOAD_TOWN)
            IfEq(GF_NOK11_Defeated_KentC, false)
                Call(MakeNpcs, false, Ref(N(KentCKoopaNPCs)))
            Else
                Call(MakeNpcs, false, Ref(N(DefaultNPCs)))
            EndIf
        Else
            Call(MakeNpcs, false, Ref(N(DefaultNPCs)))
        EndIf
    EndIf
    ExecWait(N(EVS_MakeEntities))
    Exec(N(EVS_SetupTexPan))
    Exec(N(EVS_SetupMusic))
    Call(PlaySound, SOUND_LOOP_NOK_WATER)
    Set(LVar0, Ref(N(EVS_BindExitTriggers)))
    Exec(EnterWalk)
    Wait(1)
    Return
    End
};
