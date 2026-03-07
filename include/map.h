#ifndef _MAP_H_
#define _MAP_H_

#include "common_structs.h"
#include "enums.h"
#include "world/entrances.h"
#include "script_api/map.h"
#include "npc.h"

#define CLONED_MODEL(idx)       (10000+(idx))

// TODO: consider moving Npc here

#define ENTRY_COUNT(entryList) (sizeof(entryList) / sizeof(Vec4f))
typedef Vec4f EntryList[];

/// Fields other than main, entryList, entryCount, bgName, tattle, textureArchive,
/// songVariation, and sfxReverb are initialised when the map loads.
typedef struct MapSettings {
    /* 0x00 */ struct ModelNode* modelTreeRoot;
    /* 0x04 */ s32 hitAssetCollisionOffset;
    /* 0x08 */ s32 hitAssetZoneOffset;
    /* 0x0C */ char unk_0C[4];
    /* 0x10 */ EvtScript* main;
    /* 0x14 */ EntryList* entryList;
    /* 0x18 */ s32 entryCount;
    /* 0x1C */ char unk_1C[12];
    /* 0x28 */ char** modelNameList;
    /* 0x2C */ char** colliderNameList;
    /* 0x30 */ char** zoneNameList;
    /* 0x34 */ char unk_34[4];
    /* 0x38 */ const char* bgName;
    /* 0x3C */ union {
        s32 msgID;
        s32 (*get)(void);
    } tattle;
    const char* textureArchive;
    s8 songVariation; ///< 0 or 1. @see bgm_get_map_default_variation
    s8 sfxReverb;
} MapSettings;

typedef struct MapConfig {
    char* id;
} MapConfig;

typedef struct AreaConfig {
    s32 mapCount;
    MapConfig* maps;
    char* id; ///< "area_xxx"
} AreaConfig;

MapSettings* get_current_map_settings(void);

extern char wMapTexName[];
extern char wMapHitName[];
extern char wMapShapeName[];
extern char wMapBgName[];

/// Zero-terminated.
extern AreaConfig gAreas[];

extern EvtScript EVS_NpcHitRecoil;
extern EvtScript EVS_800936C0;

#endif
