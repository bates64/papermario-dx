#include "trd_05.h"

extern EvtScript EVS_Main;

EntryList Entrances = {
    [trd_05_ENTRY_0]    { -310.0,    0.0,    0.0,   90.0 },
    [trd_05_ENTRY_1]    {    0.0,    0.0,  310.0,    0.0 },
    [trd_05_ENTRY_2]    {  290.0,    0.0,   30.0,  270.0 },
    [trd_05_ENTRY_3]    { -310.0,  240.0,    0.0,   90.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_trd_05 },
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
