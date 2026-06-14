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
    AB_KKJ19_CurrentBakeStep        = AreaByte(0),
    AB_KKJ_CompletedBakeStep        = AreaByte(1),
    AB_KKJ19_HeldIngredient         = AreaByte(2),
    AB_KKJ19_BakeStepProgress       = AreaByte(3),
    AB_KKJ19_CookwareItemIdx        = AreaByte(4),
    AB_KKJ19_CakeItemIdx            = AreaByte(5),
    AB_KKJ29_AnsweringContestant    = AreaByte(6),
    AB_KKJ29_AnswerScore            = AreaByte(7),
    AB_KKJ29_LeftKoopatrolScore     = AreaByte(8),
    AB_KKJ29_PeachScore             = AreaByte(9),
    AB_KKJ29_RightKoopatrolScore    = AreaByte(10),
    AB_KKJ_Unused_B                 = AreaByte(11),
    AB_KKJ_Unused_C                 = AreaByte(12),
    AB_KKJ_Unused_D                 = AreaByte(13),
    AB_KKJ_Unused_E                 = AreaByte(14),
    AB_KKJ_Unused_F                 = AreaByte(15),
};

enum AreaFlagsKKJ {
    AF_KKJ01_MarioLetIntoBedroom    = AreaFlag(1),
    AF_KKJ01_GuardAskedAboutBedroom = AreaFlag(2),
    AF_KKJ14_TwinkFlightSync        = AreaFlag(3),
    AF_KKJ14_HiddenButtonRemark     = AreaFlag(4),
    AF_KKJ14_HiddenPassageRemark    = AreaFlag(5),
    AF_KKJ_PeachSawGrandHall        = AreaFlag(6),
    AF_KKJ16_HeardSneakingAdvice    = AreaFlag(7),
    AF_KKJ15_LiedAboutWeakPoints    = AreaFlag(8),
    AF_KKJ19_FailedBakingTask       = AreaFlag(9),
    AF_KKJ19_AddedEgg               = AreaFlag(10),
    AF_KKJ19_AddedSugar             = AreaFlag(11),
    AF_KKJ19_AddedFlour             = AreaFlag(12),
    AF_KKJ19_AddedButter            = AreaFlag(13),
    AF_KKJ19_AddedNothingWrong      = AreaFlag(14),
    AF_KKJ19_AddedIcing             = AreaFlag(15),
    AF_KKJ19_AddedBerries           = AreaFlag(16),
    AF_KKJ_FinishedBakingCake       = AreaFlag(17),
    AF_KKJ19_CanTakeIngredients     = AreaFlag(18),
    AF_KKJ14_CaughtUsingDoor        = AreaFlag(19),
    AF_KKJ14_InspectedFireplace     = AreaFlag(20),
    AF_KKJ14_InspectedDresses       = AreaFlag(21),
    AF_KKJ14_InspectedPhoto         = AreaFlag(23),
    AF_KKJ14_InspectedBed           = AreaFlag(24),
    AF_KKJ14_InspectedFlowers       = AreaFlag(25),
    AF_KKJ25_ActivatedArenaSwitch   = AreaFlag(26),
};
