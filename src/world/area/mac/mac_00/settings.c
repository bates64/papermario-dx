#include "mac_00.h"

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .bgName = "nok_bg",
    .tattle = { MSG_MapTattle_mac_00 },
};
