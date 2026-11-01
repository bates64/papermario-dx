#include "nok_01.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $BrickBlock_1)
    IfEq(GF_NOK01_RecoveredBlockShell, false)
        Call(AssignScript, EVS_BreakBlock_DropShell)
    EndIf
    Call(MakeMarkerEntity, $SavePoint_1)
    Call(MakeMarkerEntity, $HiddenPanel_1)
    Return
    End
};
