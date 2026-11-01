
#include "jan_00.h"

extern EvtScript EVS_Main;

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .bgName = "yos_bg",
    .tattle = { MSG_MapTattle_jan_00 },
};

EvtScript EVS_80241C10 = {
    Call(SetMusic, 0, SONG_YOSHIS_VILLAGE, 0, VOL_LEVEL_FULL)
    Call(ClearAmbientSounds, 250)
    Return
    End
};
