#include "common.h"
#include "world/partners.h"
#include "twink.h"
#include "sprite/npc/Twink.h"

#define NAMESPACE world_twink

void N(init)(Npc* twink) {
    twink->collisionHeight = 20;
    twink->collisionDiameter = 20;
}

API_CALLABLE(N(TakeOut)) {
    Npc* twink = script->owner2.npc;

    if (isInitialCall) {
        partner_init_get_out(twink);
    }

    if(partner_get_out(twink)) {
        return ApiStatus_DONE1;
    } else {
        return ApiStatus_BLOCK;
    }
}

API_CALLABLE(N(Update)) {
    PlayerData* playerData = &gPlayerData;
    Npc* twink = script->owner2.npc;

    if (isInitialCall) {
        partner_flying_enable(twink, true);
    }

    partner_flying_update_player_tracking(twink);
    partner_flying_update_motion(twink);
    playerData->partnerUsedTime[PARTNER_TWINK]++;

    return ApiStatus_BLOCK;
}

API_CALLABLE(N(UseAbility)) {
    return ApiStatus_DONE2;
}

API_CALLABLE(N(PutAway)) {
    Npc* twink = script->owner2.npc;

    if (isInitialCall) {
        partner_init_put_away(twink);
    }

    if(partner_put_away(twink)) {
        return ApiStatus_DONE1;
    } else {
        return ApiStatus_BLOCK;
    }
}

EvtScript EVS_WorldTwink_TakeOut = {
    Call(N(TakeOut))
    Return
    End
};

EvtScript EVS_WorldTwink_Update = {
    Call(N(Update))
    Return
    End
};

EvtScript EVS_WorldTwink_UseAbility = {
    Call(N(UseAbility))
    Return
    End
};

EvtScript EVS_WorldTwink_PutAway = {
    Call(N(PutAway))
    Return
    End
};

WORLD_PARTNER_ENTRY = {
    .isFlying = true,
    .init = N(init),
    .takeOut = &EVS_WorldTwink_TakeOut,
    .update = &EVS_WorldTwink_Update,
    .useAbility = &EVS_WorldTwink_UseAbility,
    .putAway = &EVS_WorldTwink_PutAway,
    .idle = ANIM_Twink_Idle,
    .canUseAbility = partner_is_idle,
    .canPlayerOpenMenus = partner_is_idle,
};
