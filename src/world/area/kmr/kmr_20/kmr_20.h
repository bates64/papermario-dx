#pragma once

/// @file kmr_20.h
/// @brief Goomba Region - Mario's House

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../kmr.h"
#include "map.xml.h"

#include "sprite/npc/Luigi.h"
#include "sprite/npc/Toad.h"
#include "sprite/npc/WorldParakarry.h"
#include "sprite/npc/ShyGuy.h"

enum {
    NPC_Scene_Parakarry         = 0,
    NPC_Scene_Luigi             = 1,

    NPC_Luigi_0                 = 0,
    NPC_Luigi_1                 = 1,
    NPC_ShyGuy                  = 2,
};

enum {
    MV_RecordsDataPtr           = MapVar(10),
};

enum {
    MF_LuigiWaiting             = MapFlag(10),
    MF_ReadyForPlayerEntry      = MapFlag(11),
    MF_HouseInteriorVisible     = MapFlag(12),
    MF_LuigiInBasement          = MapFlag(13),
};

extern EvtScript EVS_Main;
extern EvtScript EVS_FadeOutAmbientSounds;
extern EvtScript EVS_PlayRestingSong;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupRooms;
extern EvtScript EVS_Setup_Interactables;
extern EvtScript EVS_SetupBed;
extern EvtScript EVS_Scene_BeginGame;
extern EvtScript EVS_Scene_SettingOff;
extern EvtScript EVS_Scene_BeginEpilogue;
extern EvtScript EVS_Scene_EpilogueGetLetter;
extern EvtScript EVS_Scene_LuigiWaitingAround;
extern EvtScript EVS_Scene_CaughtLuigiInBasement;
extern EvtScript EVS_Inspect_Records;
extern EvtScript EVS_SecretPanel_Flip;
extern EvtScript EVS_SetupTrees;
extern EvtScript EVS_SetupBushes;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList SceneNPCs;
extern NpcGroupList DefaultNPCs;

API_CALLABLE(HideWorldOutsideMariosHouse);
API_CALLABLE(Pipe_GetEntryPos);
void msg_draw_frame(s32 posX, s32 posY, s32 sizeX, s32 sizeY, s32 style, s32 palette, s32 fading, s32 bgAlpha, s32 frameAlpha);
