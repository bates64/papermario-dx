#include "kkj_27.h"

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
#if VERSION_JP
    .tattle = { MSG_MapTattle_018A },
#endif
    .sfxReverb = 1,
};
