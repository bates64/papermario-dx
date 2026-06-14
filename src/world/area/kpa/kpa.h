#pragma once

enum AreaBytesKPA {
    AB_KPA_Unused_0                         = AreaByte(0x0),
    AB_KPA17_DialogueState_Toad1            = AreaByte(0x1),
    AB_KPA17_DialogueState_Toad2            = AreaByte(0x2),
    AB_KPA17_DialogueState_ToadGuard        = AreaByte(0x3),
    AB_KPA17_DialogueState_ToadMinister     = AreaByte(0x4),
    AB_KPA91_DialogueState_Toad2            = AreaByte(0x5),
    AB_KPA91_DialogueState_ToadGuard        = AreaByte(0x6),
    AB_KPA91_DialogueState_Dryite           = AreaByte(0x7),
    AB_KPA95_DialogueState_Toad2            = AreaByte(0x8),
    AB_KPA95_DialogueState_ToadGuard        = AreaByte(0x9),
    AB_KPA95_DialogueState_Penguin          = AreaByte(0xA),
    AB_KPA_MazeProgress                     = AreaByte(0xB),
    AB_KPA82_QuizRound                      = AreaByte(0xC),
    AB_KPA82_RightAnswers                   = AreaByte(0xD),
    AB_KPA82_WrongAnswers                   = AreaByte(0xE),
    AB_KPA_Unused_F                         = AreaByte(0xF),
};

enum AreaFlagsKPA {
    // AF_KPA_00 unused
    // AF_KPA_01 unused
    // AF_KPA_02 unused
    AF_KPA08_PlatformRaised                 = AreaFlag(0x03),
    AF_KPA09_PlatformRaised                 = AreaFlag(0x04),
    AF_KPA13_HitSwitchA                     = AreaFlag(0x05),
    AF_KPA13_HitSwitchB                     = AreaFlag(0x06),
    AF_KPA16_HitSwitch                      = AreaFlag(0x07),
    AF_KPA133_HitWaterSwitch                = AreaFlag(0x08),
    AF_KPA134_HitWaterSwitch                = AreaFlag(0x09),
    // AF_KPA_0A - AF_KPA_FF unused
};
