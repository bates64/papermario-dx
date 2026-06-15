#pragma once
#include "common.h"

// TODO this is very confusing, along with AB_MIM_GateTraversal
// All the names are likely wrong but the purpose of each and
// their interations are unclear.
enum ForestGateStates {
    MIM_USEGATE_SIDE_A  = 0,
    MIM_USEGATE_INNER  = 1,
    MIM_USEGATE_SIDE_B  = 2,
};

enum AreaBytesMIM {
    AB_MIM_Unused_0                         = AreaByte(0x0),
    AB_MIM_GateTraversal                    = AreaByte(0x1),
    AB_MIM_PrevMapID                        = AreaByte(0x2),
    AB_MIM_Unused_3                         = AreaByte(0x3),
    AB_MIM_Unused_4                         = AreaByte(0x4),
    AB_MIM_Unused_5                         = AreaByte(0x5),
    AB_MIM_Unused_6                         = AreaByte(0x6),
    AB_MIM_Unused_7                         = AreaByte(0x7),
    AB_MIM_Unused_8                         = AreaByte(0x8),
    AB_MIM_Unused_9                         = AreaByte(0x9),
    AB_MIM_Unused_A                         = AreaByte(0xA),
    AB_MIM_Unused_B                         = AreaByte(0xB),
    AB_MIM_Unused_C                         = AreaByte(0xC),
    AB_MIM_Unused_D                         = AreaByte(0xD),
    AB_MIM_Unused_E                         = AreaByte(0xE),
    AB_MIM_Unused_F                         = AreaByte(0xF),
};

enum AreaFlagsMIM {
    // AF_MIM_00 unused
    AF_MIM11_MansionGateOpen                = AreaFlag(0x01),
    AF_MIM03_ToggleDialogue_Oaklie          = AreaFlag(0x02),
    AF_MIM12_BackgroundLitUp                = AreaFlag(0x03),
    AF_MIM04_ToggleDialogue_Bubulb          = AreaFlag(0x04),
    // AF_MIM_05 - AF_MIM_FF unused
};
