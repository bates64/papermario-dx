#include "isk_12.h"
#include "entity.h"
#include "effects.h"

EvtScript EVS_SmashBlock_Stone = {
    Set(GF_ISK12_Hammer2Block, true)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    IfEq(GF_ISK12_Hammer2Block, false)
        Call(MakeMarkerEntity, $Hammer2Block_1)
    EndIf
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_1.pos.x, $FlamePos_1.pos.y, $FlamePos_1.pos.z, 0.3, LVar0)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_2.pos.x, $FlamePos_2.pos.y, $FlamePos_2.pos.z, 0.3, LVar0)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_3.pos.x, $FlamePos_3.pos.y, $FlamePos_3.pos.z, 0.3, LVar0)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_4.pos.x, $FlamePos_4.pos.y, $FlamePos_4.pos.z, 0.3, LVar0)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_5.pos.x, $FlamePos_5.pos.y, $FlamePos_5.pos.z, 0.3, LVar0)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_6.pos.x, $FlamePos_6.pos.y, $FlamePos_6.pos.z, 0.3, LVar0)
    Call(MakeMarkerEntity, $Item_RuinsKey_1)
    Return
    End
};
