#include "lava_piranha.h"
#include "animation_script.h"

static StaticAnimatorNode Node05 = {
    .displayList = &Node05,
    .rot = { 0, 0, AS_F(165.157) },
    .pos = { 132.0f, -5.0f, -5.0f },
};

static StaticAnimatorNode Node04 = {
    .displayList = &Node05,
    .rot = { 0, 0, AS_F(-80.120) },
    .pos = { 98.0f, 4.0f, -5.0f },
    .sibling = &Node05,
};

static StaticAnimatorNode Node03 = {
    .displayList = &Node05,
    .rot = { 0, 0, AS_F(125.160) },
    .pos = { 129.0f, -26.0f, -6.0f },
    .sibling = &Node04,
};

static StaticAnimatorNode Node02 = {
    .displayList = &Node05,
    .rot = { 0, 0, AS_F(-154.983) },
    .pos = { 120.0f, 12.0f, -6.0f },
    .sibling = &Node03,
};

static StaticAnimatorNode Node01 = {
    .displayList = &Node05,
    .rot = { 0, 0, AS_F(-39.749) },
    .pos = { 87.0f, -13.0f, -6.0f },
    .sibling = &Node02,
};

static StaticAnimatorNode Root = {
    .child = &Node01,
};

StaticAnimatorNode* ExtraVineModel[] = {
    &Root,
    &Node01,
    &Node02,
    &Node03,
    &Node04,
    &Node05,
    nullptr,
};
