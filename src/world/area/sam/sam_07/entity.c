#include "sam_07.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    IfEq(GF_SAM07_FloorRaised, false)
        Call(MakeMarkerEntity, $GreenStompSwitch_1)
        Set(MV_SwitchEntityID, LVar0)
        Call(AssignScript, EVS_UseGreenSwitch)
    Else
        Call(MakeMarkerEntity, $GreenStompSwitch_2)
        Set(MV_SwitchEntityID, LVar0)
        Call(AssignScript, EVS_UseGreenSwitch)
    EndIf
    Call(MakeMarkerEntity, $BrickBlock_1)
    Call(MakeMarkerEntity, $HiddenYellowBlock_UltraShroom_1)
    Call(MakeMarkerEntity, $SavePoint_1)
    Return
    End
};
