#include "kkj_00.h"
#include "sprite/player.h"
#include "world/common/npc/Bootler/base.h"
#include "world/common/npc/Bow/base.h"
#include "world/common/npc/Dryite/base.h"
#include "world/common/npc/Goompa/base.h"
#include "world/common/npc/Goombario/base.h"
#include "world/common/npc/Goombaria/base.h"
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

EvtScript N(EVS_NpcInit_RussT_Ending) = {
    Call(SetNpcPos, NPC_SELF, -300, 0, 295)
    Call(SetNpcYaw, NPC_SELF, 90)
    Return
    End
};

EvtScript N(EVS_NpcInit_ShiverToad_02_Ending) = {
    Call(SetNpcPos, NPC_SELF, -175, 0, -75)
    Call(SetNpcYaw, NPC_SELF, 90)
    Return
    End
};

EvtScript N(EVS_NpcInit_Unused_Ending) = {
    Call(SetNpcPos, NPC_SELF, -440, 0, 220)
    Call(SetNpcYaw, NPC_SELF, 90)
    Return
    End
};

EvtScript N(EVS_NpcInit_Toadette_03_Ending) = {
    Call(SetNpcPos, NPC_SELF, 295, 0, -15)
    Call(SetNpcYaw, NPC_SELF, 270)
    Return
    End
};

EvtScript N(EVS_NpcInit_Toadette_04_Ending) = {
    Call(SetNpcPos, NPC_SELF, 325, 0, -10)
    Call(SetNpcYaw, NPC_SELF, 270)
    Return
    End
};

EvtScript N(EVS_NpcInit_ToadGuard_03_Ending) = {
    Call(SetNpcPos, NPC_SELF, 50, 100, -365)
    Call(SetNpcYaw, NPC_SELF, 270)
    Return
    End
};

AnimID N(LimitAnims_Peach_Ending)[] = {
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

AnimID N(LimitAnims_Minister_Ending)[] = {
    ANIM_ToadMinister_Still,
    ANIM_ToadMinister_Idle,
    ANIM_ToadMinister_Walk,
    ANIM_ToadMinister_Talk,
    ANIM_LIST_END
};

AnimID N(LimitAnims_TayceT_Ending)[] = {
    ANIM_TayceT_Still,
    ANIM_TayceT_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_RussT_Ending)[] = {
    ANIM_RussT_Still,
    ANIM_RussT_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_ShiverToad_Ending)[] = {
    ANIM_ShiverToad_Red_Still,
    ANIM_ShiverToad_Red_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Toad_Ending)[] = {
    ANIM_Toad_Red_Still,
    ANIM_Toad_Red_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Toadette_Ending)[] = {
    ANIM_Toadette_Orange_Still,
    ANIM_Toadette_Orange_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_ToadGuard_Ending)[] = {
    ANIM_ToadGuard_Red_Still,
    ANIM_ToadGuard_Red_Idle,
    ANIM_ToadGuard_Red_Talk,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Goombario_Ending)[] = {
    ANIM_WorldGoombario_Still,
    ANIM_WorldGoombario_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Kooper_Ending)[] = {
    ANIM_WorldKooper_Still,
    ANIM_WorldKooper_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Bombette_Ending)[] = {
    ANIM_WorldBombette_Still,
    ANIM_WorldBombette_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Parakarry_Ending)[] = {
    ANIM_WorldParakarry_Still,
    ANIM_WorldParakarry_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Bow_Ending)[] = {
    ANIM_WorldBow_Still,
    ANIM_WorldBow_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Watt_Ending)[] = {
    ANIM_WorldWatt_Still,
    ANIM_WorldWatt_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Sushie_Ending)[] = {
    ANIM_WorldSushie_Still,
    ANIM_WorldSushie_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Lakilester_Ending)[] = {
    ANIM_WorldLakilester_Still,
    ANIM_WorldLakilester_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Merlon_Ending)[] = {
    ANIM_Merlon_Still,
    ANIM_Merlon_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Merluvlee_Ending)[] = {
    ANIM_Merluvlee_Still,
    ANIM_Merluvlee_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Merlow_Ending)[] = {
    ANIM_Merlow_Still,
    ANIM_Merlow_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Merlee_Ending)[] = {
    ANIM_WorldMerlee_Still,
    ANIM_WorldMerlee_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Merle_Ending)[] = {
    ANIM_Merle_Still,
    ANIM_Merle_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Lakilulu_Ending)[] = {
    ANIM_Lakilulu_Still,
    ANIM_Lakilulu_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Bootler_Ending)[] = {
    ANIM_Bootler_Still,
    ANIM_Bootler_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Goompa_Ending)[] = {
    ANIM_Goompa_Still,
    ANIM_Goompa_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Goombaria_Ending)[] = {
    ANIM_Goombaria_Still,
    ANIM_Goombaria_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Yoshi_Ending)[] = {
    ANIM_Yoshi_Green_Still,
    ANIM_Yoshi_Green_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Penguin_Ending)[] = {
    ANIM_Penguin_Still,
    ANIM_Penguin_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Dryite_Ending)[] = {
    ANIM_Dryite_Green_Still,
    ANIM_Dryite_Green_Idle,
    ANIM_LIST_END
};

AnimID N(LimitAnims_Ninji_Ending)[] = {
    ANIM_Ninji_Still,
    ANIM_Ninji_Idle,
    ANIM_LIST_END
};

#define ENDING_NPC_FLAGS \
    ( ENEMY_FLAG_PASSIVE \
    | ENEMY_FLAG_DO_NOT_KILL \
    | ENEMY_FLAG_ENABLE_HIT_SCRIPT \
    | ENEMY_FLAG_IGNORE_WORLD_COLLISION \
    | ENEMY_FLAG_IGNORE_PLAYER_COLLISION \
    | ENEMY_FLAG_IGNORE_ENTITY_COLLISION \
    | ENEMY_FLAG_FLYING \
    | ENEMY_FLAG_NO_SHADOW_RAYCAST \
    | ENEMY_FLAG_IGNORE_TOUCH \
    | ENEMY_FLAG_IGNORE_JUMP \
    | ENEMY_FLAG_IGNORE_HAMMER \
    | ENEMY_FLAG_CANT_INTERACT \
    | ENEMY_FLAG_IGNORE_PARTNER \
    | ENEMY_FLAG_IGNORE_SPIN \
    )

// same as ENDING_NPC_FLAGS without ENEMY_FLAG_NO_SHADOW_RAYCAST
#define ENDING_PARAKARRY_FLAGS \
    ( ENEMY_FLAG_PASSIVE \
    | ENEMY_FLAG_DO_NOT_KILL \
    | ENEMY_FLAG_ENABLE_HIT_SCRIPT \
    | ENEMY_FLAG_IGNORE_WORLD_COLLISION \
    | ENEMY_FLAG_IGNORE_PLAYER_COLLISION \
    | ENEMY_FLAG_IGNORE_ENTITY_COLLISION \
    | ENEMY_FLAG_FLYING \
    | ENEMY_FLAG_IGNORE_TOUCH \
    | ENEMY_FLAG_IGNORE_JUMP \
    | ENEMY_FLAG_IGNORE_HAMMER \
    | ENEMY_FLAG_CANT_INTERACT \
    | ENEMY_FLAG_IGNORE_PARTNER \
    | ENEMY_FLAG_IGNORE_SPIN \
    )

#define ENDING_PEACH_FLAGS \
    ( ENEMY_FLAG_PASSIVE \
    | ENEMY_FLAG_DO_NOT_KILL \
    | ENEMY_FLAG_ENABLE_HIT_SCRIPT \
    | ENEMY_FLAG_IGNORE_WORLD_COLLISION \
    | ENEMY_FLAG_IGNORE_PLAYER_COLLISION \
    | ENEMY_FLAG_IGNORE_ENTITY_COLLISION \
    | ENEMY_FLAG_FLYING \
    | ENEMY_FLAG_USE_PLAYER_SPRITE \
    )

NpcData N(NpcData_Peach_Ending) = {
    .id = NPC_Peach,
    .pos = { 0.0f, 100.0f, -440.0f },
    .yaw = 270,
    .settings = &N(NpcSettings_Peach),
    .flags = ENDING_PEACH_FLAGS,
    .drops = NO_DROPS,
    .animations = PEACH_ANIMS,
    .limitAnimations = N(LimitAnims_Peach_Ending),
};

NpcData N(NpcData_SpecialToads_Ending)[] = {
    {
        .id = NPC_ToadMinister,
        .pos = { 100.0f, 0.0f, 250.0f },
        .yaw = 270,
        .settings = &N(NpcSettings_ToadMinister),
        .flags = ENDING_NPC_FLAGS,
        .drops = NO_DROPS,
        .animations = TOAD_MINISTER_ANIMS,
        .limitAnimations = N(LimitAnims_Minister_Ending),
    },
    {
        .id = NPC_TayceT,
        .pos = { -200.0f, 0.0f, 260.0f },
        .yaw = 90,
        .settings = &N(NpcSettings_TayceT),
        .flags = ENDING_NPC_FLAGS,
        .drops = NO_DROPS,
        .animations = TAYCE_T_ANIMS,
        .limitAnimations = N(LimitAnims_TayceT_Ending),
    },
    {
        .id = NPC_RussT_02,
        .pos = { 300.0f, 0.0f, 150.0f },
        .yaw = 90,
        .init = &N(EVS_NpcInit_RussT_Ending),
        .settings = &N(NpcSettings_RussT),
        .flags = ENDING_NPC_FLAGS,
        .drops = NO_DROPS,
        .animations = RUSS_T_ANIMS,
        .limitAnimations = N(LimitAnims_RussT_Ending),
    },
    {
        .id = NPC_ShiverToad_02,
        .pos = { 330.0f, 0.0f, 135.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_ShiverToad_02_Ending),
        .settings = &N(NpcSettings_ShiverToad),
        .flags = ENDING_NPC_FLAGS,
        .drops = NO_DROPS,
        .animations = SHIVER_TOAD_GREEN_ANIMS,
        .limitAnimations = N(LimitAnims_ShiverToad_Ending),
    },
};

NpcData N(NpcData_Party_Ending)[] = {
    {
        .id = NPC_Goombario,
        .pos = { 180.0f, 0.0f, 80.0f },
        .yaw = 270,
        .settings = &N(NpcSettings_Dummy),
        .flags = ENDING_NPC_FLAGS,
        .drops = NO_DROPS,
        .animations = GOOMBARIO_ANIMS,
        .limitAnimations = N(LimitAnims_Goombario_Ending),
    },
    {
        .id = NPC_Kooper,
        .pos = { 225.0f, 0.0f, 225.0f },
        .yaw = 270,
        .settings = &N(NpcSettings_Dummy),
        .flags = ENDING_NPC_FLAGS,
        .drops = NO_DROPS,
        .animations = KOOPER_ANIMS,
        .limitAnimations = N(LimitAnims_Kooper_Ending),
    },
    {
        .id = NPC_Bombette,
        .pos = { 270.0f, 0.0f, 115.0f },
        .yaw = 270,
        .settings = &N(NpcSettings_Dummy),
        .flags = ENDING_NPC_FLAGS,
        .drops = NO_DROPS,
        .animations = BOMBETTE_ANIMS,
        .limitAnimations = N(LimitAnims_Bombette_Ending),
    },
    {
        .id = NPC_Parakarry,
        .pos = { 325.0f, 10.0f, 175.0f },
        .yaw = 270,
        .settings = &N(NpcSettings_Dummy),
        .flags = ENDING_PARAKARRY_FLAGS,
        .drops = NO_DROPS,
        .animations = PARAKARRY_ANIMS,
        .limitAnimations = N(LimitAnims_Parakarry_Ending),
    },
    {
        .id = NPC_Bow,
        .pos = { -270.0f, 0.0f, 145.0f },
        .yaw = 90,
        .settings = &N(NpcSettings_Dummy),
        .flags = ENDING_NPC_FLAGS,
        .drops = NO_DROPS,
        .animations = BOW_ANIMS,
        .limitAnimations = N(LimitAnims_Bow_Ending),
    },
    {
        .id = NPC_Watt,
        .pos = { -235.0f, 0.0f, 85.0f },
        .yaw = 90,
        .initVarCount = 1,
        .initVar = { .value = 0 },
        .settings = &N(NpcSettings_Dummy),
        .flags = ENDING_NPC_FLAGS,
        .drops = NO_DROPS,
        .animations = WATT_ANIMS,
        .limitAnimations = N(LimitAnims_Watt_Ending),
    },
    {
        .id = NPC_Sushie,
        .pos = { -190.0f, 0.0f, 50.0f },
        .yaw = 90,
        .settings = &N(NpcSettings_Dummy),
        .flags = ENDING_NPC_FLAGS,
        .drops = NO_DROPS,
        .animations = SUSHIE_ANIMS,
        .limitAnimations = N(LimitAnims_Sushie_Ending),
    },
    {
        .id = NPC_Lakilester,
        .pos = { -320.0f, 0.0f, -60.0f },
        .yaw = 90,
        .settings = &N(NpcSettings_Dummy),
        .flags = ENDING_NPC_FLAGS,
        .drops = NO_DROPS,
        .animations = LAKILESTER_ANIMS,
        .limitAnimations = N(LimitAnims_Lakilester_Ending),
    },
};

NpcData N(NpcData_Wizards_Ending)[] = {
    {
        .id = NPC_Merlon,
        .pos = { -145.0f, 0.0f, 415.0f },
        .yaw = 90,
        .settings = &N(NpcSettings_Dummy),
        .flags = ENDING_NPC_FLAGS,
        .drops = NO_DROPS,
        .animations = {
            .idle   = ANIM_Merlon_Idle,
        },
        .limitAnimations = N(LimitAnims_Merlon_Ending),
    },
    {
        .id = NPC_Merluvlee,
        .pos = { -225.0f, 0.0f, 380.0f },
        .yaw = 90,
        .settings = &N(NpcSettings_Dummy),
        .flags = ENDING_NPC_FLAGS,
        .drops = NO_DROPS,
        .animations = {
            .idle   = ANIM_Merluvlee_Idle,
        },
        .limitAnimations = N(LimitAnims_Merluvlee_Ending),
    },
    {
        .id = NPC_Merlow,
        .pos = { -175.0f, 0.0f, 330.0f },
        .yaw = 90,
        .settings = &N(NpcSettings_Dummy),
        .flags = ENDING_NPC_FLAGS,
        .drops = NO_DROPS,
        .animations = {
            .idle   = ANIM_Merlow_Idle,
        },
        .limitAnimations = N(LimitAnims_Merlow_Ending),
    },
    {
        .id = NPC_Merlee,
        .pos = { -250.0f, 0.0f, 350.0f },
        .yaw = 90,
        .settings = &N(NpcSettings_Dummy),
        .flags = ENDING_NPC_FLAGS,
        .drops = NO_DROPS,
        .animations = MERLEE_ANIMS,
        .limitAnimations = N(LimitAnims_Merlee_Ending),
    },
    {
        .id = NPC_Merle,
        .pos = { -220.0f, 0.0f, 450.0f },
        .yaw = 90,
        .settings = &N(NpcSettings_Dummy),
        .flags = ENDING_NPC_FLAGS,
        .drops = NO_DROPS,
        .animations = MERLE_ANIMS,
        .limitAnimations = N(LimitAnims_Merle_Ending),
    },
};

NpcData N(NpcData_PartyFamily_Ending)[] = {
    {
        .id = NPC_Lakilulu,
        .pos = { -365.0f, 0.0f, -60.0f },
        .yaw = 90,
        .settings = &N(NpcSettings_Lakilulu),
        .flags = ENDING_NPC_FLAGS,
        .drops = NO_DROPS,
        .animations = LAKILULU_ANIMS,
        .limitAnimations = N(LimitAnims_Lakilulu_Ending),
    },
    {
        .id = NPC_Bootler,
        .pos = { -340.0f, 0.0f, 100.0f },
        .yaw = 90,
        .settings = &N(NpcSettings_Dummy),
        .flags = ENDING_NPC_FLAGS,
        .drops = NO_DROPS,
        .animations = BOOTLER_ANIMS,
        .limitAnimations = N(LimitAnims_Bootler_Ending),
    },
    {
        .id = NPC_Goompa,
        .pos = { 170.0f, 0.0f, 0.0f },
        .yaw = 270,
        .settings = &N(NpcSettings_Dummy),
        .flags = ENDING_NPC_FLAGS,
        .drops = NO_DROPS,
        .animations = GOOMPA_ANIMS,
        .limitAnimations = N(LimitAnims_Goompa_Ending),
    },
    {
        .id = NPC_Goombaria,
        .pos = { 140.0f, 0.0f, 50.0f },
        .yaw = 270,
        .settings = &N(NpcSettings_Dummy),
        .flags = ENDING_NPC_FLAGS,
        .drops = NO_DROPS,
        .animations = GOOMBARIA_ANIMS,
        .limitAnimations = N(LimitAnims_Goombaria_Ending),
    },
};

NpcData N(NpcData_Visitors_Ending)[] = {
    {
        .id = NPC_Yoshi,
        .pos = { -340.0f, 0.0f, 310.0f },
        .yaw = 90,
        .settings = &N(NpcSettings_Dummy),
        .flags = ENDING_NPC_FLAGS,
        .drops = NO_DROPS,
        .animations = YOSHI_BLUE_ANIMS,
        .limitAnimations = N(LimitAnims_Yoshi_Ending),
    },
    {
        .id = NPC_Penguin_02,
        .pos = { 225.0f, 0.0f, -80.0f },
        .yaw = 270,
        .settings = &N(NpcSettings_Dummy),
        .flags = ENDING_NPC_FLAGS,
        .drops = NO_DROPS,
        .animations = PENGUIN_ANIMS,
        .limitAnimations = N(LimitAnims_Penguin_Ending),
    },
    {
        .id = NPC_Penguin_03,
        .pos = { -250.0f, 0.0f, -150.0f },
        .yaw = 90,
        .settings = &N(NpcSettings_Dummy),
        .flags = ENDING_NPC_FLAGS,
        .drops = NO_DROPS,
        .animations = PENGUIN_ANIMS,
        .limitAnimations = N(LimitAnims_Penguin_Ending),
    },
    {
        .id = NPC_Dryite,
        .pos = { -320.0f, 0.0f, 245.0f },
        .yaw = 90,
        .settings = &N(NpcSettings_Dummy),
        .flags = ENDING_NPC_FLAGS,
        .drops = NO_DROPS,
        .animations = DRYITE_YELLOW_ANIMS,
        .limitAnimations = N(LimitAnims_Dryite_Ending),
    },
    {
        .id = NPC_Ninji,
        .pos = { -395.0f, 68.0f, 50.0f },
        .yaw = 90,
        .settings = &N(NpcSettings_Dummy),
        .flags = ENDING_NPC_FLAGS,
        .drops = NO_DROPS,
        .animations = NINJI_ANIMS,
        .limitAnimations = N(LimitAnims_Ninji_Ending),
    },
};

NpcData N(NpcData_Toads_Ending)[] = {
    {
        .id = NPC_Toad_04,
        .pos = { 200.0f, 0.0f, 420.0f },
        .yaw = 270,
        .settings = &N(NpcSettings_Toad),
        .flags = ENDING_NPC_FLAGS,
        .drops = NO_DROPS,
        .animations = TOAD_RED_ANIMS,
        .limitAnimations = N(LimitAnims_Toad_Ending),
    },
    {
        .id = NPC_Toad_05,
        .pos = { -120.0f, 0.0f, 205.0f },
        .yaw = 90,
        .settings = &N(NpcSettings_Toad),
        .flags = ENDING_NPC_FLAGS,
        .drops = NO_DROPS,
        .animations = TOAD_YELLOW_ANIMS,
        .limitAnimations = N(LimitAnims_Toad_Ending),
    },
    {
        .id = NPC_Toad_06,
        .pos = { -440.0f, 0.0f, 220.0f },
        .yaw = 90,
        .settings = &N(NpcSettings_Toad),
        .flags = ENDING_NPC_FLAGS,
        .drops = NO_DROPS,
        .animations = TOAD_GREEN_ANIMS,
        .limitAnimations = N(LimitAnims_Toad_Ending),
    },
    {
        .id = NPC_Toad_07,
        .pos = { 285.0f, 0.0f, 290.0f },
        .yaw = 270,
        .settings = &N(NpcSettings_Toad),
        .flags = ENDING_NPC_FLAGS,
        .drops = NO_DROPS,
        .animations = TOAD_BLUE_ANIMS,
        .limitAnimations = N(LimitAnims_Toad_Ending),
    },
};

NpcData N(NpcData_Toadettes_Ending)[] = {
    {
        .id = NPC_Toadette_03,
        .pos = { -300.0f, 0.0f, 100.0f },
        .yaw = 90,
        .init = &N(EVS_NpcInit_Toadette_03_Ending),
        .settings = &N(NpcSettings_Toadette),
        .flags = ENDING_NPC_FLAGS,
        .drops = NO_DROPS,
        .animations = TOADETTE_PINK_ANIMS,
        .limitAnimations = N(LimitAnims_Toadette_Ending),
    },
    {
        .id = NPC_Toadette_04,
        .pos = { -270.0f, 0.0f, 85.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_Toadette_04_Ending),
        .settings = &N(NpcSettings_Toadette),
        .flags = ENDING_NPC_FLAGS,
        .drops = NO_DROPS,
        .animations = TOADETTE_GREEN_ANIMS,
        .limitAnimations = N(LimitAnims_Toadette_Ending),
    },
    {
        .id = NPC_Toadette_05,
        .pos = { -190.0f, 0.0f, 160.0f },
        .yaw = 90,
        .settings = &N(NpcSettings_Toadette),
        .flags = ENDING_NPC_FLAGS,
        .drops = NO_DROPS,
        .animations = TOADETTE_ORANGE_ANIMS,
        .limitAnimations = N(LimitAnims_Toadette_Ending),
    },
    {
        .id = NPC_Toadette_06,
        .pos = { 190.0f, 0.0f, 300.0f },
        .yaw = 270,
        .settings = &N(NpcSettings_Toadette),
        .flags = ENDING_NPC_FLAGS,
        .drops = NO_DROPS,
        .animations = TOADETTE_PURPLE_ANIMS,
        .limitAnimations = N(LimitAnims_Toadette_Ending),
    },
};

NpcData N(NpcData_ToadGuards_Ending)[] = {
    {
        .id = NPC_ToadGuard_03,
        .pos = { 100.0f, 0.0f, 150.0f },
        .yaw = 270,
        .init = &N(EVS_NpcInit_ToadGuard_03_Ending),
        .settings = &N(NpcSettings_ToadGuard),
        .flags = ENDING_NPC_FLAGS,
        .drops = NO_DROPS,
        .animations = TOAD_GUARD_RED_ANIMS,
        .limitAnimations = N(LimitAnims_ToadGuard_Ending),
    },
    {
        .id = NPC_ToadGuard_04,
        .pos = { -50.0f, 100.0f, -365.0f },
        .yaw = 270,
        .settings = &N(NpcSettings_ToadGuard),
        .flags = ENDING_NPC_FLAGS,
        .drops = NO_DROPS,
        .animations = TOAD_GUARD_BLUE_ANIMS,
        .limitAnimations = N(LimitAnims_ToadGuard_Ending),
    },
    {
        .id = NPC_ToadGuard_05,
        .pos = { 225.0f, 0.0f, 125.0f },
        .yaw = 270,
        .settings = &N(NpcSettings_ToadGuard),
        .flags = ENDING_NPC_FLAGS,
        .drops = NO_DROPS,
        .animations = TOAD_GUARD_RED_ANIMS,
        .limitAnimations = N(LimitAnims_ToadGuard_Ending),
    },
    {
        .id = NPC_ToadGuard_06,
        .pos = { -392.0f, 40.0f, -230.0f },
        .yaw = 90,
        .settings = &N(NpcSettings_ToadGuard),
        .flags = ENDING_NPC_FLAGS,
        .drops = NO_DROPS,
        .animations = TOAD_GUARD_GREEN_ANIMS,
        .limitAnimations = N(LimitAnims_ToadGuard_Ending),
    },
    {
        .id = NPC_ToadGuard_07,
        .pos = { -392.0f, 40.0f, -230.0f },
        .yaw = 90,
        .settings = &N(NpcSettings_ToadGuard),
        .flags = ENDING_NPC_FLAGS,
        .drops = NO_DROPS,
        .animations = TOAD_GUARD_YELLOW_ANIMS,
        .limitAnimations = N(LimitAnims_ToadGuard_Ending),
    },
};

NpcGroupList N(EndingNPCs) = {
    NPC_GROUP(N(NpcData_Peach_Ending)),
    NPC_GROUP(N(NpcData_SpecialToads_Ending)),
    NPC_GROUP(N(NpcData_Party_Ending)),
    NPC_GROUP(N(NpcData_Wizards_Ending)),
    NPC_GROUP(N(NpcData_PartyFamily_Ending)),
    NPC_GROUP(N(NpcData_Visitors_Ending)),
    NPC_GROUP(N(NpcData_Toads_Ending)),
    NPC_GROUP(N(NpcData_Toadettes_Ending)),
    NPC_GROUP(N(NpcData_ToadGuards_Ending)),
    {}
};
