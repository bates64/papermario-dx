#include "iwa_02.h"

#include "world/common/enemy/MontyMole/ground_ambush.inc.c"
#include "world/common/enemy/MontyMole/wall_ambush.inc.c"
#include "world/common/enemy/Cleft/wander.inc.c"
#include "world/common/npc/Bubulb/idle.inc.c"

NpcData NpcData_Cleft_01 = {
    .id = NPC_Cleft_01,
    .pos = $Cleft_01.pos,
    .yaw = $Cleft_01.yaw,
    .territory = $Cleft_01.territory,
    .settings = &NpcSettings_Cleft_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = CLEFT_DROPS,
    .animations = CLEFT_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcData NpcData_Cleft_02 = {
    .id = NPC_Cleft_02,
    .pos = $Cleft_02.pos,
    .yaw = $Cleft_02.yaw,
    .territory = $Cleft_02.territory,
    .settings = &NpcSettings_Cleft_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = CLEFT_DROPS,
    .animations = CLEFT_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcData NpcData_Cleft_03 = {
    .id = NPC_Cleft_03,
    .pos = $Cleft_03.pos,
    .yaw = $Cleft_03.yaw,
    .territory = $Cleft_03.territory,
    .settings = &NpcSettings_Cleft_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_NO_SHADOW_RAYCAST,
    .drops = CLEFT_DROPS,
    .animations = CLEFT_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcData NpcData_MontyMole_01[] = {
    {
        .id = NPC_MontyMole,
        .pos = $MontyMole.pos,
        .yaw = $MontyMole.yaw,
        .territory = $MontyMole.territory,
        .settings = &NpcSettings_MontyMole_WallAmbush,
        .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = MONTY_MOLE_DROPS,
        .animations = MONTY_MOLE_AMBUSH_ANIMS,
        .aiDetectFlags = AI_DETECT_SIGHT,
    },
    {
        .id = NPC_MontyMole_Hole,
        .pos = $MontyMole_Hole.pos,
        .yaw = $MontyMole_Hole.yaw,
        .territory = $MontyMole_Hole.territory,
        .settings = &NpcSettings_MontyMole_WallAmbush_Hole,
        .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_DISABLE_AI | ENEMY_FLAG_IGNORE_WORLD_COLLISION | ENEMY_FLAG_IGNORE_PLAYER_COLLISION | ENEMY_FLAG_IGNORE_ENTITY_COLLISION | ENEMY_FLAG_FLYING,
        .drops = NO_DROPS,
        .animations = MONTY_MOLE_AMBUSH_ANIMS,
        .aiDetectFlags = AI_DETECT_SIGHT,
    },
};

EvtScript EVS_Bubulb_Conversation = {
    IfEq(AF_IWA_SpokeWithBubulb, false)
        Set(LVar2, LVar0)
        Set(AF_IWA_SpokeWithBubulb, true)
    Else
        Set(LVar2, LVar1)
        Set(AF_IWA_SpokeWithBubulb, false)
    EndIf
    Call(SpeakToPlayer, NPC_Bubulb, ANIM_Bubulb_Purple_Talk, ANIM_Bubulb_Purple_Idle, 0, LVar2)
    Return
    End
};

EvtScript EVS_NpcInteract_Bubulb = {
    IfEq(GF_IWA02_Gift_MagicalSeed2, false)
        Call(PlaySoundAtNpc, NPC_SELF, SOUND_BURROW_SURFACE, SOUND_SPACE_DEFAULT)
        Call(PlaySoundAtNpc, NPC_SELF, SOUND_MOLE_POP, SOUND_SPACE_DEFAULT)
        Call(SetNpcAnimation, NPC_SELF, ANIM_Bubulb_Purple_PopUp)
        Wait(45)
        Call(SetNpcAnimation, NPC_SELF, ANIM_Bubulb_Purple_Idle)
        Call(SetNpcCollisionSize, NPC_SELF, 45, 26)
        Call(AdjustCam, CAM_DEFAULT, 10.0, 0, 350, 15.0, -6.5)
        Call(SpeakToPlayer, NPC_SELF, ANIM_Bubulb_Purple_Talk, ANIM_Bubulb_Purple_Idle, 0, MSG_CH2_001F)
        EVT_GIVE_REWARD(ITEM_MAGICAL_SEED2)
        Call(SpeakToPlayer, NPC_SELF, ANIM_Bubulb_Purple_Talk, ANIM_Bubulb_Purple_Idle, 0, MSG_CH2_0020)
        Call(ResetCam, CAM_DEFAULT, 10.0)
        Set(GF_IWA02_Gift_MagicalSeed2, true)
        Call(SetTattleMessage, NPC_Bubulb, MSG_NpcTattle_IWA_Bubulb_Revealed)
    Else
        Switch(GB_StoryProgress)
            CaseLt(STORY_CH3_STAR_SPIRIT_RESCUED)
                Set(LVar0, MSG_CH2_0021)
                Set(LVar1, MSG_CH2_0022)
            CaseLt(STORY_CH5_HIDDEN_PASSAGE_OPEN)
                Set(LVar0, MSG_CH2_0023)
                Set(LVar1, MSG_CH2_0024)
            CaseDefault
                Set(LVar0, MSG_CH2_0025)
                Set(LVar1, MSG_CH2_0026)
        EndSwitch
        ExecWait(EVS_Bubulb_Conversation)
    EndIf
    Return
    End
};

EvtScript EVS_NpcInit_Bubulb = {
    Call(BindNpcInteract, NPC_SELF, EVS_NpcInteract_Bubulb)
    IfEq(GF_IWA02_Gift_MagicalSeed2, false)
        Call(SetNpcCollisionSize, NPC_SELF, 25, 25)
        Call(SetNpcAnimation, NPC_SELF, ANIM_Bubulb_Purple_BuriedIdle)
        Call(SetTattleMessage, NPC_Bubulb, MSG_NpcTattle_IWA_Bubulb_Hidden)
    EndIf
    Return
    End
};

NpcData NpcData_Bubulb = {
    .id = NPC_Bubulb,
    .pos = $Bubulb.pos,
    .yaw = $Bubulb.yaw,
    .init = &EVS_NpcInit_Bubulb,
    .settings = &NpcSettings_Bubulb,
    .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_FLYING,
    .drops = NO_DROPS,
    .animations = BUBULB_PURPLE_ANIMS,
    .tattle = MSG_NpcTattle_IWA_Bubulb_Revealed,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Cleft_01, "iwa:cleft_1_monty_mole_1", "iwa_01:b"),
    NPC_GROUP(NpcData_Cleft_02, "iwa:cleft_2", "iwa_01:b"),
    NPC_GROUP(NpcData_Cleft_03, "iwa:cleft_1", "iwa_01:b"),
    NPC_GROUP(NpcData_MontyMole_01, "iwa:monty_mole_1", "iwa_01:b"),
    NPC_GROUP(NpcData_Bubulb),
    {}
};
