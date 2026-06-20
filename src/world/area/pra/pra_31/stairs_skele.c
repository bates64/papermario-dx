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
s32 N(post_gfx_pad)[] = { 0, 0, 0, 0 };

StaticAnimatorNode N(StairsNode35) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = &N(unk_29_gfx),
};

StaticAnimatorNode N(StairsNode34) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .child = &N(StairsNode35),
};

StaticAnimatorNode N(StairsNode33) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = &N(unk_28_gfx),
};

StaticAnimatorNode N(StairsNode32) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .child = &N(StairsNode33),
    .sibling = &N(StairsNode34),
};

StaticAnimatorNode N(StairsNode31) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = &N(unk_27_gfx),
};

StaticAnimatorNode N(StairsNode30) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .child = &N(StairsNode31),
    .sibling = &N(StairsNode32),
};

StaticAnimatorNode N(StairsNode29) = {
    .pos = { 500.0f, 50.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(89.99725f) },
    .child = &N(StairsNode30),
};

StaticAnimatorNode N(StairsNode28) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = &N(unk_25_gfx),
};

StaticAnimatorNode N(StairsNode27) = {
    .pos = { 420.0f, 50.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-89.99725f) },
    .child = &N(StairsNode28),
    .sibling = &N(StairsNode29),
};

StaticAnimatorNode N(StairsNode26) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = &N(unk_21_gfx),
};

StaticAnimatorNode N(StairsNode25) = {
    .pos = { 410.0f, 40.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-180.0f) },
    .child = &N(StairsNode26),
    .sibling = &N(StairsNode27),
};

StaticAnimatorNode N(StairsNode24) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = &N(unk_19_gfx),
};

StaticAnimatorNode N(StairsNode23) = {
    .pos = { 400.0f, 40.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-89.99725f) },
    .child = &N(StairsNode24),
    .sibling = &N(StairsNode25),
};

StaticAnimatorNode N(StairsNode22) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = &N(unk_15_gfx),
};

StaticAnimatorNode N(StairsNode21) = {
    .pos = { 390.0f, 30.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-180.0f) },
    .child = &N(StairsNode22),
    .sibling = &N(StairsNode23),
};

StaticAnimatorNode N(StairsNode20) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = &N(unk_13_gfx),
};

StaticAnimatorNode N(StairsNode19) = {
    .pos = { 380.0f, 30.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-89.99725f) },
    .child = &N(StairsNode20),
    .sibling = &N(StairsNode21),
};

StaticAnimatorNode N(StairsNode18) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = &N(unk_11_gfx),
};

StaticAnimatorNode N(StairsNode17) = {
    .pos = { 380.0f, 20.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(89.99725f) },
    .child = &N(StairsNode18),
    .sibling = &N(StairsNode19),
};

StaticAnimatorNode N(StairsNode16) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = &N(unk_09_gfx),
};

StaticAnimatorNode N(StairsNode15) = {
    .pos = { 370.0f, 20.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-180.0f) },
    .child = &N(StairsNode16),
    .sibling = &N(StairsNode17),
};

StaticAnimatorNode N(StairsNode14) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = &N(unk_07_gfx),
};

StaticAnimatorNode N(StairsNode13) = {
    .pos = { 360.0f, 20.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-89.99725f) },
    .child = &N(StairsNode14),
    .sibling = &N(StairsNode15),
};

StaticAnimatorNode N(StairsNode12) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = &N(unk_05_gfx),
};

StaticAnimatorNode N(StairsNode11) = {
    .pos = { 360.0f, 10.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(89.99725f) },
    .child = &N(StairsNode12),
    .sibling = &N(StairsNode13),
};

StaticAnimatorNode N(StairsNode10) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = &N(unk_03_gfx),
};

StaticAnimatorNode N(StairsNode09) = {
    .pos = { 350.0f, 10.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-180.0f) },
    .child = &N(StairsNode10),
    .sibling = &N(StairsNode11),
};

StaticAnimatorNode N(StairsNode08) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = &N(unk_01_gfx),
};

StaticAnimatorNode N(StairsNode07) = {
    .pos = { 340.0f, 10.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(-89.99725f) },
    .child = &N(StairsNode08),
    .sibling = &N(StairsNode09),
};

StaticAnimatorNode N(StairsNode06) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = &N(unk_17_gfx),
};

StaticAnimatorNode N(StairsNode05) = {
    .pos = { 400.0f, 30.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(89.99725f) },
    .child = &N(StairsNode06),
    .sibling = &N(StairsNode07),
};

StaticAnimatorNode N(StairsNode04) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .displayList = &N(unk_23_gfx),
};

StaticAnimatorNode N(StairsNode03) = {
    .pos = { 420.0f, 40.0f, 0.0f },
    .rot = { AS_F(0.0f), AS_F(0.0f), AS_F(89.99725f) },
    .child = &N(StairsNode04),
    .sibling = &N(StairsNode05),
};

StaticAnimatorNode N(StairsNode02) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .child = &N(StairsNode03),
};

StaticAnimatorNode N(StairsNode01) = {
    .pos = { 0.0f, 0.0f, 0.0f },
    .child = &N(StairsNode02),
};

StaticAnimatorNode* N(AS_Stairs_Skeleton)[] = {
    &N(StairsNode01),
        &N(StairsNode02),
            &N(StairsNode03),
                &N(StairsNode04),
            &N(StairsNode05),
                &N(StairsNode06),
            &N(StairsNode07),
                &N(StairsNode08),
            &N(StairsNode09),
                &N(StairsNode10),
            &N(StairsNode11),
                &N(StairsNode12),
            &N(StairsNode13),
                &N(StairsNode14),
            &N(StairsNode15),
                &N(StairsNode16),
            &N(StairsNode17),
                &N(StairsNode18),
            &N(StairsNode19),
                &N(StairsNode20),
            &N(StairsNode21),
                &N(StairsNode22),
            &N(StairsNode23),
                &N(StairsNode24),
            &N(StairsNode25),
                &N(StairsNode26),
            &N(StairsNode27),
                &N(StairsNode28),
            &N(StairsNode29),
                &N(StairsNode30),
                    &N(StairsNode31),
                &N(StairsNode32),
                    &N(StairsNode33),
                &N(StairsNode34),
                    &N(StairsNode35),
    nullptr
};
