#include "common.h"
#include "world/area/kzn/kzn.h"
#include "sprite/player.h"

API_CALLABLE(N(SpinyTrompHit)) {
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

API_CALLABLE(N(UnkFunc46)) {
    f32 var1 = script->varTable[0];
    f32 var2 = script->varTable[2];
    f32 var3 = 0.0f;
    f32 var4 = 2000.0f;

    if (npc_raycast_down_sides(COLLIDER_FLAG_IGNORE_PLAYER, &var1, &var2, &var3, &var4)) {
        script->varTable[0] = var1;
        script->varTable[2] = var2 + 55.0f;
    }

    return ApiStatus_DONE2;
}

API_CALLABLE(N(SpinyTromp_CheckDist)) {
    f32 x = script->varTable[0] - gPlayerStatus.pos.x;
    f32 y = script->varTable[2] - gPlayerStatus.pos.y;
    f32 z = 0.0f - gPlayerStatus.pos.z;

    script->varTable[4] = sqrtf(SQ(x) + SQ(y) + SQ(z));

    return ApiStatus_DONE2;
}

API_CALLABLE(N(UnkFunc48)) {
    gPlayerStatus.pitch = evt_get_variable(script, *script->ptrReadPos);
    return ApiStatus_DONE2;
}

API_CALLABLE(N(UnkFunc49)) {
    script->varTable[5] = (cos_deg(-(f32) script->varTable[3] - 35.0) * 3.0) - 2.3;
    script->varTable[6] = sin_deg(-(f32) script->varTable[3] - 35.0) * 5.0;

    return ApiStatus_DONE2;
}

API_CALLABLE(N(UnkFunc50)) {
    f32 x = UNK_FUNC_50_LVar1 - script->varTable[0];
    f32 z = UNK_FUNC_50_LVar2 - script->varTable[2];

    script->varTable[3] = -sqrtf(SQ(x) + SQ(z));

    return ApiStatus_DONE2;
}

API_CALLABLE(N(UnkFunc51)) {
    Bytecode* args = script->ptrReadPos;

    script->functionTemp[0] = evt_get_variable(script, *args++);
    script->functionTemp[1] = evt_get_variable(script, *args++);
    script->functionTemp[2] = evt_get_variable(script, *args++);
    sfx_adjust_env_sound_pos(SOUND_LRAW_TROMP_ROLL, SOUND_SPACE_DEFAULT, script->functionTemp[0], script->functionTemp[1], script->functionTemp[2]);

    return ApiStatus_DONE2;
}

EvtScript N(D_80240D10_C7EE90) = {
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
        Call(N(UnkFunc48), 20)
    Else
        Call(InterpPlayerYaw, 270, 1)
        Wait(1)
        Call(N(UnkFunc48), -20)
    EndIf
    Call(SetPlayerAnimation, ANIM_Mario1_Fallen)
    Wait(1)
    Call(N(SpinyTrompHit))
    Call(UpdatePlayerImgFX, ANIM_Mario1_Fallen, IMGFX_SET_WAVY, Float(3.0), Float(3.0), 0, 0)
    Label(1)
        Wait(1)
        IfEq(AF_KZN_TrompRollingDone, false)
            Goto(1)
        EndIf
    Wait(30)
    Call(UpdatePlayerImgFX, ANIM_Mario1_Fallen, IMGFX_CLEAR, 0, 0, 0, 0)
    Call(SetPlayerAnimation, ANIM_Mario1_GetUp)
    Call(N(UnkFunc48), 0)
    Label(2)
    Call(DisablePlayerInput, false)
    Return
    End
};
