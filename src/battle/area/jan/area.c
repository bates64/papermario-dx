#include "area.h"

extern Stage A(jan_00);
extern Stage A(jan_01);
extern Stage A(jan_01b);
extern Stage A(jan_02);
extern Stage A(jan_03);
extern Stage A(jan_03b);
extern Stage A(jan_04);
extern Stage A(jan_04b);

Formation A(Formation_00) = {
    OVL_ACTOR_BY_IDX("spear_guy", BTL_POS_GROUND_B, 10, 0),
    OVL_ACTOR_BY_IDX("spear_guy", BTL_POS_GROUND_C, 9, 1),
};

Formation A(Formation_01) = {
    OVL_ACTOR_BY_IDX("spear_guy", BTL_POS_GROUND_A, 10, 0),
    OVL_ACTOR_BY_IDX("spear_guy", BTL_POS_GROUND_B, 9, 1),
    OVL_ACTOR_BY_IDX("spear_guy", BTL_POS_GROUND_C, 8, 1),
};

Formation A(Formation_02) = {
    OVL_ACTOR_BY_IDX("spear_guy", BTL_POS_GROUND_B, 10, 0),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_03) = {
    OVL_ACTOR_BY_IDX("spear_guy", BTL_POS_GROUND_A, 10, 0),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_D, 7),
};

Formation A(Formation_04) = {
    OVL_ACTOR_BY_IDX("spear_guy", BTL_POS_GROUND_A, 10, 0),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_05) = {
    OVL_ACTOR_BY_IDX("spear_guy", BTL_POS_GROUND_A, 10, 0),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spear_guy", BTL_POS_GROUND_C, 8, 1),
};

Formation A(Formation_06) = {
    OVL_ACTOR_BY_IDX("spear_guy", BTL_POS_GROUND_A, 10, 0),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spear_guy", BTL_POS_GROUND_C, 8, 1),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_D, 7),
};

Formation A(Formation_07) = {
    OVL_ACTOR_BY_IDX("spear_guy", BTL_POS_GROUND_A, 10, 0),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_08) = {
    OVL_ACTOR_BY_IDX("hurt_plant", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("hurt_plant", BTL_POS_GROUND_C, 10),
};

Formation A(Formation_09) = {
    OVL_ACTOR_BY_IDX("hurt_plant", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("hurt_plant", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("hurt_plant", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_0A) = {
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_0B) = {
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_0C) = {
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_D, 7),
};

Formation A(Formation_0D) = {
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spear_guy", BTL_POS_GROUND_B, 9, 1),
    OVL_ACTOR_BY_IDX("jungle_fuzzy", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_0E) = {
    OVL_ACTOR_BY_IDX("m_bush", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("m_bush", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_0F) = {
    OVL_ACTOR_BY_IDX("m_bush", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("m_bush", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("m_bush", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_10) = {
    OVL_ACTOR_BY_IDX("m_bush", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("m_bush", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("m_bush", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("m_bush", BTL_POS_GROUND_D, 7),
};

BattleList A(Formations) = {
    BATTLE(A(Formation_00), A(jan_01), "ヤリダンサーx2"),
    BATTLE(A(Formation_01), A(jan_01), "ヤリダンサーx3"),
    BATTLE(A(Formation_02), A(jan_01), "ヤリダンサー,トロピカル"),
    BATTLE(A(Formation_03), A(jan_01), "ヤリダンサー,トロピカルx３"),
    BATTLE(A(Formation_04), A(jan_01), "ヤリダンサー,トロピカルx２"),
    BATTLE(A(Formation_05), A(jan_01), "ヤリダンサー,トロピカル,ヤリダンサー"),
    BATTLE(A(Formation_06), A(jan_01), "ヤリダンサー,トロピカル,ヤリダンサー,トロピカル"),
    BATTLE(A(Formation_07), A(jan_01), "ヤリダンサー,かいふくヘイホー,トゲメット"),
    BATTLE(A(Formation_08), A(jan_01), "ピロリンそうだましx2"),
    BATTLE(A(Formation_09), A(jan_01), "ピロリンそうだましx3"),
    BATTLE(A(Formation_0A), A(jan_01), "トロピカルx2"),
    BATTLE(A(Formation_0B), A(jan_01), "トロピカルx3"),
    BATTLE(A(Formation_0C), A(jan_01), "トロピカルx4"),
    BATTLE(A(Formation_0D), A(jan_01), "トロピカル,ヤリダンサー,トロピカル"),
    BATTLE(A(Formation_0E), A(jan_01), "ぎたいそうx2"),
    BATTLE(A(Formation_0F), A(jan_01), "ぎたいそうx3"),
    BATTLE(A(Formation_10), A(jan_01), "ぎたいそうx4"),
    {},
};

StageList A(Stages) = {
    STAGE("jan_00", A(jan_00)),
    STAGE("jan_01", A(jan_01)),
    STAGE("jan_01b", A(jan_01b)),
    STAGE("jan_02", A(jan_02)),
    STAGE("jan_03", A(jan_03)),
    STAGE("jan_03b", A(jan_03b)),
    STAGE("jan_04", A(jan_04)),
    STAGE("jan_04b", A(jan_04b)),
    {},
};
