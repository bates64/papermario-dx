#include "iwa_11.h"
#include "world/area/iwa/iwa_10.h"
#include "world/area/mac/mac_03.h"

API_CALLABLE(CheckForSkipInput) {
    if (gGameStatusPtr->pressedButtons[0] & (BUTTON_A | BUTTON_B)) {
        return ApiStatus_DONE2;
    } else {
        return ApiStatus_BLOCK;
    }
}

EvtScript EVS_MonitorSceneSkip = {
    IfLt(GB_StoryProgress, STORY_CH2_ARRIVED_AT_MT_RUGGED)
        Return
    EndIf
    Call(GetEntryID, LVar0)
    Call(CheckForSkipInput)
    Switch(LVar0)
        CaseEq($ToadTownStation.index)
            Call(GotoMap, $iwa_10.Train)
        CaseEq($MtRuggedStation.index)
            Call(GotoMap, $mac_03.MtRugged)
    EndSwitch
    Wait(100)
    Return
    End
};

EvtScript EVS_Main = {
    Call(SetCamPerspective, CAM_DEFAULT, CAM_UPDATE_FROM_ZONE, 30, 16, 4096) // uses fov 25 instead of 30
    Call(SetCamBGColor, CAM_DEFAULT, 0, 0, 0)
    Call(SetCamEnabled, CAM_DEFAULT, true)
    Call(SetCamLeadPlayer, CAM_DEFAULT, false)
    Call(UseSettingsFrom, CAM_DEFAULT, 0, 0, 0)
    Call(SetCamPosA, CAM_DEFAULT, -5800, 0)
    Call(SetCamPosB, CAM_DEFAULT, 5700, 0)
    Call(SetCamSpeed, CAM_DEFAULT, 90.0)
    Call(SetPanTarget, CAM_DEFAULT, 0, 0, 0)
    Call(PanToTarget, CAM_DEFAULT, 0, true)
    Call(MakeNpcs, true, DefaultNPCs)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deiliti, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitm, COLLIDER_FLAGS_UPPER_MASK)
    ExecWait(EVS_InitializeTrainScene)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($ToadTownStation.index)
            Exec(EVS_TravelToMtRugged)
        CaseEq($MtRuggedStation.index)
            Exec(EVS_TravelToToadTown)
    EndSwitch
    Exec(EVS_UpdateSceneryPos)
    Exec(EVS_MonitorSceneSkip)
    Exec(EVS_SetupMusic)
    Return
    End
};
