#include "kpa_91.h"
#include "world/area/kpa/kpa_90.h"

EvtScript EVS_ExitWalk_kpa_90_1 = EVT_EXIT_WALK(60, $EastJailStairs, $kpa_90.EastUpperJail);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_kpa_90_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    Return
    End
};

EvtScript EVS_OpenCellDoor = {
    Call(DisablePlayerInput, true)
    Call(PlayerMoveTo, -30, 15, 20)
    Call(InterpPlayerYaw, 90, 2)
    Call(PlaySoundAtCollider, COLLIDER_deilittn, SOUND_METAL_GATE_OPEN, SOUND_SPACE_DEFAULT)
    Call(MakeLerp, 0, 140, 60, EASING_COS_IN_OUT)
    Label(0)
        Call(UpdateLerp)
        Call(RotateModel, MODEL_o199, LVar0, 0, 1, 0)
        Call(RotateModel, MODEL_g35, LVar0, 0, 1, 0)
        Wait(1)
        IfEq(LVar1, 1)
            Goto(0)
        EndIf
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilittn, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_CLEAR_BITS, COLLIDER_o297, COLLIDER_FLAGS_UPPER_MASK)
    Call(DisablePlayerInput, false)
    Unbind
    Return
    End
};

EvtScript EVS_Main = {
    Set(AB_KPA91_DialogueState_Toad2, 0)
    Set(AB_KPA91_DialogueState_Dryite, 0)
    Set(AB_KPA91_DialogueState_ToadGuard, 0)
    Call(MakeNpcs, true, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    Exec(EVS_SetupMusic)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o297, COLLIDER_FLAGS_UPPER_MASK)
    Return
    End
};
