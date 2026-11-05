#include "mac_03.h"
#include "world/area/mac/mac_02.h"
#include "world/area/mgm/mgm_00.h"

#include "world/common/entity/Pipe.inc.c"

EvtScript EVS_ExitWalk_mac_02_3 = EVT_EXIT_WALK(60, $SouthernDistrict, $mac_02.StationDistrict);

EvtScript EVS_GotoMap_mgm_00_0 = {
    Call(GotoMap, $mgm_00.StationDistrict)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitPipe_mgm_00_0 = EVT_EXIT_PIPE_VERTICAL($PlayroomPipe, COLLIDER_deilim, EVS_GotoMap_mgm_00_0);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_mac_02_3, TRIGGER_FLOOR_ABOVE, COLLIDER_deilin, 1, 0)
    BindTrigger(EVS_ExitPipe_mgm_00_0, TRIGGER_FLOOR_TOUCH, COLLIDER_deilim, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($SouthernDistrict.index)
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
        CaseEq($MtRugged.index)
            Exec(EVS_ArriveFromMtRugged)
            Exec(EVS_BindExitTriggers)
        CaseEq($PlayroomPipe.index)
            EVT_ENTER_PIPE_VERTICAL(EVS_BindExitTriggers)
        CaseEq($Entry3.index)
    EndSwitch
    Return
    End
};

EvtScript EVS_HidePlayroomPipe = {
    IfEq(GF_MAC03_UnlockedPlayroom, false)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_dokan, COLLIDER_FLAGS_UPPER_MASK)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilim, COLLIDER_FLAGS_UPPER_MASK)
        Call(EnableModel, MODEL_o241, false)
    EndIf
    Return
    End
};

API_CALLABLE(GetClockHandAngles) {
    if (script->varTable[15] > 720) {
        script->varTable[15] = 0;
    }
    script->varTable[0] = script->varTable[15] * 6;
    script->varTable[1] = script->varTable[15] / 2;
    return ApiStatus_DONE2;
}

EvtScript EVS_Main = {
#if VERSION_PAL
    Call(GetLanguage, LVar0)
    Call(SetModelTexVariant, MODEL_o110, LVar0)
#endif
    Set(AF_MAC03_Unread_20, false)
    Set(AF_MAC03_Unread_21, false)
    Set(AF_MAC03_Unread_22, false)
    Set(AF_MAC03_Unread_23, false)
    Set(AF_MAC03_Unread_24, false)
    Set(AF_MAC03_Unread_25, false)
    Call(MakeNpcs, false, DefaultNPCs)
    Exec(EVS_MakeEntities)
    Exec(EVS_SetupFoliage)
    Call(GetDemoState, LVar0)
    IfEq(LVar0, DEMO_STATE_NONE)
        Exec(EVS_InitializeLilOinks)
    EndIf
    ExecWait(EVS_InitializeTrainScene)
    Thread
        Set(LVarF, 0)
        Label(10)
            Add(LVarF, 1)
            Call(GetClockHandAngles)
            Call(RotateModel, MODEL_o148, LVar0, 0, 0, -1)
            Call(RotateModel, MODEL_o147, LVar1, 0, 0, -1)
            Wait(10)
            Goto(10)
    EndThread
    Call(GetDemoState, LVar0)
    IfNe(LVar0, DEMO_STATE_NONE)
        ExecWait(EVS_PlayDemoScene)
        Return
    EndIf
    Exec(EVS_SetupMusic)
    Exec(EVS_HidePlayroomPipe)
    Exec(EVS_EnterMap)
    Set(GF_MAC01_RowfBadgesChosen, false)
    Wait(1)
    Return
    End
};
