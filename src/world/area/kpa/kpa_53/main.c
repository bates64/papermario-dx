
#include "kpa_53.h"
#include "world/area/kpa/kpa_102.h"
#include "world/area/kpa/kpa_83.h"

export s32 map_init(void) {
    gGameStatusPtr->playerSpriteSet = PLAYER_SPRITES_COMBINED_EPILOGUE;
    use_map_geometry("kpa_50");
    return false;
}

EvtScript EVS_ExitDoors_kpa_102_1 =
    EVT_EXIT_DOUBLE_DOOR($BlueFireBridge, $kpa_102.FakePeachHallway, COLLIDER_ttw, MODEL_o321, MODEL_o323);
EvtScript EVS_ExitDoors_kpa_83_0 =
    EVT_EXIT_DOUBLE_DOOR($GuardDoor3, $kpa_83.FakePeachHallway, COLLIDER_tte, MODEL_o324, MODEL_o322);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitDoors_kpa_102_1, TRIGGER_WALL_PRESS_A, COLLIDER_ttw, 1, 0)
    IfEq(GF_KPA53_Defeated_PeachImposter, true)
        BindTrigger(EVS_ExitDoors_kpa_83_0, TRIGGER_WALL_PRESS_A, COLLIDER_tte, 1, 0)
    EndIf
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($BlueFireBridge.index)
            Set(LVar0, $BlueFireBridge.index)
            Set(LVar2, MODEL_o321)
            Set(LVar3, MODEL_o323)
            Exec(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq($GuardDoor3.index)
            Set(LVar0, $GuardDoor3.index)
            Set(LVar2, MODEL_o324)
            Set(LVar3, MODEL_o322)
            Exec(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Call(MakeNpcs, true, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_CLEAR_BITS, COLLIDER_ttw, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_CLEAR_BITS, COLLIDER_tte, COLLIDER_FLAGS_UPPER_MASK)
    Exec(EVS_EnterMap)
    Wait(1)
    Exec(EVS_SetupMusic)
    Return
    End
};
