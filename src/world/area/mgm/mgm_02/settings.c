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

EntryList Entrances = {
    [mgm_02_ENTRY_0]    { -300.0,  200.0,  200.0,   90.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
#if VERSION_PAL
    .tattle = { .get = &get_tattle },
#else
    .tattle = { MSG_MapTattle_mgm_02 },
#endif
};
