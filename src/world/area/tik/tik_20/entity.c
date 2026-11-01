#include "tik_20.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $YellowBlock_ShootingStar_1)
    Return
    End
};
