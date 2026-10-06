#include "common.h"
#include "goombaria.h"
#include "world/partners.h"
#include "sprite/npc/Goombaria.h"

void init(Npc* goombaria) {
    goombaria->collisionHeight = 24;
    goombaria->collisionDiameter = 20;
}

API_CALLABLE(TakeOut) {
    Npc* goombaria = script->owner2.npc;

    if (isInitialCall) {
        partner_init_get_out(goombaria);
    }

    return partner_get_out(goombaria) ? ApiStatus_DONE1 : ApiStatus_BLOCK;
}

API_CALLABLE(Update) {
    PlayerData* playerData = &gPlayerData;
    Npc* goombaria = script->owner2.npc;

    if (isInitialCall) {
        partner_walking_enable(goombaria, true);
    }

    partner_walking_update_player_tracking(goombaria);
    partner_walking_update_motion(goombaria);
    playerData->partnerUsedTime[PARTNER_GOOMBARIA]++;

    return ApiStatus_BLOCK;
}

API_CALLABLE(UseAbility) {
    return ApiStatus_DONE2;
}

API_CALLABLE(PutAway) {
    Npc* goombaria = script->owner2.npc;

    if (isInitialCall) {
        partner_init_put_away(goombaria);
    }

    if (partner_put_away(goombaria)) {
        return ApiStatus_DONE1;
    } else {
        return ApiStatus_BLOCK;
    }
}

EvtScript EVS_WorldGoombaria_TakeOut = {
    Call(TakeOut)
    Return
    End
};

EvtScript EVS_WorldGoombaria_Update = {
    Call(Update)
    Return
    End
};

EvtScript EVS_WorldGoombaria_UseAbility = {
    Call(UseAbility)
    Return
    End
};

EvtScript EVS_WorldGoombaria_PutAway = {
    Call(PutAway)
    Return
    End
};

WORLD_PARTNER_ENTRY = {
    .isFlying = false,
    .init = init,
    .takeOut = &EVS_WorldGoombaria_TakeOut,
    .update = &EVS_WorldGoombaria_Update,
    .useAbility = &EVS_WorldGoombaria_UseAbility,
    .putAway = &EVS_WorldGoombaria_PutAway,
    .idle = ANIM_Goombaria_Idle,
    .canUseAbility = partner_is_idle,
    .canPlayerOpenMenus = partner_is_idle,
};
