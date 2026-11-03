#include "hos_05.h"
#include "world/area/hos/hos_04.h"

EvtScript EVS_ExitWalk_hos_04_1 = EVT_EXIT_WALK(60, $OutsideSanctuary, $hos_04.StarSanctuary);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_hos_04_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_Starship_Depart, TRIGGER_FLOOR_TOUCH, COLLIDER_o630, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_STAR_HAVEN)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(GetEntryID, LVar0)
    IfEq(LVar0, $Entry3.index)
        Call(MakeNpcs, false, IntroNPCs)
    Else
        Call(MakeNpcs, false, DefaultNPCs)
    EndIf
    Exec(EVS_SetupStarshipAndWater)
    ExecWait(EVS_SetupMusic)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitw, COLLIDER_FLAGS_UPPER_MASK)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($OutsideSanctuary.index)
            Call(SetCamSpeed, CAM_DEFAULT, 2.5)
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
        CaseEq($StarShip.index)
            Thread
                ExecWait(EVS_EnterStarship)
                Exec(EVS_BindExitTriggers)
            EndThread
        CaseEq($Entry3.index)
            ExecWait(EVS_Intro_Main)
    EndSwitch
    Exec(EVS_SetupNarrator)
    Call(EnableGroup, MODEL_g277, false)
    Call(EnableGroup, MODEL_g279, false)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseRange($OutsideSanctuary.index, $StarShip.index)
            Exec(EVS_SetupLightBeam)
    EndSwitch
    Return
    End
};
