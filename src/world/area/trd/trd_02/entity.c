#include "trd_02.h"
#include "entity.h"

extern EvtScript EVS_ExitDoors_trd_01_2;

EvtScript EVS_UnlockFortressDoor = {
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
    Call(RemoveKeyItemAt, LVar1)
    Call(CloseChoicePopup)
    Set(GF_TRD02_UnlockedDoor, true)
    Call(GetEntityPosition, MV_EntityID_Padlock, LVar0, LVar1, LVar2)
    Call(PlaySoundAt, SOUND_USE_KEY, SOUND_SPACE_DEFAULT, LVar0, LVar1, LVar2)
    Call(SetEntityUsed, MV_EntityID_Padlock)
    ResumeGroup(EVT_GROUP_FLAG_INTERACT)
    Unbind
    Return
    End
};

EvtScript EVS_BindLockTrigger = {
    BindTrigger(EVS_ExitDoors_trd_01_2, TRIGGER_WALL_PRESS_A, COLLIDER_ttw2, 1, 0)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    IfEq(GF_TRD02_UnlockedDoor, false)
        Call(MakeMarkerEntity, $Padlock_1)
        Call(AssignScript, EVS_BindLockTrigger)
        Set(MV_EntityID_Padlock, LVar0)
    EndIf
    IfLt(GB_StoryProgress, STORY_CH1_LOWERED_SECOND_STAIRS)
        Call(MakeMarkerEntity, $BlueSwitch_1)
    EndIf
    Return
    End
};
