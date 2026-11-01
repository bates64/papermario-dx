#include "omo_01.h"

#include "world/common/enemy/ShyGuy/avoid_player.inc.c"

EvtScript EVS_ShyGuy_CarryItem = {
    Set(LVarA, LVar0) // npcID
    Set(LVarB, LVar1) // itemID
    Set(LVarD, LVar2) // item type
    Set(LVarE, LVar3) // pickup flag
    Call(SetNpcVar, LVarA, 10, 0)
    Call(GetNpcPos, LVarA, LVar2, LVar3, LVar4)
    Add(LVar3, 26)
    Call(MakeItemEntity, LVarB, LVar2, LVar3, LVar4, ITEM_SPAWN_MODE_DECORATION, 0)
    Set(LVar9, LVar0)
    Wait(1)
    Label(10)
        Call(GetNpcPos, LVarA, LVar2, LVar3, LVar4)
        Add(LVar3, 26)
        Sub(LVar4, 1)
        Call(SetItemPos, LVar9, LVar2, LVar3, LVar4)
        Wait(1)
        Call(GetNpcVar, LVarA, 10, LVar0)
        IfEq(LVar0, 0)
            Goto(10)
        EndIf
    Call(RemoveItemEntity, LVar9)
    Switch(LVarD)
        CaseEq(ITEM_TYPE_CONSUMABLE)
            Call(MakeItemEntity, LVarB, LVar2, LVar3, LVar4, ITEM_SPAWN_MODE_FALL_SPAWN_ALWAYS, LVarE)
        CaseEq(ITEM_TYPE_KEY)
            Call(DropItemEntity, LVarB, LVar2, LVar3, LVar4, ITEM_SPAWN_MODE_FALL_NEVER_VANISH, LVarE)
        CaseEq(ITEM_TYPE_BADGE)
            Call(DropItemEntity, LVarB, LVar2, LVar3, LVar4, ITEM_SPAWN_MODE_FALL, LVarE)
    EndSwitch
    Return
    End
};

EvtScript EVS_NpcDefeat_ShyGuy = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
        CaseEq(OUTCOME_PLAYER_WON)
            Set(GF_OMO09_Defeated_CalculatorThief, true)
            Call(SetSelfVar, 10, 1)
            Wait(2)
            Call(DoNpcDefeat)
        CaseEq(OUTCOME_PLAYER_FLED)
            Call(OnPlayerFled, false)
        CaseEq(OUTCOME_ENEMY_FLED)
            Call(SetEnemyFlagBits, NPC_SELF, ENEMY_FLAG_FLED, true)
            Call(RemoveNpc, NPC_SELF)
            Call(SetSelfVar, 10, 1)
    EndSwitch
    Return
    End
};

EvtScript EVS_NpcInit_ShyGuy = {
    IfEq(GF_OMO09_Defeated_CalculatorThief, true)
        IfEq(GF_OMO01_Item_Calculator, false)
            Call(RemoveNpc, NPC_SELF)
        EndIf
    EndIf
    Call(BindNpcDefeat, NPC_SELF, EVS_NpcDefeat_ShyGuy)
    Set(LVar0, NPC_ShyGuy_01)
    IfEq(GF_OMO01_Item_Calculator, false)
        Set(LVar1, ITEM_CALCULATOR)
        Set(LVar2, ITEM_TYPE_KEY)
        SetConst(LVar3, GF_OMO01_Item_Calculator)
    Else
        Set(LVar1, ITEM_MAPLE_SYRUP)
        Set(LVar2, ITEM_TYPE_CONSUMABLE)
        Set(LVar3, 0)
    EndIf
    Exec(EVS_ShyGuy_CarryItem)
    Return
    End
};

NpcData NpcData_ShyGuy_01 = {
    .id = NPC_ShyGuy_01,
    .pos = $ShyGuy_01.pos,
    .yaw = $ShyGuy_01.yaw,
    .territory = $ShyGuy_01.territory,
    .init = &EVS_NpcInit_ShyGuy,
    .settings = &NpcSettings_ShyGuy_AvoidPlayer,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = SHY_GUY_DROPS,
    .animations = RED_AVOID_SHY_GUY_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

EvtScript EVS_NpcInit_ShyGuy_02 = {
    Call(BindNpcDefeat, NPC_SELF, EVS_NpcDefeat_ShyGuy)
    Set(LVar0, NPC_ShyGuy_02)
    Set(LVar1, ITEM_CAKE_MIX)
    Set(LVar2, ITEM_TYPE_CONSUMABLE)
    Set(LVar3, 0)
    Exec(EVS_ShyGuy_CarryItem)
    Return
    End
};

NpcData NpcData_ShyGuy_02 = {
    .id = NPC_ShyGuy_02,
    .pos = $ShyGuy_02.pos,
    .yaw = $ShyGuy_02.yaw,
    .territory = $ShyGuy_02.territory,
    .init = &EVS_NpcInit_ShyGuy_02,
    .settings = &NpcSettings_ShyGuy_AvoidPlayer,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = SHY_GUY_DROPS,
    .animations = YELLOW_AVOID_SHY_GUY_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

EvtScript EVS_NpcInit_ShyGuy_03 = {
    Call(BindNpcDefeat, NPC_SELF, EVS_NpcDefeat_ShyGuy)
    Set(LVar0, NPC_ShyGuy_03)
    Set(LVar1, ITEM_CAKE_MIX)
    Set(LVar2, ITEM_TYPE_CONSUMABLE)
    Set(LVar3, 0)
    Exec(EVS_ShyGuy_CarryItem)
    Return
    End
};

NpcData NpcData_ShyGuy_03 = {
    .id = NPC_ShyGuy_03,
    .pos = $ShyGuy_03.pos,
    .yaw = $ShyGuy_03.yaw,
    .territory = $ShyGuy_03.territory,
    .init = &EVS_NpcInit_ShyGuy_03,
    .settings = &NpcSettings_ShyGuy_AvoidPlayer,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = SHY_GUY_DROPS,
    .animations = YELLOW_AVOID_SHY_GUY_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

EvtScript EVS_NpcInit_ShyGuy_04 = {
    Call(BindNpcDefeat, NPC_SELF, EVS_NpcDefeat_ShyGuy)
    Set(LVar0, NPC_ShyGuy_04)
    Set(LVar1, ITEM_MUSHROOM)
    Set(LVar2, ITEM_TYPE_CONSUMABLE)
    Set(LVar3, 0)
    Exec(EVS_ShyGuy_CarryItem)
    Return
    End
};

NpcData NpcData_ShyGuy_04 = {
    .id = NPC_ShyGuy_04,
    .pos = $ShyGuy_04.pos,
    .yaw = $ShyGuy_04.yaw,
    .territory = $ShyGuy_04.territory,
    .init = &EVS_NpcInit_ShyGuy_04,
    .settings = &NpcSettings_ShyGuy_AvoidPlayer,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = SHY_GUY_DROPS,
    .animations = BLUE_AVOID_SHY_GUY_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

EvtScript EVS_NpcInit_ShyGuy_05 = {
    Call(BindNpcDefeat, NPC_SELF, EVS_NpcDefeat_ShyGuy)
    Set(LVar0, NPC_ShyGuy_05)
    Set(LVar1, ITEM_FIRE_FLOWER)
    Set(LVar2, ITEM_TYPE_CONSUMABLE)
    Set(LVar3, 0)
    Exec(EVS_ShyGuy_CarryItem)
    Return
    End
};

NpcData NpcData_ShyGuy_05 = {
    .id = NPC_ShyGuy_05,
    .pos = $ShyGuy_05.pos,
    .yaw = $ShyGuy_05.yaw,
    .territory = $ShyGuy_05.territory,
    .init = &EVS_NpcInit_ShyGuy_05,
    .settings = &NpcSettings_ShyGuy_AvoidPlayer,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = SHY_GUY_DROPS,
    .animations = GREEN_AVOID_SHY_GUY_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_ShyGuy_01, "omo:red_shy_guy_2", "omo_01"),
    NPC_GROUP(NpcData_ShyGuy_02, "omo:yellow_shy_guy_2", "omo_01"),
    NPC_GROUP(NpcData_ShyGuy_03, "omo:yellow_shy_guy_2", "omo_01"),
    NPC_GROUP(NpcData_ShyGuy_04, "omo:blue_shy_guy_2", "omo_01"),
    NPC_GROUP(NpcData_ShyGuy_05, "omo:green_shy_guy_2", "omo_01"),
    {}
};
