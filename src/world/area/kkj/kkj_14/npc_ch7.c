#include "kkj_14.h"

AnimID N(LimitAnims_Bowser_Ch7)[] = {
    ANIM_WorldBowser_Still,
    ANIM_WorldBowser_Idle,
    ANIM_WorldBowser_Walk,
    ANIM_WorldBowser_Run,
    ANIM_WorldBowser_Talk,
    ANIM_WorldBowser_TalkEyesClosed,
    ANIM_WorldBowser_AngryTalk,
    ANIM_WorldBowser_Shock,
    ANIM_WorldBowser_Swipe,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Kammy_Ch7)[] = {
    ANIM_WorldKammy_Still,
    ANIM_WorldKammy_Idle,
    ANIM_WorldKammy_Walk,
    ANIM_WorldKammy_Run,
    ANIM_WorldKammy_Talk,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Koopatrol_Ch7)[] = {
    ANIM_WorldKoopatrol_Still,
    ANIM_WorldKoopatrol_Idle,
    ANIM_WorldKoopatrol_Walk,
    ANIM_WorldKoopatrol_Run,
    ANIM_WorldKoopatrol_Lift,
    ANIM_WorldKoopatrol_CarryFast,
    ANIM_WorldKoopatrol_Panic,
    ANIM_LIST_END
};

NpcData N(NpcData_Characters_Ch7)[] = {
    {
        .id = NPC_Ch7_Bowser,
        .pos = { 0.0f, -500.0f, 0.0f },
        .yaw = 270,
        .settings = &N(NpcSettings_Bowser),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
        .drops = NO_DROPS,
        .animations = BOWSER_ANIMS,
        .limitAnimations = N(LimitAnims_Bowser_Ch7),
    },
    {
        .id = NPC_Ch7_Koopatrol_01,
        .pos = { 0.0f, -500.0f, 0.0f },
        .yaw = 0,
        .settings = &N(NpcSettings_Koopatrol),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
        .drops = NO_DROPS,
        .animations = KOOPATROL_ANIMS,
        .limitAnimations = N(LimitAnims_Koopatrol_Ch7),
    },
    {
        .id = NPC_Ch7_Koopatrol_02,
        .pos = { 0.0f, -500.0f, 0.0f },
        .yaw = 0,
        .settings = &N(NpcSettings_Koopatrol),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
        .drops = NO_DROPS,
        .animations = KOOPATROL_ANIMS,
        .limitAnimations = N(LimitAnims_Koopatrol_Ch7),
    },
    {
        .id = NPC_Ch7_Kammy,
        .pos = { 0.0f, -500.0f, 0.0f },
        .yaw = 270,
        .settings = &N(NpcSettings_Kammy),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
        .drops = NO_DROPS,
        .animations = KAMMY_ANIMS,
        .limitAnimations = N(LimitAnims_Kammy_Ch7),
    },
};

NpcGroupList N(Chapter7NPCs) = {
    NPC_GROUP(N(NpcData_Characters_Ch7)),
    {}
};
