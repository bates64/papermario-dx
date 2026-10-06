#include "hos_04.h"
#include "nu/nusys.h"

#include "world/common/npc/StarSpirit/idle.inc.c"
#include "world/common/npc/Twink/idle.inc.c"

Vec3f TwinkFlightPath[] = {
    { -669.0,    98.0,  -34.0 },
    { -669.0,    68.0,  -34.0 },
    { -644.0,    14.0,  -23.0 },
    { -564.0,     8.0,   40.0 },
    { -324.0,   136.0,  175.0 },
    {  -38.0,   118.0,    0.0 },
    {  205.0,   111.0,    0.0 },
    {  305.0,   101.0,    0.0 },
};

CameraControlSettings CamSettings_PreHeist = {
    .type = CAM_CONTROL_FIXED_ORIENTATION,
    .boomLength = 700,
    .boomPitch = -0.9,
    .points = { .two = { 0.0, -1.0, 0.0, 500.0, -1.0, 0.0 }},
    .viewPitch = -17.4,
    .flag = false,
};

CameraControlSettings CamSettings_PostHeist = {
    .type = CAM_CONTROL_FIXED_ORIENTATION,
    .boomLength = 665,
    .boomPitch = -0.9,
    .points = { .two = { 0.0, -1.0, 0.0, 500.0, -1.0, 0.0 }},
    .viewPitch = -17.4,
    .flag = false,
};

API_CALLABLE(SetCamVfov) {
    Bytecode* args = script->ptrReadPos;
    s32 cameraID = evt_get_variable(script, *args++);

    gCameras[cameraID].vfov = evt_get_float_variable(script, *args++);
    return ApiStatus_DONE2;
}

API_CALLABLE(ResumeIntroState) {
    if (gGameStatusPtr->introPart > INTRO_PART_NONE && gGameStatusPtr->introPart < INTRO_PART_5) {
        gGameStatusPtr->introPart++;
        state_init_intro();
    }
    return ApiStatus_DONE1;
}

API_CALLABLE(BlockForever) {
    return ApiStatus_BLOCK;
}

#include "../common/IntroMathUtil.inc.c"

f32 TargetBoomLengthPre = 700;
u16* ColorBufferPtr = nullptr;

API_CALLABLE(AnimateBoomLengthPreHeist) {
    Camera* camera = &gCameras[gCurrentCameraID];

    if (nuGfxCfb_ptr == ColorBufferPtr) {
        return ApiStatus_BLOCK;
    }

    ColorBufferPtr = nuGfxCfb_ptr;
    lerp_value_with_max_step(700.0f, 300.0f, TargetBoomLengthPre, 1.2f, &TargetBoomLengthPre);
    camera->panActive = true;
    camera->overrideSettings.boomLength = TargetBoomLengthPre;
    return ApiStatus_BLOCK;
}

s32 TargetBoomLengthPost = 0;
BSS f32 CurrentBoomLengthPost;

API_CALLABLE(AnimateBoomLengthPostHeist) {
    Camera* camera = &gCameras[gCurrentCameraID];

    if (isInitialCall) {
        CurrentBoomLengthPost = CamSettings_PostHeist.boomLength;
    }
    interp_value_with_easing(INTRO_MATH_EASING_SIN_OUT, CamSettings_PostHeist.boomLength, 700.0f,
        TargetBoomLengthPost, 70.0f, &CurrentBoomLengthPost);
    camera->panActive = true;
    camera->overrideSettings.boomLength = CurrentBoomLengthPost;
    TargetBoomLengthPost++;
    if (TargetBoomLengthPost < (s32)(70 * DT)) {
        return ApiStatus_BLOCK;
    }
    return ApiStatus_DONE1;
}

s32 TargetViewPitch = 0;
BSS f32 CurrentViewPitch;

API_CALLABLE(AnimateViewPitchPostHeist) {
    Camera* camera = &gCameras[gCurrentCameraID];

    if (isInitialCall) {
        CurrentViewPitch = CamSettings_PostHeist.viewPitch;
    }
    interp_value_with_easing(INTRO_MATH_EASING_5, CamSettings_PostHeist.viewPitch, -80.0f,
        TargetViewPitch, 200.0f, &CurrentViewPitch);
    camera->panActive = true;
    camera->overrideSettings.viewPitch = CurrentViewPitch;
    TargetViewPitch++;
    if (TargetViewPitch == (s32)(200 * DT)) {
        return ApiStatus_DONE2;
    }
    return ApiStatus_BLOCK;
}

EvtScript EVS_ControlTwink = {
    Call(SetNpcAnimation, NPC_Twink, ANIM_Twink_Back)
    Call(SetNpcYaw, NPC_Twink, 180)
    Call(AnimateBoomLengthPostHeist)
#if VERSION_JP
    Wait(30 * DT)
#else
    Wait(15 * DT)
#endif
    Thread
        Wait(10 * DT)
        Call(InterpNpcYaw, NPC_Twink, 0, 0)
        Wait(2)
        Call(SetNpcAnimation, NPC_Twink, ANIM_Twink_Still)
        Wait(20 * DT)
        Call(InterpNpcYaw, NPC_Twink, 180, 0)
        Wait(2)
        Call(SetNpcAnimation, NPC_Twink, ANIM_Twink_Back)
    EndThread
    Thread
        Wait(100 * DT)
        Call(AnimateViewPitchPostHeist)
    EndThread
    Call(LoadPath, 200 * DT, Ref(TwinkFlightPath), ARRAY_COUNT(TwinkFlightPath), EASING_LINEAR)
    Label(0)
    Call(GetNextPathPos)
    Call(SetNpcPos, NPC_Twink, LVar1, LVar2, LVar3)
    Wait(1)
    IfEq(LVar0, 1)
        Goto(0)
    EndIf
    Call(SetNpcPos, NPC_Twink, NPC_DISPOSE_LOCATION)
    Thread
        Wait(85 * DT)
        Call(BlockForever)
    EndThread
    Wait(120 * DT)
    Call(ResumeIntroState)
    Return
    End
};

EvtScript EVS_Intro_PostHeist = {
    Call(DisablePlayerInput, true)
    Call(DisablePlayerPhysics, true)
    Call(SetCamLeadPlayer, CAM_DEFAULT, false)
    Call(SetCamVfov, CAM_DEFAULT, 75)
    Call(SetPanTarget, CAM_DEFAULT, 0, 30, 0)
    Call(LoadSettings, CAM_DEFAULT, Ref(CamSettings_PostHeist))
    Call(PanToTarget, CAM_DEFAULT, 0, true)
    Call(SetCamSpeed, CAM_DEFAULT, Float(90.0))
    Thread
        Exec(EVS_ControlTwink)
    EndThread
    Return
    End
};

// establishing shot of the star shrine; camera slowly moves along the path toward it
EvtScript EVS_Intro_PreHeist_Unused = {
    Call(DisablePlayerInput, true)
    Call(DisablePlayerPhysics, true)
    Call(SetCamLeadPlayer, CAM_DEFAULT, false)
    Call(SetCamVfov, CAM_DEFAULT, 75)
    Call(SetPanTarget, CAM_DEFAULT, 0, 30, 0)
    Call(LoadSettings, CAM_DEFAULT, Ref(CamSettings_PreHeist))
    Call(PanToTarget, CAM_DEFAULT, 0, true)
    Call(SetCamSpeed, CAM_DEFAULT, Float(90.0))
    Thread
        Call(AnimateBoomLengthPreHeist)
    EndThread
    Thread
        Wait(300)
        Call(ResumeIntroState)
    EndThread
    Return
    End
};

EvtScript EVS_NpcInit_Twink = {
    Return
    End
};

NpcData NpcData_Twink = {
    .id = NPC_Twink,
    .pos = { NPC_DISPOSE_LOCATION },
    .yaw = 270,
    .init = &EVS_NpcInit_Twink,
    .settings = &NpcSettings_Twink,
    .flags = ENEMY_FLAG_PASSIVE | ENEMY_FLAG_FLYING,
    .drops = NO_DROPS,
    .animations = TWINK_ANIMS,
};

NpcGroupList DefaultNPCs = {
    NPC_GROUP(NpcData_Twink),
    {}
};
