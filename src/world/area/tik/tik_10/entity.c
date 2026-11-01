#include "tik_10.h"
#include "entity.h"

#define SUPER_BLOCK_MAPVAR MV_SuperBlock
#define SUPER_BLOCK_GAMEFLAG GF_TIK10_SuperBlock
#include "world/common/entity/SuperBlock.inc.c"

EvtScript EVS_MakeEntities = {
    EVT_MAKE_SUPER_BLOCK(-140, 160, -40, 0)
    Call(CreatePushBlockGrid, 0, 7, 6, -64, -15, -94, 0)
    Call(SetPushBlock, 0, 1, 4, PUSH_GRID_BLOCK)
    Call(MakeMarkerEntity, $HiddenYellowBlock_Coin_1)
    Call(UseDynamicShadow, true)
    Call(MakeMarkerEntity, $HiddenYellowBlock_Coin_2)
    Call(UseDynamicShadow, true)
    Call(MakeMarkerEntity, $HiddenYellowBlock_Coin_3)
    Call(UseDynamicShadow, true)
    Return
    End
};
