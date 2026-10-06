#include "dro_01.h"

EntryList Entrances = {
    [dro_01_ENTRY_0]    { -342.0,    0.0,  316.0,   45.0 },
    [dro_01_ENTRY_1]    {  488.0,    1.0,    4.0,  270.0 },
    [dro_01_ENTRY_2]    {  430.0,   35.0, -120.0,  180.0 },
    [dro_01_ENTRY_3]    {    0.0,    0.0,    0.0,    0.0 },
    [dro_01_ENTRY_4]    {    0.0,    0.0,    0.0,    0.0 },
    [dro_01_ENTRY_5]    {    0.0,    0.0,    0.0,    0.0 },
    [dro_01_ENTRY_6]    {    0.0,    0.0,    0.0,    0.0 },
    [dro_01_ENTRY_7]    {    0.0,    0.0,    0.0,    0.0 },
    [dro_01_ENTRY_8]    {    0.0,    0.0,    0.0,    0.0 },
    [dro_01_ENTRY_9]    {    0.0,    0.0,    0.0,    0.0 },
    [dro_01_ENTRY_A]    { -211.0,   50.0,  -50.0,  120.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "sbk_bg",
    .tattle = { MSG_MapTattle_dro_01 },
};
