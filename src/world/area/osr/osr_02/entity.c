#include "osr_02.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    IfEq(GF_KKJ25_Defeated_Bowser, true)
        Return
    EndIf
    IfLt(GB_StoryProgress, STORY_CH7_STAR_SPIRIT_DEPARTED)
        Return
    EndIf
    Call(MakeMarkerEntity, $HiddenYellowBlock_UltraShroom_1)
    Call(MakeMarkerEntity, $SavePoint_1)
    Return
    End
};
