#include "kpa_16.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    IfEq(GF_KPA16_ShutOffLava, false)
        Call(MakeEntity, Entity_BlueSwitch, 470, 230, -145, 0, MAKE_ENTITY_END)
        Call(AssignSwitchFlag, EVT_INDEX_OF_AREA_FLAG(AF_KPA16_HitSwitch))
    EndIf
    Return
    End
};
