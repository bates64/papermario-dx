#include "kmr_05.h"

#include "world/common/enemy/Goomba/wander.inc.c"
#include "world/common/enemy/Paragoomba/wander.inc.c"
#include "world/common/enemy/SpikedGoomba/wander.inc.c"

EvtScript EVS_GoompaRemark = {
    Call(DisablePlayerInput, true)
    Wait(10 * DT)
    Call(SetPlayerSpeed, 3.0 / DT)
    Call(PlayerMoveTo, -60, -19, 0)
    Call(DisablePartnerAI, false)
    Call(SpeakToPlayer, NPC_PARTNER, ANIM_Goompa_Talk, ANIM_Goompa_Idle, 0, MSG_CH0_00B7)
    Call(EnablePartnerAI)
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript EVS_NpcAux_SpikedGoomba = {
    Label(0)
    Call(TranslateModel, MODEL_usokinoko, -1, 0, 0)
    Wait(1)
    Call(TranslateModel, MODEL_usokinoko, 1, 0, 0)
    Wait(20)
    Call(TranslateModel, MODEL_usokinoko, 1, 0, 0)
    Wait(1)
    Call(TranslateModel, MODEL_usokinoko, -1, 0, 0)
    Wait(8)
    Call(TranslateModel, MODEL_usokinoko, -1, 0, 0)
    Wait(1)
    Call(TranslateModel, MODEL_usokinoko, 1, 0, 0)
    Wait(30)
    Goto(0)
    Return
    End
};

EvtScript EVS_NpcIdle_SpikedGoomba = {
    Label(10)
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
        Wait(1)
        IfLt(LVar1, 100)
            Goto(10)
        EndIf
        IfLt(LVar0, 560)
            Goto(10)
        EndIf
        IfGt(LVar0, 700)
            Goto(10)
        EndIf
    Call(SetNpcAux, NPC_SELF, nullptr)
    Call(ShowEmote, NPC_SELF, EMOTE_EXCLAMATION, -30, 12, EMOTER_NPC, 0, 0, 0, 0)
    Call(SetNpcJumpscale, NPC_SELF, 1.0)
    Call(SetNpcSpeed, NPC_SELF, 5.0)
    Call(NpcJump0, NPC_SELF, 685, 100, -35, 0)
    Call(SetSelfEnemyFlagBits, ENEMY_FLAG_BEGIN_WITH_CHASING, true)
    Call(BindNpcAI, NPC_SELF, EVS_NpcAI_SpikedGoomba_Wander)
    Return
    End
};

NpcData NpcData_Goomba_01 = {
    .id = NPC_Goomba_01,
    .pos = $Goomba_01.pos,
    .yaw = $Goomba_01.yaw,
    .territory = $Goomba_01.territory,
    .settings = &NpcSettings_Goomba_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
    .drops = GOOMBA_DROPS,
    .animations = GOOMBA_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcData NpcData_Goomba_02 = {
    .id = NPC_Goomba_02,
    .pos = $Goomba_02.pos,
    .yaw = $Goomba_02.yaw,
    .territory = $Goomba_02.territory,
    .settings = &NpcSettings_Goomba_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
    .drops = GOOMBA_DROPS,
    .animations = GOOMBA_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

EvtScript EVS_NpcInit_SpikedGoomba = {
    Call(BindNpcIdle, NPC_SELF, EVS_NpcIdle_SpikedGoomba)
    Call(BindNpcAux, NPC_SELF, EVS_NpcAux_SpikedGoomba)
    Return
    End
};

NpcData NpcData_SpikedGoomba = {
    .id = NPC_SpikedGoomba,
    .pos = $SpikedGoomba.pos,
    .yaw = $SpikedGoomba.yaw,
    .territory = $SpikedGoomba.territory,
    .init = &EVS_NpcInit_SpikedGoomba,
    .settings = &NpcSettings_SpikedGoomba_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
    .drops = SPIKED_GOOMBA_DROPS,
    .animations = SPIKED_GOOMBA_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcData NpcData_Paragoomba = {
    .id = NPC_Paragoomba,
    .pos = $Paragoomba.pos,
    .yaw = $Paragoomba.yaw,
    .territory = $Paragoomba.territory,
    .settings = &NpcSettings_Paragoomba_Wander,
    .flags = ENEMY_FLAG_IGNORE_ENTITY_COLLISION,
    .drops = PARAGOOMBA_DROPS,
    .animations = PARAGOOMBA_ANIMS,
    .aiDetectFlags = AI_DETECT_SIGHT,
};

NpcGroupList NpcsBefore = {
    NPC_GROUP(NpcData_Goomba_01, "kmr_part_1:goomba_1", "kmr_05"),
    NPC_GROUP(NpcData_Goomba_02, "kmr_part_1:goomba_1", "kmr_05"),
    NPC_GROUP(NpcData_SpikedGoomba, "kmr_part_3:spiked_goomba_tutorial", "kmr_05:b"),
    NPC_GROUP(NpcData_Paragoomba, "kmr_part_3:paragoomba_tutorial", "kmr_05:b"),
    {}
};

NpcGroupList NpcsAfter = {
    NPC_GROUP(NpcData_Goomba_01, "kmr_part_1:goomba_1", "kmr_05"),
    NPC_GROUP(NpcData_Goomba_02, "kmr_part_1:goomba_1", "kmr_05"),
    NPC_GROUP(NpcData_SpikedGoomba, "kmr_part_1:spiked_goomba_1", "kmr_05"),
    NPC_GROUP(NpcData_Paragoomba, "kmr_part_1:paragoomba_2", "kmr_05"),
    {}
};
