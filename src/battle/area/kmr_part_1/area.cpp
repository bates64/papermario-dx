#include "area.hpp"
#include "stage/kmr_part_1_battle_stages.hpp"
#include "battle/common/actor/kmr_part_1/goomba_family.hpp"
// TODO: make actors relocatable
#include "battle/common/actor/kmr_part_1/goomba_family.inc.cpp"

using namespace battle::actor;

namespace battle::area::kmr_part_1 {

Formation Formation_Goomba_Solo = {
    ACTOR_BY_IDX(Goomba, BTL_POS_GROUND_B, 10),
};

Formation Formation_Goomba_Duo = {
    ACTOR_BY_IDX(Goomba, BTL_POS_GROUND_B, 10),
    ACTOR_BY_IDX(Goomba, BTL_POS_GROUND_C, 9),
};

Formation Formation_Goomba_Trio = {
    ACTOR_BY_IDX(Goomba, BTL_POS_GROUND_A, 10),
    ACTOR_BY_IDX(Goomba, BTL_POS_GROUND_B, 9),
    ACTOR_BY_IDX(Goomba, BTL_POS_GROUND_C, 8),
};

Formation Formation_Goomba_Solo_Paragoomba_Solo = {
    ACTOR_BY_IDX(Goomba, BTL_POS_GROUND_B, 10),
    ACTOR_BY_IDX(Paragoomba, BTL_POS_AIR_C, 9),
};

Formation Formation_Goomba_Quad = {
    ACTOR_BY_IDX(Goomba, BTL_POS_GROUND_A, 10),
    ACTOR_BY_IDX(Goomba, BTL_POS_GROUND_B, 9),
    ACTOR_BY_IDX(Goomba, BTL_POS_GROUND_C, 8),
    ACTOR_BY_IDX(Goomba, BTL_POS_GROUND_D, 7),
};

Formation Formation_Goomba_Solo_SpikedGoomba_Solo = {
    ACTOR_BY_IDX(Goomba, BTL_POS_GROUND_B, 10),
    ACTOR_BY_IDX(SpikedGoomba, BTL_POS_GROUND_C, 9),
};

Formation Formation_Goomba_Duo_Paragoomba_Duo = {
    ACTOR_BY_IDX(Goomba, BTL_POS_GROUND_A, 10),
    ACTOR_BY_IDX(Paragoomba, BTL_POS_AIR_B, 9),
    ACTOR_BY_IDX(Goomba, BTL_POS_GROUND_C, 8),
    ACTOR_BY_IDX(Paragoomba, BTL_POS_AIR_D, 7),
};

Formation Formation_Paragoomba_Solo = {
    ACTOR_BY_IDX(Paragoomba, BTL_POS_AIR_B, 10),
};

Formation Formation_Paragoomba_Duo = {
    ACTOR_BY_IDX(Paragoomba, BTL_POS_AIR_B, 10),
    ACTOR_BY_IDX(Paragoomba, BTL_POS_AIR_C, 9),
};

Formation Formation_Paragoomba_Trio = {
    ACTOR_BY_IDX(Paragoomba, BTL_POS_AIR_A, 10),
    ACTOR_BY_IDX(Paragoomba, BTL_POS_AIR_B, 9),
    ACTOR_BY_IDX(Paragoomba, BTL_POS_AIR_C, 8),
};

Formation Formation_SpikedGoomba_Solo = {
    ACTOR_BY_IDX(SpikedGoomba, BTL_POS_GROUND_B, 10),
};

Formation Formation_SpikedGoomba_Solo_Goomba_Solo = {
    ACTOR_BY_IDX(SpikedGoomba, BTL_POS_GROUND_B, 10),
    ACTOR_BY_IDX(Goomba, BTL_POS_GROUND_C, 9),
};

BattleList Battles = {
    BATTLE(Formation_Goomba_Solo, PleasantPath4, "クリボー"), // Battle 00
    BATTLE(Formation_Goomba_Duo, PleasantPath4, "クリボーx２"), // Battle 01
    BATTLE(Formation_Goomba_Trio, PleasantPath4, "クリボーx３"), // Battle 02
    BATTLE(Formation_Goomba_Solo_Paragoomba_Solo, PleasantPath4, "クリボー、パタクリボー"), // 0Battle 3
    BATTLE(Formation_Goomba_Quad, PleasantPath4, "クリボーx４"), // Battle 04
    BATTLE(Formation_Goomba_Solo_SpikedGoomba_Solo, PleasantPath4, "クリボー,トゲクリボー"), // Battle 05
    BATTLE(Formation_Goomba_Duo_Paragoomba_Duo, PleasantPath4, "クリボー,パタクリボー,クリボー,パタクリボー"), // Battle 06
    BATTLE(Formation_Paragoomba_Solo, PleasantPath4, "パタクリボー"), // Battle 07
    BATTLE(Formation_Paragoomba_Duo, PleasantPath4, "パタクリボーx２"), // Battle 08
    BATTLE(Formation_Paragoomba_Trio, PleasantPath4, "パタクリボーx３"), // Battle 09
    BATTLE(Formation_SpikedGoomba_Solo, PleasantPath4, "トゲクリボー"), // Battle 0A
    BATTLE(Formation_SpikedGoomba_Solo_Goomba_Solo, PleasantPath4, "トゲクリボー、クリボー"), // Battle 0B
    {},
};

StageList Stages = {
    STAGE("kmr_02", PleasantPath2),
    STAGE("kmr_03", PleasantPath3),
    STAGE("kmr_04", PleasantPath4),
    STAGE("kmr_05", PleasantPath5),
    STAGE("kmr_06", PleasantPath6),
    {},
};

} // namespace battle::area::kmr_part_1
