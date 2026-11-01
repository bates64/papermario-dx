#include "mgm_02.h"

#if VERSION_PAL
s32 get_tattle(void) {
    s32 msgID = MSG_MapTattle_mgm_02;
    if (pal_variable != 0) {
        msgID = MSG_NONE;
    }
    return msgID;
}
#endif

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
#if VERSION_PAL
    .tattle = { .get = &get_tattle },
#else
    .tattle = { MSG_MapTattle_mgm_02 },
#endif
};
