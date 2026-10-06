#include "sam_02.h"

EvtScript EVS_SetDoorRot_LeftHouse = {
    Call(RotateModel, MODEL_c_doa, LVar0, 0, -1, 0)
    Return
    End
};

EvtScript EVS_SetWallRot_LeftHouse = {
    Call(RotateGroup, MODEL_mc_sita, LVar0, 1, 0, 0)
    IfGt(LVar0, 89)
        Call(SetGroupVisibility, MODEL_mc_sita, MODEL_GROUP_HIDDEN)
    EndIf
    IfLt(LVar0, 89)
        Call(SetGroupVisibility, MODEL_mc_sita, MODEL_GROUP_VISIBLE)
    EndIf
    Return
    End
};

EvtScript EVS_DropDoor_LeftHouse = {
    Call(RotateModel, MODEL_c_doa, LVar0, 1, 0, 0)
    Return
    End
};

EvtScript EVS_RoomListener_LeftHouse = {
    Switch(LVar0)
        CaseEq(ROOM_UPDATE_ENTER_BEGIN)
            Set(AF_SAM_Snowing, false)
            Call(SetGroupVisibility, MODEL_m_naiso, MODEL_GROUP_VISIBLE)
        CaseEq(ROOM_UPDATE_EXIT_END)
            Set(AF_SAM_Snowing, true)
            Call(SetGroupVisibility, MODEL_m_naiso, MODEL_GROUP_HIDDEN)
    EndSwitch
    Return
    End
};

EvtScript EVS_SetDoorRot_Shop = {
    Call(RotateModel, MODEL_o382, LVar0, 0, -1, 0)
    Return
    End
};

EvtScript EVS_SetWallRot_Shop = {
    Call(RotateGroup, MODEL_t_ue, LVar0, 0, 0, 1)
    Call(RotateGroup, MODEL_t_sita, LVar0, 0, 0, -1)
    IfGt(LVar0, 89)
        Call(SetGroupVisibility, MODEL_t_sita, MODEL_GROUP_HIDDEN)
    EndIf
    IfLt(LVar0, 89)
        Call(SetGroupVisibility, MODEL_t_sita, MODEL_GROUP_VISIBLE)
    EndIf
    Return
    End
};

EvtScript EVS_RoomListener_Shop = {
    Switch(LVar0)
        CaseEq(ROOM_UPDATE_ENTER_BEGIN)
            Set(AF_SAM_Snowing, false)
            Call(SetGroupVisibility, MODEL_t_naiso, MODEL_GROUP_VISIBLE)
        CaseEq(ROOM_UPDATE_EXIT_BEGIN)
            Switch(GB_StoryProgress)
                CaseLt(STORY_CH7_MAYOR_MURDER_MYSTERY)
                CaseLt(STORY_CH7_MAYOR_MURDER_SOLVED)
                CaseGe(STORY_CH7_MAYOR_MURDER_SOLVED)
            EndSwitch
        CaseEq(ROOM_UPDATE_EXIT_END)
            Set(AF_SAM_Snowing, true)
            Call(SetGroupVisibility, MODEL_t_naiso, MODEL_GROUP_HIDDEN)
    EndSwitch
    Return
    End
};

EvtScript EVS_SetDoorRot_ToadHouse = {
    Call(RotateModel, MODEL_k_doa, LVar0, 0, -1, 0)
    Return
    End
};

EvtScript EVS_SetWallRot_ToadHouse = {
    Call(RotateGroup, MODEL_mk_ue, LVar0, 0, 0, 1)
    Call(RotateGroup, MODEL_mk_sita, LVar0, 0, 0, -1)
    IfGt(LVar0, 89)
        Call(SetGroupVisibility, MODEL_mk_sita, MODEL_GROUP_HIDDEN)
    EndIf
    IfLt(LVar0, 89)
        Call(SetGroupVisibility, MODEL_mk_sita, MODEL_GROUP_VISIBLE)
    EndIf
    Return
    End
};

EvtScript EVS_RoomListener_ToadHouse = {
    Switch(LVar0)
        CaseEq(ROOM_UPDATE_ENTER_BEGIN)
            Set(AF_SAM_Snowing, false)
            Call(SetGroupVisibility, MODEL_k_naisou, MODEL_GROUP_VISIBLE)
        CaseEq(ROOM_UPDATE_EXIT_END)
            Set(AF_SAM_Snowing, true)
            Call(SetGroupVisibility, MODEL_k_naisou, MODEL_GROUP_HIDDEN)
    EndSwitch
    Return
    End
};

s32 InteriorNPCs_LeftHouse[] = {
    NPC_Penguin_02,
    -1
};

s32 InteriorNPCs_Shop[] = {
    NPC_Penguin_ShopOwner,
    -1
};

s32 InteriorNPCs_ToadHouse[] = {
    NPC_ShiverToad,
    -1
};

EvtScript EVS_SetupRooms = {
    // left house
    Call(SetGroupVisibility, MODEL_m_naiso, MODEL_GROUP_HIDDEN)
    Call(CreateMapRoom,
        PACK_ROOM_FLAGS(VIS_GROUP_0, ROOM_DOOR_LEFT_HINGE_OPENS_OUT),
        Ref(EVS_SetDoorRot_LeftHouse),
        Ref(EVS_SetWallRot_LeftHouse),
        Ref(EVS_DropDoor_LeftHouse),
        Ref(EVS_RoomListener_LeftHouse),
        COLLIDER_c_doa,
        COLLIDER_o470,
        MODEL_min,
        Ref(InteriorNPCs_LeftHouse))
    // shop
    Call(SetGroupVisibility, MODEL_t_naiso, MODEL_GROUP_HIDDEN)
    Call(CreateMapRoom,
        PACK_ROOM_FLAGS(VIS_GROUP_1, ROOM_DOOR_LEFT_HINGE_OPENS_OUT),
        Ref(EVS_SetDoorRot_Shop),
        Ref(EVS_SetWallRot_Shop),
        nullptr,
        Ref(EVS_RoomListener_Shop),
        COLLIDER_o382,
        COLLIDER_o471,
        MODEL_ten,
        Ref(InteriorNPCs_Shop))
    // toad house
    Call(SetGroupVisibility, MODEL_k_naisou, MODEL_GROUP_HIDDEN)
    Call(CreateMapRoom,
        PACK_ROOM_FLAGS(VIS_GROUP_0, ROOM_DOOR_LEFT_HINGE_OPENS_OUT),
        Ref(EVS_SetDoorRot_ToadHouse),
        Ref(EVS_SetWallRot_ToadHouse),
        nullptr,
        Ref(EVS_RoomListener_ToadHouse),
        COLLIDER_k_doa,
        COLLIDER_o472,
        MODEL_kino,
        Ref(InteriorNPCs_ToadHouse))
    Return
    End
};
