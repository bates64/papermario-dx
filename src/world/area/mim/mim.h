#pragma once

enum AreaBytesMIM {
    AB_MIM_Unused_0     = AreaByte(0),
    AB_MIM_1            = AreaByte(1),
    AB_MIM_2            = AreaByte(2),
    AB_MIM_Unused_3     = AreaByte(3),
    AB_MIM_Unused_4     = AreaByte(4),
    AB_MIM_Unused_5     = AreaByte(5),
    AB_MIM_Unused_6     = AreaByte(6),
    AB_MIM_Unused_7     = AreaByte(7),
    AB_MIM_Unused_8     = AreaByte(8),
    AB_MIM_Unused_9     = AreaByte(9),
    AB_MIM_Unused_A     = AreaByte(10),
    AB_MIM_Unused_B     = AreaByte(11),
    AB_MIM_Unused_C     = AreaByte(12),
    AB_MIM_Unused_D     = AreaByte(13),
    AB_MIM_Unused_E     = AreaByte(14),
    AB_MIM_Unused_F     = AreaByte(15),
};

enum AreaFlagsMIM {
    AF_MIM11_MansionGateOpen        = AreaFlag(1),
    AF_MIM03_ToggleDialogue_Oaklie  = AreaFlag(2),
    AF_MIM04_ToggleDialogue_Bubulb  = AreaFlag(4),
    AF_MIM12_BackgroundLitUp        = AreaFlag(3),
};
