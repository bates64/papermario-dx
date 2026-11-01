#include "trd_10.h"

extern EvtScript EVS_Main;

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .tattle = { MSG_MapTattle_trd_10 },
    .songVariation = 1,
    .sfxReverb = 3,
};

EvtScript EVS_SetupMusic = {
    Switch(GB_StoryProgress)
        CaseLt(STORY_CH1_DEFEATED_KOOPA_BROS)
            Call(SetMusic, 0, SONG_KOOPA_BROS_THEME, BGM_VARIATION_1, VOL_LEVEL_FULL)
        CaseEq(STORY_CH1_DEFEATED_KOOPA_BROS)
            Call(FadeOutMusic, 0, 500)
        CaseDefault
            Call(SetMusic, 0, SONG_KOOPA_FORTRESS, 0, VOL_LEVEL_FULL)
    EndSwitch
    Call(UseDoorSounds, DOOR_SOUNDS_METAL)
    Return
    End
};
