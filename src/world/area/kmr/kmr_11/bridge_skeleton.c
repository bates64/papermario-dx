#include "kmr_11.h"

StaticAnimatorNode N(BridgeDebrisNode_dummy32) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .modelID = AS_MODEL_ID(MODEL_dummy32),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(BridgeDebrisTransform_dummy32) = {
    .pos = { -159.0f, 0.0f, -126.0f },
    .child = &N(BridgeDebrisNode_dummy32),
};

StaticAnimatorNode N(BridgeDebrisNode_dummy31) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .modelID = AS_MODEL_ID(MODEL_dummy31),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(BridgeDebrisTransform_dummy31) = {
    .pos = { -159.0f, 0.0f, -126.0f },
    .child = &N(BridgeDebrisNode_dummy31),
    .sibling = &N(BridgeDebrisTransform_dummy32),
};

StaticAnimatorNode N(BridgeDebrisNode_dummy30) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .modelID = AS_MODEL_ID(MODEL_dummy30),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(BridgeDebrisTransform_dummy30) = {
    .pos = { -159.0f, 0.0f, -126.0f },
    .child = &N(BridgeDebrisNode_dummy30),
    .sibling = &N(BridgeDebrisTransform_dummy31),
};

StaticAnimatorNode N(BridgeDebrisGroup_dummy30) = {
    .pos = { 140.0f, -10.0f, -360.0f },
    .rot = { AS_F(0.0f), AS_F(-180.0f), AS_F(0.0f) },
    .child = &N(BridgeDebrisTransform_dummy30),
};

StaticAnimatorNode N(BridgeDebrisNode_dummy3) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .modelID = AS_MODEL_ID(MODEL_dummy3),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(BridgeDebrisTransform_dummy3) = {
    .pos = { -159.0f, 0.0f, -126.0f },
    .child = &N(BridgeDebrisNode_dummy3),
};

StaticAnimatorNode N(BridgeDebrisNode_dummy2) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .modelID = AS_MODEL_ID(MODEL_dummy2),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(BridgeDebrisTransform_dummy2) = {
    .pos = { -159.0f, 0.0f, -126.0f },
    .child = &N(BridgeDebrisNode_dummy2),
    .sibling = &N(BridgeDebrisTransform_dummy3),
};

StaticAnimatorNode N(BridgeDebrisNode_dummy1) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .modelID = AS_MODEL_ID(MODEL_dummy1),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(BridgeDebrisTransform_dummy1) = {
    .pos = { -159.0f, 0.0f, -126.0f },
    .child = &N(BridgeDebrisNode_dummy1),
    .sibling = &N(BridgeDebrisTransform_dummy2),
};

StaticAnimatorNode N(BridgeDebrisGroup_dummy1) = {
    .pos = { 0.0f, -10.0f, 0.0f },
    .child = &N(BridgeDebrisTransform_dummy1),
    .sibling = &N(BridgeDebrisGroup_dummy30),
};

StaticAnimatorNode N(BridgeDebrisRoot) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .child = &N(BridgeDebrisGroup_dummy1),
};

StaticAnimatorNode N(BridgeDummyNode) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(-12.695089f), AS_F(0.0f) },
    .modelID = AS_MODEL_ID(MODEL_dummy),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(BridgeDummyTransform) = {
    .pos = { 0.0f, 110.0f, 0.0f },
    .child = &N(BridgeDummyNode),
};

StaticAnimatorNode N(BridgeSegmentNode_b1) = {
    .pos = { -237.0f, 109.0f, 155.0f },
    .rot = { AS_F(0.0f), AS_F(-12.695089f), AS_F(-179.9945f) },
    .modelID = AS_MODEL_ID(MODEL_b1),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(BridgeSegmentNode_b2) = {
    .pos = { 312.0f, -169.0f, 155.0f },
    .rot = { AS_F(0.0f), AS_F(-12.695089f), AS_F(0.0f) },
    .modelID = AS_MODEL_ID(MODEL_b2),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(BridgeSegmentNode_b3) = {
    .pos = { -237.0f, 169.0f, 155.0f },
    .rot = { AS_F(0.0f), AS_F(-12.695089f), AS_F(-179.9945f) },
    .modelID = AS_MODEL_ID(MODEL_b3),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(BridgeSegmentNode_b4) = {
    .pos = { 312.0f, -229.0f, 155.0f },
    .rot = { AS_F(0.0f), AS_F(-12.695089f), AS_F(0.0f) },
    .modelID = AS_MODEL_ID(MODEL_b4),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(BridgeSegmentNode_b5) = {
    .pos = { -237.0f, 229.0f, 155.0f },
    .rot = { AS_F(0.0f), AS_F(-12.695089f), AS_F(-179.9945f) },
    .modelID = AS_MODEL_ID(MODEL_b5),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(BridgeSegmentNode_b6) = {
    .pos = { 312.0f, -289.0f, 155.0f },
    .rot = { AS_F(0.0f), AS_F(-12.695089f), AS_F(0.0f) },
    .modelID = AS_MODEL_ID(MODEL_b6),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(BridgeSegmentRigNode16) = {
    .pos = { 75.0f, 0.0f, 0.0f },
    .sibling = &N(BridgeSegmentNode_b6),
};

StaticAnimatorNode N(BridgeSegmentRigNode15) = {
    .pos = { 30.0f, 0.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-89.99725f) },
    .child = &N(BridgeSegmentRigNode16),
};

StaticAnimatorNode N(BridgeSegmentRigNode14) = {
    .pos = { 30.0f, 0.0f, 0.0f },
    .child = &N(BridgeSegmentRigNode15),
};

StaticAnimatorNode N(BridgeSegmentRigNode13) = {
    .pos = { 75.0f, 0.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-89.99725f) },
    .child = &N(BridgeSegmentRigNode14),
    .sibling = &N(BridgeSegmentNode_b5),
};

StaticAnimatorNode N(BridgeSegmentRigNode12) = {
    .pos = { 75.0f, 0.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(179.9945f) },
    .child = &N(BridgeSegmentRigNode13),
    .sibling = &N(BridgeSegmentNode_b4),
};

StaticAnimatorNode N(BridgeSegmentRigNode11) = {
    .pos = { 30.0f, 0.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-89.99725f) },
    .child = &N(BridgeSegmentRigNode12),
};

StaticAnimatorNode N(BridgeSegmentRigNode10) = {
    .pos = { 30.0f, 0.0f, 0.0f },
    .child = &N(BridgeSegmentRigNode11),
};

StaticAnimatorNode N(BridgeSegmentRigNode09) = {
    .pos = { 75.0f, 0.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-89.99725f) },
    .child = &N(BridgeSegmentRigNode10),
    .sibling = &N(BridgeSegmentNode_b3),
};

StaticAnimatorNode N(BridgeSegmentRigNode08) = {
    .pos = { 75.0f, 0.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(179.9945f) },
    .child = &N(BridgeSegmentRigNode09),
    .sibling = &N(BridgeSegmentNode_b2),
};

StaticAnimatorNode N(BridgeSegmentRigNode07) = {
    .pos = { 30.0f, 0.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-89.99725f) },
    .child = &N(BridgeSegmentRigNode08),
};

StaticAnimatorNode N(BridgeSegmentRigNode06) = {
    .pos = { 30.0f, 0.0f, 0.0f },
    .child = &N(BridgeSegmentRigNode07),
};

StaticAnimatorNode N(BridgeSegmentRigNode05) = {
    .pos = { 75.0f, 0.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-89.99725f) },
    .child = &N(BridgeSegmentRigNode06),
    .sibling = &N(BridgeSegmentNode_b1),
};

StaticAnimatorNode N(BridgeSegmentRigRoot) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(179.9945f) },
    .child = &N(BridgeSegmentRigNode05),
};

StaticAnimatorNode N(BridgeSegmentAssembly) = {
    .pos = { 0.0f, 110.0f, 0.0f },
    .child = &N(BridgeSegmentRigRoot),
    .sibling = &N(BridgeDummyTransform),
};

StaticAnimatorNode N(BridgeAssembly) = {
    .pos = { -266.0f, 0.0f, -99.0f },
    .rot = { AS_F(0.0f), AS_F(12.695089f), AS_F(0.0f) },
    .child = &N(BridgeSegmentAssembly),
    .sibling = &N(BridgeDebrisRoot),
};

StaticAnimatorNode N(BridgeRoot) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .child = &N(BridgeAssembly),
};

StaticAnimatorNode* N(AnimSkeleton_Bridge)[] = {
    &N(BridgeRoot),
        &N(BridgeAssembly),
            &N(BridgeSegmentAssembly),
                &N(BridgeSegmentRigRoot),
                    &N(BridgeSegmentRigNode05),
                        &N(BridgeSegmentRigNode06),
                            &N(BridgeSegmentRigNode07),
                                &N(BridgeSegmentRigNode08),
                                    &N(BridgeSegmentRigNode09),
                                        &N(BridgeSegmentRigNode10),
                                            &N(BridgeSegmentRigNode11),
                                                &N(BridgeSegmentRigNode12),
                                                    &N(BridgeSegmentRigNode13),
                                                        &N(BridgeSegmentRigNode14),
                                                            &N(BridgeSegmentRigNode15),
                                                                &N(BridgeSegmentRigNode16),
                                                                &N(BridgeSegmentNode_b6),
                                                    &N(BridgeSegmentNode_b5),
                                                &N(BridgeSegmentNode_b4),
                                    &N(BridgeSegmentNode_b3),
                                &N(BridgeSegmentNode_b2),
                    &N(BridgeSegmentNode_b1),
            &N(BridgeDummyTransform),
                &N(BridgeDummyNode),
        &N(BridgeDebrisRoot),
            &N(BridgeDebrisGroup_dummy1),
                &N(BridgeDebrisTransform_dummy1),
                    &N(BridgeDebrisNode_dummy1),
                &N(BridgeDebrisTransform_dummy2),
                    &N(BridgeDebrisNode_dummy2),
                &N(BridgeDebrisTransform_dummy3),
                    &N(BridgeDebrisNode_dummy3),
            &N(BridgeDebrisGroup_dummy30),
                &N(BridgeDebrisTransform_dummy30),
                    &N(BridgeDebrisNode_dummy30),
                &N(BridgeDebrisTransform_dummy31),
                    &N(BridgeDebrisNode_dummy31),
                &N(BridgeDebrisTransform_dummy32),
                    &N(BridgeDebrisNode_dummy32),
    nullptr
};
