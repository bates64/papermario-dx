#ifndef _FIO_H_
#define _FIO_H_

#include "common.h"
#include "dx/versioning.h"

b32 fio_load_globals(void);
b32 fio_save_globals(void);
b32 fio_load_game(s32 saveSlot);
void fio_save_game(s32 saveSlot);
void fio_erase_game(s32 saveSlot);
/// The first file with nothing saved in it, or -1 if every file has a save.
s32 fio_find_empty_slot(void);

extern SaveFileSummary gSaveSlotSummary[4];
extern SaveSlotMetadata gSaveSlotMetadata[4];
extern SaveGlobals gSaveGlobals;

#endif
