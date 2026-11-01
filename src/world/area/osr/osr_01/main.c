
#include "osr_01.h"
#include "world/area/hos/hos_00.h"
#include "world/area/mac/mac_01.h"

EvtScript EVS_ExitWalk_mac_01_2 = EVT_EXIT_WALK(60, $ToadTown, $mac_01.PeachsCastle);
EvtScript EVS_ExitWalk_hos_00_0 = EVT_EXIT_WALK(60, $ShootingStarPath, $hos_00.PeachsCastle);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_mac_01_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
    BindTrigger(EVS_ExitWalk_hos_00_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript EVS_TexPan_Fountain = {
    SetGroup(EVT_GROUP_NEVER_PAUSE)
    Call(SetTexPanner, MODEL_o501, TEX_PANNER_1)
    Call(SetTexPanner, MODEL_w2, TEX_PANNER_2)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_1)
        TEX_PAN_PARAMS_STEP(    0, -200,    0,    0)
        TEX_PAN_PARAMS_FREQ(    0,    1,    0,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_2)
        TEX_PAN_PARAMS_STEP(    0,    0,    0,  300)
        TEX_PAN_PARAMS_FREQ(    0,    0,    0,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_PEACH_CASTLE_GROUNDS)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Set(GF_MAP_PeachCastleGrounds, true)
    Call(MakeNpcs, false, DefaultNPCs)
    ExecWait(EVS_PlaySong_Starship)
    Exec(EVS_TexPan_Fountain)
    Call(PlaySoundAtF, SOUND_LOOP_OSR_FOUNTAIN_BROKEN, SOUND_SPACE_WITH_DEPTH, 300, 2, 399)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($Wishing.index)
            Call(EnableModel, MODEL_o492, false)
            Exec(EVS_Scene_Wishing)
        CaseDefault
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
    EndSwitch
    Wait(1)
    Return
    End
};
