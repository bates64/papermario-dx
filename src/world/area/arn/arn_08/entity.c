#include "arn_08.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    IfLt(GB_StoryProgress, STORY_CH3_WENT_DOWN_THE_WELL)
        Call(MakeMarkerEntity, $BoardedFloor_1)
    EndIf
    Return
    End
};
