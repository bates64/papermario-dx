#include "kkj_00.h"
#include "sprite/player.h"
#include "world/common/npc/Bootler/base.h"
#include "world/common/npc/Bow/base.h"
#include "world/common/npc/Dryite/base.h"
#include "world/common/npc/GoombaFamily/base.h"
#include "world/common/npc/Kooper/base.h"
#include "world/common/npc/Merlee/base.h"
#include "world/common/npc/Merle/base.h"
#include "world/common/npc/Ninji/base.h"
#include "world/common/npc/Parakarry/base.h"
#include "world/common/npc/Penguin/base.h"
#include "world/common/npc/Sushie/base.h"
#include "world/common/npc/Yoshi/base.h"
#include "world/common/enemy/Bombette/base.h"
#include "world/common/npc/Lakilester/base.h"
#include "world/common/npc/Watt/base.h"

#include "world/common/npc/ToadGuard/idle.inc.c"
#include "world/common/npc/ToadMinister/idle.inc.c"
#include "world/common/npc/Toadette/idle.inc.c"
#include "world/common/npc/ShiverToad/idle.inc.c"
#include "world/common/npc/Toad/idle.inc.c"
#include "world/common/npc/Peach/idle.inc.c"
#include "world/common/npc/Dummy/idle.inc.c"
#include "world/common/npc/Lakilulu/idle.inc.c"
#include "world/common/npc/RussT/idle.inc.c"

EvtScript N(EVS_NpcInit_RussT) = {
    Call(SetNpcPos, NPC_SELF, -300, 0, 295)
    Call(SetNpcYaw, NPC_SELF, 90)
    Return
    End
};

EvtScript N(EVS_NpcInit_ShiverToad_02) = {
    Call(SetNpcPos, NPC_SELF, -175, 0, -75)
    Call(SetNpcYaw, NPC_SELF, 90)
    Return
    End
};

EvtScript N(EVS_NpcInit_Unused) = {
    Call(SetNpcPos, NPC_SELF, -440, 0, 220)
    Call(SetNpcYaw, NPC_SELF, 90)
    Return
    End
};

EvtScript N(EVS_NpcInit_Toadette_03) = {
    Call(SetNpcPos, NPC_SELF, 295, 0, -15)
    Call(SetNpcYaw, NPC_SELF, 270)
    Return
    End
};

EvtScript N(EVS_NpcInit_Toadette_04) = {
    Call(SetNpcPos, NPC_SELF, 325, 0, -10)
    Call(SetNpcYaw, NPC_SELF, 270)
    Return
    End
};

EvtScript N(EVS_NpcInit_ToadGuard_03) = {
    Call(SetNpcPos, NPC_SELF, 50, 100, -365)
    Call(SetNpcYaw, NPC_SELF, 270)
    Return
    End
};

AnimID N(LimitAnims_Peach)[] = {
    ANIM_Peach1_Still,
    ANIM_Peach1_Idle,
    ANIM_Peach2_TalkIdle,
    ANIM_Peach2_RaiseArms,
    ANIM_Peach2_Talk,
    ANIM_Peach2_LowerArms,
    ANIM_Peach1_Walk,
    ANIM_Peach2_SpreadArms,
    ANIM_Peach3_Pray,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Minister)[] = {
    ANIM_ToadMinister_Still,
    ANIM_ToadMinister_Idle,
    ANIM_ToadMinister_Walk,
    ANIM_ToadMinister_Talk,
    ANIM_LIST_END
};

AnimID N(LimitAnims_TayceT)[] = {
    ANIM_TayceT_Still,
    ANIM_TayceT_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_RussT)[] = {
    ANIM_RussT_Still,
    ANIM_RussT_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_ShiverToad)[] = {
    ANIM_ShiverToad_Red_Still,
    ANIM_ShiverToad_Red_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Toad)[] = {
    ANIM_Toad_Red_Still,
    ANIM_Toad_Red_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Toadette)[] = {
    ANIM_Toadette_Orange_Still,
    ANIM_Toadette_Orange_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_ToadGuard)[] = {
    ANIM_ToadGuard_Red_Still,
    ANIM_ToadGuard_Red_Idle,
    ANIM_ToadGuard_Red_Talk,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Goombario)[] = {
    ANIM_WorldGoombario_Still,
    ANIM_WorldGoombario_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Kooper)[] = {
    ANIM_WorldKooper_Still,
    ANIM_WorldKooper_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Bombette)[] = {
    ANIM_WorldBombette_Still,
    ANIM_WorldBombette_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Parakarry)[] = {
    ANIM_WorldParakarry_Still,
    ANIM_WorldParakarry_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Bow)[] = {
    ANIM_WorldBow_Still,
    ANIM_WorldBow_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Watt)[] = {
    ANIM_WorldWatt_Still,
    ANIM_WorldWatt_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Sushie)[] = {
    ANIM_WorldSushie_Still,
    ANIM_WorldSushie_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Lakilester)[] = {
    ANIM_WorldLakilester_Still,
    ANIM_WorldLakilester_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Merlon)[] = {
    ANIM_Merlon_Still,
    ANIM_Merlon_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Merluvlee)[] = {
    ANIM_Merluvlee_Still,
    ANIM_Merluvlee_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Merlow)[] = {
    ANIM_Merlow_Still,
    ANIM_Merlow_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Merlee)[] = {
    ANIM_WorldMerlee_Still,
    ANIM_WorldMerlee_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Merle)[] = {
    ANIM_Merle_Still,
    ANIM_Merle_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Lakilulu)[] = {
    ANIM_Lakilulu_Still,
    ANIM_Lakilulu_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Bootler)[] = {
    ANIM_Bootler_Still,
    ANIM_Bootler_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Goompa)[] = {
    ANIM_Goompa_Still,
    ANIM_Goompa_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Goombaria)[] = {
    ANIM_Goombaria_Still,
    ANIM_Goombaria_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Yoshi)[] = {
    ANIM_Yoshi_Green_Still,
    ANIM_Yoshi_Green_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Penguin)[] = {
    ANIM_Penguin_Still,
    ANIM_Penguin_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Dryite)[] = {
    ANIM_Dryite_Green_Still,
    ANIM_Dryite_Green_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Ninji)[] = {
    ANIM_Ninji_Still,
    ANIM_Ninji_Idle,
    ANIM_LIST_END
};

NpcData N(NpcData_Peach) = {
    .id = NPC_Peach,
    .pos = { 0.0f, 100.0f, -440.0f },
    .yaw = 270,
    .settings = &N(NpcSettings_Peach),
    .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_USE_PLAYER_SPRITE,
    .drops = NO_DROPS,
    .animations = PEACH_ANIMS,
    .limitAnimations = N(LimitAnims_Peach),
};

NpcData N(NpcData_SpecialToads)[] = {
    {
        .id = NPC_ToadMinister,
        .pos = { 100.0f, 0.0f, 250.0f },
        .yaw = 270,
        .settings = &N(NpcSettings_ToadMinister),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_PARTNER | ENEMY_FLAG_IGNORE_SPIN,
        .drops = NO_DROPS,
        .animations = TOAD_MINISTER_ANIMS,
        .limitAnimations = N(LimitAnims_Minister),
    },
    {
        .id = NPC_TayceT,
        .pos = { -200.0f, 0.0f, 260.0f },
        .yaw = 90,
        .settings = &N(NpcSettings_Toad),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_PARTNER | ENEMY_FLAG_IGNORE_SPIN,
        .drops = NO_DROPS,
        .animations = {
            .idle   = ANIM_TayceT_Idle,
        },
        .limitAnimations = N(LimitAnims_TayceT),
    },
    {
        .id = NPC_RussT_02,
        .pos = { 300.0f, 0.0f, 150.0f },
        .yaw = 90,
        .init = &N(EVS_NpcInit_RussT),
        .settings = &N(NpcSettings_RussT),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_PARTNER | ENEMY_FLAG_IGNORE_SPIN,
        .drops = NO_DROPS,
        .animations = RUSS_T_ANIMS,
        .limitAnimations = N(LimitAnims_RussT),
    },
    {
        .id = NPC_ShiverToad_02,
        .pos = { 330.0f, 0.0f, 135.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_ShiverToad_02),
        .settings = &N(NpcSettings_ShiverToad),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_PARTNER | ENEMY_FLAG_IGNORE_SPIN,
        .drops = NO_DROPS,
        .animations = SHIVER_TOAD_GREEN_ANIMS,
        .limitAnimations = N(LimitAnims_ShiverToad),
    },
};

NpcData N(NpcData_Party)[] = {
    {
        .id = NPC_Goombario,
        .pos = { 180.0f, 0.0f, 80.0f },
        .yaw = 270,
        .settings = &N(NpcSettings_Dummy),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_PARTNER | ENEMY_FLAG_IGNORE_SPIN,
        .drops = NO_DROPS,
        .animations = GOOMBARIO_ANIMS,
        .limitAnimations = N(LimitAnims_Goombario),
    },
    {
        .id = NPC_Kooper,
        .pos = { 225.0f, 0.0f, 225.0f },
        .yaw = 270,
        .settings = &N(NpcSettings_Dummy),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_PARTNER | ENEMY_FLAG_IGNORE_SPIN,
        .drops = NO_DROPS,
        .animations = KOOPER_ANIMS,
        .limitAnimations = N(LimitAnims_Kooper),
    },
    {
        .id = NPC_Bombette,
        .pos = { 270.0f, 0.0f, 115.0f },
        .yaw = 270,
        .settings = &N(NpcSettings_Dummy),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_PARTNER | ENEMY_FLAG_IGNORE_SPIN,
        .drops = NO_DROPS,
        .animations = BOMBETTE_ANIMS,
        .limitAnimations = N(LimitAnims_Bombette),
    },
    {
        .id = NPC_Parakarry,
        .pos = { 325.0f, 10.0f, 175.0f },
        .yaw = 270,
        .settings = &N(NpcSettings_Dummy),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_PARTNER | ENEMY_FLAG_IGNORE_SPIN,
        .drops = NO_DROPS,
        .animations = PARAKARRY_ANIMS,
        .limitAnimations = N(LimitAnims_Parakarry),
    },
    {
        .id = NPC_Bow,
        .pos = { -270.0f, 0.0f, 145.0f },
        .yaw = 90,
        .settings = &N(NpcSettings_Dummy),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_PARTNER | ENEMY_FLAG_IGNORE_SPIN,
        .drops = NO_DROPS,
        .animations = BOW_ANIMS,
        .limitAnimations = N(LimitAnims_Bow),
    },
    {
        .id = NPC_Watt,
        .pos = { -235.0f, 0.0f, 85.0f },
        .yaw = 90,
        .initVarCount = 1,
        .initVar = { .value = 0 },
        .settings = &N(NpcSettings_Dummy),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_PARTNER | ENEMY_FLAG_IGNORE_SPIN,
        .drops = NO_DROPS,
        .animations = WATT_ANIMS,
        .limitAnimations = N(LimitAnims_Watt),
    },
    {
        .id = NPC_Sushie,
        .pos = { -190.0f, 0.0f, 50.0f },
        .yaw = 90,
        .settings = &N(NpcSettings_Dummy),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_PARTNER | ENEMY_FLAG_IGNORE_SPIN,
        .drops = NO_DROPS,
        .animations = SUSHIE_ANIMS,
        .limitAnimations = N(LimitAnims_Sushie),
    },
    {
        .id = NPC_Lakilester,
        .pos = { -320.0f, 0.0f, -60.0f },
        .yaw = 90,
        .settings = &N(NpcSettings_Dummy),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_PARTNER | ENEMY_FLAG_IGNORE_SPIN,
        .drops = NO_DROPS,
        .animations = LAKILESTER_ANIMS,
        .limitAnimations = N(LimitAnims_Lakilester),
    },
};

NpcData N(NpcData_Wizards)[] = {
    {
        .id = NPC_Merlon,
        .pos = { -145.0f, 0.0f, 415.0f },
        .yaw = 90,
        .settings = &N(NpcSettings_Dummy),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_PARTNER | ENEMY_FLAG_IGNORE_SPIN,
        .drops = NO_DROPS,
        .animations = {
            .idle   = ANIM_Merlon_Idle,
        },
        .limitAnimations = N(LimitAnims_Merlon),
    },
    {
        .id = NPC_Merluvlee,
        .pos = { -225.0f, 0.0f, 380.0f },
        .yaw = 90,
        .settings = &N(NpcSettings_Dummy),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_PARTNER | ENEMY_FLAG_IGNORE_SPIN,
        .drops = NO_DROPS,
        .animations = {
            .idle   = ANIM_Merluvlee_Idle,
        },
        .limitAnimations = N(LimitAnims_Merluvlee),
    },
    {
        .id = NPC_Merlow,
        .pos = { -175.0f, 0.0f, 330.0f },
        .yaw = 90,
        .settings = &N(NpcSettings_Dummy),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_PARTNER | ENEMY_FLAG_IGNORE_SPIN,
        .drops = NO_DROPS,
        .animations = {
            .idle   = ANIM_Merlow_Idle,
        },
        .limitAnimations = N(LimitAnims_Merlow),
    },
    {
        .id = NPC_Merlee,
        .pos = { -250.0f, 0.0f, 350.0f },
        .yaw = 90,
        .settings = &N(NpcSettings_Dummy),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_PARTNER | ENEMY_FLAG_IGNORE_SPIN,
        .drops = NO_DROPS,
        .animations = MERLEE_ANIMS,
        .limitAnimations = N(LimitAnims_Merlee),
    },
    {
        .id = NPC_Merle,
        .pos = { -220.0f, 0.0f, 450.0f },
        .yaw = 90,
        .settings = &N(NpcSettings_Dummy),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_PARTNER | ENEMY_FLAG_IGNORE_SPIN,
        .drops = NO_DROPS,
        .animations = MERLE_ANIMS,
        .limitAnimations = N(LimitAnims_Merle),
    },
};

NpcData N(NpcData_PartyFamily)[] = {
    {
        .id = NPC_Lakilulu,
        .pos = { -365.0f, 0.0f, -60.0f },
        .yaw = 90,
        .settings = &N(NpcSettings_Lakilulu),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_PARTNER | ENEMY_FLAG_IGNORE_SPIN,
        .drops = NO_DROPS,
        .animations = LAKILULU_ANIMS,
        .limitAnimations = N(LimitAnims_Lakilulu),
    },
    {
        .id = NPC_Bootler,
        .pos = { -340.0f, 0.0f, 100.0f },
        .yaw = 90,
        .settings = &N(NpcSettings_Dummy),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_PARTNER | ENEMY_FLAG_IGNORE_SPIN,
        .drops = NO_DROPS,
        .animations = BOOTLER_ANIMS,
        .limitAnimations = N(LimitAnims_Bootler),
    },
    {
        .id = NPC_Goompa,
        .pos = { 170.0f, 0.0f, 0.0f },
        .yaw = 270,
        .settings = &N(NpcSettings_Dummy),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_PARTNER | ENEMY_FLAG_IGNORE_SPIN,
        .drops = NO_DROPS,
        .animations = GOOMPA_ANIMS,
        .limitAnimations = N(LimitAnims_Goompa),
    },
    {
        .id = NPC_Goombaria,
        .pos = { 140.0f, 0.0f, 50.0f },
        .yaw = 270,
        .settings = &N(NpcSettings_Dummy),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_PARTNER | ENEMY_FLAG_IGNORE_SPIN,
        .drops = NO_DROPS,
        .animations = GOOMBARIA_ANIMS,
        .limitAnimations = N(LimitAnims_Goombaria),
    },
};

NpcData N(NpcData_Visitors)[] = {
    {
        .id = NPC_Yoshi,
        .pos = { -340.0f, 0.0f, 310.0f },
        .yaw = 90,
        .settings = &N(NpcSettings_Dummy),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_PARTNER | ENEMY_FLAG_IGNORE_SPIN,
        .drops = NO_DROPS,
        .animations = YOSHI_BLUE_ANIMS,
        .limitAnimations = N(LimitAnims_Yoshi),
    },
    {
        .id = NPC_Penguin_02,
        .pos = { 225.0f, 0.0f, -80.0f },
        .yaw = 270,
        .settings = &N(NpcSettings_Dummy),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_PARTNER | ENEMY_FLAG_IGNORE_SPIN,
        .drops = NO_DROPS,
        .animations = PENGUIN_ANIMS,
        .limitAnimations = N(LimitAnims_Penguin),
    },
    {
        .id = NPC_Penguin_03,
        .pos = { -250.0f, 0.0f, -150.0f },
        .yaw = 90,
        .settings = &N(NpcSettings_Dummy),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_PARTNER | ENEMY_FLAG_IGNORE_SPIN,
        .drops = NO_DROPS,
        .animations = PENGUIN_ANIMS,
        .limitAnimations = N(LimitAnims_Penguin),
    },
    {
        .id = NPC_Dryite,
        .pos = { -320.0f, 0.0f, 245.0f },
        .yaw = 90,
        .settings = &N(NpcSettings_Dummy),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_PARTNER | ENEMY_FLAG_IGNORE_SPIN,
        .drops = NO_DROPS,
        .animations = DRYITE_YELLOW_ANIMS,
        .limitAnimations = N(LimitAnims_Dryite),
    },
    {
        .id = NPC_Ninji,
        .pos = { -395.0f, 68.0f, 50.0f },
        .yaw = 90,
        .settings = &N(NpcSettings_Dummy),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_PARTNER | ENEMY_FLAG_IGNORE_SPIN,
        .drops = NO_DROPS,
        .animations = NINJI_ANIMS,
        .limitAnimations = N(LimitAnims_Ninji),
    },
};

NpcData N(NpcData_Toads)[] = {
    {
        .id = NPC_Toad_04,
        .pos = { 200.0f, 0.0f, 420.0f },
        .yaw = 270,
        .settings = &N(NpcSettings_Toad),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_PARTNER | ENEMY_FLAG_IGNORE_SPIN,
        .drops = NO_DROPS,
        .animations = TOAD_RED_ANIMS,
        .limitAnimations = N(LimitAnims_Toad),
    },
    {
        .id = NPC_Toad_05,
        .pos = { -120.0f, 0.0f, 205.0f },
        .yaw = 90,
        .settings = &N(NpcSettings_Toad),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_PARTNER | ENEMY_FLAG_IGNORE_SPIN,
        .drops = NO_DROPS,
        .animations = TOAD_YELLOW_ANIMS,
        .limitAnimations = N(LimitAnims_Toad),
    },
    {
        .id = NPC_Toad_06,
        .pos = { -440.0f, 0.0f, 220.0f },
        .yaw = 90,
        .settings = &N(NpcSettings_Toad),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_PARTNER | ENEMY_FLAG_IGNORE_SPIN,
        .drops = NO_DROPS,
        .animations = TOAD_GREEN_ANIMS,
        .limitAnimations = N(LimitAnims_Toad),
    },
    {
        .id = NPC_Toad_07,
        .pos = { 285.0f, 0.0f, 290.0f },
        .yaw = 270,
        .settings = &N(NpcSettings_Toad),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_PARTNER | ENEMY_FLAG_IGNORE_SPIN,
        .drops = NO_DROPS,
        .animations = TOAD_BLUE_ANIMS,
        .limitAnimations = N(LimitAnims_Toad),
    },
};

NpcData N(NpcData_Toadettes)[] = {
    {
        .id = NPC_Toadette_03,
        .pos = { -300.0f, 0.0f, 100.0f },
        .yaw = 90,
        .init = &N(EVS_NpcInit_Toadette_03),
        .settings = &N(NpcSettings_Toadette),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_PARTNER | ENEMY_FLAG_IGNORE_SPIN,
        .drops = NO_DROPS,
        .animations = TOADETTE_PINK_ANIMS,
        .limitAnimations = N(LimitAnims_Toadette),
    },
    {
        .id = NPC_Toadette_04,
        .pos = { -270.0f, 0.0f, 85.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_Toadette_04),
        .settings = &N(NpcSettings_Toadette),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_PARTNER | ENEMY_FLAG_IGNORE_SPIN,
        .drops = NO_DROPS,
        .animations = TOADETTE_GREEN_ANIMS,
        .limitAnimations = N(LimitAnims_Toadette),
    },
    {
        .id = NPC_Toadette_05,
        .pos = { -190.0f, 0.0f, 160.0f },
        .yaw = 90,
        .settings = &N(NpcSettings_Toadette),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_PARTNER | ENEMY_FLAG_IGNORE_SPIN,
        .drops = NO_DROPS,
        .animations = TOADETTE_ORANGE_ANIMS,
        .limitAnimations = N(LimitAnims_Toadette),
    },
    {
        .id = NPC_Toadette_06,
        .pos = { 190.0f, 0.0f, 300.0f },
        .yaw = 270,
        .settings = &N(NpcSettings_Toadette),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_PARTNER | ENEMY_FLAG_IGNORE_SPIN,
        .drops = NO_DROPS,
        .animations = TOADETTE_PURPLE_ANIMS,
        .limitAnimations = N(LimitAnims_Toadette),
    },
};

NpcData N(NpcData_ToadGuards)[] = {
    {
        .id = NPC_ToadGuard_03,
        .pos = { 100.0f, 0.0f, 150.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_ToadGuard_03),
        .settings = &N(NpcSettings_ToadGuard),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_PARTNER | ENEMY_FLAG_IGNORE_SPIN,
        .drops = NO_DROPS,
        .animations = TOAD_GUARD_RED_ANIMS,
        .limitAnimations = N(LimitAnims_ToadGuard),
    },
    {
        .id = NPC_ToadGuard_04,
        .pos = { -50.0f, 100.0f, -365.0f },
        .yaw = 270,
        .settings = &N(NpcSettings_ToadGuard),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_PARTNER | ENEMY_FLAG_IGNORE_SPIN,
        .drops = NO_DROPS,
        .animations = TOAD_GUARD_BLUE_ANIMS,
        .limitAnimations = N(LimitAnims_ToadGuard),
    },
    {
        .id = NPC_ToadGuard_05,
        .pos = { 225.0f, 0.0f, 125.0f },
        .yaw = 270,
        .settings = &N(NpcSettings_ToadGuard),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_PARTNER | ENEMY_FLAG_IGNORE_SPIN,
        .drops = NO_DROPS,
        .animations = TOAD_GUARD_RED_ANIMS,
        .limitAnimations = N(LimitAnims_ToadGuard),
    },
    {
        .id = NPC_ToadGuard_06,
        .pos = { -392.0f, 40.0f, -230.0f },
        .yaw = 90,
        .settings = &N(NpcSettings_ToadGuard),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_PARTNER | ENEMY_FLAG_IGNORE_SPIN,
        .drops = NO_DROPS,
        .animations = TOAD_GUARD_GREEN_ANIMS,
        .limitAnimations = N(LimitAnims_ToadGuard),
    },
    {
        .id = NPC_ToadGuard_07,
        .pos = { -392.0f, 40.0f, -230.0f },
        .yaw = 90,
        .settings = &N(NpcSettings_ToadGuard),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_CANT_INTERACT | ENEMY_FLAG_IGNORE_PARTNER | ENEMY_FLAG_IGNORE_SPIN,
        .drops = NO_DROPS,
        .animations = TOAD_GUARD_YELLOW_ANIMS,
        .limitAnimations = N(LimitAnims_ToadGuard),
    },
};

NpcGroupList N(EndingNPCs) = {
    NPC_GROUP(N(NpcData_Peach)),
    NPC_GROUP(N(NpcData_SpecialToads)),
    NPC_GROUP(N(NpcData_Party)),
    NPC_GROUP(N(NpcData_Wizards)),
    NPC_GROUP(N(NpcData_PartyFamily)),
    NPC_GROUP(N(NpcData_Visitors)),
    NPC_GROUP(N(NpcData_Toads)),
    NPC_GROUP(N(NpcData_Toadettes)),
    NPC_GROUP(N(NpcData_ToadGuards)),
    {}
};
