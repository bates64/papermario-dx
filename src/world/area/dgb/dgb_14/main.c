#include "dgb_14.h"
#include "sprite/player.h"

EvtScript N(EVS_ExitDoors_dgb_03_3) = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(dgb_14_ENTRY_1, "dgb_03", dgb_03_ENTRY_3,
    COLLIDER_deilittse, MODEL_o102, MODEL_o101, DOOR_SOUNDS_CREAKY);

EvtScript N(EVS_ExitDoors_dgb_15_0) = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(dgb_14_ENTRY_0, "dgb_15", dgb_15_ENTRY_0,
    COLLIDER_deilittne, MODEL_o31, MODEL_o30, DOOR_SOUNDS_CREAKY);

EvtScript N(EVS_EnterMap) = {
    Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(dgb_14_ENTRY_0)
            Set(LVar2, MODEL_o102)
            Set(LVar3, MODEL_o101)
            ExecWait(EnterDoubleDoor)
        CaseEq(dgb_14_ENTRY_1)
            Call(DisablePlayerInput, true)
            Set(LVar2, MODEL_o31)
            Set(LVar3, MODEL_o30)
            ExecWait(EnterDoubleDoor)
            IfEq(AF_DGB_01, true)
                Wait(5)
                Call(SetPlayerAnimation, ANIM_MarioW2_SleepStanding)
                Wait(20)
                Call(SetPlayerAnimation, ANIM_Mario1_Idle)
            EndIf
            Call(DisablePlayerInput, false)
    EndSwitch
    Return
    End
};

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_TUBBAS_MANOR)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    ExecWait(N(EVS_MakeEntities))
    Exec(N(EVS_SetupMusic))
    BindTrigger(Ref(N(EVS_ExitDoors_dgb_03_3)), TRIGGER_WALL_PRESS_A, COLLIDER_deilittse, 1, 0)
    BindTrigger(Ref(N(EVS_ExitDoors_dgb_15_0)), TRIGGER_WALL_PRESS_A, COLLIDER_deilittne, 1, 0)
    Exec(N(EVS_EnterMap))
    Return
    End
};
