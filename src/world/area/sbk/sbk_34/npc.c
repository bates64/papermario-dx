#include "sbk_34.h"
#include "world/common/npc/Nomadimouse/idle.inc.c"

LetterDelivery N(LetterDelivery_Nomadimouse) = {
    .recipientID = NPC_Nomadimouse,
    .recipientTalk = ANIM_Nomadimouse_Talk,
    .recipientIdle = ANIM_Nomadimouse_Idle,
    .msgGreeting = MSG_CH2_005B,
    .msgCancelled = MSG_CH2_005C,
    .msgDelivered = MSG_CH2_005D,
    .msgRecieved = MSG_CH2_005E,
    .letters = { ITEM_LETTER_TO_NOMADIMOUSE },
    .reward = ITEM_STAR_PIECE,
};

EvtScript N(EVS_NpcInteract_Nomadimouse) = {
    Switch(GB_StoryProgress)
        CaseLt(STORY_CH2_ARRIVED_AT_DRY_DRY_OUTPOST)
            IfEq(GF_SBK34_Met_Nomadimouse, false)
                Call(AdjustCam, CAM_DEFAULT, Float(4.0), 0, Float(250.0), Float(15.0), Float(-6.0))
                Call(SpeakToPlayer, NPC_SELF, ANIM_Nomadimouse_Talk, ANIM_Nomadimouse_Idle, 0, MSG_CH2_0056)
                Set(GF_SBK34_Met_Nomadimouse, true)
                Call(ResetCam, CAM_DEFAULT, 4)
            Else
                Call(SpeakToPlayer, NPC_SELF, ANIM_Nomadimouse_Talk, ANIM_Nomadimouse_Idle, 0, MSG_CH2_0057)
            EndIf
        CaseLt(STORY_CH2_UNCOVERED_DRY_DRY_RUINS)
            IfEq(GF_SBK34_Met_Nomadimouse, false)
                Call(AdjustCam, CAM_DEFAULT, Float(4.0), 0, Float(250.0), Float(15.0), Float(-6.0))
                Call(SpeakToPlayer, NPC_SELF, ANIM_Nomadimouse_Talk, ANIM_Nomadimouse_Idle, 0, MSG_CH2_0058)
                Set(GF_SBK34_Met_Nomadimouse, true)
                Call(ResetCam, CAM_DEFAULT, 4)
            Else
                Call(SpeakToPlayer, NPC_SELF, ANIM_Nomadimouse_Talk, ANIM_Nomadimouse_Idle, 0, MSG_CH2_0059)
            EndIf
        CaseGe(STORY_CH2_UNCOVERED_DRY_DRY_RUINS)
            Call(SpeakToPlayer, NPC_SELF, ANIM_Nomadimouse_Talk, ANIM_Nomadimouse_Idle, 0, MSG_CH2_005A)
    EndSwitch
    Set(LVar0, Ref(N(LetterDelivery_Nomadimouse)))
    ExecWait(EVS_TryLetterDelivery)
    Return
    End
};

EvtScript N(EVS_NpcInit_Nomadimouse) = {
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_Nomadimouse)))
    Call(SetNpcAnimation, NPC_SELF, ANIM_Nomadimouse_Idle)
    Return
    End
};

EvtScript N(EVS_NpcInit_Sack) = {
    Call(SetNpcAnimation, NPC_SELF, ANIM_Nomadimouse_Sack)
    Return
    End
};

NpcData N(NpcData_Nomadimouse)[] = {
    {
        .id = NPC_Nomadimouse,
        .pos = { 114.0f, 0.0f, -50.0f },
        .yaw = 90,
        .init = &N(EVS_NpcInit_Nomadimouse),
        .settings = &N(NpcSettings_Nomadimouse),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_DO_NOT_AUTO_FACE_PLAYER,
        .drops = NO_DROPS,
        .animations = NOMADIMOUSE_ANIMS,
        .tattle = MSG_NpcTattle_SBK_Nomadimouse,
    },
    {
        .id = NPC_Sack,
        .pos = { 134.0f, 0.0f, -50.0f },
        .yaw = 90,
        .init = &N(EVS_NpcInit_Sack),
        .settings = &N(NpcSettings_Nomadimouse),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST | ENEMY_FLAG_DO_NOT_AUTO_FACE_PLAYER,
        .drops = NO_DROPS,
        .animations = NOMADIMOUSE_ANIMS,
    },
};

NpcGroupList N(DefaultNPCs) = {
    NPC_GROUP(N(NpcData_Nomadimouse)),
    {}
};
