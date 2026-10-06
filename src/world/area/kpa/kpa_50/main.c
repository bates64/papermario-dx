#include "kpa_50.h"

EvtScript EVS_ExitWalk_kpa_70_1 = EVT_EXIT_WALK(60, kpa_50_ENTRY_0, "kpa_70", kpa_70_ENTRY_1);
EvtScript EVS_ExitDoors_kpa_81_0 = EVT_EXIT_DOUBLE_DOOR(kpa_50_ENTRY_1, "kpa_81", kpa_81_ENTRY_0, COLLIDER_tte, MODEL_o324, MODEL_o322);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitWalk_kpa_70_1), TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(Ref(EVS_ExitDoors_kpa_81_0), TRIGGER_WALL_PRESS_A, COLLIDER_tte, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(kpa_50_ENTRY_0)
            Set(LVar0, Ref(EVS_BindExitTriggers))
            Exec(EnterWalk)
        CaseEq(kpa_50_ENTRY_1)
            Set(LVar0, kpa_50_ENTRY_1)
            Set(LVar2, MODEL_o324)
            Set(LVar3, MODEL_o322)
            Exec(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_BOWSERS_CASTLE)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(MakeNpcs, true, Ref(DefaultNPCs))
    Call(SetGroupVisibility, MODEL_dw1, MODEL_GROUP_HIDDEN)
    Call(SetGroupVisibility, MODEL_dw2, MODEL_GROUP_HIDDEN)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_CLEAR_BITS, COLLIDER_tte, COLLIDER_FLAGS_UPPER_MASK)
    Exec(EVS_EnterMap)
    Wait(1)
    Exec(EVS_SetupMusic)
    Return
    End
};
