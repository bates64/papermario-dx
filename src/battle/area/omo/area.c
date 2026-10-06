#include "area.h"

extern ActorBlueprint A(anti_guy);
extern ActorBlueprint A(groove_guy);

Formation A(Formation_00) = {
    OVL_ACTOR_BY_IDX("red_shy_guy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("red_shy_guy", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_01) = {
    OVL_ACTOR_BY_IDX("blue_shy_guy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("blue_shy_guy", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_02) = {
    OVL_ACTOR_BY_IDX("yellow_shy_guy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("yellow_shy_guy", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_03) = {
    OVL_ACTOR_BY_IDX("yellow_shy_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("yellow_shy_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("yellow_shy_guy", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_04) = {
    OVL_ACTOR_BY_IDX("pink_shy_guy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("pink_shy_guy", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_05) = {
    OVL_ACTOR_BY_IDX("green_shy_guy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("green_shy_guy", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_06) = {
    OVL_ACTOR_BY_IDX("red_shy_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
};

Formation A(Formation_07) = {
    OVL_ACTOR_BY_IDX("blue_shy_guy", BTL_POS_GROUND_A, 10),
    ACTOR_BY_IDX(A(groove_guy), BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
};

Formation A(Formation_08) = {
    OVL_ACTOR_BY_IDX("yellow_shy_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
};

Formation A(Formation_09) = {
    OVL_ACTOR_BY_IDX("yellow_shy_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("green_shy_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("red_shy_guy", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("blue_shy_guy", BTL_POS_GROUND_D, 7),
};

Formation A(Formation_0A) = {
    OVL_ACTOR_BY_IDX("pink_shy_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
};

Formation A(Formation_0B) = {
    OVL_ACTOR_BY_IDX("pink_shy_guy", BTL_POS_GROUND_A, 10),
    ACTOR_BY_IDX(A(groove_guy), BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_D, 7),
};

Formation A(Formation_0C) = {
    OVL_ACTOR_BY_IDX("green_shy_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("sky_guy", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
};

Formation A(Formation_0D) = {
    OVL_ACTOR_BY_IDX("sky_guy", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("sky_guy", BTL_POS_AIR_C, 9),
};

Formation A(Formation_0E) = {
    OVL_ACTOR_BY_IDX("sky_guy", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("yellow_shy_guy", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_0F) = {
    OVL_ACTOR_BY_IDX("sky_guy", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("sky_guy", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("yellow_shy_guy", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_10) = {
    OVL_ACTOR_BY_IDX("sky_guy", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 9),
};

Formation A(Formation_11) = {
    OVL_ACTOR_BY_IDX("sky_guy", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("sky_guy", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_12) = {
    OVL_ACTOR_BY_IDX("sky_guy", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("green_shy_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
};

Formation A(Formation_13) = {
    OVL_ACTOR_BY_IDX("sky_guy", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("green_shy_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_D, 7),
};

Formation A(Formation_14) = {
    OVL_ACTOR_BY_IDX("sky_guy", BTL_POS_AIR_A, 10),
    ACTOR_BY_IDX(A(groove_guy), BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
};

Formation A(Formation_15) = {
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_16) = {
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_17) = {
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 9),
};

Formation A(Formation_18) = {
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
};

Formation A(Formation_19) = {
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_D, 7),
};

Formation A(Formation_1A) = {
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_D, 7),
};

Formation A(Formation_1B) = {
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_B, 9),
    ACTOR_BY_IDX(A(groove_guy), BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_D, 7),
};

Formation A(Formation_1C) = {
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_1D) = {
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_1E) = {
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 9),
};

Formation A(Formation_1F) = {
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
};

Formation A(Formation_20) = {
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_D, 7),
};

Formation A(Formation_21) = {
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_A, 10),
    ACTOR_BY_IDX(A(groove_guy), BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_22) = {
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_B, 9),
    ACTOR_BY_IDX(A(groove_guy), BTL_POS_GROUND_C, 8),
};

Formation A(Formation_23) = {
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_A, 10),
    ACTOR_BY_IDX(A(groove_guy), BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_D, 7),
};

Formation A(Formation_24) = {
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("spy_guy", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_25) = {
    ACTOR_BY_IDX(A(groove_guy), BTL_POS_GROUND_B, 10),
    ACTOR_BY_IDX(A(groove_guy), BTL_POS_GROUND_C, 9),
};

Formation A(Formation_26) = {
    ACTOR_BY_IDX(A(groove_guy), BTL_POS_GROUND_A, 10),
    ACTOR_BY_IDX(A(groove_guy), BTL_POS_GROUND_B, 9),
    ACTOR_BY_IDX(A(groove_guy), BTL_POS_GROUND_C, 8),
};

Formation A(Formation_27) = {
    ACTOR_BY_IDX(A(groove_guy), BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
};

Formation A(Formation_28) = {
    ACTOR_BY_IDX(A(groove_guy), BTL_POS_GROUND_A, 10),
    ACTOR_BY_IDX(A(groove_guy), BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
};

Formation A(Formation_29) = {
    ACTOR_BY_IDX(A(groove_guy), BTL_POS_GROUND_A, 10),
    ACTOR_BY_IDX(A(groove_guy), BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_C, 8),
    OVL_ACTOR_BY_IDX("medi_guy", BTL_POS_AIR_D, 7),
};

Formation A(Formation_2A) = {
    ACTOR_BY_IDX(A(groove_guy), BTL_POS_GROUND_A, 10),
    ACTOR_BY_IDX(A(groove_guy), BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("pyro_guy", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_2B) = {
    ACTOR_BY_IDX(A(groove_guy), BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("blue_shy_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("sky_guy", BTL_POS_AIR_C, 8),
};

Formation A(Formation_2C) = {
    ACTOR_BY_IDX(A(anti_guy), BTL_POS_GROUND_B, 10),
};

BattleList A(Formations) = {
    BATTLE(A(Formation_00), "omo_04", "あかx２"),
    BATTLE(A(Formation_01), "omo_04", "あおx２"),
    BATTLE(A(Formation_02), "omo_04", "きいろx２"),
    BATTLE(A(Formation_03), "omo_04", "きいろx３"),
    BATTLE(A(Formation_04), "omo_04", "ももx２"),
    BATTLE(A(Formation_05), "omo_04", "みどりx２"),
    BATTLE(A(Formation_06), "omo_04", "あか,かいふくx２"),
    BATTLE(A(Formation_07), "omo_04", "あお,ダンシング,かいふく"),
    BATTLE(A(Formation_08), "omo_04", "きいろ,コマンド,かいふく"),
    BATTLE(A(Formation_09), "omo_04", "きいろ,みどり,あか,あお"),
    BATTLE(A(Formation_0A), "omo_04", "もも,ファイア,かいふく"),
    BATTLE(A(Formation_0B), "omo_04", "もも,ダンシング,かいふくx２"),
    BATTLE(A(Formation_0C), "omo_04", "みどり,バルーン,かいふく"),
    BATTLE(A(Formation_0D), "omo_04", "バルーンx２"),
    BATTLE(A(Formation_0E), "omo_04", "バルーン,きいろ"),
    BATTLE(A(Formation_0F), "omo_04", "バルーンx２,きいろ"),
    BATTLE(A(Formation_10), "omo_04", "バルーン,かいふく"),
    BATTLE(A(Formation_11), "omo_04", "バルーンx２,コマンド"),
    BATTLE(A(Formation_12), "omo_04", "バルーン,みどり,かいふく"),
    BATTLE(A(Formation_13), "omo_04", "バルーン,みどり,かいふくx２"),
    BATTLE(A(Formation_14), "omo_04", "バルーン,ダンシング,かいふく"),
    BATTLE(A(Formation_15), "omo_04", "コマンドx２"),
    BATTLE(A(Formation_16), "omo_04", "コマンド,ファイア"),
    BATTLE(A(Formation_17), "omo_04", "コマンド,かいふく"),
    BATTLE(A(Formation_18), "omo_04", "コマンドx２,かいふく"),
    BATTLE(A(Formation_19), "omo_04", "コマンドx３,かいふく"),
    BATTLE(A(Formation_1A), "omo_04", "コマンドx４"),
    BATTLE(A(Formation_1B), "omo_04", "コマンド,ファイア,ダンシング,かいふく"),
    BATTLE(A(Formation_1C), "omo_04", "ファイアx２"),
    BATTLE(A(Formation_1D), "omo_04", "ファイアx３"),
    BATTLE(A(Formation_1E), "omo_04", "ファイア,かいふく"),
    BATTLE(A(Formation_1F), "omo_04", "ファイアx２,かいふく"),
    BATTLE(A(Formation_20), "omo_04", "ファイアx２,かいふくx２"),
    BATTLE(A(Formation_21), "omo_04", "ファイア,ダンシング,ファイア"),
    BATTLE(A(Formation_22), "omo_04", "ファイア,コマンド,ダンシング"),
    BATTLE(A(Formation_23), "omo_04", "ファイア,ダンシング,かいふくx2"),
    BATTLE(A(Formation_24), "omo_04", "ファイアx2,コマンド"),
    BATTLE(A(Formation_25), "omo_04", "ダンシングx２"),
    BATTLE(A(Formation_26), "omo_04", "ダンシングx３"),
    BATTLE(A(Formation_27), "omo_04", "ダンシング,かいふくx２"),
    BATTLE(A(Formation_28), "omo_04", "ダンシングx２,かいふく"),
    BATTLE(A(Formation_29), "omo_04", "ダンシングx２,かいふくx２"),
    BATTLE(A(Formation_2A), "omo_04", "ダンシングx２,ファイアー"),
    BATTLE(A(Formation_2B), "omo_04", "ダンシング,あお,バルーン"),
    BATTLE(A(Formation_2C), "omo_04", "ブラック"),
    {},
};

StageList A(Stages) = {
    STAGE("omo_01", "omo_01"),
    STAGE("omo_02", "omo_02"),
    STAGE("omo_03", "omo_03"),
    STAGE("omo_03b", "omo_03b"),
    STAGE("omo_04", "omo_04"),
    STAGE("omo_05", "omo_05"),
    STAGE("omo_05b", "omo_05b"),
    STAGE("omo_06", "omo_06"),
    STAGE("omo_07", "omo_07"),
    {},
};
