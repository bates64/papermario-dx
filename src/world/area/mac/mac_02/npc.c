#include "mac_02.h"

#include "world/common/npc/ToadKid/wander.inc.c"
#include "world/common/npc/Toadette/idle.inc.c"
#include "world/common/npc/Toad/wander.inc.c"
#include "world/common/npc/Toad/patrol.inc.c"
#include "world/common/npc/Toad/idle.inc.c"
#include "world/common/npc/TayceT/idle.inc.c"
#include "world/common/npc/FiceT/idle.inc.c"
#include "world/common/npc/Bootler/idle.inc.c"
#include "world/common/npc/Bubulb/idle.inc.c"
#include "world/common/npc/Quizmo/quiz.inc.c"

#include "world/common/enemy/ShyGuy/base.h"

#include "npc/tayce_t.inc.c"

#include "npc/fice_t.inc.c"
#include "npc/bootler.inc.c"
#include "npc/shyguy_thief.inc.c"
#include "npc/toad_1.inc.c"
#include "npc/cooking_apprentice.inc.c"
#include "npc/toad_2.inc.c"
#include "npc/toad_kid.inc.c"
#include "npc/toad_3.inc.c"
#include "npc/toad_4.inc.c"
#include "npc/bubulb.inc.c"

AnimID LimitAnims_TayceT[] = {
    ANIM_TayceT_Still,
    ANIM_TayceT_Idle,
    ANIM_TayceT_Walk,
    ANIM_TayceT_Idle,
    ANIM_TayceT_Talk,
    ANIM_TayceT_TalkHappy,
    ANIM_TayceT_IdleSad,
    ANIM_TayceT_Cooking,
    ANIM_TayceT_TurnBack,
    ANIM_LIST_END
};

AnimID LimitAnims_Bubulb[] = {
    ANIM_Bubulb_Pink_Still,
    ANIM_Bubulb_Pink_BuriedStill,
    ANIM_Bubulb_Pink_Idle,
    ANIM_Bubulb_Pink_Talk,
    ANIM_Bubulb_Pink_PopUp,
    ANIM_Bubulb_Pink_BuriedIdle,
    ANIM_LIST_END
};

NpcData NpcData_TayceT[] = {
    {
        .id = NPC_TayceT,
        .pos = $TayceT.pos,
        .yaw = $TayceT.yaw,
        .init = &EVS_NpcInit_TayceT,
        .settings = &NpcSettings_TayceT,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TAYCE_T_ANIMS,
        .limitAnimations = LimitAnims_TayceT,
        .tattle = MSG_NpcTattle_TayceT,
    },
    {
        .id = NPC_FiceT,
        .pos = $FiceT.pos,
        .yaw = $FiceT.yaw,
        .init = &EVS_NpcInit_FiceT,
        .settings = &NpcSettings_FiceT,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = FICE_T_ANIMS,
        .tattle = MSG_NpcTattle_FiceT,
    },
    {
        .id = NPC_Bubulb,
        .pos = $Bubulb.pos,
        .yaw = $Bubulb.yaw,
        .init = &EVS_NpcInit_Bubulb,
        .settings = &NpcSettings_Bubulb,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = BUBULB_PINK_ANIMS,
        .limitAnimations = LimitAnims_Bubulb,
        .tattle = MSG_NpcTattle_MAC_Bubulb_Revealed,
    },
    {
        .id = NPC_Toad_01,
        .pos = $Toad_01.pos,
        .yaw = $Toad_01.yaw,
        .territory = $Toad_01.territory,
        .init = &EVS_NpcInit_Toad_01,
        .settings = &NpcSettings_Toad_Wander,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TOAD_BLUE_ANIMS,
        .tattle = MSG_NpcTattle_MAC_HardWorker,
    },
    {
        .id = NPC_CookingApprentice,
        .pos = $CookingApprentice.pos,
        .yaw = $CookingApprentice.yaw,
        .init = &EVS_NpcInit_CookingApprentice,
        .settings = &NpcSettings_Toadette,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TOADETTE_PURPLE_ANIMS,
        .tattle = MSG_NpcTattle_MAC_CookingApprentice,
    },
    {
        .id = NPC_Toad_02,
        .pos = $Toad_02.pos,
        .yaw = $Toad_02.yaw,
        .init = &EVS_NpcInit_Toad_02,
        .settings = &NpcSettings_Toad,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TOAD_GREEN_ANIMS,
        .tattle = MSG_NpcTattle_MAC_CantKeepQuiet,
    },
    {
        .id = NPC_ToadKid,
        .pos = $ToadKid.pos,
        .yaw = $ToadKid.yaw,
        .territory = $ToadKid.territory,
        .init = &EVS_NpcInit_ToadKid,
        .settings = &NpcSettings_ToadKid_Wander,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TOAD_KID_YELLOW_ANIMS,
        .tattle = MSG_NpcTattle_MAC_FickleDreamer,
    },
    {
        .id = NPC_Toad_03,
        .pos = $Toad_03.pos,
        .yaw = $Toad_03.yaw,
        .territory = $Toad_03.territory,
        .init = &EVS_NpcInit_Toad_03,
        .settings = &NpcSettings_Toad_Wander,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TOAD_YELLOW_ANIMS,
        .tattle = MSG_NpcTattle_MAC_PrettySmart,
    },
    {
        .id = NPC_Toad_04,
        .pos = $Toad_04.pos,
        .yaw = $Toad_04.yaw,
        .init = &EVS_NpcInit_Toad_04,
        .settings = &NpcSettings_Toad,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TOAD_RED_ANIMS,
        .tattle = MSG_NpcTattle_MAC_PetBoaster,
    },
};

NpcData NpcData_Bootler = {
    .id = NPC_Bootler,
    .pos = $Bootler.pos,
    .yaw = $Bootler.yaw,
    .init = &EVS_NpcInit_Bootler,
    .settings = &NpcSettings_Bootler,
    .flags = COMMON_PASSIVE_FLAGS,
    .drops = NO_DROPS,
    .animations = BOOTLER_ANIMS,
};

AnimID LimitAnims_ShyGuy[] = {
    ANIM_ShyGuy_Red_Still,
    ANIM_ShyGuy_Red_Idle,
    ANIM_ShyGuy_Red_Walk,
    ANIM_ShyGuy_Red_Run,
    ANIM_ShyGuy_Red_Excited,
    ANIM_ShyGuy_Red_Walk,
    ANIM_ShyGuy_Red_Dash,
    ANIM_LIST_END
};

NpcData NpcData_ShyGuy = {
    .id = NPC_ShyGuy,
    .pos = $ShyGuy.pos,
    .yaw = $ShyGuy.yaw,
    .init = &EVS_NpcInit_ShyGuy,
    .settings = &NpcSettings_Toad,
    .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = NO_DROPS,
    .animations = RED_SHY_GUY_ANIMS,
    .limitAnimations = LimitAnims_ShyGuy,
};

NpcGroupList NpcGroup4 = {
    NPC_GROUP(NpcData_TayceT),
    {}
};

NpcGroupList NpcGroup1 = {
    NPC_GROUP(NpcData_TayceT),
    NPC_GROUP(NpcData_Bootler),
    {}
};

NpcGroupList NpcGroup3 = {
    NPC_GROUP(NpcData_ShyGuy),
    NPC_GROUP(NpcData_TayceT),
    {}
};
