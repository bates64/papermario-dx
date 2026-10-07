#include "kpa_81.h"

export s32 map_init(void) {
    use_map_geometry("kpa_80");
    return false;
}

s32 RightDoorModels[] = {
    MODEL_o140,
    MODEL_o142,
    MODEL_o121,
    MODEL_g35,
    MODEL_o116,
    MODEL_o170,
    -1
};

s32 LeftDoorModels[] = {
    MODEL_o161,
    MODEL_o162,
    MODEL_o119,
    MODEL_g33,
    MODEL_o126,
    MODEL_o171,
    -1
};

EvtScript EVS_ExitDoors_kpa_50_1 = EVT_EXIT_DOUBLE_DOOR(kpa_81_ENTRY_0, "kpa_50", kpa_50_ENTRY_1, COLLIDER_deilittw, MODEL_o174, MODEL_o173);

EvtScript EVS_ExitDoors_kpa_32_0 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Set(LVar0, kpa_81_ENTRY_2)
    Set(LVar1, COLLIDER_o166)
    Set(LVar2, Ref(RightDoorModels))
    Set(LVar3, Ref(LeftDoorModels))
    Exec(BaseExitDoor)
    Wait(17)
    Call(GotoMap, Ref("kpa_32"), kpa_32_ENTRY_0)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitWalk_kpa_04_1 = EVT_EXIT_WALK(60, kpa_81_ENTRY_3, "kpa_04", kpa_04_ENTRY_1);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitDoors_kpa_50_1), TRIGGER_WALL_PRESS_A, COLLIDER_deilittw, 1, 0)
    BindTrigger(Ref(EVS_ExitWalk_kpa_04_1), TRIGGER_FLOOR_ABOVE, COLLIDER_deilin, 1, 0)
    IfNe(GB_KPA81_BowserDoorState, 0)
        BindTrigger(Ref(EVS_ExitDoors_kpa_32_0), TRIGGER_WALL_PRESS_A, COLLIDER_o166, 1, 0)
    EndIf
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(kpa_81_ENTRY_0)
            Set(LVar0, kpa_81_ENTRY_0)
            Set(LVar2, MODEL_o174)
            Set(LVar3, MODEL_o173)
            Exec(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq(kpa_81_ENTRY_2)
            Set(LVar0, kpa_81_ENTRY_2)
            Set(LVar2, Ref(LeftDoorModels))
            Set(LVar3, Ref(RightDoorModels))
            ExecWait(BaseEnterDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq(kpa_81_ENTRY_3)
            Set(LVar0, Ref(EVS_BindExitTriggers))
            Exec(EnterWalk)
    EndSwitch
    Return
    End
};

EvtScript EVS_UnusedMoveStatue = {
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    IfLt(LVar0, 0)
        Return
    EndIf
    Call(ParentColliderToModel, COLLIDER_o146, MODEL_o145)
    Call(MakeLerp, 0, -40, 40, EASING_LINEAR)
    Label(0)
        Call(UpdateLerp)
        Call(TranslateModel, MODEL_o145, LVar0, 0, 0)
        Call(TranslateModel, MODEL_o146, LVar0, 0, 0)
        Call(UpdateColliderTransform, COLLIDER_o146)
        Wait(1)
        IfEq(LVar1, 1)
            Goto(0)
        EndIf
    Unbind
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_BOWSERS_CASTLE)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, true, Ref(DefaultNPCs))
    IfNe(GB_KPA81_BowserDoorState, 0)
        Call(GetEntryID, LVar0)
        Switch(LVar0)
            CaseEq(kpa_81_ENTRY_0)
                BindTrigger(Ref(EVS_UnusedMoveStatue), TRIGGER_WALL_PRESS_A, COLLIDER_o146, 1, 0)
            CaseEq(kpa_81_ENTRY_2)
                BindTrigger(Ref(EVS_UnusedMoveStatue), TRIGGER_WALL_PRESS_A, COLLIDER_o146, 1, 0)
            CaseEq(kpa_81_ENTRY_3)
        EndSwitch
    EndIf
    Call(ParentColliderToModel, COLLIDER_o146, MODEL_o145)
    Switch(GB_KPA04_StatuePosition)
        CaseEq(1)
            Call(TranslateModel, MODEL_o145, -50, 0, 0)
            Call(TranslateModel, MODEL_o146, -50, 0, 0)
        CaseEq(2)
            Call(TranslateModel, MODEL_o145, 50, 0, 0)
            Call(TranslateModel, MODEL_o146, 50, 0, 0)
    EndSwitch
    Call(UpdateColliderTransform, COLLIDER_o146)
    Call(EnableModel, MODEL_o166, false)
    Call(EnableModel, MODEL_m_, false)
    Call(EnableModel, MODEL_m_kai, false)
    Call(EnableModel, MODEL_m1, false)
    Call(EnableModel, MODEL_m2, false)
    Call(EnableModel, MODEL_m3, false)
    Call(EnableModel, MODEL_m4, false)
    Call(EnableModel, MODEL_m5, false)
    Call(EnableModel, MODEL_m6, false)
    Call(EnableModel, MODEL_m7, false)
    Call(EnableModel, MODEL_b_, false)
    Call(EnableModel, MODEL_b_kai, false)
    Call(EnableModel, MODEL_b1, false)
    Call(EnableModel, MODEL_b2, false)
    Call(EnableModel, MODEL_b3, false)
    Call(EnableModel, MODEL_b4, false)
    Call(EnableModel, MODEL_b5, false)
    Call(EnableModel, MODEL_b6, false)
    Call(EnableModel, MODEL_b7, false)
    Exec(EVS_EnterMap)
    Wait(1)
    Exec(EVS_SetupMusic)
    Return
    End
};
