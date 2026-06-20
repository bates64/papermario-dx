#include "common.h"

// plays the hit animation and rapidly bounces the NPC before restoring its original position
// LVar0: hit animation
EvtScript EVS_NpcHitRecoil = {
    Call(SetNpcAnimation, NPC_SELF, LVar0)
    Call(GetNpcPos, NPC_SELF, LVar0, LVar3, LVar2)
    Set(LVar1, LVar3)
    Add(LVar1, 1)
    Call(SetNpcPos, NPC_SELF, LVar0, LVar1, LVar2)
    Wait(1)
    Set(LVar1, LVar3)
    Add(LVar1, 4)
    Call(SetNpcPos, NPC_SELF, LVar0, LVar1, LVar2)
    Wait(1)
    Set(LVar1, LVar3)
    Add(LVar1, 16)
    Call(SetNpcPos, NPC_SELF, LVar0, LVar1, LVar2)
    Wait(1)
    Set(LVar1, LVar3)
    Add(LVar1, 8)
    Call(SetNpcPos, NPC_SELF, LVar0, LVar1, LVar2)
    Wait(1)
    Set(LVar1, LVar3)
    Add(LVar1, 20)
    Call(SetNpcPos, NPC_SELF, LVar0, LVar1, LVar2)
    Wait(1)
    Set(LVar1, LVar3)
    Add(LVar1, 8)
    Call(SetNpcPos, NPC_SELF, LVar0, LVar1, LVar2)
    Wait(1)
    Set(LVar1, LVar3)
    Add(LVar1, 12)
    Call(SetNpcPos, NPC_SELF, LVar0, LVar1, LVar2)
    Wait(1)
    Set(LVar1, LVar3)
    Add(LVar1, 6)
    Call(SetNpcPos, NPC_SELF, LVar0, LVar1, LVar2)
    Wait(1)
    Set(LVar1, LVar3)
    Add(LVar1, 0)
    Call(SetNpcPos, NPC_SELF, LVar0, LVar1, LVar2)
    Wait(1)
    Return
    End
};

// calculates the sprite brightness for a given rotation angle
// the sprite is brightest face-on and darkest edge-on
// LVar0: rotation angle (out: clamped angle)
// LVar2: (out) sprite brightness from 160 to 255
API_CALLABLE(GetNpcRotationBrightness) {
    f32 angle = clamp_angle(script->varTable[0]);

    script->varTable[0] = angle;
    if (angle >= 180.0f) {
        angle -= 180.0f;
    }
    if (angle >= 90.0f) {
        angle = 180.0f - angle;
    }
    script->varTable[2] = (s32) (((90.0f - angle) * 95.0f) / 90.0f) + 160;
    return ApiStatus_DONE2;
}

// waits for the battle to finish loading
API_CALLABLE(AwaitBattleLoad) {
    if (gCurrentEncounter.battleTransitionState != BATTLE_TRANSITION_STATE_LOADING) {
        return ApiStatus_DONE1;
    } else {
        return ApiStatus_BLOCK;
    }
}

// pauses the NPC's normal AI while it spins and falls
EvtScript EVS_NpcAI_DoNothing = {
    Return
    End
};

// makes the NPC fall while spinning, darkening the sprite as it turns
// self var 0 prevents the effect from running more than once at a time
// LVar1: AI script to restore after the battle loads
// LVar2: animation to use while spinning
EvtScript EVS_NpcSpinAndFall = {
    Call(GetSelfVar, 0, LVar0)
    IfEq(LVar0, 0)
        Call(SetSelfVar, 0, 1)
        Call(BindNpcAI, NPC_SELF, Ref(EVS_NpcAI_DoNothing))
        Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_GRAVITY | NPC_FLAG_IGNORE_CAMERA_FOR_YAW, true)
        Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_FLYING | NPC_FLAG_JUMPING, false)
        Call(SetNpcAnimation, NPC_SELF, LVar2)
        Set(LVar0, 0)
        Loop(30)
            Call(SetNpcRotation, NPC_SELF, 0, LVar0, 0)
            Call(GetNpcRotationBrightness)
            Call(SetNpcImgFXParams, NPC_SELF, IMGFX_SET_COLOR, LVar2, LVar2, LVar2, 0)
            Add(LVar0, 30)
            Wait(1)
        EndLoop
        Call(SetNpcRotation, NPC_SELF, 0, 0, 0)
        Call(SetNpcImgFXParams, NPC_SELF, IMGFX_SET_COLOR, 255, 255, 255, 0)
        Call(SetNpcFlagBits, NPC_SELF, NPC_FLAG_IGNORE_CAMERA_FOR_YAW, false)
        Call(SetSelfVar, 0, 0)
        Call(AwaitBattleLoad)
        Call(BindNpcAI, NPC_SELF, LVar1)
    EndIf
    Return
    End
};
