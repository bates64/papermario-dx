#pragma once

enum AreaBytesSBK {
    AB_SBK_Unused_0                         = AreaByte(0x0),
    AB_SBK_Unused_1                         = AreaByte(0x1),
    AB_SBK_Unused_2                         = AreaByte(0x2),
    AB_SBK_Unused_3                         = AreaByte(0x3),
    AB_SBK_Unused_4                         = AreaByte(0x4),
    AB_SBK_Unused_5                         = AreaByte(0x5),
    AB_SBK_Unused_6                         = AreaByte(0x6),
    AB_SBK_Unused_7                         = AreaByte(0x7),
    AB_SBK_Unused_8                         = AreaByte(0x8),
    AB_SBK_Unused_9                         = AreaByte(0x9),
    AB_SBK_Unused_A                         = AreaByte(0xA),
    AB_SBK_Unused_B                         = AreaByte(0xB),
    AB_SBK_Unused_C                         = AreaByte(0xC),
    AB_SBK_Unused_D                         = AreaByte(0xD),
    AB_SBK_Unused_E                         = AreaByte(0xE),
    AB_SBK_Unused_F                         = AreaByte(0xF),
};

enum AreaFlagsSBK {
    // AF_SBK_00 unused
    AF_BanditHasCoin                        = AreaFlag(0x01),
    AF_SBK30_ToggleDialogue_Archeologist1   = AreaFlag(0x02),
    AF_SBK30_ToggleDialogue_Archeologist2   = AreaFlag(0x03),
    AF_SBK30_KoloradoHint1                  = AreaFlag(0x04),
    AF_SBK30_KoloradoHint2                  = AreaFlag(0x05),
    AF_SBK30_KoloradoHint3                  = AreaFlag(0x06),
    // AF_SBK_07 - AF_SBK_FF unused
};
