#include "sam_04.h"

EvtScript EVS_SetupMusic = {
    Call(SetMusic, 0, SONG_SHIVER_SNOWFIELD, 0, VOL_LEVEL_FULL)
    Return
    End
};
