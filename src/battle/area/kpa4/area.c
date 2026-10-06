#include "area.h"

extern ActorBlueprint A(bombshell_blaster);
extern ActorBlueprint A(bombshell_bill);
extern ActorBlueprint A(magikoopa);

Formation A(Formation_00) = {
    ACTOR_BY_IDX(A(bombshell_bill), BTL_POS_GROUND_B, 10),
    ACTOR_BY_IDX(A(bombshell_bill), BTL_POS_GROUND_C, 9),
};

Formation A(Formation_01) = {
    ACTOR_BY_IDX(A(bombshell_bill), BTL_POS_GROUND_A, 10),
    ACTOR_BY_IDX(A(bombshell_bill), BTL_POS_GROUND_B, 9),
    ACTOR_BY_IDX(A(bombshell_bill), BTL_POS_GROUND_C, 8),
};

Vec3i A(blaster_pos_1) = { 70, 0, -20 };

Vec3i A(blaster_pos_2) = { 100, 0, 0 };

Formation A(Formation_02) = {
    ACTOR_BY_POS(A(bombshell_blaster), A(blaster_pos_1), 10),
    ACTOR_BY_POS(A(bombshell_blaster), A(blaster_pos_2), 9),
};

Vec3i A(pos_3) = { 130, 0, 25 };

Formation A(Formation_03) = {
    ACTOR_BY_POS(A(bombshell_blaster), A(blaster_pos_1), 10),
    ACTOR_BY_POS(A(bombshell_blaster), A(blaster_pos_2), 9),
    OVL_ACTOR_BY_POS("koopatrol", A(pos_3), 8),
};

Formation A(Formation_04) = {
    ACTOR_BY_POS(A(bombshell_blaster), A(blaster_pos_1), 10),
    ACTOR_BY_POS(A(bombshell_blaster), A(blaster_pos_2), 9),
    ACTOR_BY_POS(A(magikoopa), A(pos_3), 8),
};

BattleList A(Formations) = {
    BATTLE(A(Formation_00), "kpa_01", "スーパーキラーx２"),
    BATTLE(A(Formation_01), "kpa_01", "スーパーキラーx３"),
    BATTLE(A(Formation_02), "kpa_01", "スーパーキラーたいほうx２"),
    BATTLE(A(Formation_03), "kpa_01", "スーパーキラーたいほうx２,トゲノコ"),
    BATTLE(A(Formation_04), "kpa_01", "スーパーキラーたいほうx２,カメック"),
    {},
};

StageList A(Stages) = {
    STAGE("kpa_01", "kpa_01"),
    STAGE("kpa_01b", "kpa_01b"),
    STAGE("kpa_02", "kpa_02"),
    STAGE("kpa_03", "kpa_03"),
    STAGE("kpa_04", "kpa_04"),
    STAGE("kpa_04b", "kpa_04b"),
    STAGE("kpa_04c", "kpa_04c"),
    STAGE("kpa_05", "kpa_05"),
    STAGE("kpa_07", "kpa_07"),
    STAGE("kpa_08", "kpa_08"),
    STAGE("kpa_09", "kpa_09"),
    STAGE("kpa_11", "kpa_11"),
    STAGE("kpa_13", "kpa_13"),
    STAGE("kpa_14", "kpa_14"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &A(Formations),
    .stages = &A(Stages),
    .battleCount = ARRAY_COUNT(A(Formations)) - 1,
    .stageCount = ARRAY_COUNT(A(Stages)) - 1,
};
