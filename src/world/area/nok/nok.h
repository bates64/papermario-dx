#pragma once
#include "common.h"

enum AreaBytesNOK {
    AB_NOK01_RadioStation                   = AreaByte(0x0),
    AB_NOK13_BlockPuzzleState               = AreaByte(0x1),
    AB_NOK11_KentEntryID                    = AreaByte(0x2),
    AB_NOK_Unused_3                         = AreaByte(0x3),
    AB_NOK_Unused_4                         = AreaByte(0x4),
    AB_NOK_Unused_5                         = AreaByte(0x5),
    AB_NOK_Unused_6                         = AreaByte(0x6),
    AB_NOK_Unused_7                         = AreaByte(0x7),
    AB_NOK_Unused_8                         = AreaByte(0x8),
    AB_NOK_Unused_9                         = AreaByte(0x9),
    AB_NOK_Unused_A                         = AreaByte(0xA),
    AB_NOK_Unused_B                         = AreaByte(0xB),
    AB_NOK_Unused_C                         = AreaByte(0xC),
    AB_NOK_Unused_D                         = AreaByte(0xD),
    AB_NOK_Unused_E                         = AreaByte(0xE),
    AB_NOK_Unused_F                         = AreaByte(0xF),
};

enum AreaFlagsNOK {
    // AF_NOK_00 unused
    AF_NOK12_HitSwitch                      = AreaFlag(0x01),
    AF_NOK14_HitSwitch                      = AreaFlag(0x02),
    AF_NOK04_PlayingGame                    = AreaFlag(0x03),
    AF_NOK04_BattleStarted                  = AreaFlag(0x04),
    AF_NOK04_BattleDone                     = AreaFlag(0x05),
    AF_NOK04_TauntMsgDone                   = AreaFlag(0x06),
    AF_NOK04_FleeMsgDone                    = AreaFlag(0x07),
    AF_NOK04_CamPanDone                     = AreaFlag(0x08),
    AF_NOK01_ToggleDialogue_RelaxedKoopa    = AreaFlag(0x09),
    AF_NOK01_ToggleDialogue_Bobomb1Crisis   = AreaFlag(0x0A),
    AF_NOK01_ToggleDialogue_Bobomb1         = AreaFlag(0x0B),
    AF_NOK01_ToggleDialogue_Bobomb2         = AreaFlag(0x0C),
    // AF_NOK_0D unused
    AF_NOK01_RecievedBobombSalute           = AreaFlag(0x0E),
    AF_NOK02_DeclinedBobombInvite           = AreaFlag(0x0F),
    AF_NOK02_InsideKoopersHouse             = AreaFlag(0x10),
    AF_NOK02_PauseBobombFight               = AreaFlag(0x11),
    AF_NOK02_PauseKooperFightSounds         = AreaFlag(0x12),
    AF_NOK02_FuzzyTreeHit                   = AreaFlag(0x13),
    // AF_NOK_14 unused
    AF_NOK02_KoloradoRequestedArtifact      = AreaFlag(0x15),
    // AF_NOK_16 - AF_NOK_FF unused
};
