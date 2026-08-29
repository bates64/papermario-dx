#include "common.h"
#include "sprite.h"
#include "entity.h"
#include "animation_script.h"
#include "ld_addrs.h"
#include "sprite/player.h"

extern AnimScript Entity_CymbalPlant_AnimationIdle;
extern AnimScript Entity_CymbalPlant_AnimationGrab;
extern StaticAnimatorNode* Entity_CymbalPlant_Mesh[];

BSS f32 SavedPlayerFacingAngle;

void entity_CymbalPlant_prepare_player_pull(Entity* entity) {
    CymbalPlantData* data = entity->dataBuf.cymbalPlant;
    data->playerPullDistance = fabs(dist2D(entity->pos.x - 2.0f, entity->pos.z - 2.0f,
        gPlayerStatus.pos.x, gPlayerStatus.pos.z) * 0.25);
    data->playerPullAngle = atan2(gPlayerStatus.pos.x, gPlayerStatus.pos.z,
        entity->pos.x - 2.0f, entity->pos.z - 2.0f);
}

void entity_CymbalPlant_pull_player(Entity* entity) {
    CymbalPlantData* data = entity->dataBuf.cymbalPlant;
    gCameras[CAM_DEFAULT].targetPos.x = gPlayerStatus.pos.x;
    gCameras[CAM_DEFAULT].targetPos.y = gPlayerStatus.pos.y;
    gCameras[CAM_DEFAULT].targetPos.z = gPlayerStatus.pos.z;
    add_vec2D_polar(&gPlayerStatus.pos.x, &gPlayerStatus.pos.z,
        data->playerPullDistance, data->playerPullAngle);
}

void entity_CymbalPlant_idle(Entity* entity) {
    CymbalPlantData* data = entity->dataBuf.cymbalPlant;
    PartnerStatus* partnerStatus = &gPartnerStatus;
    PlayerStatus* playerStatus = &gPlayerStatus;
    f32 yaw;
    f32 targetYaw;

    switch (data->state) {
        case 0:
            if (entity->collisionFlags & ENTITY_COLLISION_PLAYER_TOUCH_FLOOR) {
                if (partnerStatus->actingPartner != 0) {
                    playerStatus->animFlags |= PA_FLAG_INTERRUPT_USE_PARTNER;
                }
                partner_disable_ai_soon();
                playerStatus->animFlags |= PA_FLAG_INTERRUPT_SPIN;
                data->timer = 4;
                data->unk_01++;
                data->state++;
                disable_player_input();
                set_action_state(ACTION_STATE_IDLE);
                play_model_animation(entity->virtualModelIndex, Entity_CymbalPlant_AnimationGrab);
                sfx_play_sound(SOUND_PLANTS_CYMBAL_CRASH);
                entity_CymbalPlant_prepare_player_pull(entity);
            } else {
                data->unk_01 = 0;
            }
            break;
        case 1:
            playerStatus->animFlags |= PA_FLAG_INTERRUPT_SPIN;
            if (--data->timer == 0) {
                start_rumble(128, 10);
                data->timer = 30;
                data->state++;
                yaw = playerStatus->spriteFacingAngle;
                playerStatus->spriteFacingAngle = 80.0f;
                playerStatus->flags |= PS_FLAG_ROTATION_LOCKED;
                SavedPlayerFacingAngle = yaw;
            }
            entity_CymbalPlant_pull_player(entity);
            break;
        case 2:
            if (--data->timer == 0) {
                data->state++;
                set_player_imgfx_comp(PLAYER_SPRITE_MAIN, -1, IMGFX_CLEAR, 0, 0, 0, 0, 0);
                set_player_imgfx_all(ANIM_Mario1_Idle, IMGFX_SET_ANIM, IMGFX_ANIM_CYMBAL_CRUSH, 1, 1, 0, 0);
            }
            break;
        case 3:
            data->state++;
            break;
        case 4:
            playerStatus->spriteFacingAngle = SavedPlayerFacingAngle;
            targetYaw = 270.0f;
            if (SavedPlayerFacingAngle != 0.0f) {
                targetYaw = 90.0f;
            }
            playerStatus->targetYaw = targetYaw;
            data->timer = 80;
            data->state++;
            break;
        case 5:
            if (--data->timer == 0) {
                data->state++;
                set_player_imgfx_comp(PLAYER_SPRITE_MAIN, -1, IMGFX_CLEAR, 0, 0, 0, 0, 0);
                enable_player_input();
                playerStatus->flags &= ~PS_FLAG_ROTATION_LOCKED;
            }
            break;
        case 6:
            if (!(entity->collisionFlags & ENTITY_COLLISION_PLAYER_TOUCH_FLOOR) && partnerStatus->partnerActionState == PARTNER_ACTION_NONE) {
                data->state = 0;
                enable_partner_ai();
                phys_adjust_cam_on_landing();
            }
            break;
    }
}

EntityScript Entity_CymbalPlant_Update = {
    es_SetCallback(entity_CymbalPlant_idle, 0)
    es_End
};

DmaEntry Entity_CymbalPlant_dma[] = { ENTITY_ROM(CymbalPlant_gfx), ENTITY_ROM(CymbalPlant_anim) };

ENTITY_IMPLEMENTATION(CymbalPlant) = {
    .flags = ENTITY_FLAG_CIRCULAR_SHADOW | ENTITY_FLAG_400 | ENTITY_FLAG_FIXED_SHADOW_SIZE | ENTITY_FLAG_HAS_ANIMATED_MODEL,
    .typeDataSize = sizeof(CymbalPlantData),
    .animScript = Entity_CymbalPlant_AnimationIdle,
    .modelAnimationNodes = Entity_CymbalPlant_Mesh,
    .fpInit = nullptr,
    .updateEntityScript = Entity_CymbalPlant_Update,
    .fpHandleCollision = nullptr,
    { .dmaList = Entity_CymbalPlant_dma },
    .entityType = ENTITY_TYPE_CYMBAL_PLANT,
    .aabbSize = { 103, 30, 24 }
};
