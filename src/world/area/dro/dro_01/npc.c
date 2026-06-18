#include "dro_01.h"

#include "world/common/npc/Toad/idle.inc.c"
#include "world/common/npc/Toadette/idle.inc.c"
#include "world/common/npc/MusicianComposer/base.h"
#include "world/common/npc/Dryite/idle.inc.c"
#include "world/common/npc/Dryite/wander.inc.c"
#include "world/common/npc/Dryite/patrol.inc.c"
#include "world/common/npc/Mouser/idle.inc.c"
#include "world/common/npc/Quizmo/quiz.inc.c"

EvtScript N(EVS_NpcInteract_Mouser_01) = {
    IfGe(GB_StoryProgress, STORY_CH2_STAR_SPRIT_DEPARTED)
        Call(SpeakToPlayer, NPC_SELF, ANIM_Mouser_Blue_Talk, ANIM_Mouser_Blue_Idle, 0, MSG_CH2_0062)
        Return
    EndIf
    Switch(AB_DRO01_DialogueState_Mouser1)
        CaseEq(0)
            Call(SpeakToPlayer, NPC_SELF, ANIM_Mouser_Blue_Talk, ANIM_Mouser_Blue_Idle, 0, MSG_CH2_005F)
            Add(AB_DRO01_DialogueState_Mouser1, 1)
        CaseEq(1)
            Call(SpeakToPlayer, NPC_SELF, ANIM_Mouser_Blue_Talk, ANIM_Mouser_Blue_Idle, 0, MSG_CH2_0060)
            Add(AB_DRO01_DialogueState_Mouser1, 1)
        CaseEq(2)
            Call(SpeakToPlayer, NPC_SELF, ANIM_Mouser_Blue_Talk, ANIM_Mouser_Blue_Idle, 0, MSG_CH2_0061)
            Sub(AB_DRO01_DialogueState_Mouser1, 1)
    EndSwitch
    Return
    End
};

EvtScript N(EVS_NpcInit_Mouser_01) = {
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_Mouser_01)))
    Return
    End
};

EvtScript N(EVS_NpcInteract_Dryite_01) = {
    Switch(GB_StoryProgress)
        CaseLt(STORY_CH2_STAR_SPRIT_DEPARTED)
            IfGe(GB_StoryProgress, STORY_CH2_BOUGHT_SECRET_ITEMS)
                IfEq(AB_DRO01_DialogueState_Dryite1, 2)
                    Set(AB_DRO01_DialogueState_Dryite1, 0)
                EndIf
            EndIf
            Switch(AB_DRO01_DialogueState_Dryite1)
                CaseEq(0)
                    Call(SpeakToPlayer, NPC_SELF, ANIM_Dryite_Yellow_Talk, ANIM_Dryite_Yellow_Idle, 0, MSG_CH2_0063)
                    Add(AB_DRO01_DialogueState_Dryite1, 1)
                CaseEq(1)
                    Call(SpeakToPlayer, NPC_SELF, ANIM_Dryite_Yellow_Talk, ANIM_Dryite_Yellow_Idle, 0, MSG_CH2_0064)
                    Add(AB_DRO01_DialogueState_Dryite1, 1)
                CaseEq(2)
                    Call(SpeakToPlayer, NPC_SELF, ANIM_Dryite_Yellow_Talk, ANIM_Dryite_Yellow_Idle, 0, MSG_CH2_0065)
                    Set(AB_DRO01_DialogueState_Dryite1, 0)
            EndSwitch
        CaseLt(STORY_CH5_STAR_SPRIT_DEPARTED)
            Call(SpeakToPlayer, NPC_SELF, ANIM_Dryite_Yellow_Talk, ANIM_Dryite_Yellow_Idle, 0, MSG_CH2_0066)
        CaseDefault
            Call(SpeakToPlayer, NPC_SELF, ANIM_Dryite_Yellow_Talk, ANIM_Dryite_Yellow_Idle, 0, MSG_CH2_0067)
    EndSwitch
    Return
    End
};

EvtScript N(EVS_NpcInit_Dryite_01) = {
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_Dryite_01)))
    Return
    End
};

EvtScript N(EVS_NpcInteract_Dryite_02) = {
     //@bug this dialogue was probably supposed to cycle 0 --> 1 --> 2 --> 3 --> 0 ...
    Switch(AB_DRO01_DialogueState_Dryite2)
        CaseEq(0)
            Call(SpeakToPlayer, NPC_SELF, ANIM_Dryite_Blue_Talk, ANIM_Dryite_Blue_Idle, 0, MSG_CH2_0068)
            Add(AB_DRO01_DialogueState_Dryite2, 1)
        CaseEq(1)
            Call(SpeakToPlayer, NPC_SELF, ANIM_Dryite_Blue_Talk, ANIM_Dryite_Blue_Idle, 0, MSG_CH2_0069)
            Add(AB_DRO01_DialogueState_Dryite2, 1)
        CaseEq(2)
            Call(SpeakToPlayer, NPC_SELF, ANIM_Dryite_Blue_Talk, ANIM_Dryite_Blue_Idle, 0, MSG_CH2_006A)
            Add(AB_DRO01_DialogueState_Dryite2, 1)
        CaseEq(3)
            Call(SpeakToPlayer, NPC_SELF, ANIM_Dryite_Blue_Talk, ANIM_Dryite_Blue_Idle, 0, MSG_CH2_006B)
            Set(AB_DRO01_DialogueState_Dryite2, 0)
    EndSwitch
    Return
    End
};

EvtScript N(EVS_NpcInit_Dryite_02) = {
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_Dryite_02)))
    Return
    End
};

EvtScript N(EVS_NpcInteract_Toadette) = {
    Call(SpeakToPlayer, NPC_Toadette_01, ANIM_Toadette_Pink_Talk, ANIM_Toadette_Pink_Idle, 0, MSG_CH2_008E)
    Call(SpeakToPlayer, NPC_Toadette_02, ANIM_Toadette_Pink_Talk, ANIM_Toadette_Pink_Idle, 0, MSG_CH2_008F)
    Call(SpeakToPlayer, NPC_Toadette_03, ANIM_Toadette_Pink_Talk, ANIM_Toadette_Pink_Idle, 0, MSG_CH2_0090)
    Return
    End
};

EvtScript N(EVS_NpcInit_Toadette) = {
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_Toadette)))
    Return
    End
};

EvtScript N(EVS_NpcInteract_DojoGrad) = {
    Call(FindItem, ITEM_FIRST_DEGREE_CARD, LVar1)
    Call(FindItem, ITEM_SECOND_DEGREE_CARD, LVar2)
    Call(FindItem, ITEM_THIRD_DEGREE_CARD, LVar3)
    Call(FindItem, ITEM_FOURTH_DEGREE_CARD, LVar4)
    Call(FindItem, ITEM_DIPLOMA, LVar5)
    IfNe(LVar1, -1)
        Call(SpeakToPlayer, NPC_SELF, ANIM_Dryite_Brown_Talk, ANIM_Dryite_Brown_Idle, 0, MSG_CH2_009A)
        Return
    EndIf
    IfNe(LVar2, -1)
        Call(SpeakToPlayer, NPC_SELF, ANIM_Dryite_Brown_Talk, ANIM_Dryite_Brown_Idle, 0, MSG_CH2_009B)
        Return
    EndIf
    IfNe(LVar3, -1)
        Call(SpeakToPlayer, NPC_SELF, ANIM_Dryite_Brown_Talk, ANIM_Dryite_Brown_Idle, 0, MSG_CH2_009C)
        Return
    EndIf
    IfNe(LVar4, -1)
        Call(SpeakToPlayer, NPC_SELF, ANIM_Dryite_Brown_Talk, ANIM_Dryite_Brown_Idle, 0, MSG_CH2_009D)
        Return
    EndIf
    IfNe(LVar5, -1)
        Call(SpeakToPlayer, NPC_SELF, ANIM_Dryite_Brown_Talk, ANIM_Dryite_Brown_Idle, 0, MSG_CH2_009E)
        Return
    EndIf
    Call(SpeakToPlayer, NPC_SELF, ANIM_Dryite_Brown_Talk, ANIM_Dryite_Brown_Idle, 0, MSG_CH2_0099)
    Return
    End
};

EvtScript N(EVS_NpcInit_DojoGrad) = {
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_DojoGrad)))
    Return
    End
};

EvtScript N(EVS_NpcInteract_Dryite_06) = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_Dryite_Brown_Talk, ANIM_Dryite_Brown_Idle, 0, MSG_CH2_009F)
    Return
    End
};

EvtScript N(EVS_NpcInit_Dryite_06) = {
    Call(BindNpcInteract, NPC_SELF, Ref(N(EVS_NpcInteract_Dryite_06)))
    Return
    End
};

extern EvtScript N(EVS_NpcInit_HintDryite);
extern EvtScript N(EVS_NpcInit_Dryite_04);
extern EvtScript N(EVS_NpcInit_Composer);
extern EvtScript N(EVS_NpcInit_ShopOwner);

NpcData N(PassiveNPCs)[] = {
    {
        .id = NPC_Mouser_01,
        .pos = { -332.0f, 0.0f, 188.0f },
        .yaw = 90,
        .init = &N(EVS_NpcInit_Mouser_01),
        .settings = &N(NpcSettings_Mouser),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = MOUSER_BLUE_ANIMS,
        .tattle = MSG_NpcTattle_DRO_Greeter,
    },
    {
        .id = NPC_Dryite_01,
        .pos = { -235.0f, 0.0f, 160.0f },
        .yaw = 90,
        .territory = {
            .wander = {
                .isFlying = true,
                .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
                .wanderShape = SHAPE_CYLINDER,
                .centerPos  = { -235, 0, 160 },
                .wanderSize = { 30 },
                .detectShape = SHAPE_CYLINDER,
                .detectPos  = { 0, 0, 0 },
                .detectSize = { 0 },
            }
        },
        .init = &N(EVS_NpcInit_Dryite_01),
        .settings = &N(NpcSettings_Dryite_Wander),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = DRYITE_YELLOW_ANIMS,
        .tattle = MSG_NpcTattle_DRO_DryiteA,
    },
    {
        .id = NPC_Dryite_02,
        .pos = { -380.0f, 0.0f, -15.0f },
        .yaw = 61,
        .init = &N(EVS_NpcInit_Dryite_02),
        .settings = &N(NpcSettings_Dryite),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = DRYITE_BLUE_ANIMS,
        .tattle = MSG_NpcTattle_DRO_DryiteD,
    },
    {
        .id = NPC_Dryite_03,
        .pos = { 195.0f, 0.0f, -75.0f },
        .yaw = 74,
        .init = &N(EVS_NpcInit_HintDryite),
        .settings = &N(NpcSettings_Dryite),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = DRYITE_GREEN_ANIMS,
        .tattle = MSG_NpcTattle_DRO_DryiteB,
    },
    {
        .id = NPC_Dryite_04,
        .pos = { 225.0f, 0.0f, -83.0f },
        .yaw = 257,
        .init = &N(EVS_NpcInit_Dryite_04),
        .settings = &N(NpcSettings_Dryite),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = DRYITE_GREEN_ANIMS,
        .tattle = MSG_NpcTattle_DRO_DryiteC,
    },
    {
        .id = NPC_ArtistToad,
        .pos = { 285.0f, 0.0f, -274.0f },
        .yaw = 271,
        .init = &N(EVS_NpcInit_Composer),
        .settings = &N(NpcSettings_Dryite),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = MUSICIAN_COMPOSER_ANIMS,
        .tattle = MSG_NpcTattle_Composer,
    },
    {
        .id = NPC_Mouser_ShopOwner,
        .pos = { 31.0f, 0.0f, -374.0f },
        .yaw = 180,
        .init = &N(EVS_NpcInit_ShopOwner),
        .settings = &N(NpcSettings_Mouser),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = MOUSER_PURPLE_ANIMS,
        .tattle = MSG_NpcTattle_DRO_ShopOwner,
    },
    {
        .id = NPC_ChuckQuizmo,
        .pos = { -400.0f, 0.0f, 100.0f },
        .yaw = 263,
        .initVarCount = 1,
        .initVar = { .bytes = { 0, QUIZ_AREA_DRO, QUIZ_COUNT_DRO, QUIZ_MAP_DRO_01 }},
        .settings = &N(NpcSettings_ChuckQuizmo),
        .flags = BASE_PASSIVE_FLAGS,
        .drops = NO_DROPS,
        .animations = QUIZMO_ANIMS,
        .tattle = MSG_NpcTattle_ChuckQuizmo,
    },
    {
        .id = NPC_Dryite_05,
        .pos = { -120.0f, 0.0f, 134.0f },
        .yaw = 257,
        .territory = {
            .wander = {
                .isFlying = true,
                .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
                .wanderShape = SHAPE_CYLINDER,
                .centerPos  = { -120, 0, 134 },
                .wanderSize = { 40 },
                .detectShape = SHAPE_CYLINDER,
                .detectPos  = { 0, 0, 0 },
                .detectSize = { 0 },
            }
        },
        .init = &N(EVS_NpcInit_DojoGrad),
        .settings = &N(NpcSettings_Dryite_Wander),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = DRYITE_BROWN_ANIMS,
        .tattle = MSG_NpcTattle_DRO_DojoGraduate,
    },
    {
        .id = NPC_Dryite_06,
        .pos = { 40.0f, 0.0f, 105.0f },
        .yaw = 270,
        .territory = {
            .patrol = {
                .isFlying = true,
                .moveSpeedOverride = NO_OVERRIDE_MOVEMENT_SPEED,
                .numPoints  = 2,
                .points  = {
                    { 40, 0, 105 },
                    { -30, 0, 125 },
                },
                .detectShape = SHAPE_CYLINDER,
                .detectPos  = { 0, 0, 0 },
                .detectSize = { 0 },
            }
        },
        .init = &N(EVS_NpcInit_Dryite_06),
        .settings = &N(NpcSettings_Dryite_Patrol),
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = DRYITE_BROWN_ANIMS,
        .tattle = MSG_NpcTattle_DRO_WorriedDryite,
    },
};

NpcData N(ThreeSisterNPCs)[] = {
    {
        .id = NPC_Toadette_01,
        .pos = { -141.0f, 0.0f, -18.0f },
        .yaw = 62,
        .init = &N(EVS_NpcInit_Toadette),
        .settings = &N(NpcSettings_Toadette),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TOADETTE_PINK_ANIMS,
        .tattle = MSG_NpcTattle_TravelingMaidA,
    },
    {
        .id = NPC_Toadette_02,
        .pos = { -124.0f, 0.0f, -61.0f },
        .yaw = 63,
        .init = &N(EVS_NpcInit_Toadette),
        .settings = &N(NpcSettings_Toadette),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TOADETTE_PINK_ANIMS,
        .tattle = MSG_NpcTattle_TravelingMaidB,
    },
    {
        .id = NPC_Toadette_03,
        .pos = { -80.0f, 0.0f, -35.0f },
        .yaw = 244,
        .init = &N(EVS_NpcInit_Toadette),
        .settings = &N(NpcSettings_Toadette),
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TOADETTE_PINK_ANIMS,
        .tattle = MSG_NpcTattle_TravelingMaidC,
    },
};

NpcGroupList N(DefaultNPCs) = {
    NPC_GROUP(N(PassiveNPCs)),
    {},
};

NpcGroupList N(Chapter3NPCs) = {
    NPC_GROUP(N(PassiveNPCs)),
    NPC_GROUP(N(ThreeSisterNPCs)),
    {},
};
