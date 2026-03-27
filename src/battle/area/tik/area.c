#include "area.h"

extern Stage A(tik_01);
extern Stage A(tik_02);
extern Stage A(tik_03);
extern Stage A(tik_04);
extern Stage A(tik_05);

Formation A(Formation_00) = {
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_01) = {
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_02) = {
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_D, 7),
};

Formation A(Formation_03) = {
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("dark_paratroopa", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("dark_paratroopa", BTL_POS_AIR_C, 8),
};

Formation A(Formation_04) = {
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_05) = {
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_06) = {
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_07) = {
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("dark_koopa", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_D, 7),
};

Formation A(Formation_08) = {
    OVL_ACTOR_BY_IDX("dark_paratroopa", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("dark_paratroopa", BTL_POS_AIR_C, 9),
};

Formation A(Formation_09) = {
    OVL_ACTOR_BY_IDX("dark_paratroopa", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("dark_paratroopa", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("dark_paratroopa", BTL_POS_AIR_C, 8),
};

Formation A(Formation_0A) = {
    OVL_ACTOR_BY_IDX("gloomba", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("gloomba", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_0B) = {
    OVL_ACTOR_BY_IDX("gloomba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("gloomba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("gloomba", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("gloomba", BTL_POS_GROUND_D, 7),
};

Formation A(Formation_0C) = {
    OVL_ACTOR_BY_IDX("paragloomba", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("paragloomba", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("paragloomba", BTL_POS_AIR_C, 8),
};

Formation A(Formation_0D) = {
    OVL_ACTOR_BY_IDX("paragloomba", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("spiked_gloomba", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_0E) = {
    OVL_ACTOR_BY_IDX("spiked_gloomba", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("spiked_gloomba", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_0F) = {
    OVL_ACTOR_BY_IDX("spiked_gloomba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("gloomba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("gloomba", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_10) = {
    OVL_ACTOR_BY_IDX("spiked_gloomba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_11) = {
    OVL_ACTOR_BY_IDX("spiked_gloomba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spiked_gloomba", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_D, 7),
};

Formation A(Formation_12) = {
    OVL_ACTOR_BY_IDX("spiked_gloomba", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("paragloomba", BTL_POS_AIR_C, 8),
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_D, 7),
};

Formation A(Formation_13) = {
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_D, 7),
};

Formation A(Formation_14) = {
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_15) = {
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spiked_gloomba", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("buzzy_beetle", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_16) = {
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_17) = {
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_18) = {
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_D, 7),
};

BattleList A(Formations) = {
    BATTLE(A(Formation_00), A(tik_01), "ヤミノコノコx２"),
    BATTLE(A(Formation_01), A(tik_01), "ヤミノコノコx３"),
    BATTLE(A(Formation_02), A(tik_01), "ヤミノコノコx４"),
    BATTLE(A(Formation_03), A(tik_01), "ヤミノコノコ,ヤミパタパタx２"),
    BATTLE(A(Formation_04), A(tik_01), "ヤミノコノコ,トゲメットx２"),
    BATTLE(A(Formation_05), A(tik_01), "ヤミノコノコ,トゲメット,ヤミノコノコ"),
    BATTLE(A(Formation_06), A(tik_01), "ヤミノコノコ,トゲゾーx２"),
    BATTLE(A(Formation_07), A(tik_01), "ヤミノコノコ,トゲゾー,ヤミノコノコ,トゲゾー"),
    BATTLE(A(Formation_08), A(tik_01), "ヤミパタパタx２"),
    BATTLE(A(Formation_09), A(tik_01), "ヤミパタパタx３"),
    BATTLE(A(Formation_0A), A(tik_01), "ヤミクリボーx２"),
    BATTLE(A(Formation_0B), A(tik_01), "ヤミクリボーx４"),
    BATTLE(A(Formation_0C), A(tik_01), "ヤミパタクリx３"),
    BATTLE(A(Formation_0D), A(tik_01), "ヤミパタクリ,ヤミトゲクリ"),
    BATTLE(A(Formation_0E), A(tik_01), "ヤミトゲクリx２"),
    BATTLE(A(Formation_0F), A(tik_01), "ヤミトゲクリ,ヤミクリボーx２"),
    BATTLE(A(Formation_10), A(tik_01), "ヤミトゲクリ,メットx２"),
    BATTLE(A(Formation_11), A(tik_01), "ヤミトゲクリ,メット,ヤミトゲクリ,メット"),
    BATTLE(A(Formation_12), A(tik_01), "ヤミトゲクリ,メット,ヤミパタクリ,メット"),
    BATTLE(A(Formation_13), A(tik_01), "トゲメットx４"),
    BATTLE(A(Formation_14), A(tik_01), "トゲメットx２"),
    BATTLE(A(Formation_15), A(tik_01), "メット,ヤミトゲクリ,メット"),
    BATTLE(A(Formation_16), A(tik_01), "トゲゾーx２"),
    BATTLE(A(Formation_17), A(tik_01), "トゲゾーx３"),
    BATTLE(A(Formation_18), A(tik_01), "トゲゾーx４"),
    {},
};

StageList A(Stages) = {
    STAGE("tik_01", A(tik_01)),
    STAGE("tik_02", A(tik_02)),
    STAGE("tik_03", A(tik_03)),
    STAGE("tik_04", A(tik_04)),
    STAGE("tik_05", A(tik_05)),
    {},
};
