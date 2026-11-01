#include "sbk_23.h"
#include "world/area/sbk/sbk_14.h"
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

EvtScript EVS_GotoMap_sbk_14_4 = {
    Call(DisablePlayerInput, true)
    Call(DisablePlayerPhysics, true)
    Call(GotoMap, $sbk_14.Pipe)
    Wait(100)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $Tweester_1)
    Return
    End
};
