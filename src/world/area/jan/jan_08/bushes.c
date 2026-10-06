#include "jan_08.h"
#include "foliage.h"

#include "../common/MoveBush.inc.c"
#include "../common/MoveBushTemplates.h"

EvtScript EVS_MoveBush_Separate = EVT_MOVE_BUSHES(COLLIDER_o70,
    MODEL_o67, MODEL_o68, MV_BushMoveL, MV_BushMoveR);

EvtScript EVS_Inspect_SeparateBushes = {
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o70, COLLIDER_FLAGS_UPPER_MASK)
    Exec(EVS_MoveBush_Separate)
    Call(DisablePlayerInput, true)
    Call(MakeLerp, 0, 45, 30, EASING_CUBIC_OUT)
    Loop(0)
        Call(UpdateLerp)
        SetF(MV_BushMoveR, LVar0)
        SetF(MV_BushMoveL, MV_BushMoveR)
        MulF(MV_BushMoveL, -1)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript EVS_Inspect_FlipBush = {
    Call(DisablePlayerInput, true)
    Call(PlaySoundAtCollider, COLLIDER_o88, SOUND_SEARCH_BUSH, 0)
    Loop(3)
        Call(MoveBush_AnimateShearing, LVar1, 1)
        Wait(1)
        Call(MoveBush_AnimateShearing, LVar1, 0)
        Wait(1)
        Call(MoveBush_AnimateShearing, LVar1, -1)
        Wait(1)
    EndLoop
    Call(TranslateModel, LVar1, 0, 0, 0)
    IfEq(GB_StoryProgress, STORY_CH5_SUSHIE_JOINED_PARTY)
        IfEq(GF_JAN08_SavedYoshi, false)
            Call(GetPlayerPos, LVar3, LVar4, LVar5)
            Thread
                Call(DisablePartnerAI, false)
                Call(SetNpcFlagBits, NPC_PARTNER, NPC_FLAG_IGNORE_WORLD_COLLISION | NPC_FLAG_IGNORE_CHAR_COLLISION | NPC_FLAG_IGNORE_ENTITY_COLLISION, true)
                Call(NpcMoveTo, NPC_PARTNER, -315, LVar5, 20)
                Call(NpcFaceNpc, NPC_PARTNER, NPC_YoshiKid, 0)
                Call(SetNpcFlagBits, NPC_PARTNER, NPC_FLAG_IGNORE_WORLD_COLLISION | NPC_FLAG_IGNORE_CHAR_COLLISION | NPC_FLAG_IGNORE_ENTITY_COLLISION, false)
                Call(EnablePartnerAI)
            EndThread
            Call(PlayerMoveTo, -340, LVar5, 20)
            Call(PlayerFaceNpc, NPC_YoshiKid, false)
            Wait(10)
            Call(PlaySoundAtCollider, COLLIDER_o88, SOUND_SEPARATE_BUSHES, 0)
            Set(LVar3, 0)
            Loop(10)
                Add(LVar3, 9)
                Call(RotateModel, LVar1, LVar3, 0, 1, 0)
                Wait(1)
            EndLoop
            Set(LVar4, 270)
            Call(SetNpcRotation, NPC_YoshiKid, 0, LVar4, 0)
            Call(SetNpcPos, NPC_YoshiKid, -391, 0, -144)
            Call(SetNpcFlagBits, NPC_YoshiKid, NPC_FLAG_INVISIBLE | NPC_FLAG_IGNORE_CHAR_COLLISION, false)
            Loop(10)
                Add(LVar3, 9)
                Call(RotateModel, LVar1, LVar3, 0, 1, 0)
                Add(LVar4, 9)
                Call(SetNpcRotation, NPC_YoshiKid, 0, LVar4, 0)
                Wait(1)
            EndLoop
            Call(EnableNpcShadow, NPC_YoshiKid, true)
            Call(PlayerFaceNpc, NPC_YoshiKid, false)
            Wait(20)
            Call(SetNpcVar, NPC_YoshiKid, 0, 1)
        EndIf
    EndIf
    Call(DisablePlayerInput, false)
    Return
    End
};

FoliageModelList Bush1_BushModels = FOLIAGE_MODEL_LIST(MODEL_o59);

FoliageDropList Bush1_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_COIN,
            .pos = { 117, 20, -424 },
            .spawnMode = ITEM_SPAWN_MODE_TOSS_SPAWN_ONCE,
            .pickupFlag = GF_JAN08_Bush1_Coin,
        },
    }
};

FoliageVectorList Bush1_Effects = {
    .count = 1,
    .vectors = {
        { 117.0f, 20.0f, -424.0f },
    }
};

SearchBushConfig SearchBush_Bush1 = {
    .bush = &Bush1_BushModels,
    .drops = &Bush1_Drops,
    .vectors = &Bush1_Effects,
};

FoliageModelList Bush2_BushModels = FOLIAGE_MODEL_LIST(MODEL_o164);

FoliageDropList Bush2_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_COIN,
            .pos = { -202, 20, 167 },
            .spawnMode = ITEM_SPAWN_MODE_TOSS_SPAWN_ONCE,
            .pickupFlag = GF_JAN08_Bush2_Coin,
        },
    }
};

FoliageVectorList Bush2_Effects = {
    .count = 1,
    .vectors = {
        { -202.0f, 20.0f, 167.0f },
    }
};

SearchBushConfig SearchBush_Bush2 = {
    .bush = &Bush2_BushModels,
    .drops = &Bush2_Drops,
    .vectors = &Bush2_Effects,
};

FoliageModelList Bush3_BushModels = FOLIAGE_MODEL_LIST(MODEL_o123);

FoliageVectorList Bush3_Effects = {
    .count = 1,
    .vectors = {
        { -459.0f, 20.0f, 126.0f },
    }
};

SearchBushConfig SearchBush_Bush3 = {
    .bush = &Bush3_BushModels,
    .vectors = &Bush3_Effects,
};

FoliageModelList Bush4_BushModels = FOLIAGE_MODEL_LIST(MODEL_o114);

FoliageVectorList Bush4_Effects = {
    .count = 1,
    .vectors = {
        { -461.0f, 20.0f, -39.0f },
    }
};

SearchBushConfig SearchBush_Bush4 = {
    .bush = &Bush4_BushModels,
    .vectors = &Bush4_Effects,
};

FoliageModelList Bush5_BushModels = FOLIAGE_MODEL_LIST(MODEL_o156);

FoliageVectorList Bush5_Effects = {
    .count = 1,
    .vectors = {
        { -321.0f, 20.0f, -44.0f },
    }
};

SearchBushConfig SearchBush_Bush5 = {
    .bush = &Bush5_BushModels,
    .vectors = &Bush5_Effects,
};

FoliageModelList Bush6_BushModels = FOLIAGE_MODEL_LIST(MODEL_o115);

FoliageVectorList Bush6_Effects = {
    .count = 1,
    .vectors = {
        { -279.0f, 20.0f, -55.0f },
    }
};

SearchBushConfig SearchBush_Bush6 = {
    .bush = &Bush6_BushModels,
    .vectors = &Bush6_Effects,
};

FoliageModelList Bush7_BushModels = FOLIAGE_MODEL_LIST(MODEL_o113);

FoliageVectorList Bush7_Effects = {
    .count = 1,
    .vectors = {
        { -304.0f, 22.0f, -242.0f },
    }
};

SearchBushConfig SearchBush_Bush7 = {
    .bush = &Bush7_BushModels,
    .vectors = &Bush7_Effects,
};

FoliageModelList Bush8_BushModels = FOLIAGE_MODEL_LIST(MODEL_o158);

FoliageVectorList Bush8_Effects = {
    .count = 1,
    .vectors = {
        { -95.0f, 20.0f, -485.0f },
    }
};

SearchBushConfig SearchBush_Bush8 = {
    .bush = &Bush8_BushModels,
    .vectors = &Bush8_Effects,
};

FoliageModelList Bush9_BushModels = FOLIAGE_MODEL_LIST(MODEL_o159);

FoliageVectorList Bush9_Effects = {
    .count = 1,
    .vectors = {
        { 89.0f, 20.0f, -485.0f },
    }
};

SearchBushConfig SearchBush_Bush9 = {
    .bush = &Bush9_BushModels,
    .vectors = &Bush9_Effects,
};

FoliageModelList Bush10_BushModels = FOLIAGE_MODEL_LIST(MODEL_o160);

FoliageVectorList Bush10_Effects = {
    .count = 1,
    .vectors = {
        { 152.0f, 20.0f, -489.0f },
    }
};

SearchBushConfig SearchBush_Bush10 = {
    .bush = &Bush10_BushModels,
    .vectors = &Bush10_Effects,
};

FoliageModelList Bush11_BushModels = FOLIAGE_MODEL_LIST(MODEL_o163);

FoliageVectorList Bush11_Effects = {
    .count = 1,
    .vectors = {
        { 394.0f, 20.0f, 176.0f },
    }
};

SearchBushConfig SearchBush_Bush11 = {
    .bush = &Bush11_BushModels,
    .vectors = &Bush11_Effects,
};

FoliageModelList Bush12_BushModels = FOLIAGE_MODEL_LIST(MODEL_o161);

FoliageVectorList Bush12_Effects = {
    .count = 1,
    .vectors = {
        { 239.0f, 22.0f, 430.0f },
    }
};

SearchBushConfig SearchBush_Bush12 = {
    .bush = &Bush12_BushModels,
    .vectors = &Bush12_Effects,
};

EvtScript EVS_SetupBushes = {
    BindTrigger(Ref(EVS_Inspect_SeparateBushes), TRIGGER_WALL_PRESS_A, COLLIDER_o70, 1, 0)
    Set(LVar1, MODEL_o64)
    BindPadlock(Ref(EVS_Inspect_FlipBush), TRIGGER_WALL_PRESS_A, COLLIDER_o88, 0, 0, 1)
    Set(LVar0, Ref(SearchBush_Bush1))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o59, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush2))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o209, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush3))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o210, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush4))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o211, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush5))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o212, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush6))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o213, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush7))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o214, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush8))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o215, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush9))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o216, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush10))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o217, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush11))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o218, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush12))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o219, 1, 0)
    Return
    End
};
