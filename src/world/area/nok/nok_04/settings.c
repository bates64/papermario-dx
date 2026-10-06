#include "nok_04.h"

EntryList Entrances = {
    [nok_04_ENTRY_0]    { -336.0,    0.0,  356.0,   45.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "nok_bg",
    .tattle = { MSG_MapTattle_nok_04 },
};
