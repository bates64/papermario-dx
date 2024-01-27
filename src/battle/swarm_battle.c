#include "swarm_battle.h"

BSS b32 isSwarmBattle;

f32 swarm_battle_party_x_offset(void) {
    if (isSwarmBattle) {
        return 100.0f + 35.0f / 2.0f;
    } else {
        return 0.0f;
    }
}

b32 is_battle_swarm_battle(Battle* battle) {
    for (s32 i = 0; i < battle->formationSize; i++) {
        if (&(*battle->formation)[i].isBehind) {
            return TRUE;
        }
    }
    return FALSE;
}
