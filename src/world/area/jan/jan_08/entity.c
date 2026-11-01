#include "jan_08.h"
#include "entity.h"

#define SUPER_BLOCK_MAPVAR MV_SuperBlock
#define SUPER_BLOCK_GAMEFLAG GF_JAN08_SuperBlock
#include "world/common/entity/SuperBlock.inc.c"

EvtScript EVS_MakeEntities = {
    EVT_MAKE_SUPER_BLOCK(250, 60, 300, 0)
    Call(MakeMarkerEntity, $Item_Coin_1)
    Call(MakeMarkerEntity, $Item_Coin_2)
    Call(MakeMarkerEntity, $Item_Coin_3)
    Call(MakeMarkerEntity, $BellbellPlant_1)
    Call(MakeMarkerEntity, $HiddenYellowBlock_ThunderRage_1)
    Call(MakeMarkerEntity, $TrumpetPlant_1)
    Return
    End
};
