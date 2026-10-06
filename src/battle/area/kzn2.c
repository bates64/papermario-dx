#include "battle/battle.h"
#include "ld_addrs.h"
#include "battle/common/lava_piranha.h"

static Vec3i lava_piranha_pos = { 60, 60, 0 };

static Formation lava_piranha = {
    OVL_ACTOR_BY_POS("lava_piranha", lava_piranha_pos, 60),
};

static Vec3i petit_piranha_pos1 = { 40, 60, 0 };
static Vec3i petit_piranha_pos2 = { 80, 60, 0 };

static Formation petit_piranha = {
    OVL_ACTOR_BY_POS("petit_piranha", petit_piranha_pos1, 10),
    OVL_ACTOR_BY_POS("petit_piranha", petit_piranha_pos2, 10),
};

static BattleList Formations = {
    BATTLE(lava_piranha, "kzn_05"),
    BATTLE(petit_piranha, "kzn_05"),
    {},
};

#define PIRANHA_DMA_ENTRY(name) \
    { world_model_anim_kzn_##name##_ROM_START,\
      world_model_anim_kzn_##name##_ROM_END,\
      world_model_anim_kzn_##name##_VRAM }

static DmaTable dmaTable[] = {
    [VINE_ANIM_BOSS_IDLE]                   PIRANHA_DMA_ENTRY(00),
    [VINE_ANIM_BOSS_TWITCH]                 PIRANHA_DMA_ENTRY(01),
    [VINE_ANIM_BOSS_ATTACK]                 PIRANHA_DMA_ENTRY(02),
    [VINE_ANIM_BOSS_POST_ATTACK]            PIRANHA_DMA_ENTRY(03),
    [VINE_ANIM_BOSS_STUNNED_HEAVY_HIT]      PIRANHA_DMA_ENTRY(04),
    [VINE_ANIM_BOSS_STUNNED_LIGHT_HIT]      PIRANHA_DMA_ENTRY(05),
    [VINE_ANIM_BOSS_HEAVY_HIT]              PIRANHA_DMA_ENTRY(06),
    [VINE_ANIM_BOSS_LIGHT_HIT]              PIRANHA_DMA_ENTRY(07),
    [VINE_ANIM_BOSS_STUNNED_DEATH_BEGIN]    PIRANHA_DMA_ENTRY(08),
    [VINE_ANIM_BOSS_DEATH_BEGIN]            PIRANHA_DMA_ENTRY(09),
    [VINE_ANIM_BOSS_DEATH_MIDDLE]           PIRANHA_DMA_ENTRY(0A),
    [VINE_ANIM_BOSS_DEATH_COLLAPSE]         PIRANHA_DMA_ENTRY(0B),
    [VINE_ANIM_BOSS_EMERGE]                 PIRANHA_DMA_ENTRY(0C),
    [VINE_ANIM_BOSS_STUN]                   PIRANHA_DMA_ENTRY(0D),
    [VINE_ANIM_BOSS_RECOVER]                PIRANHA_DMA_ENTRY(0E),
    [VINE_ANIM_BOSS_DUP_EMERGE]             PIRANHA_DMA_ENTRY(0F),
    [VINE_ANIM_BOSS_SINK_AWAY]              PIRANHA_DMA_ENTRY(10),
    [VINE_ANIM_BOSS_TALK]                   PIRANHA_DMA_ENTRY(11),
    [VINE_ANIM_BUD_ATTACK]                  PIRANHA_DMA_ENTRY(12),
    [VINE_ANIM_BUD_STUNNED_HEAVY_HIT]       PIRANHA_DMA_ENTRY(13),
    [VINE_ANIM_BUD_STUNNED_LIGHT_HIT]       PIRANHA_DMA_ENTRY(14),
    [VINE_ANIM_BUD_HEAVY_HIT]               PIRANHA_DMA_ENTRY(15),
    [VINE_ANIM_BUD_LIGHT_HIT]               PIRANHA_DMA_ENTRY(16),
    [VINE_ANIM_BUD_STUNNED_DEATH_BEGIN]     PIRANHA_DMA_ENTRY(17),
    [VINE_ANIM_BUD_DEATH_BEGIN]             PIRANHA_DMA_ENTRY(18),
    [VINE_ANIM_BUD_DEATH_MIDDLE]            PIRANHA_DMA_ENTRY(19),
    [VINE_ANIM_BUD_DEATH_COLLAPSE]          PIRANHA_DMA_ENTRY(1A),
    [VINE_ANIM_BUD_STUN]                    PIRANHA_DMA_ENTRY(1B),
    [VINE_ANIM_BUD_EMERGE]                  PIRANHA_DMA_ENTRY(1C),
    [VINE_ANIM_BUD_RECOVER]                 PIRANHA_DMA_ENTRY(1D),
    [VINE_ANIM_BUD_TWITCH]                  PIRANHA_DMA_ENTRY(1E),
    [VINE_ANIM_BUD_IDLE]                    PIRANHA_DMA_ENTRY(1F),
    [VINE_ANIM_BUD_DUP_EMERGE]              PIRANHA_DMA_ENTRY(20),
    [VINE_ANIM_BUD_SINK_AWAY]               PIRANHA_DMA_ENTRY(21),
    [VINE_ANIM_EXTRA_IDLE]                  PIRANHA_DMA_ENTRY(22),
    [VINE_ANIM_EXTRA_DEATH]                 PIRANHA_DMA_ENTRY(23),
    [VINE_ANIM_EXTRA_EMERGE]                PIRANHA_DMA_ENTRY(24),
};

BATTLE_AREA_ENTRY = {
    .battles = &Formations,
    .battleCount = ARRAY_COUNT(Formations) - 1,
    .dmaTable = dmaTable,
    .dmaCount = ARRAY_COUNT(dmaTable),
};
