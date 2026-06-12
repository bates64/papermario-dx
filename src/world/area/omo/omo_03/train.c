#include "omo_03.h"

#define TRAIN_STATION_ID  OMO_STATION_BLUE
#define TRAIN_ROUTE_LEFT  TRAIN_ROUTE_RED_BLUE
#define TRAIN_ROUTE_RIGHT TRAIN_ROUTE_BLUE_PINK
#define TRAIN_COLLIDER COLLIDER_o898
#define TRAIN_ARRIVAL_MESSAGE MSG_CH4_000E
#define TRAIN_LEFT_THRESHOLD -350
#define TRAIN_RIGHT_THRESHOLD 350
#define TRAIN_LEFT_ENTRY omo_03_ENTRY_2
#define TRAIN_RIGHT_ENTRY omo_03_ENTRY_3

#include "../common/ToyTrain.inc.c"
#include "../common/TrainStationSwitches.inc.c"

EvtScript N(EVS_TrainUnk_AltD) = {
    Call(SetNpcFlagBits, NPC_Conductor, NPC_FLAG_IGNORE_WORLD_COLLISION | NPC_FLAG_IGNORE_PLAYER_COLLISION, true)
    Call(SetNpcFlagBits, NPC_PARTNER, NPC_FLAG_IGNORE_WORLD_COLLISION | NPC_FLAG_IGNORE_PLAYER_COLLISION, true)
    Set(AF_OMO_06, false)
    Call(GetPlayerPos, LVar1, LVar2, LVar3)
    IfLt(LVar2, 50)
        UseBuf(LVar9)
        BufRead4(LVar3, LVar4, LVar5, LVar6)
        Call(SetPlayerSpeed, Float(2.5))
        Call(PlayerMoveTo, LVar3, LVar4, 0)
        Call(SetPlayerJumpscale, Float(1.0))
        Call(PlayerJump, LVar5, 50, LVar6, 15)
    EndIf
    Thread
        UseBuf(LVar0)
        BufRead3(LVar1, LVar2, LVar3)
        Call(AddVectorPolar, LVar1, LVar2, Float(15.0), LVar3)
        Call(SetPlayerAnimation, ANIM_Mario1_Walk)
        Call(SetPlayerSpeed, Float(4.0))
        Call(PlayerMoveTo, LVar1, LVar2, 0)
        Call(SetPlayerSpeed, Float(0.7))
        Call(PlayerMoveTo, LVar1, LVar2, 0)
        Call(SetPlayerPos, LVar1, 50, LVar2)
        Call(SetPlayerAnimation, ANIM_Mario1_Idle)
        Call(InterpPlayerYaw, LVar3, 0)
    EndThread
    Wait(5)
    UseBuf(LVar0)
    BufRead3(LVar1, LVar2, LVar3)
    SetF(LVarA, LVar3)
    AddF(LVar3, Float(180.0))
    Call(AddVectorPolar, LVar1, LVar2, Float(15.0), LVar3)
    Call(SetNpcJumpscale, NPC_PARTNER, Float(0.7))
    Call(NpcJump0, NPC_PARTNER, LVar1, 50, LVar2, 10)
    Call(SetNpcSpeed, NPC_PARTNER, Float(0.1))
    Call(NpcMoveTo, NPC_PARTNER, LVar1, LVar2, 0)
    Call(SetNpcAnimation, NPC_PARTNER, PARTNER_ANIM_IDLE)
    Call(InterpNpcYaw, NPC_PARTNER, LVarA, 0)
    Wait(5)
    UseBuf(LVar0)
    BufRead3(LVar1, LVar2, LVar3)
    SetF(LVarA, LVar3)
    AddF(LVar3, Float(90.0))
    SetF(LVar4, LVar1)
    SetF(LVar5, LVar2)
    SetF(LVar6, LVar3)
    Call(AddVectorPolar, LVar1, LVar2, Float(60.0), LVar3)
    Call(SetNpcSpeed, NPC_Conductor, Float(3.0))
    Call(SetNpcAnimation, NPC_Conductor, ANIM_TrainToad_Walk)
    Call(NpcMoveTo, NPC_Conductor, LVar1, LVar2, 0)
    Call(SetNpcAnimation, NPC_Conductor, ANIM_TrainToad_Idle)
    Call(AddVectorPolar, LVar4, LVar5, Float(20.0), LVar6)
    Call(SetNpcJumpscale, NPC_Conductor, Float(0.7))
    Call(NpcJump0, NPC_Conductor, LVar4, 50, LVar5, 10)
    Call(InterpNpcYaw, NPC_Conductor, LVarA, 0)
    Call(SpeakToPlayer, NPC_Conductor, ANIM_TrainToad_Talk, ANIM_TrainToad_Idle, 5, MSG_CH4_0009)
    Call(PlaySound, SOUND_LRAW_TOYBOX_TRAIN_GEAR)
    Call(SetMusic, 0, SONG_TOYBOX_TRAIN, 0, VOL_LEVEL_FULL)
    Wait(10)
    Return
    End
};

EvtScript N(EVS_TrainUnk_AltE) = {
    Call(StopSound, SOUND_LRAW_TOYBOX_TRAIN_GEAR)
    Call(SetMusic, 0, SONG_SHY_GUY_TOYBOX, 0, VOL_LEVEL_FULL)
    Call(SetNpcFlagBits, NPC_Conductor, NPC_FLAG_IGNORE_WORLD_COLLISION | NPC_FLAG_IGNORE_PLAYER_COLLISION, true)
    Call(SetNpcFlagBits, NPC_PARTNER, NPC_FLAG_IGNORE_WORLD_COLLISION | NPC_FLAG_IGNORE_PLAYER_COLLISION, true)
    Set(AF_OMO_06, true)
    SetF(LVar0, MV_TrainPosX)
    SetF(LVar1, MV_TrainPosZ)
    SetF(LVar2, MV_TrainYaw)
    Thread
        Call(SetNpcAnimation, NPC_Conductor, ANIM_TrainToad_Walk)
        Call(SetNpcSpeed, NPC_Conductor, Float(3.5))
        UseBuf(LVar9)
        BufRead2(LVar3, LVar4)
        Call(NpcMoveTo, NPC_Conductor, LVar3, LVar4, 0)
        Call(SetNpcAnimation, NPC_Conductor, ANIM_TrainToad_SadIdle)
        Call(InterpNpcYaw, NPC_Conductor, 90, 0)
        Call(SetNpcFlagBits, NPC_Conductor, NPC_FLAG_IGNORE_WORLD_COLLISION | NPC_FLAG_IGNORE_PLAYER_COLLISION, false)
    EndThread
    Wait(10)
    Thread
        AddF(LVar2, Float(85.0))
        Call(AddVectorPolar, LVar0, LVar1, Float(80.0), LVar2)
        Call(SetPlayerAnimation, ANIM_Mario1_Walk)
        Call(SetPlayerSpeed, Float(3.0))
        Call(PlayerMoveTo, LVar0, LVar1, 0)
        Call(SetPlayerAnimation, ANIM_Mario1_Idle)
    EndThread
    Wait(10)
    AddF(LVar2, Float(50.0))
    Call(AddVectorPolar, LVar0, LVar1, Float(85.0), LVar2)
    Call(SetNpcAnimation, NPC_PARTNER, PARTNER_ANIM_WALK)
    Call(SetNpcSpeed, NPC_PARTNER, Float(2.5))
    Call(NpcMoveTo, NPC_PARTNER, LVar0, LVar1, 0)
    Call(SetNpcAnimation, NPC_PARTNER, PARTNER_ANIM_IDLE)
    Call(SetNpcFlagBits, NPC_PARTNER, NPC_FLAG_IGNORE_WORLD_COLLISION | NPC_FLAG_IGNORE_PLAYER_COLLISION, false)
    Return
    End
};

Vec2i N(D_80246080_DAB2C0) = {
    170, -115
};

Vec2i N(D_80246088_DAB2C8) = {
    -383, -240
};

Vec2i N(D_80246090_DAB2D0)[] = {
    { -360, -195 },
    { -335, -215 },
};

s32 N(TrainPath_802460A0_DAB2E0)[] = {
    Float(-298.93), Float(-288.62), Float(140.0),
    Float(-262.5), Float(-245.336), Float(0.0),
    Float(-175.0), Float(169.89), Float(-220.49),
    -1, -1, -1
};

s32 N(TrainPath_802460D0_DAB310)[] = {
    Float(-298.93), Float(-288.62), Float(140.0),
    Float(-262.5), Float(-245.336), Float(0.0),
    Float(-175.0), Float(262.5), Float(-245.336),
    Float(479.165), Float(-503.546),
    -1, -1, -1
};

EvtScript N(EVS_80246108) = {
    IfEq(GF_OMO03_BlueSwitchActivated, false)
        Call(DisablePlayerInput, true)
        Call(SpeakToPlayer, NPC_Conductor, ANIM_TrainToad_SadTalk, ANIM_TrainToad_SadIdle, 0, MSG_CH4_0014)
        Call(DisablePlayerInput, false)
        Return
    Else
        Call(DisablePlayerInput, true)
        Call(DisablePlayerPhysics, true)
        Call(DisablePartnerAI, 0)
        Thread
            Call(SetNpcFlagBits, NPC_Conductor, NPC_FLAG_IGNORE_PLAYER_COLLISION, true)
            Call(SetNpcJumpscale, NPC_Conductor, Float(1.0))
            Call(GetNpcPos, NPC_Conductor, LVar0, LVar1, LVar2)
            Loop(2)
                Call(NpcJump1, NPC_Conductor, LVar0, LVar1, LVar2, 15)
            EndLoop
            Call(SetNpcFlagBits, NPC_Conductor, NPC_FLAG_IGNORE_PLAYER_COLLISION, false)
        EndThread
        Call(SpeakToPlayer, NPC_Conductor, ANIM_TrainToad_Talk, ANIM_TrainToad_Idle, 0, MSG_CH4_0015)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o939, COLLIDER_FLAGS_UPPER_MASK)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o941, COLLIDER_FLAGS_UPPER_MASK)
        ExecGetTID(N(EVS_TrainUnk_C), LVarB)
        Set(LVar0, Ref(N(TrainPath_802460A0_DAB2E0)))
        Set(LVar9, Ref(N(D_80246090_DAB2D0)))
        ExecWait(N(EVS_TrainUnk_AltD))
        IfEq(AB_OMO_6, TRAIN_STATION_ID)
            Set(MV_TrainRideState, TRAIN_STATE_0)
            Set(MV_TrainPath, Ref(N(TrainPath_802460A0_DAB2E0)))
            Set(MV_TrainSpeedMode, TRAIN_SPEED_PARTIAL_PATH)
            Set(MF_TrainRideActive, true)
            Label(20)
                IfEq(MF_TrainRideActive, true)
                    Wait(1)
                    Goto(20)
                EndIf
            Wait(20)
            KillThread(LVarB)
            Exec(N(EVS_TrainUnk_B))
            Call(EnableCameraFollowPlayerY)
            Set(LVar9, Ref(N(D_80246080_DAB2C0)))
            ExecWait(N(EVS_TrainUnk_E))
            Call(SpeakToPlayer, NPC_Conductor, ANIM_TrainToad_Talk, ANIM_TrainToad_Idle, 0, MSG_CH4_000E)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_CLEAR_BITS, COLLIDER_o939, COLLIDER_FLAGS_UPPER_MASK)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_CLEAR_BITS, COLLIDER_o941, COLLIDER_FLAGS_UPPER_MASK)
            Call(DisablePlayerPhysics, false)
            Call(EnablePartnerAI)
            Call(DisablePlayerInput, false)
        Else
            Set(MV_TrainRideState, TRAIN_STATE_0)
            Set(MV_TrainPath, Ref(N(TrainPath_802460D0_DAB310)))
            Set(MV_TrainSpeedMode, TRAIN_SPEED_ACCELERATE)
            Set(MF_TrainRideActive, true)
            Wait(1)
            Exec(N(EVS_TrainUnk_H))
            Label(30)
            IfLt(MV_TrainPosX, TRAIN_RIGHT_THRESHOLD)
                Wait(1)
                Goto(30)
            EndIf
            Call(GotoMap, Ref("omo_16"), omo_16_ENTRY_0)
            Set(GB_OMO_TrainRoute, TRAIN_ROUTE_RIGHT)
            Wait(100)
        EndIf
    EndIf
    Unbind
    Return
    End
};

s32 N(TrainPath_DepartRight)[] = {
    Float(131.251), Float(-210.168), Float(74.997),
    Float(262.5), Float(-245.336), Float(479.165),
    Float(-503.546),
    -1, -1, -1
};

EvtScript N(EVS_Train_DepartRight) = {
    Call(FadeOutMusic, 0, 3000)
    Call(DisablePlayerInput, true)
    Call(DisablePartnerAI, 0)
    Call(SetNpcAnimation, NPC_PARTNER, PARTNER_ANIM_IDLE)
    Wait(10)
    Call(DisablePlayerPhysics, true)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o939, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o941, COLLIDER_FLAGS_UPPER_MASK)
    Exec(N(EVS_TrainUnk_C))
    Set(AB_OMO_5, TRAIN_STATION_ID)
    Set(LVar0, Ref(N(TrainPath_DepartRight)))
    ExecWait(N(EVS_TrainUnk_D))
    Set(MV_TrainRideState, TRAIN_STATE_0)
    Set(MV_TrainPath, Ref(N(TrainPath_DepartRight)))
    Set(MV_TrainSpeedMode, TRAIN_SPEED_ACCELERATE)
    Set(MF_TrainRideActive, true)
    Label(10)
        IfLt(MV_TrainPosX, TRAIN_RIGHT_THRESHOLD)
            Wait(1)
            Goto(10)
        EndIf
    Call(GotoMap, Ref("omo_16"), omo_16_ENTRY_0)
    Set(GB_OMO_TrainRoute, TRAIN_ROUTE_RIGHT)
    Wait(100)
    Return
    End
};

s32 N(TrainPath_DepartLeft)[] = {
    Float(131.251), Float(-210.168), Float(254.997),
    Float(0.0), Float(-175.0), Float(-262.5),
    Float(-245.336), Float(-353.418), Float(-353.688),
    Float(-479.165), Float(-503.546),
    -1, -1, -1
};

EvtScript N(EVS_Train_DepartLeft) = {
    Call(FadeOutMusic, 0, 3000)
    Call(DisablePlayerInput, true)
    Call(DisablePartnerAI, 0)
    Call(SetNpcAnimation, NPC_PARTNER, PARTNER_ANIM_IDLE)
    Wait(10)
    Call(DisablePlayerPhysics, true)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o939, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o941, COLLIDER_FLAGS_UPPER_MASK)
    Exec(N(EVS_TrainUnk_C))
    Set(AB_OMO_5, TRAIN_STATION_ID)
    Set(LVar0, Ref(N(TrainPath_DepartLeft)))
    ExecWait(N(EVS_TrainUnk_D))
    Set(MV_TrainRideState, TRAIN_STATE_0)
    Set(MV_TrainPath, Ref(N(TrainPath_DepartLeft)))
    Set(MV_TrainSpeedMode, TRAIN_SPEED_ACCELERATE)
    Set(MF_TrainRideActive, true)
    Label(10)
        IfGt(MV_TrainPosX, TRAIN_LEFT_THRESHOLD)
            Wait(1)
            Goto(10)
        EndIf
    Call(GotoMap, Ref("omo_16"), omo_16_ENTRY_1)
    Set(GB_OMO_TrainRoute, TRAIN_ROUTE_LEFT)
    Wait(100)
    Return
    End
};

s32 N(TrainPath_ArriveRight)[] = {
    Float(414.885), Float(-426.942), Float(219.92),
    Float(353.553), Float(-353.553), Float(262.5),
    Float(-245.336), Float(92.61), Float(-199.49),
    -1, -1, -1
};

s32 N(TrainPath_PassthroughRight)[] = {
    Float(414.885), Float(-426.942), Float(219.92),
    Float(353.553), Float(-353.553), Float(262.5),
    Float(-245.336), Float(0.0), Float(-175.0),
    Float(-262.5), Float(-245.336), Float(-353.418),
    Float(-353.688), Float(-479.165), Float(-503.546),
    -1, -1, -1
};

EvtScript N(EVS_Train_ArriveFromRight) = {
    Call(DisablePlayerInput, true)
    Call(DisablePlayerPhysics, true)
    Call(SetPlayerActionState, ACTION_STATE_LAND)
    Call(DisablePartnerAI, 0)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o939, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o941, COLLIDER_FLAGS_UPPER_MASK)
    IfEq(AB_OMO_6, TRAIN_STATION_ID)
        Set(MV_TrainRideState, TRAIN_STATE_0)
        Set(MV_TrainPath, Ref(N(TrainPath_ArriveRight)))
        Set(MV_TrainSpeedMode, TRAIN_SPEED_DECELERATE)
        Exec(N(EVS_Scene_RideTrain))
        Set(MF_TrainRideActive, true)
        Wait(1)
        ExecGetTID(N(EVS_TrainUnk_A), LVarB)
        Label(10)
        IfEq(MF_TrainRideActive, true)
            Wait(1)
            Goto(10)
        EndIf
        Wait(20)
        KillThread(LVarB)
        Exec(N(EVS_TrainUnk_B))
        Call(EnableCameraFollowPlayerY)
        Set(LVar9, Ref(N(D_80246080_DAB2C0)))
        ExecWait(N(EVS_TrainUnk_E))
        Call(SpeakToPlayer, NPC_Conductor, ANIM_TrainToad_Talk, ANIM_TrainToad_Idle, 0, MSG_CH4_000E)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_CLEAR_BITS, COLLIDER_o939, COLLIDER_FLAGS_UPPER_MASK)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_CLEAR_BITS, COLLIDER_o941, COLLIDER_FLAGS_UPPER_MASK)
        Call(DisablePlayerPhysics, false)
        Call(EnablePartnerAI)
        Call(DisablePlayerInput, false)
    Else
        Exec(N(EVS_TrainUnk_A))
        Set(MV_TrainRideState, TRAIN_STATE_0)
        Set(MV_TrainPath, Ref(N(TrainPath_PassthroughRight)))
        Set(MV_TrainSpeedMode, TRAIN_SPEED_CONSTANT)
        Exec(N(EVS_Scene_RideTrain))
        Set(MF_TrainRideActive, true)
        Wait(1)
        Exec(N(EVS_TrainUnk_H))
        Label(20)
        IfGt(MV_TrainPosX, TRAIN_LEFT_THRESHOLD)
            Wait(1)
            Goto(20)
        EndIf
        Call(GotoMap, Ref("omo_16"), omo_16_ENTRY_1)
        Set(GB_OMO_TrainRoute, TRAIN_ROUTE_LEFT)
        Wait(100)
    EndIf
    Return
    End
};

s32 N(TrainPath_D_80246BE0_DABE20)[] = {
    Float(-414.885), Float(-426.942), Float(140.075),
    Float(-353.418), Float(-353.688), Float(-262.5),
    Float(-245.336), Float(0.0), Float(-175.0),
    Float(169.89), Float(-220.49),
    -1, -1, -1
};

s32 N(TrainPath_D_80246C18_DABE58)[] = {
    Float(-414.885), Float(-426.942), Float(140.075),
    Float(-353.418), Float(-353.688), Float(-273.25),
    Float(-257.95),
    -1, -1, -1
};

s32 N(TrainPath_D_80246C40_DABE80)[] = {
    Float(-414.885), Float(-426.942), Float(140.075),
    Float(-353.418), Float(-353.688), Float(-262.5),
    Float(-245.336), Float(0.0), Float(-175.0),
    Float(262.5), Float(-245.336), Float(479.165),
    Float(-503.546),
    -1, -1, -1
};

EvtScript N(EVS_Train_ArriveFromLeft) = {
    Call(DisablePlayerInput, true)
    Call(DisablePlayerPhysics, true)
    Call(SetPlayerActionState, ACTION_STATE_LAND)
    Call(DisablePartnerAI, 0)
    Call(SetNpcFlagBits, NPC_PARTNER, NPC_FLAG_GRAVITY, false)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o939, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o941, COLLIDER_FLAGS_UPPER_MASK)
    IfEq(GF_OMO03_BlueSwitchActivated, false)
        Set(MV_TrainPath, Ref(N(TrainPath_D_80246C18_DABE58)))
    Else
        IfEq(AB_OMO_6, TRAIN_STATION_ID)
            Set(MV_TrainPath, Ref(N(TrainPath_D_80246BE0_DABE20)))
        Else
            Goto(15) // continue to next station
        EndIf
    EndIf
    Set(MV_TrainRideState, TRAIN_STATE_0)
    Set(MV_TrainSpeedMode, TRAIN_SPEED_DECELERATE)
    Exec(N(EVS_Scene_RideTrain))
    Set(MF_TrainRideActive, true)
    Wait(1)
    ExecGetTID(N(EVS_TrainUnk_A), LVarB)
    Label(10)
        IfEq(MF_TrainRideActive, true)
            Wait(1)
            Goto(10)
        EndIf
    Wait(20)
    KillThread(LVarB)
    Exec(N(EVS_TrainUnk_B))
    Call(EnableCameraFollowPlayerY)
    IfEq(GF_OMO03_BlueSwitchActivated, true)
        Set(LVar9, Ref(N(D_80246080_DAB2C0)))
        ExecWait(N(EVS_TrainUnk_E))
        Call(SpeakToPlayer, NPC_Conductor, ANIM_TrainToad_Talk, ANIM_TrainToad_Idle, 0, MSG_CH4_000E)
    Else
        Set(LVar9, Ref(N(D_80246088_DAB2C8)))
        ExecWait(N(EVS_TrainUnk_AltE))
        Call(SpeakToPlayer, NPC_Conductor, ANIM_TrainToad_SadTalk, ANIM_TrainToad_SadIdle, 0, MSG_CH4_0013)
    EndIf
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_CLEAR_BITS, COLLIDER_o939, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_CLEAR_BITS, COLLIDER_o941, COLLIDER_FLAGS_UPPER_MASK)
    Call(SetNpcFlagBits, NPC_PARTNER, NPC_FLAG_GRAVITY, true)
    Call(DisablePlayerPhysics, false)
    Call(EnablePartnerAI)
    Call(DisablePlayerInput, false)
    Return
    // continue to next station
    Label(15)
    Exec(N(EVS_TrainUnk_A))
    Set(MV_TrainRideState, TRAIN_STATE_0)
    Set(MV_TrainPath, Ref(N(TrainPath_D_80246C40_DABE80)))
    Set(MV_TrainSpeedMode, TRAIN_SPEED_CONSTANT)
    Exec(N(EVS_Scene_RideTrain))
    Set(MF_TrainRideActive, true)
    Wait(1)
    Exec(N(EVS_TrainUnk_H))
    Label(20)
        IfLt(MV_TrainPosX, TRAIN_RIGHT_THRESHOLD)
            Wait(1)
            Goto(20)
        EndIf
    Call(GotoMap, Ref("omo_16"), omo_16_ENTRY_0)
    Set(GB_OMO_TrainRoute, TRAIN_ROUTE_RIGHT)
    Wait(100)
    Return
    End
};

s32 N(LeftStations)[] = {
    OMO_STATION_RED,
    OMO_STATION_GREEN,
    OMO_STATION_PINK,
};

s32 N(RightStations)[] = {
    OMO_STATION_PINK,
    OMO_STATION_GREEN,
    OMO_STATION_RED,
};

EvtScript N(EVS_Conductor_ChooseRoute) = {
    IfEq(MF_EitherSwitchPressed, false)
        Call(SpeakToPlayer, NPC_Conductor, ANIM_TrainToad_Talk, ANIM_TrainToad_Idle, 0, MSG_CH4_0006)
    Else
        IfEq(AF_OMO_UsingRightSwitch, false)
            IfEq(GF_OMO03_BlueSwitchActivated, false)
                Call(SpeakToPlayer, NPC_Conductor, ANIM_TrainToad_SadTalk, ANIM_TrainToad_SadIdle, 5, MSG_CH4_0012)
            Else
                Call(SpeakToPlayer, NPC_Conductor, ANIM_TrainToad_Talk, ANIM_TrainToad_Idle, 0, MSG_CH4_0007)
                Call(ShowChoice, MSG_Choice_003A)
                IfNe(LVar0, 3)
                    Call(CloseMessage)
                    UseBuf(Ref(N(LeftStations)))
                    Add(LVar0, 1)
                    Loop(LVar0)
                        BufRead1(LVar1)
                    EndLoop
                    Set(AB_OMO_6, LVar1)
                    ExecWait(N(EVS_Train_DepartLeft))
                Else
                    Call(ContinueSpeech, NPC_Conductor, ANIM_TrainToad_Talk, ANIM_TrainToad_Idle, 0, MSG_CH4_0008)
                EndIf
            EndIf
        Else
            Call(SpeakToPlayer, NPC_Conductor, ANIM_TrainToad_Talk, ANIM_TrainToad_Idle, 0, MSG_CH4_0007)
            Switch(GB_StoryProgress)
                CaseLt(STORY_CH4_PULLED_SWITCH_SWITCH)
                    Call(ShowChoice, MSG_Choice_0037)
                    IfNe(LVar0, 1)
                        Call(CloseMessage)
                        UseBuf(Ref(N(RightStations)))
                        Add(LVar0, 1)
                        Loop(LVar0)
                            BufRead1(LVar1)
                        EndLoop
                        Set(AB_OMO_6, LVar1)
                        ExecWait(N(EVS_Train_DepartRight))
                    Else
                        Call(ContinueSpeech, NPC_Conductor, ANIM_TrainToad_Talk, ANIM_TrainToad_Idle, 0, MSG_CH4_0008)
                    EndIf
                CaseLt(STORY_CH4_SOLVED_COLOR_PUZZLE)
                    Call(ShowChoice, MSG_Choice_0038)
                    IfNe(LVar0, 2)
                        Call(CloseMessage)
                        UseBuf(Ref(N(RightStations)))
                        Add(LVar0, 1)
                        Loop(LVar0)
                            BufRead1(LVar1)
                        EndLoop
                        Set(AB_OMO_6, LVar1)
                        ExecWait(N(EVS_Train_DepartRight))
                    Else
                        Call(ContinueSpeech, NPC_Conductor, ANIM_TrainToad_Talk, ANIM_TrainToad_Idle, 0, MSG_CH4_0008)
                    EndIf
                CaseGe(STORY_CH4_SOLVED_COLOR_PUZZLE)
                    Call(ShowChoice, MSG_Choice_0039)
                    IfNe(LVar0, 3)
                        Call(CloseMessage)
                        UseBuf(Ref(N(RightStations)))
                        Add(LVar0, 1)
                        Loop(LVar0)
                            BufRead1(LVar1)
                        EndLoop
                        Set(AB_OMO_6, LVar1)
                        ExecWait(N(EVS_Train_DepartRight))
                    Else
                        Call(ContinueSpeech, NPC_Conductor, ANIM_TrainToad_Talk, ANIM_TrainToad_Idle, 0, MSG_CH4_0008)
                    EndIf
            EndSwitch
        EndIf
    EndIf
    Return
    End
};

s32 N(TrainPath_Idle)[] = {
    Float(131.251), Float(-210.168), Float(74.997),
    -1, -1, -1
};

EvtScript N(EVS_SetupTrain) = {
    ExecWait(N(EVS_SetupSwitches))
    Call(EnableGroup, MODEL_po, false)
    IfLt(GB_StoryProgress, STORY_CH4_RETURNED_TOY_TRAIN)
        Call(EnableGroup, MODEL_popo, false)
    Else
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_eki1, COLLIDER_FLAGS_UPPER_MASK)
    EndIf
    Call(GetLoadType, LVar1)
    IfEq(LVar1, LOAD_FROM_FILE_SELECT)
        Set(MV_TrainRideState, TRAIN_STATE_0)
        Set(MV_TrainPath, Ref(N(TrainPath_Idle)))
        Set(MV_TrainSpeedMode, TRAIN_SPEED_CONSTANT)
        Exec(N(EVS_Scene_RideTrain))
        Set(MF_TrainRideActive, true)
    Else
        Call(GetEntryID, LVar0)
        Switch(LVar0)
            CaseEq(TRAIN_LEFT_ENTRY)
                Exec(N(EVS_Train_ArriveFromLeft))
            CaseEq(TRAIN_RIGHT_ENTRY)
                Exec(N(EVS_Train_ArriveFromRight))
            CaseEq(omo_03_ENTRY_6)
                Call(EnableGroup, MODEL_popo, false)
                Call(EnableGroup, MODEL_po, true)
            CaseDefault
                Set(MV_TrainRideState, TRAIN_STATE_0)
                Set(MV_TrainPath, Ref(N(TrainPath_Idle)))
                Set(MV_TrainSpeedMode, TRAIN_SPEED_CONSTANT)
                Exec(N(EVS_Scene_RideTrain))
                Set(MF_TrainRideActive, true)
        EndSwitch
    EndIf
    Return
    End
};

#undef TRAIN_STATION_ID
#undef TRAIN_ROUTE_LEFT
#undef TRAIN_ROUTE_RIGHT
#undef TRAIN_COLLIDER
#undef TRAIN_ARRIVAL_MESSAGE
#undef TRAIN_LEFT_THRESHOLD
#undef TRAIN_RIGHT_THRESHOLD
#undef TRAIN_LEFT_ENTRY
#undef TRAIN_RIGHT_ENTRY
