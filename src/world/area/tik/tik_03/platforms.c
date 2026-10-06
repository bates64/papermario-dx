#include "tik_03.h"

s32 PlatformColliders[] = {
    COLLIDER_1,
    COLLIDER_2,
    COLLIDER_3,
    COLLIDER_4,
};

API_CALLABLE(PausePlatformsDuringPound) {
    PlayerStatus* player = &gPlayerStatus;
    u32 i;

    for (i = 0; i < ARRAY_COUNT(PlatformColliders); i++) {
        if (gCollisionStatus.curFloor != PlatformColliders[i]) {
            continue;
        }
        if ((player->actionState == ACTION_STATE_SPIN_POUND) || (player->actionState == ACTION_STATE_TORNADO_POUND)) {
            return ApiStatus_BLOCK;
        }
    }
    return ApiStatus_DONE2;
}

EvtScript EVS_UpdatePlatform = {
    SetGroup(EVT_GROUP_NOT_BATTLE)
    Call(ParentColliderToModel, LVarB, LVarA)
    SetF(LVar0, Float(0.0))
    SetF(LVarD, Float(-300.0))
    SubF(LVarD, LVarC)
    Label(0)
        SetF(LVar1, LVarC)
        SubF(LVar0, Float(80.0))
        Label(1)
            Call(PausePlatformsDuringPound)
            AddF(LVar0, Float(1.5))
            AddF(LVar1, Float(1.5))
            Call(TranslateModel, LVarA, 0, LVar0, 0)
            Call(UpdateColliderTransform, LVarB)
            Wait(1)
            IfLt(LVar1, Float(100.0))
                Goto(1)
            EndIf
        Call(TranslateModel, LVarA, 0, LVarD, 0)
        SetF(LVar0, LVarD)
        SetF(LVarC, Float(-300.0))
        Wait(1)
        Goto(0)
    Return
    End
};

EvtScript EVS_CreatePlatform1 = {
    Set(LVarA, MODEL_erb)
    Set(LVarB, COLLIDER_1)
    Set(LVarC, 20)
    ExecWait(EVS_UpdatePlatform)
    Return
    End
};

EvtScript EVS_CreatePlatform2 = {
    Set(LVarA, MODEL_o40)
    Set(LVarB, COLLIDER_3)
    Set(LVarC, -80)
    ExecWait(EVS_UpdatePlatform)
    Return
    End
};

EvtScript EVS_CreatePlatform3 = {
    Set(LVarA, MODEL_o41)
    Set(LVarB, COLLIDER_4)
    Set(LVarC, -170)
    ExecWait(EVS_UpdatePlatform)
    Return
    End
};

EvtScript EVS_CreatePlatform4 = {
    Set(LVarA, MODEL_o39)
    Set(LVarB, COLLIDER_2)
    Set(LVarC, -270)
    ExecWait(EVS_UpdatePlatform)
    Return
    End
};

EvtScript EVS_SetupPlatforms = {
    Exec(EVS_CreatePlatform1)
    Exec(EVS_CreatePlatform2)
    Exec(EVS_CreatePlatform3)
    Exec(EVS_CreatePlatform4)
    Return
    End
};
