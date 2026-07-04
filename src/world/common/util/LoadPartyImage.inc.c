#include "common.h"
#include "npc.h"

#define PARTY_IMAGE_PALETTE_SIZE 256
#define PARTY_IMAGE_WIDTH 150
#define PARTY_IMAGE_HEIGHT 105

typedef struct PartyImage {
    /* 0x0000 */ PAL_BIN palette[PARTY_IMAGE_PALETTE_SIZE];
    /* 0x0200 */ IMG_BIN raster[PARTY_IMAGE_WIDTH * PARTY_IMAGE_HEIGHT];
    /* 0x3F86 */ PAD(10);
} PartyImage; // size = 0x3F90

API_CALLABLE(N(LoadPartyImage)) {
    static PartyImage img;
    static MessageImageData image;

    const char* assetName = (const char*)evt_get_variable(script, *script->ptrReadPos);
    u32 decompressedSize;
    void* compressed = load_asset_by_name(assetName, &decompressedSize);

    decode_yay0(compressed, &img);
    general_heap_free(compressed);

    image.raster = img.raster;
    image.palette = img.palette;

    image.width = PARTY_IMAGE_WIDTH;
    image.height = PARTY_IMAGE_HEIGHT;
    image.format = G_IM_FMT_CI;
    image.bitDepth = G_IM_SIZ_8b;
    set_message_images(&image);
    return ApiStatus_DONE2;
}
