#include "sbk_66.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeEntity, Entity_MulticoinBlock, -80, 60, -200, 0, MAKE_ENTITY_END)
    Call(AssignBlockFlag, GF_SBK66_MultiCoinBrickA)
    Call(MakeEntity, Entity_MulticoinBlock, 80, 60, -200, 0, MAKE_ENTITY_END)
    Call(AssignBlockFlag, GF_SBK66_MultiCoinBrickB)
    Call(MakeEntity, Entity_MulticoinBlock, 160, 60, 0, 0, MAKE_ENTITY_END)
    Call(AssignBlockFlag, GF_SBK66_MultiCoinBrickC)
    Call(MakeEntity, Entity_MulticoinBlock, -160, 60, 0, 0, MAKE_ENTITY_END)
    Call(AssignBlockFlag, GF_SBK66_MultiCoinBrickD)
    Call(MakeEntity, Entity_MulticoinBlock, -60, 60, 200, 0, MAKE_ENTITY_END)
    Call(AssignBlockFlag, GF_SBK66_MultiCoinBrickE)
    Call(MakeEntity, Entity_MulticoinBlock, 60, 60, 200, 0, MAKE_ENTITY_END)
    Call(AssignBlockFlag, GF_SBK66_MultiCoinBrickF)
    Return
    End
};
