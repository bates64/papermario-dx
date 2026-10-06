#pragma once

#include "battle/battle.h"

typedef struct BattlePartner {
    /* 0x00 */ s32 id;
    /* 0x04 */ s32 posY;
    /* 0x08 */ ActorBlueprint* blueprint;
} BattlePartner; // size = 0x0C

#define BATTLE_PARTNER_EXPORT_NAME "gBattlePartner"
#define OVL_DEF_BATTLE_PARTNER(partnerID, partnerPosY) \
    export const BattlePartner gBattlePartner = { \
        .id = (partnerID), \
        .posY = (partnerPosY), \
        .blueprint = &blueprint, \
    }

const BattlePartner* load_battle_partner(s32 partnerID);
struct Overlay* get_battle_partner_overlay(void);
void unload_battle_partner(void);
void reset_battle_partner_overlay(void);
