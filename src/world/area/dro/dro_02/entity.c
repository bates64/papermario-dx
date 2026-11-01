#include "dro_02.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $Item_LetterToNomadimouse_1)
    Call(MakeMarkerEntity, $HiddenPanel_1)
    Return
    End
};
