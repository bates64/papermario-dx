#include "isk_03.h"
#include "effects.h"

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $Item_RuinsKey_1)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_1.pos.x, $FlamePos_1.pos.y, $FlamePos_1.pos.z, 0.3, LVar0)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_2.pos.x, $FlamePos_2.pos.y, $FlamePos_2.pos.z, 0.3, LVar0)
    Return
    End
};
