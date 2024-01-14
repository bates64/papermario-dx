#include "area.h"

#include "battle/common/stage/area_mod/mod_00.inc.c"
#include "battle/common/newactor/king_boo.inc.c"

extern ActorBlueprint A(reznor);

extern Stage A(mod_00);

Vec3i A(KingBooPos) = { 70, 50, 5 };

Formation A(Formation_00) = {
    ACTOR_BY_POS(A(king_boo), A(KingBooPos), 10),
};

BattleList A(Formations) = {
    BATTLE(A(Formation_00), A(mod_00), "ハイパークリボー"),
    {},
};

StageList A(Stages) = {
    STAGE("mod_00", A(mod_00)),
    {},
};
