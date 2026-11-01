#include "tik_21.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeEntity, Entity_YellowBlock, -157, -45, 0, 0, ITEM_COIN, MAKE_ENTITY_END)
    Call(AssignBlockFlag, GF_TIK21_ItemBlock_Coin)
    Call(MakeEntity, Entity_HiddenYellowBlock, -82, -45, 0, 0, ITEM_COIN, MAKE_ENTITY_END)
    Call(AssignBlockFlag, GF_TIK21_HiddenItem_CoinA)
    Call(MakeEntity, Entity_HiddenYellowBlock, -7, -45, 0, 0, ITEM_COIN, MAKE_ENTITY_END)
    Call(AssignBlockFlag, GF_TIK21_HiddenItem_CoinB)
    Call(MakeEntity, Entity_HiddenYellowBlock, 68, -45, 0, 0, ITEM_COIN, MAKE_ENTITY_END)
    Call(AssignBlockFlag, GF_TIK21_HiddenItem_CoinC)
    Call(MakeEntity, Entity_HiddenYellowBlock, 142, -45, 0, 0, ITEM_COIN, MAKE_ENTITY_END)
    Call(AssignBlockFlag, GF_TIK21_HiddenItem_CoinD)
    Return
    End
};
