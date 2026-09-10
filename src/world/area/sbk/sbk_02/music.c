#include "sbk_02.h"

EvtScript N(EVS_SetupMusic) = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseOrEq(sbk_02_ENTRY_6)
        CaseOrEq(sbk_02_ENTRY_7)
        EndCaseGroup
        CaseDefault
            Call(SetMusic, 0, SONG_DRY_DRY_DESERT, 0, VOL_LEVEL_FULL)
    EndSwitch
    Return
    End
};
