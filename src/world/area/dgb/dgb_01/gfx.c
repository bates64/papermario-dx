#include "dgb_01.h"
#include "../dgb_vtx.h"

#ifdef DEBUG_DGB_01_MESH_COLORS
#define DEBUG_MESH_COLOR(r, g, b) gsDPSetPrimColor(0, 0, r, g, b, 255),
#else
#define DEBUG_MESH_COLOR(r, g, b)
#endif

Lights1 N(SmashBridgesLights) = gdSPDefLights1(0, 0, 0, 0, 0, 0, 0, 0, 0);

Mtx N(UpperBridgeLeftMtx) = RDP_MATRIX(
    1.0, 0.0, 0.0, -218.9449005126953125,
    0.0, 1.0, 0.0, 434.4014892578125,
    0.0, 0.0, 1.0, -0.1583404541015625,
    0.0, 0.0, 0.0, 1.0
);

Mtx N(UpperBridgeRightCollapseMtx) = RDP_MATRIX(
    1.0, 0.0, 0.0, 42.723876953125,
    0.0, 1.0, 0.0, 446.4925537109375,
    0.0, 0.0, 1.0, -0.1865692138671875,
    0.0, 0.0, 0.0, 1.0
);

Mtx N(UpperRailingDebris11Mtx) = RDP_MATRIX(
    1.0, 0.0, 0.0, -375.0,
    0.0, 1.0, 0.0, 420.0,
    0.0, 0.0, 1.0, -48.72808837890625,
    0.0, 0.0, 0.0, 1.0
);

Mtx N(UpperRailingDebris10Mtx) = RDP_MATRIX(
    1.0, 0.0, 0.0, -425.0,
    0.0, 1.0, 0.0, 420.0,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0
);

Mtx N(UpperRailingDebris9Mtx) = RDP_MATRIX(
    1.0, 0.0, 0.0, -425.0,
    0.0, 1.0, 0.0, 420.0,
    0.0, 0.0, 1.0, 49.72808837890625,
    0.0, 0.0, 0.0, 1.0
);

Mtx N(UpperRailingDebris8Mtx) = RDP_MATRIX(
    1.0, 0.0, 0.0, -375.0,
    0.0, 1.0, 0.0, 420.0,
    0.0, 0.0, 1.0, 49.72808837890625,
    0.0, 0.0, 0.0, 1.0
);

Mtx N(UpperRailingDebris7Mtx) = RDP_MATRIX(
    1.0, 0.0, 0.0, -75.0,
    0.0, 1.0, 0.0, 420.0,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0
);

Mtx N(UpperRailingDebris6Mtx) = RDP_MATRIX(
    1.0, 0.0, 0.0, -75.0,
    0.0, 1.0, 0.0, 420.0,
    0.0, 0.0, 1.0, 49.72808837890625,
    0.0, 0.0, 0.0, 1.0
);

Mtx N(UpperRailingDebris5Mtx) = RDP_MATRIX(
    1.0, 0.0, 0.0, -25.0,
    0.0, 1.0, 0.0, 420.0,
    0.0, 0.0, 1.0, 49.72808837890625,
    0.0, 0.0, 0.0, 1.0
);

Mtx N(UpperRailingDebris4Mtx) = RDP_MATRIX(
    1.0, 0.0, 0.0, 175.0,
    0.0, 1.0, 0.0, 420.0,
    0.0, 0.0, 1.0, -48.72808837890625,
    0.0, 0.0, 0.0, 1.0
);

Mtx N(UpperRailingDebris3Mtx) = RDP_MATRIX(
    1.0, 0.0, 0.0, 125.0,
    0.0, 1.0, 0.0, 420.0,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0
);

Mtx N(UpperRailingDebris2Mtx) = RDP_MATRIX(
    1.0, 0.0, 0.0, 125.0,
    0.0, 1.0, 0.0, 420.0,
    0.0, 0.0, 1.0, 49.72808837890625,
    0.0, 0.0, 0.0, 1.0
);

Mtx N(UpperRailingDebris1Mtx) = RDP_MATRIX(
    1.0, 0.0, 0.0, 175.0,
    0.0, 1.0, 0.0, 420.0,
    0.0, 0.0, 1.0, 49.72808837890625,
    0.0, 0.0, 0.0, 1.0
);

Mtx N(SmashBridgesNode077Mtx) = RDP_MATRIX(
    1.0, 0.0, 0.0, -375.0,
    0.0, 1.0, 0.0, 400.0,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0
);

Mtx N(SmashBridgesNode082Mtx) = RDP_MATRIX(
    1.0, 0.0, 0.0, -75.0,
    0.0, 1.0, 0.0, 400.0,
    0.0, 0.0, 1.0, -48.72808837890625,
    0.0, 0.0, 0.0, 1.0
);

Mtx N(SmashBridgesNode079Mtx) = RDP_MATRIX(
    1.0, 0.0, 0.0, -75.0,
    0.0, 1.0, 0.0, 400.0,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0
);

Mtx N(SmashBridgesNode080Mtx) = RDP_MATRIX(
    1.0, 0.0, 0.0, -75.0,
    0.0, 1.0, 0.0, 400.0,
    0.0, 0.0, 1.0, 49.72808837890625,
    0.0, 0.0, 0.0, 1.0
);

Mtx N(SmashBridgesNode081Mtx) = RDP_MATRIX(
    1.0, 0.0, 0.0, -25.0,
    0.0, 1.0, 0.0, 400.0,
    0.0, 0.0, 1.0, 49.72808837890625,
    0.0, 0.0, 0.0, 1.0
);

Mtx N(SmashBridgesNode076Mtx) = RDP_MATRIX(
    1.0, 0.0, 0.0, 175.0,
    0.0, 1.0, 0.0, 400.0,
    0.0, 0.0, 1.0, -48.72808837890625,
    0.0, 0.0, 0.0, 1.0
);

Mtx N(SmashBridgesNode075Mtx) = RDP_MATRIX(
    1.0, 0.0, 0.0, 125.0,
    0.0, 1.0, 0.0, 400.0,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0
);

Mtx N(SmashBridgesNode074Mtx) = RDP_MATRIX(
    1.0, 0.0, 0.0, 125.0,
    0.0, 1.0, 0.0, 400.0,
    0.0, 0.0, 1.0, 49.72808837890625,
    0.0, 0.0, 0.0, 1.0
);

Mtx N(SmashBridgesNode073Mtx) = RDP_MATRIX(
    1.0, 0.0, 0.0, 175.0,
    0.0, 1.0, 0.0, 400.0,
    0.0, 0.0, 1.0, 49.72808837890625,
    0.0, 0.0, 0.0, 1.0
);

Mtx N(UpperBridgeRearRailingMtx) = RDP_MATRIX(
    1.0, 0.0, 0.0, 26.4285736083984375,
    0.0, 1.0, 0.0, 482.03570556640625,
    0.0, 0.0, 1.0, -85.9561920166015625,
    0.0, 0.0, 0.0, 1.0
);

Mtx N(SmashBridgesIdentityMtx) = RDP_MATRIX(
    1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0
);

Mtx N(SmashBridgesNode020Mtx) = RDP_MATRIX(
    1.0, 0.0, 0.0, -500.0,
    0.0, 1.0, 0.0, 210.0,
    0.0, 0.0, 1.0, -90.0,
    0.0, 0.0, 0.0, 1.0
);

Mtx N(SmashBridgesNode019Mtx) = RDP_MATRIX(
    1.0, 0.0, 0.0, -500.0,
    0.0, 1.0, 0.0, 210.0,
    0.0, 0.0, 1.0, 90.0,
    0.0, 0.0, 0.0, 1.0
);

Mtx N(LowerBridgeLeftCollapseMtx) = RDP_MATRIX(
    1.0, 0.0, 0.0, -293.639923095703125,
    0.0, 1.0, 0.0, 228.275665283203125,
    0.0, 0.0, 1.0, -0.664398193359375,
    0.0, 0.0, 0.0, 1.0
);

Mtx N(LowerBridgeCenterCollapseMtx) = RDP_MATRIX(
    1.0, 0.0, 0.0, -92.72760009765625,
    0.0, 1.0, 0.0, 235.680999755859375,
    0.0, 0.0, 1.0, -0.0857086181640625,
    0.0, 0.0, 0.0, 1.0
);

Mtx N(SmashBridgesNode029Mtx) = RDP_MATRIX(
    1.0, 0.0, 0.0, 95.1289825439453125,
    0.0, 1.0, 0.0, 49.319000244140625,
    0.0, 0.0, 1.0, 87.041900634765625,
    0.0, 0.0, 0.0, 1.0
);

Mtx N(SmashBridgesNode043Mtx) = RDP_MATRIX(
    1.0, 0.0, 0.0, 253.643310546875,
    0.0, 1.0, 0.0, 285.0,
    0.0, 0.0, 1.0, 86.9561920166015625,
    0.0, 0.0, 0.0, 1.0
);

Mtx N(SmashBridgesNode071Mtx) = RDP_MATRIX(
    1.0, 0.0, 0.0, -425.0,
    0.0, 1.0, 0.0, 190.0,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0
);

Mtx N(SmashBridgesNode070Mtx) = RDP_MATRIX(
    1.0, 0.0, 0.0, -175.0,
    0.0, 1.0, 0.0, 190.0,
    0.0, 0.0, 1.0, -48.72808837890625,
    0.0, 0.0, 0.0, 1.0
);

Mtx N(SmashBridgesNode069Mtx) = RDP_MATRIX(
    1.0, 0.0, 0.0, 75.0,
    0.0, 1.0, 0.0, 190.0,
    0.0, 0.0, 1.0, -48.72808837890625,
    0.0, 0.0, 0.0, 1.0
);

Gfx N(Gfx_DrawMesh_WoodBridgeStructure3)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_Wood)),
    DEBUG_MESH_COLOR(0, 128, 48)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C2E620, 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(3, 2, 4, 0, 3, 4, 5, 0),
    gsSP2Triangles(6, 7, 1, 0, 6, 1, 0, 0),
    gsSP2Triangles(8, 9, 7, 0, 8, 7, 6, 0),
    gsSP2Triangles(10, 11, 12, 0, 13, 14, 15, 0),
    gsSP2Triangles(13, 15, 11, 0, 13, 11, 16, 0),
    gsSP2Triangles(17, 13, 16, 0, 17, 16, 18, 0),
    gsSP2Triangles(19, 17, 18, 0, 19, 18, 20, 0),
    gsSP2Triangles(21, 22, 23, 0, 21, 23, 24, 0),
    gsSP2Triangles(23, 22, 25, 0, 23, 25, 26, 0),
    gsSP1Triangle(27, 28, 29, 0),
    gsSPVertex(vtx_C2E7B0, 3, 0),
    gsSPVertex(vtx_C2E800, 14, 3),
    gsSPVertex(vtx_C2E980, 15, 17),
    gsSP2Triangles(3, 2, 4, 0, 3, 4, 5, 0),
    gsSP2Triangles(3, 5, 6, 0, 7, 3, 6, 0),
    gsSP2Triangles(7, 6, 17, 0, 8, 7, 17, 0),
    gsSP2Triangles(8, 17, 18, 0, 9, 19, 20, 0),
    gsSP2Triangles(9, 20, 21, 0, 1, 0, 10, 0),
    gsSP2Triangles(1, 10, 22, 0, 11, 23, 24, 0),
    gsSP2Triangles(11, 24, 12, 0, 12, 24, 25, 0),
    gsSP2Triangles(12, 25, 13, 0, 13, 25, 26, 0),
    gsSP2Triangles(13, 26, 14, 0, 14, 26, 27, 0),
    gsSP2Triangles(14, 27, 28, 0, 15, 16, 29, 0),
    gsSP2Triangles(15, 29, 30, 0, 15, 30, 31, 0),
    gsSPVertex(vtx_C2E8C0, 12, 0),
    gsSPVertex(vtx_C2EA60, 20, 12),
    gsSP2Triangles(1, 13, 14, 0, 2, 0, 12, 0),
    gsSP2Triangles(2, 12, 15, 0, 3, 2, 15, 0),
    gsSP2Triangles(3, 15, 16, 0, 4, 17, 18, 0),
    gsSP2Triangles(5, 19, 20, 0, 5, 20, 17, 0),
    gsSP2Triangles(5, 17, 21, 0, 6, 5, 21, 0),
    gsSP2Triangles(6, 21, 22, 0, 7, 6, 22, 0),
    gsSP2Triangles(7, 22, 23, 0, 8, 24, 25, 0),
    gsSP2Triangles(8, 25, 9, 0, 9, 25, 26, 0),
    gsSP2Triangles(9, 26, 27, 0, 10, 28, 24, 0),
    gsSP2Triangles(10, 24, 8, 0, 11, 29, 30, 0),
    gsSP1Triangle(11, 30, 31, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_WoodBridgeStructure2)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_Wood)),
    DEBUG_MESH_COLOR(0, 128, 48)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C2E020, 30, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(7, 6, 8, 0, 7, 8, 9, 0),
    gsSP2Triangles(9, 8, 10, 0, 9, 10, 11, 0),
    gsSP2Triangles(11, 10, 12, 0, 11, 12, 13, 0),
    gsSP2Triangles(14, 15, 16, 0, 14, 16, 17, 0),
    gsSP2Triangles(18, 14, 17, 0, 18, 17, 19, 0),
    gsSP2Triangles(15, 20, 21, 0, 15, 21, 16, 0),
    gsSP2Triangles(20, 22, 23, 0, 20, 23, 21, 0),
    gsSP2Triangles(24, 25, 26, 0, 24, 26, 27, 0),
    gsSP2Triangles(28, 29, 25, 0, 28, 25, 24, 0),
    gsSPVertex(vtx_C2E1E0, 13, 0),
    gsSPVertex(vtx_C2E390, 17, 13),
    gsSP2Triangles(2, 13, 14, 0, 2, 14, 15, 0),
    gsSP2Triangles(3, 2, 15, 0, 3, 15, 16, 0),
    gsSP2Triangles(4, 3, 16, 0, 4, 16, 17, 0),
    gsSP2Triangles(5, 4, 17, 0, 5, 17, 18, 0),
    gsSP2Triangles(6, 19, 1, 0, 6, 1, 0, 0),
    gsSP2Triangles(7, 20, 19, 0, 7, 19, 6, 0),
    gsSP2Triangles(8, 21, 22, 0, 8, 22, 23, 0),
    gsSP2Triangles(9, 24, 25, 0, 9, 25, 10, 0),
    gsSP2Triangles(10, 25, 26, 0, 10, 26, 27, 0),
    gsSP2Triangles(11, 28, 24, 0, 11, 24, 9, 0),
    gsSP2Triangles(12, 29, 28, 0, 12, 28, 11, 0),
    gsSPVertex(vtx_C2E2B0, 12, 0),
    gsSPVertex(vtx_C2E4A0, 20, 12),
    gsSP2Triangles(0, 1, 12, 0, 0, 12, 13, 0),
    gsSP2Triangles(1, 2, 14, 0, 1, 14, 12, 0),
    gsSP2Triangles(2, 3, 15, 0, 2, 15, 14, 0),
    gsSP2Triangles(3, 16, 17, 0, 3, 17, 15, 0),
    gsSP2Triangles(4, 18, 19, 0, 4, 19, 20, 0),
    gsSP2Triangles(5, 6, 21, 0, 5, 21, 22, 0),
    gsSP2Triangles(6, 7, 23, 0, 6, 23, 21, 0),
    gsSP2Triangles(7, 8, 24, 0, 7, 24, 23, 0),
    gsSP2Triangles(8, 25, 26, 0, 8, 26, 24, 0),
    gsSP2Triangles(9, 27, 28, 0, 9, 28, 29, 0),
    gsSP2Triangles(10, 30, 31, 0, 10, 31, 11, 0),
    gsSPVertex(vtx_C2E360, 3, 0),
    gsSPVertex(vtx_C2E5D0, 5, 3),
    gsSP2Triangles(0, 3, 4, 0, 0, 4, 1, 0),
    gsSP2Triangles(1, 4, 5, 0, 1, 5, 2, 0),
    gsSP2Triangles(2, 5, 6, 0, 2, 6, 7, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_WoodBridgeStructure1)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_Wood)),
    DEBUG_MESH_COLOR(0, 128, 48)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C2DA20, 30, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(8, 9, 5, 0, 8, 5, 4, 0),
    gsSP2Triangles(10, 11, 9, 0, 10, 9, 8, 0),
    gsSP2Triangles(12, 13, 11, 0, 12, 11, 10, 0),
    gsSP2Triangles(14, 15, 16, 0, 14, 16, 17, 0),
    gsSP2Triangles(18, 14, 17, 0, 18, 17, 19, 0),
    gsSP2Triangles(15, 20, 21, 0, 15, 21, 16, 0),
    gsSP2Triangles(20, 22, 23, 0, 20, 23, 21, 0),
    gsSP2Triangles(24, 25, 26, 0, 24, 26, 27, 0),
    gsSP2Triangles(27, 26, 28, 0, 27, 28, 29, 0),
    gsSPVertex(vtx_C2DBE0, 13, 0),
    gsSPVertex(vtx_C2DD90, 17, 13),
    gsSP2Triangles(2, 13, 14, 0, 2, 14, 15, 0),
    gsSP2Triangles(3, 2, 15, 0, 3, 15, 16, 0),
    gsSP2Triangles(4, 3, 16, 0, 4, 16, 17, 0),
    gsSP2Triangles(5, 4, 17, 0, 5, 17, 18, 0),
    gsSP2Triangles(1, 0, 6, 0, 1, 6, 7, 0),
    gsSP2Triangles(7, 6, 19, 0, 7, 19, 20, 0),
    gsSP2Triangles(8, 21, 22, 0, 8, 22, 23, 0),
    gsSP2Triangles(9, 24, 25, 0, 9, 25, 10, 0),
    gsSP2Triangles(10, 25, 26, 0, 10, 26, 11, 0),
    gsSP2Triangles(11, 26, 27, 0, 11, 27, 12, 0),
    gsSP2Triangles(12, 27, 28, 0, 12, 28, 29, 0),
    gsSPVertex(vtx_C2DCB0, 12, 0),
    gsSPVertex(vtx_C2DEA0, 20, 12),
    gsSP2Triangles(0, 1, 12, 0, 0, 12, 13, 0),
    gsSP2Triangles(1, 2, 14, 0, 1, 14, 12, 0),
    gsSP2Triangles(2, 3, 15, 0, 2, 15, 14, 0),
    gsSP2Triangles(3, 16, 17, 0, 3, 17, 15, 0),
    gsSP2Triangles(4, 18, 19, 0, 4, 19, 20, 0),
    gsSP2Triangles(5, 6, 21, 0, 5, 21, 22, 0),
    gsSP2Triangles(6, 7, 23, 0, 6, 23, 21, 0),
    gsSP2Triangles(7, 8, 24, 0, 7, 24, 23, 0),
    gsSP2Triangles(8, 25, 26, 0, 8, 26, 24, 0),
    gsSP2Triangles(9, 27, 28, 0, 9, 28, 29, 0),
    gsSP2Triangles(10, 30, 31, 0, 10, 31, 11, 0),
    gsSPVertex(vtx_C2DD50, 4, 0),
    gsSPVertex(vtx_C2DFC0, 6, 4),
    gsSP2Triangles(1, 5, 6, 0, 1, 6, 7, 0),
    gsSP2Triangles(2, 8, 4, 0, 2, 4, 0, 0),
    gsSP2Triangles(3, 9, 8, 0, 3, 8, 2, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_SmashBridgesStaticPart01)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_RailingPostDamaged)),
    DEBUG_MESH_COLOR(0, 128, 48)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C2D830, 12, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSPVertex(vtx_C2D8F0, 19, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSP2Triangles(4, 0, 2, 0, 5, 6, 7, 0),
    gsSP2Triangles(6, 8, 7, 0, 8, 9, 7, 0),
    gsSP2Triangles(10, 11, 12, 0, 10, 13, 11, 0),
    gsSP2Triangles(10, 14, 15, 0, 10, 16, 14, 0),
    gsSP2Triangles(10, 15, 13, 0, 10, 17, 18, 0),
    gsSP1Triangle(10, 12, 17, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_StaticWoodPanelCeiling)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_WoodPanelCeiling)),
    DEBUG_MESH_COLOR(0, 128, 48)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C2D6E0, 21, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(12, 13, 11, 0, 12, 11, 10, 0),
    gsSP2Triangles(14, 15, 16, 0, 14, 16, 17, 0),
    gsSP2Triangles(18, 19, 20, 0, 18, 20, 17, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawGroup_BridgeSupportArches)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPDisplayList(N(Gfx_DrawMesh_StaticWoodPanelCeiling)),
    gsSPDisplayList(N(Gfx_DrawMesh_SmashBridgesStaticPart01)),
    gsSPDisplayList(N(Gfx_DrawMesh_WoodBridgeStructure1)),
    gsSPDisplayList(N(Gfx_DrawMesh_WoodBridgeStructure2)),
    gsSPDisplayList(N(Gfx_DrawMesh_WoodBridgeStructure3)),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawQuad_LowerBridgeWoodPanelTrimNode069)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_WoodPanelTrim)),
    DEBUG_MESH_COLOR(24, 48, 160)
    gsSPClearGeometryMode(G_CULL_BACK | G_LIGHTING),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPVertex(vtx_C2D6A0, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_Transform_SmashBridgesNode069)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPMatrix(&N(SmashBridgesNode069Mtx), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW),
    gsSPDisplayList(N(Gfx_DrawQuad_LowerBridgeWoodPanelTrimNode069)),
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawQuad_LowerBridgeWoodPanelTrimNode070)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_WoodPanelTrim)),
    DEBUG_MESH_COLOR(24, 48, 160)
    gsSPClearGeometryMode(G_CULL_BACK | G_LIGHTING),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPVertex(vtx_C2D660, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_Transform_SmashBridgesNode070)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPMatrix(&N(SmashBridgesNode070Mtx), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW),
    gsSPDisplayList(N(Gfx_DrawQuad_LowerBridgeWoodPanelTrimNode070)),
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawQuad_LowerBridgeWoodPanelTrimNode071)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_WoodPanelTrim)),
    DEBUG_MESH_COLOR(24, 48, 160)
    gsSPClearGeometryMode(G_CULL_BACK | G_LIGHTING),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPVertex(vtx_C2D620, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_Transform_SmashBridgesNode071)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPMatrix(&N(SmashBridgesNode071Mtx), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW),
    gsSPDisplayList(N(Gfx_DrawQuad_LowerBridgeWoodPanelTrimNode071)),
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawGroup_LowerBridgeWoodPanelTrimDebris)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPDisplayList(N(Gfx_Transform_SmashBridgesNode071)),
    gsSPDisplayList(N(Gfx_Transform_SmashBridgesNode070)),
    gsSPDisplayList(N(Gfx_Transform_SmashBridgesNode069)),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_BridgeFragmentFloorTileNode118)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_FloorTile)),
    DEBUG_MESH_COLOR(160, 255, 32)
    gsSPClearGeometryMode(G_LIGHTING | G_SHADING_SMOOTH),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPVertex(vtx_C2D5C0, 6, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(1, 4, 5, 0, 1, 5, 2, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_BridgeFragmentFloorTileNode119)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_FloorTile)),
    DEBUG_MESH_COLOR(160, 255, 32)
    gsSPClearGeometryMode(G_LIGHTING | G_SHADING_SMOOTH),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPVertex(vtx_C2D560, 6, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(1, 4, 5, 0, 1, 5, 2, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_BridgeFragmentFloorTileNode120)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_FloorTile)),
    DEBUG_MESH_COLOR(160, 255, 32)
    gsSPClearGeometryMode(G_LIGHTING | G_SHADING_SMOOTH),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPVertex(vtx_C2D500, 6, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(1, 4, 5, 0, 1, 5, 2, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_BridgeFragmentWoodNode115)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_Wood)),
    DEBUG_MESH_COLOR(160, 255, 32)
    gsSPClearGeometryMode(G_LIGHTING | G_SHADING_SMOOTH),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPVertex(vtx_C2D260, 30, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(1, 4, 5, 0, 1, 5, 2, 0),
    gsSP2Triangles(4, 6, 7, 0, 4, 7, 5, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(9, 12, 13, 0, 9, 13, 10, 0),
    gsSP2Triangles(14, 15, 16, 0, 14, 17, 18, 0),
    gsSP2Triangles(14, 18, 15, 0, 17, 19, 20, 0),
    gsSP2Triangles(17, 20, 18, 0, 19, 21, 22, 0),
    gsSP2Triangles(19, 22, 20, 0, 6, 23, 7, 0),
    gsSP2Triangles(24, 25, 26, 0, 24, 26, 27, 0),
    gsSP2Triangles(25, 28, 29, 0, 25, 29, 26, 0),
    gsSPVertex(vtx_C2D3E0, 1, 0),
    gsSPVertex(vtx_C2D410, 1, 1),
    gsSPVertex(vtx_C2D440, 12, 2),
    gsSP2Triangles(2, 0, 1, 0, 2, 1, 7, 0),
    gsSP2Triangles(2, 7, 8, 0, 3, 4, 9, 0),
    gsSP2Triangles(3, 9, 10, 0, 4, 5, 11, 0),
    gsSP2Triangles(4, 11, 9, 0, 5, 6, 12, 0),
    gsSP2Triangles(5, 12, 11, 0, 6, 13, 12, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_BridgeFragmentWoodNode116)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_Wood)),
    DEBUG_MESH_COLOR(160, 255, 32)
    gsSPClearGeometryMode(G_LIGHTING | G_SHADING_SMOOTH),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPVertex(vtx_C2CFC0, 30, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(1, 4, 5, 0, 1, 5, 2, 0),
    gsSP2Triangles(4, 6, 7, 0, 4, 7, 5, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(9, 12, 13, 0, 9, 13, 10, 0),
    gsSP2Triangles(14, 15, 16, 0, 14, 17, 18, 0),
    gsSP2Triangles(14, 18, 15, 0, 17, 19, 20, 0),
    gsSP2Triangles(17, 20, 18, 0, 19, 21, 22, 0),
    gsSP2Triangles(19, 22, 20, 0, 6, 23, 7, 0),
    gsSP2Triangles(24, 25, 26, 0, 24, 26, 27, 0),
    gsSP2Triangles(25, 28, 29, 0, 25, 29, 26, 0),
    gsSPVertex(vtx_C2D140, 1, 0),
    gsSPVertex(vtx_C2D170, 1, 1),
    gsSPVertex(vtx_C2D1A0, 12, 2),
    gsSP2Triangles(2, 0, 1, 0, 2, 1, 7, 0),
    gsSP2Triangles(2, 7, 8, 0, 3, 4, 9, 0),
    gsSP2Triangles(3, 9, 10, 0, 4, 5, 11, 0),
    gsSP2Triangles(4, 11, 9, 0, 5, 6, 12, 0),
    gsSP2Triangles(5, 12, 11, 0, 6, 13, 12, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_BridgeFragmentWoodNode117)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_Wood)),
    DEBUG_MESH_COLOR(160, 255, 32)
    gsSPClearGeometryMode(G_LIGHTING | G_SHADING_SMOOTH),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPVertex(vtx_C2CD20, 30, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(1, 4, 5, 0, 1, 5, 2, 0),
    gsSP2Triangles(4, 6, 7, 0, 4, 7, 5, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(9, 12, 13, 0, 9, 13, 10, 0),
    gsSP2Triangles(14, 15, 16, 0, 15, 17, 18, 0),
    gsSP2Triangles(15, 18, 16, 0, 17, 19, 20, 0),
    gsSP2Triangles(17, 20, 18, 0, 19, 21, 22, 0),
    gsSP2Triangles(19, 22, 20, 0, 6, 23, 7, 0),
    gsSP2Triangles(24, 25, 26, 0, 24, 26, 27, 0),
    gsSP2Triangles(25, 28, 29, 0, 25, 29, 26, 0),
    gsSPVertex(vtx_C2CEA0, 1, 0),
    gsSPVertex(vtx_C2CED0, 1, 1),
    gsSPVertex(vtx_C2CF00, 12, 2),
    gsSP2Triangles(2, 0, 1, 0, 2, 1, 8, 0),
    gsSP2Triangles(3, 2, 8, 0, 4, 5, 9, 0),
    gsSP2Triangles(4, 9, 10, 0, 5, 6, 11, 0),
    gsSP2Triangles(5, 11, 9, 0, 6, 7, 12, 0),
    gsSP2Triangles(6, 12, 11, 0, 7, 13, 12, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawGroup_WoodAndFloorTileDebris)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPDisplayList(N(Gfx_DrawMesh_BridgeFragmentWoodNode117)),
    gsSPDisplayList(N(Gfx_DrawMesh_BridgeFragmentWoodNode116)),
    gsSPDisplayList(N(Gfx_DrawMesh_BridgeFragmentWoodNode115)),
    gsSPDisplayList(N(Gfx_DrawMesh_BridgeFragmentFloorTileNode120)),
    gsSPDisplayList(N(Gfx_DrawMesh_BridgeFragmentFloorTileNode119)),
    gsSPDisplayList(N(Gfx_DrawMesh_BridgeFragmentFloorTileNode118)),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_BridgeFragmentWoodNode111)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_Wood)),
    DEBUG_MESH_COLOR(0, 160, 128)
    gsSPClearGeometryMode(G_LIGHTING | G_SHADING_SMOOTH),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPVertex(vtx_C2CBA0, 24, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 0, 3, 0, 4, 3, 5, 0),
    gsSP2Triangles(6, 4, 5, 0, 6, 5, 7, 0),
    gsSP2Triangles(6, 7, 8, 0, 9, 10, 11, 0),
    gsSP2Triangles(9, 11, 12, 0, 10, 13, 14, 0),
    gsSP2Triangles(10, 14, 11, 0, 15, 16, 17, 0),
    gsSP2Triangles(15, 17, 18, 0, 16, 19, 17, 0),
    gsSP2Triangles(20, 15, 18, 0, 20, 18, 21, 0),
    gsSP2Triangles(22, 20, 21, 0, 22, 21, 23, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_BridgeFragmentWoodNode112)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_Wood)),
    DEBUG_MESH_COLOR(0, 160, 128)
    gsSPClearGeometryMode(G_LIGHTING | G_SHADING_SMOOTH),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPVertex(vtx_C2CA20, 24, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 0, 3, 0, 4, 3, 5, 0),
    gsSP2Triangles(6, 4, 5, 0, 6, 5, 7, 0),
    gsSP2Triangles(8, 6, 7, 0, 9, 10, 11, 0),
    gsSP2Triangles(9, 11, 12, 0, 10, 13, 14, 0),
    gsSP2Triangles(10, 14, 11, 0, 15, 16, 17, 0),
    gsSP2Triangles(15, 17, 18, 0, 16, 19, 17, 0),
    gsSP2Triangles(20, 15, 18, 0, 20, 18, 21, 0),
    gsSP2Triangles(22, 20, 21, 0, 22, 21, 23, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_BridgeFragmentWoodNode113)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_Wood)),
    DEBUG_MESH_COLOR(0, 160, 128)
    gsSPClearGeometryMode(G_LIGHTING | G_SHADING_SMOOTH),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPVertex(vtx_C2C8A0, 24, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(1, 4, 5, 0, 1, 5, 2, 0),
    gsSP2Triangles(4, 6, 7, 0, 4, 7, 5, 0),
    gsSP2Triangles(6, 8, 7, 0, 9, 10, 11, 0),
    gsSP2Triangles(9, 11, 12, 0, 10, 13, 14, 0),
    gsSP2Triangles(10, 14, 11, 0, 15, 16, 17, 0),
    gsSP2Triangles(15, 17, 18, 0, 15, 18, 19, 0),
    gsSP2Triangles(16, 20, 21, 0, 16, 21, 17, 0),
    gsSP2Triangles(20, 22, 23, 0, 20, 23, 21, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawGroup_WoodDebris)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPDisplayList(N(Gfx_DrawMesh_BridgeFragmentWoodNode113)),
    gsSPDisplayList(N(Gfx_DrawMesh_BridgeFragmentWoodNode112)),
    gsSPDisplayList(N(Gfx_DrawMesh_BridgeFragmentWoodNode111)),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawGroup_BridgeDebris)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPDisplayList(N(Gfx_DrawGroup_WoodDebris)),
    gsSPDisplayList(N(Gfx_DrawGroup_WoodAndFloorTileDebris)),
    gsSPDisplayList(N(Gfx_DrawGroup_LowerBridgeWoodPanelTrimDebris)),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_LowerBridgeWoodNode034)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_Wood)),
    DEBUG_MESH_COLOR(255, 128, 0)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C2C4E0, 30, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 3, 2, 0, 2, 5, 4, 0),
    gsSP2Triangles(2, 6, 5, 0, 2, 7, 6, 0),
    gsSP2Triangles(8, 7, 2, 0, 8, 2, 1, 0),
    gsSP2Triangles(9, 8, 1, 0, 8, 9, 10, 0),
    gsSP2Triangles(9, 1, 0, 0, 11, 9, 12, 0),
    gsSP2Triangles(9, 0, 12, 0, 13, 10, 9, 0),
    gsSP2Triangles(13, 9, 14, 0, 9, 11, 14, 0),
    gsSP2Triangles(15, 16, 17, 0, 18, 15, 17, 0),
    gsSP2Triangles(19, 17, 16, 0, 19, 20, 17, 0),
    gsSP2Triangles(21, 17, 20, 0, 17, 21, 22, 0),
    gsSP2Triangles(23, 18, 17, 0, 23, 17, 22, 0),
    gsSP2Triangles(24, 25, 26, 0, 24, 22, 25, 0),
    gsSP2Triangles(21, 20, 25, 0, 20, 27, 25, 0),
    gsSP2Triangles(25, 27, 28, 0, 29, 25, 28, 0),
    gsSP2Triangles(21, 25, 22, 0, 29, 26, 25, 0),
    gsSPVertex(vtx_C2C6C0, 30, 0),
    gsSP2Triangles(0, 14, 2, 0, 0, 2, 15, 0),
    gsSP2Triangles(1, 15, 2, 0, 2, 16, 17, 0),
    gsSP2Triangles(3, 16, 2, 0, 3, 2, 14, 0),
    gsSP2Triangles(2, 18, 1, 0, 2, 17, 18, 0),
    gsSP2Triangles(4, 3, 14, 0, 3, 4, 19, 0),
    gsSP2Triangles(4, 14, 0, 0, 5, 4, 20, 0),
    gsSP2Triangles(4, 0, 20, 0, 6, 4, 21, 0),
    gsSP2Triangles(4, 5, 21, 0, 6, 19, 4, 0),
    gsSP2Triangles(7, 22, 8, 0, 8, 23, 7, 0),
    gsSP2Triangles(9, 8, 22, 0, 8, 24, 23, 0),
    gsSP2Triangles(8, 25, 24, 0, 10, 25, 8, 0),
    gsSP2Triangles(10, 8, 26, 0, 9, 26, 8, 0),
    gsSP2Triangles(11, 26, 9, 0, 11, 9, 27, 0),
    gsSP2Triangles(11, 10, 26, 0, 12, 28, 11, 0),
    gsSP2Triangles(10, 11, 28, 0, 12, 11, 29, 0),
    gsSP2Triangles(13, 11, 27, 0, 11, 13, 29, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_Transform_SmashBridgesNode034)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPMatrix(&N(SmashBridgesIdentityMtx), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW),
    gsSPDisplayList(N(Gfx_DrawMesh_LowerBridgeWoodNode034)),
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_LowerBridgeWoodNode045)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_Wood)),
    DEBUG_MESH_COLOR(255, 128, 0)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C2C300, 30, 0),
    gsSP2Triangles(0, 1, 2, 0, 2, 3, 0, 0),
    gsSP2Triangles(3, 4, 0, 0, 0, 5, 6, 0),
    gsSP2Triangles(1, 0, 6, 0, 4, 7, 0, 0),
    gsSP2Triangles(0, 7, 8, 0, 5, 0, 8, 0),
    gsSP2Triangles(9, 6, 10, 0, 6, 5, 10, 0),
    gsSP2Triangles(5, 8, 10, 0, 9, 10, 11, 0),
    gsSP2Triangles(12, 11, 10, 0, 12, 10, 13, 0),
    gsSP2Triangles(10, 14, 13, 0, 14, 10, 8, 0),
    gsSP2Triangles(15, 16, 17, 0, 18, 15, 19, 0),
    gsSP2Triangles(18, 20, 15, 0, 21, 19, 15, 0),
    gsSP2Triangles(21, 15, 22, 0, 23, 22, 15, 0),
    gsSP2Triangles(15, 17, 23, 0, 15, 20, 16, 0),
    gsSP2Triangles(18, 24, 25, 0, 24, 18, 19, 0),
    gsSP2Triangles(24, 19, 21, 0, 26, 24, 27, 0),
    gsSP2Triangles(26, 25, 24, 0, 24, 28, 27, 0),
    gsSP2Triangles(24, 21, 29, 0, 28, 24, 29, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_Transform_SmashBridgesNode045)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPMatrix(&N(SmashBridgesIdentityMtx), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW),
    gsSPDisplayList(N(Gfx_DrawMesh_LowerBridgeWoodNode045)),
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_LowerBridgeRailingPostDestroyedNode047)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2),
    gsSPDisplayList(N(Gfx_SetupTex_RailingPostDestroyed)),
    DEBUG_MESH_COLOR(255, 128, 0)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C2C1C0, 20, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsSP2Triangles(16, 17, 18, 0, 16, 18, 19, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_LowerBridgeWoodNode046)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_Wood)),
    DEBUG_MESH_COLOR(255, 128, 0)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C2BF50, 30, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
    gsSP2Triangles(4, 3, 2, 0, 4, 2, 5, 0),
    gsSP2Triangles(5, 2, 6, 0, 2, 7, 6, 0),
    gsSP2Triangles(2, 8, 7, 0, 2, 1, 8, 0),
    gsSP2Triangles(5, 6, 9, 0, 10, 4, 5, 0),
    gsSP2Triangles(11, 12, 13, 0, 11, 13, 14, 0),
    gsSP2Triangles(15, 16, 13, 0, 13, 17, 14, 0),
    gsSP2Triangles(18, 19, 14, 0, 20, 21, 15, 0),
    gsSP2Triangles(22, 20, 12, 0, 22, 12, 11, 0),
    gsSP2Triangles(23, 24, 25, 0, 26, 27, 24, 0),
    gsSP2Triangles(26, 24, 28, 0, 24, 27, 25, 0),
    gsSP1Triangle(27, 29, 25, 0),
    gsSPVertex(vtx_C2BF60, 1, 1),
    gsSPVertex(vtx_C2BFD0, 1, 2),
    gsSPVertex(vtx_C2C080, 2, 3),
    gsSPVertex(vtx_C2C0B0, 1, 5),
    gsSPVertex(vtx_C2C0F0, 2, 6),
    gsSPVertex(vtx_C2C130, 9, 8),
    gsSP2Triangles(8, 15, 1, 0, 0, 9, 8, 0),
    gsSP2Triangles(0, 8, 1, 0, 1, 10, 16, 0),
    gsSP2Triangles(1, 16, 2, 0, 1, 11, 10, 0),
    gsSP2Triangles(6, 12, 7, 0, 5, 3, 13, 0),
    gsSP1Triangle(5, 14, 4, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_Transform_SmashBridgesNode043)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPMatrix(&N(SmashBridgesNode043Mtx), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW),
    gsSPDisplayList(N(Gfx_DrawMesh_LowerBridgeWoodNode046)),
    gsSPDisplayList(N(Gfx_DrawMesh_LowerBridgeRailingPostDestroyedNode047)),
    gsSPDisplayList(N(Gfx_Transform_SmashBridgesNode045)),
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_LowerBridgeRailingPostDestroyedNode041)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2),
    gsSPDisplayList(N(Gfx_SetupTex_RailingPostDestroyed)),
    DEBUG_MESH_COLOR(255, 128, 0)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C2BE50, 16, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_LowerBridgeFloorSmoothNode039)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2),
    gsSPDisplayList(N(Gfx_SetupTex_FloorSmooth)),
    DEBUG_MESH_COLOR(255, 128, 0)
    gsSPClearGeometryMode(G_CULL_BACK | G_LIGHTING),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPVertex(vtx_C2BB50, 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsSP2Triangles(16, 17, 18, 0, 16, 18, 19, 0),
    gsSP2Triangles(20, 21, 22, 0, 20, 22, 23, 0),
    gsSP2Triangles(24, 25, 26, 0, 24, 26, 27, 0),
    gsSP2Triangles(28, 29, 30, 0, 28, 30, 31, 0),
    gsSPVertex(vtx_C2BD50, 16, 0),
    gsSP2Triangles(0, 4, 5, 0, 0, 5, 6, 0),
    gsSP2Triangles(1, 7, 8, 0, 1, 8, 9, 0),
    gsSP2Triangles(2, 10, 11, 0, 2, 11, 12, 0),
    gsSP2Triangles(3, 13, 14, 0, 3, 14, 15, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_LowerBridgeFloorSmoothNode040)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2),
    gsSPDisplayList(N(Gfx_SetupTex_FloorSmooth)),
    DEBUG_MESH_COLOR(255, 128, 0)
    gsSPClearGeometryMode(G_CULL_BACK | G_LIGHTING),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPVertex(vtx_C2BA50, 16, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_LowerBridgeFloorTileNode036)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_FloorTile)),
    DEBUG_MESH_COLOR(255, 128, 0)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C2B9B0, 10, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSP2Triangles(1, 4, 3, 0, 5, 6, 7, 0),
    gsSP2Triangles(5, 7, 8, 0, 5, 8, 9, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_LowerBridgeRailingPostDamagedNode037)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_RailingPostDamaged)),
    DEBUG_MESH_COLOR(255, 128, 0)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C2B8E0, 13, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(2, 4, 5, 0, 2, 5, 3, 0),
    gsSP2Triangles(4, 6, 7, 0, 4, 7, 5, 0),
    gsSP2Triangles(3, 5, 8, 0, 3, 8, 9, 0),
    gsSP2Triangles(10, 0, 3, 0, 10, 3, 9, 0),
    gsSP2Triangles(1, 11, 12, 0, 1, 12, 6, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_LowerBridgeWoodPanelTrimNode038)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_WoodPanelTrim)),
    DEBUG_MESH_COLOR(255, 128, 0)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C2B850, 9, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 3, 0, 4, 3, 6, 0),
    gsSP2Triangles(4, 7, 8, 0, 4, 8, 5, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_LowerBridgeWoodNode035)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_Wood)),
    DEBUG_MESH_COLOR(255, 128, 0)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C2B050, 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
    gsSP2Triangles(0, 4, 3, 0, 5, 6, 7, 0),
    gsSP2Triangles(6, 8, 7, 0, 8, 9, 7, 0),
    gsSP2Triangles(8, 10, 11, 0, 8, 11, 9, 0),
    gsSP2Triangles(5, 7, 12, 0, 11, 13, 9, 0),
    gsSP2Triangles(14, 15, 16, 0, 14, 17, 18, 0),
    gsSP2Triangles(14, 18, 19, 0, 14, 20, 17, 0),
    gsSP2Triangles(17, 21, 22, 0, 23, 5, 12, 0),
    gsSP2Triangles(24, 25, 26, 0, 24, 26, 27, 0),
    gsSP2Triangles(24, 27, 28, 0, 29, 25, 30, 0),
    gsSP2Triangles(25, 24, 31, 0, 25, 31, 30, 0),
    gsSPVertex(vtx_C2B220, 2, 0),
    gsSPVertex(vtx_C2B250, 8, 2),
    gsSPVertex(vtx_C2B410, 21, 10),
    gsSP2Triangles(2, 0, 1, 0, 2, 1, 10, 0),
    gsSP2Triangles(3, 11, 12, 0, 3, 12, 13, 0),
    gsSP2Triangles(4, 14, 15, 0, 4, 15, 16, 0),
    gsSP2Triangles(5, 17, 18, 0, 5, 18, 19, 0),
    gsSP2Triangles(6, 20, 21, 0, 6, 21, 22, 0),
    gsSP2Triangles(7, 23, 24, 0, 7, 24, 25, 0),
    gsSP2Triangles(8, 26, 27, 0, 8, 27, 28, 0),
    gsSP2Triangles(8, 9, 26, 0, 9, 29, 30, 0),
    gsSP1Triangle(9, 30, 26, 0),
    gsSPVertex(vtx_C2B2D0, 8, 0),
    gsSPVertex(vtx_C2B560, 23, 8),
    gsSP2Triangles(0, 8, 9, 0, 0, 9, 10, 0),
    gsSP2Triangles(0, 10, 11, 0, 1, 12, 13, 0),
    gsSP2Triangles(1, 2, 14, 0, 1, 14, 15, 0),
    gsSP2Triangles(1, 16, 2, 0, 2, 17, 18, 0),
    gsSP2Triangles(3, 19, 20, 0, 3, 20, 21, 0),
    gsSP2Triangles(4, 3, 21, 0, 5, 22, 23, 0),
    gsSP2Triangles(5, 24, 22, 0, 5, 25, 24, 0),
    gsSP2Triangles(6, 26, 7, 0, 6, 7, 27, 0),
    gsSP2Triangles(6, 27, 28, 0, 6, 29, 30, 0),
    gsSPVertex(vtx_C2B340, 11, 0),
    gsSPVertex(vtx_C2B6D0, 21, 11),
    gsSP2Triangles(0, 11, 12, 0, 1, 2, 13, 0),
    gsSP2Triangles(1, 13, 14, 0, 2, 15, 16, 0),
    gsSP2Triangles(2, 16, 13, 0, 3, 17, 18, 0),
    gsSP2Triangles(3, 18, 19, 0, 4, 20, 21, 0),
    gsSP2Triangles(4, 21, 22, 0, 5, 23, 24, 0),
    gsSP2Triangles(5, 24, 25, 0, 6, 5, 25, 0),
    gsSP2Triangles(6, 25, 26, 0, 7, 27, 28, 0),
    gsSP2Triangles(8, 29, 7, 0, 8, 7, 28, 0),
    gsSP2Triangles(8, 28, 30, 0, 9, 10, 31, 0),
    gsSPVertex(vtx_C2B3C0, 1, 0),
    gsSPVertex(vtx_C2B3E0, 3, 1),
    gsSPVertex(vtx_C2B800, 5, 4),
    gsSP2Triangles(1, 6, 5, 0, 1, 7, 2, 0),
    gsSP2Triangles(1, 2, 6, 0, 2, 8, 6, 0),
    gsSP1Triangle(3, 0, 4, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawGroup_LowerBridgeRightFixed)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPDisplayList(N(Gfx_DrawMesh_LowerBridgeWoodNode035)),
    gsSPDisplayList(N(Gfx_DrawMesh_LowerBridgeWoodPanelTrimNode038)),
    gsSPDisplayList(N(Gfx_DrawMesh_LowerBridgeRailingPostDamagedNode037)),
    gsSPDisplayList(N(Gfx_DrawMesh_LowerBridgeFloorTileNode036)),
    gsSPDisplayList(N(Gfx_DrawMesh_LowerBridgeFloorSmoothNode040)),
    gsSPDisplayList(N(Gfx_DrawMesh_LowerBridgeFloorSmoothNode039)),
    gsSPDisplayList(N(Gfx_DrawMesh_LowerBridgeRailingPostDestroyedNode041)),
    gsSPDisplayList(N(Gfx_Transform_SmashBridgesNode043)),
    gsSPDisplayList(N(Gfx_Transform_SmashBridgesNode034)),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_LowerBridgeWoodNode022)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_Wood)),
    DEBUG_MESH_COLOR(255, 80, 160)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C2AAB0, 30, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
    gsSP2Triangles(1, 4, 2, 0, 5, 1, 3, 0),
    gsSP2Triangles(5, 6, 1, 0, 7, 1, 6, 0),
    gsSP2Triangles(7, 8, 1, 0, 8, 4, 1, 0),
    gsSP2Triangles(9, 10, 11, 0, 9, 11, 12, 0),
    gsSP2Triangles(13, 11, 14, 0, 11, 15, 14, 0),
    gsSP2Triangles(15, 11, 16, 0, 11, 17, 16, 0),
    gsSP2Triangles(11, 10, 17, 0, 11, 13, 12, 0),
    gsSP2Triangles(18, 17, 19, 0, 17, 18, 16, 0),
    gsSP2Triangles(7, 20, 8, 0, 21, 8, 20, 0),
    gsSP2Triangles(20, 7, 6, 0, 22, 20, 6, 0),
    gsSP2Triangles(15, 16, 18, 0, 15, 18, 23, 0),
    gsSP2Triangles(18, 24, 23, 0, 18, 25, 24, 0),
    gsSP2Triangles(18, 26, 25, 0, 26, 18, 19, 0),
    gsSP2Triangles(27, 28, 20, 0, 21, 20, 29, 0),
    gsSP2Triangles(22, 27, 20, 0, 28, 29, 20, 0),
    gsSPVertex(vtx_C2AC90, 17, 0),
    gsSPVertex(vtx_C2AEB0, 15, 17),
    gsSP2Triangles(0, 17, 4, 0, 0, 4, 18, 0),
    gsSP2Triangles(1, 0, 18, 0, 0, 1, 19, 0),
    gsSP2Triangles(2, 0, 19, 0, 0, 2, 20, 0),
    gsSP2Triangles(3, 0, 20, 0, 3, 17, 0, 0),
    gsSP2Triangles(4, 5, 18, 0, 5, 4, 21, 0),
    gsSP2Triangles(1, 18, 5, 0, 6, 5, 21, 0),
    gsSP2Triangles(5, 22, 23, 0, 5, 24, 22, 0),
    gsSP2Triangles(5, 6, 24, 0, 1, 5, 23, 0),
    gsSP2Triangles(7, 25, 8, 0, 7, 8, 26, 0),
    gsSP2Triangles(8, 27, 26, 0, 9, 27, 8, 0),
    gsSP2Triangles(10, 9, 8, 0, 11, 28, 8, 0),
    gsSP2Triangles(11, 8, 25, 0, 10, 8, 28, 0),
    gsSP2Triangles(12, 29, 16, 0, 12, 16, 30, 0),
    gsSP2Triangles(13, 16, 29, 0, 13, 31, 16, 0),
    gsSP2Triangles(14, 16, 31, 0, 14, 15, 16, 0),
    gsSPVertex(vtx_C2AD20, 2, 0),
    gsSPVertex(vtx_C2AD70, 17, 2),
    gsSPVertex(vtx_C2AF60, 1, 19),
    gsSPVertex(vtx_C2AF80, 10, 20),
    gsSP2Triangles(4, 22, 20, 0, 3, 22, 4, 0),
    gsSP2Triangles(5, 3, 6, 0, 2, 6, 3, 0),
    gsSP2Triangles(6, 2, 21, 0, 7, 11, 23, 0),
    gsSP2Triangles(7, 0, 11, 0, 8, 23, 11, 0),
    gsSP2Triangles(1, 11, 0, 0, 9, 8, 11, 0),
    gsSP2Triangles(10, 9, 11, 0, 10, 11, 19, 0),
    gsSP2Triangles(11, 1, 19, 0, 12, 6, 21, 0),
    gsSP2Triangles(12, 13, 6, 0, 13, 14, 6, 0),
    gsSP2Triangles(14, 24, 6, 0, 5, 6, 24, 0),
    gsSP2Triangles(15, 25, 26, 0, 16, 15, 26, 0),
    gsSP2Triangles(15, 18, 27, 0, 17, 15, 27, 0),
    gsSP2Triangles(15, 17, 28, 0, 15, 28, 25, 0),
    gsSP2Triangles(18, 15, 29, 0, 16, 29, 15, 0),
    gsSPVertex(vtx_C2AE50, 1, 0),
    gsSPVertex(vtx_C2AE70, 4, 1),
    gsSPVertex(vtx_C2B010, 4, 5),
    gsSP2Triangles(2, 1, 5, 0, 2, 6, 1, 0),
    gsSP2Triangles(0, 2, 5, 0, 2, 0, 7, 0),
    gsSP2Triangles(3, 2, 8, 0, 3, 6, 2, 0),
    gsSP2Triangles(2, 4, 8, 0, 4, 2, 7, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_Transform_SmashBridgesNode022)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPMatrix(&N(SmashBridgesIdentityMtx), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW),
    gsSPDisplayList(N(Gfx_DrawMesh_LowerBridgeWoodNode022)),
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_LowerBridgeWoodNode032)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_Wood)),
    DEBUG_MESH_COLOR(255, 80, 160)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C2A8D0, 30, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 0, 3, 0),
    gsSP2Triangles(1, 3, 4, 0, 1, 4, 2, 0),
    gsSP2Triangles(5, 6, 0, 0, 6, 7, 0, 0),
    gsSP2Triangles(8, 0, 7, 0, 8, 3, 0, 0),
    gsSP2Triangles(9, 0, 2, 0, 9, 5, 0, 0),
    gsSP2Triangles(3, 10, 4, 0, 11, 2, 4, 0),
    gsSP2Triangles(4, 10, 12, 0, 13, 4, 12, 0),
    gsSP2Triangles(13, 14, 4, 0, 11, 4, 14, 0),
    gsSP2Triangles(15, 16, 17, 0, 18, 16, 15, 0),
    gsSP2Triangles(18, 15, 19, 0, 15, 20, 19, 0),
    gsSP2Triangles(20, 15, 21, 0, 15, 22, 21, 0),
    gsSP2Triangles(22, 15, 23, 0, 15, 17, 23, 0),
    gsSP2Triangles(24, 17, 25, 0, 17, 24, 23, 0),
    gsSP2Triangles(22, 23, 24, 0, 22, 24, 26, 0),
    gsSP2Triangles(24, 27, 26, 0, 28, 24, 25, 0),
    gsSP2Triangles(24, 28, 29, 0, 24, 29, 27, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_Transform_SmashBridgesNode032)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPMatrix(&N(SmashBridgesIdentityMtx), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW),
    gsSPDisplayList(N(Gfx_DrawMesh_LowerBridgeWoodNode032)),
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_LowerBridgeRailingPostDestroyedNode030)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2),
    gsSPDisplayList(N(Gfx_SetupTex_RailingPostDestroyed)),
    DEBUG_MESH_COLOR(255, 80, 160)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C2A790, 20, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsSP2Triangles(16, 17, 18, 0, 16, 18, 19, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_LowerBridgeWoodNode031)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_Wood)),
    DEBUG_MESH_COLOR(255, 80, 160)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C2A540, 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
    gsSP2Triangles(3, 2, 4, 0, 0, 5, 6, 0),
    gsSP2Triangles(0, 6, 1, 0, 7, 1, 8, 0),
    gsSP2Triangles(7, 8, 9, 0, 7, 9, 10, 0),
    gsSP2Triangles(1, 7, 11, 0, 1, 11, 12, 0),
    gsSP2Triangles(2, 1, 12, 0, 13, 14, 8, 0),
    gsSP2Triangles(13, 8, 1, 0, 13, 1, 6, 0),
    gsSP2Triangles(15, 2, 12, 0, 15, 12, 16, 0),
    gsSP2Triangles(17, 18, 19, 0, 17, 19, 20, 0),
    gsSP2Triangles(17, 20, 21, 0, 21, 20, 22, 0),
    gsSP2Triangles(21, 22, 23, 0, 21, 23, 24, 0),
    gsSP2Triangles(25, 26, 27, 0, 25, 27, 28, 0),
    gsSP2Triangles(27, 29, 28, 0, 27, 30, 31, 0),
    gsSP1Triangle(27, 31, 29, 0),
    gsSPVertex(vtx_C2A700, 2, 0),
    gsSPVertex(vtx_C2A740, 5, 2),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 4, 0),
    gsSP2Triangles(1, 4, 2, 0, 0, 2, 5, 0),
    gsSP1Triangle(0, 5, 6, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_Transform_SmashBridgesNode029)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPMatrix(&N(SmashBridgesNode029Mtx), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW),
    gsSPDisplayList(N(Gfx_DrawMesh_LowerBridgeWoodNode031)),
    gsSPDisplayList(N(Gfx_DrawMesh_LowerBridgeRailingPostDestroyedNode030)),
    gsSPDisplayList(N(Gfx_Transform_SmashBridgesNode032)),
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_LowerBridgeRailingPostDestroyedNode028)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2),
    gsSPDisplayList(N(Gfx_SetupTex_RailingPostDestroyed)),
    DEBUG_MESH_COLOR(255, 80, 160)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C2A3C0, 24, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsSP2Triangles(16, 17, 18, 0, 16, 18, 19, 0),
    gsSP2Triangles(20, 21, 22, 0, 20, 22, 23, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_StaticFloorSmooth)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2),
    gsSPDisplayList(N(Gfx_SetupTex_FloorSmooth)),
    DEBUG_MESH_COLOR(255, 80, 160)
    gsSPClearGeometryMode(G_CULL_BACK | G_LIGHTING),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPVertex(vtx_C2A2C0, 16, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_LowerBridgeFloorSmoothNode027)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2),
    gsSPDisplayList(N(Gfx_SetupTex_FloorSmooth)),
    DEBUG_MESH_COLOR(255, 80, 160)
    gsSPClearGeometryMode(G_CULL_BACK | G_LIGHTING),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPVertex(vtx_C2A180, 20, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsSP2Triangles(16, 17, 18, 0, 16, 18, 19, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_LowerBridgeFloorTileNode024)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_FloorTile)),
    DEBUG_MESH_COLOR(255, 80, 160)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C2A080, 16, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(0, 3, 4, 0, 5, 6, 2, 0),
    gsSP2Triangles(5, 2, 1, 0, 5, 1, 7, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(8, 11, 12, 0, 12, 11, 13, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_LowerBridgeRailingPostDamagedNode025)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_RailingPostDamaged)),
    DEBUG_MESH_COLOR(255, 80, 160)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C29F50, 19, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(1, 4, 5, 0, 1, 5, 2, 0),
    gsSP2Triangles(6, 7, 8, 0, 6, 8, 4, 0),
    gsSP2Triangles(2, 5, 9, 0, 2, 9, 10, 0),
    gsSP2Triangles(3, 2, 10, 0, 3, 10, 11, 0),
    gsSP2Triangles(12, 13, 3, 0, 12, 3, 11, 0),
    gsSP2Triangles(13, 6, 0, 0, 13, 0, 3, 0),
    gsSP2Triangles(11, 10, 14, 0, 11, 14, 15, 0),
    gsSP2Triangles(16, 17, 8, 0, 16, 8, 18, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_LowerBridgeWoodPanelTrimNode026)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_WoodPanelTrim)),
    DEBUG_MESH_COLOR(255, 80, 160)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C29E00, 21, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 0, 3, 0, 4, 3, 5, 0),
    gsSP2Triangles(6, 1, 7, 0, 6, 7, 8, 0),
    gsSP2Triangles(9, 10, 6, 0, 9, 6, 11, 0),
    gsSP2Triangles(4, 5, 12, 0, 4, 12, 7, 0),
    gsSP2Triangles(13, 14, 8, 0, 13, 8, 15, 0),
    gsSP2Triangles(16, 17, 9, 0, 16, 9, 13, 0),
    gsSP2Triangles(16, 13, 15, 0, 16, 15, 18, 0),
    gsSP2Triangles(13, 9, 11, 0, 13, 11, 14, 0),
    gsSP2Triangles(19, 16, 18, 0, 19, 18, 20, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_LowerBridgeWoodNode023)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_Wood)),
    DEBUG_MESH_COLOR(255, 80, 160)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C29330, 30, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(2, 4, 3, 0, 2, 5, 6, 0),
    gsSP2Triangles(2, 6, 4, 0, 3, 7, 8, 0),
    gsSP2Triangles(3, 8, 9, 0, 3, 4, 7, 0),
    gsSP2Triangles(4, 10, 11, 0, 4, 11, 7, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsSP2Triangles(12, 15, 16, 0, 17, 15, 14, 0),
    gsSP2Triangles(17, 14, 18, 0, 17, 18, 19, 0),
    gsSP2Triangles(20, 15, 21, 0, 20, 22, 16, 0),
    gsSP2Triangles(20, 16, 15, 0, 21, 15, 23, 0),
    gsSP2Triangles(15, 17, 24, 0, 15, 24, 23, 0),
    gsSP2Triangles(25, 26, 27, 0, 25, 27, 28, 0),
    gsSP1Triangle(25, 28, 29, 0),
    gsSPVertex(vtx_C29470, 2, 0),
    gsSPVertex(vtx_C294A0, 1, 2),
    gsSPVertex(vtx_C294F0, 13, 3),
    gsSPVertex(vtx_C297F0, 16, 16),
    gsSP2Triangles(4, 3, 5, 0, 4, 5, 16, 0),
    gsSP2Triangles(4, 16, 17, 0, 6, 0, 1, 0),
    gsSP2Triangles(6, 1, 18, 0, 7, 1, 2, 0),
    gsSP2Triangles(7, 2, 19, 0, 8, 11, 10, 0),
    gsSP2Triangles(9, 20, 8, 0, 9, 8, 10, 0),
    gsSP2Triangles(10, 11, 21, 0, 10, 21, 22, 0),
    gsSP2Triangles(10, 22, 23, 0, 11, 24, 25, 0),
    gsSP2Triangles(11, 25, 21, 0, 12, 13, 15, 0),
    gsSP2Triangles(12, 15, 26, 0, 13, 14, 15, 0),
    gsSP2Triangles(13, 27, 28, 0, 13, 28, 14, 0),
    gsSP2Triangles(14, 29, 30, 0, 14, 30, 31, 0),
    gsSP1Triangle(15, 14, 31, 0),
    gsSPVertex(vtx_C29540, 1, 0),
    gsSPVertex(vtx_C29570, 1, 1),
    gsSPVertex(vtx_C295B0, 8, 2),
    gsSPVertex(vtx_C298E0, 22, 10),
    gsSP2Triangles(3, 2, 10, 0, 3, 10, 12, 0),
    gsSP2Triangles(0, 11, 13, 0, 0, 13, 1, 0),
    gsSP2Triangles(4, 14, 15, 0, 4, 15, 16, 0),
    gsSP2Triangles(5, 17, 18, 0, 5, 18, 19, 0),
    gsSP2Triangles(6, 20, 21, 0, 6, 21, 22, 0),
    gsSP2Triangles(7, 23, 24, 0, 7, 24, 25, 0),
    gsSP2Triangles(8, 26, 27, 0, 8, 27, 28, 0),
    gsSP2Triangles(9, 29, 30, 0, 9, 30, 31, 0),
    gsSPVertex(vtx_C29630, 9, 0),
    gsSPVertex(vtx_C29A40, 23, 9),
    gsSP2Triangles(0, 9, 10, 0, 0, 10, 11, 0),
    gsSP2Triangles(1, 12, 13, 0, 1, 13, 14, 0),
    gsSP2Triangles(2, 15, 3, 0, 2, 3, 16, 0),
    gsSP2Triangles(3, 4, 17, 0, 3, 17, 18, 0),
    gsSP2Triangles(4, 19, 20, 0, 4, 20, 17, 0),
    gsSP2Triangles(5, 19, 21, 0, 5, 21, 22, 0),
    gsSP2Triangles(6, 23, 24, 0, 6, 24, 25, 0),
    gsSP2Triangles(7, 26, 27, 0, 7, 27, 28, 0),
    gsSP2Triangles(8, 29, 30, 0, 8, 30, 31, 0),
    gsSPVertex(vtx_C29650, 1, 0),
    gsSPVertex(vtx_C296C0, 10, 1),
    gsSPVertex(vtx_C29AB0, 1, 11),
    gsSPVertex(vtx_C29BB0, 19, 12),
    gsSP2Triangles(1, 12, 13, 0, 1, 13, 14, 0),
    gsSP2Triangles(1, 14, 15, 0, 2, 16, 13, 0),
    gsSP2Triangles(2, 13, 12, 0, 2, 12, 17, 0),
    gsSP2Triangles(3, 18, 19, 0, 3, 19, 20, 0),
    gsSP2Triangles(4, 21, 19, 0, 4, 19, 22, 0),
    gsSP2Triangles(5, 4, 22, 0, 5, 22, 23, 0),
    gsSP2Triangles(6, 23, 24, 0, 6, 24, 25, 0),
    gsSP2Triangles(7, 6, 25, 0, 7, 25, 26, 0),
    gsSP2Triangles(8, 0, 11, 0, 8, 11, 27, 0),
    gsSP2Triangles(9, 28, 29, 0, 9, 29, 30, 0),
    gsSP1Triangle(9, 30, 10, 0),
    gsSPVertex(vtx_C29750, 10, 0),
    gsSPVertex(vtx_C29CD0, 19, 10),
    gsSP2Triangles(0, 10, 11, 0, 0, 11, 12, 0),
    gsSP2Triangles(0, 12, 13, 0, 1, 2, 3, 0),
    gsSP2Triangles(1, 3, 14, 0, 2, 15, 16, 0),
    gsSP2Triangles(2, 16, 9, 0, 2, 9, 3, 0),
    gsSP2Triangles(3, 9, 17, 0, 4, 3, 17, 0),
    gsSP2Triangles(4, 17, 18, 0, 5, 19, 20, 0),
    gsSP2Triangles(5, 20, 8, 0, 5, 8, 7, 0),
    gsSP2Triangles(6, 21, 5, 0, 6, 5, 7, 0),
    gsSP2Triangles(7, 8, 22, 0, 8, 23, 24, 0),
    gsSP2Triangles(8, 24, 22, 0, 7, 22, 25, 0),
    gsSP2Triangles(7, 25, 26, 0, 9, 27, 28, 0),
    gsSP1Triangle(9, 28, 17, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawGroup_LowerBridgeCenterCollapse)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPDisplayList(N(Gfx_DrawMesh_LowerBridgeWoodNode023)),
    gsSPDisplayList(N(Gfx_DrawMesh_LowerBridgeWoodPanelTrimNode026)),
    gsSPDisplayList(N(Gfx_DrawMesh_LowerBridgeRailingPostDamagedNode025)),
    gsSPDisplayList(N(Gfx_DrawMesh_LowerBridgeFloorTileNode024)),
    gsSPDisplayList(N(Gfx_DrawMesh_LowerBridgeFloorSmoothNode027)),
    gsSPDisplayList(N(Gfx_DrawMesh_StaticFloorSmooth)),
    gsSPDisplayList(N(Gfx_DrawMesh_LowerBridgeRailingPostDestroyedNode028)),
    gsSPDisplayList(N(Gfx_Transform_SmashBridgesNode029)),
    gsSPDisplayList(N(Gfx_Transform_SmashBridgesNode022)),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_Transform_LowerBridgeCenterCollapse)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPMatrix(&N(LowerBridgeCenterCollapseMtx), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW),
    gsSPDisplayList(N(Gfx_DrawGroup_LowerBridgeCenterCollapse)),
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_LowerBridgeWoodNode059)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_Wood)),
    DEBUG_MESH_COLOR(128, 64, 16)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C29150, 30, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
    gsSP2Triangles(1, 4, 2, 0, 5, 2, 6, 0),
    gsSP2Triangles(2, 4, 6, 0, 2, 7, 3, 0),
    gsSP2Triangles(7, 2, 8, 0, 2, 5, 8, 0),
    gsSP2Triangles(9, 10, 6, 0, 5, 6, 10, 0),
    gsSP2Triangles(8, 5, 10, 0, 11, 10, 12, 0),
    gsSP2Triangles(10, 9, 12, 0, 11, 13, 10, 0),
    gsSP2Triangles(14, 10, 13, 0, 14, 8, 10, 0),
    gsSP2Triangles(15, 16, 17, 0, 17, 18, 19, 0),
    gsSP2Triangles(20, 17, 19, 0, 18, 17, 21, 0),
    gsSP2Triangles(17, 22, 21, 0, 23, 22, 17, 0),
    gsSP2Triangles(16, 23, 17, 0, 17, 20, 15, 0),
    gsSP2Triangles(24, 19, 25, 0, 19, 18, 25, 0),
    gsSP2Triangles(18, 21, 25, 0, 26, 27, 25, 0),
    gsSP2Triangles(24, 25, 27, 0, 25, 28, 29, 0),
    gsSP2Triangles(28, 25, 21, 0, 26, 25, 29, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_Transform_SmashBridgesNode059)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPMatrix(&N(SmashBridgesIdentityMtx), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW),
    gsSPDisplayList(N(Gfx_DrawMesh_LowerBridgeWoodNode059)),
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_LowerBridgeWoodNode060)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_Wood)),
    DEBUG_MESH_COLOR(128, 64, 16)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C28D90, 30, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(2, 4, 3, 0, 2, 5, 6, 0),
    gsSP2Triangles(5, 2, 7, 0, 2, 8, 7, 0),
    gsSP2Triangles(8, 2, 1, 0, 2, 6, 4, 0),
    gsSP2Triangles(9, 8, 1, 0, 9, 10, 8, 0),
    gsSP2Triangles(0, 9, 1, 0, 9, 11, 12, 0),
    gsSP2Triangles(11, 9, 13, 0, 9, 0, 13, 0),
    gsSP2Triangles(14, 10, 9, 0, 14, 9, 12, 0),
    gsSP2Triangles(15, 16, 17, 0, 18, 15, 19, 0),
    gsSP2Triangles(15, 18, 20, 0, 21, 15, 20, 0),
    gsSP2Triangles(15, 17, 22, 0, 23, 15, 22, 0),
    gsSP2Triangles(23, 19, 15, 0, 15, 21, 16, 0),
    gsSP2Triangles(23, 24, 19, 0, 24, 23, 25, 0),
    gsSP2Triangles(24, 18, 19, 0, 26, 27, 24, 0),
    gsSP2Triangles(24, 27, 18, 0, 26, 24, 28, 0),
    gsSP2Triangles(24, 29, 28, 0, 29, 24, 25, 0),
    gsSPVertex(vtx_C28F70, 30, 0),
    gsSP2Triangles(0, 6, 1, 0, 0, 1, 20, 0),
    gsSP2Triangles(1, 3, 21, 0, 2, 1, 21, 0),
    gsSP2Triangles(2, 5, 1, 0, 3, 1, 6, 0),
    gsSP2Triangles(4, 20, 1, 0, 5, 4, 1, 0),
    gsSP2Triangles(3, 6, 9, 0, 6, 22, 9, 0),
    gsSP2Triangles(3, 9, 21, 0, 7, 9, 23, 0),
    gsSP2Triangles(7, 21, 9, 0, 8, 23, 9, 0),
    gsSP2Triangles(9, 22, 24, 0, 8, 9, 24, 0),
    gsSP2Triangles(10, 13, 25, 0, 10, 26, 13, 0),
    gsSP2Triangles(11, 27, 13, 0, 12, 11, 13, 0),
    gsSP2Triangles(13, 27, 25, 0, 12, 13, 28, 0),
    gsSP2Triangles(14, 28, 13, 0, 14, 13, 26, 0),
    gsSP2Triangles(15, 12, 28, 0, 12, 15, 11, 0),
    gsSP2Triangles(16, 19, 15, 0, 17, 29, 15, 0),
    gsSP2Triangles(18, 15, 29, 0, 18, 11, 15, 0),
    gsSP2Triangles(19, 17, 15, 0, 16, 15, 28, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_Transform_SmashBridgesNode060)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPMatrix(&N(SmashBridgesIdentityMtx), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW),
    gsSPDisplayList(N(Gfx_DrawMesh_LowerBridgeWoodNode060)),
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_LowerBridgeRailingPostNode066)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2),
    gsSPDisplayList(N(Gfx_SetupTex_RailingPost)),
    DEBUG_MESH_COLOR(128, 64, 16)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C28BB0, 30, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 0, 0, 4, 0, 3, 0),
    gsSP2Triangles(6, 7, 8, 0, 6, 8, 9, 0),
    gsSP2Triangles(8, 10, 11, 0, 8, 11, 9, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsSP2Triangles(12, 15, 16, 0, 12, 16, 17, 0),
    gsSP2Triangles(18, 19, 20, 0, 18, 20, 21, 0),
    gsSP2Triangles(18, 21, 22, 0, 18, 22, 23, 0),
    gsSP2Triangles(24, 25, 26, 0, 24, 26, 27, 0),
    gsSP2Triangles(26, 28, 29, 0, 26, 29, 27, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_LowerBridgeFloorSmoothNode062)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2),
    gsSPDisplayList(N(Gfx_SetupTex_FloorSmooth)),
    DEBUG_MESH_COLOR(128, 64, 16)
    gsSPClearGeometryMode(G_CULL_BACK | G_LIGHTING),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPVertex(vtx_C28A70, 20, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsSP2Triangles(16, 17, 18, 0, 16, 18, 19, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_LowerBridgeFloorTileNode063)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_FloorTile)),
    DEBUG_MESH_COLOR(128, 64, 16)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C28970, 16, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(0, 3, 4, 0, 2, 5, 6, 0),
    gsSP2Triangles(2, 1, 5, 0, 1, 7, 5, 0),
    gsSP2Triangles(8, 9, 10, 0, 9, 8, 11, 0),
    gsSP2Triangles(9, 11, 12, 0, 9, 12, 13, 0),
    gsSP2Triangles(9, 14, 10, 0, 15, 8, 10, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_LowerBridgeRailingPostDamagedNode064)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_RailingPostDamaged)),
    DEBUG_MESH_COLOR(128, 64, 16)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C28890, 14, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(5, 8, 9, 0, 5, 9, 10, 0),
    gsSP2Triangles(11, 12, 6, 0, 11, 6, 13, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_LowerBridgeWoodPanelTrimNode065)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_WoodPanelTrim)),
    DEBUG_MESH_COLOR(128, 64, 16)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C287A0, 15, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(1, 4, 5, 0, 1, 5, 2, 0),
    gsSP2Triangles(6, 7, 8, 0, 6, 8, 9, 0),
    gsSP2Triangles(8, 4, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(12, 13, 11, 0, 12, 11, 14, 0),
    gsSP2Triangles(12, 6, 9, 0, 12, 9, 13, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_LowerBridgeWoodNode061)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_Wood)),
    DEBUG_MESH_COLOR(128, 64, 16)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C27D60, 31, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(1, 4, 2, 0, 1, 5, 6, 0),
    gsSP2Triangles(1, 6, 4, 0, 7, 8, 9, 0),
    gsSP2Triangles(8, 10, 9, 0, 10, 11, 9, 0),
    gsSP2Triangles(5, 12, 13, 0, 5, 13, 6, 0),
    gsSP2Triangles(5, 14, 12, 0, 15, 16, 17, 0),
    gsSP2Triangles(15, 17, 18, 0, 19, 20, 17, 0),
    gsSP2Triangles(17, 21, 18, 0, 22, 23, 18, 0),
    gsSP2Triangles(24, 25, 26, 0, 26, 27, 28, 0),
    gsSP2Triangles(29, 30, 26, 0, 29, 26, 28, 0),
    gsSPVertex(vtx_C27F20, 13, 0),
    gsSPVertex(vtx_C281E0, 19, 13),
    gsSP2Triangles(3, 13, 0, 0, 4, 14, 15, 0),
    gsSP2Triangles(5, 4, 16, 0, 4, 17, 18, 0),
    gsSP2Triangles(4, 18, 16, 0, 4, 5, 14, 0),
    gsSP2Triangles(6, 5, 16, 0, 6, 16, 19, 0),
    gsSP2Triangles(5, 20, 21, 0, 5, 21, 22, 0),
    gsSP2Triangles(5, 22, 14, 0, 1, 7, 23, 0),
    gsSP2Triangles(1, 23, 8, 0, 2, 1, 8, 0),
    gsSP2Triangles(2, 8, 24, 0, 2, 24, 25, 0),
    gsSP2Triangles(9, 26, 27, 0, 9, 10, 26, 0),
    gsSP2Triangles(10, 28, 26, 0, 11, 29, 12, 0),
    gsSP2Triangles(11, 12, 30, 0, 12, 31, 30, 0),
    gsSPVertex(vtx_C27FC0, 1, 0),
    gsSPVertex(vtx_C27FE0, 10, 1),
    gsSPVertex(vtx_C282D0, 1, 11),
    gsSPVertex(vtx_C282F0, 1, 12),
    gsSPVertex(vtx_C28310, 17, 13),
    gsSP2Triangles(3, 15, 12, 0, 2, 13, 1, 0),
    gsSP2Triangles(4, 16, 17, 0, 4, 17, 18, 0),
    gsSP2Triangles(5, 19, 20, 0, 5, 20, 21, 0),
    gsSP2Triangles(6, 22, 23, 0, 6, 23, 24, 0),
    gsSP2Triangles(0, 7, 14, 0, 0, 14, 11, 0),
    gsSP2Triangles(7, 25, 26, 0, 7, 26, 14, 0),
    gsSP2Triangles(7, 27, 25, 0, 8, 9, 28, 0),
    gsSP2Triangles(9, 10, 28, 0, 10, 29, 28, 0),
    gsSPVertex(vtx_C28080, 10, 0),
    gsSPVertex(vtx_C28190, 1, 10),
    gsSPVertex(vtx_C28420, 21, 11),
    gsSP2Triangles(0, 2, 1, 0, 0, 1, 11, 0),
    gsSP2Triangles(0, 11, 12, 0, 1, 2, 13, 0),
    gsSP2Triangles(1, 13, 14, 0, 2, 15, 13, 0),
    gsSP2Triangles(3, 16, 17, 0, 3, 4, 18, 0),
    gsSP2Triangles(3, 18, 19, 0, 3, 19, 20, 0),
    gsSP2Triangles(4, 3, 17, 0, 5, 4, 17, 0),
    gsSP2Triangles(6, 21, 22, 0, 6, 22, 23, 0),
    gsSP2Triangles(7, 6, 23, 0, 6, 7, 10, 0),
    gsSP2Triangles(6, 10, 24, 0, 7, 23, 25, 0),
    gsSP2Triangles(7, 25, 26, 0, 8, 27, 28, 0),
    gsSP1Triangle(8, 28, 29, 0),
    gsSPVertex(vtx_C28110, 10, 0),
    gsSPVertex(vtx_C284F0, 1, 10),
    gsSPVertex(vtx_C28550, 20, 11),
    gsSP2Triangles(0, 11, 12, 0, 0, 12, 13, 0),
    gsSP2Triangles(1, 15, 16, 0, 1, 16, 17, 0),
    gsSP2Triangles(2, 1, 17, 0, 2, 17, 18, 0),
    gsSP2Triangles(3, 19, 20, 0, 3, 20, 21, 0),
    gsSP2Triangles(4, 3, 21, 0, 4, 21, 22, 0),
    gsSP2Triangles(5, 23, 24, 0, 5, 24, 25, 0),
    gsSP2Triangles(6, 26, 27, 0, 6, 27, 28, 0),
    gsSP2Triangles(7, 29, 10, 0, 8, 14, 10, 0),
    gsSP1Triangle(9, 30, 8, 0),
    gsSPVertex(vtx_C281B0, 3, 0),
    gsSPVertex(vtx_C28690, 9, 3),
    gsSP2Triangles(0, 3, 4, 0, 0, 4, 5, 0),
    gsSP2Triangles(1, 0, 5, 0, 0, 6, 7, 0),
    gsSP2Triangles(0, 1, 6, 0, 1, 8, 9, 0),
    gsSP2Triangles(1, 9, 6, 0, 2, 1, 5, 0),
    gsSP2Triangles(2, 5, 10, 0, 1, 11, 8, 0),
    gsSPVertex(vtx_C28720, 8, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSP2Triangles(4, 5, 6, 0, 5, 7, 6, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawGroup_LowerBridgeLeftCollapse)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPDisplayList(N(Gfx_DrawMesh_LowerBridgeWoodNode061)),
    gsSPDisplayList(N(Gfx_DrawMesh_LowerBridgeWoodPanelTrimNode065)),
    gsSPDisplayList(N(Gfx_DrawMesh_LowerBridgeRailingPostDamagedNode064)),
    gsSPDisplayList(N(Gfx_DrawMesh_LowerBridgeFloorTileNode063)),
    gsSPDisplayList(N(Gfx_DrawMesh_LowerBridgeFloorSmoothNode062)),
    gsSPDisplayList(N(Gfx_DrawMesh_LowerBridgeRailingPostNode066)),
    gsSPDisplayList(N(Gfx_Transform_SmashBridgesNode060)),
    gsSPDisplayList(N(Gfx_Transform_SmashBridgesNode059)),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_Transform_LowerBridgeLeftCollapse)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPMatrix(&N(LowerBridgeLeftCollapseMtx), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW),
    gsSPDisplayList(N(Gfx_DrawGroup_LowerBridgeLeftCollapse)),
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_LowerBridgeWoodNode012)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_Wood)),
    DEBUG_MESH_COLOR(255, 32, 32)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C27B80, 30, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 0, 3, 0),
    gsSP2Triangles(1, 4, 2, 0, 3, 5, 1, 0),
    gsSP2Triangles(5, 6, 1, 0, 6, 7, 1, 0),
    gsSP2Triangles(1, 7, 8, 0, 4, 1, 8, 0),
    gsSP2Triangles(9, 2, 10, 0, 2, 4, 10, 0),
    gsSP2Triangles(4, 8, 10, 0, 11, 10, 12, 0),
    gsSP2Triangles(10, 13, 12, 0, 9, 10, 14, 0),
    gsSP2Triangles(11, 14, 10, 0, 13, 10, 8, 0),
    gsSP2Triangles(15, 16, 17, 0, 17, 18, 15, 0),
    gsSP2Triangles(18, 19, 15, 0, 19, 20, 15, 0),
    gsSP2Triangles(15, 20, 21, 0, 22, 15, 21, 0),
    gsSP2Triangles(15, 22, 23, 0, 16, 15, 23, 0),
    gsSP2Triangles(24, 25, 21, 0, 25, 24, 26, 0),
    gsSP2Triangles(22, 21, 25, 0, 27, 28, 25, 0),
    gsSP2Triangles(29, 23, 25, 0, 23, 22, 25, 0),
    gsSP2Triangles(29, 25, 28, 0, 27, 25, 26, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_LowerBridgeWoodNode019)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_Wood)),
    DEBUG_MESH_COLOR(255, 32, 32)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C27880, 31, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(2, 1, 4, 0, 2, 4, 5, 0),
    gsSP2Triangles(5, 4, 6, 0, 5, 6, 7, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsSP2Triangles(13, 16, 17, 0, 13, 17, 14, 0),
    gsSP2Triangles(18, 19, 20, 0, 18, 20, 21, 0),
    gsSP2Triangles(16, 22, 23, 0, 16, 23, 24, 0),
    gsSP2Triangles(16, 24, 17, 0, 22, 25, 26, 0),
    gsSP2Triangles(27, 28, 29, 0, 27, 29, 30, 0),
    gsSPVertex(vtx_C27A40, 2, 0),
    gsSPVertex(vtx_C27A70, 17, 2),
    gsSP2Triangles(0, 2, 8, 0, 0, 8, 1, 0),
    gsSP2Triangles(2, 9, 10, 0, 2, 10, 11, 0),
    gsSP2Triangles(2, 11, 8, 0, 3, 11, 12, 0),
    gsSP2Triangles(4, 13, 14, 0, 4, 14, 5, 0),
    gsSP2Triangles(5, 14, 15, 0, 5, 15, 16, 0),
    gsSP2Triangles(6, 17, 13, 0, 6, 13, 4, 0),
    gsSP2Triangles(7, 18, 17, 0, 7, 17, 6, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_Transform_SmashBridgesNode019)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPMatrix(&N(SmashBridgesNode019Mtx), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW),
    gsSPDisplayList(N(Gfx_DrawMesh_LowerBridgeWoodNode019)),
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_LowerBridgeWoodNode020)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_Wood)),
    DEBUG_MESH_COLOR(255, 32, 32)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C27580, 31, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 1, 0, 4, 1, 0, 0),
    gsSP2Triangles(3, 2, 6, 0, 3, 6, 7, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsSP2Triangles(13, 16, 17, 0, 13, 17, 14, 0),
    gsSP2Triangles(18, 19, 20, 0, 18, 20, 21, 0),
    gsSP2Triangles(22, 23, 24, 0, 16, 25, 26, 0),
    gsSP2Triangles(16, 26, 23, 0, 16, 23, 17, 0),
    gsSP2Triangles(27, 28, 29, 0, 27, 29, 30, 0),
    gsSPVertex(vtx_C27740, 2, 0),
    gsSPVertex(vtx_C27770, 17, 2),
    gsSP2Triangles(0, 2, 8, 0, 0, 8, 1, 0),
    gsSP2Triangles(2, 3, 9, 0, 2, 9, 10, 0),
    gsSP2Triangles(2, 10, 8, 0, 3, 11, 12, 0),
    gsSP2Triangles(4, 13, 14, 0, 4, 14, 5, 0),
    gsSP2Triangles(5, 14, 15, 0, 5, 15, 6, 0),
    gsSP2Triangles(6, 15, 16, 0, 6, 16, 7, 0),
    gsSP2Triangles(7, 16, 17, 0, 7, 17, 18, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_Transform_SmashBridgesNode020)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPMatrix(&N(SmashBridgesNode020Mtx), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW),
    gsSPDisplayList(N(Gfx_DrawMesh_LowerBridgeWoodNode020)),
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_LowerBridgeRailingPostNode018)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2),
    gsSPDisplayList(N(Gfx_SetupTex_RailingPost)),
    DEBUG_MESH_COLOR(255, 32, 32)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C27460, 18, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(0, 3, 4, 0, 0, 4, 5, 0),
    gsSP2Triangles(6, 7, 8, 0, 6, 8, 9, 0),
    gsSP2Triangles(6, 10, 11, 0, 6, 11, 7, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsSP2Triangles(14, 16, 17, 0, 14, 17, 15, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_Transform_SmashBridgesNode018)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPMatrix(&N(SmashBridgesIdentityMtx), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW),
    gsSPDisplayList(N(Gfx_DrawMesh_LowerBridgeRailingPostNode018)),
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_LowerBridgeFloorSmoothNode014)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2),
    gsSPDisplayList(N(Gfx_SetupTex_FloorSmooth)),
    DEBUG_MESH_COLOR(255, 32, 32)
    gsSPClearGeometryMode(G_CULL_BACK | G_LIGHTING),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPVertex(vtx_C273A0, 12, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_Transform_SmashBridgesNode014)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPMatrix(&N(SmashBridgesIdentityMtx), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW),
    gsSPDisplayList(N(Gfx_DrawMesh_LowerBridgeFloorSmoothNode014)),
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_LowerBridgeFloorTileNode015)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_FloorTile)),
    DEBUG_MESH_COLOR(255, 32, 32)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C27300, 10, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(1, 4, 2, 0, 5, 6, 7, 0),
    gsSP2Triangles(6, 8, 7, 0, 9, 5, 7, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_LowerBridgeRailingPostDamagedNode016)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_RailingPostDamaged)),
    DEBUG_MESH_COLOR(255, 32, 32)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C27220, 14, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 3, 5, 0, 4, 5, 6, 0),
    gsSP2Triangles(3, 2, 7, 0, 3, 7, 5, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 7, 0),
    gsSP2Triangles(10, 11, 4, 0, 10, 4, 6, 0),
    gsSP2Triangles(11, 12, 13, 0, 11, 13, 4, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_LowerBridgeWoodPanelTrimNode017)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_WoodPanelTrim)),
    DEBUG_MESH_COLOR(255, 32, 32)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C27180, 10, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 3, 5, 0, 4, 5, 6, 0),
    gsSP2Triangles(7, 4, 8, 0, 7, 8, 9, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_LowerBridgeWoodNode013)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_Wood)),
    DEBUG_MESH_COLOR(255, 32, 32)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C26CC0, 31, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(1, 4, 5, 0, 1, 5, 2, 0),
    gsSP2Triangles(1, 6, 4, 0, 7, 8, 9, 0),
    gsSP2Triangles(8, 10, 11, 0, 8, 11, 9, 0),
    gsSP2Triangles(8, 12, 10, 0, 7, 9, 13, 0),
    gsSP2Triangles(14, 15, 16, 0, 17, 18, 14, 0),
    gsSP2Triangles(19, 20, 14, 0, 19, 14, 16, 0),
    gsSP2Triangles(21, 22, 16, 0, 23, 24, 25, 0),
    gsSP2Triangles(23, 25, 26, 0, 27, 28, 29, 0),
    gsSP1Triangle(27, 29, 30, 0),
    gsSPVertex(vtx_C26EB0, 9, 0),
    gsSPVertex(vtx_C26FB0, 22, 9),
    gsSP2Triangles(0, 9, 10, 0, 0, 10, 11, 0),
    gsSP2Triangles(1, 12, 13, 0, 1, 13, 14, 0),
    gsSP2Triangles(2, 15, 16, 0, 2, 3, 15, 0),
    gsSP2Triangles(3, 17, 15, 0, 4, 18, 19, 0),
    gsSP2Triangles(4, 19, 20, 0, 5, 6, 21, 0),
    gsSP2Triangles(5, 21, 22, 0, 6, 23, 24, 0),
    gsSP2Triangles(6, 24, 25, 0, 7, 26, 27, 0),
    gsSP2Triangles(7, 27, 28, 0, 8, 29, 30, 0),
    gsSP1Triangle(8, 30, 27, 0),
    gsSPVertex(vtx_C26F40, 7, 0),
    gsSPVertex(vtx_C27110, 7, 7),
    gsSP2Triangles(0, 7, 2, 0, 0, 2, 8, 0),
    gsSP2Triangles(1, 9, 2, 0, 2, 10, 8, 0),
    gsSP2Triangles(3, 11, 8, 0, 4, 5, 12, 0),
    gsSP2Triangles(5, 6, 12, 0, 6, 13, 12, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawGroup_LowerBridgeLeftAttachment)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPDisplayList(N(Gfx_DrawMesh_LowerBridgeWoodNode013)),
    gsSPDisplayList(N(Gfx_DrawMesh_LowerBridgeWoodPanelTrimNode017)),
    gsSPDisplayList(N(Gfx_DrawMesh_LowerBridgeRailingPostDamagedNode016)),
    gsSPDisplayList(N(Gfx_DrawMesh_LowerBridgeFloorTileNode015)),
    gsSPDisplayList(N(Gfx_Transform_SmashBridgesNode014)),
    gsSPDisplayList(N(Gfx_Transform_SmashBridgesNode018)),
    gsSPDisplayList(N(Gfx_Transform_SmashBridgesNode020)),
    gsSPDisplayList(N(Gfx_Transform_SmashBridgesNode019)),
    gsSPDisplayList(N(Gfx_DrawMesh_LowerBridgeWoodNode012)),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawGroup_BridgeSectionsAndDebris)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPDisplayList(N(Gfx_DrawGroup_LowerBridgeLeftAttachment)),
    gsSPDisplayList(N(Gfx_Transform_LowerBridgeLeftCollapse)),
    gsSPDisplayList(N(Gfx_Transform_LowerBridgeCenterCollapse)),
    gsSPDisplayList(N(Gfx_DrawGroup_LowerBridgeRightFixed)),
    gsSPDisplayList(N(Gfx_DrawGroup_BridgeDebris)),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_UpperBridgeWoodNode057)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_Wood)),
    DEBUG_MESH_COLOR(192, 48, 255)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C26890, 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 0, 5, 0, 4, 5, 6, 0),
    gsSP2Triangles(0, 3, 5, 0, 7, 8, 9, 0),
    gsSP2Triangles(7, 9, 3, 0, 7, 3, 2, 0),
    gsSP2Triangles(10, 3, 9, 0, 10, 9, 11, 0),
    gsSP2Triangles(10, 11, 12, 0, 3, 10, 13, 0),
    gsSP2Triangles(3, 13, 14, 0, 5, 3, 14, 0),
    gsSP2Triangles(15, 5, 14, 0, 15, 14, 16, 0),
    gsSP2Triangles(17, 18, 19, 0, 17, 19, 20, 0),
    gsSP2Triangles(19, 21, 20, 0, 19, 22, 23, 0),
    gsSP2Triangles(19, 23, 21, 0, 20, 21, 24, 0),
    gsSP2Triangles(21, 25, 26, 0, 21, 26, 24, 0),
    gsSP2Triangles(20, 24, 27, 0, 20, 27, 28, 0),
    gsSPVertex(vtx_C26A60, 8, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(0, 3, 4, 0, 4, 3, 5, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSPVertex(vtx_C26AE0, 30, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
    gsSP2Triangles(4, 5, 3, 0, 6, 4, 3, 0),
    gsSP2Triangles(5, 1, 3, 0, 1, 7, 8, 0),
    gsSP2Triangles(9, 2, 1, 0, 9, 1, 8, 0),
    gsSP2Triangles(5, 10, 1, 0, 10, 7, 1, 0),
    gsSP2Triangles(5, 4, 10, 0, 11, 10, 4, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsSP2Triangles(14, 13, 16, 0, 14, 17, 15, 0),
    gsSP2Triangles(14, 18, 19, 0, 17, 14, 19, 0),
    gsSP2Triangles(14, 16, 20, 0, 18, 14, 20, 0),
    gsSP2Triangles(21, 16, 22, 0, 16, 21, 20, 0),
    gsSP2Triangles(18, 20, 21, 0, 21, 23, 24, 0),
    gsSP2Triangles(21, 25, 23, 0, 21, 26, 25, 0),
    gsSP2Triangles(26, 21, 22, 0, 18, 21, 24, 0),
    gsSP2Triangles(11, 4, 27, 0, 28, 29, 4, 0),
    gsSP2Triangles(6, 28, 4, 0, 29, 27, 4, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_UpperBridgeRailingPostDestroyedNode056)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2),
    gsSPDisplayList(N(Gfx_SetupTex_RailingPostDestroyed)),
    DEBUG_MESH_COLOR(192, 48, 255)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C26750, 20, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsSP2Triangles(16, 17, 18, 0, 16, 18, 19, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawGroup_UpperBridgeRearRailing)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPDisplayList(N(Gfx_DrawMesh_UpperBridgeRailingPostDestroyedNode056)),
    gsSPDisplayList(N(Gfx_DrawMesh_UpperBridgeWoodNode057)),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_Transform_UpperBridgeRearRailing)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPMatrix(&N(UpperBridgeRearRailingMtx), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW),
    gsSPDisplayList(N(Gfx_DrawGroup_UpperBridgeRearRailing)),
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawQuad_UpperBridgeWoodPanelTrimNode073)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_WoodPanelTrim)),
    DEBUG_MESH_COLOR(32, 96, 255)
    gsSPClearGeometryMode(G_CULL_BACK | G_LIGHTING),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPVertex(vtx_C26710, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_Transform_SmashBridgesNode073)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPMatrix(&N(SmashBridgesNode073Mtx), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW),
    gsSPDisplayList(N(Gfx_DrawQuad_UpperBridgeWoodPanelTrimNode073)),
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawQuad_UpperBridgeWoodPanelTrimNode074)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_WoodPanelTrim)),
    DEBUG_MESH_COLOR(32, 96, 255)
    gsSPClearGeometryMode(G_CULL_BACK | G_LIGHTING),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPVertex(vtx_C266D0, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_Transform_SmashBridgesNode074)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPMatrix(&N(SmashBridgesNode074Mtx), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW),
    gsSPDisplayList(N(Gfx_DrawQuad_UpperBridgeWoodPanelTrimNode074)),
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawQuad_UpperBridgeWoodPanelTrimNode075)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_WoodPanelTrim)),
    DEBUG_MESH_COLOR(32, 96, 255)
    gsSPClearGeometryMode(G_CULL_BACK | G_LIGHTING),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPVertex(vtx_C26690, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_Transform_SmashBridgesNode075)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPMatrix(&N(SmashBridgesNode075Mtx), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW),
    gsSPDisplayList(N(Gfx_DrawQuad_UpperBridgeWoodPanelTrimNode075)),
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawQuad_UpperBridgeWoodPanelTrimNode076)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_WoodPanelTrim)),
    DEBUG_MESH_COLOR(32, 96, 255)
    gsSPClearGeometryMode(G_CULL_BACK | G_LIGHTING),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPVertex(vtx_C26650, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_Transform_SmashBridgesNode076)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPMatrix(&N(SmashBridgesNode076Mtx), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW),
    gsSPDisplayList(N(Gfx_DrawQuad_UpperBridgeWoodPanelTrimNode076)),
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawQuad_UpperBridgeWoodPanelTrimNode081)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_WoodPanelTrim)),
    DEBUG_MESH_COLOR(32, 96, 255)
    gsSPClearGeometryMode(G_CULL_BACK | G_LIGHTING),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPVertex(vtx_C26610, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_Transform_SmashBridgesNode081)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPMatrix(&N(SmashBridgesNode081Mtx), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW),
    gsSPDisplayList(N(Gfx_DrawQuad_UpperBridgeWoodPanelTrimNode081)),
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawQuad_UpperBridgeWoodPanelTrimNode080)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_WoodPanelTrim)),
    DEBUG_MESH_COLOR(32, 96, 255)
    gsSPClearGeometryMode(G_CULL_BACK | G_LIGHTING),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPVertex(vtx_C265D0, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_Transform_SmashBridgesNode080)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPMatrix(&N(SmashBridgesNode080Mtx), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW),
    gsSPDisplayList(N(Gfx_DrawQuad_UpperBridgeWoodPanelTrimNode080)),
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawQuad_UpperBridgeWoodPanelTrimNode079)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_WoodPanelTrim)),
    DEBUG_MESH_COLOR(32, 96, 255)
    gsSPClearGeometryMode(G_CULL_BACK | G_LIGHTING),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPVertex(vtx_C26590, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_Transform_SmashBridgesNode079)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPMatrix(&N(SmashBridgesNode079Mtx), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW),
    gsSPDisplayList(N(Gfx_DrawQuad_UpperBridgeWoodPanelTrimNode079)),
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawQuad_UpperBridgeWoodPanelTrimNode082)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_WoodPanelTrim)),
    DEBUG_MESH_COLOR(32, 96, 255)
    gsSPClearGeometryMode(G_CULL_BACK | G_LIGHTING),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPVertex(vtx_C26550, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_Transform_SmashBridgesNode082)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPMatrix(&N(SmashBridgesNode082Mtx), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW),
    gsSPDisplayList(N(Gfx_DrawQuad_UpperBridgeWoodPanelTrimNode082)),
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawQuad_UpperBridgeWoodPanelTrimNode077)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_WoodPanelTrim)),
    DEBUG_MESH_COLOR(32, 96, 255)
    gsSPClearGeometryMode(G_CULL_BACK | G_LIGHTING),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPVertex(vtx_C26510, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_Transform_SmashBridgesNode077)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPMatrix(&N(SmashBridgesNode077Mtx), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW),
    gsSPDisplayList(N(Gfx_DrawQuad_UpperBridgeWoodPanelTrimNode077)),
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawGroup_UpperBridgeWoodPanelTrimDebris)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPDisplayList(N(Gfx_Transform_SmashBridgesNode077)),
    gsSPDisplayList(N(Gfx_Transform_SmashBridgesNode082)),
    gsSPDisplayList(N(Gfx_Transform_SmashBridgesNode079)),
    gsSPDisplayList(N(Gfx_Transform_SmashBridgesNode080)),
    gsSPDisplayList(N(Gfx_Transform_SmashBridgesNode081)),
    gsSPDisplayList(N(Gfx_Transform_SmashBridgesNode076)),
    gsSPDisplayList(N(Gfx_Transform_SmashBridgesNode075)),
    gsSPDisplayList(N(Gfx_Transform_SmashBridgesNode074)),
    gsSPDisplayList(N(Gfx_Transform_SmashBridgesNode073)),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawQuad_UpperRailingDebris1)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_RailingPostDamaged)),
    DEBUG_MESH_COLOR(32, 208, 255)
    gsSPClearGeometryMode(G_CULL_BACK | G_LIGHTING),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPVertex(vtx_C264D0, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_Transform_UpperRailingDebris1)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPMatrix(&N(UpperRailingDebris1Mtx), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW),
    gsSPDisplayList(N(Gfx_DrawQuad_UpperRailingDebris1)),
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawQuad_UpperRailingDebris2)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_RailingPostDamaged)),
    DEBUG_MESH_COLOR(32, 208, 255)
    gsSPClearGeometryMode(G_CULL_BACK | G_LIGHTING),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPVertex(vtx_C26490, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_Transform_UpperRailingDebris2)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPMatrix(&N(UpperRailingDebris2Mtx), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW),
    gsSPDisplayList(N(Gfx_DrawQuad_UpperRailingDebris2)),
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawQuad_UpperRailingDebris3)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_RailingPostDamaged)),
    DEBUG_MESH_COLOR(32, 208, 255)
    gsSPClearGeometryMode(G_CULL_BACK | G_LIGHTING),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPVertex(vtx_C26450, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_Transform_UpperRailingDebris3)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPMatrix(&N(UpperRailingDebris3Mtx), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW),
    gsSPDisplayList(N(Gfx_DrawQuad_UpperRailingDebris3)),
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawQuad_UpperRailingDebris4)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_RailingPostDamaged)),
    DEBUG_MESH_COLOR(32, 208, 255)
    gsSPClearGeometryMode(G_CULL_BACK | G_LIGHTING),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPVertex(vtx_C26410, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_Transform_UpperRailingDebris4)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPMatrix(&N(UpperRailingDebris4Mtx), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW),
    gsSPDisplayList(N(Gfx_DrawQuad_UpperRailingDebris4)),
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawQuad_UpperRailingDebris5)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_RailingPostDamaged)),
    DEBUG_MESH_COLOR(32, 208, 255)
    gsSPClearGeometryMode(G_CULL_BACK | G_LIGHTING),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPVertex(vtx_C263D0, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_Transform_UpperRailingDebris5)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPMatrix(&N(UpperRailingDebris5Mtx), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW),
    gsSPDisplayList(N(Gfx_DrawQuad_UpperRailingDebris5)),
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawQuad_UpperRailingDebris6)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_RailingPostDamaged)),
    DEBUG_MESH_COLOR(32, 208, 255)
    gsSPClearGeometryMode(G_CULL_BACK | G_LIGHTING),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPVertex(vtx_C26390, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_Transform_UpperRailingDebris6)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPMatrix(&N(UpperRailingDebris6Mtx), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW),
    gsSPDisplayList(N(Gfx_DrawQuad_UpperRailingDebris6)),
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawQuad_UpperRailingDebris7)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_RailingPostDamaged)),
    DEBUG_MESH_COLOR(32, 208, 255)
    gsSPClearGeometryMode(G_CULL_BACK | G_LIGHTING),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPVertex(vtx_C26350, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_Transform_UpperRailingDebris7)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPMatrix(&N(UpperRailingDebris7Mtx), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW),
    gsSPDisplayList(N(Gfx_DrawQuad_UpperRailingDebris7)),
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawQuad_UpperRailingDebris8)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_RailingPostDamaged)),
    DEBUG_MESH_COLOR(32, 208, 255)
    gsSPClearGeometryMode(G_CULL_BACK | G_LIGHTING),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPVertex(vtx_C26310, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_Transform_UpperRailingDebris8)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPMatrix(&N(UpperRailingDebris8Mtx), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW),
    gsSPDisplayList(N(Gfx_DrawQuad_UpperRailingDebris8)),
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawQuad_UpperRailingDebris9)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_RailingPostDamaged)),
    DEBUG_MESH_COLOR(32, 208, 255)
    gsSPClearGeometryMode(G_CULL_BACK | G_LIGHTING),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPVertex(vtx_C262D0, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_Transform_UpperRailingDebris9)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPMatrix(&N(UpperRailingDebris9Mtx), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW),
    gsSPDisplayList(N(Gfx_DrawQuad_UpperRailingDebris9)),
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawQuad_UpperRailingDebris10)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_RailingPostDamaged)),
    DEBUG_MESH_COLOR(32, 208, 255)
    gsSPClearGeometryMode(G_CULL_BACK | G_LIGHTING),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPVertex(vtx_C26290, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_Transform_UpperRailingDebris10)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPMatrix(&N(UpperRailingDebris10Mtx), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW),
    gsSPDisplayList(N(Gfx_DrawQuad_UpperRailingDebris10)),
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawQuad_UpperRailingDebris11)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_RailingPostDamaged)),
    DEBUG_MESH_COLOR(32, 208, 255)
    gsSPClearGeometryMode(G_CULL_BACK | G_LIGHTING),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPVertex(vtx_C26250, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_Transform_UpperRailingDebris11)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPMatrix(&N(UpperRailingDebris11Mtx), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW),
    gsSPDisplayList(N(Gfx_DrawQuad_UpperRailingDebris11)),
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawGroup_UpperBridgeRailingDebris)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPDisplayList(N(Gfx_Transform_UpperRailingDebris11)),
    gsSPDisplayList(N(Gfx_Transform_UpperRailingDebris10)),
    gsSPDisplayList(N(Gfx_Transform_UpperRailingDebris9)),
    gsSPDisplayList(N(Gfx_Transform_UpperRailingDebris8)),
    gsSPDisplayList(N(Gfx_Transform_UpperRailingDebris7)),
    gsSPDisplayList(N(Gfx_Transform_UpperRailingDebris6)),
    gsSPDisplayList(N(Gfx_Transform_UpperRailingDebris5)),
    gsSPDisplayList(N(Gfx_Transform_UpperRailingDebris4)),
    gsSPDisplayList(N(Gfx_Transform_UpperRailingDebris3)),
    gsSPDisplayList(N(Gfx_Transform_UpperRailingDebris2)),
    gsSPDisplayList(N(Gfx_Transform_UpperRailingDebris1)),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_StaticFloorTile)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_FloorTile)),
    DEBUG_MESH_COLOR(32, 208, 255)
    gsSPClearGeometryMode(G_LIGHTING | G_SHADING_SMOOTH),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPVertex(vtx_C26130, 18, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(1, 4, 5, 0, 1, 5, 2, 0),
    gsSP2Triangles(6, 7, 8, 0, 6, 8, 9, 0),
    gsSP2Triangles(7, 10, 11, 0, 7, 11, 8, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsSP2Triangles(13, 16, 17, 0, 13, 17, 14, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_StaticWood01)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_Wood)),
    DEBUG_MESH_COLOR(32, 208, 255)
    gsSPClearGeometryMode(G_LIGHTING | G_SHADING_SMOOTH),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPVertex(vtx_C25950, 30, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 4, 0),
    gsSP2Triangles(1, 4, 2, 0, 5, 6, 7, 0),
    gsSP2Triangles(5, 8, 9, 0, 5, 9, 6, 0),
    gsSP2Triangles(8, 10, 11, 0, 8, 11, 9, 0),
    gsSP2Triangles(10, 12, 13, 0, 10, 13, 11, 0),
    gsSP2Triangles(3, 14, 15, 0, 3, 15, 4, 0),
    gsSP2Triangles(16, 17, 18, 0, 16, 18, 19, 0),
    gsSP2Triangles(17, 20, 21, 0, 17, 21, 18, 0),
    gsSP2Triangles(20, 22, 23, 0, 20, 23, 21, 0),
    gsSP2Triangles(24, 25, 26, 0, 24, 26, 27, 0),
    gsSP2Triangles(28, 24, 27, 0, 28, 27, 29, 0),
    gsSPVertex(vtx_C25A30, 2, 0),
    gsSPVertex(vtx_C25B30, 11, 2),
    gsSPVertex(vtx_C25C00, 1, 13),
    gsSPVertex(vtx_C25DA0, 17, 14),
    gsSP2Triangles(0, 2, 14, 0, 0, 14, 1, 0),
    gsSP2Triangles(3, 4, 15, 0, 3, 15, 16, 0),
    gsSP2Triangles(4, 12, 17, 0, 4, 17, 15, 0),
    gsSP2Triangles(5, 18, 19, 0, 5, 19, 20, 0),
    gsSP2Triangles(6, 5, 20, 0, 6, 20, 21, 0),
    gsSP2Triangles(7, 22, 23, 0, 7, 23, 24, 0),
    gsSP2Triangles(8, 7, 24, 0, 8, 24, 25, 0),
    gsSP2Triangles(9, 8, 25, 0, 9, 25, 26, 0),
    gsSP2Triangles(9, 26, 27, 0, 10, 11, 28, 0),
    gsSP2Triangles(10, 28, 29, 0, 11, 13, 30, 0),
    gsSP1Triangle(11, 30, 28, 0),
    gsSPVertex(vtx_C25AB0, 2, 0),
    gsSPVertex(vtx_C25BD0, 13, 2),
    gsSPVertex(vtx_C25DD0, 1, 15),
    gsSPVertex(vtx_C25EA0, 16, 16),
    gsSP2Triangles(2, 3, 17, 0, 2, 17, 15, 0),
    gsSP2Triangles(3, 18, 17, 0, 4, 19, 20, 0),
    gsSP2Triangles(5, 4, 20, 0, 5, 20, 16, 0),
    gsSP2Triangles(0, 6, 1, 0, 7, 8, 21, 0),
    gsSP2Triangles(7, 21, 22, 0, 8, 23, 21, 0),
    gsSP2Triangles(9, 24, 25, 0, 10, 9, 25, 0),
    gsSP2Triangles(10, 25, 26, 0, 11, 10, 26, 0),
    gsSP2Triangles(11, 26, 27, 0, 12, 11, 27, 0),
    gsSP2Triangles(12, 27, 28, 0, 13, 29, 30, 0),
    gsSP1Triangle(13, 30, 31, 0),
    gsSPVertex(vtx_C25C20, 1, 0),
    gsSPVertex(vtx_C25C80, 12, 1),
    gsSPVertex(vtx_C25F00, 1, 13),
    gsSPVertex(vtx_C25F90, 17, 14),
    gsSP2Triangles(2, 1, 14, 0, 2, 14, 15, 0),
    gsSP2Triangles(3, 0, 13, 0, 3, 13, 16, 0),
    gsSP2Triangles(4, 5, 17, 0, 4, 17, 18, 0),
    gsSP2Triangles(4, 18, 19, 0, 5, 6, 20, 0),
    gsSP2Triangles(5, 20, 17, 0, 6, 21, 22, 0),
    gsSP2Triangles(6, 22, 20, 0, 7, 3, 16, 0),
    gsSP2Triangles(7, 16, 23, 0, 8, 9, 24, 0),
    gsSP2Triangles(8, 24, 25, 0, 9, 26, 27, 0),
    gsSP2Triangles(9, 27, 24, 0, 10, 11, 28, 0),
    gsSP2Triangles(10, 28, 29, 0, 11, 12, 30, 0),
    gsSP1Triangle(11, 30, 28, 0),
    gsSPVertex(vtx_C25CF0, 1, 0),
    gsSPVertex(vtx_C25D30, 7, 1),
    gsSPVertex(vtx_C26040, 1, 8),
    gsSPVertex(vtx_C26090, 10, 9),
    gsSP2Triangles(1, 2, 10, 0, 1, 10, 9, 0),
    gsSP2Triangles(2, 11, 10, 0, 3, 0, 8, 0),
    gsSP2Triangles(3, 8, 12, 0, 4, 13, 14, 0),
    gsSP2Triangles(4, 14, 15, 0, 5, 4, 15, 0),
    gsSP2Triangles(5, 15, 16, 0, 6, 5, 16, 0),
    gsSP2Triangles(6, 16, 17, 0, 6, 17, 18, 0),
    gsSP1Triangle(7, 3, 12, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawGroup_StaticFloorTileAndWood)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPDisplayList(N(Gfx_DrawMesh_StaticWood01)),
    gsSPDisplayList(N(Gfx_DrawMesh_StaticFloorTile)),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_StaticWood02)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_Wood)),
    DEBUG_MESH_COLOR(32, 96, 255)
    gsSPClearGeometryMode(G_LIGHTING | G_SHADING_SMOOTH),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPVertex(vtx_C25350, 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(1, 4, 5, 0, 1, 5, 2, 0),
    gsSP2Triangles(4, 6, 7, 0, 4, 7, 5, 0),
    gsSP2Triangles(6, 8, 7, 0, 9, 10, 11, 0),
    gsSP2Triangles(9, 11, 12, 0, 10, 13, 14, 0),
    gsSP2Triangles(10, 14, 11, 0, 15, 16, 17, 0),
    gsSP2Triangles(15, 17, 18, 0, 15, 18, 19, 0),
    gsSP2Triangles(16, 20, 21, 0, 16, 21, 17, 0),
    gsSP2Triangles(20, 22, 23, 0, 20, 23, 21, 0),
    gsSP2Triangles(24, 25, 26, 0, 27, 24, 26, 0),
    gsSP1Triangle(27, 26, 28, 0),
    gsSPVertex(vtx_C25500, 17, 0),
    gsSPVertex(vtx_C25710, 14, 17),
    gsSP2Triangles(2, 3, 4, 0, 2, 4, 5, 0),
    gsSP2Triangles(6, 2, 5, 0, 6, 5, 7, 0),
    gsSP2Triangles(8, 6, 7, 0, 8, 7, 17, 0),
    gsSP2Triangles(8, 17, 18, 0, 9, 10, 19, 0),
    gsSP2Triangles(9, 19, 20, 0, 10, 21, 22, 0),
    gsSP2Triangles(10, 22, 19, 0, 11, 0, 1, 0),
    gsSP2Triangles(11, 1, 23, 0, 12, 11, 23, 0),
    gsSP2Triangles(12, 23, 24, 0, 13, 14, 25, 0),
    gsSP2Triangles(13, 25, 26, 0, 14, 27, 28, 0),
    gsSP2Triangles(14, 28, 25, 0, 15, 16, 29, 0),
    gsSP1Triangle(15, 29, 30, 0),
    gsSPVertex(vtx_C25600, 13, 0),
    gsSPVertex(vtx_C257D0, 1, 13),
    gsSPVertex(vtx_C257F0, 17, 14),
    gsSP2Triangles(0, 1, 14, 0, 0, 14, 13, 0),
    gsSP2Triangles(1, 2, 15, 0, 1, 15, 14, 0),
    gsSP2Triangles(2, 16, 15, 0, 3, 4, 17, 0),
    gsSP2Triangles(4, 5, 18, 0, 4, 18, 17, 0),
    gsSP2Triangles(5, 6, 19, 0, 5, 19, 18, 0),
    gsSP2Triangles(6, 20, 21, 0, 6, 21, 19, 0),
    gsSP2Triangles(7, 22, 23, 0, 7, 23, 24, 0),
    gsSP2Triangles(8, 7, 24, 0, 8, 24, 25, 0),
    gsSP2Triangles(9, 8, 25, 0, 9, 25, 26, 0),
    gsSP2Triangles(10, 9, 26, 0, 11, 12, 27, 0),
    gsSP2Triangles(11, 27, 28, 0, 12, 29, 30, 0),
    gsSP1Triangle(12, 30, 27, 0),
    gsSPVertex(vtx_C256D0, 4, 0),
    gsSPVertex(vtx_C25900, 5, 4),
    gsSP2Triangles(0, 1, 4, 0, 0, 4, 5, 0),
    gsSP2Triangles(1, 6, 4, 0, 2, 0, 5, 0),
    gsSP2Triangles(2, 5, 7, 0, 3, 2, 7, 0),
    gsSP1Triangle(3, 7, 8, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawGroup_StaticWood02)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPDisplayList(N(Gfx_DrawMesh_StaticWood02)),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawGroup_UpperBridgeTrimAndRailingDebris)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPDisplayList(N(Gfx_DrawGroup_StaticWood02)),
    gsSPDisplayList(N(Gfx_DrawGroup_StaticFloorTileAndWood)),
    gsSPDisplayList(N(Gfx_DrawGroup_UpperBridgeRailingDebris)),
    gsSPDisplayList(N(Gfx_DrawGroup_UpperBridgeWoodPanelTrimDebris)),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawQuad_UpperBridgeRailingPostDestroyedNode104)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2),
    gsSPDisplayList(N(Gfx_SetupTex_RailingPostDestroyed)),
    DEBUG_MESH_COLOR(32, 224, 64)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C25310, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_UpperBridgeFloorSmoothNode105)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2),
    gsSPDisplayList(N(Gfx_SetupTex_FloorSmooth)),
    DEBUG_MESH_COLOR(32, 224, 64)
    gsSPClearGeometryMode(G_CULL_BACK | G_LIGHTING),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPVertex(vtx_C25050, 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsSP2Triangles(16, 17, 18, 0, 16, 18, 19, 0),
    gsSP2Triangles(20, 21, 22, 0, 20, 22, 23, 0),
    gsSP2Triangles(24, 25, 26, 0, 24, 26, 27, 0),
    gsSP2Triangles(28, 29, 30, 0, 28, 30, 31, 0),
    gsSPVertex(vtx_C25250, 12, 0),
    gsSP2Triangles(0, 3, 4, 0, 0, 4, 5, 0),
    gsSP2Triangles(1, 6, 7, 0, 1, 7, 8, 0),
    gsSP2Triangles(2, 9, 10, 0, 2, 10, 11, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_UpperBridgeFloorTileNode096)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_FloorTile)),
    DEBUG_MESH_COLOR(32, 224, 64)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C24FB0, 10, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSP2Triangles(1, 4, 3, 0, 5, 6, 7, 0),
    gsSP2Triangles(5, 7, 8, 0, 5, 8, 9, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_UpperBridgeRailingPostDamagedNode098)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_RailingPostDamaged)),
    DEBUG_MESH_COLOR(32, 224, 64)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C24F30, 8, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_UpperBridgeWoodPanelTrimNode100)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_WoodPanelTrim)),
    DEBUG_MESH_COLOR(32, 224, 64)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C24EB0, 8, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_UpperBridgeWoodNode102)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_Wood)),
    DEBUG_MESH_COLOR(32, 224, 64)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C24350, 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 4, 0),
    gsSP2Triangles(1, 4, 2, 0, 5, 6, 7, 0),
    gsSP2Triangles(7, 8, 9, 0, 5, 7, 10, 0),
    gsSP2Triangles(5, 10, 11, 0, 5, 12, 13, 0),
    gsSP2Triangles(14, 15, 16, 0, 14, 17, 18, 0),
    gsSP2Triangles(14, 18, 19, 0, 14, 20, 17, 0),
    gsSP2Triangles(17, 21, 22, 0, 3, 23, 4, 0),
    gsSP2Triangles(23, 24, 4, 0, 23, 25, 26, 0),
    gsSP2Triangles(23, 26, 24, 0, 26, 27, 24, 0),
    gsSP2Triangles(28, 29, 30, 0, 28, 30, 31, 0),
    gsSPVertex(vtx_C24510, 1, 0),
    gsSPVertex(vtx_C24540, 12, 1),
    gsSPVertex(vtx_C24730, 17, 13),
    gsSP2Triangles(0, 1, 2, 0, 3, 13, 14, 0),
    gsSP2Triangles(4, 15, 3, 0, 4, 3, 14, 0),
    gsSP2Triangles(4, 14, 16, 0, 5, 17, 18, 0),
    gsSP2Triangles(6, 19, 20, 0, 7, 21, 22, 0),
    gsSP2Triangles(8, 23, 24, 0, 9, 4, 16, 0),
    gsSP2Triangles(10, 11, 25, 0, 11, 9, 16, 0),
    gsSP2Triangles(11, 16, 25, 0, 12, 26, 27, 0),
    gsSP2Triangles(12, 28, 26, 0, 12, 29, 28, 0),
    gsSPVertex(vtx_C24600, 10, 0),
    gsSPVertex(vtx_C24840, 20, 10),
    gsSP2Triangles(0, 10, 11, 0, 0, 12, 10, 0),
    gsSP2Triangles(0, 13, 12, 0, 1, 14, 2, 0),
    gsSP2Triangles(1, 2, 15, 0, 1, 15, 16, 0),
    gsSP2Triangles(1, 17, 18, 0, 2, 19, 20, 0),
    gsSP2Triangles(3, 21, 22, 0, 4, 23, 3, 0),
    gsSP2Triangles(4, 3, 22, 0, 4, 22, 24, 0),
    gsSP2Triangles(5, 4, 24, 0, 6, 7, 25, 0),
    gsSP2Triangles(7, 26, 25, 0, 7, 27, 26, 0),
    gsSP2Triangles(8, 9, 28, 0, 8, 28, 29, 0),
    gsSPVertex(vtx_C24690, 10, 0),
    gsSPVertex(vtx_C24960, 1, 10),
    gsSPVertex(vtx_C24980, 21, 11),
    gsSP2Triangles(0, 11, 12, 0, 0, 12, 10, 0),
    gsSP2Triangles(1, 13, 14, 0, 1, 14, 15, 0),
    gsSP2Triangles(2, 16, 17, 0, 2, 17, 18, 0),
    gsSP2Triangles(3, 19, 20, 0, 3, 20, 21, 0),
    gsSP2Triangles(4, 3, 21, 0, 4, 21, 22, 0),
    gsSP2Triangles(5, 6, 23, 0, 6, 24, 7, 0),
    gsSP2Triangles(6, 7, 25, 0, 6, 25, 23, 0),
    gsSP2Triangles(7, 26, 25, 0, 8, 27, 28, 0),
    gsSP2Triangles(8, 9, 29, 0, 8, 29, 30, 0),
    gsSP1Triangle(8, 31, 9, 0),
    gsSPVertex(vtx_C24720, 1, 0),
    gsSPVertex(vtx_C24AD0, 2, 1),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPVertex(vtx_C24AF0, 30, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 2, 0),
    gsSP2Triangles(5, 6, 2, 0, 2, 7, 0, 0),
    gsSP2Triangles(3, 2, 1, 0, 2, 6, 8, 0),
    gsSP2Triangles(2, 8, 7, 0, 5, 2, 4, 0),
    gsSP2Triangles(9, 3, 10, 0, 9, 4, 3, 0),
    gsSP2Triangles(11, 9, 10, 0, 9, 11, 12, 0),
    gsSP2Triangles(13, 14, 9, 0, 13, 9, 12, 0),
    gsSP2Triangles(9, 5, 4, 0, 5, 9, 14, 0),
    gsSP2Triangles(15, 16, 17, 0, 15, 18, 19, 0),
    gsSP2Triangles(15, 19, 16, 0, 20, 15, 17, 0),
    gsSP2Triangles(15, 20, 21, 0, 18, 15, 22, 0),
    gsSP2Triangles(23, 22, 15, 0, 23, 15, 21, 0),
    gsSP2Triangles(16, 24, 25, 0, 16, 19, 24, 0),
    gsSP2Triangles(18, 26, 24, 0, 18, 24, 19, 0),
    gsSP2Triangles(24, 26, 27, 0, 24, 27, 28, 0),
    gsSP2Triangles(24, 28, 29, 0, 29, 25, 24, 0),
    gsSPVertex(vtx_C24CD0, 30, 0),
    gsSP2Triangles(0, 2, 14, 0, 1, 14, 2, 0),
    gsSP2Triangles(1, 2, 15, 0, 2, 0, 16, 0),
    gsSP2Triangles(2, 3, 15, 0, 3, 2, 17, 0),
    gsSP2Triangles(2, 4, 17, 0, 2, 16, 4, 0),
    gsSP2Triangles(0, 5, 16, 0, 4, 16, 5, 0),
    gsSP2Triangles(4, 5, 18, 0, 0, 19, 5, 0),
    gsSP2Triangles(5, 19, 20, 0, 6, 18, 5, 0),
    gsSP2Triangles(5, 21, 6, 0, 5, 20, 21, 0),
    gsSP2Triangles(7, 22, 8, 0, 8, 23, 24, 0),
    gsSP2Triangles(8, 24, 9, 0, 9, 25, 8, 0),
    gsSP2Triangles(10, 8, 25, 0, 10, 26, 8, 0),
    gsSP2Triangles(7, 8, 26, 0, 8, 22, 23, 0),
    gsSP2Triangles(11, 7, 26, 0, 12, 11, 27, 0),
    gsSP2Triangles(11, 26, 10, 0, 11, 10, 28, 0),
    gsSP2Triangles(13, 11, 28, 0, 11, 13, 27, 0),
    gsSP2Triangles(7, 11, 29, 0, 12, 29, 11, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawGroup_UpperBridgeRightFixed)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPDisplayList(N(Gfx_DrawMesh_UpperBridgeWoodNode102)),
    gsSPDisplayList(N(Gfx_DrawMesh_UpperBridgeWoodPanelTrimNode100)),
    gsSPDisplayList(N(Gfx_DrawMesh_UpperBridgeRailingPostDamagedNode098)),
    gsSPDisplayList(N(Gfx_DrawMesh_UpperBridgeFloorTileNode096)),
    gsSPDisplayList(N(Gfx_DrawMesh_UpperBridgeFloorSmoothNode105)),
    gsSPDisplayList(N(Gfx_DrawQuad_UpperBridgeRailingPostDestroyedNode104)),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_UpperBridgeRailingPostDestroyedNode052)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2),
    gsSPDisplayList(N(Gfx_SetupTex_RailingPostDestroyed)),
    DEBUG_MESH_COLOR(255, 224, 0)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C241D0, 24, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsSP2Triangles(16, 17, 18, 0, 16, 18, 19, 0),
    gsSP2Triangles(20, 21, 22, 0, 20, 22, 23, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_UpperBridgeFloorSmoothNode054)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2),
    gsSPDisplayList(N(Gfx_SetupTex_FloorSmooth)),
    DEBUG_MESH_COLOR(255, 224, 0)
    gsSPClearGeometryMode(G_CULL_BACK | G_LIGHTING),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPVertex(vtx_C240D0, 16, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_UpperBridgeFloorTileNode051)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_FloorTile)),
    DEBUG_MESH_COLOR(255, 224, 0)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C23FD0, 16, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(0, 3, 4, 0, 5, 6, 2, 0),
    gsSP2Triangles(5, 2, 1, 0, 5, 1, 7, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(8, 11, 12, 0, 12, 11, 13, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_UpperBridgeRailingPostDamagedNode050)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_RailingPostDamaged)),
    DEBUG_MESH_COLOR(255, 224, 0)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C23F10, 12, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(1, 4, 5, 0, 1, 5, 2, 0),
    gsSP2Triangles(6, 7, 8, 0, 6, 8, 4, 0),
    gsSP2Triangles(9, 10, 8, 0, 9, 8, 11, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_UpperBridgeWoodPanelTrimNode049)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_WoodPanelTrim)),
    DEBUG_MESH_COLOR(255, 224, 0)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C23E50, 12, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(1, 4, 5, 0, 1, 5, 2, 0),
    gsSP2Triangles(5, 6, 7, 0, 5, 7, 8, 0),
    gsSP2Triangles(9, 6, 10, 0, 9, 10, 11, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_UpperBridgeWoodNode053)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_Wood)),
    DEBUG_MESH_COLOR(255, 224, 0)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C230A0, 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(2, 4, 3, 0, 2, 5, 6, 0),
    gsSP2Triangles(2, 6, 4, 0, 4, 7, 8, 0),
    gsSP2Triangles(4, 8, 9, 0, 3, 4, 9, 0),
    gsSP2Triangles(10, 11, 12, 0, 10, 12, 13, 0),
    gsSP2Triangles(11, 14, 12, 0, 11, 15, 16, 0),
    gsSP2Triangles(11, 16, 14, 0, 12, 14, 17, 0),
    gsSP2Triangles(18, 12, 17, 0, 18, 17, 19, 0),
    gsSP2Triangles(14, 20, 21, 0, 14, 21, 17, 0),
    gsSP2Triangles(3, 9, 22, 0, 3, 22, 23, 0),
    gsSP2Triangles(24, 25, 26, 0, 24, 26, 27, 0),
    gsSP2Triangles(25, 28, 26, 0, 29, 28, 25, 0),
    gsSP2Triangles(30, 29, 25, 0, 30, 25, 31, 0),
    gsSPVertex(vtx_C23240, 1, 0),
    gsSPVertex(vtx_C23260, 2, 1),
    gsSPVertex(vtx_C232A0, 12, 3),
    gsSPVertex(vtx_C234B0, 17, 15),
    gsSP2Triangles(1, 3, 15, 0, 1, 15, 0, 0),
    gsSP2Triangles(2, 4, 16, 0, 2, 16, 1, 0),
    gsSP2Triangles(5, 17, 6, 0, 5, 6, 7, 0),
    gsSP2Triangles(6, 18, 19, 0, 6, 19, 8, 0),
    gsSP2Triangles(6, 8, 7, 0, 7, 8, 20, 0),
    gsSP2Triangles(7, 20, 21, 0, 7, 21, 22, 0),
    gsSP2Triangles(8, 23, 24, 0, 8, 24, 20, 0),
    gsSP2Triangles(9, 14, 13, 0, 10, 9, 13, 0),
    gsSP2Triangles(10, 13, 25, 0, 9, 26, 27, 0),
    gsSP2Triangles(9, 27, 14, 0, 11, 28, 29, 0),
    gsSP2Triangles(11, 29, 14, 0, 11, 14, 27, 0),
    gsSP2Triangles(12, 14, 29, 0, 12, 29, 30, 0),
    gsSP1Triangle(12, 30, 31, 0),
    gsSPVertex(vtx_C23330, 13, 0),
    gsSPVertex(vtx_C235C0, 19, 13),
    gsSP2Triangles(1, 2, 13, 0, 2, 0, 14, 0),
    gsSP2Triangles(2, 14, 13, 0, 3, 1, 13, 0),
    gsSP2Triangles(3, 13, 15, 0, 4, 16, 17, 0),
    gsSP2Triangles(4, 17, 18, 0, 4, 18, 5, 0),
    gsSP2Triangles(5, 18, 19, 0, 5, 19, 20, 0),
    gsSP2Triangles(5, 20, 21, 0, 6, 22, 7, 0),
    gsSP2Triangles(6, 7, 8, 0, 7, 9, 8, 0),
    gsSP2Triangles(7, 23, 24, 0, 7, 24, 9, 0),
    gsSP2Triangles(8, 25, 26, 0, 8, 26, 27, 0),
    gsSP2Triangles(8, 9, 25, 0, 9, 28, 29, 0),
    gsSP2Triangles(9, 29, 25, 0, 10, 30, 12, 0),
    gsSP1Triangle(10, 12, 31, 0),
    gsSPVertex(vtx_C233D0, 12, 0),
    gsSPVertex(vtx_C236E0, 20, 12),
    gsSP2Triangles(2, 3, 14, 0, 2, 14, 15, 0),
    gsSP2Triangles(1, 0, 12, 0, 1, 12, 13, 0),
    gsSP2Triangles(3, 16, 17, 0, 3, 17, 14, 0),
    gsSP2Triangles(4, 16, 18, 0, 4, 18, 19, 0),
    gsSP2Triangles(5, 20, 21, 0, 5, 21, 22, 0),
    gsSP2Triangles(6, 5, 22, 0, 6, 22, 23, 0),
    gsSP2Triangles(7, 9, 24, 0, 7, 24, 20, 0),
    gsSP2Triangles(8, 25, 26, 0, 8, 26, 27, 0),
    gsSP2Triangles(9, 28, 26, 0, 9, 26, 24, 0),
    gsSP2Triangles(10, 29, 30, 0, 10, 30, 31, 0),
    gsSP1Triangle(10, 31, 11, 0),
    gsSPVertex(vtx_C23480, 3, 0),
    gsSPVertex(vtx_C23810, 10, 3),
    gsSP2Triangles(0, 3, 4, 0, 0, 4, 5, 0),
    gsSP2Triangles(0, 5, 6, 0, 1, 7, 8, 0),
    gsSP2Triangles(1, 8, 9, 0, 1, 9, 10, 0),
    gsSP2Triangles(2, 9, 8, 0, 2, 8, 11, 0),
    gsSP1Triangle(2, 11, 12, 0),
    gsSPVertex(vtx_C238B0, 31, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSP2Triangles(4, 1, 5, 0, 0, 6, 1, 0),
    gsSP2Triangles(7, 1, 6, 0, 7, 5, 1, 0),
    gsSP2Triangles(4, 8, 1, 0, 8, 3, 1, 0),
    gsSP2Triangles(9, 10, 11, 0, 11, 12, 13, 0),
    gsSP2Triangles(12, 11, 10, 0, 9, 11, 14, 0),
    gsSP2Triangles(11, 15, 14, 0, 11, 16, 15, 0),
    gsSP2Triangles(17, 11, 13, 0, 11, 17, 16, 0),
    gsSP2Triangles(18, 4, 5, 0, 4, 18, 8, 0),
    gsSP2Triangles(19, 18, 5, 0, 20, 8, 18, 0),
    gsSP2Triangles(21, 22, 23, 0, 22, 21, 24, 0),
    gsSP2Triangles(25, 21, 23, 0, 25, 26, 21, 0),
    gsSP2Triangles(21, 9, 24, 0, 9, 21, 10, 0),
    gsSP2Triangles(21, 12, 10, 0, 21, 26, 12, 0),
    gsSP2Triangles(27, 28, 29, 0, 27, 30, 28, 0),
    gsSPVertex(vtx_C239D0, 3, 0),
    gsSPVertex(vtx_C23A70, 20, 3),
    gsSPVertex(vtx_C23CE0, 8, 23),
    gsSP2Triangles(6, 9, 3, 0, 7, 6, 3, 0),
    gsSP2Triangles(7, 3, 23, 0, 8, 23, 3, 0),
    gsSP2Triangles(8, 3, 5, 0, 3, 9, 4, 0),
    gsSP2Triangles(7, 14, 6, 0, 10, 6, 14, 0),
    gsSP2Triangles(10, 14, 24, 0, 11, 24, 14, 0),
    gsSP2Triangles(12, 11, 14, 0, 13, 12, 14, 0),
    gsSP2Triangles(13, 14, 23, 0, 14, 7, 23, 0),
    gsSP2Triangles(1, 15, 0, 0, 15, 16, 0, 0),
    gsSP2Triangles(16, 17, 0, 0, 2, 0, 17, 0),
    gsSP2Triangles(18, 20, 25, 0, 18, 26, 20, 0),
    gsSP2Triangles(18, 19, 26, 0, 19, 18, 27, 0),
    gsSP2Triangles(20, 28, 25, 0, 20, 29, 28, 0),
    gsSP2Triangles(20, 21, 29, 0, 21, 20, 30, 0),
    gsSP2Triangles(20, 22, 30, 0, 22, 20, 26, 0),
    gsSP1Triangle(19, 22, 26, 0),
    gsSPVertex(vtx_C23B70, 1, 0),
    gsSPVertex(vtx_C23BA0, 17, 1),
    gsSPVertex(vtx_C23D20, 1, 18),
    gsSPVertex(vtx_C23D60, 13, 19),
    gsSP2Triangles(2, 5, 20, 0, 2, 3, 5, 0),
    gsSP2Triangles(3, 7, 5, 0, 4, 8, 5, 0),
    gsSP2Triangles(5, 6, 20, 0, 6, 5, 8, 0),
    gsSP2Triangles(4, 5, 21, 0, 7, 21, 5, 0),
    gsSP2Triangles(6, 8, 11, 0, 8, 22, 11, 0),
    gsSP2Triangles(9, 11, 23, 0, 9, 20, 11, 0),
    gsSP2Triangles(6, 11, 20, 0, 10, 23, 11, 0),
    gsSP2Triangles(11, 22, 24, 0, 10, 11, 24, 0),
    gsSP2Triangles(0, 12, 25, 0, 12, 0, 18, 0),
    gsSP2Triangles(13, 0, 25, 0, 13, 19, 0, 0),
    gsSP2Triangles(0, 19, 1, 0, 14, 15, 26, 0),
    gsSP2Triangles(15, 17, 27, 0, 15, 28, 17, 0),
    gsSP2Triangles(15, 14, 28, 0, 14, 16, 28, 0),
    gsSP2Triangles(16, 17, 28, 0, 17, 16, 29, 0),
    gsSP2Triangles(17, 30, 27, 0, 17, 31, 30, 0),
    gsSPVertex(vtx_C23C70, 1, 0),
    gsSPVertex(vtx_C23C90, 5, 1),
    gsSPVertex(vtx_C23DD0, 1, 6),
    gsSPVertex(vtx_C23E00, 1, 7),
    gsSPVertex(vtx_C23E20, 3, 8),
    gsSP2Triangles(0, 9, 1, 0, 3, 2, 7, 0),
    gsSP2Triangles(4, 0, 10, 0, 4, 9, 0, 0),
    gsSP2Triangles(0, 5, 10, 0, 5, 0, 6, 0),
    gsSP1Triangle(2, 3, 8, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawGroup_UpperBridgeRightCollapse)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPDisplayList(N(Gfx_DrawMesh_UpperBridgeWoodNode053)),
    gsSPDisplayList(N(Gfx_DrawMesh_UpperBridgeWoodPanelTrimNode049)),
    gsSPDisplayList(N(Gfx_DrawMesh_UpperBridgeRailingPostDamagedNode050)),
    gsSPDisplayList(N(Gfx_DrawMesh_UpperBridgeFloorTileNode051)),
    gsSPDisplayList(N(Gfx_DrawMesh_UpperBridgeFloorSmoothNode054)),
    gsSPDisplayList(N(Gfx_DrawMesh_UpperBridgeRailingPostDestroyedNode052)),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_Transform_UpperBridgeRightCollapse)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPMatrix(&N(UpperBridgeRightCollapseMtx), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW),
    gsSPDisplayList(N(Gfx_DrawGroup_UpperBridgeRightCollapse)),
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_UpperBridgeRailingPostNode005)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2),
    gsSPDisplayList(N(Gfx_SetupTex_RailingPost)),
    DEBUG_MESH_COLOR(144, 0, 0)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C22EC0, 30, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(0, 4, 5, 0, 0, 5, 1, 0),
    gsSP2Triangles(6, 7, 8, 0, 6, 8, 9, 0),
    gsSP2Triangles(10, 11, 6, 0, 10, 6, 9, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsSP2Triangles(12, 15, 16, 0, 12, 16, 17, 0),
    gsSP2Triangles(18, 19, 20, 0, 18, 20, 21, 0),
    gsSP2Triangles(18, 21, 22, 0, 18, 22, 23, 0),
    gsSP2Triangles(24, 25, 26, 0, 24, 26, 27, 0),
    gsSP2Triangles(26, 28, 29, 0, 26, 29, 27, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_UpperBridgeFloorSmoothNode009)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2),
    gsSPDisplayList(N(Gfx_SetupTex_FloorSmooth)),
    DEBUG_MESH_COLOR(144, 0, 0)
    gsSPClearGeometryMode(G_CULL_BACK | G_LIGHTING),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPVertex(vtx_C22C00, 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsSP2Triangles(16, 17, 18, 0, 16, 18, 19, 0),
    gsSP2Triangles(20, 21, 22, 0, 20, 22, 23, 0),
    gsSP2Triangles(24, 25, 26, 0, 24, 26, 27, 0),
    gsSP2Triangles(28, 29, 30, 0, 28, 30, 31, 0),
    gsSPVertex(vtx_C22E00, 12, 0),
    gsSP2Triangles(0, 3, 4, 0, 0, 4, 5, 0),
    gsSP2Triangles(1, 6, 7, 0, 1, 7, 8, 0),
    gsSP2Triangles(2, 9, 10, 0, 2, 10, 11, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_UpperBridgeFloorTileNode006)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_FloorTile)),
    DEBUG_MESH_COLOR(144, 0, 0)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C22B00, 16, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(0, 3, 4, 0, 2, 5, 6, 0),
    gsSP2Triangles(2, 1, 5, 0, 1, 7, 5, 0),
    gsSP2Triangles(8, 9, 10, 0, 9, 8, 11, 0),
    gsSP2Triangles(9, 11, 12, 0, 9, 12, 13, 0),
    gsSP2Triangles(9, 14, 10, 0, 15, 8, 10, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_UpperBridgeRailingPostDamagedNode007)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_RailingPostDamaged)),
    DEBUG_MESH_COLOR(144, 0, 0)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C229F0, 17, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(6, 8, 9, 0, 6, 9, 7, 0),
    gsSP2Triangles(8, 10, 11, 0, 8, 11, 9, 0),
    gsSP2Triangles(12, 4, 11, 0, 12, 11, 13, 0),
    gsSP2Triangles(14, 15, 10, 0, 14, 10, 16, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_UpperBridgeWoodPanelTrimNode008)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_WoodPanelTrim)),
    DEBUG_MESH_COLOR(144, 0, 0)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C22950, 10, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(0, 4, 5, 0, 0, 5, 1, 0),
    gsSP2Triangles(4, 6, 7, 0, 4, 7, 5, 0),
    gsSP2Triangles(8, 6, 3, 0, 8, 3, 9, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_UpperBridgeWoodNode010)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_Wood)),
    DEBUG_MESH_COLOR(144, 0, 0)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C21930, 31, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
    gsSP2Triangles(3, 2, 4, 0, 0, 5, 6, 0),
    gsSP2Triangles(0, 6, 7, 0, 0, 7, 8, 0),
    gsSP2Triangles(1, 0, 8, 0, 1, 8, 9, 0),
    gsSP2Triangles(10, 11, 12, 0, 10, 12, 13, 0),
    gsSP2Triangles(11, 14, 12, 0, 11, 15, 16, 0),
    gsSP2Triangles(11, 16, 17, 0, 11, 18, 15, 0),
    gsSP2Triangles(14, 11, 17, 0, 14, 17, 19, 0),
    gsSP2Triangles(14, 20, 21, 0, 14, 21, 12, 0),
    gsSP2Triangles(1, 22, 23, 0, 1, 23, 2, 0),
    gsSP2Triangles(24, 25, 26, 0, 27, 28, 26, 0),
    gsSP2Triangles(29, 30, 27, 0, 29, 27, 26, 0),
    gsSPVertex(vtx_C21AE0, 1, 0),
    gsSPVertex(vtx_C21B20, 11, 1),
    gsSPVertex(vtx_C21E00, 19, 12),
    gsSP2Triangles(1, 12, 13, 0, 2, 14, 13, 0),
    gsSP2Triangles(3, 4, 2, 0, 3, 2, 13, 0),
    gsSP2Triangles(4, 3, 15, 0, 3, 16, 17, 0),
    gsSP2Triangles(3, 17, 15, 0, 4, 15, 18, 0),
    gsSP2Triangles(4, 18, 19, 0, 5, 20, 2, 0),
    gsSP2Triangles(6, 7, 21, 0, 7, 22, 23, 0),
    gsSP2Triangles(7, 23, 21, 0, 7, 6, 8, 0),
    gsSP2Triangles(7, 8, 24, 0, 6, 21, 25, 0),
    gsSP2Triangles(6, 25, 26, 0, 8, 27, 24, 0),
    gsSP2Triangles(9, 28, 8, 0, 10, 29, 24, 0),
    gsSP1Triangle(11, 30, 0, 0),
    gsSPVertex(vtx_C21BD0, 12, 0),
    gsSPVertex(vtx_C21F30, 18, 12),
    gsSP2Triangles(0, 12, 13, 0, 0, 1, 12, 0),
    gsSP2Triangles(1, 5, 14, 0, 1, 14, 15, 0),
    gsSP2Triangles(1, 15, 12, 0, 2, 3, 16, 0),
    gsSP2Triangles(3, 4, 16, 0, 4, 17, 16, 0),
    gsSP2Triangles(5, 18, 19, 0, 5, 19, 14, 0),
    gsSP2Triangles(6, 20, 21, 0, 7, 22, 23, 0),
    gsSP2Triangles(8, 24, 25, 0, 9, 26, 25, 0),
    gsSP2Triangles(10, 27, 9, 0, 10, 9, 25, 0),
    gsSP2Triangles(11, 28, 9, 0, 5, 29, 18, 0),
    gsSPVertex(vtx_C21C90, 10, 0),
    gsSPVertex(vtx_C22050, 20, 10),
    gsSP2Triangles(0, 1, 10, 0, 1, 2, 10, 0),
    gsSP2Triangles(2, 11, 10, 0, 3, 5, 12, 0),
    gsSP2Triangles(3, 12, 13, 0, 3, 13, 14, 0),
    gsSP2Triangles(4, 3, 14, 0, 4, 14, 15, 0),
    gsSP2Triangles(5, 16, 17, 0, 5, 17, 18, 0),
    gsSP2Triangles(5, 18, 12, 0, 6, 19, 20, 0),
    gsSP2Triangles(6, 20, 21, 0, 6, 22, 23, 0),
    gsSP2Triangles(6, 23, 19, 0, 7, 24, 21, 0),
    gsSP2Triangles(7, 21, 25, 0, 8, 7, 25, 0),
    gsSP2Triangles(8, 25, 26, 0, 9, 27, 28, 0),
    gsSP1Triangle(9, 28, 29, 0),
    gsSPVertex(vtx_C21D30, 12, 0),
    gsSPVertex(vtx_C22190, 20, 12),
    gsSP2Triangles(0, 12, 13, 0, 0, 13, 14, 0),
    gsSP2Triangles(1, 2, 15, 0, 1, 15, 16, 0),
    gsSP2Triangles(2, 3, 17, 0, 2, 17, 15, 0),
    gsSP2Triangles(3, 18, 4, 0, 3, 4, 19, 0),
    gsSP2Triangles(4, 20, 21, 0, 4, 21, 19, 0),
    gsSP2Triangles(5, 22, 23, 0, 5, 23, 24, 0),
    gsSP2Triangles(6, 7, 25, 0, 7, 26, 25, 0),
    gsSP2Triangles(7, 6, 27, 0, 7, 27, 28, 0),
    gsSP2Triangles(7, 28, 29, 0, 8, 6, 25, 0),
    gsSP2Triangles(9, 11, 10, 0, 9, 10, 30, 0),
    gsSP1Triangle(9, 30, 31, 0),
    gsSPVertex(vtx_C21DD0, 3, 0),
    gsSPVertex(vtx_C222D0, 6, 3),
    gsSP2Triangles(0, 1, 3, 0, 1, 4, 3, 0),
    gsSP2Triangles(0, 3, 5, 0, 2, 6, 7, 0),
    gsSP1Triangle(2, 7, 8, 0),
    gsSPVertex(vtx_C22330, 30, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 1, 0, 0),
    gsSP2Triangles(1, 3, 4, 0, 1, 4, 2, 0),
    gsSP2Triangles(3, 5, 4, 0, 6, 2, 4, 0),
    gsSP2Triangles(7, 8, 2, 0, 9, 2, 8, 0),
    gsSP2Triangles(9, 0, 2, 0, 2, 6, 10, 0),
    gsSP2Triangles(7, 2, 10, 0, 3, 11, 12, 0),
    gsSP2Triangles(13, 5, 3, 0, 14, 13, 3, 0),
    gsSP2Triangles(11, 3, 0, 0, 12, 14, 3, 0),
    gsSP2Triangles(15, 16, 17, 0, 18, 15, 17, 0),
    gsSP2Triangles(19, 17, 16, 0, 20, 17, 21, 0),
    gsSP2Triangles(20, 18, 17, 0, 17, 22, 21, 0),
    gsSP2Triangles(19, 23, 17, 0, 22, 17, 23, 0),
    gsSP2Triangles(24, 21, 25, 0, 22, 25, 21, 0),
    gsSP2Triangles(22, 23, 25, 0, 26, 27, 28, 0),
    gsSP1Triangle(29, 26, 28, 0),
    gsSPVertex(vtx_C224A0, 3, 0),
    gsSPVertex(vtx_C224E0, 20, 3),
    gsSPVertex(vtx_C22780, 1, 23),
    gsSPVertex(vtx_C22810, 6, 24),
    gsSP2Triangles(4, 3, 6, 0, 7, 4, 6, 0),
    gsSP2Triangles(8, 5, 4, 0, 4, 9, 8, 0),
    gsSP2Triangles(9, 4, 23, 0, 4, 7, 23, 0),
    gsSP2Triangles(10, 24, 25, 0, 11, 24, 10, 0),
    gsSP2Triangles(12, 26, 10, 0, 12, 10, 25, 0),
    gsSP2Triangles(13, 10, 26, 0, 13, 27, 10, 0),
    gsSP2Triangles(14, 10, 27, 0, 14, 11, 10, 0),
    gsSP2Triangles(14, 16, 11, 0, 15, 11, 16, 0),
    gsSP2Triangles(16, 14, 27, 0, 17, 16, 27, 0),
    gsSP2Triangles(15, 16, 28, 0, 18, 28, 16, 0),
    gsSP2Triangles(17, 19, 16, 0, 19, 18, 16, 0),
    gsSP2Triangles(0, 20, 2, 0, 1, 2, 21, 0),
    gsSP2Triangles(22, 21, 2, 0, 2, 20, 29, 0),
    gsSP1Triangle(22, 2, 29, 0),
    gsSPVertex(vtx_C22620, 22, 0),
    gsSPVertex(vtx_C22870, 8, 22),
    gsSP2Triangles(0, 22, 3, 0, 0, 3, 23, 0),
    gsSP2Triangles(1, 3, 24, 0, 2, 5, 3, 0),
    gsSP2Triangles(3, 1, 23, 0, 4, 3, 22, 0),
    gsSP2Triangles(4, 2, 3, 0, 5, 24, 3, 0),
    gsSP2Triangles(6, 11, 25, 0, 7, 6, 25, 0),
    gsSP2Triangles(7, 26, 6, 0, 8, 6, 26, 0),
    gsSP2Triangles(8, 9, 6, 0, 9, 10, 6, 0),
    gsSP2Triangles(10, 27, 6, 0, 11, 6, 27, 0),
    gsSP2Triangles(12, 14, 15, 0, 13, 12, 15, 0),
    gsSP2Triangles(14, 28, 15, 0, 15, 10, 9, 0),
    gsSP2Triangles(15, 16, 13, 0, 15, 28, 27, 0),
    gsSP2Triangles(10, 15, 27, 0, 16, 15, 9, 0),
    gsSP2Triangles(17, 18, 19, 0, 18, 29, 19, 0),
    gsSP2Triangles(19, 29, 24, 0, 5, 19, 24, 0),
    gsSP2Triangles(19, 5, 2, 0, 20, 19, 2, 0),
    gsSP2Triangles(19, 20, 21, 0, 21, 17, 19, 0),
    gsSPVertex(vtx_C22510, 2, 0),
    gsSPVertex(vtx_C22780, 9, 2),
    gsSPVertex(vtx_C228F0, 6, 11),
    gsSP2Triangles(1, 0, 6, 0, 2, 1, 6, 0),
    gsSP2Triangles(3, 2, 6, 0, 4, 6, 0, 0),
    gsSP2Triangles(3, 6, 11, 0, 5, 11, 6, 0),
    gsSP2Triangles(5, 6, 12, 0, 6, 4, 12, 0),
    gsSP2Triangles(7, 8, 13, 0, 8, 14, 13, 0),
    gsSP2Triangles(9, 10, 15, 0, 10, 16, 15, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawGroup_UpperBridgeLeft)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPDisplayList(N(Gfx_DrawMesh_UpperBridgeWoodNode010)),
    gsSPDisplayList(N(Gfx_DrawMesh_UpperBridgeWoodPanelTrimNode008)),
    gsSPDisplayList(N(Gfx_DrawMesh_UpperBridgeRailingPostDamagedNode007)),
    gsSPDisplayList(N(Gfx_DrawMesh_UpperBridgeFloorTileNode006)),
    gsSPDisplayList(N(Gfx_DrawMesh_UpperBridgeFloorSmoothNode009)),
    gsSPDisplayList(N(Gfx_DrawMesh_UpperBridgeRailingPostNode005)),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_Transform_UpperBridgeLeft)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPMatrix(&N(UpperBridgeLeftMtx), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW),
    gsSPDisplayList(N(Gfx_DrawGroup_UpperBridgeLeft)),
    gsSPPopMatrix(G_MTX_MODELVIEW),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_UpperBridgeRailingPostNode106)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2),
    gsSPDisplayList(N(Gfx_SetupTex_RailingPost)),
    DEBUG_MESH_COLOR(128, 255, 96)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C21810, 18, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(2, 4, 5, 0, 2, 5, 3, 0),
    gsSP2Triangles(6, 7, 8, 0, 6, 8, 9, 0),
    gsSP2Triangles(6, 10, 11, 0, 6, 11, 7, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsSP2Triangles(14, 16, 17, 0, 14, 17, 15, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_UpperBridgeFloorTileNode097)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_FloorTile)),
    DEBUG_MESH_COLOR(128, 255, 96)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C21770, 10, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(1, 4, 2, 0, 5, 6, 7, 0),
    gsSP2Triangles(6, 8, 7, 0, 9, 5, 7, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_UpperBridgeRailingPostDamagedNode099)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_RailingPostDamaged)),
    DEBUG_MESH_COLOR(128, 255, 96)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C21700, 7, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 3, 0, 4, 3, 6, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_UpperBridgeWoodPanelTrimNode101)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_WoodPanelTrim)),
    DEBUG_MESH_COLOR(128, 255, 96)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C215A0, 22, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsSP2Triangles(13, 16, 17, 0, 13, 17, 18, 0),
    gsSP2Triangles(19, 20, 21, 0, 19, 21, 16, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawMesh_UpperBridgeWoodNode103)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPDisplayList(N(Gfx_SetupTex_Wood)),
    DEBUG_MESH_COLOR(128, 255, 96)
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(vtx_C20F40, 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 4, 0),
    gsSP2Triangles(1, 4, 5, 0, 1, 5, 2, 0),
    gsSP2Triangles(0, 2, 6, 0, 7, 8, 9, 0),
    gsSP2Triangles(8, 10, 11, 0, 8, 11, 12, 0),
    gsSP2Triangles(8, 12, 9, 0, 7, 9, 13, 0),
    gsSP2Triangles(14, 15, 16, 0, 14, 16, 17, 0),
    gsSP2Triangles(18, 19, 20, 0, 18, 20, 21, 0),
    gsSP2Triangles(22, 23, 24, 0, 22, 24, 25, 0),
    gsSP2Triangles(26, 27, 28, 0, 29, 30, 28, 0),
    gsSPVertex(vtx_C21100, 2, 0),
    gsSPVertex(vtx_C21130, 11, 2),
    gsSPVertex(vtx_C211F0, 1, 13),
    gsSPVertex(vtx_C21240, 18, 14),
    gsSP2Triangles(2, 3, 1, 0, 2, 1, 0, 0),
    gsSP2Triangles(4, 14, 1, 0, 5, 6, 15, 0),
    gsSP2Triangles(6, 16, 15, 0, 5, 15, 17, 0),
    gsSP2Triangles(7, 18, 19, 0, 7, 19, 20, 0),
    gsSP2Triangles(8, 9, 21, 0, 8, 21, 22, 0),
    gsSP2Triangles(9, 23, 24, 0, 9, 24, 25, 0),
    gsSP2Triangles(10, 26, 27, 0, 10, 27, 28, 0),
    gsSP2Triangles(11, 29, 30, 0, 11, 30, 27, 0),
    gsSP1Triangle(12, 31, 13, 0),
    gsSPVertex(vtx_C211E0, 6, 0),
    gsSPVertex(vtx_C21360, 6, 6),
    gsSP2Triangles(0, 6, 1, 0, 0, 1, 7, 0),
    gsSP2Triangles(1, 8, 7, 0, 2, 9, 7, 0),
    gsSP2Triangles(3, 4, 10, 0, 4, 5, 10, 0),
    gsSP1Triangle(5, 11, 10, 0),
    gsSPVertex(vtx_C213C0, 30, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 1, 0),
    gsSP2Triangles(4, 5, 1, 0, 1, 5, 2, 0),
    gsSP2Triangles(5, 6, 2, 0, 5, 4, 6, 0),
    gsSP2Triangles(0, 2, 7, 0, 8, 7, 2, 0),
    gsSP2Triangles(8, 2, 9, 0, 2, 10, 9, 0),
    gsSP2Triangles(10, 2, 6, 0, 4, 3, 11, 0),
    gsSP2Triangles(11, 12, 4, 0, 12, 13, 4, 0),
    gsSP2Triangles(4, 14, 6, 0, 13, 14, 4, 0),
    gsSP2Triangles(15, 16, 17, 0, 16, 18, 17, 0),
    gsSP2Triangles(17, 18, 19, 0, 20, 17, 19, 0),
    gsSP2Triangles(21, 15, 17, 0, 17, 22, 21, 0),
    gsSP2Triangles(22, 17, 23, 0, 17, 20, 23, 0),
    gsSP2Triangles(24, 25, 26, 0, 24, 27, 25, 0),
    gsSP2Triangles(20, 19, 25, 0, 28, 25, 19, 0),
    gsSP2Triangles(25, 28, 26, 0, 29, 25, 27, 0),
    gsSP2Triangles(29, 23, 25, 0, 23, 20, 25, 0),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawGroup_UpperBridgeLeftFixed)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPDisplayList(N(Gfx_DrawMesh_UpperBridgeWoodNode103)),
    gsSPDisplayList(N(Gfx_DrawMesh_UpperBridgeWoodPanelTrimNode101)),
    gsSPDisplayList(N(Gfx_DrawMesh_UpperBridgeRailingPostDamagedNode099)),
    gsSPDisplayList(N(Gfx_DrawMesh_UpperBridgeFloorTileNode097)),
    gsSPDisplayList(N(Gfx_DrawMesh_UpperBridgeRailingPostNode106)),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawGroup_BridgeMainStructures)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPDisplayList(N(Gfx_DrawGroup_UpperBridgeLeftFixed)),
    gsSPDisplayList(N(Gfx_Transform_UpperBridgeLeft)),
    gsSPDisplayList(N(Gfx_Transform_UpperBridgeRightCollapse)),
    gsSPDisplayList(N(Gfx_DrawGroup_UpperBridgeRightFixed)),
    gsSPDisplayList(N(Gfx_DrawGroup_UpperBridgeTrimAndRailingDebris)),
    gsSPDisplayList(N(Gfx_Transform_UpperBridgeRearRailing)),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawGroup_BridgeSceneGeometry)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPDisplayList(N(Gfx_DrawGroup_BridgeMainStructures)),
    gsSPDisplayList(N(Gfx_DrawGroup_BridgeSectionsAndDebris)),
    gsSPDisplayList(N(Gfx_DrawGroup_BridgeSupportArches)),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawGroup_SmashBridgesRoot)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPDisplayList(N(Gfx_DrawGroup_BridgeSceneGeometry)),
    gsSPEndDisplayList(),
};

Gfx N(Gfx_DrawModel_SmashBridges)[] = {
    gsSPSetLights1(N(SmashBridgesLights)),
    gsSPDisplayList(N(Gfx_DrawGroup_SmashBridgesRoot)),
    gsSPEndDisplayList(),
};

#include "smash_bridges_skeleton.inc.c"

#include "smash_bridges_anim.inc.c"
