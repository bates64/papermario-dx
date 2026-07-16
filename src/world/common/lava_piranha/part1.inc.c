enum {
    VINE_0      = 0,
    VINE_1      = 1,
    VINE_2      = 2,
    VINE_3      = 3,
    NUM_VINES   = 4
};

extern Addr D_80200000;
extern Addr D_80204000;
extern Addr D_80207000;
extern Addr D_8020A000;
#define VINE_0_BASE (s32) &D_80200000
#define VINE_1_BASE (s32) &D_80204000
#define VINE_2_BASE (s32) &D_80207000
#define VINE_3_BASE (s32) &D_8020A000

#include "world/common/lava_piranha/skele1.c"
#include "world/common/lava_piranha/skele2.c"
#include "world/common/lava_piranha/skele3.c"
