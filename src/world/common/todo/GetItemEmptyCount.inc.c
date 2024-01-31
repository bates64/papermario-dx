#include "common.h"

API_CALLABLE(N(GetItemEmptyCount)) {
    script->varTable[1] = get_consumables_empty();

    return ApiStatus_DONE2;
}
