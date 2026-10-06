#include "common.h"
#include "battle/script_module.h"
#include "script_api/battle.h"
#include "sprite/player.h"

#include "battle/common/move/StarPowerSupport.inc.c"

API_CALLABLE(RestoreStarPower) {
    PlayerData* playerData = &gPlayerData;
    PlayerData* playerData2 = &gPlayerData;

    if (is_ability_active(ABILITY_DEEP_FOCUS)) {
        playerData->starPower += SP_PER_SEG * 4;
    }
    if (is_ability_active(ABILITY_SUPER_FOCUS)) {
        playerData->starPower += SP_PER_BAR;
    }

    playerData->starPower += SP_PER_SEG * 4;

    if (playerData2->starPower >= playerData2->maxStarPower * SP_PER_BAR) {
        playerData2->starPower = playerData2->maxStarPower * SP_PER_BAR;
    }

    return ApiStatus_DONE2;
}

EvtScript EVS_UsePower = {
    Call(UseBattleCamPreset, BTL_CAM_PLAYER_WISH)
    Wait(10)
    Call(SetAnimation, ACTOR_PLAYER, 0, ANIM_Peach2_SpreadArms)
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Add(LVar0, 16)
    Call(SetActorSpeed, ACTOR_PLAYER, Float(4.0))
    Call(SetGoalPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Call(PlayerRunToGoal, 0)
    Wait(8)
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Add(LVar1, 20)
    Call(SpawnStarSparkleFX, LVar0, LVar1, LVar2)
    Call(DarkenBackground)
    Wait(20)
    Call(SetAnimation, ACTOR_PLAYER, 0, ANIM_Peach3_Pray)
    Wait(10)
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Add(LVar1, 20)
    Call(SpawnWishSparkleFX, LVar0, LVar1, LVar2)
    Wait(30)
    Call(SetAnimation, ACTOR_PLAYER, 0, ANIM_Peach2_Curious)
    Call(RestoreStarPower)
    Wait(10)
    Call(LightenBackground)
    Wait(15)
    Call(SetGoalToHome, ACTOR_PLAYER)
    Call(SetActorSpeed, ACTOR_PLAYER, Float(8.0))
    Call(SetAnimation, ACTOR_PLAYER, 0, ANIM_Peach1_Run)
    Call(PlayerRunToGoal, 0)
    Call(SetAnimation, ACTOR_PLAYER, 0, ANIM_Peach1_Idle)
    Return
    End
};

OVL_DEF_BATTLE_SCRIPT(BATTLE_SCRIPT_KIND_STAR_POWER,
    &EVS_UsePower,
);
