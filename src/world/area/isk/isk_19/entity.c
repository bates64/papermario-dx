#include "isk_19.h"
#include "entity.h"
#include "effects.h"

EvtScript EVS_MakeEntities = {
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_1.pos.x, $FlamePos_1.pos.y, $FlamePos_1.pos.z, 0.3, LVar0)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_2.pos.x, $FlamePos_2.pos.y, $FlamePos_2.pos.z, 0.3, LVar0)
    Call(MakeMarkerEntity, $SavePoint_1)
    Return
    End
};
