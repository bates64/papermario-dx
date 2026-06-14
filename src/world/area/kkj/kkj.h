#pragma once

enum {
    CAKE_TYPE_NONE              = 0, // cake has not been started
    CAKE_TYPE_BEGUN             = 1, // the cake has been imagined
    CAKE_TYPE_READY_TO_MIX      = 2, // added sugar and eggs
    CAKE_TYPE_MIXED             = 3, // mixed the batter
    CAKE_TYPE_READY_TO_BAKE     = 4, // added flour and butter
    CAKE_TYPE_BAKED             = 5, // baked in the oven
    CAKE_TYPE_DONE              = 6, // decorated
};

enum AreaBytesKKJ {
    AB_KKJ19_CurrentBakeStep                = AreaByte(0x0),
    AB_KKJ_CompletedBakeStep                = AreaByte(0x1),
    AB_KKJ19_HeldIngredient                 = AreaByte(0x2),
    AB_KKJ19_BakeStepProgress               = AreaByte(0x3),
    AB_KKJ19_CookwareItemIdx                = AreaByte(0x4),
    AB_KKJ19_CakeItemIdx                    = AreaByte(0x5),
    AB_KKJ29_AnsweringContestant            = AreaByte(0x6),
    AB_KKJ29_AnswerScore                    = AreaByte(0x7),
    AB_KKJ29_LeftKoopatrolScore             = AreaByte(0x8),
    AB_KKJ29_PeachScore                     = AreaByte(0x9),
    AB_KKJ29_RightKoopatrolScore            = AreaByte(0xA),
    AB_KKJ_Unused_B                         = AreaByte(0xB),
    AB_KKJ_Unused_C                         = AreaByte(0xC),
    AB_KKJ_Unused_D                         = AreaByte(0xD),
    AB_KKJ_Unused_E                         = AreaByte(0xE),
    AB_KKJ_Unused_F                         = AreaByte(0xF),
};

enum AreaFlagsKKJ {
    // AF_KKJ_00 unused
    AF_KKJ01_MarioLetIntoBedroom            = AreaFlag(0x01),
    AF_KKJ01_GuardAskedAboutBedroom         = AreaFlag(0x02),
    AF_KKJ14_TwinkFlightSync                = AreaFlag(0x03),
    AF_KKJ14_HiddenButtonRemark             = AreaFlag(0x04),
    AF_KKJ14_HiddenPassageRemark            = AreaFlag(0x05),
    AF_KKJ_PeachSawGrandHall                = AreaFlag(0x06),
    AF_KKJ16_HeardSneakingAdvice            = AreaFlag(0x07),
    AF_KKJ15_LiedAboutWeakPoints            = AreaFlag(0x08),
    AF_KKJ19_FailedBakingTask               = AreaFlag(0x09),
    AF_KKJ19_AddedEgg                       = AreaFlag(0x0A),
    AF_KKJ19_AddedSugar                     = AreaFlag(0x0B),
    AF_KKJ19_AddedFlour                     = AreaFlag(0x0C),
    AF_KKJ19_AddedButter                    = AreaFlag(0x0D),
    AF_KKJ19_AddedNothingWrong              = AreaFlag(0x0E),
    AF_KKJ19_AddedIcing                     = AreaFlag(0x0F),
    AF_KKJ19_AddedBerries                   = AreaFlag(0x10),
    AF_KKJ_FinishedBakingCake               = AreaFlag(0x11),
    AF_KKJ19_CanTakeIngredients             = AreaFlag(0x12),
    AF_KKJ14_CaughtUsingDoor                = AreaFlag(0x13),
    AF_KKJ14_InspectedFireplace             = AreaFlag(0x14),
    AF_KKJ14_InspectedDresses               = AreaFlag(0x15),
    // AF_KKJ_16 unused
    AF_KKJ14_InspectedPhoto                 = AreaFlag(0x17),
    AF_KKJ14_InspectedBed                   = AreaFlag(0x18),
    AF_KKJ14_InspectedFlowers               = AreaFlag(0x19),
    AF_KKJ25_ActivatedArenaSwitch           = AreaFlag(0x1A),
    // AF_KKJ_1B - AF_KKJ_FF unused
};
