#include "sbk_02.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    IfGe(GB_StoryProgress, STORY_CH2_UNCOVERED_DRY_DRY_RUINS)
        Call(MakeMarkerEntity, $HeartBlock_1)
    EndIf
    Return
    End
};
