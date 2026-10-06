#include "osr_01.h"

export s32 map_init(void) {
    if (gGameStatusPtr->entryID == osr_01_ENTRY_3) {
        sprintf(wMapBgName, "hos_bg");
    }
    return false;
}

EntryList Entrances = {
    [osr_01_ENTRY_0]    {    0.0,    0.0,  604.0,    0.0 },
    [osr_01_ENTRY_1]    {  612.0,    0.0,  111.0,  270.0 },
    [osr_01_ENTRY_2]    {    0.0,    0.0, -290.0,  180.0 },
    [osr_01_ENTRY_3]    {    0.0, -1000.0,    0.0,    0.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "nok_bg",
    .tattle = { MSG_MapTattle_osr_01 },
};
