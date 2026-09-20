#include "common.h"
#include "world/disguise.h"

#include "sprite/npc/WorldClubba.h"
#include "sprite/npc/WorldKoopatrol.h"
#include "sprite/npc/HammerBros.h"

s32 PeachDisguiseReapplyDelay;

AnimID ClubbaDisguiseLimitAnims[] = {
    ANIM_WorldClubba_Still,
    ANIM_WorldClubba_Idle,
    ANIM_WorldClubba_Walk,
    ANIM_WorldClubba_Run,
    ANIM_WorldClubba_Talk,
    ANIM_WorldClubba_WakeUp,
    ANIM_WorldClubba_Sleep,
    ANIM_WorldClubba_IdleMini,
    ANIM_WorldClubba_GotItem,
    ANIM_LIST_END
};

AnimID HammerBroDisguiseLimitAnims[] = {
    ANIM_HammerBros_Still,
    ANIM_HammerBros_Idle,
    ANIM_HammerBros_IdleDisarmed,
    ANIM_HammerBros_Walk,
    ANIM_HammerBros_WalkDisarmed,
    ANIM_HammerBros_Run,
    ANIM_HammerBros_RunDisarmed,
    ANIM_HammerBros_Talk,
    ANIM_HammerBros_TalkDisarmed,
    ANIM_HammerBros_GotItem,
    ANIM_LIST_END
};

AnimID KoopatrolDisguiseLimitAnims[] = {
    ANIM_WorldKoopatrol_Still,
    ANIM_WorldKoopatrol_Idle,
    ANIM_WorldKoopatrol_IdleFlashlight,
    ANIM_WorldKoopatrol_Walk,
    ANIM_WorldKoopatrol_WalkFlashlight,
    ANIM_WorldKoopatrol_Run,
    ANIM_WorldKoopatrol_RunFlashlight,
    ANIM_WorldKoopatrol_Talk,
    ANIM_WorldKoopatrol_TalkFlashlight,
    ANIM_WorldKoopatrol_Lift,
    ANIM_WorldKoopatrol_CarryFast,
    ANIM_WorldKoopatrol_GotItem,
    ANIM_LIST_END
};

DisguiseAnims BasicPeachDisguiseAnims[] = {
    [PEACH_DISGUISE_NONE] {
        ANIM_WorldKoopatrol_Idle,
        ANIM_WorldKoopatrol_Walk,
        ANIM_WorldKoopatrol_Run,
        ANIM_WorldKoopatrol_Talk,
        ANIM_WorldKoopatrol_Still,
        ANIM_WorldKoopatrol_GotItem
    },
    [PEACH_DISGUISE_KOOPATROL] {
        ANIM_WorldKoopatrol_Idle,
        ANIM_WorldKoopatrol_Walk,
        ANIM_WorldKoopatrol_Run,
        ANIM_WorldKoopatrol_Talk,
        ANIM_WorldKoopatrol_Still,
        ANIM_WorldKoopatrol_GotItem
    },
    [PEACH_DISGUISE_HAMMER_BROS] {
        ANIM_HammerBros_IdleDisarmed,
        ANIM_HammerBros_WalkDisarmed,
        ANIM_HammerBros_RunDisarmed,
        ANIM_HammerBros_TalkDisarmed,
        ANIM_HammerBros_Still,
        ANIM_HammerBros_GotItem
    },
    [PEACH_DISGUISE_CLUBBA] {
        ANIM_WorldClubba_Idle,
        ANIM_WorldClubba_Walk,
        ANIM_WorldClubba_Run,
        ANIM_WorldClubba_Talk,
        ANIM_WorldClubba_Still,
        ANIM_WorldClubba_GotItem
    },
};

AnimID* PeachDisguiseLimitAnims[] = {
    [PEACH_DISGUISE_NONE] KoopatrolDisguiseLimitAnims,
    [PEACH_DISGUISE_KOOPATROL] KoopatrolDisguiseLimitAnims,
    [PEACH_DISGUISE_HAMMER_BROS] HammerBroDisguiseLimitAnims,
    [PEACH_DISGUISE_CLUBBA] ClubbaDisguiseLimitAnims
};

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
                    if (disguiseNpc != nullptr) {
                        disguiseNpc->flags &= ~NPC_FLAG_IGNORE_CAMERA_FOR_YAW;
                    }
                }
            }
        } else if ((gGameStatusPtr->peachFlags & PEACH_FLAG_HAS_PARASOL) && (playerStatus->pressedButtons & BUTTON_B)) {
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

Npc* peach_make_disguise_npc(s32 peachDisguise) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    NpcBlueprint bp;
    NpcBlueprint* bpPtr = &bp;
    Npc* npc;
    f32 yaw;

    if (peachDisguise == PEACH_DISGUISE_NONE) {
        return nullptr;
    }

    playerStatus->colliderHeight = 37;
    playerStatus->colliderDiameter = 38;
    playerStatus->peachDisguise = peachDisguise;
    gGameStatusPtr->peachDisguise = peachDisguise;

    bpPtr->flags = NPC_FLAG_FLYING | NPC_FLAG_IGNORE_WORLD_COLLISION | NPC_FLAG_IGNORE_CHAR_COLLISION | NPC_FLAG_IGNORE_CAMERA_FOR_YAW;
    bpPtr->initialAnim = BasicPeachDisguiseAnims[playerStatus->peachDisguise].idle;
    bpPtr->onUpdate = nullptr;
    bpPtr->onRender = nullptr;

    PeachDisguiseNpcIndex = create_standard_npc(bpPtr, PeachDisguiseLimitAnims[playerStatus->peachDisguise]);
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
