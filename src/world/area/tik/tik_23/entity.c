#include "tik_23.h"
#include "entity.h"

EvtScript EVS_OnSmashBlock = {
    Set(GF_TIK23_Hammer2Block, true)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o102, COLLIDER_FLAGS_UPPER_MASK)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    IfEq(GF_TIK23_Hammer2Block, false)
        Call(MakeMarkerEntity, $Hammer2Block_1)
    Else
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o102, COLLIDER_FLAGS_UPPER_MASK)
    EndIf
    Call(MakeMarkerEntity, $HiddenYellowBlock_MapleSyrup_1)
    Call(MakeMarkerEntity, $HiddenYellowBlock_StopWatch_1)
    Call(MakeMarkerEntity, $HiddenYellowBlock_VoltShroom_1)
    Call(MakeMarkerEntity, $YellowBlock_Coin_1)
    Return
    End
};
