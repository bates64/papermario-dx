#include "dgb_01.h"
#include "entity.h"

EvtScript N(EVS_UnlockPrompt_Door) = {
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
    Call(RemoveItem, ITEM_TUBBA_CASTLE_KEY)
    Call(CloseChoicePopup)
    Set(GF_DGB01_UnlockedEastWing, true)
    Call(GetEntityPosition, MV_EntityID_Padlock, LVar0, LVar1, LVar2)
    Call(PlaySoundAt, SOUND_USE_KEY, SOUND_SPACE_DEFAULT, LVar0, LVar1, LVar2)
    Call(SetEntityUsed, MV_EntityID_Padlock)
    ResumeGroup(EVT_GROUP_FLAG_INTERACT)
    Unbind
    Return
    End
};

EvtScript N(EVS_OpenLockedDoor) = {
    BindTrigger(Ref(N(EVS_ExitDoors_dgb_08_0)), TRIGGER_WALL_PRESS_A, COLLIDER_deilittse, 1, 0)
    Return
    End
};

EvtScript N(EVS_MakeEntities) = {
    IfEq(GF_DGB01_UnlockedEastWing, false)
        Call(MakeEntity, Ref(Entity_Padlock), 490, 8, 0, -80, MAKE_ENTITY_END)
        Call(AssignScript, Ref(N(EVS_OpenLockedDoor)))
        Set(MV_EntityID_Padlock, LVar0)
    EndIf
    Return
    End
};
