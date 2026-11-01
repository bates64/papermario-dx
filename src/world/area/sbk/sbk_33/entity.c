#include "sbk_33.h"
#include "world/area/sbk/sbk_24.h"
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

EvtScript EVS_GotoMap_sbk_24_4 = {
    Call(DisablePlayerInput, true)
    Call(DisablePlayerPhysics, true)
    Call(GotoMap, $sbk_24.Pipe)
    Wait(100)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $HiddenPanel_1)
    Call(MakeMarkerEntity, $Tweester_1)
    Return
    End
};
