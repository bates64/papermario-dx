#pragma once

enum AreaBytesJAN {
    AB_JAN22_ZiplineNpc1                    = AreaByte(0x0),
    AB_JAN22_ZiplineNpc2                    = AreaByte(0x1),
    AB_JAN13_LargeGeyserState               = AreaByte(0x2),
    AB_JAN13_LastPuzzleProgress             = AreaByte(0x3),
    AB_JAN_Unused_4                         = AreaByte(0x4),
    AB_JAN_Unused_5                         = AreaByte(0x5),
    AB_JAN_Unused_6                         = AreaByte(0x6),
    AB_JAN_Unused_7                         = AreaByte(0x7),
    AB_JAN_Unused_8                         = AreaByte(0x8),
    AB_JAN_Unused_9                         = AreaByte(0x9),
    AB_JAN_Unused_A                         = AreaByte(0xA),
    AB_JAN_Unused_B                         = AreaByte(0xB),
    AB_JAN_Unused_C                         = AreaByte(0xC),
    AB_JAN_Unused_D                         = AreaByte(0xD),
    AB_JAN_Unused_E                         = AreaByte(0xE),
    AB_JAN_Unused_F                         = AreaByte(0xF),
};

enum AreaFlagsJAN {
    // AF_JAN_00 unused
    // AF_JAN_01 unused
    AF_JAN_SavedCurrentYoshiKid             = AreaFlag(0x02),
    AF_JAN_PlayingRaphaelVariant            = AreaFlag(0x03),
    AF_JAN02_RaphaelComment                 = AreaFlag(0x04),
    AF_JAN02_MetCouncillor                  = AreaFlag(0x05),
    AF_JAN03_KoloradoLocalsHint             = AreaFlag(0x06),
    AF_JAN03_MetSushieDialogue              = AreaFlag(0x07),
    AF_JAN04_IgnoreSushieTreeHit            = AreaFlag(0x08),
    AF_JAN01_KoloradoShouting               = AreaFlag(0x09),
    AF_JAN22_PauseSpearGuyAttack            = AreaFlag(0x0A),
    AF_JAN22_MisstarReleasedParty           = AreaFlag(0x0B),
    AF_JAN22_MisstarReleasedKolorado        = AreaFlag(0x0C),
    AF_JAN00_TreeDrop1                      = AreaFlag(0x0D),
    AF_JAN01_TreeDrop2                      = AreaFlag(0x0E),
    AF_JAN01_TreeDrop3                      = AreaFlag(0x0F),
    AF_JAN01_TreeDrop4                      = AreaFlag(0x10),
    AF_JAN01_TreeDrop5                      = AreaFlag(0x11),
    AF_JAN01_TreeDrop6                      = AreaFlag(0x12),
    AF_JAN01_TreeDrop7                      = AreaFlag(0x13),
    AF_JAN02_TreeDrop2                      = AreaFlag(0x14),
    AF_JAN02_TreeDrop3                      = AreaFlag(0x15),

    // AF_JAN_16 unused
    AF_JAN03_TreeDrop1                      = AreaFlag(0x17),
    // AF_JAN_18 - AF_JAN_FF unused
};
