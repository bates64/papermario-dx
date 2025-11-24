#include "mim_02.h"

EvtScript N(EVS_SetupMusic) = {
    Call(SetMusic, 0, SONG_FOREVER_FOREST, 0, 8)
    Call(PlayAmbientSounds, AMBIENT_SPOOKY)
    Return
    End
};
