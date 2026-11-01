#include "flo_17.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $HiddenYellowBlock_ThunderRage_1)
    Call(MakeMarkerEntity, $Item_LetterToMinhT_1)
    Return
    End
};
