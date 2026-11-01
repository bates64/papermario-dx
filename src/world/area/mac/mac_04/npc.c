#include "mac_04.h"
#include "world/area/omo/omo_03.h"
#include "sprite/player.h"
#include "world/common/enemy/ShyGuy/base.h"

#include "world/common/npc/Toad/idle.inc.c"
#include "world/common/npc/Toad/wander.inc.c"
#include "world/common/npc/ToadKid/idle.inc.c"
#include "world/common/npc/Toadette/idle.inc.c"
#include "world/common/npc/HarryT/idle.inc.c"
#include "world/common/npc/ChetRippo/idle.inc.c"

#include "world/common/npc/Goomama/idle.inc.c"
#include "world/common/npc/Goombaria/idle.inc.c"
#include "world/common/npc/StarSpirit/idle.inc.c"
#include "world/common/npc/Twink/idle.inc.c"
#include "world/common/npc/Quizmo/quiz.inc.c"

EvtScript EVS_TossTrainInToybox = {
    Call(FacePlayerTowardPoint, -440, -150, 0)
    Wait(15)
    Thread
        Wait(7)
        Call(GetPlayerPos, LVar2, LVar3, LVar4)
        Add(LVar3, 50)
        SetF(LVar5, 3)
        Call(MakeItemEntity, ITEM_TOY_TRAIN, LVar2, LVar3, LVar4, ITEM_SPAWN_MODE_DECORATION, 0)
        Set(LVar7, LVar0)
        Call(MakeLerp, LVar4, -150, 30, EASING_CUBIC_OUT)
        Loop(0)
            Call(UpdateLerp)
            Call(SetItemPos, LVar7, -440, LVar3, LVar0)
            AddF(LVar5, -0.5)
            Add(LVar3, LVar5)
            IfLt(LVar3, 0)
                Set(LVar3, 0)
            EndIf
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        Call(RemoveItemEntity, LVar7)
    EndThread
    Call(SetPlayerAnimation, ANIM_MarioW1_TakeItem)
    Wait(20)
    Call(SetPlayerAnimation, ANIM_Mario1_Idle)
    Wait(10)
    Return
    End
};

EvtScript EVS_ItemPrompt_ToyTrain = {
    SetGroup(EVT_GROUP_NEVER_PAUSE)
    Call(SetTimeFreezeMode, TIME_FREEZE_PARTIAL)
    Call(ShowKeyChoicePopup)
    Set(LVar2, LVar0)
    Switch(LVar2)
        CaseEq(ITEM_CHOICE_NONE)
            Call(ShowMessageAtScreenPos, MSG_Menus_Inspect_Toybox, 160, 40)
            Call(CloseChoicePopup)
            Call(SetTimeFreezeMode, TIME_FREEZE_NONE)
            Return
        CaseEq(ITEM_CHOICE_CANCELED)
            Call(CloseChoicePopup)
            Call(SetTimeFreezeMode, TIME_FREEZE_NONE)
            Return
    EndSwitch
    Call(DisablePlayerInput, true)
    Call(RemoveKeyItemAt, LVar1)
    Call(PlaySoundAtCollider, COLLIDER_omo_ent, SOUND_OMO_TOYBOX_LID, SOUND_SPACE_DEFAULT)
    Call(MakeLerp, 0, -90, 10, EASING_LINEAR)
    Loop(0)
        Call(UpdateLerp)
        Set(LVar2, 0)
        Sub(LVar2, LVar0)
        Div(LVar2, 3)
        Call(RotateGroup, MODEL_box_top, LVar0, 1, 0, 0)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    ExecWait(EVS_TossTrainInToybox)
    Call(MakeLerp, -90, 0, 10, EASING_LINEAR)
    Loop(0)
        Call(UpdateLerp)
        Set(LVar2, 0)
        Sub(LVar2, LVar0)
        Div(LVar2, 3)
        Call(RotateGroup, MODEL_box_top, LVar0, 1, 0, 0)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Call(PlaySoundAtCollider, COLLIDER_omo_ent, SOUND_OMO_TOYBOX_LID, SOUND_SPACE_DEFAULT)
    Call(CloseChoicePopup)
    Set(GB_StoryProgress, STORY_CH4_RETURNED_TOY_TRAIN)
    Call(SetTimeFreezeMode, TIME_FREEZE_NONE)
    Unbind
    Call(GotoMap, $omo_03.TrainReturned)
    Wait(100)
    Return
    End
};

ITEM_LIST(ItemList_ToyTrain, ITEM_TOY_TRAIN);

EvtScript EVS_Toybox_SetupTrainPrompt = {
    IfLt(GB_StoryProgress, STORY_CH4_RETURNED_TOY_TRAIN)
        BindPadlock(EVS_ItemPrompt_ToyTrain, TRIGGER_WALL_PRESS_A, COLLIDER_o468, ItemList_ToyTrain, 0, 1)
    EndIf
    Return
    End
};

s32 get_total_equipped_bp_cost(void) {
    s32 bpCost = 0;
    s32 i = 0;
    ItemData* itemTable = gItemTable;

    for (; i < ARRAY_COUNT(gPlayerData.equippedBadges); i++) {
        s16 badge = gPlayerData.equippedBadges[i];

        if (badge != 0) {
            bpCost += gMoveTable[itemTable[badge].moveID].costBP;
        }
    }
    return bpCost;
}

API_CALLABLE(EnforceNewStatLimits) {
    Bytecode* args = script->ptrReadPos;
    s32 outVar = *args++;
    s32 bpCost = get_total_equipped_bp_cost();
    s32 i;

    if (gPlayerData.maxBP >= bpCost) {
        evt_set_variable(script, outVar, false);
        return ApiStatus_DONE2;
    } else {
        s16* badges = gPlayerData.equippedBadges;
        // force unequip all badges if over the limit
        for (i = 0; i < ARRAY_COUNT(gPlayerData.equippedBadges); i++) {
            badges[i] = 0;
        }
        enforce_hpfp_limits();
        evt_set_variable(script, outVar, true);
        return ApiStatus_DONE2;
    }
}

// npc scripts
#include "npc_muskular.inc.c"
#include "npc_twink.inc.c"
#include "npc_toybox_shyguy.inc.c"
#include "npc_harry_t.inc.c"
#include "npc_chet_rippo.inc.c"
#include "npc_new_residents.inc.c"
#include "npc_toad_01.inc.c"
#include "npc_toad_02.inc.c"
#include "npc_toad_kids.inc.c"
#include "npc_toadette_03.inc.c"
#include "npc_toad_03.inc.c"
#include "npc_gossip_trio.inc.c"
#include "npc_goomba_family.inc.c"

NpcData NpcData_Townsfolk[] = {
    {
        .id = NPC_ChetRippo,
        .pos = $ChetRippo.pos,
        .yaw = $ChetRippo.yaw,
        .init = &EVS_NpcInit_ChetRippo,
        .settings = &NpcSettings_ChetRippo,
        .flags = COMMON_PASSIVE_FLAGS,
        .drops = NO_DROPS,
        .animations = CHET_RIPPO_ANIMS,
        .tattle = MSG_NpcTattle_ChetRippo,
    },
    {
        .id = NPC_HarryT,
        .pos = $HarryT.pos,
        .yaw = $HarryT.yaw,
        .init = &EVS_NpcInit_HarryT,
        .settings = &NpcSettings_HarryT,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = HARRY_T_ANIMS,
        .tattle = MSG_NpcTattle_HarryT_ShopOwner,
    },
    {
        .id = NPC_NewResident1,
        .pos = $NewResident1.pos,
        .yaw = $NewResident1.yaw,
        .init = &EVS_NpcInit_NewResident1,
        .settings = &NpcSettings_Toadette,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TOADETTE_GREEN_ANIMS,
        .tattle = MSG_NpcTattle_MAC_NewResidentA,
    },
    {
        .id = NPC_NewResident2,
        .pos = $NewResident2.pos,
        .yaw = $NewResident2.yaw,
        .init = &EVS_NpcInit_NewResident2,
        .settings = &NpcSettings_Toadette,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TOADETTE_PURPLE_ANIMS,
        .tattle = MSG_NpcTattle_MAC_NewResidentB,
    },
    {
        .id = NPC_Toad_01,
        .pos = $Toad_01.pos,
        .yaw = $Toad_01.yaw,
        .territory = $Toad_01.territory,
        .init = &EVS_NpcInit_Toad_01,
        .settings = &NpcSettings_Toad_Wander,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TOAD_BLUE_ANIMS,
        .tattle = MSG_NpcTattle_MAC_TalksAlot,
    },
    {
        .id = NPC_Toad_02,
        .pos = $Toad_02.pos,
        .yaw = $Toad_02.yaw,
        .init = &EVS_NpcInit_Toad_02,
        .settings = &NpcSettings_Toad,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TOAD_BLUE_ANIMS,
        .tattle = MSG_NpcTattle_MAC_WaryListener,
    },
    {
        .id = NPC_ToadKid_01,
        .pos = $ToadKid_01.pos,
        .yaw = $ToadKid_01.yaw,
        .init = &EVS_NpcInit_ToadKid_01,
        .settings = &NpcSettings_ToadKid,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TOAD_KID_RED_ANIMS,
        .tattle = MSG_NpcTattle_MAC_CarefreeKids,
    },
    {
        .id = NPC_ToadKid_02,
        .pos = $ToadKid_02.pos,
        .yaw = $ToadKid_02.yaw,
        .init = &EVS_NpcInit_ToadKid_02,
        .settings = &NpcSettings_ToadKid,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TOAD_KID_YELLOW_ANIMS,
        .tattle = MSG_NpcTattle_MAC_OutdoorKids,
    },
    {
        .id = NPC_ToadKid_03,
        .pos = $ToadKid_03.pos,
        .yaw = $ToadKid_03.yaw,
        .init = &EVS_NpcInit_ToadKid_03,
        .settings = &NpcSettings_ToadKid,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TOAD_KID_GREEN_ANIMS,
        .tattle = MSG_NpcTattle_MAC_ShyKid,
    },
    {
        .id = NPC_Toadette_03,
        .pos = $Toadette_03.pos,
        .yaw = $Toadette_03.yaw,
        .init = &EVS_NpcInit_Toadette_03,
        .settings = &NpcSettings_Toadette,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TOADETTE_ORANGE_ANIMS,
        .tattle = MSG_NpcTattle_ToadWhoWalks,
    },
    {
        .id = NPC_Toad_03,
        .pos = $Toad_03.pos,
        .yaw = $Toad_03.yaw,
        .init = &EVS_NpcInit_Toad_03,
        .settings = &NpcSettings_Toad,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TOAD_GREEN_ANIMS,
        .tattle = MSG_NpcTattle_GuideToad,
    },
    {
        .id = NPC_GossipTrio1,
        .pos = $GossipTrio1.pos,
        .yaw = $GossipTrio1.yaw,
        .init = &EVS_NpcInit_GossipTrio1,
        .settings = &NpcSettings_Toad,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TOAD_GREEN_ANIMS,
        .tattle = MSG_NpcTattle_GreatGossipTrioA,
    },
    {
        .id = NPC_GossipTrio2,
        .pos = $GossipTrio2.pos,
        .yaw = $GossipTrio2.yaw,
        .init = &EVS_NpcInit_GossipTrio2,
        .settings = &NpcSettings_Toad,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TOAD_RED_ANIMS,
        .tattle = MSG_NpcTattle_GreatGossipTrioB,
    },
    {
        .id = NPC_GossipTrio3,
        .pos = $GossipTrio3.pos,
        .yaw = $GossipTrio3.yaw,
        .init = &EVS_NpcInit_GossipTrio3,
        .settings = &NpcSettings_Toad,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TOAD_YELLOW_ANIMS,
        .tattle = MSG_NpcTattle_GreatGossipTrioC,
    },
};

AnimID LimitAnims_Twink[] = {
    ANIM_Twink_Idle,
    ANIM_Twink_Fly,
    ANIM_Twink_Talk,
    ANIM_LIST_END
};

NpcData NpcData_Chapter4[] = {
    {
        .id = NPC_Twink,
        .pos = $Twink.pos,
        .yaw = $Twink.yaw,
        .init = &EVS_NpcInit_TwinkStartCh4,
        .settings = &NpcSettings_Twink,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TWINK_ANIMS,
        .limitAnimations = LimitAnims_Twink,
    },
    {
        .id = NPC_ShyGuy_01,
        .pos = $ShyGuy_01.pos,
        .yaw = $ShyGuy_01.yaw,
        .settings = &NpcSettings_Toad,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = RED_SHY_GUY_ANIMS,
    },
    {
        .id = NPC_ShyGuy_02,
        .pos = $ShyGuy_02.pos,
        .yaw = $ShyGuy_02.yaw,
        .init = &EVS_NpcInit_ShyGuy_02,
        .settings = &NpcSettings_Toad,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_ENABLE_HIT_SCRIPT | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = RED_SHY_GUY_ANIMS,
    },
};

NpcData NpcData_PostChapter4[] = {
    {
        .id = NPC_Muskular,
        .pos = $Muskular.pos,
        .yaw = $Muskular.yaw,
        .init = &EVS_NpcInit_Muskular,
        .settings = &NpcSettings_StarSpirit,
        .flags = COMMON_PASSIVE_FLAGS,
        .drops = NO_DROPS,
        .animations = MUSKULAR_ANIMS,
    },
    {
        .id = NPC_Twink,
        .pos = $Twink_1.pos,
        .yaw = $Twink_1.yaw,
        .init = &EVS_NpcInit_TwinkEndCh4,
        .settings = &NpcSettings_StarSpirit,
        .flags = COMMON_PASSIVE_FLAGS,
        .drops = NO_DROPS,
        .animations = TWINK_ANIMS,
    },
};

NpcData NpcData_GoombaFamily[] = {
    {
        .id = NPC_Goomama,
        .pos = $Goomama.pos,
        .yaw = $Goomama.yaw,
        .init = &EVS_NpcInit_Goomama,
        .settings = &NpcSettings_Goomama,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = GOOMAMA_ANIMS,
        .tattle = MSG_NpcTattle_Goomama,
    },
    {
        .id = NPC_Goombaria,
        .pos = $Goombaria.pos,
        .yaw = $Goombaria.yaw,
        .init = &EVS_NpcInit_Goombaria,
        .settings = &NpcSettings_Goombaria,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = GOOMBARIA_ANIMS,
        .tattle = MSG_NpcTattle_Goombaria,
    },
};

NpcData NpcData_ChuckQuizmo = {
    .id = NPC_ChuckQuizmo,
    .pos = $ChuckQuizmo.pos,
    .yaw = $ChuckQuizmo.yaw,
    .initVarCount = 1,
    .initVar = { .bytes = { 0, QUIZ_AREA_MAC, QUIZ_COUNT_MAC, QUIZ_MAP_MAC_04 }},
    .settings = &NpcSettings_ChuckQuizmo,
    .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_HAS_NO_SPRITE,
    .drops = NO_DROPS,
    .animations = QUIZMO_ANIMS,
    .tattle = MSG_NpcTattle_ChuckQuizmo,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Townsfolk),
    NPC_GROUP(NpcData_ChuckQuizmo),
    {}
};

NpcGroupList Chapter4NPCs = {
    NPC_GROUP(NpcData_Townsfolk),
    NPC_GROUP(NpcData_Chapter4),
    {}
};

NpcGroupList PostChapter4NPCs = {
    NPC_GROUP(NpcData_Townsfolk),
    NPC_GROUP(NpcData_PostChapter4),
    {}
};

NpcGroupList Chapter7NPCs = {
    NPC_GROUP(NpcData_Townsfolk),
    NPC_GROUP(NpcData_GoombaFamily),
    {}
};
