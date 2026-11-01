#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../obk.h"
#include "obk_09.h"

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .tattle = { MSG_MapTattle_obk_09 },
    .songVariation = 1,
    .sfxReverb = 2,
};
