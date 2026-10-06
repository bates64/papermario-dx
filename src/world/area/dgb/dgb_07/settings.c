#include "dgb_07.h"

EntryList Entrances = {
    [dgb_07_ENTRY_0]    { -450.0,    0.0,  -40.0,    0.0 },
    [dgb_07_ENTRY_1]    {  250.0,  190.0, -250.0,  180.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_dgb_07 },
    .songVariation = 1,
    .sfxReverb = 2,
};
