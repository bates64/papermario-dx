
#include "sbk_56.h"
#include "entity.h"

#define SUPER_BLOCK_MAPVAR MV_SuperBlock
#define SUPER_BLOCK_GAMEFLAG GF_SBK56_SuperBlock
#include "world/common/entity/SuperBlock.inc.c"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $HeartBlock_1)
    EVT_MAKE_SUPER_BLOCK(-50, 60, 275, 0)
    Return
    End
};
