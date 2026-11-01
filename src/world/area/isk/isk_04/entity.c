#include "isk_04.h"
#include "entity.h"
#include "effects.h"

EvtScript EVS_MakeEntities = {
    IfEq(GF_ISK04_UnlockedDoor, false)
        Call(MakeMarkerEntity, $Padlock_1)
        Set(MV_RuinsLockEntityID, LVar0)
    EndIf
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_1.pos.x, $FlamePos_1.pos.y, $FlamePos_1.pos.z, 0.3, LVar0)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_2.pos.x, $FlamePos_2.pos.y, $FlamePos_2.pos.z, 0.3, LVar0)
    Return
    End
};
