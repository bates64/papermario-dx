#include "hos_05.h"

EntryList Entrances = {
    [hos_05_ENTRY_0]    {    0.0,   85.0,  390.0,    0.0 },
    [hos_05_ENTRY_1]    {    0.0,  700.0,    0.0,  225.0 },
    [hos_05_ENTRY_2]    {    0.0,    0.0,    0.0,    0.0 },
    [hos_05_ENTRY_3]    {    0.0,   85.0,  390.0,    0.0 },
    [hos_05_ENTRY_4]    {    0.0,   85.0,  390.0,    0.0 },
    [hos_05_ENTRY_5]    {    0.0,    0.0,    0.0,    0.0 },
    [hos_05_ENTRY_6]    {    0.0,    0.0,    0.0,    0.0 },
    [hos_05_ENTRY_7]    {    0.0,    0.0,    0.0,    0.0 },
    [hos_05_ENTRY_8]    {    0.0,    0.0,    0.0,    0.0 },
    [hos_05_ENTRY_9]    {    0.0,    0.0,    0.0,    0.0 },
    [hos_05_ENTRY_A]    {  354.0,    0.0,  294.0,  117.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "hos_bg",
    .tattle = { MSG_MapTattle_hos_05 },
    .songVariation = 1,
    .sfxReverb = 2,
};
