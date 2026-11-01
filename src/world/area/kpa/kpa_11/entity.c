#include "kpa_11.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $SavePoint_1)
    IfEq(GF_KPA11_Defeated_Guard, true)
        Call(MakeMarkerEntity, $Item_BowserCastleKey_1)
    EndIf
    Call(MakeMarkerEntity, $YellowBlock_LifeShroom_1)
    Return
    End
};
