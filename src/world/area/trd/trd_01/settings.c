#include "trd_01.h"

extern EvtScript EVS_Main;

EntryList Entrances = {
    [trd_01_ENTRY_0]    { -310.0,    0.0,    0.0,   90.0 },
    [trd_01_ENTRY_1]    {  310.0,    0.0,    0.0,  270.0 },
    [trd_01_ENTRY_2]    {  310.0,  220.0,    0.0,  270.0 },
    [trd_01_ENTRY_3]    {  310.0,  520.0,    0.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_trd_01 },
    .songVariation = 1,
    .sfxReverb = 3,
};

EvtScript EVS_SetupMusic = {
    Call(SetMusic, 0, SONG_KOOPA_FORTRESS, 0, VOL_LEVEL_FULL)
    Call(UseDoorSounds, DOOR_SOUNDS_METAL)
    Return
    End
};
