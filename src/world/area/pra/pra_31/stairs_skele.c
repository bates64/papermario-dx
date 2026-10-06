#include "pra_31.h"

#include "world/area/pra/pra_31/unk_01.gfx.inc.c"
#include "world/area/pra/pra_31/unk_02.gfx.inc.c"
#include "world/area/pra/pra_31/unk_03.gfx.inc.c"
#include "world/area/pra/pra_31/unk_04.gfx.inc.c"
#include "world/area/pra/pra_31/unk_05.gfx.inc.c"
#include "world/area/pra/pra_31/unk_06.gfx.inc.c"
#include "world/area/pra/pra_31/unk_07.gfx.inc.c"
#include "world/area/pra/pra_31/unk_08.gfx.inc.c"
#include "world/area/pra/pra_31/unk_09.gfx.inc.c"
#include "world/area/pra/pra_31/unk_10.gfx.inc.c"
#include "world/area/pra/pra_31/unk_11.gfx.inc.c"
#include "world/area/pra/pra_31/unk_12.gfx.inc.c"
#include "world/area/pra/pra_31/unk_13.gfx.inc.c"
#include "world/area/pra/pra_31/unk_14.gfx.inc.c"
#include "world/area/pra/pra_31/unk_15.gfx.inc.c"
#include "world/area/pra/pra_31/unk_16.gfx.inc.c"
#include "world/area/pra/pra_31/unk_17.gfx.inc.c"
#include "world/area/pra/pra_31/unk_18.gfx.inc.c"
#include "world/area/pra/pra_31/unk_19.gfx.inc.c"
#include "world/area/pra/pra_31/unk_20.gfx.inc.c"
#include "world/area/pra/pra_31/unk_21.gfx.inc.c"
#include "world/area/pra/pra_31/unk_22.gfx.inc.c"
#include "world/area/pra/pra_31/unk_23.gfx.inc.c"
#include "world/area/pra/pra_31/unk_24.gfx.inc.c"
#include "world/area/pra/pra_31/unk_25.gfx.inc.c"
#include "world/area/pra/pra_31/unk_26.gfx.inc.c"
#include "world/area/pra/pra_31/unk_27.gfx.inc.c"
#include "world/area/pra/pra_31/unk_28.gfx.inc.c"
#include "world/area/pra/pra_31/unk_29.gfx.inc.c"
#include "world/area/pra/pra_31/unk_30.gfx.inc.c"
#include "world/area/pra/pra_31/unk_31.gfx.inc.c"
#include "world/area/pra/pra_31/unk_32.gfx.inc.c"
#include "world/area/pra/pra_31/unk_33.gfx.inc.c"
#include "world/area/pra/pra_31/unk_34.gfx.inc.c"

// 0x10 long, doesnt seem to indicate a split
s32 post_gfx_pad[] = { 0, 0, 0, 0 };

StaticAnimatorNode StairsNode35 = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = &pra_31_unk_29_gfx,
};

StaticAnimatorNode StairsNode34 = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .child = &StairsNode35,
};

StaticAnimatorNode StairsNode33 = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = &pra_31_unk_28_gfx,
};

StaticAnimatorNode StairsNode32 = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .child = &StairsNode33,
    .sibling = &StairsNode34,
};

StaticAnimatorNode StairsNode31 = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = &pra_31_unk_27_gfx,
};

StaticAnimatorNode StairsNode30 = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .child = &StairsNode31,
    .sibling = &StairsNode32,
};

StaticAnimatorNode StairsNode29 = {
    .pos = { 500.0f, 50.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(89.99725f) },
    .child = &StairsNode30,
};

StaticAnimatorNode StairsNode28 = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = &pra_31_unk_25_gfx,
};

StaticAnimatorNode StairsNode27 = {
    .pos = { 420.0f, 50.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-89.99725f) },
    .child = &StairsNode28,
    .sibling = &StairsNode29,
};

StaticAnimatorNode StairsNode26 = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = &pra_31_unk_21_gfx,
};

StaticAnimatorNode StairsNode25 = {
    .pos = { 410.0f, 40.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-180.0f) },
    .child = &StairsNode26,
    .sibling = &StairsNode27,
};

StaticAnimatorNode StairsNode24 = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = &pra_31_unk_19_gfx,
};

StaticAnimatorNode StairsNode23 = {
    .pos = { 400.0f, 40.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-89.99725f) },
    .child = &StairsNode24,
    .sibling = &StairsNode25,
};

StaticAnimatorNode StairsNode22 = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = &pra_31_unk_15_gfx,
};

StaticAnimatorNode StairsNode21 = {
    .pos = { 390.0f, 30.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-180.0f) },
    .child = &StairsNode22,
    .sibling = &StairsNode23,
};

StaticAnimatorNode StairsNode20 = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = &pra_31_unk_13_gfx,
};

StaticAnimatorNode StairsNode19 = {
    .pos = { 380.0f, 30.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-89.99725f) },
    .child = &StairsNode20,
    .sibling = &StairsNode21,
};

StaticAnimatorNode StairsNode18 = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = &pra_31_unk_11_gfx,
};

StaticAnimatorNode StairsNode17 = {
    .pos = { 380.0f, 20.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(89.99725f) },
    .child = &StairsNode18,
    .sibling = &StairsNode19,
};

StaticAnimatorNode StairsNode16 = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = &pra_31_unk_09_gfx,
};

StaticAnimatorNode StairsNode15 = {
    .pos = { 370.0f, 20.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-180.0f) },
    .child = &StairsNode16,
    .sibling = &StairsNode17,
};

StaticAnimatorNode StairsNode14 = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = &pra_31_unk_07_gfx,
};

StaticAnimatorNode StairsNode13 = {
    .pos = { 360.0f, 20.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-89.99725f) },
    .child = &StairsNode14,
    .sibling = &StairsNode15,
};

StaticAnimatorNode StairsNode12 = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = &pra_31_unk_05_gfx,
};

StaticAnimatorNode StairsNode11 = {
    .pos = { 360.0f, 10.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(89.99725f) },
    .child = &StairsNode12,
    .sibling = &StairsNode13,
};

StaticAnimatorNode StairsNode10 = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = &pra_31_unk_03_gfx,
};

StaticAnimatorNode StairsNode09 = {
    .pos = { 350.0f, 10.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-180.0f) },
    .child = &StairsNode10,
    .sibling = &StairsNode11,
};

StaticAnimatorNode StairsNode08 = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = &pra_31_unk_01_gfx,
};

StaticAnimatorNode StairsNode07 = {
    .pos = { 340.0f, 10.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-89.99725f) },
    .child = &StairsNode08,
    .sibling = &StairsNode09,
};

StaticAnimatorNode StairsNode06 = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = &pra_31_unk_17_gfx,
};

StaticAnimatorNode StairsNode05 = {
    .pos = { 400.0f, 30.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(89.99725f) },
    .child = &StairsNode06,
    .sibling = &StairsNode07,
};

StaticAnimatorNode StairsNode04 = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = &pra_31_unk_23_gfx,
};

StaticAnimatorNode StairsNode03 = {
    .pos = { 420.0f, 40.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(89.99725f) },
    .child = &StairsNode04,
    .sibling = &StairsNode05,
};

StaticAnimatorNode StairsNode02 = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .child = &StairsNode03,
};

StaticAnimatorNode StairsNode01 = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .child = &StairsNode02,
};

StaticAnimatorNode* AS_Stairs_Skeleton[] = {
    &StairsNode01,
        &StairsNode02,
            &StairsNode03,
                &StairsNode04,
            &StairsNode05,
                &StairsNode06,
            &StairsNode07,
                &StairsNode08,
            &StairsNode09,
                &StairsNode10,
            &StairsNode11,
                &StairsNode12,
            &StairsNode13,
                &StairsNode14,
            &StairsNode15,
                &StairsNode16,
            &StairsNode17,
                &StairsNode18,
            &StairsNode19,
                &StairsNode20,
            &StairsNode21,
                &StairsNode22,
            &StairsNode23,
                &StairsNode24,
            &StairsNode25,
                &StairsNode26,
            &StairsNode27,
                &StairsNode28,
            &StairsNode29,
                &StairsNode30,
                    &StairsNode31,
                &StairsNode32,
                    &StairsNode33,
                &StairsNode34,
                    &StairsNode35,
    nullptr
};
