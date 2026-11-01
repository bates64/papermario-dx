#include "isk_12.h"
#include "world/area/isk/isk_11.h"
#include "world/area/isk/isk_13.h"
#include "world/area/isk/isk_18.h"

b32 CamAdjustReady = false;

s32 adjust_cam_on_landing(void) {
    s32 ret = LANDING_CAM_CHECK_SURFACE;

    if (gGameStatusPtr->entryID == $StonePuzzleRoomUpper.index) {
        if (!CamAdjustReady) {
            if (!(gPlayerStatus.pos.y > -520.0f)) {
                CamAdjustReady = true;
            } else {
                return LANDING_CAM_ALWAYS_ADJUST;
            }
        }

        if (gPlayerStatus.pos.y > -520.0f) {
            ret = LANDING_CAM_NEVER_ADJUST;
        }
    }

    if (evt_get_variable(nullptr, GB_StoryProgress) >= STORY_CH2_DRAINED_THIRD_SAND_ROOM) {
        ret = LANDING_CAM_ALWAYS_ADJUST;
    }

    return ret;
}

API_CALLABLE(SetupLandingCamAdjust) {
    phys_set_landing_adjust_cam_check(adjust_cam_on_landing);
    return ApiStatus_DONE2;
}

EvtScript EVS_ExitWalk_isk_11_1 = EVT_EXIT_WALK(40, $StonePuzzleRoomUpper, $isk_11.SandDrainage3Upper);
EvtScript EVS_ExitWalk_isk_11_2 = EVT_EXIT_WALK(40, $StonePuzzleRoomLower, $isk_11.SandDrainage3Lower);
EvtScript EVS_ExitWalk_isk_18_1 = EVT_EXIT_WALK(40, $DeepTunnel, $isk_18.SandDrainage3);
EvtScript EVS_ExitWalk_isk_13_0 = EVT_EXIT_WALK(40, $LunarStoneRoom, $isk_13.SandDrainage3);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_isk_11_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deilinw, 1, 0)
    BindTrigger(EVS_ExitWalk_isk_11_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_isk_18_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deilisw, 1, 0)
    BindTrigger(EVS_ExitWalk_isk_13_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_DRY_DRY_RUINS)
    Call(SetSpriteShading, SHADING_ISK_12)
    Call(SetupLandingCamAdjust)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    IfLt(GB_StoryProgress, STORY_CH2_DRAINED_THIRD_SAND_ROOM)
        Call(SetZoneEnabled, ZONE_deiliw, false)
    Else
        Call(SetZoneEnabled, ZONE_deiliw, false)
        Call(SetZoneEnabled, ZONE_on, false)
    EndIf
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupSand)
    Exec(EVS_SetupSwitches)
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
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Return
    End
};
