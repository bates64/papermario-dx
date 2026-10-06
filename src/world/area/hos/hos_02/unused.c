#include "hos_02.h"

API_CALLABLE(FetchEntryID) {
    script->varTable[0] = gGameStatusPtr->entryID;
    return ApiStatus_DONE2;
}

EvtScript EVS_SetupUnused = {
    Return
    End
};
