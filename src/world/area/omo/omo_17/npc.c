#include "omo_17.h"

#include "world/common/enemy/ShyGuy/wander.inc.c"
#include "world/common/enemy/PyroGuy/wander.inc.c"
#include "world/common/enemy/GrooveGuy/wander.inc.c"
#include "world/common/enemy/SkyGuy/wander.inc.c"
#include "world/common/enemy/SpyGuy/wander.inc.c"

EvtScript EVS_NpcCreate_Conductor = {
    Return
    End
};

EvtScript EVS_NpcInteract_Conductor = {
    Return
    End
};

EvtScript EVS_NpcAI_Conductor = {
    Return
    End
};

NpcSettings NpcSettings_Conductor = {
    .defaultAnim = ANIM_TrainToad_Blue_Idle,
    .height = 24,
    .radius = 24,
    .doAI = &EVS_NpcAI_Conductor,
    .onCreate = &EVS_NpcCreate_Conductor,
    .onInteract = &EVS_NpcInteract_Conductor,
    .flags = ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
};

NpcData NpcData_Conductor = {
    .id = NPC_Conductor,
    .pos = $Conductor.pos,
    .yaw = $Conductor.yaw,
    .initVarCount = 1,
    .initVar = { .value = 0 },
    .settings = &NpcSettings_Conductor,
    .flags = ENEMY_FLAG_PASSIVE,
};

NpcData NpcData_SpyGuy[] = {
    {
        .id = NPC_SpyGuy,
        .pos = $SpyGuy.pos,
        .yaw = $SpyGuy.yaw,
        .territory = $SpyGuy.territory,
        .settings = &NpcSettings_SpyGuy_Wander,
        .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = SPY_GUY_DROPS,
        .animations = SPY_GUY_ANIMS,
        .aiDetectFlags = AI_DETECT_SIGHT,
    },
    SPY_GUY_ROCK_HITBOX(NPC_SpyGuy_Rock1),
    SPY_GUY_ROCK_HITBOX(NPC_SpyGuy_Rock2),
    SPY_GUY_ROCK_HITBOX(NPC_SpyGuy_Rock3),
};

NpcData NpcData_PyroGuy = {
    .id = NPC_PyroGuy,
    .pos = $PyroGuy.pos,
    .yaw = $PyroGuy.yaw,
    .territory = $PyroGuy.territory,
    .settings = &NpcSettings_PyroGuy_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = PYRO_GUY_DROPS,
    .animations = PYRO_GUY_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcData NpcData_GrooveGuy = {
    .id = NPC_GrooveGuy,
    .pos = $GrooveGuy.pos,
    .yaw = $GrooveGuy.yaw,
    .territory = $GrooveGuy.territory,
    .settings = &NpcSettings_GrooveGuy_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = GROOVE_GUY_DROPS_B,
    .animations = GROOVE_GUY_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_SpyGuy, "omo:spy_guy_1_medi_guy_1", "omo_05:b"),
    NPC_GROUP(NpcData_PyroGuy, "omo:pyro_guy_3", "omo_05:b"),
    NPC_GROUP(NpcData_GrooveGuy, "omo:groove_guy_1_blue_shy_guy_1_sky_guy_1", "omo_05:b"),
    NPC_GROUP(NpcData_Conductor),
    {}
};
