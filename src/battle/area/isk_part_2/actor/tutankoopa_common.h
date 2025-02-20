#pragma once

#include "macros.h"
#include "enums.h"

enum N(BattleCommon) {
    ACTOR_TUTANKOOPA    = ACTOR_ENEMY0,
    ACTOR_CHOMP         = ACTOR_ENEMY1,
    AVAR_Tutankoopa_Stunned         = 8,  // actor var for Tutankoopa
    AVAR_Tutankoopa_NextSummonTime  = 12, // actor var for Tutankoopa to signal chomp has died
};
