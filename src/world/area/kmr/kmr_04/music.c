#include "kmr_04.h"

EvtScript EVS_SetNormalMusic = {
    Call(SetMusic, 0, SONG_PLEASANT_PATH, 0, VOL_LEVEL_FULL)
    Return
    End
};

EvtScript EVS_SetJrTroopaMusic = {
    Call(SetMusic, 0, SONG_JR_TROOPA_THEME, 0, VOL_LEVEL_FULL)
    Return
    End
};

EvtScript EVS_PlayUpgradeSong = {
    Call(PushSong, SONG_ITEM_UPGRADE, 0)
    Wait(130)
    Call(PopSong)
    Return
    End
};
