#include "dro_02.h"
#include "world/area/dro/dro_01.h"
#include "world/area/sbk/sbk_02.h"

EvtScript EVS_ExitWalk_dro_01_1 = EVT_EXIT_WALK(60, $Dro01, $dro_01.Dro02);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_dro_01_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    Return
    End
};

EvtScript EVS_OnReadPoster = {
    Call(DisablePlayerInput, true)
    Call(ShowMessageAtScreenPos, MSG_Menus_017C, 160, 40)
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript EVS_EnterScene = {
    Call(PlaySound, SOUND_LOOP_SBK_RUINS_RISING_DISTANT)
    Call(UseSettingsFrom, CAM_DEFAULT, 190, 0, -37)
    Call(SetPanTarget, CAM_DEFAULT, 190, 0, -37)
    Call(SetCamDistance, CAM_DEFAULT, 200.0)
    Call(SetCamPitch, CAM_DEFAULT, 13.0, -10.0)
    Call(SetCamSpeed, CAM_DEFAULT, 90.0)
    Call(PanToTarget, CAM_DEFAULT, 0, true)
    Call(SetModelTintMode, APPLY_TINT_BG, nullptr, ENV_TINT_REMAP)
    Call(SetModelTintMode, APPLY_TINT_GROUPS, -1, ENV_TINT_REMAP)
    Call(SetModelTintParams, ENV_TINT_REMAP, 44, 32, 177, 0, 0, 0, 0, 0, 0)
    Call(DisablePlayerInput, true)
    Thread
        Call(ShakeCam, CAM_DEFAULT, 0, 300, 0.2)
    EndThread
    Thread
        Wait(60)
        Call(GetEntryID, LVar0)
        IfEq(LVar0, $RuinsRisingA.index)
            Call(GotoMap, $sbk_02.RuinsRisingA)
        Else
            Call(GotoMap, $sbk_02.RuinsRisingB)
        EndIf
        Wait(100)
    EndThread
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_DRY_DRY_OUTPOST)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, false, DefaultNPCs)
    Call(InitVirtualEntityList)
    ExecWait(EVS_MakeEntities)
    ExecWait(EVS_SetupRooms)
    Exec(EVS_SetupMusic)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseOrEq($RuinsRisingA.index)
        CaseOrEq($RuinsRisingB.index)
            ExecWait(EVS_EnterScene)
        EndCaseGroup
        CaseDefault
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
    EndSwitch
    Wait(1)
    Thread
        Call(SetTexPanner, MODEL_kemuri, TEX_PANNER_1)
        TEX_PAN_PARAMS_ID(TEX_PANNER_1)
        TEX_PAN_PARAMS_STEP(    0,  420,    0,    0)
        TEX_PAN_PARAMS_FREQ(    0,    1,    0,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Set(MF_SheekTauntPending, false)
    BindTrigger(EVS_OnReadPoster, TRIGGER_WALL_PRESS_A, COLLIDER_poster, 1, 0)
    Thread
        Loop(0)
            Call(GetPlayerPos, LVar0, LVar1, LVar2)
            IfLt(LVar2, -200)
                Call(EnableGroup, MODEL_mazinai, true)
            Else
                Call(EnableGroup, MODEL_mazinai, false)
            EndIf
            Wait(1)
        EndLoop
    EndThread
    Call(SetCamSpeed, CAM_DEFAULT, 1.334)
    Return
    End
};
