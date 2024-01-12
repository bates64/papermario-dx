#include "area.h"

#include "battle/common/stage/area_mod/mod_00.inc.c"
#include "battle/common/newactor/reznor.inc.c"

extern ActorBlueprint A(reznor);

extern Stage A(mod_00);

Formation A(Formation_00) = {
    ACTOR_BY_IDX(A(reznor), BTL_POS_GROUND_B, 10),
};

BattleList A(Formations) = {
    BATTLE(A(Formation_00), A(mod_00), "ハイパークリボー"),
    {},
};

StageList A(Stages) = {
    STAGE("mod_00", A(mod_00)),
    {},
};
