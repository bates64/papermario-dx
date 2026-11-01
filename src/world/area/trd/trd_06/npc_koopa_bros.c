#include "trd_06.h"
#include "world/area/trd/trd_10.h"

#include "world/common/enemy/KoopaBros/wander.inc.c"

EvtScript EVS_Scene_ImprisonedKoopaBros = {
    Wait(60)
    Call(EnableNpcAI, NPC_KoopaBros_Red, false)
    Call(SpeakToPlayer, NPC_KoopaBros_Red, ANIM_KoopaBros_Red_Dizzy, ANIM_KoopaBros_Red_Dizzy, 0, MSG_CH1_010C)
    Call(EnableNpcAI, NPC_KoopaBros_Red, true)
    Wait(30)
    Call(FadeOutMusic, 0, 2000)
    Wait(30)
    Call(GetEntryID, LVar0)
    Call(GotoMap, $trd_10.Trd06)
    Wait(100)
    Return
    End
};

NpcData NpcData_KoopaBros[] = {
    {
        .id = NPC_KoopaBros_Red,
        .pos = $KoopaBros_Red.pos,
        .yaw = $KoopaBros_Red.yaw,
        .territory = $KoopaBros_Red.territory,
        .settings = &NpcSettings_KoopaBros,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = RED_KOOPA_BROS_ANIMS,
    },
    {
        .id = NPC_KoopaBros_Black,
        .pos = $KoopaBros_Black.pos,
        .yaw = $KoopaBros_Black.yaw,
        .territory = $KoopaBros_Black.territory,
        .settings = &NpcSettings_KoopaBros,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = BLACK_KOOPA_BROS_ANIMS,
    },
    {
        .id = NPC_KoopaBros_Yellow,
        .pos = $KoopaBros_Yellow.pos,
        .yaw = $KoopaBros_Yellow.yaw,
        .territory = $KoopaBros_Yellow.territory,
        .settings = &NpcSettings_KoopaBros,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = YELLOW_KOOPA_BROS_ANIMS,
    },
    {
        .id = NPC_KoopaBros_Green,
        .pos = $KoopaBros_Green.pos,
        .yaw = $KoopaBros_Green.yaw,
        .territory = $KoopaBros_Green.territory,
        .settings = &NpcSettings_KoopaBros,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = GREEN_KOOPA_BROS_ANIMS,
    },
};

NpcGroupList NpcGroup_KoopaBros = {
    NPC_GROUP(NpcData_KoopaBros),
    {}
};
