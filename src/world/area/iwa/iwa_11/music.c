#include "iwa_11.h"

EvtScript EVS_SetupMusic = {
    Call(SetMusic, 0, SONG_RIDING_THE_RAILS, 0, VOL_LEVEL_FULL)
    Return
    End
};
