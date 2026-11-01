#include "hos_01.h"

EvtScript EVS_SetupMusic = {
    Call(GetEntryID, LVar0)
    IfEq(LVar0, $ShootingStarPath.index)
        Call(SetMusic, 0, SONG_SHOOTING_STAR_SUMMIT, 0, VOL_LEVEL_FULL)
    EndIf
    Return
    End
};
