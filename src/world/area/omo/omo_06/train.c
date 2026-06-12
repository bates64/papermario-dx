#include "omo_06.h"

#include "../common/ToyTrain.inc.c"
#include "../common/TrainStationSwitches.inc.c"

#define TRAIN_STATION_ID  OMO_STATION_PINK
#define TRAIN_ROUTE_LEFT  TRAIN_ROUTE_BLUE_PINK
#define TRAIN_ROUTE_RIGHT TRAIN_ROUTE_PINK_GREEN
#define TRAIN_COLLIDER COLLIDER_o898
#define TRAIN_ARRIVAL_MESSAGE MSG_CH4_000F
#define TRAIN_LEFT_THRESHOLD -480
#define TRAIN_RIGHT_THRESHOLD 350
#define TRAIN_LEFT_ENTRY omo_06_ENTRY_2
#define TRAIN_RIGHT_ENTRY omo_06_ENTRY_3

#include "../common/TrainStation.inc.c"

Vec2i N(TrainConductorPos) = {
    50, 45
};

s32 N(TrainPath_DepartRight)[] = {
    Float(-1.825), Float(-35.275), Float(66.038),
    Float(162.917), Float(-108.494), Float(353.442),
    Float(-353.717), Float(414.885), Float(-426.942),
    -1, -1, -1
};

s32 N(TrainPath_DepartLeft)[] = {
    Float(-1.825), Float(-35.275), Float(246.038),
    Float(-166.506), Float(37.917), Float(-500.0),
    Float(0.279), Float(-600.0), Float(0.558),
    -1, -1, -1
};

s32 N(TrainPath_ArriveRight)[] = {
    Float(414.885),  Float(-426.942), Float(219.925),
    Float(353.442),  Float(-353.717), Float(162.917),
    Float(-108.494), Float(-38.38),   Float(-19.05),
    -1, -1, -1
};

s32 N(TrainPath_PassthroughRight)[] = {
    Float(414.885), Float(-426.942), Float(219.925),
    Float(353.442), Float(-353.717), Float(162.917),
    Float(-108.494), Float(-166.506), Float(37.917),
    Float(-500.0), Float(0.279), Float(-600.0),
    Float(0.558),  -1, -1, -1
};

s32 N(TrainPath_ArriveLeft)[] = {
    Float(-600.0), Float(0.558), Float(89.875),
    Float(-500.0), Float(0.279), Float(-166.506),
    Float(37.917), Float(34.74), Float(-51.5),
    -1, -1, -1
};

s32 N(TrainPath_PassthroughLeft)[] = {
    Float(-600.0), Float(0.558), Float(89.875),
    Float(-500.0), Float(0.279), Float(-166.506),
    Float(37.917), Float(162.917), Float(-108.494),
    Float(353.442), Float(-353.717), Float(414.885),
    Float(-426.942),
    -1, -1, -1
};

s32 N(LeftStations)[] = {
    OMO_STATION_BLUE,
    OMO_STATION_RED,
    OMO_STATION_GREEN,
};

s32 N(RightStations)[] = {
    OMO_STATION_GREEN,
    OMO_STATION_RED,
    OMO_STATION_BLUE,
};

EvtScript N(EVS_Conductor_ChooseRoute) = {
    IfEq(MF_EitherSwitchPressed, false)
        Call(SpeakToPlayer, NPC_Conductor, ANIM_TrainToad_Talk, ANIM_TrainToad_Idle, 0, MSG_CH4_0006)
    Else
        IfEq(AF_OMO_UsingRightSwitch, false)
            Call(SpeakToPlayer, NPC_Conductor, ANIM_TrainToad_Talk, ANIM_TrainToad_Idle, 0, MSG_CH4_0007)
            IfEq(GF_OMO03_BlueSwitchActivated, false)
                Call(ShowChoice, MSG_Choice_003D)
                IfNe(LVar0, 1)
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
            Else
                Call(ShowChoice, MSG_Choice_003E)
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
            Switch(GB_StoryProgress)
                CaseLt(STORY_CH4_PULLED_SWITCH_SWITCH)
                    Call(SpeakToPlayer, NPC_Conductor, ANIM_TrainToad_SadTalk, ANIM_TrainToad_SadIdle, 0, MSG_CH4_0012)
                CaseLt(STORY_CH4_SOLVED_COLOR_PUZZLE)
                    Call(SpeakToPlayer, NPC_Conductor, ANIM_TrainToad_Talk, ANIM_TrainToad_Idle, 0, MSG_CH4_0007)
                    Call(ShowChoice, MSG_Choice_003B)
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
                CaseGe(STORY_CH4_SOLVED_COLOR_PUZZLE)
                    Call(SpeakToPlayer, NPC_Conductor, ANIM_TrainToad_Talk, ANIM_TrainToad_Idle, 0, MSG_CH4_0007)
                    Call(ShowChoice, MSG_Choice_003C)
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
    Float(-1.825), Float(-35.275), Float(66.038),
    -1, -1, -1
};
