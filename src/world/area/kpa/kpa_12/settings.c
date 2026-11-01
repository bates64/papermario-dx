#include "kpa_12.h"

s32 get_tattle(void) {
    if (!evt_get_variable(nullptr, GF_KPA16_ShutOffLava)) {
        return MSG_MapTattle_kpa_12_before;
    } else {
        return MSG_MapTattle_kpa_12_after;
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
