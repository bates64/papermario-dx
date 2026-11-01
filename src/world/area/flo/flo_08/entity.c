#include "flo_08.h"
#include "entity.h"

#define SUPER_BLOCK_MAPVAR MV_SuperBlock
#define SUPER_BLOCK_GAMEFLAG GF_FLO08_SuperBlock
#include "world/common/entity/SuperBlock.inc.c"

EvtScript EVS_MakeEntities = {
    EVT_MAKE_SUPER_BLOCK(-780, 120, -110, 0)
    Call(MakeMarkerEntity, $Item_StarPiece_1)
    Return
    End
};
