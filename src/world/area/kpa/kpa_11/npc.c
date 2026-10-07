#include "kpa_11.h"

#include "world/common/npc/ToadGuard/idle.inc.c"
#include "world/common/enemy/Koopatrol/wander.inc.c"
#include "world/common/npc/Toad/idle.inc.c"

EvtScript EVS_NpcDefeat_Koopatrol = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
        CaseEq(OUTCOME_PLAYER_WON)
            Set(GF_KPA11_Defeated_Guard, true)
            Call(GetNpcPos, NPC_SELF, LVar0, LVar1, LVar2)
            Call(MakeItemEntity, ITEM_BOWSER_CASTLE_KEY, LVar0, LVar1, LVar2, ITEM_SPAWN_MODE_TOSS_NEVER_VANISH, GF_KPA11_Item_CastleKey2)
            Call(DoNpcDefeat)
        CaseEq(OUTCOME_PLAYER_FLED)
        CaseEq(OUTCOME_ENEMY_FLED)
            Set(GF_KPA11_Defeated_Guard, true)
            Call(GetNpcPos, NPC_SELF, LVar0, LVar1, LVar2)
            Call(MakeItemEntity, ITEM_BOWSER_CASTLE_KEY, LVar0, LVar1, LVar2, ITEM_SPAWN_MODE_TOSS_NEVER_VANISH, GF_KPA11_Item_CastleKey2)
            Call(SetEnemyFlagBits, NPC_SELF, ENEMY_FLAG_FLED, true)
            Call(RemoveNpc, NPC_SELF)
    EndSwitch
    Return
    End
};

EvtScript EVS_NpcInit_Koopatrol = {
    IfEq(GF_KPA11_Defeated_Guard, false)
        Call(BindNpcDefeat, NPC_SELF, Ref(EVS_NpcDefeat_Koopatrol))
    Else
        Call(RemoveNpc, NPC_SELF)
    EndIf
    Return
    End
};

NpcData NpcData_Koopatrol = {
    .id = NPC_Koopatrol,
    .pos = { 550.0f, 30.0f, -145.0f },
    .yaw = 270,
    .territory = {
        .wander = {
            .isFlying = true,
            .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
            .wanderShape = SHAPE_CYLINDER,
            .centerPos  = { 550, 30, -145 },
            .wanderSize = { 30 },
            .detectShape = SHAPE_CYLINDER,
            .detectPos  = { 550, 30, -145 },
            .detectSize = { 200 },
        }
    },
    .init = &EVS_NpcInit_Koopatrol,
    .settings = &NpcSettings_Koopatrol_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_NO_DELAY_AFTER_FLEE | ENEMY_FLAG_NO_DROPS,
    .drops = NO_DROPS,
    .animations = KOOPATROL_ANIMS,
};

EvtScript EVS_NpcInit_Prisoner = {
    Return
    End
};

NpcData NpcData_Prisoners[] = {
    {
        .id = NPC_Toad_01,
#if VERSION_JP
        .pos = { 840.0f, 30.0f, -260.0f },
#else
        .pos = { 845.0f, 30.0f, -285.0f },
#endif
        .yaw = 0,
        .init = &EVS_NpcInit_Prisoner,
        .settings = &NpcSettings_Toad,
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TOAD_RED_ANIMS,
        .tattle = MSG_NpcTattle_KPA_CaptiveToadA,
    },
    {
        .id = NPC_Toad_02,
#if VERSION_JP
        .pos = { 870.0f, 30.0f, -310.0f },
#else
        .pos = { 872.0f, 30.0f, -315.0f },
#endif
        .yaw = 0,
        .init = &EVS_NpcInit_Prisoner,
        .settings = &NpcSettings_Toad,
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TOAD_BLUE_ANIMS,
        .tattle = MSG_NpcTattle_KPA_CaptiveToadB,
    },
    {
        .id = NPC_ToadGuard,
#if VERSION_JP
        .pos = { 900.0f, 30.0f, -260.0f },
#else
        .pos = { 900.0f, 30.0f, -285.0f },
#endif
        .yaw = 0,
        .init = &EVS_NpcInit_Prisoner,
        .settings = &NpcSettings_ToadGuard,
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TOAD_GUARD_YELLOW_ANIMS,
        .tattle = MSG_NpcTattle_KPA_CaptiveSoldierA,
    },
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Koopatrol, "kpa:koopatrol_2", "kpa_02"),
    NPC_GROUP(NpcData_Prisoners),
    {}
};
