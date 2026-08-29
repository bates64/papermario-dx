#include "common.h"
#include "effects.h"
#include "entity.h"
#include "animation_script.h"
#include "ld_addrs.h"

extern AnimScript Entity_TrumpetPlant_AnimationIdle;
extern AnimScript Entity_TrumpetPlant_AnimationUse;
extern StaticAnimatorNode* Entity_TrumpetPlant_Mesh[];

#define TRUMPET_PLANT_MAX_COINS 3

void entity_TrumpetPlant_idle(Entity* entity) {
    if ((gPlayerStatus.animFlags & PA_FLAG_INTERACT_PROMPT_AVAILABLE) &&
        (entity->collisionFlags & (ENTITY_COLLISION_PLAYER_HAMMER | ENTITY_COLLISION_PLAYER_TOUCH_WALL))) {
        exec_entity_commandlist(entity);
        play_model_animation(entity->virtualModelIndex, Entity_TrumpetPlant_AnimationUse);
    }
}

void entity_TrumpetPlant_create_effect(Entity* entity) {
    f32 xOffset, zOffset, angle;

    angle = DEG_TO_RAD(clamp_angle(entity->rot.y));
    xOffset = -26.0 * cos_rad(angle);
    zOffset = 6.0 * sin_rad(angle);
    fx_stars_burst(0, entity->pos.x + xOffset, entity->pos.y + 62.0f, entity->pos.z + zOffset, clamp_angle(entity->rot.y - 90.0), 54.0f, 2);
}

void entity_TrumpetPlant_spawn_coin(Entity* entity) {
    TrumpetPlantData* data = entity->dataBuf.trumpetPlant;

    entity_TrumpetPlant_create_effect(entity);
    if (data->numCoins < TRUMPET_PLANT_MAX_COINS) {
        f32 xOffset, zOffset, angle;

        angle = DEG_TO_RAD(clamp_angle(entity->rot.y));
        xOffset = -26.0 * cos_rad(angle);
        zOffset = 6.0 * sin_rad(angle);

        if (rand_int(32) > 16) {
            f32 facingAngle = entity->rot.y - 110.0f + (data->numCoins % 3) * 30;
            data->numCoins++;
            make_item_entity(ITEM_COIN,
                             entity->pos.x + xOffset,
                             entity->pos.y + 62.0f,
                             entity->pos.z + zOffset,
                             ITEM_SPAWN_MODE_TOSS_SPAWN_ALWAYS, 0,
                             facingAngle, 0);
        }
    }
}

EntityScript Entity_TrumpetPlant_Script = {
    es_SetCallback(entity_TrumpetPlant_idle, 0)
    es_ClearFlags(ENTITY_FLAG_SHOWS_INSPECT_PROMPT)
    es_PlaySound(SOUND_PLANTS_TRUMPET)
    es_SetCallback(nullptr, 15)
    es_Call(entity_TrumpetPlant_create_effect)
    es_SetCallback(nullptr, 3)
    es_Call(entity_TrumpetPlant_create_effect)
    es_SetCallback(nullptr, 2)
    es_Call(entity_TrumpetPlant_spawn_coin)
    es_SetCallback(nullptr, 3)
    es_Call(entity_TrumpetPlant_create_effect)
    es_SetCallback(nullptr, 2)
    es_Call(entity_TrumpetPlant_create_effect)
    es_SetCallback(nullptr, 3)
    es_Call(entity_TrumpetPlant_create_effect)
    es_SetCallback(nullptr, 32)
    es_SetFlags(ENTITY_FLAG_SHOWS_INSPECT_PROMPT)
    es_Restart
    es_End
};

DmaEntry Entity_TrumpetPlant_dma[] = { ENTITY_ROM(TrumpetPlant_gfx), ENTITY_ROM(TrumpetPlant_anim) };

ENTITY_IMPLEMENTATION(TrumpetPlant) = {
    .flags = ENTITY_FLAG_SHOWS_INSPECT_PROMPT | ENTITY_FLAG_HAS_ANIMATED_MODEL,
    .typeDataSize = sizeof(TrumpetPlantData),
    .animScript = Entity_TrumpetPlant_AnimationIdle,
    .modelAnimationNodes = Entity_TrumpetPlant_Mesh,
    .fpInit = nullptr,
    .updateEntityScript = Entity_TrumpetPlant_Script,
    .fpHandleCollision = nullptr,
    { .dmaList = Entity_TrumpetPlant_dma },
    .entityType = ENTITY_TYPE_TRUMPET_PLANT,
    .aabbSize = { 30, 40, 30 }
};
