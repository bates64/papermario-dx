#include "kpa_63.h"
#include "world/area/kpa/kpa_62.h"

EvtScript EVS_OpenHangerDoor = {
    Call(PlaySoundAtCollider, COLLIDER_tts, SOUND_AIRSHIP_DOCK_DOOR_OPEN, SOUND_SPACE_DEFAULT)
    Call(MakeLerp, 100, 0, 20, EASING_CUBIC_IN)
    Loop(0)
        Call(UpdateLerp)
        SetF(LVar5, LVar0)
        MulF(LVar5, 0.01)
        Call(ScaleGroup, MODEL_g75, LVar5, 1, 1)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Return
    End
};

EvtScript EVS_CloseHangerDoor = {
    Call(MakeLerp, 0, 100, 20, EASING_CUBIC_IN)
    Loop(0)
        Call(UpdateLerp)
        SetF(LVar5, LVar0)
        MulF(LVar5, 0.01)
        Call(ScaleGroup, MODEL_g75, LVar5, 1, 1)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Call(PlaySoundAtCollider, COLLIDER_tts, SOUND_AIRSHIP_DOCK_DOOR_CLOSE, SOUND_SPACE_DEFAULT)
    Return
    End
};

EvtScript EVS_ExitDoor_kpa_62_3 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Exec(EVS_OpenHangerDoor)
    Wait(15)
    Call(UseExitHeading, 60, $FrontDoor.index)
    Exec(ExitWalk)
    Call(GotoMap, $kpa_62.Hanger)
    Wait(100)
    Return
    End
};

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitDoor_kpa_62_3, TRIGGER_WALL_PRESS_A, COLLIDER_tts, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetLoadType, LVar0)
    IfEq(LVar0, LOAD_FROM_FILE_SELECT)
        Exec(EnterSavePoint)
        Exec(EVS_BindExitTriggers)
        Return
    EndIf
    Call(GetEntryID, LVar0)
    IfEq(LVar0, $Starship.index)
        Exec(EVS_Starship_Arrive)
        Exec(EVS_BindExitTriggers)
    Else
        Exec(EVS_CloseHangerDoor)
        Set(LVar0, EVS_BindExitTriggers)
        Exec(EnterWalk)
        Wait(1)
    EndIf
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_BOWSERS_CASTLE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Set(GF_MAP_BowsersCastle, true)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_EnterMap)
    Exec(EVS_SetupMusic)
    BindTrigger(EVS_Starship_Depart, TRIGGER_FLOOR_TOUCH, COLLIDER_o400, 1, 0)
    Exec(EVS_SetupStarship)
    Return
    End
};
