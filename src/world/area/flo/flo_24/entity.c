#include "flo_24.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $YellowBlock_DizzyDial_1)
    Call(MakeMarkerEntity, $HiddenYellowBlock_MapleSyrup_1)
    Call(MakeMarkerEntity, $HiddenPanel_1)
    Return
    End
};
