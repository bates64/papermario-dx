#include "mac_00.h"
#include "entity.h"

EvtScript EVS_Inspect_StreetSign = {
    Call(DisablePlayerInput, true)
    Call(ShowMessageAtScreenPos, MSG_Menus_016F, 160, 40)
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $HiddenPanel_1)
    Call(MakeMarkerEntity, $Item_StarPiece_1)
    BindTrigger(EVS_Inspect_StreetSign, TRIGGER_WALL_PRESS_A, COLLIDER_sign, 1, 0)
    Return
    End
};
