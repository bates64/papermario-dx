#include "area.h"

extern ActorBlueprint A(red_magikoopa_flying);
extern ActorBlueprint A(white_magikoopa_flying);

extern Stage A(kzn_01);
extern Stage A(kzn_01b);
extern Stage A(kzn_02);
extern Stage A(kzn_04);
extern Stage A(kzn_04b);
extern Stage A(kzn_04c);
extern Stage A(kzn_05);

Formation A(Formation_00) = {
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_01) = {
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_02) = {
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_D, 7),
};

Formation A(Formation_03) = {
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_D, 7),
};

Formation A(Formation_04) = {
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
};

Formation A(Formation_05) = {
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_B, 9),
    ACTOR_BY_IDX(A(red_magikoopa_flying), BTL_POS_AIR_C, 8),
};

Formation A(Formation_06) = {
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_B, 9),
    ACTOR_BY_IDX(A(white_magikoopa_flying), BTL_POS_AIR_C, 8),
};

Formation A(Formation_07) = {
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_08) = {
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_09) = {
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_0A) = {
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_0B) = {
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_0C) = {
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_0D) = {
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_D, 7),
};

Formation A(Formation_0E) = {
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_D, 7),
};

Formation A(Formation_0F) = {
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_10) = {
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_11) = {
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("lava_bubble", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_12) = {
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_13) = {
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_14) = {
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("putrid_piranha", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("spike_top", BTL_POS_GROUND_D, 7),
};

BattleList A(Formations) = {
    BATTLE(A(Formation_00), A(kzn_01), "バブルx2"),
    BATTLE(A(Formation_01), A(kzn_01), "バブルx3"),
    BATTLE(A(Formation_02), A(kzn_01), "バブルx4"),
    BATTLE(A(Formation_03), A(kzn_01), "バブル,トゲメットx３"),
    BATTLE(A(Formation_04), A(kzn_01), "バブルx2,かいふくヘイホー"),
    BATTLE(A(Formation_05), A(kzn_01), "バブルx2,レッドカメック"),
    BATTLE(A(Formation_06), A(kzn_01), "バブルx2,ホワイトカメック"),
    BATTLE(A(Formation_07), A(kzn_01), "バブルx2,トゲメット"),
    BATTLE(A(Formation_08), A(kzn_01), "トゲメットx２"),
    BATTLE(A(Formation_09), A(kzn_01), "トゲメット,バブル"),
    BATTLE(A(Formation_0A), A(kzn_01), "トゲメットx２,バブル"),
    BATTLE(A(Formation_0B), A(kzn_01), "トゲメット,ポイズンパックン"),
    BATTLE(A(Formation_0C), A(kzn_01), "トゲメットx２,ポイズンパックン"),
    BATTLE(A(Formation_0D), A(kzn_01), "トゲメットx２,ポイズンパックンx２"),
    BATTLE(A(Formation_0E), A(kzn_01), "トゲメット,バブルx３"),
    BATTLE(A(Formation_0F), A(kzn_01), "ポイズンパックンx２"),
    BATTLE(A(Formation_10), A(kzn_01), "ポイズンパックンx３"),
    BATTLE(A(Formation_11), A(kzn_01), "ポイズンパックン,バブル,ポイズンパックン"),
    BATTLE(A(Formation_12), A(kzn_01), "ポイズンパックンx２,トゲメット"),
    BATTLE(A(Formation_13), A(kzn_01), "ポイズンパックン,トゲメット,ポイズンパックン"),
    BATTLE(A(Formation_14), A(kzn_01), "ポイズンパックン,トゲメット,ポイズンパックン,トゲメット"),
    {},
};

StageList A(Stages) = {
    STAGE("kzn_01", A(kzn_01)),
    STAGE("kzn_01b", A(kzn_01b)),
    STAGE("kzn_02", A(kzn_02)),
    STAGE("kzn_04", A(kzn_04)),
    STAGE("kzn_04b", A(kzn_04b)),
    STAGE("kzn_04c", A(kzn_04c)),
    STAGE("kzn_05", A(kzn_05)),
    {},
};
