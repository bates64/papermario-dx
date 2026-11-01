#include "arn_12.h"
#include "entity.h"

EvtScript EVS_ReadSign = {
    Call(DisablePlayerInput, true)
    Call(ShowMessageAtScreenPos, MSG_Menus_0183, 160, 40)
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $Signpost_1)
    Return
    End
};
