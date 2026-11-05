#include "sbk_30.h"
#include "world/area/dro/dro_01.h"
#include "world/area/sbk/sbk_20.h"
#include "world/area/sbk/sbk_31.h"
#include "world/area/sbk/sbk_40.h"
#include "world/area/sbk/sbk_99.h"
#include "effects.h"

EvtScript EVS_ExitWalk_sbk_99_1 = EVT_EXIT_WALK(60, $MtRugged, $sbk_99.Sbk30);
EvtScript EVS_ExitWalk_sbk_31_0 = EVT_EXIT_WALK(60, $East, $sbk_31.West);
EvtScript EVS_ExitWalk_sbk_20_3 = EVT_EXIT_WALK(60, $North, $sbk_20.South);
EvtScript EVS_ExitWalk_sbk_40_2 = EVT_EXIT_WALK(60, $South, $sbk_40.North);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_sbk_99_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_31_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_20_3, TRIGGER_FLOOR_ABOVE, COLLIDER_deilin, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_40_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($MtRugged.index)
            IfEq(GF_SBK30_Visited, false)
                Set(GF_SBK30_Visited, true)
                Set(GB_StoryProgress, STORY_CH2_ARRIVED_AT_DRY_DRY_DESERT)
            EndIf
        CaseEq($East.index)
        CaseEq($North.index)
        CaseEq($South.index)
        CaseEq($RuinsRisingA.index)
            Return
    EndSwitch
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Return
    End
};

EvtScript EVS_Scene_RuinsRising = {
    Call(PlaySound, SOUND_LOOP_SBK_RUINS_RISING_DISTANT)
    Call(UseSettingsFrom, CAM_DEFAULT, 193, 0, -237)
    Call(SetPanTarget, CAM_DEFAULT, 193, 0, -237)
    Call(SetCamSpeed, CAM_DEFAULT, 90.0)
    Call(PanToTarget, CAM_DEFAULT, 0, true)
    Call(SetModelTintMode, APPLY_TINT_BG, nullptr, ENV_TINT_REMAP)
    Call(SetModelTintMode, APPLY_TINT_GROUPS, -1, ENV_TINT_REMAP)
    Call(SetModelTintParams, ENV_TINT_REMAP, 44, 32, 177, 0, 0, 0, 0, 0, 0)
    Call(DisablePlayerInput, true)
    Thread
        Call(ShakeCam, CAM_DEFAULT, 0, 300, 0.25)
    EndThread
    Thread
        Wait(60)
        Call(GetEntryID, LVar0)
        IfEq(LVar0, $RuinsRisingA.index)
            Call(GotoMap, $dro_01.RuinsRisingA)
        Else
            Call(GotoMap, $dro_01.RuinsRisingB)
        EndIf
        Wait(100)
    EndThread
    Return
    End
};

EvtScript EVS_Main = {
    IfEq(GB_StoryProgress, STORY_CH2_GOT_PULSE_STONE)
        Call(DisablePulseStone, false)
    EndIf
    IfLt(GB_StoryProgress, STORY_UNUSED_FFFFFFCC)
        Call(EnableGroup, MODEL_g28, false)
        Call(MakeNpcs, false, DefaultNPCs)
    Else
        Call(EnableGroup, MODEL_g23, false)
        Call(EnableGroup, MODEL_sakji_tent, false)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_Default, COLLIDER_FLAGS_UPPER_MASK)
        Call(SetZoneEnabled, ZONE_o25, false)
    EndIf
    Exec(EVS_SetupMusic)
    Exec(EVS_EnterMap)
    Exec(EVS_SetupFoliage)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseOrEq($RuinsRisingA.index)
        CaseOrEq($RuinsRisingB.index)
            ExecWait(EVS_Scene_RuinsRising)
        EndCaseGroup
        CaseDefault
            Call(SpawnSunEffect, FX_SUN_FROM_LEFT)
    EndSwitch
    Return
    End
};
