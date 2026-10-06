#include "iwa_04.h"

EvtScript EVS_SetupMusic = {
    Call(SetMusic, 0, SONG_MT_RUGGED, 0, VOL_LEVEL_FULL)
    Return
    End
};
