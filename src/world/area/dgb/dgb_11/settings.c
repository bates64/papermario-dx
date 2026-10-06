#include "dgb_11.h"

EntryList Entrances = {
    [dgb_11_ENTRY_0]    {  450.0,    0.0,  -40.0,    0.0 },
    [dgb_11_ENTRY_1]    {  500.0,  180.0, -100.0,  180.0 },
    [dgb_11_ENTRY_2]    {  500.0,  180.0, -250.0,  180.0 },
    [dgb_11_ENTRY_3]    {  375.0,  180.0, -250.0,  180.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_dgb_11 },
    .songVariation = 1,
    .sfxReverb = 2,
};
