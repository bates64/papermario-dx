#include "common.h"
#include "model.h"

// This scratch region has addresses embedded in code and packed map assets.
BSS u8 D_80200000[0x4000];
BSS u8 D_80204000[0x3000];
BSS u8 D_80207000[0x3000];
BSS u8 D_8020A000[0x6000];
BSS ShapeFile gMapShapeData;

// Animation blobs are linked for Vine0Base and use the other buffers as
// alternate DMA destinations. Keep these addresses outside relocatable areas.
BSS u8 Vine3Base[0x2000];
BSS u8 Vine2Base[0x3000];
BSS u8 Vine1Base[0x3000];
BSS u8 Vine0Base[0x4000];
