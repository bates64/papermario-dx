#include "jan_06.h"

#include "world/common/enemy/JungleFuzzy/wander.inc.c"
#include "world/common/enemy/HeartPlant/idle.inc.c"
#include "world/common/enemy/HurtPlant/idle.inc.c"
#include "world/common/enemy/SpearGuy/wander.inc.c"

AnimID LimitAnims_JungleFuzzy[] = {
    ANIM_Fuzzy_Blue_Idle,
    ANIM_Fuzzy_Blue_Walk,
    ANIM_Fuzzy_Blue_Run,
    ANIM_Fuzzy_Blue_Hurt,
    ANIM_LIST_END
};

NpcData NpcData_JungleFuzzy = {
    .id = NPC_JungleFuzzy,
    .pos = $JungleFuzzy.pos,
    .yaw = $JungleFuzzy.yaw,
    .territory = $JungleFuzzy.territory,
    .settings = &NpcSettings_JungleFuzzy_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_DO_NOT_AUTO_FACE_PLAYER,
    .drops = JUNGLE_FUZZY_DROPS,
    .animations = JUNGLE_FUZZY_ANIMS,
    .limitAnimations = LimitAnims_JungleFuzzy,
    .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
};

AnimID LimitAnims_SpearGuy_Custom[] = {
    ANIM_SpearGuy_IdleUp,
    ANIM_SpearGuy_IdleFwd,
    ANIM_SpearGuy_Walk,
    ANIM_SpearGuy_Run,
    ANIM_SpearGuy_Dizzy,
    ANIM_SpearGuy_ShakeSpear,
    ANIM_SpearGuy_HurtUp,
    ANIM_SpearGuy_HurtFwd,
    ANIM_SpearGuy_HurtStill,
    ANIM_SpearGuy_Sleep,
    ANIM_SpearGuy_StabWindup,
    ANIM_SpearGuy_StabThrust,
    ANIM_LIST_END
};

NpcData NpcData_SpearGuy[] = {
    {
        .id = NPC_SpearGuy,
        .pos = $SpearGuy.pos,
        .yaw = $SpearGuy.yaw,
        .territory = $SpearGuy.territory,
        .settings = &NpcSettings_SpearGuy_Wander,
        .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_DO_NOT_AUTO_FACE_PLAYER,
        .drops = SPEAR_GUY_DROPS,
        .animations = SPEAR_GUY_ANIMS,
        .limitAnimations = LimitAnims_SpearGuy_Custom,
        .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
    },
    SPEAR_GUY_HITBOX(NPC_SpearGuy_Hitbox),
};

NpcData NpcData_HeartPlant = {
    .id = NPC_HeartPlant,
    .pos = $HeartPlant.pos,
    .yaw = $HeartPlant.yaw,
    .settings = &NpcSettings_HeartPlant,
    .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_USE_INSPECT_ICON | ENEMY_FLAG_DO_NOT_AUTO_FACE_PLAYER,
    .drops = NO_DROPS,
    .animations = HEART_PLANT_ANIMS,
    .tattle = MSG_NpcTattle_HeartPlant,
};

NpcData NpcData_HurtPlant_01 = {
    .id = NPC_HurtPlant_01,
    .pos = $HurtPlant_01.pos,
    .yaw = $HurtPlant_01.yaw,
    .settings = &NpcSettings_HurtPlant,
    .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_USE_INSPECT_ICON | ENEMY_FLAG_DO_NOT_AUTO_FACE_PLAYER,
    .drops = HURT_PLANT_DROPS,
    .animations = HURT_PLANT_ANIMS,
    .tattle = MSG_NpcTattle_HeartPlant,
};

NpcData NpcData_HurtPlant_02 = {
    .id = NPC_HurtPlant_02,
    .pos = $HurtPlant_02.pos,
    .yaw = $HurtPlant_02.yaw,
    .settings = &NpcSettings_HurtPlant,
    .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_USE_INSPECT_ICON | ENEMY_FLAG_DO_NOT_AUTO_FACE_PLAYER,
    .drops = HURT_PLANT_DROPS,
    .animations = HURT_PLANT_ANIMS,
    .tattle = MSG_NpcTattle_HeartPlant,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_JungleFuzzy, "jan:jungle_fuzzy_1_spear_guy_1_jungle_fuzzy_1", "jan_01"),
    NPC_GROUP(NpcData_SpearGuy, "jan:spear_guy_1_jungle_fuzzy_1", "jan_01"),
    NPC_GROUP(NpcData_HeartPlant),
    NPC_GROUP(NpcData_HurtPlant_01, "jan:hurt_plant_2", "jan_01"),
    NPC_GROUP(NpcData_HurtPlant_02, "jan:hurt_plant_2", "jan_01"),
    {}
};
