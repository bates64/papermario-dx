#include "iwa_10.h"

EvtScript EVS_SetupMusic = {
    Call(SetMusic, 0, SONG_MT_RUGGED, 0, VOL_LEVEL_FULL)
    Return
    End
};

EvtScript EVS_PushSong = {
    Call(StopSound, SOUND_LOOP_IWA10_FLOW1)
    Call(PushSong, SONG_NEW_PARTNER, 0)
    Return
    End
};

EvtScript EVS_PopSong = {
    Call(FadeOutMusic, 0, 500)
    Wait(15)
    Call(PopSong)
    Call(PlaySoundAtF, SOUND_LOOP_IWA10_FLOW1, SOUND_SPACE_WITH_DEPTH, -560, 0, -233)
    Return
    End
};
