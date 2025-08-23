#include "types.h"
#include "include_asset.h"

s32 ResetGameState = 0;
u16* ResetSavedFrameImg = nullptr;
s16 D_80073E08 = 0;
s16 D_80073E0A = 0;

INCLUDE_IMG("reset_tiles.png", ResetTilesImg);
