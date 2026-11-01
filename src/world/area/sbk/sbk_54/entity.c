#include "sbk_54.h"
#include "world/area/sbk/sbk_45.h"
#include "entity.h"

TweesterPath TweesterPath1 = {
    { -65, 0, 217 },
    { -262, 0, -64 },
    { 57, 0, -286 },
    { 327, 0, 8 },
    TWEESTER_PATH_LOOP
};

TweesterPath* TweesterPaths[] = {
    &TweesterPath1,
    PTR_LIST_END
};

EvtScript EVS_GotoMap_sbk_45_4 = {
    Call(DisablePlayerInput, true)
    Call(DisablePlayerPhysics, true)
    Call(GotoMap, $sbk_45.Pipe)
    Wait(100)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $Tweester_1)
    Return
    End
};
