#include "tik_07.h"
#include "entity.h"

#define SUPER_BLOCK_MAPVAR MV_SuperBlock
#define SUPER_BLOCK_GAMEFLAG GF_TIK07_SuperBlock
#include "world/common/entity/SuperBlock.inc.c"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $Item_StarPiece_1)
    EVT_MAKE_SUPER_BLOCK(820, 70, -5, 0)
    Return
    End
};
