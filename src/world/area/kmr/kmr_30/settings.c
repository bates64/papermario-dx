#include "kmr_30.h"

EntryList Entrances = {
    [kmr_30_ENTRY_0]    {    0.0,    0.0,    0.0,    0.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
};
