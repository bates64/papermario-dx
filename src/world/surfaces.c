#include "surfaces.h"
#include "effects.h"

void player_surface_spawn_basic_fx(void);
void player_surface_spawn_flower_fx(void);
void player_surface_spawn_cloud_fx(void);
void player_surface_spawn_snow_fx(void);
void player_surface_spawn_hedges_fx(void);
void player_surface_spawn_water_fx(void);

BSS s32 PrevTimeInAir;
BSS s32 LandedTimeInAir;

s32 PrevSurfaceType = SURFACE_TYPE_DEFAULT;

s32 SurfaceWalkEffectType = SURFACE_WALK_FX_STANDARD;

void surface_set_walk_effect(s32 effect) {
    SurfaceWalkEffectType = effect;
}

API_CALLABLE(SetSurfaceWalkEffect) {
    Bytecode* args = script->ptrReadPos;
    s32 effect = evt_get_variable(script, *args++);

    surface_set_walk_effect(effect);
    return ApiStatus_DONE2;
}

s16 PlayerDustSpawnDelay = 4;
f32 PlayerFlowerSplashAngle = 0.0f;
s16 PlayerFlowerSplashDelay = 5;
s16 PlayerFlowerTrailDelay = 4;
s32 PlayerFlowerTrailVariant = 0;
f32 PlayerCloudPuffAngle = 0.0f;
s16 PlayerSnowSpawnDelay = 4;
b32 PlayerNextFootParity = false; // false => RIGHT, true => LEFT
s16 PlayerHedgeSpawnDelay = 4;
s16 PlayerWaterSpawnDelay = 4;

// Particles (dust, flowers, snow) and etc
void player_surface_spawn_fx(void) {
    s32 surfaceType = SURFACE_TYPE_DEFAULT;

    if (gPlayerStatus.actionState == ACTION_STATE_JUMP) {
        surfaceType = PrevSurfaceType;
    }

    PrevSurfaceType = get_collider_flags((u16)gCollisionStatus.curFloor) & COLLIDER_FLAGS_SURFACE_TYPE_MASK;

    if (gPlayerStatus.actionState != ACTION_STATE_JUMP) {
        surfaceType = PrevSurfaceType;
    }

    if (gPlayerStatus.actionState == ACTION_STATE_LAND && gPlayerStatus.flags & PS_FLAG_ACTION_STATE_CHANGED) {
        LandedTimeInAir = PrevTimeInAir;
    }

    PrevTimeInAir = gPlayerStatus.timeInAir;

    switch (surfaceType) {
        case SURFACE_TYPE_FLOWERS:
            player_surface_spawn_flower_fx();
            break;
        case SURFACE_TYPE_CLOUD:
            player_surface_spawn_cloud_fx();
            break;
        case SURFACE_TYPE_SNOW:
            player_surface_spawn_snow_fx();
            break;
        case SURFACE_TYPE_HEDGES:
            player_surface_spawn_hedges_fx();
            break;
        case SURFACE_TYPE_WATER:
            player_surface_spawn_water_fx();
            break;
        default:
            player_surface_spawn_basic_fx();
            break;
    }
}

void player_surface_spawn_basic_fx(void) {
    f32 sinAngle, cosAngle;
    f32 x, y, z;

    // spawn effects if landing from a decent height
    if (gPlayerStatus.actionState == ACTION_STATE_LAND
        && (gPlayerStatus.flags & PS_FLAG_ACTION_STATE_CHANGED)
        && LandedTimeInAir >= 10
    ) {
        x = gPlayerStatus.pos.x;
        y = gPlayerStatus.pos.y;
        z = gPlayerStatus.pos.z;
        switch (SurfaceWalkEffectType) {
            case SURFACE_WALK_FX_STANDARD:
                fx_landing_dust(0, x, y, z, 0.0f);
                break;
            case SURFACE_WALK_FX_SPARKLE:
                fx_misc_particles(3, x, y, z, 13.0f, 10.0f, 1.0f, 5, 30);
                break;
        }
        return;
    }

    // spawn effects if ground pounding
    if ((gPlayerStatus.actionState == ACTION_STATE_SPIN_POUND && gPlayerStatus.flags & PS_FLAG_SPECIAL_LAND)
     || (gPlayerStatus.actionState == ACTION_STATE_TORNADO_POUND && gPlayerStatus.flags & PS_FLAG_SPECIAL_LAND)
    ) {
        x = gPlayerStatus.pos.x;
        y = gPlayerStatus.pos.y;
        z = gPlayerStatus.pos.z;
        switch (SurfaceWalkEffectType) {
            case SURFACE_WALK_FX_STANDARD:
                fx_landing_dust(0, x, y, z, 0.0f);
                break;
            case SURFACE_WALK_FX_SPARKLE:
                fx_misc_particles(3, x, y, z, gPlayerStatus.colliderDiameter, 10.0f, 1.0f, 5, 40);
                break;
        }
        return;
    }

    // spawn effects if spinning and moving
    if (gPlayerStatus.actionState == ACTION_STATE_SPIN && gPlayerStatus.curSpeed != 0.0f) {
        if (PlayerDustSpawnDelay++ >= 4) {
            PlayerDustSpawnDelay = 2;

            switch (SurfaceWalkEffectType) {
                case SURFACE_WALK_FX_STANDARD:
                    sin_cos_rad(DEG_TO_RAD(clamp_angle(-gPlayerStatus.curYaw)), &sinAngle, &cosAngle);
                    fx_walking_dust(
                        0,
                        gPlayerStatus.pos.x + (gPlayerStatus.colliderDiameter * sinAngle * 0.2f),
                        gPlayerStatus.pos.y + 1.5f,
                        gPlayerStatus.pos.z + (gPlayerStatus.colliderDiameter * cosAngle * 0.2f),
                        sinAngle,
                        cosAngle
                    );
                    break;
                case SURFACE_WALK_FX_SPARKLE:
                    sin_cos_rad(DEG_TO_RAD(clamp_angle(gPlayerStatus.targetYaw)), &sinAngle, &cosAngle);
                    fx_misc_particles(
                        3,
                        gPlayerStatus.pos.x + (gPlayerStatus.colliderDiameter * sinAngle),
                        gPlayerStatus.pos.y + 1.5f,
                        gPlayerStatus.pos.z + (gPlayerStatus.colliderDiameter * cosAngle),
                        13.0f, 10.0f, 1.0f, 5, 30
                    );
                    break;
            }
        }
        return;
    }

    // spawn effects if running or starting a spin
    if (gPlayerStatus.actionState == ACTION_STATE_RUN
        || (gPlayerStatus.actionState == ACTION_STATE_SPIN && gPlayerStatus.actionSubstate == 0)
    ) {
        if (PlayerDustSpawnDelay++ >= 4) {
            PlayerDustSpawnDelay = 0;

            switch (SurfaceWalkEffectType) {
                case SURFACE_WALK_FX_STANDARD:
                    sin_cos_rad(DEG_TO_RAD(clamp_angle(-gPlayerStatus.curYaw)), &sinAngle, &cosAngle);
                    fx_walking_dust(
                        0,
                        gPlayerStatus.pos.x + (gPlayerStatus.colliderDiameter * sinAngle * 0.2f),
                        gPlayerStatus.pos.y + 1.5f,
                        gPlayerStatus.pos.z + (gPlayerStatus.colliderDiameter * cosAngle * 0.2f),
                        sinAngle,
                        cosAngle
                    );
                    break;
                case SURFACE_WALK_FX_SPARKLE:
                    sin_cos_rad(DEG_TO_RAD(clamp_angle(gPlayerStatus.targetYaw)), &sinAngle, &cosAngle);
                    fx_misc_particles(
                        3,
                        gPlayerStatus.pos.x + (gPlayerStatus.curSpeed * sinAngle),
                        gPlayerStatus.pos.y + 1.5f,
                        gPlayerStatus.pos.z + (gPlayerStatus.curSpeed * cosAngle),
                        13.0f, 10.0f, 1.0f, 5, 30
                    );
                    break;
            }
        }
        return;
    }

    // reset the delay
    PlayerDustSpawnDelay = 4;
    return;
}

void player_surface_spawn_flower_fx(void) {
    f32 sinAngle, cosAngle;
    f32 x, y, z;

    if (gPlayerStatus.actionState == ACTION_STATE_JUMP
        && gPlayerStatus.timeInAir == 1
        && PlayerFlowerSplashDelay == 5
    ) {
        x = gPlayerStatus.pos.x;
        z = gPlayerStatus.pos.z;
        y = gPlayerStatus.pos.y + 14.0f;

        fx_flower_splash(x, y, z, PlayerFlowerSplashAngle);
        PlayerFlowerSplashAngle = clamp_angle(PlayerFlowerSplashAngle + 35.0f);
        PlayerFlowerSplashDelay = 0;
        return;
    }

    PlayerFlowerSplashDelay++;
    if (PlayerFlowerSplashDelay > 5) {
        PlayerFlowerSplashDelay = 5;
    }

    if (gPlayerStatus.actionState == ACTION_STATE_WALK
        || gPlayerStatus.actionState == ACTION_STATE_RUN
        || (gPlayerStatus.actionState == ACTION_STATE_SPIN && gPlayerStatus.actionSubstate == 0)
    ) {
        if (PlayerFlowerTrailDelay++ > 0) {
            PlayerFlowerTrailDelay = 0;
            sin_cos_rad(DEG_TO_RAD(clamp_angle(-gPlayerStatus.curYaw)), &sinAngle, &cosAngle);

            x = gPlayerStatus.pos.x + (gPlayerStatus.colliderDiameter * sinAngle * -0.4f);
            z = gPlayerStatus.pos.z + (gPlayerStatus.colliderDiameter * cosAngle * -0.4f);
            y = gPlayerStatus.pos.y + 15.5f;

            fx_flower_trail(0, x, y, z, -gPlayerStatus.curYaw + rand_int(10) - 5.0f, PlayerFlowerTrailVariant);
            PlayerFlowerTrailVariant = !PlayerFlowerTrailVariant;
        }
        return;
    }

    PlayerFlowerTrailDelay = 0;
    return;
}

void player_surface_spawn_cloud_fx(void) {
    f32 sinAngle, cosAngle;
    f32 dx, dy, dz;
    s32 i;

    if (((gPlayerStatus.actionState == ACTION_STATE_LAND && (gPlayerStatus.flags & PS_FLAG_ACTION_STATE_CHANGED))
        || (gPlayerStatus.actionState == ACTION_STATE_SPIN_POUND && (gPlayerStatus.flags & PS_FLAG_SPECIAL_LAND))
        || (gPlayerStatus.actionState == ACTION_STATE_TORNADO_POUND && (gPlayerStatus.flags & PS_FLAG_SPECIAL_LAND)))
        && LandedTimeInAir >= 10
    ) {
        fx_cloud_puff(
            gPlayerStatus.pos.x,
            (gPlayerStatus.pos.y + 14.0f) - 5.0f,
            gPlayerStatus.pos.z,
            PlayerCloudPuffAngle
        );
        PlayerCloudPuffAngle = clamp_angle(PlayerCloudPuffAngle + 35.0f);

        for (i = 0; i < 4; i++) {
            dx = rand_int(10) - 5;
            dz = rand_int(10) - 5;
            dy = -2.0f - ((SQ(dx) + SQ(dz)) / 5.0f);

            sin_cos_rad(DEG_TO_RAD(clamp_angle(-gPlayerStatus.curYaw + (i * 90))), &sinAngle, &cosAngle);
            fx_cloud_trail(
                0,
                gPlayerStatus.pos.x + (gPlayerStatus.colliderDiameter * sinAngle * -0.3f) + dx,
                gPlayerStatus.pos.y + 15.5f + dy,
                gPlayerStatus.pos.z + (gPlayerStatus.colliderDiameter * cosAngle * -0.3f) + dz
            );
        }
        return;
    }

    if (gPlayerStatus.actionState == ACTION_STATE_WALK
        || gPlayerStatus.actionState == ACTION_STATE_RUN
        || (gPlayerStatus.actionState == ACTION_STATE_SPIN && gPlayerStatus.actionSubstate == 0)
    ) {
        dx = rand_int(10) - 5;
        dz = rand_int(10) - 5;
        dy = -2.0f - ((SQ(dx) + SQ(dz)) / 5.0f);

        sin_cos_rad(DEG_TO_RAD(clamp_angle(-gPlayerStatus.curYaw)), &sinAngle, &cosAngle);
        fx_cloud_trail(
            1,
            gPlayerStatus.pos.x + (gPlayerStatus.colliderDiameter * sinAngle * -0.3f) + dx,
            gPlayerStatus.pos.y + 15.5f + dy,
            gPlayerStatus.pos.z + (gPlayerStatus.colliderDiameter * cosAngle * -0.3f) + dz
        );

    }
    return;
}

void player_surface_spawn_snow_fx(void) {
    f32 sinAngle, cosAngle;

    if (gPlayerStatus.actionState == ACTION_STATE_WALK
        || gPlayerStatus.actionState == ACTION_STATE_RUN
        || (gPlayerStatus.actionState == ACTION_STATE_SPIN && gPlayerStatus.actionSubstate == 0)
        || (gPlayerStatus.actionState == ACTION_STATE_LAND && gPlayerStatus.flags & PS_FLAG_ACTION_STATE_CHANGED)
        || (gPlayerStatus.actionState == ACTION_STATE_IDLE && gPlayerStatus.flags & PS_FLAG_ACTION_STATE_CHANGED)
    ) {
        if (PlayerSnowSpawnDelay++ >= 4) {
            PlayerSnowSpawnDelay = 0;
            sin_cos_rad(DEG_TO_RAD(clamp_angle(-gPlayerStatus.curYaw)), &sinAngle, &cosAngle);
            fx_footprint(
                gPlayerStatus.pos.x + (gPlayerStatus.colliderDiameter * sinAngle * 0.2f),
                gPlayerStatus.pos.y + 1.5f,
                gPlayerStatus.pos.z + (gPlayerStatus.colliderDiameter * cosAngle * 0.2f),
                -gPlayerStatus.curYaw,
                PlayerNextFootParity
            );
            PlayerNextFootParity = !PlayerNextFootParity;
        }
        return;
    }

    PlayerSnowSpawnDelay = 4;
    return;
}

void player_surface_spawn_hedges_fx(void) {
    f32 sinAngle, cosAngle;

    if (gPlayerStatus.actionState == ACTION_STATE_WALK
        || gPlayerStatus.actionState == ACTION_STATE_RUN
        || (gPlayerStatus.actionState == ACTION_STATE_SPIN && gPlayerStatus.actionSubstate == 0)
        || (gPlayerStatus.actionState == ACTION_STATE_LAND && gPlayerStatus.flags & PS_FLAG_ACTION_STATE_CHANGED)
        || (gPlayerStatus.actionState == ACTION_STATE_IDLE && gPlayerStatus.flags & PS_FLAG_ACTION_STATE_CHANGED)
    ) {
        if (PlayerHedgeSpawnDelay++ >= 4) {
            PlayerHedgeSpawnDelay = 0;
            sin_cos_rad(DEG_TO_RAD(clamp_angle(-gPlayerStatus.curYaw)), &sinAngle, &cosAngle);
            fx_falling_leaves(
                0,
                gPlayerStatus.pos.x + (gPlayerStatus.colliderDiameter * sinAngle * 0.2f),
                40.0f,
                gPlayerStatus.pos.z + (gPlayerStatus.colliderDiameter * cosAngle * 0.2f)
            );
        }
        return;
    }

    PlayerHedgeSpawnDelay = 4;
    return;
}

void player_surface_spawn_water_fx(void) {
    f32 sinAngle, cosAngle;

    if (gPlayerStatus.actionState == ACTION_STATE_WALK
        || gPlayerStatus.actionState == ACTION_STATE_RUN
        || (gPlayerStatus.actionState == ACTION_STATE_SPIN && gPlayerStatus.actionSubstate == 0)
        || (gPlayerStatus.actionState == ACTION_STATE_LAND && gPlayerStatus.flags & PS_FLAG_ACTION_STATE_CHANGED)
        || (gPlayerStatus.actionState == ACTION_STATE_IDLE && gPlayerStatus.flags & PS_FLAG_ACTION_STATE_CHANGED)
    ) {
        if (PlayerWaterSpawnDelay++ >= 4) {
            PlayerWaterSpawnDelay = 0;
            sin_cos_rad(DEG_TO_RAD(clamp_angle(-gPlayerStatus.curYaw)), &sinAngle, &cosAngle);
            fx_rising_bubble(
                0,
                gPlayerStatus.pos.x + (gPlayerStatus.colliderDiameter * sinAngle * 0.2f),
                gPlayerStatus.pos.y + 0.0f,
                gPlayerStatus.pos.z + (gPlayerStatus.colliderDiameter * cosAngle * 0.2f),
                0.0f
            );
        }
        return;
    }

    PlayerWaterSpawnDelay = 4;
    return;
}

s16 NpcDustSpawnDelay = 4;
f32 NpcDustSpawnAngle = 0.0f;
s16 NpcFlowerSplashDelay = 5;
f32 NpcFlowerSplashAngle = 0;
s16 NpcFlowerTrailDelay = 4;
s32 NpcFlowerTrailVariant = 0;
f32 NpcCloudPuffAngle = 0.0f;
s16 NpcSnowSpawnDelay = 4;
s32 NpcNextFootParity = 0;
s16 NpcHedgeSpawnDelay = 4;
s16 NpcWaterSpawnDelay = 4;

void npc_surface_spawn_basic_fx(Npc* npc, SurfaceInteractMode mode);
void npc_surface_spawn_flower_fx(Npc* npc, SurfaceInteractMode mode);
void npc_surface_spawn_cloud_fx(Npc* npc, SurfaceInteractMode mode);
void npc_surface_spawn_snow_fx(Npc* npc, SurfaceInteractMode mode);
void npc_surface_spawn_hedges_fx(Npc* npc, SurfaceInteractMode mode);
void npc_surface_spawn_water_fx(Npc* npc, SurfaceInteractMode mode);

void npc_surface_spawn_fx(Npc* npc, SurfaceInteractMode mode) {
    s32 surfaceType;

    if ((npc->flags & NPC_FLAG_INVISIBLE) || !(npc->flags & NPC_FLAG_TOUCHES_GROUND) || npc->moveSpeed == 0.0f) {
        return;
    }

    surfaceType = get_collider_flags((u16)npc->curFloor) & COLLIDER_FLAGS_SURFACE_TYPE_MASK;
    switch (surfaceType) {
        case SURFACE_TYPE_FLOWERS:
            npc_surface_spawn_flower_fx(npc, mode);
            break;
        case SURFACE_TYPE_CLOUD:
            npc_surface_spawn_cloud_fx(npc, mode);
            break;
        case SURFACE_TYPE_SNOW:
            npc_surface_spawn_snow_fx(npc, mode);
            break;
        case SURFACE_TYPE_HEDGES:
            npc_surface_spawn_hedges_fx(npc, mode);
            break;
        case SURFACE_TYPE_WATER:
            npc_surface_spawn_water_fx(npc, mode);
            break;
        default:
            npc_surface_spawn_basic_fx(npc, mode);
            break;
    }
}

void npc_surface_spawn_basic_fx(Npc* npc, SurfaceInteractMode mode) {
    f32 sinTheta, cosTheta;
    f32 x, y, z;

    if (mode == SURFACE_INTERACT_LAND) {
        x = npc->pos.x;
        y = npc->pos.y + 0.0f;
        z = npc->pos.z;

        switch (SurfaceWalkEffectType) {
            case SURFACE_WALK_FX_STANDARD:
                fx_landing_dust(0, x, y, z, NpcDustSpawnAngle);
                NpcDustSpawnAngle = clamp_angle(NpcDustSpawnAngle + 35.0f);
                break;
            case SURFACE_WALK_FX_SPARKLE:
                fx_misc_particles(3, x, y, z,  13.0f, 10.0f, 1.0f, 5, 30);
                break;
        }
    } else if (mode != SURFACE_INTERACT_WALK) {
        if (NpcDustSpawnDelay++ >= 4) {
            NpcDustSpawnDelay = 0;

            switch (SurfaceWalkEffectType) {
                case SURFACE_WALK_FX_STANDARD:
                    sin_cos_rad(DEG_TO_RAD(clamp_angle(-npc->yaw)), &sinTheta, &cosTheta);
                    fx_walking_dust(0,
                        npc->pos.x + (npc->collisionDiameter * sinTheta * 0.2f),
                        npc->pos.y + 1.5f,
                        npc->pos.z + (npc->collisionDiameter * cosTheta * 0.2f),
                        sinTheta,
                        cosTheta);
                    break;
                case SURFACE_WALK_FX_SPARKLE:
                    sin_cos_rad(DEG_TO_RAD(clamp_angle(npc->yaw)), &sinTheta, &cosTheta);
                    fx_misc_particles(3,
                        npc->pos.x + (npc->collisionDiameter * sinTheta),
                        npc->pos.y + 1.5f,
                        npc->pos.z + (npc->collisionDiameter * cosTheta),
                        5.0f, 10.0f, 1.0f, 5, 30);
                    break;
            }
        }
    }
}

void npc_surface_spawn_flower_fx(Npc* npc, SurfaceInteractMode mode) {
    f32 sinAngle, cosAngle;
    f32 x, y, z;

    if (mode == SURFACE_INTERACT_LAND && NpcFlowerSplashDelay == 5) {
        x = npc->pos.x;
        y = npc->pos.y + + 14.0f;
        z = npc->pos.z;

        fx_flower_splash(x, y, z, NpcFlowerSplashAngle);
        NpcFlowerSplashAngle = clamp_angle(NpcFlowerSplashAngle + 35.0f);
        NpcFlowerSplashDelay = 0;
        return;
    }

    NpcFlowerSplashDelay++;
    if (NpcFlowerSplashDelay > 5) {
        NpcFlowerSplashDelay = 5;
    }

    if (NpcFlowerTrailDelay++ > 0) {
        NpcFlowerTrailDelay = 0;

        sin_cos_rad(DEG_TO_RAD(clamp_angle(-npc->yaw)), &sinAngle, &cosAngle);
        x = npc->pos.x + (npc->collisionDiameter * sinAngle * -0.4f);
        z = npc->pos.z + (npc->collisionDiameter * cosAngle * -0.4f);
        y = npc->pos.y + 15.5f;

        fx_flower_trail(1, x, y, z, -npc->yaw + rand_int(10) - 5.0f, NpcFlowerTrailVariant);
        NpcFlowerTrailVariant = !NpcFlowerTrailVariant;
    }
}

void npc_surface_spawn_cloud_fx(Npc* npc, SurfaceInteractMode mode) {
    f32 sinAngle, cosAngle;
    f32 dx, dy, dz;
    s32 i;

    if (mode == SURFACE_INTERACT_LAND) {
        fx_cloud_puff(npc->pos.x, (npc->pos.y + 14.0f) - 5.0f, npc->pos.z, NpcCloudPuffAngle);

        NpcCloudPuffAngle = clamp_angle(NpcCloudPuffAngle + 35.0f);

        for (i = 0; i < 4; i++) {
            dx = rand_int(10) - 5;
            dz = rand_int(10) - 5;
            dy = -2.0f - ((SQ(dx) + SQ(dz)) / 5.0f);

            sin_cos_rad(DEG_TO_RAD(clamp_angle(-npc->yaw + (i * 90))), &sinAngle, &cosAngle);
            fx_cloud_trail(
                1,
                npc->pos.x + (npc->collisionDiameter * sinAngle * -0.3f) + dx,
                npc->pos.y + 15.5f + dy,
                npc->pos.z + (npc->collisionDiameter * cosAngle * -0.3f) + dz
            );
        }
    } else {
        dx = rand_int(10) - 5;
        dz = rand_int(10) - 5;
        dy = -2.0f - ((SQ(dx) + SQ(dz)) / 5.0f);

        sin_cos_rad(DEG_TO_RAD(clamp_angle(-npc->yaw)), &sinAngle, &cosAngle);
        fx_cloud_trail(
            1,
            npc->pos.x + (npc->collisionDiameter * sinAngle * -0.3f) + dx,
            npc->pos.y + 15.5f + dy,
            npc->pos.z + (npc->collisionDiameter * cosAngle * -0.3f) + dz
        );
    }
}

void npc_surface_spawn_snow_fx(Npc* npc, SurfaceInteractMode mode) {
    f32 sinAngle, cosAngle;

    if (gPartnerStatus.actingPartner == PARTNER_LAKILESTER && gPartnerStatus.partnerActionState == PARTNER_ACTION_NONE) {
        return;
    }

    if (NpcSnowSpawnDelay++ >= 4) {
        NpcSnowSpawnDelay = 0;
        sin_cos_rad(DEG_TO_RAD(clamp_angle(-npc->yaw)), &sinAngle, &cosAngle);
        fx_footprint(
            npc->pos.x + (npc->collisionDiameter * sinAngle * 0.2f),
            npc->pos.y + 1.5f,
            npc->pos.z + (npc->collisionDiameter * cosAngle * 0.2f),
            -npc->yaw,
            NpcNextFootParity);
        NpcNextFootParity = !NpcNextFootParity;
    }
}

void npc_surface_spawn_hedges_fx(Npc* npc, SurfaceInteractMode mode) {
    f32 sinAngle, cosAngle;

    if (NpcHedgeSpawnDelay++ >= 4) {
        NpcHedgeSpawnDelay = 0;
        sin_cos_rad(DEG_TO_RAD(clamp_angle(-npc->yaw)), &sinAngle, &cosAngle);
        fx_falling_leaves(
            1,
            npc->pos.x + (npc->collisionDiameter * sinAngle * 0.2f),
            40.0f,
            npc->pos.z + (npc->collisionDiameter * cosAngle * 0.2f));
    }
}

void npc_surface_spawn_water_fx(Npc* npc, SurfaceInteractMode mode) {
    f32 sinAngle, cosAngle;

    if (NpcWaterSpawnDelay++ >= 4) {
        NpcWaterSpawnDelay = 0;
        sin_cos_rad(DEG_TO_RAD(clamp_angle(-npc->yaw)), &sinAngle, &cosAngle);
        fx_rising_bubble(
            0,
            npc->pos.x + (npc->collisionDiameter * sinAngle * 0.2f),
            npc->pos.y + 0.0f,
            npc->pos.z + (npc->collisionDiameter * cosAngle * 0.2f),
            0.0f);
    }
}
