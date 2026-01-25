#include "obk_09.h"

EvtScript N(EVS_EnterMap) = {
    Call(DisablePlayerInput, TRUE)
    Call(EnableGroup, MODEL_ori, FALSE)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_ori, COLLIDER_FLAGS_UPPER_MASK)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(obk_09_ENTRY_0)
            Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
            Set(LVar2, MODEL_d1_2)
            Set(LVar3, MODEL_d1_1)
            ExecWait(EnterDoubleDoor)
        CaseEq(obk_09_ENTRY_1)
            Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
            Set(LVar2, MODEL_d2_2)
            Set(LVar3, MODEL_d2_1)
            ExecWait(EnterDoubleDoor)
    EndSwitch
    Exec(N(EVS_Scene_MeetBow))
    Wait(1)
    Call(DisablePlayerInput, FALSE)
    Return
    End
};

EvtScript N(EVS_ExitDoors_obk_01_5) = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(obk_09_ENTRY_0, "obk_01", obk_01_ENTRY_5,
    COLLIDER_tt1, MODEL_d1_2, MODEL_d1_1, DOOR_SOUNDS_CREAKY);

EvtScript N(EVS_ExitDoors_obk_01_6) = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(obk_09_ENTRY_1, "obk_01", obk_01_ENTRY_6,
    COLLIDER_tt2, MODEL_d2_2, MODEL_d2_1, DOOR_SOUNDS_CREAKY);

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_BOOS_MANSION)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(GetEntryID, LVar0)
    IfEq(LVar0, obk_09_ENTRY_2)
        Call(MakeNpcs, FALSE, Ref(N(EpilogueNPCs)))
        Exec(N(EVS_Scene_Epilogue))
        Call(FadeInMusic, 0, SONG_CHEERFUL_BOOS_MANSION, 0, 3000, 0, 127)
        Wait(1)
        Return
    EndIf
    Call(MakeNpcs, FALSE, Ref(N(DefaultNPCs)))
    BindTrigger(Ref(N(EVS_ExitDoors_obk_01_5)), TRIGGER_WALL_PRESS_A, COLLIDER_tt1, 1, 0)
    BindTrigger(Ref(N(EVS_ExitDoors_obk_01_6)), TRIGGER_WALL_PRESS_A, COLLIDER_tt2, 1, 0)
    Exec(N(EVS_EnterMap))
    Exec(N(EVS_SetupMusic))
    Return
    End
};
