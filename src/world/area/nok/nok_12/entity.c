#include "nok_12.h"
#include "entity.h"

API_CALLABLE(SetNpcVarSafe) {
    Bytecode* args = script->ptrReadPos;
    Enemy* enemy = script->owner1.enemy;
    s32 npcID = evt_get_variable(script, *args++);
    s32 varIdx = evt_get_variable(script, *args++);
    s32 val = evt_get_variable(script, *args++);

    if (npcID == NPC_SELF) {
        npcID = enemy->npcID;
    }

    enemy = get_enemy_safe(npcID);
    if (enemy != nullptr) {
        enemy->varTable[varIdx] = val;
    }

    return ApiStatus_DONE2;
}

EvtScript EVS_BreakBlock_Ambush = {
    Call(SetNpcVarSafe, NPC_SpikedGoomba, 0, 1)
    Return
    End
};

EvtScript EVS_OnShakeTree_DropSwitch = {
    IfLt(GB_StoryProgress, STORY_CH1_KNOCKED_SWITCH_FROM_TREE)
        Set(GB_StoryProgress, STORY_CH1_KNOCKED_SWITCH_FROM_TREE)
        Wait(15)
        SetGroup(EVT_GROUP_NEVER_PAUSE)
        Call(SetTimeFreezeMode, TIME_FREEZE_PARTIAL)
        Call(DisablePlayerInput, true)
        Call(MakeLerp, 95, 0, 12, EASING_QUADRATIC_IN)
        Label(0)
            Call(UpdateLerp)
            Call(SetEntityPosition, MV_SwitchEntityID, -470, LVar0, -150)
            Wait(1)
            IfEq(LVar1, 1)
                Goto(0)
            EndIf
        Call(PlaySoundAt, SOUND_OBJECT_LAND, SOUND_SPACE_DEFAULT, -470, LVar0, -150)
        Call(ShakeCam, CAM_DEFAULT, 0, 5, 1.0)
        Thread
            Wait(5)
            Call(SetTimeFreezeMode, TIME_FREEZE_NONE)
        EndThread
        Call(DisablePlayerInput, false)
    EndIf
    Return
    End
};

EvtScript EVS_MakeEntities = {
    IfLe(GB_StoryProgress, STORY_CH1_KNOCKED_SWITCH_FROM_TREE)
        IfEq(GB_StoryProgress, STORY_CH1_KNOCKED_SWITCH_FROM_TREE)
            Call(MakeMarkerEntity, $BlueSwitch_1)
        Else
            Call(MakeEntity, Entity_BlueSwitch, NPC_DISPOSE_LOCATION, 0, MAKE_ENTITY_END)
            Call(AssignSwitchFlag, EVT_INDEX_OF_AREA_FLAG(AF_NOK12_HitSwitch))
            Set(MV_SwitchEntityID, LVar0)
        EndIf
    EndIf
    Call(MakeMarkerEntity, $YellowBlock_PowBlock_1)
    Call(MakeMarkerEntity, $BrickBlock_1)
    Call(MakeMarkerEntity, $BrickBlock_2)
    Call(MakeMarkerEntity, $BrickBlock_3)
    Call(MakeMarkerEntity, $BrickBlock_4)
    Call(MakeMarkerEntity, $MulticoinBlock_1)
    Call(MakeMarkerEntity, $Item_StarPiece_1)
    Call(MakeMarkerEntity, $Item_SleepySheep_1)
    Return
    End
};
