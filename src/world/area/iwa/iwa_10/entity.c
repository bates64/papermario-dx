#include "iwa_10.h"
#include "entity.h"

#define SUPER_BLOCK_MAPVAR MV_SuperBlock
#define SUPER_BLOCK_GAMEFLAG GF_IWA10_SuperBlock
#include "world/common/entity/SuperBlock.inc.c"

EvtScript EVS_OnSmashBlock = {
    Set(GF_IWA10_Hammer1Block, true)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    IfEq(GF_IWA10_Hammer1Block, false)
        Call(MakeMarkerEntity, $Hammer2BlockWideZ_1)
    EndIf
    EVT_MAKE_SUPER_BLOCK(-1350, 220, -210, 0)
    Call(MakeMarkerEntity, $ArrowSign_1)
    Call(MakeMarkerEntity, $ArrowSign_2)
    Call(MakeMarkerEntity, $ArrowSign_3)
    Call(MakeMarkerEntity, $SavePoint_1)
    Call(MakeMarkerEntity, $HeartBlock_1)
    Return
    End
};
