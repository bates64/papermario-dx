#ifndef _WORLD_AREA_DRO_DRO_H_
#define _WORLD_AREA_DRO_DRO_H_

enum {
    AB_DRO01_DialogueState_Mouser1       = AreaByte(0),
    AB_DRO01_DialogueState_Dryite1       = AreaByte(1),
    AB_DRO01_DialogueState_Dryite2       = AreaByte(2),
    AB_DRO02_DialogueState_Archeologist  = AreaByte(3),
    AB_DRO_SHOP_PREV1   = AreaByte(4),
    AB_DRO_SHOP_PREV2   = AreaByte(5),
    AB_DRO_SHOP_PREV3   = AreaByte(6),
    AB_DRO_Unused_7            = AreaByte(7),
    AB_DRO_Unused_8            = AreaByte(8),
    AB_DRO_Unused_9            = AreaByte(9),
    AB_DRO_Unused_A            = AreaByte(10),
    AB_DRO_Unused_B            = AreaByte(11),
    AB_DRO_Unused_C            = AreaByte(12),
    AB_DRO_Unused_D            = AreaByte(13),
    AB_DRO_Unused_E            = AreaByte(14),
    AB_DRO_Unused_F            = AreaByte(15),
};

enum {
    AF_DRO01_ToggleDialogue_HintDryite = AreaFlag(1),
    AF_DRO01_ToggleDialogue_Composer   = AreaFlag(2),
    AF_DRO02_ToggleDialogue_Dryite2    = AreaFlag(3),
    AF_DRO02_ToggleDialogue_Mouser1    = AreaFlag(4),
    AF_DRO02_ToggleDialogue_Mouser2    = AreaFlag(5),
};

extern MapSettings dro_01_settings;
extern MapSettings dro_02_settings;

#endif
