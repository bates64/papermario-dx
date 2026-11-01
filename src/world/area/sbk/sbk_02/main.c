#include "sbk_02.h"
#include "world/area/isk/isk_01.h"
#include "world/area/sbk/sbk_01.h"
#include "world/area/sbk/sbk_03.h"
#include "world/area/sbk/sbk_12.h"
#include "effects.h"

EvtScript EVS_ExitWalk_sbk_01_1 = EVT_EXIT_WALK(60, $West, $sbk_01.East);
EvtScript EVS_ExitWalk_sbk_03_0 = EVT_EXIT_WALK(60, $East, $sbk_03.West);
EvtScript EVS_ExitWalk_sbk_12_2 = EVT_EXIT_WALK(60, $South, $sbk_12.North);
EvtScript EVS_ExitWalk_isk_01_0 = EVT_EXIT_WALK(60, $DryDryRuins, $isk_01.DryDryDesert);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_sbk_01_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_03_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_12_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
    BindTrigger(EVS_ExitWalk_isk_01_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($PeachInterlude.index)
            Exec(EVS_BindExitTriggers)
        CaseOrEq($RuinsRisingA.index)
        CaseOrEq($RuinsRisingB.index)
            Exec(EVS_BindExitTriggers)
        EndCaseGroup
        CaseDefault
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_DRY_DRY_DESERT)
    Call(SetSpriteShading, SHADING_NONE)
    IfEq(GB_StoryProgress, STORY_CH2_GOT_PULSE_STONE)
        Call(DisablePulseStone, false)
    EndIf
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, false, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    IfLt(GB_StoryProgress, STORY_CH2_UNCOVERED_DRY_DRY_RUINS)
        PlayEffect(EFFECT_SUN, FX_SUN_FROM_LEFT, $SunPos_1.pos.x, $SunPos_1.pos.y, $SunPos_1.pos.z, 0, 0)
        Set(MV_Effect_Sun, LVarF)
    EndIf
    IfEq(GB_StoryProgress, STORY_CH2_BEGAN_PEACH_MISSION)
        Call(SetMusic, 0, SONG_STAR_SPIRIT_THEME, BGM_VARIATION_1, VOL_LEVEL_FULL)
    Else
        Exec(EVS_SetupMusic)
    EndIf
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseOrEq($RuinsRisingA.index)
        CaseOrEq($RuinsRisingB.index)
        EndCaseGroup
        CaseDefault
            ExecWait(EVS_SetupRuins)
    EndSwitch
    Exec(EVS_EnterMap)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($PeachInterlude.index)
            Wait(65)
        CaseOrEq($RuinsRisingA.index)
        CaseOrEq($RuinsRisingB.index)
            Exec(EVS_Ruins_Arise_Continued)
            Wait(3)
        EndCaseGroup
        CaseDefault
            Wait(1)
    EndSwitch
    Return
    End
};
