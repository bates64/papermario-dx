#include "hos_01.h"

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .bgName = "hos_bg",
    .tattle = { MSG_MapTattle_hos_01 },
};
