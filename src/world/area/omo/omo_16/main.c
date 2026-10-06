#include "omo_16.h"

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_SHY_GUYS_TOYBOX)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(MakeNpcs, true, Ref(DefaultNPCs))
    Call(SetMusic, 0, SONG_TOYBOX_TRAIN, 0, VOL_LEVEL_FULL)
    ExecWait(EVS_Scene_TrainTraveling)
    Wait(3)
    Return
    End
};
