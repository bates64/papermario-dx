
#include "sbk_46.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeEntity, Entity_YellowBlock, 0, 0, 0, 0, ITEM_COIN, MAKE_ENTITY_END)
    Call(AssignBlockFlag, GF_SBK46_ItemBlock_Coin)
    Call(MakeEntity, Entity_HiddenYellowBlock, 0, 85, 0, 0, ITEM_LIFE_SHROOM, MAKE_ENTITY_END)
    Call(AssignBlockFlag, GF_SBK46_HiddenItem_LifeShroom)
    Return
    End
};
