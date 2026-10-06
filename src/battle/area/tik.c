#include "battle/battle.h"

static Formation Formation_00 = {
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_C, 9),
};

static Formation Formation_01 = {
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_C, 8),
};

static Formation Formation_02 = {
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_D, 7),
};

static Formation Formation_03 = {
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("dark_paratroopa", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("dark_paratroopa", BTL_POS_AIR_C, 8),
};

static Formation Formation_04 = {
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_C, 8),
};

static Formation Formation_05 = {
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_C, 8),
};

static Formation Formation_06 = {
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_C, 8),
};

static Formation Formation_07 = {
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_D, 7),
};

static Formation Formation_08 = {
    OVL_ACTOR_BY_IDX("dark_paratroopa", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("dark_paratroopa", BTL_POS_AIR_C, 9),
};

static Formation Formation_09 = {
    OVL_ACTOR_BY_IDX("dark_paratroopa", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("dark_paratroopa", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("dark_paratroopa", BTL_POS_AIR_C, 8),
};

static Formation Formation_0A = {
    OVL_ACTOR_BY_IDX("gloomba", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("gloomba", BTL_POS_GROUND_C, 9),
};

static Formation Formation_0B = {
    OVL_ACTOR_BY_IDX("gloomba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("gloomba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("gloomba", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("gloomba", BTL_POS_GROUND_D, 7),
};

static Formation Formation_0C = {
    OVL_ACTOR_BY_IDX("paragloomba", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("paragloomba", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("paragloomba", BTL_POS_AIR_C, 8),
};

static Formation Formation_0D = {
    OVL_ACTOR_BY_IDX("paragloomba", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("spiked_gloomba", BTL_POS_GROUND_C, 9),
};

static Formation Formation_0E = {
    OVL_ACTOR_BY_IDX("spiked_gloomba", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("spiked_gloomba", BTL_POS_GROUND_C, 9),
};

static Formation Formation_0F = {
    OVL_ACTOR_BY_IDX("spiked_gloomba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("gloomba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("gloomba", BTL_POS_GROUND_C, 8),
};

static Formation Formation_10 = {
    OVL_ACTOR_BY_IDX("spiked_gloomba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_C, 8),
};

static Formation Formation_11 = {
    OVL_ACTOR_BY_IDX("spiked_gloomba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spiked_gloomba", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_D, 7),
};

static Formation Formation_12 = {
    OVL_ACTOR_BY_IDX("spiked_gloomba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("paragloomba", BTL_POS_AIR_C, 8),
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_D, 7),
};

static Formation Formation_13 = {
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_D, 7),
};

static Formation Formation_14 = {
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_C, 9),
};

static Formation Formation_15 = {
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spiked_gloomba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_C, 8),
};

static Formation Formation_16 = {
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_C, 9),
};

static Formation Formation_17 = {
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_C, 8),
};

static Formation Formation_18 = {
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_D, 7),
};

static BattleList Formations = {
    BATTLE(Formation_00, "tik_01", "Dark Koopa x2"),
    BATTLE(Formation_01, "tik_01", "Dark Koopa x3"),
    BATTLE(Formation_02, "tik_01", "Dark Koopa x4"),
    BATTLE(Formation_03, "tik_01", "Dark Koopa, Dark Paratroopa x2"),
    BATTLE(Formation_04, "tik_01", "Dark Koopa, Spike Top x2"),
    BATTLE(Formation_05, "tik_01", "Dark Koopa, Spike Top, Dark Koopa"),
    BATTLE(Formation_06, "tik_01", "Dark Koopa, Spiny x2"),
    BATTLE(Formation_07, "tik_01", "Dark Koopa, Spiny, Dark Koopa, Spiny"),
    BATTLE(Formation_08, "tik_01", "Dark Paratroopa x2"),
    BATTLE(Formation_09, "tik_01", "Dark Paratroopa x3"),
    BATTLE(Formation_0A, "tik_01", "Gloomba x2"),
    BATTLE(Formation_0B, "tik_01", "Gloomba x4"),
    BATTLE(Formation_0C, "tik_01", "Paragloomba x3"),
    BATTLE(Formation_0D, "tik_01", "Paragloomba, Spiked Gloomba"),
    BATTLE(Formation_0E, "tik_01", "Spiked Gloomba x2"),
    BATTLE(Formation_0F, "tik_01", "Spiked Gloomba, Gloomba x2"),
    BATTLE(Formation_10, "tik_01", "Spiked Gloomba, Buzzy Beetle x2"),
    BATTLE(Formation_11, "tik_01", "Spiked Gloomba, Buzzy Beetle, Spiked Gloomba, Buzzy Beetle"),
    BATTLE(Formation_12, "tik_01", "Spiked Gloomba, Buzzy Beetle, Paragloomba, Buzzy Beetle"),
    BATTLE(Formation_13, "tik_01", "Spike Top x4"),
    BATTLE(Formation_14, "tik_01", "Spike Top x2"),
    BATTLE(Formation_15, "tik_01", "Buzzy Beetle, Spiked Gloomba, Buzzy Beetle"),
    BATTLE(Formation_16, "tik_01", "Spiny x2"),
    BATTLE(Formation_17, "tik_01", "Spiny x3"),
    BATTLE(Formation_18, "tik_01", "Spiny x4"),
    {},
};

static StageList Stages = {
    STAGE("tik_01", "tik_01"),
    STAGE("tik_02", "tik_02"),
    STAGE("tik_03", "tik_03"),
    STAGE("tik_04", "tik_04"),
    STAGE("tik_05", "tik_05"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .stages = &Stages,
    .battleCount = ARRAY_COUNT(Formations) - 1,
    .stageCount = ARRAY_COUNT(Stages) - 1,
};
