#include "arn_03.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeEntity, Entity_YellowBlock, 300, 237, 60, 0, ITEM_COIN, MAKE_ENTITY_END)
    Call(AssignBlockFlag, GF_ARN03_ItemBlock_Coin)
    Call(MakeEntity, Entity_SavePoint, 250, 237, 125, 0, MAKE_ENTITY_END)
    Return
    End
};
