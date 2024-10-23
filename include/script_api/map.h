#ifndef _SCRIPT_API_MAP_H_
#define _SCRIPT_API_MAP_H_

#include "common_structs.h"
#include "evt.h"

#include "script_api/common.h"

#ifdef _LANGUAGE_C_PLUS_PLUS
extern "C" {
#endif

API_CALLABLE(MakeNpcs);
API_CALLABLE(BasicAI_Main);
API_CALLABLE(ResetFromLava);
API_CALLABLE(MakeShop);
API_CALLABLE(MakeShopOwner);
API_CALLABLE(CreateMapRoom);
API_CALLABLE(CheckActionState);
API_CALLABLE(CreatePushBlockGrid);
API_CALLABLE(SetPushBlock);
API_CALLABLE(GetPushBlock);

/// @evtapi
/// Fill a row of a `PushBlockGrid` from startZ to endZ (inclusive) along constant gridX
/// @param gridSystemID
/// @param gridX fixed x grid cell
/// @param startZ first z grid cell to be filled
/// @param endZ last z grid cell to be filled
/// @param occupant `PushGridOccupant` to fill with, be wary of placing too many PUSH_GRID_BLOCK
API_CALLABLE(FillPushBlockX);

/// @evtapi
/// Fill a row of a `PushBlockGrid` from startX to endX (inclusive) along constant gridZ
/// @param gridSystemID
/// @param gridZ fixed z grid cell
/// @param startX first x grid cell to be filled
/// @param endX last x grid cell to be filled
/// @param occupant `PushGridOccupant` to fill with, be wary of placing too many PUSH_GRID_BLOCK
API_CALLABLE(FillPushBlockZ);

API_CALLABLE(GetGridIndexFromPos);
API_CALLABLE(SetPushBlockFallEffect);
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
}
#endif

#endif
