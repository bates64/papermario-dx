#include "common.h"
#include "effects_internal.h"
#include "message_ids.h"

#define NAMESPACE chapter_change

typedef struct TexturePiece {
    /* 0x00 */ Gfx* displayList;
    /* 0x04 */ s16 x;
    /* 0x06 */ s16 y;
    /* 0x08 */ s16 width;
    /* 0x0A */ s16 height;
} TexturePiece; // size: 0xC

extern Gfx D_0900BE40_3F7CA0[];
extern Gfx D_0900BE88_3F7CE8[];
extern Gfx D_0900BED0_3F7D30[];
extern Gfx D_0900BF18_3F7D78[];
extern Gfx D_0900BF60_3F7DC0[];
extern Gfx D_0900BFA8_3F7E08[];
extern Gfx D_0900BFF0_3F7E50[];
extern Gfx D_0900C038_3F7E98[];
#if VERSION_JP
extern Gfx D_0900B900_3FFA20[];
extern Gfx D_0900B9E8_3FFB08[];
extern Gfx D_0900BA30_3FFB50[];
extern Gfx D_0900BB18_3FFC38[];
#else
extern Gfx D_0900C080_3F7EE0[];
extern Gfx D_0900C168_3F7FC8[];
extern Gfx D_0900C1B0_3F8010[];
extern Gfx D_0900C1F8_3F8058[];
extern Gfx D_0900C240_3F80A0[];
extern Gfx D_0900C328_3F8188[];
extern Gfx D_0900C370_3F81D0[];
#endif
extern Gfx D_0900C458_3F82B8[];
extern Gfx D_0900C540_3F83A0[];

s32 N(SubtitleMsg)[] = {
    -1,
    MSG_Menus_019D, MSG_Menus_019E, MSG_Menus_019F,
    MSG_Menus_01A0, MSG_Menus_01A1, MSG_Menus_01A2,
    MSG_Menus_01A3, MSG_Menus_01A4, MSG_Menus_019C,
    -1, -1, -1,
    -1, -1, -1,
    -1, -1, -1,
};

TexturePiece D_E010E79C[] = {
#if VERSION_JP
    { D_0900B900_3FFA20,   0,  0, 104, 20 },
    { D_0900B9E8_3FFB08,   0, 20, 104, 20 },
#else
    { D_0900C080_3F7EE0, 104,  0, 128, 10 },
    { D_0900C168_3F7FC8, 104, 10, 128, 10 },
    { D_0900C1B0_3F8010, 104, 20, 128, 10 },
    { D_0900C1F8_3F8058, 104, 30, 128, 10 },
#endif
    {              nullptr,   0,  0,   0,  0 }
};

TexturePiece D_E010E7D8[] = {
    { D_0900C458_3F82B8, -16, -6, 144, 20 },
    { D_0900C540_3F83A0, -16, 14, 144, 20 },
    {              nullptr,   0,  0,   0,  0 }
};

TexturePiece D_E010E7FC[] = {
#if VERSION_JP
    { D_0900B900_3FFA20,  24, -6, 104, 20 },
    { D_0900B9E8_3FFB08,  24, 14, 104, 20 },
#else
    { D_0900C080_3F7EE0, 0, -6, 128, 10 },
    { D_0900C168_3F7FC8, 0,  4, 128, 10 },
    { D_0900C1B0_3F8010, 0, 14, 128, 10 },
    { D_0900C1F8_3F8058, 0, 24, 128, 10 },
#endif
    {              nullptr, 0,  0,   0,  0 }
};

TexturePiece D_E010E838[] = {
#if VERSION_IQUE
    { D_0900C240_3F80A0,  70,  0, 104, 20 },
    { D_0900C328_3F8188,  70, 20, 104, 20 },
    { D_0900C370_3F81D0, 172,  0,  16, 40 },
#elif VERSION_JP
    { D_0900BA30_3FFB50,  96,  0,  96, 20 },
    { D_0900BB18_3FFC38,  96, 20,  96, 20 },
#else
    { D_0900C240_3F80A0,   0,  0, 104, 20 },
    { D_0900C328_3F8188,   0, 20, 104, 20 },
    { D_0900C370_3F81D0, 232,  0,  16, 40 },
#endif
    {              nullptr,   0,  0,   0,  0 }
};

#if VERSION_PAL
ChapterChangeTexturePiece D_E010E838_b[] = {
    { D_0900C080_3F7EE0, 0,  0, 128, 10 },
    { D_0900C168_3F7FC8, 0, 10, 128, 10 },
    { D_0900C1B0_3F8010, 0, 20, 128, 10 },
    { D_0900C1F8_3F8058, 0, 30, 128, 10 },
    {              nullptr, 0,  0,   0,  0 }
};

ChapterChangeTexturePiece D_E010E838_c[] = {
        { D_0900C240_3F80A0, 128,  0, 104, 20 },
        { D_0900C328_3F8188, 128, 20, 104, 20 },
        { D_0900C370_3F81D0, 232,  0,  16, 40 },
        {              nullptr,   0,  0,   0,  0 }
};
#endif

#if VERSION_IQUE
#define X_VAR 48
#define Y_VAR -13
#else
#define X_VAR 128
#define Y_VAR -33
#endif

TexturePiece D_E010E868[] = {
    { D_0900BE40_3F7CA0, X_VAR, Y_VAR, 64, 64 },
    {              nullptr,     0,     0,  0,  0 },
    { D_0900BE88_3F7CE8, X_VAR, Y_VAR, 64, 64 },
    {              nullptr,     0,     0,  0,  0 },
    { D_0900BED0_3F7D30, X_VAR, Y_VAR, 64, 64 },
    {              nullptr,     0,     0,  0,  0 },
    { D_0900BF18_3F7D78, X_VAR, Y_VAR, 64, 64 },
    {              nullptr,     0,     0,  0,  0 },
    { D_0900BF60_3F7DC0, X_VAR, Y_VAR, 64, 64 },
    {              nullptr,     0,     0,  0,  0 },
    { D_0900BFA8_3F7E08, X_VAR, Y_VAR, 64, 64 },
    {              nullptr,     0,     0,  0,  0 },
    { D_0900BFF0_3F7E50, X_VAR, Y_VAR, 64, 64 },
    {              nullptr,     0,     0,  0,  0 },
    { D_0900C038_3F7E98, X_VAR, Y_VAR, 64, 64 },
    {              nullptr,     0,     0,  0,  0 }
};

void chapter_change_init(EffectInstance* effect);
void chapter_change_update(EffectInstance* effect);
void chapter_change_render(EffectInstance* effect);
void chapter_change_appendGfx(void* effect);

void chapter_change_draw_texture_pieces(ChapterChangeFXData* data, s32 useEndOfPos, TexturePiece* pieces) {
    s32 time = data->lifetime;
    TexturePiece* piece;
    f32 posX, posY;
    s32 tileX, tileZ;

    if (useEndOfPos == 0) {
        posX = data->chapterPos.x;
        posY = data->chapterPos.y;
    } else {
        posX = data->endOfPos.x;
        posY = data->endOfPos.y;
    }

    if (pieces != nullptr) {
        for (piece = pieces; piece->displayList != nullptr; piece++) {
            gSPDisplayList(gMainGfxPos++, piece->displayList);

            tileX = time * 4 - (piece->x - 384);
            tileZ = time * 4 - (piece->x + 511);
            gDPSetTileSize(gMainGfxPos++, 1, tileX * 4, 0, tileZ * 4, 0);
            gSPScisTextureRectangle(gMainGfxPos++,
                (posX + piece->x) * 4,
                (posY + piece->y) * 4,
                (posX + piece->x + piece->width) * 4,
                (posY + piece->y + piece->height) * 4,
                G_TX_RENDERTILE, 0, 0, 1024, 1024);
        }

        gDPPipeSync(gMainGfxPos++);
    }
}

EffectInstance* chapter_change_main(s32 type, f32 posX, f32 posY, f32 arg3, f32 scale, s32 duration) {
    EffectBlueprint bp;
    ChapterChangeFXData* data;
    EffectInstance* effect;
    s32 numParts = 1;

    bp.init = chapter_change_init;
    bp.update = chapter_change_update;
    bp.renderScene = chapter_change_render;
    bp.unk_00 = 0;
    bp.renderUI = nullptr;
    bp.effectID = EFFECT_CHAPTER_CHANGE;

    effect = create_effect_instance(&bp);
    effect->numParts = numParts;
    data = effect->data.chapterChange = general_heap_malloc(numParts * sizeof(*data));
    ASSERT(effect->data.chapterChange != nullptr);

    data->type = type;
    data->lifetime = 0;
    if (duration <= 0) {
        data->timeLeft = 1000;
    } else {
        data->timeLeft = duration;
    }
    data->chapterPos.x = data->endOfPos.x = posX;
    data->chapterPos.y = data->endOfPos.y = posY;
    data->unused_0C = arg3;
    data->scale = scale;
    data->primCol.r = 255;
    data->primCol.g = 255;
    data->primCol.b = 255;
    data->primCol.a = 255;
    data->envCol.r = 0;
    data->envCol.g = 0;
    data->envCol.b = 0;
    if (type == 0 || (type >= 10 && type <= 18)) {
        data->envCol.a = 0;
    } else {
        data->envCol.a = 255;
    }
    data->msgID = N(SubtitleMsg)[type];
    if (data->msgID >= 0) {
        data->msgPos.x = 160;
        data->msgPos.y = 160;
        data->msgWidth = get_msg_width(data->msgID, 0);
        data->msgHeight = 24;
    }

    return effect;
}

void chapter_change_init(EffectInstance* effect) {
}

void chapter_change_update(EffectInstance* effect) {
    ChapterChangeFXData* data = effect->data.chapterChange;

    if (effect->flags & FX_INSTANCE_FLAG_DISMISS) {
        effect->flags &= ~FX_INSTANCE_FLAG_DISMISS;
        data->timeLeft = 16;
    }

    if (data->timeLeft < 1000) {
        data->timeLeft--;
    }

    data->lifetime++;

    if (data->timeLeft < 0) {
        remove_effect(effect);
    }
}

void chapter_change_render(EffectInstance* effect) {
    RenderTask renderTask;
    RenderTask* retTask;

    renderTask.appendGfx = chapter_change_appendGfx;
    renderTask.appendGfxArg = effect;
    renderTask.dist = 10;
    renderTask.renderMode = RENDER_MODE_CLOUD_NO_ZCMP;

    retTask = queue_render_task(&renderTask);
    retTask->renderMode |= RENDER_TASK_FLAG_REFLECT_FLOOR;
}

void chapter_change_appendGfx(void* effect) {
    ChapterChangeFXData* data = ((EffectInstance*)effect)->data.chapterChange;
    s32 alpha = data->primCol.a;
    u32 type = data->type;
    TexturePiece* ptr0;
    TexturePiece* ptr1;

    gDPPipeSync(gMainGfxPos++);
    gSPSegment(gMainGfxPos++, 0x09, VIRTUAL_TO_PHYSICAL(((EffectInstance*)effect)->shared->graphics));

    switch (type) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            ptr0 = D_E010E7FC;
            ptr1 = &D_E010E868[(type - 1) * 2];
            break;
        case 9:
            ptr0 = D_E010E7D8;
            ptr1 = nullptr;
            break;
        case 0:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
#if VERSION_PAL
            if (gCurrentLanguage == LANGUAGE_DE) {
                ptr0 = D_E010E838_b;
                ptr1 = D_E010E838_c;
                break;
            }
#endif
            ptr0 = D_E010E79C;
            ptr1 = D_E010E838;
            break;
        default:
            ptr1 = nullptr;
            ptr0 = nullptr;
            break;
    }

    gDPSetPrimColor(gMainGfxPos++, 0, 0, data->primCol.r, data->primCol.g, data->primCol.b, alpha);
    gDPSetEnvColor(gMainGfxPos++, data->envCol.r, data->envCol.g, data->envCol.b, data->envCol.a);

    chapter_change_draw_texture_pieces(data, false, ptr0);
    chapter_change_draw_texture_pieces(data, true, ptr1);

    if (data->msgID > -1) {
        draw_msg(data->msgID, data->msgPos.x - data->msgWidth, data->msgPos.y, 255, 21, 0);
    }

    gDPPipeSync(gMainGfxPos++);
}
