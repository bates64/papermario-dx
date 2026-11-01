#include "jan_22.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Thread
        Label(0)
            IfLt(GB_StoryProgress, STORY_CH5_ZIP_LINE_READY)
                Wait(1)
                Goto(0)
            EndIf
        Call(MakeMarkerEntity, $HeartBlock_1)
    EndThread
    Call(MakeMarkerEntity, $Item_JamminJelly_1)
    Call(MakeMarkerEntity, $PinkFlower_1)
    Return
    End
};
