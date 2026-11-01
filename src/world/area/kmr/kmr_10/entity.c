#include "kmr_10.h"
#include "entity.h"
#include "animation_script.h"

extern AnimScript Entity_SimpleSpring_AnimLaunch;

#include "world/common/entity/Chest.inc.c"

API_CALLABLE(PlaySpringReboundAnimation) {
    Bytecode* args = script->ptrReadPos;
    Entity* entity = get_entity_by_index(evt_get_variable(script, *args++));

    if (entity == nullptr) {
        return ApiStatus_BLOCK;
    }

    play_model_animation(entity->virtualModelIndex, Entity_SimpleSpring_AnimLaunch);
    return ApiStatus_DONE2;
}

API_CALLABLE(SetSpringPosition) {
    Bytecode* args = script->ptrReadPos;
    s32 entityIndex = evt_get_variable(script, *args++);
    s32 x = evt_get_variable(script, *args++);
    s32 y = evt_get_variable(script, *args++);
    s32 z = evt_get_variable(script, *args++);
    Entity* entity = get_entity_by_index(entityIndex);

    entity->pos.x = x;
    entity->pos.y = y;
    entity->pos.z = z;
    return ApiStatus_DONE2;
}

EvtScript EVS_OnShakeTree1 = {
    Wait(15)
    IfEq(GF_KMR10_KnockedSpringOutOfTree, false)
        Set(GF_KMR10_KnockedSpringOutOfTree, true)
        Call(DisablePlayerInput, true)
        Call(SetNpcPos, NPC_Dummy, 370, 115, -20)
        Thread
            Loop(17)
                Call(GetNpcPos, NPC_Dummy, LVar0, LVar1, LVar2)
                Call(SetSpringPosition, MV_EntityID_Spring, LVar0, LVar1, LVar2)
                Wait(1)
            EndLoop
            Call(SetNpcPos, NPC_Dummy, NPC_DISPOSE_LOCATION)
        EndThread
        Call(SetNpcJumpscale, NPC_Dummy, 0.8)
        Call(NpcJump0, NPC_Dummy, 370, 10, 20, 15)
        Call(PlaySoundAt, SOUND_OBJECT_LAND, SOUND_SPACE_DEFAULT, 370, 10, 20)
        Call(PlaySoundAt, SOUND_SPRING, SOUND_SPACE_DEFAULT, 370, 10, 20)
        Call(PlaySpringReboundAnimation, MV_EntityID_Spring)
        IfEq(GF_KMR10_UnreadFlagForSpring, false)
            Add(GF_KMR10_UnreadFlagForSpring, 1)
        EndIf
        Call(DisablePlayerInput, false)
    EndIf
    Return
    End
};

EvtScript EVS_Spring_TetherCameraToPlayer = {
    Label(0)
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
        Call(SetCamTarget, CAM_DEFAULT, LVar0, LVar1, LVar2)
        Wait(1)
        Goto(0)
    Return
    End
};

EvtScript EVS_UseSpring = {
    Call(DisablePlayerInput, true)
    Call(DisablePlayerPhysics, true)
    Call(SetPlayerActionState, ACTION_STATE_LAUNCH)
    ExecGetTID(EVS_Spring_TetherCameraToPlayer, LVarA)
    Call(SetPlayerJumpscale, 1.2)
    Call(PlayerJump, 456, 142, 99, 30)
    KillThread(LVarA)
    Call(SetPlayerActionState, ACTION_STATE_IDLE)
    Call(DisablePlayerPhysics, false)
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript EVS_OpenChest_HammerThrow = EVT_OPEN_CHEST(ITEM_HAMMER_THROW, GF_KMR10_Chest_HammerThrow);

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $YellowBlock_SleepySheep_1)
    Call(MakeMarkerEntity, $Chest_HammerThrow)
    IfEq(GF_KMR10_KnockedSpringOutOfTree, false)
        Call(MakeMarkerEntity, $ScriptSpring_1)
        Set(MV_EntityID_Spring, LVar0)
    Else
        Call(MakeMarkerEntity, $ScriptSpring_2)
    EndIf
    Return
    End
};
