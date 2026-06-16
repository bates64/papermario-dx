#include "kpa_95.h"
#include "entity.h"

ITEM_LIST(N(KeyList_PrisonCell), ITEM_PRISON_KEY);

EvtScript N(EVS_UnlockPrompt_PrisonCell) = {
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
    Set(GF_KPA95_UnlockedDoor, true)
    Call(GetEntityPosition, MV_EntityID_Padlock, LVar0, LVar1, LVar2)
    Call(PlaySoundAt, SOUND_USE_KEY, SOUND_SPACE_DEFAULT, LVar0, LVar1, LVar2)
    Call(SetEntityUsed, MV_EntityID_Padlock)
    Set(LVar1, 0)
    Wait(5)
    Call(CloseChoicePopup)
    BindTrigger(Ref(N(EVS_OpenCellDoor)), TRIGGER_WALL_PRESS_A, COLLIDER_deilittn, 1, 0)
    Unbind
    Return
    End
};

EvtScript N(EVS_MakeEntities) = {
    IfEq(GF_KPA95_UnlockedDoor, false)
        Call(MakeEntity, Ref(Entity_Padlock), -5, 10, 13, 0, MAKE_ENTITY_END)
        Set(MV_EntityID_Padlock, LVar0)
        BindPadlock(Ref(N(EVS_UnlockPrompt_PrisonCell)), TRIGGER_WALL_PRESS_A, EVT_ENTITY_INDEX(0), Ref(N(KeyList_PrisonCell)), 0, 1)
    Else
        BindTrigger(Ref(N(EVS_OpenCellDoor)), TRIGGER_WALL_PRESS_A, COLLIDER_deilittn, 1, 0)
    EndIf
    IfEq(GF_KPA95_Defeated_Guard, true)
        Call(MakeItemEntity, ITEM_PRISON_KEY, -70, 0, 55, ITEM_SPAWN_MODE_FIXED_NEVER_VANISH, GF_KPA95_Item_PrisonKey1)
    EndIf
    Return
    End
};
