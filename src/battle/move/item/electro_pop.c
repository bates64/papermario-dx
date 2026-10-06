#include "common.h"
#include "battle/script_module.h"
#include "script_api/battle.h"
#include "sprite/player.h"

#include "effects.h"

API_CALLABLE(func_802A123C_7307DC) {
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* player = battleStatus->playerActor;

    inflict_status(player, STATUS_KEY_STATIC, script->varTable[0]);
    player->statusAfflicted = 0;
    return ApiStatus_DONE2;
}

#if !VERSION_PAL
API_CALLABLE(func_802A1450_7309F0) {
    ItemData* item = &gItemTable[ITEM_ELECTRO_POP];
    PlayerData* playerData = &gPlayerData;

    playerData->curHP += item->potencyA;
    if (playerData->curHP > playerData->curMaxHP) {
        playerData->curHP = playerData->curMaxHP;
    }

    script->varTable[3] = item->potencyA;

    return ApiStatus_DONE2;
}
#endif

API_CALLABLE(func_802A14F0_730A90) {
    ItemData* item = &gItemTable[ITEM_ELECTRO_POP];
    PlayerData* playerData = &gPlayerData;

#if VERSION_PAL
    playerData->curFP += item->potencyB;
#else
    playerData->curFP += item->potencyA;
#endif
    if (playerData->curFP > playerData->curMaxFP) {
        playerData->curFP = playerData->curMaxFP;
    }

    script->varTable[3] = item->potencyB;

    return ApiStatus_DONE2;
}

#include "battle/common/move/UseItem.inc.c"

EvtScript EVS_UseItem = {
    SetConst(LVarA, ITEM_ELECTRO_POP)
    ExecWait(UseItemWithEffect)
    ExecWait(EatItem)
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Add(LVar1, 20)
    PlayEffect(EFFECT_SNAKING_STATIC, 0, LVar0, LVar1, LVar2, Float(1.0), 30)
    Call(PlaySound, SOUND_VOLT_SHROOM_APPLY)
    Call(GetItemPower, ITEM_VOLT_SHROOM, LVar0, LVar1)
    Call(func_802A123C_7307DC)
    Wait(40)
    Call(func_802A14F0_730A90)
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Add(LVar0, 20)
    Add(LVar1, 25)
    Call(SpawnRecoverFlowerFX, LVar0, LVar1, LVar2, LVar3)
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Add(LVar1, 25)
    Call(ShowStartRecoveryShimmer, LVar0, LVar1, LVar2, LVar3)
#if !VERSION_PAL
    Call(AddFP, LVar3)
#endif
    Wait(10)
    Call(SetAnimation, ACTOR_PLAYER, 0, ANIM_Mario1_ThumbsUp)
    Wait(30)
    Call(GetActorPos, ACTOR_PLAYER, LVar0, LVar1, LVar2)
    Call(ShowRecoveryShimmer, LVar0, LVar1, LVar2, LVar3)
    Call(SetAnimation, ACTOR_PLAYER, 0, ANIM_Mario1_Idle)
    Wait(20)
    Call(ShowMessageBox, BTL_MSG_PLAYER_CHARGED, 60)
    Call(WaitForMessageBoxDone)
    ExecWait(PlayerGoHome)
    Return
    End
};

BATTLE_SCRIPT_MODULE(BATTLE_SCRIPT_KIND_ITEM,
    &EVS_UseItem,
);
