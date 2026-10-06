#include "common.h"
#include "battle/script_module.h"
#include "script_api/battle.h"
#include "effects.h"

#include "battle/common/move/HammerSupport.inc.c"

API_CALLABLE(MakeGreenImpactFX) {
    Bytecode* args = script->ptrReadPos;
    s32 x = evt_get_variable(script, *args++);
    s32 y = evt_get_variable(script, *args++);
    s32 z = evt_get_variable(script, *args++);
    b32 success = script->varTable[10]; // value from GetPlayerActionQuality

    if (!success) {
        fx_green_impact(true, x + 30, y + 25, z, 45.0f);
    } else {
        fx_green_impact(false, x + 30, y + 25, z, 45.0f);
    }

    return ApiStatus_DONE2;
}

extern EvtScript EVS_UseMove_Impl;

EvtScript EVS_UseMove = {
    Call(ShowActionHud, true)
    Call(SetDamageSource, DMG_SRC_D_DOWN_POUND)
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
    Switch(LVar1)
        CaseEq(0)
            Set(LVarD, 50) // duration
            Set(LVarE, BASIC_HAMMER_DMG_BAD)
            Set(LVarF, BASIC_HAMMER_DMG_GOOD)
            ExecWait(EVS_UseMove_Impl)
        CaseEq(1)
            Set(LVarD, 50) // duration
            Set(LVarE, SUPER_HAMMER_DMG_BAD)
            Set(LVarF, SUPER_HAMMER_DMG_GOOD)
            ExecWait(EVS_UseMove_Impl)
        CaseEq(2)
            Set(LVarD, 50) // duration
            Set(LVarE, ULTRA_HAMMER_DMG_BAD)
            Set(LVarF, ULTRA_HAMMER_DMG_GOOD)
            ExecWait(EVS_UseMove_Impl)
    EndSwitch
    Return
    End
};


EvtScript EVS_UseMove_Impl = {
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
    Switch(LVar1)
        CaseEq(0)
            ExecWait(EVS_UseBasicHammer)
        CaseEq(1)
            ExecWait(EVS_UseSuperHammer)
        CaseEq(2)
            ExecWait(EVS_UseUltraHammer)
    EndSwitch
    Call(PlayerTestEnemy, LVar0, DAMAGE_TYPE_SMASH | DAMAGE_TYPE_IGNORE_DEFENSE, 25, 0, LVar9, 16)
    Call(GetPlayerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(false)
            Call(GetMenuSelection, LVar0, LVar1, LVar2)
            Switch(LVar1)
                CaseEq(0)
                    Call(StartRumble, BTL_RUMBLE_PLAYER_LIGHT)
                    Thread
                        Call(ShakeCam, CAM_BATTLE, 0, 10, Float(1.3))
                    EndThread
                CaseEq(1)
                    Call(StartRumble, BTL_RUMBLE_PLAYER_HEAVY)
                    Thread
                        Call(ShakeCam, CAM_BATTLE, 0, 10, Float(1.6))
                    EndThread
                CaseEq(2)
                    Call(StartRumble, BTL_RUMBLE_PLAYER_EXTREME)
                    Thread
                        Call(ShakeCam, CAM_BATTLE, 0, 10, Float(1.9))
                    EndThread
            EndSwitch
        CaseDefault
            Call(GetMenuSelection, LVar0, LVar1, LVar2)
            Switch(LVar1)
                CaseEq(0)
                    Call(StartRumble, BTL_RUMBLE_PLAYER_LIGHT)
                    Thread
                        Call(ShakeCam, CAM_BATTLE, 0, 2, Float(1.3))
                    EndThread
                CaseEq(1)
                    Call(StartRumble, BTL_RUMBLE_PLAYER_HEAVY)
                    Thread
                        Call(ShakeCam, CAM_BATTLE, 0, 2, Float(1.6))
                    EndThread
                CaseEq(2)
                    Call(StartRumble, BTL_RUMBLE_PLAYER_EXTREME)
                    Thread
                        Call(ShakeCam, CAM_BATTLE, 0, 2, Float(1.9))
                    EndThread
            EndSwitch
    EndSwitch
    Call(GetPlayerActionQuality, LVar0)
    IfGt(LVar0, false)
        Call(UseBattleCamPreset, BTL_CAM_PLAYER_HAMMER_STRIKE)
        Call(MoveBattleCamOver, 5)
    Else
        Call(UseBattleCamPreset, BTL_CAM_PLAYER_HAMMER_STRIKE)
        Call(MoveBattleCamOver, 50)
    EndIf
    Call(GetMenuSelection, LVar0, LVar1, LVar2)
    Switch(LVar1)
        CaseEq(0)
            Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_D_DOWN_HIT_1)
        CaseEq(1)
            Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_D_DOWN_HIT_2)
        CaseEq(2)
            Call(PlaySoundAtActor, ACTOR_PLAYER, SOUND_D_DOWN_HIT_3)
    EndSwitch
    Call(PlayerTestEnemy, LVar0, DAMAGE_TYPE_SMASH, 25, 0, 0, 16)
    IfEq(LVar0, HIT_RESULT_MISS)
        ExecWait(EVS_HammerSupport_ReturnHome_SmashMiss)
        Return
    EndIf
    Call(GetPlayerActionQuality, LVarA)
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Call(MakeGreenImpactFX, LVar0, LVar1, LVar2)
    Call(GetPlayerActionQuality, LVar0)
    Switch(LVar0)
        CaseGt(false)
            Call(PlayerDamageEnemy, LVar0, DAMAGE_TYPE_SMASH | DAMAGE_TYPE_IGNORE_DEFENSE, SUPPRESS_EVENTS_HAMMER, 0, LVarF, BS_FLAGS1_TRIGGER_EVENTS | BS_FLAGS1_INCLUDE_POWER_UPS | BS_FLAGS1_NICE_HIT)
        CaseDefault
            Call(PlayerDamageEnemy, LVar0, DAMAGE_TYPE_SMASH | DAMAGE_TYPE_IGNORE_DEFENSE, SUPPRESS_EVENTS_HAMMER, 0, LVarE, BS_FLAGS1_INCLUDE_POWER_UPS | BS_FLAGS1_TRIGGER_EVENTS)
    EndSwitch
    Switch(LVar0)
        CaseOrEq(HIT_RESULT_NICE)
        CaseOrEq(HIT_RESULT_NICE_NO_DAMAGE)
            ExecWait(EVS_HammerSupport_ReturnHome_SmashSuccess)
        EndCaseGroup
        CaseOrEq(HIT_RESULT_HIT)
        CaseOrEq(HIT_RESULT_NO_DAMAGE)
            ExecWait(EVS_HammerSupport_ReturnHome_SmashMiss)
        EndCaseGroup
    EndSwitch
    Return
    End
};

OVL_DEF_BATTLE_SCRIPT(BATTLE_SCRIPT_KIND_MOVE,
    &EVS_UseMove,
);
