#pragma once

enum AreaBytesIWA {
    AB_IWA_Unused_0                         = AreaByte(0x0),
    AB_IWA_Unused_1                         = AreaByte(0x1),
    AB_IWA_Unused_2                         = AreaByte(0x2),
    AB_IWA_Unused_3                         = AreaByte(0x3),
    AB_IWA_Unused_4                         = AreaByte(0x4),
    AB_IWA_Unused_5                         = AreaByte(0x5),
    AB_IWA_Unused_6                         = AreaByte(0x6),
    AB_IWA_Unused_7                         = AreaByte(0x7),
    AB_IWA_Unused_8                         = AreaByte(0x8),
    AB_IWA_Unused_9                         = AreaByte(0x9),
    AB_IWA_Unused_A                         = AreaByte(0xA),
    AB_IWA_Unused_B                         = AreaByte(0xB),
    AB_IWA_Unused_C                         = AreaByte(0xC),
    AB_IWA_Unused_D                         = AreaByte(0xD),
    AB_IWA_Unused_E                         = AreaByte(0xE),
    AB_IWA_Unused_F                         = AreaByte(0xF),
};

enum AreaFlagsIWA {
    // AF_IWA_00 unused
    AF_IWA_SpokeWithBubulb                  = AreaFlag(0x01),
    AF_IWA_SpokeWIthDryite                  = AreaFlag(0x02),
    // AF_IWA_03 - AF_IWA_FF unused
};
