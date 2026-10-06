#include "kkj_14.h"

AnimID LimitAnims_Bowser_Ch2[] = {
    ANIM_WorldBowser_Still,
    ANIM_WorldBowser_Idle,
    ANIM_WorldBowser_Walk,
    ANIM_WorldBowser_Run,
    ANIM_WorldBowser_Talk,
    ANIM_WorldBowser_TalkEyesClosed,
    ANIM_WorldBowser_ArmsCrossed,
    ANIM_WorldBowser_Shock,
    ANIM_LIST_END
};

AnimID LimitAnims_Kammy_Ch2[] = {
    ANIM_WorldKammy_Idle,
    ANIM_WorldKammy_Walk,
    ANIM_WorldKammy_Run,
    ANIM_WorldKammy_Talk,
    ANIM_LIST_END
};

NpcData NpcData_Characters_Ch2[] = {
    {
        .id = NPC_Bowser,
        .pos = { 0.0f, -500.0f, 0.0f },
        .yaw = 270,
        .settings = &NpcSettings_Bowser,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = BOWSER_ANIMS,
        .limitAnimations = LimitAnims_Bowser_Ch2,
    },
    {
        .id = NPC_Kammy,
        .pos = { 0.0f, -500.0f, 0.0f },
        .yaw = 270,
        .settings = &NpcSettings_Kammy,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = KAMMY_ANIMS,
        .limitAnimations = LimitAnims_Kammy_Ch2,
    },
};

NpcGroupList Chapter2NPCs = {
    NPC_GROUP(NpcData_Characters_Ch2),
    {}
};
