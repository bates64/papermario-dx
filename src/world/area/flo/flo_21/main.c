#include "flo_21.h"
#include "sprite/player.h"

#include "world/common/prefab/StarSpiritCard.inc.c"

EvtScript N(EVS_TrySpawningStarCard) = {
    Switch(GB_StoryProgress)
        CaseEq(STORY_CH6_GREW_MAGIC_BEANSTALK)
            Set(LVar0, false)
            IfEq(MV_BossDefeated, false)
                Return
            EndIf
            Set(GB_StoryProgress, STORY_CH6_DEFEATED_HUFF_N_PUFF)
        CaseEq(STORY_CH6_DEFEATED_HUFF_N_PUFF)
            Set(LVar0, true)
        CaseDefault
            Return
    EndSwitch
    IfEq(LVar0, false)
        Call(DisablePlayerInput, true)
        Call(UseSettingsFrom, CAM_DEFAULT, 650, 205, 0)
        Call(SetCamSpeed, CAM_DEFAULT, Float(0.6))
        Call(SetPanTarget, CAM_DEFAULT, 650, 150, 0)
        EVT_SPIRIT_ADJUST_CAM(Float(-5.5))
        Call(PanToTarget, CAM_DEFAULT, 0, true)
        Call(N(InitSpiritCardSpawn), MV_SpiritCardData, 5, 180, 650, 170, 0, 650, 205, 0, 150, 120)
        Thread
            Call(N(UpdateSpiritCardSpawn))
        EndThread
        Thread
            Wait(1)
            Call(PlaySound, SOUND_LOOP_STAR_ORB_RISING)
            Call(N(AwaitSpiritOrbBurst))
            Call(StopSound, SOUND_LOOP_STAR_ORB_RISING)
            Call(PlaySoundAt, SOUND_STAR_ORB_BURST, SOUND_SPACE_DEFAULT, 650, 205, 0)
        EndThread
        Thread
            Wait(45)
            Call(SetPlayerAnimation, ANIM_Mario1_LookUp)
        EndThread
        Thread
            Wait(180)
            Wait(115)
            Call(PlaySoundAt, SOUND_STAR_CARD_APPEARS, SOUND_SPACE_DEFAULT, 650, 205, 0)
        EndThread
        Call(N(AwaitSpiritCardProgress), SPIRIT_CARD_NOTIFY_FALLING)
        Thread
            Wait(80)
            Call(SetPlayerAnimation, ANIM_Mario1_Idle)
        EndThread
        Add(LVar1, 100)
        Call(SetCamDistance, CAM_DEFAULT, LVar1)
        Call(SetPanTarget, CAM_DEFAULT, 650, 120, 0)
        Call(N(AwaitSpiritCardProgress), SPIRIT_CARD_NOTIFY_DONE_FALLING)
        Call(GetPlayerPos, LVar2, LVar3, LVar4)
        Call(UseSettingsFrom, CAM_DEFAULT, LVar2, LVar3, LVar4)
        Call(SetCamSpeed, CAM_DEFAULT, Float(1.0))
        Call(SetPanTarget, CAM_DEFAULT, LVar2, LVar3, LVar4)
        Call(WaitForCam, CAM_DEFAULT, Float(1.0))
        Call(PanToTarget, CAM_DEFAULT, 0, false)
        Call(DisablePlayerInput, false)
    Else
        Call(N(SpawnExistingSpiritCard), 5, 650, 150, 0, 120)
        Thread
            Call(N(UpdateExistingSpiritCard))
        EndThread
        Wait(1)
    EndIf
    Call(N(AwaitSpiritCardProgress), SPIRIT_CARD_NOTIFY_PLAYER_TOUCH)
    Call(PlaySoundAtPlayer, SOUND_RESCUE_STAR_SPIRIT, SOUND_SPACE_DEFAULT)
    Call(DisablePlayerInput, true)
    Set(GB_StoryProgress, STORY_CH6_STAR_SPIRIT_RESCUED)
    Call(GotoMapSpecial, Ref("kmr_23"), kmr_23_ENTRY_5, TRANSITION_GET_STAR_CARD)
    Wait(100)
    Return
    End
};

EvtScript N(EVS_ExitWalk_flo_19_1) = EVT_EXIT_WALK(60, flo_21_ENTRY_0, "flo_19", flo_19_ENTRY_1);

EvtScript N(EVS_BindExitTriggers) = {
    BindTrigger(Ref(N(EVS_ExitWalk_flo_19_1)), TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    Return
    End
};

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_CLOUDY_CLIMB)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, false, Ref(N(DefaultNPCs)))
    Exec(N(EVS_Scene_HuffNPuffAmbush))
    Call(HidePlayerShadow, true)
    Exec(N(EVS_SetupCloudPuffs))
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o114, SURFACE_TYPE_CLOUD)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o115, SURFACE_TYPE_CLOUD)
    Call(GetEntryID, LVar0)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitw, COLLIDER_FLAGS_UPPER_MASK)
    Set(LVar0, Ref(N(EVS_BindExitTriggers)))
    Exec(EnterWalk)
    ExecWait(N(EVS_SetupMusic))
    IfGe(GB_StoryProgress, STORY_CH6_DESTROYED_PUFF_PUFF_MACHINE)
        Call(SpawnSunEffect, FX_SUN_FROM_RIGHT)
    EndIf
    Exec(N(EVS_TrySpawningStarCard))
    Return
    End
};
