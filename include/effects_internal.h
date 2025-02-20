#pragma once

#include "effects.h"

// slimmed down assert so that all effects still fit under the TLB page size limit of 0x1000 bytes
#undef ASSERT
#define ASSERT(condition) \
    if (!(condition)) { \
        IS_DEBUG_PANIC("ASSERT"); \
    }

s32 effect_rand_int(s32);
s32 effect_simple_rand(s32, s32);

#include "effect_shims.h"
