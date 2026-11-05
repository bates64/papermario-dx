#include "osr_01.h"

export s32 map_init(void) {
    if (gGameStatusPtr->entryID == $Wishing.index) {
        sprintf(wMapBgName, "hos_bg");
    }
    return false;
}
