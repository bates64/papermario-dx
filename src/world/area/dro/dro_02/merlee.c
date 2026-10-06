#include "dro_02.h"
#include "model.h"
#include "entity.h"
#include "sprite.h"
#include "effects.h"
#include "sprite/player.h"
#include "include_asset.h"

BSS f32 CardRiseSpeed;
BSS f32 PlayerFallSpeed;
BSS s32 RitualStateTime;
BSS EffectInstance* ReleaseEnergyFX[4];

// a dro_02_card can draw itself, with or without the player; or one of the shuffle/merge ImgFX animations
typedef struct RitualCard {
    /* 0x00 */ s32 drawMode;
    /* 0x04 */ Vec3f pos;
    /* 0x10 */ f32 yaw;
    /* 0x14 */ f32 pitch;
    /* 0x18 */ s32 playerSpriteID;
    /* 0x1C */ s32 playerRasterIndex;
    /* 0x20 */ s32 spriteOffsetX;
} RitualCard; // size = 0x24

BSS Evt* CreatorScript;

// shared storage used by the event script and the dro_02_card worker
BSS s32 RitualBuffer[16];

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
BSS RitualCard RitualCards[3];

s8 MerleeSpellCasts[] = {
    20, 10, 5, 0,
};

s8 MerleeCoinCosts[] = {
    50, 20, 5, 0,
};

INCLUDE_IMG("world/area/dro/dro_02/card.png", dro_02_card);
INCLUDE_PAL("world/area/dro/dro_02/card.pal", dro_02_card_pal);
#include "world/area/dro/dro_02/card_1.vtx.inc.c"
#include "world/area/dro/dro_02/card_2.vtx.inc.c"
#include "world/area/dro/dro_02/card_setup.gfx.inc.c"
#include "world/area/dro/dro_02/card_1.gfx.inc.c"
#include "world/area/dro/dro_02/card_2.gfx.inc.c"

void UpdateRitualCards(void);
void RenderRitualCards(void);

API_CALLABLE(TryEnchantPlayer) {
    PlayerData* playerData = &gPlayerData;
    Bytecode* args = script->ptrReadPos;
    s32 tier = evt_get_variable(script, *args++);
    s32 outPrevented = *args++;
    u8 coins = MerleeCoinCosts[tier];
    u8 casts = MerleeSpellCasts[tier];

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

API_CALLABLE(DarkenWorld) {
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

API_CALLABLE(UndarkenWorld) {
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

API_CALLABLE(CreateRitualCards) {
    s32 imgfxIdx;

    CreatorScript = script;

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
        UpdateRitualCards,
        RenderRitualCards));
    return ApiStatus_DONE2;
}

API_CALLABLE(DestroyRitualCards) {
    imgfx_release_instance(evt_get_variable(script, RITUAL_VAR_SHUFFLE_IMGFX));
    imgfx_release_instance(evt_get_variable(script, RITUAL_VAR_FLIP1_IMGFX));
    imgfx_release_instance(evt_get_variable(script, RITUAL_VAR_FLIP2_IMGFX));
    imgfx_release_instance(evt_get_variable(script, RITUAL_VAR_FLIP3_IMGFX));
    free_worker(evt_get_variable(script, RITUAL_VAR_WORKER));
    return ApiStatus_DONE2;
}

s32 AppendGfx_RitualCard(RitualCard* dro_02_card, Matrix4f mtxParent) {
    Matrix4f mtxTransform;
    Matrix4f mtxTemp;
    ImgFXTexture ifxImg;
    SpriteRasterInfo rasterInfo;
    s32 animResult;

    // resolves a deadlock where imgfx_appendGfx_component would exit early if uninitialized
    ifxImg.alpha = 255;

    if (dro_02_card->drawMode == CARD_DRAW_HIDDEN) {
        return IMGFX_RENDER_RESULT_DONE;
    }

    gSPDisplayList(gMainGfxPos++, dro_02_card_setup_gfx);

    if (dro_02_card->drawMode == CARD_DRAW_CARD_AND_PLAYER
        || dro_02_card->drawMode == CARD_DRAW_CARD_ONLY
        || dro_02_card->drawMode == CARD_DRAW_PLAYER_ONLY
    ) {
        guTranslateF(mtxTemp, dro_02_card->pos.x, dro_02_card->pos.y, dro_02_card->pos.z);
        guMtxCatF(mtxTemp, mtxParent, mtxTransform);
        guRotateF(mtxTemp, dro_02_card->yaw, 0.0f, 1.0f, 0.0f);
        guMtxCatF(mtxTemp, mtxTransform, mtxTransform);
        guRotateF(mtxTemp, dro_02_card->pitch, 1.0f, 0.0f, 0.0f);
        guMtxCatF(mtxTemp, mtxTransform, mtxTransform);
        guMtxF2L(mtxTransform, &gDisplayContext->matrixStack[gMatrixListPos]);
        gSPMatrix(gMainGfxPos++, VIRTUAL_TO_PHYSICAL(&gDisplayContext->matrixStack[gMatrixListPos++]), G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        // draw dro_02_card
        if (dro_02_card->drawMode == CARD_DRAW_CARD_AND_PLAYER || dro_02_card->drawMode == CARD_DRAW_CARD_ONLY) {
            gSPDisplayList(gMainGfxPos++, dro_02_card_1_gfx);
        }

        // draw player
        if (dro_02_card->drawMode == CARD_DRAW_CARD_AND_PLAYER || dro_02_card->drawMode == CARD_DRAW_PLAYER_ONLY) {
            spr_get_player_raster_info(&rasterInfo, dro_02_card->playerSpriteID, dro_02_card->playerRasterIndex);
            gDPSetTextureLUT(gMainGfxPos++, G_TT_RGBA16);
            gDPLoadTLUT_pal16(gMainGfxPos++, 0, rasterInfo.defaultPal);
            gDPLoadTextureTile_4b(gMainGfxPos++, rasterInfo.raster, G_IM_FMT_CI, rasterInfo.width, rasterInfo.height,
                                    0, 0, rasterInfo.width - 1, rasterInfo.height - 1, 0,
                                    G_TX_CLAMP, G_TX_CLAMP, 8, 8, G_TX_NOLOD, G_TX_NOLOD);
            guTranslateF(mtxTransform, dro_02_card->spriteOffsetX + 30 - rasterInfo.width / 2, 0.0f, 0.0f);
            guMtxF2L(mtxTransform, &gDisplayContext->matrixStack[gMatrixListPos]);
            gSPMatrix(gMainGfxPos++, VIRTUAL_TO_PHYSICAL(&gDisplayContext->matrixStack[gMatrixListPos++]), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
            gSPDisplayList(gMainGfxPos++, dro_02_card_2_gfx);
            gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
        }
        gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
        return IMGFX_RENDER_RESULT_DONE;
    }

    if (dro_02_card->drawMode == CARD_DRAW_SHUFFLE_ANIM) {
        gDPSetTileSize(gMainGfxPos++, G_TX_RENDERTILE, 256 * 4, 256 * 4, 287 * 4, 287 * 4);
        guTranslateF(mtxTemp, RitualCards[0].pos.x, RitualCards[0].pos.y, RitualCards[0].pos.z);
        guMtxCatF(mtxTemp, mtxParent, mtxTransform);
        guMtxF2L(mtxTransform, &gDisplayContext->matrixStack[gMatrixListPos]);
        gSPMatrix(gMainGfxPos++, VIRTUAL_TO_PHYSICAL(&gDisplayContext->matrixStack[gMatrixListPos++]), G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        animResult = imgfx_appendGfx_component(evt_get_variable(CreatorScript, RITUAL_VAR_SHUFFLE_IMGFX), &ifxImg, IMGFX_FLAG_SKIP_GFX_SETUP | IMGFX_FLAG_SKIP_TEX_SETUP, mtxTransform);
        gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
        return animResult;
    }

    if (dro_02_card->drawMode == CARD_DRAW_MERGE_ANIM) {
        gDPSetTileSize(gMainGfxPos++, G_TX_RENDERTILE, 256 * 4, 256 * 4, 287 * 4, 287 * 4);
        guTranslateF(mtxTemp, RitualCards[0].pos.x, RitualCards[0].pos.y, RitualCards[0].pos.z);
        guMtxCatF(mtxTemp, mtxParent, mtxTransform);
        guMtxF2L(mtxTransform, &gDisplayContext->matrixStack[gMatrixListPos]);
        gSPMatrix(gMainGfxPos++, VIRTUAL_TO_PHYSICAL(&gDisplayContext->matrixStack[gMatrixListPos++]), G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        imgfx_appendGfx_component(evt_get_variable(CreatorScript, RITUAL_VAR_FLIP1_IMGFX), &ifxImg, IMGFX_FLAG_SKIP_GFX_SETUP | IMGFX_FLAG_SKIP_TEX_SETUP, mtxTransform);
        imgfx_appendGfx_component(evt_get_variable(CreatorScript, RITUAL_VAR_FLIP2_IMGFX), &ifxImg, IMGFX_FLAG_SKIP_GFX_SETUP | IMGFX_FLAG_SKIP_TEX_SETUP, mtxTransform);
        gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
        guTranslateF(mtxTemp, RitualCards[0].pos.x, RitualCards[0].pos.y, RitualCards[0].pos.z);
        guMtxCatF(mtxTemp, mtxParent, mtxTransform);
        guMtxF2L(mtxTransform, &gDisplayContext->matrixStack[gMatrixListPos]);
        gSPMatrix(gMainGfxPos++, VIRTUAL_TO_PHYSICAL(&gDisplayContext->matrixStack[gMatrixListPos++]), G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        spr_get_player_raster_info(&rasterInfo, dro_02_card->playerSpriteID, dro_02_card->playerRasterIndex);
        ifxImg.raster = rasterInfo.raster;
        ifxImg.palette = rasterInfo.defaultPal;
        ifxImg.width = rasterInfo.width;
        ifxImg.height = rasterInfo.height;
        ifxImg.xOffset = -(rasterInfo.width / 2);
        ifxImg.yOffset = rasterInfo.height / 2;
        ifxImg.alpha = 255;
        animResult = imgfx_appendGfx_component(evt_get_variable(CreatorScript, RITUAL_VAR_FLIP3_IMGFX), &ifxImg, IMGFX_FLAG_SKIP_GFX_SETUP, mtxTransform);
        gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
        return animResult;
    }

    return IMGFX_RENDER_RESULT_DONE;
}

void GetCardWorldPos(s32 index, f32* outX, f32* outY, f32* outZ) {
    RitualCard* dro_02_card;
    Matrix4f mtxTransform;
    Matrix4f mtxTemp;
    Matrix4f mtxParent;

    guPositionF(mtxParent, 0.0f, -gCameras[gCurrentCameraID].curYaw, 0.0f, SPRITE_WORLD_SCALE_F,
                evt_get_variable(CreatorScript, RITUAL_VAR_POS_X),
                evt_get_variable(CreatorScript, RITUAL_VAR_POS_Y),
                evt_get_variable(CreatorScript, RITUAL_VAR_POS_Z));

    dro_02_card = &RitualCards[index];
    guTranslateF(mtxTemp, dro_02_card->pos.x, dro_02_card->pos.y, dro_02_card->pos.z);
    guMtxCatF(mtxTemp, mtxParent, mtxTransform);
    guRotateF(mtxTemp, dro_02_card->yaw, 0.0f, 1.0f, 0.0f);
    guMtxCatF(mtxTemp, mtxTransform, mtxTransform);
    guTranslateF(mtxTemp, 0.0f, 0.0f, 1.0f);
    guMtxCatF(mtxTemp, mtxTransform, mtxTransform);
    *outX = mtxTransform[3][0];
    *outY = mtxTransform[3][1];
    *outZ = mtxTransform[3][2];
}

void UpdateRitualCards(void) {
    f32 leftX, leftY, leftZ;
    f32 middleX, middleY, middleZ;
    f32 rightX, rightY, rightZ;
    f32 playerX, playerY, playerZ;
    s32 j;

    switch (evt_get_variable(CreatorScript, RITUAL_VAR_STATE)) {
        case RITUAL_STATE_INIT:
            RitualStateTime = 0;
            evt_set_variable(CreatorScript, RITUAL_VAR_STATE, RITUAL_STATE_CARDS_APPEAR);
            RitualCards[0].drawMode = CARD_DRAW_CARD_AND_PLAYER;
            RitualCards[0].pos.x = -200.0f;
            RitualCards[0].pos.y = 0.0f;
            RitualCards[0].pos.z = 0.0f;
            RitualCards[0].pitch = 0.0f;
            RitualCards[0].yaw = 0.0f;
            RitualCards[0].playerSpriteID = 1;
            RitualCards[0].playerRasterIndex = 12;
            RitualCards[0].spriteOffsetX = 2;

            RitualCards[1].drawMode = CARD_DRAW_CARD_AND_PLAYER;
            RitualCards[1].pos.x = 200.0f;
            RitualCards[1].pos.y = 0.0f;
            RitualCards[1].pos.z = 1.0f;
            RitualCards[1].pitch = 0.0f;
            RitualCards[1].yaw = 0.0f;
            RitualCards[1].playerSpriteID = 1;
            RitualCards[1].playerRasterIndex = 48;
            RitualCards[1].spriteOffsetX = 0;

            RitualCards[2].playerSpriteID = 8;
            RitualCards[2].playerRasterIndex = 5;
            RitualCards[2].drawMode = CARD_DRAW_CARD_AND_PLAYER;
            RitualCards[2].pos.x = 0.0f;
            RitualCards[2].pos.y = 200.0f;
            RitualCards[2].pos.z = 2.0f;
            RitualCards[2].pitch = 0.0f;
            RitualCards[2].yaw = 0.0f;
            RitualCards[2].spriteOffsetX = 4;
            break;
        case RITUAL_STATE_CARDS_APPEAR:
            RitualStateTime++;
            RitualCards[0].pos.x += 10.0f;
            RitualCards[1].pos.x += -10.0f;
            RitualCards[2].pos.y += -10.0f;
            if (RitualStateTime == 18) {
                gPlayerStatus.pos.y = NPC_DISPOSE_POS_Y;
            }
            if (RitualStateTime == 20) {
                evt_set_variable(CreatorScript, RITUAL_VAR_STATE, RITUAL_STATE_SHUFFLE_CARDS);
                RitualStateTime = 0;
            }
            break;
        case RITUAL_STATE_SHUFFLE_CARDS:
            RitualCards[0].drawMode = CARD_DRAW_SHUFFLE_ANIM;
            RitualCards[1].drawMode = CARD_DRAW_HIDDEN;
            RitualCards[2].drawMode = CARD_DRAW_HIDDEN;
            RitualCards[0].pos.x = 0.0f;
            RitualCards[0].pos.y = 0.0f;
            RitualCards[0].pos.z = 0;
            break;
        case RITUAL_STATE_SPREAD_CARDS:
            RitualCards[0].drawMode = CARD_DRAW_CARD_AND_PLAYER;
            RitualCards[1].drawMode = CARD_DRAW_CARD_AND_PLAYER;
            RitualCards[2].drawMode = CARD_DRAW_CARD_AND_PLAYER;
            RitualStateTime++;
            RitualCards[0].pos.x -= 10.0f;
            RitualCards[1].pos.x += 10.0f;
            if (RitualStateTime == 10) {
                RitualStateTime = 0;
                evt_set_variable(CreatorScript, RITUAL_VAR_STATE, RITUAL_STATE_WAIT_BEFORE_REVEAL);
            }
            break;
        case RITUAL_STATE_WAIT_BEFORE_REVEAL:
            RitualCards[0].pos.x = -100.0f;
            RitualCards[0].pos.y = 0.0f;
            RitualCards[0].pos.z = 0;
            RitualCards[1].pos.x = 100.0f;
            RitualCards[1].pos.y = 0.0f;
            RitualCards[1].pos.z = 1.0f;
            RitualCards[2].pos.x = 0;
            RitualCards[2].pos.y = 0.0f;
            RitualCards[2].pos.z = 2.0f;
            RitualStateTime++;
            if (RitualStateTime == 20) {
                RitualStateTime = 0;
                evt_set_variable(CreatorScript, RITUAL_VAR_STATE, RITUAL_STATE_REVEAL_LEFT);
                sfx_play_sound_with_params(SOUND_MERLEE_SHOW_CARD, 0, 24, 0);
            }
            break;
        case RITUAL_STATE_REVEAL_LEFT:
            RitualCards[0].yaw += 18.0f;
            RitualCards[1].yaw = 0.0f;
            RitualCards[2].yaw = 0.0f;
            RitualStateTime++;
            if (RitualStateTime == 8) {
                GetCardWorldPos(0, &leftX, &leftY, &leftZ);
                fx_sparkles(0, leftX, leftY + 20.0f, leftZ, 30.0f);
            }
            if (RitualStateTime == 10) {
                RitualStateTime = 0;
                evt_set_variable(CreatorScript, RITUAL_VAR_STATE, RITUAL_STATE_REVEAL_MIDDLE);
                sfx_play_sound_with_params(SOUND_MERLEE_SHOW_CARD, 0, 64, 0);
            }
            break;
        case RITUAL_STATE_REVEAL_MIDDLE:
            RitualCards[0].yaw += 18.0f;
            RitualCards[1].yaw = 0.0f;
            RitualCards[2].yaw += 18.0f;
            RitualStateTime++;
            if (RitualStateTime == 8) {
                GetCardWorldPos(2, &middleX, &middleY, &middleZ);
                fx_sparkles(0, middleX, middleY + 20.0f, middleZ, 30.0f);
            }
            if (RitualStateTime == 10) {
                RitualStateTime = 0;
                evt_set_variable(CreatorScript, RITUAL_VAR_STATE, RITUAL_STATE_REVEAL_RIGHT);
                sfx_play_sound_with_params(SOUND_MERLEE_SHOW_CARD, 0, 104, 0);
            }
            break;
        case RITUAL_STATE_REVEAL_RIGHT:
            RitualCards[0].yaw = 0.0f;
            RitualCards[1].yaw += 18.0f;
            RitualCards[2].yaw += 18.0f;
            RitualStateTime++;
            if (RitualStateTime == 8) {
                GetCardWorldPos(1, &rightX, &rightY, &rightZ);
                fx_sparkles(0, rightX, rightY + 20.0f, rightZ, 30.0f);
            }
            if (RitualStateTime == 10) {
                RitualStateTime = 0;
                evt_set_variable(CreatorScript, RITUAL_VAR_STATE, RITUAL_STATE_FINISH_RIGHT_FLIP);
            }
            break;
        case RITUAL_STATE_FINISH_RIGHT_FLIP:
            RitualCards[0].yaw = 0.0f;
            RitualCards[1].yaw += 18.0f;
            RitualCards[2].yaw = 0.0f;
            RitualStateTime++;
            if (RitualStateTime == 10) {
                RitualStateTime = 0;
                evt_set_variable(CreatorScript, RITUAL_VAR_STATE, RITUAL_STATE_GATHER_CARDS);
            }
            break;
        case RITUAL_STATE_GATHER_CARDS:
            RitualCards[0].pos.x += 10.0f;
            RitualCards[0].pos.y = 0.0f;
            RitualCards[0].yaw = 0.0f;
            RitualCards[1].pos.x -= 10.0f;
            RitualCards[1].pos.y = 0.0f;
            RitualCards[1].yaw = 0.0f;
            RitualCards[2].pos.x = 0;
            RitualCards[2].pos.y = 0.0f;
            RitualCards[2].yaw = 0.0f;
            RitualStateTime++;
            if (RitualStateTime == 10) {
                RitualStateTime = 0;
                evt_set_variable(CreatorScript, RITUAL_VAR_STATE, RITUAL_STATE_MERGE_CARDS);
                return;
            }
            break;
        case RITUAL_STATE_MERGE_CARDS:
            RitualCards[0].drawMode = CARD_DRAW_MERGE_ANIM;
            RitualCards[0].playerSpriteID = 8;
            RitualCards[1].drawMode = CARD_DRAW_HIDDEN;
            RitualCards[2].drawMode = CARD_DRAW_HIDDEN;
            RitualCards[0].playerRasterIndex = 0x11;
            return;
        case RITUAL_STATE_BEGIN_RELEASE_PLAYER:
            RitualCards[0].drawMode = CARD_DRAW_CARD_ONLY;
            RitualCards[1].drawMode = CARD_DRAW_PLAYER_ONLY;
            RitualCards[1].playerSpriteID = 8;
            RitualCards[0].pos.x = 0.0f;
            RitualCards[0].pos.z = 0;
            RitualCards[1].pos.x = 0.0f;
            RitualCards[1].pos.z = 0;
            RitualCards[1].playerRasterIndex = 10;
            RitualCards[1].spriteOffsetX = 0;
            RitualStateTime = 0;
            RitualCards[0].pos.y = 68.0f;
            RitualCards[0].yaw = 180.0f;
            RitualCards[1].pos.y = 68.0f;
            RitualCards[1].yaw = 180.0f;
            evt_set_variable(CreatorScript, RITUAL_VAR_STATE, RITUAL_STATE_RELEASE_PLAYER);
            CardRiseSpeed = 0.0f;
            PlayerFallSpeed = 1.0f;

            GetCardWorldPos(1, &playerX, &playerY, &playerZ);

            for (j = 0; j < ARRAY_COUNT(ReleaseEnergyFX); j++) {
                s32 i;

                ReleaseEnergyFX[j] = fx_energy_in_out(2, playerX, playerY + 20.0f, playerZ, 8.0f, -1);
                ReleaseEnergyFX[j]->data.energyInOut->unk_28 = 215;
                ReleaseEnergyFX[j]->data.energyInOut->unk_2C = 55;
                ReleaseEnergyFX[j]->data.energyInOut->unk_30 = 255;

                for (i = 1; i < ReleaseEnergyFX[j]->numParts; i++) {
                    ReleaseEnergyFX[j]->data.energyInOut[i].unk_38 *= 0.1;
                }
            }
            break;
        case RITUAL_STATE_RELEASE_PLAYER:
            GetCardWorldPos(1, &playerX, &playerY, &playerZ);

            for (j = 0; j < ARRAY_COUNT(ReleaseEnergyFX); j++) {
                s32 i;

                ReleaseEnergyFX[j]->data.energyInOut->pos.x = playerX;
                ReleaseEnergyFX[j]->data.energyInOut->pos.y = playerY + 20.0f;
                ReleaseEnergyFX[j]->data.energyInOut->pos.z = playerZ;
                ReleaseEnergyFX[j]->data.energyInOut->scale -= 0.1;

                if (ReleaseEnergyFX[j]->data.energyInOut->scale < 0.1) {
                    ReleaseEnergyFX[j]->data.energyInOut->scale = 0.1f;
                }

                for (i = 1; i < ReleaseEnergyFX[j]->numParts; i++) {
                    ReleaseEnergyFX[j]->data.energyInOut[i].unk_38 += 0.01;
                }
            }

            RitualCards[0].pos.y += CardRiseSpeed;
            RitualCards[1].pos.y += PlayerFallSpeed;
            CardRiseSpeed += 0.4;
            PlayerFallSpeed -= 0.05;
            RitualStateTime++;

            if (RitualCards[1].pos.y < -5.0f) {
                RitualCards[1].pos.y = -5.0f;
                RitualStateTime = 0;
                evt_set_variable(CreatorScript, RITUAL_VAR_STATE, RITUAL_STATE_COMPLETE);
                RitualCards[0].drawMode = CARD_DRAW_HIDDEN;
                RitualCards[1].drawMode = CARD_DRAW_HIDDEN;
                GetCardWorldPos(1, &playerX, &playerY, &playerZ);
                fx_sparkles(0, playerX, playerY + 20.0f, playerZ, 30.0f);
                sfx_play_sound(SOUND_MERLEE_COMPLETE_SPELL);

                for (j = 0; j < ARRAY_COUNT(ReleaseEnergyFX); j++) {
                    ReleaseEnergyFX[j]->flags |= FX_INSTANCE_FLAG_DISMISS;
                }
            }
            break;
        case RITUAL_STATE_COMPLETE:
            break;
    }
}

void RenderRitualCards(void) {
    Matrix4f mtx;
    s32 animResult;

    guPositionF(mtx, 0.0f, -gCameras[gCurrentCameraID].curYaw, 0.0f, SPRITE_WORLD_SCALE_F,
                evt_get_variable(CreatorScript, RITUAL_VAR_POS_X),
                evt_get_variable(CreatorScript, RITUAL_VAR_POS_Y),
                evt_get_variable(CreatorScript, RITUAL_VAR_POS_Z));

    animResult = AppendGfx_RitualCard(&RitualCards[0], mtx);
    AppendGfx_RitualCard(&RitualCards[1], mtx);
    AppendGfx_RitualCard(&RitualCards[2], mtx);

    // communicate when the ImgFX animations are done to the owner script
    if (RitualCards[0].drawMode == CARD_DRAW_SHUFFLE_ANIM
        && (animResult == IMGFX_RENDER_RESULT_DONE || animResult == IMGFX_RENDER_RESULT_HOLDING)
    ) {
        evt_set_variable(CreatorScript, RITUAL_VAR_STATE, RITUAL_STATE_SPREAD_CARDS);
    }
    if (RitualCards[0].drawMode == CARD_DRAW_MERGE_ANIM
        && (animResult == IMGFX_RENDER_RESULT_DONE || animResult == IMGFX_RENDER_RESULT_HOLDING)
    ) {
        evt_set_variable(CreatorScript, RITUAL_VAR_STATE, RITUAL_STATE_BEGIN_RELEASE_PLAYER);
    }
}

API_CALLABLE(PlayShuffleSoundLeft) {
    sfx_play_sound_with_params(SOUND_SHUFFLE_CARD_A, 0, 24, 0);
    return ApiStatus_DONE2;
}

API_CALLABLE(PlayShuffleSoundRight) {
    sfx_play_sound_with_params(SOUND_SHUFFLE_CARD_B, 0, 104, 0);
    return ApiStatus_DONE2;
}

EvtScript EVS_PerformRitual = {
    UseArray(Ref(RitualBuffer))
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
    Call(DarkenWorld)
    Call(DisablePlayerPhysics, true)
    Call(InterpPlayerYaw, 0, 0)
    Call(CreateRitualCards)
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
        Call(PlayShuffleSoundLeft)
        Wait(2)
        Call(PlayShuffleSoundRight)
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
    Call(DestroyRitualCards)
    Thread
        Call(UndarkenWorld)
    EndThread
    Return
    End
};

EvtScript EVS_BeginMerleeCamera = {
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

EvtScript EVS_EndMerleeCamera = {
    Call(PanToTarget, CAM_DEFAULT, 0, false)
    Call(SetCamSpeed, CAM_DEFAULT, Float(3.0))
    Call(WaitForCam, CAM_DEFAULT, Float(1.0))
    Return
    End
};

EvtScript EVS_NpcInteract_Merlee = {
    Call(SetPartnerForcedFollowMode, 1)
    ExecWait(EVS_BeginMerleeCamera)
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
        ExecWait(EVS_EndMerleeCamera)
        Return
    EndIf
    Call(SpeakToPlayer, NPC_SELF, ANIM_WorldMerlee_Talk, ANIM_WorldMerlee_Idle, 0, MSG_CH2_00D6)
    Call(ShowChoice, MSG_Choice_0011)
    IfNe(LVar0, 0)
        Call(ContinueSpeech, -1, ANIM_WorldMerlee_Talk, ANIM_WorldMerlee_Idle, 0, MSG_CH2_00D7)
        Call(SetPartnerForcedFollowMode, 0)
        ExecWait(EVS_EndMerleeCamera)
        Return
    EndIf
    Call(ContinueSpeech, -1, ANIM_WorldMerlee_Talk, ANIM_WorldMerlee_Idle, 0, MSG_CH2_00D8)
    Call(ShowCoinCounter, 1)
    Call(ShowChoice, MSG_Choice_0018)
    Call(ShowCoinCounter, 0)
    IfEq(LVar0, 3)
        Call(ContinueSpeech, -1, ANIM_WorldMerlee_Talk, ANIM_WorldMerlee_Idle, 0, MSG_CH2_00D7)
        Call(SetPartnerForcedFollowMode, 0)
        ExecWait(EVS_EndMerleeCamera)
        Return
    EndIf
    Call(TryEnchantPlayer, LVar0, LVar1)
    IfNe(LVar1, 0)
        Call(ContinueSpeech, -1, ANIM_WorldMerlee_Talk, ANIM_WorldMerlee_Idle, 0, MSG_CH2_00D9)
        Call(SetPartnerForcedFollowMode, 0)
        ExecWait(EVS_EndMerleeCamera)
        Return
    EndIf
    Call(ContinueSpeech, -1, ANIM_WorldMerlee_Talk, ANIM_WorldMerlee_Idle, 0, MSG_CH2_00DA)
    Call(SetMusic, 0, SONG_MERLEE_SPELL, 0, VOL_LEVEL_FULL)
    Call(DisablePartnerAI, false)
    Call(SetNpcAnimation, NPC_PARTNER, PARTNER_ANIM_IDLE)
    ExecGetID(LVar9, EVS_PerformRitual)
    Loop(0)
        IsScriptRunning(LVar9, LVar1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
        Wait(1)
    EndLoop
    Wait(60)
    Call(SetNpcAnimation, 4, ANIM_WorldMerlee_Idle)
    Call(PlayerMoveTo, -100, -370, 8)
    Call(SpeakToPlayer, NPC_SELF, ANIM_WorldMerlee_Talk, ANIM_WorldMerlee_Idle, 0, MSG_CH2_00DB)
    Exec(EVS_SetupMusic)
    Call(EnablePartnerAI)
    Call(SetPartnerForcedFollowMode, 0)
    ExecWait(EVS_EndMerleeCamera)
    Return
    End
};
