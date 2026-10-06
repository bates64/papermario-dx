#include "sbk_36.h"
#include "entity.h"

EvtScript ReadSign = {
    SetGroup(EVT_GROUP_NEVER_PAUSE)
    Call(SetTimeFreezeMode, TIME_FREEZE_PARTIAL)
    Call(DisablePlayerInput, true)
    Call(ShowMessageAtScreenPos, MSG_Menus_017A, 160, 40)
    Call(DisablePlayerInput, false)
    Call(SetTimeFreezeMode, TIME_FREEZE_NONE)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Call(MakeEntity, Ref(Entity_Signpost), 410, 0, -75, 0, MAKE_ENTITY_END)
    Call(AssignScript, Ref(ReadSign))
    Return
    End
};
