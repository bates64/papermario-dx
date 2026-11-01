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
    Call(MakeMarkerEntity, $Signpost_1)
    Return
    End
};
