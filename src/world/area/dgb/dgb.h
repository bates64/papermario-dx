#pragma once

enum AreaBytesDGB {
    AB_DGB_Unused_0                         = AreaByte(0x0),
    AB_DGB_Unused_1                         = AreaByte(0x1),
    AB_DGB_Unused_2                         = AreaByte(0x2),
    AB_DGB_Unused_3                         = AreaByte(0x3),
    AB_DGB_Unused_4                         = AreaByte(0x4),
    AB_DGB_Unused_5                         = AreaByte(0x5),
    AB_DGB_Unused_6                         = AreaByte(0x6),
    AB_DGB_Unused_7                         = AreaByte(0x7),
    AB_DGB_Unused_8                         = AreaByte(0x8),
    AB_DGB_Unused_9                         = AreaByte(0x9),
    AB_DGB_Unused_A                         = AreaByte(0xA),
    AB_DGB_Unused_B                         = AreaByte(0xB),
    AB_DGB_Unused_C                         = AreaByte(0xC),
    AB_DGB_Unused_D                         = AreaByte(0xD),
    AB_DGB_Unused_E                         = AreaByte(0xE),
    AB_DGB_Unused_F                         = AreaByte(0xF),
};

enum AreaFlagsDGB {
    // AF_DGB_00 unused
    AF_DGB_CloseCallWithTubba               = AreaFlag(0x01),
    AF_DGB11_FallingFromHole                = AreaFlag(0x02),
    AF_DGB11_SpringInUse                    = AreaFlag(0x03),
    AF_DGB06_ToggleDialogue_Boo             = AreaFlag(0x04),
    // AF_DGB_05 - AF_DGB_FF unused
};
