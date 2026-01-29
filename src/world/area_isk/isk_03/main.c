#include "isk_03.h"

b32 N(CamAdjustReady) = false;

s32 N(adjust_cam_on_landing)(void) {
    s32 ret = LANDING_CAM_CHECK_SURFACE;

    if (gGameStatusPtr->entryID == isk_03_ENTRY_0) {
        if (!N(CamAdjustReady)) {
            if (!(gPlayerStatus.pos.y > 0.0f)) {
                N(CamAdjustReady) = true;
            } else {
                return LANDING_CAM_ALWAYS_ADJUST;
            }
        }

        if (gPlayerStatus.pos.y > 0.0f) {
            ret = LANDING_CAM_NEVER_ADJUST;
        }
    } else {
        ret = LANDING_CAM_ALWAYS_ADJUST;
    }

    return ret;
}

API_CALLABLE(N(SetupLandingCamAdjust)) {
    phys_set_landing_adjust_cam_check(N(adjust_cam_on_landing));
    return ApiStatus_DONE2;
}

EvtScript N(EVS_ExitWalk_isk_02_1) = EVT_EXIT_WALK(40, isk_03_ENTRY_0, "isk_02", isk_02_ENTRY_1);
EvtScript N(EVS_ExitWalk_isk_02_2) = EVT_EXIT_WALK(40, isk_03_ENTRY_1, "isk_02", isk_02_ENTRY_2);
EvtScript N(EVS_ExitWalk_isk_04_0) = EVT_EXIT_WALK(40, isk_03_ENTRY_2, "isk_04", isk_04_ENTRY_0);

EvtScript N(EVS_BindExitTriggers) = {
    BindTrigger(Ref(N(EVS_ExitWalk_isk_02_1)), TRIGGER_FLOOR_ABOVE, COLLIDER_deilinw, 1, 0)
    BindTrigger(Ref(N(EVS_ExitWalk_isk_02_2)), TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(Ref(N(EVS_ExitWalk_isk_04_0)), TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_DRY_DRY_RUINS)
    Call(SetSpriteShading, SHADING_ISK_03)
    Call(N(SetupLandingCamAdjust))
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    IfLt(GB_StoryProgress, STORY_CH2_DRAINED_FIRST_SAND_ROOM)
        Call(SetZoneEnabled, ZONE_o2023, false)
        Call(SetZoneEnabled, ZONE_03, false)
    Else
        Call(SetZoneEnabled, ZONE_o2023, false)
        Call(SetZoneEnabled, ZONE_o2008, false)
    EndIf
    ExecWait(N(EVS_MakeEntities))
    Exec(N(EVS_SetupSand))
    Exec(N(EVS_SetupSwitch))
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
    Set(LVar0, Ref(N(EVS_BindExitTriggers)))
    Exec(EnterWalk)
    Return
    End
};
