#include "mim_07.h"

EvtScript N(EVS_PlayForestMusic) = {
    Call(SetMusic, 0, SONG_FOREVER_FOREST, 0, 8)
    Call(PlayAmbientSounds, AMBIENT_SPOOKY)
    Return
    End
};

EvtScript N(EVS_JrTroopaMusic) = {
    Call(SetMusic, 0, SONG_JR_TROOPA_THEME, 0, 8)
    Return
    End
};
