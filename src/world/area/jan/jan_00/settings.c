#include "jan_00.h"

extern EvtScript EVS_Main;

EvtScript EVS_80241C10 = {
    Call(SetMusic, 0, SONG_YOSHIS_VILLAGE, 0, VOL_LEVEL_FULL)
    Call(ClearAmbientSounds, 250)
    Return
    End
};
