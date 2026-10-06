#include "flo_21.h"

EntryList Entrances = {
    [flo_21_ENTRY_0]    { -800.0,  -46.0,    0.0,   90.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "sra_bg",
    .tattle = { MSG_MapTattle_flo_21 },
};
