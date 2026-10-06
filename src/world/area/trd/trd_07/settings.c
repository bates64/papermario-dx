#include "trd_07.h"

extern EvtScript EVS_Main;

EntryList Entrances = {
    [trd_07_ENTRY_0]    {  220.0,    0.0,    0.0,  270.0 },
    [trd_07_ENTRY_1]    { -200.0,    0.0,    0.0,   90.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_trd_07 },
    .songVariation = 1,
    .sfxReverb = 3,
};

EvtScript EVS_SetupMusic = {
    Call(SetMusic, 0, SONG_KOOPA_FORTRESS, 0, VOL_LEVEL_FULL)
    Call(UseDoorSounds, DOOR_SOUNDS_METAL)
    Return
    End
};
