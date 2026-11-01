#include "flo_13.h"
#include "entity.h"

EvtScript EVS_OnBlast_Rock = {
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o85, COLLIDER_FLAGS_UPPER_MASK)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $Item_MegaSmash_1)
    Call(MakeMarkerEntity, $Item_ShootingStar_1)
    IfEq(GF_FLO13_Item_MegaSmash, false)
        Call(MakeMarkerEntity, $BombableRock_1)
    Else
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o85, COLLIDER_FLAGS_UPPER_MASK)
    EndIf
    Return
    End
};
