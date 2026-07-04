#include "kpa_134.h"
#include "entity.h"

EvtScript N(EVS_BreakBlock_Brick) = {
    IfEq(GF_KPA134_BlueSwitch, true)
        Return
    EndIf
    Call(DisablePlayerInput, true)
    Set(LVar5, -224)
    Call(MakeLerp, 355, 370, 4, EASING_QUADRATIC_OUT)
    Loop(0)
        Call(UpdateLerp)
        Call(SetEntityPosition, MV_SwitchEntityID, LVar5, LVar0, 0)
        Wait(1)
        Sub(LVar5, 2)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Call(MakeLerp, LVar0, 240, 16, EASING_QUADRATIC_IN)
    Loop(0)
        Call(UpdateLerp)
        Call(SetEntityPosition, MV_SwitchEntityID, LVar5, LVar0, 0)
        Wait(1)
        Sub(LVar5, 2)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Call(DisablePlayerInput, false)
    Return
    End
};

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
    Set(GF_KPA134_UnlockedDoor, true)
    Call(GetEntityPosition, MV_EntityID_Padlock, LVar0, LVar1, LVar2)
    Call(PlaySoundAt, SOUND_USE_KEY, SOUND_SPACE_DEFAULT, LVar0, LVar1, LVar2)
    Call(SetEntityUsed, MV_EntityID_Padlock)
    Set(LVar1, 0)
    Wait(5)
    Call(CloseChoicePopup)
    Unbind
    BindTrigger(Ref(N(EVS_ExitDoors_kpa_130_0)), TRIGGER_WALL_PRESS_A, COLLIDER_nno, 1, 0)
    Return
    End
};

EvtScript N(EVS_MakeEntities) = {
    IfEq(GF_KPA134_UnlockedDoor, false)
        Call(MakeEntity, Ref(Entity_Padlock), 743, 10, 115, 270, MAKE_ENTITY_END)
        Set(MV_EntityID_Padlock, LVar0)
        BindPadlock(Ref(N(EVS_UnlockPrompt_Door)), TRIGGER_WALL_PRESS_A, EVT_ENTITY_INDEX(0), Ref(N(KeyList_BowsersCastle)), 0, 1)
    Else
        BindTrigger(Ref(N(EVS_ExitDoors_kpa_130_0)), TRIGGER_WALL_PRESS_A, COLLIDER_nno, 1, 0)
    EndIf
    IfEq(GF_KPA134_BlueSwitch, false)
        Call(MakeEntity, Ref(Entity_BlueSwitch), -224, 355, -25, 0, MAKE_ENTITY_END)
        Call(AssignSwitchFlag, EVT_INDEX_OF_AREA_FLAG(AF_KPA134_HitWaterSwitch))
        Set(MV_SwitchEntityID, LVar0)
    EndIf
    Call(MakeEntity, Ref(Entity_BrickBlock), -224, 330, -25, 0, MAKE_ENTITY_END)
    Call(AssignScript, Ref(N(EVS_BreakBlock_Brick)))
    Call(MakeEntity, Ref(Entity_SimpleSpring), 475, 0, -20, 90, 60, MAKE_ENTITY_END)
    Call(MakeEntity, Ref(Entity_HiddenYellowBlock), 195, 300, -75, 0, ITEM_MAPLE_SYRUP, MAKE_ENTITY_END)
    Call(AssignBlockFlag, GF_KPA134_HiddenItem_MapleSyrup)
    Return
    End
};
