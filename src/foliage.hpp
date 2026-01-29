#include "common.h"
#include "npc.h"
#include "model.h"
#include "effects.h"

struct FoliageModelList {
    s32 count;
    s32* models;
};

struct FoliageDrop {
    s32 itemID;
    Vec3i pos;
    s32 spawnMode;
    Bytecode pickupFlag;
    Bytecode spawnFlag;
};

struct FoliageDropList {
    s32 count;
    FoliageDrop* drops;
};

struct FoliageVectorList {
    s32 count;
    Vec3i* vectors;
};

struct SearchBushConfig {
    FoliageModelList* bush;
    FoliageDropList* drops;
    FoliageVectorList* vectors;
    EvtScript* callback;
};

struct ShakeTreeConfig {
    FoliageModelList* leaves;
    FoliageModelList* trunk;
    FoliageDropList* drops;
    FoliageVectorList* vectors;
    EvtScript* callback;
};

namespace foliage {
    extern EvtScript EVS_SearchBush;
    extern EvtScript EVS_ShakeTree;
}

//used for shaking a bush that doesn't drop anything
#define DEFINE_BUSH(name, model, pos_macro) \
    namespace name { \
        s32 BushModelsData[] = { model }; \
        FoliageModelList BushModels = { .count = 1, .models = BushModelsData }; \
        Vec3i EffectsData[] = { \
            { pos_macro }, \
        }; \
        FoliageVectorList Effects = { \
            .count = 1, \
            .vectors = EffectsData, \
        }; \
        SearchBushConfig SearchBush = { \
            .bush = &BushModels, \
            .drops = nullptr, \
            .vectors = &Effects, \
        }; \
    }; \

#define DEFINE_BUSH_WITH_DROP(name, model, pos_macro, item, spawn_mode, pickup_flag, spawn_flag) \
    namespace name { \
        s32 BushModelsData[] = { model }; \
        FoliageModelList BushModels = { .count = 1, .models = BushModelsData }; \
        FoliageDrop DropsData[] = { \
            { \
                .itemID = item, \
                .pos = { pos_macro }, \
                .spawnMode = spawn_mode, \
                .pickupFlag = pickup_flag, \
                .spawnFlag = spawn_flag, \
            }, \
        }; \
        FoliageDropList Drops = { \
            .count = 1, \
            .drops = DropsData, \
        }; \
        Vec3i EffectsData[] = { \
            { pos_macro }, \
        }; \
        FoliageVectorList Effects = { \
            .count = 1, \
            .vectors = EffectsData, \
        }; \
        SearchBushConfig SearchBush = { \
            .bush = &BushModels, \
            .drops = &Drops, \
            .vectors = &Effects, \
        }; \
    }; \

#define DEFINE_TREE(name, leaf_model, trunk_model, bomb_pos, bomb_diameter) \
    namespace name { \
        s32 LeafModelsData[] = { leaf_model }; \
        FoliageModelList LeafModels = { .count = ARRAY_COUNT(LeafModelsData), .models = LeafModelsData }; \
        s32 TrunkModelsData[] = { trunk_model }; \
        FoliageModelList TrunkModels = { .count = ARRAY_COUNT(TrunkModelsData), .models = TrunkModelsData }; \
        ShakeTreeConfig ShakeTree = { \
            .leaves = &LeafModels, \
            .trunk = &TrunkModels, \
            .drops = nullptr, \
        }; \
        BombTrigger BombPos = { \
            .pos = { bomb_pos }, \
            .diameter = bomb_diameter, \
        }; \
    }; \

#define DEFINE_TREE_NO_LEAVES(name, trunk_model, bomb_pos, bomb_diameter) \
    namespace name { \
        s32 TrunkModelsData[] = { trunk_model }; \
        FoliageModelList TrunkModels = { .count = 1, .models = TrunkModelsData }; \
        ShakeTreeConfig ShakeTree = { \
            .leaves = nullptr, \
            .trunk = &TrunkModels, \
            .drops = nullptr, \
        }; \
        BombTrigger BombPos = { \
            .pos = { bomb_pos }, \
            .diameter = bomb_diameter, \
        }; \
    }; \

#define DEFINE_TREE_WITH_FALLING_LEAVES(name, leaf_model, trunk_model, bomb_pos, bomb_diameter, falling_leaves) \
    namespace name { \
        FoliageVectorList Vectors = { \
            .count = ARRAY_COUNT(falling_leaves), \
            .vectors = falling_leaves, \
        }; \
        s32 LeafModelsData[] = { leaf_model }; \
        FoliageModelList LeafModels = { .count = 1, .models = LeafModelsData }; \
        s32 TrunkModelsData[] = { trunk_model }; \
        FoliageModelList TrunkModels = { .count = 1, .models = TrunkModelsData }; \
        ShakeTreeConfig ShakeTree = { \
            .leaves = &LeafModels, \
            .trunk = &TrunkModels, \
            .drops = nullptr, \
            .vectors = &Vectors, \
        }; \
        BombTrigger BombPos = { \
            .pos = { bomb_pos }, \
            .diameter = bomb_diameter, \
        }; \
    }; \

#define DEFINE_TREE_WITH_DROP(name, leaf_model, trunk_model, bomb_pos, bomb_diameter, pos_macro, item, spawn_mode, spawn_flag) \
    namespace name { \
        s32 LeafModelsData[] = { leaf_model }; \
        FoliageModelList LeafModels = { .count = 1, .models = LeafModelsData }; \
        s32 TrunkModelsData[] = { trunk_model }; \
        FoliageModelList TrunkModels = { .count = 1, .models = TrunkModelsData }; \
        FoliageDrop DropsData[] = { \
            { \
                .itemID = item, \
                .pos = { pos_macro }, \
                .spawnMode = spawn_mode, \
                .spawnFlag = spawn_flag, \
            }, \
        }; \
        FoliageDropList Drops = { \
            .count = 1, \
            .drops = DropsData, \
        }; \
        ShakeTreeConfig ShakeTree = { \
            .leaves = &LeafModels, \
            .trunk = &TrunkModels, \
            .drops = &Drops, \
        }; \
        BombTrigger BombPos = { \
            .pos = { bomb_pos }, \
            .diameter = bomb_diameter, \
        }; \
    }; \

/// @param falling_leaves array of positions where leaves will fall from e.g. `{ { x, y, z }, { x, y, z } }`
#define DEFINE_TREE_WITH_FALLING_LEAVES_WITH_DROP(name, leaf_model, trunk_model, bomb_pos, bomb_diameter, falling_leaves, pos_macro, item, spawn_mode, spawn_flag) \
    namespace name { \
        FoliageVectorList Vectors = { \
            .count = ARRAY_COUNT(falling_leaves), \
            .vectors = falling_leaves, \
        }; \
        s32 LeafModelsData[] = { leaf_model }; \
        FoliageModelList LeafModels = { .count = 1, .models = LeafModelsData }; \
        s32 TrunkModelsData[] = { trunk_model }; \
        FoliageModelList TrunkModels = { .count = 1, .models = TrunkModelsData }; \
        FoliageDrop DropsData[] = { \
            { \
                .itemID = item, \
                .pos = { pos_macro }, \
                .spawnMode = spawn_mode, \
                .spawnFlag = spawn_flag, \
            }, \
        }; \
        FoliageDropList Drops = { \
            .count = 1, \
            .drops = DropsData, \
        }; \
        ShakeTreeConfig ShakeTree = { \
            .leaves = &LeafModels, \
            .trunk = &TrunkModels, \
            .drops = &Drops, \
            .vectors = &Vectors, \
        }; \
        BombTrigger BombPos = { \
            .pos = { bomb_pos }, \
            .diameter = bomb_diameter, \
        }; \
    }; \

#define BIND_BUSH(name, collider) \
    Set(LVar0, Ref(name::SearchBush)) \
    BindTrigger(Ref(foliage::EVS_SearchBush), TRIGGER_WALL_PRESS_A, collider, 1, 0)

#define BIND_TREE(name, collider) \
    Set(LVar0, Ref(name::ShakeTree)) \
    BindTrigger(Ref(foliage::EVS_ShakeTree), TRIGGER_WALL_HAMMER, collider, 1, 0) \
    BindTrigger(Ref(foliage::EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(name::BombPos), 1, 0)
