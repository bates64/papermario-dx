#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/mim_bt01_shape.h"

API_CALLABLE(SetupFog) {
    enable_world_fog();
    set_world_fog_dist(950, 1000);
    set_world_fog_color(16, 16, 16, 255);
    gCameras[CAM_BATTLE].bgColor[0] = 20;
    gCameras[CAM_BATTLE].bgColor[1] = 20;
    gCameras[CAM_BATTLE].bgColor[2] = 28;

    return ApiStatus_DONE2;
}

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetupFog)
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

BATTLE_STAGE_ENTRY = {
    .texture = "mim_tex",
    .shape = "mim_bt01_shape",
    .hit = "mim_bt01_hit",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
};
