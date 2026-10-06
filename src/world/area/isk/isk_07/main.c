#include "isk_07.h"

EvtScript EVS_ExitWalk_isk_08_2 = EVT_EXIT_WALK(40, isk_07_ENTRY_0, "isk_08", isk_08_ENTRY_2);
EvtScript EVS_ExitWalk_isk_04_1 = EVT_EXIT_WALK(40, isk_07_ENTRY_1, "isk_04", isk_04_ENTRY_1);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitWalk_isk_08_2), TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(Ref(EVS_ExitWalk_isk_04_1), TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_DRY_DRY_RUINS)
    Call(SetSpriteShading, SHADING_ISK_07)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    IfEq(GF_ISK07_Defeated_Mummies, false)
        Call(MakeNpcs, true, Ref(DefaultNPCs))
    EndIf
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupLock)
    Exec(EVS_SetupStairs)
    Exec(EVS_SetupSwitch)
    Exec(EVS_SetupSarcophagi)
#if VERSION_PAL
    Call(SetMusic, 0, SONG_DRY_DRY_RUINS, 0, VOL_LEVEL_FULL)
#else
    Switch(GB_StoryProgress)
        CaseLt(STORY_CH2_SOLVED_ARTIFACT_PUZZLE)
            Call(SetMusic, 0, SONG_DRY_DRY_RUINS, 0, VOL_LEVEL_FULL)
        CaseLt(STORY_CH2_DEFEATED_TUTANKOOPA)
            Call(SetMusic, 0, SONG_RUINS_BASEMENT, 0, VOL_LEVEL_FULL)
        CaseGe(STORY_CH2_DEFEATED_TUTANKOOPA)
            Call(SetMusic, 0, SONG_DRY_DRY_RUINS, 0, VOL_LEVEL_FULL)
    EndSwitch
#endif
    Set(LVar0, Ref(EVS_BindExitTriggers))
    Exec(EnterWalk)
    Return
    End
};
