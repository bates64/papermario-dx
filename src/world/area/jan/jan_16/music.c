#include "jan_16.h"

EvtScript EVS_SetupMusic = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($Jan15.index)
            Call(SetMusic, 0, SONG_RAPHAEL_RAVEN, 0, VOL_LEVEL_FULL)
            Set(AF_JAN_PlayingRaphaelVariant, false)
        CaseEq($Jan15FirstVisit.index)
            Call(SetMusic, 0, SONG_RAPHAEL_RAVEN, BGM_VARIATION_1, VOL_LEVEL_FULL)
            Set(AF_JAN_PlayingRaphaelVariant, true)
        CaseDefault
            IfEq(AF_JAN_PlayingRaphaelVariant, false)
                Call(SetMusic, 0, SONG_RAPHAEL_RAVEN, 0, VOL_LEVEL_FULL)
            EndIf
    EndSwitch
    Call(PlayAmbientSounds, AMBIENT_JUNGLE)
    Return
    End
};
