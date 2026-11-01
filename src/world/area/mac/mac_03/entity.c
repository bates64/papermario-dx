#include "mac_03.h"
#include "entity.h"

EvtScript EVS_OnBlast_RailRock = {
    Set(GF_MAC03_BombedRock, true)
    Return
    End
};

EvtScript EVS_ReadSign_LilOInks = {
    Call(DisablePlayerInput, true)
    Call(ShowMessageAtScreenPos, MSG_Menus_0175, 160, 40)
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript EVS_OnInspect_StreetSign = {
    Call(DisablePlayerInput, true)
    Call(ShowMessageAtScreenPos, MSG_Menus_0172, 160, 40)
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Call(GetDemoState, LVar0)
    IfEq(LVar0, DEMO_STATE_NONE)
        IfEq(GF_MAC03_BombedRock, false)
            Call(MakeMarkerEntity, $BombableRock_1)
        EndIf
    EndIf
    Call(MakeMarkerEntity, $HiddenPanel_1)
    Call(MakeMarkerEntity, $Signpost_1)
    BindTrigger(EVS_OnInspect_StreetSign, TRIGGER_WALL_PRESS_A, COLLIDER_sign, 1, 0)
    Return
    End
};
