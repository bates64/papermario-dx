#include "kpa_14.h"

s32 get_tattle(void) {
    if (!evt_get_variable(nullptr, GF_KPA16_ShutOffLava)) {
        return MSG_MapTattle_kpa_14_before;
    } else {
        return MSG_MapTattle_kpa_14_after;
    }
}

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .tattle = { .get = &get_tattle },
    .songVariation = 1,
    .sfxReverb = 3,
};
