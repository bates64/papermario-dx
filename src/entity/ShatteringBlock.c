#include "common.h"
#include "ld_addrs.h"
#include "entity.h"

#if VERSION_JP // TODO remove once segments are split
extern Addr entity_model_ShatteringBrickBlock_ROM_END;
extern Addr entity_model_ShatteringBrickBlock_ROM_START;
extern Addr entity_model_ShatteringHammer1Block_ROM_END;
extern Addr entity_model_ShatteringHammer1Block_ROM_START;
extern Addr entity_model_ShatteringHammer2Block_ROM_END;
extern Addr entity_model_ShatteringHammer2Block_ROM_START;
extern Addr entity_model_ShatteringHammer3Block_ROM_END;
extern Addr entity_model_ShatteringHammer3Block_ROM_START;
#endif

extern Mtx Entity_ShatteringHammer1Block_FragmentsMatrices[];
extern Gfx* Entity_ShatteringHammer1Block_FragmentsRender[];
extern Mtx Entity_ShatteringHammer2Block_FragmentsMatrices[];
extern Gfx* Entity_ShatteringHammer2Block_FragmentsRender[];
extern Mtx Entity_ShatteringHammer3Block_FragmentsMatrices[];
extern Gfx* Entity_ShatteringHammer3Block_FragmentsRender[];
extern Mtx Entity_ShatteringBrickBlock_FragmentsMatrices[];
extern Gfx* Entity_ShatteringBrickBlock_FragmentsRender[];

extern Gfx Entity_RenderNone[];
extern EntityScript Entity_ShatteringBlock_Script;

void entity_shattering_init_pieces(Entity* entity, Gfx** dlists, Mtx* matrices);
void entity_shattering_block_init(Entity* entity);

EntityModelScript Entity_ShatteringBlock_RenderScript = STANDARD_ENTITY_MODEL_SCRIPT(Entity_RenderNone, RENDER_MODE_SURFACE_XLU_LAYER1);

ENTITY_IMPLEMENTATION(ShatteringHammer1Block) = {
    .flags = 0,
    .typeDataSize = sizeof(ShatteringBlockData),
    .renderCommandList = Entity_ShatteringBlock_RenderScript,
    .modelAnimationNodes = nullptr,
    .fpInit = entity_shattering_block_init,
    .updateEntityScript = Entity_ShatteringBlock_Script,
    .fpHandleCollision = nullptr,
    { .dma = ENTITY_ROM(ShatteringHammer1Block) },
    .entityType = ENTITY_TYPE_HAMMER1_BLOCK,
    .aabbSize = {16, 16, 16}
};

ENTITY_IMPLEMENTATION(ShatteringHammer2Block) = {
    .flags = 0,
    .typeDataSize = sizeof(ShatteringBlockData),
    .renderCommandList = Entity_ShatteringBlock_RenderScript,
    .modelAnimationNodes = nullptr,
    .fpInit = entity_shattering_block_init,
    .updateEntityScript = Entity_ShatteringBlock_Script,
    .fpHandleCollision = nullptr,
    { .dma = ENTITY_ROM(ShatteringHammer2Block) },
    .entityType = ENTITY_TYPE_HAMMER2_BLOCK,
    .aabbSize = {16, 16, 16}
};

ENTITY_IMPLEMENTATION(ShatteringHammer3Block) = {
    .flags = 0,
    .typeDataSize = sizeof(ShatteringBlockData),
    .renderCommandList = Entity_ShatteringBlock_RenderScript,
    .modelAnimationNodes = nullptr,
    .fpInit = entity_shattering_block_init,
    .updateEntityScript = Entity_ShatteringBlock_Script,
    .fpHandleCollision = nullptr,
    { .dma = ENTITY_ROM(ShatteringHammer3Block) },
    .entityType = ENTITY_TYPE_HAMMER3_BLOCK,
    .aabbSize = {16, 16, 16}
};

ENTITY_IMPLEMENTATION(ShatteringHammer1BlockTiny) = {
    .flags = 0,
    .typeDataSize = sizeof(ShatteringBlockData),
    .renderCommandList = Entity_ShatteringBlock_RenderScript,
    .modelAnimationNodes = nullptr,
    .fpInit = entity_shattering_block_init,
    .updateEntityScript = Entity_ShatteringBlock_Script,
    .fpHandleCollision = nullptr,
    { .dma = ENTITY_ROM(ShatteringHammer1Block) },
    .entityType = ENTITY_TYPE_HAMMER1_BLOCK_TINY,
    .aabbSize = {8, 8, 8}
};

ENTITY_IMPLEMENTATION(ShatteringHammer2BlockTiny) = {
    .flags = 0,
    .typeDataSize = sizeof(ShatteringBlockData),
    .renderCommandList = Entity_ShatteringBlock_RenderScript,
    .modelAnimationNodes = nullptr,
    .fpInit = entity_shattering_block_init,
    .updateEntityScript = Entity_ShatteringBlock_Script,
    .fpHandleCollision = nullptr,
    { .dma = ENTITY_ROM(ShatteringHammer2Block) },
    .entityType = ENTITY_TYPE_HAMMER2_BLOCK_TINY,
    .aabbSize = {8, 8, 8}
};

ENTITY_IMPLEMENTATION(ShatteringHammer3BlockTiny) = {
    .flags = 0,
    .typeDataSize = sizeof(ShatteringBlockData),
    .renderCommandList = Entity_ShatteringBlock_RenderScript,
    .modelAnimationNodes = nullptr,
    .fpInit = entity_shattering_block_init,
    .updateEntityScript = Entity_ShatteringBlock_Script,
    .fpHandleCollision = nullptr,
    { .dma = ENTITY_ROM(ShatteringHammer3Block) },
    .entityType = ENTITY_TYPE_HAMMER3_BLOCK_TINY,
    .aabbSize = {8, 8, 8}
};

ENTITY_IMPLEMENTATION(ShatteringBrickBlock) = {
    .flags = 0,
    .typeDataSize = sizeof(ShatteringBlockData),
    .renderCommandList = Entity_ShatteringBlock_RenderScript,
    .modelAnimationNodes = nullptr,
    .fpInit = entity_shattering_block_init,
    .updateEntityScript = Entity_ShatteringBlock_Script,
    .fpHandleCollision = nullptr,
    { .dma = ENTITY_ROM(ShatteringBrickBlock) },
    .entityType = ENTITY_TYPE_BRICK_BLOCK,
    .aabbSize = {8, 8, 8}
};

void entity_shattering_block_init(Entity* entity) {
    u32 type;
    Mtx* fragmentMatrices = nullptr;
    Gfx** fragmentDisplayLists = nullptr;

    entity->dataBuf.shatteringBlock->originalPosY = entity->pos.y;
    type = get_entity_type(entity->listIndex);

    if (type == ENTITY_TYPE_HAMMER1_BLOCK_TINY ||
        type == ENTITY_TYPE_HAMMER2_BLOCK_TINY ||
        type == ENTITY_TYPE_HAMMER3_BLOCK_TINY)
    {
        entity->scale.x = 0.5f;
        entity->scale.y = 0.5f;
        entity->scale.z = 0.5f;
    }

    switch (type) {
        case ENTITY_TYPE_HAMMER1_BLOCK:
        case ENTITY_TYPE_HAMMER1_BLOCK_TINY:
            fragmentDisplayLists = Entity_ShatteringHammer1Block_FragmentsRender;
            fragmentMatrices = Entity_ShatteringHammer1Block_FragmentsMatrices;
            break;
        case ENTITY_TYPE_HAMMER2_BLOCK:
        case ENTITY_TYPE_HAMMER2_BLOCK_TINY:
            fragmentDisplayLists = Entity_ShatteringHammer2Block_FragmentsRender;
            fragmentMatrices = Entity_ShatteringHammer2Block_FragmentsMatrices;
            break;
        case ENTITY_TYPE_HAMMER3_BLOCK:
        case ENTITY_TYPE_HAMMER3_BLOCK_TINY:
            fragmentDisplayLists = Entity_ShatteringHammer3Block_FragmentsRender;
            fragmentMatrices = Entity_ShatteringHammer3Block_FragmentsMatrices;
            break;
        case ENTITY_TYPE_BRICK_BLOCK:
            sfx_play_sound_at_position(SOUND_BLOCK_SHATTER, SOUND_SPACE_DEFAULT, entity->pos.x, entity->pos.y, entity->pos.z);
            fragmentDisplayLists = Entity_ShatteringBrickBlock_FragmentsRender;
            fragmentMatrices = Entity_ShatteringBrickBlock_FragmentsMatrices;
            break;
        case ENTITY_TYPE_MULTI_COIN_BRICK:
        case ENTITY_TYPE_YELLOW_BLOCK:
        case ENTITY_TYPE_SINGLE_TRIGGER_BLOCK:
        case ENTITY_TYPE_HIDDEN_YELLOW_BLOCK:
        case ENTITY_TYPE_HIDDEN_RED_BLOCK:
        case ENTITY_TYPE_INACTIVE_BLOCK:
            break;
    }

    if (fragmentMatrices == nullptr) {
        return;
    }

    entity_shattering_init_pieces(entity, fragmentDisplayLists, fragmentMatrices);
}
