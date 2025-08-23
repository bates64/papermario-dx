#include "isk_05.h"

s32 N(adjust_cam_on_landing)(void) {
    s32 ret = LANDING_CAM_CHECK_SURFACE;

    if (gPlayerStatus.pos.y > 50.0f) {
        ret = LANDING_CAM_NEVER_ADJUST;
    }

    return ret;
}

API_CALLABLE(N(SetupLandingCamAdjust)) {
    phys_set_landing_adjust_cam_check(N(adjust_cam_on_landing));
    return ApiStatus_DONE2;
}

EvtScript N(EVS_ExitWalk_isk_04_4) = EVT_EXIT_WALK(40, isk_05_ENTRY_0, "isk_04", isk_04_ENTRY_4);

EvtScript N(EVS_BindExitTriggers) = {
    BindTrigger(Ref(N(EVS_ExitWalk_isk_04_4)), TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    Return
    End
};

EvtScript N(EVS_EnterWalk_80241F98) = {
    Call(TranslateGroup, MODEL_g304, 0, 65, 0)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilittw, COLLIDER_FLAGS_UPPER_MASK)
    Set(LVar0, Ref(N(EVS_BindExitTriggers)))
    Exec(EnterWalk)
    Return
    End
};

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_DRY_DRY_RUINS)
    Call(SetSpriteShading, SHADING_ISK_05)
    SetUP_CAMERA_ALT_NO_LEAD()
    Call(MakeNpcs, true, Ref(N(DefaultNPCs)))
    ExecWait(N(EVS_MakeEntities))
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
    Call(TranslateGroup, MODEL_g304, 0, 65, 0)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilittw, COLLIDER_FLAGS_UPPER_MASK)
    IfEq(GF_ISK05_Hammer2Block, false)
        Call(SetGroupVisibility, MODEL_wan1, MODEL_GROUP_VISIBLE)
        Call(SetGroupVisibility, MODEL_wan2, MODEL_GROUP_HIDDEN)
    Else
        Call(SetGroupVisibility, MODEL_wan1, MODEL_GROUP_HIDDEN)
        Call(SetGroupVisibility, MODEL_wan2, MODEL_GROUP_VISIBLE)
    EndIf
    Set(LVar0, Ref(N(EVS_BindExitTriggers)))
    Exec(EnterWalk)
    Wait(1)
    Return
    End
};
