#pragma once

enum AreaBytesKZN {
    AB_KZN_LastZiplineNpc1                  = AreaByte(0x0),
    AB_KZN_LastZiplineNpc2                  = AreaByte(0x1),
    AB_KZN_Unused_2                         = AreaByte(0x2),
    AB_KZN_Unused_3                         = AreaByte(0x3),
    AB_KZN_Unused_4                         = AreaByte(0x4),
    AB_KZN_Unused_5                         = AreaByte(0x5),
    AB_KZN_Unused_6                         = AreaByte(0x6),
    AB_KZN_Unused_7                         = AreaByte(0x7),
    AB_KZN_Unused_8                         = AreaByte(0x8),
    AB_KZN_Unused_9                         = AreaByte(0x9),
    AB_KZN_Unused_A                         = AreaByte(0xA),
    AB_KZN_Unused_B                         = AreaByte(0xB),
    AB_KZN_Unused_C                         = AreaByte(0xC),
    AB_KZN_Unused_D                         = AreaByte(0xD),
    AB_KZN_Unused_E                         = AreaByte(0xE),
    AB_KZN_Unused_F                         = AreaByte(0xF),
};

enum AreaFlagsKZN {
    // AF_KZN_00 unused
    // AF_KZN_01 unused
    AF_KZN_TrompRollingDone                 = AreaFlag(0x02),
    AF_KZN_TrompHitPlayer                   = AreaFlag(0x03),
    AF_KZN_Tromp1_ShakingDone               = AreaFlag(0x04),
    AF_KZN_Tromp2_HitKolorado               = AreaFlag(0x05),
    AF_KZN_Tromp2_ShakingDone               = AreaFlag(0x06),
    AF_KZN_Tromp2_StopPlayer                = AreaFlag(0x07),
    AF_KZN_BossRoomFloorBroken              = AreaFlag(0x08),
    AF_KZN20_MisstarFlightDone              = AreaFlag(0x09),
    AF_KZN20_SceneSync                      = AreaFlag(0x0A),
    AF_KZN_RumblingIntensified              = AreaFlag(0x0B),
    AF_KZN23_SceneStarted                   = AreaFlag(0x0C),
    AF_KZN23_MessageClosed                  = AreaFlag(0x0D),
    AF_KZN23_GrabbedKolorado                = AreaFlag(0x0E),
    AF_KZN23_GrabbedPlayer                  = AreaFlag(0x0F),
    AF_KZN22_FlewAway                       = AreaFlag(0x10),
    AF_KZN23_UseAlternateSound              = AreaFlag(0x11),
    AF_KZN04_FireBar1_Coins                 = AreaFlag(0x12),
    AF_KZN04_FireBar2_Coins                 = AreaFlag(0x13),
    AF_KZN04_FireBar3_Coins                 = AreaFlag(0x14),
    AF_KZN11_FireBar1_Coins                 = AreaFlag(0x15),
    AF_KZN11_FireBar2_Coins                 = AreaFlag(0x16),
    AF_KZN11_FireBar3_Coins                 = AreaFlag(0x17),
    // AF_KZN_18 - AF_KZN_FF unused
};
