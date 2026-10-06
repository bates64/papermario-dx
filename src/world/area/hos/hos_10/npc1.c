#include "hos_10.h"

EvtScript EVS_NpcInit_Peach_Descent = {
    Call(SetNpcPos, NPC_Peach, -100, 200, 1300)
    Return
    End
};

EvtScript EVS_NpcInit_Twink_Descent = {
    Call(SetNpcPos, NPC_Twink, -130, 260, 1300)
    Return
    End
};

EvtScript EVS_NpcInit_Eldstar_Descent = {
    Call(SetNpcPos, NPC_Eldstar, -121, 200, 1369)
    Return
    End
};

EvtScript EVS_NpcInit_Mamar_Descent = {
    Call(SetNpcPos, NPC_Mamar, -175, 200, 1342)
    Return
    End
};

EvtScript EVS_NpcInit_Skolar_Descent = {
    Call(SetNpcPos, NPC_Skolar, -188, 200, 1284)
    Return
    End
};

EvtScript EVS_NpcInit_Muskular_Descent = {
    Call(SetNpcPos, NPC_Muskular, -150, 200, 1237)
    Return
    End
};

EvtScript EVS_NpcInit_Misstar_Descent = {
    Call(SetNpcPos, NPC_Misstar, -100, 200, 1237)
    Return
    End
};

EvtScript EVS_NpcInit_Klevar_Descent = {
    Call(SetNpcPos, NPC_Klevar, -52, 200, 1284)
    Return
    End
};

EvtScript EVS_NpcInit_Kalmar_Descent = {
    Call(SetNpcPos, NPC_Kalmar, -65, 200, 1342)
    Return
    End
};

AnimID LimitAnims_Peach_Descent[] = {
    ANIM_Peach1_Idle,
    ANIM_Peach1_Walk,
    ANIM_Peach2_RaiseArms,
    ANIM_Peach2_GaspStill,
    ANIM_Peach2_TiedIdle,
    ANIM_Peach2_TalkIdle,
    ANIM_LIST_END
};

AnimID LimitAnims_Twink_Descent[] = {
    ANIM_Twink_Idle,
    ANIM_Twink_Talk,
    ANIM_LIST_END
};

AnimID LimitAnims_Eldstar_Descent[] = {
    ANIM_WorldEldstar_Idle,
    ANIM_WorldEldstar_Wave,
    ANIM_LIST_END
};

AnimID LimitAnims_Mamar_Descent[] = {
    ANIM_WorldMamar_Idle,
    ANIM_WorldMamar_TalkHappy,
    ANIM_LIST_END
};

AnimID LimitAnims_Skolar_Descent[] = {
    ANIM_WorldSkolar_Idle,
    ANIM_WorldSkolar_TalkAngry,
    ANIM_LIST_END
};

AnimID LimitAnims_Muskular_Descent[] = {
    ANIM_WorldMuskular_Idle,
    ANIM_WorldMuskular_Talk,
    ANIM_LIST_END
};

AnimID LimitAnims_Misstar_Descent[] = {
    ANIM_WorldMisstar_Idle,
    ANIM_WorldMisstar_Talk,
    ANIM_LIST_END
};

AnimID LimitAnims_Klevar_Descent[] = {
    ANIM_WorldKlevar_Idle,
    ANIM_WorldKlevar_Talk,
    ANIM_LIST_END
};

AnimID LimitAnims_Kalmar_Descent[] = {
    ANIM_WorldKalmar_Idle,
    ANIM_WorldKalmar_Talk,
    ANIM_LIST_END
};

NpcData NpcData_Spirits_Descent[] = {
    {
        .id = NPC_Peach,
        .pos = { NPC_DISPOSE_LOCATION },
        .yaw = 270,
        .init = &EVS_NpcInit_Peach_Descent,
        .settings = &NpcSettings_Dummy,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_USE_PLAYER_SPRITE,
        .drops = NO_DROPS,
        .animations = PEACH_ANIMS,
        .limitAnimations = LimitAnims_Peach_Descent,
    },
    {
        .id = NPC_Twink,
        .pos = { NPC_DISPOSE_LOCATION },
        .yaw = 270,
        .init = &EVS_NpcInit_Twink_Descent,
        .settings = &NpcSettings_Twink,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = TWINK_ANIMS,
        .limitAnimations = LimitAnims_Twink_Descent,
    },
    {
        .id = NPC_Eldstar,
        .pos = { NPC_DISPOSE_LOCATION },
        .yaw = 270,
        .init = &EVS_NpcInit_Eldstar_Descent,
        .settings = &NpcSettings_StarSpirit,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = ELDSTAR_ANIMS,
        .limitAnimations = LimitAnims_Eldstar_Descent,
    },
    {
        .id = NPC_Mamar,
        .pos = { NPC_DISPOSE_LOCATION },
        .yaw = 270,
        .init = &EVS_NpcInit_Mamar_Descent,
        .settings = &NpcSettings_StarSpirit,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = MAMAR_ANIMS,
        .limitAnimations = LimitAnims_Mamar_Descent,
    },
    {
        .id = NPC_Skolar,
        .pos = { NPC_DISPOSE_LOCATION },
        .yaw = 90,
        .init = &EVS_NpcInit_Skolar_Descent,
        .settings = &NpcSettings_StarSpirit,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = SKOLAR_ANIMS,
        .limitAnimations = LimitAnims_Skolar_Descent,
    },
    {
        .id = NPC_Muskular,
        .pos = { NPC_DISPOSE_LOCATION },
        .yaw = 270,
        .init = &EVS_NpcInit_Muskular_Descent,
        .settings = &NpcSettings_StarSpirit,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = MUSKULAR_ANIMS,
        .limitAnimations = LimitAnims_Muskular_Descent,
    },
    {
        .id = NPC_Misstar,
        .pos = { NPC_DISPOSE_LOCATION },
        .yaw = 90,
        .init = &EVS_NpcInit_Misstar_Descent,
        .settings = &NpcSettings_StarSpirit,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = MISSTAR_ANIMS,
        .limitAnimations = LimitAnims_Misstar_Descent,
    },
    {
        .id = NPC_Klevar,
        .pos = { NPC_DISPOSE_LOCATION },
        .yaw = 270,
        .init = &EVS_NpcInit_Klevar_Descent,
        .settings = &NpcSettings_StarSpirit,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = KLEVAR_ANIMS,
        .limitAnimations = LimitAnims_Klevar_Descent,
    },
    {
        .id = NPC_Kalmar,
        .pos = { NPC_DISPOSE_LOCATION },
        .yaw = 90,
        .init = &EVS_NpcInit_Kalmar_Descent,
        .settings = &NpcSettings_StarSpirit,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = KALMAR_ANIMS,
        .limitAnimations = LimitAnims_Kalmar_Descent,
    },
};

NpcGroupList NpcGroup_Descent = {
    NPC_GROUP(NpcData_Spirits_Descent),
    {}
};
