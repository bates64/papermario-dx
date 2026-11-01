#include "sbk_14.h"
#include "entity.h"

TweesterPath DefaultTweesterPath = {
    { -65, 0, 217 },
    { -262, 0, -64 },
    { 57, 0, -286 },
    { 327, 0, 8 },
    TWEESTER_PATH_LOOP
};

TweesterPath* TweesterPaths[] = {
    &DefaultTweesterPath,
    PTR_LIST_END
};

EvtScript EVS_GotoMap_sbk_05_4 = {
    Call(DisablePlayerInput, true)
    Call(DisablePlayerPhysics, true)
    Call(GotoMap, "sbk_05", sbk_05_ENTRY_4)
    Wait(100)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Call(MakeEntity, Entity_Tweester, 327, 0, 8, 0, TweesterPaths, MAKE_ENTITY_END)
    Call(AssignScript, EVS_GotoMap_sbk_05_4)
    Call(MakeEntity, Entity_MulticoinBlock, 0, 60, -100, 0, MAKE_ENTITY_END)
    Call(AssignBlockFlag, GF_SBK14_MultiCoinBrick)
    Call(MakeEntity, Entity_YellowBlock, -240, 0, 215, 0, ITEM_COIN, MAKE_ENTITY_END)
    Call(AssignBlockFlag, GF_SBK14_ItemBlock_Coin)
    Call(MakeEntity, Entity_YellowBlock, 220, 0, 150, 0, ITEM_HONEY_SYRUP, MAKE_ENTITY_END)
    Call(AssignBlockFlag, GF_SBK14_ItemBlock_HoneySyrup)
    Return
    End
};
