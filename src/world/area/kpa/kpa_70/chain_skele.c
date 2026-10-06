#include "kpa_70.h"

StaticAnimatorNode ChainDriveNode_m03 = {
    .pos = { 0.0f, 150.0f, 0.0f },
    .modelID = AS_MODEL_ID(MODEL_m03),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode ChainDriveNode_m02 = {
    .pos = { 69.0f, 250.0f, 0.0f },
    .sibling = &ChainDriveNode_m03,
    .modelID = AS_MODEL_ID(MODEL_m02),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode ChainDriveNode_m01 = {
    .pos = { 106.0f, 9.0f, 0.0f },
    .sibling = &ChainDriveNode_m02,
    .modelID = AS_MODEL_ID(MODEL_m01),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode ChainDriveNode_b03 = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .sibling = &ChainDriveNode_m01,
    .modelID = AS_MODEL_ID(MODEL_b03),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode ChainDriveNode_b02 = {
    .pos = { 0.0f, 150.0f, 0.0f },
    .sibling = &ChainDriveNode_b03,
    .modelID = AS_MODEL_ID(MODEL_b02),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode ChainDriveNode_b01 = {
    .pos = { 30.0f, 180.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-89.99725f) },
    .sibling = &ChainDriveNode_b02,
    .modelID = AS_MODEL_ID(MODEL_b01),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode ChainDriveNode_k02 = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .sibling = &ChainDriveNode_b01,
    .modelID = AS_MODEL_ID(MODEL_k02),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode ChainDriveNode_k01 = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .sibling = &ChainDriveNode_k02,
    .modelID = AS_MODEL_ID(MODEL_k01),
    .vtxList = 0,
    .vertexStartOffset = -1
};

StaticAnimatorNode ChainDriveRoot = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .child = &ChainDriveNode_k01,
};

StaticAnimatorNode* ChainDriveSkeleton[] = {
    &ChainDriveRoot,
        &ChainDriveNode_k01,
        &ChainDriveNode_k02,
        &ChainDriveNode_b01,
        &ChainDriveNode_b02,
        &ChainDriveNode_b03,
        &ChainDriveNode_m01,
        &ChainDriveNode_m02,
        &ChainDriveNode_m03,
    nullptr
};
