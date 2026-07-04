#include "kkj_14.h"

AnimID N(LimitAnims_Bowser_Ch0)[] = {
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

AnimID N(LimitAnims_Kammy_Ch0)[] = {
    ANIM_WorldKammy_Idle,
    ANIM_WorldKammy_Walk,
    ANIM_WorldKammy_Talk,
    ANIM_LIST_END
};

NpcData N(NpcData_Characters_Ch0)[] = {
    {
        .id = NPC_Bowser,
        .pos = { 0.0f, -500.0f, 0.0f },
        .yaw = 270,
        .settings = &N(NpcSettings_Bowser),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = BOWSER_ANIMS,
        .limitAnimations = N(LimitAnims_Bowser_Ch0),
    },
    {
        .id = NPC_Kammy,
        .pos = { 0.0f, -500.0f, 0.0f },
        .yaw = 270,
        .settings = &N(NpcSettings_Kammy),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = KAMMY_ANIMS,
        .limitAnimations = N(LimitAnims_Kammy_Ch0),
    },
};

NpcGroupList N(Chapter0NPCs) = {
    NPC_GROUP(N(NpcData_Characters_Ch0)),
    {}
};
