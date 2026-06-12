#include "omo_08.h"

#include "../common/ToyTrain.inc.c"
#include "../common/TrainStationSwitches.inc.c"

#define TRAIN_STATION_ID  OMO_STATION_GREEN
#define TRAIN_ROUTE_LEFT  TRAIN_ROUTE_PINK_GREEN
#define TRAIN_ROUTE_RIGHT TRAIN_ROUTE_GREEN_RED
#define TRAIN_COLLIDER COLLIDER_o1074
#define TRAIN_ARRIVAL_MESSAGE MSG_CH4_0010
#define TRAIN_LEFT_THRESHOLD -350
#define TRAIN_RIGHT_THRESHOLD 350
#define TRAIN_LEFT_ENTRY omo_08_ENTRY_1
#define TRAIN_RIGHT_ENTRY omo_08_ENTRY_2

#include "../common/TrainStation.inc.c"

Vec2i N(TrainConductorPos) = {
    -145, -110
};

s32 N(TrainPath_DepartRight)[] = {
    Float(-131.227), Float(-210.271), Float(105.004),
    Float(0.0), Float(-175.0), Float(262.5),
    Float(-245.336), Float(479.165), Float(-503.546),
    -1, -1, -1
};

s32 N(TrainPath_DepartLeft)[] = {
    Float(-131.227), Float(-210.271), Float(285.004),
    Float(-262.5), Float(-245.336), Float(-353.418),
    Float(-353.688), Float(-479.165), Float(-503.546),
    -1, -1, -1
};

s32 N(TrainPath_ArriveRight)[] = {
    Float(414.885), Float(-426.942), Float(219.92),
    Float(353.553), Float(-353.553), Float(262.5),
    Float(-245.336), Float(0.0), Float(-175.0),
    Float(-169.87), Float(-220.59),
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

s32 N(TrainPath_ArriveLeft)[] = {
    Float(-414.885), Float(-426.942), Float(140.075),
    Float(-353.418), Float(-353.688), Float(-262.5),
    Float(-245.336), Float(-92.58), Float(-199.95),
    -1, -1, -1
};

s32 N(TrainPath_PassthroughLeft)[] = {
    Float(-414.885), Float(-426.942), Float(140.075),
    Float(-353.418), Float(-353.688), Float(-262.5),
    Float(-245.336), Float(0.0), Float(-175.0),
    Float(262.5), Float(-245.336), Float(479.165),
    Float(-503.546),
    -1, -1, -1
};

s32 N(LeftStations)[] = {
    OMO_STATION_PINK,
    OMO_STATION_BLUE,
    OMO_STATION_RED,
};

s32 N(RightStations)[] = {
    OMO_STATION_RED,
    OMO_STATION_BLUE,
    OMO_STATION_PINK,
};

EvtScript N(EVS_Conductor_ChooseRoute) = {
    IfEq(MF_EitherSwitchPressed, false)
        Call(SpeakToPlayer, NPC_Conductor, ANIM_TrainToad_Talk, ANIM_TrainToad_Idle, 0, MSG_CH4_0006)
    Else
        IfEq(AF_OMO_UsingRightSwitch, false)
            Call(SpeakToPlayer, NPC_Conductor, ANIM_TrainToad_Talk, ANIM_TrainToad_Idle, 0, MSG_CH4_0007)
            IfEq(GF_OMO03_BlueSwitchActivated, false)
                Call(ShowChoice, MSG_Choice_0040)
                IfNe(LVar0, 2)
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
                Call(ShowChoice, MSG_Choice_0041)
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
                CaseLt(STORY_CH4_SOLVED_COLOR_PUZZLE)
                    Call(SpeakToPlayer, NPC_Conductor, ANIM_TrainToad_SadTalk, ANIM_TrainToad_SadIdle, 0, MSG_CH4_0016)
                CaseGe(STORY_CH4_SOLVED_COLOR_PUZZLE)
                    Call(SpeakToPlayer, NPC_Conductor, ANIM_TrainToad_Talk, ANIM_TrainToad_Idle, 0, MSG_CH4_0007)
                    Call(ShowChoice, MSG_Choice_003F)
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
    Float(-131.227), Float(-210.271), Float(105.004),
    -1, -1, -1
};
