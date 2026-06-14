#pragma once

enum AreaBytesDGB {
    AB_DGB_Unused_0     = AreaByte(0),
    AB_DGB_Unused_1     = AreaByte(1),
    AB_DGB_Unused_2     = AreaByte(2),
    AB_DGB_Unused_3     = AreaByte(3),
    AB_DGB_Unused_4     = AreaByte(4),
    AB_DGB_Unused_5     = AreaByte(5),
    AB_DGB_Unused_6     = AreaByte(6),
    AB_DGB_Unused_7     = AreaByte(7),
    AB_DGB_Unused_8     = AreaByte(8),
    AB_DGB_Unused_9     = AreaByte(9),
    AB_DGB_Unused_A     = AreaByte(10),
    AB_DGB_Unused_B     = AreaByte(11),
    AB_DGB_Unused_C     = AreaByte(12),
    AB_DGB_Unused_D     = AreaByte(13),
    AB_DGB_Unused_E     = AreaByte(14),
    AB_DGB_Unused_F     = AreaByte(15),
};

enum AreaFlagsDGB {
    AF_DGB_CloseCallWithTubba   = AreaFlag(1),
    AF_DGB11_FallingFromHole               = AreaFlag(2),
    AF_DGB11_SpringInUse               = AreaFlag(3),
    AF_DGB06_ToggleDialogue_Boo = AreaFlag(4),
};
