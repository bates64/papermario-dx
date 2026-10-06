#include "sam_06.h"

EvtScript EVS_SetupMusic = {
    Call(SetMusic, 0, SONG_STARBORN_VALLEY, 0, VOL_LEVEL_FULL)
    Return
    End
};

EvtScript EVS_PlayRestingSong = {
    Call(SetMusic, 0, SONG_TAKING_REST, 0, VOL_LEVEL_FULL)
    Return
    End
};
