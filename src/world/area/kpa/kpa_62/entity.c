#include "kpa_62.h"
#include "entity.h"

ITEM_LIST(N(KeyList_FrontDoor), ITEM_BOWSER_CASTLE_KEY);

EvtScript N(EVS_UnlockPrompt_FrontDoor) = {
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
    Set(GF_KPA62_UnlockedFrontDoor, true)
    Call(GetEntityPosition, MV_EntityID_Padlock, LVar0, LVar1, LVar2)
    Call(PlaySoundAt, SOUND_USE_KEY, SOUND_SPACE_DEFAULT, LVar0, LVar1, LVar2)
    Call(SetEntityUsed, MV_EntityID_Padlock)
    Set(LVar1, 0)
    Wait(5)
    Call(CloseChoicePopup)
    Unbind
    BindTrigger(Ref(N(EVS_ExitDoors_kpa_70_0)), TRIGGER_WALL_PRESS_A, COLLIDER_deilittn, 1, 0)
    Return
    End
};

EvtScript N(EVS_MakeEntities) = {
    IfEq(GF_KPA62_UnlockedFrontDoor, false)
        Call(MakeEntity, Ref(Entity_Padlock), -200, 10, -207, 0, MAKE_ENTITY_END)
        Set(MV_EntityID_Padlock, LVar0)
        BindPadlock(Ref(N(EVS_UnlockPrompt_FrontDoor)), TRIGGER_WALL_PRESS_A, EVT_ENTITY_INDEX(0), Ref(N(KeyList_FrontDoor)), 0, 1)
    Else
        BindTrigger(Ref(N(EVS_ExitDoors_kpa_70_0)), TRIGGER_WALL_PRESS_A, COLLIDER_deilittn, 1, 0)
    EndIf
    Call(MakeEntity, Ref(Entity_RedBlock), -532, 145, -59, 0, ITEM_DEEP_FOCUS_C, MAKE_ENTITY_END)
    Call(AssignBlockFlag, GF_KPA62_BadgeBlock_DeepFocus3)
    Return
    End
};
