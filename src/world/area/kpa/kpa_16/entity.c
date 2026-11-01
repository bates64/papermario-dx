#include "kpa_16.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    IfEq(GF_KPA16_ShutOffLava, false)
        Call(MakeMarkerEntity, $BlueSwitch_1)
    EndIf
    Return
    End
};
