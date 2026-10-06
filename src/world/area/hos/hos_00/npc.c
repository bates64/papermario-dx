#include "hos_00.h"

#include "world/common/npc/Toad/idle.inc.c"
#include "world/common/npc/ToadKid/idle.inc.c"
#include "world/common/npc/Toadette/idle.inc.c"
#include "world/common/npc/Twink/idle.inc.c"

#include "world/common/enemy/FlyingMagikoopa/idle.inc.c"

EvtScript EVS_Scene_Wishing = {
    Call(DisablePlayerInput, true)
    Call(UseSettingsFrom, CAM_DEFAULT, 305, -10, -50)
    Call(SetPanTarget, CAM_DEFAULT, 305, -10, -50)
    Call(SetCamDistance, CAM_DEFAULT, Float(400.0))
    Call(SetCamPitch, CAM_DEFAULT, Float(9.0), Float(-10.0))
    Call(SetCamSpeed, CAM_DEFAULT, Float(90.0))
    Call(PanToTarget, CAM_DEFAULT, 0, true)
    Call(WaitForCam, CAM_DEFAULT, Float(1.0))
    Wait(30)
    Call(SpeakToPlayer, NPC_ToadKid, ANIM_ToadKid_Red_Talk, ANIM_ToadKid_Red_Disappointed, 0, MSG_HOS_006C)
    Wait(10)
    Call(SetNpcAnimation, NPC_ToadKid, ANIM_ToadKid_Red_Idle)
    Call(SpeakToPlayer, NPC_Toadette, ANIM_Toadette_Pink_Talk, ANIM_Toadette_Pink_Idle, 0, MSG_HOS_006D)
    Wait(10)
    Call(SpeakToPlayer, NPC_ToadKid, ANIM_ToadKid_Red_Talk, ANIM_ToadKid_Red_Idle, 0, MSG_HOS_006E)
    Wait(50)
    Call(GotoMap, Ref("osr_01"), osr_01_ENTRY_3)
    Wait(100)
    Return
    End
};

EvtScript EVS_NpcDefeat_FlyingMagikoopa = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
        CaseEq(OUTCOME_PLAYER_WON)
            Call(GetPlayerPos, LVar3, LVar1, LVar2)
            Call(SetPlayerPos, LVar3, LVar1, -45)
            Add(LVar3, 40)
            Call(SetNpcPos, NPC_PARTNER, LVar3, LVar1, -45)
            Call(GetNpcPos, NPC_Twink, LVar3, LVar1, LVar2)
            Add(LVar3, -25)
            Call(SetNpcPos, NPC_Twink, LVar3, LVar1, -45)
            Exec(EVS_Scene_TwinkDeparts)
            Call(DoNpcDefeat)
        CaseEq(OUTCOME_PLAYER_LOST)
        CaseEq(OUTCOME_PLAYER_FLED)
    EndSwitch
    Return
    End
};

EvtScript EVS_NpcIdle_FlyingMagikoopa = {
    Label(0)
        Call(GetSelfVar, 0, LVar0)
        Switch(LVar0)
            CaseEq(0)
            CaseEq(1)
                Call(StartBossBattle, SONG_SPECIAL_BATTLE)
        EndSwitch
        Wait(1)
        Goto(0)
    Return
    End
};

EvtScript EVS_NpcInit_FlyingMagikoopa = {
    IfLt(GB_StoryProgress, STORY_CH0_TWINK_GAVE_LUCKY_STAR)
        Call(BindNpcIdle, NPC_SELF, Ref(EVS_NpcIdle_FlyingMagikoopa))
        Call(BindNpcDefeat, NPC_SELF, Ref(EVS_NpcDefeat_FlyingMagikoopa))
    Else
        Call(RemoveNpc, NPC_SELF)
    EndIf
    Return
    End
};

API_CALLABLE(SetCurrentPartner) {
    gPlayerData.curPartner = evt_get_variable(script, *script->ptrReadPos);
    return ApiStatus_DONE2;
}

EvtScript EVS_NpcIdle_Twink = {
    Call(SetSelfVar, 0, 0)
    Loop(0)
        Call(GetSelfVar, 0, LVar0)
        IfEq(LVar0, 1)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Call(EnablePartner, PARTNER_TWINK)
    Call(SetCurrentPartner, PARTNER_TWINK)
    Call(StartBattle)
    Return
    End
};

EvtScript EVS_NpcInteract_Twink = {
    Return
    End
};

EvtScript EVS_NpcDefeat_Twink = {
    Call(SetSelfVar, 0, 2)
    Call(DisablePartner, PARTNER_TWINK)
    Call(SetCurrentPartner, PARTNER_GOOMBARIO)
    Return
    End
};

EvtScript EVS_NpcInit_Twink = {
    Call(BindNpcIdle, NPC_SELF, Ref(EVS_NpcIdle_Twink))
    Call(BindNpcInteract, NPC_SELF, Ref(EVS_NpcInteract_Twink))
    Call(BindNpcDefeat, NPC_SELF, Ref(EVS_NpcDefeat_Twink))
    Return
    End
};

NpcData NpcData_Twink = {
    .id = NPC_Twink,
    .pos = { NPC_DISPOSE_LOCATION },
    .yaw = 90,
    .init = &EVS_NpcInit_Twink,
    .settings = &NpcSettings_Twink,
    .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
    .drops = NO_DROPS,
    .animations = TWINK_ANIMS,
};

NpcData NpcData_FlyingMagikoopa = {
    .id = NPC_FlyingMagikoopa,
    .pos = { NPC_DISPOSE_LOCATION },
    .yaw = 270,
    .init = &EVS_NpcInit_FlyingMagikoopa,
    .settings = &NpcSettings_FlyingMagikoopa,
    .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_NO_DELAY_AFTER_FLEE | ENEMY_FLAG_NO_DROPS,
    .drops = NO_DROPS,
    .animations = FLYING_MAGIKOOPA_ANIMS,
};

NpcData NpcData_Wishing[] = {
    {
        .id = NPC_Toadette,
        .pos = { 280.0f, -10.0f, -50.0f },
        .yaw = 90,
        .settings = &NpcSettings_Toadette,
        .flags = ENEMY_FLAG_PASSIVE,
        .drops = NO_DROPS,
        .animations = TOADETTE_PINK_ANIMS,
    },
    {
        .id = NPC_ToadKid,
        .pos = { 330.0f, -10.0f, -40.0f },
        .yaw = 270,
        .settings = &NpcSettings_ToadKid,
        .flags = ENEMY_FLAG_PASSIVE,
        .drops = NO_DROPS,
        .animations = TOAD_KID_RED_ANIMS,
    },
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Twink, "hos:action_command_tutorial"),
    NPC_GROUP(NpcData_FlyingMagikoopa, "hos:magikoopa_miniboss"),
    {}
};

NpcGroupList WishingNPCs = {
    NPC_GROUP(NpcData_Wishing),
    {}
};
