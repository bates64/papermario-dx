#include "trd_00.h"

extern EvtScript EVS_Main;

EvtScript EVS_SetupMusic = {
    Switch(GB_StoryProgress)
        CaseLt(STORY_CH1_ARRIVED_AT_KOOPA_FORTRESS)
            Call(SetMusic, 0, SONG_KOOPA_FORTRESS, BGM_VARIATION_1, VOL_LEVEL_FULL)
            Call(PlaySound, SOUND_LOOP_TRD_WATER_EXT)
        CaseEq(STORY_CH1_BEGAN_PEACH_MISSION)
            Call(SetMusic, 0, SONG_STAR_SPIRIT_THEME, BGM_VARIATION_1, VOL_LEVEL_FULL)
        CaseDefault
            Call(SetMusic, 0, SONG_PLEASANT_PATH, 0, VOL_LEVEL_FULL)
            Call(PlaySound, SOUND_LOOP_TRD_WATER_EXT)
    EndSwitch
    Call(UseDoorSounds, DOOR_SOUNDS_METAL)
    Return
    End
};
