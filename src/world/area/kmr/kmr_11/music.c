#include "kmr_11.h"

EvtScript EVS_SetupMusic = {
    Call(SetMusic, 0, SONG_PLEASANT_PATH, 0, VOL_LEVEL_FULL)
    Return
    End
};
