#include "common.h"
#include "sprite.h"
#include "sprite/player.h"

HitID player_raycast_below(f32 yaw, f32 diameter, f32* outX, f32* outY, f32* outZ, f32* outLength,
    f32* hitRx, f32* hitRz, f32* hitDirX, f32* hitDirZ);

s32 get_player_back_anim(s32 arg0);
void appendGfx_player(void* data);
void appendGfx_player_spin(void* data);

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

s32 get_player_back_anim(s32 anim) {
    s32 sprIndex = (anim >> 16) & 0xff;
    s32 outAnim = 0;

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

void render_player(void) {
    if (gGameStatusPtr->debugScripts == DEBUG_SCRIPTS_NONE) {
        render_player_model();
    }
}

void render_player_model(void) {
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

void appendGfx_player(void* data) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    Matrix4f sp20, sp60, spA0, spE0;
    f32 temp_f0 = -gCameras[gCurrentCamID].curYaw;
    s32 spriteIdx;

    if (playerStatus->actionState == ACTION_STATE_SLIDING) {
        guScaleF(spE0, SPRITE_WORLD_SCALE_D, SPRITE_WORLD_SCALE_D, SPRITE_WORLD_SCALE_D);
        guRotateF(sp20, temp_f0, 0.0f, 1.0f, 0.0f);
        guMtxCatF(spE0, sp20, sp20);
        guRotateF(spA0, playerStatus->spriteFacingAngle, 0.0f, 1.0f, 0.0f);
        guMtxCatF(sp20, spA0, sp20);
        guTranslateF(sp60, playerStatus->pos.x, playerStatus->pos.y - 1.0f, playerStatus->pos.z);
        guMtxCatF(sp20, sp60, sp20);
        spr_draw_player_sprite(PLAYER_SPRITE_MAIN, 0, 0, 0, sp20);
    } else {
        guRotateF(spA0, temp_f0, 0.0f, -1.0f, 0.0f);
        guRotateF(sp20, clamp_angle(playerStatus->pitch), 0.0f, 0.0f, 1.0f);
        guMtxCatF(spA0, sp20, sp20);
        guTranslateF(sp60, 0.0f, -playerStatus->colliderHeight * 0.5f, 0.0f);
        guMtxCatF(sp60, sp20, sp20);
        guRotateF(spA0, temp_f0, 0.0f, 1.0f, 0.0f);
        guMtxCatF(sp20, spA0, sp20);
        guRotateF(spA0, playerStatus->spriteFacingAngle, 0.0f, 1.0f, 0.0f);
        guMtxCatF(sp20, spA0, sp20);
        guTranslateF(sp60, 0.0f, playerStatus->colliderHeight * 0.5f, 0.0f);
        guMtxCatF(sp20, sp60, sp20);
        guScaleF(spE0, SPRITE_WORLD_SCALE_D, SPRITE_WORLD_SCALE_D, SPRITE_WORLD_SCALE_D);
        guMtxCatF(sp20, spE0, sp20);
        guTranslateF(sp60, playerStatus->pos.x, playerStatus->pos.y, playerStatus->pos.z);
        guMtxCatF(sp20, sp60, sp20);

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

        spr_draw_player_sprite(spriteIdx, 0, 0, 0, sp20);
    }
}

/// Only used when speedy spinning.
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

void update_player_shadow(void) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    Shadow* shadow = get_shadow_by_index(gPlayerStatusPtr->shadowID);
    Camera* camera = &gCameras[gCurrentCameraID];
    f32 shadowScale = 0.0f;
    f32 yawTemp = 0.0f;
    f32 hitDirX, hitDirZ;
    f32 hitRx, hitRz;
    f32 x, y, z;
    f32 playerX, playerZ;
    f32 raycastYaw;

    if (playerStatus->spriteFacingAngle >= 90.0f && playerStatus->spriteFacingAngle < 270.0f) {
        yawTemp = 180.0f;
    }

    raycastYaw = (yawTemp - 90.0f) + gCameras[gCurrentCameraID].curYaw;
    shadow->pos.x = playerX = playerStatus->pos.x;
    shadow->pos.z = playerZ = playerStatus->pos.z;
    x = playerX;
    y = playerStatus->pos.y + (playerStatus->colliderHeight / 3.5f);
    z = playerZ;
    shadowScale = 1024.0f;
    gCollisionStatus.floorBelow = player_raycast_below(raycastYaw, playerStatus->colliderDiameter, &x, &y, &z,
                                                       &shadowScale, &hitRx, &hitRz, &hitDirX, &hitDirZ);
    shadow->rot.x = hitRx;
    shadow->rot.z = hitRz;
    shadow->rot.y = clamp_angle(-camera->curYaw);
    hitRx += 180.0f;
    hitRz += 180.0f;

    if (hitRx != 0.0f || hitRz != 0.0f) {
        s32 dist = dist2D(x, z, playerStatus->pos.x, playerStatus->pos.z);
        f32 tan = atan2(playerStatus->pos.x, playerStatus->pos.z, x, z);
        s32 angleTemp = clamp_angle((-90.0f - tan) + get_player_normal_yaw());

        if (gGameStatusPtr->playerGroundTraceNormal.y != 0.0f) {
            y -= sqrtf(SQ(gGameStatusPtr->playerGroundTraceNormal.x) + SQ(gGameStatusPtr->playerGroundTraceNormal.z)) /
                       gGameStatusPtr->playerGroundTraceNormal.y * dist * sin_deg(angleTemp);
        }
    }

    shadow->pos.y = y;
    shadow->alpha = (f64)playerStatus->curAlpha / 2;

    if (gGameStatusPtr->peachFlags & PEACH_FLAG_IS_PEACH) {
        set_peach_shadow_scale(shadow, shadowScale);
    } else {
        set_standard_shadow_scale(shadow, shadowScale);
    }
}
