#include "area.h"

#include "battle/common/stage/area_mod/mod_00.inc.c"

extern ActorBlueprint A(king_boo);
extern ActorBlueprint A(pink_shy_guy);


extern Stage A(mod_00);

Vec3i A(KingBooPos) = { 70, 50, 5 };

Formation A(Formation_00) = {
    ACTOR_BY_POS(A(king_boo), A(KingBooPos), 10),
};

Formation A(Formation_01) = {
    ACTOR_BY_IDX(A(pink_shy_guy), BTL_POS_GROUND_B, 10),
    ACTOR_BY_IDX(A(pink_shy_guy), BTL_POS_GROUND_B, 9, .isBehind = TRUE),
};

BattleList A(Formations) = {
    BATTLE(A(Formation_00), A(mod_00), "ハイパークリボー"),
    BATTLE(A(Formation_01), A(mod_00), "ハイパークリボー"),
    {},
};

StageList A(Stages) = {
    STAGE("mod_00", A(mod_00)),
    {},
};
