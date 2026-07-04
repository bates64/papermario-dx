#include "common.h"
#include "sprite.h"
#include "nu/nusys.h"
#include "ld_addrs.h"
#include "sprite/player.h"

extern b32 SpriteUseGeneralHeap;
extern HeapNode heap_generalHead;
extern HeapNode heap_spriteHead;

BSS s32 spr_asset_entry[2];
BSS s32 PlayerRasterLoadDescBuffer[101]; //NOTE: maximum rasters supported for a single player sprite is 101
BSS s32 PlayerRasterLoadDescNumLoaded;
BSS s32 PlayerRasterLoadDescBeginSpriteIndex[SPR_Peach3]; //TODO size linked to number of player sprites
BSS s32 PlayerRasterLoadDesc[0x2E0]; // correct length?

BSS PlayerRastersHeader PlayerRasterHeader;
BSS s32 PlayerSpriteRasterSets[SPR_Peach3 + 1]; //TODO size linked to number of player sprites
BSS s32 PlayerRasterCacheSize;
BSS s32 PlayerRasterMaxSize;
BSS s32 SpriteDataHeader[3];
BSS PlayerSpriteCacheEntry PlayerRasterCache[18];

#define ALIGN4(v) (((u32)(v) >> 2) << 2)
#define SPR_SWIZZLE(base,offset) ((void*)((s32)(offset) + (s32)(base)))

void spr_swizzle_anim_offsets(s32 arg0, s32 base, void* spriteData) {
    SpriteAnimComponent*** animList;
    SpriteAnimComponent** compList;
    SpriteAnimComponent* comp;

    // required to match, spriteData->animList would be nicer
    animList = (SpriteAnimComponent***) spriteData;
    animList += 4;

    while (true) {
        if (*animList == PTR_LIST_END) {
            break;
        }
        compList = (SpriteAnimComponent**) ((s32)*animList - ALIGN4(base));
        compList = SPR_SWIZZLE(ALIGN4(spriteData), compList);
        *animList = compList;
        while (true) {
            if (*compList == PTR_LIST_END) {
                break;
            }
            *compList = comp = SPR_SWIZZLE(ALIGN4(spriteData), (s32)*compList - ALIGN4(base));
            comp->cmdList = SPR_SWIZZLE(ALIGN4(spriteData), (s32)comp->cmdList - ALIGN4(base));
            compList++;
        }
        animList++;
    }
}

SpriteAnimData* spr_load_sprite(s32 idx, s32 isPlayerSprite, s32 useTailAlloc) {
    SpriteAnimData* animData;
    s32 base;
    s32 i;
    s32 compressedSize;
    s32* ptr1;
    IMG_PTR image;
    s32 count;
    s32** data;
    s32** palettes;

    if (isPlayerSprite) {
        base = SpriteDataHeader[1];
    } else {
        base = SpriteDataHeader[2];
    }

    // read current and next sprite offsets, so we can find the difference
    nuPiReadRom(base + idx * 4, &spr_asset_entry, sizeof(spr_asset_entry));

    compressedSize = ALIGN8(spr_asset_entry[1] - spr_asset_entry[0]);
    data = general_heap_malloc(compressedSize);
    nuPiReadRom(base + spr_asset_entry[0], data, compressedSize);

    ptr1 = (s32*)data;
    // skip 4 bytes: 'YAY0' signature
    ptr1++;

    if (useTailAlloc) {
        animData = _heap_malloc_tail(&heap_spriteHead, *ptr1);
    } else {
        animData = _heap_malloc(&heap_spriteHead, *ptr1);
    }
    ASSERT_MSG(animData, "out of sprite memory");
    decode_yay0(data, animData);
    general_heap_free(data);

    // swizzle raster array
    data = (s32**)animData->rastersOffset;
    data = SPR_SWIZZLE(ALIGN4(animData), data);
    animData->rastersOffset = (SpriteRasterEntry**)data;

    while (true) {
        ptr1 = *data;
        if (ptr1 == PTR_LIST_END) {
            break;
        }
        // swizzle each raster cache entry
        ptr1 = SPR_SWIZZLE(ALIGN4(animData), ptr1);
        *data++ = ptr1;
        image = ((SpriteRasterEntry*)ptr1)->image;

        if (!isPlayerSprite) {
            // swizzle image pointer in the cache entry
            image = SPR_SWIZZLE(ALIGN4(animData), image);
            *ptr1 = (s32)image;
        }
    }

    if (isPlayerSprite) {
        PlayerRasterLoadDescBeginSpriteIndex[idx] = PlayerRasterLoadDescNumLoaded;
        count = PlayerSpriteRasterSets[idx + 1] - PlayerSpriteRasterSets[idx];
        // load a range of raster loading desciptors to a buffer and copy contents into PlayerRasterLoadDesc
        nuPiReadRom(SpriteDataHeader[0] + PlayerRasterHeader.loadDescriptors + sizeof(u32) * PlayerSpriteRasterSets[idx],
            PlayerRasterLoadDescBuffer, sizeof(PlayerRasterLoadDescBuffer));
        for (i = 0; i < count; i++) {
            PlayerRasterLoadDesc[PlayerRasterLoadDescNumLoaded++] = PlayerRasterLoadDescBuffer[i];
        }
    }

    // swizzle palettes array
    palettes = SPR_SWIZZLE(ALIGN4(animData), animData->palettesOffset);
    animData->palettesOffset = (PAL_PTR*)palettes;
    while (true) {
        ptr1 = *palettes;
        if (ptr1 == PTR_LIST_END) {
            break;
        }
        // swizzle each palette pointer
        ptr1 = SPR_SWIZZLE(ALIGN4(animData), ptr1);
        *palettes++ = ptr1;
    }

    spr_swizzle_anim_offsets(0, 0, animData);
    return animData;
}

void spr_init_player_raster_cache(s32 cacheSize, s32 maxRasterSize) {
    u32 headerRomPos = (u32) sprites_ROM_START + 0x10;
    void* raster;
    s32 i;

    nuPiReadRom(headerRomPos, &SpriteDataHeader, sizeof(SpriteDataHeader));
    PlayerRasterCacheSize = cacheSize;
    PlayerRasterMaxSize = maxRasterSize;
    SpriteDataHeader[0] += headerRomPos;
    SpriteDataHeader[1] += headerRomPos;
    SpriteDataHeader[2] += headerRomPos;
    raster = _heap_malloc(&heap_spriteHead, maxRasterSize * cacheSize);

    for (i = 0; i < ARRAY_COUNT(PlayerRasterCache); i++) {
        PlayerRasterCache[i].raster = raster;
        raster += PlayerRasterMaxSize;
        PlayerRasterCache[i].lazyDeleteTime = 0;
        PlayerRasterCache[i].rasterIndex = 0;
        PlayerRasterCache[i].spriteIndex = 0xFF;
    }

    for (i = 0; i < ARRAY_COUNT(PlayerRasterLoadDescBeginSpriteIndex); i++)    {
        PlayerRasterLoadDescBeginSpriteIndex[i] = 0;
    }
    PlayerRasterLoadDescNumLoaded = 0;
    nuPiReadRom(SpriteDataHeader[0], &PlayerRasterHeader, sizeof(PlayerRasterHeader));
    nuPiReadRom(SpriteDataHeader[0] + PlayerRasterHeader.indexRanges, PlayerSpriteRasterSets, sizeof(PlayerSpriteRasterSets));
}

IMG_PTR spr_get_player_raster(s32 rasterIndex, s32 playerSpriteID) {
    PlayerSpriteCacheEntry* cacheEntry;
    u32 playerRasterInfo;
    s32 idx = -1;
    s32 i;

    for (i = 0; i < PlayerRasterCacheSize; i++) {
        if (PlayerRasterCache[i].lazyDeleteTime != 0) {
            if (PlayerRasterCache[i].rasterIndex == rasterIndex && PlayerRasterCache[i].spriteIndex == playerSpriteID) {
                PlayerRasterCache[i].lazyDeleteTime = 2;
                return PlayerRasterCache[i].raster;
            }
        } else if (idx == -1) {
            idx = i;
        }
    }

    if (idx == -1) {
        return nullptr;
    }

    cacheEntry = &PlayerRasterCache[idx];
    cacheEntry->rasterIndex = rasterIndex;
    cacheEntry->spriteIndex = playerSpriteID;
    cacheEntry->lazyDeleteTime = 2;

    // each player raster load descriptor has image size (in bytes) and relative offset packed into one word
    // upper three nibbles give size / 16, lower 5 give offset
    playerRasterInfo = PlayerRasterLoadDesc[PlayerRasterLoadDescBeginSpriteIndex[playerSpriteID] + rasterIndex];
    nuPiReadRom(SpriteDataHeader[0] + (playerRasterInfo & 0xFFFFF), cacheEntry->raster, (playerRasterInfo >> 0x10) & 0xFFF0);
    return cacheEntry->raster;
}

void spr_update_player_raster_cache(void) {
    s32 i;

    for (i = 0; i < PlayerRasterCacheSize; i++) {
        if (PlayerRasterCache[i].lazyDeleteTime != 0) {
            PlayerRasterCache[i].lazyDeleteTime--;
        }
    }
}

void spr_npc_unload_unused_assets(SpriteAnimData* spriteData, AnimID* limitAnimList) {
    u8* rasterDataSrc;
    s32 imgID;
    s32 rasterBlockSize;
    s32 cmdsRemaining;
    u16 animCmd;
    u16* cmdReadPos;
    u32 animID;
    u8* compactWritePos;
    void* lastRetainedRaster;
    SpriteAnimComponent* animComponent;
    SpriteAnimComponent** animComponents;
    void* tableWritePos;
    SpriteRasterEntry** rasterReadPos;
    SpriteRasterEntry* raster;
    PAL_PTR* paletteReadPos;
    PAL_PTR palette;
    // one extra required for 'done' sentinel
    s32 keepRaster[100 + 1];
    s32 i;

    for (i = 0; i < ARRAY_COUNT(keepRaster) - 1; i++) {
        keepRaster[i] = false;
    }

    // mark every raster appearing in animations from limitAnimList
    while ((animID = *limitAnimList++) != ANIM_LIST_END) {
        animComponents = spriteData->animListStart[animID & 0xFF];
        while ((animComponent = *animComponents++) != PTR_LIST_END) {
            cmdReadPos = animComponent->cmdList;
            cmdsRemaining = (s16) animComponent->cmdListSize / 2;
            while (cmdsRemaining > 0) {
                animCmd = *cmdReadPos++;
                cmdsRemaining--;
                switch (animCmd & 0xF000) {
                    case 0x1000:
                        imgID = animCmd & 0xFF;
                        if (imgID < ARRAY_COUNT(keepRaster) - 1) {
                            keepRaster[imgID] = true;
                        }
                        break;
                    case 0x3000:
                        cmdReadPos++;
                        cmdsRemaining--;
                        // fallthrough
                    case 0x4000:
                        cmdReadPos++;
                        cmdsRemaining--;
                        // fallthrough
                    case 0x7000:
                    case 0x5000:
                        cmdReadPos++;
                        cmdsRemaining--;
                        // fallthrough
                    case 0x0000:
                    case 0x2000:
                    case 0x6000:
                    case 0x8000:
                        break;
                }
            }
        }
    }

    rasterReadPos = spriteData->rastersOffset;
    raster = *rasterReadPos;
    compactWritePos = raster->image;

    // pack retained raster data and cache entries over the discarded blocks
    for (i = 0; i < ARRAY_COUNT(keepRaster) - 1; i++) {
        if ((raster = *rasterReadPos) == PTR_LIST_END) {
            break;
        }
        if (keepRaster[i]) {
            rasterDataSrc = raster->image;
            rasterBlockSize = (raster->width * raster->height) / 2;
            lastRetainedRaster = &compactWritePos[rasterBlockSize];
            rasterBlockSize += sizeof(*raster);
            if (compactWritePos != rasterDataSrc) {
                raster->image = compactWritePos;
                bcopy(rasterDataSrc, compactWritePos, rasterBlockSize);
            }
            *rasterReadPos = lastRetainedRaster;
            compactWritePos += rasterBlockSize;
        }
        rasterReadPos++;
    }
    // sentinel value to mark end of valid data
    keepRaster[i] = true;

    tableWritePos = compactWritePos;

    // rebuild the raster table, redirecting discarded slots to a valid retained entry
    rasterReadPos = spriteData->rastersOffset;
    spriteData->rastersOffset = tableWritePos;

    for (i = 0; i < ARRAY_COUNT(keepRaster) - 1; i++) {
        raster = *rasterReadPos++;
        if (keepRaster[i]) {
            *(SpriteRasterEntry**) tableWritePos = raster;
        } else {
            *(SpriteRasterEntry**) tableWritePos = lastRetainedRaster;
        }
        tableWritePos += 4;
        if (raster == PTR_LIST_END) {
            break;
        }
    }

    // relocate the palette pointer table; the palette data itself is retained unchanged
    paletteReadPos = spriteData->palettesOffset;
    spriteData->palettesOffset = tableWritePos;

    for (i = 0; i < ARRAY_COUNT(keepRaster) - 1; i++) {
        palette = *paletteReadPos++;
        *(PAL_PTR*)tableWritePos = palette;
        tableWritePos += sizeof(PAL_PTR);
        if (palette == PTR_LIST_END) {
            break;
        }
    }

    // compact the sprite in memory
    _heap_realloc(&heap_spriteHead, spriteData, (s32)tableWritePos - (s32)spriteData);
}

SpriteComponent** spr_allocate_components(s32 count) {
    s32 listSize;
    SpriteComponent** listStart;
    SpriteComponent* component;
    SpriteComponent** listPos;
    u32 totalSize;
    s32 i;

    // data will contain a -1 terminated list, followed by the SpriteComponents
    // corresponding to that list
    listSize = (count + 1) * 4;
    totalSize = (count * sizeof(SpriteComponent)) + listSize;

    if (SpriteUseGeneralHeap) {
        listStart = _heap_malloc(&heap_generalHead, totalSize);
        listPos = listStart;
        component = (SpriteComponent*) listPos;
    } else {
        listStart = _heap_malloc(&heap_spriteHead, totalSize);
        listPos = listStart;
        component = (SpriteComponent*) listPos;
    }

    component = (SpriteComponent*)((s32)(component) + (listSize / 4) * 4);

    // fill list values
    for (i = 0; i < count; i++) {
        *listPos++ = component;
        component++;
    }
    *listPos = PTR_LIST_END;

    return listStart;
}
