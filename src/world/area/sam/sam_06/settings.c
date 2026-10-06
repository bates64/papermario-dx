#include "sam_06.h"

EntryList Entrances = {
    [sam_06_ENTRY_0]    { -340.0,    0.0,  340.0,   45.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "sam_bg",
    .tattle = { MSG_MapTattle_sam_06 },
};
