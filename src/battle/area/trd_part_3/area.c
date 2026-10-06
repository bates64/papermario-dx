#include "area.h"

extern ActorBlueprint A(eldstar);

Formation A(Formation_00) = {
    ACTOR_BY_IDX(A(eldstar), BTL_POS_AIR_C, 10),
};

BattleList A(Formations) = {
    BATTLE(A(Formation_00), "nok_01", "ほしのせい レクチャー"),
    {},
};

StageList A(Stages) = {
    STAGE("nok_01", "nok_01"),
    {},
};
