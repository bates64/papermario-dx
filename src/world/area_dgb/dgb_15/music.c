#include "dgb_15.h"

EvtScript N(EVS_SetupMusic) = {
    Switch(GB_StoryProgress)
        CaseLt(STORY_CH3_TUBBA_WOKE_UP)
            IfEq(GB_ARN_Tubba_MapID, 15)
                Call(SetMusic, 0, SONG_TUBBA_BLUBBA_THEME, 0, 8)
            Else
                Call(SetMusic, 0, SONG_TUBBAS_MANOR, 0, 8)
            EndIf
        CaseLt(STORY_CH3_DEFEATED_TUBBA_BLUBBA)
            Call(SetMusic, 0, SONG_TUBBA_ESCAPE, 0, 8)
        CaseDefault
            Call(SetMusic, 0, SONG_TUBBAS_MANOR, 0, 8)
    EndSwitch
    Return
    End
};
