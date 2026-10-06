#include "area.h"

extern ActorBlueprint A(magikoopa);
extern ActorBlueprint A(magikoopa_flying);

Formation A(Formation_00) = {
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_B, 10, 1),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_01) = {
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_A, 10, 1),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_02) = {
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_A, 10, 1),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_03) = {
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_A, 10, 1),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_04) = {
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_A, 10, 1),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_B, 9),
    ACTOR_BY_IDX(A(magikoopa), BTL_POS_GROUND_C, 8),
};

Formation A(Formation_05) = {
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_A, 10, 1),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_C, 8),
    ACTOR_BY_IDX(A(magikoopa), BTL_POS_GROUND_D, 7),
};

Formation A(Formation_06) = {
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_A, 10, 1),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_C, 8),
    ACTOR_BY_IDX(A(magikoopa), BTL_POS_GROUND_D, 7),
};

Formation A(Formation_07) = {
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_08) = {
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_09) = {
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_D, 7),
};

Formation A(Formation_0A) = {
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("ember", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("ember", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("ember", BTL_POS_GROUND_D, 7),
};

Formation A(Formation_0B) = {
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_B, 9),
    ACTOR_BY_IDX(A(magikoopa), BTL_POS_GROUND_C, 8),
};

Formation A(Formation_0C) = {
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_0D) = {
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_0E) = {
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_D, 7),
};

Formation A(Formation_0F) = {
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_10) = {
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_11) = {
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_12) = {
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_13) = {
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_14) = {
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_C, 8),
    ACTOR_BY_IDX(A(magikoopa), BTL_POS_GROUND_D, 9),
};

Formation A(Formation_15) = {
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_B, 9),
    ACTOR_BY_IDX(A(magikoopa_flying), BTL_POS_AIR_C, 8),
};

Formation A(Formation_16) = {
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_C, 8),
    ACTOR_BY_IDX(A(magikoopa_flying), BTL_POS_AIR_D, 9),
};

Formation A(Formation_17) = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 10),
};

Formation A(Formation_18) = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_19) = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_1A) = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_D, 7),
};

Formation A(Formation_1B) = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_1C) = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_D, 7),
};

Vec3i A(Formation_1D_pos1) = { 5, 0, -20 };

Vec3i A(Formation_1D_pos2) = { 45, 0, -10 };

Vec3i A(Formation_1D_pos3) = { 85, 0, 0 };

Vec3i A(Formation_1D_pos4) = { 125, 0, 5 };

Formation A(Formation_1D) = {
    OVL_ACTOR_BY_POS("koopatrol", A(Formation_1D_pos1), 10),
    OVL_ACTOR_BY_POS("koopatrol", A(Formation_1D_pos2), 9),
    OVL_ACTOR_BY_POS("koopatrol", A(Formation_1D_pos3), 8),
    ACTOR_BY_POS(A(magikoopa), A(Formation_1D_pos4), 7),
};

Formation A(Formation_1E) = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 9),
    ACTOR_BY_IDX(A(magikoopa), BTL_POS_GROUND_C, 8),
    ACTOR_BY_IDX(A(magikoopa), BTL_POS_GROUND_D, 7),
};

Formation A(Formation_1F) = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_B, 9),
    ACTOR_BY_IDX(A(magikoopa), BTL_POS_GROUND_C, 8),
    ACTOR_BY_IDX(A(magikoopa), BTL_POS_GROUND_D, 7),
};

Formation A(Formation_20) = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_21) = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_22) = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_23) = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_24) = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_25) = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 9),
    ACTOR_BY_IDX(A(magikoopa), BTL_POS_GROUND_C, 8),
    ACTOR_BY_IDX(A(magikoopa_flying), BTL_POS_AIR_D, 7),
};

Formation A(Formation_26) = {
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_A, 10),
    ACTOR_BY_IDX(A(magikoopa), BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_C, 8),
    ACTOR_BY_IDX(A(magikoopa), BTL_POS_GROUND_D, 7),
};

Formation A(Formation_27) = {
    ACTOR_BY_IDX(A(magikoopa), BTL_POS_GROUND_B, 10),
    ACTOR_BY_IDX(A(magikoopa), BTL_POS_GROUND_C, 9),
};

Formation A(Formation_28) = {
    ACTOR_BY_IDX(A(magikoopa), BTL_POS_GROUND_A, 10),
    ACTOR_BY_IDX(A(magikoopa), BTL_POS_GROUND_B, 9),
    ACTOR_BY_IDX(A(magikoopa), BTL_POS_GROUND_C, 8),
};

Formation A(Formation_29) = {
    ACTOR_BY_IDX(A(magikoopa), BTL_POS_GROUND_A, 10),
    ACTOR_BY_IDX(A(magikoopa_flying), BTL_POS_AIR_B, 9),
    ACTOR_BY_IDX(A(magikoopa_flying), BTL_POS_AIR_C, 8),
};

Formation A(Formation_2A) = {
    ACTOR_BY_IDX(A(magikoopa), BTL_POS_GROUND_A, 10),
    ACTOR_BY_IDX(A(magikoopa), BTL_POS_GROUND_B, 9),
    ACTOR_BY_IDX(A(magikoopa_flying), BTL_POS_AIR_C, 8),
    ACTOR_BY_IDX(A(magikoopa_flying), BTL_POS_AIR_D, 7),
};

Formation A(Formation_2B) = {
    ACTOR_BY_IDX(A(magikoopa), BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_D, 7),
};

Formation A(Formation_2C) = {
    ACTOR_BY_IDX(A(magikoopa), BTL_POS_GROUND_A, 10),
    ACTOR_BY_IDX(A(magikoopa), BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_2D) = {
    ACTOR_BY_IDX(A(magikoopa), BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_B, 9),
    ACTOR_BY_IDX(A(magikoopa), BTL_POS_GROUND_C, 8),
};

Formation A(Formation_2E) = {
    ACTOR_BY_IDX(A(magikoopa), BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bony_beetle", BTL_POS_GROUND_C, 8),
    ACTOR_BY_IDX(A(magikoopa), BTL_POS_GROUND_D, 7),
};

Formation A(Formation_2F) = {
    ACTOR_BY_IDX(A(magikoopa), BTL_POS_GROUND_A, 10),
    ACTOR_BY_IDX(A(magikoopa), BTL_POS_GROUND_B, 9),
    ACTOR_BY_IDX(A(magikoopa_flying), BTL_POS_AIR_C, 8),
};

Formation A(Formation_30) = {
    ACTOR_BY_IDX(A(magikoopa), BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 9),
    ACTOR_BY_IDX(A(magikoopa), BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_D, 7),
};

Formation A(Formation_31) = {
    ACTOR_BY_IDX(A(magikoopa_flying), BTL_POS_AIR_B, 10),
    ACTOR_BY_IDX(A(magikoopa_flying), BTL_POS_AIR_C, 9),
};

Formation A(Formation_32) = {
    ACTOR_BY_IDX(A(magikoopa_flying), BTL_POS_AIR_A, 10),
    ACTOR_BY_IDX(A(magikoopa_flying), BTL_POS_AIR_B, 9),
    ACTOR_BY_IDX(A(magikoopa_flying), BTL_POS_AIR_C, 8),
};

Formation A(Formation_33) = {
    ACTOR_BY_IDX(A(magikoopa_flying), BTL_POS_AIR_A, 10),
    ACTOR_BY_IDX(A(magikoopa), BTL_POS_GROUND_B, 9),
    ACTOR_BY_IDX(A(magikoopa_flying), BTL_POS_AIR_C, 8),
    ACTOR_BY_IDX(A(magikoopa), BTL_POS_GROUND_D, 7),
};

Formation A(Formation_34) = {
    ACTOR_BY_IDX(A(magikoopa_flying), BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_35) = {
    ACTOR_BY_IDX(A(magikoopa_flying), BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_C, 9),
};

Formation A(Formation_36) = {
    ACTOR_BY_IDX(A(magikoopa_flying), BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("dry_bones", BTL_POS_GROUND_C, 8),
};

Formation A(Formation_37) = {
    ACTOR_BY_IDX(A(magikoopa_flying), BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("koopatrol", BTL_POS_GROUND_B, 10),
    ACTOR_BY_IDX(A(magikoopa_flying), BTL_POS_AIR_C, 9),
};

Formation A(Formation_38) = {
    ACTOR_BY_IDX(A(magikoopa_flying), BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("hammer_bro", BTL_POS_GROUND_C, 8),
    ACTOR_BY_IDX(A(magikoopa_flying), BTL_POS_AIR_D, 7),
};

BattleList A(Formations) = {
    BATTLE(A(Formation_00), "kpa_01", "ホネメットx２"),
    BATTLE(A(Formation_01), "kpa_01", "ホネメットx３"),
    BATTLE(A(Formation_02), "kpa_01", "ホネメット,カロンx２"),
    BATTLE(A(Formation_03), "kpa_01", "ホネメットx２,カロン"),
    BATTLE(A(Formation_04), "kpa_01", "ホネメットx２,カメック"),
    BATTLE(A(Formation_05), "kpa_01", "ホネメットx３,カメック"),
    BATTLE(A(Formation_06), "kpa_01", "ホネメット,カロン,ホネメット,カメック"),
    BATTLE(A(Formation_07), "kpa_01", "カロンx２"),
    BATTLE(A(Formation_08), "kpa_01", "カロンx３"),
    BATTLE(A(Formation_09), "kpa_01", "カロンx４"),
    BATTLE(A(Formation_0A), "kpa_01", "カロン,エルモスx３"),
    BATTLE(A(Formation_0B), "kpa_01", "カロンx２,カメック"),
    BATTLE(A(Formation_0C), "kpa_01", "カロン,トゲノコx２"),
    BATTLE(A(Formation_0D), "kpa_01", "カロンx２,ホネメット"),
    BATTLE(A(Formation_0E), "kpa_01", "カロンx２,ホネメットx２"),
    BATTLE(A(Formation_0F), "kpa_01", "ハンマーブロスx２"),
    BATTLE(A(Formation_10), "kpa_01", "ハンマーブロスx３"),
    BATTLE(A(Formation_11), "kpa_01", "ハンマーブロス,トゲノコ"),
    BATTLE(A(Formation_12), "kpa_01", "ハンマーブロスx２,トゲノコ"),
    BATTLE(A(Formation_13), "kpa_01", "ハンマーブロス,トゲノコx２"),
    BATTLE(A(Formation_14), "kpa_01", "ハンマーブロス,カロン,ハンンマーブロス,カメック"),
    BATTLE(A(Formation_15), "kpa_01", "ハンマーブロスx２,くうちゅうカメック"),
    BATTLE(A(Formation_16), "kpa_01", "ハンマーブロスx３,くうちゅうカメック"),
    BATTLE(A(Formation_17), "kpa_01", "トゲノコ"),
    BATTLE(A(Formation_18), "kpa_01", "トゲノコx２"),
    BATTLE(A(Formation_19), "kpa_01", "トゲノコx３"),
    BATTLE(A(Formation_1A), "kpa_01", "トゲノコx４"),
    BATTLE(A(Formation_1B), "kpa_01", "トゲノコ,ハンマーブロス"),
    BATTLE(A(Formation_1C), "kpa_01", "トゲノコ,ハンマーブロス,トゲノコ,ハンマーブロス"),
    BATTLE(A(Formation_1D), "kpa_01", "トゲノコx３,カメック"),
    BATTLE(A(Formation_1E), "kpa_01", "トゲノコx２,カメックx２"),
    BATTLE(A(Formation_20), "kpa_01", "トゲノコ,ホネメット"),
    BATTLE(A(Formation_21), "kpa_01", "トゲノコx２,ホネメット"),
    BATTLE(A(Formation_22), "kpa_01", "トゲノコ,ホネメットx２"),
    BATTLE(A(Formation_23), "kpa_01", "トゲノコ,ホネメット,トゲノコ"),
    BATTLE(A(Formation_24), "kpa_01", "トゲノコ,カロンx２"),
    BATTLE(A(Formation_25), "kpa_01", "トゲノコx２,カメック,くうちゅうカメック"),
    BATTLE(A(Formation_26), "kpa_01", "トゲノコ,カメック,トゲノコ,カメック"),
    BATTLE(A(Formation_27), "kpa_01", "カメックx２"),
    BATTLE(A(Formation_28), "kpa_01", "カメックx３"),
    BATTLE(A(Formation_29), "kpa_01", "カメック,くうちゅうカメックx２"),
    BATTLE(A(Formation_2A), "kpa_01", "カメックx２,くうちゅうカメックx２"),
    BATTLE(A(Formation_2B), "kpa_01", "カメック,トゲノコx３"),
    BATTLE(A(Formation_2C), "kpa_01", "カメックx２,カロン"),
    BATTLE(A(Formation_2D), "kpa_01", "カメック,ホネメット,カメック"),
    BATTLE(A(Formation_2E), "kpa_01", "カメック,ホネメットx２,カメック"),
    BATTLE(A(Formation_2F), "kpa_01", "カメックx２,くうちゅうカメック"),
    BATTLE(A(Formation_30), "kpa_01", "カメック,トゲノコ,カメック,トゲノコ"),
    BATTLE(A(Formation_31), "kpa_01", "くうちゅうカメックx２"),
    BATTLE(A(Formation_32), "kpa_01", "くうちゅうカメックx３"),
    BATTLE(A(Formation_33), "kpa_01", "くうちゅうカメック,カメック,くうちゅうカメック,カメック"),
    BATTLE(A(Formation_34), "kpa_01", "くうちゅうカメック,トゲノコx２"),
    BATTLE(A(Formation_35), "kpa_01", "くうちゅうカメック,ハンマーブロス"),
    BATTLE(A(Formation_36), "kpa_01", "くうちゅうカメック,カロンx２"),
    BATTLE(A(Formation_37), "kpa_01", "くうちゅうカメック,トゲノコ,くうちゅうカメック"),
    BATTLE(A(Formation_38), "kpa_01", "くうちゅうカメック,ハンマーブロスx２,くうちゅうカメック"),
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
