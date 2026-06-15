#pragma once

enum AreaBytesKMR {
    AB_KMR04_JrTroopaAmbushState            = AreaByte(0x0),
    AB_KMR_Unused_1                         = AreaByte(0x1),
    AB_KMR02_DialogueState_Goombaria        = AreaByte(0x2),
    AB_KMR_Unused_3                         = AreaByte(0x3),
    AB_KMR_Unused_4                         = AreaByte(0x4),
    AB_KMR_Unused_5                         = AreaByte(0x5),
    AB_KMR_Unused_6                         = AreaByte(0x6),
    AB_KMR_Unused_7                         = AreaByte(0x7),
    AB_KMR_Unused_8                         = AreaByte(0x8),
    AB_KMR_Unused_9                         = AreaByte(0x9),
    AB_KMR_Unused_A                         = AreaByte(0xA),
    AB_KMR_Unused_B                         = AreaByte(0xB),
    AB_KMR_Unused_C                         = AreaByte(0xC),
    AB_KMR_Unused_D                         = AreaByte(0xD),
    AB_KMR_Unused_E                         = AreaByte(0xE),
    AB_KMR_Unused_F                         = AreaByte(0xF),
};

enum AreaFlagsKMR {
    // AF_KMR_00 - AF_KMR_03 unused
    AF_KMR11_Switch_SelfDestruct            = AreaFlag(0x04),
    // AF_KMR_05 unused
    AF_KMR03_LastHitGoompaWithJump          = AreaFlag(0x06),
    AF_KMR03_HitGoompaWithHammer            = AreaFlag(0x07),
    // AF_KMR_08 unused
    AF_KMR04_DollyDropped                   = AreaFlag(0x09),
    // AF_KMR_0A unused
    AF_KMR20_SpringCanLaunch                = AreaFlag(0x0B),
    AF_KMR20_DiaryBlockedByLuigi            = AreaFlag(0x0C),
    AF_KMR10_LongEntryDelay                 = AreaFlag(0x0D), /// extended delay before entering after prologue Kammy scene
    // AF_KMR_0E - AF_KMR_FF unused
};
