#include "trd_02.h"
#include "world/area/trd/trd_01.h"
#include "world/area/trd/trd_03.h"
#include "effects.h"

extern EvtScript EVS_UnlockFortressDoor;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;

EvtScript EVS_ExitDoors_trd_01_1 =
    EVT_EXIT_DOUBLE_DOOR($Trd01Lower, $trd_01.Trd02Lower, COLLIDER_ttw, MODEL_o6, MODEL_o7);
EvtScript EVS_ExitDoors_trd_03_0 =
    EVT_EXIT_DOUBLE_DOOR($Trd03Lower, $trd_03.Trd04Lower, COLLIDER_tte, MODEL_o9, MODEL_o8);
EvtScript EVS_ExitDoors_trd_01_2 =
    EVT_EXIT_DOUBLE_DOOR($Trd01Upper, $trd_01.Trd02Upper, COLLIDER_ttw2, MODEL_o13, MODEL_o12);
EvtScript EVS_ExitDoors_trd_03_2 =
    EVT_EXIT_DOUBLE_DOOR($Trd03Upper, $trd_03.Trd02Upper, COLLIDER_tte2, MODEL_o10, MODEL_o11);
EvtScript EVS_ExitWalk_trd_03_4 = EVT_EXIT_WALK(40, $Trd03Walk, $trd_03.Trd02Walk);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_trd_03_4, TRIGGER_FLOOR_ABOVE, COLLIDER_deilia, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    SetGroup(EVT_GROUP_NEVER_PAUSE)
    SuspendGroup(EVT_GROUP_FLAG_INTERACT)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($Trd01Lower.index)
            Set(LVar2, MODEL_o6)
            Set(LVar3, MODEL_o7)
            ExecWait(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq($Trd03Lower.index)
            Set(LVar2, MODEL_o9)
            Set(LVar3, MODEL_o8)
            ExecWait(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq($Trd01Upper.index)
            Set(LVar2, MODEL_o13)
            Set(LVar3, MODEL_o12)
            ExecWait(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq($Trd03Upper.index)
            Set(LVar2, MODEL_o10)
            Set(LVar3, MODEL_o11)
            ExecWait(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq($Trd03Walk.index)
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
    EndSwitch
    ResumeGroup(EVT_GROUP_FLAG_INTERACT)
    Return
    End
};

EvtScript EVS_Scene_LowerStairs = {
    SetGroup(EVT_GROUP_NEVER_PAUSE)
    Call(SetTimeFreezeMode, 0)
    SuspendGroup(EVT_GROUP_FLAG_INTERACT)
    Call(DisablePlayerInput, true)
    Wait(30)
    Call(SetGroupVisibility, MODEL_move_saku, MODEL_GROUP_HIDDEN)
    Call(PlaySound, SOUND_LOOP_TRD_02_LOWER_STAIRS)
    Thread
        Call(ShakeCam, CAM_DEFAULT, 0, 10, 0.7)
        Call(ShakeCam, CAM_DEFAULT, 0, 320, 1.0)
        Call(ShakeCam, CAM_DEFAULT, 0, 10, 0.7)
        Call(ShakeCam, CAM_DEFAULT, 0, 10, 0.4)
    EndThread
    Wait(20)
    Thread
        Loop(5)
            Call(GetPlayerPos, LVar0, LVar1, LVar2)
            Add(LVar1, 150)
            PlayEffect(EFFECT_DUST, 0, LVar0, LVar1, LVar2, 40)
            Call(RandInt, 20, LVar0)
            Add(LVar0, 20)
            Wait(LVar0)
        EndLoop
    EndThread
    Thread
        Loop(7)
            Call(GetPlayerPos, LVar1, LVar2, LVar3)
            Call(RandInt, 200, LVar4)
            Sub(LVar4, 100)
            Call(RandInt, 200, LVar5)
            Sub(LVar5, 100)
            Add(LVar1, LVar4)
            Add(LVar2, 200)
            Add(LVar3, LVar5)
            PlayEffect(EFFECT_SHATTERING_STONES, 0, LVar1, LVar2, LVar3, 187)
            Call(RandInt, 30, LVar0)
            Add(LVar0, 30)
            Wait(LVar0)
        EndLoop
    EndThread
    Wait(20)
    Call(MakeLerp, 187, 0, 300, EASING_COS_IN_OUT)
    Label(0)
    Call(UpdateLerp)
    Call(TranslateModel, MODEL_dan, 0, LVar0, 0)
    Call(TranslateModel, MODEL_k_soku, 0, LVar0, 0)
    Call(TranslateModel, MODEL_kusari, 0, LVar0, 0)
    Wait(1)
    IfEq(LVar1, 1)
        Goto(0)
    EndIf
    Call(UpdateColliderTransform, COLLIDER_o54)
    Call(UpdateColliderTransform, COLLIDER_o55)
    Call(UpdateColliderTransform, COLLIDER_o65)
    Call(StopSound, SOUND_LOOP_TRD_02_LOWER_STAIRS)
    Call(PlaySound, SOUND_TRD_02_STAIRS_LOWERED)
    Set(GB_StoryProgress, STORY_CH1_LOWERED_SECOND_STAIRS)
    Call(DisablePlayerInput, false)
    Call(SetTimeFreezeMode, 0)
    ResumeGroup(EVT_GROUP_FLAG_INTERACT)
    Unbind
    Return
    End
};

BombTrigger BombPos_Wall = {
    .pos = $BombPos_Wall.pos,
    .diameter = 2.0f * $BombPos_Wall.radius,
};

EvtScript EVS_BlastBombableWall = {
    SetGroup(EVT_GROUP_NEVER_PAUSE)
    SuspendGroup(EVT_GROUP_FLAG_INTERACT)
    PlayEffect(EFFECT_BOMBETTE_BREAKING, 0, $BombetteBreakingPos_1.pos.x, $BombetteBreakingPos_1.pos.y, $BombetteBreakingPos_1.pos.z, 10, 30)
    Call(EnableModel, MODEL_anaaki, true)
    Loop(10)
        Call(SetGroupVisibility, MODEL_g14, MODEL_GROUP_VISIBLE)
        Wait(1)
        Call(SetGroupVisibility, MODEL_g14, MODEL_GROUP_HIDDEN)
        Wait(1)
    EndLoop
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_tta, COLLIDER_FLAGS_UPPER_MASK)
    Set(GF_TRD02_BombedWall, true)
    ResumeGroup(EVT_GROUP_FLAG_INTERACT)
    Unbind
    Return
    End
};

ITEM_LIST(KeyList, ITEM_KOOPA_FORTRESS_KEY);

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_KOOPA_BROS_FORTRESS)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, true, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    BindTrigger(EVS_ExitDoors_trd_01_1, TRIGGER_WALL_PRESS_A, COLLIDER_ttw, 1, 0)
    BindTrigger(EVS_ExitDoors_trd_03_0, TRIGGER_WALL_PRESS_A, COLLIDER_tte, 1, 0)
    IfEq(GF_TRD02_UnlockedDoor, false)
        BindPadlock(EVS_UnlockFortressDoor, TRIGGER_WALL_PRESS_A, EVT_ENTITY_INDEX(0), KeyList, 0, 1)
    Else
        BindTrigger(EVS_ExitDoors_trd_01_2, TRIGGER_WALL_PRESS_A, COLLIDER_ttw2, 1, 0)
    EndIf
    BindTrigger(EVS_ExitDoors_trd_03_2, TRIGGER_WALL_PRESS_A, COLLIDER_tte2, 1, 0)
    IfEq(GF_TRD02_BombedWall, false)
        Call(EnableModel, MODEL_anaaki, false)
        BindTrigger(EVS_BlastBombableWall, TRIGGER_POINT_BOMB, BombPos_Wall, 1, 0)
    Else
        Call(SetGroupVisibility, MODEL_g14, MODEL_GROUP_HIDDEN)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_tta, COLLIDER_FLAGS_UPPER_MASK)
    EndIf
    Exec(EVS_SetupMusic)
    Set(AF_TRD02_LowerStairs, false)
    Call(ParentColliderToModel, COLLIDER_o55, MODEL_dan)
    Call(ParentColliderToModel, COLLIDER_o54, MODEL_k_soku)
    Call(ParentColliderToModel, COLLIDER_o65, MODEL_kusari)
    IfLt(GB_StoryProgress, STORY_CH1_LOWERED_SECOND_STAIRS)
        Call(TranslateModel, MODEL_dan, 0, 187, 0)
        Call(TranslateModel, MODEL_k_soku, 0, 187, 0)
        Call(TranslateModel, MODEL_kusari, 0, 187, 0)
        Call(UpdateColliderTransform, COLLIDER_o55)
        Call(UpdateColliderTransform, COLLIDER_o54)
        Call(UpdateColliderTransform, COLLIDER_o65)
        BindTrigger(EVS_Scene_LowerStairs, TRIGGER_AREA_FLAG_SET, AF_TRD02_LowerStairs, 1, 0)
    Else
        Call(UpdateColliderTransform, COLLIDER_o55)
        Call(UpdateColliderTransform, COLLIDER_o54)
        Call(UpdateColliderTransform, COLLIDER_o65)
        Call(SetGroupVisibility, MODEL_move_saku, MODEL_GROUP_HIDDEN)
    EndIf
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
