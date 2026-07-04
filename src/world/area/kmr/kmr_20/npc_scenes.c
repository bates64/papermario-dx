#include "kmr_20.h"
#include "world/common/npc/Luigi/base.h"
#include "world/common/npc/Parakarry/base.h"

NpcSettings N(NpcSettings_Scenes) = {
    .height = 24,
    .radius = 24,
    .level = ACTOR_LEVEL_NONE,
};

EvtScript N(EVS_NpcInit_Luigi_Scenes) = {
    Call(SetNpcCollisionSize, NPC_SELF, 46, 26)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseOrEq(kmr_20_ENTRY_2)
        CaseOrEq(kmr_20_ENTRY_3)
            Call(SetNpcAnimation, NPC_SELF, ANIM_Luigi_IdleSit)
            Call(SetNpcPos, NPC_SELF, 196, 44, -37)
            Call(SetNpcYaw, NPC_SELF, 270)
        EndCaseGroup
    EndSwitch
    Return
    End
};

NpcData N(NpcData_Scenes)[] = {
    {
        .id = NPC_Scene_Parakarry,
        .pos = { NPC_DISPOSE_LOCATION },
        .yaw = 90,
        .settings = &N(NpcSettings_Scenes),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_ACTIVE_WHILE_OFFSCREEN | ENEMY_FLAG_DO_NOT_AUTO_FACE_PLAYER,
        .drops = NO_DROPS,
        .animations = PARAKARRY_ANIMS,
    },
    {
        .id = NPC_Scene_Luigi,
        .pos = { NPC_DISPOSE_LOCATION },
        .yaw = 90,
        .init = &N(EVS_NpcInit_Luigi_Scenes),
        .settings = &N(NpcSettings_Scenes),
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_GRAVITY,
        .drops = NO_DROPS,
        .animations = LUIGI_ANIMS,
    },
};

NpcGroupList N(SceneNPCs) = {
    NPC_GROUP(N(NpcData_Scenes)),
    {}
};
