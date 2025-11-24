#include "jan_03.h"

EvtScript N(EVS_SetupMusic) = {
    Switch(GB_StoryProgress)
        CaseRange(STORY_CH5_YOSHI_CHILDREN_ARE_MISSING, STORY_CH5_SUSHIE_JOINED_PARTY)
            Call(SetMusic, 0, SONG_YOSHIS_PANIC, 0, 8)
        CaseDefault
            Call(SetMusic, 0, SONG_YOSHIS_VILLAGE, 0, 8)
    EndSwitch
    Call(ClearAmbientSounds, 250)
    Return
    End
};

EvtScript N(EVS_PlayRestingSong) = {
    Call(SetMusic, 0, SONG_TAKING_REST, 0, 8)
    Return
    End
};
