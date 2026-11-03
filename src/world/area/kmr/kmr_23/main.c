#include "kmr_23.h"
#include "world/area/kmr/kmr_24.h"
#include "world/area/kzn/kzn_19.h"
#include "sprite/player.h"

API_CALLABLE(DrawBackCurtains) {
    set_curtain_scale_goal(2.0f);
    set_curtain_draw_callback(nullptr);
    return ApiStatus_DONE2;
}

EvtScript EVS_GotoNextAfterSceneEnd = {
    Set(MF_EndChapterSceneDone, false)
    Loop(0)
        IfNe(MF_EndChapterSceneDone, false)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Call(GetEntryID, LVar0)
    IfNe(LVar0, $Misstar.index)
        Call(GotoMapSpecial, $kmr_24.Entry0, TRANSITION_BEGIN_OR_END_CHAPTER)
    Else
        Call(GotoMapSpecial, $kzn_19.Entry3, TRANSITION_END_CHAPTER_INTERRUPTED)
    EndIf
    Call(FadeOutMusic, 0, 2000)
    Call(DrawBackCurtains)
    Wait(100)
    Return
    End
};

EvtScript EVS_Main = {
    Call(DisablePlayerInput, true)
    Call(DisablePlayerPhysics, true)
    Call(SetPlayerPos, -2, 0, 0)
    Call(SetPlayerFlagBits, PS_FLAG_NO_FLIPPING, true)
    Call(InterpPlayerYaw, 90, 0)
    Wait(1)
    Call(SetPlayerAnimation, ANIM_Mario1_GetItem)
    Call(GetCurrentPartnerID, LVar0)
    IfNe(LVar0, PARTNER_NONE)
        Call(DisablePartnerAI, false)
        Call(SetNpcFlagBits, NPC_PARTNER, NPC_FLAG_GRAVITY, false)
        Call(SetNpcPos, NPC_PARTNER, NPC_DISPOSE_LOCATION)
    EndIf
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(SetCamType, CAM_DEFAULT, CAM_CONTROL_FIXED_POS_AND_ORIENTATION, false)
    Call(SetCamPitch, CAM_DEFAULT, 0, 0)
    Call(SetCamDistance, CAM_DEFAULT, 440)
    Call(SetCamPosA, CAM_DEFAULT, 0, 100)
    Call(SetCamPosB, CAM_DEFAULT, 0, 0)
    Call(SetCamPosC, CAM_DEFAULT, 0, 65)
    Call(SetPanTarget, CAM_DEFAULT, 0, 0, 0)
    Call(SetCamSpeed, CAM_DEFAULT, 90.0)
    Call(PanToTarget, CAM_DEFAULT, 0, true)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($Eldstar.index)
            Call(MakeNpcs, false, NpcGroup_Eldstar)
        CaseEq($Mamar.index)
            Call(MakeNpcs, false, NpcGroup_Mamar)
        CaseEq($Skolar.index)
            Call(MakeNpcs, false, NpcGroup_Skolar)
        CaseEq($Muskular.index)
            Call(MakeNpcs, false, NpcGroup_Muskular)
        CaseEq($Misstar.index)
            Call(MakeNpcs, false, NpcGroup_Misstar)
        CaseEq($Klevar.index)
            Call(MakeNpcs, false, NpcGroup_Klevar)
        CaseEq($Kalmar.index)
            Call(MakeNpcs, false, NpcGroup_Kalmar)
    EndSwitch
    Call(DisablePlayerInput, true)
    Call(DisablePlayerPhysics, true)
    Wait(1)
    Exec(EVS_GotoNextAfterSceneEnd)
    Thread
        Call(FadeOutMusic, 0, 150)
        Call(ClearAmbientSounds, 150)
        Wait(10)
        Call(SetMusic, 0, SONG_CHAPTER_END, 0, VOL_LEVEL_FULL)
    EndThread
    Wait(20)
    Return
    End
};
