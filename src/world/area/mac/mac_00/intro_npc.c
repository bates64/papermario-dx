#include "mac_00.h"

#include "world/common/npc/Chan/idle.inc.c"
#include "world/common/npc/Lee/idle.inc.c"

EvtScript N(EVS_NpcInit_Chan_Intro) = {
    Call(SetNpcPos, NPC_SELF, 570, 20, -150)
    Call(SetNpcYaw, NPC_SELF, 270)
    Return
    End
};

EvtScript N(EVS_NpcInit_Lee_Intro) = {
    Call(SetNpcPos, NPC_SELF, 600, 20, -145)
    Call(SetNpcYaw, NPC_SELF, 270)
    Return
    End
};

AnimID N(LimitAnims_Chan_Intro)[] = {
    ANIM_Chan_Still,
    ANIM_Chan_Idle,
    ANIM_Chan_Run,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Lee_Intro)[] = {
    ANIM_Lee_Still,
    ANIM_Lee_Idle,
    ANIM_Lee_Talk,
    ANIM_LIST_END
};

NpcData N(NpcData_IntroNPCs)[] = {
    {
        .id = NPC_Luigi_Intro,
        .pos = { NPC_DISPOSE_LOCATION },
        .yaw = 90,
        .settings = &N(NpcSettings_Dummy),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = LUIGI_ANIMS,
    },
    {
        .id = NPC_Toad_01,
        .pos = { -150.0f, 0.0f, -275.0f },
        .yaw = 90,
        .settings = &N(NpcSettings_Toad),
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_RAYCAST_TO_INTERACT | ENEMY_FLAG_SKIP_BATTLE,
        .drops = NO_DROPS,
        .animations = TOAD_RED_ANIMS,
        .tattle = MSG_NpcTattle_MAC_GateGuardian,
    },
    {
        .id = NPC_Toad_02,
        .pos = { 219.0f, 0.0f, -45.0f },
        .yaw = 90,
        .territory = {
            .patrol = {
                .isFlying = true,
                .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
                .numPoints  = 5,
                .points  = {
                    { 219, 0, -45 },
                    { 144, 0, -10 },
                    { 163, 0, -50 },
                    { 240, 0, 50 },
                    { 275, 0, 10 },
                },
                .detectShape = SHAPE_CYLINDER,
                .detectPos  = { 0, 0, 0 },
                .detectSize = { 200 },
            }
        },
        .settings = &N(NpcSettings_Toad_Wander),
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_RAYCAST_TO_INTERACT,
        .drops = NO_DROPS,
        .animations = TOAD_RED_ANIMS,
        .tattle = MSG_NpcTattle_MAC_ShopLoiterer,
    },
    {
        .id = NPC_Toad_03,
        .pos = { 424.0f, 20.0f, -85.0f },
        .yaw = 270,
        .settings = &N(NpcSettings_Toad),
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_RAYCAST_TO_INTERACT,
        .drops = NO_DROPS,
        .animations = TOAD_BLUE_ANIMS,
        .tattle = MSG_NpcTattle_MAC_DojoSpectator,
    },
    {
        .id = NPC_Chan,
        .pos = { 310.0f, 115.0f, -390.0f },
        .yaw = 45,
        .init = &N(EVS_NpcInit_Chan_Intro),
        .settings = &N(NpcSettings_Chan),
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_RAYCAST_TO_INTERACT | ENEMY_FLAG_SKIP_BATTLE,
        .drops = NO_DROPS,
        .animations = CHAN_ANIMS,
        .limitAnimations = N(LimitAnims_Chan_Intro),
        .tattle = MSG_NpcTattle_Chan,
    },
    {
        .id = NPC_Lee,
        .pos = { 330.0f, 115.0f, -410.0f },
        .yaw = 45,
        .init = &N(EVS_NpcInit_Lee_Intro),
        .settings = &N(NpcSettings_Lee),
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_RAYCAST_TO_INTERACT | ENEMY_FLAG_SKIP_BATTLE,
        .drops = NO_DROPS,
        .animations = LEE_ANIMS,
        .limitAnimations = N(LimitAnims_Lee_Intro),
        .tattle = MSG_NpcTattle_Lee,
    },
};

NpcGroupList N(IntroNPCs) = {
    NPC_GROUP(N(NpcData_IntroNPCs)),
    {}
};
