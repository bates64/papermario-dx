#include "break_bridges.h"

StaticAnimatorNode UnusedAnimMarker = {
    .pos = { 225.0f, 255.0f, 0.0f },
};

StaticAnimatorNode BridgeFragmentFloor3 = {
    .displayList = Gfx_DrawMesh_BridgeFragmentFloor3,
    .pos = { 0.0f, -500.0f, 0.0f },
};

StaticAnimatorNode BridgeFragmentFloor2 = {
    .displayList = Gfx_DrawMesh_BridgeFragmentFloor2,
    .pos = { 0.0f, -500.0f, 0.0f },
    .sibling = &BridgeFragmentFloor3,
};

StaticAnimatorNode BridgeFragmentFloor1 = {
    .displayList = Gfx_DrawMesh_BridgeFragmentFloor1,
    .pos = { 0.0f, -500.0f, 0.0f },
    .sibling = &BridgeFragmentFloor2,
};

StaticAnimatorNode BridgeFragmentWood3 = {
    .displayList = Gfx_DrawMesh_BridgeFragmentWood3,
    .pos = { 0.0f, -500.0f, 0.0f },
    .sibling = &BridgeFragmentFloor1,
};

StaticAnimatorNode BridgeFragmentWood2 = {
    .displayList = Gfx_DrawMesh_BridgeFragmentWood2,
    .pos = { 0.0f, -500.0f, 0.0f },
    .sibling = &BridgeFragmentWood3,
};

StaticAnimatorNode BridgeFragmentWood1 = {
    .displayList = Gfx_DrawMesh_BridgeFragmentWood1,
    .pos = { 0.0f, -500.0f, 0.0f },
    .sibling = &BridgeFragmentWood2,
};

StaticAnimatorNode WoodAndFloorTileDebris = {
    .child = &BridgeFragmentWood1,
};

StaticAnimatorNode WoodDebris3 = {
    .displayList = Gfx_DrawMesh_WoodDebris3,
    .pos = { 0.0f, -500.0f, 0.0f },
};

StaticAnimatorNode WoodDebris2 = {
    .displayList = Gfx_DrawMesh_WoodDebris2,
    .pos = { 0.0f, -500.0f, 0.0f },
    .sibling = &WoodDebris3,
};

StaticAnimatorNode WoodDebris1 = {
    .displayList = Gfx_DrawMesh_WoodDebris1,
    .pos = { 0.0f, -500.0f, 0.0f },
    .sibling = &WoodDebris2,
};

StaticAnimatorNode WoodDebris = {
    .sibling = &WoodAndFloorTileDebris,
    .child = &WoodDebris1,
};

StaticAnimatorNode BridgeSupportArch3 = {
    .displayList = Gfx_DrawMesh_BridgeSupportArch3,
};

StaticAnimatorNode BridgeSupportArch2 = {
    .displayList = Gfx_DrawMesh_BridgeSupportArch2,
    .sibling = &BridgeSupportArch3,
};

StaticAnimatorNode BridgeSupportArch1 = {
    .displayList = Gfx_DrawMesh_BridgeSupportArch1,
    .sibling = &BridgeSupportArch2,
};

StaticAnimatorNode UpperLeftFixedRailing = {
    .displayList = Gfx_DrawMesh_UpperLeftFixedRailing,
    .sibling = &BridgeSupportArch1,
};

StaticAnimatorNode UpperRightFixedSmoothFloor = {
    .displayList = Gfx_DrawMesh_UpperRightFixedSmoothFloor,
    .sibling = &UpperLeftFixedRailing,
};

StaticAnimatorNode UpperRightFixedBrokenRailing = {
    .displayList = Gfx_DrawQuad_UpperRightFixedBrokenRailing,
    .sibling = &UpperRightFixedSmoothFloor,
};

StaticAnimatorNode UpperLeftFixedWood = {
    .displayList = Gfx_DrawMesh_UpperLeftFixedWood,
    .sibling = &UpperRightFixedBrokenRailing,
};

StaticAnimatorNode UpperRightFixedWood = {
    .displayList = Gfx_DrawMesh_UpperRightFixedWood,
    .sibling = &UpperLeftFixedWood,
};

StaticAnimatorNode UpperLeftFixedTrim = {
    .displayList = Gfx_DrawMesh_UpperLeftFixedTrim,
    .sibling = &UpperRightFixedWood,
};

StaticAnimatorNode UpperRightFixedTrim = {
    .displayList = Gfx_DrawMesh_UpperRightFixedTrim,
    .sibling = &UpperLeftFixedTrim,
};

StaticAnimatorNode UpperLeftFixedDamagedRailing = {
    .displayList = Gfx_DrawMesh_UpperLeftFixedDamagedRailing,
    .sibling = &UpperRightFixedTrim,
};

StaticAnimatorNode UpperRightFixedDamagedRailing = {
    .displayList = Gfx_DrawMesh_UpperRightFixedDamagedRailing,
    .sibling = &UpperLeftFixedDamagedRailing,
};

StaticAnimatorNode UpperLeftFixedFloor = {
    .displayList = Gfx_DrawMesh_UpperLeftFixedFloor,
    .sibling = &UpperRightFixedDamagedRailing,
};

StaticAnimatorNode UpperRightFixedFloor = {
    .displayList = Gfx_DrawMesh_UpperRightFixedFloor,
    .sibling = &UpperLeftFixedFloor,
};

StaticAnimatorNode BridgeFixedStructures = {
    .sibling = &WoodDebris,
    .child = &UpperRightFixedFloor,
};

StaticAnimatorNode UpperRailingDebris11 = {
    .displayList = Gfx_DrawQuad_UpperRailingDebris11,
    .rot = { AS_F(0.000000f), AS_F(44.995880f), AS_F(-180.000000f) },
    .pos = { -315.0f, 2.0f, -139.0f },
};

StaticAnimatorNode UpperRailingDebris10 = {
    .displayList = Gfx_DrawQuad_UpperRailingDebris10,
    .rot = { AS_F(-180.000000f), AS_F(59.998169f), AS_F(-180.000000f) },
    .pos = { -455.0f, 421.0f, -20.0f },
    .sibling = &UpperRailingDebris11,
};

StaticAnimatorNode UpperRailingDebris09 = {
    .displayList = Gfx_DrawQuad_UpperRailingDebris09,
    .rot = { AS_F(-180.000000f), AS_F(-44.995880f), AS_F(0.000000f) },
    .pos = { -385.0f, 2.0f, 169.0f },
    .sibling = &UpperRailingDebris10,
};

StaticAnimatorNode UpperRailingDebris08 = {
    .displayList = Gfx_DrawQuad_UpperRailingDebris08,
    .rot = { AS_F(0.000000f), AS_F(59.998169f), AS_F(-180.000000f) },
    .pos = { -105.0f, 2.0f, -210.0f },
    .sibling = &UpperRailingDebris09,
};

StaticAnimatorNode UpperRailingDebris07 = {
    .displayList = Gfx_DrawQuad_UpperRailingDebris07,
    .rot = { AS_F(0.000000f), AS_F(-29.999084f), AS_F(-180.000000f) },
    .pos = { -5.0f, 2.0f, -180.0f },
    .sibling = &UpperRailingDebris08,
};

StaticAnimatorNode UpperRailingDebris06 = {
    .displayList = Gfx_DrawQuad_UpperRailingDebris06,
    .rot = { AS_F(-180.000000f), AS_F(14.996796f), AS_F(0.000000f) },
    .pos = { -195.0f, 2.0f, 259.0f },
    .sibling = &UpperRailingDebris07,
};

StaticAnimatorNode UpperRailingDebris05 = {
    .displayList = Gfx_DrawQuad_UpperRailingDebris05,
    .rot = { AS_F(-180.000000f), AS_F(-59.998169f), AS_F(-180.000000f) },
    .pos = { -65.0f, 2.0f, 189.0f },
    .sibling = &UpperRailingDebris06,
};

StaticAnimatorNode UpperRailingDebris04 = {
    .displayList = Gfx_DrawQuad_UpperRailingDebris04,
    .rot = { AS_F(-180.000000f), AS_F(0.000000f), AS_F(0.000000f) },
    .pos = { 275.0f, 2.0f, -129.0f },
    .sibling = &UpperRailingDebris05,
};

StaticAnimatorNode UpperRailingDebris03 = {
    .displayList = Gfx_DrawQuad_UpperRailingDebris03,
    .rot = { AS_F(0.000000f), AS_F(-14.996796f), AS_F(-180.000000f) },
    .pos = { 195.0f, 421.0f, -40.0f },
    .sibling = &UpperRailingDebris04,
};

StaticAnimatorNode UpperRailingDebris02 = {
    .displayList = Gfx_DrawQuad_UpperRailingDebris02,
    .rot = { AS_F(-180.000000f), AS_F(29.999084f), AS_F(-180.000000f) },
    .pos = { 85.0f, 2.0f, 329.0f },
    .sibling = &UpperRailingDebris03,
};

StaticAnimatorNode UpperRailingDebris01 = {
    .displayList = Gfx_DrawQuad_UpperRailingDebris01,
    .rot = { AS_F(-180.000000f), AS_F(29.999084f), AS_F(0.000000f) },
    .pos = { 215.0f, 421.0f, 29.0f },
    .sibling = &UpperRailingDebris02,
};

StaticAnimatorNode UpperBridgeRailingDebris = {
    .sibling = &BridgeFixedStructures,
    .child = &UpperRailingDebris01,
};

StaticAnimatorNode UpperTrimDebris9 = {
    .displayList = Gfx_DrawQuad_UpperTrimDebris9,
    .rot = { AS_F(-180.000000f), AS_F(0.000000f), AS_F(0.000000f) },
    .pos = { 8.0f, -23.0f, -49.0f },
};

StaticAnimatorNode UpperTrimDebris8 = {
    .displayList = Gfx_DrawQuad_UpperTrimDebris8,
    .rot = { AS_F(0.000000f), AS_F(-9.997864f), AS_F(-180.000000f) },
    .pos = { 73.0f, -23.0f, 20.0f },
    .sibling = &UpperTrimDebris9,
};

StaticAnimatorNode UpperTrimDebris7 = {
    .displayList = Gfx_DrawQuad_UpperTrimDebris7,
    .rot = { AS_F(-180.000000f), AS_F(0.000000f), AS_F(0.000000f) },
    .pos = { -1.0f, -23.0f, 49.0f },
    .sibling = &UpperTrimDebris8,
};

StaticAnimatorNode UpperTrimDebris6 = {
    .displayList = Gfx_DrawQuad_UpperTrimDebris6,
    .rot = { AS_F(-180.000000f), AS_F(0.000000f), AS_F(-180.000000f) },
    .pos = { 18.0f, -23.0f, 0.0f },
    .sibling = &UpperTrimDebris7,
};

StaticAnimatorNode UpperTrimDebrisCluster = {
    .rot = { AS_F(0.000000f), AS_F(44.995880f), AS_F(0.000000f) },
    .pos = { 61.0f, 47.0f, -31.0f },
    .child = &UpperTrimDebris6,
};

StaticAnimatorNode UpperTrimDebris5 = {
    .displayList = Gfx_DrawQuad_UpperTrimDebris5,
    .rot = { AS_F(-180.000000f), AS_F(14.996796f), AS_F(0.000000f) },
    .pos = { -415.0f, 21.0f, 20.0f },
    .sibling = &UpperTrimDebrisCluster,
};

StaticAnimatorNode UpperTrimDebris4 = {
    .displayList = Gfx_DrawQuad_UpperTrimDebris4,
    .rot = { AS_F(-180.000000f), AS_F(-9.997864f), AS_F(-180.000000f) },
    .pos = { 195.0f, 211.0f, -39.0f },
    .sibling = &UpperTrimDebris5,
};

StaticAnimatorNode UpperTrimDebris3 = {
    .displayList = Gfx_DrawQuad_UpperTrimDebris3,
    .rot = { AS_F(-180.000000f), AS_F(-19.995727f), AS_F(-180.000000f) },
    .pos = { 95.0f, 210.0f, -30.0f },
    .sibling = &UpperTrimDebris4,
};

StaticAnimatorNode UpperTrimDebris2 = {
    .displayList = Gfx_DrawQuad_UpperTrimDebris2,
    .rot = { AS_F(-180.000000f), AS_F(29.999084f), AS_F(-180.000000f) },
    .pos = { 115.0f, 211.0f, 39.0f },
    .sibling = &UpperTrimDebris3,
};

StaticAnimatorNode UpperTrimDebris1 = {
    .displayList = Gfx_DrawQuad_UpperTrimDebris1,
    .rot = { AS_F(-180.000000f), AS_F(14.996796f), AS_F(-180.000000f) },
    .pos = { 215.0f, 211.0f, 39.0f },
    .sibling = &UpperTrimDebris2,
};

StaticAnimatorNode UpperBridgeWoodPanelTrimDebris = {
    .sibling = &UpperBridgeRailingDebris,
    .child = &UpperTrimDebris1,
};

StaticAnimatorNode LowerTrimDebris3 = {
    .displayList = Gfx_DrawQuad_LowerTrimDebris3,
    .rot = { AS_F(0.000000f), AS_F(14.996796f), AS_F(0.000000f) },
    .pos = { -375.0f, 2.0f, 0.0f },
};

StaticAnimatorNode LowerTrimDebris2 = {
    .displayList = Gfx_DrawQuad_LowerTrimDebris2,
    .rot = { AS_F(0.000000f), AS_F(-29.999084f), AS_F(-180.000000f) },
    .pos = { -175.0f, 2.0f, -49.0f },
    .sibling = &LowerTrimDebris3,
};

StaticAnimatorNode LowerTrimDebris1 = {
    .displayList = Gfx_DrawQuad_LowerTrimDebris1,
    .rot = { AS_F(-180.000000f), AS_F(0.000000f), AS_F(-180.000000f) },
    .pos = { 75.0f, 2.0f, -49.0f },
    .sibling = &LowerTrimDebris2,
};

StaticAnimatorNode LowerBridgeWoodPanelTrimDebris = {
    .sibling = &UpperBridgeWoodPanelTrimDebris,
    .child = &LowerTrimDebris1,
};

StaticAnimatorNode BridgeStructuresAndDebris = {
    .sibling = &UnusedAnimMarker,
    .child = &LowerBridgeWoodPanelTrimDebris,
};

StaticAnimatorNode LowerLeftCollapseRailing = {
    .displayList = Gfx_DrawMesh_LowerLeftCollapseRailing,
};

StaticAnimatorNode LowerLeftCollapseTrim = {
    .displayList = Gfx_DrawMesh_LowerLeftCollapseTrim,
    .sibling = &LowerLeftCollapseRailing,
};

StaticAnimatorNode LowerLeftCollapseDamagedRailing = {
    .displayList = Gfx_DrawMesh_LowerLeftCollapseDamagedRailing,
    .sibling = &LowerLeftCollapseTrim,
};

StaticAnimatorNode LowerLeftCollapseFloor = {
    .displayList = Gfx_DrawMesh_LowerLeftCollapseFloor,
    .sibling = &LowerLeftCollapseDamagedRailing,
};

StaticAnimatorNode LowerLeftCollapseSmoothFloor = {
    .displayList = Gfx_DrawMesh_LowerLeftCollapseSmoothFloor,
    .sibling = &LowerLeftCollapseFloor,
};

StaticAnimatorNode LowerLeftCollapseWood3 = {
    .displayList = Gfx_DrawMesh_LowerLeftCollapseWood3,
    .sibling = &LowerLeftCollapseSmoothFloor,
};

StaticAnimatorNode LowerLeftCollapseWood2 = {
    .displayList = Gfx_DrawMesh_LowerLeftCollapseWood2,
    .sibling = &LowerLeftCollapseWood3,
};

StaticAnimatorNode LowerLeftCollapseWood1 = {
    .displayList = Gfx_DrawMesh_LowerLeftCollapseWood1,
    .sibling = &LowerLeftCollapseWood2,
};

StaticAnimatorNode LowerBridgeLeftCollapse = {
    .rot = { AS_F(0.000000f), AS_F(0.000000f), AS_F(-30.065004f) },
    .pos = { -360.0f, 85.0f, -1.0f },
    .child = &LowerLeftCollapseWood1,
};

StaticAnimatorNode UpperRearRailingWood = {
    .displayList = Gfx_DrawMesh_UpperRearRailingWood,
};

StaticAnimatorNode UpperRearBrokenRailing = {
    .displayList = Gfx_DrawMesh_UpperRearBrokenRailing,
    .sibling = &UpperRearRailingWood,
};

StaticAnimatorNode UpperBridgeRearRailing = {
    .rot = { AS_F(-29.999084f), AS_F(65.431074f), AS_F(-22.247993f) },
    .pos = { 35.0f, 316.0f, 36.0f },
    .sibling = &LowerBridgeLeftCollapse,
    .child = &UpperRearBrokenRailing,
};

StaticAnimatorNode UpperRightCollapseSmoothFloor = {
    .displayList = Gfx_DrawMesh_UpperRightCollapseSmoothFloor,
};

StaticAnimatorNode UpperRightCollapseWood = {
    .displayList = Gfx_DrawMesh_UpperRightCollapseWood,
    .sibling = &UpperRightCollapseSmoothFloor,
};

StaticAnimatorNode UpperRightCollapseBrokenRailing = {
    .displayList = Gfx_DrawMesh_UpperRightCollapseBrokenRailing,
    .sibling = &UpperRightCollapseWood,
};

StaticAnimatorNode UpperRightCollapseFloor = {
    .displayList = Gfx_DrawMesh_UpperRightCollapseFloor,
    .sibling = &UpperRightCollapseBrokenRailing,
};

StaticAnimatorNode UpperRightCollapseDamagedRailing = {
    .displayList = Gfx_DrawMesh_UpperRightCollapseDamagedRailing,
    .sibling = &UpperRightCollapseFloor,
};

StaticAnimatorNode UpperRightCollapseTrim = {
    .displayList = Gfx_DrawMesh_UpperRightCollapseTrim,
    .sibling = &UpperRightCollapseDamagedRailing,
};

StaticAnimatorNode UpperBridgeRightCollapse = {
    .rot = { AS_F(-4.998932f), AS_F(-2.598346f), AS_F(0.000000f) },
    .pos = { 133.0f, 271.0f, 30.0f },
    .sibling = &UpperBridgeRearRailing,
    .child = &UpperRightCollapseTrim,
};

StaticAnimatorNode LowerRailingSplitRightBrokenRailing = {
    .displayList = Gfx_DrawMesh_LowerRailingSplitRightBrokenRailing,
    .pos = { 252.0f, 0.0f, 0.0f },
};

StaticAnimatorNode LowerRailingSplitRightWood2 = {
    .displayList = Gfx_DrawMesh_LowerRailingSplitRightWood2,
    .pos = { 252.0f, 0.0f, 0.0f },
    .sibling = &LowerRailingSplitRightBrokenRailing,
};

StaticAnimatorNode LowerRailingSplitRightWood1 = {
    .displayList = Gfx_DrawMesh_LowerRailingSplitRightWood1,
    .pos = { 252.0f, 0.0f, 0.0f },
    .sibling = &LowerRailingSplitRightWood2,
};

StaticAnimatorNode LowerRailingSplitRightParts = {
    .sibling = &LowerRailingSplitRightWood1,
};

StaticAnimatorNode LowerRailingSplitRightHinge = {
    .rot = { AS_F(0.000000f), AS_F(0.000000f), AS_F(-13.997009f) },
    .pos = { -252.0f, 0.0f, 0.0f },
    .child = &LowerRailingSplitRightParts,
};

StaticAnimatorNode LowerRailingSplitRight = {
    .rot = { AS_F(0.000000f), AS_F(0.000000f), AS_F(13.997009f) },
    .pos = { 253.0f, 285.0f, 86.0f },
    .child = &LowerRailingSplitRightHinge,
};

StaticAnimatorNode LowerRightBrokenRailing = {
    .displayList = Gfx_DrawMesh_LowerRightBrokenRailing,
    .sibling = &LowerRailingSplitRight,
};

StaticAnimatorNode LowerRightSmoothFloor2 = {
    .displayList = Gfx_DrawMesh_LowerRightSmoothFloor2,
    .pos = { 0.0f, -500.0f, 0.0f },
    .sibling = &LowerRightBrokenRailing,
};

StaticAnimatorNode LowerRightSmoothFloor1 = {
    .displayList = Gfx_DrawMesh_LowerRightSmoothFloor1,
    .sibling = &LowerRightSmoothFloor2,
};

StaticAnimatorNode LowerRightTrim = {
    .displayList = Gfx_DrawMesh_LowerRightTrim,
    .sibling = &LowerRightSmoothFloor1,
};

StaticAnimatorNode LowerRightDamagedRailing = {
    .displayList = Gfx_DrawMesh_LowerRightDamagedRailing,
    .sibling = &LowerRightTrim,
};

StaticAnimatorNode LowerRightFloor = {
    .displayList = Gfx_DrawMesh_LowerRightFloor,
    .sibling = &LowerRightDamagedRailing,
};

StaticAnimatorNode LowerRightWood2 = {
    .displayList = Gfx_DrawMesh_LowerRightWood2,
    .sibling = &LowerRightFloor,
};

StaticAnimatorNode LowerRightWood1 = {
    .displayList = Gfx_DrawMesh_LowerRightWood1,
    .sibling = &LowerRightWood2,
};

StaticAnimatorNode LowerBridgeRightFixed = {
    .sibling = &UpperBridgeRightCollapse,
    .child = &LowerRightWood1,
};

StaticAnimatorNode LowerRailingSplitLeftWood2 = {
    .displayList = Gfx_DrawMesh_LowerRailingSplitLeftWood2,
};

StaticAnimatorNode LowerRailingSplitLeftWood1 = {
    .displayList = Gfx_DrawMesh_LowerRailingSplitLeftWood1,
    .sibling = &LowerRailingSplitLeftWood2,
};

StaticAnimatorNode LowerRailingSplitLeftBrokenRailing = {
    .displayList = Gfx_DrawMesh_LowerRailingSplitLeftBrokenRailing,
    .sibling = &LowerRailingSplitLeftWood1,
};

StaticAnimatorNode LowerRailingSplitLeft = {
    .pos = { 105.0f, -8.0f, 87.0f },
    .child = &LowerRailingSplitLeftBrokenRailing,
};

StaticAnimatorNode LowerCenterBrokenRailing = {
    .displayList = Gfx_DrawMesh_LowerCenterBrokenRailing,
    .sibling = &LowerRailingSplitLeft,
};

StaticAnimatorNode LowerCenterSmoothFloor = {
    .displayList = Gfx_DrawMesh_LowerCenterSmoothFloor,
    .sibling = &LowerCenterBrokenRailing,
};

StaticAnimatorNode LowerCenterTrim = {
    .displayList = Gfx_DrawMesh_LowerCenterTrim,
    .sibling = &LowerCenterSmoothFloor,
};

StaticAnimatorNode LowerCenterDamagedRailing = {
    .displayList = Gfx_DrawMesh_LowerCenterDamagedRailing,
    .sibling = &LowerCenterTrim,
};

StaticAnimatorNode LowerCenterFloor = {
    .displayList = Gfx_DrawMesh_LowerCenterFloor,
    .sibling = &LowerCenterDamagedRailing,
};

StaticAnimatorNode LowerCenterWood2 = {
    .displayList = Gfx_DrawMesh_LowerCenterWood2,
    .sibling = &LowerCenterFloor,
};

StaticAnimatorNode LowerCenterWood1 = {
    .displayList = Gfx_DrawMesh_LowerCenterWood1,
    .sibling = &LowerCenterWood2,
};

StaticAnimatorNode LowerBridgeCenterCollapse = {
    .rot = { AS_F(0.000000f), AS_F(44.995880f), AS_F(0.000000f) },
    .pos = { 61.0f, 47.0f, -31.0f },
    .sibling = &LowerBridgeRightFixed,
    .child = &LowerCenterWood1,
};

StaticAnimatorNode LowerLeftAttachWood4 = {
    .displayList = Gfx_DrawMesh_LowerLeftAttachWood4,
    .rot = { AS_F(4.998932f), AS_F(0.000000f), AS_F(34.998016f) },
    .pos = { -465.0f, 210.0f, -90.0f },
};

StaticAnimatorNode LowerLeftAttachWood3 = {
    .displayList = Gfx_DrawMesh_LowerLeftAttachWood3,
    .rot = { AS_F(0.000000f), AS_F(34.998016f), AS_F(29.999084f) },
    .pos = { -465.0f, 210.0f, 90.0f },
    .sibling = &LowerLeftAttachWood4,
};

StaticAnimatorNode LowerLeftAttachRailing = {
    .displayList = Gfx_DrawMesh_LowerLeftAttachRailing,
    .sibling = &LowerLeftAttachWood3,
};

StaticAnimatorNode LowerLeftAttachTrim = {
    .displayList = Gfx_DrawMesh_LowerLeftAttachTrim,
    .sibling = &LowerLeftAttachRailing,
};

StaticAnimatorNode LowerLeftAttachDamagedRailing = {
    .displayList = Gfx_DrawMesh_LowerLeftAttachDamagedRailing,
    .sibling = &LowerLeftAttachTrim,
};

StaticAnimatorNode LowerLeftAttachFloor = {
    .displayList = Gfx_DrawMesh_LowerLeftAttachFloor,
    .sibling = &LowerLeftAttachDamagedRailing,
};

StaticAnimatorNode LowerLeftAttachSmoothFloor = {
    .displayList = Gfx_DrawMesh_LowerLeftAttachSmoothFloor,
    .pos = { 0.0f, -500.0f, 0.0f },
    .sibling = &LowerLeftAttachFloor,
};

StaticAnimatorNode LowerLeftAttachWood2 = {
    .displayList = Gfx_DrawMesh_LowerLeftAttachWood2,
    .sibling = &LowerLeftAttachSmoothFloor,
};

StaticAnimatorNode LowerLeftAttachWood1 = {
    .displayList = Gfx_DrawMesh_LowerLeftAttachWood1,
    .sibling = &LowerLeftAttachWood2,
};

StaticAnimatorNode LowerBridgeLeftAttachment = {
    .pos = { 0.0f, -188.0f, 0.0f },
    .sibling = &LowerBridgeCenterCollapse,
    .child = &LowerLeftAttachWood1,
};

StaticAnimatorNode UpperLeftWood = {
    .displayList = Gfx_DrawMesh_UpperLeftWood,
    .pos = { -179.0f, 34.0f, 98.0f },
};

StaticAnimatorNode UpperLeftSmoothFloor = {
    .displayList = Gfx_DrawMesh_UpperLeftSmoothFloor,
    .pos = { -179.0f, 34.0f, 98.0f },
    .sibling = &UpperLeftWood,
};

StaticAnimatorNode UpperLeftTrim = {
    .displayList = Gfx_DrawMesh_UpperLeftTrim,
    .pos = { -179.0f, 34.0f, 98.0f },
    .sibling = &UpperLeftSmoothFloor,
};

StaticAnimatorNode UpperLeftDamagedRailing = {
    .displayList = Gfx_DrawMesh_UpperLeftDamagedRailing,
    .pos = { -179.0f, 34.0f, 98.0f },
    .sibling = &UpperLeftTrim,
};

StaticAnimatorNode UpperLeftFloor = {
    .displayList = Gfx_DrawMesh_UpperLeftFloor,
    .pos = { -179.0f, 34.0f, 98.0f },
    .sibling = &UpperLeftDamagedRailing,
};

StaticAnimatorNode UpperLeftRailing = {
    .displayList = Gfx_DrawMesh_UpperLeftRailing,
    .pos = { -179.0f, 34.0f, 98.0f },
    .sibling = &UpperLeftFloor,
};

StaticAnimatorNode UpperBridgeLeft = {
    .rot = { AS_F(-6.998505f), AS_F(-81.499069f), AS_F(0.000000f) },
    .pos = { 179.0f, -34.0f, -98.0f },
    .child = &UpperLeftRailing,
};

StaticAnimatorNode UpperBridgeLeftCollapse = {
    .rot = { AS_F(0.000000f), AS_F(-8.404798f), AS_F(-83.828242f) },
    .pos = { -245.0f, 196.0f, 21.0f },
    .sibling = &LowerBridgeLeftAttachment,
    .child = &UpperBridgeLeft,
};

StaticAnimatorNode BridgeSections = {
    .sibling = &BridgeStructuresAndDebris,
    .child = &UpperBridgeLeftCollapse,
};

StaticAnimatorNode SmashBridgesRoot = {
    .child = &BridgeSections,
};

StaticAnimatorNode* SmashBridgesSkeleton[] = {
    &SmashBridgesRoot,
        &BridgeSections,
            &UpperBridgeLeftCollapse,
                &UpperBridgeLeft,
                    &UpperLeftRailing,
                    &UpperLeftFloor,
                    &UpperLeftDamagedRailing,
                    &UpperLeftTrim,
                    &UpperLeftSmoothFloor,
                    &UpperLeftWood,
            &LowerBridgeLeftAttachment,
                &LowerLeftAttachWood1,
                &LowerLeftAttachWood2,
                &LowerLeftAttachSmoothFloor,
                &LowerLeftAttachFloor,
                &LowerLeftAttachDamagedRailing,
                &LowerLeftAttachTrim,
                &LowerLeftAttachRailing,
                &LowerLeftAttachWood3,
                &LowerLeftAttachWood4,
            &LowerBridgeCenterCollapse,
                &LowerCenterWood1,
                &LowerCenterWood2,
                &LowerCenterFloor,
                &LowerCenterDamagedRailing,
                &LowerCenterTrim,
                &LowerCenterSmoothFloor,
                &LowerCenterBrokenRailing,
                &LowerRailingSplitLeft,
                    &LowerRailingSplitLeftBrokenRailing,
                    &LowerRailingSplitLeftWood1,
                    &LowerRailingSplitLeftWood2,
            &LowerBridgeRightFixed,
                &LowerRightWood1,
                &LowerRightWood2,
                &LowerRightFloor,
                &LowerRightDamagedRailing,
                &LowerRightTrim,
                &LowerRightSmoothFloor1,
                &LowerRightSmoothFloor2,
                &LowerRightBrokenRailing,
                &LowerRailingSplitRight,
                    &LowerRailingSplitRightHinge,
                        &LowerRailingSplitRightParts,
                        &LowerRailingSplitRightWood1,
                        &LowerRailingSplitRightWood2,
                        &LowerRailingSplitRightBrokenRailing,
            &UpperBridgeRightCollapse,
                &UpperRightCollapseTrim,
                &UpperRightCollapseDamagedRailing,
                &UpperRightCollapseFloor,
                &UpperRightCollapseBrokenRailing,
                &UpperRightCollapseWood,
                &UpperRightCollapseSmoothFloor,
            &UpperBridgeRearRailing,
                &UpperRearBrokenRailing,
                &UpperRearRailingWood,
            &LowerBridgeLeftCollapse,
                &LowerLeftCollapseWood1,
                &LowerLeftCollapseWood2,
                &LowerLeftCollapseWood3,
                &LowerLeftCollapseSmoothFloor,
                &LowerLeftCollapseFloor,
                &LowerLeftCollapseDamagedRailing,
                &LowerLeftCollapseTrim,
                &LowerLeftCollapseRailing,
        &BridgeStructuresAndDebris,
            &LowerBridgeWoodPanelTrimDebris,
                &LowerTrimDebris1,
                &LowerTrimDebris2,
                &LowerTrimDebris3,
            &UpperBridgeWoodPanelTrimDebris,
                &UpperTrimDebris1,
                &UpperTrimDebris2,
                &UpperTrimDebris3,
                &UpperTrimDebris4,
                &UpperTrimDebris5,
                &UpperTrimDebrisCluster,
                    &UpperTrimDebris6,
                    &UpperTrimDebris7,
                    &UpperTrimDebris8,
                    &UpperTrimDebris9,
            &UpperBridgeRailingDebris,
                &UpperRailingDebris01,
                &UpperRailingDebris02,
                &UpperRailingDebris03,
                &UpperRailingDebris04,
                &UpperRailingDebris05,
                &UpperRailingDebris06,
                &UpperRailingDebris07,
                &UpperRailingDebris08,
                &UpperRailingDebris09,
                &UpperRailingDebris10,
                &UpperRailingDebris11,
            &BridgeFixedStructures,
                &UpperRightFixedFloor,
                &UpperLeftFixedFloor,
                &UpperRightFixedDamagedRailing,
                &UpperLeftFixedDamagedRailing,
                &UpperRightFixedTrim,
                &UpperLeftFixedTrim,
                &UpperRightFixedWood,
                &UpperLeftFixedWood,
                &UpperRightFixedBrokenRailing,
                &UpperRightFixedSmoothFloor,
                &UpperLeftFixedRailing,
                &BridgeSupportArch1,
                &BridgeSupportArch2,
                &BridgeSupportArch3,
            &WoodDebris,
                &WoodDebris1,
                &WoodDebris2,
                &WoodDebris3,
            &WoodAndFloorTileDebris,
                &BridgeFragmentWood1,
                &BridgeFragmentWood2,
                &BridgeFragmentWood3,
                &BridgeFragmentFloor1,
                &BridgeFragmentFloor2,
                &BridgeFragmentFloor3,
        &UnusedAnimMarker,
    nullptr,
};
