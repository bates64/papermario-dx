#include "kpa_15.h"

#if VERSION_JP
s32 get_tattle(void) {
    if (!evt_get_variable(nullptr, GF_KPA16_ShutOffLava)) {
        return MSG_MapTattle_kpa_15_before;
    } else {
        return MSG_MapTattle_kpa_15_after;
    }
}
#endif

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
#if VERSION_JP
    .tattle = { .get = &get_tattle },
#else
    .tattle = { MSG_MapTattle_kpa_15 },
#endif
    .songVariation = 1,
    .sfxReverb = 3,
};
