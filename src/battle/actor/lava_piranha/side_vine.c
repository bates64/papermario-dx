#include "lava_piranha.h"

static StaticAnimatorNode Node07 = {
    .displayList = &Node07,
    .rot = { 0, 0, 13020 },
    .pos = { 62.0f, 53.0f, -20.0f },
};

static StaticAnimatorNode Node06 = {
    .displayList = &Node07,
    .rot = { 0, 0, 13067 },
    .pos = { 97.0f, 51.0f, -20.0f },
    .sibling = &Node07,
};

static StaticAnimatorNode Node05 = {
    .displayList = &Node07,
    .rot = { 0, 0, -10126 },
    .pos = { 75.0f, 19.0f, -20.0f },
    .sibling = &Node06,
};

static StaticAnimatorNode Node04 = {
    .displayList = &Node07,
    .rot = { 0, 0, 122 },
    .pos = { 69.0f, -19.0f, -20.0f },
    .sibling = &Node05,
};

static StaticAnimatorNode Node03 = {
    .displayList = &Node07,
    .rot = { 0, 0, 24663 },
    .pos = { 76.0f, 62.0f, -21.0f },
    .sibling = &Node04,
};

static StaticAnimatorNode Node02 = {
    .displayList = &Node07,
    .rot = { 0, 0, 1470 },
    .pos = { 96.0f, 28.0f, -21.0f },
    .sibling = &Node03,
};

static StaticAnimatorNode Node01 = {
    .displayList = &Node07,
    .rot = { 0, 0, -5339 },
    .pos = { 67.0f, 0.0f, -21.0f },
    .sibling = &Node02,
};

static StaticAnimatorNode Root = {
    .child = &Node01,
};

StaticAnimatorNode* SideHeadVineModel[] = {
    &Root,
    &Node01,
    &Node02,
    &Node03,
    &Node04,
    &Node05,
    &Node06,
    &Node07,
    nullptr,
};
