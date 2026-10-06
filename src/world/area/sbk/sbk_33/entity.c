#include "sbk_33.h"
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
    Call(GotoMap, Ref("sbk_24"), sbk_24_ENTRY_4)
    Wait(100)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Call(MakeEntity, Ref(Entity_HiddenPanel), 0, 0, 225, 0, MODEL_stage, MAKE_ENTITY_END)
    Call(AssignPanelFlag, GF_SBK33_HiddenPanel)
    Call(MakeEntity, Ref(Entity_Tweester), 327, 0, 8, 0, Ref(TweesterPaths), MAKE_ENTITY_END)
    Call(AssignScript, Ref(EVS_GotoMap_sbk_24_4))
    Return
    End
};
