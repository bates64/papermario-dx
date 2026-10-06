#include "tst_04.h"
#include "sprite.h"
#include "entity.h"
#include "model.h"

void worker_render_player_reflection(void);
void appendGfx_test_player_reflection(void* data);
void worker_update_partner_reflection(void);

static s32 Animator;

API_CALLABLE(EnablePlayerReflection) {
    script->array[0] = create_worker_frontUI(nullptr, &worker_render_player_reflection);
    return ApiStatus_DONE2;
}

void worker_render_player_reflection(void) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    EntityModel* entityModel;
    RenderTask renderTask;
    RenderTask* renderTaskPtr = &renderTask;
    s32 screenX;
    s32 screenY;
    s32 screenZ;

    if (playerStatus->flags & PS_FLAG_HAS_REFLECTION) {
        entityModel = get_entity_model(get_shadow_by_index(playerStatus->shadowID)->entityModelID);
        entityModel->flags |= ENTITY_MODEL_FLAG_REFLECT;

        get_screen_coords(gCurrentCamID, playerStatus->pos.x, playerStatus->pos.y, -playerStatus->pos.z,
                          &screenX, &screenY, &screenZ);

        renderTaskPtr->renderMode = playerStatus->renderMode;
        renderTaskPtr->appendGfxArg = playerStatus;
        renderTaskPtr->appendGfx = &appendGfx_test_player_reflection;
        renderTaskPtr->dist = -screenZ;
        queue_render_task(renderTaskPtr);
    }
}

void appendGfx_test_player_reflection(void* data) {
    PlayerStatus* playerStatus = data;
    f32 yaw = -gCameras[gCurrentCamID].curYaw;
    Matrix4f main;
    Matrix4f translation;
    Matrix4f rotation;
    Matrix4f scale;

    guRotateF(rotation, yaw, 0.0f, -1.0f, 0.0f);
    guRotateF(main, clamp_angle(playerStatus->pitch), 0.0f, 0.0f, 1.0f);
    guMtxCatF(rotation, main, main);
    guRotateF(rotation, yaw, 0.0f, 1.0f, 0.0f);
    guMtxCatF(main, rotation, main);
    guRotateF(rotation, playerStatus->spriteFacingAngle, 0.0f, 1.0f, 0.0f);
    guMtxCatF(main, rotation, main);
    guScaleF(scale, SPRITE_WORLD_SCALE_F, SPRITE_WORLD_SCALE_F, SPRITE_WORLD_SCALE_F);
    guMtxCatF(main, scale, main);
    guTranslateF(translation, playerStatus->pos.x, playerStatus->pos.y, -playerStatus->pos.z);
    guMtxCatF(main, translation, main);
    spr_update_player_sprite(PLAYER_SPRITE_AUX1, playerStatus->trueAnimation, 1.0f);
    spr_draw_player_sprite(PLAYER_SPRITE_AUX1, 0, 0, nullptr, main);
}

API_CALLABLE(EnablePartnerReflection) {
    Npc* partner;

    script->array[1] = create_worker_scene(&worker_update_partner_reflection, nullptr);
    partner = get_npc_safe(NPC_PARTNER);

    if (partner == nullptr) {
        return ApiStatus_DONE2;
    }

    partner->flags |= NPC_FLAG_REFLECT_WALL;
    partner->flags |= NPC_FLAG_REFLECT_FLOOR;
    return ApiStatus_DONE2;
}

void worker_update_partner_reflection(void) {
    Npc* partner = get_npc_safe(NPC_PARTNER);

    if (partner != nullptr) {
        partner->flags |= NPC_FLAG_REFLECT_WALL;
        partner->flags |= NPC_FLAG_REFLECT_FLOOR;
    }
}

void worker_update_animator(void) {
    update_model_animator(Animator);
}

void worker_draw_animator(void) {
    Matrix4f tempMtx;
    Mtx transformMtx;

    guTranslateF(tempMtx, -484.0f, 25.0f, -40.0f);
    guMtxF2L(tempMtx, &transformMtx);
    render_animated_model(Animator, &transformMtx);
}

API_CALLABLE(SetupAnimatedModel) {
    create_worker_scene(worker_update_animator, worker_draw_animator);
    return ApiStatus_DONE2;
}

EvtScript EVS_SetupReflection = {
    Call(SetupAnimatedModel)
    MallocArray(16, LVarA)
    Call(EnablePlayerReflection)
    Call(EnablePartnerReflection)
    Return
    End
};
