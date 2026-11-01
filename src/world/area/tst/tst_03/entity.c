#include "tst_03.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $RedBlock_None_1)
    Call(MakeMarkerEntity, $HiddenRedBlock_None_1)
    Call(MakeMarkerEntity, $InertYellowBlock_1)
    Call(MakeMarkerEntity, $BrickBlock_1)
    Call(MakeMarkerEntity, $MulticoinBlock_1)
    Call(MakeMarkerEntity, $YellowBlock_Coin_1)
    Call(MakeMarkerEntity, $TriggerBlock_1)
    Call(MakeMarkerEntity, $HiddenYellowBlock_Mushroom_1)
    Call(MakeEntity, Entity_SuperBlock, 300, 60, 160, 0, MAKE_ENTITY_END)
    Call(MakeMarkerEntity, $HeartBlock_1)
    Call(MakeMarkerEntity, $SavePoint_1)
    Call(MakeMarkerEntity, $PowBlock_1)
    Call(MakeMarkerEntity, $Hammer1BlockTiny_1)
    Call(MakeMarkerEntity, $Hammer1BlockTiny_2)
    Call(MakeMarkerEntity, $Hammer2BlockTiny_1)
    Call(MakeMarkerEntity, $Hammer3BlockTiny_1)
    Call(MakeMarkerEntity, $PowBlock_2)
    Call(MakeMarkerEntity, $BoardedFloor_1)
    Call(MakeMarkerEntity, $WoodenCrate_1)
    Call(MakeMarkerEntity, $WoodenCrate_2)
    Call(MakeMarkerEntity, $WoodenCrate_3)
    Return
    End
};
