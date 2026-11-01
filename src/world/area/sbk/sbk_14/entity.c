#include "sbk_14.h"
#include "world/area/sbk/sbk_05.h"
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
    Call(GotoMap, $sbk_05.Pipe)
    Wait(100)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $Tweester_1)
    Call(MakeMarkerEntity, $MulticoinBlock_1)
    Call(MakeMarkerEntity, $YellowBlock_Coin_1)
    Call(MakeMarkerEntity, $YellowBlock_HoneySyrup_1)
    Return
    End
};
