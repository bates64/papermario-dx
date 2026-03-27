#include "flo_21.h"

EntryList N(Entrances) = {
    [flo_21_ENTRY_0]    { -800.0,  -46.0,    0.0,   90.0 },
};

export MapSettings N(settings) = {
    .main = &N(EVS_Main),
    .entryList = &N(Entrances),
    .entryCount = ENTRY_COUNT(N(Entrances)),
    .bgName = "sra_bg",
    .tattle = { MSG_MapTattle_flo_21 },
};
