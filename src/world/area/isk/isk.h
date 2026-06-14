#pragma once

enum AreaBytesISK {
    AB_ISK_Unused_0                         = AreaByte(0x0),
    AB_ISK_Unused_1                         = AreaByte(0x1),
    AB_ISK_Unused_2                         = AreaByte(0x2),
    AB_ISK_Unused_3                         = AreaByte(0x3),
    AB_ISK_Unused_4                         = AreaByte(0x4),
    AB_ISK_Unused_5                         = AreaByte(0x5),
    AB_ISK_Unused_6                         = AreaByte(0x6),
    AB_ISK_Unused_7                         = AreaByte(0x7),
    AB_ISK_Unused_8                         = AreaByte(0x8),
    AB_ISK_Unused_9                         = AreaByte(0x9),
    AB_ISK_Unused_A                         = AreaByte(0xA),
    AB_ISK_Unused_B                         = AreaByte(0xB),
    AB_ISK_Unused_C                         = AreaByte(0xC),
    AB_ISK_Unused_D                         = AreaByte(0xD),
    AB_ISK_Unused_E                         = AreaByte(0xE),
    AB_ISK_Unused_F                         = AreaByte(0xF),
};

enum AreaFlagsISK {
    // AF_ISK_00 unused
    AF_ISK03_SandSwitchActivated            = AreaFlag(0x01),
    AF_ISK06_SandSwitchActivated            = AreaFlag(0x02),
    AF_ISK12_SandSwitchActivated            = AreaFlag(0x03),
    AF_ISK02_Sarcophagus1Opened             = AreaFlag(0x04),
    AF_ISK02_Sarcophagus2Opened             = AreaFlag(0x05),
    AF_ISK02_Sarcophagus3Opened             = AreaFlag(0x06),
    AF_ISK02_OpeningSarcophagus1            = AreaFlag(0x07),
    AF_ISK02_OpeningSarcophagus2            = AreaFlag(0x08),
    AF_ISK02_OpeningSarcophagus3            = AreaFlag(0x09),
    AF_ISK07_OpeningSarcophagus1            = AreaFlag(0x0A),
    AF_ISK07_OpeningSarcophagus2            = AreaFlag(0x0B),
    AF_ISK07_OpeningSarcophagus3            = AreaFlag(0x0C),
    AF_ISK07_MummiesReleased                = AreaFlag(0x0D),
    AF_ISK07_FlippingRedStairs              = AreaFlag(0x0E),
    AF_ISK09_FlippingBlueStairs             = AreaFlag(0x0F),
    AF_ISK09_FlippingRedStairs              = AreaFlag(0x10),
    AF_ISK05_StoneChompDefeated             = AreaFlag(0x11),
    AF_ISK12_StairSwitchActivated           = AreaFlag(0x12),
    AF_ISK14_StoneChompDefeated             = AreaFlag(0x13),
    // AF_ISK_14 - AF_ISK_FF unused
};
