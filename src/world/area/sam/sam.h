#pragma once

enum AreaBytesSAM {
    AB_SAM_Unused_0     = AreaByte(0),
    AB_SAM_Unused_1     = AreaByte(1),
    AB_SAM_Unused_2     = AreaByte(2),
    AB_SAM_Unused_3     = AreaByte(3),
    AB_SAM_Unused_4     = AreaByte(4),
    AB_SAM_Unused_5     = AreaByte(5),
    AB_SAM_Unused_6     = AreaByte(6),
    AB_SAM_Unused_7     = AreaByte(7),
    AB_SAM_Unused_8     = AreaByte(8),
    AB_SAM_Unused_9     = AreaByte(9),
    AB_SAM_Unused_A     = AreaByte(10),
    AB_SAM_Unused_B     = AreaByte(11),
    AB_SAM_Unused_C     = AreaByte(12),
    AB_SAM_Unused_D     = AreaByte(13),
    AB_SAM_Unused_E     = AreaByte(14),
    AB_SAM_Unused_F     = AreaByte(15),
};

enum AreaFlagsSAM {
    AF_SAM_Snowing      = AreaFlag(1),
    AF_SAM_LastSnowing  = AreaFlag(2),
    AF_SAM01_InsideMayorOffice      = AreaFlag(3),
    AF_SAM01_InsideMayorFoyer       = AreaFlag(4),
    AF_SAM_05           = AreaFlag(5),
    AF_SAM08_ImposterSwitchPressed  = AreaFlag(6),
};
