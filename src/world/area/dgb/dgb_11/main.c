#include "dgb_11.h"
#include "world/area/dgb/dgb_02.h"

EvtScript EVS_ExitDoor_dgb_02_3 = EVT_EXIT_SINGLE_DOOR_SET_SOUNDS(
    $Dgb02, $dgb_02.Dgb11, COLLIDER_deilits, MODEL_o109, DOOR_SWING_IN, DOOR_SOUNDS_BASIC
);

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($Dgb02.index)
            Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
            Set(LVar2, MODEL_o109)
            Set(LVar3, DOOR_SWING_IN)
            ExecWait(EnterSingleDoor)
            Return
        CaseEq($HoleSouthEast.index)
            Call(UseSettingsFrom, CAM_DEFAULT, 500, 0, -100)
            Call(SetPanTarget, CAM_DEFAULT, 500, 0, -100)
            Set(LVar3, 1)
        CaseEq($HoleNorthEast.index)
            Call(UseSettingsFrom, CAM_DEFAULT, 500, 75, -250)
            Call(SetPanTarget, CAM_DEFAULT, 500, 75, -250)
            Set(LVar3, 75)
        CaseEq($HoleNorthWest.index)
            Call(SetZoneEnabled, ZONE_o203, false)
            Call(UseSettingsFrom, CAM_DEFAULT, 375, 0, -175)
            Call(SetPanTarget, CAM_DEFAULT, 375, 0, -175)
            Set(AF_DGB11_FallingFromHole, true)
            Set(LVar3, 1)
    EndSwitch
    Call(DisablePlayerInput, true)
    Call(InterpPlayerYaw, 180, 0)
    Call(SetCamSpeed, CAM_DEFAULT, 90.0)
    Call(PanToTarget, CAM_DEFAULT, 0, true)
    Loop(0)
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
        IfLe(LVar1, LVar3)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Call(PanToTarget, CAM_DEFAULT, 0, false)
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_TUBBAS_MANOR)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    BindTrigger(EVS_ExitDoor_dgb_02_3, TRIGGER_WALL_PRESS_A, COLLIDER_deilits, 1, 0)
    Exec(EVS_EnterMap)
    Return
    End
};
