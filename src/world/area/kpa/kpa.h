#ifndef _WORLD_AREA_KPA_KPA_H_
#define _WORLD_AREA_KPA_KPA_H_

enum {
    AB_KPA_Unused_0             = AreaByte(0),
    AB_KPA17_Toad1_Dialogue     = AreaByte(1),
    AB_KPA17_Toad2_Dialogue     = AreaByte(2),
    AB_KPA17_Toad3_Dialogue     = AreaByte(3),
    AB_KPA17_Toad4_Dialogue     = AreaByte(4),
    AB_KPA91_Toad2_Dialogue     = AreaByte(5),
    AB_KPA91_Toad3_Dialogue     = AreaByte(6),
    AB_KPA91_Dryite_Dialogue    = AreaByte(7),
    AB_KPA95_Toad2_Dialogue     = AreaByte(8),
    AB_KPA95_Toad3_Dialogue     = AreaByte(9),
    AB_KPA95_Penguin_Dialogue   = AreaByte(10),
    AB_KPA_MazeProgress         = AreaByte(11),
    AB_KPA82_QuizRound          = AreaByte(12),
    AB_KPA82_RightAnswers       = AreaByte(13),
    AB_KPA82_WrongAnswers       = AreaByte(14),
    AB_KPA_Unused_F             = AreaByte(15),
};

enum {
    AF_KPA08_PlatformRaised     = AreaFlag(3),
    AF_KPA09_PlatformRaised     = AreaFlag(4),
    AF_KPA13_HitSwitchA         = AreaFlag(5),
    AF_KPA13_HitSwitchB         = AreaFlag(6),
    AF_KPA16_HitSwitch          = AreaFlag(7),
    AF_KPA133_HitWaterSwitch    = AreaFlag(8),
    AF_KPA134_HitWaterSwitch    = AreaFlag(9),
};

#endif
