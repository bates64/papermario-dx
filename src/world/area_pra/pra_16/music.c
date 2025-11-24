#include "pra_16.h"

EvtScript N(EVS_SetupMusic) = {
    Call(SetMusic, 0, SONG_CRYSTAL_PALACE, 0, 8)
    Return
    End
};
