#pragma once

enum AreaBytesFLO {
    AB_FLO00_DialogueState_Tolielup         = AreaByte(0x0),
    AB_FLO03_DialogueState_Petunia          = AreaByte(0x1),
    AB_FLO_CrystalTreeHitCount              = AreaByte(0x2),
    AB_FLO_PoiseKickedOutCount              = AreaByte(0x3),
    AB_FLO_TreePuzzle_FirstCorrect          = AreaByte(0x4),
    AB_FLO_TreePuzzle_SecondCorrect         = AreaByte(0x5),
    AB_FLO_GuardLakituTalkCount             = AreaByte(0x6),
    AB_FLO_GuardedMachineHitCount           = AreaByte(0x7),
    AB_FLO_Unused_8                         = AreaByte(0x8),
    AB_FLO_Unused_9                         = AreaByte(0x9),
    AB_FLO_Unused_A                         = AreaByte(0xA),
    AB_FLO_Unused_B                         = AreaByte(0xB),
    AB_FLO_Unused_C                         = AreaByte(0xC),
    AB_FLO_Unused_D                         = AreaByte(0xD),
    AB_FLO_Unused_E                         = AreaByte(0xE),
    AB_FLO_Unused_F                         = AreaByte(0xF),
};

enum AreaFlagsFLO {
    // flo_07
    // AF_FLO_00 - AF_FLO_04 unused
    AF_FLO07_ToggleDialogue_Posie           = AreaFlag(0x05),
    AF_FLO_MadeCrystalBerry                 = AreaFlag(0x06),
    // flo_00
    // AF_FLO_07 - AF_FLO_0F unused
    AF_FLO_BeanstalkFacingRight             = AreaFlag(0x10),
    AF_FLO_PlatingInstructionsToggle        = AreaFlag(0x11),
    AF_FLO00_ToggleDialogue_PinkBubulb      = AreaFlag(0x12),
    AF_FLO00_ToggleDialogue_PurpleBubulb    = AreaFlag(0x13),
    AF_FLO00_ToggleDialogue_GreenBubulb     = AreaFlag(0x14),
    AF_FLO00_ToggleDialogue_YellowBubulb    = AreaFlag(0x15),
    // flo_12
    AF_FLO_GivenCrystalBerry                = AreaFlag(0x16),
    // flo_03
    AF_FLO_IsUnderground_Mole_01            = AreaFlag(0x17),
    AF_FLO_IsUnderground_Mole_02            = AreaFlag(0x18),
    AF_FLO_IsUnderground_Mole_03            = AreaFlag(0x19),
    AF_FLO_IsUnderground_Mole_04            = AreaFlag(0x1A),
    AF_FLO_TreeDrop_RedBerry1               = AreaFlag(0x1B),
    AF_FLO_TreeDrop_RedBerry2               = AreaFlag(0x1C),
    // flo_08
    AF_FLO_TreeDrop_BlueBerry1              = AreaFlag(0x1D),
    AF_FLO_TreeDrop_BlueBerry2              = AreaFlag(0x1E),
    // flo_24
    AF_FLO_TreeDrop_BubbleBerry1            = AreaFlag(0x1F),
    AF_FLO_TreeDrop_BubbleBerry2            = AreaFlag(0x20),
    // flo_25
    AF_FLO_TreeDrop_YellowBerry1            = AreaFlag(0x21),
    AF_FLO_TreeDrop_YellowBerry2            = AreaFlag(0x22),
    // flo_14
    AF_FLO_PauseBlowingBubbles              = AreaFlag(0x23),
    AF_FLO_BlowingBigBubble                 = AreaFlag(0x24),
    AF_FLO_BigBubbleReady                   = AreaFlag(0x25),
    // flo_15
    AF_FLO_MetTheSun                        = AreaFlag(0x26),
    // flo_16
    AF_FLO16_FoundHiddenStarPiece           = AreaFlag(0x27),
    // flo_19
    AF_FLO_BeanstalkGrowing                 = AreaFlag(0x28),
    // flo_16
    AF_FLO_RaisedRedPillar                  = AreaFlag(0x29),
    AF_FLO_RaisedGreenPillar                = AreaFlag(0x2A),
    AF_FLO_LoweredPurplePillar              = AreaFlag(0x2B),
    AF_FLO_RidingBeanstalk                  = AreaFlag(0x2C),
    AF_FLO_BeanstalkFadedOut                = AreaFlag(0x2D),
    // AF_FLO_2E - AF_FLO_FF unused
};
