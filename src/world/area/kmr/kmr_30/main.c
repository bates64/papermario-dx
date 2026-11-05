#include "kmr_30.h"

EvtScript EVS_Main = {
    Call(MakeNpcs, false, DefaultNPCs)
    Call(EnableWorldStatusBar, false)
    Thread
        Call(FadeOutMusic, 0, 0x00001388)
        Wait(390)
        Call(SetMusic, 0, SONG_THE_END, 0, VOL_LEVEL_FULL)
    EndThread
    Exec(EVS_Scene_TheEnd)
    Return
    End
};
