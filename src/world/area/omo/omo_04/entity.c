#include "omo_04.h"
#include "entity.h"

#include "world/common/entity/Chest.inc.c"

EvtScript EVS_OpenChest_StoreroomKey = {
    Set(LVarA, ITEM_STOREROOM_KEY)
    Set(GF_OMO04_Chest_StoreroomKey, true)
    ExecWait(EVS_Chest_GetItem)
    Set(GF_MAC04_StoreroomKeyStolen, true)
    Set(GB_StoryProgress, STORY_CH4_GOT_STOREROOM_KEY)
    Return
    End
};

EvtScript EVS_TetherCamToPlayer = {
    Label(0)
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
        Call(SetCamTarget, CAM_DEFAULT, LVar0, LVar1, LVar2)
        Wait(1)
        Goto(0)
    Return
    End
};

Vec3i StarBoxLaunchTargets[] = {
    { -852,   0, -125 },
    { -887,   0,   98 },
    { -682,  80,  -77 },
    { -542,  80,   62 },
    { -647,  80,  132 },
    { -507,  80,  132 },
    {  672, 105,  132 },
    {  927,  80,  -87 },
};

EvtScript EVS_StarBoxLaunch_Impl = {
    Call(DisablePlayerInput, true)
    Call(DisablePlayerPhysics, true)
    UseBuf(StarBoxLaunchTargets)
    Loop(LVar0)
        BufRead3(LVar7, LVar8, LVar9)
    EndLoop
    Call(SetPlayerActionState, ACTION_STATE_IDLE)
    Wait(1)
    Call(SetPlayerActionState, ACTION_STATE_LAUNCH)
    Wait(1)
    Call(EnableCameraFollowPlayerY)
    ExecGetTID(EVS_TetherCamToPlayer, LVarA)
    Call(SetPlayerJumpscale, 0.7)
    Call(PlayerJump, LVar7, LVar8, LVar9, 40)
    KillThread(LVarA)
    Call(DisableCameraFollowPlayerY)
    Wait(1)
    Call(SetPlayerActionState, ACTION_STATE_IDLE)
    Call(DisablePlayerPhysics, false)
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript EVS_StarBoxLaunch1 = {
    Set(LVar0, 1) // entityID
    ExecWait(EVS_StarBoxLaunch_Impl)
    Return
    End
};

EvtScript EVS_StarBoxLaunch2 = {
    Set(LVar0, 2) // entityID
    ExecWait(EVS_StarBoxLaunch_Impl)
    Return
    End
};

EvtScript EVS_StarBoxLaunch3 = {
    Set(LVar0, 3) // entityID
    ExecWait(EVS_StarBoxLaunch_Impl)
    Return
    End
};

EvtScript EVS_StarBoxLaunch4 = {
    Set(LVar0, 4) // entityID
    ExecWait(EVS_StarBoxLaunch_Impl)
    Return
    End
};

EvtScript EVS_StarBoxLaunch5 = {
    Set(LVar0, 5) // entityID
    ExecWait(EVS_StarBoxLaunch_Impl)
    Return
    End
};

EvtScript EVS_StarBoxLaunch6 = {
    Set(LVar0, 6) // entityID
    ExecWait(EVS_StarBoxLaunch_Impl)
    Return
    End
};

EvtScript EVS_StarBoxLaunch7 = {
    Set(LVar0, 7) // entityID
    ExecWait(EVS_StarBoxLaunch_Impl)
    Return
    End
};

API_CALLABLE(GetPlayerForwardPos) {
    f32 playerVx = gPlayerStatus.curSpeed * 5.0f * sin_deg(gPlayerStatus.targetYaw);
    f32 playerVz = gPlayerStatus.curSpeed * 5.0f * -cos_deg(gPlayerStatus.targetYaw);
    script->varTable[0] = (gPlayerStatus.pos.x + playerVx);
    script->varTable[1] = (gPlayerStatus.pos.z + playerVz);

    return ApiStatus_DONE2;
}

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $Chest_StoreroomKey)
    Call(MakeMarkerEntity, $StarBoxLauncher_1)
    Call(MakeMarkerEntity, $StarBoxLauncher_2)
    Call(MakeMarkerEntity, $StarBoxLauncher_3)
    Call(MakeMarkerEntity, $StarBoxLauncher_4)
    Call(MakeMarkerEntity, $StarBoxLauncher_5)
    Call(MakeMarkerEntity, $StarBoxLauncher_6)
    Call(MakeMarkerEntity, $StarBoxLauncher_7)
    Call(MakeMarkerEntity, $YellowBlock_Coin_1)
    Call(MakeMarkerEntity, $YellowBlock_Coin_2)
    Call(MakeMarkerEntity, $YellowBlock_ThunderBolt_1)
    Call(MakeMarkerEntity, $Item_Coin_1)
    Call(MakeMarkerEntity, $Item_Coin_2)
    Call(MakeMarkerEntity, $Item_Coin_3)
    Call(MakeMarkerEntity, $Item_Coin_4)
    Call(MakeMarkerEntity, $Item_Coin_5)
    Call(MakeMarkerEntity, $Item_Coin_6)
    Call(MakeMarkerEntity, $Item_Coin_7)
    Call(MakeMarkerEntity, $Item_Coin_8)
    Call(MakeMarkerEntity, $Item_StarPiece_1)
    Call(MakeMarkerEntity, $Item_StarPiece_2)
    Return
    End
};
