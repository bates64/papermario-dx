#include "area.h"

extern ActorBlueprint A(tubba_blubba);

extern EvtScript A(dig_01_script);
extern EvtScript A(dig_02_script);
extern EvtScript A(dig_03_script);
extern EvtScript A(dig_04_script);
extern EvtScript A(dig_05_script);

Formation A(Formation_00) = {
    OVL_ACTOR_BY_IDX("fuzzy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("fuzzy", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("fuzzy", BTL_POS_GROUND_D, 7),
};

Formation A(Formation_01) = {
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_C, 9),
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_D, 8),
};

Formation A(Formation_02) = {
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_C, 9),
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_D, 8),
};

Formation A(Formation_03) = {
    OVL_ACTOR_BY_IDX("red_shy_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("red_shy_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("red_shy_guy", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("red_shy_guy", BTL_POS_GROUND_D, 7),
};

Formation A(Formation_04) = {
    ACTOR_BY_IDX(A(tubba_blubba), BTL_POS_GROUND_C, 10),
};

BattleList A(Formations) = {
    BATTLE_WITH_SCRIPT(A(Formation_00), "nok_04", A(dig_01_script), "ダイジェスト０１"),
    BATTLE_WITH_SCRIPT(A(Formation_01), "iwa_01b", A(dig_02_script), "ダイジェスト０２"),
    BATTLE_WITH_SCRIPT(A(Formation_02), "sbk_02", A(dig_03_script), "ダイジェスト０３"),
    BATTLE_WITH_SCRIPT(A(Formation_03), "omo_04", A(dig_04_script), "ダイジェスト０４"),
    BATTLE_WITH_SCRIPT(A(Formation_04), "dgb_05", A(dig_05_script), "ダイジェスト０５"),
    {},
};

StageList A(Stages) = {
    STAGE("dig_01", "nok_04"),
    STAGE("dig_02", "iwa_01b"),
    STAGE("dig_03", "sbk_02"),
    STAGE("dig_04", "omo_04"),
    STAGE("dig_05", "dgb_05"),
    {},
};
