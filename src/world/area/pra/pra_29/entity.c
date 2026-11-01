#include "pra_29.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    IfGe(GB_StoryProgress, STORY_CH7_EXTENDED_PALACE_BRIDGE)
    Else
        Call(MakeMarkerEntity, $BlueSwitch_1)
        Call(MakeMarkerEntity, $BlueSwitch_2)
    EndIf
    Return
    End
};
