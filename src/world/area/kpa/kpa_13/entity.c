#include "kpa_13.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Set(AF_KPA13_HitSwitchA, false)
    Set(AF_KPA13_HitSwitchB, false)
    IfEq(GF_KPA13_BlueSwitchA, false)
        Call(MakeMarkerEntity, $BlueSwitch_1)
    EndIf
    IfEq(GF_KPA13_BlueSwitchB, false)
        Call(MakeMarkerEntity, $BlueSwitch_2)
    EndIf
    Return
    End
};
