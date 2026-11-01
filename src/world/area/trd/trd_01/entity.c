#include "trd_01.h"
#include "entity.h"

extern EvtScript EVS_ExitDoors_trd_02_0;

EvtScript EVS_FocusCamOnLock = {
    Label(0)
        IfEq(GF_TRD01_Item_FortressKey, true)
            Call(AwaitPlayerApproach, 320, 0, 40)
            Call(UseSettingsFrom, CAM_DEFAULT, 220, 0, 0)
            Call(SetPanTarget, CAM_DEFAULT, 300, 0, 0)
            Call(SetCamDistance, CAM_DEFAULT, 350.0)
            Call(GetCamPosA, CAM_DEFAULT, LVar0, LVar1)
            Call(SetCamPosA, CAM_DEFAULT, -64.0, LVar1)
            Call(SetCamSpeed, CAM_DEFAULT, 3.0)
            Call(PanToTarget, CAM_DEFAULT, 0, true)
            Call(AwaitPlayerLeave, 320, 0, 60)
            Call(PanToTarget, CAM_DEFAULT, 0, false)
        EndIf
        Wait(1)
        Goto(0)
    Return
    End
};

EvtScript EVS_UnlockDoors = {
    SetGroup(EVT_GROUP_NEVER_PAUSE)
    SuspendGroup(EVT_GROUP_FLAG_INTERACT)
    Call(ShowKeyChoicePopup)
    IfEq(LVar0, ITEM_CHOICE_NONE)
        Call(ShowMessageAtScreenPos, MSG_Menus_00D8, 160, 40)
        Call(CloseChoicePopup)
        ResumeGroup(EVT_GROUP_FLAG_INTERACT)
        Return
    EndIf
    IfEq(LVar0, ITEM_CHOICE_CANCELED)
        Call(CloseChoicePopup)
        ResumeGroup(EVT_GROUP_FLAG_INTERACT)
        Return
    EndIf
    Call(RemoveItem, ITEM_KOOPA_FORTRESS_KEY)
    Call(CloseChoicePopup)
    Set(GF_TRD01_UnlockedDoor, true)
    Call(GetEntityPosition, MV_EntityID_Padlock, LVar0, LVar1, LVar2)
    Call(PlaySoundAt, SOUND_USE_KEY, SOUND_SPACE_DEFAULT, LVar0, LVar1, LVar2)
    Call(SetEntityUsed, MV_EntityID_Padlock)
    Call(PanToTarget, CAM_DEFAULT, 0, false)
    ResumeGroup(EVT_GROUP_FLAG_INTERACT)
    Unbind
    Return
    End
};

EvtScript EVS_BindLockTrigger = {
    BindTrigger(EVS_ExitDoors_trd_02_0, TRIGGER_WALL_PRESS_A, COLLIDER_tte, 1, 0)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    IfEq(GF_TRD01_UnlockedDoor, false)
        Call(MakeMarkerEntity, $Padlock_1)
        Call(AssignScript, EVS_BindLockTrigger)
        Set(MV_EntityID_Padlock, LVar0)
    EndIf
    IfLt(GB_StoryProgress, STORY_CH1_RAISED_SUBMERGED_STAIRS)
        Call(MakeMarkerEntity, $BlueSwitch_1)
    EndIf
    Call(MakeMarkerEntity, $Item_SmashCharge_1)
    IfEq(GF_TRD01_Defeated_KoopaGuard, true)
        IfEq(GF_TRD01_Item_FortressKey, false)
            Call(MakeMarkerEntity, $Item_KoopaFortressKey_1)
        EndIf
    EndIf
    Return
    End
};
