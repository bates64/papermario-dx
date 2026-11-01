#include "mac_01.h"
#include "world/area/kmr/kmr_22.h"
#include "world/area/mac/mac_00.h"
#include "world/area/mac/mac_02.h"
#include "world/area/nok/nok_11.h"
#include "world/area/osr/osr_00.h"
#include "world/area/osr/osr_01.h"

EvtScript EVS_ExitWalk_mac_00_1 = EVT_EXIT_WALK(60, $GateDistrict, $mac_00.PlazaDistrict);

EvtScript EVS_ExitWalk_nok_11_0 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(UseExitHeading, 60, $PleasantPath.index)
    Exec(ExitWalk)
    IfEq(GF_StartedChapter1, false)
        Set(GF_StartedChapter1, true)
        Call(FadeOutMusic, 0, 1500)
        Call(GotoMapSpecial, $kmr_22.Chapter1, TRANSITION_BEGIN_OR_END_CHAPTER)
        Wait(100)
        Return
    EndIf
    Call(GotoMap, $nok_11.ToadTown)
    Wait(100)
    Return
    End
};

s32 Models_CastleGateL[] = {
    MODEL_o306,
    MODEL_o307,
    -1
};

s32 Models_CastleGateR[] = {
    MODEL_o308,
    MODEL_o309,
    -1
};

EvtScript EVS_ExitDoors_osr_01_0 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Call(UseDoorSounds, DOOR_SOUNDS_LARGE)
    Set(LVar0, 2)
    Set(LVar1, 5)
    Set(LVar2, Models_CastleGateL)
    Set(LVar3, Models_CastleGateR)
    Exec(BaseExitDoor)
    Wait(17)
    Switch(GB_StoryProgress)
        CaseRange(STORY_CH0_WAKE_UP, STORY_CH8_REACHED_PEACHS_CASTLE)
            Call(GotoMap, $osr_01.ToadTown)
        CaseDefault
            Call(GotoMap, $osr_00.ToadTown)
    EndSwitch
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitWalk_mac_02_2 = EVT_EXIT_WALK(60, $SouthernDistrict, $mac_02.PlazaDistrict);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_mac_00_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitDoors_osr_01_0, TRIGGER_WALL_PRESS_A, COLLIDER_deilitn, 1, 0)
    IfGe(GB_StoryProgress, STORY_EPILOGUE)
        Return
    EndIf
    BindTrigger(EVS_ExitWalk_nok_11_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    BindTrigger(EVS_ExitWalk_mac_02_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
    BindTrigger(EVS_ExitFlowerGate, TRIGGER_WALL_PRESS_A, COLLIDER_deilitf, 1, 0)
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
        CaseEq($PeachsCastle.index)
            Call(DisablePlayerInput, true)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitn, COLLIDER_FLAGS_UPPER_MASK)
            Call(RotateGroup, MODEL_east_gate, 80, 0, 1, 0)
            Call(RotateGroup, MODEL_west_gate, 80, 0, -1, 0)
            Call(UseDoorSounds, DOOR_SOUNDS_LARGE)
            Set(LVar0, EVS_BindExitTriggers)
            ExecWait(EnterWalk)
            Call(MakeLerp, 80, 0, 10, EASING_LINEAR)
            Loop(0)
                Call(UpdateLerp)
                Call(RotateGroup, MODEL_east_gate, LVar0, 0, 1, 0)
                Call(RotateGroup, MODEL_west_gate, LVar0, 0, -1, 0)
                Wait(1)
                IfEq(LVar1, 0)
                    BreakLoop
                EndIf
            EndLoop
            Call(PlaySoundAtCollider, COLLIDER_deilitn, SOUND_LARGE_DOOR_CLOSE, SOUND_SPACE_DEFAULT)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_CLEAR_BITS, COLLIDER_deilitn, COLLIDER_FLAGS_UPPER_MASK)
            Call(DisablePlayerInput, false)
        CaseEq($Intro.index)
            Exec(EVS_Scene_IntroWalking)
        CaseEq($FlowerGate.index)
            ExecWait(EVS_EnterFlowerGate)
            Exec(EVS_BindExitTriggers)
        CaseDefault
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_TOAD_TOWN)
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamPerspective, CAM_DEFAULT, CAM_UPDATE_FROM_ZONE, 25, 90, 4096) // note: unusually large near clip dist: 90 vs 16
    Call(SetCamBGColor, CAM_DEFAULT, 0, 0, 0)
    Call(SetCamEnabled, CAM_DEFAULT, true)
    Call(SetCamLeadPlayer, CAM_DEFAULT, false)
#if VERSION_PAL
    Call(GetLanguage, LVar0)
    Call(SetModelTexVariant, MODEL_k11, LVar0)
#endif
    Set(AF_MAC01_Unread_0E, false)
    Set(AF_MAC01_Unread_0F, false)
    Set(AF_MAC01_Unread_10, false)
    Set(AF_MAC01_Unread_11, false)
    Set(AF_MAC01_Unread_12, false)
    Set(AF_MAC01_Unread_13, false)
    Set(AF_MAC01_ToggleDialogue_MinhT, false)
    Set(AF_MAC01_Unread_15, false)
    IfLt(GB_StoryProgress, STORY_EPILOGUE)
        Exec(EVS_SetupBadgeShop)
    Else
        Call(EnableGroup, MODEL_jutan1, false)
    EndIf
    Switch(GB_StoryProgress)
        CaseEq(STORY_INTRO)
            Call(MakeNpcs, false, IntroNPCs)
        CaseGe(STORY_EPILOGUE)
            Call(MakeNpcs, false, EpilogueNPCs)
        CaseLt(STORY_CH1_MERLON_REVEALED_KOOPA_BROS)
            Call(MakeNpcs, false, Chapter0NPCs)
        CaseLt(STORY_CH1_STAR_SPIRIT_DEPARTED)
            Call(MakeNpcs, false, Chapter1NPCs)
        CaseEq(STORY_CH1_DEFEATED_JR_TROOPA)
            Call(MakeNpcs, false, TwinkMeetingNPCs)
        CaseRange(STORY_CH3_STAR_SPIRIT_DEPARTED, STORY_CH4_STAR_SPIRIT_RESCUED)
            Call(MakeNpcs, false, Chapter4NPCs)
        CaseEq(STORY_CH6_RETURNED_TO_TOAD_TOWN)
            Call(MakeNpcs, false, NinjiMeetingNPCs)
        CaseDefault
            Call(MakeNpcs, false, DefaultNPCs)
    EndSwitch
    IfGe(GB_StoryProgress, STORY_CH1_MERLON_REVEALED_KOOPA_BROS)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_tt, COLLIDER_FLAGS_UPPER_MASK)
    EndIf
    Exec(EVS_SetupFlowerModels)
    Exec(EVS_MakeEntities)
    Exec(EVS_SetupRooms)
    Exec(EVS_SetupBulletinBoard)
    Exec(EVS_SetupCrystalBallGfx)
    Exec(EVS_SetupMusic)
    Call(UseDoorSounds, DOOR_SOUNDS_LARGE)
    Call(UseRoomDoorSounds, DOOR_SOUNDS_BASIC)
    Exec(EVS_EnterMap)
    Wait(1)
    // merlon light shafts
    Call(SetTexPanner, MODEL_hikari, TEX_PANNER_3)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_3)
        TEX_PAN_PARAMS_STEP(-100,    0, -200, -200)
        TEX_PAN_PARAMS_FREQ(   1,    0,    1,    1)
        TEX_PAN_PARAMS_INIT(   0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    BindTrigger(EVS_Merlon_GiveHint, TRIGGER_WALL_PRESS_A, COLLIDER_o335, 1, 0)
    Exec(EVS_SetupQuickChangeTrigger)
    Exec(EVS_SetupFoliage)
    Call(SetCamSpeed, CAM_DEFAULT, 2.0)
    Return
    End
};
