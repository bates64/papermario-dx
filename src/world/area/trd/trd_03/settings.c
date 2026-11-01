#include "trd_03.h"

extern EvtScript EVS_Main;

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .tattle = { MSG_MapTattle_trd_03 },
    .songVariation = 1,
    .sfxReverb = 3,
};

EvtScript EVS_SetupMusic = {
    Call(SetMusic, 0, SONG_KOOPA_FORTRESS, 0, VOL_LEVEL_FULL)
    Call(UseDoorSounds, DOOR_SOUNDS_METAL)
    Return
    End
};

EvtScript EVS_StartKoopaBrosTheme = {
    Call(FadeInMusic, 1, SONG_KOOPA_BROS_INTERLUDE, 0, 3000, 0, 127)
    Call(FadeOutMusic, 0, 3000)
    Return
    End
};

EvtScript EVS_EndKoopaBrosTheme = {
    Call(FadeInMusic, 0, SONG_KOOPA_FORTRESS, 0, 3000, 0, 127)
    Call(FadeOutMusic, 1, 3000)
    Return
    End
};
