#pragma once

#include "types.h"
#include "common_structs.h"

typedef struct HitAssetCollider {
    /* 0x00 */ s16 boundingBoxOffset;
    /* 0x02 */ s16 nextSibling;
    /* 0x04 */ s16 firstChild;
    /* 0x06 */ s16 numTriangles;
    /* 0x08 */ s32* triangles;
} HitAssetCollider; // size = 0x0C

typedef struct HitFileHeader {
    /* 0x00 */ s16 numColliders;
    /* 0x02 */ char pad_02[2];
    /* 0x04 */ HitAssetCollider* colliders;
    /* 0x08 */ s16 numVertices;
    /* 0x0A */ char pad_0A[2];
    /* 0x0C */ Vec3s* vertices;
    /* 0x10 */ s16 boundingBoxesDataSize;
    /* 0x12 */ char pad_12[2];
    /* 0x14 */ u32* boundingBoxes;
} HitFileHeader; // size = 0x18

typedef struct HitFile {
    /* 0x00 */ HitFileHeader* collision;
    /* 0x04 */ HitFileHeader* zone;
} HitFile; // size = 0x08
