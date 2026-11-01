#include "isk_13.h"
#include "entity.h"
#include "effects.h"

EvtScript EVS_OnSmash_Block = {
    Set(GF_ISK13_Hammer2Block, true)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $Item_LunarStone_1)
    IfEq(GF_ISK13_Hammer2Block, false)
        Call(MakeMarkerEntity, $Hammer2BlockWideX_1)
    EndIf
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_1.pos.x, $FlamePos_1.pos.y, $FlamePos_1.pos.z, 0.3, LVar0)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_2.pos.x, $FlamePos_2.pos.y, $FlamePos_2.pos.z, 0.3, LVar0)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_3.pos.x, $FlamePos_3.pos.y, $FlamePos_3.pos.z, 0.3, LVar0)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_4.pos.x, $FlamePos_4.pos.y, $FlamePos_4.pos.z, 0.3, LVar0)
    Return
    End
};
