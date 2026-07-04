#include "dro_02.h"
#include "model.h"
#include "entity.h"
#include "sprite.h"
#include "effects.h"
#include "sprite/player.h"
#include "include_asset.h"

BSS f32 N(CardRiseSpeed);
BSS f32 N(PlayerFallSpeed);
BSS s32 N(RitualStateTime);
BSS EffectInstance* N(ReleaseEnergyFX)[4];

// a card can draw itself, with or without the player; or one of the shuffle/merge ImgFX animations
typedef struct RitualCard {
    /* 0x00 */ s32 drawMode;
    /* 0x04 */ Vec3f pos;
    /* 0x10 */ f32 yaw;
    /* 0x14 */ f32 pitch;
    /* 0x18 */ s32 playerSpriteID;
    /* 0x1C */ s32 playerRasterIndex;
    /* 0x20 */ s32 spriteOffsetX;
} RitualCard; // size = 0x24

BSS Evt* N(CreatorScript);

// shared storage used by the event script and the card worker
BSS s32 N(RitualBuffer)[16];

enum {
    RITUAL_VAR_SHUFFLE_IMGFX    = ArrayVar(0),
    RITUAL_VAR_FLIP1_IMGFX      = ArrayVar(1),
    RITUAL_VAR_FLIP2_IMGFX      = ArrayVar(2),
    RITUAL_VAR_FLIP3_IMGFX      = ArrayVar(3),
    RITUAL_VAR_POS_X            = ArrayVar(4),
    RITUAL_VAR_POS_Y            = ArrayVar(5),
    RITUAL_VAR_POS_Z            = ArrayVar(6),
    RITUAL_VAR_WORKER           = ArrayVar(7),
    RITUAL_VAR_ORB_EFFECT       = ArrayVar(8),
    RITUAL_VAR_STATE            = ArrayVar(9),
};

enum {
    RITUAL_STATE_INIT                   = 0,
    RITUAL_STATE_CARDS_APPEAR           = 1,
    RITUAL_STATE_SHUFFLE_CARDS          = 2,
    RITUAL_STATE_SPREAD_CARDS           = 3,
    RITUAL_STATE_WAIT_BEFORE_REVEAL     = 4,
    RITUAL_STATE_REVEAL_LEFT            = 5,
    RITUAL_STATE_REVEAL_MIDDLE          = 6,
    RITUAL_STATE_REVEAL_RIGHT           = 7,
    RITUAL_STATE_FINISH_RIGHT_FLIP      = 8,
    RITUAL_STATE_GATHER_CARDS           = 9,
    RITUAL_STATE_MERGE_CARDS            = 10,
    RITUAL_STATE_BEGIN_RELEASE_PLAYER   = 11,
    RITUAL_STATE_RELEASE_PLAYER         = 12,
    RITUAL_STATE_COMPLETE               = 13,
};

enum {
    CARD_DRAW_HIDDEN             = 0,
    CARD_DRAW_CARD_AND_PLAYER    = 1,
    CARD_DRAW_SHUFFLE_ANIM       = 2,
    CARD_DRAW_MERGE_ANIM         = 3,
    CARD_DRAW_CARD_ONLY          = 4,
    CARD_DRAW_PLAYER_ONLY        = 5,
};

// Stored in screen order as left, right, middle.
BSS RitualCard N(RitualCards)[3];

s8 N(MerleeSpellCasts)[] = {
    20, 10, 5, 0,
};

s8 N(MerleeCoinCosts)[] = {
    50, 20, 5, 0,
};

INCLUDE_IMG("world/area/dro/dro_02/card.png", dro_02_card);
INCLUDE_PAL("world/area/dro/dro_02/card.pal", dro_02_card_pal);
#include "world/area/dro/dro_02/card_1.vtx.inc.c"
#include "world/area/dro/dro_02/card_2.vtx.inc.c"
#include "world/area/dro/dro_02/card_setup.gfx.inc.c"
#include "world/area/dro/dro_02/card_1.gfx.inc.c"
#include "world/area/dro/dro_02/card_2.gfx.inc.c"

void N(UpdateRitualCards)(void);
void N(RenderRitualCards)(void);

API_CALLABLE(N(TryEnchantPlayer)) {
    PlayerData* playerData = &gPlayerData;
    Bytecode* args = script->ptrReadPos;
    s32 tier = evt_get_variable(script, *args++);
    s32 outPrevented = *args++;
    u8 coins = N(MerleeCoinCosts)[tier];
    u8 casts = N(MerleeSpellCasts)[tier];

    if (playerData->coins < coins) {
        evt_set_variable(script, outPrevented, true);
    } else {
        playerData->coins = playerData->coins - coins;
        if (playerData->merleeCastsLeft < casts) {
            playerData->merleeCastsLeft = casts;
        }
        playerData->merleeTurnCount = rand_int(2) + 1;
        switch (rand_int(3)) {
            case 0:
                playerData->merleeSpellType = MERLEE_SPELL_ATK_BOOST;
                break;
            case 1:
                playerData->merleeSpellType = MERLEE_SPELL_DEF_BOOST;
                break;
            case 2:
                playerData->merleeSpellType = MERLEE_SPELL_EXP_BOOST;
                break;
            case 3:
                playerData->merleeSpellType = MERLEE_SPELL_COIN_BOOST;
                break;
        }
        evt_set_variable(script, outPrevented, false);
    }

    return ApiStatus_DONE2;
}

API_CALLABLE(N(DarkenWorld)) {
    s32 i;

    if (isInitialCall) {
        mdl_set_all_tint_type(ENV_TINT_SHROUD);
        *gBackgroundTintModePtr = ENV_TINT_SHROUD;
        mdl_set_shroud_tint_params(0, 0, 0, 0);

        for (i = 0; i < MAX_NPCS; i++) {
            Npc* npc = get_npc_by_index(i);
            if (npc != 0 && npc->flags != 0 && npc->npcID != NPC_PARTNER && npc->npcID != NPC_Merlee) {
                npc->flags |= NPC_FLAG_HIDING;
            }
        }
        script->functionTemp[0] = 0;
    }

    script->functionTemp[0] += 8;
    if (script->functionTemp[0] > 255) {
        script->functionTemp[0] = 255;
    }
    mdl_set_shroud_tint_params(0, 0, 0, script->functionTemp[0]);

    if (script->functionTemp[0] == 255) {
        return ApiStatus_DONE2;
    } else {
        return ApiStatus_BLOCK;
    }
}

API_CALLABLE(N(UndarkenWorld)) {
    s32 i;

    if (isInitialCall) {
        mdl_set_shroud_tint_params(0, 0, 0, 255);
        script->functionTemp[0] = 255;
        script->functionTemp[1] = 0;
    }
    script->functionTemp[0] -= 8;
    if (script->functionTemp[0] < 0) {
        script->functionTemp[0] = 0;
    }
    mdl_set_shroud_tint_params(0, 0, 0, script->functionTemp[0]);

    if (script->functionTemp[0] == 0 && script->functionTemp[1] == 0) {
        script->functionTemp[1] = 1;
    } else if (script->functionTemp[1] == 1) {
        mdl_set_all_tint_type(ENV_TINT_NONE);
        *gBackgroundTintModePtr = ENV_TINT_NONE;
        for (i = 0; i < MAX_NPCS; i++) {
            Npc* npc = get_npc_by_index(i);

            if (npc != nullptr && npc->flags != 0 && npc->npcID != NPC_PARTNER && npc->npcID != NPC_Merlee) {
                npc->flags &= ~NPC_FLAG_HIDING;
            }
        }
        return ApiStatus_DONE2;
    }
    return ApiStatus_BLOCK;
}

API_CALLABLE(N(CreateRitualCards)) {
    s32 imgfxIdx;

    N(CreatorScript) = script;

    imgfxIdx = imgfx_get_free_instances(1);
    imgfx_update(imgfxIdx, IMGFX_SET_ANIM, IMGFX_ANIM_SHUFFLE_CARDS, 1, 1, 0, IMGFX_FLAG_HOLD_DONE);
    evt_set_variable(script, RITUAL_VAR_SHUFFLE_IMGFX, imgfxIdx);
    imgfxIdx = imgfx_get_free_instances(1);
    imgfx_update(imgfxIdx, IMGFX_SET_ANIM, IMGFX_ANIM_FLIP_CARD_1, 1, 1, 0, IMGFX_FLAG_HOLD_DONE);
    evt_set_variable(script, RITUAL_VAR_FLIP1_IMGFX, imgfxIdx);
    imgfxIdx = imgfx_get_free_instances(1);
    imgfx_update(imgfxIdx, IMGFX_SET_ANIM, IMGFX_ANIM_FLIP_CARD_2, 1, 1, 0, IMGFX_FLAG_HOLD_DONE);
    evt_set_variable(script, RITUAL_VAR_FLIP2_IMGFX, imgfxIdx);
    imgfxIdx = imgfx_get_free_instances(1);
    imgfx_update(imgfxIdx, IMGFX_SET_ANIM, IMGFX_ANIM_FLIP_CARD_3, 1, 1, 0, IMGFX_FLAG_HOLD_DONE);
    evt_set_variable(script, RITUAL_VAR_FLIP3_IMGFX, imgfxIdx);

    evt_set_variable(script, RITUAL_VAR_WORKER, create_worker_scene(
        N(UpdateRitualCards),
        N(RenderRitualCards)));
    return ApiStatus_DONE2;
}

API_CALLABLE(N(DestroyRitualCards)) {
    imgfx_release_instance(evt_get_variable(script, RITUAL_VAR_SHUFFLE_IMGFX));
    imgfx_release_instance(evt_get_variable(script, RITUAL_VAR_FLIP1_IMGFX));
    imgfx_release_instance(evt_get_variable(script, RITUAL_VAR_FLIP2_IMGFX));
    imgfx_release_instance(evt_get_variable(script, RITUAL_VAR_FLIP3_IMGFX));
    free_worker(evt_get_variable(script, RITUAL_VAR_WORKER));
    return ApiStatus_DONE2;
}

s32 N(AppendGfx_RitualCard)(RitualCard* card, Matrix4f mtxParent) {
    Matrix4f mtxTransform;
    Matrix4f mtxTemp;
    ImgFXTexture ifxImg;
    SpriteRasterInfo rasterInfo;
    s32 animResult;

    // resolves a deadlock where imgfx_appendGfx_component would exit early if uninitialized
    ifxImg.alpha = 255;

    if (card->drawMode == CARD_DRAW_HIDDEN) {
        return IMGFX_RENDER_RESULT_DONE;
    }

    gSPDisplayList(gMainGfxPos++, N(card_setup_gfx));

    if (card->drawMode == CARD_DRAW_CARD_AND_PLAYER
        || card->drawMode == CARD_DRAW_CARD_ONLY
        || card->drawMode == CARD_DRAW_PLAYER_ONLY
    ) {
        guTranslateF(mtxTemp, card->pos.x, card->pos.y, card->pos.z);
        guMtxCatF(mtxTemp, mtxParent, mtxTransform);
        guRotateF(mtxTemp, card->yaw, 0.0f, 1.0f, 0.0f);
        guMtxCatF(mtxTemp, mtxTransform, mtxTransform);
        guRotateF(mtxTemp, card->pitch, 1.0f, 0.0f, 0.0f);
        guMtxCatF(mtxTemp, mtxTransform, mtxTransform);
        guMtxF2L(mtxTransform, &gDisplayContext->matrixStack[gMatrixListPos]);
        gSPMatrix(gMainGfxPos++, VIRTUAL_TO_PHYSICAL(&gDisplayContext->matrixStack[gMatrixListPos++]), G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        // draw card
        if (card->drawMode == CARD_DRAW_CARD_AND_PLAYER || card->drawMode == CARD_DRAW_CARD_ONLY) {
            gSPDisplayList(gMainGfxPos++, N(card_1_gfx));
        }

        // draw player
        if (card->drawMode == CARD_DRAW_CARD_AND_PLAYER || card->drawMode == CARD_DRAW_PLAYER_ONLY) {
            spr_get_player_raster_info(&rasterInfo, card->playerSpriteID, card->playerRasterIndex);
            gDPSetTextureLUT(gMainGfxPos++, G_TT_RGBA16);
            gDPLoadTLUT_pal16(gMainGfxPos++, 0, rasterInfo.defaultPal);
            gDPLoadTextureTile_4b(gMainGfxPos++, rasterInfo.raster, G_IM_FMT_CI, rasterInfo.width, rasterInfo.height,
                                    0, 0, rasterInfo.width - 1, rasterInfo.height - 1, 0,
                                    G_TX_CLAMP, G_TX_CLAMP, 8, 8, G_TX_NOLOD, G_TX_NOLOD);
            guTranslateF(mtxTransform, card->spriteOffsetX + 30 - rasterInfo.width / 2, 0.0f, 0.0f);
            guMtxF2L(mtxTransform, &gDisplayContext->matrixStack[gMatrixListPos]);
            gSPMatrix(gMainGfxPos++, VIRTUAL_TO_PHYSICAL(&gDisplayContext->matrixStack[gMatrixListPos++]), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
            gSPDisplayList(gMainGfxPos++, N(card_2_gfx));
            gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
        }
        gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
        return IMGFX_RENDER_RESULT_DONE;
    }

    if (card->drawMode == CARD_DRAW_SHUFFLE_ANIM) {
        gDPSetTileSize(gMainGfxPos++, G_TX_RENDERTILE, 256 * 4, 256 * 4, 287 * 4, 287 * 4);
        guTranslateF(mtxTemp, N(RitualCards)[0].pos.x, N(RitualCards)[0].pos.y, N(RitualCards)[0].pos.z);
        guMtxCatF(mtxTemp, mtxParent, mtxTransform);
        guMtxF2L(mtxTransform, &gDisplayContext->matrixStack[gMatrixListPos]);
        gSPMatrix(gMainGfxPos++, VIRTUAL_TO_PHYSICAL(&gDisplayContext->matrixStack[gMatrixListPos++]), G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        animResult = imgfx_appendGfx_component(evt_get_variable(N(CreatorScript), RITUAL_VAR_SHUFFLE_IMGFX), &ifxImg, IMGFX_FLAG_SKIP_GFX_SETUP | IMGFX_FLAG_SKIP_TEX_SETUP, mtxTransform);
        gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
        return animResult;
    }

    if (card->drawMode == CARD_DRAW_MERGE_ANIM) {
        gDPSetTileSize(gMainGfxPos++, G_TX_RENDERTILE, 256 * 4, 256 * 4, 287 * 4, 287 * 4);
        guTranslateF(mtxTemp, N(RitualCards)[0].pos.x, N(RitualCards)[0].pos.y, N(RitualCards)[0].pos.z);
        guMtxCatF(mtxTemp, mtxParent, mtxTransform);
        guMtxF2L(mtxTransform, &gDisplayContext->matrixStack[gMatrixListPos]);
        gSPMatrix(gMainGfxPos++, VIRTUAL_TO_PHYSICAL(&gDisplayContext->matrixStack[gMatrixListPos++]), G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        imgfx_appendGfx_component(evt_get_variable(N(CreatorScript), RITUAL_VAR_FLIP1_IMGFX), &ifxImg, IMGFX_FLAG_SKIP_GFX_SETUP | IMGFX_FLAG_SKIP_TEX_SETUP, mtxTransform);
        imgfx_appendGfx_component(evt_get_variable(N(CreatorScript), RITUAL_VAR_FLIP2_IMGFX), &ifxImg, IMGFX_FLAG_SKIP_GFX_SETUP | IMGFX_FLAG_SKIP_TEX_SETUP, mtxTransform);
        gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
        guTranslateF(mtxTemp, N(RitualCards)[0].pos.x, N(RitualCards)[0].pos.y, N(RitualCards)[0].pos.z);
        guMtxCatF(mtxTemp, mtxParent, mtxTransform);
        guMtxF2L(mtxTransform, &gDisplayContext->matrixStack[gMatrixListPos]);
        gSPMatrix(gMainGfxPos++, VIRTUAL_TO_PHYSICAL(&gDisplayContext->matrixStack[gMatrixListPos++]), G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        spr_get_player_raster_info(&rasterInfo, card->playerSpriteID, card->playerRasterIndex);
        ifxImg.raster = rasterInfo.raster;
        ifxImg.palette = rasterInfo.defaultPal;
        ifxImg.width = rasterInfo.width;
        ifxImg.height = rasterInfo.height;
        ifxImg.xOffset = -(rasterInfo.width / 2);
        ifxImg.yOffset = rasterInfo.height / 2;
        ifxImg.alpha = 255;
        animResult = imgfx_appendGfx_component(evt_get_variable(N(CreatorScript), RITUAL_VAR_FLIP3_IMGFX), &ifxImg, IMGFX_FLAG_SKIP_GFX_SETUP, mtxTransform);
        gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
        return animResult;
    }

    return IMGFX_RENDER_RESULT_DONE;
}

void N(GetCardWorldPos)(s32 index, f32* outX, f32* outY, f32* outZ) {
    RitualCard* card;
    Matrix4f mtxTransform;
    Matrix4f mtxTemp;
    Matrix4f mtxParent;

    guPositionF(mtxParent, 0.0f, -gCameras[gCurrentCameraID].curYaw, 0.0f, SPRITE_WORLD_SCALE_F,
                evt_get_variable(N(CreatorScript), RITUAL_VAR_POS_X),
                evt_get_variable(N(CreatorScript), RITUAL_VAR_POS_Y),
                evt_get_variable(N(CreatorScript), RITUAL_VAR_POS_Z));

    card = &N(RitualCards)[index];
    guTranslateF(mtxTemp, card->pos.x, card->pos.y, card->pos.z);
    guMtxCatF(mtxTemp, mtxParent, mtxTransform);
    guRotateF(mtxTemp, card->yaw, 0.0f, 1.0f, 0.0f);
    guMtxCatF(mtxTemp, mtxTransform, mtxTransform);
    guTranslateF(mtxTemp, 0.0f, 0.0f, 1.0f);
    guMtxCatF(mtxTemp, mtxTransform, mtxTransform);
    *outX = mtxTransform[3][0];
    *outY = mtxTransform[3][1];
    *outZ = mtxTransform[3][2];
}

void N(UpdateRitualCards)(void) {
    f32 leftX, leftY, leftZ;
    f32 middleX, middleY, middleZ;
    f32 rightX, rightY, rightZ;
    f32 playerX, playerY, playerZ;
    s32 j;

    switch (evt_get_variable(N(CreatorScript), RITUAL_VAR_STATE)) {
        case RITUAL_STATE_INIT:
            N(RitualStateTime) = 0;
            evt_set_variable(N(CreatorScript), RITUAL_VAR_STATE, RITUAL_STATE_CARDS_APPEAR);
            N(RitualCards)[0].drawMode = CARD_DRAW_CARD_AND_PLAYER;
            N(RitualCards)[0].pos.x = -200.0f;
            N(RitualCards)[0].pos.y = 0.0f;
            N(RitualCards)[0].pos.z = 0.0f;
            N(RitualCards)[0].pitch = 0.0f;
            N(RitualCards)[0].yaw = 0.0f;
            N(RitualCards)[0].playerSpriteID = 1;
            N(RitualCards)[0].playerRasterIndex = 12;
            N(RitualCards)[0].spriteOffsetX = 2;

            N(RitualCards)[1].drawMode = CARD_DRAW_CARD_AND_PLAYER;
            N(RitualCards)[1].pos.x = 200.0f;
            N(RitualCards)[1].pos.y = 0.0f;
            N(RitualCards)[1].pos.z = 1.0f;
            N(RitualCards)[1].pitch = 0.0f;
            N(RitualCards)[1].yaw = 0.0f;
            N(RitualCards)[1].playerSpriteID = 1;
            N(RitualCards)[1].playerRasterIndex = 48;
            N(RitualCards)[1].spriteOffsetX = 0;

            N(RitualCards)[2].playerSpriteID = 8;
            N(RitualCards)[2].playerRasterIndex = 5;
            N(RitualCards)[2].drawMode = CARD_DRAW_CARD_AND_PLAYER;
            N(RitualCards)[2].pos.x = 0.0f;
            N(RitualCards)[2].pos.y = 200.0f;
            N(RitualCards)[2].pos.z = 2.0f;
            N(RitualCards)[2].pitch = 0.0f;
            N(RitualCards)[2].yaw = 0.0f;
            N(RitualCards)[2].spriteOffsetX = 4;
            break;
        case RITUAL_STATE_CARDS_APPEAR:
            N(RitualStateTime)++;
            N(RitualCards)[0].pos.x += 10.0f;
            N(RitualCards)[1].pos.x += -10.0f;
            N(RitualCards)[2].pos.y += -10.0f;
            if (N(RitualStateTime) == 18) {
                gPlayerStatus.pos.y = NPC_DISPOSE_POS_Y;
            }
            if (N(RitualStateTime) == 20) {
                evt_set_variable(N(CreatorScript), RITUAL_VAR_STATE, RITUAL_STATE_SHUFFLE_CARDS);
                N(RitualStateTime) = 0;
            }
            break;
        case RITUAL_STATE_SHUFFLE_CARDS:
            N(RitualCards)[0].drawMode = CARD_DRAW_SHUFFLE_ANIM;
            N(RitualCards)[1].drawMode = CARD_DRAW_HIDDEN;
            N(RitualCards)[2].drawMode = CARD_DRAW_HIDDEN;
            N(RitualCards)[0].pos.x = 0.0f;
            N(RitualCards)[0].pos.y = 0.0f;
            N(RitualCards)[0].pos.z = 0;
            break;
        case RITUAL_STATE_SPREAD_CARDS:
            N(RitualCards)[0].drawMode = CARD_DRAW_CARD_AND_PLAYER;
            N(RitualCards)[1].drawMode = CARD_DRAW_CARD_AND_PLAYER;
            N(RitualCards)[2].drawMode = CARD_DRAW_CARD_AND_PLAYER;
            N(RitualStateTime)++;
            N(RitualCards)[0].pos.x -= 10.0f;
            N(RitualCards)[1].pos.x += 10.0f;
            if (N(RitualStateTime) == 10) {
                N(RitualStateTime) = 0;
                evt_set_variable(N(CreatorScript), RITUAL_VAR_STATE, RITUAL_STATE_WAIT_BEFORE_REVEAL);
            }
            break;
        case RITUAL_STATE_WAIT_BEFORE_REVEAL:
            N(RitualCards)[0].pos.x = -100.0f;
            N(RitualCards)[0].pos.y = 0.0f;
            N(RitualCards)[0].pos.z = 0;
            N(RitualCards)[1].pos.x = 100.0f;
            N(RitualCards)[1].pos.y = 0.0f;
            N(RitualCards)[1].pos.z = 1.0f;
            N(RitualCards)[2].pos.x = 0;
            N(RitualCards)[2].pos.y = 0.0f;
            N(RitualCards)[2].pos.z = 2.0f;
            N(RitualStateTime)++;
            if (N(RitualStateTime) == 20) {
                N(RitualStateTime) = 0;
                evt_set_variable(N(CreatorScript), RITUAL_VAR_STATE, RITUAL_STATE_REVEAL_LEFT);
                sfx_play_sound_with_params(SOUND_MERLEE_SHOW_CARD, 0, 24, 0);
            }
            break;
        case RITUAL_STATE_REVEAL_LEFT:
            N(RitualCards)[0].yaw += 18.0f;
            N(RitualCards)[1].yaw = 0.0f;
            N(RitualCards)[2].yaw = 0.0f;
            N(RitualStateTime)++;
            if (N(RitualStateTime) == 8) {
                N(GetCardWorldPos)(0, &leftX, &leftY, &leftZ);
                fx_sparkles(0, leftX, leftY + 20.0f, leftZ, 30.0f);
            }
            if (N(RitualStateTime) == 10) {
                N(RitualStateTime) = 0;
                evt_set_variable(N(CreatorScript), RITUAL_VAR_STATE, RITUAL_STATE_REVEAL_MIDDLE);
                sfx_play_sound_with_params(SOUND_MERLEE_SHOW_CARD, 0, 64, 0);
            }
            break;
        case RITUAL_STATE_REVEAL_MIDDLE:
            N(RitualCards)[0].yaw += 18.0f;
            N(RitualCards)[1].yaw = 0.0f;
            N(RitualCards)[2].yaw += 18.0f;
            N(RitualStateTime)++;
            if (N(RitualStateTime) == 8) {
                N(GetCardWorldPos)(2, &middleX, &middleY, &middleZ);
                fx_sparkles(0, middleX, middleY + 20.0f, middleZ, 30.0f);
            }
            if (N(RitualStateTime) == 10) {
                N(RitualStateTime) = 0;
                evt_set_variable(N(CreatorScript), RITUAL_VAR_STATE, RITUAL_STATE_REVEAL_RIGHT);
                sfx_play_sound_with_params(SOUND_MERLEE_SHOW_CARD, 0, 104, 0);
            }
            break;
        case RITUAL_STATE_REVEAL_RIGHT:
            N(RitualCards)[0].yaw = 0.0f;
            N(RitualCards)[1].yaw += 18.0f;
            N(RitualCards)[2].yaw += 18.0f;
            N(RitualStateTime)++;
            if (N(RitualStateTime) == 8) {
                N(GetCardWorldPos)(1, &rightX, &rightY, &rightZ);
                fx_sparkles(0, rightX, rightY + 20.0f, rightZ, 30.0f);
            }
            if (N(RitualStateTime) == 10) {
                N(RitualStateTime) = 0;
                evt_set_variable(N(CreatorScript), RITUAL_VAR_STATE, RITUAL_STATE_FINISH_RIGHT_FLIP);
            }
            break;
        case RITUAL_STATE_FINISH_RIGHT_FLIP:
            N(RitualCards)[0].yaw = 0.0f;
            N(RitualCards)[1].yaw += 18.0f;
            N(RitualCards)[2].yaw = 0.0f;
            N(RitualStateTime)++;
            if (N(RitualStateTime) == 10) {
                N(RitualStateTime) = 0;
                evt_set_variable(N(CreatorScript), RITUAL_VAR_STATE, RITUAL_STATE_GATHER_CARDS);
            }
            break;
        case RITUAL_STATE_GATHER_CARDS:
            N(RitualCards)[0].pos.x += 10.0f;
            N(RitualCards)[0].pos.y = 0.0f;
            N(RitualCards)[0].yaw = 0.0f;
            N(RitualCards)[1].pos.x -= 10.0f;
            N(RitualCards)[1].pos.y = 0.0f;
            N(RitualCards)[1].yaw = 0.0f;
            N(RitualCards)[2].pos.x = 0;
            N(RitualCards)[2].pos.y = 0.0f;
            N(RitualCards)[2].yaw = 0.0f;
            N(RitualStateTime)++;
            if (N(RitualStateTime) == 10) {
                N(RitualStateTime) = 0;
                evt_set_variable(N(CreatorScript), RITUAL_VAR_STATE, RITUAL_STATE_MERGE_CARDS);
                return;
            }
            break;
        case RITUAL_STATE_MERGE_CARDS:
            N(RitualCards)[0].drawMode = CARD_DRAW_MERGE_ANIM;
            N(RitualCards)[0].playerSpriteID = 8;
            N(RitualCards)[1].drawMode = CARD_DRAW_HIDDEN;
            N(RitualCards)[2].drawMode = CARD_DRAW_HIDDEN;
            N(RitualCards)[0].playerRasterIndex = 0x11;
            return;
        case RITUAL_STATE_BEGIN_RELEASE_PLAYER:
            N(RitualCards)[0].drawMode = CARD_DRAW_CARD_ONLY;
            N(RitualCards)[1].drawMode = CARD_DRAW_PLAYER_ONLY;
            N(RitualCards)[1].playerSpriteID = 8;
            N(RitualCards)[0].pos.x = 0.0f;
            N(RitualCards)[0].pos.z = 0;
            N(RitualCards)[1].pos.x = 0.0f;
            N(RitualCards)[1].pos.z = 0;
            N(RitualCards)[1].playerRasterIndex = 10;
            N(RitualCards)[1].spriteOffsetX = 0;
            N(RitualStateTime) = 0;
            N(RitualCards)[0].pos.y = 68.0f;
            N(RitualCards)[0].yaw = 180.0f;
            N(RitualCards)[1].pos.y = 68.0f;
            N(RitualCards)[1].yaw = 180.0f;
            evt_set_variable(N(CreatorScript), RITUAL_VAR_STATE, RITUAL_STATE_RELEASE_PLAYER);
            N(CardRiseSpeed) = 0.0f;
            N(PlayerFallSpeed) = 1.0f;

            N(GetCardWorldPos)(1, &playerX, &playerY, &playerZ);

            for (j = 0; j < ARRAY_COUNT(N(ReleaseEnergyFX)); j++) {
                s32 i;

                N(ReleaseEnergyFX)[j] = fx_energy_in_out(2, playerX, playerY + 20.0f, playerZ, 8.0f, -1);
                N(ReleaseEnergyFX)[j]->data.energyInOut->unk_28 = 215;
                N(ReleaseEnergyFX)[j]->data.energyInOut->unk_2C = 55;
                N(ReleaseEnergyFX)[j]->data.energyInOut->unk_30 = 255;

                for (i = 1; i < N(ReleaseEnergyFX)[j]->numParts; i++) {
                    N(ReleaseEnergyFX)[j]->data.energyInOut[i].unk_38 *= 0.1;
                }
            }
            break;
        case RITUAL_STATE_RELEASE_PLAYER:
            N(GetCardWorldPos)(1, &playerX, &playerY, &playerZ);

            for (j = 0; j < ARRAY_COUNT(N(ReleaseEnergyFX)); j++) {
                s32 i;

                N(ReleaseEnergyFX)[j]->data.energyInOut->pos.x = playerX;
                N(ReleaseEnergyFX)[j]->data.energyInOut->pos.y = playerY + 20.0f;
                N(ReleaseEnergyFX)[j]->data.energyInOut->pos.z = playerZ;
                N(ReleaseEnergyFX)[j]->data.energyInOut->scale -= 0.1;

                if (N(ReleaseEnergyFX)[j]->data.energyInOut->scale < 0.1) {
                    N(ReleaseEnergyFX)[j]->data.energyInOut->scale = 0.1f;
                }

                for (i = 1; i < N(ReleaseEnergyFX)[j]->numParts; i++) {
                    N(ReleaseEnergyFX)[j]->data.energyInOut[i].unk_38 += 0.01;
                }
            }

            N(RitualCards)[0].pos.y += N(CardRiseSpeed);
            N(RitualCards)[1].pos.y += N(PlayerFallSpeed);
            N(CardRiseSpeed) += 0.4;
            N(PlayerFallSpeed) -= 0.05;
            N(RitualStateTime)++;

            if (N(RitualCards)[1].pos.y < -5.0f) {
                N(RitualCards)[1].pos.y = -5.0f;
                N(RitualStateTime) = 0;
                evt_set_variable(N(CreatorScript), RITUAL_VAR_STATE, RITUAL_STATE_COMPLETE);
                N(RitualCards)[0].drawMode = CARD_DRAW_HIDDEN;
                N(RitualCards)[1].drawMode = CARD_DRAW_HIDDEN;
                N(GetCardWorldPos)(1, &playerX, &playerY, &playerZ);
                fx_sparkles(0, playerX, playerY + 20.0f, playerZ, 30.0f);
                sfx_play_sound(SOUND_MERLEE_COMPLETE_SPELL);

                for (j = 0; j < ARRAY_COUNT(N(ReleaseEnergyFX)); j++) {
                    N(ReleaseEnergyFX)[j]->flags |= FX_INSTANCE_FLAG_DISMISS;
                }
            }
            break;
        case RITUAL_STATE_COMPLETE:
            break;
    }
}

void N(RenderRitualCards)(void) {
    Matrix4f mtx;
    s32 animResult;

    guPositionF(mtx, 0.0f, -gCameras[gCurrentCameraID].curYaw, 0.0f, SPRITE_WORLD_SCALE_F,
                evt_get_variable(N(CreatorScript), RITUAL_VAR_POS_X),
                evt_get_variable(N(CreatorScript), RITUAL_VAR_POS_Y),
                evt_get_variable(N(CreatorScript), RITUAL_VAR_POS_Z));

    animResult = N(AppendGfx_RitualCard)(&N(RitualCards)[0], mtx);
    N(AppendGfx_RitualCard)(&N(RitualCards)[1], mtx);
    N(AppendGfx_RitualCard)(&N(RitualCards)[2], mtx);

    // communicate when the ImgFX animations are done to the owner script
    if (N(RitualCards)[0].drawMode == CARD_DRAW_SHUFFLE_ANIM
        && (animResult == IMGFX_RENDER_RESULT_DONE || animResult == IMGFX_RENDER_RESULT_HOLDING)
    ) {
        evt_set_variable(N(CreatorScript), RITUAL_VAR_STATE, RITUAL_STATE_SPREAD_CARDS);
    }
    if (N(RitualCards)[0].drawMode == CARD_DRAW_MERGE_ANIM
        && (animResult == IMGFX_RENDER_RESULT_DONE || animResult == IMGFX_RENDER_RESULT_HOLDING)
    ) {
        evt_set_variable(N(CreatorScript), RITUAL_VAR_STATE, RITUAL_STATE_BEGIN_RELEASE_PLAYER);
    }
}

API_CALLABLE(N(PlayShuffleSoundLeft)) {
    sfx_play_sound_with_params(SOUND_SHUFFLE_CARD_A, 0, 24, 0);
    return ApiStatus_DONE2;
}

API_CALLABLE(N(PlayShuffleSoundRight)) {
    sfx_play_sound_with_params(SOUND_SHUFFLE_CARD_B, 0, 104, 0);
    return ApiStatus_DONE2;
}

EvtScript N(EVS_PerformRitual) = {
    UseArray(Ref(N(RitualBuffer)))
    Set(RITUAL_VAR_STATE, RITUAL_STATE_INIT)
    Call(GetNpcPos, NPC_Merlee, RITUAL_VAR_POS_X, RITUAL_VAR_POS_Y, RITUAL_VAR_POS_Z)
    Add(RITUAL_VAR_POS_X, 60)
    Add(RITUAL_VAR_POS_Z, 0)
    Call(PlaySoundAtNpc, NPC_Merlee, SOUND_MERLEE_TWIRL, SOUND_SPACE_DEFAULT)
    Thread
        Call(MakeLerp, 720, 0, 60, EASING_LINEAR)
        Loop(0)
            Call(UpdateLerp)
            Call(SetNpcRotation, NPC_Merlee, 0, LVar0, 0)
            IfGt(LVar0, 360)
                Add(LVar0, -360)
            EndIf
            Switch(LVar0)
                CaseRange(90, 270)
                    Set(LVar2, ANIM_WorldMerlee_SpinBack)
                CaseDefault
                    Set(LVar2, ANIM_WorldMerlee_SpinFront)
            EndSwitch
            Call(SetNpcAnimation, NPC_Merlee, LVar2)
            Wait(1)
            IfEq(LVar1, 0)
                BreakLoop
            EndIf
        EndLoop
        Call(SetNpcRotation, NPC_Merlee, 0, 0, 0)
        Call(SetNpcAnimation, NPC_Merlee, ANIM_WorldMerlee_Gather)
        Wait(200)
        Call(SetNpcAnimation, NPC_Merlee, ANIM_WorldMerlee_Bow)
        Wait(40)
        Call(SetNpcAnimation, NPC_Merlee, ANIM_WorldMerlee_Gather)
        Wait(75)
        Call(SetNpcAnimation, NPC_Merlee, ANIM_WorldMerlee_Release)
    EndThread
    Wait(60)
    Call(PlaySoundAtNpc, NPC_Merlee, SOUND_MERLEE_GATHER_ENERGY, SOUND_SPACE_DEFAULT)
    Set(LVar0, RITUAL_VAR_POS_Y)
    Add(LVar0, 25)
    PlayEffect(EFFECT_RADIATING_ENERGY_ORB, 0, RITUAL_VAR_POS_X, LVar0, RITUAL_VAR_POS_Z, 1, -1)
    Set(RITUAL_VAR_ORB_EFFECT, LVarF)
    Thread
        Wait(30)
        Call(DismissEffect, RITUAL_VAR_ORB_EFFECT)
    EndThread
    Call(N(DarkenWorld))
    Call(DisablePlayerPhysics, true)
    Call(InterpPlayerYaw, 0, 0)
    Call(N(CreateRitualCards))
    Thread
        Loop(0)
            IfEq(RITUAL_VAR_STATE, RITUAL_STATE_SHUFFLE_CARDS)
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
        Call(PlaySound, SOUND_SEQ_SHUFFLE_CARD)
        Wait(10)
        Call(PlaySound, SOUND_SEQ_SHUFFLE_CARD)
        Wait(9)
        Call(PlaySound, SOUND_SEQ_SHUFFLE_CARD)
        Wait(4)
        Call(PlaySound, SOUND_SEQ_SHUFFLE_CARD)
        Wait(4)
        Call(PlaySound, SOUND_SEQ_SHUFFLE_CARD)
        Wait(3)
        Call(PlaySound, SOUND_SEQ_SHUFFLE_CARD)
        Wait(2)
        Call(PlaySound, SOUND_SEQ_SHUFFLE_CARD)
        Wait(2)
        Call(PlaySound, SOUND_SEQ_SHUFFLE_CARD)
        Wait(2)
        Call(PlaySound, SOUND_SEQ_SHUFFLE_CARD)
        Wait(3)
        Call(PlaySound, SOUND_SEQ_SHUFFLE_CARD)
        Wait(2)
        Call(PlaySound, SOUND_SEQ_SHUFFLE_CARD)
        Wait(6)
        Call(PlaySound, SOUND_SEQ_SHUFFLE_CARD)
        Wait(3)
        Call(PlaySound, SOUND_SEQ_SHUFFLE_CARD)
        Wait(3)
        Call(PlaySound, SOUND_SEQ_SHUFFLE_CARD)
        Wait(3)
        Call(PlaySound, SOUND_SEQ_SHUFFLE_CARD)
        Wait(3)
        Call(PlaySound, SOUND_SEQ_SHUFFLE_CARD)
    EndThread
    Thread
        Loop(0)
            IfGe(RITUAL_VAR_STATE, RITUAL_STATE_SPREAD_CARDS)
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
        Wait(9)
        Call(N(PlayShuffleSoundLeft))
        Wait(2)
        Call(N(PlayShuffleSoundRight))
        Loop(0)
            IfGe(RITUAL_VAR_STATE, RITUAL_STATE_MERGE_CARDS)
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
        Wait(3)
        Call(PlaySound, SOUND_MERLEE_GATHER_CARDS)
        Loop(0)
            IfGe(RITUAL_VAR_STATE, RITUAL_STATE_BEGIN_RELEASE_PLAYER)
                BreakLoop
            EndIf
            Wait(1)
        EndLoop
        Wait(15)
        Call(PlaySound, SOUND_MERLEE_RELEASE_PLAYER)
    EndThread
    Loop(0)
        IfEq(RITUAL_VAR_STATE, RITUAL_STATE_COMPLETE)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Call(SetPlayerPos, RITUAL_VAR_POS_X, RITUAL_VAR_POS_Y, RITUAL_VAR_POS_Z)
    Call(SetPlayerAnimation, ANIM_Mario1_UsePower)
    Wait(1)
    Call(SetPlayerPos, RITUAL_VAR_POS_X, RITUAL_VAR_POS_Y, RITUAL_VAR_POS_Z)
    Wait(1)
    Call(DisablePlayerPhysics, false)
    Call(N(DestroyRitualCards))
    Thread
        Call(N(UndarkenWorld))
    EndThread
    Return
    End
};

EvtScript N(EVS_BeginMerleeCamera) = {
    Call(GetNpcPos, NPC_Merlee, LVar0, LVar1, LVar2)
    Call(UseSettingsFrom, CAM_DEFAULT, LVar0, LVar1, LVar2)
    Call(SetCamDistance, CAM_DEFAULT, 200)
    Call(SetPanTarget, CAM_DEFAULT, LVar0, LVar1, LVar2)
    Call(SetCamSpeed, CAM_DEFAULT, Float(8.0))
    Call(SetCamPitch, CAM_DEFAULT, 20, -15)
    Call(PanToTarget, CAM_DEFAULT, 0, true)
    Call(WaitForCam, CAM_DEFAULT, Float(1.0))
    Return
    End
};

EvtScript N(EVS_EndMerleeCamera) = {
    Call(PanToTarget, CAM_DEFAULT, 0, false)
    Call(SetCamSpeed, CAM_DEFAULT, Float(3.0))
    Call(WaitForCam, CAM_DEFAULT, Float(1.0))
    Return
    End
};

EvtScript N(EVS_NpcInteract_Merlee) = {
    Call(SetPartnerForcedFollowMode, 1)
    ExecWait(N(EVS_BeginMerleeCamera))
    Set(LVar0, 0)
    IfEq(GB_KootFavor_Current, KOOT_FAVOR_CH4_1)
        Add(LVar0, 1)
    EndIf
    IfEq(GF_HOS06_MerluvleeRequestedCrystalBall, 1)
        Add(LVar0, 1)
    EndIf
    IfEq(GF_DRO01_Gift_CrystalBall, 0)
        Add(LVar0, 1)
    EndIf
    IfEq(LVar0, 3)
        Call(SpeakToPlayer, NPC_SELF, ANIM_WorldMerlee_Talk, ANIM_WorldMerlee_Idle, 0, MSG_CH2_00DC)
        EVT_GIVE_REWARD(ITEM_CRYSTAL_BALL)
        Set(GF_DRO01_Gift_CrystalBall, 1)
        Wait(20)
        Call(SetPartnerForcedFollowMode, 0)
        ExecWait(N(EVS_EndMerleeCamera))
        Return
    EndIf
    Call(SpeakToPlayer, NPC_SELF, ANIM_WorldMerlee_Talk, ANIM_WorldMerlee_Idle, 0, MSG_CH2_00D6)
    Call(ShowChoice, MSG_Choice_0011)
    IfNe(LVar0, 0)
        Call(ContinueSpeech, -1, ANIM_WorldMerlee_Talk, ANIM_WorldMerlee_Idle, 0, MSG_CH2_00D7)
        Call(SetPartnerForcedFollowMode, 0)
        ExecWait(N(EVS_EndMerleeCamera))
        Return
    EndIf
    Call(ContinueSpeech, -1, ANIM_WorldMerlee_Talk, ANIM_WorldMerlee_Idle, 0, MSG_CH2_00D8)
    Call(ShowCoinCounter, 1)
    Call(ShowChoice, MSG_Choice_0018)
    Call(ShowCoinCounter, 0)
    IfEq(LVar0, 3)
        Call(ContinueSpeech, -1, ANIM_WorldMerlee_Talk, ANIM_WorldMerlee_Idle, 0, MSG_CH2_00D7)
        Call(SetPartnerForcedFollowMode, 0)
        ExecWait(N(EVS_EndMerleeCamera))
        Return
    EndIf
    Call(N(TryEnchantPlayer), LVar0, LVar1)
    IfNe(LVar1, 0)
        Call(ContinueSpeech, -1, ANIM_WorldMerlee_Talk, ANIM_WorldMerlee_Idle, 0, MSG_CH2_00D9)
        Call(SetPartnerForcedFollowMode, 0)
        ExecWait(N(EVS_EndMerleeCamera))
        Return
    EndIf
    Call(ContinueSpeech, -1, ANIM_WorldMerlee_Talk, ANIM_WorldMerlee_Idle, 0, MSG_CH2_00DA)
    Call(SetMusic, 0, SONG_MERLEE_SPELL, 0, VOL_LEVEL_FULL)
    Call(DisablePartnerAI, false)
    Call(SetNpcAnimation, NPC_PARTNER, PARTNER_ANIM_IDLE)
    ExecGetTID(N(EVS_PerformRitual), LVar9)
    Loop(0)
        IsThreadRunning(LVar9, LVar1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Wait(60)
    Call(SetNpcAnimation, 4, ANIM_WorldMerlee_Idle)
    Call(PlayerMoveTo, -100, -370, 8)
    Call(SpeakToPlayer, NPC_SELF, ANIM_WorldMerlee_Talk, ANIM_WorldMerlee_Idle, 0, MSG_CH2_00DB)
    Exec(N(EVS_SetupMusic))
    Call(EnablePartnerAI)
    Call(SetPartnerForcedFollowMode, 0)
    ExecWait(N(EVS_EndMerleeCamera))
    Return
    End
};
