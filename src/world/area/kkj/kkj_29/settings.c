#include "kkj_29.h"

EntryList Entrances = {
    [kkj_29_ENTRY_0]    {  325.0,    0.0,  -30.0,  270.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
#if VERSION_JP
    .tattle = { MSG_MapTattle_018B },
#endif
    .sfxReverb = 1,
};
