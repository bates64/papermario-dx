#include "hos_00.h"

export s32 map_init(void) {
    if (gGameStatusPtr->entryID == hos_00_ENTRY_3) {
        sprintf(wMapBgName, "hos_bg");
    }
    return false;
}

EntryList Entrances = {
    [hos_00_ENTRY_0]    { -610.0,    0.0,  -45.0,   90.0 },
    [hos_00_ENTRY_1]    {  870.0,   60.0, -130.0,  270.0 },
    [hos_00_ENTRY_2]    {  870.0,  -10.0,   30.0,  270.0 },
    [hos_00_ENTRY_3]    {  870.0,  -10.0,   30.0,  270.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "nok_bg",
    .tattle = { MSG_MapTattle_hos_00 },
};
