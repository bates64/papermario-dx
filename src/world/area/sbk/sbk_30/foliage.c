#include "sbk_30.h"

#include "foliage.h"

FoliageModelList Tree2_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_ki_ha);
FoliageModelList Tree2_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_ki_miki);

FoliageDropList Tree1_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_LETTER_TO_GOOMPA,
            .pos = { 204, 92, -220 },
            .spawnMode = ITEM_SPAWN_MODE_FALL_NEVER_VANISH,
            .pickupFlag = GF_SBK30_Tree2_Letter02,
            .spawnFlag = MF_TreeDrop_Letter,
        },
    }
};

ShakeTreeConfig ShakeTree_Tree2 = {
    .leaves = &Tree2_LeafModels,
    .trunk = &Tree2_TrunkModels,
};

ShakeTreeConfig ShakeTree_Tree1 = {
    .leaves = &Tree2_LeafModels,
    .trunk = &Tree2_TrunkModels,
    .drops = &Tree1_Drops,
};

BombTrigger BombPos_Tree = {
    .pos = { 266.0f, 0.0f, -209.0f },
    .diameter = 0.0f
};

EvtScript EVS_SetupFoliage = {
    IfLt(GB_StoryProgress, STORY_UNUSED_FFFFFFCC)
        Set(LVar0, Ref(ShakeTree_Tree2))
    Else
        Set(LVar0, Ref(ShakeTree_Tree1))
    EndIf
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o84, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree), 1, 0)
    Return
    End
};
