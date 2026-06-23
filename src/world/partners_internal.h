#pragma once

#include "common_structs.h"
#include "world/partners.h"
#include "macros.h"
#include "npc.h"

enum PartnerSpawnModes {
    PARTNER_SPAWN_NONE      = 0,
    PARTNER_SPAWN_RESET     = 1,
    PARTNER_SPAWN_INSTA     = 2,
    PARTNER_SPAWN_SWITCH    = 3,
};

extern s32 PartnerSpawnMode;

extern WorldPartner* ActivePartner;
extern s32 CurrentPartnerID;
extern Vec3f SavedPartnerPos;

void create_partner_npc(void);
void partner_free_npc(void);
void partner_clear_collision_flags(Npc* partner);
void partner_clear_player_tracking(Npc* partner);

void init_partner_commands(void);
void suspend_partner_commands(void);
void resume_partner_commands(void);
