#include "mac_06.h"

EntryList Entrances = {
    [mac_06_ENTRY_0]    {    0.0,    0.0,  100.0,   90.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "nok_bg",
};
