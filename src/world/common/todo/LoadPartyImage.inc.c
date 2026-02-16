#include "common.h"
#include "npc.h"

#ifndef PARTY_IMAGE
#error "Define PARTY_IMAGE to the asset name to use LoadPartyImage."
#endif

#define PARTY_IMAGE_PALETTE_SIZE 256
#define PARTY_IMAGE_WIDTH 150
#define PARTY_IMAGE_HEIGHT 105

typedef struct PartyImage {
    PAL_BIN palette[PARTY_IMAGE_PALETTE_SIZE];
    IMG_BIN raster[PARTY_IMAGE_WIDTH * PARTY_IMAGE_HEIGHT];
    char padding[10];
} PartyImage;

API_CALLABLE(N(LoadPartyImage)) {
    #ifdef SHIFT
    static PartyImage img;
    #else
    static PAL_BIN palette[PARTY_IMAGE_PALETTE_SIZE];
    static IMG_BIN raster[PARTY_IMAGE_WIDTH * PARTY_IMAGE_HEIGHT];
    static u8 padding[10];
    #endif
    static MessageImageData image;

    u32 decompressedSize;
    void* decompressed = load_asset_by_name(PARTY_IMAGE, &decompressedSize);

    #ifdef SHIFT
    memcpy(&img, decompressed, decompressedSize);
    #else
    memcpy(palette, decompressed, decompressedSize);
    #endif

    general_heap_free(decompressed);

    #ifdef SHIFT
    image.raster = img.raster;
    image.palette = img.palette;
    #else
    image.raster = raster;
    image.palette = palette;
    #endif

    image.width = PARTY_IMAGE_WIDTH;
    image.height = PARTY_IMAGE_HEIGHT;
    image.format = G_IM_FMT_CI;
    image.bitDepth = G_IM_SIZ_8b;
    set_message_images(&image);
    return ApiStatus_DONE2;
}

#undef PARTY_IMAGE
