#include "dgb_01.h"

EvtScript N(EVS_ExitDoors_dgb_00_1) = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(dgb_01_ENTRY_0, "dgb_00", dgb_00_ENTRY_1,
    COLLIDER_deilitts, MODEL_o380, MODEL_o381, DOOR_SOUNDS_CREAKY);

EvtScript N(EVS_ExitDoors_dgb_02_1) = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(dgb_01_ENTRY_1, "dgb_02", dgb_02_ENTRY_1,
    COLLIDER_deilittsw, MODEL_o163, MODEL_o164, DOOR_SOUNDS_CREAKY);

EvtScript N(EVS_ExitDoors_dgb_08_0) = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(dgb_01_ENTRY_2, "dgb_08", dgb_08_ENTRY_0,
    COLLIDER_deilittse, MODEL_o168, MODEL_o167, DOOR_SOUNDS_CREAKY);

EvtScript N(EVS_ExitDoors_dgb_09_1) = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(dgb_01_ENTRY_3, "dgb_09", dgb_09_ENTRY_1,
    COLLIDER_deilittw, MODEL_o165, MODEL_o166, DOOR_SOUNDS_CREAKY);

EvtScript N(EVS_ExitDoors_dgb_08_1) = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(dgb_01_ENTRY_4, "dgb_08", dgb_08_ENTRY_1,
    COLLIDER_deilitte, MODEL_o299, MODEL_o298, DOOR_SOUNDS_CREAKY);

EvtScript N(EVS_ExitDoors_dgb_17_1) = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(dgb_01_ENTRY_5, "dgb_17", dgb_17_ENTRY_1,
    COLLIDER_deilittnw, MODEL_o161, MODEL_o162, DOOR_SOUNDS_CREAKY);

EvtScript N(EVS_ExitDoors_dgb_18_0) = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(dgb_01_ENTRY_6, "dgb_18", dgb_18_ENTRY_0,
    COLLIDER_deilittne, MODEL_o301, MODEL_o300, DOOR_SOUNDS_CREAKY);

EvtScript N(EVS_EnterMap) = {
    Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(dgb_01_ENTRY_0)
            IfEq(GF_DGB01_Visited, false)
                Set(GF_DGB01_Visited, true)
                Set(GB_StoryProgress, STORY_CH3_ARRIVED_AT_TUBBAS_MANOR)
            EndIf
            Set(LVar2, MODEL_o380)
            Set(LVar3, MODEL_o381)
            ExecWait(EnterDoubleDoor)
        CaseEq(dgb_01_ENTRY_1)
            Set(LVar2, MODEL_o163)
            Set(LVar3, MODEL_o164)
            ExecWait(EnterDoubleDoor)
        CaseEq(dgb_01_ENTRY_2)
            Set(LVar2, MODEL_o168)
            Set(LVar3, MODEL_o167)
            ExecWait(EnterDoubleDoor)
        CaseEq(dgb_01_ENTRY_3)
            Set(LVar2, MODEL_o165)
            Set(LVar3, MODEL_o166)
            ExecWait(EnterDoubleDoor)
        CaseEq(dgb_01_ENTRY_4)
            Set(LVar2, MODEL_o299)
            Set(LVar3, MODEL_o298)
            ExecWait(EnterDoubleDoor)
        CaseEq(dgb_01_ENTRY_5)
            Set(LVar2, MODEL_o161)
            Set(LVar3, MODEL_o162)
            ExecWait(EnterDoubleDoor)
        CaseEq(dgb_01_ENTRY_6)
            Set(LVar2, MODEL_o301)
            Set(LVar3, MODEL_o300)
            ExecWait(EnterDoubleDoor)
    EndSwitch
    Return
    End
};

s32 N(KeyList)[] = {
    ITEM_TUBBA_CASTLE_KEY,
    ITEM_NONE
};

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_TUBBAS_MANOR)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Set(GF_MAP_TubbasManor, true)
    ExecWait(N(EVS_MakeEntities))
    Exec(N(EVS_SetupBridges))
    Exec(N(EVS_SetupMusic))
    BindTrigger(Ref(N(EVS_ExitDoors_dgb_00_1)), TRIGGER_WALL_PRESS_A, COLLIDER_deilitts, 1, 0)
    BindTrigger(Ref(N(EVS_ExitDoors_dgb_02_1)), TRIGGER_WALL_PRESS_A, COLLIDER_deilittsw, 1, 0)
    BindTrigger(Ref(N(EVS_ExitDoors_dgb_09_1)), TRIGGER_WALL_PRESS_A, COLLIDER_deilittw, 1, 0)
    BindTrigger(Ref(N(EVS_ExitDoors_dgb_08_1)), TRIGGER_WALL_PRESS_A, COLLIDER_deilitte, 1, 0)
    BindTrigger(Ref(N(EVS_ExitDoors_dgb_17_1)), TRIGGER_WALL_PRESS_A, COLLIDER_deilittnw, 1, 0)
    BindTrigger(Ref(N(EVS_ExitDoors_dgb_18_0)), TRIGGER_WALL_PRESS_A, COLLIDER_deilittne, 1, 0)
    IfEq(GF_DGB01_UnlockedEastWing, false)
        BindPadlock(Ref(N(EVS_UnlockPrompt_Door)), TRIGGER_WALL_PRESS_A, EVT_ENTITY_INDEX(0), Ref(N(KeyList)), 0, 1)
    Else
        BindTrigger(Ref(N(EVS_ExitDoors_dgb_08_0)), TRIGGER_WALL_PRESS_A, COLLIDER_deilittse, 1, 0)
    EndIf
    Switch(GB_StoryProgress)
        CaseLt(STORY_CH3_TUBBA_WOKE_UP)
            Call(MakeNpcs, true, Ref(N(DefaultNPCs)))
        CaseLt(STORY_CH3_DEFEATED_TUBBA_BLUBBA)
            Call(GetEntryID, LVar0)
            Switch(LVar0)
                CaseEq(dgb_01_ENTRY_2)
                    Call(MakeNpcs, true, Ref(N(FirstFloorEscapeNPCs)))
                CaseEq(dgb_01_ENTRY_4)
                    Call(MakeNpcs, true, Ref(N(SecondFloorEscapeNPCs)))
                CaseEq(dgb_01_ENTRY_6)
                    Call(MakeNpcs, true, Ref(N(ThirdFloorEscapeNPCs)))
            EndSwitch
    EndSwitch
    Exec(N(EVS_EnterMap))
    Return
    End
};
