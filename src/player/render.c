#include "render.h"

#include <ultra64.h>
#include "sprite.h"
#include "sprite/player.h"

AnimID get_player_back_anim(AnimID anim) {
    enum PlayerSprites sprIndex = (anim >> 16) & 0xff;
    AnimID outAnim = 0;

    if (sprIndex != SPR_Mario1) {
        if (sprIndex != SPR_MarioW1 && sprIndex != SPR_Peach1) {
            return anim;
        }

        if (sprIndex == SPR_Mario1) {
            if (anim > ANIM_Mario1_SpinFall) {
                return anim;
            }
        } else if (sprIndex == SPR_MarioW1) {
            if (anim == ANIM_MarioW1_Lift) {
                outAnim = ANIM_MarioW1_Lift_Back;
            } else if (anim == ANIM_MarioW1_Toss) {
                outAnim = ANIM_MarioW1_Toss_Back;
            } else if (anim == ANIM_MarioW1_Smash1_Miss) {
                outAnim = ANIM_MarioW1_Smash1_Miss_Back;
            } else if (anim == ANIM_MarioW1_Smash1_Hit) {
                outAnim = ANIM_MarioW1_Smash1_Hit_Back;
            } else if (anim == ANIM_MarioW1_Smash2_Miss) {
                outAnim = ANIM_MarioW1_Smash2_Miss_Back;
            } else if (anim == ANIM_MarioW1_Smash2_Hit) {
                outAnim = ANIM_MarioW1_Smash2_Hit_Back;
            } else if (anim == ANIM_MarioW1_Smash3_Miss) {
                outAnim = ANIM_MarioW1_Smash3_Miss_Back;
            } else if (anim == ANIM_MarioW1_Smash3_Hit) {
                outAnim = ANIM_MarioW1_Smash3_Hit_Back;
            }
        } else if (sprIndex == SPR_Peach1) {
            if (anim > ANIM_Peach1_StepDown) {
                outAnim = anim + 1;
            }
        }
    } else if (anim > ANIM_Mario1_SpinFall) {
        return anim;
    }

    if (outAnim != 0) {
        return outAnim;
    } else {
        return anim | SPRITE_ID_BACK_FACING;
    }
}

void player_update_sprite(void) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    f32 cameraYaw = gCameras[gCurrentCameraID].curYaw;
    f32 camRelativeYaw = get_clamped_angle_diff(cameraYaw, playerStatus->curYaw);
    s32 trueAnim;
    s32 sprIndex;
    f32 angle;
    s32 direction;
    f32 timescale;

    if (camRelativeYaw < -5.0f && camRelativeYaw > -175.0f) {
        camRelativeYaw = 0.0f;
        direction = 0;
    } else if (camRelativeYaw > 5.0f && camRelativeYaw < 175.0f) {
        camRelativeYaw = 180.0f;
        direction = 1;
    } else {
        // direction is close to flipping, use saved value
        camRelativeYaw = PrevPlayerCamRelativeYaw;
        direction = 2;
    }
    // detect direction change
    if (PrevPlayerDirection != direction && direction != 2) {
        PrevPlayerDirection = direction;
        playerStatus->flipYaw[gCurrentCameraID] = (direction != 0) ? 180.0f : -180.0f;

        if (fabsf(get_clamped_angle_diff(cameraYaw, playerStatus->curYaw)) >= 90.0f) {
            playerStatus->flipYaw[gCurrentCameraID] = -playerStatus->flipYaw[gCurrentCameraID];
        }
    }
    // handle sprite 'flipping' when changing direction
    angle = playerStatus->flipYaw[gCurrentCameraID];
    if (angle != 0.0f) {
        if (angle < 0.0f) {
            angle += 28.0f;
            if (angle > 0.0f) {
                angle = 0.0f;
            }
        }
        if (angle > 0.0f) {
            angle -= 28.0f;
            if (angle < 0.0f) {
                angle = 0.0f;
            }
        }
    }

    if (playerStatus->flags & PS_FLAG_NO_FLIPPING) {
        angle = 0.0f;
    }

    playerStatus->flipYaw[gCurrentCameraID] = angle;

    PrevPlayerCamRelativeYaw = angle = clamp_angle(camRelativeYaw);
    angle = clamp_angle(playerStatus->flipYaw[gCurrentCameraID] + angle);

    trueAnim = playerStatus->anim;
    if (!(playerStatus->flags & PS_FLAG_SPINNING)) {
        sprIndex = (playerStatus->anim >> 0x10) & 0xFF;

        if (playerStatus->actionState == ACTION_STATE_TORNADO_JUMP || playerStatus->flags & PS_FLAG_ROTATION_LOCKED) {
            if (!(playerStatus->flags & PS_FLAG_FACE_FORWARD)
                && (sprIndex == SPR_Mario1 || sprIndex == SPR_MarioW1 || sprIndex == SPR_Peach1)
                && playerStatus->spriteFacingAngle < 350.0f && playerStatus->spriteFacingAngle > 190.0f
            ) {
                trueAnim = get_player_back_anim(trueAnim);
            }
        } else {
            playerStatus->spriteFacingAngle = angle;
            if (!(playerStatus->flags & PS_FLAG_FACE_FORWARD)
                && (sprIndex == SPR_Mario1 || sprIndex == SPR_MarioW1 || sprIndex == SPR_Peach1)
                && fabsf(get_clamped_angle_diff(cameraYaw, playerStatus->curYaw)) < 60.0f
            ) {
                trueAnim = get_player_back_anim(trueAnim);
            }
            playerStatus->curYaw = playerStatus->targetYaw;
        }
    }
    playerStatus->trueAnimation = trueAnim;

    timescale = 1.0f;
    if (playerStatus->flags & PS_FLAG_ENTERING_BATTLE) {
        timescale = 0.5f;
    }
    if (playerStatus->flags & PS_FLAG_TIME_STOPPED) {
        timescale = 0.0f;
    }
    playerStatus->animNotifyValue = spr_update_player_sprite(PLAYER_SPRITE_MAIN, playerStatus->trueAnimation, timescale);
    playerStatus->flags |= PS_FLAG_SPRITE_REDRAW;
}

void appendGfx_player(void* data) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    Matrix4f mtx, translate, rotateSprite, scale;
    f32 negCamYaw = -gCameras[gCurrentCamID].curYaw;
    s32 spriteIdx;

    if (playerStatus->actionState == ACTION_STATE_SLIDING) {
        guScaleF(scale, SPRITE_WORLD_SCALE_D, SPRITE_WORLD_SCALE_D, SPRITE_WORLD_SCALE_D);
        guRotateF(mtx, negCamYaw, 0.0f, 1.0f, 0.0f);
        guMtxCatF(scale, mtx, mtx);
        guRotateF(rotateSprite, playerStatus->spriteFacingAngle, 0.0f, 1.0f, 0.0f);
        guMtxCatF(mtx, rotateSprite, mtx);
        guTranslateF(translate, playerStatus->pos.x, playerStatus->pos.y - 1.0f, playerStatus->pos.z);
        guMtxCatF(mtx, translate, mtx);
        spr_draw_player_sprite(PLAYER_SPRITE_MAIN, 0, 0, 0, mtx);
    } else {
        guRotateF(rotateSprite, negCamYaw, 0.0f, -1.0f, 0.0f);
        guRotateF(mtx, clamp_angle(playerStatus->pitch), 0.0f, 0.0f, 1.0f);
        guMtxCatF(rotateSprite, mtx, mtx);
        guTranslateF(translate, 0.0f, -playerStatus->colliderHeight * 0.5f, 0.0f);
        guMtxCatF(translate, mtx, mtx);
        guRotateF(rotateSprite, negCamYaw, 0.0f, 1.0f, 0.0f);
        guMtxCatF(mtx, rotateSprite, mtx);
        guRotateF(rotateSprite, playerStatus->spriteFacingAngle, 0.0f, 1.0f, 0.0f);
        guMtxCatF(mtx, rotateSprite, mtx);
        guTranslateF(translate, 0.0f, playerStatus->colliderHeight * 0.5f, 0.0f);
        guMtxCatF(mtx, translate, mtx);
        guScaleF(scale, SPRITE_WORLD_SCALE_D, SPRITE_WORLD_SCALE_D, SPRITE_WORLD_SCALE_D);
        guMtxCatF(mtx, scale, mtx);
        guTranslateF(translate, playerStatus->pos.x, playerStatus->pos.y, playerStatus->pos.z);
        guMtxCatF(mtx, translate, mtx);

        if (playerStatus->animFlags & PA_FLAG_SHIVERING) {
            playerStatus->animFlags = playerStatus->animFlags & ~PA_FLAG_SHIVERING;
            playerStatus->shiverTime = 22;
            set_player_imgfx_comp(PLAYER_SPRITE_MAIN, -1, IMGFX_CLEAR, 0, 0, 0, 0, 0);
            set_player_imgfx_all(playerStatus->anim, IMGFX_SET_ANIM, IMGFX_ANIM_SHIVER, 1, 1, 0, 0);
        }

        if (playerStatus->shiverTime != 0) {
            playerStatus->shiverTime--;
            if (playerStatus->shiverTime == 0) {
                set_player_imgfx_comp(PLAYER_SPRITE_MAIN, -1, IMGFX_CLEAR, 0, 0, 0, 0, 0);
            }
        }

        if (playerStatus->spriteFacingAngle >= 90.0f && playerStatus->spriteFacingAngle < 270.0f) {
            spriteIdx = PLAYER_SPRITE_MAIN | DRAW_SPRITE_UPSIDE_DOWN;
        } else {
            spriteIdx = PLAYER_SPRITE_MAIN;
        }

        spr_draw_player_sprite(spriteIdx, 0, 0, 0, mtx);
    }
}

void appendGfx_player_spin(void* data) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    Matrix4f mtx;
    Matrix4f translation;
    Matrix4f rotation;
    Matrix4f scale;
    f32 yaw;
    f32 blurAngle;
    s32 tint;
    f32 px, py, pz;
    s32 x, y, z;
    s32 i;
    s32 spriteIdx;

    for (i = 0; i < 2; i++) {
        yaw = -gCameras[gCurrentCamID].curYaw;

        if (i == 0) {
            if (playerStatus->spriteFacingAngle > 90.0f && playerStatus->spriteFacingAngle <= 180.0f) {
                yaw = 180.0f - playerStatus->spriteFacingAngle;
            } else {
                if (playerStatus->spriteFacingAngle > 180.0f && playerStatus->spriteFacingAngle <= 270.0f) {
                    yaw = playerStatus->spriteFacingAngle - 180.0f;
                } else if (playerStatus->spriteFacingAngle > 270.0f && playerStatus->spriteFacingAngle <= 360.0f) {
                    yaw = 360.0f - playerStatus->spriteFacingAngle;
                } else {
                    yaw = playerStatus->spriteFacingAngle;
                }
            }

            tint = yaw / 25.0f;
            tint = 255 - (tint * 60);
            if (tint < 100) {
                tint = 100;
            }

            set_player_imgfx_all(PLAYER_SPRITE_MAIN, IMGFX_SET_COLOR, tint, tint, tint, 255, 0);

            guRotateF(rotation, yaw, 0.0f, -1.0f, 0.0f);
            guRotateF(mtx, clamp_angle(playerStatus->pitch), 0.0f, 0.0f, 1.0f);
            guMtxCatF(rotation, mtx, mtx);
            px = playerStatus->pos.x;
            py = playerStatus->pos.y;
            pz = playerStatus->pos.z;
        } else {
            blurAngle = phys_get_spin_history(i, &x, &y, &z);

            if (y == 0x80000000) {
                py = playerStatus->pos.y;
            } else {
                py = y;
            }

            px = playerStatus->pos.x;
            pz = playerStatus->pos.z;
            set_player_imgfx_comp(PLAYER_SPRITE_MAIN, -1, IMGFX_SET_ALPHA, 0, 0, 0, 64, 0);
            guRotateF(mtx, yaw, 0.0f, -1.0f, 0.0f);
            guRotateF(rotation, yaw, 0.0f, -1.0f, 0.0f);
            guRotateF(mtx, blurAngle, 0.0f, 1.0f, 0.0f);
            guMtxCatF(rotation, mtx, mtx);
        }

        guTranslateF(translation, 0.0f, -playerStatus->colliderHeight * 0.5f, 0.0f);
        guMtxCatF(translation, mtx, mtx);
        guRotateF(rotation, yaw, 0.0f, 1.0f, 0.0f);
        guMtxCatF(mtx, rotation, mtx);
        guRotateF(rotation, playerStatus->spriteFacingAngle, 0.0f, 1.0f, 0.0f);
        guMtxCatF(mtx, rotation, mtx);
        guTranslateF(translation, 0.0f, playerStatus->colliderHeight * 0.5f, 0.0f);
        guMtxCatF(mtx, translation, mtx);
        guScaleF(scale, SPRITE_WORLD_SCALE_D, SPRITE_WORLD_SCALE_D, SPRITE_WORLD_SCALE_D);
        guMtxCatF(mtx, scale, mtx);
        guTranslateF(translation, px, py, pz);
        guMtxCatF(mtx, translation, mtx);

        if (playerStatus->spriteFacingAngle >= 90.0f && playerStatus->spriteFacingAngle < 270.0f) {
            spriteIdx = PLAYER_SPRITE_MAIN | DRAW_SPRITE_UPSIDE_DOWN;
        } else {
            spriteIdx = PLAYER_SPRITE_MAIN;
        }

        spr_draw_player_sprite(spriteIdx, 0, 0, 0, mtx);
    }
}

void render_player(void) {
    if (gGameStatusPtr->debugScripts != DEBUG_SCRIPTS_NONE) {
        return;
    }

    RenderTask task;
    RenderTask* rtPtr = &task;
    PlayerStatus* playerStatus = &gPlayerStatus;
    s32 x, y, z;

    if (playerStatus->flags & PS_FLAG_SPRITE_REDRAW) {
        playerStatus->flags &= ~PS_FLAG_SPRITE_REDRAW;
        get_screen_coords(gCurrentCamID, playerStatus->pos.x, playerStatus->pos.y,
                          playerStatus->pos.z, &x, &y, &z);
        if (!(playerStatus->flags & PS_FLAG_SPINNING)) {
            if (playerStatus->curAlpha != playerStatus->prevAlpha) {
                if (playerStatus->curAlpha < 254) {
                    if (playerStatus->animFlags & PA_FLAG_MAP_HAS_SWITCH) {
                        playerStatus->renderMode = RENDER_MODE_SURFACE_XLU_LAYER2;
                    } else {
                        playerStatus->renderMode = RENDER_MODE_SURFACE_XLU_LAYER1;
                    }
                    set_player_imgfx_comp(PLAYER_SPRITE_MAIN, -1, IMGFX_SET_ALPHA, 0, 0, 0, playerStatus->curAlpha, 0);

                } else {
                    playerStatus->renderMode = RENDER_MODE_ALPHATEST;
                    set_player_imgfx_comp(PLAYER_SPRITE_MAIN, -1, IMGFX_CLEAR, 0, 0, 0, 0, 0);
                }
            }

            playerStatus->prevAlpha = playerStatus->curAlpha;

        } else {
            playerStatus->renderMode = RENDER_MODE_SURFACE_XLU_LAYER1;
            playerStatus->prevAlpha = 0;
        }

        if (!(playerStatus->animFlags & PA_FLAG_INVISIBLE)) {
            rtPtr->appendGfxArg = playerStatus;
            rtPtr->dist = -z;
            rtPtr->renderMode = playerStatus->renderMode;

            if (playerStatus->flags & PS_FLAG_SPINNING) {
                rtPtr->appendGfx = appendGfx_player_spin;
            } else {
                rtPtr->appendGfx = appendGfx_player;
            }

            queue_render_task(rtPtr);
        }
    }
}
