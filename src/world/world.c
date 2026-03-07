#include "common.h"
#include "ld_addrs.h"
#include "npc.h"
#include "hud_element.h"
#include "rumble.h"
#include "sprite.h"
#include "model.h"
#include <string.h>
#include "world/surfaces.h"
#include "dx/overlay.h"

#ifdef SHIFT
#define ASSET_TABLE_ROM_START (s32) mapfs_ROM_START
#elif VERSION_JP
#define ASSET_TABLE_ROM_START 0x1E00000
#else
#define ASSET_TABLE_ROM_START 0x1E40000
#endif

#define ASSET_TABLE_HEADER_SIZE 0x20
#define ASSET_TABLE_FIRST_ENTRY (ASSET_TABLE_ROM_START + ASSET_TABLE_HEADER_SIZE)

BSS MapConfig* gMapConfig;
BSS MapSettings gMapSettings;

char wMapHitName[0x18];
char wMapShapeName[0x18];
char wMapTexName[0x18];
char wMapBgName[0x14];

s32 WorldReverbModeMapping[] = { 0, 1, 2, 3 };

typedef struct {
    /* 0x00 */ char name[16];
    /* 0x10 */ u32 offset;
    /* 0x14 */ u32 compressedLength;
    /* 0x18 */ u32 decompressedLength;
} AssetHeader; // size = 0x1C

void fio_deserialize_state(void);
void load_map_hit_asset(void);

#if defined(SHIFT) || VERSION_IQUE
#define shim_general_heap_create_obfuscated general_heap_create
#endif

extern ShapeFile gMapShapeData;

void load_map_script_lib(void) {
    DMA_COPY_SEGMENT(world_script_api);
}

void load_map_by_IDs(s16 areaID, s16 mapID, s16 loadType) {
    s32 skipLoadingAssets = 0;
    MapConfig* mapConfig;
    s32 decompressedSize;

    ovl_unload_type(OVL_MAP);

    sfx_stop_env_sounds();
    gOverrideFlags &= ~GLOBAL_OVERRIDES_40;
    gOverrideFlags &= ~GLOBAL_OVERRIDES_ENABLE_FLOOR_REFLECTION;

    gGameStatusPtr->playerSpriteSet = PLAYER_SPRITES_MARIO_WORLD;
    surface_set_walk_effect(SURFACE_WALK_FX_STANDARD);
    phys_set_player_sliding_check(nullptr);
    phys_set_landing_adjust_cam_check(nullptr);

#if !VERSION_IQUE
    load_obfuscation_shims();
#endif
    shim_general_heap_create_obfuscated();

#if VERSION_JP
    reset_max_rumble_duration();
#endif
    clear_render_tasks();
    clear_worker_list();
    clear_script_list();

    switch (loadType) {
        case LOAD_FROM_MAP:
            clear_area_flags();
            gGameStatusPtr->loadType = LOAD_FROM_MAP;
            break;
        case LOAD_FROM_FILE_SELECT:
            fio_deserialize_state();
            areaID = gGameStatusPtr->areaID;
            mapID = gGameStatusPtr->mapID;
            gGameStatusPtr->prevArea = areaID;
            gGameStatusPtr->loadType = LOAD_FROM_FILE_SELECT;
            break;
    }

    gGameStatusPtr->mapShop = nullptr;

    ASSERT_MSG(gAreas[areaID].maps != nullptr, "Invalid area ID %d", areaID);
    ASSERT_MSG(mapID < gAreas[areaID].mapCount, "Invalid map ID %d in %s", mapID, gAreas[areaID].id);
    mapConfig = &gAreas[areaID].maps[mapID];

    #if DX_DEBUG_MENU
    dx_debug_set_map_info(mapConfig->id, gGameStatus.entryID);
    #endif

    sprintf(wMapShapeName, "%s_shape", mapConfig->id);
    sprintf(wMapHitName, "%s_hit", mapConfig->id);

    gMapConfig = mapConfig;
    load_map_script_lib();

    // TODO: don't use NAMESPACE in maps
    char symSettings[32];
    char symInit[32];
    sprintf(symSettings, "%s_settings", mapConfig->id);
    sprintf(symInit, "%s_map_init", mapConfig->id);

    Overlay* ovl = ovl_load(mapConfig->id, OVL_MAP);
    MapSettings* settings = ovl_import(ovl, symSettings);
    ASSERT_MSG(settings != nullptr, "Map '%s' does not export 'settings'", mapConfig->id);
    gMapSettings = *settings;

    if (gMapSettings.textureArchive != nullptr) {
        sprintf(wMapTexName, "%s_tex", gMapSettings.textureArchive);
    } else {
        char texStr[17];
        strcpy(texStr, mapConfig->id);
        texStr[3] = '\0';
        sprintf(wMapTexName, "%s_tex", texStr);
    }

    if (gMapSettings.bgName != nullptr) {
        strcpy(wMapBgName, gMapSettings.bgName);
    }

    s32 (*init)(void) = ovl_import(ovl, symInit);
    if (init != nullptr) {
        skipLoadingAssets = init();
    }

    if (!skipLoadingAssets) {
        ShapeFile* shapeFile = &gMapShapeData;
        void* yay0Asset = load_asset_by_name(wMapShapeName, &decompressedSize);

        decode_yay0(yay0Asset, shapeFile);
        general_heap_free(yay0Asset);

        gMapSettings.modelTreeRoot = shapeFile->header.root;
        gMapSettings.modelNameList = shapeFile->header.modelNames;
        gMapSettings.colliderNameList = shapeFile->header.colliderNames;
        gMapSettings.zoneNameList = shapeFile->header.zoneNames;
    }

    if (gMapSettings.bgName != nullptr) {
        load_map_bg(wMapBgName);
    }

#if !VERSION_IQUE
    load_obfuscation_shims();
#endif
    shim_general_heap_create_obfuscated();

    sfx_clear_env_sounds(0);
    clear_worker_list();
    clear_script_list();
    create_cameras();
    spr_init_sprites(gGameStatusPtr->playerSpriteSet);
    clear_animator_list();
    clear_entity_models();
    clear_npcs();
    hud_element_clear_cache();
    clear_trigger_data();
    clear_model_data();
    clear_sprite_shading_data();
    reset_background_settings();

    if (gGameStatusPtr->introPart == INTRO_PART_NONE) {
        reset_back_screen_overlay_progress();
    }

    if (!skipLoadingAssets) {
        initialize_collision();
        load_map_hit_asset();
    }

    reset_battle_status();
    clear_encounter_status();
    clear_entity_data(true);
    clear_effect_data();
    clear_player_status();
    player_reset_data();
    partner_reset_data();
    clear_printers();
    clear_item_entity_data();

    gPlayerStatus.targetYaw = gPlayerStatus.curYaw;

    sfx_set_reverb_mode(WorldReverbModeMapping[gMapSettings.sfxReverb & 0x3]);
    sfx_reset_door_sounds();

    if (!skipLoadingAssets) {
        s32 texturesOffset = get_asset_offset(wMapTexName, &decompressedSize);

        if (gMapSettings.modelTreeRoot != nullptr) {
            load_data_for_models(gMapSettings.modelTreeRoot, texturesOffset, decompressedSize);
        }
    }

    if (gMapSettings.bgName != nullptr) {
        set_background(&gBackgroundImage);
    } else {
        set_background_size(SCREEN_XMAX - SCREEN_XMIN, SCREEN_YMAX - SCREEN_YMIN,
            SCREEN_INSET_X, SCREEN_INSET_Y);
    }

    gCurrentCameraID = CAM_DEFAULT;
    gCameras[CAM_DEFAULT].flags |= CAMERA_FLAG_DISABLED;
    gCameras[CAM_BATTLE].flags |= CAMERA_FLAG_DISABLED;
    gCameras[CAM_TATTLE].flags |= CAMERA_FLAG_DISABLED;
    gCameras[CAM_HUD].flags |= CAMERA_FLAG_DISABLED;

    if (gGameStatusPtr->introPart == INTRO_PART_NONE) {
        set_cam_viewport(CAM_DEFAULT, 12, 20, 296, 200);
    } else {
        set_cam_viewport(CAM_DEFAULT, 29, 28, 262, 162);
    }

    initialize_status_bar();
    gGameStatusPtr->unk_90 = 1000;
    gGameStatusPtr->unk_92 = 1000;
    gGameStatusPtr->mainScriptID = start_script_in_group(gMapSettings.main, EVT_PRIORITY_0, 0, EVT_GROUP_NEVER_PAUSE)->id;
}

MapConfig* get_current_map_config(void) {
    return gMapConfig;
}

MapSettings* get_current_map_settings(void) {
    return &gMapSettings;
}

NODISCARD s32 get_map_IDs_by_name(const char* mapName, s16* areaID, s16* mapID) {
    s32 i;
    s32 j;
    MapConfig* maps;

    // TODO: Potentially a fake match? Difficult to not set the temp in the for conditional.
    for (i = 0; (maps = gAreas[i].maps) != nullptr; i++) {
        for (j = 0; j < gAreas[i].mapCount; j++) {
            if (strcmp(maps[j].id, mapName) == 0) {
                *areaID = i;
                *mapID = j;
                return true;
            }
        }
    }

    return false;
}

void get_map_IDs_by_name_checked(const char* mapName, s16* areaID, s16* mapID) {
    ASSERT_MSG(get_map_IDs_by_name(mapName, areaID, mapID), "Map not found: %s", mapName);
}

void* load_asset_by_name(const char* assetName, u32* decompressedSize) {
    AssetHeader firstHeader;
    AssetHeader* assetTableBuffer;
    AssetHeader* curAsset;
    void* ret;

    dma_copy((u8*) ASSET_TABLE_FIRST_ENTRY, (u8*) ASSET_TABLE_FIRST_ENTRY + sizeof(AssetHeader), &firstHeader);
    assetTableBuffer = heap_malloc(firstHeader.offset);
    curAsset = &assetTableBuffer[0];
    dma_copy((u8*) ASSET_TABLE_FIRST_ENTRY, (u8*) ASSET_TABLE_FIRST_ENTRY + firstHeader.offset, assetTableBuffer);
    while (strcmp(curAsset->name, assetName) != 0) {
        ASSERT_MSG(strcmp(curAsset->name, "end_data") != 0, "Asset not found: %s", assetName);
        curAsset++;
    }
    *decompressedSize = curAsset->decompressedLength;
    ret = general_heap_malloc(curAsset->compressedLength);
    dma_copy((u8*) ASSET_TABLE_FIRST_ENTRY + curAsset->offset,
             (u8*) ASSET_TABLE_FIRST_ENTRY + curAsset->offset + curAsset->compressedLength, ret);
    heap_free(assetTableBuffer);
    return ret;
}

s32 get_asset_offset(char* assetName, s32* compressedSize) {
    AssetHeader firstHeader;
    AssetHeader* assetTableBuffer;
    AssetHeader* curAsset;
    s32 ret;

    dma_copy((u8*) ASSET_TABLE_FIRST_ENTRY, (u8*) ASSET_TABLE_FIRST_ENTRY + sizeof(AssetHeader), &firstHeader);
    assetTableBuffer = heap_malloc(firstHeader.offset);
    curAsset = &assetTableBuffer[0];
    dma_copy((u8*) ASSET_TABLE_FIRST_ENTRY, (u8*) ASSET_TABLE_FIRST_ENTRY + firstHeader.offset, assetTableBuffer);
    while (strcmp(curAsset->name, assetName) != 0) {
        ASSERT_MSG(strcmp(curAsset->name, "end_data") != 0, "Asset not found: %s", assetName);
        curAsset++;
    }
    *compressedSize = curAsset->compressedLength;
    ret = ASSET_TABLE_FIRST_ENTRY + curAsset->offset;
    heap_free(assetTableBuffer);
    return ret;
}

#include "world/gAreas.inc.c"
