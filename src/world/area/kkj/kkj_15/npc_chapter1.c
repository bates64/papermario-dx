#include "kkj_15.h"

AnimID N(LimitAnims_Bowser_Ch1)[] = {
    ANIM_WorldBowser_Still,
    ANIM_WorldBowser_Idle,
    ANIM_WorldBowser_Walk,
    ANIM_WorldBowser_Talk,
    ANIM_WorldBowser_Shock,
    ANIM_WorldBowser_AngryTalk,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Koopatrol_Ch1)[] = {
    ANIM_WorldKoopatrol_Idle,
    ANIM_WorldKoopatrol_Run,
    ANIM_WorldKoopatrol_Talk,
    ANIM_WorldKoopatrol_Lift,
    ANIM_WorldKoopatrol_CarryFast,
    ANIM_LIST_END
};

NpcData N(NpcData_Characters_Ch1)[] = {
    {
        .id = NPC_Bowser,
        .pos = { 0.0f, -500.0f, 0.0f },
        .yaw = 270,
        .settings = &N(NpcSettings_Bowser),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = BOWSER_ANIMS,
        .limitAnimations = N(LimitAnims_Bowser_Ch1),
    },
    {
        .id = NPC_Kammy,
        .pos = { 0.0f, -500.0f, 0.0f },
        .yaw = 0,
        .settings = &N(NpcSettings_Koopatrol),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = KOOPATROL_ANIMS,
        .limitAnimations = N(LimitAnims_Koopatrol_Ch1),
    },
    {
        .id = NPC_KoopaBros_01,
        .pos = { 0.0f, -500.0f, 0.0f },
        .yaw = 0,
        .settings = &N(NpcSettings_Koopatrol),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = KOOPATROL_ANIMS,
        .limitAnimations = N(LimitAnims_Koopatrol_Ch1),
    },
};

NpcGroupList N(Chapter1NPCs) = {
    NPC_GROUP(N(NpcData_Characters_Ch1)),
    {}
};
