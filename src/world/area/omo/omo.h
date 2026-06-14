#pragma once

// "CrowdScript" used in omo_02 and omo_15
enum {
    op_CS_MOVE      = 0,
    op_CS_JUMP      = 1,
    op_CS_FALL      = 2,
    op_CS_END       = -1,
};

#define CS_MOVE(x, y)       op_CS_MOVE, x, y,
#define CS_JUMP(x, y, z)    op_CS_JUMP, x, y, z,
#define CS_FALL()           op_CS_FALL,
#define CS_END              op_CS_END,

enum AreaBytesOMO {
    AB_OMO_Unused_0                         = AreaByte(0x0),
    AB_OMO12_LightSource                    = AreaByte(0x1),
    AB_OMO12_LightPowerMod                  = AreaByte(0x2),
    AB_OMO09_IsPlayerNearSlotMachine        = AreaByte(0x3),
    AB_OMO_CurrentPeachChoice               = AreaByte(0x4),
    AB_OMO_TrainOrigin                      = AreaByte(0x5),
    AB_OMO_TrainDest                        = AreaByte(0x6),
    AB_OMO_Unused_7                         = AreaByte(0x7),
    AB_OMO_Unused_8                         = AreaByte(0x8),
    AB_OMO_Unused_9                         = AreaByte(0x9),
    AB_OMO_Unused_A                         = AreaByte(0xA),
    AB_OMO_Unused_B                         = AreaByte(0xB),
    AB_OMO_Unused_C                         = AreaByte(0xC),
    AB_OMO_Unused_D                         = AreaByte(0xD),
    AB_OMO_Unused_E                         = AreaByte(0xE),
    AB_OMO_Unused_F                         = AreaByte(0xF),
};

enum AreaFlagsOMO {
    // AF_OMO_00 unused
    // AF_OMO_01 unused
    AF_OMO_UsingRightSwitch                 = AreaFlag(0x02),
    AF_OMO_TrainSoundToggle                 = AreaFlag(0x03),
    AF_OMO03_EnteringViaSpring              = AreaFlag(0x04), // prevents the spring from immediately launching the player back out
    AF_OMO03_ToggleDialogue_Conductor       = AreaFlag(0x05),
    AF_OMO03_TrainStuck                     = AreaFlag(0x06),
    AF_OMO07_NpcPool0                       = AreaFlag(0x07),
    AF_OMO07_NpcPool1                       = AreaFlag(0x08),
    AF_OMO07_NpcPool2                       = AreaFlag(0x09),
    AF_OMO07_NpcPool3                       = AreaFlag(0x0A),
    AF_OMO09_StartBlock_DontBlink           = AreaFlag(0x0B),
    AF_OMO09_Block1_DontBlink               = AreaFlag(0x0C),
    AF_OMO09_Block2_DontBlink               = AreaFlag(0x0D),
    AF_OMO09_Block3_DontBlink               = AreaFlag(0x0E),
    AF_OMO07_DoorOpening                    = AreaFlag(0x0F),
    AF_OMO12_StopLanternFlicker             = AreaFlag(0x10),
    // AF_OMO_11 - AF_OMO_FF unused
};
