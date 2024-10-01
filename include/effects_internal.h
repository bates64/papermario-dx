#ifndef _EFFECTS_INTERNAL_H_
#define _EFFECTS_INTERNAL_H_

#include "effects.h"

// slimmed down assert so that all effects still fit under the TLB page size limit of 0x1000 bytes
#define ASSERT(condition) \
    if (!(condition)) { \
        IS_DEBUG_PANIC("Assert", __FILE_NAME__, __LINE__, NULL); \
    }

s32 effect_rand_int(s32);
s32 effect_simple_rand(s32, s32);

#include "effect_shims.h"

#endif
