#include "hos_00.h"
#include "entity.h"

EvtScript EVS_ReadSign_ToSummit = {
    Call(DisablePlayerInput, true)
    Call(ShowMessageAtScreenPos, MSG_Menus_016E, 160, 40)
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript EVS_ReadSign_ToMerluvlee = {
    Call(DisablePlayerInput, true)
    Call(ShowMessageAtScreenPos, MSG_Menus_016D, 160, 40)
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $Signpost_1)
    Call(MakeMarkerEntity, $Signpost_2)
    Call(MakeMarkerEntity, $HiddenPanel_1)
    Return
    End
};
