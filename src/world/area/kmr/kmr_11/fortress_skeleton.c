#include "kmr_11.h"

StaticAnimatorNode N(FortressNode_td1) = {
    .pos = { -334.0f, -285.0f, -118.0f },
    .rot = { AS_F(0.0f), AS_F(-164.94827f), AS_F(0.0f) },
    .modelID = AS_MODEL_ID(MODEL_td1),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(FortressWallTransform_td1_2) = {
    .pos = { 0.0f, 89.0f, 0.0f },
    .rot = { AS_F(-180.0f), AS_F(0.0f), AS_F(0.0f) },
    .child = &N(FortressNode_td1),
};

StaticAnimatorNode N(FortressWallTransform_td1_1) = {
    .pos = { -3.0f, -20.0f, -103.0f },
    .rot = { AS_F(-180.0f), AS_F(152.24768f), AS_F(0.0f) },
    .child = &N(FortressWallTransform_td1_2),
};

StaticAnimatorNode N(FortressNode_te1) = {
    .pos = { -129.0f, -285.0f, -386.0f },
    .rot = { AS_F(0.0f), AS_F(135.04807f), AS_F(0.0f) },
    .modelID = AS_MODEL_ID(MODEL_te1),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(FortressWallTransform_te1_2) = {
    .pos = { 0.0f, 89.0f, 0.0f },
    .rot = { AS_F(-180.0f), AS_F(0.0f), AS_F(0.0f) },
    .child = &N(FortressNode_te1),
};

StaticAnimatorNode N(FortressWallTransform_te1_1) = {
    .pos = { -77.0f, -20.0f, -101.0f },
    .rot = { AS_F(-180.0f), AS_F(-147.74864f), AS_F(0.0f) },
    .child = &N(FortressWallTransform_te1_2),
    .sibling = &N(FortressWallTransform_td1_1),
};

StaticAnimatorNode N(FortressNode_tf1) = {
    .pos = { 205.0f, -285.0f, -342.0f },
    .rot = { AS_F(0.0f), AS_F(75.0499f), AS_F(0.0f) },
    .modelID = AS_MODEL_ID(MODEL_tf1),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(FortressWallTransform_tf1_2) = {
    .pos = { 0.0f, 89.0f, 0.0f },
    .rot = { AS_F(-180.0f), AS_F(0.0f), AS_F(0.0f) },
    .child = &N(FortressNode_tf1),
};

StaticAnimatorNode N(FortressWallTransform_tf1_1) = {
    .pos = { -111.0f, -20.0f, -35.0f },
    .rot = { AS_F(-180.0f), AS_F(-87.74499f), AS_F(0.0f) },
    .child = &N(FortressWallTransform_tf1_2),
    .sibling = &N(FortressWallTransform_te1_1),
};

StaticAnimatorNode N(FortressNode_ta1) = {
    .pos = { 334.0f, -285.0f, -31.0f },
    .rot = { AS_F(0.0f), AS_F(15.046235f), AS_F(0.0f) },
    .modelID = AS_MODEL_ID(MODEL_ta1),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(FortressWallTransform_ta1_2) = {
    .pos = { 0.0f, 89.0f, 0.0f },
    .rot = { AS_F(-180.0f), AS_F(0.0f), AS_F(0.0f) },
    .child = &N(FortressNode_ta1),
};

StaticAnimatorNode N(FortressWallTransform_ta1_1) = {
    .pos = { -71.0f, -20.0f, 27.0f },
    .rot = { AS_F(-180.0f), AS_F(-27.746819f), AS_F(0.0f) },
    .child = &N(FortressWallTransform_ta1_2),
    .sibling = &N(FortressWallTransform_tf1_1),
};

StaticAnimatorNode N(FortressNode_tb1) = {
    .pos = { 129.0f, -285.0f, 236.0f },
    .rot = { AS_F(0.0f), AS_F(-44.94644f), AS_F(0.0f) },
    .modelID = AS_MODEL_ID(MODEL_tb1),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(FortressWallTransform_tb1_2) = {
    .pos = { 0.0f, 89.0f, 0.0f },
    .rot = { AS_F(-180.0f), AS_F(0.0f), AS_F(0.0f) },
    .child = &N(FortressNode_tb1),
};

StaticAnimatorNode N(FortressWallTransform_tb1_1) = {
    .pos = { 2.0f, -20.0f, 24.0f },
    .rot = { AS_F(-180.0f), AS_F(32.245857f), AS_F(0.0f) },
    .child = &N(FortressWallTransform_tb1_2),
    .sibling = &N(FortressWallTransform_ta1_1),
};

StaticAnimatorNode N(FortressNode_tc1) = {
    .pos = { -205.0f, -285.0f, 192.0f },
    .rot = { AS_F(0.0f), AS_F(-104.94461f), AS_F(0.0f) },
    .modelID = AS_MODEL_ID(MODEL_tc1),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(FortressWallTransform_tc1_2) = {
    .pos = { 0.0f, 89.0f, 0.0f },
    .rot = { AS_F(-180.0f), AS_F(0.0f), AS_F(0.0f) },
    .child = &N(FortressNode_tc1),
};

StaticAnimatorNode N(FortressWallTransform_tc1_1) = {
    .pos = { 36.0f, -20.0f, -41.0f },
    .rot = { AS_F(-180.0f), AS_F(92.24952f), AS_F(0.0f) },
    .child = &N(FortressWallTransform_tc1_2),
    .sibling = &N(FortressWallTransform_tb1_1),
};

StaticAnimatorNode N(FortressWallTopRoot) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .child = &N(FortressWallTransform_tc1_1),
};

StaticAnimatorNode N(FortressNode_td2) = {
    .pos = { -334.0f, -196.0f, -117.0f },
    .rot = { AS_F(0.0f), AS_F(-164.94827f), AS_F(0.0f) },
    .modelID = AS_MODEL_ID(MODEL_td2),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(FortressWallTransform_td2) = {
    .pos = { -3.0f, -109.0f, -103.0f },
    .rot = { AS_F(-180.0f), AS_F(152.24768f), AS_F(0.0f) },
    .child = &N(FortressNode_td2),
};

StaticAnimatorNode N(FortressNode_te2) = {
    .pos = { -129.0f, -196.0f, -385.0f },
    .rot = { AS_F(0.0f), AS_F(135.04807f), AS_F(0.0f) },
    .modelID = AS_MODEL_ID(MODEL_te2),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(FortressWallTransform_te2) = {
    .pos = { -77.0f, -109.0f, -101.0f },
    .rot = { AS_F(-180.0f), AS_F(-147.74864f), AS_F(0.0f) },
    .child = &N(FortressNode_te2),
    .sibling = &N(FortressWallTransform_td2),
};

StaticAnimatorNode N(FortressNode_tf2) = {
    .pos = { 205.0f, -196.0f, -341.0f },
    .rot = { AS_F(0.0f), AS_F(75.0499f), AS_F(0.0f) },
    .modelID = AS_MODEL_ID(MODEL_tf2),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(FortressWallTransform_tf2) = {
    .pos = { -111.0f, -109.0f, -35.0f },
    .rot = { AS_F(-180.0f), AS_F(-87.74499f), AS_F(0.0f) },
    .child = &N(FortressNode_tf2),
    .sibling = &N(FortressWallTransform_te2),
};

StaticAnimatorNode N(FortressNode_ta2) = {
    .pos = { 334.0f, -196.0f, -30.0f },
    .rot = { AS_F(0.0f), AS_F(15.046235f), AS_F(0.0f) },
    .modelID = AS_MODEL_ID(MODEL_ta2),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(FortressWallTransform_ta2) = {
    .pos = { -71.0f, -109.0f, 27.0f },
    .rot = { AS_F(-180.0f), AS_F(-27.746819f), AS_F(0.0f) },
    .child = &N(FortressNode_ta2),
    .sibling = &N(FortressWallTransform_tf2),
};

StaticAnimatorNode N(FortressNode_tb2) = {
    .pos = { 129.0f, -196.0f, 237.0f },
    .rot = { AS_F(0.0f), AS_F(-44.94644f), AS_F(0.0f) },
    .modelID = AS_MODEL_ID(MODEL_tb2),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(FortressWallTransform_tb2) = {
    .pos = { 2.0f, -109.0f, 24.0f },
    .rot = { AS_F(-180.0f), AS_F(32.245857f), AS_F(0.0f) },
    .child = &N(FortressNode_tb2),
    .sibling = &N(FortressWallTransform_ta2),
};

StaticAnimatorNode N(FortressNode_tc2) = {
    .pos = { -205.0f, -196.0f, 193.0f },
    .rot = { AS_F(0.0f), AS_F(-104.94461f), AS_F(0.0f) },
    .modelID = AS_MODEL_ID(MODEL_tc2),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(FortressWallTransform_tc2) = {
    .pos = { 36.0f, -109.0f, -41.0f },
    .rot = { AS_F(-180.0f), AS_F(92.24952f), AS_F(0.0f) },
    .child = &N(FortressNode_tc2),
    .sibling = &N(FortressWallTransform_tb2),
};

StaticAnimatorNode N(FortressWallMiddleRoot) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .child = &N(FortressWallTransform_tc2),
    .sibling = &N(FortressWallTopRoot),
};

StaticAnimatorNode N(FortressNode_te3) = {
    .pos = { -129.0f, -106.0f, -384.0f },
    .rot = { AS_F(0.0f), AS_F(135.04807f), AS_F(0.0f) },
    .modelID = AS_MODEL_ID(MODEL_te3),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(FortressWallTransform_te3) = {
    .pos = { -76.0f, -106.0f, -100.0f },
    .rot = { AS_F(0.0f), AS_F(-147.74864f), AS_F(0.0f) },
    .child = &N(FortressNode_te3),
};

StaticAnimatorNode N(FortressNode_td3) = {
    .pos = { -334.0f, -106.0f, -116.0f },
    .rot = { AS_F(0.0f), AS_F(-164.94827f), AS_F(0.0f) },
    .modelID = AS_MODEL_ID(MODEL_td3),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(FortressWallTransform_td3) = {
    .pos = { -3.0f, -106.0f, -103.0f },
    .rot = { AS_F(0.0f), AS_F(152.24768f), AS_F(0.0f) },
    .child = &N(FortressNode_td3),
    .sibling = &N(FortressWallTransform_te3),
};

StaticAnimatorNode N(FortressNode_tf3) = {
    .pos = { 205.0f, -106.0f, -340.0f },
    .rot = { AS_F(0.0f), AS_F(75.0499f), AS_F(0.0f) },
    .modelID = AS_MODEL_ID(MODEL_tf3),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(FortressWallTransform_tf3) = {
    .pos = { -110.0f, -106.0f, -35.0f },
    .rot = { AS_F(0.0f), AS_F(-87.74499f), AS_F(0.0f) },
    .child = &N(FortressNode_tf3),
    .sibling = &N(FortressWallTransform_td3),
};

StaticAnimatorNode N(FortressNode_ta3) = {
    .pos = { 334.0f, -106.0f, -29.0f },
    .rot = { AS_F(0.0f), AS_F(15.046235f), AS_F(0.0f) },
    .modelID = AS_MODEL_ID(MODEL_ta3),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(FortressWallTransform_ta3) = {
    .pos = { -71.0f, -106.0f, 26.0f },
    .rot = { AS_F(0.0f), AS_F(-27.746819f), AS_F(0.0f) },
    .child = &N(FortressNode_ta3),
    .sibling = &N(FortressWallTransform_tf3),
};

StaticAnimatorNode N(FortressNode_tb3) = {
    .pos = { 129.0f, -106.0f, 238.0f },
    .rot = { AS_F(0.0f), AS_F(-44.94644f), AS_F(0.0f) },
    .modelID = AS_MODEL_ID(MODEL_tb3),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(FortressWallTransform_tb3) = {
    .pos = { 1.0f, -106.0f, 23.0f },
    .rot = { AS_F(0.0f), AS_F(32.245857f), AS_F(0.0f) },
    .child = &N(FortressNode_tb3),
    .sibling = &N(FortressWallTransform_ta3),
};

StaticAnimatorNode N(FortressNode_tc3) = {
    .pos = { -205.0f, -106.0f, 194.0f },
    .rot = { AS_F(0.0f), AS_F(-104.94461f), AS_F(0.0f) },
    .modelID = AS_MODEL_ID(MODEL_tc3),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(FortressWallTransform_tc3) = {
    .pos = { 35.0f, -106.0f, -41.0f },
    .rot = { AS_F(0.0f), AS_F(92.24952f), AS_F(0.0f) },
    .child = &N(FortressNode_tc3),
    .sibling = &N(FortressWallTransform_tb3),
};

StaticAnimatorNode N(FortressWallBottomRoot) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .child = &N(FortressWallTransform_tc3),
    .sibling = &N(FortressWallMiddleRoot),
};

StaticAnimatorNode N(FortressWallsTransform) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .child = &N(FortressWallBottomRoot),
};

StaticAnimatorNode N(FortressWallsRoot) = {
    .pos = { -266.0f, 0.0f, -99.0f },
    .rot = { AS_F(0.0f), AS_F(12.695089f), AS_F(0.0f) },
    .child = &N(FortressWallsTransform),
};

StaticAnimatorNode N(FortressNode_dummy27) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .modelID = AS_MODEL_ID(MODEL_dummy27),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(FortressDebrisTransform_dummy27_2) = {
    .pos = { -50.0f, -224.0f, 0.0f },
    .child = &N(FortressNode_dummy27),
};

StaticAnimatorNode N(FortressDebrisTransform_dummy27_1) = {
    .pos = { -67.0f, 0.0f, 86.0f },
    .rot = { AS_F(0.0f), AS_F(-44.99588f), AS_F(0.0f) },
    .child = &N(FortressDebrisTransform_dummy27_2),
};

StaticAnimatorNode N(FortressNode_dummy28) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .modelID = AS_MODEL_ID(MODEL_dummy28),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(FortressDebrisTransform_dummy28_2) = {
    .pos = { -75.0f, -400.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-180.0f) },
    .child = &N(FortressNode_dummy28),
};

StaticAnimatorNode N(FortressDebrisTransform_dummy28_1) = {
    .pos = { -53.0f, 0.0f, 72.0f },
    .rot = { AS_F(0.0f), AS_F(-44.99588f), AS_F(0.0f) },
    .child = &N(FortressDebrisTransform_dummy28_2),
    .sibling = &N(FortressDebrisTransform_dummy27_1),
};

StaticAnimatorNode N(FortressNode_dummy29) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .modelID = AS_MODEL_ID(MODEL_dummy29),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(FortressDebrisTransform_dummy29_2) = {
    .pos = { -50.0f, -224.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-89.99725f) },
    .child = &N(FortressNode_dummy29),
};

StaticAnimatorNode N(FortressDebrisTransform_dummy29_1) = {
    .pos = { -58.0f, 0.0f, 55.0f },
    .rot = { AS_F(0.0f), AS_F(-44.99588f), AS_F(0.0f) },
    .child = &N(FortressDebrisTransform_dummy29_2),
    .sibling = &N(FortressDebrisTransform_dummy28_1),
};

StaticAnimatorNode N(FortressDebrisGroup_dummy27) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .child = &N(FortressDebrisTransform_dummy29_1),
};

StaticAnimatorNode N(FortressNode_dummy21) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .modelID = AS_MODEL_ID(MODEL_dummy21),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(FortressDebrisTransform_dummy21_2) = {
    .pos = { -50.0f, -224.0f, 0.0f },
    .child = &N(FortressNode_dummy21),
};

StaticAnimatorNode N(FortressDebrisTransform_dummy21_1) = {
    .pos = { -288.0f, 0.0f, 204.0f },
    .rot = { AS_F(0.0f), AS_F(-89.99725f), AS_F(0.0f) },
    .child = &N(FortressDebrisTransform_dummy21_2),
};

StaticAnimatorNode N(FortressNode_dummy22) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .modelID = AS_MODEL_ID(MODEL_dummy22),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(FortressDebrisTransform_dummy22_2) = {
    .pos = { -75.0f, -400.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-180.0f) },
    .child = &N(FortressNode_dummy22),
};

StaticAnimatorNode N(FortressDebrisTransform_dummy22_1) = {
    .pos = { -300.0f, 0.0f, 201.0f },
    .rot = { AS_F(0.0f), AS_F(-89.99725f), AS_F(0.0f) },
    .child = &N(FortressDebrisTransform_dummy22_2),
    .sibling = &N(FortressDebrisTransform_dummy21_1),
};

StaticAnimatorNode N(FortressNode_dummy23) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .modelID = AS_MODEL_ID(MODEL_dummy23),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(FortressDebrisTransform_dummy23_2) = {
    .pos = { -50.0f, -224.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-89.99725f) },
    .child = &N(FortressNode_dummy23),
};

StaticAnimatorNode N(FortressDebrisTransform_dummy23_1) = {
    .pos = { -269.0f, 0.0f, 186.0f },
    .rot = { AS_F(0.0f), AS_F(-89.99725f), AS_F(0.0f) },
    .child = &N(FortressDebrisTransform_dummy23_2),
    .sibling = &N(FortressDebrisTransform_dummy22_1),
};

StaticAnimatorNode N(FortressDebrisGroup_dummy21) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .child = &N(FortressDebrisTransform_dummy23_1),
    .sibling = &N(FortressDebrisGroup_dummy27),
};

StaticAnimatorNode N(FortressNode_dummy7) = {
    .pos = { 0.0f, -20.0f, 0.0f },
    .modelID = AS_MODEL_ID(MODEL_dummy7),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(FortressDebrisTransform_dummy7_2) = {
    .pos = { 0.0f, -400.0f, 203.0f },
    .child = &N(FortressNode_dummy7),
};

StaticAnimatorNode N(FortressDebrisTransform_dummy7_1) = {
    .pos = { -271.0f, 0.0f, 53.0f },
    .child = &N(FortressDebrisTransform_dummy7_2),
};

StaticAnimatorNode N(FortressNode_dummy8) = {
    .pos = { 0.0f, -20.0f, 0.0f },
    .modelID = AS_MODEL_ID(MODEL_dummy8),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(FortressDebrisTransform_dummy8_2) = {
    .pos = { 0.0f, -400.0f, 203.0f },
    .child = &N(FortressNode_dummy8),
};

StaticAnimatorNode N(FortressDebrisTransform_dummy8_1) = {
    .pos = { -271.0f, 0.0f, 53.0f },
    .rot = { AS_F(0.0f), AS_F(9.997864f), AS_F(0.0f) },
    .child = &N(FortressDebrisTransform_dummy8_2),
    .sibling = &N(FortressDebrisTransform_dummy7_1),
};

StaticAnimatorNode N(FortressNode_dummy9) = {
    .pos = { 0.0f, -20.0f, 0.0f },
    .modelID = AS_MODEL_ID(MODEL_dummy9),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(FortressDebrisTransform_dummy9_2) = {
    .pos = { 0.0f, -400.0f, 203.0f },
    .child = &N(FortressNode_dummy9),
};

StaticAnimatorNode N(FortressDebrisTransform_dummy9_1) = {
    .pos = { -271.0f, 0.0f, 53.0f },
    .rot = { AS_F(0.0f), AS_F(74.994965f), AS_F(0.0f) },
    .child = &N(FortressDebrisTransform_dummy9_2),
    .sibling = &N(FortressDebrisTransform_dummy8_1),
};

StaticAnimatorNode N(FortressNode_dummy10) = {
    .pos = { 0.0f, -20.0f, 0.0f },
    .modelID = AS_MODEL_ID(MODEL_dummy10),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(FortressDebrisTransform_dummy10_2) = {
    .pos = { 0.0f, -400.0f, 203.0f },
    .rot = { AS_F(0.0f), AS_F(89.99725f), AS_F(0.0f) },
    .child = &N(FortressNode_dummy10),
};

StaticAnimatorNode N(FortressDebrisTransform_dummy10_1) = {
    .pos = { -271.0f, 0.0f, 53.0f },
    .rot = { AS_F(0.0f), AS_F(49.994812f), AS_F(0.0f) },
    .child = &N(FortressDebrisTransform_dummy10_2),
    .sibling = &N(FortressDebrisTransform_dummy9_1),
};

StaticAnimatorNode N(FortressNode_dummy11) = {
    .pos = { 0.0f, -20.0f, 0.0f },
    .modelID = AS_MODEL_ID(MODEL_dummy11),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(FortressDebrisTransform_dummy11_2) = {
    .pos = { 0.0f, -400.0f, 203.0f },
    .child = &N(FortressNode_dummy11),
};

StaticAnimatorNode N(FortressDebrisTransform_dummy11_1) = {
    .pos = { -271.0f, 0.0f, 53.0f },
    .rot = { AS_F(0.0f), AS_F(-19.995728f), AS_F(0.0f) },
    .child = &N(FortressDebrisTransform_dummy11_2),
    .sibling = &N(FortressDebrisTransform_dummy10_1),
};

StaticAnimatorNode N(FortressDebrisGroup_dummy7) = {
    .pos = { -30.0f, 20.0f, -30.0f },
    .child = &N(FortressDebrisTransform_dummy11_1),
    .sibling = &N(FortressDebrisGroup_dummy21),
};

StaticAnimatorNode N(FortressNode_dummy6) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .modelID = AS_MODEL_ID(MODEL_dummy6),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(FortressDebrisTransform_dummy6) = {
    .pos = { -135.0f, -400.0f, -191.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-180.0f) },
    .child = &N(FortressNode_dummy6),
};

StaticAnimatorNode N(FortressNode_dummy5) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .modelID = AS_MODEL_ID(MODEL_dummy5),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(FortressDebrisTransform_dummy5) = {
    .pos = { -150.0f, -400.0f, -191.0f },
    .child = &N(FortressNode_dummy5),
    .sibling = &N(FortressDebrisTransform_dummy6),
};

StaticAnimatorNode N(FortressNode_dummy4) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .modelID = AS_MODEL_ID(MODEL_dummy4),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(FortressDebrisTransform_dummy4) = {
    .pos = { -135.0f, -400.0f, -191.0f },
    .child = &N(FortressNode_dummy4),
    .sibling = &N(FortressDebrisTransform_dummy5),
};

StaticAnimatorNode N(FortressDebrisGroup_dummy4) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .child = &N(FortressDebrisTransform_dummy4),
    .sibling = &N(FortressDebrisGroup_dummy7),
};

StaticAnimatorNode N(FortressDebrisRoot) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .child = &N(FortressDebrisGroup_dummy4),
    .sibling = &N(FortressWallsRoot),
};

StaticAnimatorNode N(FortressNode_top) = {
    .pos = { 276.0f, -401.0f, 194.0f },
    .rot = { AS_F(0.0f), AS_F(-12.695089f), AS_F(0.0f) },
    .modelID = AS_MODEL_ID(MODEL_top),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(FortressTopTransform04) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .child = &N(FortressNode_top),
};

StaticAnimatorNode N(FortressTopTransform03) = {
    .pos = { 8.0f, 26.0f, 104.0f },
    .rot = { AS_F(0.0f), AS_F(-177.84662f), AS_F(0.0f) },
    .child = &N(FortressTopTransform04),
};

StaticAnimatorNode N(FortressTopTransform02) = {
    .pos = { -6.0f, 0.0f, 197.0f },
    .rot = { AS_F(0.0f), AS_F(177.84662f), AS_F(0.0f) },
    .child = &N(FortressTopTransform03),
};

StaticAnimatorNode N(FortressTopTransform01) = {
    .pos = { 3.0f, 0.0f, 87.0f },
    .rot = { AS_F(89.99725f), AS_F(0.0f), AS_F(0.0f) },
    .child = &N(FortressTopTransform02),
};

StaticAnimatorNode N(FortressTopRoot) = {
    .pos = { 300.0f, -250.0f, -150.0f },
    .rot = { AS_F(0.0f), AS_F(12.695089f), AS_F(0.0f) },
    .child = &N(FortressTopTransform01),
    .sibling = &N(FortressDebrisRoot),
};

StaticAnimatorNode N(FortressNode_mado3) = {
    .pos = { 346.0f, -335.0f, -34.0f },
    .rot = { AS_F(0.0f), AS_F(14.996796f), AS_F(0.0f) },
    .modelID = AS_MODEL_ID(MODEL_mado3),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(FortressTransform_mado3) = {
    .pos = { -343.0f, -55.0f, -56.0f },
    .rot = { AS_F(0.0f), AS_F(-14.996796f), AS_F(-34.998016f) },
    .child = &N(FortressNode_mado3),
};

StaticAnimatorNode N(FortressNode_mado1) = {
    .pos = { 176.0f, -206.0f, -342.0f },
    .rot = { AS_F(0.0f), AS_F(74.994965f), AS_F(0.0f) },
    .modelID = AS_MODEL_ID(MODEL_mado1),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(FortressTransform_mado1) = {
    .pos = { -376.0f, -106.0f, -82.0f },
    .rot = { AS_F(29.999084f), AS_F(-74.994965f), AS_F(0.0f) },
    .child = &N(FortressNode_mado1),
    .sibling = &N(FortressTransform_mado3),
};

StaticAnimatorNode N(FortressNode_mado2) = {
    .pos = { 122.0f, -212.0f, 235.0f },
    .rot = { AS_F(0.0f), AS_F(-44.99588f), AS_F(0.0f) },
    .modelID = AS_MODEL_ID(MODEL_mado2),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(FortressTransform_mado2) = {
    .pos = { -252.0f, -102.0f, -80.0f },
    .rot = { AS_F(0.0f), AS_F(44.99588f), AS_F(89.99725f) },
    .child = &N(FortressNode_mado2),
    .sibling = &N(FortressTransform_mado1),
};

StaticAnimatorNode N(FortressWindowsRoot) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .child = &N(FortressTransform_mado2),
    .sibling = &N(FortressTopRoot),
};

StaticAnimatorNode N(FortressRoot) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .child = &N(FortressWindowsRoot),
};

StaticAnimatorNode* N(AnimSkeleton_Fortress)[] = {
    &N(FortressRoot),
        &N(FortressWindowsRoot),
            &N(FortressTransform_mado2),
                &N(FortressNode_mado2),
            &N(FortressTransform_mado1),
                &N(FortressNode_mado1),
            &N(FortressTransform_mado3),
                &N(FortressNode_mado3),
        &N(FortressTopRoot),
            &N(FortressTopTransform01),
                &N(FortressTopTransform02),
                    &N(FortressTopTransform03),
                        &N(FortressTopTransform04),
                            &N(FortressNode_top),
        &N(FortressDebrisRoot),
            &N(FortressDebrisGroup_dummy4),
                &N(FortressDebrisTransform_dummy4),
                    &N(FortressNode_dummy4),
                &N(FortressDebrisTransform_dummy5),
                    &N(FortressNode_dummy5),
                &N(FortressDebrisTransform_dummy6),
                    &N(FortressNode_dummy6),
            &N(FortressDebrisGroup_dummy7),
                &N(FortressDebrisTransform_dummy11_1),
                    &N(FortressDebrisTransform_dummy11_2),
                        &N(FortressNode_dummy11),
                &N(FortressDebrisTransform_dummy10_1),
                    &N(FortressDebrisTransform_dummy10_2),
                        &N(FortressNode_dummy10),
                &N(FortressDebrisTransform_dummy9_1),
                    &N(FortressDebrisTransform_dummy9_2),
                        &N(FortressNode_dummy9),
                &N(FortressDebrisTransform_dummy8_1),
                    &N(FortressDebrisTransform_dummy8_2),
                        &N(FortressNode_dummy8),
                &N(FortressDebrisTransform_dummy7_1),
                    &N(FortressDebrisTransform_dummy7_2),
                        &N(FortressNode_dummy7),
            &N(FortressDebrisGroup_dummy21),
                &N(FortressDebrisTransform_dummy23_1),
                    &N(FortressDebrisTransform_dummy23_2),
                        &N(FortressNode_dummy23),
                &N(FortressDebrisTransform_dummy22_1),
                    &N(FortressDebrisTransform_dummy22_2),
                        &N(FortressNode_dummy22),
                &N(FortressDebrisTransform_dummy21_1),
                    &N(FortressDebrisTransform_dummy21_2),
                        &N(FortressNode_dummy21),
            &N(FortressDebrisGroup_dummy27),
                &N(FortressDebrisTransform_dummy29_1),
                    &N(FortressDebrisTransform_dummy29_2),
                        &N(FortressNode_dummy29),
                &N(FortressDebrisTransform_dummy28_1),
                    &N(FortressDebrisTransform_dummy28_2),
                        &N(FortressNode_dummy28),
                &N(FortressDebrisTransform_dummy27_1),
                    &N(FortressDebrisTransform_dummy27_2),
                        &N(FortressNode_dummy27),
        &N(FortressWallsRoot),
            &N(FortressWallsTransform),
                &N(FortressWallBottomRoot),
                    &N(FortressWallTransform_tc3),
                        &N(FortressNode_tc3),
                    &N(FortressWallTransform_tb3),
                        &N(FortressNode_tb3),
                    &N(FortressWallTransform_ta3),
                        &N(FortressNode_ta3),
                    &N(FortressWallTransform_tf3),
                        &N(FortressNode_tf3),
                    &N(FortressWallTransform_td3),
                        &N(FortressNode_td3),
                    &N(FortressWallTransform_te3),
                        &N(FortressNode_te3),
                &N(FortressWallMiddleRoot),
                    &N(FortressWallTransform_tc2),
                        &N(FortressNode_tc2),
                    &N(FortressWallTransform_tb2),
                        &N(FortressNode_tb2),
                    &N(FortressWallTransform_ta2),
                        &N(FortressNode_ta2),
                    &N(FortressWallTransform_tf2),
                        &N(FortressNode_tf2),
                    &N(FortressWallTransform_te2),
                        &N(FortressNode_te2),
                    &N(FortressWallTransform_td2),
                        &N(FortressNode_td2),
                &N(FortressWallTopRoot),
                    &N(FortressWallTransform_tc1_1),
                        &N(FortressWallTransform_tc1_2),
                            &N(FortressNode_tc1),
                    &N(FortressWallTransform_tb1_1),
                        &N(FortressWallTransform_tb1_2),
                            &N(FortressNode_tb1),
                    &N(FortressWallTransform_ta1_1),
                        &N(FortressWallTransform_ta1_2),
                            &N(FortressNode_ta1),
                    &N(FortressWallTransform_tf1_1),
                        &N(FortressWallTransform_tf1_2),
                            &N(FortressNode_tf1),
                    &N(FortressWallTransform_te1_1),
                        &N(FortressWallTransform_te1_2),
                            &N(FortressNode_te1),
                    &N(FortressWallTransform_td1_1),
                        &N(FortressWallTransform_td1_2),
                            &N(FortressNode_td1),
    nullptr
};
