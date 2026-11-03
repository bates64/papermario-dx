#include "dgb_14.h"
#include "world/area/dgb/dgb_03.h"
#include "world/area/dgb/dgb_15.h"
#include "sprite/player.h"

EvtScript EVS_ExitDoors_dgb_03_3 = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(
    $Dgb15, $dgb_03.Dgb14, COLLIDER_deilittse, MODEL_o102, MODEL_o101, DOOR_SOUNDS_CREAKY
);

EvtScript EVS_ExitDoors_dgb_15_0 = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(
    $Dgb03, $dgb_15.Dgb14, COLLIDER_deilittne, MODEL_o31, MODEL_o30, DOOR_SOUNDS_CREAKY
);

EvtScript EVS_EnterMap = {
    Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($Dgb03.index)
            Set(LVar2, MODEL_o102)
            Set(LVar3, MODEL_o101)
            ExecWait(EnterDoubleDoor)
        CaseEq($Dgb15.index)
            Call(DisablePlayerInput, true)
            Set(LVar2, MODEL_o31)
            Set(LVar3, MODEL_o30)
            ExecWait(EnterDoubleDoor)
            IfEq(AF_DGB_CloseCallWithTubba, true)
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

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_TUBBAS_MANOR)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    BindTrigger(EVS_ExitDoors_dgb_03_3, TRIGGER_WALL_PRESS_A, COLLIDER_deilittse, 1, 0)
    BindTrigger(EVS_ExitDoors_dgb_15_0, TRIGGER_WALL_PRESS_A, COLLIDER_deilittne, 1, 0)
    Exec(EVS_EnterMap)
    Return
    End
};
