#include "hos_03.h"
#include "sprite/player.h"

#include "world/common/npc/StarMan/idle.inc.c"
#include "world/common/npc/StarMan/wander.inc.c"

#include "world/common/prefab/ToadHouse.inc.c"
#include "world/common/prefab/ToadHouseHos.data.inc.c"

#include "world/common/npc/Quizmo/quiz.inc.c"

EvtScript EVS_NpcInteract_StarKid_01 = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_StarMan_Talk, ANIM_StarMan_Idle, 0, MSG_HOS_005F)
    Return
    End
};

EvtScript EVS_NpcInit_StarKid_01 = {
    Call(BindNpcInteract, NPC_SELF, EVS_NpcInteract_StarKid_01)
    Return
    End
};

EvtScript EVS_NpcInteract_StarKid_02 = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_StarMan_Talk, ANIM_StarMan_Idle, 0, MSG_HOS_0060)
    Return
    End
};

EvtScript EVS_NpcInit_StarKid_02 = {
    Call(BindNpcInteract, NPC_SELF, EVS_NpcInteract_StarKid_02)
    Return
    End
};

EvtScript EVS_NpcInteract_StarKid_03 = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_StarMan_Talk, ANIM_StarMan_Idle, 0, MSG_HOS_0061)
    Return
    End
};

EvtScript EVS_NpcInit_StarKid_03 = {
    Call(BindNpcInteract, NPC_SELF, EVS_NpcInteract_StarKid_03)
    Return
    End
};

EvtScript EVS_NpcInteract_StarKid_04 = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_StarMan_Talk, ANIM_StarMan_Idle, 0, MSG_HOS_0062)
    Return
    End
};

EvtScript EVS_NpcInit_StarKid_04 = {
    Call(BindNpcInteract, NPC_SELF, EVS_NpcInteract_StarKid_04)
    Return
    End
};

EvtScript EVS_NpcInteract_StarKid_05 = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_StarMan_Talk, ANIM_StarMan_Idle, 0, MSG_HOS_0063)
    Return
    End
};

EvtScript EVS_NpcInit_StarKid_05 = {
    Call(BindNpcInteract, NPC_SELF, EVS_NpcInteract_StarKid_05)
    Return
    End
};

EvtScript EVS_ToadHouse_GetInBed = {
    Exec(EVS_PlayRestingSong)
    Thread
        Wait(20)
        Call(ToadHouse_CamSetFOV, 0, 40)
        Call(SetCamType, CAM_DEFAULT, CAM_CONTROL_FIXED_POS_AND_ORIENTATION, false)
        Call(SetCamPitch, CAM_DEFAULT, 34, -8)
        Call(SetCamDistance, CAM_DEFAULT, 220)
        Call(SetCamPosA, CAM_DEFAULT, 448.0, 180.0)
        Call(SetCamPosB, CAM_DEFAULT, 410.0, 150.0)
        Call(SetCamPosC, CAM_DEFAULT, 0, 25)
        Call(SetCamSpeed, CAM_DEFAULT, 90.0)
        Call(PanToTarget, CAM_DEFAULT, 0, true)
    EndThread
    Call(func_802D1270, 442, 140, 3.0)
    Call(InterpPlayerYaw, 191, 1)
    Wait(5)
    Call(InterpPlayerYaw, 204, 1)
    Call(HidePlayerShadow, true)
    Call(SetPlayerAnimation, ANIM_Mario1_Idle)
    Call(SetPlayerImgFXFlags, IMGFX_FLAG_HOLD_DONE)
    Call(UpdatePlayerImgFX, ANIM_Mario1_Idle, IMGFX_SET_ANIM, IMGFX_ANIM_GET_IN_BED, 1, 1, 0)
    Wait(61)
    Call(SetPlayerAnimation, ANIM_MarioW2_SleepStanding)
    Thread
        Wait(70)
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
        Call(UseSettingsFrom, CAM_DEFAULT, LVar0, LVar1, LVar2)
        Wait(1)
        Call(PanToTarget, CAM_DEFAULT, 0, false)
    EndThread
    Return
    End
};

EvtScript EVS_ToadHouse_ReturnFromRest = {
    Exec(EVS_SetupMusic)
    Call(ToadHouse_CamSetFOV, 0, 25)
    Call(UpdatePlayerImgFX, ANIM_Mario1_Idle, IMGFX_CLEAR, 0, 0, 0, 0)
    Call(SetPlayerPos, 445, 25, 185)
    Call(PlayerMoveTo, 440, 215, 20)
    Return
    End
};

EvtScript EVS_ToadHouse_SetDialogue = {
    Set(LVar0, MSG_HOS_0064)
    Set(LVar8, MSG_HOS_0065)
    Set(LVar1, MSG_HOS_0066)
    Set(LVar2, MSG_HOS_0067)
    Set(LVar3, MSG_HOS_0068)
    Return
    End
};

EvtScript EVS_NpcInit_ToadHouseKeeper = {
    Call(BindNpcInteract, NPC_SELF, EVS_NpcInteract_ToadHouseKeeper)
    Return
    End
};

EvtScript EVS_NpcInteract_ShopOwner = {
    ExecWait(EVS_ShopOwnerDialog)
    Return
    End
};

EvtScript EVS_NpcInit_ShopOwner = {
    Call(BindNpcInteract, NPC_SELF, EVS_NpcInteract_ShopOwner)
    Return
    End
};

NpcData NpcData_Townsfolk[] = {
    {
        .id = NPC_StarMan_01,
        .pos = $StarMan_01.pos,
        .yaw = $StarMan_01.yaw,
        .init = &EVS_NpcInit_StarKid_01,
        .settings = &NpcSettings_StarMan,
        .flags = COMMON_PASSIVE_FLAGS,
        .drops = NO_DROPS,
        .animations = STAR_MAN_ANIMS,
        .tattle = MSG_NpcTattle_HOS_StarKidA,
    },
    {
        .id = NPC_StarMan_02,
        .pos = $StarMan_02.pos,
        .yaw = $StarMan_02.yaw,
        .init = &EVS_NpcInit_StarKid_02,
        .settings = &NpcSettings_StarMan,
        .flags = COMMON_PASSIVE_FLAGS,
        .drops = NO_DROPS,
        .animations = STAR_MAN_ANIMS,
        .tattle = MSG_NpcTattle_HOS_StarKidB,
    },
    {
        .id = NPC_StarMan_03,
        .pos = $StarMan_03.pos,
        .yaw = $StarMan_03.yaw,
        .territory = $StarMan_03.territory,
        .init = &EVS_NpcInit_StarKid_03,
        .settings = &NpcSettings_StarMan_Wander,
        .flags = COMMON_PASSIVE_FLAGS,
        .drops = NO_DROPS,
        .animations = STAR_MAN_ANIMS,
        .tattle = MSG_NpcTattle_HOS_StarKidC,
    },
    {
        .id = NPC_StarMan_04,
        .pos = $StarMan_04.pos,
        .yaw = $StarMan_04.yaw,
        .territory = $StarMan_04.territory,
        .init = &EVS_NpcInit_StarKid_04,
        .settings = &NpcSettings_StarMan_Wander,
        .flags = COMMON_PASSIVE_FLAGS,
        .drops = NO_DROPS,
        .animations = STAR_MAN_ANIMS,
        .tattle = MSG_NpcTattle_HOS_StarKidD,
    },
    {
        .id = NPC_StarMan_05,
        .pos = $StarMan_05.pos,
        .yaw = $StarMan_05.yaw,
        .init = &EVS_NpcInit_StarKid_05,
        .settings = &NpcSettings_StarMan,
        .flags = COMMON_PASSIVE_FLAGS,
        .drops = NO_DROPS,
        .animations = STAR_MAN_ANIMS,
        .tattle = MSG_NpcTattle_HOS_StarKidE,
    },
    {
        .id = NPC_StarMan_ToadHouse,
        .pos = $StarMan_ToadHouse.pos,
        .yaw = $StarMan_ToadHouse.yaw,
        .init = &EVS_NpcInit_ToadHouseKeeper,
        .settings = &NpcSettings_StarMan,
        .flags = COMMON_PASSIVE_FLAGS,
        .drops = NO_DROPS,
        .animations = STAR_MAN_ANIMS,
        .tattle = MSG_NpcTattle_HOS_ToadHouseStarKid,
    },
    {
        .id = NPC_StarMan_ShopOwner,
        .pos = $StarMan_ShopOwner.pos,
        .yaw = $StarMan_ShopOwner.yaw,
        .init = &EVS_NpcInit_ShopOwner,
        .settings = &NpcSettings_StarMan,
        .flags = COMMON_PASSIVE_FLAGS,
        .drops = NO_DROPS,
        .animations = STAR_MAN_ANIMS,
        .tattle = MSG_NpcTattle_HOS_ShopOwner,
    },
    {
        .id = NPC_ChuckQuizmo,
        .pos = $ChuckQuizmo.pos,
        .yaw = $ChuckQuizmo.yaw,
        .initVarCount = 1,
        .initVar = { .bytes = { 0, QUIZ_AREA_HOS, QUIZ_COUNT_HOS, QUIZ_MAP_HOS_03 }},
        .settings = &NpcSettings_ChuckQuizmo,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = QUIZMO_ANIMS,
        .tattle = MSG_NpcTattle_ChuckQuizmo,
    },
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Townsfolk),
    {}
};
