
#include "jan_00.h"

extern EvtScript EVS_Main;

EntryList Entrances = {
    [jan_00_ENTRY_0]    {  150.0,    0.0,  200.0,    0.0 },
    [jan_00_ENTRY_1]    {  340.0,    0.0,  340.0,  315.0 },
    [jan_00_ENTRY_2]    {  340.0,    0.0, -340.0,  225.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "yos_bg",
    .tattle = { MSG_MapTattle_jan_00 },
};

EvtScript EVS_80241C10 = {
    Call(SetMusic, 0, SONG_YOSHIS_VILLAGE, 0, VOL_LEVEL_FULL)
    Call(ClearAmbientSounds, 250)
    Return
    End
};
