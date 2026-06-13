#include "nok_01.h"
#include "sprite/player.h"

enum RadioStation {
    RADIO_STATION_ISLAND_SOUNDS     = 0,
    RADIO_STATION_GOLDEN_OLDIES     = 1,
    RADIO_STATION_HOT_HITS          = 2,
    RADIO_STATION_INFORMATION       = 3,
    RADIO_STATION_COUNT             = 4,
};

s16 N(StationMseqMapping)[] = {
    [RADIO_STATION_ISLAND_SOUNDS]   0,
    [RADIO_STATION_GOLDEN_OLDIES]   2,
    [RADIO_STATION_HOT_HITS]        1,
    [RADIO_STATION_INFORMATION]     4,
};

API_CALLABLE(N(InitializeRadio)) {
    Bytecode* args = script->ptrReadPos;

    evt_get_variable(script, *args++);
    snd_load_ambient(AMBIENT_RADIO);
    snd_ambient_radio_setup(4);
    snd_ambient_set_volume(0, 250, 1);
    return ApiStatus_DONE2;
}

API_CALLABLE(N(SetRadioVolumeMax)) {
    Bytecode* args = script->ptrReadPos;
    s32 idx = evt_get_variable(script, *args++);

    snd_ambient_radio_select(N(StationMseqMapping)[idx]);
    snd_ambient_set_volume(N(StationMseqMapping)[idx], 1500, 127);
    return ApiStatus_DONE2;
}

API_CALLABLE(N(SetRadioVolumeMute)) {
    Bytecode* args = script->ptrReadPos;
    s32 idx = evt_get_variable(script, *args++);

    snd_ambient_set_volume(N(StationMseqMapping)[idx], 1500, 1);
    return ApiStatus_DONE2;
}

API_CALLABLE(N(MuteAllRadioStations)) {
    snd_ambient_radio_select(4);
    return ApiStatus_DONE2;
}

API_CALLABLE(N(StopAllRadioStations)) {
    snd_ambient_radio_stop(100);
    return ApiStatus_DONE2;
}

API_CALLABLE(N(SetRadioStation)) {
    Bytecode* args = script->ptrReadPos;
    s32 index = evt_get_variable(script, *args++);

    snd_ambient_radio_select(N(StationMseqMapping)[index]);
    return ApiStatus_DONE2;
}

API_CALLABLE(N(SetTradeEventStartTime)) {
    gPlayerData.tradeEventStartTime = gPlayerData.frameCounter;
    return ApiStatus_DONE2;
}

EvtScript N(EVS_InitiateTradingEvent) = {
    Switch(GB_TradingEvent_Count)
        CaseEq(0)
            IfLt(GB_StoryProgress, STORY_CH1_STAR_SPRIT_DEPARTED)
                IfLt(GB_StoryProgress, STORY_CH1_KOOPER_JOINED_PARTY)
                    Call(SwitchMessage, MSG_CH1_0028)
                Else
                    Call(SwitchMessage, MSG_CH1_0029)
                EndIf
            Else
                Call(SwitchMessage, MSG_CH1_002A)
                Set(GF_TradingEvent1_Active, true)
                Call(N(SetTradeEventStartTime))
            EndIf
        CaseEq(1)
            IfLt(GB_StoryProgress, STORY_CH3_BEGAN_PEACH_MISSION)
                Call(SwitchMessage, MSG_CH1_002E)
            Else
                Call(SwitchMessage, MSG_CH1_002B)
                Set(GF_TradingEvent2_Active, true)
                Call(N(SetTradeEventStartTime))
            EndIf
        CaseEq(2)
            IfLt(GB_StoryProgress, STORY_CH5_STAR_SPRIT_DEPARTED)
                Call(SwitchMessage, MSG_CH1_002E)
            Else
                Call(SwitchMessage, MSG_CH1_002C)
                Set(GF_TradingEvent3_Active, true)
                Call(N(SetTradeEventStartTime))
            EndIf
        CaseEq(3)
            Call(SwitchMessage, MSG_CH1_002D)
    EndSwitch
    Return
    End
};

EvtScript N(EVS_Interact_Radio) = {
    Call(DisablePlayerInput, true)
    Call(SetPlayerAnimation, ANIM_Mario1_Idle)
    Wait(2)
    Call(SetPlayerAnimation, ANIM_MarioW2_RideLaki)
    Wait(7)
    Call(SetPlayerAnimation, ANIM_Mario1_Idle)
    // increment channel
    Add(AB_NOK01_RadioStation, 1)
    IfGe(AB_NOK01_RadioStation, RADIO_STATION_COUNT)
        Set(AB_NOK01_RadioStation, 0)
    EndIf
    // skip HOT_HITS if not unlocked
    IfNe(GF_MAC05_SimonGotMelody, true)
        IfEq(AB_NOK01_RadioStation, RADIO_STATION_HOT_HITS)
            Add(AB_NOK01_RadioStation, 1)
        EndIf
    EndIf
    Call(N(SetRadioStation), AB_NOK01_RadioStation)
    Switch(AB_NOK01_RadioStation)
        CaseEq(RADIO_STATION_ISLAND_SOUNDS)
            Call(ShowMessageAtScreenPos, MSG_CH1_002F, 160, 40)
        CaseEq(RADIO_STATION_GOLDEN_OLDIES)
            Call(ShowMessageAtScreenPos, MSG_CH1_0030, 160, 40)
        CaseEq(RADIO_STATION_HOT_HITS)
            Call(ShowMessageAtScreenPos, MSG_CH1_0031, 160, 40)
        CaseEq(RADIO_STATION_INFORMATION)
            Call(ShowMessageAtScreenPos, MSG_CH1_0032, 160, 40)
            ExecWait(N(EVS_InitiateTradingEvent))
    EndSwitch
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript N(EVS_SetupRadio) = {
    BindTrigger(Ref(N(EVS_Interact_Radio)), TRIGGER_WALL_PRESS_A, COLLIDER_o235, 1, 0)
    Return
    End
};
