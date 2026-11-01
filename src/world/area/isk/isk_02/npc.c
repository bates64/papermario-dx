#include "isk_02.h"

#include "world/common/enemy/PokeyMummy/wander.inc.c"

EvtScript EVS_NpcIdle_Pokey_01 = {
    Call(SetSelfEnemyFlagBits, ENEMY_FLAG_SKIP_BATTLE | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_IGNORE_PARTNER, true)
    Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_INVISIBLE, true)
    Label(1)
    IfEq(AF_ISK02_OpeningSarcophagus1, false)
        Wait(1)
        Goto(1)
    EndIf
    Wait(15)
    Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_IGNORE_WORLD_COLLISION, true)
    Call(SetSelfEnemyFlagBits, ENEMY_FLAG_SKIP_BATTLE | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_IGNORE_PARTNER, false)
    Call(NpcMoveTo, NPC_SELF, -315, 455, 10)
    Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_IGNORE_WORLD_COLLISION, false)
    Call(SetSelfEnemyFlagBits, ENEMY_FLAG_BEGIN_WITH_CHASING, true)
    Call(BindNpcAI, NPC_SELF, EVS_NpcAI_PokeyMummy_Wander)
    Return
    End
};

EvtScript EVS_NpcIdle_Pokey_02 = {
    Call(SetSelfEnemyFlagBits, ENEMY_FLAG_SKIP_BATTLE | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_IGNORE_PARTNER, true)
    Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_INVISIBLE, true)
    Label(1)
    IfEq(AF_ISK02_OpeningSarcophagus2, false)
        Wait(1)
        Goto(1)
    EndIf
    Wait(15)
    Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_IGNORE_WORLD_COLLISION, true)
    Call(SetSelfEnemyFlagBits, ENEMY_FLAG_SKIP_BATTLE | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_IGNORE_PARTNER, false)
    Call(NpcMoveTo, NPC_SELF, -145, 535, 10)
    Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_IGNORE_WORLD_COLLISION, false)
    Call(SetSelfEnemyFlagBits, ENEMY_FLAG_BEGIN_WITH_CHASING, true)
    Call(BindNpcAI, NPC_SELF, EVS_NpcAI_PokeyMummy_Wander)
    Return
    End
};

EvtScript EVS_NpcIdle_Pokey_03 = {
    Call(SetSelfEnemyFlagBits, ENEMY_FLAG_SKIP_BATTLE | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_IGNORE_PARTNER, true)
    Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_INVISIBLE, true)
    Label(1)
    IfEq(AF_ISK02_OpeningSarcophagus3, false)
        Wait(1)
        Goto(1)
    EndIf
    Wait(15)
    Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_IGNORE_WORLD_COLLISION, true)
    Call(SetSelfEnemyFlagBits, ENEMY_FLAG_SKIP_BATTLE | ENEMY_FLAG_IGNORE_TOUCH | ENEMY_FLAG_IGNORE_JUMP | ENEMY_FLAG_IGNORE_HAMMER | ENEMY_FLAG_IGNORE_PARTNER, false)
    Call(NpcMoveTo, NPC_SELF, 50, 550, 10)
    Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_IGNORE_WORLD_COLLISION, false)
    Call(SetSelfEnemyFlagBits, ENEMY_FLAG_BEGIN_WITH_CHASING, true)
    Call(BindNpcAI, NPC_SELF, EVS_NpcAI_PokeyMummy_Wander)
    Return
    End
};

EvtScript EVS_NpcInit_Pokey_01 = {
    Call(BindNpcIdle, NPC_SELF, EVS_NpcIdle_Pokey_01)
    Call(SetOwnerInstigatorValue, 3)
    Return
    End
};

EvtScript EVS_NpcInit_Pokey_02 = {
    Call(BindNpcIdle, NPC_SELF, EVS_NpcIdle_Pokey_02)
    Call(SetOwnerInstigatorValue, 3)
    Return
    End
};

EvtScript EVS_NpcInit_Pokey_03 = {
    Call(BindNpcIdle, NPC_SELF, EVS_NpcIdle_Pokey_03)
    Call(SetOwnerInstigatorValue, 3)
    Return
    End
};

NpcData NpcData_Pokey_01 = {
    .id = NPC_Pokey_01,
    .pos = $Pokey_01.pos,
    .yaw = $Pokey_01.yaw,
    .territory = $Pokey_01.territory,
    .init = &EVS_NpcInit_Pokey_01,
    .settings = &NpcSettings_PokeyMummy_Wander,
    .flags = ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_FLYING,
    .drops = POKEY_MUMMY_DROPS,
    .animations = POKEY_MUMMY_ANIMS,
};

NpcData NpcData_Pokey_02 = {
    .id = NPC_Pokey_02,
    .pos = $Pokey_02.pos,
    .yaw = $Pokey_02.yaw,
    .territory = $Pokey_02.territory,
    .init = &EVS_NpcInit_Pokey_02,
    .settings = &NpcSettings_PokeyMummy_Wander,
    .flags = ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_FLYING,
    .drops = POKEY_MUMMY_DROPS,
    .animations = POKEY_MUMMY_ANIMS,
};

NpcData NpcData_Pokey_03 = {
    .id = NPC_Pokey_03,
    .pos = $Pokey_03.pos,
    .yaw = $Pokey_03.yaw,
    .territory = $Pokey_03.territory,
    .init = &EVS_NpcInit_Pokey_03,
    .settings = &NpcSettings_PokeyMummy_Wander,
    .flags = ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_FLYING,
    .drops = POKEY_MUMMY_DROPS,
    .animations = POKEY_MUMMY_ANIMS,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Pokey_01, "isk_part_1:pokey_mummy_2", "isk_03"),
    NPC_GROUP(NpcData_Pokey_02, "isk_part_1:pokey_mummy_2", "isk_03"),
    NPC_GROUP(NpcData_Pokey_03, "isk_part_1:pokey_mummy_3", "isk_03"),
    {}
};
