#include "kpa_70.h"

StaticAnimatorNode N(ChainDriveNode_m03) = {
    .pos = { 0.0f, 150.0f, 0.0f },
    .modelID = AS_MODEL_ID(MODEL_m03),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(ChainDriveNode_m02) = {
    .pos = { 69.0f, 250.0f, 0.0f },
    .sibling = &N(ChainDriveNode_m03),
    .modelID = AS_MODEL_ID(MODEL_m02),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(ChainDriveNode_m01) = {
    .pos = { 106.0f, 9.0f, 0.0f },
    .sibling = &N(ChainDriveNode_m02),
    .modelID = AS_MODEL_ID(MODEL_m01),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(ChainDriveNode_b03) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .sibling = &N(ChainDriveNode_m01),
    .modelID = AS_MODEL_ID(MODEL_b03),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(ChainDriveNode_b02) = {
    .pos = { 0.0f, 150.0f, 0.0f },
    .sibling = &N(ChainDriveNode_b03),
    .modelID = AS_MODEL_ID(MODEL_b02),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(ChainDriveNode_b01) = {
    .pos = { 30.0f, 180.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-89.99725f) },
    .sibling = &N(ChainDriveNode_b02),
    .modelID = AS_MODEL_ID(MODEL_b01),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(ChainDriveNode_k02) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .sibling = &N(ChainDriveNode_b01),
    .modelID = AS_MODEL_ID(MODEL_k02),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(ChainDriveNode_k01) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .sibling = &N(ChainDriveNode_k02),
    .modelID = AS_MODEL_ID(MODEL_k01),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode N(ChainDriveRoot) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .child = &N(ChainDriveNode_k01),
};

StaticAnimatorNode* N(ChainDriveSkeleton)[] = {
    &N(ChainDriveRoot),
        &N(ChainDriveNode_k01),
        &N(ChainDriveNode_k02),
        &N(ChainDriveNode_b01),
        &N(ChainDriveNode_b02),
        &N(ChainDriveNode_b03),
        &N(ChainDriveNode_m01),
        &N(ChainDriveNode_m02),
        &N(ChainDriveNode_m03),
    nullptr
};
