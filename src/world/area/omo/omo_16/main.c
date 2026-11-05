#include "omo_16.h"

EvtScript EVS_Main = {
    Call(MakeNpcs, true, DefaultNPCs)
    Call(SetMusic, 0, SONG_TOYBOX_TRAIN, 0, VOL_LEVEL_FULL)
    ExecWait(EVS_Scene_TrainTraveling)
    Wait(3)
    Return
    End
};
