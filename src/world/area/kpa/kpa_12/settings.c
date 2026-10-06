#include "kpa_12.h"

s32 get_tattle(void) {
    if (!evt_get_variable(nullptr, GF_KPA16_ShutOffLava)) {
        return MSG_MapTattle_kpa_12_before;
    } else {
        return MSG_MapTattle_kpa_12_after;
    }
}

EntryList Entrances = {
    [kpa_12_ENTRY_0]    {   30.0,   30.0, -150.0,   90.0 },
    [kpa_12_ENTRY_1]    { 1470.0,   30.0, -150.0,  270.0 },
    [kpa_12_ENTRY_2]    {   17.0,  -20.0,  -17.0,   90.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { .get = &get_tattle },
    .songVariation = 1,
    .sfxReverb = 3,
};
