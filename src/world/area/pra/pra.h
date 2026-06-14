#pragma once

enum AreaBytesPRA {
    AB_PRA_Unused_0                         = AreaByte(0x0),
    AB_PRA_Unused_1                         = AreaByte(0x1),
    AB_PRA_Unused_2                         = AreaByte(0x2),
    AB_PRA_Unused_3                         = AreaByte(0x3),
    AB_PRA_Unused_4                         = AreaByte(0x4),
    AB_PRA_Unused_5                         = AreaByte(0x5),
    AB_PRA_Unused_6                         = AreaByte(0x6),
    AB_PRA_Unused_7                         = AreaByte(0x7),
    AB_PRA_Unused_8                         = AreaByte(0x8),
    AB_PRA_Unused_9                         = AreaByte(0x9),
    AB_PRA_Unused_A                         = AreaByte(0xA),
    AB_PRA_Unused_B                         = AreaByte(0xB),
    AB_PRA_Unused_C                         = AreaByte(0xC),
    AB_PRA_Unused_D                         = AreaByte(0xD),
    AB_PRA_Unused_E                         = AreaByte(0xE),
    AB_PRA_Unused_F                         = AreaByte(0xF),
};

enum AreaFlagsPRA {
    // AF_PRA_00 unused
    // AF_PRA_01 unused
    AF_PRA09_HitSwitch                      = AreaFlag(0x02),
    AF_PRA33_FlippingWall                   = AreaFlag(0x03),
    // AF_PRA_04 - AF_PRA_FF unused
};
