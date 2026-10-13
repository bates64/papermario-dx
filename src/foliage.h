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
    /* 0x00 */ s32 count;
    /* 0x04 */ s32 models[VLA];
} FoliageModelList;

typedef struct FoliageDrop {
    /* 0x00 */ s32 itemID;
    /* 0x04 */ Vec3i pos;
    /* 0x10 */ s32 spawnMode;
    /* 0x14 */ EvtVar pickupFlag;
    /* 0x18 */ EvtVar spawnFlag;
} FoliageDrop; // size = 0x1C

typedef struct FoliageDropList {
    /* 0x00 */ s32 count;
    /* 0x04 */ FoliageDrop drops[VLA];
} FoliageDropList;

typedef struct FoliageVectorList {
    /* 0x00 */ s32 count;
    /* 0x04 */ Vec3i vectors[VLA];
} FoliageVectorList;

typedef struct SearchBushConfig {
    /* 0x00 */ FoliageModelList* bush;
    /* 0x04 */ FoliageDropList* drops;
    /* 0x08 */ FoliageVectorList* vectors;
    /* 0x0C */ EvtScript* callback;
    /* 0x10 */ BushType type;
} SearchBushConfig; // size = 0x14

typedef struct ShakeTreeConfig {
    /* 0x00 */ FoliageModelList* leaves;
    /* 0x04 */ FoliageModelList* trunk;
    /* 0x08 */ FoliageDropList* drops;
    /* 0x0C */ FoliageVectorList* vectors;
    /* 0x10 */ EvtScript* callback;
    /* 0x14 */ TreeType type;
} ShakeTreeConfig; // size = 0x18
