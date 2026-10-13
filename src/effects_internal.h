#ifndef _EFFECTS_INTERNAL_H_
#define _EFFECTS_INTERNAL_H_

#include "effects.h"

// slimmed down assert so that effect overlays fit within their 0x1000-byte pool slots
#undef ASSERT
#define ASSERT(condition) \
    if (!(condition)) { \
        IS_DEBUG_PANIC("ASSERT"); \
    }

s32 effect_rand_int(s32);
s32 effect_simple_rand(s32, s32);

#define FX_TIME_FOREVER (1000)

#endif
