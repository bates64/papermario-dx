#include "trd_06.h"

extern EvtScript EVS_Main;

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .tattle = { MSG_MapTattle_trd_06 },
    .songVariation = 1,
    .sfxReverb = 3,
};

EvtScript EVS_SetupMusic = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseGe($BossDefeated.index)
        CaseDefault
            Call(SetMusic, 0, SONG_KOOPA_FORTRESS, 0, VOL_LEVEL_FULL)
    EndSwitch
    Call(UseDoorSounds, DOOR_SOUNDS_METAL)
    Return
    End
};

EvtScript EVS_PushSong = {
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
