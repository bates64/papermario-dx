#include "common.h"

API_CALLABLE(N(PreventNextPeachDisguise)) {
    gGameStatus.peachFlags |= PEACH_FLAG_BLOCK_NEXT_DISGUISE;
    return ApiStatus_DONE2;
}
