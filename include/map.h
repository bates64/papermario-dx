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
    /* 0x0C */ PAD(4);
    /* 0x10 */ EvtScript* main;
    /* 0x14 */ EntryList* entryList;
    /* 0x18 */ s32 entryCount;
    /* 0x1C */ PAD(12);
    /* 0x28 */ char** modelNameList;
    /* 0x2C */ char** colliderNameList;
    /* 0x30 */ char** zoneNameList;
    /* 0x34 */ PAD(4);
    /* 0x38 */ const char* bgName;
    /* 0x3C */ union {
    /*      */ s32 msgID;
    /*      */ s32 (*get)(void);
    /* 0x3C */ } tattle;
    /* 0x40 */ const char* textureArchive;
    /* 0x44 */ s8 songVariation; ///< 0 or 1. @see bgm_get_map_default_variation
    /* 0x45 */ s8 sfxReverb;
    /* 0x46 */ PAD(2);
} MapSettings; // size = 0x48

/// Define the descriptor exported by a map overlay.
#define OVL_DEF_MAP() export MapSettings settings

typedef struct AreaConfig {
    s32 mapCount;
    const char* const* maps;
    char* id; ///< "area_xxx"
} AreaConfig;

MapSettings* get_current_map_settings(void);

/// The size of a name in the map filesystem, with its terminator, such as w_kmr_02_shape. tools/build/mapfs/combine.py
/// writes names this size.
#define ASSET_NAME_MAX 32

extern char wMapTexName[ASSET_NAME_MAX];
extern char wMapHitName[ASSET_NAME_MAX];
extern char wMapShapeName[ASSET_NAME_MAX];
extern char wMapBgName[ASSET_NAME_MAX];
extern const char* wMapName;

/// Zero-terminated.
extern AreaConfig gAreas[];

extern EvtScript EVS_NpcHitRecoil;

#endif
