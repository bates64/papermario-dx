#include "isk_11.h"

extern EvtScript N(EVS_ItemPrompt_Socket1);
extern EvtScript N(EVS_ItemPrompt_Socket2);
extern EvtScript N(EVS_ItemPrompt_Socket3);
extern EvtScript N(EVS_ItemPrompt_Socket4);
extern EvtScript N(EVS_ItemPrompt_Socket5);

ITEM_LIST(N(ItemList_Artifacts), ITEM_LUNAR_STONE, ITEM_PYRAMID_STONE, ITEM_DIAMOND_STONE);

EvtScript N(EVS_SetupPuzzle) = {
    IfLt(GB_StoryProgress, STORY_CH2_SOLVED_ARTIFACT_PUZZLE)
        BindPadlock(Ref(N(EVS_ItemPrompt_Socket1)), TRIGGER_WALL_PRESS_A, COLLIDER_o2087, Ref(N(ItemList_Artifacts)), 0, 1)
        BindPadlock(Ref(N(EVS_ItemPrompt_Socket2)), TRIGGER_WALL_PRESS_A, COLLIDER_o2091, Ref(N(ItemList_Artifacts)), 0, 1)
        BindPadlock(Ref(N(EVS_ItemPrompt_Socket3)), TRIGGER_WALL_PRESS_A, COLLIDER_o2090, Ref(N(ItemList_Artifacts)), 0, 1)
        BindPadlock(Ref(N(EVS_ItemPrompt_Socket4)), TRIGGER_WALL_PRESS_A, COLLIDER_o2089, Ref(N(ItemList_Artifacts)), 0, 1)
        BindPadlock(Ref(N(EVS_ItemPrompt_Socket5)), TRIGGER_WALL_PRESS_A, COLLIDER_o2088, Ref(N(ItemList_Artifacts)), 0, 1)
    EndIf
    Set(MV_ItemEntity_Socket1, -1)
    Set(MV_ItemEntity_Socket2, -1)
    Set(MV_ItemEntity_Socket3, -1)
    Set(MV_ItemEntity_Socket4, -1)
    Set(MV_ItemEntity_Socket5, -1)
    IfNe(GB_ISK11_ItemSocket1, 0)
        Call(MakeItemEntity, GB_ISK11_ItemSocket1, -88, -508, 502, ITEM_SPAWN_MODE_DECORATION, 0)
        Set(MV_ItemEntity_Socket1, LVar0)
    EndIf
    IfNe(GB_ISK11_ItemSocket2, 0)
        Call(MakeItemEntity, GB_ISK11_ItemSocket2, -44, -508, 508, ITEM_SPAWN_MODE_DECORATION, 0)
        Set(MV_ItemEntity_Socket2, LVar0)
    EndIf
    IfNe(GB_ISK11_ItemSocket3, 0)
        Call(MakeItemEntity, GB_ISK11_ItemSocket3, 0, -508, 510, ITEM_SPAWN_MODE_DECORATION, 0)
        Set(MV_ItemEntity_Socket3, LVar0)
    EndIf
    IfNe(GB_ISK11_ItemSocket4, 0)
        Call(MakeItemEntity, GB_ISK11_ItemSocket4, 44, -508, 508, ITEM_SPAWN_MODE_DECORATION, 0)
        Set(MV_ItemEntity_Socket4, LVar0)
    EndIf
    IfNe(GB_ISK11_ItemSocket5, 0)
        Call(MakeItemEntity, GB_ISK11_ItemSocket5, 88, -508, 502, ITEM_SPAWN_MODE_DECORATION, 0)
        Set(MV_ItemEntity_Socket5, LVar0)
    EndIf
    Return
    End
};

EvtScript N(EVS_ItemPrompt_Socket1) = {
    IfGe(GB_StoryProgress, STORY_CH2_SOLVED_ARTIFACT_PUZZLE)
        Unbind
        Return
    EndIf
    SetGroup(EVT_GROUP_NEVER_PAUSE)
    Call(SetTimeFreezeMode, TIME_FREEZE_PARTIAL)
    IfNe(GB_ISK11_ItemSocket1, 0)
        Call(DisablePlayerInput, true)
        Call(GetItemName, GB_ISK11_ItemSocket1, LVar0)
        Call(SetMessageText, LVar0, 0)
        Call(ShowMessageAtScreenPos, MSG_Menus_ISK11_TakeItemPrompt, 160, 40)
        Call(ShowChoice, MSG_Choice_000D)
        Call(CloseMessage)
        IfEq(LVar0, 0)
            Call(PlaySoundAtCollider, COLLIDER_o2087, SOUND_ISK_PLACE_IN_SOCKET, SOUND_SPACE_DEFAULT)
            Call(AddItem, GB_ISK11_ItemSocket1, EVT_IGNORE_ARG)
            Set(LVar0, GB_ISK11_ItemSocket1)
            Set(GB_ISK11_ItemSocket1, 0)
            Call(RemoveItemEntity, MV_ItemEntity_Socket1)
            Set(MV_ItemEntity_Socket1, -1)
            Call(ShowGotItem, LVar0, false, ITEM_PICKUP_FLAG_NO_SOUND)
        EndIf
        Call(DisablePlayerInput, false)
        Call(SetTimeFreezeMode, TIME_FREEZE_NONE)
        Return
    EndIf
    Call(ShowKeyChoicePopup)
    Set(LVar2, LVar0)
    Switch(LVar2)
        CaseEq(ITEM_CHOICE_NONE)
            Call(ShowMessageAtScreenPos, MSG_Menus_Inspect_ChompStatue, 160, 40)
            Call(CloseChoicePopup)
            Call(SetTimeFreezeMode, TIME_FREEZE_NONE)
            Return
        CaseEq(ITEM_CHOICE_CANCELED)
            Call(CloseChoicePopup)
            Call(SetTimeFreezeMode, TIME_FREEZE_NONE)
            Return
    EndSwitch
    Set(GB_ISK11_ItemSocket1, LVar2)
    Call(RemoveKeyItemAt, LVar1)
    Call(MakeItemEntity, GB_ISK11_ItemSocket1, -88, -508, 502, ITEM_SPAWN_MODE_DECORATION, 0)
    Set(MV_ItemEntity_Socket1, LVar0)
    Call(CloseChoicePopup)
    Call(PlaySoundAtCollider, COLLIDER_o2087, SOUND_ISK_PLACE_IN_SOCKET, SOUND_SPACE_DEFAULT)
    Call(SetTimeFreezeMode, TIME_FREEZE_NONE)
    Return
    End
};

EvtScript N(EVS_ItemPrompt_Socket2) = {
    IfGe(GB_StoryProgress, STORY_CH2_SOLVED_ARTIFACT_PUZZLE)
        Unbind
        Return
    EndIf
    SetGroup(EVT_GROUP_NEVER_PAUSE)
    Call(SetTimeFreezeMode, TIME_FREEZE_PARTIAL)
    IfNe(GB_ISK11_ItemSocket2, 0)
        Call(DisablePlayerInput, true)
        Call(GetItemName, GB_ISK11_ItemSocket2, LVar0)
        Call(SetMessageText, LVar0, 0)
        Call(ShowMessageAtScreenPos, MSG_Menus_ISK11_TakeItemPrompt, 160, 40)
        Call(ShowChoice, MSG_Choice_000D)
        Call(CloseMessage)
        IfEq(LVar0, 0)
            Call(PlaySoundAtCollider, COLLIDER_o2091, SOUND_ISK_PLACE_IN_SOCKET, SOUND_SPACE_DEFAULT)
            Call(AddItem, GB_ISK11_ItemSocket2, EVT_IGNORE_ARG)
            Set(LVar0, GB_ISK11_ItemSocket2)
            Set(GB_ISK11_ItemSocket2, 0)
            Call(RemoveItemEntity, MV_ItemEntity_Socket2)
            Set(MV_ItemEntity_Socket2, -1)
            Call(ShowGotItem, LVar0, false, ITEM_PICKUP_FLAG_NO_SOUND)
        EndIf
        Call(DisablePlayerInput, false)
        Call(SetTimeFreezeMode, TIME_FREEZE_NONE)
        Return
    EndIf
    Call(ShowKeyChoicePopup)
    Set(LVar2, LVar0)
    Switch(LVar2)
        CaseEq(ITEM_CHOICE_NONE)
            Call(ShowMessageAtScreenPos, MSG_Menus_Inspect_ChompStatue, 160, 40)
            Call(CloseChoicePopup)
            Call(SetTimeFreezeMode, TIME_FREEZE_NONE)
            Return
        CaseEq(ITEM_CHOICE_CANCELED)
            Call(CloseChoicePopup)
            Call(SetTimeFreezeMode, TIME_FREEZE_NONE)
            Return
    EndSwitch
    Set(GB_ISK11_ItemSocket2, LVar2)
    Call(RemoveKeyItemAt, LVar1)
    Call(MakeItemEntity, GB_ISK11_ItemSocket2, -44, -508, 508, ITEM_SPAWN_MODE_DECORATION, 0)
    Set(MV_ItemEntity_Socket2, LVar0)
    Call(CloseChoicePopup)
    Call(SetTimeFreezeMode, TIME_FREEZE_NONE)
    Call(PlaySoundAtCollider, COLLIDER_o2091, SOUND_ISK_PLACE_IN_SOCKET, SOUND_SPACE_DEFAULT)
    Return
    End
};

EvtScript N(EVS_ItemPrompt_Socket3) = {
    IfGe(GB_StoryProgress, STORY_CH2_SOLVED_ARTIFACT_PUZZLE)
        Unbind
        Return
    EndIf
    SetGroup(EVT_GROUP_NEVER_PAUSE)
    Call(SetTimeFreezeMode, TIME_FREEZE_PARTIAL)
    IfNe(GB_ISK11_ItemSocket3, 0)
        Call(DisablePlayerInput, true)
        Call(GetItemName, GB_ISK11_ItemSocket3, LVar0)
        Call(SetMessageText, LVar0, 0)
        Call(ShowMessageAtScreenPos, MSG_Menus_ISK11_TakeItemPrompt, 160, 40)
        Call(ShowChoice, MSG_Choice_000D)
        Call(CloseMessage)
        IfEq(LVar0, 0)
            Call(PlaySoundAtCollider, COLLIDER_o2090, SOUND_ISK_PLACE_IN_SOCKET, SOUND_SPACE_DEFAULT)
            Call(AddItem, GB_ISK11_ItemSocket3, EVT_IGNORE_ARG)
            Set(LVar0, GB_ISK11_ItemSocket3)
            Set(GB_ISK11_ItemSocket3, 0)
            Call(RemoveItemEntity, MV_ItemEntity_Socket3)
            Set(MV_ItemEntity_Socket3, -1)
            Call(ShowGotItem, LVar0, false, ITEM_PICKUP_FLAG_NO_SOUND)
        EndIf
        Call(DisablePlayerInput, false)
        Call(SetTimeFreezeMode, TIME_FREEZE_NONE)
        Return
    EndIf
    Call(ShowKeyChoicePopup)
    Set(LVar2, LVar0)
    Switch(LVar2)
        CaseEq(ITEM_CHOICE_NONE)
            Call(ShowMessageAtScreenPos, MSG_Menus_Inspect_ChompStatue, 160, 40)
            Call(CloseChoicePopup)
            Call(SetTimeFreezeMode, TIME_FREEZE_NONE)
            Return
        CaseEq(ITEM_CHOICE_CANCELED)
            Call(CloseChoicePopup)
            Call(SetTimeFreezeMode, TIME_FREEZE_NONE)
            Return
    EndSwitch
    Set(GB_ISK11_ItemSocket3, LVar2)
    Call(RemoveKeyItemAt, LVar1)
    Call(MakeItemEntity, GB_ISK11_ItemSocket3, 0, -508, 510, ITEM_SPAWN_MODE_DECORATION, 0)
    Set(MV_ItemEntity_Socket3, LVar0)
    Call(CloseChoicePopup)
    Call(SetTimeFreezeMode, TIME_FREEZE_NONE)
    Call(PlaySoundAtCollider, COLLIDER_o2090, SOUND_ISK_PLACE_IN_SOCKET, SOUND_SPACE_DEFAULT)
    Return
    End
};

EvtScript N(EVS_ItemPrompt_Socket4) = {
    IfGe(GB_StoryProgress, STORY_CH2_SOLVED_ARTIFACT_PUZZLE)
        Unbind
        Return
    EndIf
    SetGroup(EVT_GROUP_NEVER_PAUSE)
    Call(SetTimeFreezeMode, TIME_FREEZE_PARTIAL)
    IfNe(GB_ISK11_ItemSocket4, 0)
        Call(DisablePlayerInput, true)
        Call(GetItemName, GB_ISK11_ItemSocket4, LVar0)
        Call(SetMessageText, LVar0, 0)
        Call(ShowMessageAtScreenPos, MSG_Menus_ISK11_TakeItemPrompt, 160, 40)
        Call(ShowChoice, MSG_Choice_000D)
        Call(CloseMessage)
        IfEq(LVar0, 0)
            Call(PlaySoundAtCollider, COLLIDER_o2089, SOUND_ISK_PLACE_IN_SOCKET, SOUND_SPACE_DEFAULT)
            Call(AddItem, GB_ISK11_ItemSocket4, EVT_IGNORE_ARG)
            Set(LVar0, GB_ISK11_ItemSocket4)
            Set(GB_ISK11_ItemSocket4, 0)
            Call(RemoveItemEntity, MV_ItemEntity_Socket4)
            Set(MV_ItemEntity_Socket4, -1)
            Call(ShowGotItem, LVar0, false, ITEM_PICKUP_FLAG_NO_SOUND)
        EndIf
        Call(DisablePlayerInput, false)
        Call(SetTimeFreezeMode, TIME_FREEZE_NONE)
        Return
    EndIf
    Call(ShowKeyChoicePopup)
    Set(LVar2, LVar0)
    Switch(LVar2)
        CaseEq(ITEM_CHOICE_NONE)
            Call(ShowMessageAtScreenPos, MSG_Menus_Inspect_ChompStatue, 160, 40)
            Call(CloseChoicePopup)
            Call(SetTimeFreezeMode, TIME_FREEZE_NONE)
            Return
        CaseEq(ITEM_CHOICE_CANCELED)
            Call(CloseChoicePopup)
            Call(SetTimeFreezeMode, TIME_FREEZE_NONE)
            Return
    EndSwitch
    Set(GB_ISK11_ItemSocket4, LVar2)
    Call(RemoveKeyItemAt, LVar1)
    Call(MakeItemEntity, GB_ISK11_ItemSocket4, 44, -508, 508, ITEM_SPAWN_MODE_DECORATION, 0)
    Set(MV_ItemEntity_Socket4, LVar0)
    Call(CloseChoicePopup)
    Call(SetTimeFreezeMode, TIME_FREEZE_NONE)
    Call(PlaySoundAtCollider, COLLIDER_o2089, SOUND_ISK_PLACE_IN_SOCKET, SOUND_SPACE_DEFAULT)
    Return
    End
};

EvtScript N(EVS_ItemPrompt_Socket5) = {
    IfGe(GB_StoryProgress, STORY_CH2_SOLVED_ARTIFACT_PUZZLE)
        Unbind
        Return
    EndIf
    SetGroup(EVT_GROUP_NEVER_PAUSE)
    Call(SetTimeFreezeMode, TIME_FREEZE_PARTIAL)
    IfNe(GB_ISK11_ItemSocket5, 0)
        Call(DisablePlayerInput, true)
        Call(GetItemName, GB_ISK11_ItemSocket5, LVar0)
        Call(SetMessageText, LVar0, 0)
        Call(ShowMessageAtScreenPos, MSG_Menus_ISK11_TakeItemPrompt, 160, 40)
        Call(ShowChoice, MSG_Choice_000D)
        Call(CloseMessage)
        IfEq(LVar0, 0)
            Call(PlaySoundAtCollider, COLLIDER_o2088, SOUND_ISK_PLACE_IN_SOCKET, SOUND_SPACE_DEFAULT)
            Call(AddItem, GB_ISK11_ItemSocket5, EVT_IGNORE_ARG)
            Set(LVar0, GB_ISK11_ItemSocket5)
            Set(GB_ISK11_ItemSocket5, 0)
            Call(RemoveItemEntity, MV_ItemEntity_Socket5)
            Set(MV_ItemEntity_Socket5, -1)
            Call(ShowGotItem, LVar0, false, ITEM_PICKUP_FLAG_NO_SOUND)
        EndIf
        Call(DisablePlayerInput, false)
        Call(SetTimeFreezeMode, TIME_FREEZE_NONE)
        Return
    EndIf
    Call(ShowKeyChoicePopup)
    Set(LVar2, LVar0)
    Switch(LVar2)
        CaseEq(ITEM_CHOICE_NONE)
            Call(ShowMessageAtScreenPos, MSG_Menus_Inspect_ChompStatue, 160, 40)
            Call(CloseChoicePopup)
            Call(SetTimeFreezeMode, TIME_FREEZE_NONE)
            Return
        CaseEq(ITEM_CHOICE_CANCELED)
            Call(CloseChoicePopup)
            Call(SetTimeFreezeMode, TIME_FREEZE_NONE)
            Return
    EndSwitch
    Set(GB_ISK11_ItemSocket5, LVar2)
    Call(RemoveKeyItemAt, LVar1)
    Call(MakeItemEntity, GB_ISK11_ItemSocket5, 88, -508, 502, ITEM_SPAWN_MODE_DECORATION, 0)
    Set(MV_ItemEntity_Socket5, LVar0)
    Call(CloseChoicePopup)
    Call(SetTimeFreezeMode, TIME_FREEZE_NONE)
    Call(PlaySoundAtCollider, COLLIDER_o2088, SOUND_ISK_PLACE_IN_SOCKET, SOUND_SPACE_DEFAULT)
    Return
    End
};
