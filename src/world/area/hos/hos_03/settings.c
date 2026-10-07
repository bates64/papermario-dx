#include "hos_03.h"

EntryList Entrances = {
    [hos_03_ENTRY_0]    { -497.0,    0.0,  479.0,   45.0 },
    [hos_03_ENTRY_1]    {  705.0,    0.0,    0.0,  270.0 },
    [hos_03_ENTRY_2]    {    0.0,    0.0,    0.0,    0.0 },
    [hos_03_ENTRY_3]    {    0.0,    0.0,    0.0,    0.0 },
    [hos_03_ENTRY_4]    {    0.0,    0.0,    0.0,    0.0 },
    [hos_03_ENTRY_5]    {    0.0,    0.0,    0.0,    0.0 },
    [hos_03_ENTRY_6]    {    0.0,    0.0,    0.0,    0.0 },
    [hos_03_ENTRY_7]    {    0.0,    0.0,    0.0,    0.0 },
    [hos_03_ENTRY_8]    {    0.0,    0.0,    0.0,    0.0 },
    [hos_03_ENTRY_9]    {    0.0,    0.0,    0.0,    0.0 },
    [hos_03_ENTRY_A]    {  354.0,    0.0,  294.0,  117.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "hos_bg",
    .tattle = { MSG_MapTattle_hos_03 },
};
