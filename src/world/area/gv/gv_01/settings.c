#include "gv_01.h"

EntryList Entrances = {
    [gv_01_ENTRY_0]     {    0.0,    0.0,    0.0,   90.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
};
