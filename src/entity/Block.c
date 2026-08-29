#include "common.h"
#include "effects.h"
#include "vars_access.h"
#include "ld_addrs.h"
#include "entity.h"

#if VERSION_JP // TODO remove once segments are split
extern Addr entity_model_BrickBlock_ROM_END;
extern Addr entity_model_BrickBlock_ROM_START;
extern Addr entity_model_Hammer1Block_ROM_END;
extern Addr entity_model_Hammer1Block_ROM_START;
extern Addr entity_model_Hammer2Block_ROM_END;
extern Addr entity_model_Hammer2Block_ROM_START;
extern Addr entity_model_Hammer3Block_ROM_END;
extern Addr entity_model_Hammer3Block_ROM_START;
extern Addr entity_model_InertRedBlock_ROM_END;
extern Addr entity_model_InertRedBlock_ROM_START;
extern Addr entity_model_InertYellowBlock_ROM_END;
extern Addr entity_model_InertYellowBlock_ROM_START;
extern Addr entity_model_PowBlock_ROM_END;
extern Addr entity_model_PowBlock_ROM_START;
extern Addr entity_model_PushBlock_ROM_END;
extern Addr entity_model_PushBlock_ROM_START;
#endif

extern Gfx Entity_InertYellowBlock_Render[];
extern Gfx Entity_InertRedBlock_Render[];
extern Gfx Entity_BrickBlock_Render[];
extern Gfx Entity_Hammer1Block_Render[];
extern Gfx Entity_Hammer2Block_Render[];
extern Gfx Entity_Hammer3Block_Render[];
extern Gfx Entity_PushBlock_Render[];
extern Gfx Entity_PowBlock_Render[];

extern EntityScript Entity_CreatedInertBlock_Script;
extern EntityScript Entity_BreakingBlock_Script;
extern EntityScript Entity_InertBlock_Script;

extern EntityBlueprint Entity_ShatteringHammer1Block;
extern EntityBlueprint Entity_ShatteringHammer2Block;
extern EntityBlueprint Entity_ShatteringHammer3Block;
extern EntityBlueprint Entity_ShatteringHammer1BlockTiny;
extern EntityBlueprint Entity_ShatteringHammer2BlockTiny;
extern EntityBlueprint Entity_ShatteringHammer3BlockTiny;
extern EntityBlueprint Entity_ShatteringBrickBlock;

void entity_BrickBlock_idle(Entity* entity);
void entity_breakable_block_create_shattering_entity(Entity* entity);

void entity_MulticoinBlock_update_timer(Entity* entity);

#define MULTICOIN_BLOCK_MAX_COINS 10

void entity_BrickBlock_idle(Entity* entity) {
    entity_base_block_idle(entity);
}

void entity_base_block_setupGfx(s32 entityIndex) {
    Gfx* gfx = gMainGfxPos;
    Entity* entity = get_entity_by_index(entityIndex);

    gDPSetTextureLUT(gfx++, G_TT_NONE);
    gSPTexture(gfx++, -1, -1, 0, G_TX_RENDERTILE, G_ON);

    if (entity->alpha >= 255) {
        gDPSetRenderMode(gfx++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
        gDPSetCombineMode(gfx++, G_CC_MODULATEIA, G_CC_MODULATEIA);
    } else {
        gDPSetCombineMode(gfx++, PM_CC_01, PM_CC_02);
        gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, entity->alpha);
    }

    gMainGfxPos = gfx;
}

void entity_base_block_play_vanish_effect(Entity* entity) {
    fx_cold_breath(0, entity->pos.x, entity->pos.y, entity->pos.z, 1.0f, 0x3C);
}

void entity_MulticoinBlock_init(Entity* entity) {
    BlockData* data;

    entity_base_block_init(entity);
    data = entity->dataBuf.block;
    data->coinsLeft = MULTICOIN_BLOCK_MAX_COINS;
    data->timeLeft = 123;
    data->gameFlagIndex = 0xFFFF;
}

void entity_MulticoinBlock_spawn_coin(Entity* entity) {
    BlockData* data = entity->dataBuf.block;
    s32 itemSpawnMode;
    s32 flagIndex;

    if (data->coinsLeft > 0) {
        if (data->coinsLeft == MULTICOIN_BLOCK_MAX_COINS) {
            itemSpawnMode = ITEM_SPAWN_MODE_ITEM_BLOCK_COIN;
            flagIndex = data->gameFlagIndex;
        } else {
            itemSpawnMode = ITEM_SPAWN_MODE_ITEM_BLOCK_SPAWN_ALWAYS;
            flagIndex = 0;
        }
        make_item_entity_nodelay(ITEM_COIN, entity->pos.x, entity->pos.y + 28.0, entity->pos.z,
            itemSpawnMode, flagIndex);
        data->coinsLeft--;
    }

    if ((data->coinsLeft == 0) || (data->timeLeft == 0)) {
        data->empty = true;
        set_entity_commandlist(get_entity_by_index(create_entity(&Entity_InertYellowBlock,
            (s32)entity->pos.x, (s32)entity->pos.y, (s32)entity->pos.z,
            (s32)entity->rot.y, MAKE_ENTITY_END)), Entity_CreatedInertBlock_Script);
        entity->flags |= (ENTITY_FLAG_DISABLE_COLLISION | ENTITY_FLAG_PENDING_INSTANCE_DELETE);
    }
}

void entity_MulticoinBlock_idle(Entity* entity) {
    BlockData* data = entity->dataBuf.block;

    if (entity->collisionFlags & ENTITY_COLLISION_PARTNER) {
        exec_entity_commandlist(entity);
        return;
    }
    entity_MulticoinBlock_update_timer(entity);
    entity_base_block_idle(entity);
    if (data->empty) {
        create_entity(&Entity_InertYellowBlock, (s32)entity->pos.x, (s32)entity->pos.y, (s32)entity->pos.z, (s32)entity->rot.y, MAKE_ENTITY_END);
        entity->flags |= (ENTITY_FLAG_DISABLE_COLLISION | ENTITY_FLAG_PENDING_INSTANCE_DELETE);
    }
}

void entity_MulticoinBlock_check_if_inactive(Entity* entity) {
    BlockData* data = entity->dataBuf.block;

    if (data->gameFlagIndex != 0xFFFF) {
        if (get_global_flag(data->gameFlagIndex) != 0) {
            create_entity(&Entity_InertYellowBlock, (s32)entity->pos.x, (s32)entity->pos.y, (s32)entity->pos.z, (s32)entity->rot.y, MAKE_ENTITY_END);
            entity->flags |= (ENTITY_FLAG_DISABLE_COLLISION | ENTITY_FLAG_PENDING_INSTANCE_DELETE);
        }
    }
}

void entity_init_Hammer1Block_normal(Entity* entity) {
    entity_base_block_init(entity);
    entity->renderSetupFunc = entity_base_block_setupGfx;
}

void entity_init_HammerBlock_small(Entity* entity) {
    BlockData* data = entity->dataBuf.block;

    data->item = -1;
    data->initialY = entity->pos.y;
    data->sinkingTimer = -1;
    entity->flags &= ~ENTITY_FLAG_200000;
    entity->scale.x = 0.5f;
    entity->scale.y = 0.5f;
    entity->scale.z = 0.5f;
}

EntityScript Entity_PowBlock_Script = {
    es_SetCallback(entity_base_block_idle, 0)
    es_PlaySound(SOUND_HIT_BLOCK)
    es_Call(entity_block_hit_init_scale)
    es_SetCallback(entity_block_hit_animate_scale, 6)
    es_Call(entity_start_script)
    es_Restart
    es_End
};
EntityScript Entity_BaseBlock_Script = {
    es_SetCallback(entity_base_block_idle, 0)
    es_Call(entity_start_script)
    es_Restart
    es_End
};
EntityScript D_802E9DEC = {
    es_SetCallback(entity_base_block_idle, 0)
    es_PlaySound(SOUND_HIT_BLOCK)
    es_Restart
    es_End
};
EntityScript Entity_CreatedInertBlock_Script = {
    es_Call(entity_inactive_block_hit_init)
    es_SetCallback(entity_inactive_block_hit_anim, 0)
    es_SetCallback(entity_inactive_block_recoil_anim, 0)
    es_Jump(Entity_InertBlock_Script)
    es_End
};
EntityScript Entity_BrickBlock_Script = {
    es_SetCallback(entity_BrickBlock_idle, 0)
    es_Call(entity_start_script)
    es_SetFlags(ENTITY_FLAG_HIDDEN)
    es_SetFlags(ENTITY_FLAG_DISABLE_COLLISION)
    es_Call(entity_breakable_block_create_shattering_entity)
    es_PlaySound(SOUND_HIT_BLOCK)
    es_SetCallback(nullptr, 2)
    es_SetFlags(ENTITY_FLAG_PENDING_INSTANCE_DELETE)
    es_End
};
EntityScript Entity_Hammer1Block_Script = {
    es_SetCallback(entity_base_block_idle, 0)
    es_PlaySound(SOUND_HIT_BLOCK)
    es_Call(entity_start_script)
    es_Restart
    es_End
};
EntityScript Entity_MulticoinBlock_Script = {
    es_Call(entity_MulticoinBlock_check_if_inactive)
    es_Label(1)
        es_SetCallback(entity_MulticoinBlock_idle, 0)
        es_PlaySound(SOUND_HIT_BLOCK)
        es_Call(entity_MulticoinBlock_spawn_coin)
        es_Call(entity_inactive_block_hit_init)
        es_SetCallback(entity_inactive_block_hit_anim, 0)
        es_SetCallback(entity_inactive_block_recoil_anim, 0)
    es_Goto(1)
    es_End
};

EntityModelScript Entity_InertYellowBlock_RenderScript = STANDARD_ENTITY_MODEL_SCRIPT(Entity_InertYellowBlock_Render, RENDER_MODE_SURFACE_OPA);

EntityModelScript Entity_InertRedBlock_RenderScript = STANDARD_ENTITY_MODEL_SCRIPT(Entity_InertRedBlock_Render, RENDER_MODE_SURFACE_OPA);

EntityModelScript Entity_MulticoinBrick_RenderScript = STANDARD_ENTITY_MODEL_SCRIPT(Entity_BrickBlock_Render, RENDER_MODE_SURFACE_OPA);

EntityModelScript Entity_Hammer1Block_RenderScript = STANDARD_ENTITY_MODEL_SCRIPT(Entity_Hammer1Block_Render, RENDER_MODE_SURFACE_OPA);

EntityModelScript Entity_Hammer2Block_RenderScript = STANDARD_ENTITY_MODEL_SCRIPT(Entity_Hammer2Block_Render, RENDER_MODE_SURFACE_OPA);

EntityModelScript Entity_Hammer3Block_RenderScript = STANDARD_ENTITY_MODEL_SCRIPT(Entity_Hammer3Block_Render, RENDER_MODE_SURFACE_OPA);

EntityModelScript Entity_PushBlock_RenderScript = STANDARD_ENTITY_MODEL_SCRIPT(Entity_PushBlock_Render, RENDER_MODE_SURFACE_OPA);

EntityModelScript Entity_BrickBlock_RenderScript = STANDARD_ENTITY_MODEL_SCRIPT(Entity_BrickBlock_Render, RENDER_MODE_SURFACE_OPA);

EntityModelScript Entity_PowBlock_RenderScript = STANDARD_ENTITY_MODEL_SCRIPT(Entity_PowBlock_Render, RENDER_MODE_SURFACE_OPA);

ENTITY_IMPLEMENTATION(InertYellowBlock) = {
    .flags = ENTITY_FLAG_4000 | ENTITY_FLAG_FIXED_SHADOW_SIZE,
    .typeDataSize = sizeof(BlockData),
    .renderCommandList = Entity_InertYellowBlock_RenderScript,
    .modelAnimationNodes = nullptr,
    .fpInit = entity_init_Hammer1Block_normal,
    .updateEntityScript = Entity_InertBlock_Script,
    .fpHandleCollision = entity_block_handle_collision,
    { .dma = ENTITY_ROM(InertYellowBlock) },
    .entityType = ENTITY_TYPE_MULTI_TRIGGER_BLOCK,
    .aabbSize = { 25, 25, 25 }
};

ENTITY_IMPLEMENTATION(InertRedBlock) = {
    .flags = ENTITY_FLAG_4000 | ENTITY_FLAG_FIXED_SHADOW_SIZE,
    .typeDataSize = sizeof(BlockData),
    .renderCommandList = Entity_InertRedBlock_RenderScript,
    .modelAnimationNodes = nullptr,
    .fpInit = entity_init_Hammer1Block_normal,
    .updateEntityScript = Entity_InertBlock_Script,
    .fpHandleCollision = entity_block_handle_collision,
    { .dma = ENTITY_ROM(InertRedBlock) },
    .entityType = ENTITY_TYPE_INACTIVE_BLOCK,
    .aabbSize = { 25, 25, 25 }
};

ENTITY_IMPLEMENTATION(BrickBlock) = {
    .flags = ENTITY_FLAG_4000 | ENTITY_FLAG_FIXED_SHADOW_SIZE | ENTITY_FLAG_80,
    .typeDataSize = sizeof(BlockData),
    .renderCommandList = Entity_BrickBlock_RenderScript,
    .modelAnimationNodes = nullptr,
    .fpInit = entity_base_block_init,
    .updateEntityScript = Entity_BrickBlock_Script,
    .fpHandleCollision = entity_block_handle_collision,
    { .dma = ENTITY_ROM(BrickBlock) },
    .entityType = ENTITY_TYPE_BRICK_BLOCK,
    .aabbSize = { 25, 25, 25 }
};

ENTITY_IMPLEMENTATION(MulticoinBlock) = {
    .flags = ENTITY_FLAG_4000 | ENTITY_FLAG_FIXED_SHADOW_SIZE,
    .typeDataSize = sizeof(BlockData),
    .renderCommandList = Entity_MulticoinBrick_RenderScript,
    .modelAnimationNodes = nullptr,
    .fpInit = entity_MulticoinBlock_init,
    .updateEntityScript = Entity_MulticoinBlock_Script,
    .fpHandleCollision = entity_block_handle_collision,
    { .dma = ENTITY_ROM(BrickBlock) },
    .entityType = ENTITY_TYPE_MULTI_COIN_BRICK,
    .aabbSize = { 25, 25, 25 }
};

ENTITY_IMPLEMENTATION(Hammer1Block) = {
    .flags = ENTITY_FLAG_4000 | ENTITY_FLAG_FIXED_SHADOW_SIZE | ENTITY_FLAG_80,
    .typeDataSize = sizeof(BlockData),
    .renderCommandList = Entity_Hammer1Block_RenderScript,
    .modelAnimationNodes = nullptr,
    .fpInit = entity_init_Hammer1Block_normal,
    .updateEntityScript = Entity_Hammer1Block_Script,
    .fpHandleCollision = entity_block_handle_collision,
    { .dma = ENTITY_ROM(Hammer1Block) },
    .entityType = ENTITY_TYPE_HAMMER1_BLOCK,
    .aabbSize = { 50, 50, 50 }
};

ENTITY_IMPLEMENTATION(Hammer1BlockWideX) = {
    .flags = ENTITY_FLAG_4000 | ENTITY_FLAG_FIXED_SHADOW_SIZE | ENTITY_FLAG_80,
    .typeDataSize = sizeof(BlockData),
    .renderCommandList = Entity_Hammer1Block_RenderScript,
    .modelAnimationNodes = nullptr,
    .fpInit = entity_init_Hammer1Block_normal,
    .updateEntityScript = Entity_Hammer1Block_Script,
    .fpHandleCollision = entity_block_handle_collision,
    { .dma = ENTITY_ROM(Hammer1Block) },
    .entityType = ENTITY_TYPE_HAMMER1_BLOCK,
    .aabbSize = { 100, 50, 50 }
};

ENTITY_IMPLEMENTATION(Hammer1BlockWideZ) = {
    .flags = ENTITY_FLAG_4000 | ENTITY_FLAG_FIXED_SHADOW_SIZE | ENTITY_FLAG_80,
    .typeDataSize = sizeof(BlockData),
    .renderCommandList = Entity_Hammer1Block_RenderScript,
    .modelAnimationNodes = nullptr,
    .fpInit = entity_init_Hammer1Block_normal,
    .updateEntityScript = Entity_Hammer1Block_Script,
    .fpHandleCollision = entity_block_handle_collision,
    { .dma = ENTITY_ROM(Hammer1Block) },
    .entityType = ENTITY_TYPE_HAMMER1_BLOCK,
    .aabbSize = { 50, 50, 100 }
};

ENTITY_IMPLEMENTATION(Hammer1BlockTiny) = {
    .flags = ENTITY_FLAG_4000 | ENTITY_FLAG_FIXED_SHADOW_SIZE | ENTITY_FLAG_80,
    .typeDataSize = sizeof(BlockData),
    .renderCommandList = Entity_Hammer1Block_RenderScript,
    .modelAnimationNodes = nullptr,
    .fpInit = entity_init_HammerBlock_small,
    .updateEntityScript = Entity_BaseBlock_Script,
    .fpHandleCollision = entity_block_handle_collision,
    { .dma = ENTITY_ROM(Hammer1Block) },
    .entityType = ENTITY_TYPE_HAMMER1_BLOCK_TINY,
    .aabbSize = { 25, 25, 25 }
};

ENTITY_IMPLEMENTATION(Hammer2Block) = {
    .flags = ENTITY_FLAG_4000 | ENTITY_FLAG_FIXED_SHADOW_SIZE | ENTITY_FLAG_80,
    .typeDataSize = sizeof(BlockData),
    .renderCommandList = Entity_Hammer2Block_RenderScript,
    .modelAnimationNodes = nullptr,
    .fpInit = entity_base_block_init,
    .updateEntityScript = Entity_BaseBlock_Script,
    .fpHandleCollision = entity_block_handle_collision,
    { .dma = ENTITY_ROM(Hammer2Block) },
    .entityType = ENTITY_TYPE_HAMMER2_BLOCK,
    .aabbSize = { 50, 50, 50 }
};

ENTITY_IMPLEMENTATION(Hammer2BlockWideX) = {
    .flags = ENTITY_FLAG_4000 | ENTITY_FLAG_FIXED_SHADOW_SIZE | ENTITY_FLAG_80,
    .typeDataSize = sizeof(BlockData),
    .renderCommandList = Entity_Hammer2Block_RenderScript,
    .modelAnimationNodes = nullptr,
    .fpInit = entity_base_block_init,
    .updateEntityScript = Entity_BaseBlock_Script,
    .fpHandleCollision = entity_block_handle_collision,
    { .dma = ENTITY_ROM(Hammer2Block) },
    .entityType = ENTITY_TYPE_HAMMER2_BLOCK,
    .aabbSize = { 100, 50, 50 }
};

ENTITY_IMPLEMENTATION(Hammer2BlockWideZ) = {
    .flags = ENTITY_FLAG_4000 | ENTITY_FLAG_FIXED_SHADOW_SIZE | ENTITY_FLAG_80,
    .typeDataSize = sizeof(BlockData),
    .renderCommandList = Entity_Hammer2Block_RenderScript,
    .modelAnimationNodes = nullptr,
    .fpInit = entity_base_block_init,
    .updateEntityScript = Entity_BaseBlock_Script,
    .fpHandleCollision = entity_block_handle_collision,
    { .dma = ENTITY_ROM(Hammer2Block) },
    .entityType = ENTITY_TYPE_HAMMER2_BLOCK,
    .aabbSize = { 50, 50, 100 }
};

ENTITY_IMPLEMENTATION(Hammer2BlockTiny) = {
    .flags = ENTITY_FLAG_4000 | ENTITY_FLAG_FIXED_SHADOW_SIZE | ENTITY_FLAG_80,
    .typeDataSize = sizeof(BlockData),
    .renderCommandList = Entity_Hammer2Block_RenderScript,
    .modelAnimationNodes = nullptr,
    .fpInit = entity_init_HammerBlock_small,
    .updateEntityScript = Entity_BaseBlock_Script,
    .fpHandleCollision = entity_block_handle_collision,
    { .dma = ENTITY_ROM(Hammer2Block) },
    .entityType = ENTITY_TYPE_HAMMER2_BLOCK_TINY,
    .aabbSize = { 25, 25, 25 }
};

ENTITY_IMPLEMENTATION(Hammer3Block) = {
    .flags = ENTITY_FLAG_4000 | ENTITY_FLAG_FIXED_SHADOW_SIZE | ENTITY_FLAG_80,
    .typeDataSize = sizeof(BlockData),
    .renderCommandList = Entity_Hammer3Block_RenderScript,
    .modelAnimationNodes = nullptr,
    .fpInit = entity_base_block_init,
    .updateEntityScript = Entity_BaseBlock_Script,
    .fpHandleCollision = entity_block_handle_collision,
    { .dma = ENTITY_ROM(Hammer3Block) },
    .entityType = ENTITY_TYPE_HAMMER3_BLOCK,
    .aabbSize = { 50, 50, 50 }
};

ENTITY_IMPLEMENTATION(Hammer3BlockWideX) = {
    .flags = ENTITY_FLAG_4000 | ENTITY_FLAG_FIXED_SHADOW_SIZE | ENTITY_FLAG_80,
    .typeDataSize = sizeof(BlockData),
    .renderCommandList = Entity_Hammer3Block_RenderScript,
    .modelAnimationNodes = nullptr,
    .fpInit = entity_base_block_init,
    .updateEntityScript = Entity_BaseBlock_Script,
    .fpHandleCollision = entity_block_handle_collision,
    { .dma = ENTITY_ROM(Hammer3Block) },
    .entityType = ENTITY_TYPE_HAMMER3_BLOCK,
    .aabbSize = { 100, 50, 50 }
};

ENTITY_IMPLEMENTATION(Hammer3BlockWideZ) = {
    .flags = ENTITY_FLAG_4000 | ENTITY_FLAG_FIXED_SHADOW_SIZE | ENTITY_FLAG_80,
    .typeDataSize = sizeof(BlockData),
    .renderCommandList = Entity_Hammer3Block_RenderScript,
    .modelAnimationNodes = nullptr,
    .fpInit = entity_base_block_init,
    .updateEntityScript = Entity_BaseBlock_Script,
    .fpHandleCollision = entity_block_handle_collision,
    { .dma = ENTITY_ROM(Hammer3Block) },
    .entityType = ENTITY_TYPE_HAMMER3_BLOCK,
    .aabbSize = { 50, 50, 100 }
};

ENTITY_IMPLEMENTATION(Hammer3BlockTiny) = {
    .flags = ENTITY_FLAG_4000 | ENTITY_FLAG_FIXED_SHADOW_SIZE | ENTITY_FLAG_80,
    .typeDataSize = sizeof(BlockData),
    .renderCommandList = Entity_Hammer3Block_RenderScript,
    .modelAnimationNodes = nullptr,
    .fpInit = entity_init_HammerBlock_small,
    .updateEntityScript = Entity_BaseBlock_Script,
    .fpHandleCollision = entity_block_handle_collision,
    { .dma = ENTITY_ROM(Hammer3Block) },
    .entityType = ENTITY_TYPE_HAMMER3_BLOCK_TINY,
    .aabbSize = { 25, 25, 25 }
};

ENTITY_IMPLEMENTATION(PushBlock) = {
    .flags = ENTITY_FLAG_4000,
    .typeDataSize = sizeof(BlockData),
    .renderCommandList = Entity_PushBlock_RenderScript,
    .modelAnimationNodes = nullptr,
    .fpInit = entity_base_block_init,
    .updateEntityScript = Entity_BaseBlock_Script,
    .fpHandleCollision = entity_block_handle_collision,
    { .dma = ENTITY_ROM(PushBlock) },
    .entityType = ENTITY_TYPE_PUSH_BLOCK,
    .aabbSize = { 25, 25, 25 }
};

ENTITY_IMPLEMENTATION(PowBlock) = {
    .flags = ENTITY_FLAG_4000,
    .typeDataSize = sizeof(BlockData),
    .renderCommandList = Entity_PowBlock_RenderScript,
    .modelAnimationNodes = nullptr,
    .fpInit = entity_base_block_init,
    .updateEntityScript = Entity_PowBlock_Script,
    .fpHandleCollision = entity_block_handle_collision,
    { .dma = ENTITY_ROM(PowBlock) },
    .entityType = ENTITY_TYPE_POW_BLOCK,
    .aabbSize = { 30, 25, 25 },
};
