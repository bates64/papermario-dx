#ifndef _MAP_H_
#define _MAP_H_

#include "common_structs.h"
#include "enums.h"
#include "script_api/map.h"
#include "npc.h"

#define CLONED_MODEL(idx)       (10000+(idx))

// TODO: consider moving Npc here

#define ENTRY_COUNT(entryList) (sizeof(entryList) / sizeof(Vec4f))
typedef Vec4f EntryList[];

/// The current map's settings, which the game fills in as it loads the map.
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
    /* 0x40 */ const char* textureArchive DEPRECATED("maps can use any texture, so this does nothing; delete it");
    /* 0x44 */ s8 songVariation; ///< 0 or 1. @see bgm_get_map_default_variation
    /* 0x45 */ s8 sfxReverb;
    /* 0x46 */ PAD(2);
} MapSettings; // size = 0x48

/// Define the settings a map overlay exports, in place of the ones the game takes from the map's EVS_Main and
/// features.json.
/// @deprecated Delete it, and set its background, tattle, and reverb in the map editor.
#define OVL_DEF_MAP() \
    _Pragma("GCC warning \"OVL_DEF_MAP is deprecated: delete it, and set its background, tattle, and reverb in the map editor\"") \
    export MapSettings settings

// The map editor's markers. A map's code gets each of its markers from map.xml.h, as a constant named after it with a
// `$` in front, such as `$Goompa`.

/// How map.xml.h declares markers, so their fields are constant expressions in C++ as well as in C.
#ifdef __cplusplus
#define MARKER_CONST static constexpr
#else
#define MARKER_CONST static const
#endif

typedef struct PositionMarker {
    Vec3f pos;
    f32 yaw;
} PositionMarker;

/// Where the player appears when they enter a map. Another map gets a map's entries as fields of a constant named after
/// it, such as `$kmr_03.Front`, by including that map's header, such as world/area/kmr/kmr_03.h.
typedef struct EntryMarker {
    const char* map;
    Vec3f pos;
    f32 yaw;
    s32 index; ///< Its place in the map's entry list, the entry ID GotoMap and GetEntryID use.
} EntryMarker;

typedef struct NpcMarker {
    Vec3f pos;
    f32 yaw;
    EnemyTerritory territory;
} NpcMarker;

enum EntityMarkerFlagKind {
    ENTITY_MARKER_FLAG_NONE,
    ENTITY_MARKER_FLAG_BLOCK,
    ENTITY_MARKER_FLAG_CHEST,
    ENTITY_MARKER_FLAG_PANEL,
    ENTITY_MARKER_FLAG_CRATE,
    ENTITY_MARKER_FLAG_SWITCH,
};

/// An entity or item for MakeMarkerEntity to make.
typedef struct EntityMarker {
    Vec3f pos;
    f32 yaw;
    EntityBlueprint* blueprint; ///< nullptr for an item
    s32 args[3]; ///< The blueprint's arguments, or an item's ID and spawn mode.
    EvtScript* script;
    s32 flag;
    u8 flagKind; ///< enum EntityMarkerFlagKind
} EntityMarker;

typedef struct SphereMarker {
    Vec3f pos;
    f32 radius;
} SphereMarker;

typedef struct CylinderMarker {
    Vec3f pos; ///< The center of its base.
    f32 radius;
    f32 height;
} CylinderMarker;

typedef struct VolumeMarker {
    Vec3f min;
    Vec3f max;
} VolumeMarker;

/// A camera setup for UseCamTarget to apply.
typedef struct CamTargetMarker {
    Vec3f pos;
    b8 useZone; ///< Take the settings from the camera zone under `pos`, instead of from `settings`.
    b8 overrideDist; ///< With `useZone`, replace the zone's boom length with `boomLength`.
    b8 overrideAngles; ///< With `useZone`, replace the zone's pitches with `boomPitch` and `viewPitch`.
    b8 pan; ///< Pan to `pos` at `panSpeed`, and wait until the camera arrives.
    f32 boomLength;
    f32 boomPitch;
    f32 viewPitch;
    f32 panSpeed;
    CameraControlSettings settings;
} CamTargetMarker;

typedef struct PathMarkerPoint {
    Vec3s pos;
    u16 nextCount;
    const u16* next; ///< The indices of the points it leads to.
} PathMarkerPoint;

/// Points that each lead to any number of others. The map's code gets the index of each named point as
/// `$<path>_<point>`, such as `$Route_Start`.
typedef struct PathMarker {
    s32 count;
    const PathMarkerPoint* points;
} PathMarker;

typedef struct AreaConfig {
    s32 mapCount;
    const char* const* maps;
    char* id; ///< "area_xxx"
} AreaConfig;

MapSettings* get_current_map_settings(void);

/// The size of a name in the map filesystem, with its terminator, such as w_kmr_02_shape. tools/build/mapfs/combine.py
/// writes names this size.
#define ASSET_NAME_MAX 32

extern char wMapTexName[ASSET_NAME_MAX] DEPRECATED(
    "maps can use any texture, so this does nothing; delete the code that sets it"
);
extern char wMapHitName[ASSET_NAME_MAX];
extern char wMapShapeName[ASSET_NAME_MAX];
extern char wMapBgName[ASSET_NAME_MAX];
extern const char* wMapName;

/// Loads the geometry of the map named mapName, such as kmr_02. A map that shares another's geometry calls this
/// from its map_init.
void use_map_geometry(const char* mapName);

/// Zero-terminated.
extern AreaConfig gAreas[];

extern EvtScript EVS_NpcHitRecoil;

#endif
