#include "isk_04.h"
#include "effects.h"

ITEM_LIST(KeyList, ITEM_RUINS_KEY);

BombTrigger BombPos_Wall = {
    .pos = $BombPos_Wall.pos,
    .diameter = 2.0f * $BombPos_Wall.radius,
};

EvtScript EVS_OnBlast_Wall = {
    PlayEffect(EFFECT_BOMBETTE_BREAKING, 0, $BombetteBreakingPos_1.pos.x, $BombetteBreakingPos_1.pos.y, $BombetteBreakingPos_1.pos.z, 10, 30)
    Loop(10)
        Call(EnableModel, MODEL_g262, true)
        Wait(1)
        Call(EnableModel, MODEL_g262, false)
        Wait(1)
    EndLoop
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilittne, COLLIDER_FLAGS_UPPER_MASK)
    Set(GF_ISK04_BombedWall, true)
    Unbind
    Return
    End
};

EvtScript EVS_UnlockDoorPrompt = {
    Call(ShowKeyChoicePopup)
    Switch(LVar0)
        CaseEq(ITEM_CHOICE_NONE)
            Call(ShowMessageAtScreenPos, MSG_Menus_00D8, 160, 40)
            Call(CloseChoicePopup)
            Return
        CaseEq(ITEM_CHOICE_CANCELED)
            Call(CloseChoicePopup)
            Return
    EndSwitch
    Call(PlaySoundAt, SOUND_USE_KEY, SOUND_SPACE_DEFAULT, 600, -330, 100)
    Call(RemoveKeyItemAt, LVar1)
    Set(GF_ISK04_UnlockedDoor, true)
    Call(SetEntityUsed, MV_RuinsLockEntityID)
    Set(LVar1, 0)
    Wait(5)
    Call(PlaySoundAtCollider, COLLIDER_deilittsw, SOUND_ISK_DOOR_OPEN, SOUND_SPACE_DEFAULT)
    Call(MakeLerp, 0, 65, 65, EASING_LINEAR)
    Label(10)
    Call(UpdateLerp)
    Call(TranslateGroup, MODEL_g304, 0, LVar0, 0)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(10)
    EndIf
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilittsw, COLLIDER_FLAGS_UPPER_MASK)
    Call(CloseChoicePopup)
    Unbind
    Return
    End
};

EvtScript EVS_SetupObstructions = {
    IfEq(GF_ISK04_BombedWall, false)
        BindTrigger(EVS_OnBlast_Wall, TRIGGER_POINT_BOMB, BombPos_Wall, 1, 0)
    Else
        Call(EnableModel, MODEL_g262, false)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilittne, COLLIDER_FLAGS_UPPER_MASK)
    EndIf
    IfEq(GF_ISK04_UnlockedDoor, false)
        Call(MakeTransformGroup, MODEL_g304)
        BindPadlock(EVS_UnlockDoorPrompt, TRIGGER_WALL_PRESS_A, EVT_ENTITY_INDEX(0), KeyList, 0, 1)
    Else
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilittsw, COLLIDER_FLAGS_UPPER_MASK)
        Call(EnableModel, MODEL_g304, false)
    EndIf
    Return
    End
};
