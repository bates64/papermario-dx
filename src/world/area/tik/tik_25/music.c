#include "tik_25.h"

EvtScript EVS_SetupMusic = {
    Call(SetMusic, 0, SONG_TOAD_TOWN_TUNNELS, 0, VOL_LEVEL_FULL)
    Return
    End
};

EvtScript EVS_PlayUpgradeSong = {
    Call(PushSong, SONG_ITEM_UPGRADE, 1)
    Wait(130)
    Call(PopSong)
    Return
    End
};
