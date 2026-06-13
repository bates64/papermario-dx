#include "kkj_25.h"
#include "entity.h"

EvtScript N(EVS_MakeEntities) = {
    IfEq(GF_KKJ25_Defeated_Kammy, false)
        Call(MakeEntity, Ref(Entity_GreenStompSwitch), 300, 0, 0, 0, MAKE_ENTITY_END)
        Set(MV_EntityID_Switch, LVar0)
        Call(AssignSwitchFlag, EVT_INDEX_OF_AREA_FLAG(AF_KKJ25_ActivatedArenaSwitch))
        BindTrigger(Ref(N(EVS_Scene_ActivateMachine)), TRIGGER_AREA_FLAG_SET, AF_KKJ25_ActivatedArenaSwitch, 1, 0)
    EndIf
    Return
    End
};
