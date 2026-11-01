#include "isk_07.h"
#include "entity.h"
#include "effects.h"

EvtScript EVS_HitBlock_Trigger = {
    Set(GF_ISK07_OpenedSarcophagi, true)
    Return
    End
};

EvtScript EVS_SmashBlock_Stone = {
    Set(GF_ISK07_Hammer2Block, true)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    IfEq(GF_ISK07_UnlockedDoor, false)
        Call(MakeMarkerEntity, $Padlock_1)
        Set(MV_LockEntityID, LVar0)
    EndIf
    IfEq(GF_ISK07_Hammer2Block, false)
        Call(MakeMarkerEntity, $Hammer2BlockWideX_1)
    EndIf
    IfEq(GF_ISK07_OpenedSarcophagi, false)
        Call(MakeMarkerEntity, $TriggerBlock_1)
    EndIf
    IfEq(GF_ISK07_Defeated_Mummies, true)
        Call(MakeMarkerEntity, $Item_RuinsKey_1)
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
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_10.pos.x, $FlamePos_10.pos.y, $FlamePos_10.pos.z, 0.3, LVar0)
    Call(MakeMarkerEntity, $Item_Artifact_1)
    Return
    End
};
