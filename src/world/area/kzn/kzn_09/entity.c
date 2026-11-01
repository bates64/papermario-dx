#include "kzn_09.h"
#include "entity.h"

#define SUPER_BLOCK_MAPVAR MV_SuperBlock
#define SUPER_BLOCK_GAMEFLAG GF_KZN09_SuperBlock
#include "world/common/entity/SuperBlock.inc.c"

EvtScript EVS_MakeEntities = {
    EVT_MAKE_SUPER_BLOCK(130, 480, -75, 0)
    Call(MakeMarkerEntity, $HiddenPanel_1)
    Return
    End
};
