#pragma once

#include "map.h"
#include "script_api/macros.h"

enum {
    AF_ISK03_SandSwitchActivated    = AreaFlag(1),
    AF_ISK06_SandSwitchActivated    = AreaFlag(2),
    AF_ISK12_SandSwitchActivated    = AreaFlag(3),
    AF_ISK02_Sarcophagus1Opened     = AreaFlag(4),
    AF_ISK02_Sarcophagus2Opened     = AreaFlag(5),
    AF_ISK02_Sarcophagus3Opened     = AreaFlag(6),
    AF_ISK02_OpeningSarcophagus1    = AreaFlag(7),
    AF_ISK02_OpeningSarcophagus2    = AreaFlag(8),
    AF_ISK02_OpeningSarcophagus3    = AreaFlag(9),
    AF_ISK07_OpeningSarcophagus1    = AreaFlag(10),
    AF_ISK07_OpeningSarcophagus2    = AreaFlag(11),
    AF_ISK07_OpeningSarcophagus3    = AreaFlag(12),
    AF_ISK07_MummiesReleased        = AreaFlag(13),
    AF_ISK07_FlippingRedStairs      = AreaFlag(14),
    AF_ISK09_FlippingBlueStairs     = AreaFlag(15),
    AF_ISK09_FlippingRedStairs      = AreaFlag(16),
    AF_ISK05_StoneChompDefeated     = AreaFlag(17),
    AF_ISK12_StairSwitchActivated   = AreaFlag(18),
    AF_ISK14_StoneChompDefeated     = AreaFlag(19),
};

extern MapSettings isk_01_settings;
extern MapSettings isk_02_settings;
extern MapSettings isk_03_settings;
extern MapSettings isk_04_settings;
extern MapSettings isk_05_settings;
extern MapSettings isk_06_settings;
extern MapSettings isk_07_settings;
extern MapSettings isk_08_settings;
extern MapSettings isk_09_settings;
extern MapSettings isk_10_settings;
extern MapSettings isk_11_settings;
extern MapSettings isk_12_settings;
extern MapSettings isk_13_settings;
extern MapSettings isk_14_settings;
extern MapSettings isk_16_settings;
extern MapSettings isk_18_settings;
extern MapSettings isk_19_settings;
