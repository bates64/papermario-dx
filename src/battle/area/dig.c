#include "battle/battle.h"
#include "script_api/battle.h"

extern s16 DemoBattleBeginDelay;

static API_CALLABLE(SetDemoBattleBeginDelay) {
    DemoBattleBeginDelay = script->varTable[0];
    return ApiStatus_DONE2;
}

static API_CALLABLE(SetupDemoHammer) {
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* player = battleStatus->playerActor;
    SelectableTarget* selectableTarget;

    battleStatus->moveCategory = BTL_MENU_TYPE_SMASH;
    battleStatus->selectedMoveID = MOVE_HAMMER1;
    battleStatus->moveArgument = gCurrentEncounter.hitTier;
    battleStatus->curTargetListFlags = gMoveTable[MOVE_HAMMER1].flags;

    create_current_pos_target_list(player);
    player->selectedTargetIndex = 0;
    selectableTarget = &player->targetData[player->targetIndexList[player->selectedTargetIndex]];
    player->targetActorID = selectableTarget->actorID;
    player->targetPartID = selectableTarget->partID;

    return ApiStatus_DONE2;
}

static EvtScript EVS_Demo01 = {
    Wait(3)
    Call(SetCamViewport, CAM_BATTLE, 29, 20, 262, 177)
    Call(EnableBattleStatusBar, false)
    Set(LVar0, 15)
    Call(SetDemoBattleBeginDelay)
    Call(WaitForState, BATTLE_STATE_PLAYER_MENU)
    Call(SetupDemoHammer)
    Call(SetBattleState, BATTLE_STATE_PLAYER_MOVE)
    Wait(10000)
    Return
    End
};

static API_CALLABLE(SetupDemoPowerBounce) {
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* player = battleStatus->playerActor;
    SelectableTarget* selectableTarget;

    battleStatus->moveCategory = BTL_MENU_TYPE_JUMP;
    battleStatus->selectedMoveID = MOVE_POWER_BOUNCE;
    battleStatus->moveArgument = gCurrentEncounter.hitTier;
    battleStatus->curTargetListFlags = gMoveTable[MOVE_POWER_BOUNCE].flags;

    create_current_pos_target_list(player);
    player->selectedTargetIndex = 1;
    selectableTarget = &player->targetData[player->targetIndexList[player->selectedTargetIndex]];
    player->targetActorID = selectableTarget->actorID;
    player->targetPartID = selectableTarget->partID;

    return ApiStatus_DONE2;
}

static EvtScript EVS_Demo02 = {
    Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
    Call(MoveBattleCamOver, 1)
    Wait(3)
    Call(SetCamViewport, CAM_BATTLE, 29, 20, 262, 177)
    Call(EnableBattleStatusBar, false)
    Call(WaitForState, BATTLE_STATE_PLAYER_MENU)
    Call(SetupDemoPowerBounce)
    Call(SetBattleState, BATTLE_STATE_PLAYER_MOVE)
    Wait(130)
    Loop(30)
        Call(SetCommandAutoSuccess, false)
        Wait(1)
    EndLoop
    Return
    End
};

static API_CALLABLE(SetupDemoShellShot) {
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* partner = battleStatus->partnerActor;
    SelectableTarget* selectableTarget;

    battleStatus->moveCategory = BTL_MENU_TYPE_ABILITY;
    battleStatus->selectedMoveID = MOVE_SHELL_SHOT;
    battleStatus->moveArgument = 0;
    battleStatus->curTargetListFlags = gMoveTable[MOVE_SHELL_SHOT].flags;

    create_current_pos_target_list(partner);
    partner->selectedTargetIndex = 0;
    selectableTarget = &partner->targetData[partner->targetIndexList[partner->selectedTargetIndex]];
    partner->targetActorID = selectableTarget->actorID;
    partner->targetPartID = selectableTarget->partID;

    return ApiStatus_DONE2;
}

static EvtScript EVS_Demo03 = {
    Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
    Call(MoveBattleCamOver, 1)
    Wait(3)
    Call(SetCamViewport, CAM_BATTLE, 29, 20, 262, 177)
    Call(EnableBattleStatusBar, false)
    Call(WaitForState, BATTLE_STATE_PLAYER_MENU)
    Call(SetupDemoShellShot)
    Call(SetBattleState, BATTLE_STATE_PARTNER_MOVE)
    Wait(90)
    Return
    End
};

static API_CALLABLE(SetupDemoThunderRage) {
    BattleStatus* battleStatus = &gBattleStatus;
    PlayerData* playerData = &gPlayerData;
    s32 itemID;
    Actor* player = battleStatus->playerActor;
    SelectableTarget* selectableTarget;

    itemID = ITEM_THUNDER_RAGE;
    battleStatus->moveCategory = BTL_MENU_TYPE_ITEMS;
    battleStatus->selectedMoveID = 0;
    battleStatus->moveArgument = itemID;
    battleStatus->curAttackElement = 0;
    playerData->invItems[0] = itemID;
    battleStatus->curTargetListFlags = gItemTable[itemID].targetFlags | TARGET_FLAG_PRIMARY_ONLY;

    create_current_pos_target_list(player);
    player->selectedTargetIndex = 0;
    selectableTarget = &player->targetData[player->targetIndexList[player->selectedTargetIndex]];
    player->targetActorID = selectableTarget->actorID;
    player->targetPartID = selectableTarget->partID;

    return ApiStatus_DONE2;
}

static EvtScript EVS_Demo04 = {
    Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
    Call(MoveBattleCamOver, 1)
    Wait(3)
    Call(SetCamViewport, CAM_BATTLE, 29, 20, 262, 177)
    Call(EnableBattleStatusBar, false)
    Call(WaitForState, BATTLE_STATE_PLAYER_MENU)
    Call(SetupDemoThunderRage)
    Call(SetBattleState, BATTLE_STATE_PLAYER_MOVE)
    Return
    End
};

static EvtScript EVS_Demo05 = {
    Call(UseBattleCamPreset, BTL_CAM_DEFAULT)
    Call(MoveBattleCamOver, 1)
    Wait(3)
    Call(SetCamViewport, CAM_BATTLE, 29, 20, 262, 177)
    Call(EnableBattleStatusBar, false)
    Set(LVar0, 5)
    Call(SetDemoBattleBeginDelay)
    Call(WaitForState, BATTLE_STATE_PLAYER_MENU)
    Call(SetBattleState, BATTLE_STATE_NEXT_ENEMY)
    Return
    End
};

static Formation demo_01 = {
    OVL_ACTOR_BY_IDX("fuzzy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("fuzzy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("fuzzy", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("fuzzy", BTL_POS_GROUND_D, 7),
};

static Formation demo_02 = {
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_C, 9),
    OVL_ACTOR_BY_IDX("monty_mole", BTL_POS_GROUND_D, 8),
};

static Formation demo_03 = {
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_B, 10),
    OVL_ACTOR_BY_IDX("bandit", BTL_POS_GROUND_C, 9),
    OVL_ACTOR_BY_IDX("pokey", BTL_POS_GROUND_D, 8),
};

static Formation demo_04 = {
    OVL_ACTOR_BY_IDX("red_shy_guy", BTL_POS_GROUND_A, 10),
    OVL_ACTOR_BY_IDX("red_shy_guy", BTL_POS_GROUND_B, 9),
    OVL_ACTOR_BY_IDX("red_shy_guy", BTL_POS_GROUND_C, 8),
    OVL_ACTOR_BY_IDX("red_shy_guy", BTL_POS_GROUND_D, 7),
};

static Formation demo_05 = {
    OVL_ACTOR_BY_IDX("tubba_blubba_dig", BTL_POS_GROUND_C, 10),
};

static BattleList Formations = {
    BATTLE_WITH_SCRIPT(demo_01, "nok_04", EVS_Demo01),
    BATTLE_WITH_SCRIPT(demo_02, "iwa_01b", EVS_Demo02),
    BATTLE_WITH_SCRIPT(demo_03, "sbk_02", EVS_Demo03),
    BATTLE_WITH_SCRIPT(demo_04, "omo_04", EVS_Demo04),
    BATTLE_WITH_SCRIPT(demo_05, "dgb_05", EVS_Demo05),
};

OVL_DEF_BATTLE_AREA(Formations);
