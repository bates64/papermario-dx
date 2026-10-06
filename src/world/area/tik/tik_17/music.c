#include "tik_17.h"

API_CALLABLE(AdjustTrackVolumes) {
    bgm_set_track_volumes(0, TRACK_VOLS_TIK_SHIVER);
    return ApiStatus_DONE2;
}

EvtScript EVS_SetupMusic = {
    Call(SetMusic, 0, SONG_TOAD_TOWN_TUNNELS, 0, VOL_LEVEL_FULL)
    Thread
        Wait(30)
        Call(AdjustTrackVolumes)
    EndThread
    Return
    End
};
