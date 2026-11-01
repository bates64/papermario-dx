#include "isk_10.h"
#include "entity.h"

#define SUPER_BLOCK_MAPVAR MV_SuperBlock
#define SUPER_BLOCK_GAMEFLAG GF_ISK10_SuperBlock
#include "world/common/entity/SuperBlock.inc.c"

API_CALLABLE(MonitorPlayerLastFloor) {
    s32 level = -1;

    if (gPlayerStatus.lastGoodPos.y > -600.0) {
        level = 0;
    }
    if (gPlayerStatus.lastGoodPos.y < -770.0) {
        level = 1;
    }
    if (level >= 0) {
        evt_set_variable(script, MV_LastFloorLevel, level);
    }
    return ApiStatus_BLOCK;
}

EvtScript EVS_UseSpring = {
    Call(DisablePlayerInput, true)
    Call(DisablePlayerPhysics, true)
    Call(SetPlayerActionState, ACTION_STATE_JUMP)
    Wait(1)
    IfEq(MV_LastFloorLevel, 0)
        Call(SetPlayerJumpscale, 1.4)
        Call(PlayerJump, -577, -780, -75, 15)
    Else
        Call(SetCamSpeed, CAM_DEFAULT, 2.8)
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
        Call(UseSettingsFrom, CAM_DEFAULT, LVar0, LVar1, LVar2)
        Call(SetCamPosC, CAM_DEFAULT, 0, -520)
        Call(PanToTarget, CAM_DEFAULT, 0, true)
        Call(SetPlayerJumpscale, 1.4)
        Call(PlayerJump, -561, -520, 23, 30)
        Call(PanToTarget, CAM_DEFAULT, 0, false)
        Call(SetCamSpeed, CAM_DEFAULT, 2.8)
    EndIf
    Call(SetPlayerActionState, ACTION_STATE_IDLE)
    Call(DisablePlayerPhysics, false)
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    EVT_MAKE_SUPER_BLOCK(-550, -720, 0, 0)
    Thread
        Call(MonitorPlayerLastFloor)
    EndThread
    Call(MakeMarkerEntity, $ScriptSpring_1)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_1.pos.x, $FlamePos_1.pos.y, $FlamePos_1.pos.z, 0.3, LVar0)
    PlayEffect(EFFECT_FLAME, FX_FLAME_RED, $FlamePos_2.pos.x, $FlamePos_2.pos.y, $FlamePos_2.pos.z, 0.3, LVar0)
    Return
    End
};
