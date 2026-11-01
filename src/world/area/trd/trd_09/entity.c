#include "trd_09.h"
#include "entity.h"

EvtScript EVS_BombRock = {
    Set(GF_TRD09_BombedRock, true)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    IfEq(GF_TRD09_BombedRock, false)
        Call(MakeEntity, Entity_BombableRockWide, -470, -75, 139, 0, MAKE_ENTITY_END)
        Call(AssignScript, EVS_BombRock)
    EndIf
    Call(MakeEntity, Entity_HeartBlock, 1400, -15, 135, 0, MAKE_ENTITY_END)
    Call(MakeEntity, Entity_SavePoint, 1490, -15, 135, 0, MAKE_ENTITY_END)
    Call(MakeEntity, Entity_YellowBlock, -540, -15, 135, 0, ITEM_MAPLE_SYRUP, MAKE_ENTITY_END)
    Call(AssignBlockFlag, GF_TRD09_ItemBlock_MapleSyrup)
    Return
    End
};
