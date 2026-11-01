#include "isk_11.h"
#include "entity.h"
#include "effects.h"

EvtScript EVS_MakeEntities = {
    IfEq(GF_ISK11_UnlockedDoor, false)
        Call(MakeMarkerEntity, $Padlock_1)
        Set(MV_LockEntityID, LVar0)
    EndIf
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_1.pos.x, $FlamePos_1.pos.y, $FlamePos_1.pos.z, 0.3, LVar0)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_2.pos.x, $FlamePos_2.pos.y, $FlamePos_2.pos.z, 0.3, LVar0)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_3.pos.x, $FlamePos_3.pos.y, $FlamePos_3.pos.z, 0.3, LVar0)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_4.pos.x, $FlamePos_4.pos.y, $FlamePos_4.pos.z, 0.3, LVar0)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_5.pos.x, $FlamePos_5.pos.y, $FlamePos_5.pos.z, 0.3, LVar0)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_6.pos.x, $FlamePos_6.pos.y, $FlamePos_6.pos.z, 0.3, LVar0)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_7.pos.x, $FlamePos_7.pos.y, $FlamePos_7.pos.z, 0.3, LVar0)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_8.pos.x, $FlamePos_8.pos.y, $FlamePos_8.pos.z, 0.3, LVar0)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_9.pos.x, $FlamePos_9.pos.y, $FlamePos_9.pos.z, 0.3, LVar0)
    Call(MakeMarkerEntity, $HeartBlock_1)
    Return
    End
};
