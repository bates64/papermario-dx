#include "kpa_111.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $YellowBlock_SuperShroom_1)
    Call(MakeMarkerEntity, $HiddenYellowBlock_MapleSyrup_1)
    Return
    End
};
