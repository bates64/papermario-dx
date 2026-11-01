#include "flo_10.h"

EvtScript EVS_MakeEntities = {
    IfGe(GB_StoryProgress, STORY_CH6_FILLED_SPRING_WITH_WATER)
        Call(MakeMarkerEntity, $Item_WaterStone_1)
    EndIf
    Return
    End
};
