#include "break_bridges.h"

StaticAnimatorNode N(UnusedAnimMarker) = {
    .pos = { 225.0f, 255.0f, 0.0f },
};

StaticAnimatorNode N(BridgeFragmentFloor3) = {
    .displayList = N(Gfx_DrawMesh_BridgeFragmentFloor3),
    .pos = { 0.0f, -500.0f, 0.0f },
};

StaticAnimatorNode N(BridgeFragmentFloor2) = {
    .displayList = N(Gfx_DrawMesh_BridgeFragmentFloor2),
    .pos = { 0.0f, -500.0f, 0.0f },
    .sibling = &N(BridgeFragmentFloor3),
};

StaticAnimatorNode N(BridgeFragmentFloor1) = {
    .displayList = N(Gfx_DrawMesh_BridgeFragmentFloor1),
    .pos = { 0.0f, -500.0f, 0.0f },
    .sibling = &N(BridgeFragmentFloor2),
};

StaticAnimatorNode N(BridgeFragmentWood3) = {
    .displayList = N(Gfx_DrawMesh_BridgeFragmentWood3),
    .pos = { 0.0f, -500.0f, 0.0f },
    .sibling = &N(BridgeFragmentFloor1),
};

StaticAnimatorNode N(BridgeFragmentWood2) = {
    .displayList = N(Gfx_DrawMesh_BridgeFragmentWood2),
    .pos = { 0.0f, -500.0f, 0.0f },
    .sibling = &N(BridgeFragmentWood3),
};

StaticAnimatorNode N(BridgeFragmentWood1) = {
    .displayList = N(Gfx_DrawMesh_BridgeFragmentWood1),
    .pos = { 0.0f, -500.0f, 0.0f },
    .sibling = &N(BridgeFragmentWood2),
};

StaticAnimatorNode N(WoodAndFloorTileDebris) = {
    .child = &N(BridgeFragmentWood1),
};

StaticAnimatorNode N(WoodDebris3) = {
    .displayList = N(Gfx_DrawMesh_WoodDebris3),
    .pos = { 0.0f, -500.0f, 0.0f },
};

StaticAnimatorNode N(WoodDebris2) = {
    .displayList = N(Gfx_DrawMesh_WoodDebris2),
    .pos = { 0.0f, -500.0f, 0.0f },
    .sibling = &N(WoodDebris3),
};

StaticAnimatorNode N(WoodDebris1) = {
    .displayList = N(Gfx_DrawMesh_WoodDebris1),
    .pos = { 0.0f, -500.0f, 0.0f },
    .sibling = &N(WoodDebris2),
};

StaticAnimatorNode N(WoodDebris) = {
    .sibling = &N(WoodAndFloorTileDebris),
    .child = &N(WoodDebris1),
};

StaticAnimatorNode N(BridgeSupportArch3) = {
    .displayList = N(Gfx_DrawMesh_BridgeSupportArch3),
};

StaticAnimatorNode N(BridgeSupportArch2) = {
    .displayList = N(Gfx_DrawMesh_BridgeSupportArch2),
    .sibling = &N(BridgeSupportArch3),
};

StaticAnimatorNode N(BridgeSupportArch1) = {
    .displayList = N(Gfx_DrawMesh_BridgeSupportArch1),
    .sibling = &N(BridgeSupportArch2),
};

StaticAnimatorNode N(UpperLeftFixedRailing) = {
    .displayList = N(Gfx_DrawMesh_UpperLeftFixedRailing),
    .sibling = &N(BridgeSupportArch1),
};

StaticAnimatorNode N(UpperRightFixedSmoothFloor) = {
    .displayList = N(Gfx_DrawMesh_UpperRightFixedSmoothFloor),
    .sibling = &N(UpperLeftFixedRailing),
};

StaticAnimatorNode N(UpperRightFixedBrokenRailing) = {
    .displayList = N(Gfx_DrawQuad_UpperRightFixedBrokenRailing),
    .sibling = &N(UpperRightFixedSmoothFloor),
};

StaticAnimatorNode N(UpperLeftFixedWood) = {
    .displayList = N(Gfx_DrawMesh_UpperLeftFixedWood),
    .sibling = &N(UpperRightFixedBrokenRailing),
};

StaticAnimatorNode N(UpperRightFixedWood) = {
    .displayList = N(Gfx_DrawMesh_UpperRightFixedWood),
    .sibling = &N(UpperLeftFixedWood),
};

StaticAnimatorNode N(UpperLeftFixedTrim) = {
    .displayList = N(Gfx_DrawMesh_UpperLeftFixedTrim),
    .sibling = &N(UpperRightFixedWood),
};

StaticAnimatorNode N(UpperRightFixedTrim) = {
    .displayList = N(Gfx_DrawMesh_UpperRightFixedTrim),
    .sibling = &N(UpperLeftFixedTrim),
};

StaticAnimatorNode N(UpperLeftFixedDamagedRailing) = {
    .displayList = N(Gfx_DrawMesh_UpperLeftFixedDamagedRailing),
    .sibling = &N(UpperRightFixedTrim),
};

StaticAnimatorNode N(UpperRightFixedDamagedRailing) = {
    .displayList = N(Gfx_DrawMesh_UpperRightFixedDamagedRailing),
    .sibling = &N(UpperLeftFixedDamagedRailing),
};

StaticAnimatorNode N(UpperLeftFixedFloor) = {
    .displayList = N(Gfx_DrawMesh_UpperLeftFixedFloor),
    .sibling = &N(UpperRightFixedDamagedRailing),
};

StaticAnimatorNode N(UpperRightFixedFloor) = {
    .displayList = N(Gfx_DrawMesh_UpperRightFixedFloor),
    .sibling = &N(UpperLeftFixedFloor),
};

StaticAnimatorNode N(BridgeFixedStructures) = {
    .sibling = &N(WoodDebris),
    .child = &N(UpperRightFixedFloor),
};

StaticAnimatorNode N(UpperRailingDebris11) = {
    .displayList = N(Gfx_DrawQuad_UpperRailingDebris11),
    .rot = { AS_F(0.000000f), AS_F(44.995880f), AS_F(-180.000000f) },
    .pos = { -315.0f, 2.0f, -139.0f },
};

StaticAnimatorNode N(UpperRailingDebris10) = {
    .displayList = N(Gfx_DrawQuad_UpperRailingDebris10),
    .rot = { AS_F(-180.000000f), AS_F(59.998169f), AS_F(-180.000000f) },
    .pos = { -455.0f, 421.0f, -20.0f },
    .sibling = &N(UpperRailingDebris11),
};

StaticAnimatorNode N(UpperRailingDebris09) = {
    .displayList = N(Gfx_DrawQuad_UpperRailingDebris09),
    .rot = { AS_F(-180.000000f), AS_F(-44.995880f), AS_F(0.000000f) },
    .pos = { -385.0f, 2.0f, 169.0f },
    .sibling = &N(UpperRailingDebris10),
};

StaticAnimatorNode N(UpperRailingDebris08) = {
    .displayList = N(Gfx_DrawQuad_UpperRailingDebris08),
    .rot = { AS_F(0.000000f), AS_F(59.998169f), AS_F(-180.000000f) },
    .pos = { -105.0f, 2.0f, -210.0f },
    .sibling = &N(UpperRailingDebris09),
};

StaticAnimatorNode N(UpperRailingDebris07) = {
    .displayList = N(Gfx_DrawQuad_UpperRailingDebris07),
    .rot = { AS_F(0.000000f), AS_F(-29.999084f), AS_F(-180.000000f) },
    .pos = { -5.0f, 2.0f, -180.0f },
    .sibling = &N(UpperRailingDebris08),
};

StaticAnimatorNode N(UpperRailingDebris06) = {
    .displayList = N(Gfx_DrawQuad_UpperRailingDebris06),
    .rot = { AS_F(-180.000000f), AS_F(14.996796f), AS_F(0.000000f) },
    .pos = { -195.0f, 2.0f, 259.0f },
    .sibling = &N(UpperRailingDebris07),
};

StaticAnimatorNode N(UpperRailingDebris05) = {
    .displayList = N(Gfx_DrawQuad_UpperRailingDebris05),
    .rot = { AS_F(-180.000000f), AS_F(-59.998169f), AS_F(-180.000000f) },
    .pos = { -65.0f, 2.0f, 189.0f },
    .sibling = &N(UpperRailingDebris06),
};

StaticAnimatorNode N(UpperRailingDebris04) = {
    .displayList = N(Gfx_DrawQuad_UpperRailingDebris04),
    .rot = { AS_F(-180.000000f), AS_F(0.000000f), AS_F(0.000000f) },
    .pos = { 275.0f, 2.0f, -129.0f },
    .sibling = &N(UpperRailingDebris05),
};

StaticAnimatorNode N(UpperRailingDebris03) = {
    .displayList = N(Gfx_DrawQuad_UpperRailingDebris03),
    .rot = { AS_F(0.000000f), AS_F(-14.996796f), AS_F(-180.000000f) },
    .pos = { 195.0f, 421.0f, -40.0f },
    .sibling = &N(UpperRailingDebris04),
};

StaticAnimatorNode N(UpperRailingDebris02) = {
    .displayList = N(Gfx_DrawQuad_UpperRailingDebris02),
    .rot = { AS_F(-180.000000f), AS_F(29.999084f), AS_F(-180.000000f) },
    .pos = { 85.0f, 2.0f, 329.0f },
    .sibling = &N(UpperRailingDebris03),
};

StaticAnimatorNode N(UpperRailingDebris01) = {
    .displayList = N(Gfx_DrawQuad_UpperRailingDebris01),
    .rot = { AS_F(-180.000000f), AS_F(29.999084f), AS_F(0.000000f) },
    .pos = { 215.0f, 421.0f, 29.0f },
    .sibling = &N(UpperRailingDebris02),
};

StaticAnimatorNode N(UpperBridgeRailingDebris) = {
    .sibling = &N(BridgeFixedStructures),
    .child = &N(UpperRailingDebris01),
};

StaticAnimatorNode N(UpperTrimDebris9) = {
    .displayList = N(Gfx_DrawQuad_UpperTrimDebris9),
    .rot = { AS_F(-180.000000f), AS_F(0.000000f), AS_F(0.000000f) },
    .pos = { 8.0f, -23.0f, -49.0f },
};

StaticAnimatorNode N(UpperTrimDebris8) = {
    .displayList = N(Gfx_DrawQuad_UpperTrimDebris8),
    .rot = { AS_F(0.000000f), AS_F(-9.997864f), AS_F(-180.000000f) },
    .pos = { 73.0f, -23.0f, 20.0f },
    .sibling = &N(UpperTrimDebris9),
};

StaticAnimatorNode N(UpperTrimDebris7) = {
    .displayList = N(Gfx_DrawQuad_UpperTrimDebris7),
    .rot = { AS_F(-180.000000f), AS_F(0.000000f), AS_F(0.000000f) },
    .pos = { -1.0f, -23.0f, 49.0f },
    .sibling = &N(UpperTrimDebris8),
};

StaticAnimatorNode N(UpperTrimDebris6) = {
    .displayList = N(Gfx_DrawQuad_UpperTrimDebris6),
    .rot = { AS_F(-180.000000f), AS_F(0.000000f), AS_F(-180.000000f) },
    .pos = { 18.0f, -23.0f, 0.0f },
    .sibling = &N(UpperTrimDebris7),
};

StaticAnimatorNode N(UpperTrimDebrisCluster) = {
    .rot = { AS_F(0.000000f), AS_F(44.995880f), AS_F(0.000000f) },
    .pos = { 61.0f, 47.0f, -31.0f },
    .child = &N(UpperTrimDebris6),
};

StaticAnimatorNode N(UpperTrimDebris5) = {
    .displayList = N(Gfx_DrawQuad_UpperTrimDebris5),
    .rot = { AS_F(-180.000000f), AS_F(14.996796f), AS_F(0.000000f) },
    .pos = { -415.0f, 21.0f, 20.0f },
    .sibling = &N(UpperTrimDebrisCluster),
};

StaticAnimatorNode N(UpperTrimDebris4) = {
    .displayList = N(Gfx_DrawQuad_UpperTrimDebris4),
    .rot = { AS_F(-180.000000f), AS_F(-9.997864f), AS_F(-180.000000f) },
    .pos = { 195.0f, 211.0f, -39.0f },
    .sibling = &N(UpperTrimDebris5),
};

StaticAnimatorNode N(UpperTrimDebris3) = {
    .displayList = N(Gfx_DrawQuad_UpperTrimDebris3),
    .rot = { AS_F(-180.000000f), AS_F(-19.995727f), AS_F(-180.000000f) },
    .pos = { 95.0f, 210.0f, -30.0f },
    .sibling = &N(UpperTrimDebris4),
};

StaticAnimatorNode N(UpperTrimDebris2) = {
    .displayList = N(Gfx_DrawQuad_UpperTrimDebris2),
    .rot = { AS_F(-180.000000f), AS_F(29.999084f), AS_F(-180.000000f) },
    .pos = { 115.0f, 211.0f, 39.0f },
    .sibling = &N(UpperTrimDebris3),
};

StaticAnimatorNode N(UpperTrimDebris1) = {
    .displayList = N(Gfx_DrawQuad_UpperTrimDebris1),
    .rot = { AS_F(-180.000000f), AS_F(14.996796f), AS_F(-180.000000f) },
    .pos = { 215.0f, 211.0f, 39.0f },
    .sibling = &N(UpperTrimDebris2),
};

StaticAnimatorNode N(UpperBridgeWoodPanelTrimDebris) = {
    .sibling = &N(UpperBridgeRailingDebris),
    .child = &N(UpperTrimDebris1),
};

StaticAnimatorNode N(LowerTrimDebris3) = {
    .displayList = N(Gfx_DrawQuad_LowerTrimDebris3),
    .rot = { AS_F(0.000000f), AS_F(14.996796f), AS_F(0.000000f) },
    .pos = { -375.0f, 2.0f, 0.0f },
};

StaticAnimatorNode N(LowerTrimDebris2) = {
    .displayList = N(Gfx_DrawQuad_LowerTrimDebris2),
    .rot = { AS_F(0.000000f), AS_F(-29.999084f), AS_F(-180.000000f) },
    .pos = { -175.0f, 2.0f, -49.0f },
    .sibling = &N(LowerTrimDebris3),
};

StaticAnimatorNode N(LowerTrimDebris1) = {
    .displayList = N(Gfx_DrawQuad_LowerTrimDebris1),
    .rot = { AS_F(-180.000000f), AS_F(0.000000f), AS_F(-180.000000f) },
    .pos = { 75.0f, 2.0f, -49.0f },
    .sibling = &N(LowerTrimDebris2),
};

StaticAnimatorNode N(LowerBridgeWoodPanelTrimDebris) = {
    .sibling = &N(UpperBridgeWoodPanelTrimDebris),
    .child = &N(LowerTrimDebris1),
};

StaticAnimatorNode N(BridgeStructuresAndDebris) = {
    .sibling = &N(UnusedAnimMarker),
    .child = &N(LowerBridgeWoodPanelTrimDebris),
};

StaticAnimatorNode N(LowerLeftCollapseRailing) = {
    .displayList = N(Gfx_DrawMesh_LowerLeftCollapseRailing),
};

StaticAnimatorNode N(LowerLeftCollapseTrim) = {
    .displayList = N(Gfx_DrawMesh_LowerLeftCollapseTrim),
    .sibling = &N(LowerLeftCollapseRailing),
};

StaticAnimatorNode N(LowerLeftCollapseDamagedRailing) = {
    .displayList = N(Gfx_DrawMesh_LowerLeftCollapseDamagedRailing),
    .sibling = &N(LowerLeftCollapseTrim),
};

StaticAnimatorNode N(LowerLeftCollapseFloor) = {
    .displayList = N(Gfx_DrawMesh_LowerLeftCollapseFloor),
    .sibling = &N(LowerLeftCollapseDamagedRailing),
};

StaticAnimatorNode N(LowerLeftCollapseSmoothFloor) = {
    .displayList = N(Gfx_DrawMesh_LowerLeftCollapseSmoothFloor),
    .sibling = &N(LowerLeftCollapseFloor),
};

StaticAnimatorNode N(LowerLeftCollapseWood3) = {
    .displayList = N(Gfx_DrawMesh_LowerLeftCollapseWood3),
    .sibling = &N(LowerLeftCollapseSmoothFloor),
};

StaticAnimatorNode N(LowerLeftCollapseWood2) = {
    .displayList = N(Gfx_DrawMesh_LowerLeftCollapseWood2),
    .sibling = &N(LowerLeftCollapseWood3),
};

StaticAnimatorNode N(LowerLeftCollapseWood1) = {
    .displayList = N(Gfx_DrawMesh_LowerLeftCollapseWood1),
    .sibling = &N(LowerLeftCollapseWood2),
};

StaticAnimatorNode N(LowerBridgeLeftCollapse) = {
    .rot = { AS_F(0.000000f), AS_F(0.000000f), AS_F(-30.065004f) },
    .pos = { -360.0f, 85.0f, -1.0f },
    .child = &N(LowerLeftCollapseWood1),
};

StaticAnimatorNode N(UpperRearRailingWood) = {
    .displayList = N(Gfx_DrawMesh_UpperRearRailingWood),
};

StaticAnimatorNode N(UpperRearBrokenRailing) = {
    .displayList = N(Gfx_DrawMesh_UpperRearBrokenRailing),
    .sibling = &N(UpperRearRailingWood),
};

StaticAnimatorNode N(UpperBridgeRearRailing) = {
    .rot = { AS_F(-29.999084f), AS_F(65.431074f), AS_F(-22.247993f) },
    .pos = { 35.0f, 316.0f, 36.0f },
    .sibling = &N(LowerBridgeLeftCollapse),
    .child = &N(UpperRearBrokenRailing),
};

StaticAnimatorNode N(UpperRightCollapseSmoothFloor) = {
    .displayList = N(Gfx_DrawMesh_UpperRightCollapseSmoothFloor),
};

StaticAnimatorNode N(UpperRightCollapseWood) = {
    .displayList = N(Gfx_DrawMesh_UpperRightCollapseWood),
    .sibling = &N(UpperRightCollapseSmoothFloor),
};

StaticAnimatorNode N(UpperRightCollapseBrokenRailing) = {
    .displayList = N(Gfx_DrawMesh_UpperRightCollapseBrokenRailing),
    .sibling = &N(UpperRightCollapseWood),
};

StaticAnimatorNode N(UpperRightCollapseFloor) = {
    .displayList = N(Gfx_DrawMesh_UpperRightCollapseFloor),
    .sibling = &N(UpperRightCollapseBrokenRailing),
};

StaticAnimatorNode N(UpperRightCollapseDamagedRailing) = {
    .displayList = N(Gfx_DrawMesh_UpperRightCollapseDamagedRailing),
    .sibling = &N(UpperRightCollapseFloor),
};

StaticAnimatorNode N(UpperRightCollapseTrim) = {
    .displayList = N(Gfx_DrawMesh_UpperRightCollapseTrim),
    .sibling = &N(UpperRightCollapseDamagedRailing),
};

StaticAnimatorNode N(UpperBridgeRightCollapse) = {
    .rot = { AS_F(-4.998932f), AS_F(-2.598346f), AS_F(0.000000f) },
    .pos = { 133.0f, 271.0f, 30.0f },
    .sibling = &N(UpperBridgeRearRailing),
    .child = &N(UpperRightCollapseTrim),
};

StaticAnimatorNode N(LowerRailingSplitRightBrokenRailing) = {
    .displayList = N(Gfx_DrawMesh_LowerRailingSplitRightBrokenRailing),
    .pos = { 252.0f, 0.0f, 0.0f },
};

StaticAnimatorNode N(LowerRailingSplitRightWood2) = {
    .displayList = N(Gfx_DrawMesh_LowerRailingSplitRightWood2),
    .pos = { 252.0f, 0.0f, 0.0f },
    .sibling = &N(LowerRailingSplitRightBrokenRailing),
};

StaticAnimatorNode N(LowerRailingSplitRightWood1) = {
    .displayList = N(Gfx_DrawMesh_LowerRailingSplitRightWood1),
    .pos = { 252.0f, 0.0f, 0.0f },
    .sibling = &N(LowerRailingSplitRightWood2),
};

StaticAnimatorNode N(LowerRailingSplitRightParts) = {
    .sibling = &N(LowerRailingSplitRightWood1),
};

StaticAnimatorNode N(LowerRailingSplitRightHinge) = {
    .rot = { AS_F(0.000000f), AS_F(0.000000f), AS_F(-13.997009f) },
    .pos = { -252.0f, 0.0f, 0.0f },
    .child = &N(LowerRailingSplitRightParts),
};

StaticAnimatorNode N(LowerRailingSplitRight) = {
    .rot = { AS_F(0.000000f), AS_F(0.000000f), AS_F(13.997009f) },
    .pos = { 253.0f, 285.0f, 86.0f },
    .child = &N(LowerRailingSplitRightHinge),
};

StaticAnimatorNode N(LowerRightBrokenRailing) = {
    .displayList = N(Gfx_DrawMesh_LowerRightBrokenRailing),
    .sibling = &N(LowerRailingSplitRight),
};

StaticAnimatorNode N(LowerRightSmoothFloor2) = {
    .displayList = N(Gfx_DrawMesh_LowerRightSmoothFloor2),
    .pos = { 0.0f, -500.0f, 0.0f },
    .sibling = &N(LowerRightBrokenRailing),
};

StaticAnimatorNode N(LowerRightSmoothFloor1) = {
    .displayList = N(Gfx_DrawMesh_LowerRightSmoothFloor1),
    .sibling = &N(LowerRightSmoothFloor2),
};

StaticAnimatorNode N(LowerRightTrim) = {
    .displayList = N(Gfx_DrawMesh_LowerRightTrim),
    .sibling = &N(LowerRightSmoothFloor1),
};

StaticAnimatorNode N(LowerRightDamagedRailing) = {
    .displayList = N(Gfx_DrawMesh_LowerRightDamagedRailing),
    .sibling = &N(LowerRightTrim),
};

StaticAnimatorNode N(LowerRightFloor) = {
    .displayList = N(Gfx_DrawMesh_LowerRightFloor),
    .sibling = &N(LowerRightDamagedRailing),
};

StaticAnimatorNode N(LowerRightWood2) = {
    .displayList = N(Gfx_DrawMesh_LowerRightWood2),
    .sibling = &N(LowerRightFloor),
};

StaticAnimatorNode N(LowerRightWood1) = {
    .displayList = N(Gfx_DrawMesh_LowerRightWood1),
    .sibling = &N(LowerRightWood2),
};

StaticAnimatorNode N(LowerBridgeRightFixed) = {
    .sibling = &N(UpperBridgeRightCollapse),
    .child = &N(LowerRightWood1),
};

StaticAnimatorNode N(LowerRailingSplitLeftWood2) = {
    .displayList = N(Gfx_DrawMesh_LowerRailingSplitLeftWood2),
};

StaticAnimatorNode N(LowerRailingSplitLeftWood1) = {
    .displayList = N(Gfx_DrawMesh_LowerRailingSplitLeftWood1),
    .sibling = &N(LowerRailingSplitLeftWood2),
};

StaticAnimatorNode N(LowerRailingSplitLeftBrokenRailing) = {
    .displayList = N(Gfx_DrawMesh_LowerRailingSplitLeftBrokenRailing),
    .sibling = &N(LowerRailingSplitLeftWood1),
};

StaticAnimatorNode N(LowerRailingSplitLeft) = {
    .pos = { 105.0f, -8.0f, 87.0f },
    .child = &N(LowerRailingSplitLeftBrokenRailing),
};

StaticAnimatorNode N(LowerCenterBrokenRailing) = {
    .displayList = N(Gfx_DrawMesh_LowerCenterBrokenRailing),
    .sibling = &N(LowerRailingSplitLeft),
};

StaticAnimatorNode N(LowerCenterSmoothFloor) = {
    .displayList = N(Gfx_DrawMesh_LowerCenterSmoothFloor),
    .sibling = &N(LowerCenterBrokenRailing),
};

StaticAnimatorNode N(LowerCenterTrim) = {
    .displayList = N(Gfx_DrawMesh_LowerCenterTrim),
    .sibling = &N(LowerCenterSmoothFloor),
};

StaticAnimatorNode N(LowerCenterDamagedRailing) = {
    .displayList = N(Gfx_DrawMesh_LowerCenterDamagedRailing),
    .sibling = &N(LowerCenterTrim),
};

StaticAnimatorNode N(LowerCenterFloor) = {
    .displayList = N(Gfx_DrawMesh_LowerCenterFloor),
    .sibling = &N(LowerCenterDamagedRailing),
};

StaticAnimatorNode N(LowerCenterWood2) = {
    .displayList = N(Gfx_DrawMesh_LowerCenterWood2),
    .sibling = &N(LowerCenterFloor),
};

StaticAnimatorNode N(LowerCenterWood1) = {
    .displayList = N(Gfx_DrawMesh_LowerCenterWood1),
    .sibling = &N(LowerCenterWood2),
};

StaticAnimatorNode N(LowerBridgeCenterCollapse) = {
    .rot = { AS_F(0.000000f), AS_F(44.995880f), AS_F(0.000000f) },
    .pos = { 61.0f, 47.0f, -31.0f },
    .sibling = &N(LowerBridgeRightFixed),
    .child = &N(LowerCenterWood1),
};

StaticAnimatorNode N(LowerLeftAttachWood4) = {
    .displayList = N(Gfx_DrawMesh_LowerLeftAttachWood4),
    .rot = { AS_F(4.998932f), AS_F(0.000000f), AS_F(34.998016f) },
    .pos = { -465.0f, 210.0f, -90.0f },
};

StaticAnimatorNode N(LowerLeftAttachWood3) = {
    .displayList = N(Gfx_DrawMesh_LowerLeftAttachWood3),
    .rot = { AS_F(0.000000f), AS_F(34.998016f), AS_F(29.999084f) },
    .pos = { -465.0f, 210.0f, 90.0f },
    .sibling = &N(LowerLeftAttachWood4),
};

StaticAnimatorNode N(LowerLeftAttachRailing) = {
    .displayList = N(Gfx_DrawMesh_LowerLeftAttachRailing),
    .sibling = &N(LowerLeftAttachWood3),
};

StaticAnimatorNode N(LowerLeftAttachTrim) = {
    .displayList = N(Gfx_DrawMesh_LowerLeftAttachTrim),
    .sibling = &N(LowerLeftAttachRailing),
};

StaticAnimatorNode N(LowerLeftAttachDamagedRailing) = {
    .displayList = N(Gfx_DrawMesh_LowerLeftAttachDamagedRailing),
    .sibling = &N(LowerLeftAttachTrim),
};

StaticAnimatorNode N(LowerLeftAttachFloor) = {
    .displayList = N(Gfx_DrawMesh_LowerLeftAttachFloor),
    .sibling = &N(LowerLeftAttachDamagedRailing),
};

StaticAnimatorNode N(LowerLeftAttachSmoothFloor) = {
    .displayList = N(Gfx_DrawMesh_LowerLeftAttachSmoothFloor),
    .pos = { 0.0f, -500.0f, 0.0f },
    .sibling = &N(LowerLeftAttachFloor),
};

StaticAnimatorNode N(LowerLeftAttachWood2) = {
    .displayList = N(Gfx_DrawMesh_LowerLeftAttachWood2),
    .sibling = &N(LowerLeftAttachSmoothFloor),
};

StaticAnimatorNode N(LowerLeftAttachWood1) = {
    .displayList = N(Gfx_DrawMesh_LowerLeftAttachWood1),
    .sibling = &N(LowerLeftAttachWood2),
};

StaticAnimatorNode N(LowerBridgeLeftAttachment) = {
    .pos = { 0.0f, -188.0f, 0.0f },
    .sibling = &N(LowerBridgeCenterCollapse),
    .child = &N(LowerLeftAttachWood1),
};

StaticAnimatorNode N(UpperLeftWood) = {
    .displayList = N(Gfx_DrawMesh_UpperLeftWood),
    .pos = { -179.0f, 34.0f, 98.0f },
};

StaticAnimatorNode N(UpperLeftSmoothFloor) = {
    .displayList = N(Gfx_DrawMesh_UpperLeftSmoothFloor),
    .pos = { -179.0f, 34.0f, 98.0f },
    .sibling = &N(UpperLeftWood),
};

StaticAnimatorNode N(UpperLeftTrim) = {
    .displayList = N(Gfx_DrawMesh_UpperLeftTrim),
    .pos = { -179.0f, 34.0f, 98.0f },
    .sibling = &N(UpperLeftSmoothFloor),
};

StaticAnimatorNode N(UpperLeftDamagedRailing) = {
    .displayList = N(Gfx_DrawMesh_UpperLeftDamagedRailing),
    .pos = { -179.0f, 34.0f, 98.0f },
    .sibling = &N(UpperLeftTrim),
};

StaticAnimatorNode N(UpperLeftFloor) = {
    .displayList = N(Gfx_DrawMesh_UpperLeftFloor),
    .pos = { -179.0f, 34.0f, 98.0f },
    .sibling = &N(UpperLeftDamagedRailing),
};

StaticAnimatorNode N(UpperLeftRailing) = {
    .displayList = N(Gfx_DrawMesh_UpperLeftRailing),
    .pos = { -179.0f, 34.0f, 98.0f },
    .sibling = &N(UpperLeftFloor),
};

StaticAnimatorNode N(UpperBridgeLeft) = {
    .rot = { AS_F(-6.998505f), AS_F(-81.499069f), AS_F(0.000000f) },
    .pos = { 179.0f, -34.0f, -98.0f },
    .child = &N(UpperLeftRailing),
};

StaticAnimatorNode N(UpperBridgeLeftCollapse) = {
    .rot = { AS_F(0.000000f), AS_F(-8.404798f), AS_F(-83.828242f) },
    .pos = { -245.0f, 196.0f, 21.0f },
    .sibling = &N(LowerBridgeLeftAttachment),
    .child = &N(UpperBridgeLeft),
};

StaticAnimatorNode N(BridgeSections) = {
    .sibling = &N(BridgeStructuresAndDebris),
    .child = &N(UpperBridgeLeftCollapse),
};

StaticAnimatorNode N(SmashBridgesRoot) = {
    .child = &N(BridgeSections),
};

StaticAnimatorNode* N(SmashBridgesSkeleton)[] = {
    &N(SmashBridgesRoot),
        &N(BridgeSections),
            &N(UpperBridgeLeftCollapse),
                &N(UpperBridgeLeft),
                    &N(UpperLeftRailing),
                    &N(UpperLeftFloor),
                    &N(UpperLeftDamagedRailing),
                    &N(UpperLeftTrim),
                    &N(UpperLeftSmoothFloor),
                    &N(UpperLeftWood),
            &N(LowerBridgeLeftAttachment),
                &N(LowerLeftAttachWood1),
                &N(LowerLeftAttachWood2),
                &N(LowerLeftAttachSmoothFloor),
                &N(LowerLeftAttachFloor),
                &N(LowerLeftAttachDamagedRailing),
                &N(LowerLeftAttachTrim),
                &N(LowerLeftAttachRailing),
                &N(LowerLeftAttachWood3),
                &N(LowerLeftAttachWood4),
            &N(LowerBridgeCenterCollapse),
                &N(LowerCenterWood1),
                &N(LowerCenterWood2),
                &N(LowerCenterFloor),
                &N(LowerCenterDamagedRailing),
                &N(LowerCenterTrim),
                &N(LowerCenterSmoothFloor),
                &N(LowerCenterBrokenRailing),
                &N(LowerRailingSplitLeft),
                    &N(LowerRailingSplitLeftBrokenRailing),
                    &N(LowerRailingSplitLeftWood1),
                    &N(LowerRailingSplitLeftWood2),
            &N(LowerBridgeRightFixed),
                &N(LowerRightWood1),
                &N(LowerRightWood2),
                &N(LowerRightFloor),
                &N(LowerRightDamagedRailing),
                &N(LowerRightTrim),
                &N(LowerRightSmoothFloor1),
                &N(LowerRightSmoothFloor2),
                &N(LowerRightBrokenRailing),
                &N(LowerRailingSplitRight),
                    &N(LowerRailingSplitRightHinge),
                        &N(LowerRailingSplitRightParts),
                        &N(LowerRailingSplitRightWood1),
                        &N(LowerRailingSplitRightWood2),
                        &N(LowerRailingSplitRightBrokenRailing),
            &N(UpperBridgeRightCollapse),
                &N(UpperRightCollapseTrim),
                &N(UpperRightCollapseDamagedRailing),
                &N(UpperRightCollapseFloor),
                &N(UpperRightCollapseBrokenRailing),
                &N(UpperRightCollapseWood),
                &N(UpperRightCollapseSmoothFloor),
            &N(UpperBridgeRearRailing),
                &N(UpperRearBrokenRailing),
                &N(UpperRearRailingWood),
            &N(LowerBridgeLeftCollapse),
                &N(LowerLeftCollapseWood1),
                &N(LowerLeftCollapseWood2),
                &N(LowerLeftCollapseWood3),
                &N(LowerLeftCollapseSmoothFloor),
                &N(LowerLeftCollapseFloor),
                &N(LowerLeftCollapseDamagedRailing),
                &N(LowerLeftCollapseTrim),
                &N(LowerLeftCollapseRailing),
        &N(BridgeStructuresAndDebris),
            &N(LowerBridgeWoodPanelTrimDebris),
                &N(LowerTrimDebris1),
                &N(LowerTrimDebris2),
                &N(LowerTrimDebris3),
            &N(UpperBridgeWoodPanelTrimDebris),
                &N(UpperTrimDebris1),
                &N(UpperTrimDebris2),
                &N(UpperTrimDebris3),
                &N(UpperTrimDebris4),
                &N(UpperTrimDebris5),
                &N(UpperTrimDebrisCluster),
                    &N(UpperTrimDebris6),
                    &N(UpperTrimDebris7),
                    &N(UpperTrimDebris8),
                    &N(UpperTrimDebris9),
            &N(UpperBridgeRailingDebris),
                &N(UpperRailingDebris01),
                &N(UpperRailingDebris02),
                &N(UpperRailingDebris03),
                &N(UpperRailingDebris04),
                &N(UpperRailingDebris05),
                &N(UpperRailingDebris06),
                &N(UpperRailingDebris07),
                &N(UpperRailingDebris08),
                &N(UpperRailingDebris09),
                &N(UpperRailingDebris10),
                &N(UpperRailingDebris11),
            &N(BridgeFixedStructures),
                &N(UpperRightFixedFloor),
                &N(UpperLeftFixedFloor),
                &N(UpperRightFixedDamagedRailing),
                &N(UpperLeftFixedDamagedRailing),
                &N(UpperRightFixedTrim),
                &N(UpperLeftFixedTrim),
                &N(UpperRightFixedWood),
                &N(UpperLeftFixedWood),
                &N(UpperRightFixedBrokenRailing),
                &N(UpperRightFixedSmoothFloor),
                &N(UpperLeftFixedRailing),
                &N(BridgeSupportArch1),
                &N(BridgeSupportArch2),
                &N(BridgeSupportArch3),
            &N(WoodDebris),
                &N(WoodDebris1),
                &N(WoodDebris2),
                &N(WoodDebris3),
            &N(WoodAndFloorTileDebris),
                &N(BridgeFragmentWood1),
                &N(BridgeFragmentWood2),
                &N(BridgeFragmentWood3),
                &N(BridgeFragmentFloor1),
                &N(BridgeFragmentFloor2),
                &N(BridgeFragmentFloor3),
        &N(UnusedAnimMarker),
    nullptr,
};
