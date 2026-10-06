#include "jan_04.h"

s32 get_tattle(void) {
    if (evt_get_variable(nullptr, GB_StoryProgress) < STORY_CH5_SUSHIE_JOINED_PARTY) {
        return MSG_MapTattle_jan_04_before;
    } else {
        return MSG_MapTattle_jan_04_after;
    }
}

EntryList Entrances = {
    [jan_04_ENTRY_0]    { -483.0,    0.0,    0.0,   90.0 },
    [jan_04_ENTRY_1]    {    0.0, -100.0,    0.0,   90.0 },
    [jan_04_ENTRY_2]    {    0.0, -100.0,    0.0,   90.0 },
    [jan_04_ENTRY_3]    {    0.0, -100.0,    0.0,   90.0 },
    [jan_04_ENTRY_4]    { -110.0,  -15.0,  204.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "yos_bg",
    .tattle = { .get = &get_tattle },
};
