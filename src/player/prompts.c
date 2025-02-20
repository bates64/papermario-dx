#include <ultra64.h>
#include "enums.h"
#include "ld_addrs.h"

void check_for_ispy(void) {
    PlayerStatus* playerStatus = &gPlayerStatus;

    if (gCurrentHiddenPanels.activateISpy && ISpyNotificationCallback == NULL) {
        if (!(playerStatus->animFlags &
            (PA_FLAG_SPEECH_PROMPT_AVAILABLE | PA_FLAG_INTERACT_PROMPT_AVAILABLE))) {
            DMA_COPY_SEGMENT(i_spy);
            ISpyNotificationCallback = ispy_notification_setup;
        }
    }

    if (ISpyNotificationCallback != NULL) {
        ISpyNotificationCallback();
    }
}

void render_ispy_icon(void) {
    if ((gPlayerStatusPtr->animFlags & PA_FLAG_ISPY_VISIBLE) && (ISpyNotificationCallback != NULL)) {
        appendGfx_ispy_icon();
    }
}

void clear_ispy_icon(void) {
    ISpyNotificationCallback = NULL;
    gPlayerStatusPtr->animFlags &= ~PA_FLAG_ISPY_VISIBLE;
}

/// unavoidable use of hardcoded map and area IDs
void check_for_pulse_stone(void) {
    s32 dx, dy;

    if (PulseStoneNotificationCallback == NULL) {
        if (gPlayerStatus.animFlags & PA_FLAG_ISPY_VISIBLE) {
            return;
        }

        if (gGameStatusPtr->areaID != AREA_SBK || gGameStatusPtr->context != CONTEXT_WORLD) {
            return;
        }

        dx = abs((gGameStatusPtr->mapID % 7) - 2);
        dy = gGameStatusPtr->mapID / 7;
        if ((dx + dy) > 5) {
            return;
        }

        if (!(gPlayerStatus.animFlags & (PA_FLAG_USING_PULSE_STONE | PA_FLAG_PULSE_STONE_VISIBLE))) {
            return;
        }

        if (gPlayerStatus.flags & PS_FLAG_PAUSED || gPlayerStatus.inputDisabledCount != 0) {
            return;
        }

        if (!(gPlayerStatus.animFlags & (PA_FLAG_SPEECH_PROMPT_AVAILABLE | PA_FLAG_INTERACT_PROMPT_AVAILABLE))) {
            DMA_COPY_SEGMENT(pulse_stone);
            PulseStoneNotificationCallback = pulse_stone_notification_setup;
        }
    }

    if (PulseStoneNotificationCallback != NULL) {
        PulseStoneNotificationCallback();
    }
}

void render_pulse_stone_icon(void) {
    if ((gPlayerStatusPtr->animFlags & PA_FLAG_PULSE_STONE_VISIBLE) && (PulseStoneNotificationCallback != NULL)) {
        appendGfx_pulse_stone_icon();
    }
}

void clear_pulse_stone_icon(void) {
    PulseStoneNotificationCallback = NULL;
    gPlayerStatusPtr->animFlags &= ~PA_FLAG_PULSE_STONE_VISIBLE;
}

s32 has_valid_conversation_npc(void) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    Npc* npc = playerStatus->encounteredNPC;
    s32 ret = FALSE;
    s32 cond;

    if (npc != NULL && !(npc->flags & NPC_FLAG_USE_INSPECT_ICON)) {
        cond = !(playerStatus->flags & PS_FLAG_INPUT_DISABLED) && (playerStatus->flags & PS_FLAG_HAS_CONVERSATION_NPC);
        ret = cond;
    }
    return ret;
}

void check_for_conversation_prompt(void) {
    if (gPlayerStatus.animFlags & PA_FLAG_ISPY_VISIBLE || InteractNotificationCallback || PulseStoneNotificationCallback != NULL) {
        return;
    }

    if (TalkNotificationCallback == NULL) {
        if (gPlayerStatus.inputDisabledCount || gPlayerStatus.flags & PS_FLAG_PAUSED) {
            return;
        }

        if (has_valid_conversation_npc()) {
            TalkNotificationCallback = NULL;
            DMA_COPY_SEGMENT(speech_bubble);
            TalkNotificationCallback = interact_speech_setup;
        } else {
            TalkNotificationCallback = NULL;
            return;
        }
    }

    if (TalkNotificationCallback != NULL) {
        TalkNotificationCallback();
    }
}

void render_conversation_prompt(void) {
    if ((gPlayerStatusPtr->animFlags & PA_FLAG_SPEECH_PROMPT_AVAILABLE) && (TalkNotificationCallback != NULL)) {
        appendGfx_speech_bubble();
    }
}

void clear_conversation_prompt(void) {
    TalkNotificationCallback = NULL;
    gPlayerStatusPtr->animFlags &= ~PA_FLAG_SPEECH_PROMPT_AVAILABLE;
}

s32 func_800E06D8(void) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    s32 currentWall;

    if (playerStatus->timeInAir != 0 || playerStatus->inputDisabledCount != 0) {
        return FALSE;
    }
    if (gCollisionStatus.curWall == NO_COLLIDER) {
        return FALSE;
    }
    if (playerStatus->flags & PS_FLAG_HAS_CONVERSATION_NPC
        && !(playerStatus->flags & PS_FLAG_INPUT_DISABLED)
        && playerStatus->encounteredNPC != NULL
        && playerStatus->encounteredNPC->flags & NPC_FLAG_USE_INSPECT_ICON
    ) {
        playerStatus->interactingWithID = NO_COLLIDER;
        return TRUE;
    }

    currentWall = gCollisionStatus.curWall;
    if (!(currentWall & COLLISION_WITH_ENTITY_BIT)) {
        if (!should_collider_allow_interact(currentWall)) {
            return FALSE;
        }
    } else if (!phys_can_player_interact()) {
        playerStatus->interactingWithID = NO_COLLIDER;
        return FALSE;
    } else if (get_entity_type(currentWall) == ENTITY_TYPE_PUSH_BLOCK) {
        return FALSE;
    }

    if (playerStatus->interactingWithID == currentWall) {
        if (playerStatus->flags & PS_FLAG_INTERACTED) {
            return FALSE;
        }
    } else {
        playerStatus->flags &= ~PS_FLAG_INTERACTED;
    }
    playerStatus->interactingWithID = NO_COLLIDER;

    return TRUE;
}

void check_for_interactables(void) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    Npc* npc = gPlayerStatus.encounteredNPC;
    b32 collidingWithEntity = FALSE;

    if ((playerStatus->animFlags & PA_FLAG_ISPY_VISIBLE) || TalkNotificationCallback || PulseStoneNotificationCallback != NULL) {
        return;
    }

    if (InteractNotificationCallback == NULL) {
        s16 curInteraction = gCollisionStatus.curWall;

        if (playerStatus->inputDisabledCount != 0) {
            if (gPlayerStatus.interactingWithID != curInteraction) {
                gPlayerStatus.interactingWithID = curInteraction;
            }
            return;
        }

        if (playerStatus->timeInAir != 0) {
            return;
        }

        if (curInteraction == NO_COLLIDER) {
            s16 floor = gCollisionStatus.curFloor;

            if ((floor > NO_COLLIDER) && (floor & COLLISION_WITH_ENTITY_BIT)) {
                collidingWithEntity = TRUE;
                curInteraction = floor;
                switch (get_entity_type(floor)) {
                    case ENTITY_TYPE_PADLOCK:
                    case ENTITY_TYPE_PADLOCK_RED_FRAME:
                    case ENTITY_TYPE_PADLOCK_RED_FACE:
                    case ENTITY_TYPE_PADLOCK_BLUE_FACE:
                    case ENTITY_TYPE_PUSH_BLOCK:
                    case ENTITY_TYPE_CHEST:
                    case ENTITY_TYPE_SIGNPOST:
                        curInteraction = NO_COLLIDER;
                        break;
                }
            } else if (
                (!(playerStatus->flags & PS_FLAG_INPUT_DISABLED))
                && (playerStatus->flags & PS_FLAG_HAS_CONVERSATION_NPC)
                && (npc != NULL)
                && (npc->flags & NPC_FLAG_USE_INSPECT_ICON)
            ) {
                curInteraction = npc->npcID;
                curInteraction |= COLLISION_WITH_NPC_BIT;
                if (playerStatus->interactingWithID == curInteraction) {
                    return;
                }
            } else {
                playerStatus->interactingWithID = NO_COLLIDER;
                playerStatus->flags &= ~PS_FLAG_INTERACTED;
                return;
            }
        } else {
            if (curInteraction & COLLISION_WITH_ENTITY_BIT) {
                collidingWithEntity = TRUE;
                if (!phys_can_player_interact()) {
                    playerStatus->interactingWithID = NO_COLLIDER;
                    playerStatus->flags &= ~PS_FLAG_INTERACTED;
                    return;
                }
            } else {
                if (!(curInteraction & COLLISION_WITH_NPC_BIT)) {
                    if (!should_collider_allow_interact(curInteraction)) {
                        playerStatus->interactingWithID = NO_COLLIDER;
                        playerStatus->flags &= ~PS_FLAG_INTERACTED;
                        return;
                    }
                }
            }
        }
        if (playerStatus->interactingWithID == curInteraction) {
            if ((playerStatus->flags & PS_FLAG_INTERACTED)) {
                return;
            }
        } else {
            playerStatus->flags &= ~PS_FLAG_INTERACTED;
        }

        playerStatus->interactingWithID = curInteraction;
        if (!collidingWithEntity || (curInteraction > NO_COLLIDER && get_entity_by_index(curInteraction)->flags & ENTITY_FLAG_SHOWS_INSPECT_PROMPT)) {
            if (playerStatus->actionState == ACTION_STATE_IDLE || playerStatus->actionState == ACTION_STATE_WALK || playerStatus->actionState == ACTION_STATE_RUN) {
                playerStatus->animFlags |= PA_FLAG_INTERACT_PROMPT_AVAILABLE;
                func_800EF3D4(2);
            }
        }
    }

    if (!(playerStatus->animFlags & PA_FLAG_INTERACT_PROMPT_AVAILABLE)) {
        func_800EF3D4(0);
        partner_reset_tether_distance();
        return;
    }

    if (InteractNotificationCallback == NULL) {
        DMA_COPY_SEGMENT(inspect_icon);
        InteractNotificationCallback = interact_inspect_setup;

    }

    if (InteractNotificationCallback != NULL) {
        InteractNotificationCallback();
    }
}

void appendGfx_interact_prompt(void);

void render_interact_prompt(void) {
    if ((gPlayerStatusPtr->animFlags & PA_FLAG_INTERACT_PROMPT_AVAILABLE) && (InteractNotificationCallback != NULL)) {
        appendGfx_interact_prompt();
    }
}

void clear_interact_prompt(void) {
    InteractNotificationCallback = NULL;
    gPlayerStatusPtr->animFlags &= ~PA_FLAG_INTERACT_PROMPT_AVAILABLE;
}

void player_render_interact_prompts(void) {
    render_conversation_prompt();
    render_interact_prompt();
    render_pulse_stone_icon();
    render_ispy_icon();
}
