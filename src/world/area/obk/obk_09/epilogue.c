#include "obk_09.h"
#include "world/area/omo/omo_03.h"

API_CALLABLE(SetInvitationLetterScale) {
    get_item_entity(script->varTable[0])->scale = 0.6f;
    return ApiStatus_DONE2;
}

EvtScript EVS_Scene_Epilogue = {
    Call(DisablePlayerInput, true)
    Call(DisablePlayerPhysics, true)
    Call(SetPlayerPos, NPC_DISPOSE_LOCATION)
    Call(SetCamType, CAM_DEFAULT, CAM_CONTROL_FIXED_POS_AND_ORIENTATION, true)
    Call(SetCamSpeed, CAM_DEFAULT, 90.0)
    Call(SetCamPitch, CAM_DEFAULT, 15.0, -8.0)
    Call(SetCamDistance, CAM_DEFAULT, 450)
    Call(SetCamPosA, CAM_DEFAULT, -280, 234)
    Call(SetCamPosB, CAM_DEFAULT, -135, 105)
    Call(SetCamPosC, CAM_DEFAULT, 0, 0)
    Call(PanToTarget, CAM_DEFAULT, 0, true)
    Call(SetNpcAnimation, NPC_Bootler, ANIM_Bootler_Walk)
    Call(NpcMoveTo, NPC_Bootler, -159, 158, 50)
    Call(SetNpcAnimation, NPC_Bootler, ANIM_Bootler_Idle)
    Wait(15)
    Call(SetNpcAnimation, NPC_Bootler, ANIM_Bootler_Talk)
    Wait(15)
    Call(SetNpcAnimation, NPC_Bootler, ANIM_Bootler_Idle)
    Wait(15)
    Thread
        Call(DropResizableItemEntity, ITEM_LETTER_TO_KOLORADO, NPC_DISPOSE_LOCATION, ITEM_SPAWN_MODE_DECORATION, 0)
        Call(SetInvitationLetterScale)
        Loop(35)
            Call(GetNpcPos, NPC_Bootler, LVar1, LVar2, LVar3)
            Add(LVar1, -16)
            Add(LVar2, 4)
            Add(LVar3, -10)
            Call(SetItemPos, LVar0, LVar1, LVar2, LVar3)
            Wait(1)
        EndLoop
        Wait(35)
        Call(RemoveItemEntity, LVar0)
    EndThread
    Wait(10)
    Call(NpcMoveTo, NPC_Bootler, -172, 143, 20)
    Call(SetNpcJumpscale, NPC_Bootler, 0)
    Wait(10)
    Call(NpcJump1, NPC_Bootler, -159, 10, 158, 20)
    Wait(10)
    Call(SetNpcAnimation, NPC_Bow, ANIM_WorldBow_Read)
    Wait(40)
    Call(SetNpcAnimation, NPC_Bow, ANIM_WorldBow_Idle)
    Wait(10)
    Call(SetNpcAnimation, NPC_Bow, ANIM_WorldBow_CelebrateSlow)
    Wait(30)
    Call(FadeOutMusic, 0, 1000)
    Call(GotoMap, $omo_03.Epilogue)
    Wait(100)
    Return
    End
};
