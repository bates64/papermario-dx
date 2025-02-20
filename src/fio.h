#include "common.h"
#include "dx/versioning.h"

b32 fio_load_globals(void);
b32 fio_save_globals(void);
b32 fio_load_game(s32 saveSlot);
void fio_save_game(s32 saveSlot);
void fio_erase_game(s32 saveSlot);

extern SaveFileSummary gSaveSlotSummary[4];
extern SaveSlotMetadata gSaveSlotMetadata[4];
extern SaveGlobals gSaveGlobals;
