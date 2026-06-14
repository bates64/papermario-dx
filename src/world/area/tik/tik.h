#pragma once

enum AreaBytesTIK {
    AB_TIK_Unused_0                         = AreaByte(0x0),
    AB_TIK_Unused_1                         = AreaByte(0x1),
    AB_TIK_Unused_2                         = AreaByte(0x2),
    AB_TIK_Unused_3                         = AreaByte(0x3),
    AB_TIK_Unused_4                         = AreaByte(0x4),
    AB_TIK_Unused_5                         = AreaByte(0x5),
    AB_TIK_Unused_6                         = AreaByte(0x6),
    AB_TIK_Unused_7                         = AreaByte(0x7),
    AB_TIK_Unused_8                         = AreaByte(0x8),
    AB_TIK_Unused_9                         = AreaByte(0x9),
    AB_TIK_Unused_A                         = AreaByte(0xA),
    AB_TIK_Unused_B                         = AreaByte(0xB),
    AB_TIK_Unused_C                         = AreaByte(0xC),
    AB_TIK_Unused_D                         = AreaByte(0xD),
    AB_TIK_Unused_E                         = AreaByte(0xE),
    AB_TIK_Unused_F                         = AreaByte(0xF),
};

enum AreaFlagsTIK {
    // AF_TIK_00 unused
    // AF_TIK_01 unused
    AF_TIK15_RipCheatoRepeatVisit           = AreaFlag(0x02),
    AF_TIK01_Switch_WarpPipe                = AreaFlag(0x03),
    AF_TIK08_Switch_WarpPipe                = AreaFlag(0x04),
    AF_TIK09_Switch_WarpPipe                = AreaFlag(0x05),
    // AF_TIK_06 - AF_TIK_FF unused
};
