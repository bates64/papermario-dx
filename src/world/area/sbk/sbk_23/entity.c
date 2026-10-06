#include "sbk_23.h"
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
    Call(GotoMap, Ref("sbk_14"), sbk_14_ENTRY_4)
    Wait(100)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Call(MakeEntity, Ref(Entity_Tweester), 327, 0, 8, 0, Ref(TweesterPaths), MAKE_ENTITY_END)
    Call(AssignScript, Ref(EVS_GotoMap_sbk_14_4))
    Return
    End
};
