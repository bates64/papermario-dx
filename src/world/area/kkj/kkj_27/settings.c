#include "kkj_27.h"

EntryList Entrances = {
    [kkj_27_ENTRY_0]    {  425.0,    0.0,   40.0,    0.0 },
    [kkj_27_ENTRY_1]    { -250.0,   10.0,    0.0,    0.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
#if VERSION_JP
    .tattle = { MSG_MapTattle_018A },
#endif
    .sfxReverb = 1,
};
