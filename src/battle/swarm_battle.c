#include "swarm_battle.h"

BSS b32 isSwarmBattle;

f32 swarm_battle_party_x_offset(void) {
    if (isSwarmBattle) {
        return 100.0f + 35.0f / 2.0f;
    } else {
        return 0.0f;
    }
}
