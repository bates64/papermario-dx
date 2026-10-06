#include "kkj_14.h"

export s32 map_init(void) {
    if (evt_get_variable(nullptr, GB_StoryProgress) == STORY_INTRO) {
        sprintf(wMapBgName, "nok_bg");
    }
    return false;
}

EntryList Entrances = {
    [kkj_14_ENTRY_0]    { -375.0,    0.0,  -30.0,   90.0 },
    [kkj_14_ENTRY_1]    {  435.0,   30.0,  -33.0,  270.0 },
    [kkj_14_ENTRY_2]    { -122.0,   10.0,  -82.0,  180.0 },
    [kkj_14_ENTRY_3]    {  -20.0,    0.0,   30.0,  270.0 },
    [kkj_14_ENTRY_4]    { -140.0,    0.0,    0.0,  270.0 },
    [kkj_14_ENTRY_5]    {   40.0,    0.0,   30.0,  180.0 },
    [kkj_14_ENTRY_6]    {  -20.0,    0.0,    0.0,  270.0 },
    [kkj_14_ENTRY_7]    {    0.0,    0.0,   30.0,  180.0 },
    [kkj_14_ENTRY_8]    { -130.0,    0.0,    0.0,  180.0 },
    [kkj_14_ENTRY_9]    {  -60.0,    0.0,    0.0,  270.0 },
    [kkj_14_ENTRY_A]    {  380.0,   30.0,   10.0,  270.0 },
    [kkj_14_ENTRY_B]    {  150.0,    0.0,  -30.0,   90.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "kpa_bg",
    .tattle = { MSG_MapTattle_kkj_14 },
};
