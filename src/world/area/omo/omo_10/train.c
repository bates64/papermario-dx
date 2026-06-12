#include "omo_10.h"

#include "../common/ToyTrain.inc.c"
#include "../common/TrainStationSwitches.inc.c"

#define TRAIN_STATION_ID  OMO_STATION_RED
#define TRAIN_ROUTE_LEFT  TRAIN_ROUTE_GREEN_RED
#define TRAIN_ROUTE_RIGHT TRAIN_ROUTE_RED_BLUE
#define TRAIN_COLLIDER COLLIDER_o961
#define TRAIN_ARRIVAL_MESSAGE MSG_CH4_0011
#define TRAIN_LEFT_THRESHOLD -350
#define TRAIN_RIGHT_THRESHOLD 350
#define TRAIN_LEFT_ENTRY omo_10_ENTRY_2
#define TRAIN_RIGHT_ENTRY omo_10_ENTRY_3

#include "../common/TrainStation.inc.c"

Vec2i N(TrainConductorPos) = {
    10, -105
};

s32 N(TrainPath_DepartRight)[] = {
    Float(-2.266),   Float(-209.494), Float(90.0),
    Float(124.202),  Float(-209.494), Float(262.5),
    Float(-245.336), Float(479.165),  Float(-503.546),
    -1, -1, -1
};

s32 N(TrainPath_DepartLeft)[] = {
    Float(-2.266),   Float(-209.494), Float(270.0),
    Float(-128.733), Float(-209.494), Float(-262.5),
    Float(-245.336), Float(-353.418), Float(-353.688),
    Float(-479.165), Float(-503.546),
    -1, -1, -1
};

s32 N(TrainPath_ArriveRight)[] = {
    Float(414.885),  Float(-426.942), Float(219.92),
    Float(353.553),  Float(-353.553), Float(262.5),
    Float(-245.336), Float(124.202),  Float(-209.494),
    Float(-42.27),   Float(-209.49),
    -1, -1, -1
};

s32 N(TrainPath_PassthroughRight)[] = {
    Float(414.885),  Float(-426.942), Float(219.92),
    Float(353.553),  Float(-353.553), Float(262.5),
    Float(-245.336), Float(124.202),  Float(-209.494),
    Float(-128.733), Float(-209.494), Float(-262.5),
    Float(-245.336), Float(-353.418), Float(-353.688),
    Float(-479.165), Float(-503.546),
    -1, -1, -1
};

s32 N(TrainPath_ArriveLeft)[] = {
    Float(-414.885), Float(-426.942), Float(140.075),
    Float(-353.418), Float(-353.688), Float(-262.5),
    Float(-245.336), Float(-128.733), Float(-209.494),
    Float(37.73), Float(-209.49),
    -1, -1, -1
};

s32 N(TrainPath_PassthroughLeft)[] = {
    Float(-414.885), Float(-426.942), Float(140.075),
    Float(-353.418), Float(-353.688), Float(-262.5),
    Float(-245.336), Float(-128.733), Float(-209.494),
    Float(124.202),  Float(-209.494), Float(262.5),
    Float(-245.336), Float(479.165),  Float(-503.546),
    -1, -1, -1
};

s32 N(LeftStations)[] = {
    OMO_STATION_GREEN,
    OMO_STATION_PINK,
    OMO_STATION_BLUE,
};

s32 N(RightStations)[] = {
    OMO_STATION_BLUE,
    OMO_STATION_PINK,
    OMO_STATION_GREEN,
};

EvtScript N(EVS_Conductor_ChooseRoute) = {
    IfEq(MF_EitherSwitchPressed, false)
        Call(SpeakToPlayer, NPC_Conductor, ANIM_TrainToad_Talk, ANIM_TrainToad_Idle, 0, MSG_CH4_0006)
    Else
        IfEq(AF_OMO_UsingRightSwitch, false)
            Call(SpeakToPlayer, NPC_Conductor, ANIM_TrainToad_Talk, ANIM_TrainToad_Idle, 0, MSG_CH4_0007)
            Call(ShowChoice, MSG_Choice_0043)
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
        Else
            Call(SpeakToPlayer, NPC_Conductor, ANIM_TrainToad_Talk, ANIM_TrainToad_Idle, 0, MSG_CH4_0007)
            Call(ShowChoice, MSG_Choice_0042)
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
        EndIf
    EndIf
    Return
    End
};

s32 N(TrainPath_Idle)[] = {
    Float(-2.266), Float(-209.494), Float(90.0),
    -1, -1, -1
};
