#include "common.h"
#include "sprite/player.h"

typedef Bytecode TrainPath;
#define TRAIN_PATH_BEGIN(x, z, yaw) Float(x), Float(z), Float(yaw)
#define TRAIN_PATH_POINT(x, z)      Float(x), Float(z)
#define TRAIN_PATH_END              -1, -1, -1

enum TrainStations {
    OMO_STATION_BLUE            = 0, // omo_03
    OMO_STATION_PINK            = 1, // omo_06
    OMO_STATION_GREEN           = 2, // omo_08
    OMO_STATION_RED             = 3, // omo_10
};

// Toy Train route cycle:
// -> Blue -> Pink -> Green -> Red -> (back to) Blue
enum TrainRoute {
    TRAIN_ROUTE_BLUE_PINK       = 0,
    TRAIN_ROUTE_PINK_GREEN      = 1,
    TRAIN_ROUTE_GREEN_RED       = 2,
    TRAIN_ROUTE_RED_BLUE        = 3,
};

enum TrainStates {
    // Initialize the engine and carriage positions, then measure the path length.
    TRAIN_STATE_INIT        = 0,
    // Read the first waypoint and initialize the two path cursors.
    TRAIN_STATE_BEGIN       = 1,
    // Move both path cursors toward their current waypoints and update the train transform.
    TRAIN_STATE_TRAVEL      = 10,
    // The end-of-path sentinel was reached; keep rendering the train at its final position.
    TRAIN_STATE_DONE        = 100,
};

enum TrainSpeedMode {
    TRAIN_SPEED_CONSTANT        = 0,
    TRAIN_SPEED_ACCELERATE      = 1,
    TRAIN_SPEED_DECELERATE      = 2,
    TRAIN_SPEED_PARTIAL_PATH    = 3,
};

API_CALLABLE(N(CompareFloats)) {
    Bytecode* args = script->ptrReadPos;
    f32 a = evt_get_float_variable(script, *args++);
    f32 b = evt_get_float_variable(script, *args++);
    s32 outVar = *args++;

    if (b < a) {
        evt_set_variable(script, outVar, true);
    } else {
        evt_set_variable(script, outVar, false);
    }
    return ApiStatus_DONE2;
}

API_CALLABLE(N(AdvanceBuffer)) {
    Bytecode* args = script->ptrReadPos;
    s32 constant = evt_get_variable(script, *args++);
    s32 size = evt_get_variable(script, *args++);
    s32 count = evt_get_variable(script, *args++);

    script->buffer = &script->buffer[constant + size * count];
    return ApiStatus_DONE2;
}

API_CALLABLE(N(SetPlayerStatusPosYaw)) {
    Bytecode* args = script->ptrReadPos;
    f32 x = evt_get_float_variable(script, *args++);
    f32 y = evt_get_float_variable(script, *args++);
    f32 z = evt_get_float_variable(script, *args++);
    f32 yaw = evt_get_float_variable(script, *args++);

    gPlayerStatus.pos.x = x;
    gPlayerStatus.pos.y = y;
    gPlayerStatus.pos.z = z;
    gPlayerStatus.targetYaw = yaw;
    return ApiStatus_DONE2;
}

API_CALLABLE(N(SetNpcPosYaw)) {
    Bytecode* args = script->ptrReadPos;
    s32 npcID = evt_get_variable(script, *args++);
    f32 x = evt_get_float_variable(script, *args++);
    f32 y = evt_get_float_variable(script, *args++);
    f32 z = evt_get_float_variable(script, *args++);
    f32 yaw = evt_get_float_variable(script, *args++);
    Npc* npc = get_npc_safe(npcID);

    npc->pos.x = x;
    npc->pos.y = y;
    npc->pos.z = z;
    npc->yaw = yaw;
    npc->colliderPos.x = npc->pos.x;
    npc->colliderPos.y = npc->pos.y;
    npc->colliderPos.z = npc->pos.z;
    npc->flags |= NPC_FLAG_DIRTY_SHADOW;
    return ApiStatus_DONE2;
}

API_CALLABLE(N(IsAOrBPressed)) {
    script->varTable[0] = false;
    if (gGameStatusPtr->pressedButtons[0] & BUTTON_A) {
        script->varTable[0] = true;
    }
    if (gGameStatusPtr->pressedButtons[0] & BUTTON_B) {
        script->varTable[0] = true;
    }
    return ApiStatus_DONE2;
}

EvtScript N(EVS_UpdateTrain) = {
    MallocArray(20, LVar0)
    UseArray(LVar0)
    SetF(ArrayVar(2), Float(0.0))
    SetF(ArrayVar(3), Float(0.0))
    SetF(ArrayVar(7), Float(0.0))
    SetF(ArrayVar(8), Float(0.0))
    SetF(ArrayVar(14), Float(0.0))
    SetF(ArrayVar(15), Float(0.0))
    SetF(ArrayVar(16), Float(0.0))
    Set(AF_OMO_TrainSoundToggle, false)
    Label(0)
        Switch(MV_TrainRideState)
            CaseEq(TRAIN_STATE_INIT)
                UseBuf(MV_TrainPath)
                BufRead3(LVar0, LVar1, LVar2)
                SetF(ArrayVar(0), LVar0)
                SetF(ArrayVar(1), LVar1)
                Call(AddVectorPolar, ArrayVar(0), ArrayVar(1), Float(40.0), LVar2)
                SetF(ArrayVar(5), LVar0)
                SetF(ArrayVar(6), LVar1)
                SetF(LVar3, LVar2)
                AddF(LVar3, Float(180.0))
                Call(AddVectorPolar, ArrayVar(5), ArrayVar(6), Float(40.0), LVar3)
                SetF(ArrayVar(11), LVar0)
                SetF(ArrayVar(12), LVar1)
                SetF(MV_TrainPosX, ArrayVar(11))
                SetF(MV_TrainPosZ, ArrayVar(12))
                SetF(MV_TrainYaw, LVar2)
                SetF(ArrayVar(17), Float(0.0))
                Label(11)
                    BufRead2(LVar2, LVar3)
                    IfEq(LVar2, -1)
                        Goto(12)
                    EndIf
                    Call(GetDist2D, LVar4, LVar0, LVar1, LVar2, LVar3)
                    AddF(ArrayVar(17), LVar4)
                    SetF(LVar0, LVar2)
                    SetF(LVar1, LVar3)
                    Goto(11)
                Label(12)
                SubF(ArrayVar(17), Float(40.0))
                SetF(ArrayVar(10), Float(0.0))
                SetF(ArrayVar(13), Float(0.0))
                Set(ArrayVar(18), 0)
                IfEq(MF_TrainRideActive, true)
                    Set(MV_TrainRideState, TRAIN_STATE_BEGIN)
                EndIf
            CaseEq(TRAIN_STATE_BEGIN)
                UseBuf(MV_TrainPath)
                Call(N(AdvanceBuffer), 3, 0, 0)
                BufRead2(LVar0, LVar1)
                IfEq(LVar0, -1)
                    Set(MV_TrainRideState, TRAIN_STATE_DONE)
                    Set(MF_TrainRideActive, false)
                Else
                    SetF(ArrayVar(2), LVar0)
                    SetF(ArrayVar(3), LVar1)
                    Set(ArrayVar(4), 1)
                    SetF(ArrayVar(7), LVar0)
                    SetF(ArrayVar(8), LVar1)
                    Set(ArrayVar(9), 1)
                    Set(MV_TrainRideState, TRAIN_STATE_TRAVEL)
                EndIf
            CaseEq(TRAIN_STATE_TRAVEL)
                Switch(MV_TrainSpeedMode)
                    CaseEq(TRAIN_SPEED_CONSTANT)
                        SetF(ArrayVar(10), Float(10.0))
                    CaseEq(TRAIN_SPEED_ACCELERATE)
                        Call(CosInterpMinMax, ArrayVar(18), ArrayVar(10), Float(0.0), Float(10.0), 100, 1, Float(0.0))
                        Add(ArrayVar(18), 1)
                    CaseEq(TRAIN_SPEED_DECELERATE)
                        Set(LVar0, ArrayVar(13))
                        Set(LVar1, ArrayVar(17))
                        Call(CosInterpMinMax, LVar0, ArrayVar(10), Float(10.0), Float(2.0), LVar1, 0, Float(0.0))
                    CaseEq(TRAIN_SPEED_PARTIAL_PATH)
                        Set(LVar0, ArrayVar(13))
                        Set(LVar1, ArrayVar(17))
                        Div(LVar1, 2)
                        Call(CosInterpMinMax, LVar0, ArrayVar(10), Float(1.0), Float(10.0), LVar1, 0, Float(0.0))
                EndSwitch
                Call(GetDist2D, LVar0, ArrayVar(0), ArrayVar(1), ArrayVar(2), ArrayVar(3))
                Call(N(CompareFloats), LVar0, ArrayVar(10), LVar2)
                IfEq(LVar2, 1)
                    Call(GetFloatAngleClamped, LVar0, ArrayVar(0), ArrayVar(1), ArrayVar(2), ArrayVar(3))
                    Call(AddVectorPolar, ArrayVar(0), ArrayVar(1), ArrayVar(10), LVar0)
                Else
                    SetF(LVar1, ArrayVar(10))
                    SubF(LVar1, LVar0)
                    SetF(ArrayVar(0), ArrayVar(2))
                    SetF(ArrayVar(1), ArrayVar(3))
                    UseBuf(MV_TrainPath)
                    Call(N(AdvanceBuffer), 3, 2, ArrayVar(4))
                    BufRead2(ArrayVar(2), ArrayVar(3))
                    Add(ArrayVar(4), 1)
                    IfEq(ArrayVar(2), -1)
                        Set(MV_TrainRideState, TRAIN_STATE_DONE)
                        Set(MF_TrainRideActive, false)
                        Set(LFlag1, true)
                    Else
                        Call(GetFloatAngleClamped, LVar0, ArrayVar(0), ArrayVar(1), ArrayVar(2), ArrayVar(3))
                        Call(AddVectorPolar, ArrayVar(0), ArrayVar(1), LVar1, LVar0)
                    EndIf
                EndIf
                Call(GetDist2D, LVar0, ArrayVar(5), ArrayVar(6), ArrayVar(7), ArrayVar(8))
                Call(N(CompareFloats), LVar0, ArrayVar(10), LVar2)
                IfEq(LVar2, 1)
                    Call(GetFloatAngleClamped, LVar0, ArrayVar(5), ArrayVar(6), ArrayVar(7), ArrayVar(8))
                    Call(AddVectorPolar, ArrayVar(5), ArrayVar(6), ArrayVar(10), LVar0)
                Else
                    SetF(LVar1, ArrayVar(10))
                    SubF(LVar1, LVar0)
                    SetF(ArrayVar(5), ArrayVar(7))
                    SetF(ArrayVar(6), ArrayVar(8))
                    UseBuf(MV_TrainPath)
                    Call(N(AdvanceBuffer), 3, 2, ArrayVar(9))
                    BufRead2(ArrayVar(7), ArrayVar(8))
                    Add(ArrayVar(9), 1)
                    IfEq(ArrayVar(7), -1)
                        Set(MV_TrainRideState, TRAIN_STATE_DONE)
                        Set(MF_TrainRideActive, false)
                        Set(LFlag1, false)
                    Else
                        Call(GetFloatAngleClamped, LVar0, ArrayVar(5), ArrayVar(6), ArrayVar(7), ArrayVar(8))
                        Call(AddVectorPolar, ArrayVar(5), ArrayVar(6), LVar1, LVar0)
                    EndIf
                EndIf
                IfEq(MV_TrainRideState, TRAIN_STATE_DONE)
                    IfEq(LFlag1, true)
                        Call(GetFloatAngleClamped, LVar0, ArrayVar(0), ArrayVar(1), ArrayVar(5), ArrayVar(6))
                        SetF(ArrayVar(5), ArrayVar(0))
                        SetF(ArrayVar(6), ArrayVar(1))
                        Call(AddVectorPolar, ArrayVar(5), ArrayVar(6), Float(80.0), LVar0)
                    Else
                        Call(GetFloatAngleClamped, LVar0, ArrayVar(5), ArrayVar(6), ArrayVar(0), ArrayVar(1))
                        SetF(ArrayVar(0), ArrayVar(5))
                        SetF(ArrayVar(1), ArrayVar(6))
                        Call(AddVectorPolar, ArrayVar(0), ArrayVar(1), Float(80.0), LVar0)
                    EndIf
                EndIf
                SetF(LVar0, ArrayVar(0))
                SetF(LVar1, ArrayVar(1))
                AddF(LVar0, ArrayVar(5))
                AddF(LVar1, ArrayVar(6))
                DivF(LVar0, Float(2.0))
                DivF(LVar1, Float(2.0))
                Call(GetFloatAngleClamped, LVar2, ArrayVar(5), ArrayVar(6), ArrayVar(0), ArrayVar(1))
                SetF(MV_TrainPosX, LVar0)
                SetF(MV_TrainPosZ, LVar1)
                SetF(MV_TrainYaw, LVar2)
                Call(GetDist2D, LVar3, LVar0, LVar1, ArrayVar(11), ArrayVar(12))
                AddF(ArrayVar(13), LVar3)
                SetF(ArrayVar(14), ArrayVar(13))
                MulF(ArrayVar(14), Float(1.432))
                IfEq(LFlag0, false)
                    SetF(LVar0, ArrayVar(10))
                    IfLt(LVar0, 1)
                        SetF(LVar0, Float(1.0))
                    EndIf
                    DivF(LVar0, Float(3.0))
                    SubF(ArrayVar(15), LVar0)
                    IfLt(ArrayVar(15), -10)
                        SetF(ArrayVar(15), Float(-10.0))
                        Set(LFlag0, true)
                        IfEq(AF_OMO_TrainSoundToggle, false)
                            Call(PlaySound, SOUND_OMO_TOY_TRAIN_WHISTLE_A)
                        Else
                            Call(PlaySound, SOUND_OMO_TOY_TRAIN_WHISTLE_B)
                        EndIf
                    EndIf
                Else
                    SetF(LVar0, ArrayVar(10))
                    IfLt(LVar0, 1)
                        SetF(LVar0, Float(1.0))
                    EndIf
                    DivF(LVar0, Float(3.0))
                    AddF(ArrayVar(15), LVar0)
                    IfGt(ArrayVar(15), 10)
                        SetF(ArrayVar(15), Float(10.0))
                        Set(LFlag0, false)
                        IfEq(AF_OMO_TrainSoundToggle, false)
                            Call(PlaySound, SOUND_OMO_TOY_TRAIN_CLICK)
                            Set(AF_OMO_TrainSoundToggle, true)
                        Else
                            Call(PlaySound, SOUND_OMO_TOY_TRAIN_CLICK)
                            Set(AF_OMO_TrainSoundToggle, false)
                        EndIf
                    EndIf
                EndIf
                SetF(LVar0, MV_TrainPosX)
                SetF(LVar1, MV_TrainPosZ)
                SetF(LVar2, MV_TrainYaw)
                Call(AddVectorPolar, LVar0, LVar1, Float(15.0), LVar2)
                Call(N(SetPlayerStatusPosYaw), LVar0, 50, LVar1, MV_TrainYaw)
                SetF(LVar0, MV_TrainPosX)
                SetF(LVar1, MV_TrainPosZ)
                SetF(LVar2, MV_TrainYaw)
                AddF(LVar2, Float(180.0))
                Call(AddVectorPolar, LVar0, LVar1, Float(15.0), LVar2)
                Call(N(SetNpcPosYaw), NPC_PARTNER, LVar0, 50, LVar1, MV_TrainYaw)
                SetF(LVar0, MV_TrainPosX)
                SetF(LVar1, MV_TrainPosZ)
                SetF(LVar2, MV_TrainYaw)
                IfLt(LVar2, 180)
                    AddF(LVar2, Float(90.0))
                Else
                    SubF(LVar2, Float(90.0))
                EndIf
                Call(AddVectorPolar, LVar0, LVar1, Float(20.0), LVar2)
                Call(N(SetNpcPosYaw), NPC_Conductor, LVar0, 50, LVar1, MV_TrainYaw)
            CaseEq(TRAIN_STATE_DONE)
                // do nothing
        EndSwitch
        Call(TranslateGroup, MODEL_p2, Float(79.1), Float(-27.93), Float(-29.53))
        Call(TranslateGroup, MODEL_p3, Float(-35.1), Float(-27.93), Float(-29.53))
        Call(RotateGroup, MODEL_p2, Float(-45.0), Float(0.0), Float(0.0), Float(1.0))
        Call(RotateGroup, MODEL_p3, Float(45.0), Float(0.0), Float(0.0), Float(1.0))
        Call(TranslateGroup, MODEL_p5, Float(40.5), Float(-20.0), Float(-0.4))
        Call(TranslateGroup, MODEL_p6, Float(-39.5), Float(-20.0), Float(-0.4))
        Call(TranslateGroup, MODEL_popo, MV_TrainPosX, Float(10.0), MV_TrainPosZ)
        IfLt(MV_TrainYaw, 180)
            SetF(LVar1, MV_TrainYaw)
            SubF(LVar1, Float(90.0))
            Call(RotateGroup, MODEL_popo, LVar1, Float(0.0), Float(-1.0), Float(0.0))
        Else
            SetF(LVar1, MV_TrainYaw)
            SubF(LVar1, Float(180.0))
            SubF(LVar1, Float(90.0))
            Call(RotateGroup, MODEL_popo, LVar1, Float(0.0), Float(-1.0), Float(0.0))
        EndIf
        Call(RotateGroup, MODEL_p2, Float(45.0), Float(0.0), Float(0.0), Float(1.0))
        Call(RotateGroup, MODEL_p3, Float(-45.0), Float(0.0), Float(0.0), Float(1.0))
        Call(TranslateGroup, MODEL_p2, Float(-79.1), Float(27.93), Float(29.53))
        Call(TranslateGroup, MODEL_p3, Float(35.1), Float(27.93), Float(29.53))
        Call(TranslateGroup, MODEL_p5, Float(-40.5), Float(20.0), Float(0.4))
        Call(TranslateGroup, MODEL_p6, Float(39.5), Float(20.0), Float(0.4))
        IfLt(MV_TrainYaw, 180)
            Call(RotateGroup, MODEL_p5, ArrayVar(14), Float(0.0), Float(0.0), Float(-1.0))
            Call(RotateGroup, MODEL_p6, ArrayVar(14), Float(0.0), Float(0.0), Float(-1.0))
        Else
            Call(RotateGroup, MODEL_p5, ArrayVar(14), Float(0.0), Float(0.0), Float(1.0))
            Call(RotateGroup, MODEL_p6, ArrayVar(14), Float(0.0), Float(0.0), Float(1.0))
        EndIf
        Call(TranslateGroup, MODEL_p2, Float(0.0), ArrayVar(15), Float(0.0))
        SetF(LVar0, ArrayVar(15))
        MulF(LVar0, Float(-1.0))
        Call(TranslateGroup, MODEL_p3, Float(0.0), LVar0, Float(0.0))
        SetF(LVar0, ArrayVar(10))
        IfLt(LVar0, 1)
            SetF(LVar0, Float(1.0))
        EndIf
        AddF(ArrayVar(16), LVar0)
        IfGt(ArrayVar(16), 360)
            SubF(ArrayVar(16), Float(360.0))
        EndIf
        Call(RotateGroup, MODEL_p4, ArrayVar(16), Float(0.0), Float(1.0), Float(0.0))
        SetF(ArrayVar(11), MV_TrainPosX)
        SetF(ArrayVar(12), MV_TrainPosZ)
        Wait(1)
        Goto(0)
    Return
    End
};

EvtScript N(EVS_UpdateCameraDuringTrainRide) = {
    Label(0)
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
        Call(SetCamTarget, CAM_DEFAULT, LVar0, 0, LVar2)
        Wait(1)
        Goto(0)
    Return
    End
};

EvtScript N(EVS_RestoreCameraAfterTrainRide) = {
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Call(MakeLerp, 0, LVar1, 45, EASING_LINEAR)
    Loop(0)
        Call(UpdateLerp)
        Call(GetPlayerPos, LVar2, LVar3, LVar4)
        Call(SetCamTarget, CAM_DEFAULT, LVar2, LVar0, LVar4)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Return
    End
};

EvtScript N(EVS_LowerCameraBeforeTrainRide) = {
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Call(MakeLerp, LVar1, 0, 40, EASING_LINEAR)
    Loop(0)
        Call(UpdateLerp)
        Call(GetPlayerPos, LVar2, LVar3, LVar4)
        Call(SetCamTarget, CAM_DEFAULT, LVar2, LVar0, LVar4)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Loop(0)
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
        Call(SetCamTarget, CAM_DEFAULT, LVar0, 0, LVar2)
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript N(EVS_BoardTrain) = {
    Call(SetNpcFlagBits, NPC_Conductor, NPC_FLAG_IGNORE_WORLD_COLLISION | NPC_FLAG_IGNORE_CHAR_COLLISION, true)
    Call(SetNpcFlagBits, NPC_PARTNER, NPC_FLAG_IGNORE_WORLD_COLLISION | NPC_FLAG_IGNORE_CHAR_COLLISION, true)
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
    Call(SetNpcSpeed, NPC_PARTNER, Float(0.5))
    Call(NpcMoveTo, NPC_PARTNER, LVar1, LVar2, 0)
    Call(SetNpcAnimation, NPC_PARTNER, PARTNER_ANIM_IDLE)
    Call(InterpNpcYaw, NPC_PARTNER, LVarA, 0)
    Wait(5)
    UseBuf(LVar0)
    BufRead3(LVar1, LVar2, LVar3)
    SetF(LVarA, LVar3)
    IfLt(LVar3, 180)
        AddF(LVar3, Float(90.0))
    Else
        SubF(LVar3, Float(90.0))
    EndIf
    SetF(LVar4, LVar1)
    SetF(LVar5, LVar2)
    SetF(LVar6, LVar3)
    Call(AddVectorPolar, LVar1, LVar2, Float(100.0), LVar3)
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

EvtScript N(EVS_DisembarkTrain) = {
    Call(StopSound, SOUND_LRAW_TOYBOX_TRAIN_GEAR)
    Call(SetMusic, 0, SONG_SHY_GUY_TOYBOX, 0, VOL_LEVEL_FULL)
    Call(SetNpcFlagBits, NPC_Conductor, NPC_FLAG_IGNORE_WORLD_COLLISION | NPC_FLAG_IGNORE_CHAR_COLLISION, true)
    Call(SetNpcFlagBits, NPC_PARTNER, NPC_FLAG_IGNORE_WORLD_COLLISION | NPC_FLAG_IGNORE_CHAR_COLLISION, true)
    SetF(LVar0, MV_TrainPosX)
    SetF(LVar1, MV_TrainPosZ)
    SetF(LVar2, MV_TrainYaw)
    IfLt(LVar2, 180)
        AddF(LVar2, Float(90.0))
    Else
        SubF(LVar2, Float(90.0))
    EndIf
    Call(AddVectorPolar, LVar0, LVar1, Float(100.0), LVar2)
    Thread
        Call(SetNpcJumpscale, NPC_Conductor, Float(1.0))
        Call(NpcJump0, NPC_Conductor, LVar0, 50, LVar1, 10)
        Call(SetNpcAnimation, NPC_Conductor, ANIM_TrainToad_Walk)
        Call(SetNpcSpeed, NPC_Conductor, Float(2.0))
        UseBuf(LVar9)
        BufRead2(LVar3, LVar4)
        Call(NpcMoveTo, NPC_Conductor, LVar3, LVar4, 0)
        Call(SetNpcAnimation, NPC_Conductor, ANIM_TrainToad_Idle)
        Call(InterpNpcYaw, NPC_Conductor, 270, 15)
        Call(SetNpcFlagBits, NPC_Conductor, NPC_FLAG_IGNORE_WORLD_COLLISION | NPC_FLAG_IGNORE_CHAR_COLLISION, false)
    EndThread
    Wait(10)
    Thread
        AddF(LVar2, Float(60.0))
        Call(AddVectorPolar, LVar0, LVar1, Float(20.0), LVar2)
        Call(SetPlayerAnimation, ANIM_Mario1_Walk)
        Call(SetPlayerSpeed, Float(3.0))
        Call(PlayerMoveTo, LVar0, LVar1, 0)
        Call(SetPlayerAnimation, ANIM_Mario1_Idle)
    EndThread
    Wait(10)
    Sub(LVar1, 30)
    Call(SetNpcAnimation, NPC_PARTNER, PARTNER_ANIM_WALK)
    Call(SetNpcSpeed, NPC_PARTNER, Float(2.5))
    Call(NpcMoveTo, NPC_PARTNER, LVar0, LVar1, 0)
    Call(SetNpcAnimation, NPC_PARTNER, PARTNER_ANIM_IDLE)
    Call(SetNpcFlagBits, NPC_PARTNER, NPC_FLAG_IGNORE_WORLD_COLLISION | NPC_FLAG_IGNORE_CHAR_COLLISION, false)
    Return
    End
};

EvtScript N(EVS_SkipTrainRideToDestination) = {
    Switch(AB_OMO_TrainDest)
        CaseEq(OMO_STATION_BLUE)
            Call(GotoMapSpecial, Ref("omo_03"), omo_03_ENTRY_3, TRANSITION_TOY_TRAIN)
        CaseEq(OMO_STATION_PINK)
            Call(GotoMapSpecial, Ref("omo_06"), omo_06_ENTRY_3, TRANSITION_TOY_TRAIN)
        CaseEq(OMO_STATION_GREEN)
            Call(GotoMapSpecial, Ref("omo_08"), omo_08_ENTRY_2, TRANSITION_TOY_TRAIN)
        CaseEq(OMO_STATION_RED)
            Call(GotoMapSpecial, Ref("omo_10"), omo_10_ENTRY_3, TRANSITION_TOY_TRAIN)
    EndSwitch
    Wait(100)
    Return
    End
};

EvtScript N(EVS_SkipTrainRideToNextStation) = {
    Switch(AB_OMO_TrainOrigin)
        CaseEq(OMO_STATION_BLUE)
            Switch(AB_OMO_TrainDest)
                CaseEq(OMO_STATION_PINK)
                    Call(GotoMapSpecial, Ref("omo_06"), omo_06_ENTRY_2, TRANSITION_TOY_TRAIN)
                CaseEq(OMO_STATION_GREEN)
                    Call(GotoMapSpecial, Ref("omo_08"), omo_08_ENTRY_1, TRANSITION_TOY_TRAIN)
                CaseEq(OMO_STATION_RED)
                    Call(GotoMapSpecial, Ref("omo_10"), omo_10_ENTRY_2, TRANSITION_TOY_TRAIN)
            EndSwitch
        CaseEq(OMO_STATION_PINK)
            Switch(AB_OMO_TrainDest)
                CaseEq(OMO_STATION_BLUE)
                    Call(GotoMapSpecial, Ref("omo_03"), omo_03_ENTRY_2, TRANSITION_TOY_TRAIN)
                CaseEq(OMO_STATION_GREEN)
                    Call(GotoMapSpecial, Ref("omo_08"), omo_08_ENTRY_1, TRANSITION_TOY_TRAIN)
                CaseEq(OMO_STATION_RED)
                    Call(GotoMapSpecial, Ref("omo_10"), omo_10_ENTRY_2, TRANSITION_TOY_TRAIN)
            EndSwitch
        CaseEq(OMO_STATION_GREEN)
            Switch(AB_OMO_TrainDest)
                CaseEq(OMO_STATION_BLUE)
                    Call(GotoMapSpecial, Ref("omo_03"), omo_03_ENTRY_2, TRANSITION_TOY_TRAIN)
                CaseEq(OMO_STATION_PINK)
                    IfEq(GF_OMO03_BlueSwitchActivated, true)
                        Call(GotoMapSpecial, Ref("omo_06"), omo_06_ENTRY_2, TRANSITION_TOY_TRAIN)
                    Else
                        Call(GotoMapSpecial, Ref("omo_03"), omo_03_ENTRY_2, TRANSITION_TOY_TRAIN)
                    EndIf
                CaseEq(OMO_STATION_RED)
                    Call(GotoMapSpecial, Ref("omo_10"), omo_10_ENTRY_2, TRANSITION_TOY_TRAIN)
            EndSwitch
        CaseEq(OMO_STATION_RED)
            Switch(AB_OMO_TrainDest)
                CaseEq(OMO_STATION_BLUE)
                    Call(GotoMapSpecial, Ref("omo_03"), omo_03_ENTRY_2, TRANSITION_TOY_TRAIN)
                CaseEq(OMO_STATION_PINK)
                    IfEq(GF_OMO03_BlueSwitchActivated, true)
                        Call(GotoMapSpecial, Ref("omo_06"), omo_06_ENTRY_2, TRANSITION_TOY_TRAIN)
                    Else
                        Call(GotoMapSpecial, Ref("omo_03"), omo_03_ENTRY_2, TRANSITION_TOY_TRAIN)
                    EndIf
                CaseEq(OMO_STATION_GREEN)
                    IfEq(GF_OMO03_BlueSwitchActivated, true)
                        Call(GotoMapSpecial, Ref("omo_08"), omo_08_ENTRY_1, TRANSITION_TOY_TRAIN)
                    Else
                        Call(GotoMapSpecial, Ref("omo_03"), omo_03_ENTRY_2, TRANSITION_TOY_TRAIN)
                    EndIf
            EndSwitch
    EndSwitch
    Wait(100)
    Return
    End
};

EvtScript N(EVS_AwaitTrainRideSkip) = {
    Label(10)
        Wait(1)
        Call(N(IsAOrBPressed))
        IfNe(LVar0, 1)
            Goto(10)
        EndIf
    IfEq(AF_OMO_UsingRightSwitch, false)
        ExecWait(N(EVS_SkipTrainRideToDestination))
    Else
        ExecWait(N(EVS_SkipTrainRideToNextStation))
    EndIf
    Return
    End
};
