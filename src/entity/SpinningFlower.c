#include "common.h"
#include "entity.h"
#include "ld_addrs.h"
#include "model.h"
#include "sprite/player.h"

extern Mtx PetalBaseMtx;
extern Gfx Entity_SpinningFlower_RenderPetals[];
extern Gfx Entity_SpinningFlower_Render[];

#define SPINNING_FLOWER_LAUNCH_TRIGGER_RADIUS 60.0
#define SPINNING_FLOWER_DEFAULT_GOAL_HEIGHT   100.0f
#define SPINNING_FLOWER_MAX_IDLE_SPEED        14.0f
#define SPINNING_FLOWER_MAX_LAUNCH_SPEED      40.0f
#define SPINNING_FLOWER_LAUNCH_SPIN_FRAMES    70

void entity_SpinningFlower_setupGfx(s32 entityIndex) {
    Entity* entity = get_entity_by_index(entityIndex);
    SpinningFlowerData* data = entity->dataBuf.spinningFlower;
    Gfx* gfxPos = gMainGfxPos;
    Matrix4f sp18;
    Matrix4f sp58;
    Matrix4f sp98;
    Gfx* gfx;

    guMtxL2F(sp18, ENTITY_ADDR(entity, Mtx*, &PetalBaseMtx));
    guRotateF(sp58, data->rot.x, 1.0f, 0.0f, 0.0f);
    guRotateF(sp98, data->rot.z, 0.0f, 0.0f, 1.0f);
    guMtxCatF(sp58, sp98, sp98);
    guRotateF(sp58, data->rot.y, 0.0f, 1.0f, 0.0f);
    guMtxCatF(sp98, sp58, sp58);
    guMtxCatF(sp58, sp18, sp18);
    guMtxF2L(sp18, &data->petalMtx);
    gDisplayContext->matrixStack[gMatrixListPos] = data->petalMtx;
    gSPMatrix(gfxPos++, &gDisplayContext->matrixStack[gMatrixListPos++], G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
    gfx = ENTITY_ADDR(entity, Gfx*, Entity_SpinningFlower_RenderPetals);
    gSPDisplayList(gfxPos++, gfx);
    gSPPopMatrix(gfxPos++, G_MTX_MODELVIEW);
    gMainGfxPos = gfxPos;
}

void entity_SpinningFlower_check_player_interaction(Entity* entity) {
    SpinningFlowerData* data = entity->dataBuf.spinningFlower;
    PlayerStatus* playerStatus = &gPlayerStatus;

    if ((entity->collisionFlags & ENTITY_COLLISION_PLAYER_TOUCH_FLOOR) && !is_picking_up_item()) {
        if (playerStatus->actionState == ACTION_STATE_RIDE) {
            playerStatus->animFlags |= PA_FLAG_INTERRUPT_USE_PARTNER;
        } else if (playerStatus->actionState != ACTION_STATE_USE_SPINNING_FLOWER) {
            FlowerGoalPosition.x = data->goalPos.x;
            FlowerGoalPosition.y = data->goalPos.y;
            FlowerGoalPosition.z = data->goalPos.z;
            set_action_state(ACTION_STATE_USE_SPINNING_FLOWER);
        }
    }
}

void entity_SpinningFlower_idle(Entity* entity) {
    SpinningFlowerData* data = entity->dataBuf.spinningFlower;
    PlayerStatus* playerStatus = &gPlayerStatus;

    entity_SpinningFlower_check_player_interaction(entity);
    switch (data->state) {
        case 0:
            data->unk_18 = 0;
            data->unk_00 = 0;
            data->state = 1;
            data->rot.x = 0.0f;
            data->rot.z = 0.0f;
            break;
        case 1:
            if (!(entity->collisionFlags & ENTITY_COLLISION_PLAYER_TOUCH_FLOOR)) {
                data->spinSpeed += 0.02;
                if (data->spinSpeed > 2.0) {
                    if (data->spinSpeed > 2.0) {
                        data->spinSpeed -= 0.4;
                    }
                }
            } else {
                data->spinSpeed += 0.8;
                if (data->spinSpeed > SPINNING_FLOWER_MAX_IDLE_SPEED) {
                    data->spinSpeed = SPINNING_FLOWER_MAX_IDLE_SPEED;
                }
            }
            break;
    }

    data->rot.y = clamp_angle(data->rot.y + data->spinSpeed);

    if (!(entity->collisionFlags & ENTITY_COLLISION_PLAYER_TOUCH_FLOOR) &&
        (playerStatus->animFlags & PA_FLAG_SPINNING) &&
        fabs(dist2D(entity->pos.x, entity->pos.z, playerStatus->pos.x, playerStatus->pos.z)) < SPINNING_FLOWER_LAUNCH_TRIGGER_RADIUS)
        {
        exec_entity_commandlist(entity);
    }
}

void entity_SpinningFlower_spin_fast(Entity* entity) {
    SpinningFlowerData* data = entity->dataBuf.spinningFlower;

    entity_SpinningFlower_check_player_interaction(entity);
    data->spinSpeed += 2.0;
    if (data->spinSpeed > SPINNING_FLOWER_MAX_LAUNCH_SPEED) {
        data->spinSpeed = SPINNING_FLOWER_MAX_LAUNCH_SPEED;
    }
    data->rot.y = clamp_angle(data->rot.y + data->spinSpeed);
}

void entity_SpinningFlower_init(Entity* entity) {
    SpinningFlowerData* data = entity->dataBuf.spinningFlower;
    s32 x, y, z;

    x = CreateEntityVarArgBuffer[0];
    y = CreateEntityVarArgBuffer[1];
    z = CreateEntityVarArgBuffer[2];
    if (!(x | y | z)) {
        x = entity->pos.x;
        y = entity->pos.y + SPINNING_FLOWER_DEFAULT_GOAL_HEIGHT;
        z = entity->pos.z;
    }

    data->goalPos.x = x;
    data->goalPos.y = y;
    data->goalPos.z = z;
    data->state = 0;
    entity->renderSetupFunc = entity_SpinningFlower_setupGfx;
}

void entity_SpinningFlower_start_spin_sound(Entity* entity) {
    sfx_play_sound_at_position(SOUND_LOOP_SPINNING_FLOWER, SOUND_SPACE_DEFAULT, entity->pos.x, entity->pos.y, entity->pos.z);
}

void entity_SpinningFlower_stop_spin_sound(Entity* entity) {
    sfx_play_sound(SOUND_LRAW_SPINNING_FLOWER | SOUND_ID_TRIGGER_CHANGE_SOUND);
    sfx_stop_tracking_env_sound_pos(SOUND_LRAW_SPINNING_FLOWER, true);
}

EntityScript Entity_SpinningFlower_Script = {
    es_SetCallback(entity_SpinningFlower_idle, 0)
    es_Call(entity_SpinningFlower_start_spin_sound)
    es_SetCallback(entity_SpinningFlower_spin_fast, SPINNING_FLOWER_LAUNCH_SPIN_FRAMES)
    es_Call(entity_SpinningFlower_stop_spin_sound)
    es_Restart
    es_End
};

EntityModelScript Entity_SpinningFlower_RenderScript = STANDARD_ENTITY_MODEL_SCRIPT(Entity_SpinningFlower_Render, RENDER_MODE_SURFACE_XLU_LAYER1);

ENTITY_IMPLEMENTATION(SpinningFlower) = {
    .flags = 0,
    .typeDataSize = sizeof(SpinningFlowerData),
    .renderCommandList = Entity_SpinningFlower_RenderScript,
    .modelAnimationNodes = nullptr,
    .fpInit = entity_SpinningFlower_init,
    .updateEntityScript = Entity_SpinningFlower_Script,
    .fpHandleCollision = nullptr,
    { .dma = ENTITY_ROM(SpinningFlower) },
    .entityType = ENTITY_TYPE_SPINNING_FLOWER,
    .aabbSize = { 45, 22, 42 }
};
