#include "sam_04.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $HiddenPanel_1)
    Call(MakeMarkerEntity, $Item_LetterToMayorPenguin_1)
    Set(MV_LetterItemID, LVar0)
    Call(MakeMarkerEntity, $Item_RepelGel_1)
    Return
    End
};
