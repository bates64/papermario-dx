#include "kpa_111.h"

#include "world/common/enemy/DryBones/wander.inc.c"

NpcData NpcData_DryBones[] = {
    {
        .id = NPC_DryBones_01,
        .pos = $DryBones_01.pos,
        .yaw = $DryBones_01.yaw,
        .territory = $DryBones_01.territory,
        .settings = &NpcSettings_DryBones_Wander,
        .flags = ENEMY_FLAG_FLYING,
        .drops = DRY_BONES_DROPS,
        .animations = DRY_BONES_ANIMS,
    },
    DRY_BONES_BONE_HITBOX(NPC_DryBones_01 + 1),
    DRY_BONES_BONE_HITBOX(NPC_DryBones_01 + 2),
    DRY_BONES_BONE_HITBOX(NPC_DryBones_01 + 3),
};

NpcData NpcData_DryBones_02[] = {
    {
        .id = NPC_DryBones_02,
        .pos = $DryBones_02.pos,
        .yaw = $DryBones_02.yaw,
        .territory = $DryBones_02.territory,
        .settings = &NpcSettings_DryBones_Wander,
        .flags = ENEMY_FLAG_FLYING,
        .drops = DRY_BONES_DROPS,
        .animations = DRY_BONES_ANIMS,
    },
    DRY_BONES_BONE_HITBOX(NPC_DryBones_02 + 1),
    DRY_BONES_BONE_HITBOX(NPC_DryBones_02 + 2),
    DRY_BONES_BONE_HITBOX(NPC_DryBones_02 + 3),
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_DryBones, "kpa:dry_bones_2", "kpa_13"),
    NPC_GROUP(NpcData_DryBones_02, "kpa:dry_bones_1_koopatrol_2", "kpa_13"),
    {}
};
