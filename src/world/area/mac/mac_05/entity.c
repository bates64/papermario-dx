#include "mac_05.h"
#include "entity.h"

EvtScript EVS_OnInspect_StreetSign = {
    Call(DisablePlayerInput, true)
    Call(ShowMessageAtScreenPos, MSG_Menus_0174, 160, 40)
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript EVS_OnInspect_Menu = {
    Call(DisablePlayerInput, true)
    Call(ShowMessageAtScreenPos, MSG_Menus_016C, 160, 40)
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $SavePoint_1)
    Call(MakeMarkerEntity, $HiddenPanel_1)
    Call(MakeMarkerEntity, $MulticoinBlock_1)
    BindTrigger(EVS_OnInspect_StreetSign, TRIGGER_WALL_PRESS_A, COLLIDER_sign, 1, 0)
    BindTrigger(EVS_OnInspect_Menu, TRIGGER_WALL_PRESS_A, COLLIDER_o154, 1, 0)
    Return
    End
};
