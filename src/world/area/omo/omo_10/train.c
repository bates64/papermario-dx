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

Vec2i N(ConductorPos) = {
    10, -105
};

TrainPath N(TrainPath_DepartRight)[] = {
    TRAIN_PATH_BEGIN(-2.266, -209.494, 90.0),
    TRAIN_PATH_POINT(124.202, -209.494),
    TRAIN_PATH_POINT(262.5, -245.336),
    TRAIN_PATH_POINT(479.165, -503.546),
    TRAIN_PATH_END
};

TrainPath N(TrainPath_DepartLeft)[] = {
    TRAIN_PATH_BEGIN(-2.266, -209.494, 270.0),
    TRAIN_PATH_POINT(-128.733, -209.494),
    TRAIN_PATH_POINT(-262.5, -245.336),
    TRAIN_PATH_POINT(-353.418, -353.688),
    TRAIN_PATH_POINT(-479.165, -503.546),
    TRAIN_PATH_END
};

TrainPath N(TrainPath_ArriveRight)[] = {
    TRAIN_PATH_BEGIN(414.885, -426.942, 219.92),
    TRAIN_PATH_POINT(353.553, -353.553),
    TRAIN_PATH_POINT(262.5, -245.336),
    TRAIN_PATH_POINT(124.202, -209.494),
    TRAIN_PATH_POINT(-42.27, -209.49),
    TRAIN_PATH_END
};

TrainPath N(TrainPath_PassthroughRight)[] = {
    TRAIN_PATH_BEGIN(414.885, -426.942, 219.92),
    TRAIN_PATH_POINT(353.553, -353.553),
    TRAIN_PATH_POINT(262.5, -245.336),
    TRAIN_PATH_POINT(124.202, -209.494),
    TRAIN_PATH_POINT(-128.733, -209.494),
    TRAIN_PATH_POINT(-262.5, -245.336),
    TRAIN_PATH_POINT(-353.418, -353.688),
    TRAIN_PATH_POINT(-479.165, -503.546),
    TRAIN_PATH_END
};

TrainPath N(TrainPath_ArriveLeft)[] = {
    TRAIN_PATH_BEGIN(-414.885, -426.942, 140.075),
    TRAIN_PATH_POINT(-353.418, -353.688),
    TRAIN_PATH_POINT(-262.5, -245.336),
    TRAIN_PATH_POINT(-128.733, -209.494),
    TRAIN_PATH_POINT(37.73, -209.49),
    TRAIN_PATH_END
};

TrainPath N(TrainPath_PassthroughLeft)[] = {
    TRAIN_PATH_BEGIN(-414.885, -426.942, 140.075),
    TRAIN_PATH_POINT(-353.418, -353.688),
    TRAIN_PATH_POINT(-262.5, -245.336),
    TRAIN_PATH_POINT(-128.733, -209.494),
    TRAIN_PATH_POINT(124.202, -209.494),
    TRAIN_PATH_POINT(262.5, -245.336),
    TRAIN_PATH_POINT(479.165, -503.546),
    TRAIN_PATH_END
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
                Set(AB_OMO_TrainDest, LVar1)
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
                Set(AB_OMO_TrainDest, LVar1)
                ExecWait(N(EVS_Train_DepartRight))
            Else
                Call(ContinueSpeech, NPC_Conductor, ANIM_TrainToad_Talk, ANIM_TrainToad_Idle, 0, MSG_CH4_0008)
            EndIf
        EndIf
    EndIf
    Return
    End
};

TrainPath N(TrainPath_Idle)[] = {
    TRAIN_PATH_BEGIN(-2.266, -209.494, 90.0),
    TRAIN_PATH_END
};
