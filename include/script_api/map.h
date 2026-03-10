#ifndef _SCRIPT_API_MAP_H_
#define _SCRIPT_API_MAP_H_

#include "common_structs.h"
#include "evt.h"

#include "script_api/common.h"

#ifdef _LANGUAGE_C_PLUS_PLUS
extern "C" {
#endif

/// @evtapi
/// @param aiSettingsPtr
API_CALLABLE(BasicAI_Main);

/// @evtapi
/// @param itemPositionsPtr
/// @param inventoryPtr
/// @param sellPricesPtr
/// @param inventoryItemFlagsPtr
API_CALLABLE(MakeShop);

/// @evtapi
/// @param shopOwnerPtr
API_CALLABLE(MakeShopOwner);

/// @evtapi
/// @param packedFlags
/// @param openDoorScript
/// @param moveWallsScript
/// @param dropDoorScript
/// @param stateListenerScript
/// @param doorInColliderID
/// @param doorOutColliderID
/// @param interiorModelGroup
/// @param interiorNPCList
API_CALLABLE(CreateMapRoom);

/// @evtapi
/// @param outResult
/// @param actionState
API_CALLABLE(CheckActionState);

/// @evtapi
/// @param blockSystemID
/// @param sizeNx
/// @param sizeNz
/// @param centerX
/// @param centerY
/// @param centerZ
/// @param inputGridDataPtr
API_CALLABLE(CreatePushBlockGrid);

/// @evtapi
/// @param blockSystemID
/// @param gridX
/// @param gridZ
/// @param occupant
API_CALLABLE(SetPushBlock);

/// @evtapi
/// @param blockSystemID
/// @param gridX
/// @param gridZ
/// @param outOccupant
API_CALLABLE(GetPushBlock);

/// Fill a row of a [`PushBlockGrid`] from `startZ` to `endZ` (inclusive) along constant `gridX`.
/// Be wary of placing too many `PUSH_GRID_BLOCK` occupants.
/// @evtapi
/// @param gridSystemID
/// @param gridX
/// @param startZ
/// @param endZ
/// @param occupant
API_CALLABLE(FillPushBlockX);

/// Fill a row of a [`PushBlockGrid`] from `startX` to `endX` (inclusive) along constant `gridZ`.
/// Be wary of placing too many `PUSH_GRID_BLOCK` occupants.
/// @evtapi
/// @param gridSystemID
/// @param gridZ
/// @param startX
/// @param endX
/// @param occupant
API_CALLABLE(FillPushBlockZ);

/// @evtapi
/// @param blockSystemID
/// @param posX
/// @param posY
/// @param posZ
/// @param outGridX
/// @param outGridZ
API_CALLABLE(GetGridIndexFromPos);

/// @evtapi
/// @param blockSystemID
/// @param fallCallback
API_CALLABLE(SetPushBlockFallEffect);

/// @evtapi
API_CALLABLE(TeleportPartnerToPlayer);

extern EvtScript EnterWalk;
extern EvtScript EnterWalkShort;
extern EvtScript EnterSavePoint;
extern EvtScript ExitWalk;
extern EvtScript ExitSingleDoor;
extern EvtScript EnterSingleDoor;
extern EvtScript ExitSplitSingleDoor;
extern EvtScript EnterSplitSingleDoor;
extern EvtScript ExitDoubleDoor;
extern EvtScript EnterDoubleDoor;
extern EvtScript ExitSplitDoubleDoor;
extern EvtScript EnterSplitDoubleDoor;
extern EvtScript BaseExitDoor;
extern EvtScript BaseEnterDoor;
extern EvtScript EnterPostPipe;
extern EvtScript EVS_ShopOwnerDialog;

#ifdef _LANGUAGE_C_PLUS_PLUS
} // extern "C"
#endif

#endif
