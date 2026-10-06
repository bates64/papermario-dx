#include "pra_16.h"

EvtScript EVS_SetupMusic = {
    Call(SetMusic, 0, SONG_CRYSTAL_PALACE, 0, VOL_LEVEL_FULL)
    Return
    End
};
