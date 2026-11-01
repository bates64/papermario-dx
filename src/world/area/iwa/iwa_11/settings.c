#include "iwa_11.h"

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .bgName = "iwa_bg",
#if VERSION_JP
    .tattle = { MSG_MapTattle_018C }
#endif
};
