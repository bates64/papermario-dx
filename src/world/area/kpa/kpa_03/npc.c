#include "kpa_03.h"

#include "world/common/enemy/Koopatrol/wander.inc.c"
#include "world/common/enemy/SpikeTop/wander.inc.c"
#include "world/common/enemy/Magikoopa/wander.inc.c"

AnimID LimitAnims_Koopatrol[] = {
    ANIM_WorldKoopatrol_Idle,
    ANIM_WorldKoopatrol_Walk,
    ANIM_WorldKoopatrol_Run,
    ANIM_WorldKoopatrol_Hurt,
    ANIM_WorldKoopatrol_ShellSpin,
    ANIM_LIST_END
};

NpcData NpcData_Koopatrol_01 = {
    .id = NPC_Koopatrol_01,
    .pos = $Koopatrol_01.pos,
    .yaw = $Koopatrol_01.yaw,
    .territory = $Koopatrol_01.territory,
    .settings = &NpcSettings_Koopatrol_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
    .drops = KOOPATROL_DROPS,
    .animations = KOOPATROL_ANIMS,
    .limitAnimations = LimitAnims_Koopatrol,
    .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
};

NpcData NpcData_Koopatrol_02 = {
    .id = NPC_Koopatrol_02,
    .pos = $Koopatrol_02.pos,
    .yaw = $Koopatrol_02.yaw,
    .territory = $Koopatrol_02.territory,
    .settings = &NpcSettings_Koopatrol_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
    .drops = KOOPATROL_DROPS,
    .animations = KOOPATROL_ANIMS,
    .limitAnimations = LimitAnims_Koopatrol,
    .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
};

NpcData NpcData_BonyBeetle_01 = {
    .id = NPC_BonyBeetle_01,
    .pos = $BonyBeetle_01.pos,
    .yaw = $BonyBeetle_01.yaw,
    .territory = $BonyBeetle_01.territory,
    .settings = &NpcSettings_BonyBeetle_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = BONY_BEETLE_DROPS_ALT,
    .animations = BONY_BEETLE_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
};

NpcData NpcData_BonyBeetle_02 = {
    .id = NPC_BonyBeetle_02,
    .pos = $BonyBeetle_02.pos,
    .yaw = $BonyBeetle_02.yaw,
    .territory = $BonyBeetle_02.territory,
    .settings = &NpcSettings_BonyBeetle_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = BONY_BEETLE_DROPS,
    .animations = BONY_BEETLE_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
};

NpcData NpcData_Magikoopa_01[] = {
    {
        .id = NPC_Magikoopa_01,
        .pos = $Magikoopa_01.pos,
        .yaw = $Magikoopa_01.yaw,
        .territory = $Magikoopa_01.territory,
        .settings = &NpcSettings_Magikoopa_Wander,
        .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
        .drops = MAGIKOOPA_DROPS,
        .animations = MAGIKOOPA_ANIMS,
        .limitAnimations = LimitAnims_Magikoopa,
        .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
    },
    MAGIKOOPA_SPELL_HITBOX(NPC_Magikoopa_01_Spell),
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Koopatrol_01, "kpa:koopatrol_2_bony_beetle_1", "kpa_03"),
    NPC_GROUP(NpcData_Koopatrol_02, "kpa:koopatrol_1_bony_beetle_1", "kpa_03"),
    NPC_GROUP(NpcData_BonyBeetle_01, "kpa:bony_beetle_3", "kpa_03"),
    NPC_GROUP(NpcData_BonyBeetle_02, "kpa:bony_beetle_2_magikoopa_1", "kpa_03"),
    NPC_GROUP(NpcData_Magikoopa_01, "kpa:magikoopa_1_koopatrol_1_magikoopa_1_koopatrol_1", "kpa_03"),
    {}
};
