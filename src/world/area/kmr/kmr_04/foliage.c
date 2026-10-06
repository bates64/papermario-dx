#include "kmr_04.h"
#include "sprite/player.h"
#include "include_asset.h"

#include "foliage.h"
#include "effects.h"

#include "world/area/kmr/kmr_04/hammer_block_message.png.h"
INCLUDE_IMG("world/area/kmr/kmr_04/hammer_block_message.png", kmr_04_hammer_block_message_img);
INCLUDE_PAL("world/area/kmr/kmr_04/hammer_block_message.pal", kmr_04_hammer_block_message_pal);

static MessageImageData MessageImage;

API_CALLABLE(SetMessageImage_HammerBlock) {
    MessageImage.raster = kmr_04_hammer_block_message_img;
    MessageImage.palette = kmr_04_hammer_block_message_pal;
    MessageImage.width = kmr_04_hammer_block_message_img_width;
    MessageImage.height = kmr_04_hammer_block_message_img_height;
    MessageImage.format = G_IM_FMT_CI;
    MessageImage.bitDepth = G_IM_SIZ_4b;
    set_message_images(&MessageImage);
    return ApiStatus_DONE2;
}

API_CALLABLE(GiveWoodenHammer) {
    gPlayerData.hammerLevel = GEAR_RANK_NORMAL;

    return ApiStatus_DONE2;
}

EvtScript EVS_GotHammer = {
    Call(SetPlayerAnimation, ANIM_MarioW1_Lift)
    Call(GetPlayerPos, LVar5, LVar6, LVar7)
    Add(LVar6, 40)
    Call(MakeItemEntity, ITEM_HAMMER, LVar5, LVar6, LVar7, ITEM_SPAWN_MODE_DECORATION, 0)
    Set(LVarC, LVar0)
    Add(LVar6, 16)
    PlayEffect(EFFECT_GOT_ITEM_OUTLINE, 0, LVar5, LVar6, LVar7, Float(1.0), LVar8)
    PlayEffect(EFFECT_RADIAL_SHIMMER, 9, LVar5, LVar6, LVar7, Float(1.0), 100)
    Exec(EVS_PlayUpgradeSong)
    Thread
        Wait(4 * DT)
        Call(GetPlayerPos, LVar3, LVar4, LVar5)
        Add(LVar4, 50)
        Add(LVar5, 2)
        Add(LVar3, 8)
        PlayEffect(EFFECT_SPARKLES, 3, LVar3, LVar4, LVar5, 20)
        Add(LVar3, -16)
        PlayEffect(EFFECT_SPARKLES, 3, LVar3, LVar4, LVar5, 20)
    EndThread
    Loop(0)
        Wait(1)
        IfEq(MF_GotHammerDone, true)
            BreakLoop
        EndIf
    EndLoop
    Call(DismissItemOutline, LVar8)
    Call(RemoveItemEntity, LVarC)
    Call(SetPlayerAnimation, ANIM_Mario1_Idle)
    Return
    End
};

EvtScript EVS_OnSearch_HammerBush = {
    Call(AdjustCam, CAM_DEFAULT, Float(8.0), 0, Float(300.0), Float(19.0), Float(-9.0))
    Set(MF_GotHammerDone, false)
    Exec(EVS_GotHammer)
    Call(GiveWoodenHammer)
    Wait(30 * DT)
    Call(SetMessageImage_HammerBlock)
    Call(ShowMessageAtScreenPos, MSG_Menus_Inspect_FoundHammer, 160, 40)
    Set(MF_GotHammerDone, true)
    Call(DisablePartnerAI, false)
    Wait(10 * DT)
    Call(SpeakToPlayer, NPC_PARTNER, ANIM_Goompa_Talk, ANIM_Goompa_Idle, 0, MSG_CH0_00AA)
    Call(SetNpcAnimation, NPC_PARTNER, ANIM_Goompa_Idle)
    Set(GB_StoryProgress, STORY_CH0_FOUND_HAMMER)
    Call(ClearPartnerMoveHistory, NPC_PARTNER)
    Call(EnablePartnerAI)
    Thread
#if VERSION_PAL
        Call(ResetCam, CAM_DEFAULT, Float(3 * DT))
#else
        Call(ResetCam, CAM_DEFAULT, 3)
#endif
    EndThread
    Return
    End
};

EvtScript EVS_OnSearchBush7 = {
    IfGe(GB_StoryProgress, STORY_CH0_FOUND_HAMMER)
        Return
    EndIf
    Call(DisablePlayerInput, true)
    ExecWait(EVS_OnSearch_HammerBush)
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript EVS_OnSearchBush8 = {
    IfGe(GB_StoryProgress, STORY_CH0_FOUND_HAMMER)
        Return
    EndIf
    Call(DisablePlayerInput, true)
    Call(MakeLerp, 0, 85, 20 * DT, EASING_COS_IN_OUT)
    Label(0)
    Call(UpdateLerp)
    Call(RotateModel, MODEL_o213, LVar0, 1, 0, 0)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(0)
    EndIf
    ExecWait(EVS_OnSearch_HammerBush)
    Call(MakeLerp, 85, 0, 20 * DT, EASING_COS_IN_OUT)
    Label(10)
    Call(UpdateLerp)
    Call(RotateModel, MODEL_o213, LVar0, 1, 0, 0)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(10)
    EndIf
    Call(DisablePlayerInput, false)
    Return
    End
};

FoliageModelList Bush1_BushModels = FOLIAGE_MODEL_LIST(MODEL_o181);

FoliageDropList Bush1_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_COIN,
            .pos = { 248, 17, 97 },
            .spawnMode = ITEM_SPAWN_MODE_TOSS_SPAWN_ONCE,
            .pickupFlag = GF_KMR04_Bush1_Coin,
            .spawnFlag = MF_Drop_Bush1,
        },
    }
};

FoliageVectorList Bush1_Effects = {
    .count = 1,
    .vectors = {
        { 248.0f, 17.0f, 97.0f },
    }
};

SearchBushConfig SearchBush_Bush1 = {
    .bush = &Bush1_BushModels,
    .drops = &Bush1_Drops,
    .vectors = &Bush1_Effects,
};

FoliageModelList Bush2_BushModels = FOLIAGE_MODEL_LIST(MODEL_o212);

FoliageDropList Bush2_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_COIN,
            .pos = { 99, 17, 237 },
            .spawnMode = ITEM_SPAWN_MODE_TOSS,
            .pickupFlag = GF_KMR04_Bush2_Coin,
            .spawnFlag = MF_Drop_Bush2,
        },
    }
};

FoliageVectorList Bush2_Effects = {
    .count = 1,
    .vectors = {
        { 100.0f, 19.0f, 246.0f },
    }
};

SearchBushConfig SearchBush_Bush2 = {
    .bush = &Bush2_BushModels,
    .drops = &Bush2_Drops,
    .vectors = &Bush2_Effects,
};

FoliageModelList Bush3_BushModels = FOLIAGE_MODEL_LIST(MODEL_o235);

FoliageDropList Bush3_Drops = {
    .count = 2,
    .drops = {
        {
            .itemID = ITEM_COIN,
            .pos = { 50, 18, -200 },
            .spawnMode = ITEM_SPAWN_MODE_TOSS_SPAWN_ONCE,
            .pickupFlag = GF_KMR04_Bush3_CoinA,
            .spawnFlag = MF_Drop_Bush3A,
        },
        {
            .itemID = ITEM_COIN,
            .pos = { 50, 18, -200 },
            .spawnMode = ITEM_SPAWN_MODE_TOSS_SPAWN_ONCE,
            .pickupFlag = GF_KMR04_Bush3_CoinB,
            .spawnFlag = MF_Drop_Bush3B,
        },
    }
};

FoliageVectorList Bush3_Effects = {
    .count = 1,
    .vectors = {
        { 50.0f, 18.0f, -200.0f },
    }
};

SearchBushConfig SearchBush_Bush3 = {
    .bush = &Bush3_BushModels,
    .drops = &Bush3_Drops,
    .vectors = &Bush3_Effects,
};

FoliageModelList Bush4_BushModels = FOLIAGE_MODEL_LIST(MODEL_o182);

FoliageDropList Bush4_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_COIN,
            .pos = { -49, 20, 146 },
            .spawnMode = ITEM_SPAWN_MODE_TOSS_SPAWN_ONCE,
            .pickupFlag = GF_KMR04_Bush4_Coin,
            .spawnFlag = MF_Drop_Bush4,
        },
    }
};

FoliageVectorList Bush4_Effects = {
    .count = 1,
    .vectors = {
        { -49.0f, 20.0f, 146.0f },
    }
};

SearchBushConfig SearchBush_Bush4 = {
    .bush = &Bush4_BushModels,
    .drops = &Bush4_Drops,
    .vectors = &Bush4_Effects,
};

FoliageModelList Bush5_BushModels = FOLIAGE_MODEL_LIST(MODEL_o205);

FoliageDropList Bush5_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_COIN,
            .pos = { -148, 16, -150 },
            .spawnMode = ITEM_SPAWN_MODE_TOSS_SPAWN_ONCE,
            .pickupFlag = GF_KMR04_Bush5_Coin,
            .spawnFlag = MF_Drop_Bush5,
        },
    }
};

FoliageVectorList Bush5_Effects = {
    .count = 1,
    .vectors = {
        { -148.0f, 16.0f, -150.0f },
    }
};

SearchBushConfig SearchBush_Bush5 = {
    .bush = &Bush5_BushModels,
    .drops = &Bush5_Drops,
    .vectors = &Bush5_Effects,
};

FoliageModelList Bush8_BushModels = FOLIAGE_MODEL_LIST(MODEL_o213);

FoliageVectorList Bush8_Effects = {
    .count = 1,
    .vectors = {
        { -224.0f, 20.0f, 96.0f },
    }
};

SearchBushConfig SearchBush_Bush7 = {
    .bush = &Bush8_BushModels,
    .vectors = &Bush8_Effects,
    .callback = &EVS_OnSearchBush7,
};

SearchBushConfig SearchBush_Bush8 = {
    .bush = &Bush8_BushModels,
    .vectors = &Bush8_Effects,
    .callback = &EVS_OnSearchBush8,
};

FoliageModelList Bush6_BushModels = FOLIAGE_MODEL_LIST(MODEL_o213);

FoliageVectorList Bush6_Effects = {
    .count = 1,
    .vectors = {
        { -224.0f, 20.0f, 96.0f },
    }
};

SearchBushConfig SearchBush_Bush6 = {
    .bush = &Bush6_BushModels,
    .vectors = &Bush6_Effects,
};

FoliageModelList Bush9_BushModels = FOLIAGE_MODEL_LIST(MODEL_o239);

FoliageVectorList Bush9_Effects = {
    .count = 1,
    .vectors = {
        { -174.0f, 19.0f, 296.0f },
    }
};

SearchBushConfig SearchBush_Bush9 = {
    .bush = &Bush9_BushModels,
    .vectors = &Bush9_Effects,
};

FoliageModelList Tree1_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o237);
FoliageModelList Tree1_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o236);

FoliageDropList Tree1_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_COIN,
            .pos = { -302, 128, 2 },
            .spawnMode = ITEM_SPAWN_MODE_FALL_SPAWN_ONCE,
            .pickupFlag = GF_KMR04_Tree1_Coin,
        },
    }
};

FoliageVectorList Tree1_Effects = {
    .count = 2,
    .vectors = {
        { -391.0f, 150.0f, 20.0f },
        { -267.0f, 150.0f, 22.0f },
    }
};

ShakeTreeConfig ShakeTree_Tree1 = {
    .leaves = &Tree1_LeafModels,
    .trunk = &Tree1_TrunkModels,
    .drops = &Tree1_Drops,
    .vectors = &Tree1_Effects,
};

BombTrigger BombPos_Tree1 = {
    .pos = { -352.0f, 0.0f, 10.0f },
    .diameter = 0.0f
};

FoliageModelList Tree2_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o194);
FoliageModelList Tree2_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o193);

FoliageDropList Tree2_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_COIN,
            .pos = { -96, 132, -255 },
            .spawnMode = ITEM_SPAWN_MODE_TOSS_SPAWN_ONCE,
            .pickupFlag = GF_KMR04_Tree2_Coin,
        },
    }
};

FoliageVectorList Tree2_Effects = {
    .count = 2,
    .vectors = {
        { -156.0f, 150.0f, -255.0f },
        { -32.0f, 150.0f, -272.0f },
    }
};

ShakeTreeConfig ShakeTree_Tree2 = {
    .leaves = &Tree2_LeafModels,
    .trunk = &Tree2_TrunkModels,
    .drops = &Tree2_Drops,
    .vectors = &Tree2_Effects,
};

BombTrigger BombPos_Tree2 = {
    .pos = { -92.0f, 0.0f, -295.0f },
    .diameter = 0.0f
};

EvtScript EVS_OnShakeTree3 = {
    IfEq(GF_KMR04_Tree3_Dolly, true)
        Return
    EndIf
    IfEq(AF_KMR04_DollyDropped, true)
        Return
    EndIf
    Wait(15)
    Call(MakeItemEntity, ITEM_DOLLY, 250, 132, -100, ITEM_SPAWN_MODE_FALL_NEVER_VANISH, GF_KMR04_Tree3_Dolly)
    Set(AF_KMR04_DollyDropped, true)
    Thread
        Label(10)
        IfEq(GF_KMR04_Tree3_Dolly, false)
            Wait(1)
            Goto(10)
        EndIf
        Call(GetCurrentPartnerID, LVar0)
        IfEq(LVar0, PARTNER_GOOMPA)
            Call(DisablePlayerInput, true)
            Wait(5)
            Call(DisablePartnerAI, false)
            Call(SpeakToPlayer, NPC_PARTNER, ANIM_Goompa_Talk, ANIM_Goompa_Idle, 0, MSG_CH0_00AB)
            Call(SetNpcAnimation, NPC_PARTNER, ANIM_Goompa_Idle)
            Call(EnablePartnerAI)
            Call(DisablePlayerInput, false)
        EndIf
    EndThread
    Return
    End
};

FoliageModelList Tree3_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o192);
FoliageModelList Tree3_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o191);

FoliageVectorList Tree3_Effects = {
    .count = 2,
    .vectors = {
        { 190.0f, 150.0f, -124.0f },
        { 295.0f, 150.0f, -124.0f },
    }
};

ShakeTreeConfig ShakeTree_Tree3 = {
    .leaves = &Tree3_LeafModels,
    .trunk = &Tree3_TrunkModels,
    .vectors = &Tree3_Effects,
    .callback = &EVS_OnShakeTree3,
};

BombTrigger BombPos_Tree3 = {
    .pos = { 248.0f, 0.0f, -122.0f },
    .diameter = 0.0f
};

EvtScript EVS_SetupFoliage = {
    Set(LVar0, Ref(SearchBush_Bush1))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o402, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush2))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o415, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush3))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o409, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush4))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o412, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush5))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o399, 1, 0)
    IfGe(GB_StoryProgress, STORY_CH0_FOUND_HAMMER)
        Set(LVar0, Ref(SearchBush_Bush6))
        BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o410, 1, 0)
        Set(LVar0, Ref(SearchBush_Bush6))
        BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o410_1, 1, 0)
    Else
        Set(LVar0, Ref(SearchBush_Bush7))
        BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o410, 1, 0)
        Set(LVar0, Ref(SearchBush_Bush8))
        BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o410_1, 1, 0)
    EndIf
    Set(LVar0, Ref(SearchBush_Bush9))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o413, 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree1))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o407, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree1), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree2))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o271, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree2), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree3))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o341, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree3), 1, 0)
    Return
    End
};
