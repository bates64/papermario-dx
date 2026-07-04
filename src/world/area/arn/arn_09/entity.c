#include "arn_09.h"
#include "entity.h"
#include "sprite/player.h"

EvtScript N(EVS_UseSpring) = {
    IfEq(AF_ARN_UsingWellSpring, true)
        Return
    EndIf
    Set(AF_ARN_UsingWellSpring, true)
    Call(DisablePlayerInput, true)
    Call(DisablePlayerPhysics, true)
    Call(SetPlayerActionState, ACTION_STATE_LAUNCH)
    Wait(1)
    Call(SetPlayerJumpscale, Float(1.0))
    Call(PlayerJump, 0, 200, 0, 30)
    Call(GotoMap, Ref("arn_08"), arn_08_ENTRY_1)
    Wait(100)
    Call(DisablePlayerInput, false)
    Call(DisablePlayerPhysics, false)
    Return
    End
};

EvtScript N(EVS_LandFromWell) = {
    IfEq(AF_ARN_UsingWellSpring, false)
        Return
    EndIf
    Set(AF_ARN_UsingWellSpring, true)
    Call(DisablePlayerInput, true)
    Call(SetPlayerActionState, ACTION_STATE_FALLING)
    Call(AwaitAnyPlayerFloorTouch)
    Call(SetPlayerActionState, ACTION_STATE_LAUNCH)
    Call(SetPlayerJumpscale, Float(1.5))
    Call(PlayerJump, 50, 0, 0, 16)
    Call(SetPlayerAnimation, ANIM_Mario1_Idle)
    Set(AF_ARN_UsingWellSpring, false)
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript N(EVS_MakeEntities) = {
    Call(MakeEntity, Ref(Entity_ScriptSpring), 0, 0, 0, 0, MAKE_ENTITY_END)
    Call(AssignScript, Ref(N(EVS_UseSpring)))
    Return
    End
};
