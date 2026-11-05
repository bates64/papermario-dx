#include "hos_00.h"

export s32 map_init(void) {
    if (gGameStatusPtr->entryID == $StarShip.index) {
        sprintf(wMapBgName, "hos_bg");
    }
    return false;
}
