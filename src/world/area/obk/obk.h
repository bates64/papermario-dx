#pragma once

enum AreaBytesOBK {
    AB_OBK_Unused_0                         = AreaByte(0x0),
    AB_OBK_Unused_1                         = AreaByte(0x1),
    AB_OBK_Unused_2                         = AreaByte(0x2),
    AB_OBK_Unused_3                         = AreaByte(0x3),
    AB_OBK_Unused_4                         = AreaByte(0x4),
    AB_OBK_Unused_5                         = AreaByte(0x5),
    AB_OBK_Unused_6                         = AreaByte(0x6),
    AB_OBK_Unused_7                         = AreaByte(0x7),
    AB_OBK_Unused_8                         = AreaByte(0x8),
    AB_OBK_Unused_9                         = AreaByte(0x9),
    AB_OBK_Unused_A                         = AreaByte(0xA),
    AB_OBK_Unused_B                         = AreaByte(0xB),
    AB_OBK_Unused_C                         = AreaByte(0xC),
    AB_OBK_Unused_D                         = AreaByte(0xD),
    AB_OBK_Unused_E                         = AreaByte(0xE),
    AB_OBK_Unused_F                         = AreaByte(0xF),
};

enum AreaFlagsOBK {
    // AF_OBK_00 unused
    AF_OBK01_CabinetMoved                   = AreaFlag(0x01),
    // AF_OBK_02 unused
    AF_OBK01_IsPlayerNearPortrait           = AreaFlag(0x03),
    AF_OBK01_WasPlayerNearPortrait          = AreaFlag(0x04),
    AF_OBK03_HitFirstSwitch                 = AreaFlag(0x05),
    AF_OBK03_HitSecondSwitch                = AreaFlag(0x06),
    AF_OBK03_HitThirdSwitch                 = AreaFlag(0x07),
    AF_OBK08_KeepAwayStarted                = AreaFlag(0x08),
    // AF_OBK_09 - AF_OBK_FF unused
};
