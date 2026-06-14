#pragma once

enum AreaBytesARN {
    AB_ARN_Unused_0                         = AreaByte(0x0),
    AB_ARN_Unused_1                         = AreaByte(0x1),
    AB_ARN_Unused_2                         = AreaByte(0x2),
    AB_ARN_Unused_3                         = AreaByte(0x3),
    AB_ARN_Unused_4                         = AreaByte(0x4),
    AB_ARN_Unused_5                         = AreaByte(0x5),
    AB_ARN_Unused_6                         = AreaByte(0x6),
    AB_ARN_Unused_7                         = AreaByte(0x7),
    AB_ARN_Unused_8                         = AreaByte(0x8),
    AB_ARN_Unused_9                         = AreaByte(0x9),
    AB_ARN_Unused_A                         = AreaByte(0xA),
    AB_ARN_Unused_B                         = AreaByte(0xB),
    AB_ARN_Unused_C                         = AreaByte(0xC),
    AB_ARN_Unused_D                         = AreaByte(0xD),
    AB_ARN_Unused_E                         = AreaByte(0xE),
    AB_ARN_Unused_F                         = AreaByte(0xF),
};

enum AreaFlagsARN {
    // AF_ARN_00 unused
    AF_ARN_UsingWellSpring                  = AreaFlag(0x01),
    AF_ARN03_ToggleDialogue_Boo1            = AreaFlag(0x02),
    AF_ARN03_ToggleDialogue_Boo2            = AreaFlag(0x03),
    AF_ARN03_ToggleDialogue_Boo3            = AreaFlag(0x04),
    AF_ARN03_ToggleDialogue_Boo4            = AreaFlag(0x05),
    AF_ARN05_ToggleDialogue_Boo1            = AreaFlag(0x06),
    AF_ARN05_ToggleDialogue_Boo2            = AreaFlag(0x07),
    AF_ARN05_ToggleDialogue_Boo5            = AreaFlag(0x08),
    AF_ARN05_Boo3GaveRecentAdvice           = AreaFlag(0x09),
    // AF_ARN_0A - AF_ARN_FF unused
};
