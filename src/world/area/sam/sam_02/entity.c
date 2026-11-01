#include "sam_02.h"
#include "entity.h"

EvtScript EVS_MakeToadHouseGifts = {
    IfEq(GF_SAM02_MushroomPresents, true)
        Call(MakeMarkerEntity, $Item_UltraShroom_1)
        Call(MakeMarkerEntity, $Item_Mushroom_1)
        Call(MakeMarkerEntity, $Item_Mushroom_2)
        Call(MakeMarkerEntity, $Item_Mushroom_3)
        Call(MakeMarkerEntity, $Item_Mushroom_4)
    EndIf
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $SavePoint_1)
    Exec(EVS_MakeToadHouseGifts)
    Return
    End
};
