#include "common.h"
#include "battle/script_module.h"
#include "script_api/battle.h"

#include "battle/common/move/JumpSupport.inc.c"

extern EvtScript EVS_UseMove_Basic;
extern EvtScript EVS_UseMove_Super;
extern EvtScript EVS_UseMove_Ultra;

EvtScript EVS_UseMove = {
    Call(EnablePlayerBlur, ACTOR_BLUR_ENABLE)
    Call(ShowActionHud, true)
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
    Switch(LVar1)
        CaseEq(0)
            ExecWait(EVS_UseMove_Basic)
        CaseEq(1)
            ExecWait(EVS_UseMove_Super)
        CaseEq(2)
            ExecWait(EVS_UseMove_Ultra)
    EndSwitch
    Call(EnablePlayerBlur, ACTOR_BLUR_DISABLE)
    Return
    End
};

EvtScript EVS_PlayQuakeFX = {
    Call(StartRumble, BTL_RUMBLE_PLAYER_MAX)
    Thread
        Call(ShakeCam, CAM_BATTLE, 0, 2, Float(1.0))
        Call(ShakeCam, CAM_BATTLE, 0, 2, Float(3.0))
        Call(ShakeCam, CAM_BATTLE, 0, 2, Float(6.0))
        Call(ShakeCam, CAM_BATTLE, 0, 2, Float(5.0))
        Call(ShakeCam, CAM_BATTLE, 0, 2, Float(4.0))
        Call(ShakeCam, CAM_BATTLE, 0, 2, Float(3.0))
        Call(ShakeCam, CAM_BATTLE, 0, 2, Float(2.0))
        Call(ShakeCam, CAM_BATTLE, 0, 2, Float(1.0))
        Call(ShakeCam, CAM_BATTLE, 0, 2, Float(0.5))
        Call(ShakeCam, CAM_BATTLE, 0, 2, Float(0.2))
    EndThread
    Return
    End
};

EvtScript EVS_UseMove_Basic = {
    ExecWait(EVS_JumpSupport_ApproachAndJump)
    Call(PlayerTestEnemy, LVar0, DAMAGE_TYPE_JUMP, 0, 0, 1, 0)
    IfEq(LVar0, HIT_RESULT_MISS)
        ExecWait(EVS_JumpSupport_Miss)
        Return
    EndIf
    ExecWait(EVS_PlayQuakeFX)
    Wait(1)
    Call(GetPlayerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(false)
            Call(SetActorSounds, ACTOR_PLAYER, ACTOR_SOUND_HURT, SOUND_ACTOR_JUMPED_1, SOUND_NONE)
            Call(PlayerDamageEnemy, LVar0, DAMAGE_TYPE_JUMP, 0, 0, 6, BS_FLAGS1_INCLUDE_POWER_UPS | BS_FLAGS1_TRIGGER_EVENTS | BS_FLAGS1_NICE_HIT)
        CaseDefault
            Call(SetActorSounds, ACTOR_PLAYER, ACTOR_SOUND_HURT, SOUND_ACTOR_JUMPED_1, SOUND_NONE)
            Call(PlayerDamageEnemy, LVar0, DAMAGE_TYPE_JUMP, 0, 0, 5, BS_FLAGS1_INCLUDE_POWER_UPS | BS_FLAGS1_TRIGGER_EVENTS)
    EndSwitch
    Switch(LVar0)
        CaseGt(HIT_RESULT_HIT)
            ExecWait(EVS_JumpSupport_Rebound)
        CaseDefault
            ExecWait(EVS_JumpSupport_WeakRebound)
    EndSwitch
    Return
    End
};


EvtScript EVS_UseMove_Super = {
    ExecWait(EVS_JumpSupport_ApproachAndJump)
    Call(PlayerTestEnemy, LVar0, DAMAGE_TYPE_JUMP, 0, 0, 1, 0)
    IfEq(LVar0, HIT_RESULT_MISS)
        ExecWait(EVS_JumpSupport_Miss)
        Return
    EndIf
    ExecWait(EVS_PlayQuakeFX)
    Wait(1)
    Call(GetPlayerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(false)
            Call(SetActorSounds, ACTOR_PLAYER, ACTOR_SOUND_HURT, SOUND_ACTOR_JUMPED_2, SOUND_NONE)
            Call(PlayerDamageEnemy, LVar0, DAMAGE_TYPE_JUMP, 0, 0, 8, BS_FLAGS1_INCLUDE_POWER_UPS | BS_FLAGS1_TRIGGER_EVENTS | BS_FLAGS1_NICE_HIT)
        CaseDefault
            Call(SetActorSounds, ACTOR_PLAYER, ACTOR_SOUND_HURT, SOUND_ACTOR_JUMPED_2, SOUND_NONE)
            Call(PlayerDamageEnemy, LVar0, DAMAGE_TYPE_JUMP, 0, 0, 6, BS_FLAGS1_INCLUDE_POWER_UPS | BS_FLAGS1_TRIGGER_EVENTS)
    EndSwitch
    Switch(LVar0)
        CaseGt(HIT_RESULT_HIT)
            ExecWait(EVS_JumpSupport_Rebound)
        CaseDefault
            ExecWait(EVS_JumpSupport_WeakRebound)
    EndSwitch
    Return
    End
};

EvtScript EVS_UseMove_Ultra = {
    ExecWait(EVS_JumpSupport_ApproachAndJump)
    Call(PlayerTestEnemy, LVar0, DAMAGE_TYPE_JUMP, 0, 0, 1, 0)
    IfEq(LVar0, HIT_RESULT_MISS)
        ExecWait(EVS_JumpSupport_Miss)
        Return
    EndIf
    ExecWait(EVS_PlayQuakeFX)
    Wait(1)
    Call(GetPlayerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(false)
            Call(SetActorSounds, ACTOR_PLAYER, ACTOR_SOUND_HURT, SOUND_ACTOR_JUMPED_3, SOUND_NONE)
            Call(PlayerDamageEnemy, LVar0, DAMAGE_TYPE_JUMP, 0, 0, 10, BS_FLAGS1_INCLUDE_POWER_UPS | BS_FLAGS1_TRIGGER_EVENTS | BS_FLAGS1_NICE_HIT)
        CaseDefault
            Call(SetActorSounds, ACTOR_PLAYER, ACTOR_SOUND_HURT, SOUND_ACTOR_JUMPED_3, SOUND_NONE)
            Call(PlayerDamageEnemy, LVar0, DAMAGE_TYPE_JUMP, 0, 0, 7, BS_FLAGS1_INCLUDE_POWER_UPS | BS_FLAGS1_TRIGGER_EVENTS)
    EndSwitch
    Switch(LVar0)
        CaseGt(HIT_RESULT_HIT)
            ExecWait(EVS_JumpSupport_Rebound)
        CaseDefault
            ExecWait(EVS_JumpSupport_WeakRebound)
    EndSwitch
    Return
    End
};

OVL_DEF_BATTLE_SCRIPT(BATTLE_SCRIPT_KIND_MOVE,
    &EVS_UseMove,
);
