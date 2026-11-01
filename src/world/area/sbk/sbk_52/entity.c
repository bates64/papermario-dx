#include "sbk_52.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeEntity, Entity_MulticoinBlock, 0, 60, -100, 0, MAKE_ENTITY_END)
    Call(AssignBlockFlag, GF_SBK52_MultiCoinBrick)
    Call(MakeEntity, Entity_BrickBlock, 80, 60, 270, 0, MAKE_ENTITY_END)
    Call(MakeEntity, Entity_BrickBlock, -210, 60, 165, 0, MAKE_ENTITY_END)
    Return
    End
};
