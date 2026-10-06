#include "osr_04.h"

EntryList Entrances = {
    [osr_04_ENTRY_0]    {    0.0,    0.0,  604.0,    0.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "nok_bg",
};
