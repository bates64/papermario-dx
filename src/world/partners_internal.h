#pragma once

#include "common_structs.h"
#include "world/partners.h"
#include "macros.h"
#include "npc.h"

enum PartnerCommands {
    PARTNER_CMD_NONE                = 0,
    PARTNER_CMD_CLEAR               = 1,
    PARTNER_CMD_INSTA_SWITCH        = 2, // skips put away / take out scripts. assumes valid current partner.
    PARTNER_CMD_SWITCH              = 3, // assumes valid current partner.
    PARTNER_CMD_PUT_AWAY            = 4, // switches to null partner.
    PARTNER_CMD_INSTA_PUT_AWAY      = 5,
    PARTNER_CMD_TAKE_OUT            = 6, // assumes no current partner.
    PARTNER_CMD_INSTA_TAKE_OUT      = 7,
    PARTNER_CMD_USE_ABILITY         = 8,
    PARTNER_CMD_RESET               = 9,
    PARTNER_CMD_ABORT               = 10,
};

enum PartnerMovementStates {
    PARTNER_MOVE_FOLLOW_PLAYER      = 0,
    PARTNER_MOVE_BEGIN_JUMP         = 1,
    PARTNER_MOVE_JUMPING            = 2,
    PARTNER_MOVE_IDLE_NEAR_PLAYER   = 5,
    PARTNER_MOVE_TO_SIDE            = 15,
    PARTNER_MOVE_TO_GOAL            = 20,
    PARTNER_MOVE_DISABLE_ASAP       = 40,
    PARTNER_MOVE_DISABLED           = 50,
};

enum PartnerSpawnMode {
    PARTNER_SPAWN_NONE      = 0,
    PARTNER_SPAWN_RESET     = 1,
    PARTNER_SPAWN_INSTA     = 2,
    PARTNER_SPAWN_SWITCH    = 3,
};

extern s32 PartnerCommandState;
extern s32 PartnerSpawnMode;
extern Evt* PartnerCurrentScript;
extern s32 PartnerCurrentScriptID;
extern b32 PartnerCommandPending;
extern s32 NextPartnerCommand;
extern s32 CurPartnerCommand;

extern s16 PartnerFollowState;
extern s16 PartnerForcedFollowMode;

extern WorldPartner* ActivePartner;
extern s32 CurrentPartnerID;
extern Vec3f SavedPartnerPos;

void create_partner_npc(void);
void partner_free_npc(void);
void partner_clear_collision_flags(Npc* partner);
void partner_clear_player_tracking(Npc* partner);

