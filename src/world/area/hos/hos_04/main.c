#include "hos_04.h"
#include "world/area/hos/hos_03.h"
#include "world/area/hos/hos_05.h"

EvtScript EVS_ExitWalk_hos_03_1 = EVT_EXIT_WALK(60, $StarHaven, $hos_03.OutsideSanctuary);

#if VERSION_JP
EvtScript EVS_ExitWalk_hos_05_0 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o162, COLLIDER_FLAGS_UPPER_MASK)
    Call(UseExitHeading, 60, $StarSanctuary.index)
    Exec(ExitWalk)
    Call(GotoMap, $hos_05.OutsideSanctuary)
    Wait(100)
    Return
    End
};
#else
EvtScript EVS_ExitWalk_hos_05_0 = EVT_EXIT_WALK(60, $StarSanctuary, $hos_05.OutsideSanctuary);
#endif

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_hos_03_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deilinw, 1, 0)
    BindTrigger(EVS_ExitWalk_hos_05_0, TRIGGER_FLOOR_ABOVE, COLLIDER_o163, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Set(AF_HOS05_SkipMusicChange, false)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($StarHaven.index)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitnw, COLLIDER_FLAGS_UPPER_MASK)
            IfEq(GF_HOS04_Visited, false)
                Thread
                    Call(DisablePlayerInput, true)
                    Call(SetPlayerPos, -630, 0, 0)
                    Call(GetPartnerInUse, LVar0)
                    IfEq(LVar0, PARTNER_NONE)
                        Call(DisablePartnerAI, false)
                        Call(SetNpcPos, NPC_PARTNER, -660, 0, 0)
                        Wait(1)
                        Call(EnablePartnerAI)
                    EndIf
                    Call(UseSettingsFrom, CAM_DEFAULT, -565, 0, 0)
                    Call(SetPanTarget, CAM_DEFAULT, -565, 0, 0)
                    Call(SetCamDistance, CAM_DEFAULT, 1350)
                    Call(SetCamPitch, CAM_DEFAULT, 15.0, -25.0)
                    Call(SetCamPosA, CAM_DEFAULT, -15.0, -100.0)
                    Call(SetCamPosB, CAM_DEFAULT, 87.5, 50.0)
                    Call(SetCamSpeed, CAM_DEFAULT, 90.0)
                    Call(PanToTarget, CAM_DEFAULT, 0, true)
                    Call(WaitForCam, CAM_DEFAULT, 1.0)
                    Wait(10)
                    Call(SetCamPitch, CAM_DEFAULT, 4.0, -7.5)
                    Call(SetCamSpeed, CAM_DEFAULT, 0.15)
                    Call(PanToTarget, CAM_DEFAULT, 0, true)
                    Call(WaitForCam, CAM_DEFAULT, 1.0)
                    Wait(30)
                    Set(LVar0, EVS_BindExitTriggers)
                    ExecWait(EnterWalk)
                    Wait(20)
                    Set(GF_HOS04_Visited, true)
                    Call(GetPlayerPos, LVar0, LVar1, LVar2)
                    Call(UseSettingsFrom, CAM_DEFAULT, LVar0, 0, LVar2)
                    Call(SetPanTarget, CAM_DEFAULT, LVar0, 0, LVar2)
                    Call(SetCamSpeed, CAM_DEFAULT, 90.0)
                    Call(PanToTarget, CAM_DEFAULT, 0, true)
                    Call(WaitForCam, CAM_DEFAULT, 1.0)
                    Call(PanToTarget, CAM_DEFAULT, 0, false)
                    Set(AF_HOS05_SkipMusicChange, true)
                    Call(DisablePlayerInput, false)
                EndThread
            Else
                Set(LVar0, EVS_BindExitTriggers)
                Exec(EnterWalk)
                Wait(1)
            EndIf
        CaseEq($StarSanctuary.index)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitnw, COLLIDER_FLAGS_UPPER_MASK)
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
        CaseEq($StarShip.index)
            Exec(EVS_Starship_FlyingAway)
        CaseEq($Entry3.index)
            ExecWait(EVS_Intro_PreHeist_Unused)
        CaseEq($Entry4.index)
            ExecWait(EVS_Intro_PostHeist)
        CaseEq(5)
            Call(EnableGroup, MODEL_g1, false)
            Exec(EVS_BetaStarship_Flight1)
        CaseEq(6)
            Call(EnableGroup, MODEL_g1, false)
            Exec(EVS_BetaStarship_Flight2)
        CaseEq(7)
            Call(EnableGroup, MODEL_g1, false)
            Exec(EVS_BetaStarship_Return)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_STAR_HAVEN)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Thread
        Call(MakeNpcs, false, DefaultNPCs)
    EndThread
    Exec(EVS_SetupFountains)
    ExecWait(EVS_SetupMusic)
    Exec(EVS_EnterMap)
    Wait(1)
    Exec(EVS_SetupNarrator)
    Return
    End
};
