#pragma once

#include "common.h"

/// Execute this script to animate a shaking bush and potentially spawn an item from it.
/// Expects a SearchBushConfig on LVar0.
/// Typically used with BindTrigger.
extern EvtScript EVS_SearchBush;

/// Execute this script to animate a shaking tree and potentially spawn items from it.
/// Expects a ShakeTreeConfig on LVar0.
/// Typically used with BindTrigger.
extern EvtScript EVS_ShakeTree;

typedef enum BushType {
    BUSH_TYPE_STANDARD  = 0,
} BushType;

typedef enum TreeType {
    TREE_TYPE_STANDARD  = 0,
    TREE_TYPE_SPARKLY   = 1,
} TreeType;

typedef struct FoliageModelList {
    s32 count;
    s32 models[VLA];
} FoliageModelList;

typedef struct FoliageDrop {
    s32 itemID;
    Vec3i pos;
    s32 spawnMode;
    Bytecode pickupFlag;
    Bytecode spawnFlag;
} FoliageDrop;

typedef struct FoliageDropList {
    s32 count;
    FoliageDrop drops[VLA];
} FoliageDropList;

typedef struct FoliageVectorList {
    s32 count;
    Vec3i vectors[VLA];
} FoliageVectorList;

typedef struct SearchBushConfig {
    FoliageModelList* bush;
    FoliageDropList* drops;
    FoliageVectorList* vectors;
    EvtScript* callback;
    BushType type;
} SearchBushConfig;

typedef struct ShakeTreeConfig {
    FoliageModelList* leaves;
    FoliageModelList* trunk;
    FoliageDropList* drops;
    FoliageVectorList* vectors;
    EvtScript* callback;
    TreeType type;
} ShakeTreeConfig;
