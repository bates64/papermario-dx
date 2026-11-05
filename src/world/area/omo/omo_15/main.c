#include "omo_15.h"
#include "world/area/kmr/kmr_23.h"
#include "world/area/omo/omo_14.h"
#include "sprite/player.h"

#include "world/common/prefab/StarSpiritCard.inc.c"

EvtScript EVS_TrySpawningStarCard = {
    // determine if card should be spawned
    Switch(GB_StoryProgress)
        CaseEq(STORY_CH4_OPENED_GENERAL_GUY_ROOM)
            Set(LVar0, false)
            Set(GB_StoryProgress, STORY_CH4_DEFEATED_GENERAL_GUY)
        CaseEq(STORY_CH4_DEFEATED_GENERAL_GUY)
            Set(LVar0, true)
        CaseDefault
            Return
    EndSwitch
    IfEq(LVar0, false)
        // card appearing scene
        Call(DisablePlayerInput, true)
        Call(UseSettingsFrom, CAM_DEFAULT, -100, 85, 0)
        Call(SetCamSpeed, CAM_DEFAULT, 0.5)
        Call(SetPanTarget, CAM_DEFAULT, -100, 30, 0)
        EVT_SPIRIT_ADJUST_CAM(10000)
        Call(PanToTarget, CAM_DEFAULT, 0, true)
        Call(InitSpiritCardSpawn, MV_SpiritCardData, 3, 180, 215, 60, 0, -100, 85, 0, 30, 0)
        Thread
            Call(UpdateSpiritCardSpawn)
        EndThread
        Thread
            Wait(1)
            Call(PlaySound, SOUND_LOOP_STAR_ORB_RISING)
            Call(AwaitSpiritOrbBurst)
            Call(StopSound, SOUND_LOOP_STAR_ORB_RISING)
            Call(PlaySoundAt, SOUND_STAR_ORB_BURST, SOUND_SPACE_DEFAULT, -100, 85, 0)
        EndThread
        Thread
            Wait(45)
            Call(SetPlayerAnimation, ANIM_Mario1_LookUp)
        EndThread
        Thread
            Wait(180)
            Wait(115)
            Call(PlaySoundAt, SOUND_STAR_CARD_APPEARS, SOUND_SPACE_DEFAULT, -100, 85, 0)
        EndThread
        Call(AwaitSpiritCardProgress, SPIRIT_CARD_NOTIFY_FALLING)
        Thread
            Wait(80)
            Call(SetPlayerAnimation, ANIM_Mario1_Idle)
        EndThread
        Add(LVar1, 100)
        Call(SetCamDistance, CAM_DEFAULT, LVar1)
        Call(SetPanTarget, CAM_DEFAULT, -100, 0, 0)
        Call(AwaitSpiritCardProgress, SPIRIT_CARD_NOTIFY_DONE_FALLING)
        Call(GetPlayerPos, LVar2, LVar3, LVar4)
        Call(UseSettingsFrom, CAM_DEFAULT, LVar2, LVar3, LVar4)
        Call(SetCamSpeed, CAM_DEFAULT, 4.0)
        Call(SetPanTarget, CAM_DEFAULT, LVar2, LVar3, LVar4)
        Call(WaitForCam, CAM_DEFAULT, 1.0)
        Call(PanToTarget, CAM_DEFAULT, 0, false)
        Call(DisablePlayerInput, false)
    Else
        // just make the card spawn
        Call(SpawnExistingSpiritCard, 3, -100, 30, 0, 0)
        Thread
            Call(UpdateExistingSpiritCard)
        EndThread
        Wait(1)
    EndIf
    // wait for pickup
    Call(AwaitSpiritCardProgress, SPIRIT_CARD_NOTIFY_PLAYER_TOUCH)
    Call(PlaySoundAtPlayer, SOUND_RESCUE_STAR_SPIRIT, SOUND_SPACE_DEFAULT)
    Call(DisablePlayerInput, true)
    Set(GB_StoryProgress, STORY_CH4_STAR_SPIRIT_RESCUED)
    Call(GotoMapSpecial, $kmr_23.Muskular, TRANSITION_GET_STAR_CARD)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitWalk_omo_14_1 = EVT_EXIT_WALK(60, $Omo14, $omo_14.Omo15);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_omo_14_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Call(MakeNpcs, true, DefaultNPCs)
    ExecWait(EVS_SetupMusic)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    IfEq(GB_StoryProgress, STORY_CH4_DEFEATED_GENERAL_GUY)
        Exec(EVS_TrySpawningStarCard)
    EndIf
    Return
    End
};
