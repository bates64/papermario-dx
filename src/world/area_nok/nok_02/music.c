#include "nok_02.h"

EvtScript N(EVS_SetupMusic) = {
    IfLt(GB_StoryProgress, STORY_CH1_KOOPER_JOINED_PARTY)
        Call(SetMusic, 0, SONG_FUZZY_ATTACK, 0, 8)
    Else
        Call(SetMusic, 0, SONG_KOOPA_VILLAGE, 0, 8)
    EndIf
    Return
    End
};
