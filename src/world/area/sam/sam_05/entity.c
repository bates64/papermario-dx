#include "sam_05.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $Item_LetterToMerlow_1)
    Call(MakeMarkerEntity, $HiddenYellowBlock_StopWatch_1)
    Return
    End
};
