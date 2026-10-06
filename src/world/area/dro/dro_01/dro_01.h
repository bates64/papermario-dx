#pragma once

/// @file dro_01.h
/// @brief Dry Dry Outpost - Outpost 1

#include "common.h"
#include "message_ids.h"
#include "map.h"

#include "../dro.h"
#include "mapfs/dro_01_shape.h"
#include "mapfs/dro_01_hit.h"

#include "sprite/npc/WorldParakarry.h"
#include "sprite/npc/Mouser.h"
#include "sprite/npc/Dryite.h"
#include "sprite/npc/Toadette.h"

enum {
    NPC_Mouser_01               = 0,
    NPC_Dryite_01               = 1,
    NPC_Dryite_02               = 2,
    NPC_Dryite_03               = 3,
    NPC_Dryite_04               = 4,
    NPC_ArtistToad              = 5,
    NPC_Mouser_ShopOwner        = 6,
    NPC_Toadette_01             = 7,
    NPC_Toadette_02             = 8,
    NPC_Toadette_03             = 9,
    NPC_ChuckQuizmo             = 10,
    NPC_Dryite_05               = 11,
    NPC_Dryite_06               = 12,
};

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_SetupFoliage;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;
extern NpcGroupList Chapter3NPCs;

extern EvtScript EVS_SetupRooms;
extern EvtScript EVS_OpenShopDoor;
extern EvtScript EVS_CloseShopDoor;
extern EvtScript EVS_ShopSignSwing;

extern ShopItemData ShopInventory[];
extern ShopSellPriceData ShopPriceList[];
extern ShopItemLocation ShopItemPositions[];
extern ShopOwner MouserShopOwner;
