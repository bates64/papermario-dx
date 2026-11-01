#include "dro_01.h"
#include "world/area/dro/dro_02.h"
#include "world/area/sbk/sbk_36.h"

#include "world/common/entity/Pipe.inc.c"

EvtScript EVS_ExitWalk_sbk_36_1 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Set(GF_DRO01_HeardHintAboutSpinningRoof, 0)
    Call(UseExitHeading, 60, $DryDryDesert.index)
    Exec(ExitWalk)
    Call(GotoMap, $sbk_36.DryDryOutpost)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitWalk_dro_02_0 = EVT_EXIT_WALK(60, $Dro02, $dro_02.Dro01);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_sbk_36_1, TRIGGER_FLOOR_ABOVE, 1, 1, 0)
    BindTrigger(EVS_ExitWalk_dro_02_0, TRIGGER_FLOOR_ABOVE, 5, 1, 0)
    Return
    End
};

EvtScript EVS_Scene_RuinsRising = {
    Call(PlaySound, SOUND_LOOP_SBK_RUINS_RISING_DISTANT)
    Call(UseSettingsFrom, CAM_DEFAULT, 175, 0, -201)
    Call(SetPanTarget, CAM_DEFAULT, 175, 0, -201)
    Call(SetCamSpeed, CAM_DEFAULT, 90.0)
    Call(PanToTarget, CAM_DEFAULT, 0, true)
    Call(SetModelTintMode, APPLY_TINT_BG, nullptr, ENV_TINT_REMAP)
    Call(SetModelTintMode, APPLY_TINT_GROUPS, -1, ENV_TINT_REMAP)
    Call(SetModelTintParams, ENV_TINT_REMAP, 44, 32, 177, 0, 0, 0, 0, 0, 0)
    Call(DisablePlayerInput, true)
    Thread
        Call(ShakeCam, CAM_DEFAULT, 0, 300, 0.2)
    EndThread
    Thread
        Wait(60)
        Call(GetEntryID, LVar0)
        IfEq(LVar0, $RuinsRisingA.index)
            Call(GotoMap, $dro_02.RuinsRisingA)
        Else
            Call(GotoMap, $dro_02.RuinsRisingB)
        EndIf
        Wait(100)
    EndThread
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetLoadType, LVar1)
    IfEq(LVar1, LOAD_FROM_FILE_SELECT)
        Exec(EnterSavePoint)
        Exec(EVS_BindExitTriggers)
        Return
    EndIf
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($Pipe.index)
            IfEq(GF_DRO01_WarpPipe, false)
                Call(DisablePlayerInput, true)
                Call(DisablePlayerPhysics, true)
                Call(GetPlayerPos, LVar0, LVar1, LVar2)
                Call(SetNpcPos, NPC_PARTNER, LVar0, LVar1, LVar2)
                Call(SetPlayerPos, LVar0, NPC_DISPOSE_POS_Y, LVar2)
                Wait(30)
                Call(PlaySound, SOUND_GROW)
                Set(GF_DRO01_WarpPipe, true)
                Wait(30)
                Call(SetPlayerActionState, ACTION_STATE_IDLE)
                Call(SetPlayerPos, LVar0, LVar1, LVar2)
                Call(SetNpcPos, NPC_PARTNER, LVar0, LVar1, LVar2)
                Call(DisablePlayerPhysics, false)
                Call(DisablePlayerInput, false)
            EndIf
            Set(LVarA, EVS_BindExitTriggers)
            ExecWait(EVS_Pipe_EnterVertical)
        CaseOrEq($RuinsRisingA.index)
        CaseOrEq($RuinsRisingB.index)
            ExecWait(EVS_Scene_RuinsRising)
        EndCaseGroup
        CaseEq($Entry10.index)
            Exec(EnterPostPipe)
            Exec(EVS_BindExitTriggers)
        CaseDefault
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
    EndSwitch
    Wait(1)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_DRY_DRY_OUTPOST)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Set(GF_MAP_DryDryOutpost, true)
    IfLt(GB_StoryProgress, STORY_CH2_ARRIVED_AT_DRY_DRY_OUTPOST)
        Set(GB_StoryProgress, STORY_CH2_ARRIVED_AT_DRY_DRY_OUTPOST)
    EndIf
    Switch(GB_StoryProgress)
        CaseRange(STORY_CH2_STAR_SPIRIT_DEPARTED, STORY_CH4_BEGAN_PEACH_MISSION)
            Call(MakeNpcs, false, Chapter3NPCs)
        CaseDefault
            Call(MakeNpcs, false, DefaultNPCs)
    EndSwitch
    Call(InitVirtualEntityList)
    ExecWait(EVS_MakeEntities)
    Call(MakeShop, ShopItemPositions, ShopInventory, ShopPriceList, 0)
    Call(MakeShopOwner, MouserShopOwner)
    ExecWait(EVS_SetupRooms)
    Exec(EVS_ShopSignSwing)
    Exec(EVS_SetupMusic)
    Exec(EVS_EnterMap)
    Wait(1)
    Exec(EVS_SetupFoliage)
    Return
    End
};
