#include "common.h"
#include "entity.h"
#include "animation_script.h"
#include "ld_addrs.h"
#include "sprite/player.h"

extern EntityModelScript Entity_RenderNone_Script;

extern AnimScript Entity_MunchlesiaReset_AnimationIdle;
extern AnimScript Entity_MunchlesiaReset_AnimationReset;
extern StaticAnimatorNode* Entity_MunchlesiaReset_Mesh[];
extern AnimScript Entity_MunchlesiaGrab_Animation;
extern StaticAnimatorNode* Entity_MunchlesiaGrab_Mesh[];
extern AnimScript Entity_MunchlesiaEnvelop_Animation;
extern StaticAnimatorNode* Entity_MunchlesiaEnvelop_Mesh[];
extern AnimScript Entity_MunchlesiaBeginChew_Animation;
extern StaticAnimatorNode* Entity_MunchlesiaBeginChew_Mesh[];
extern AnimScript Entity_MunchlesiaChewing_Animation;
extern StaticAnimatorNode* Entity_MunchlesiaChewing_Mesh[];
extern AnimScript Entity_MunchlesiaSpitOut_Animation;
extern StaticAnimatorNode* Entity_MunchlesiaSpitOut_Mesh[];
extern AnimScript Entity_MunchlesiaReset1_Animation;
extern StaticAnimatorNode* Entity_MunchlesiaReset1_Mesh[];

#define MUNCHLESIA_DAMAGE                   1
#define MUNCHLESIA_CHEW_BOB_AMPLITUDE       3.0f
#define MUNCHLESIA_CHEW_PHASE_STEP          24.0f
#define MUNCHLESIA_CHEW_SOUND_PHASE         96.0f
#define MUNCHLESIA_PLAYER_PULL_FRAMES       4
#define MUNCHLESIA_CHEW_FRAMES              44

void entity_Munchlesia_init(Entity* entity) {
    make_item_entity_nodelay(ITEM_COIN, entity->pos.x, entity->pos.y + 30.0f, entity->pos.z,
        ITEM_SPAWN_MODE_FIXED_SPAWN_ALWAYS_NEVER_VANISH, 0);
}

void entity_Munchlesia_idle(Entity* entity) {

    if (entity->collisionFlags & ENTITY_COLLISION_PLAYER_TOUCH_FLOOR) {
        Entity* resetMunchlesia;
        gPlayerStatus.animFlags |= PA_FLAG_INTERRUPT_USE_PARTNER;
        partner_disable_ai_soon();
        resetMunchlesia = get_entity_by_index(entity->dataBuf.munchlesia->resetEntityIndex);
        exec_entity_commandlist(entity);
        exec_entity_commandlist(resetMunchlesia);
    }
}

void entity_MunchlesiaReset_begin(Entity* entity) {
    play_model_animation(entity->virtualModelIndex, Entity_MunchlesiaReset_AnimationReset);
    disable_player_input();
    disable_player_shadow();
}

void entity_MunchlesiaGrab_prepare_player_pull(Entity* entity) {
    MunchlesiaData* data = entity->dataBuf.munchlesia;
    data->playerPullDistance = fabs(dist2D(entity->pos.x, entity->pos.z,
        gPlayerStatus.pos.x, gPlayerStatus.pos.z) * 0.25);
    data->playerPullAngle = atan2(gPlayerStatus.pos.x, gPlayerStatus.pos.z,
        entity->pos.x, entity->pos.z);
}

void entity_MunchlesiaGrab_pull_player(Entity* entity) {
    MunchlesiaData* data = entity->dataBuf.munchlesia;

    gCameras[CAM_DEFAULT].targetPos.x = gPlayerStatus.pos.x;
    gCameras[CAM_DEFAULT].targetPos.y = gPlayerStatus.pos.y;
    gCameras[CAM_DEFAULT].targetPos.z = gPlayerStatus.pos.z;
    add_vec2D_polar(&gPlayerStatus.pos.x, &gPlayerStatus.pos.z,
        data->playerPullDistance, data->playerPullAngle);
}

s32 entity_Munchlesia_create_child(Entity* entity, EntityBlueprint* entityBlueprint) {
    return create_entity(entityBlueprint, (s32)entity->pos.x, (s32)entity->pos.y, (s32)entity->pos.z, (s32)entity->rot.y);
}

void entity_Munchlesia_spawn_reset(Entity* entity) {
    MunchlesiaData* data = entity->dataBuf.munchlesia;
    data->resetEntityIndex = entity_Munchlesia_create_child(entity, &Entity_MunchlesiaReset);
}

void entity_MunchlesiaReset_spawn_grab(Entity* entity) {
    entity_Munchlesia_create_child(entity, &Entity_MunchlesiaGrab);
}

void entity_MunchlesiaGrab_envelop_player(Entity* entity) {
    subtract_hp(MUNCHLESIA_DAMAGE);
    entity_Munchlesia_create_child(entity, &Entity_MunchlesiaEnvelop);
    set_action_state(ACTION_STATE_USE_SPRING);
}

void entity_MunchlesiaEnvelop_begin_chew(Entity* entity) {
    entity_Munchlesia_create_child(entity, &Entity_MunchlesiaBeginChew);
    gPlayerStatus.prevActionState = 0;
    gPlayerStatus.actionState = 0;
    gPlayerStatus.flags &= ~PS_FLAG_ACTION_STATE_CHANGED;
    suggest_player_anim_always_forward(ANIM_MarioW2_FlailArms);
}

void entity_MunchlesiaBeginChew_start_chewing(Entity* entity) {
    entity_Munchlesia_create_child(entity, &Entity_MunchlesiaChewing);
}

void entity_MunchlesiaChewing_spit_out(Entity* entity) {
    entity_Munchlesia_create_child(entity, &Entity_MunchlesiaSpitOut);
    enable_partner_ai();
}

void entity_MunchlesiaSpitOut_spawn_reset1(Entity* entity) {
    entity_Munchlesia_create_child(entity, &Entity_MunchlesiaReset1);
}

void entity_MunchlesiaReset1_spawn_reset2(Entity* entity) {
    entity_Munchlesia_create_child(entity, &Entity_MunchlesiaReset2);
}

void entity_MunchlesiaSpitOut_release_player(void) {
    enable_player_input();
    enable_player_shadow();
    set_action_state(ACTION_STATE_USE_MUNCHLESIA);
}

void entity_MunchlesiaChewing_init(Entity* entity) {
    MunchlesiaData* data = entity->dataBuf.munchlesia;
    data->playerBaseY = gPlayerStatus.pos.y;
    data->chewPhase = 0;
}

void entity_MunchlesiaChewing_update_player(Entity* entity) {
    MunchlesiaData* data = entity->dataBuf.munchlesia;
    gPlayerStatus.pos.y = data->playerBaseY
        + (sin_rad(DEG_TO_RAD(data->chewPhase)) * MUNCHLESIA_CHEW_BOB_AMPLITUDE);

    data->chewPhase += MUNCHLESIA_CHEW_PHASE_STEP;
    if (data->chewPhase > 360.0f) {
        data->chewPhase -= 360.0f;
    }
    if (data->chewPhase == MUNCHLESIA_CHEW_SOUND_PHASE) {
        sfx_play_sound(SOUND_MUNCHLESIA_CHEW);
    }
}

EntityScript Entity_Munchlesia_Script = {
    es_Call(entity_Munchlesia_spawn_reset)
    es_Label(1)
        es_SetCallback(entity_Munchlesia_idle, 0)
        es_SetCallback(nullptr, 80)
    es_Goto(1)
    es_End
};

EntityScript Entity_MunchlesiaReset_Script = {
    es_SetCallback(nullptr, 0)
    es_Call(entity_MunchlesiaReset_begin)
    es_SetCallback(nullptr, 7)
    es_Call(entity_MunchlesiaReset_spawn_grab)
    es_PlaySound(SOUND_MUNCHLESIA_SUCTION)
    es_SetFlags(ENTITY_FLAG_HIDDEN)
    es_SetCallback(nullptr, 3)
    es_SetFlags(ENTITY_FLAG_PENDING_INSTANCE_DELETE)
    es_End
};

EntityScript Entity_MunchlesiaGrab_Script = {
    es_SetCallback(nullptr, 3)
    es_Call(entity_MunchlesiaGrab_prepare_player_pull)
    es_SetCallback(entity_MunchlesiaGrab_pull_player, MUNCHLESIA_PLAYER_PULL_FRAMES)
    es_Call(entity_MunchlesiaGrab_envelop_player)
    es_SetFlags(ENTITY_FLAG_HIDDEN)
    es_SetCallback(nullptr, 3)
    es_SetFlags(ENTITY_FLAG_PENDING_INSTANCE_DELETE)
    es_End
};

EntityScript Entity_MunchlesiaEnvelop_Script = {
    es_SetCallback(nullptr, 7)
    es_Call(entity_MunchlesiaEnvelop_begin_chew)
    es_SetFlags(ENTITY_FLAG_HIDDEN)
    es_SetCallback(nullptr, 3)
    es_SetFlags(ENTITY_FLAG_PENDING_INSTANCE_DELETE)
    es_End
};

EntityScript Entity_MunchlesiaBeginChew_Script = {
    es_SetCallback(nullptr, 8)
    es_Call(entity_MunchlesiaBeginChew_start_chewing)
    es_SetFlags(ENTITY_FLAG_HIDDEN)
    es_SetCallback(nullptr, 3)
    es_SetFlags(ENTITY_FLAG_PENDING_INSTANCE_DELETE)
    es_End
};

EntityScript Entity_MunchlesiaChewing_Script = {
    es_SetCallback(nullptr, 1)
    es_SetCallback(entity_MunchlesiaChewing_update_player, MUNCHLESIA_CHEW_FRAMES)
    es_SetCallback(nullptr, 13)
    es_Call(entity_MunchlesiaChewing_spit_out)
    es_SetFlags(ENTITY_FLAG_HIDDEN)
    es_SetCallback(nullptr, 3)
    es_SetFlags(ENTITY_FLAG_PENDING_INSTANCE_DELETE)
    es_End
};

EntityScript Entity_MunchlesiaSpitOut_Script = {
    es_SetCallback(nullptr, 4)
    es_Call(entity_MunchlesiaSpitOut_release_player)
    es_PlaySound(SOUND_MUNCHLESIA_SPIT)
    es_SetCallback(nullptr, 4)
    es_Call(entity_MunchlesiaSpitOut_spawn_reset1)
    es_SetFlags(ENTITY_FLAG_HIDDEN)
    es_SetCallback(nullptr, 3)
    es_SetFlags(ENTITY_FLAG_PENDING_INSTANCE_DELETE)
    es_End
};

EntityScript Entity_MunchlesiaReset1_Script = {
    es_SetCallback(nullptr, 8)
    es_Call(entity_MunchlesiaReset1_spawn_reset2)
    es_SetFlags(ENTITY_FLAG_HIDDEN)
    es_SetCallback(nullptr, 3)
    es_SetFlags(ENTITY_FLAG_PENDING_INSTANCE_DELETE)
    es_End
};

EntityScript Entity_MunchlesiaReset2_Script = {
    es_SetCallback(nullptr, 9)
    es_Call(entity_Munchlesia_spawn_reset)
    es_SetFlags(ENTITY_FLAG_HIDDEN)
    es_SetCallback(nullptr, 10)
    es_SetFlags(ENTITY_FLAG_PENDING_INSTANCE_DELETE)
    es_End
};

DmaEntry Entity_MunchlesiaReset_dma[] = { ENTITY_ROM(MunchlesiaReset_gfx), ENTITY_ROM(MunchlesiaReset_anim) };
DmaEntry Entity_MunchlesiaGrab_dma[] = { ENTITY_ROM(MunchlesiaGrab_gfx), ENTITY_ROM(MunchlesiaGrab_anim) };
DmaEntry Entity_MunchlesiaEnvelop_dma[] = { ENTITY_ROM(MunchlesiaEnvelop_gfx), ENTITY_ROM(MunchlesiaEnvelop_anim) };
DmaEntry Entity_MunchlesiaBeginChew_dma[] = { ENTITY_ROM(MunchlesiaBeginChew_gfx), ENTITY_ROM(MunchlesiaBeginChew_anim) };
DmaEntry Entity_MunchlesiaChewing_dma[] = { ENTITY_ROM(MunchlesiaChewing_gfx), ENTITY_ROM(MunchlesiaChewing_anim) };
DmaEntry Entity_MunchlesiaSpitOut_dma[] = { ENTITY_ROM(MunchlesiaSpitOut_gfx), ENTITY_ROM(MunchlesiaSpitOut_anim) };
DmaEntry Entity_MunchlesiaReset1_dma[] = { ENTITY_ROM(MunchlesiaReset1_gfx), ENTITY_ROM(MunchlesiaReset1_anim) };

ENTITY_IMPLEMENTATION(Munchlesia) = {
    .flags = ENTITY_FLAG_CIRCULAR_SHADOW | ENTITY_FLAG_400 | ENTITY_FLAG_FIXED_SHADOW_SIZE,
    .typeDataSize = sizeof(MunchlesiaData),
    .renderCommandList = Entity_RenderNone_Script,
    .modelAnimationNodes = nullptr,
    .fpInit = entity_Munchlesia_init,
    .updateEntityScript = Entity_Munchlesia_Script,
    .fpHandleCollision = nullptr,
    { .dmaList = nullptr },
    .entityType = ENTITY_TYPE_MUNCHLESIA,
    .aabbSize = { 45, 20, 45 }
};

ENTITY_IMPLEMENTATION(MunchlesiaReset) = {
    .flags = ENTITY_FLAG_DISABLE_COLLISION | ENTITY_FLAG_HAS_ANIMATED_MODEL,
    .typeDataSize = sizeof(MunchlesiaData),
    .animScript = Entity_MunchlesiaReset_AnimationIdle,
    .modelAnimationNodes = Entity_MunchlesiaReset_Mesh,
    .fpInit = nullptr,
    .updateEntityScript = Entity_MunchlesiaReset_Script,
    .fpHandleCollision = nullptr,
    { .dmaList = Entity_MunchlesiaReset_dma },
    .entityType = ENTITY_TYPE_RESET_MUNCHLESIA,
    .aabbSize = { 40, 20, 40 }
};

ENTITY_IMPLEMENTATION(MunchlesiaGrab) = {
    .flags = ENTITY_FLAG_DISABLE_COLLISION | ENTITY_FLAG_HAS_ANIMATED_MODEL,
    .typeDataSize = sizeof(MunchlesiaData),
    .animScript = Entity_MunchlesiaGrab_Animation,
    .modelAnimationNodes = Entity_MunchlesiaGrab_Mesh,
    .fpInit = nullptr,
    .updateEntityScript = Entity_MunchlesiaGrab_Script,
    .fpHandleCollision = nullptr,
    { .dmaList = Entity_MunchlesiaGrab_dma },
    .entityType = ENTITY_TYPE_MUNCHLESIA_GRAB,
    .aabbSize = { 40, 20, 40 }
};

ENTITY_IMPLEMENTATION(MunchlesiaEnvelop) = {
    .flags = ENTITY_FLAG_DISABLE_COLLISION | ENTITY_FLAG_HAS_ANIMATED_MODEL,
    .typeDataSize = sizeof(MunchlesiaData),
    .animScript = Entity_MunchlesiaEnvelop_Animation,
    .modelAnimationNodes = Entity_MunchlesiaEnvelop_Mesh,
    .fpInit = nullptr,
    .updateEntityScript = Entity_MunchlesiaEnvelop_Script,
    .fpHandleCollision = nullptr,
    { .dmaList = Entity_MunchlesiaEnvelop_dma },
    .entityType = ENTITY_TYPE_MUNCHLESIA_ENVELOP,
    .aabbSize = { 40, 20, 40 }
};

ENTITY_IMPLEMENTATION(MunchlesiaBeginChew) = {
    .flags = ENTITY_FLAG_DISABLE_COLLISION | ENTITY_FLAG_HAS_ANIMATED_MODEL,
    .typeDataSize = sizeof(MunchlesiaData),
    .animScript = Entity_MunchlesiaBeginChew_Animation,
    .modelAnimationNodes = Entity_MunchlesiaBeginChew_Mesh,
    .fpInit = nullptr,
    .updateEntityScript = Entity_MunchlesiaBeginChew_Script,
    .fpHandleCollision = nullptr,
    { .dmaList = Entity_MunchlesiaBeginChew_dma },
    .entityType = ENTITY_TYPE_MUNCHLESIA_BEGIN_CHEW,
    .aabbSize = { 40, 20, 40 }
};

ENTITY_IMPLEMENTATION(MunchlesiaChewing) = {
    .flags = ENTITY_FLAG_DISABLE_COLLISION | ENTITY_FLAG_HAS_ANIMATED_MODEL,
    .typeDataSize = sizeof(MunchlesiaData),
    .animScript = Entity_MunchlesiaChewing_Animation,
    .modelAnimationNodes = Entity_MunchlesiaChewing_Mesh,
    .fpInit = entity_MunchlesiaChewing_init,
    .updateEntityScript = Entity_MunchlesiaChewing_Script,
    .fpHandleCollision = nullptr,
    { .dmaList = Entity_MunchlesiaChewing_dma },
    .entityType = ENTITY_TYPE_MUNCHLESIA_CHEWING,
    .aabbSize = { 40, 20, 40 }
};

ENTITY_IMPLEMENTATION(MunchlesiaSpitOut) = {
    .flags = ENTITY_FLAG_DISABLE_COLLISION | ENTITY_FLAG_HAS_ANIMATED_MODEL,
    .typeDataSize = sizeof(MunchlesiaData),
    .animScript = Entity_MunchlesiaSpitOut_Animation,
    .modelAnimationNodes = Entity_MunchlesiaSpitOut_Mesh,
    .fpInit = nullptr,
    .updateEntityScript = Entity_MunchlesiaSpitOut_Script,
    .fpHandleCollision = nullptr,
    { .dmaList = Entity_MunchlesiaSpitOut_dma },
    .entityType = ENTITY_TYPE_MUNCHLESIA_SPIT_OUT,
    .aabbSize = { 40, 20, 40 }
};

ENTITY_IMPLEMENTATION(MunchlesiaReset1) = {
    .flags = ENTITY_FLAG_DISABLE_COLLISION | ENTITY_FLAG_HAS_ANIMATED_MODEL,
    .typeDataSize = sizeof(MunchlesiaData),
    .animScript = Entity_MunchlesiaReset1_Animation,
    .modelAnimationNodes = Entity_MunchlesiaReset1_Mesh,
    .fpInit = nullptr,
    .updateEntityScript = Entity_MunchlesiaReset1_Script,
    .fpHandleCollision = nullptr,
    { .dmaList = Entity_MunchlesiaReset1_dma },
    .entityType = ENTITY_TYPE_MUNCHLESIA_RESET1,
    .aabbSize = { 40, 20, 40 }
};

ENTITY_IMPLEMENTATION(MunchlesiaReset2) = {
    .flags = ENTITY_FLAG_DISABLE_COLLISION | ENTITY_FLAG_HAS_ANIMATED_MODEL,
    .typeDataSize = sizeof(MunchlesiaData),
    .animScript = Entity_MunchlesiaReset_AnimationIdle,
    .modelAnimationNodes = Entity_MunchlesiaReset_Mesh,
    .fpInit = nullptr,
    .updateEntityScript = Entity_MunchlesiaReset2_Script,
    .fpHandleCollision = nullptr,
    { .dmaList = Entity_MunchlesiaReset_dma },
    .entityType = ENTITY_TYPE_MUNCHLESIA_RESET2,
    .aabbSize = { 40, 20, 40 }
};
