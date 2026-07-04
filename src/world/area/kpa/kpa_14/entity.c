
#include "kpa_14.h"
#include "entity.h"

ITEM_LIST(N(KeyList_BowsersCastle), ITEM_BOWSER_CASTLE_KEY);

EvtScript N(EVS_UnlockPrompt_Door) = {
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
    BindTrigger(Ref(N(EVS_ExitDoor_kpa_01_0)), TRIGGER_WALL_PRESS_A, COLLIDER_deilitte, 1, 0)
    Return
    End
};

EvtScript N(EVS_MakeEntities) = {
    IfEq(GF_KPA14_UnlockedDoor, false)
        Call(MakeEntity, Ref(Entity_Padlock), 1995, 40, -162, 270, MAKE_ENTITY_END)
        Set(MV_EntityID_Padlock, LVar0)
        BindPadlock(Ref(N(EVS_UnlockPrompt_Door)), TRIGGER_WALL_PRESS_A, EVT_ENTITY_INDEX(0), Ref(N(KeyList_BowsersCastle)), 0, 1)
    Else
        BindTrigger(Ref(N(EVS_ExitDoor_kpa_01_0)), TRIGGER_WALL_PRESS_A, COLLIDER_deilitte, 1, 0)
    EndIf
    Call(MakeItemEntity, ITEM_MYSTERY, 350, 30, -150, ITEM_SPAWN_MODE_FIXED_NEVER_VANISH, GF_KPA14_Item_Mystery)
    Call(MakeItemEntity, ITEM_THUNDER_RAGE, 800, 30, -150, ITEM_SPAWN_MODE_FIXED_NEVER_VANISH, GF_KPA14_Item_ThunderRage)
    Return
    End
};
