#include "kmr_12.h"

EvtScript N(EVS_SetupMusic) = {
    Call(SetMusic, 0, SONG_PLEASANT_PATH, 0, 8)
    Return
    End
};
