#include "effects.h"

#define MULTICOIN_BLOCK_MAX_COINS 10

void entity_base_block_update_slow_sinking(Entity* entity) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    BlockData* data = entity->dataBuf.block;
    f32 deltaY;

    if (entity->alpha < 255) {
        entity->flags &= ~ENTITY_FLAG_200000;
        return;
    }

    if (!(data->sinkingTimer & 0x8000)) {
        if (data->sinkingTimer < 150) {
            data->sinkingTimer++;
            return;
        }

        if (entity->pos.y < data->initialY - 25.0f) {
            deltaY = (entity->pos.y - data->initialY + 50.0f) * 0.125f;
        } else {
            deltaY = (data->initialY - entity->pos.y) * 0.125f;
        }

        if (deltaY > 1.2) {
            deltaY = 1.2f;
        }
        if (deltaY < 0.3) {
            deltaY = 0.3f;
        }

        entity->pos.y += deltaY;

        if (data->initialY < entity->pos.y) {
            entity->pos.y = data->initialY;
            data->sinkingTimer = -1;
            entity->flags &= ~ENTITY_FLAG_200000;
        }
    } else {
        if (entity->collisionFlags & ENTITY_COLLISION_PLAYER_TOUCH_CEILING) {
            if (!(playerStatus->flags & PS_FLAG_JUMPING)) {
                Shadow* shadow = get_shadow_by_index(entity->shadowIndex);
                if (shadow != nullptr) {
                    f32 temp2 = entity->pos.y - shadow->pos.y;

                    if (entity->pos.y - temp2 <= playerStatus->colliderHeight + 1) {
                        entity->pos.y = playerStatus->colliderHeight + 1;
                        data->sinkingTimer = 1;
                    }
                }
            } else {
                data->sinkingTimer = 1;
                return;
            }
        } else {
            Shadow* shadow = get_shadow_by_index(entity->shadowIndex);
            if (shadow != nullptr && entity->pos.y <= shadow->pos.y) {
                entity->pos.y = shadow->pos.y;
                data->sinkingTimer = 1;
            }
        }

        if (entity->collisionFlags & ENTITY_COLLISION_PLAYER_TOUCH_CEILING) {
            data->sinkingTimer = 1;
            return;
        }

        if (entity->pos.y < data->initialY - 25.0f) {
            deltaY = (entity->pos.y - data->initialY + 50.0f) * 0.125f;
        } else {
            deltaY = (data->initialY - entity->pos.y) * 0.125f;
        }

        if (deltaY > 1.2) {
            deltaY = 1.2f;
        }
        if (deltaY < 0.3) {
            deltaY = 0.3f;
        }

        entity->pos.y -= deltaY;

        if (entity->pos.y < data->initialY - 50.0f) {
            entity->pos.y = data->initialY - 50.0f;
            data->sinkingTimer = 1;
        }
    }
}

s32 entity_base_block_idle(Entity* entity) {
    BlockData* data = entity->dataBuf.block;
    s32 ret = 0;

    if (is_block_on_ground(entity) != 0 && (entity->flags & ENTITY_FLAG_200000)) {
        ret = 1;
        entity_base_block_update_slow_sinking(entity);
        if (data->item != -1) {
            ItemEntity* itemEntity = get_item_entity(data->item);
            itemEntity->pos.y = entity->pos.y + 4.0f;
        }
    }

    return ret;
}

void entity_base_block_init(Entity* entity) {
    BlockData* data = entity->dataBuf.block;

    data->item = -1;
    data->initialY = entity->pos.y;
    data->sinkingTimer = -1;
    entity->flags &= ~ENTITY_FLAG_200000;
}

void entity_MulticoinBlock_update_timer(Entity* entity) {
    BlockData* data = entity->dataBuf.block;

    if (entity->type == ENTITY_TYPE_MULTI_COIN_BRICK && data->coinsLeft != MULTICOIN_BLOCK_MAX_COINS) {
        data->timeLeft--;
        if (data->timeLeft < 0) {
            data->timeLeft = 0;
            data->coinsLeft = 1;
        }
    }
}

void entity_inactive_block_hit_init(Entity* entity) {
    entity->dataBuf.block->recoilInterpPhase = 90.0f;
}

void entity_inactive_block_hit_anim(Entity* entity) {
    BlockData* data = entity->dataBuf.block;
    f64 currentY;

    entity_MulticoinBlock_update_timer(entity);
    currentY = entity->pos.y;
    entity->pos.y = currentY + ((f64)sin_rad(DEG_TO_RAD(data->recoilInterpPhase)) * 2);
    data->recoilInterpPhase += 60.0f;
    if (data->recoilInterpPhase > 450.0f) {
        data->recoilInterpPhase = clamp_angle(data->recoilInterpPhase);
        exec_entity_commandlist(entity);
    }
}

void entity_inactive_block_recoil_anim(Entity* entity) {
    BlockData* data = entity->dataBuf.block;
    f64 currentY;

    entity_MulticoinBlock_update_timer(entity);
    currentY = entity->pos.y;
    entity->pos.y = currentY + ((f64)sin_rad(DEG_TO_RAD(data->recoilInterpPhase)));
    data->recoilInterpPhase += 60.0f;
    if (data->recoilInterpPhase >= 360.0f) {
        data->recoilInterpPhase = 0.0f;
        entity->pos.y = data->initialY;
        exec_entity_commandlist(entity);
    }
}

void entity_block_hit_init_scale(Entity* entity) {
    s32 type = get_entity_type(entity->listIndex);

    if (type == ENTITY_TYPE_HAMMER1_BLOCK_TINY ||
        type == ENTITY_TYPE_HAMMER2_BLOCK_TINY ||
        type == ENTITY_TYPE_HAMMER3_BLOCK_TINY)
    {
        entity->scale.y = 0.23f;
        entity->scale.x = 1.04f;
        entity->scale.z = 1.04f;
    } else {
        entity->scale.y = 0.46f;
        entity->scale.x = 2.08f;
        entity->scale.z = 2.08f;
    }
    entity->pos.y += 18.0f;
}

void entity_block_hit_animate_scale(Entity* entity) {
    s32 type = get_entity_type(entity->listIndex);

    if (type == ENTITY_TYPE_HAMMER1_BLOCK_TINY ||
        type == ENTITY_TYPE_HAMMER2_BLOCK_TINY ||
        type == ENTITY_TYPE_HAMMER3_BLOCK_TINY)
    {
        entity->scale.x -= 0.09;
        entity->scale.z -= 0.09;
        entity->scale.y += 0.045;
    } else {
        entity->scale.x -= 0.18;
        entity->scale.z -= 0.18;
        entity->scale.y += 0.09;
    }
    entity->pos.y -= 3.0f;
    entity_base_block_idle(entity);
}

void entity_breakable_block_create_shattering_entity(Entity* entity) {
    EntityBlueprint* bp = nullptr;

    switch (get_entity_type(entity->listIndex)) {
        case ENTITY_TYPE_HAMMER1_BLOCK:
            bp = &Entity_ShatteringHammer1Block;
            break;
        case ENTITY_TYPE_HAMMER1_BLOCK_TINY:
            bp = &Entity_ShatteringHammer1BlockTiny;
            break;
        case ENTITY_TYPE_HAMMER2_BLOCK:
            bp = &Entity_ShatteringHammer2Block;
            break;
        case ENTITY_TYPE_HAMMER2_BLOCK_TINY:
            bp = &Entity_ShatteringHammer2BlockTiny;
            break;
        case ENTITY_TYPE_HAMMER3_BLOCK:
            bp = &Entity_ShatteringHammer3Block;
            break;
        case ENTITY_TYPE_HAMMER3_BLOCK_TINY:
            bp = &Entity_ShatteringHammer3BlockTiny;
            break;
        case ENTITY_TYPE_BRICK_BLOCK:
            bp = &Entity_ShatteringBrickBlock;
            break;
    }

    if (bp != nullptr) {
        create_entity(bp, (s32)entity->pos.x, (s32)entity->pos.y, (s32)entity->pos.z, 0, MAKE_ENTITY_END);
    }
}

EntityScript Entity_BreakingBlock_Script = {
    es_RestartBoundScript
    es_SetFlags(ENTITY_FLAG_HIDDEN)
    es_SetFlags(ENTITY_FLAG_DISABLE_COLLISION)
    es_Call(entity_breakable_block_create_shattering_entity)
    es_SetCallback(nullptr, 1)
    es_SetFlags(ENTITY_FLAG_PENDING_INSTANCE_DELETE)
    es_End
};

EntityScript Entity_InertBlock_Script = {
    es_SetCallback(entity_base_block_idle, 0)
    es_PlaySound(SOUND_HIT_BLOCK)
    es_Call(entity_inactive_block_hit_init)
    es_Call(entity_start_script)
    es_SetCallback(entity_inactive_block_hit_anim, 0)
    es_SetCallback(entity_inactive_block_recoil_anim, 0)
    es_Restart
    es_End
};

s32 entity_block_handle_collision(Entity* entity) {
    s32 breakBlock;
    PlayerStatus* playerStatus = &gPlayerStatus;

    if (entity->alpha == 0 && (entity->collisionFlags & ENTITY_COLLISION_PLAYER_TOUCH_FLOOR)) {
        return false;
    }

    if (entity->collisionFlags & ENTITY_COLLISION_PLAYER_TOUCH_CEILING) {
        s32 type = get_entity_type(entity->listIndex);
        switch (type) {
            case ENTITY_TYPE_PUSH_BLOCK:
            case ENTITY_TYPE_HAMMER1_BLOCK:
            case ENTITY_TYPE_HAMMER2_BLOCK:
            case ENTITY_TYPE_HAMMER3_BLOCK:
            case ENTITY_TYPE_HAMMER1_BLOCK_TINY:
            case ENTITY_TYPE_HAMMER2_BLOCK_TINY:
            case ENTITY_TYPE_HAMMER3_BLOCK_TINY:
                return false;
        }

        if (playerStatus->flags & PS_FLAG_JUMPING) {
            exec_entity_commandlist(entity);
        }
        return true;
    }

    if (entity->collisionFlags & ENTITY_COLLISION_PARTNER) {
        if (gPlayerData.curPartner == PARTNER_BOMBETTE) {
            switch (get_entity_type(entity->listIndex)) {
                case ENTITY_TYPE_HAMMER1_BLOCK:
                case ENTITY_TYPE_HAMMER1_BLOCK_TINY:
                    set_entity_commandlist(entity, Entity_BreakingBlock_Script);
                    sfx_play_sound_at_position(SOUND_SMASH_HAMER_BLOCK_1, SOUND_SPACE_DEFAULT,
                                               entity->pos.x, entity->pos.y, entity->pos.z);
                    return true;
            }
        }
        exec_entity_commandlist(entity);
        return true;
    }

    breakBlock = false;
    if (entity->collisionFlags & ENTITY_COLLISION_PLAYER_TOUCH_FLOOR) {
        if (playerStatus->actionState == ACTION_STATE_SPIN_JUMP ||
            playerStatus->actionState == ACTION_STATE_TORNADO_JUMP)
        {
            return false;
        }

        if (playerStatus->actionState == ACTION_STATE_SPIN_POUND ||
            playerStatus->actionState == ACTION_STATE_TORNADO_POUND)
        {
            breakBlock = true;
        } else {
            return true;
        }
    } else {
        if (!(entity->collisionFlags & ENTITY_COLLISION_PLAYER_HAMMER) ||
            !(playerStatus->flags & PS_FLAG_HAMMER_CHECK))
        {
            return true;
        }
    }

    switch (get_entity_type(entity->listIndex)) {
        case ENTITY_TYPE_BRICK_BLOCK:
        case ENTITY_TYPE_MULTI_COIN_BRICK:
        case ENTITY_TYPE_YELLOW_BLOCK:
        case ENTITY_TYPE_SINGLE_TRIGGER_BLOCK:
        case ENTITY_TYPE_HIDDEN_YELLOW_BLOCK:
        case ENTITY_TYPE_HIDDEN_RED_BLOCK:
        case ENTITY_TYPE_RED_BLOCK:
            exec_entity_commandlist(entity);
            break;
        case ENTITY_TYPE_HAMMER1_BLOCK:
        case ENTITY_TYPE_HAMMER1_BLOCK_TINY:
            if (breakBlock) {
                if (gPlayerData.bootsLevel < GEAR_RANK_SUPER) {
                    breakBlock = false;
                }
            } else if (gPlayerData.hammerLevel > GEAR_RANK_NONE) {
                breakBlock = true;
            }
            if (!breakBlock) {
                return true;
            }
            set_entity_commandlist(entity, Entity_BreakingBlock_Script);
            sfx_play_sound_at_position(SOUND_SMASH_HAMER_BLOCK_1, SOUND_SPACE_DEFAULT,
                                       entity->pos.x, entity->pos.y, entity->pos.z);
            break;
        case ENTITY_TYPE_HAMMER2_BLOCK:
        case ENTITY_TYPE_HAMMER2_BLOCK_TINY:
            if (breakBlock) {
                if (gPlayerData.bootsLevel < GEAR_RANK_ULTRA) {
                    breakBlock = false;
                }
            } else if (gPlayerData.hammerLevel > GEAR_RANK_NORMAL) {
                breakBlock = true;
            }
            if (!breakBlock) {
                return true;
            }
            set_entity_commandlist(entity, Entity_BreakingBlock_Script);
            sfx_play_sound_at_position(SOUND_SMASH_HAMER_BLOCK_2, SOUND_SPACE_DEFAULT,
                                       entity->pos.x, entity->pos.y, entity->pos.z);
            break;
        case ENTITY_TYPE_HAMMER3_BLOCK:
        case ENTITY_TYPE_HAMMER3_BLOCK_TINY:
            if (gPlayerData.hammerLevel < GEAR_RANK_ULTRA) {
                return true;
            }
            set_entity_commandlist(entity, Entity_BreakingBlock_Script);
            sfx_play_sound_at_position(SOUND_SMASH_HAMER_BLOCK_3, SOUND_SPACE_DEFAULT,
                                       entity->pos.x, entity->pos.y, entity->pos.z);
            break;
        case ENTITY_TYPE_MULTI_TRIGGER_BLOCK:
        case ENTITY_TYPE_HEALING_BLOCK:
        case ENTITY_TYPE_1C:
        case ENTITY_TYPE_1D:
        case ENTITY_TYPE_1E:
        case ENTITY_TYPE_HEALING_BLOCK_FRAME:
            entity_start_script(entity);
            exec_entity_commandlist(entity);
            break;
        case ENTITY_TYPE_PUSH_BLOCK:
            entity_start_script(entity);
            break;
        case ENTITY_TYPE_INACTIVE_BLOCK:
            break;
    }

    return true;
}

void entity_upgrade_block_hide_content(s32 entityIndex) {
    Entity* entity = get_entity_by_index(entityIndex);
    BlockData* data = entity->dataBuf.block;

    if (data->childEntityIndex >= 0) {
        Entity* childEntity = get_entity_by_index(data->childEntityIndex);
        SuperBlockContentData* childEntityData = childEntity->dataBuf.superBlockContent;

        childEntityData->isHidden = true;
    }
}

#undef MULTICOIN_BLOCK_MAX_COINS
