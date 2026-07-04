#pragma once

enum AreaBytesSAM {
    AB_SAM_Unused_0                         = AreaByte(0x0),
    AB_SAM_Unused_1                         = AreaByte(0x1),
    AB_SAM_Unused_2                         = AreaByte(0x2),
    AB_SAM_Unused_3                         = AreaByte(0x3),
    AB_SAM_Unused_4                         = AreaByte(0x4),
    AB_SAM_Unused_5                         = AreaByte(0x5),
    AB_SAM_Unused_6                         = AreaByte(0x6),
    AB_SAM_Unused_7                         = AreaByte(0x7),
    AB_SAM_Unused_8                         = AreaByte(0x8),
    AB_SAM_Unused_9                         = AreaByte(0x9),
    AB_SAM_Unused_A                         = AreaByte(0xA),
    AB_SAM_Unused_B                         = AreaByte(0xB),
    AB_SAM_Unused_C                         = AreaByte(0xC),
    AB_SAM_Unused_D                         = AreaByte(0xD),
    AB_SAM_Unused_E                         = AreaByte(0xE),
    AB_SAM_Unused_F                         = AreaByte(0xF),
};

enum AreaFlagsSAM {
    // AF_SAM_00 unused
    AF_SAM_Snowing                          = AreaFlag(0x01),
    AF_SAM_LastSnowing                      = AreaFlag(0x02),
    AF_SAM01_InsideMayorOffice              = AreaFlag(0x03),
    AF_SAM01_InsideMayorFoyer               = AreaFlag(0x04),
    AF_SAM06_MeetingWithMerle               = AreaFlag(0x05),
    AF_SAM08_ImposterSwitchPressed          = AreaFlag(0x06),
    // AF_SAM_07 - AF_SAM_FF unused
};
