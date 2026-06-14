#pragma once

enum AreaBytesDRO {
    AB_DRO01_DialogueState_Mouser1          = AreaByte(0x0),
    AB_DRO01_DialogueState_Dryite1          = AreaByte(0x1),
    AB_DRO01_DialogueState_Dryite2          = AreaByte(0x2),
    AB_DRO02_DialogueState_Archeologist     = AreaByte(0x3),
    AB_DRO_SHOP_PREV1                       = AreaByte(0x4),
    AB_DRO_SHOP_PREV2                       = AreaByte(0x5),
    AB_DRO_SHOP_PREV3                       = AreaByte(0x6),
    AB_DRO_Unused_7                         = AreaByte(0x7),
    AB_DRO_Unused_8                         = AreaByte(0x8),
    AB_DRO_Unused_9                         = AreaByte(0x9),
    AB_DRO_Unused_A                         = AreaByte(0xA),
    AB_DRO_Unused_B                         = AreaByte(0xB),
    AB_DRO_Unused_C                         = AreaByte(0xC),
    AB_DRO_Unused_D                         = AreaByte(0xD),
    AB_DRO_Unused_E                         = AreaByte(0xE),
    AB_DRO_Unused_F                         = AreaByte(0xF),
};

enum AreaFlagsDRO {
    // AF_DRO_00 unused
    AF_DRO01_ToggleDialogue_HintDryite      = AreaFlag(0x01),
    AF_DRO01_ToggleDialogue_Composer        = AreaFlag(0x02),
    AF_DRO02_ToggleDialogue_Dryite2         = AreaFlag(0x03),
    AF_DRO02_ToggleDialogue_Mouser1         = AreaFlag(0x04),
    AF_DRO02_ToggleDialogue_Mouser2         = AreaFlag(0x05),
    // AF_DRO_06 - AF_DRO_FF unused
};

