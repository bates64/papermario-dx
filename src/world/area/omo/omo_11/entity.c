#include "omo_11.h"
#include "entity.h"

#define SUPER_BLOCK_MAPVAR MV_SuperBlock
#define SUPER_BLOCK_GAMEFLAG GF_OMO11_SuperBlock
#include "world/common/entity/SuperBlock.inc.c"

EvtScript EVS_MakeEntities = {
    EVT_MAKE_SUPER_BLOCK(-115, 270, -120, 0)
    Call(MakeMarkerEntity, $MulticoinBlock_1)
    Call(UseDynamicShadow, true)
    Call(MakeMarkerEntity, $HiddenYellowBlock_VoltShroom_1)
    Call(MakeMarkerEntity, $HiddenYellowBlock_SnowmanDoll_1)
    Call(MakeMarkerEntity, $YellowBlock_Coin_1)
    Call(MakeMarkerEntity, $HiddenRedBlock_DeepFocusB_1)
    Call(MakeMarkerEntity, $YellowBlock_Coin_2)
    Return
    End
};
