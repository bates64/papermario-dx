#include "iwa_03.h"
#include "entity.h"

#include "world/common/entity/Chest.inc.c"

API_CALLABLE(MonitorPlayerAltitude) {
    s32 result = -1;

    if (gPlayerStatus.lastGoodPos.y > 200.0) {
        result = 0;
    }
    if (gPlayerStatus.lastGoodPos.y < 40.0) {
        result = 1;
    }
    if (result >= 0) {
        evt_set_variable(script, MV_PlayerCliffLevel, result);
    }
    return ApiStatus_BLOCK;
}

EvtScript EVS_TetherCameraToPlayer = {
    Loop(0)
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
        Call(SetCamTarget, CAM_DEFAULT, LVar0, LVar1, LVar2)
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript EVS_UseSpring = {
    Call(DisablePlayerInput, true)
    Call(DisablePlayerPhysics, true)
    Call(SetPlayerActionState, ACTION_STATE_LAUNCH)
    Wait(1)
    ExecGetTID(EVS_TetherCameraToPlayer, LVarA)
    IfEq(MV_PlayerCliffLevel, 0)
        Call(SetPlayerJumpscale, 1.4)
        Call(PlayerJump, -1582, 23, 60, 15)
    Else
        Call(SetPlayerJumpscale, 0.7)
        Call(PlayerJump, -1582, 408, -60, 40)
    EndIf
    KillThread(LVarA)
    Call(SetPlayerActionState, ACTION_STATE_IDLE)
    Call(DisablePlayerPhysics, false)
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript EVS_OpenChest = EVT_OPEN_CHEST(ITEM_DAMAGE_DODGE_B, GF_IWA03_Chest_DamageDodgeB);

EvtScript EVS_MakeEntities = {
    Thread
        Call(MonitorPlayerAltitude)
    EndThread
    Call(MakeMarkerEntity, $ScriptSpring_1)
    Call(MakeMarkerEntity, $YellowBlock_Coin_1)
    Call(MakeMarkerEntity, $YellowBlock_Mushroom_1)
    Call(MakeMarkerEntity, $YellowBlock_HoneySyrup_1)
    Call(MakeMarkerEntity, $Item_LetterToKolorado_1)
    Call(MakeMarkerEntity, $Item_StarPiece_1)
    Call(MakeMarkerEntity, $Item_Coin_1)
    Call(MakeMarkerEntity, $Item_Coin_2)
    Call(MakeMarkerEntity, $Item_Coin_3)
    Call(MakeMarkerEntity, $Item_Coin_4)
    Call(MakeMarkerEntity, $Item_Coin_5)
    Call(MakeMarkerEntity, $Item_Coin_6)
    Call(MakeMarkerEntity, $Item_Coin_7)
    Call(MakeMarkerEntity, $Item_Coin_8)
    Call(MakeMarkerEntity, $Chest_DamageDodgeB)
    Return
    End
};
