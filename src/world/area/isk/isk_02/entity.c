#include "isk_02.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    IfEq(GF_ISK02_UnlockedDoor, false)
        Call(MakeMarkerEntity, $Padlock_1)
        Set(MV_EntityID_Padlock, LVar0)
    EndIf
    Return
    End
};
