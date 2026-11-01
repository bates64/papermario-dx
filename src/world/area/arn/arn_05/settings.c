
#include "arn_05.h"

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .bgName = "arn_bg",
    .tattle = { MSG_MapTattle_arn_05 },
};
