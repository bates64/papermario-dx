#include "kpa_09.h"

#include "world/common/enemy/DryBones/wander.inc.c"

NpcData NpcData_DryBones[] = {
    {
        .id = NPC_DryBones,
        .pos = $DryBones.pos,
        .yaw = $DryBones.yaw,
        .territory = $DryBones.territory,
        .settings = &NpcSettings_DryBones_Wander,
        .flags = ENEMY_FLAG_FLYING,
        .drops = DRY_BONES_DROPS,
        .animations = DRY_BONES_ANIMS,
        .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
    },
    DRY_BONES_BONE_HITBOX(NPC_DryBones_Bone1),
    DRY_BONES_BONE_HITBOX(NPC_DryBones_Bone2),
    DRY_BONES_BONE_HITBOX(NPC_DryBones_Bone3),
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_DryBones, "kpa:dry_bones_2_magikoopa_1", "kpa_01:b"),
    {}
};
