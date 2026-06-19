#include "mac_05.h"

EvtScript N(EVS_SetDoorRot_Club64) = {
    Call(RotateModel, MODEL_o80, LVar0, 0, -1, 0)
    Return
    End
};

EvtScript N(EVS_SetWallRot_Club64) = {
    Set(LVar1, LVar0)
    Call(RotateModel, MODEL_o95, LVar1, 1, 0, 0)
    Call(RotateModel, MODEL_o96, LVar1, 1, 0, 0)
    Call(RotateModel, MODEL_o98, LVar1, 1, 0, 0)
    Call(RotateModel, MODEL_o99, LVar1, 1, 0, 0)
    Call(RotateModel, MODEL_o100, LVar1, 1, 0, 0)
    Call(RotateModel, MODEL_o101, LVar1, 1, 0, 0)
    Call(RotateModel, MODEL_o102, LVar1, 1, 0, 0)
    Call(RotateModel, MODEL_o104, LVar1, 1, 0, 0)
    Set(LVar1, LVar0)
    Call(RotateModel, MODEL_o133, LVar1, 1, 0, 0)
    Call(RotateModel, MODEL_o134, LVar1, 1, 0, 0)
    Call(RotateModel, MODEL_o137, LVar1, 1, 0, 0)
    Set(LVar1, LVar0)
    MulF(LVar1, Float(-1.0))
    Call(RotateModel, MODEL_o82, LVar1, 1, 0, 0)
    Call(RotateModel, MODEL_o83, LVar1, 1, 0, 0)
    Call(RotateModel, MODEL_o84, LVar1, 1, 0, 0)
    Call(RotateModel, MODEL_o136, LVar1, 1, 0, 0)
    Call(RotateModel, MODEL_o81, LVar1, 1, 0, 0)
    Call(RotateModel, MODEL_o135, LVar1, 1, 0, 0)
    Return
    End
};

EvtScript N(EVS_DropDoor_Club64) = {
    Call(RotateModel, MODEL_o80, LVar0, 1, 0, 0)
    Return
    End
};

EvtScript N(EVS_RoomListener_Club64) = {
    Switch(LVar0)
        CaseEq(0)
            Call(SetMusic, 0, SONG_CLUB64, 0, VOL_LEVEL_FULL)
            Call(StopSound, SOUND_LOOP_MAC_HARBOR_WATER)
            Call(StopTrackingSoundPos, SOUND_LRAW_MAC_HARBOR_WATER)
            Call(EnableGroup, MODEL_bar_inn, true)
            Call(EnableModel, MODEL_o139, false)
            Call(EnableModel, MODEL_o140, false)
        CaseEq(3)
            Set(MF_DivaSongPlaying, false)
            Call(EnableGroup, MODEL_bar_inn, false)
            Call(EnableModel, MODEL_o139, true)
            Call(EnableModel, MODEL_o140, true)
            Wait(5)
            Exec(N(EVS_SetupMusic))
    EndSwitch
    Return
    End
};

s32 N(InsideNPCs_Club64)[] = {
    NPC_Toad_02,
    NPC_Bartender,
    NPC_Chanterelle,
    NPC_ArtistToad,
    NPC_TradeEventToad,
    -1
};

EvtScript N(EVS_SetupRooms) = {
    Call(CreateMapRoom,
        2,
        Ref(N(EVS_SetDoorRot_Club64)),
        Ref(N(EVS_SetWallRot_Club64)),
        Ref(N(EVS_DropDoor_Club64)),
        Ref(N(EVS_RoomListener_Club64)),
        COLLIDER_deilit1,
        COLLIDER_deilit1u,
        MODEL_harbour_club,
        Ref(N(InsideNPCs_Club64)))
    Set(LVar0, 3)
    Exec(N(EVS_RoomListener_Club64))
    Return
    End
};
