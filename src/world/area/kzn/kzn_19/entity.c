#include "kzn_19.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $YellowBlock_SuperShroom_1)
    Call(MakeMarkerEntity, $YellowBlock_MapleSyrup_1)
    Return
    End
};
