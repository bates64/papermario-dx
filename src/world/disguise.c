#include "disguise.h"
#include "sprite/npc/WorldClubba.h"
#include "sprite/npc/WorldKoopatrol.h"
#include "sprite/npc/HammerBros.h"
#include "player/physics.h"

AnimID ClubbaDisguiseExtraAnims[] = {
    ANIM_WorldClubba_Anim00,
    ANIM_WorldClubba_Anim02,
    ANIM_WorldClubba_Anim03,
    ANIM_WorldClubba_Anim04,
    ANIM_WorldClubba_Anim05,
    ANIM_WorldClubba_Anim08,
    ANIM_WorldClubba_Anim07,
    ANIM_WorldClubba_Anim13,
    ANIM_WorldClubba_Anim14,
    ANIM_LIST_END
};

AnimID HammerBroDisguiseExtraAnims[] = {
    ANIM_HammerBros_Anim00,
    ANIM_HammerBros_Anim02,
    ANIM_HammerBros_Anim03,
    ANIM_HammerBros_Anim04,
    ANIM_HammerBros_Anim06,
    ANIM_HammerBros_Anim07,
    ANIM_HammerBros_Anim09,
    ANIM_HammerBros_Anim0A,
    ANIM_HammerBros_Anim0B,
    ANIM_HammerBros_Anim1A,
    ANIM_LIST_END
};

AnimID KoopatrolDisguiseExtraAnims[] = {
    ANIM_WorldKoopatrol_Anim00,
    ANIM_WorldKoopatrol_Anim01,
    ANIM_WorldKoopatrol_Anim02,
    ANIM_WorldKoopatrol_Anim04,
    ANIM_WorldKoopatrol_Anim05,
    ANIM_WorldKoopatrol_Anim06,
    ANIM_WorldKoopatrol_Anim07,
    ANIM_WorldKoopatrol_Anim08,
    ANIM_WorldKoopatrol_Anim09,
    ANIM_WorldKoopatrol_Anim12,
    ANIM_WorldKoopatrol_Anim14,
    ANIM_WorldKoopatrol_Anim1B,
    ANIM_LIST_END
};

DisguiseAnims BasicPeachDisguiseAnims[] = {
    [PEACH_DISGUISE_NONE] = {
        ANIM_WorldKoopatrol_Anim01,
        ANIM_WorldKoopatrol_Anim04,
        ANIM_WorldKoopatrol_Anim06,
        ANIM_WorldKoopatrol_Anim08,
        ANIM_WorldKoopatrol_Anim00,
        ANIM_WorldKoopatrol_Anim1B
    },
    [PEACH_DISGUISE_KOOPATROL] = {
        ANIM_WorldKoopatrol_Anim01,
        ANIM_WorldKoopatrol_Anim04,
        ANIM_WorldKoopatrol_Anim06,
        ANIM_WorldKoopatrol_Anim08,
        ANIM_WorldKoopatrol_Anim00,
        ANIM_WorldKoopatrol_Anim1B
    },
    [PEACH_DISGUISE_HAMMER_BROS] = {
        ANIM_HammerBros_Anim03,
        ANIM_HammerBros_Anim06,
        ANIM_HammerBros_Anim09,
        ANIM_HammerBros_Anim0B,
        ANIM_HammerBros_Anim00,
        ANIM_HammerBros_Anim1A
    },
    [PEACH_DISGUISE_CLUBBA] = {
        ANIM_WorldClubba_Anim02,
        ANIM_WorldClubba_Anim03,
        ANIM_WorldClubba_Anim04,
        ANIM_WorldClubba_Anim05,
        ANIM_WorldClubba_Anim00,
        ANIM_WorldClubba_Anim14
    },
};

AnimID* PeachDisguiseExtraAnims[] = {
    [PEACH_DISGUISE_NONE] = KoopatrolDisguiseExtraAnims,
    [PEACH_DISGUISE_KOOPATROL] = KoopatrolDisguiseExtraAnims,
    [PEACH_DISGUISE_HAMMER_BROS] = HammerBroDisguiseExtraAnims,
    [PEACH_DISGUISE_CLUBBA] = ClubbaDisguiseExtraAnims
};

s32 PeachDisguiseReapplyDelay;

void peach_set_disguise_anim(AnimID anim) {
    s32 listIndex = PeachDisguiseNpcIndex;

    if (listIndex >= 0) {
        get_npc_by_index(listIndex)->curAnim = anim;
    }
}

void peach_force_disguise_action(s32 useParasol) {
    PlayerStatus* playerStatus = &gPlayerStatus;

    if (useParasol) {
        set_action_state(ACTION_STATE_USE_SNEAKY_PARASOL);
    } else {
        playerStatus->animFlags &= ~PA_FLAG_INVISIBLE;
        gGameStatusPtr->peachFlags &= ~PEACH_FLAG_DISGUISED;
        playerStatus->peachDisguise = PEACH_DISGUISE_NONE;
        free_npc_by_index(PeachDisguiseNpcIndex);
        set_action_state(ACTION_STATE_IDLE);
        playerStatus->colliderHeight = 55;
        playerStatus->colliderDiameter = 38;
    }
}

void peach_check_for_parasol_input(void) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    s32 actionState = playerStatus->actionState;
    Npc* disguiseNpc;

    if (actionState == ACTION_STATE_IDLE || actionState == ACTION_STATE_WALK || actionState == ACTION_STATE_RUN) {
        if (PeachDisguiseReapplyDelay != 0) {
            PeachDisguiseReapplyDelay--;
            if (PeachDisguiseReapplyDelay == 0) {
                if (gGameStatusPtr->peachFlags & PEACH_FLAG_DISGUISED) {
                    playerStatus->animFlags |= PA_FLAG_INVISIBLE;
                    gGameStatusPtr->peachFlags |= PEACH_FLAG_DISGUISED;

                    disguiseNpc = peach_make_disguise_npc(gGameStatusPtr->peachDisguise);
                    if (disguiseNpc != NULL) {
                        disguiseNpc->flags &= ~NPC_FLAG_IGNORE_CAMERA_FOR_YAW;
                    }
                }
            }
        } else if (gGameStatusPtr->peachFlags & PEACH_FLAG_HAS_PARASOL && playerStatus->pressedButtons & BUTTON_B) {
            set_action_state(ACTION_STATE_USE_SNEAKY_PARASOL);
        }
    }
}

void peach_sync_disguise_npc(void) {
    PlayerStatus* playerStatus = &gPlayerStatus;

    if (PeachDisguiseNpcIndex >= 0) {
        Npc* npc = get_npc_by_index(PeachDisguiseNpcIndex);

        if (npc->flags & NPC_FLAG_IGNORE_CAMERA_FOR_YAW) {
            npc->renderYaw = playerStatus->spriteFacingAngle;
        } else {
            npc->yaw = playerStatus->targetYaw;
        }

        npc->pos.x = playerStatus->pos.x;
        npc->pos.y = playerStatus->pos.y;
        npc->pos.z = playerStatus->pos.z;
    }
}

Npc* peach_make_disguise_npc(enum PeachDisguise peachDisguise) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    NpcBlueprint bp;
    NpcBlueprint* bpPtr = &bp;
    Npc* npc;
    f32 yaw;

    if (peachDisguise == PEACH_DISGUISE_NONE) {
        return NULL;
    }

    playerStatus->colliderHeight = 37;
    playerStatus->colliderDiameter = 38;
    playerStatus->peachDisguise = peachDisguise;
    gGameStatusPtr->peachDisguise = peachDisguise;

    bpPtr->flags = NPC_FLAG_FLYING | NPC_FLAG_IGNORE_WORLD_COLLISION | NPC_FLAG_IGNORE_PLAYER_COLLISION | NPC_FLAG_IGNORE_CAMERA_FOR_YAW;
    bpPtr->initialAnim = BasicPeachDisguiseAnims[playerStatus->peachDisguise].idle;
    bpPtr->onUpdate = NULL;
    bpPtr->onRender = NULL;

    PeachDisguiseNpcIndex = create_standard_npc(bpPtr, PeachDisguiseExtraAnims[playerStatus->peachDisguise]);
    npc = get_npc_by_index(PeachDisguiseNpcIndex);

    disable_npc_shadow(npc);

    if (!(playerStatus->spriteFacingAngle >= 90.0f) || !(playerStatus->spriteFacingAngle < 270.0f)) {
        yaw = 180.0f;
    } else {
        yaw = 0.0f;
    }

    set_npc_yaw(npc, yaw);

    npc->pos.x = playerStatus->pos.x;
    npc->pos.y = playerStatus->pos.y;
    npc->pos.z = playerStatus->pos.z;

    return npc;
}

s32 peach_disguise_check_overlaps(void) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    Camera* camera = &gCameras[gCurrentCameraID];
    f32 yaw, dx, dy;
    s32 radius;
    s32 hitID;
    s32 i;

    if (playerStatus->spriteFacingAngle >= 90.0f && playerStatus->spriteFacingAngle < 270.0f) {
        yaw = camera->curYaw - 270.0f;
    } else {
        yaw = camera->curYaw - 90.0f;
    }
    sin_cos_rad(DEG_TO_RAD(clamp_angle(yaw)), &dx, &dy);

    for (radius = 2, i = 2; i > 0; radius += 18, i--) {
        f32 x = playerStatus->pos.x + (dx * radius);
        f32 y = playerStatus->pos.y + 4.0f;
        f32 z = playerStatus->pos.z - (dy * radius);
        hitID = player_test_lateral_overlap(PLAYER_COLLISION_HAMMER, playerStatus, &x, &y, &z, 4.0f, yaw);
        if (hitID > NO_COLLIDER) {
            break;
        }
    }

    return hitID;
}
