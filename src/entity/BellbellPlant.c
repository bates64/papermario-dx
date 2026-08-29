#include "common.h"
#include "entity.h"
#include "animation_script.h"
#include "ld_addrs.h"

extern AnimScript Entity_BellbellPlant_AnimationIdle;
extern AnimScript Entity_BellbellPlant_AnimationUse;
extern StaticAnimatorNode* Entity_BellbellPlant_Mesh[];

void entity_BellbellPlant_idle(Entity* entity) {
    if ((gPlayerStatus.animFlags & PA_FLAG_INTERACT_PROMPT_AVAILABLE) &&
        (entity->collisionFlags & (ENTITY_COLLISION_PLAYER_HAMMER | ENTITY_COLLISION_PLAYER_TOUCH_WALL))) {
        exec_entity_commandlist(entity);
        play_model_animation(entity->virtualModelIndex, Entity_BellbellPlant_AnimationUse);
    }
}

EntityScript Entity_BellbellPlant_Script = {
    es_SetCallback(entity_BellbellPlant_idle, 0)
    es_ClearFlags(ENTITY_FLAG_SHOWS_INSPECT_PROMPT)
    es_PlaySound(SOUND_PLANTS_BELL)
    es_SetCallback(nullptr, 60)
    es_SetFlags(ENTITY_FLAG_SHOWS_INSPECT_PROMPT)
    es_Restart
    es_End
};

DmaEntry Entity_BellbellPlant_dma[] = { ENTITY_ROM(BellbellPlant_gfx), ENTITY_ROM(BellbellPlant_anim) };

ENTITY_IMPLEMENTATION(BellbellPlant) = {
    .flags = ENTITY_FLAG_SHOWS_INSPECT_PROMPT | ENTITY_FLAG_CIRCULAR_SHADOW | ENTITY_FLAG_400 | ENTITY_FLAG_FIXED_SHADOW_SIZE | ENTITY_FLAG_HAS_ANIMATED_MODEL,
    .typeDataSize = 0,
    .animScript = Entity_BellbellPlant_AnimationIdle,
    .modelAnimationNodes = Entity_BellbellPlant_Mesh,
    .fpInit = nullptr,
    .updateEntityScript = Entity_BellbellPlant_Script,
    .fpHandleCollision = nullptr,
    { .dmaList = Entity_BellbellPlant_dma },
    .entityType = ENTITY_TYPE_BELLBELL_PLANT,
    .aabbSize = { 30, 40, 30 }
};
