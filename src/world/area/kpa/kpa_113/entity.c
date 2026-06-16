#include "kpa_113.h"
#include "entity.h"

ITEM_LIST(N(KeyList_BowsersCastle), ITEM_BOWSER_CASTLE_KEY);

EvtScript N(EVS_ExitDoors_kpa_82_0) = EVT_EXIT_DOUBLE_DOOR(kpa_113_ENTRY_1, "kpa_82", kpa_82_ENTRY_0, COLLIDER_deiliett, MODEL_o136, MODEL_o137);

EvtScript N(EVS_UnlockPrompt_LockedDoor) = {
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
    BindTrigger(Ref(N(EVS_ExitDoors_kpa_82_0)), TRIGGER_WALL_PRESS_A, COLLIDER_deiliett, 1, 0)
    Return
    End
};

EvtScript N(EVS_MakeEntities) = {
    IfEq(GF_KPA113_UnlockedDoor, false)
        Call(MakeEntity, Ref(Entity_Padlock), 418, 10, 100, 280, MAKE_ENTITY_END)
        Set(MV_EntityID_Padlock, LVar0)
        BindPadlock(Ref(N(EVS_UnlockPrompt_LockedDoor)), TRIGGER_WALL_PRESS_A, EVT_ENTITY_INDEX(0), Ref(N(KeyList_BowsersCastle)), 0, 1)
    Else
        BindTrigger(Ref(N(EVS_ExitDoors_kpa_82_0)), TRIGGER_WALL_PRESS_A, COLLIDER_deiliett, 1, 0)
    EndIf
    Call(MakeEntity, Ref(Entity_SavePoint), 375, 60, 50, 0, MAKE_ENTITY_END)
    Return
    End
};
