#include "hos_20.h"

EntryList Entrances = {
    [hos_20_ENTRY_0]    { -400.0,    0.0,    0.0,  135.0 },
    [hos_20_ENTRY_1]    {    0.0,    0.0,    0.0,  135.0 },
    [hos_20_ENTRY_2]    {  400.0,    0.0,    0.0,  225.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
};
