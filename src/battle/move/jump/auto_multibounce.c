#include "common.h"
#include "script_api/battle.h"
#include "battle/action_cmd/jump.h"
#include "sprite/player.h"

#define NAMESPACE battle_move_auto_multibounce

#include "battle/common/move/JumpSupport.inc.c"

extern EvtScript N(EVS_UseMove_Normal);
extern EvtScript N(EVS_UseMove_Super);
extern EvtScript N(EVS_UseMove_Ultra);

EvtScript N(EVS_UseMove) = {
    Call(ShowActionHud, TRUE)
    Call(SetBattleFlagBits, BS_FLAGS1_AUTO_SUCCEED_ACTION, TRUE)
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
    Switch(LVar1)
        CaseEq(0)
            ExecWait(N(EVS_UseMove_Normal))
        CaseEq(1)
            ExecWait(N(EVS_UseMove_Super))
        CaseEq(2)
            ExecWait(N(EVS_UseMove_Ultra))
    EndSwitch
    Return
    End
};

EvtScript N(EVS_UseMove_Normal) = {
    ExecWait(N(EVS_JumpSupport_ApproachAndJump))
    Call(PlayerTestEnemy, LVar0, DAMAGE_TYPE_JUMP, 0, 0, 1, 0)
    IfEq(LVar0, HIT_RESULT_MISS)
        ExecWait(N(EVS_JumpSupport_Miss))
        Return
    EndIf
    Set(LFlag0, FALSE)
    Call(GetTargetListLength, LVar0)
    IfEq(LVar0, 1)
        Set(LFlag0, TRUE)
    EndIf
    Wait(1)
    Call(GetPlayerActionSuccess, LVar0)
    Switch(LVar0)
        CaseGt(FALSE)
            IfEq(LFlag0, FALSE)
                Call(SetActorSounds, ACTOR_PLAYER, ACTOR_SOUND_HURT, SOUND_ACTOR_JUMPED_1, SOUND_NONE)
                Call(PlayerDamageEnemy, LVar0, DAMAGE_TYPE_JUMP | DAMAGE_TYPE_MULTI_BOUNCE | DAMAGE_TYPE_MULTIPLE_POPUPS, 0, 0, 1, BS_FLAGS1_TRIGGER_EVENTS | BS_FLAGS1_INCLUDE_POWER_UPS | BS_FLAGS1_NICE_HIT)
            Else
                Call(SetActorSounds, ACTOR_PLAYER, ACTOR_SOUND_HURT, SOUND_ACTOR_JUMPED_1, SOUND_NONE)
                Call(PlayerDamageEnemy, LVar0, DAMAGE_TYPE_JUMP | DAMAGE_TYPE_MULTI_BOUNCE | DAMAGE_TYPE_MULTIPLE_POPUPS, 0, 0, 1, BS_FLAGS1_TRIGGER_EVENTS | BS_FLAGS1_INCLUDE_POWER_UPS | BS_FLAGS1_NICE_HIT)
            EndIf
        CaseDefault
            Call(SetActorSounds, ACTOR_PLAYER, ACTOR_SOUND_HURT, SOUND_ACTOR_JUMPED_1, SOUND_NONE)
            Call(PlayerDamageEnemy, LVar0, DAMAGE_TYPE_JUMP | DAMAGE_TYPE_MULTI_BOUNCE | DAMAGE_TYPE_MULTIPLE_POPUPS, 0, 0, 1, BS_FLAGS1_INCLUDE_POWER_UPS | BS_FLAGS1_TRIGGER_EVENTS)
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_JUMP_COMBO_1)
    Switch(LVar0)
        CaseOrEq(HIT_RESULT_HIT)
        CaseOrEq(HIT_RESULT_NO_DAMAGE)
            IfEq(LFlag0, TRUE)
                ExecWait(N(EVS_JumpSupport_Rebound))
                Return
            EndIf
            ExecWait(N(EVS_JumpSupport_NoFollowUp))
            Return
        EndCaseGroup
        CaseOrEq(HIT_RESULT_NICE)
        CaseOrEq(HIT_RESULT_NICE_NO_DAMAGE)
            IfEq(LFlag0, TRUE)
                ExecWait(N(EVS_JumpSupport_Rebound))
                Return
            EndIf
        EndCaseGroup
    EndSwitch
    Call(GetActionResult, LVarE)
    Add(LVarF, 1)
    Set(LFlag0, FALSE)
    Label(10)
        Call(UseBattleCamPreset, BTL_CAM_PLAYER_MULTIBOUNCE)
        Call(GetTargetListLength, LVar0)
        Sub(LVar0, 1)
        IfEq(LVarF, LVar0)
            Set(LFlag0, TRUE)
        EndIf
        Call(CloseActionCommandInfo)
        Call(LoadActionCommand, ACTION_COMMAND_JUMP)
        Call(action_command_jump_init)
        IfEq(LFlag0, TRUE)
            Call(ShowActionHud, FALSE)
        EndIf
        Call(ChooseNextTarget, ITER_NEXT, LVar0)
        Call(SetGoalToTarget, ACTOR_PLAYER)
        ExecWait(N(EVS_JumpSupport_CalcJumpTime))
        Add(LVarA, 5)
        Call(action_command_jump_start, LVarA, 3)
        Call(SetGoalToTarget, ACTOR_PLAYER)
        Call(SetJumpAnimations, ACTOR_PLAYER, 0, ANIM_Mario1_Jump, ANIM_Mario1_Fall, ANIM_Mario1_SpinFall)
        IfEq(LVarF, 1)
            Call(PlayerBasicJumpToGoal, LVarA, PLAYER_BASIC_JUMP_3)
        Else
            Call(PlayerBasicJumpToGoal, LVarA, PLAYER_BASIC_JUMP_4)
        EndIf
        Call(PlayerTestEnemy, LVar0, DAMAGE_TYPE_JUMP, 0, 0, 1, 0)
        IfEq(LVar0, HIT_RESULT_MISS)
            ExecWait(N(EVS_JumpSupport_Miss))
            Return
        EndIf
        Wait(1)
        Call(GetPlayerActionSuccess, LVar0)
        Switch(LVar0)
            CaseGt(FALSE)
                IfEq(LFlag0, FALSE)
                    Call(SetActorSounds, ACTOR_PLAYER, ACTOR_SOUND_HURT, SOUND_ACTOR_JUMPED_1, SOUND_NONE)
                    Call(PlayerDamageEnemy, LVar0, DAMAGE_TYPE_JUMP | DAMAGE_TYPE_MULTI_BOUNCE | DAMAGE_TYPE_MULTIPLE_POPUPS, 0, 0, 1, BS_FLAGS1_TRIGGER_EVENTS | BS_FLAGS1_INCLUDE_POWER_UPS | BS_FLAGS1_NICE_HIT)
                Else
                    Call(SetActorSounds, ACTOR_PLAYER, ACTOR_SOUND_HURT, SOUND_ACTOR_JUMPED_1, SOUND_NONE)
                    Call(PlayerDamageEnemy, LVar0, DAMAGE_TYPE_JUMP | DAMAGE_TYPE_MULTI_BOUNCE | DAMAGE_TYPE_MULTIPLE_POPUPS, 0, 0, 1, BS_FLAGS1_INCLUDE_POWER_UPS | BS_FLAGS1_TRIGGER_EVENTS | BS_FLAGS1_NICE_HIT | BS_FLAGS1_NO_RATING)
                EndIf
            CaseDefault
                IfEq(LFlag0, FALSE)
                    Call(SetActorSounds, ACTOR_PLAYER, ACTOR_SOUND_HURT, SOUND_ACTOR_JUMPED_1, SOUND_NONE)
                    Call(PlayerDamageEnemy, LVar0, DAMAGE_TYPE_JUMP | DAMAGE_TYPE_MULTI_BOUNCE | DAMAGE_TYPE_MULTIPLE_POPUPS, 0, 0, 1, BS_FLAGS1_INCLUDE_POWER_UPS | BS_FLAGS1_TRIGGER_EVENTS)
                Else
                    Call(SetActorSounds, ACTOR_PLAYER, ACTOR_SOUND_HURT, SOUND_ACTOR_JUMPED_1, SOUND_NONE)
                    Call(PlayerDamageEnemy, LVar0, DAMAGE_TYPE_JUMP | DAMAGE_TYPE_MULTI_BOUNCE | DAMAGE_TYPE_MULTIPLE_POPUPS, 0, 0, 1, BS_FLAGS1_INCLUDE_POWER_UPS | BS_FLAGS1_TRIGGER_EVENTS | BS_FLAGS1_NICE_HIT | BS_FLAGS1_NO_RATING)
                EndIf
        EndSwitch
        Switch(LVarF)
            CaseEq(0)
                Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_JUMP_COMBO_1)
            CaseEq(1)
                Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_JUMP_COMBO_2)
            CaseEq(2)
                Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_JUMP_COMBO_3)
            CaseEq(3)
                Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_JUMP_COMBO_4)
            CaseDefault
                Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_JUMP_COMBO_4)
        EndSwitch
        Call(SetActionResult, LVarE)
        Call(GetPlayerActionSuccess, LVar0)
        Switch(LVar0)
            CaseOrEq(FALSE)
            CaseOrEq(2)
                IfEq(LFlag0, TRUE)
                    ExecWait(N(EVS_JumpSupport_Rebound))
                    Return
                EndIf
                ExecWait(N(EVS_JumpSupport_NoFollowUp))
                Return
            EndCaseGroup
            CaseOrEq(TRUE)
            CaseOrEq(3)
                IfEq(LFlag0, TRUE)
                    ExecWait(N(EVS_JumpSupport_Rebound))
                    Return
                EndIf
            EndCaseGroup
        EndSwitch
        Add(LVarF, 1)
        Call(GetTargetListLength, LVar0)
        IfGe(LVarF, LVar0)
            ExecWait(N(EVS_JumpSupport_WeakRebound))
            Return
        EndIf
        Goto(10)
    Return
    End
};

EvtScript N(EVS_UseMove_Super) = {
    ExecWait(N(EVS_JumpSupport_ApproachAndJump))
    Call(PlayerTestEnemy, LVar0, DAMAGE_TYPE_JUMP, 0, 0, 1, 0)
    IfEq(LVar0, HIT_RESULT_MISS)
        ExecWait(N(EVS_JumpSupport_Miss))
        Return
    EndIf
    Set(LFlag0, FALSE)
    Call(GetTargetListLength, LVar0)
    IfEq(LVar0, 1)
        Set(LFlag0, TRUE)
    EndIf
    Wait(1)
    Call(GetPlayerActionSuccess, LVar0)
    Switch(LVar0)
        CaseGt(FALSE)
            IfEq(LFlag0, FALSE)
                Call(SetActorSounds, ACTOR_PLAYER, ACTOR_SOUND_HURT, SOUND_ACTOR_JUMPED_2, SOUND_NONE)
                Call(PlayerDamageEnemy, LVar0, DAMAGE_TYPE_JUMP | DAMAGE_TYPE_MULTI_BOUNCE | DAMAGE_TYPE_MULTIPLE_POPUPS, 0, 0, 2, BS_FLAGS1_TRIGGER_EVENTS | BS_FLAGS1_INCLUDE_POWER_UPS | BS_FLAGS1_NICE_HIT)
            Else
                Call(SetActorSounds, ACTOR_PLAYER, ACTOR_SOUND_HURT, SOUND_ACTOR_JUMPED_2, SOUND_NONE)
                Call(PlayerDamageEnemy, LVar0, DAMAGE_TYPE_JUMP | DAMAGE_TYPE_MULTI_BOUNCE | DAMAGE_TYPE_MULTIPLE_POPUPS, 0, 0, 2, BS_FLAGS1_TRIGGER_EVENTS | BS_FLAGS1_INCLUDE_POWER_UPS | BS_FLAGS1_NICE_HIT)
            EndIf
        CaseDefault
            Call(SetActorSounds, ACTOR_PLAYER, ACTOR_SOUND_HURT, SOUND_ACTOR_JUMPED_2, SOUND_NONE)
            Call(PlayerDamageEnemy, LVar0, DAMAGE_TYPE_JUMP | DAMAGE_TYPE_MULTI_BOUNCE | DAMAGE_TYPE_MULTIPLE_POPUPS, 0, 0, 2, BS_FLAGS1_INCLUDE_POWER_UPS | BS_FLAGS1_TRIGGER_EVENTS)
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_JUMP_COMBO_1)
    Switch(LVar0)
        CaseOrEq(HIT_RESULT_HIT)
        CaseOrEq(HIT_RESULT_NO_DAMAGE)
            IfEq(LFlag0, TRUE)
                ExecWait(N(EVS_JumpSupport_Rebound))
                Return
            EndIf
            ExecWait(N(EVS_JumpSupport_NoFollowUp))
            Return
        EndCaseGroup
        CaseOrEq(HIT_RESULT_NICE)
        CaseOrEq(HIT_RESULT_NICE_NO_DAMAGE)
            IfEq(LFlag0, TRUE)
                ExecWait(N(EVS_JumpSupport_Rebound))
                Return
            EndIf
        EndCaseGroup
    EndSwitch
    Call(GetActionResult, LVarE)
    Set(LFlag0, FALSE)
    Set(LVarF, 0)
    Add(LVarF, 1)
    Label(10)
        Call(GetTargetListLength, LVar0)
        Sub(LVar0, 1)
        IfEq(LVarF, LVar0)
            Set(LFlag0, TRUE)
        EndIf
        Call(CloseActionCommandInfo)
        Call(LoadActionCommand, ACTION_COMMAND_JUMP)
        Call(action_command_jump_init)
        IfEq(LFlag0, TRUE)
            Call(ShowActionHud, FALSE)
        EndIf
        Call(UseBattleCamPreset, BTL_CAM_PLAYER_MULTIBOUNCE)
        Call(action_command_jump_start, 37, 3)
        Call(ChooseNextTarget, ITER_NEXT, LVar0)
        Call(SetGoalToTarget, ACTOR_PLAYER)
        Call(SetGoalToTarget, ACTOR_PLAYER)
        Call(SetJumpAnimations, ACTOR_PLAYER, 0, ANIM_Mario1_Jump, ANIM_Mario1_Sit, ANIM_Mario1_SpinJump)
        Call(EnablePlayerBlur, ACTOR_BLUR_ENABLE)
        IfEq(LVarF, 1)
            Call(PlayerSuperJumpToGoal, 20, PLAYER_SUPER_JUMP_3)
            Wait(7)
            Call(PlayerSuperJumpToGoal, 3, PLAYER_SUPER_JUMP_6)
        Else
            Call(PlayerSuperJumpToGoal, 20, PLAYER_SUPER_JUMP_4)
            Wait(7)
            Call(PlayerSuperJumpToGoal, 3, PLAYER_SUPER_JUMP_5)
        EndIf
        Call(EnablePlayerBlur, ACTOR_BLUR_DISABLE)
        Call(PlayerTestEnemy, LVar0, DAMAGE_TYPE_JUMP, 0, 0, 1, 0)
        IfEq(LVar0, HIT_RESULT_MISS)
            ExecWait(N(EVS_JumpSupport_Miss))
            Return
        EndIf
        Wait(1)
        Call(GetPlayerActionSuccess, LVar0)
        Switch(LVar0)
            CaseGt(FALSE)
                IfEq(LFlag0, FALSE)
                    Call(SetActorSounds, ACTOR_PLAYER, ACTOR_SOUND_HURT, SOUND_ACTOR_JUMPED_2, SOUND_NONE)
                    Call(PlayerDamageEnemy, LVar0, DAMAGE_TYPE_JUMP | DAMAGE_TYPE_MULTI_BOUNCE | DAMAGE_TYPE_MULTIPLE_POPUPS, 0, 0, 2, BS_FLAGS1_TRIGGER_EVENTS | BS_FLAGS1_INCLUDE_POWER_UPS | BS_FLAGS1_NICE_HIT)
                Else
                    Call(SetActorSounds, ACTOR_PLAYER, ACTOR_SOUND_HURT, SOUND_ACTOR_JUMPED_2, SOUND_NONE)
                    Call(PlayerDamageEnemy, LVar0, DAMAGE_TYPE_JUMP | DAMAGE_TYPE_MULTI_BOUNCE | DAMAGE_TYPE_MULTIPLE_POPUPS, 0, 0, 2, BS_FLAGS1_INCLUDE_POWER_UPS | BS_FLAGS1_TRIGGER_EVENTS | BS_FLAGS1_NICE_HIT | BS_FLAGS1_NO_RATING)
                EndIf
            CaseDefault
                IfEq(LFlag0, FALSE)
                    Call(SetActorSounds, ACTOR_PLAYER, ACTOR_SOUND_HURT, SOUND_ACTOR_JUMPED_2, SOUND_NONE)
                    Call(PlayerDamageEnemy, LVar0, DAMAGE_TYPE_JUMP | DAMAGE_TYPE_MULTI_BOUNCE | DAMAGE_TYPE_MULTIPLE_POPUPS, 0, 0, 2, BS_FLAGS1_INCLUDE_POWER_UPS | BS_FLAGS1_TRIGGER_EVENTS)
                Else
                    Call(SetActorSounds, ACTOR_PLAYER, ACTOR_SOUND_HURT, SOUND_ACTOR_JUMPED_2, SOUND_NONE)
                    Call(PlayerDamageEnemy, LVar0, DAMAGE_TYPE_JUMP | DAMAGE_TYPE_MULTI_BOUNCE | DAMAGE_TYPE_MULTIPLE_POPUPS, 0, 0, 2, BS_FLAGS1_INCLUDE_POWER_UPS | BS_FLAGS1_TRIGGER_EVENTS | BS_FLAGS1_NICE_HIT | BS_FLAGS1_NO_RATING)
                EndIf
        EndSwitch
        Switch(LVarF)
            CaseEq(0)
                Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_JUMP_COMBO_1)
            CaseEq(1)
                Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_JUMP_COMBO_2)
            CaseEq(2)
                Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_JUMP_COMBO_3)
            CaseEq(3)
                Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_JUMP_COMBO_4)
            CaseDefault
                Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_JUMP_COMBO_4)
        EndSwitch
        Call(SetActionResult, LVarE)
        Call(GetPlayerActionSuccess, LVar0)
        Switch(LVar0)
            CaseOrEq(FALSE)
            CaseOrEq(2)
                IfEq(LFlag0, TRUE)
                    ExecWait(N(EVS_JumpSupport_Rebound))
                    Return
                EndIf
                ExecWait(N(EVS_JumpSupport_NoFollowUp))
                Return
            EndCaseGroup
            CaseOrEq(TRUE)
            CaseOrEq(3)
                IfEq(LFlag0, TRUE)
                    ExecWait(N(EVS_JumpSupport_Rebound))
                    Return
                EndIf
            EndCaseGroup
        EndSwitch
        Add(LVarF, 1)
        Call(GetTargetListLength, LVar0)
        IfGe(LVarF, LVar0)
            ExecWait(N(EVS_JumpSupport_NoFollowUp))
            Return
        EndIf
        Goto(10)
    Return
    End
};

EvtScript N(EVS_UseMove_Ultra) = {
    ExecWait(N(EVS_JumpSupport_ApproachAndJump))
    Call(PlayerTestEnemy, LVar0, DAMAGE_TYPE_JUMP, 0, 0, 1, 0)
    IfEq(LVar0, HIT_RESULT_MISS)
        ExecWait(N(EVS_JumpSupport_Miss))
        Return
    EndIf
    Set(LFlag0, FALSE)
    Call(GetTargetListLength, LVar0)
    IfEq(LVar0, 1)
        Set(LFlag0, TRUE)
    EndIf
    Wait(1)
    Call(GetPlayerActionSuccess, LVar0)
    Switch(LVar0)
        CaseGt(FALSE)
            IfEq(LFlag0, FALSE)
                Call(SetActorSounds, ACTOR_PLAYER, ACTOR_SOUND_HURT, SOUND_ACTOR_JUMPED_3, SOUND_NONE)
                Call(PlayerDamageEnemy, LVar0, DAMAGE_TYPE_JUMP | DAMAGE_TYPE_MULTI_BOUNCE | DAMAGE_TYPE_MULTIPLE_POPUPS, 0, 0, 3, BS_FLAGS1_TRIGGER_EVENTS | BS_FLAGS1_INCLUDE_POWER_UPS | BS_FLAGS1_NICE_HIT)
            Else
                Call(SetActorSounds, ACTOR_PLAYER, ACTOR_SOUND_HURT, SOUND_ACTOR_JUMPED_3, SOUND_NONE)
                Call(PlayerDamageEnemy, LVar0, DAMAGE_TYPE_JUMP | DAMAGE_TYPE_MULTI_BOUNCE | DAMAGE_TYPE_MULTIPLE_POPUPS, 0, 0, 3, BS_FLAGS1_TRIGGER_EVENTS | BS_FLAGS1_INCLUDE_POWER_UPS | BS_FLAGS1_NICE_HIT)
            EndIf
        CaseDefault
            Call(SetActorSounds, ACTOR_PLAYER, ACTOR_SOUND_HURT, SOUND_ACTOR_JUMPED_3, SOUND_NONE)
            Call(PlayerDamageEnemy, LVar0, DAMAGE_TYPE_JUMP | DAMAGE_TYPE_MULTI_BOUNCE | DAMAGE_TYPE_MULTIPLE_POPUPS, 0, 0, 3, BS_FLAGS1_INCLUDE_POWER_UPS | BS_FLAGS1_TRIGGER_EVENTS)
    EndSwitch
    Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_JUMP_COMBO_1)
    Switch(LVar0)
        CaseOrEq(HIT_RESULT_HIT)
        CaseOrEq(HIT_RESULT_NO_DAMAGE)
            IfEq(LFlag0, TRUE)
                ExecWait(N(EVS_JumpSupport_Rebound))
                Return
            EndIf
            ExecWait(N(EVS_JumpSupport_NoFollowUp))
            Return
        EndCaseGroup
        CaseOrEq(HIT_RESULT_NICE)
        CaseOrEq(HIT_RESULT_NICE_NO_DAMAGE)
            IfEq(LFlag0, TRUE)
                ExecWait(N(EVS_JumpSupport_Rebound))
                Return
            EndIf
        EndCaseGroup
    EndSwitch
    Call(GetActionResult, LVarE)
    Set(LFlag0, FALSE)
    Set(LVarF, 0)
    Add(LVarF, 1)
    Label(20)
        Call(GetTargetListLength, LVar0)
        Sub(LVar0, 1)
        IfEq(LVarF, LVar0)
            Set(LFlag0, TRUE)
        EndIf
        Call(CloseActionCommandInfo)
        Call(LoadActionCommand, ACTION_COMMAND_JUMP)
        Call(action_command_jump_init)
        IfEq(LFlag0, TRUE)
            Call(ShowActionHud, FALSE)
        EndIf
        Call(UseBattleCamPreset, BTL_CAM_PLAYER_MULTIBOUNCE)
        Call(action_command_jump_start, 25, 3)
        Call(ChooseNextTarget, ITER_NEXT, LVar0)
        Call(SetGoalToTarget, ACTOR_PLAYER)
        Call(SetJumpAnimations, ACTOR_PLAYER, 0, ANIM_Mario1_Jump, ANIM_Mario1_Jump, ANIM_Mario1_SpinFall)
        IfEq(LVarF, 1)
            Call(PlayerUltraJumpToGoal, 25, PLAYER_ULTRA_JUMP_2)
        Else
            Call(PlayerUltraJumpToGoal, 25, PLAYER_ULTRA_JUMP_4)
        EndIf
        Call(PlayerTestEnemy, LVar0, DAMAGE_TYPE_JUMP, 0, 0, 1, 0)
        IfEq(LVar0, HIT_RESULT_MISS)
            ExecWait(N(EVS_JumpSupport_Miss))
            Return
        EndIf
        Wait(1)
        Call(GetPlayerActionSuccess, LVar0)
        Switch(LVar0)
            CaseGt(FALSE)
                IfEq(LFlag0, FALSE)
                    Call(SetActorSounds, ACTOR_PLAYER, ACTOR_SOUND_HURT, SOUND_ACTOR_JUMPED_3, SOUND_NONE)
                    Call(PlayerDamageEnemy, LVar0, DAMAGE_TYPE_JUMP | DAMAGE_TYPE_MULTI_BOUNCE | DAMAGE_TYPE_MULTIPLE_POPUPS, 0, 0, 3, BS_FLAGS1_TRIGGER_EVENTS | BS_FLAGS1_INCLUDE_POWER_UPS | BS_FLAGS1_NICE_HIT)
                Else
                    Call(SetActorSounds, ACTOR_PLAYER, ACTOR_SOUND_HURT, SOUND_ACTOR_JUMPED_3, SOUND_NONE)
                    Call(PlayerDamageEnemy, LVar0, DAMAGE_TYPE_JUMP | DAMAGE_TYPE_MULTI_BOUNCE | DAMAGE_TYPE_MULTIPLE_POPUPS, 0, 0, 3, BS_FLAGS1_INCLUDE_POWER_UPS | BS_FLAGS1_TRIGGER_EVENTS | BS_FLAGS1_NICE_HIT | BS_FLAGS1_NO_RATING)
                EndIf
            CaseDefault
                IfEq(LFlag0, FALSE)
                    Call(SetActorSounds, ACTOR_PLAYER, ACTOR_SOUND_HURT, SOUND_ACTOR_JUMPED_3, SOUND_NONE)
                    Call(PlayerDamageEnemy, LVar0, DAMAGE_TYPE_JUMP | DAMAGE_TYPE_MULTI_BOUNCE | DAMAGE_TYPE_MULTIPLE_POPUPS, 0, 0, 3, BS_FLAGS1_INCLUDE_POWER_UPS | BS_FLAGS1_TRIGGER_EVENTS)
                Else
                    Call(SetActorSounds, ACTOR_PLAYER, ACTOR_SOUND_HURT, SOUND_ACTOR_JUMPED_3, SOUND_NONE)
                    Call(PlayerDamageEnemy, LVar0, DAMAGE_TYPE_JUMP | DAMAGE_TYPE_MULTI_BOUNCE | DAMAGE_TYPE_MULTIPLE_POPUPS, 0, 0, 3, BS_FLAGS1_INCLUDE_POWER_UPS | BS_FLAGS1_TRIGGER_EVENTS | BS_FLAGS1_NICE_HIT | BS_FLAGS1_NO_RATING)
                EndIf
        EndSwitch
        Switch(LVarF)
            CaseEq(0)
                Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_JUMP_COMBO_1)
            CaseEq(1)
                Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_JUMP_COMBO_2)
            CaseEq(2)
                Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_JUMP_COMBO_3)
            CaseEq(3)
                Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_JUMP_COMBO_4)
            CaseDefault
                Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_JUMP_COMBO_4)
        EndSwitch
        Call(SetActionResult, LVarE)
        Call(GetPlayerActionSuccess, LVar0)
        Switch(LVar0)
            CaseOrEq(FALSE)
            CaseOrEq(2)
                IfEq(LFlag0, TRUE)
                    ExecWait(N(EVS_JumpSupport_Rebound))
                    Return
                EndIf
                ExecWait(N(EVS_JumpSupport_NoFollowUp))
                Return
            EndCaseGroup
            CaseOrEq(TRUE)
            CaseOrEq(3)
                IfEq(LFlag0, TRUE)
                    ExecWait(N(EVS_JumpSupport_Rebound))
                    Return
                EndIf
            EndCaseGroup
        EndSwitch
        Add(LVarF, 1)
        Call(GetTargetListLength, LVar0)
        IfGe(LVarF, LVar0)
            ExecWait(N(EVS_JumpSupport_NoFollowUp))
            Return
        EndIf
        Goto(20)
    Return
    End
};
