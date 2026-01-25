#include "obk_02.h"

#include "world/common/atomic/TexturePan.inc.c"

enum {
    REGION_INIT_LAST    = -2,
    REGION_INIT         = -1,
    REGION_UPPER_FLOOR  = 0,
    REGION_STAIRS       = 1,
    REGION_LOWER_FLOOR  = 2,
};

EvtScript N(EVS_ExitDoor_obk_01_1) = EVT_EXIT_SINGLE_DOOR(obk_02_ENTRY_0, "obk_01", obk_01_ENTRY_1,
    COLLIDER_tt1, MODEL_door1b, DOOR_SWING_OUT);

EvtScript N(EVS_ExitDoor_obk_03_0) = EVT_EXIT_SINGLE_DOOR(obk_02_ENTRY_1, "obk_03", obk_03_ENTRY_0,
    COLLIDER_tt2, MODEL_door2, DOOR_SWING_OUT);

EvtScript N(EVS_ExitWalk_obk_06_1) = EVT_EXIT_WALK(60, obk_02_ENTRY_2, "obk_06", obk_06_ENTRY_1);

EvtScript N(EVS_BindExitTriggers) = {
    BindTrigger(Ref(N(EVS_ExitDoor_obk_01_1)), TRIGGER_WALL_PRESS_A, COLLIDER_tt1, 1, 0)
    BindTrigger(Ref(N(EVS_ExitDoor_obk_03_0)), TRIGGER_WALL_PRESS_A, COLLIDER_tt2, 1, 0)
    BindTrigger(Ref(N(EVS_ExitWalk_obk_06_1)), TRIGGER_FLOOR_ABOVE, COLLIDER_deili3, 1, 0)
    Return
    End
};

EvtScript N(EVS_EnterMap) = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(obk_02_ENTRY_0)
            Set(LVar2, MODEL_door1b)
            Set(LVar3, DOOR_SWING_OUT)
            ExecWait(EnterSingleDoor)
            ExecWait(N(EVS_BindExitTriggers))
        CaseEq(obk_02_ENTRY_1)
            Set(LVar2, MODEL_door2)
            Set(LVar3, DOOR_SWING_OUT)
            ExecWait(EnterSingleDoor)
            ExecWait(N(EVS_BindExitTriggers))
        CaseEq(obk_02_ENTRY_2)
            Set(LVar0, Ref(N(EVS_BindExitTriggers)))
            Exec(EnterWalk)
    EndSwitch
    Return
    End
};

EvtScript N(EVS_OnStep_UpperFloor) = {
    Set(MV_CurrentMapRegion, REGION_UPPER_FLOOR)
    Return
    End
};

EvtScript N(EVS_OnStep_Stairs) = {
    Set(MV_CurrentMapRegion, REGION_STAIRS)
    Return
    End
};

EvtScript N(EVS_OnStep_LowerFloor) = {
    Set(MV_CurrentMapRegion, REGION_LOWER_FLOOR)
    Return
    End
};

EvtScript N(EVS_EnableModels_LowerFloor) = {
    Call(EnableGroup, MODEL_off_1, TRUE)
    Call(EnableGroup, MODEL_bom, TRUE)
    Call(EnableGroup, MODEL_tokei, TRUE)
    Call(EnableGroup, MODEL_hikido, TRUE)
    IfEq(GF_OBK06_BombedWall, FALSE)
        Call(EnableModel, MODEL_bomu_ato, FALSE)
    Else
        Call(EnableModel, MODEL_bom_mae, FALSE)
    EndIf
    Return
    End
};

EvtScript N(EVS_DisableModels_LowerFloor) = {
    Call(EnableGroup, MODEL_off_1, FALSE)
    Call(EnableGroup, MODEL_bom, FALSE)
    Call(EnableGroup, MODEL_tokei, FALSE)
    Call(EnableGroup, MODEL_hikido, FALSE)
    Return
    End
};

EvtScript N(EVS_EnableModels_UpperFloor) = {
    Call(EnableGroup, MODEL_off_2, TRUE)
    Call(EnableGroup, MODEL_shiyan, TRUE)
    Call(EnableGroup, MODEL_door_1, TRUE)
    Return
    End
};

EvtScript N(EVS_DisableModels_UpperFloor) = {
    Call(EnableGroup, MODEL_off_2, FALSE)
    Call(EnableGroup, MODEL_shiyan, FALSE)
    Call(EnableGroup, MODEL_door_1, FALSE)
    Return
    End
};

EvtScript N(EVS_ManageRegionVisibility) = {
    BindTrigger(Ref(N(EVS_OnStep_UpperFloor)), TRIGGER_FLOOR_TOUCH, COLLIDER_o296, 1, 0)
    BindTrigger(Ref(N(EVS_OnStep_Stairs)), TRIGGER_FLOOR_TOUCH, COLLIDER_o309, 1, 0)
    BindTrigger(Ref(N(EVS_OnStep_LowerFloor)), TRIGGER_FLOOR_TOUCH, COLLIDER_o291, 1, 0)
    Set(MV_CurrentMapRegion, REGION_INIT)
    Set(MV_LastMapRegion, REGION_INIT_LAST)
    Loop(0)
        IfNe(MV_CurrentMapRegion, MV_LastMapRegion)
            Switch(MV_CurrentMapRegion)
                CaseEq(REGION_UPPER_FLOOR)
                    ExecWait(N(EVS_DisableModels_LowerFloor))
                    ExecWait(N(EVS_EnableModels_UpperFloor))
                CaseEq(REGION_STAIRS)
                    ExecWait(N(EVS_EnableModels_LowerFloor))
                    ExecWait(N(EVS_EnableModels_UpperFloor))
                CaseEq(REGION_LOWER_FLOOR)
                    ExecWait(N(EVS_EnableModels_LowerFloor))
                    ExecWait(N(EVS_DisableModels_UpperFloor))
            EndSwitch
        EndIf
        Set(MV_LastMapRegion, MV_CurrentMapRegion)
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript N(EVS_SetupTexPan) = {
    // spooky fog
    Call(SetTexPanner, MODEL_m2, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_m3, TEX_PANNER_0)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_0)
        TEX_PAN_PARAMS_STEP(  300,  100,    0,    0)
        TEX_PAN_PARAMS_FREQ(    1,    1,    0,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    Return
    End
};

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_BOOS_MANSION)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, FALSE, Ref(N(DefaultNPCs)))
    ExecWait(N(EVS_MakeEntities))
    Exec(N(EVS_SetupTexPan))
    Exec(N(EVS_SetupBombableWall))
    Exec(N(EVS_ClockDoNothing))
    Exec(N(EVS_UpdateClock))
    Exec(N(EVS_SetupMusic))
    Exec(N(EVS_EnterMap))
    Exec(N(EVS_ManageRegionVisibility))
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_si, COLLIDER_FLAGS_UPPER_MASK)
    Return
    End
};
