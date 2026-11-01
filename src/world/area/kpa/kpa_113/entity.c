#include "kpa_113.h"
#include "world/area/kpa/kpa_82.h"
#include "entity.h"

ITEM_LIST(KeyList_BowsersCastle, ITEM_BOWSER_CASTLE_KEY);

EvtScript EVS_ExitDoors_kpa_82_0 =
    EVT_EXIT_DOUBLE_DOOR($GuardDoor2, $kpa_82.HiddenDoorRoom2, COLLIDER_deiliett, MODEL_o136, MODEL_o137);

EvtScript EVS_UnlockPrompt_LockedDoor = {
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
    Call(PlaySound, SOUND_USE_KEY)
    Call(RemoveKeyItemAt, LVar1)
    Set(GF_KPA113_UnlockedDoor, true)
    Call(SetEntityUsed, MV_EntityID_Padlock)
    Set(LVar1, 0)
    Wait(5)
    Call(CloseChoicePopup)
    Unbind
    BindTrigger(EVS_ExitDoors_kpa_82_0, TRIGGER_WALL_PRESS_A, COLLIDER_deiliett, 1, 0)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    IfEq(GF_KPA113_UnlockedDoor, false)
        Call(MakeMarkerEntity, $Padlock_1)
        Set(MV_EntityID_Padlock, LVar0)
        BindPadlock(EVS_UnlockPrompt_LockedDoor, TRIGGER_WALL_PRESS_A, EVT_ENTITY_INDEX(0), KeyList_BowsersCastle, 0, 1)
    Else
        BindTrigger(EVS_ExitDoors_kpa_82_0, TRIGGER_WALL_PRESS_A, COLLIDER_deiliett, 1, 0)
    EndIf
    Call(MakeMarkerEntity, $SavePoint_1)
    Return
    End
};
