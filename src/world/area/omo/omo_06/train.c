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

Vec2i N(ConductorPos) = {
    50, 45
};

TrainPath N(TrainPath_DepartRight)[] = {
    TRAIN_PATH_BEGIN(-1.825, -35.275, 66.038),
    TRAIN_PATH_POINT(162.917, -108.494),
    TRAIN_PATH_POINT(353.442, -353.717),
    TRAIN_PATH_POINT(414.885, -426.942),
    TRAIN_PATH_END
};

TrainPath N(TrainPath_DepartLeft)[] = {
    TRAIN_PATH_BEGIN(-1.825, -35.275, 246.038),
    TRAIN_PATH_POINT(-166.506, 37.917),
    TRAIN_PATH_POINT(-500.0, 0.279),
    TRAIN_PATH_POINT(-600.0, 0.558),
    TRAIN_PATH_END
};

TrainPath N(TrainPath_ArriveRight)[] = {
    TRAIN_PATH_BEGIN(414.885, -426.942, 219.925),
    TRAIN_PATH_POINT(353.442, -353.717),
    TRAIN_PATH_POINT(162.917, -108.494),
    TRAIN_PATH_POINT(-38.38, -19.05),
    TRAIN_PATH_END
};

TrainPath N(TrainPath_PassthroughRight)[] = {
    TRAIN_PATH_BEGIN(414.885, -426.942, 219.925),
    TRAIN_PATH_POINT(353.442, -353.717),
    TRAIN_PATH_POINT(162.917, -108.494),
    TRAIN_PATH_POINT(-166.506, 37.917),
    TRAIN_PATH_POINT(-500.0, 0.279),
    TRAIN_PATH_POINT(-600.0, 0.558),
    TRAIN_PATH_END
};

TrainPath N(TrainPath_ArriveLeft)[] = {
    TRAIN_PATH_BEGIN(-600.0, 0.558, 89.875),
    TRAIN_PATH_POINT(-500.0, 0.279),
    TRAIN_PATH_POINT(-166.506, 37.917),
    TRAIN_PATH_POINT(34.74, -51.5),
    TRAIN_PATH_END
};

TrainPath N(TrainPath_PassthroughLeft)[] = {
    TRAIN_PATH_BEGIN(-600.0, 0.558, 89.875),
    TRAIN_PATH_POINT(-500.0, 0.279),
    TRAIN_PATH_POINT(-166.506, 37.917),
    TRAIN_PATH_POINT(162.917, -108.494),
    TRAIN_PATH_POINT(353.442, -353.717),
    TRAIN_PATH_POINT(414.885, -426.942),
    TRAIN_PATH_END
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
                    Set(AB_OMO_TrainDest, LVar1)
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
                    Set(AB_OMO_TrainDest, LVar1)
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
                        Set(AB_OMO_TrainDest, LVar1)
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
                        Set(AB_OMO_TrainDest, LVar1)
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

TrainPath N(TrainPath_Idle)[] = {
    TRAIN_PATH_BEGIN(-1.825, -35.275, 66.038),
    TRAIN_PATH_END
};
