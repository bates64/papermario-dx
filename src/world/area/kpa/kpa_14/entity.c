
#include "kpa_14.h"
#include "entity.h"

ITEM_LIST(KeyList_BowsersCastle, ITEM_BOWSER_CASTLE_KEY);

EvtScript EVS_UnlockPrompt_Door = {
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
    Set(GF_KPA14_UnlockedDoor, true)
    Call(GetEntityPosition, MV_EntityID_Padlock, LVar0, LVar1, LVar2)
    Call(PlaySoundAt, SOUND_USE_KEY, SOUND_SPACE_DEFAULT, LVar0, LVar1, LVar2)
    Call(SetEntityUsed, MV_EntityID_Padlock)
    Set(LVar1, 0)
    Wait(5)
    Call(CloseChoicePopup)
    Unbind
    BindTrigger(EVS_ExitDoor_kpa_01_0, TRIGGER_WALL_PRESS_A, COLLIDER_deilitte, 1, 0)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    IfEq(GF_KPA14_UnlockedDoor, false)
        Call(MakeMarkerEntity, $Padlock_1)
        Set(MV_EntityID_Padlock, LVar0)
        BindPadlock(EVS_UnlockPrompt_Door, TRIGGER_WALL_PRESS_A, EVT_ENTITY_INDEX(0), KeyList_BowsersCastle, 0, 1)
    Else
        BindTrigger(EVS_ExitDoor_kpa_01_0, TRIGGER_WALL_PRESS_A, COLLIDER_deilitte, 1, 0)
    EndIf
    Call(MakeMarkerEntity, $Item_Mystery_1)
    Call(MakeMarkerEntity, $Item_ThunderRage_1)
    Return
    End
};
