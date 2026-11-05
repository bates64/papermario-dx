#include "mac_04.h"

export s32 map_init(void) {
    if (gGameStatusPtr->entryID == $WishingToad.index) {
        sprintf(wMapBgName, "hos_bg");
    }
    return false;
}
