#include "common.h"
#include "hud_element.h"

HudScript HES_HandPointDownLoop = {
    hs_SetVisible
    hs_SetTileSize(HUD_ELEMENT_SIZE_24x24)
    hs_Loop
        hs_SetTexelOffset(0, -1)
        hs_SetIcon(1, anim_hand_0)
        hs_SetTexelOffset(0, -1)
        hs_SetIcon(1, anim_hand_0)
        hs_SetTexelOffset(0, -1)
        hs_SetIcon(1, anim_hand_0)
        hs_SetTexelOffset(0, -1)
        hs_SetIcon(1, anim_hand_0)
        hs_SetTexelOffset(2, -1)
        hs_SetIcon(1, anim_hand_1)
        hs_SetTexelOffset(2, -1)
        hs_SetIcon(1, anim_hand_2)
        hs_SetTexelOffset(2, -1)
        hs_SetIcon(4, anim_hand_3)
        hs_SetTexelOffset(2, 4)
        hs_SetIcon(1, anim_hand_1)
        hs_SetTexelOffset(0, 3)
        hs_SetIcon(1, anim_hand_0)
        hs_SetTexelOffset(0, -1)
        hs_SetIcon(14, anim_hand_4)
    hs_Restart
    hs_End
};

HudScript HES_HandPointDown = {
    hs_SetVisible
    hs_SetTileSize(HUD_ELEMENT_SIZE_24x24)
    hs_SetTexelOffset(0, -1)
    hs_SetIcon(1, anim_hand_0)
    hs_SetTexelOffset(2, -1)
    hs_SetIcon(1, anim_hand_1)
    hs_SetTexelOffset(2, -1)
    hs_SetIcon(1, anim_hand_2)
    hs_SetTexelOffset(2, -1)
    hs_SetIcon(4, anim_hand_3)
    hs_SetTexelOffset(2, 4)
    hs_SetIcon(1, anim_hand_1)
    hs_SetTexelOffset(0, 3)
    hs_SetIcon(1, anim_hand_0)
    hs_SetTexelOffset(0, -1)
    hs_SetIcon(2, anim_hand_4)
    hs_SetTexelOffset(0, 3)
    hs_Loop
        hs_SetIcon(60, anim_hand_0)
    hs_Restart
    hs_End
};

HudScript HES_HandPointDownHeld = {
    hs_SetVisible
    hs_SetTileSize(HUD_ELEMENT_SIZE_24x24)
    hs_Loop
        hs_SetIcon(60, anim_hand_0)
    hs_Restart
    hs_End
};

HudScript HES_HandPointLeftLoop = {
    hs_SetVisible
    hs_SetTileSize(HUD_ELEMENT_SIZE_24x24)
    hs_Loop
        hs_SetTexelOffset(0, 0)
        hs_SetIcon(1, anim_hand_5)
        hs_SetTexelOffset(0, 0)
        hs_SetIcon(1, anim_hand_5)
        hs_SetTexelOffset(0, 0)
        hs_SetIcon(1, anim_hand_5)
        hs_SetTexelOffset(0, 0)
        hs_SetIcon(1, anim_hand_5)
        hs_SetTexelOffset(0, -1)
        hs_SetIcon(1, anim_hand_6)
        hs_SetTexelOffset(0, -1)
        hs_SetIcon(1, anim_hand_7)
        hs_SetTexelOffset(1, -3)
        hs_SetIcon(4, anim_hand_8)
        hs_SetTexelOffset(0, 4)
        hs_SetIcon(1, anim_hand_6)
        hs_SetTexelOffset(0, 4)
        hs_SetIcon(1, anim_hand_5)
        hs_SetTexelOffset(0, 1)
        hs_SetIcon(14, anim_hand_9)
    hs_Restart
    hs_End
};

HudScript HES_HandPointLeft = {
    hs_SetVisible
    hs_SetTileSize(HUD_ELEMENT_SIZE_24x24)
    hs_SetTexelOffset(0, 0)
    hs_SetIcon(1, anim_hand_5)
    hs_SetTexelOffset(0, -1)
    hs_SetIcon(1, anim_hand_6)
    hs_SetTexelOffset(0, -1)
    hs_SetIcon(1, anim_hand_7)
    hs_SetTexelOffset(1, -3)
    hs_SetIcon(4, anim_hand_8)
    hs_SetTexelOffset(0, 4)
    hs_SetIcon(1, anim_hand_6)
    hs_SetTexelOffset(0, 4)
    hs_SetIcon(1, anim_hand_5)
    hs_SetTexelOffset(0, 1)
    hs_SetIcon(2, anim_hand_9)
    hs_SetTexelOffset(0, 4)
    hs_Loop
        hs_SetIcon(60, anim_hand_5)
    hs_Restart
    hs_End
};

HudScript HES_HandPointLeftHeld = {
    hs_SetVisible
    hs_SetTileSize(HUD_ELEMENT_SIZE_24x24)
    hs_Loop
        hs_SetIcon(60, anim_hand_5)
    hs_Restart
    hs_End
};
