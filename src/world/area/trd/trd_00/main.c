#include "trd_00.h"
#include "world/area/nok/nok_15.h"
#include "world/area/trd/trd_01.h"
#include "world/area/trd/trd_05.h"
#include "sprite/player.h"

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;

EvtScript EVS_ExitWalk_nok_15_1 = EVT_EXIT_WALK(60, $PleasantPath, $nok_15.KoopaBrosFortress);
EvtScript EVS_ExitDoors_trd_01_0 = EVT_EXIT_DOUBLE_DOOR($Trd01, $trd_01.Trd00, COLLIDER_tt2, MODEL_o62, MODEL_doa);
EvtScript EVS_ExitDoors_trd_05_1 =
    EVT_EXIT_DOUBLE_DOOR($Trd05Door, $trd_05.Trd00Door, COLLIDER_tt3, MODEL_o70, MODEL_o69);
EvtScript EVS_ExitWalk_trd_05_2 = EVT_EXIT_WALK(60, $Trd05Walk, $trd_05.Trd00Walk);
EvtScript EVS_ExitWalk_nok_15_2 = EVT_EXIT_WALK(60, $PleasantPathUpper, $nok_15.KoopaBrosFortressUpper);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_nok_15_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitDoors_trd_01_0, TRIGGER_WALL_PRESS_A, COLLIDER_tt2, 1, 0)
    BindTrigger(EVS_ExitDoors_trd_05_1, TRIGGER_WALL_PRESS_A, COLLIDER_tt3, 1, 0)
    BindTrigger(EVS_ExitWalk_trd_05_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deili5, 1, 0)
    BindTrigger(EVS_ExitWalk_nok_15_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deilit, 1, 0)
    Return
    End
};

EvtScript EVS_Scene_ArriveAtFortress = {
    Call(DisablePlayerInput, true)
    Call(DisablePlayerPhysics, true)
    Call(SetPlayerPos,NPC_DISPOSE_LOCATION)
    Call(SetNpcPos, NPC_PARTNER, NPC_DISPOSE_LOCATION)
    Thread
        Call(UseSettingsFrom, CAM_DEFAULT, -730, 0, 400)
        Call(SetPanTarget, CAM_DEFAULT, 20, 0, 400)
        Call(SetCamDistance, CAM_DEFAULT, -1000)
        Call(SetCamPitch, CAM_DEFAULT, 18, -20.0)
        Call(SetCamSpeed, CAM_DEFAULT, 90.0)
        Call(PanToTarget, CAM_DEFAULT, 0, true)
        Call(WaitForCam, CAM_DEFAULT, 1.0)
        Call(SetPanTarget, CAM_DEFAULT, -480, 0, 400)
        Call(SetCamDistance, CAM_DEFAULT, -1300)
        Call(SetCamPitch, CAM_DEFAULT, 18, -11.5)
        Call(SetCamSpeed, CAM_DEFAULT, 0.8)
        Call(PanToTarget, CAM_DEFAULT, 0, true)
        Call(WaitForCam, CAM_DEFAULT, 1.0)
        Wait(5)
        Call(ResetCam, CAM_DEFAULT, 4.0)
    EndThread
    Wait(82)
    Call(SetPlayerPos, -1041, 0, 204)
    Call(SetPlayerAnimation, ANIM_Mario1_Walk)
    Call(SetNpcPos, NPC_PARTNER, -1041, 0, 204)
    Call(DisablePlayerPhysics, false)
    Call(PlayerMoveTo, -900, 200, 30)
    Call(SetPlayerAnimation, ANIM_Mario1_Idle)
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript EVS_EnterMap = {
    SetGroup(EVT_GROUP_NEVER_PAUSE)
    SuspendGroup(EVT_GROUP_FLAG_INTERACT)
    Call(GetLoadType, LVar1)
    IfEq(LVar1, LOAD_FROM_FILE_SELECT)
        Exec(EnterSavePoint)
        Exec(EVS_BindExitTriggers)
        Return
    EndIf
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($PleasantPath.index)
            IfLt(GB_StoryProgress, STORY_CH1_ARRIVED_AT_KOOPA_FORTRESS)
                Set(GB_StoryProgress, STORY_CH1_ARRIVED_AT_KOOPA_FORTRESS)
                ExecWait(EVS_Scene_ArriveAtFortress)
                Exec(EVS_BindExitTriggers)
            Else
                Set(LVar0, EVS_BindExitTriggers)
                Exec(EnterWalk)
            EndIf
        CaseEq($Trd01.index)
            Set(LVar2, MODEL_o62)
            Set(LVar3, MODEL_doa)
            ExecWait(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq($Trd05Door.index)
            Set(LVar2, MODEL_o70)
            Set(LVar3, MODEL_o69)
            ExecWait(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq($Trd05Walk.index)
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
        CaseEq($PleasantPathUpper.index)
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
        CaseEq($PeachInterlude.index)
            Exec(EVS_BindExitTriggers)
    EndSwitch
    ResumeGroup(EVT_GROUP_FLAG_INTERACT)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GF_MAP_KoopaBrosFortress, true)
    Call(MakeNpcs, true, DefaultNPCs)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($PleasantPath.index)
            // do nothing
        CaseOrEq($Trd01.index)
        CaseOrEq($PleasantPathUpper.index)
        EndCaseGroup
    EndSwitch
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    Wait(1)
    IfEq(GF_TRD05_BombedWall, false)
        Call(SetGroupVisibility, MODEL_g21, MODEL_GROUP_HIDDEN)
    Else
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_tt5, COLLIDER_FLAGS_UPPER_MASK)
        Call(SetGroupVisibility, MODEL_ana, MODEL_GROUP_HIDDEN)
    EndIf
    Exec(EVS_EnterMap)
    Call(GetEntryID, LVar0)
    IfEq(LVar0, $PeachInterlude.index)
        Wait(65)
    Else
        Wait(1)
    EndIf
    Call(SetTexPanner, MODEL_ue, TEX_PANNER_1)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_1)
        TEX_PAN_PARAMS_STEP(  100,    0, -100,    0)
        TEX_PAN_PARAMS_FREQ(    1,    0,    1,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Call(SetTexPanner, MODEL_o125, TEX_PANNER_2)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_2)
        TEX_PAN_PARAMS_STEP(    0,   90,  -60,  -70)
        TEX_PAN_PARAMS_FREQ(    1,    1,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Return
    End
};
