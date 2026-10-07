#pragma once

/// @file obk_08.h
/// @brief Boo's Mansion - Record Room

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../obk.h"
#include "map.xml.h"

#include "sprite/npc/Boo.h"

enum {
    NPC_HiddenBoo           = 0,
    NPC_KeepAwayBoo1        = 1,
    NPC_KeepAwayBoo2        = 2,
    NPC_KeepAwayBoo3        = 3,
    NPC_KeepAwayBoo4        = 4,
    NPC_KeepAwayBoo5        = 5,
    NPC_KeepAwayBoo6        = 6,
    NPC_KeepAwayBoo7        = 7,
    NPC_KeepAwayBoo8        = 8,
    NPC_TrafficBoo1         = 9,
    NPC_TrafficBoo2         = 10,
    NPC_LeaderBoo           = 11,
    NPC_DummyBoo            = 12, // for the item being thrown
};

enum {
    MV_KeepAwayItem         = MapVar(0),
    MV_KeepAwayRingReady    = MapVar(1),
    MV_KeepAwayRingPaused   = MapVar(2),
    MV_ThrowTargetNpc       = MapVar(3),
    MV_KeepAwayResult       = MapVar(4),
    MV_LeaderBooThrowYaw    = MapVar(5),
    MV_ItemCarrierNpc       = MapVar(6),
    MV_KnockdownPosX        = MapVar(7),
    MV_KnockdownPosY        = MapVar(8),
    MV_KnockdownPosZ        = MapVar(9),
    MV_WindowsIdle          = MapVar(11),
    MV_Trigger_NearCabinet  = MapVar(12),
    MV_Trigger_MidCabinet   = MapVar(13),
    MV_Trigger_FarCabinet   = MapVar(14),
};

enum KeepAwayResult {
    KEEP_AWAY_WAITING   = 0,
    KEEP_AWAY_RIGHT     = 1,
    KEEP_AWAY_WRONG     = 2,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_ManageWindows;
extern EvtScript EVS_SetupCabinets;
extern EvtScript EVS_BindCabinetTriggers;
extern EvtScript EVS_Scene_BoosUnleashed;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
