#include "mac_04.h"

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .bgName = "nok_bg",
    .tattle = { MSG_MapTattle_mac_04 },
};

export s32 map_init(void) {
    if (gGameStatusPtr->entryID == $WishingToad.index) {
        sprintf(wMapBgName, "hos_bg");
    }
    return false;
}
