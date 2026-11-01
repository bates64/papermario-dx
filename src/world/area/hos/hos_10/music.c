#include "hos_10.h"

EvtScript EVS_SetupMusic = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($Descent.index)
            Call(SetMusic, 0, SONG_INTRO_STORY, BGM_VARIATION_3, VOL_LEVEL_FULL)
        CaseEq($FlyAway.index)
            // do nothing
        CaseOrEq($Entry3.index)
        CaseOrEq($Entry4.index)
        EndCaseGroup
        CaseEq($PreTitle.index)
            Thread
                Wait(10)
                Call(SetMusic, 0, SONG_MARIO_FALLS, 0, VOL_LEVEL_FULL)
            EndThread
    EndSwitch
    Return
    End
};
