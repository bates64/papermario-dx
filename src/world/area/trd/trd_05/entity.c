#include "trd_05.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    IfLt(GB_StoryProgress, STORY_CH1_MARIO_ACTIVATED_TRAP)
        Call(MakeMarkerEntity, $TriggerBlock_1)
    EndIf
    Return
    End
};
