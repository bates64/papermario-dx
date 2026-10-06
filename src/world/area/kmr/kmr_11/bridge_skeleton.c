#include "kmr_11.h"

StaticAnimatorNode BridgeDebrisNode_dummy32 = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .modelID = AS_MODEL_ID(MODEL_dummy32),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode BridgeDebrisTransform_dummy32 = {
    .pos = { -159.0f, 0.0f, -126.0f },
    .child = &BridgeDebrisNode_dummy32,
};

StaticAnimatorNode BridgeDebrisNode_dummy31 = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .modelID = AS_MODEL_ID(MODEL_dummy31),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode BridgeDebrisTransform_dummy31 = {
    .pos = { -159.0f, 0.0f, -126.0f },
    .child = &BridgeDebrisNode_dummy31,
    .sibling = &BridgeDebrisTransform_dummy32,
};

StaticAnimatorNode BridgeDebrisNode_dummy30 = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .modelID = AS_MODEL_ID(MODEL_dummy30),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode BridgeDebrisTransform_dummy30 = {
    .pos = { -159.0f, 0.0f, -126.0f },
    .child = &BridgeDebrisNode_dummy30,
    .sibling = &BridgeDebrisTransform_dummy31,
};

StaticAnimatorNode BridgeDebrisGroup_dummy30 = {
    .pos = { 140.0f, -10.0f, -360.0f },
    .rot = { AS_F(0.0f), AS_F(-180.0f), AS_F(0.0f) },
    .child = &BridgeDebrisTransform_dummy30,
};

StaticAnimatorNode BridgeDebrisNode_dummy3 = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .modelID = AS_MODEL_ID(MODEL_dummy3),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode BridgeDebrisTransform_dummy3 = {
    .pos = { -159.0f, 0.0f, -126.0f },
    .child = &BridgeDebrisNode_dummy3,
};

StaticAnimatorNode BridgeDebrisNode_dummy2 = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .modelID = AS_MODEL_ID(MODEL_dummy2),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode BridgeDebrisTransform_dummy2 = {
    .pos = { -159.0f, 0.0f, -126.0f },
    .child = &BridgeDebrisNode_dummy2,
    .sibling = &BridgeDebrisTransform_dummy3,
};

StaticAnimatorNode BridgeDebrisNode_dummy1 = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .modelID = AS_MODEL_ID(MODEL_dummy1),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode BridgeDebrisTransform_dummy1 = {
    .pos = { -159.0f, 0.0f, -126.0f },
    .child = &BridgeDebrisNode_dummy1,
    .sibling = &BridgeDebrisTransform_dummy2,
};

StaticAnimatorNode BridgeDebrisGroup_dummy1 = {
    .pos = { 0.0f, -10.0f, 0.0f },
    .child = &BridgeDebrisTransform_dummy1,
    .sibling = &BridgeDebrisGroup_dummy30,
};

StaticAnimatorNode BridgeDebrisRoot = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .child = &BridgeDebrisGroup_dummy1,
};

StaticAnimatorNode BridgeDummyNode = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(-12.695089f), AS_F(0.0f) },
    .modelID = AS_MODEL_ID(MODEL_dummy),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode BridgeDummyTransform = {
    .pos = { 0.0f, 110.0f, 0.0f },
    .child = &BridgeDummyNode,
};

StaticAnimatorNode BridgeSegmentNode_b1 = {
    .pos = { -237.0f, 109.0f, 155.0f },
    .rot = { AS_F(0.0f), AS_F(-12.695089f), AS_F(-179.9945f) },
    .modelID = AS_MODEL_ID(MODEL_b1),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode BridgeSegmentNode_b2 = {
    .pos = { 312.0f, -169.0f, 155.0f },
    .rot = { AS_F(0.0f), AS_F(-12.695089f), AS_F(0.0f) },
    .modelID = AS_MODEL_ID(MODEL_b2),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode BridgeSegmentNode_b3 = {
    .pos = { -237.0f, 169.0f, 155.0f },
    .rot = { AS_F(0.0f), AS_F(-12.695089f), AS_F(-179.9945f) },
    .modelID = AS_MODEL_ID(MODEL_b3),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode BridgeSegmentNode_b4 = {
    .pos = { 312.0f, -229.0f, 155.0f },
    .rot = { AS_F(0.0f), AS_F(-12.695089f), AS_F(0.0f) },
    .modelID = AS_MODEL_ID(MODEL_b4),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode BridgeSegmentNode_b5 = {
    .pos = { -237.0f, 229.0f, 155.0f },
    .rot = { AS_F(0.0f), AS_F(-12.695089f), AS_F(-179.9945f) },
    .modelID = AS_MODEL_ID(MODEL_b5),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode BridgeSegmentNode_b6 = {
    .pos = { 312.0f, -289.0f, 155.0f },
    .rot = { AS_F(0.0f), AS_F(-12.695089f), AS_F(0.0f) },
    .modelID = AS_MODEL_ID(MODEL_b6),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode BridgeSegmentRigNode16 = {
    .pos = { 75.0f, 0.0f, 0.0f },
    .sibling = &BridgeSegmentNode_b6,
};

StaticAnimatorNode BridgeSegmentRigNode15 = {
    .pos = { 30.0f, 0.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-89.99725f) },
    .child = &BridgeSegmentRigNode16,
};

StaticAnimatorNode BridgeSegmentRigNode14 = {
    .pos = { 30.0f, 0.0f, 0.0f },
    .child = &BridgeSegmentRigNode15,
};

StaticAnimatorNode BridgeSegmentRigNode13 = {
    .pos = { 75.0f, 0.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-89.99725f) },
    .child = &BridgeSegmentRigNode14,
    .sibling = &BridgeSegmentNode_b5,
};

StaticAnimatorNode BridgeSegmentRigNode12 = {
    .pos = { 75.0f, 0.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(179.9945f) },
    .child = &BridgeSegmentRigNode13,
    .sibling = &BridgeSegmentNode_b4,
};

StaticAnimatorNode BridgeSegmentRigNode11 = {
    .pos = { 30.0f, 0.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-89.99725f) },
    .child = &BridgeSegmentRigNode12,
};

StaticAnimatorNode BridgeSegmentRigNode10 = {
    .pos = { 30.0f, 0.0f, 0.0f },
    .child = &BridgeSegmentRigNode11,
};

StaticAnimatorNode BridgeSegmentRigNode09 = {
    .pos = { 75.0f, 0.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-89.99725f) },
    .child = &BridgeSegmentRigNode10,
    .sibling = &BridgeSegmentNode_b3,
};

StaticAnimatorNode BridgeSegmentRigNode08 = {
    .pos = { 75.0f, 0.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(179.9945f) },
    .child = &BridgeSegmentRigNode09,
    .sibling = &BridgeSegmentNode_b2,
};

StaticAnimatorNode BridgeSegmentRigNode07 = {
    .pos = { 30.0f, 0.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-89.99725f) },
    .child = &BridgeSegmentRigNode08,
};

StaticAnimatorNode BridgeSegmentRigNode06 = {
    .pos = { 30.0f, 0.0f, 0.0f },
    .child = &BridgeSegmentRigNode07,
};

StaticAnimatorNode BridgeSegmentRigNode05 = {
    .pos = { 75.0f, 0.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-89.99725f) },
    .child = &BridgeSegmentRigNode06,
    .sibling = &BridgeSegmentNode_b1,
};

StaticAnimatorNode BridgeSegmentRigRoot = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(179.9945f) },
    .child = &BridgeSegmentRigNode05,
};

StaticAnimatorNode BridgeSegmentAssembly = {
    .pos = { 0.0f, 110.0f, 0.0f },
    .child = &BridgeSegmentRigRoot,
    .sibling = &BridgeDummyTransform,
};

StaticAnimatorNode BridgeAssembly = {
    .pos = { -266.0f, 0.0f, -99.0f },
    .rot = { AS_F(0.0f), AS_F(12.695089f), AS_F(0.0f) },
    .child = &BridgeSegmentAssembly,
    .sibling = &BridgeDebrisRoot,
};

StaticAnimatorNode BridgeRoot = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .child = &BridgeAssembly,
};

StaticAnimatorNode* AnimSkeleton_Bridge[] = {
    &BridgeRoot,
        &BridgeAssembly,
            &BridgeSegmentAssembly,
                &BridgeSegmentRigRoot,
                    &BridgeSegmentRigNode05,
                        &BridgeSegmentRigNode06,
                            &BridgeSegmentRigNode07,
                                &BridgeSegmentRigNode08,
                                    &BridgeSegmentRigNode09,
                                        &BridgeSegmentRigNode10,
                                            &BridgeSegmentRigNode11,
                                                &BridgeSegmentRigNode12,
                                                    &BridgeSegmentRigNode13,
                                                        &BridgeSegmentRigNode14,
                                                            &BridgeSegmentRigNode15,
                                                                &BridgeSegmentRigNode16,
                                                                &BridgeSegmentNode_b6,
                                                    &BridgeSegmentNode_b5,
                                                &BridgeSegmentNode_b4,
                                    &BridgeSegmentNode_b3,
                                &BridgeSegmentNode_b2,
                    &BridgeSegmentNode_b1,
            &BridgeDummyTransform,
                &BridgeDummyNode,
        &BridgeDebrisRoot,
            &BridgeDebrisGroup_dummy1,
                &BridgeDebrisTransform_dummy1,
                    &BridgeDebrisNode_dummy1,
                &BridgeDebrisTransform_dummy2,
                    &BridgeDebrisNode_dummy2,
                &BridgeDebrisTransform_dummy3,
                    &BridgeDebrisNode_dummy3,
            &BridgeDebrisGroup_dummy30,
                &BridgeDebrisTransform_dummy30,
                    &BridgeDebrisNode_dummy30,
                &BridgeDebrisTransform_dummy31,
                    &BridgeDebrisNode_dummy31,
                &BridgeDebrisTransform_dummy32,
                    &BridgeDebrisNode_dummy32,
    nullptr
};
