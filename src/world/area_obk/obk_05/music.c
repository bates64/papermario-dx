#include "obk_05.h"

EvtScript N(EVS_SetupMusic) = {
    IfLt(GB_StoryProgress, STORY_CH3_DEFEATED_TUBBA_BLUBBA)
        Call(SetMusic, 0, SONG_BOOS_MANSION, 0, 8)
    Else
        Call(SetMusic, 0, SONG_CHEERFUL_BOOS_MANSION, 0, 8)
    EndIf
    Return
    End
};
