#pragma once
#include "common.h"

enum AreaBytesNOK {
    AB_NOK01_RadioStation                   = AreaByte(0),
    AB_NOK13_BlockPuzzleState               = AreaByte(1),
    AB_NOK11_KentEntryID                    = AreaByte(2),
    AB_NOK_Unused_3                         = AreaByte(3),
    AB_NOK_Unused_4                         = AreaByte(4),
    AB_NOK_Unused_5                         = AreaByte(5),
    AB_NOK_Unused_6                         = AreaByte(6),
    AB_NOK_Unused_7                         = AreaByte(7),
    AB_NOK_Unused_8                         = AreaByte(8),
    AB_NOK_Unused_9                         = AreaByte(9),
    AB_NOK_Unused_A                         = AreaByte(10),
    AB_NOK_Unused_B                         = AreaByte(11),
    AB_NOK_Unused_C                         = AreaByte(12),
    AB_NOK_Unused_D                         = AreaByte(13),
    AB_NOK_Unused_E                         = AreaByte(14),
    AB_NOK_Unused_F                         = AreaByte(15),
};

enum AreaFlagsNOK {
    // AF_NOK_00 unused
    AF_NOK12_HitSwitch                      = AreaFlag(1),
    AF_NOK14_HitSwitch                      = AreaFlag(2),
    AF_NOK04_PlayingGame                    = AreaFlag(3),
    AF_NOK04_BattleStarted                  = AreaFlag(4),
    AF_NOK04_BattleDone                     = AreaFlag(5),
    AF_NOK04_TauntMsgDone                   = AreaFlag(6),
    AF_NOK04_FleeMsgDone                    = AreaFlag(7),
    AF_NOK04_CamPanDone                     = AreaFlag(8),
    AF_NOK01_ToggleDialogue_RelaxedKoopa    = AreaFlag(9),
    AF_NOK01_ToggleDialogue_Bobomb1Crisis   = AreaFlag(10),
    AF_NOK01_ToggleDialogue_Bobomb1         = AreaFlag(11),
    AF_NOK01_ToggleDialogue_Bobomb2         = AreaFlag(12),
    AF_NOK01_RecievedBobombSalute           = AreaFlag(14),
    AF_NOK02_DeclinedBobombInvite           = AreaFlag(15),
    AF_NOK02_InsideKoopersHouse             = AreaFlag(16),
    AF_NOK02_PauseBobombFight               = AreaFlag(17),
    AF_NOK02_PauseKooperFightSounds         = AreaFlag(18),
    AF_NOK02_FuzzyTreeHit                   = AreaFlag(19),
    AF_NOK02_KoloradoRequestedArtifact      = AreaFlag(21),
    // AF_NOK_16 - AF_NOK_FF unused
};
