#include "mgm_01.h"
#include "entity.h"

EvtScript EVS_ReadSign_HowToPlay = {
    Call(DisablePlayerInput, true)
    Call(SetMsgImgs_Panels)
    Call(ShowMessageAtScreenPos, MSG_MGM_003B, 160, 40)
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Call(MakeEntity, Ref(Entity_Signpost), -55, -2, -80, 0, MAKE_ENTITY_END)
    Call(AssignScript, Ref(EVS_ReadSign_HowToPlay))
    Return
    End
};
