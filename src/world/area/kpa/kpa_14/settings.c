#include "kpa_14.h"

s32 get_tattle(void) {
    if (!evt_get_variable(nullptr, GF_KPA16_ShutOffLava)) {
        return MSG_MapTattle_kpa_14_before;
    } else {
        return MSG_MapTattle_kpa_14_after;
    }
}
