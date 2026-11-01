#include "flo_19.h"

EvtScript EVS_SetupMusic = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseOrEq($Entry0.index)
        CaseOrEq($Flo21.index)
            Call(SetMusic, 0, SONG_CLOUDY_CLIMB, 0, VOL_LEVEL_FULL)
        EndCaseGroup
        CaseOrEq($BeanstalkGrowing.index)
        CaseOrEq(7)
        EndCaseGroup
        CaseEq($Beanstalk.index)
            IfNe(AF_FLO_RidingBeanstalk, false)
            Else
                Call(FadeOutMusic, 1, 3000)
                Call(FadeInMusic, 0, SONG_CLOUDY_CLIMB, 0, 3000, 0, 127)
            EndIf
    EndSwitch
    Return
    End
};
