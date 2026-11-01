#include "dgb_10.h"
#include "world/area/dgb/dgb_09.h"

EvtScript EVS_ExitWalk_dgb_09_3 = EVT_EXIT_WALK(40, $Dgb09, $dgb_09.Dgb10);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_dgb_09_3, TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($Dgb09.index)
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
            Wait(1)
        CaseEq($Dgb11.index)
            Call(UseSettingsFrom, CAM_DEFAULT, 375, 0, -188)
            Call(SetPanTarget, CAM_DEFAULT, 375, 0, -188)
            Call(SetCamSpeed, CAM_DEFAULT, 90.0)
            Call(PanToTarget, CAM_DEFAULT, 0, true)
            Call(DisablePlayerInput, true)
            Call(DisablePlayerPhysics, true)
            Call(SetPlayerActionState, ACTION_STATE_JUMP)
            Wait(1)
            Call(SetPlayerJumpscale, 0.7)
            Call(PlayerJump, 375, 0, -188, 20)
            Call(PanToTarget, CAM_DEFAULT, 0, false)
            Call(DisablePlayerPhysics, false)
            Call(DisablePlayerInput, false)
            Call(SetPlayerActionState, ACTION_STATE_IDLE)
            Exec(EVS_BindExitTriggers)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_TUBBAS_MANOR)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupHoles)
    Exec(EVS_SetupMusic)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilits, COLLIDER_FLAGS_UPPER_MASK)
    Call(EnableModel, MODEL_o117, false)
    Call(EnableModel, MODEL_o116, false)
    Call(EnableModel, MODEL_o113, false)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitt1, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitt2, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitt3, COLLIDER_FLAGS_UPPER_MASK)
    Exec(EVS_EnterMap)
    Return
    End
};
