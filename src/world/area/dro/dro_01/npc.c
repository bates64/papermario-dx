#include "dro_01.h"

#include "world/common/npc/Toad/idle.inc.c"
#include "world/common/npc/Toadette/idle.inc.c"
#include "world/common/npc/MusicianComposer/base.h"
#include "world/common/npc/Dryite/idle.inc.c"
#include "world/common/npc/Dryite/wander.inc.c"
#include "world/common/npc/Dryite/patrol.inc.c"
#include "world/common/npc/Mouser/idle.inc.c"
#include "world/common/npc/Quizmo/quiz.inc.c"

EvtScript EVS_NpcInteract_Mouser_01 = {
    IfGe(GB_StoryProgress, STORY_CH2_STAR_SPIRIT_DEPARTED)
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

EvtScript EVS_NpcInit_Mouser_01 = {
    Call(BindNpcInteract, NPC_SELF, EVS_NpcInteract_Mouser_01)
    Return
    End
};

EvtScript EVS_NpcInteract_Dryite_01 = {
    Switch(GB_StoryProgress)
        CaseLt(STORY_CH2_STAR_SPIRIT_DEPARTED)
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
        CaseLt(STORY_CH5_STAR_SPIRIT_DEPARTED)
            Call(SpeakToPlayer, NPC_SELF, ANIM_Dryite_Yellow_Talk, ANIM_Dryite_Yellow_Idle, 0, MSG_CH2_0066)
        CaseDefault
            Call(SpeakToPlayer, NPC_SELF, ANIM_Dryite_Yellow_Talk, ANIM_Dryite_Yellow_Idle, 0, MSG_CH2_0067)
    EndSwitch
    Return
    End
};

EvtScript EVS_NpcInit_Dryite_01 = {
    Call(BindNpcInteract, NPC_SELF, EVS_NpcInteract_Dryite_01)
    Return
    End
};

EvtScript EVS_NpcInteract_Dryite_02 = {
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

EvtScript EVS_NpcInit_Dryite_02 = {
    Call(BindNpcInteract, NPC_SELF, EVS_NpcInteract_Dryite_02)
    Return
    End
};

EvtScript EVS_NpcInteract_Toadette = {
    Call(SpeakToPlayer, NPC_Toadette_01, ANIM_Toadette_Pink_Talk, ANIM_Toadette_Pink_Idle, 0, MSG_CH2_008E)
    Call(SpeakToPlayer, NPC_Toadette_02, ANIM_Toadette_Pink_Talk, ANIM_Toadette_Pink_Idle, 0, MSG_CH2_008F)
    Call(SpeakToPlayer, NPC_Toadette_03, ANIM_Toadette_Pink_Talk, ANIM_Toadette_Pink_Idle, 0, MSG_CH2_0090)
    Return
    End
};

EvtScript EVS_NpcInit_Toadette = {
    Call(BindNpcInteract, NPC_SELF, EVS_NpcInteract_Toadette)
    Return
    End
};

EvtScript EVS_NpcInteract_DojoGrad = {
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

EvtScript EVS_NpcInit_DojoGrad = {
    Call(BindNpcInteract, NPC_SELF, EVS_NpcInteract_DojoGrad)
    Return
    End
};

EvtScript EVS_NpcInteract_Dryite_06 = {
    Call(SpeakToPlayer, NPC_SELF, ANIM_Dryite_Brown_Talk, ANIM_Dryite_Brown_Idle, 0, MSG_CH2_009F)
    Return
    End
};

EvtScript EVS_NpcInit_Dryite_06 = {
    Call(BindNpcInteract, NPC_SELF, EVS_NpcInteract_Dryite_06)
    Return
    End
};

extern EvtScript EVS_NpcInit_HintDryite;
extern EvtScript EVS_NpcInit_Dryite_04;
extern EvtScript EVS_NpcInit_Composer;
extern EvtScript EVS_NpcInit_ShopOwner;

NpcData PassiveNPCs[] = {
    {
        .id = NPC_Mouser_01,
        .pos = $Mouser_01.pos,
        .yaw = $Mouser_01.yaw,
        .init = &EVS_NpcInit_Mouser_01,
        .settings = &NpcSettings_Mouser,
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = MOUSER_BLUE_ANIMS,
        .tattle = MSG_NpcTattle_DRO_Greeter,
    },
    {
        .id = NPC_Dryite_01,
        .pos = $Dryite_01.pos,
        .yaw = $Dryite_01.yaw,
        .territory = $Dryite_01.territory,
        .init = &EVS_NpcInit_Dryite_01,
        .settings = &NpcSettings_Dryite_Wander,
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = DRYITE_YELLOW_ANIMS,
        .tattle = MSG_NpcTattle_DRO_DryiteA,
    },
    {
        .id = NPC_Dryite_02,
        .pos = $Dryite_02.pos,
        .yaw = $Dryite_02.yaw,
        .init = &EVS_NpcInit_Dryite_02,
        .settings = &NpcSettings_Dryite,
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = DRYITE_BLUE_ANIMS,
        .tattle = MSG_NpcTattle_DRO_DryiteD,
    },
    {
        .id = NPC_Dryite_03,
        .pos = $Dryite_03.pos,
        .yaw = $Dryite_03.yaw,
        .init = &EVS_NpcInit_HintDryite,
        .settings = &NpcSettings_Dryite,
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = DRYITE_GREEN_ANIMS,
        .tattle = MSG_NpcTattle_DRO_DryiteB,
    },
    {
        .id = NPC_Dryite_04,
        .pos = $Dryite_04.pos,
        .yaw = $Dryite_04.yaw,
        .init = &EVS_NpcInit_Dryite_04,
        .settings = &NpcSettings_Dryite,
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = DRYITE_GREEN_ANIMS,
        .tattle = MSG_NpcTattle_DRO_DryiteC,
    },
    {
        .id = NPC_ArtistToad,
        .pos = $ArtistToad.pos,
        .yaw = $ArtistToad.yaw,
        .init = &EVS_NpcInit_Composer,
        .settings = &NpcSettings_Dryite,
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = MUSICIAN_COMPOSER_ANIMS,
        .tattle = MSG_NpcTattle_Composer,
    },
    {
        .id = NPC_Mouser_ShopOwner,
        .pos = $Mouser_ShopOwner.pos,
        .yaw = $Mouser_ShopOwner.yaw,
        .init = &EVS_NpcInit_ShopOwner,
        .settings = &NpcSettings_Mouser,
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = MOUSER_PURPLE_ANIMS,
        .tattle = MSG_NpcTattle_DRO_ShopOwner,
    },
    {
        .id = NPC_ChuckQuizmo,
        .pos = $ChuckQuizmo.pos,
        .yaw = $ChuckQuizmo.yaw,
        .initVarCount = 1,
        .initVar = { .bytes = { 0, QUIZ_AREA_DRO, QUIZ_COUNT_DRO, QUIZ_MAP_DRO_01 }},
        .settings = &NpcSettings_ChuckQuizmo,
        .flags = BASE_PASSIVE_FLAGS,
        .drops = NO_DROPS,
        .animations = QUIZMO_ANIMS,
        .tattle = MSG_NpcTattle_ChuckQuizmo,
    },
    {
        .id = NPC_Dryite_05,
        .pos = $Dryite_05.pos,
        .yaw = $Dryite_05.yaw,
        .territory = $Dryite_05.territory,
        .init = &EVS_NpcInit_DojoGrad,
        .settings = &NpcSettings_Dryite_Wander,
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = DRYITE_BROWN_ANIMS,
        .tattle = MSG_NpcTattle_DRO_DojoGraduate,
    },
    {
        .id = NPC_Dryite_06,
        .pos = $Dryite_06.pos,
        .yaw = $Dryite_06.yaw,
        .territory = $Dryite_06.territory,
        .init = &EVS_NpcInit_Dryite_06,
        .settings = &NpcSettings_Dryite_Patrol,
        .flags = COMMON_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = DRYITE_BROWN_ANIMS,
        .tattle = MSG_NpcTattle_DRO_WorriedDryite,
    },
};

NpcData ThreeSisterNPCs[] = {
    {
        .id = NPC_Toadette_01,
        .pos = $Toadette_01.pos,
        .yaw = $Toadette_01.yaw,
        .init = &EVS_NpcInit_Toadette,
        .settings = &NpcSettings_Toadette,
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TOADETTE_PINK_ANIMS,
        .tattle = MSG_NpcTattle_TravelingMaidA,
    },
    {
        .id = NPC_Toadette_02,
        .pos = $Toadette_02.pos,
        .yaw = $Toadette_02.yaw,
        .init = &EVS_NpcInit_Toadette,
        .settings = &NpcSettings_Toadette,
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TOADETTE_PINK_ANIMS,
        .tattle = MSG_NpcTattle_TravelingMaidB,
    },
    {
        .id = NPC_Toadette_03,
        .pos = $Toadette_03.pos,
        .yaw = $Toadette_03.yaw,
        .init = &EVS_NpcInit_Toadette,
        .settings = &NpcSettings_Toadette,
        .flags = BASE_PASSIVE_FLAGS | ENEMY_FLAG_NO_SHADOW_RAYCAST,
        .drops = NO_DROPS,
        .animations = TOADETTE_PINK_ANIMS,
        .tattle = MSG_NpcTattle_TravelingMaidC,
    },
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(PassiveNPCs),
    {},
};

NpcGroupList Chapter3NPCs = {
    NPC_GROUP(PassiveNPCs),
    NPC_GROUP(ThreeSisterNPCs),
    {},
};
