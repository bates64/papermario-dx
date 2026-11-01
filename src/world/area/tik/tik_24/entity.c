#include "tik_24.h"
#include "entity.h"

EvtScript EVS_OnSmashBlock = {
    Set(GF_TIK24_Hammer3Block, true)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o44, COLLIDER_FLAGS_UPPER_MASK)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    IfEq(GF_TIK24_Hammer3Block, false)
        Call(MakeMarkerEntity, $Hammer3Block_1)
    Else
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o44, COLLIDER_FLAGS_UPPER_MASK)
    EndIf
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o45, COLLIDER_FLAGS_UPPER_MASK)
    Call(MakeMarkerEntity, $HiddenYellowBlock_LifeShroom_1)
    Call(MakeMarkerEntity, $YellowBlock_Coin_1)
    Call(MakeMarkerEntity, $YellowBlock_Coin_2)
    Call(MakeMarkerEntity, $BrickBlock_1)
    Call(MakeMarkerEntity, $BrickBlock_2)
    Call(MakeMarkerEntity, $BrickBlock_3)
    Call(MakeMarkerEntity, $BrickBlock_4)
    Return
    End
};
