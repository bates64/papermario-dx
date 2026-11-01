#include "jan_04.h"

EvtScript EVS_SetupMusic = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseRange($MtLavalava.index, $TreasureChest.index)
            Call(SetMusic, 0, SONG_VOLCANO_ESCAPE, 0, VOL_LEVEL_FULL)
        CaseEq($Epilogue.index)
            Call(FadeInMusic, 0, SONG_JADE_JUNGLE, 0, 3000, 0, 127)
        CaseDefault
            Call(SetMusic, 0, SONG_JADE_JUNGLE, 0, VOL_LEVEL_FULL)
    EndSwitch
    Call(ClearAmbientSounds, 250)
    Return
    End
};

EvtScript EVS_PushNewPartnerSong = {
    Call(PushSong, SONG_NEW_PARTNER, 0)
    Return
    End
};

EvtScript EVS_PopSong = {
    Call(FadeOutMusic, 0, 500)
    Wait(15)
    Call(PopSong)
    Return
    End
};
