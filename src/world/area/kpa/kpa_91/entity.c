#include "kpa_91.h"
#include "entity.h"

ITEM_LIST(KeyList_PrisonCell, ITEM_PRISON_KEY);

EvtScript EVS_UnlockPrompt_PrisonCell = {
    Call(ShowKeyChoicePopup)
    IfEq(LVar0, ITEM_CHOICE_NONE)
        Call(ShowMessageAtScreenPos, MSG_Menus_00D8, 160, 40)
        Call(CloseChoicePopup)
        Return
    EndIf
    IfEq(LVar0, ITEM_CHOICE_CANCELED)
        Call(CloseChoicePopup)
        Return
    EndIf
    Call(RemoveKeyItemAt, LVar1)
    Set(GF_KPA91_UnlockedDoor, true)
    Call(GetEntityPosition, MV_EntityID_Padlock, LVar0, LVar1, LVar2)
    Call(PlaySoundAt, SOUND_USE_KEY, SOUND_SPACE_DEFAULT, LVar0, LVar1, LVar2)
    Call(SetEntityUsed, MV_EntityID_Padlock)
    Set(LVar1, 0)
    Wait(5)
    Call(CloseChoicePopup)
    BindTrigger(EVS_OpenCellDoor, TRIGGER_WALL_PRESS_A, COLLIDER_deilittn, 1, 0)
    Unbind
    Return
    End
};

EvtScript EVS_MakeEntities = {
    IfEq(GF_KPA91_UnlockedDoor, false)
        Call(MakeMarkerEntity, $Padlock_1)
        Set(MV_EntityID_Padlock, LVar0)
        BindPadlock(EVS_UnlockPrompt_PrisonCell, TRIGGER_WALL_PRESS_A, EVT_ENTITY_INDEX(0), KeyList_PrisonCell, 0, 1)
    Else
        BindTrigger(EVS_OpenCellDoor, TRIGGER_WALL_PRESS_A, COLLIDER_deilittn, 1, 0)
    EndIf
    IfEq(GF_KPA91_Defeated_Guard, true)
        Call(MakeMarkerEntity, $Item_PrisonKey_1)
    EndIf
    Return
    End
};
