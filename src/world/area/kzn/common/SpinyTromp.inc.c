#include "common.h"
#include "world/area/kzn/kzn.h"
#include "sprite/player.h"

#define SPINY_TROMP_RADIUS 55

API_CALLABLE(N(SpinyTromp_DamagePlayer)) {
    subtract_hp(1);
    return ApiStatus_DONE2;
}

API_CALLABLE(N(SpinyTromp_GetActingPartner)) {
    if (gPartnerStatus.partnerActionState != PARTNER_ACTION_NONE) {
        script->varTable[0] = gPartnerStatus.actingPartner;
    } else {
        script->varTable[0] = -1;
    }
    return ApiStatus_DONE2;
}

API_CALLABLE(N(SpinyTromp_SnapToGround)) {
    f32 posX = script->varTable[0];
    f32 posY = script->varTable[2];
    f32 posZ = 0.0f;
    f32 hitDepth = 2000.0f;

    if (npc_raycast_down_sides(COLLIDER_FLAG_IGNORE_PLAYER, &posX, &posY, &posZ, &hitDepth)) {
        script->varTable[0] = posX;
        script->varTable[2] = posY + SPINY_TROMP_RADIUS;
    }

    return ApiStatus_DONE2;
}

API_CALLABLE(N(SpinyTromp_GetPlayerDist)) {
    f32 dx = script->varTable[0] - gPlayerStatus.pos.x;
    f32 dy = script->varTable[2] - gPlayerStatus.pos.y;
    f32 dz = 0.0f - gPlayerStatus.pos.z;

    script->varTable[4] = sqrtf(SQ(dx) + SQ(dy) + SQ(dz));

    return ApiStatus_DONE2;
}

API_CALLABLE(N(SpinyTromp_SetPlayerPitch)) {
    gPlayerStatus.pitch = evt_get_variable(script, *script->ptrReadPos);
    return ApiStatus_DONE2;
}

// update small position offset applied to model as it rolls
API_CALLABLE(N(SpinyTromp_UpdateRollWobble)) {
    script->varTable[5] = (cos_deg(-(f32) script->varTable[3] - 35.0) * 3.0) - 2.3;
    script->varTable[6] = sin_deg(-(f32) script->varTable[3] - 35.0) * 5.0;

    return ApiStatus_DONE2;
}

API_CALLABLE(N(SpinyTromp_UpdateRollAngle)) {
    Bytecode* args = script->ptrReadPos;
    f32 startX = evt_get_float_variable(script, *args++);
    f32 startY = evt_get_float_variable(script, *args++);
    f32 dx = startX - script->varTable[0];
    f32 dy = startY - script->varTable[2];

    script->varTable[3] = -sqrtf(SQ(dx) + SQ(dy));

    return ApiStatus_DONE2;
}

API_CALLABLE(N(SpinyTromp_UpdateSoundPos)) {
    Bytecode* args = script->ptrReadPos;

    script->functionTemp[0] = evt_get_variable(script, *args++);
    script->functionTemp[1] = evt_get_variable(script, *args++);
    script->functionTemp[2] = evt_get_variable(script, *args++);
    sfx_adjust_env_sound_pos(SOUND_LRAW_TROMP_ROLL, SOUND_SPACE_DEFAULT, script->functionTemp[0], script->functionTemp[1], script->functionTemp[2]);

    return ApiStatus_DONE2;
}

EvtScript N(EVS_SpinyTromp_HitPlayer) = {
    Call(DisablePlayerInput, true)
    Label(10)
    Call(GetPartnerInUse, LVar0)
    IfNe(LVar0, 0)
        Call(InterruptUsePartner)
    EndIf
    Label(0)
    Wait(1)
    Call(GetPartnerInUse, LVar0)
    IfNe(LVar0, 0)
        Call(GetCurrentPartnerID, LVar0)
        IfEq(LVar0, PARTNER_BOW)
            Goto(2)
        Else
            Goto(10)
        EndIf
    EndIf
    Call(GetPlayerActionState, LVar0)
    IfNe(LVar0, ACTION_STATE_IDLE)
        Goto(0)
    EndIf
    Call(GetPlayerTargetYaw, LVar0)
    IfLt(LVar0, 180)
        Call(InterpPlayerYaw, 90, 1)
        Wait(1)
        Call(N(SpinyTromp_SetPlayerPitch), 20)
    Else
        Call(InterpPlayerYaw, 270, 1)
        Wait(1)
        Call(N(SpinyTromp_SetPlayerPitch), -20)
    EndIf
    Call(SetPlayerAnimation, ANIM_Mario1_Fallen)
    Wait(1)
    Call(N(SpinyTromp_DamagePlayer))
    Call(UpdatePlayerImgFX, ANIM_Mario1_Fallen, IMGFX_SET_WAVY, Float(3.0), Float(3.0), 0, 0)
    Label(1)
        Wait(1)
        IfEq(AF_KZN_TrompRollingDone, false)
            Goto(1)
        EndIf
    Wait(30)
    Call(UpdatePlayerImgFX, ANIM_Mario1_Fallen, IMGFX_CLEAR, 0, 0, 0, 0)
    Call(SetPlayerAnimation, ANIM_Mario1_GetUp)
    Call(N(SpinyTromp_SetPlayerPitch), 0)
    Label(2)
    Call(DisablePlayerInput, false)
    Return
    End
};
