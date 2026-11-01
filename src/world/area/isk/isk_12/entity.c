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
        Call(MakeEntity, Entity_Hammer2Block, 627, -840, 135, 75, MAKE_ENTITY_END)
        Call(AssignScript, EVS_SmashBlock_Stone)
    EndIf
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, 415, -453, 291, 0.3, LVar0)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, 505, -453, 44, 0.3, LVar0)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, 415, -643, 291, 0.3, LVar0)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, 505, -643, 44, 0.3, LVar0)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, 417, -643, 196, 0.3, LVar0)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, 444, -643, 120, 0.3, LVar0)
    Call(MakeItemEntity, ITEM_RUINS_KEY, 461, -760, 109, ITEM_SPAWN_MODE_KEY, GF_ISK12_Item_RuinsKey)
    Return
    End
};
