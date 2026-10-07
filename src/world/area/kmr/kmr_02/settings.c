#include "kmr_02.h"

EntryList Entrances = {
    [kmr_02_ENTRY_0]    {  391.0,    0.0,  286.0,  315.0 },
    [kmr_02_ENTRY_1]    { -371.0,    0.0,  304.0,   45.0 },
    [kmr_02_ENTRY_2]    { -473.0,    0.0,    4.0,   90.0 },
    [kmr_02_ENTRY_3]    {    0.0,   35.0,  355.0,  180.0 },
    [kmr_02_ENTRY_4]    {   60.0,    0.0,   10.0,    0.0 },
    [kmr_02_ENTRY_5]    { -230.0,   36.0, -332.0,    0.0 },
    [kmr_02_ENTRY_6]    {    0.0,    0.0,    0.0,    0.0 },
    [kmr_02_ENTRY_7]    {    0.0,    0.0,    0.0,    0.0 },
    [kmr_02_ENTRY_8]    {    0.0,    0.0,    0.0,    0.0 },
    [kmr_02_ENTRY_9]    {    0.0,    0.0,    0.0,    0.0 },
    [kmr_02_ENTRY_A]    {  200.0,   50.0,   70.0,   90.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "kmr_bg",
    .tattle = { MSG_MapTattle_kmr_02 },
};
