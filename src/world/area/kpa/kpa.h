#pragma once

enum AreaBytesKPA {
    AB_KPA_Unused_0                     = AreaByte(0),
    AB_KPA17_DialogueState_Toad1        = AreaByte(1),
    AB_KPA17_DialogueState_Toad2        = AreaByte(2),
    AB_KPA17_DialogueState_ToadGuard    = AreaByte(3),
    AB_KPA17_DialogueState_ToadMinister = AreaByte(4),
    AB_KPA91_DialogueState_Toad2        = AreaByte(5),
    AB_KPA91_DialogueState_ToadGuard    = AreaByte(6),
    AB_KPA91_DialogueState_Dryite       = AreaByte(7),
    AB_KPA95_DialogueState_Toad2        = AreaByte(8),
    AB_KPA95_DialogueState_ToadGuard    = AreaByte(9),
    AB_KPA95_DialogueState_Penguin      = AreaByte(10),
    AB_KPA_MazeProgress                 = AreaByte(11),
    AB_KPA82_QuizRound                  = AreaByte(12),
    AB_KPA82_RightAnswers               = AreaByte(13),
    AB_KPA82_WrongAnswers               = AreaByte(14),
    AB_KPA_Unused_F                     = AreaByte(15),
};

enum AreaFlagsKPA {
    AF_KPA08_PlatformRaised     = AreaFlag(3),
    AF_KPA09_PlatformRaised     = AreaFlag(4),
    AF_KPA13_HitSwitchA         = AreaFlag(5),
    AF_KPA13_HitSwitchB         = AreaFlag(6),
    AF_KPA16_HitSwitch          = AreaFlag(7),
    AF_KPA133_HitWaterSwitch    = AreaFlag(8),
    AF_KPA134_HitWaterSwitch    = AreaFlag(9),
};
