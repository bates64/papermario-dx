#include "dgb_08.h"
#include "world/area/dgb/dgb_01.h"

#include "world/common/npc/Yakkey/idle.inc.c"

#include "world/common/enemy/TubbaBlubba/patrol.inc.c"
#include "world/common/enemy/TubbaBlubba/idle.inc.c"

#include "world/common/enemy/Clubba/wander.inc.c"

#define AI_SENTINEL_FIRST_NPC NPC_Sentinel_01
#define AI_SENTINEL_LAST_NPC  NPC_Sentinel_02
#include "world/common/enemy/Sentinel/wander.inc.c"

NpcSettings NpcSettings_LastClubba = {
    .height = 24,
    .radius = 24,
    .level = ACTOR_LEVEL_NONE,
};

extern EvtScript EVS_NpcAI_Tubba;

EvtScript EVS_NpcIdle_Tubba = {
    Loop(0)
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
        IfGe(LVar0, -350)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Set(GB_ARN_Tubba_MapID, 8)
    Set(GB_StoryProgress, STORY_CH3_TUBBA_CHASED_MARIO_IN_HALL)
    Call(PlaySoundAtCollider, COLLIDER_deilittne, SOUND_CREAKY_DOOR_OPEN, SOUND_SPACE_DEFAULT)
    Call(MakeLerp, 0, 80, 10, EASING_LINEAR)
    Loop(0)
        Call(UpdateLerp)
        Call(RotateModel, MODEL_o140, LVar0, 0, -1, 0)
        Call(RotateModel, MODEL_o141, LVar0, 0, 1, 0)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Call(SetNpcAnimation, NPC_Tubba, ANIM_WorldTubba_WalkAngry)
    Call(SetNpcPos, NPC_SELF, -665, 210, 180)
    Call(SetNpcYaw, NPC_SELF, 90)
    Call(NpcMoveTo, NPC_SELF, -530, 180, 30)
    Thread
        Wait(20)
        Call(MakeLerp, 80, 0, 10, EASING_LINEAR)
        Loop(0)
            Call(UpdateLerp)
            Call(RotateModel, MODEL_o140, LVar0, 0, -1, 0)
            Call(RotateModel, MODEL_o141, LVar0, 0, 1, 0)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        Call(PlaySoundAtCollider, COLLIDER_deilittne, SOUND_CREAKY_DOOR_CLOSE, SOUND_SPACE_DEFAULT)
    EndThread
    Call(NpcMoveTo, NPC_SELF, -500, 80, 10)
    Call(BindNpcAI, NPC_SELF, EVS_NpcAI_Tubba)
    Return
    End
};

API_CALLABLE(SetTubbaPatrolTerritory) {
    if (get_enemy_safe(NPC_Tubba)) {
        Enemy* enemy = get_enemy(NPC_Tubba);
        enemy->territory->patrol.numPoints = 2;
        enemy->territory->patrol.points[0].x = -450;
        enemy->territory->patrol.points[0].y = 0;
        enemy->territory->patrol.points[0].z = 175;
        enemy->territory->patrol.points[1].x = 300;
        enemy->territory->patrol.points[1].y = 0;
        enemy->territory->patrol.points[1].z = 175;
        return ApiStatus_DONE2;
    }

    return ApiStatus_DONE2;
}

API_CALLABLE(SetTubbaPatrolMode) {
    if (get_enemy_safe(NPC_Tubba)) {
        Enemy* enemy = get_enemy(NPC_Tubba);
        enemy->aiFlags |= AI_FLAG_CAN_RESUME_PATROL;
        return ApiStatus_DONE2;
    }

    return ApiStatus_DONE2;
}

EvtScript EVS_SetPatrolAfterWaiting = {
    Label(10)
    Call(GetNpcPos, NPC_Tubba, LVar0, LVar1, LVar2)
    IfGt(LVar1, 0)
        Wait(1)
        Goto(10)
    EndIf
    Call(SetTubbaPatrolTerritory)
    Return
    End
};

EvtScript EVS_NpcAI_Tubba = {
    Call(SetTubbaPatrolMode)
    Exec(EVS_SetPatrolAfterWaiting)
    Thread
        Loop(0)
            Call(PlaySoundAtNpc, NPC_SELF, SOUND_HEAVY_NPC_STEP_C, SOUND_PARAM_QUIET)
            Call(ShakeCam, CAM_DEFAULT, 0, 5, 2.0)
            Wait(5)
            Call(PlaySoundAtNpc, NPC_SELF, SOUND_HEAVY_NPC_STEP_C, SOUND_PARAM_QUIET)
            Call(ShakeCam, CAM_DEFAULT, 0, 2, 1.0)
            Wait(8)
        EndLoop
    EndThread
    Call(PatrolNoAttackAI_Main, AISettings_Tubba_Patrol)
    Return
    End
};

API_CALLABLE(PostBattleHideWorld) {
    increment_status_bar_disabled();
    set_screen_overlay_params_back(OVERLAY_SCREEN_COLOR, 255.0f);
    return ApiStatus_DONE2;
}

// failsafe if the player somehow defeats Tubba
EvtScript EVS_NpcDefeat_Tubba = {
    Call(PostBattleHideWorld)
    Call(GotoMap, $dgb_01.Dgb08Lower)
    Wait(100)
    Return
    End
};

EvtScript EVS_NpcInit_Tubba = {
    IfLt(GB_StoryProgress, STORY_CH3_TUBBA_SMASHED_THE_BRIDGES)
        Call(SetNpcPos, NPC_SELF, NPC_DISPOSE_LOCATION)
        Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_INACTIVE, true)
        Return
    EndIf
    IfGe(GB_StoryProgress, STORY_CH3_TUBBA_CHASED_MARIO_IN_FOYER)
        Call(SetNpcPos, NPC_SELF, NPC_DISPOSE_LOCATION)
        Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_INACTIVE, true)
        Return
    EndIf
    Call(SetNpcScale, NPC_SELF, 1.25, 1.25, 1.25)
    Call(BindNpcDefeat, NPC_SELF, EVS_NpcDefeat_Tubba)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($Dgb01Lower.index)
            IfNe(GB_ARN_Tubba_MapID, 8)
                Call(SetNpcPos, NPC_SELF, NPC_DISPOSE_LOCATION)
                Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_INACTIVE, true)
            Else
                Call(SetNpcPos, NPC_SELF, -130, 0, 200)
                Call(BindNpcIdle, NPC_SELF, EVS_NpcAI_Tubba)
            EndIf
        CaseEq($Dgb01Upper.index)
            IfNe(GB_ARN_Tubba_MapID, 8)
                Call(BindNpcIdle, NPC_SELF, EVS_NpcIdle_Tubba)
            Else
                Call(SetNpcPos, NPC_SELF, -130, 210, 80)
                Call(BindNpcIdle, NPC_SELF, EVS_NpcAI_Tubba)
            EndIf
    EndSwitch
    Return
    End
};

NpcData NpcData_Tubba = {
    .id = NPC_Tubba,
    .pos = $Tubba.pos,
    .yaw = $Tubba.yaw,
    .territory = $Tubba.territory,
    .init = &EVS_NpcInit_Tubba,
    .settings = &NpcSettings_TubbaBlubba,
    .flags = ENEMY_FLAG_DO_NOT_KILL | ENEMY_FLAG_NO_DELAY_AFTER_FLEE | ENEMY_FLAG_ACTIVE_WHILE_OFFSCREEN | ENEMY_FLAG_NO_DROPS,
    .drops = CLUBBA_DROPS,
    .animations = TUBBA_ANGRY_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcData NpcData_Clubba_01[] = {
    {
        .id = NPC_Clubba_01,
        .pos = $Clubba_01.pos,
        .yaw = $Clubba_01.yaw,
        .territory = $Clubba_01.territory,
        .settings = &NpcSettings_Clubba_Wander,
        .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
        .drops = CLUBBA_DROPS,
        .animations = CLUBBA_ANIMS,
        .limitAnimations = LimitAnims_Clubba,
        .aiDetectFlags = AI_DETECT_MOTION_SENSITIVE,
    },
    CLUBBA_MACE_HITBOX(NPC_Clubba_01_Hitbox),
};

NpcData NpcData_Clubba_02[] = {
    {
        .id = NPC_Clubba_02,
        .pos = $Clubba_02.pos,
        .yaw = $Clubba_02.yaw,
        .territory = $Clubba_02.territory,
        .settings = &NpcSettings_Clubba_Wander,
        .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
        .drops = CLUBBA_DROPS,
        .animations = CLUBBA_ANIMS,
        .limitAnimations = LimitAnims_Clubba,
        .aiDetectFlags = AI_DETECT_MOTION_SENSITIVE,
    },
    CLUBBA_MACE_HITBOX(NPC_Clubba_02_Hitbox),
};

NpcData NpcData_Clubba_03[] = {
    {
        .id = NPC_Clubba_03,
        .pos = $Clubba_03.pos,
        .yaw = $Clubba_03.yaw,
        .territory = $Clubba_03.territory,
        .settings = &NpcSettings_Clubba_Wander,
        .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
        .drops = CLUBBA_DROPS,
        .animations = CLUBBA_ANIMS,
        .limitAnimations = LimitAnims_Clubba,
        .aiDetectFlags = AI_DETECT_SIGHT | AI_DETECT_MOTION_SENSITIVE,
    },
    CLUBBA_MACE_HITBOX(NPC_Clubba_03_Hitbox),
};

NpcData NpcData_Sentinel_01 = {
    .id = NPC_Sentinel_01,
    .pos = $Sentinel_01.pos,
    .yaw = $Sentinel_01.yaw,
    .territory = $Sentinel_01.territory,
    .settings = &NpcSettings_Sentinel_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
    .drops = NO_DROPS,
    .animations = SENTINEL_ANIMS,
};

NpcData NpcData_Sentinel_02 = {
    .id = NPC_Sentinel_02,
    .pos = $Sentinel_02.pos,
    .yaw = $Sentinel_02.yaw,
    .territory = $Sentinel_02.territory,
    .settings = &NpcSettings_Sentinel_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
    .drops = NO_DROPS,
    .animations = SENTINEL_ANIMS,
};

API_CALLABLE(PlayAlertSound) {
    ai_enemy_play_sound(get_npc_unsafe(script->owner1.enemy->npcID), SOUND_SNORE_INHALE_A, 0);
    return ApiStatus_DONE2;
}

EvtScript EVS_NpcIdle_LastClubba = {
    Label(0)
        Call(SetNpcAnimation, NPC_SELF, ANIM_WorldClubba_Sleep)
        Wait(30)
        Loop(15)
            Call(PlayAlertSound)
            Wait(60)
        EndLoop
        Call(SetNpcAnimation, NPC_SELF, ANIM_WorldClubba_Hurt)
        Wait(20)
        Call(SetNpcAnimation, NPC_SELF, ANIM_WorldClubba_Sleep)
        Wait(30)
        Loop(5)
            Call(PlayAlertSound)
            Wait(60)
        EndLoop
        Call(SetNpcAnimation, NPC_SELF, ANIM_WorldClubba_Hurt)
        Wait(15)
        Goto(0)
    Return
    End
};

EvtScript EVS_NpcInteract_LastClubba = {
    Call(SetNpcAnimation, NPC_SELF, ANIM_WorldClubba_WakeUp)
    Call(PlaySoundAtNpc, NPC_SELF, SOUND_SNAP_AWAKE_A, SOUND_SPACE_DEFAULT)
    Wait(10)
    Call(SetNpcAnimation, NPC_SELF, ANIM_WorldClubba_Idle)
    Wait(20)
    Call(GetNpcYaw, NPC_SELF, LVar0)
    Add(LVar0, 180)
    Call(InterpNpcYaw, NPC_SELF, LVar0, 0)
    Wait(10)
    Call(GetNpcYaw, NPC_SELF, LVar0)
    Add(LVar0, 180)
    Call(InterpNpcYaw, NPC_SELF, LVar0, 0)
    Wait(25)
    Call(GetNpcYaw, NPC_SELF, LVar0)
    Add(LVar0, 180)
    Call(InterpNpcYaw, NPC_SELF, LVar0, 0)
    Wait(15)
    Call(NpcFacePlayer, NPC_SELF, 0)
    Call(SpeakToPlayer, NPC_SELF, ANIM_WorldClubba_Talk, ANIM_WorldClubba_Idle, 0, MSG_CH3_00F2)
    Wait(10)
    Call(SetNpcAnimation, NPC_SELF, ANIM_WorldClubba_FallAsleep)
    Wait(10)
    Call(SetNpcAnimation, NPC_SELF, ANIM_WorldClubba_Sleep)
    Return
    End
};

EvtScript EVS_NpcInit_LastClubba = {
    Call(SetNpcCollisionSize, NPC_SELF, 36, 30)
    Call(SetNpcAnimation, NPC_SELF, ANIM_WorldClubba_Sleep)
    Call(BindNpcInteract, NPC_SELF, EVS_NpcInteract_LastClubba)
    Call(BindNpcIdle, NPC_SELF, EVS_NpcIdle_LastClubba)
    Return
    End
};

NpcData NpcData_LastClubba = {
    .id = NPC_Clubba_Last,
    .pos = $Clubba_Last.pos,
    .yaw = $Clubba_Last.yaw,
    .territory = $Clubba_Last.territory,
    .init = &EVS_NpcInit_LastClubba,
    .settings = &NpcSettings_LastClubba,
    .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_ACTIVE_WHILE_OFFSCREEN | ENEMY_FLAG_DO_NOT_AUTO_FACE_PLAYER,
    .drops = NO_DROPS,
    .animations = CLUBBA_ANIMS,
    .aiDetectFlags = AI_DETECT_MOTION_SENSITIVE,
    .tattle = MSG_NpcTattle_LastClubba,
};

EvtScript EVS_NpcIdle_Clubba_Unused = {
    Return
    End
};

EvtScript EVS_NpcInit_Clubba_Unused = {
    Call(BindNpcIdle, NPC_SELF, EVS_NpcIdle_Clubba_Unused)
    Call(SetNpcPos, NPC_SELF, NPC_DISPOSE_LOCATION)
    Return
    End
};

NpcData NpcData_Clubba_Unused = {
    .id = NPC_Clubba_Unused,
    .pos = $Clubba_Unused.pos,
    .yaw = $Clubba_Unused.yaw,
    .territory = $Clubba_Unused.territory,
    .init = &EVS_NpcInit_Clubba_Unused,
    .settings = &NpcSettings_Clubba_Wander,
    .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
    .drops = CLUBBA_DROPS,
    .animations = CLUBBA_ANIMS,
    .limitAnimations = LimitAnims_Clubba,
    .aiDetectFlags = AI_DETECT_MOTION_SENSITIVE,
};

NpcGroupList BeforeNPCs = {
    NPC_GROUP(NpcData_Clubba_Unused, "dgb:clubba_3", "dgb_03"),
    NPC_GROUP(NpcData_Clubba_01, "dgb:clubba_3", "dgb_03"),
    NPC_GROUP(NpcData_Clubba_02, "dgb:clubba_3", "dgb_03"),
    NPC_GROUP(NpcData_Clubba_03, "dgb:clubba_4", "dgb_03"),
    NPC_GROUP(NpcData_Sentinel_01),
    NPC_GROUP(NpcData_Sentinel_02),
    {}
};

NpcGroupList TubbaNPCs = {
    NPC_GROUP(NpcData_Tubba, "dgb:tubba_blubba", "dgb_01"),
    {}
};

NpcGroupList AfterNPCs = {
    NPC_GROUP(NpcData_LastClubba),
    {}
};
