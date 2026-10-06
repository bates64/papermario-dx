#include "animation_script.h"

StaticAnimatorNode D_802433B0_C90F60 = {
    .pos = { 132.0, -5.0, -5.0 },
    .rot = { AS_F(0.0), AS_F(0.0), AS_F(165.157013) },
    .displayList = &D_802433B0_C90F60,
};

StaticAnimatorNode D_802433DC_C90F8C = {
    .pos = { 98.0, 4.0, -5.0 },
    .rot = { AS_F(0.0), AS_F(0.0), AS_F(-80.120239) },
    .sibling = &D_802433B0_C90F60,
    .displayList = &D_802433B0_C90F60,
};

StaticAnimatorNode D_80243408_C90FB8 = {
    .pos = { 129.0, -26.0, -6.0 },
    .rot = { AS_F(0.0), AS_F(0.0), AS_F(125.160072) },
    .sibling = &D_802433DC_C90F8C,
    .displayList = &D_802433B0_C90F60,
};

StaticAnimatorNode D_80243434_C90FE4 = {
    .pos = { 120.0, 12.0, -6.0 },
    .rot = { AS_F(0.0), AS_F(0.0), AS_F(-154.983368) },
    .sibling = &D_80243408_C90FB8,
    .displayList = &D_802433B0_C90F60,
};

StaticAnimatorNode D_80243460_C91010 = {
    .pos = { 87.0, -13.0, -6.0 },
    .rot = { AS_F(0.0), AS_F(0.0), AS_F(-39.749748) },
    .sibling = &D_80243434_C90FE4,
    .displayList = &D_802433B0_C90F60,
};

StaticAnimatorNode D_8024348C_C9103C = {
    .pos = { 0.0, 0.0, 0.0 },
    .rot = { AS_F(0.0), AS_F(0.0), AS_F(0.0) },
    .child = &D_80243460_C91010,
};

StaticAnimatorNode* AnimModel_ExtraVine[] = {
    &D_8024348C_C9103C, &D_80243460_C91010, &D_80243434_C90FE4, &D_80243408_C90FB8,
    &D_802433DC_C90F8C, &D_802433B0_C90F60, nullptr, nullptr
};
