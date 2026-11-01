#include "arn_10.h"
#include "entity.h"

EvtScript EVS_ReadSign = {
    Call(DisablePlayerInput, true)
    Call(ShowMessageAtScreenPos, MSG_Menus_0182, 160, 40)
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Call(MakeEntity, Entity_Signpost, 200, 0, -40, 0, MAKE_ENTITY_END)
    Call(AssignScript, EVS_ReadSign)
    Return
    End
};
