#include "obk_09.h"
#include "world/area/obk/obk_01.h"

EvtScript EVS_EnterMap = {
    Call(DisablePlayerInput, true)
    Call(EnableGroup, MODEL_ori, false)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_ori, COLLIDER_FLAGS_UPPER_MASK)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($FoyerWest.index)
            Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
            Set(LVar2, MODEL_d1_2)
            Set(LVar3, MODEL_d1_1)
            ExecWait(EnterDoubleDoor)
        CaseEq($FoyerEast.index)
            Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
            Set(LVar2, MODEL_d2_2)
            Set(LVar3, MODEL_d2_1)
            ExecWait(EnterDoubleDoor)
    EndSwitch
    Exec(EVS_Scene_MeetBow)
    Wait(1)
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript EVS_ExitDoors_obk_01_5 = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(
    $FoyerWest, $obk_01.LadyBowsRoomWest, COLLIDER_tt1, MODEL_d1_2, MODEL_d1_1, DOOR_SOUNDS_CREAKY
);

EvtScript EVS_ExitDoors_obk_01_6 = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(
    $FoyerEast, $obk_01.LadyBowsRoomEast, COLLIDER_tt2, MODEL_d2_2, MODEL_d2_1, DOOR_SOUNDS_CREAKY
);

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_BOOS_MANSION)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(GetEntryID, LVar0)
    IfEq(LVar0, $Epilogue.index)
        Call(MakeNpcs, false, EpilogueNPCs)
        Exec(EVS_Scene_Epilogue)
        Call(FadeInMusic, 0, SONG_CHEERFUL_BOOS_MANSION, 0, 3000, 0, 127)
        Wait(1)
        Return
    EndIf
    Call(MakeNpcs, false, DefaultNPCs)
    BindTrigger(EVS_ExitDoors_obk_01_5, TRIGGER_WALL_PRESS_A, COLLIDER_tt1, 1, 0)
    BindTrigger(EVS_ExitDoors_obk_01_6, TRIGGER_WALL_PRESS_A, COLLIDER_tt2, 1, 0)
    Exec(EVS_EnterMap)
    Exec(EVS_SetupMusic)
    Return
    End
};
