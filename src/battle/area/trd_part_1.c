#include "battle/battle.h"

static Formation koopa_troopa_1 = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_B, 10),
};

static Formation koopa_troopa_2 = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_C, 9),
};

static Formation koopa_troopa_3 = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_C, 8),
};

static Formation koopa_troopa_1_bob_omb_1 = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_C, 9),
};

static Formation koopa_troopa_1_bob_omb_2 = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_C, 8),
};

static Formation koopa_troopa_1_bob_omb_3 = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_D, 7),
};

static Formation koopa_troopa_2_bob_omb_1 = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_C, 8),
};

static Formation koopa_troopa_2_bob_omb_2 = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_D, 7),
};

static Formation paratroopa_2 = {
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_C, 9),
};

static Formation paratroopa_3 = {
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_B, 9),
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_C, 8),
};

static Formation paratroopa_1_koopa_troopa_1 = {
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_B, 10),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_C, 9),
};

static Formation paratroopa_1_koopa_troopa_1_paratroopa_1 = {
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_C, 8),
};

static Formation paratroopa_1_koopa_troopa_1_paratroopa_1_koopa_troopa_1 = {
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_C, 8),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_D, 7),
};

static Formation paratroopa_1_bob_omb_2 = {
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_C, 9),
};

static Formation paratroopa_1_bob_omb_3 = {
    OVL_ACTOR_BY_IDX("paratroopa", BTL_POS_AIR_A, 10),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_C, 9),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_D, 8),
};

static Formation bob_omb_1 = {
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_B, 10),
};

static Formation bob_omb_2 = {
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_C, 9),
};

static Formation bob_omb_3 = {
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_C, 8),
};

static Formation bob_omb_4 = {
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_D, 7),
};

static Formation bob_omb_1_koopa_troopa_1 = {
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_C, 9),
};

static Formation bob_omb_2_koopa_troopa_1 = {
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_C, 8),
};

static Formation bob_omb_1_koopa_troopa_2 = {
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_C, 8),
};

static Formation koopa_troopa_1_bob_omb_2_alt = {
    OVL_ACTOR_BY_IDX("koopa_troopa", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bob_omb", BTL_POS_GROUND_C, 8),
};

static Vec3i BlasterPos1 = { 50, 0, -20 };
static Vec3i BlasterPos2 = { 80, 0, 0 };
static Vec3i BlasterPos3 = { 110, 0, 20 };

static Formation bill_blaster_3 = {
    OVL_ACTOR_BY_POS("bill_blaster", BlasterPos1, 10),
    OVL_ACTOR_BY_POS("bill_blaster", BlasterPos2, 9),
    OVL_ACTOR_BY_POS("bill_blaster", BlasterPos3, 9),
};

static Formation bullet_bill_2 = {
    OVL_ACTOR_BY_IDX("bullet_bill", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("bullet_bill", BTL_POS_GROUND_C, 9),
};

static Formation bullet_bill_1 = {
    OVL_ACTOR_BY_IDX("bullet_bill", BTL_POS_GROUND_B, 10),
};

static Formation bullet_bill_3 = {
    OVL_ACTOR_BY_IDX("bullet_bill", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("bullet_bill", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("bullet_bill", BTL_POS_GROUND_C, 8),
};

static BattleList Formations = {
    BATTLE(koopa_troopa_1, "trd_01"),
    BATTLE(koopa_troopa_2, "trd_01"),
    BATTLE(koopa_troopa_3, "trd_01"),
    BATTLE(koopa_troopa_1_bob_omb_1, "trd_01"),
    BATTLE(koopa_troopa_1_bob_omb_2, "trd_01"),
    BATTLE(koopa_troopa_1_bob_omb_3, "trd_01"),
    BATTLE(koopa_troopa_2_bob_omb_1, "trd_01"),
    BATTLE(koopa_troopa_2_bob_omb_2, "trd_01"),
    BATTLE(paratroopa_2, "trd_01"),
    BATTLE(paratroopa_3, "trd_01"),
    BATTLE(paratroopa_1_koopa_troopa_1, "trd_01"),
    BATTLE(paratroopa_1_koopa_troopa_1_paratroopa_1, "trd_01"),
    BATTLE(paratroopa_1_koopa_troopa_1_paratroopa_1_koopa_troopa_1, "trd_01"),
    BATTLE(paratroopa_1_bob_omb_2, "trd_01"),
    BATTLE(paratroopa_1_bob_omb_3, "trd_01"),
    BATTLE(bob_omb_1, "trd_01"),
    BATTLE(bob_omb_2, "trd_01"),
    BATTLE(bob_omb_3, "trd_01"),
    BATTLE(bob_omb_4, "trd_01"),
    BATTLE(bob_omb_1_koopa_troopa_1, "trd_01"),
    BATTLE(bob_omb_2_koopa_troopa_1, "trd_01"),
    BATTLE(bob_omb_1_koopa_troopa_2, "trd_01"),
    BATTLE(koopa_troopa_1_bob_omb_2_alt, "trd_01"),
    BATTLE(bill_blaster_3, "trd_01"),
    BATTLE(bullet_bill_2, "trd_01"),
    BATTLE(bullet_bill_1, "trd_01"),
    BATTLE(bullet_bill_3, "trd_01"),
};

OVL_DEF_BATTLE_AREA(Formations);
