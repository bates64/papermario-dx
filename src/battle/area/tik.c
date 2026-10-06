#include "battle/battle.h"

static Formation dark_koopa_2 = {
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_C, 9),
};

static Formation dark_koopa_3 = {
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_C, 8),
};

static Formation dark_koopa_4 = {
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_D, 7),
};

static Formation dark_koopa_1_dark_paratroopa_2 = {
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("dark_paratroopa", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("dark_paratroopa", BTL_POS_AIR_C, 8),
};

static Formation dark_koopa_1_spike_top_2 = {
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_C, 8),
};

static Formation dark_koopa_1_spike_top_1_dark_koopa_1 = {
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_C, 8),
};

static Formation dark_koopa_1_spiny_2 = {
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_C, 8),
};

static Formation dark_koopa_1_spiny_1_dark_koopa_1_spiny_1 = {
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_D, 7),
};

static Formation dark_paratroopa_2 = {
    OVL_ACTOR_BY_IDX("dark_paratroopa", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("dark_paratroopa", BTL_POS_AIR_C, 9),
};

static Formation dark_paratroopa_3 = {
    OVL_ACTOR_BY_IDX("dark_paratroopa", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("dark_paratroopa", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("dark_paratroopa", BTL_POS_AIR_C, 8),
};

static Formation gloomba_2 = {
    OVL_ACTOR_BY_IDX("gloomba", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("gloomba", BTL_POS_GROUND_C, 9),
};

static Formation gloomba_4 = {
    OVL_ACTOR_BY_IDX("gloomba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("gloomba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("gloomba", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("gloomba", BTL_POS_GROUND_D, 7),
};

static Formation paragloomba_3 = {
    OVL_ACTOR_BY_IDX("paragloomba", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("paragloomba", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("paragloomba", BTL_POS_AIR_C, 8),
};

static Formation paragloomba_1_spiked_gloomba_1 = {
    OVL_ACTOR_BY_IDX("paragloomba", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("spiked_gloomba", BTL_POS_GROUND_C, 9),
};

static Formation spiked_gloomba_2 = {
    OVL_ACTOR_BY_IDX("spiked_gloomba", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("spiked_gloomba", BTL_POS_GROUND_C, 9),
};

static Formation spiked_gloomba_1_gloomba_2 = {
    OVL_ACTOR_BY_IDX("spiked_gloomba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("gloomba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("gloomba", BTL_POS_GROUND_C, 8),
};

static Formation spiked_gloomba_1_buzzy_beetle_2 = {
    OVL_ACTOR_BY_IDX("spiked_gloomba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_C, 8),
};

static Formation spiked_gloomba_1_mixed_11 = {
    OVL_ACTOR_BY_IDX("spiked_gloomba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spiked_gloomba", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_D, 7),
};

static Formation spiked_gloomba_1_mixed_12 = {
    OVL_ACTOR_BY_IDX("spiked_gloomba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("paragloomba", BTL_POS_AIR_C, 8),
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_D, 7),
};

static Formation spike_top_4 = {
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_D, 7),
};

static Formation spike_top_2 = {
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_C, 9),
};

static Formation buzzy_beetle_1_spiked_gloomba_1_buzzy_beetle_1 = {
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spiked_gloomba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_C, 8),
};

static Formation spiny_2 = {
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_C, 9),
};

static Formation spiny_3 = {
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_C, 8),
};

static Formation spiny_4 = {
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_D, 7),
};

static BattleList Formations = {
    BATTLE(dark_koopa_2, "tik_01"),
    BATTLE(dark_koopa_3, "tik_01"),
    BATTLE(dark_koopa_4, "tik_01"),
    BATTLE(dark_koopa_1_dark_paratroopa_2, "tik_01"),
    BATTLE(dark_koopa_1_spike_top_2, "tik_01"),
    BATTLE(dark_koopa_1_spike_top_1_dark_koopa_1, "tik_01"),
    BATTLE(dark_koopa_1_spiny_2, "tik_01"),
    BATTLE(dark_koopa_1_spiny_1_dark_koopa_1_spiny_1, "tik_01"),
    BATTLE(dark_paratroopa_2, "tik_01"),
    BATTLE(dark_paratroopa_3, "tik_01"),
    BATTLE(gloomba_2, "tik_01"),
    BATTLE(gloomba_4, "tik_01"),
    BATTLE(paragloomba_3, "tik_01"),
    BATTLE(paragloomba_1_spiked_gloomba_1, "tik_01"),
    BATTLE(spiked_gloomba_2, "tik_01"),
    BATTLE(spiked_gloomba_1_gloomba_2, "tik_01"),
    BATTLE(spiked_gloomba_1_buzzy_beetle_2, "tik_01"),
    BATTLE(spiked_gloomba_1_mixed_11, "tik_01"),
    BATTLE(spiked_gloomba_1_mixed_12, "tik_01"),
    BATTLE(spike_top_4, "tik_01"),
    BATTLE(spike_top_2, "tik_01"),
    BATTLE(buzzy_beetle_1_spiked_gloomba_1_buzzy_beetle_1, "tik_01"),
    BATTLE(spiny_2, "tik_01"),
    BATTLE(spiny_3, "tik_01"),
    BATTLE(spiny_4, "tik_01"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .battleCount = ARRAY_COUNT(Formations) - 1,
};
