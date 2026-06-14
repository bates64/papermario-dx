#pragma once

enum AreaBytesTRD {
    AB_TRD_Unused_0                         = AreaByte(0x0),
    AB_TRD_Unused_1                         = AreaByte(0x1),
    AB_TRD_Unused_2                         = AreaByte(0x2),
    AB_TRD_Unused_3                         = AreaByte(0x3),
    AB_TRD_Unused_4                         = AreaByte(0x4),
    AB_TRD_Unused_5                         = AreaByte(0x5),
    AB_TRD_Unused_6                         = AreaByte(0x6),
    AB_TRD_Unused_7                         = AreaByte(0x7),
    AB_TRD_Unused_8                         = AreaByte(0x8),
    AB_TRD_Unused_9                         = AreaByte(0x9),
    AB_TRD_Unused_A                         = AreaByte(0xA),
    AB_TRD_Unused_B                         = AreaByte(0xB),
    AB_TRD_Unused_C                         = AreaByte(0xC),
    AB_TRD_Unused_D                         = AreaByte(0xD),
    AB_TRD_Unused_E                         = AreaByte(0xE),
    AB_TRD_Unused_F                         = AreaByte(0xF),
};

enum AreaFlagsTRD {
    // AF_TRD_00 unused
    AF_TRD01_RaiseStairs                    = AreaFlag(0x01),
    AF_TRD02_LowerStairs                    = AreaFlag(0x02),
    // AF_TRD_03 unused
    AF_TRD04_LowerStairs                    = AreaFlag(0x04),
    // AF_TRD_05 unused
    AF_TRD_MetPrisoner1                     = AreaFlag(0x06),
    AF_TRD_MetPrisoner2                     = AreaFlag(0x07),
    AF_TRD_MetPrisoner3                     = AreaFlag(0x08),
    AF_TRD_MetPrisoner4                     = AreaFlag(0x09),
    // AF_TRD_0A unused
    AF_TRD08_FireBar1_Coins                 = AreaFlag(0x0B),
    AF_TRD08_FireBar2_Coins                 = AreaFlag(0x0C),
    AF_TRD_FakeBowserRevealed               = AreaFlag(0x0D),
    // AF_TRD_0E - AF_TRD_FF unused
};
