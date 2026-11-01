#include "kpa_133.h"
#include "entity.h"
#include "effects.h"
#include "sprite/player.h"

extern EvtScript EVS_TriggerSwitch;
extern EvtScript EVS_SetupHiddenSpring;

API_CALLABLE(SetSpringRotation) {
    Bytecode* args = script->ptrReadPos;
    Entity* entity = get_entity_by_index(evt_get_variable(nullptr, MV_SpringEntityID));

    entity->rot.x = evt_get_variable(script, *args++);
    entity->rot.y = evt_get_variable(script, *args++);
    entity->rot.z = evt_get_variable(script, *args++);
    return ApiStatus_DONE2;
}

API_CALLABLE(SetSpringPosition) {
    Bytecode* args = script->ptrReadPos;
    Entity* entity = get_entity_by_index(evt_get_variable(nullptr, MV_SpringEntityID));

    entity->pos.x = evt_get_variable(script, *args++);
    entity->pos.y = evt_get_variable(script, *args++);
    entity->pos.z = evt_get_variable(script, *args++);
    return ApiStatus_DONE2;
}

EvtScript EVS_MakeEntities = {
    IfEq(GF_KPA133_BlueSwitch, false)
        Call(MakeMarkerEntity, $BlueSwitch_1)
        Call(AssignScript, EVS_TriggerSwitch)
    EndIf
    IfEq(GF_KPA133_BlueSwitch, true)
        Call(MakeMarkerEntity, $SimpleSpring_1)
    Else
        Call(MakeMarkerEntity, $SimpleSpring_2)
        Set(MV_SpringEntityID, LVar0)
        Call(SetSpringRotation, -90, 0, 0)
        Exec(EVS_SetupHiddenSpring)
    EndIf
    Call(MakeMarkerEntity, $Item_BowserCastleKey_1)
    Return
    End
};

EvtScript EVS_SetupHiddenSpring = {
    Loop(0)
        Wait(1)
        IfEq(MV_RevealHiddenSpring, true)
            BreakLoop
        EndIf
    EndLoop
    Call(DisablePlayerInput, true)
    Set(GF_KPA133_BlueSwitch, true)
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    IfGe(LVar0, 115)
        IfLe(LVar0, 180)
            Set(LVar3, LVar0)
            IfLt(LVar0, 150)
                Add(LVar3, -40)
                Set(LVar4, 90)
            Else
                Add(LVar3, 40)
                Set(LVar4, 270)
            EndIf
            Thread
                Wait(2)
                Call(InterpPlayerYaw, LVar4, 0)
                Wait(2)
                Call(SetPlayerJumpscale, 2.0)
                Call(SetPlayerAnimation, ANIM_Mario1_Flail)
                Call(PlayerJump1, LVar3, LVar1, LVar2, 10)
                Call(SetPlayerAnimation, ANIM_Mario1_Idle)
                Wait(5)
            EndThread
        EndIf
    EndIf
    Thread
        Call(MakeLerp, 0, 80, 15, EASING_QUADRATIC_IN)
        Loop(0)
            Call(UpdateLerp)
            Call(RotateModel, MODEL_kakusitobira, LVar0, 1, 0, 0)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        PlayEffect(EFFECT_LANDING_DUST, 1, $LandingDustPos_1.pos.x, $LandingDustPos_1.pos.y, $LandingDustPos_1.pos.z, 0)
        PlayEffect(EFFECT_LANDING_DUST, 1, $LandingDustPos_2.pos.x, $LandingDustPos_2.pos.y, $LandingDustPos_2.pos.z, 0)
        PlayEffect(EFFECT_LANDING_DUST, 1, $LandingDustPos_3.pos.x, $LandingDustPos_3.pos.y, $LandingDustPos_3.pos.z, 0)
        PlayEffect(EFFECT_LANDING_DUST, 1, $LandingDustPos_4.pos.x, $LandingDustPos_4.pos.y, $LandingDustPos_4.pos.z, 0)
        PlayEffect(EFFECT_LANDING_DUST, 1, $LandingDustPos_5.pos.x, $LandingDustPos_5.pos.y, $LandingDustPos_5.pos.z, 0)
        PlayEffect(EFFECT_LANDING_DUST, 1, $LandingDustPos_6.pos.x, $LandingDustPos_6.pos.y, $LandingDustPos_6.pos.z, 0)
        Wait(20)
        Call(EnableModel, MODEL_kakusitobira, false)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_123, COLLIDER_FLAGS_UPPER_MASK)
    EndThread
    Thread
        Wait(18)
        Call(PlaySoundAtNpc, NPC_Dummy, SOUND_KPA_DROP_WALL, SOUND_SPACE_DEFAULT)
    EndThread
    Thread
        Call(MakeLerp, -90, 0, 15, EASING_QUADRATIC_IN)
        Loop(0)
            Call(UpdateLerp)
            Call(SetSpringRotation, LVar0, 0, 0)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
    EndThread
    Thread
        Loop(23)
            Call(GetNpcPos, NPC_Dummy, LVar0, LVar1, LVar2)
            Call(SetSpringPosition, LVar0, LVar1, LVar2)
            Wait(1)
        EndLoop
        Call(SetNpcPos, NPC_Dummy, NPC_DISPOSE_LOCATION)
    EndThread
    Wait(3)
    Call(SetNpcPos, NPC_Dummy, 150, 150, -105)
    Call(SetNpcJumpscale, NPC_Dummy, 1.0)
    Call(NpcJump0, NPC_Dummy, 150, 115, 0, 17)
    Call(GetNpcPos, NPC_Dummy, LVar0, LVar1, LVar2)
    Wait(20)
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript EVS_TriggerSwitch = {
    Set(MV_RevealHiddenSpring, true)
    Return
    End
};
