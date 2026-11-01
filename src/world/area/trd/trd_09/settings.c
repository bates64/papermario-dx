#include "trd_09.h"

extern EvtScript EVS_Main;

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .bgName = "nok_bg",
    .tattle = { MSG_MapTattle_trd_09 },
};

EvtScript EVS_SetupMusic = {
    IfEq(GB_StoryProgress, STORY_CH1_KOOPA_BROS_FIRING_BLASTERS)
        IfEq(GF_TRD09_Defeated_BillBlasters, false)
            Call(SetMusic, 0, SONG_BULLET_BILL_ASSAULT, 0, VOL_LEVEL_FULL)
        Else
            Call(SetMusic, 0, SONG_KOOPA_FORTRESS, 0, VOL_LEVEL_FULL)
        EndIf
    Else
        Call(SetMusic, 0, SONG_KOOPA_FORTRESS, 0, VOL_LEVEL_FULL)
    EndIf
    Call(UseDoorSounds, DOOR_SOUNDS_METAL)
    Return
    End
};
