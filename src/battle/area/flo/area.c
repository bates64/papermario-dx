#include "area.h"

extern ActorBlueprint A(lakitu);
extern ActorBlueprint A(white_magikoopa);
extern ActorBlueprint A(red_magikoopa);
extern ActorBlueprint A(yellow_magikoopa);
extern ActorBlueprint A(green_magikoopa_flying);
extern ActorBlueprint A(yellow_magikoopa_flying);

Formation A(Formation_00) = {
    ACTOR_BY_IDX(A(lakitu), BTL_POS_AIR_B, 10),
    ACTOR_BY_IDX(A(lakitu), BTL_POS_AIR_C, 9),
};

Formation A(Formation_01) = {
    ACTOR_BY_IDX(A(lakitu), BTL_POS_AIR_A, 10),
    ACTOR_BY_IDX(A(lakitu), BTL_POS_AIR_B, 9),
    ACTOR_BY_IDX(A(lakitu), BTL_POS_AIR_C, 8),
};

Formation A(Formation_02) = {
    ACTOR_BY_IDX(A(lakitu), BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_C, 9),
};

Formation A(Formation_03) = {
    ACTOR_BY_IDX(A(lakitu), BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_C, 8),
};

Formation A(Formation_04) = {
    ACTOR_BY_IDX(A(lakitu), BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_B, 9),
    ACTOR_BY_IDX(A(lakitu), BTL_POS_AIR_C, 8),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_D, 7),
};

Formation A(Formation_05) = {
    ACTOR_BY_IDX(A(lakitu), BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_06) = {
    ACTOR_BY_IDX(A(lakitu), BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_07) = {
    ACTOR_BY_IDX(A(lakitu), BTL_POS_AIR_A, 10),
    ACTOR_BY_IDX(A(lakitu), BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_D, 7),
};

Formation A(Formation_08) = {
    ACTOR_BY_IDX(A(lakitu), BTL_POS_AIR_A, 10),
    ACTOR_BY_IDX(A(lakitu), BTL_POS_AIR_B, 9),
    ACTOR_BY_IDX(A(lakitu), BTL_POS_AIR_C, 8),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_D, 7),
};

Formation A(Formation_09) = {
    ACTOR_BY_IDX(A(lakitu), BTL_POS_AIR_A, 10),
    ACTOR_BY_IDX(A(lakitu), BTL_POS_AIR_B, 9),
    ACTOR_BY_IDX(A(white_magikoopa), BTL_POS_GROUND_C, 8),
};

Formation A(Formation_0A) = {
    ACTOR_BY_IDX(A(lakitu), BTL_POS_AIR_A, 10),
    ACTOR_BY_IDX(A(lakitu), BTL_POS_AIR_B, 9),
    ACTOR_BY_IDX(A(red_magikoopa), BTL_POS_GROUND_C, 8),
};

Formation A(Formation_0B) = {
    ACTOR_BY_IDX(A(lakitu), BTL_POS_AIR_A, 10),
    ACTOR_BY_IDX(A(lakitu), BTL_POS_AIR_B, 9),
    ACTOR_BY_IDX(A(lakitu), BTL_POS_AIR_C, 8),
    ACTOR_BY_IDX(A(yellow_magikoopa), BTL_POS_GROUND_D, 7),
};

Formation A(Formation_0C) = {
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_0D) = {
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_0E) = {
    OVL_ACTOR_BY_IDX("spiny", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
};

Formation A(Formation_0F) = {
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_B, 10),
};

Formation A(Formation_10) = {
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_11) = {
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_12) = {
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_D, 7),
};

Formation A(Formation_13) = {
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_C, 9),
};

Formation A(Formation_14) = {
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_C, 8),
};

Formation A(Formation_15) = {
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_C, 8),
};

Formation A(Formation_16) = {
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("amazy_dayzee", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_17) = {
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_C, 9),
};

Formation A(Formation_18) = {
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_C, 8),
};

Formation A(Formation_19) = {
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_B, 9),
    ACTOR_BY_IDX(A(green_magikoopa_flying), BTL_POS_AIR_C, 8),
};

Formation A(Formation_1A) = {
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_C, 9),
};

Formation A(Formation_1B) = {
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_C, 8),
};

Formation A(Formation_1C) = {
    OVL_ACTOR_BY_IDX("amazy_dayzee", BTL_POS_GROUND_B, 10),
};

Formation A(Formation_1D) = {
    OVL_ACTOR_BY_IDX("amazy_dayzee", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_C, 8),
};

Formation A(Formation_1E) = {
    OVL_ACTOR_BY_IDX("amazy_dayzee", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("amazy_dayzee", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("amazy_dayzee", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("amazy_dayzee", BTL_POS_GROUND_D, 7),
};

Formation A(Formation_1F) = {
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_C, 9),
};

Formation A(Formation_20) = {
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_C, 8),
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_D, 7),
};

Formation A(Formation_21) = {
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_B, 10),
    ACTOR_BY_IDX(A(lakitu), BTL_POS_AIR_C, 9),
};

Formation A(Formation_22) = {
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("bzzap", BTL_POS_AIR_C, 8),
};

Formation A(Formation_23) = {
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("crazee_dayzee", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_24) = {
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("ruff_puff", BTL_POS_AIR_B, 9),
    ACTOR_BY_IDX(A(yellow_magikoopa_flying), BTL_POS_AIR_C, 8),
};

BattleList A(Formations) = {
    BATTLE(A(Formation_00), "flo_01", "ジュゲムx2"),
    BATTLE(A(Formation_01), "flo_01", "ジュゲムx3"),
    BATTLE(A(Formation_02), "flo_01", "ジュゲム,クモクモーン"),
    BATTLE(A(Formation_03), "flo_01", "ジュゲム,ハッチーx２"),
    BATTLE(A(Formation_04), "flo_01", "ジュゲム,ハッチー,ジュゲム,ハッチー"),
    BATTLE(A(Formation_05), "flo_01", "ジュゲム,パンジー"),
    BATTLE(A(Formation_06), "flo_01", "ジュゲム,トゲゾー"),
    BATTLE(A(Formation_07), "flo_01", "ジュゲムx２,トゲゾーx２"),
    BATTLE(A(Formation_08), "flo_01", "ジュゲムx３,トゲゾー"),
    BATTLE(A(Formation_09), "flo_01", "ジュゲムx２,ホワイトカメック"),
    BATTLE(A(Formation_0A), "flo_01", "ジュゲムx２,レッドカメック"),
    BATTLE(A(Formation_0B), "flo_01", "ジュゲムx３,イエローカメック"),
    BATTLE(A(Formation_0C), "flo_01", "トゲゾーx2"),
    BATTLE(A(Formation_0D), "flo_01", "トゲゾーx3"),
    BATTLE(A(Formation_0E), "flo_01", "トゲゾー,パンジーさん,かいふくヘイホー"),
    BATTLE(A(Formation_0F), "flo_01", "パンジーさん"),
    BATTLE(A(Formation_10), "flo_01", "パンジーさんx2"),
    BATTLE(A(Formation_11), "flo_01", "パンジーさんx3"),
    BATTLE(A(Formation_12), "flo_01", "パンジーさんx4"),
    BATTLE(A(Formation_13), "flo_01", "パンジーさん,ハッチー"),
    BATTLE(A(Formation_14), "flo_01", "パンジーさん,ハッチーx2"),
    BATTLE(A(Formation_15), "flo_01", "パンジーさんx2,ハッチー"),
    BATTLE(A(Formation_16), "flo_01", "パンジーさんx2,きらめくパンジーさん"),
    BATTLE(A(Formation_17), "flo_01", "ハッチーx2"),
    BATTLE(A(Formation_18), "flo_01", "ハッチーx3"),
    BATTLE(A(Formation_19), "flo_01", "ハッチーx2,グリーンカメック（そら）"),
    BATTLE(A(Formation_1A), "flo_01", "ハッチー,クモクモーン"),
    BATTLE(A(Formation_1B), "flo_01", "ハッチー,クモクモーン,ハッチー"),
    BATTLE(A(Formation_1C), "flo_01", "きらめくパンジーさん"),
    BATTLE(A(Formation_1D), "flo_01", "きらめくパンジーさん,ハッチーx2"),
    BATTLE(A(Formation_1E), "flo_01", "きらめくパンジーさんx４"),
    BATTLE(A(Formation_1F), "flo_01", "クモクモーンx2"),
    BATTLE(A(Formation_20), "flo_01", "クモクモーンx4"),
    BATTLE(A(Formation_21), "flo_01", "クモクモーン,ジュゲム"),
    BATTLE(A(Formation_22), "flo_01", "クモクモーンx２,ハッチー"),
    BATTLE(A(Formation_23), "flo_01", "クモクモーンx２,パンジー"),
    BATTLE(A(Formation_24), "flo_01", "クモクモーンx２,イエローカメック（そら）"),
    {},
};

StageList A(Stages) = {
    STAGE("flo_01", "flo_01"),
    STAGE("flo_01b", "flo_01b"),
    STAGE("flo_01c", "flo_01c"),
    STAGE("flo_02", "flo_02"),
    STAGE("flo_02b", "flo_02b"),
    STAGE("flo_02c", "flo_02c"),
    STAGE("flo_03", "flo_03"),
    STAGE("flo_04", "flo_04"),
    STAGE("flo_05", "flo_05"),
    STAGE("flo_06", "flo_06"),
    {},
};

BATTLE_AREA_ENTRY = {
    .battles = &A(Formations),
    .stages = &A(Stages),
    .battleCount = ARRAY_COUNT(A(Formations)) - 1,
    .stageCount = ARRAY_COUNT(A(Stages)) - 1,
};
