#include "osr_00.h"

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .bgName = "nok_bg",
#if VERSION_JP
    .tattle = { MSG_MapTattle_0189 },
#endif
};
