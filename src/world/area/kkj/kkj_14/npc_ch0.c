#include "kkj_14.h"

#define NAME_SUFFIX _Ch0

#include "world/common/npc/Bowser/idle.inc.c"
#include "world/common/enemy/Kammy/idle.inc.c"

AnimID N(LimitAnims_Bowser)[] = {
    ANIM_WorldBowser_Still,
    ANIM_WorldBowser_Idle,
    ANIM_WorldBowser_BrandishIdle,
    ANIM_WorldBowser_Walk,
    ANIM_WorldBowser_Talk,
    ANIM_WorldBowser_TalkEyesClosed,
    ANIM_WorldBowser_BrandishTalk,
    ANIM_WorldBowser_Brandish,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Kammy)[] = {
    ANIM_WorldKammy_Anim01,
    ANIM_WorldKammy_Anim02,
    ANIM_WorldKammy_Anim04,
    ANIM_LIST_END
};

NpcData N(NpcData_Characters)[] = {
    {
        .id = NPC_Bowser,
        .pos = { 0.0f, -500.0f, 0.0f },
        .yaw = 270,
        .settings = &N(NpcSettings_Bowser),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = BOWSER_ANIMS,
        .limitAnimations = N(LimitAnims_Bowser),
    },
    {
        .id = NPC_Kammy,
        .pos = { 0.0f, -500.0f, 0.0f },
        .yaw = 270,
        .settings = &N(NpcSettings_Kammy),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = KAMMY_ANIMS,
        .limitAnimations = N(LimitAnims_Kammy),
    },
};

#define NAME_SUFFIX

NpcGroupList N(Chapter0NPCs) = {
    NPC_GROUP(N(NpcData_Characters_Ch0)),
    {}
};
