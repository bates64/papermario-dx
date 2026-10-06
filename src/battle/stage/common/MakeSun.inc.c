#include "common.h"
#include "effects.h"
#include <string.h>

char* RightSunMaps[] = {
    "flo_03",
    "flo_08",
    "flo_09",
    "flo_10",
    "flo_16",
    "flo_17",
    "flo_18",
    "flo_19",
    "flo_21",
    "flo_22",
    "flo_24",
};

API_CALLABLE(SpawnStageSunEffect) {
    s32 direction = FX_SUN_FROM_LEFT;
    u32 i;

    for (i = 0; i < ARRAY_COUNT(RightSunMaps); i++) {
        if (strcmp(gAreas[gGameStatusPtr->areaID].maps[gGameStatusPtr->mapID], RightSunMaps[i]) == 0) {
            direction = FX_SUN_FROM_RIGHT;
            break;
        }
    }

    fx_sun(direction, 0, 0, 0, 0, 0);
    return ApiStatus_DONE2;
}

EvtScript MakeSun = {
    IfGe(GB_StoryProgress, STORY_CH6_DESTROYED_PUFF_PUFF_MACHINE)
        Call(SpawnStageSunEffect)
    EndIf
    Return
    End
};
