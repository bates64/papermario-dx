#include "common.h"
#include "entity.h"
#include "animation_script.h"
#include "ld_addrs.h"
#include "model.h"

extern Gfx Entity_RenderNone[];
extern AnimScript Entity_PinkFlower_AnimationLightUp;
extern StaticAnimatorNode* Entity_PinkFlower_Mesh[];
extern AnimScript Entity_PinkFlower_AnimationIdle;
extern Mtx Entity_PinkFlowerLight_BaseMtx;
extern Gfx Entity_PinkFlowerLight_Render[];

void entity_PinkFlowerLight_setupGfx(s32 entityIndex) {
    Entity* entity = get_entity_by_index(entityIndex);
    PinkFlowerData* data = entity->dataBuf.pinkFlower;
    Gfx* gfxPos = gMainGfxPos;
    Matrix4f sp18;
    Matrix4f sp58;
    f32 sinAngle, cosAngle;

    guRotateF(sp58, entity->rot.y, 0.0f, 1.0f, 0.0f);
    guScaleF(sp18, entity->scale.x, entity->scale.x, entity->scale.x);
    guMtxCatF(sp18, sp58, sp58);
    guMtxL2F(sp18, ENTITY_ADDR(entity, Mtx*, &Entity_PinkFlowerLight_BaseMtx));
    sin_cos_rad(DEG_TO_RAD(gCameras[CAM_DEFAULT].curYaw + 180.0f), &sinAngle, &cosAngle);
    sp18[3][1] += 10.0f;
    sp18[3][2] -= 10.0f;
    guMtxCatF(sp58, sp18, sp18);
    guRotateF(sp58, entity->rot.z, 0.0f, 0.0f, 1.0f);
    guMtxCatF(sp18, sp58, sp18);
    guRotateF(sp58, data->flowerYaw, 0.0f, 1.0f, 0.0f);
    guMtxCatF(sp18, sp58, sp18);
    guTranslateF(sp58, entity->pos.x + 16.0f * sinAngle, entity->pos.y , entity->pos.z - 16.0f * cosAngle);
    guMtxCatF(sp18, sp58, sp18);
    gDPSetCombineMode(gfxPos++, PM_CC_01, PM_CC_02);
    gDPSetPrimColor(gfxPos++, 0, 0, 0, 0, 0, entity->alpha);
    guMtxF2L(sp18, &gDisplayContext->matrixStack[gMatrixListPos]);
    gSPMatrix(gfxPos++, &gDisplayContext->matrixStack[gMatrixListPos++], G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfxPos++, Entity_PinkFlowerLight_Render);
    gSPPopMatrix(gfxPos++, G_MTX_MODELVIEW);
    gMainGfxPos = gfxPos;
}

void entity_PinkFlower_idle(Entity* entity) {
    PinkFlowerData* data = entity->dataBuf.pinkFlower;

    if (gPlayerStatus.animFlags & PA_FLAG_INTERACT_PROMPT_AVAILABLE
            && entity->collisionFlags & (ENTITY_COLLISION_PLAYER_TOUCH_WALL | ENTITY_COLLISION_PLAYER_HAMMER)) {
        if (entity->flags & ENTITY_FLAG_SHOWS_INSPECT_PROMPT) {
            entity->flags &= ~ENTITY_FLAG_SHOWS_INSPECT_PROMPT;
            data = get_entity_by_index(data->linkedEntityIndex)->dataBuf.pinkFlower;
            if (data->activationPending == 0) {
                data->activationPending = 1;
                exec_entity_commandlist(entity);
                play_model_animation(entity->virtualModelIndex, Entity_PinkFlower_AnimationLightUp);
            }
        }
    }
}

void entity_PinkFlower_init(Entity* entity) {
    PinkFlowerData* data = entity->dataBuf.pinkFlower;
    Entity* newEntity;
    s32 entityIndex;

    get_animator_by_index(entity->virtualModelIndex)->renderMode = RENDER_MODE_SURFACE_XLU_LAYER1;
    entityIndex = create_entity(&Entity_PinkFlowerLight, (s32)entity->pos.x, (s32)entity->pos.y, (s32)entity->pos.z, 0, MAKE_ENTITY_END);
    data->linkedEntityIndex = entityIndex;
    newEntity = get_entity_by_index(entityIndex);
    data = newEntity->dataBuf.pinkFlower;
    data->linkedEntityIndex = entity->listIndex;
    data->flowerYaw = newEntity->rot.y;
}

void entity_PinkFlowerLight_init(Entity* entity) {
    entity->scale.x = 0.0f;
    entity->renderSetupFunc = entity_PinkFlowerLight_setupGfx;
}

void entity_PinkFlowerLight_idle(Entity* entity) {
    PinkFlowerData* data = entity->dataBuf.pinkFlower;

    switch (data->fadeState) {
        case 0:
            if (data->activationPending != 0) {
                data->activationPending = 0;
                data->fadeState++;
                entity->rot.z = -25.0f;
                entity->scale.x = 1.8f;
                entity->alpha = 255;
            }
            break;
        case 1:
            entity->rot.z += 1.0f;
            if (entity->rot.z >= 8.0f) {
                entity->rot.z = 8.0f;
            }

            entity->alpha -= 6;
            if (entity->alpha < 6) {
                entity->alpha = 6;
            }

            entity->scale.x -= 0.03;
            if (entity->scale.x <= 0.1) {
                data->fadeState = 0;
                entity->scale.x = 0.0f;
            }
            entity->scale.y = entity->scale.x;
            entity->scale.z = entity->scale.x;
            break;
    }

    data->flowerYaw = get_entity_by_index(data->linkedEntityIndex)->rot.y;
    entity->rot.y = gCameras[CAM_DEFAULT].curYaw;
}

EntityScript Entity_PinkFlower_Script = {
    es_SetCallback(entity_PinkFlower_idle, 0)
    es_PlaySound(SOUND_PLANTS_LIGHT_UP)
    es_SetCallback(nullptr, 50)
    es_SetFlags(ENTITY_FLAG_SHOWS_INSPECT_PROMPT)
    es_Restart
    es_End
};

EntityScript Entity_PinkFlowerLight_Script = {
    es_SetCallback(entity_PinkFlowerLight_idle, 0)
    es_Restart
    es_End
};

EntityModelScript Entity_PinkFlowerLight_RenderScript = STANDARD_ENTITY_MODEL_SCRIPT(Entity_RenderNone, RENDER_MODE_SURFACE_XLU_LAYER2);
DmaEntry Entity_PinkFlower_dma[] = { ENTITY_ROM(PinkFlower_gfx), ENTITY_ROM(PinkFlower_anim) };

ENTITY_IMPLEMENTATION(PinkFlower) = {
    .flags = ENTITY_FLAG_SHOWS_INSPECT_PROMPT | ENTITY_FLAG_CIRCULAR_SHADOW | ENTITY_FLAG_400 | ENTITY_FLAG_FIXED_SHADOW_SIZE | ENTITY_FLAG_HAS_ANIMATED_MODEL,
    .typeDataSize = sizeof(PinkFlowerData),
    .animScript = Entity_PinkFlower_AnimationIdle,
    .modelAnimationNodes = Entity_PinkFlower_Mesh,
    .fpInit = entity_PinkFlower_init,
    .updateEntityScript = Entity_PinkFlower_Script,
    .fpHandleCollision = nullptr,
    { .dmaList = Entity_PinkFlower_dma },
    .entityType = ENTITY_TYPE_PINK_FLOWER,
    .aabbSize = { 44, 100, 25 }
};

ENTITY_IMPLEMENTATION(PinkFlowerLight) = {
    .flags = ENTITY_FLAG_SHOWS_INSPECT_PROMPT | ENTITY_FLAG_DISABLE_COLLISION,
    .typeDataSize = sizeof(PinkFlowerData),
    .renderCommandList = Entity_PinkFlowerLight_RenderScript,
    .modelAnimationNodes = nullptr,
    .fpInit = entity_PinkFlowerLight_init,
    .updateEntityScript = Entity_PinkFlowerLight_Script,
    .fpHandleCollision = nullptr,
    { .dma = ENTITY_ROM(PinkFlower_gfx) },
    .entityType = ENTITY_TYPE_PINK_FLOWER,
    .aabbSize = { 44, 100, 25 }
};
