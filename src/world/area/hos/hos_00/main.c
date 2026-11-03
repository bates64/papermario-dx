#include "hos_00.h"
#include "world/area/hos/hos_01.h"
#include "world/area/hos/hos_06.h"
#include "world/area/osr/osr_00.h"
#include "world/area/osr/osr_01.h"

#include "../common/FallingStars.inc.c"

EvtScript EVS_ExitWalk_osr = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(UseExitHeading, 60, $PeachsCastle.index)
    Exec(ExitWalk)
    Switch(GB_StoryProgress)
        CaseRange(STORY_CH0_WAKE_UP, STORY_CH8_REACHED_PEACHS_CASTLE)
            Call(GotoMap, $osr_01.ShootingStarPath)
        CaseDefault
            Call(GotoMap, $osr_00.ShootingStarPath)
    EndSwitch
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitWalk_hos_01_0 = EVT_EXIT_WALK(60, $ShootingStarSummit, $hos_01.ShootingStarPath);
EvtScript EVS_ExitWalk_hos_06_0 = EVT_EXIT_WALK(60, $MerluvleesHouse, $hos_06.ShootingStarPath);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_osr, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_hos_01_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deiline, 1, 0)
    BindTrigger(EVS_ExitWalk_hos_06_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilise, 1, 0)
    Return
    End
};

EvtScript EVS_TexPan_Unknown = {
    SetGroup(EVT_GROUP_NEVER_PAUSE)
    Set(LVar0, 0)
    Loop(0)
        Call(SetTexPanOffset, TEX_PANNER_D, TEX_PANNER_MAIN, LVar0, 0)
        Add(LVar0, 0x4000)
        Wait(15)
    EndLoop
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetLoadType, LVar1)
    IfEq(LVar1, LOAD_FROM_FILE_SELECT)
        Exec(EVS_SetupBackgroundShade)
        Exec(EnterSavePoint)
        Exec(EVS_BindExitTriggers)
        Return
    EndIf
    Call(GetEntryID, LVar0)
    IfEq(LVar0, $StarShip.index)
        Call(SetGroupVisibility, MODEL_g107, MODEL_GROUP_HIDDEN)
        Exec(EVS_Scene_Wishing)
        Return
    Else
        Exec(EVS_SetupBackgroundShade)
        Set(LVar0, EVS_BindExitTriggers)
        Exec(EnterWalk)
        Wait(1)
    EndIf
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_SHOOTING_STAR_SUMMIT)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Set(GF_MAP_ShootingStarSummit, true)
    Set(GF_MAC01_RowfBadgesChosen, false)
    Call(GetEntryID, LVar0)
    IfEq(LVar0, $StarShip.index)
        Call(MakeNpcs, false, WishingNPCs)
    Else
        Call(MakeNpcs, false, DefaultNPCs)
    EndIf
    ExecWait(EVS_MakeEntities)
    Call(GetEntryID, LVar0)
    IfNe(LVar0, $StarShip.index)
        Exec(EVS_Starfall_Directed)
    EndIf
    ExecWait(EVS_SetupMusic)
    IfEq(GB_StoryProgress, STORY_CH0_BEGAN_PEACH_MISSION)
        IfEq(AF_HOS00_SkipTwinkMeetingDelay, false)
            Wait(50)
            Set(AF_HOS00_SkipTwinkMeetingDelay, true)
        EndIf
        Exec(EVS_Scene_MeetingTwink)
    EndIf
    Exec(EVS_EnterMap)
    Exec(EVS_TexPan_Unknown)
    Return
    End
};
