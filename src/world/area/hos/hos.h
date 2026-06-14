#pragma once

enum AreaBytesHOS {
    AB_HOS_StatcAmt_Eldstar                 = AreaByte(0x0),
    AB_HOS_StatcAmt_Mamar                   = AreaByte(0x1),
    AB_HOS_StatcAmt_Skolar                  = AreaByte(0x2),
    AB_HOS_StatcAmt_Muskular                = AreaByte(0x3),
    AB_HOS_StatcAmt_Misstar                 = AreaByte(0x4),
    AB_HOS_StatcAmt_Klevar                  = AreaByte(0x5),
    AB_HOS_StatcAmt_Kalmar                  = AreaByte(0x6),
    AB_HOS_Unused_7                         = AreaByte(0x7),
    AB_HOS_Unused_8                         = AreaByte(0x8),
    AB_HOS_Unused_9                         = AreaByte(0x9),
    AB_HOS_Unused_A                         = AreaByte(0xA),
    AB_HOS_Unused_B                         = AreaByte(0xB),
    AB_HOS_Unused_C                         = AreaByte(0xC),
    AB_HOS_Unused_D                         = AreaByte(0xD),
    AB_HOS_Unused_E                         = AreaByte(0xE),
    AB_HOS_Unused_F                         = AreaByte(0xF),
};

enum AreaFlagsHOS {
    // AF_HOS_00 unused
    // AF_HOS_01 unused
    // AF_HOS_02 unused
    AF_HOS06_BadgeHints                     = AreaFlag(0x03),
    // AF_HOS_04 - AF_HOS_63 unused
    AF_HOS06_SuperBlocksHints               = AreaFlag(0x64),
    // AF_HOS_65 - AF_HOS_73 unused
    AF_HOS06_StarPieceHints                 = AreaFlag(0x74),
    // AF_HOS_75 - AF_HOS_B3 unused
    AF_HOS00_SkipTwinkMeetingDelay          = AreaFlag(0xB4),
    AF_HOS05_SkipMusicChange                = AreaFlag(0xB5),
    AF_HOS06_SpokeWithMerluvlee             = AreaFlag(0xB6),
    // AF_HOS_B7 - AF_HOS_FF unused
};
