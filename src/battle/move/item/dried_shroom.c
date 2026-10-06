#include "common.h"
#include "battle/script_module.h"
#include "script_api/battle.h"
#include "effects.h"
#include "sprite/player.h"

API_CALLABLE(func_802A12FC_71CFDC) {
    PlayerData* playerData = &gPlayerData;

    playerData->curHP++;
    if (playerData->curHP > playerData->curMaxHP) {
        playerData->curHP = playerData->curMaxHP;
    }
    return ApiStatus_DONE2;
}

#include "battle/common/move/UseItem.inc.c"

EvtScript EVS_UseItem = {
    SetConst(LVarA, ITEM_DRIED_SHROOM)
    ExecWait(UseItemWithEffect)
    ExecWait(EatItem)
    Call(SetAnimation, ACTOR_PLAYER, 0, ANIM_Mario1_StickOutTongue)
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Add(LVar0, 0)
    Add(LVar1, 35)
    Call(SpawnRecoverHeartFX, LVar0, LVar1, LVar2, 1)
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Add(LVar1, 25)
    Add(LVar2, 5)
    Call(ShowStartRecoveryShimmer, LVar0, LVar1, LVar2, 1)
    Call(func_802A12FC_71CFDC)
    Wait(30)
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Add(LVar2, 5)
    Call(ShowRecoveryShimmer, LVar0, LVar1, LVar2, 1)
    Call(SetAnimation, ACTOR_PLAYER, 0, ANIM_Mario1_Idle)
    Wait(20)
    ExecWait(PlayerGoHome)
    Return
    End
};

OVL_DEF_BATTLE_SCRIPT(BATTLE_SCRIPT_KIND_ITEM,
    &EVS_UseItem,
);
