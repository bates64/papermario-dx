#include "obk_03.h"

#include "world/common/npc/Boo/idle.inc.c"

LetterDelivery N(LetterDelivery_Igor) = {
    .recipientID = NPC_Igor,
    .recipientTalk = ANIM_Boo_Talk,
    .recipientIdle = ANIM_Boo_Idle,
    .msgGreeting = MSG_CH3_005D,
    .msgCancelled = MSG_CH3_005E,
    .msgDelivered = MSG_CH3_005F,
    .msgRecieved = MSG_CH3_0060,
    .letters = { ITEM_LETTER_TO_IGOR },
    .reward = ITEM_STAR_PIECE,
};

EvtScript N(EVS_NpcInteract_Igor) = {
    IfGe(GB_StoryProgress, STORY_CH3_BOW_JOINED_PARTY)
        ExecWait(EVS_ShopOwnerDialog)
    Else
        Call(SpeakToPlayer, NPC_SELF, ANIM_Boo_Talk, ANIM_Boo_Idle, 0, MSG_CH3_005C)
    EndIf
    Set(LVar0, Ref(N(LetterDelivery_Igor)))
    ExecWait(EVS_TryLetterDelivery)
    Return
    End
};

EvtScript N(EVS_NpcInit_Igor) = {
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_Igor)))
    Return
    End
};

NpcData N(NpcData_Igor) = {
    .id = NPC_Igor,
    .pos = { 43.0f, -200.0f, -9.0f },
    .yaw = 90,
    .init = &N(EVS_NpcInit_Igor),
    .settings = &N(NpcSettings_Boo),
    .flags = BASE_PASSIVE_FLAGS,
    .drops = NO_DROPS,
    .animations = NORMAL_BOO_ANIMS,
    .tattle = MSG_NpcTattle_OBK_ShopOwner,
};

NpcGroupList N(DefaultNPCs) = {
    NPC_GROUP(N(NpcData_Igor)),
    {}
};
