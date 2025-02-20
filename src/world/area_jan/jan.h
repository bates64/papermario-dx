#pragma once

#include "map.h"
#include "script_api/macros.h"

enum {
    AB_JAN22_ZiplineNpc1            = AreaByte(0),
    AB_JAN22_ZiplineNpc2            = AreaByte(1),
    AB_JAN_2                        = AreaByte(2),
    AB_JAN13_LastPuzzleProgress     = AreaByte(3),
};

enum {
    AF_JAN_02                           = AreaFlag(2),
    AF_JAN_03                           = AreaFlag(3),
    AF_JAN02_RaphaelComment             = AreaFlag(4),
    AF_JAN02_MetCouncillor              = AreaFlag(5),
    AF_JAN_06                           = AreaFlag(6),
    AF_JAN_07                           = AreaFlag(7),
    AF_JAN_08                           = AreaFlag(8),
    AF_JAN01_KoloradoShouting           = AreaFlag(9),
    AF_JAN_0A                           = AreaFlag(10),
    AF_JAN22_MisstarReleasedParty       = AreaFlag(11),
    AF_JAN22_MisstarReleasedKolorado    = AreaFlag(12),
    AF_JAN00_TreeDrop1                  = AreaFlag(13),

    AF_JAN01_TreeDrop2                  = AreaFlag(14),
    AF_JAN01_TreeDrop3                  = AreaFlag(15),
    AF_JAN01_TreeDrop4                  = AreaFlag(16),
    AF_JAN01_TreeDrop5                  = AreaFlag(17),
    AF_JAN01_TreeDrop6                  = AreaFlag(18),
    AF_JAN01_TreeDrop7                  = AreaFlag(19),

    AF_JAN02_TreeDrop2                  = AreaFlag(20),
    AF_JAN02_TreeDrop3                  = AreaFlag(21),
    AF_JAN_16                           = AreaFlag(22),
    AF_JAN03_TreeDrop1                  = AreaFlag(23),
};

extern MapSettings jan_00_settings;
extern MapSettings jan_01_settings;
extern MapSettings jan_02_settings;
extern MapSettings jan_03_settings;
extern MapSettings jan_04_settings;
extern MapSettings jan_05_settings;
extern MapSettings jan_06_settings;
extern MapSettings jan_07_settings;
extern MapSettings jan_08_settings;
extern MapSettings jan_09_settings;
extern MapSettings jan_10_settings;
extern MapSettings jan_11_settings;
extern MapSettings jan_12_settings;
extern MapSettings jan_13_settings;
extern MapSettings jan_14_settings;
extern MapSettings jan_15_settings;
extern MapSettings jan_16_settings;
extern MapSettings jan_17_settings;
extern MapSettings jan_18_settings;
extern MapSettings jan_19_settings;
extern MapSettings jan_22_settings;
extern MapSettings jan_23_settings;
