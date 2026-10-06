#include "isk_01.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    Call(MakeEntity, Ref(Entity_SavePoint), -530, 60, 43, 0, MAKE_ENTITY_END)
    Return
    End
};
