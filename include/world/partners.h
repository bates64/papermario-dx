#pragma once

typedef void (*PartnerFunc)(Npc* partner);
typedef s32 (*PartnerBoolFunc)(Npc* partner);
typedef s32 (*PartnerTesHitFunc)(Npc* partner, Npc* enemy);
typedef void (*PartnerVoidFunc)(void);

typedef struct WorldPartner {
    /* 0x00 */ s32 isFlying;
    /* 0x04 */ PartnerFunc init;
    /* 0x08 */ EvtScript* takeOut;
    /* 0x0C */ EvtScript* update;
    /* 0x10 */ EvtScript* useAbility;
    /* 0x14 */ EvtScript* putAway;
    /* 0x18 */ s32 idle;
    /* 0x1C */ PartnerTesHitFunc testFirstStrike;
    /* 0x20 */ PartnerBoolFunc canUseAbility;
    /* 0x24 */ PartnerBoolFunc canPlayerOpenMenus;
    /* 0x28 */ PartnerFunc preBattle;
    /* 0x2C */ PartnerFunc postBattle;
    /* 0x30 */ EvtScript* onEnterMap;
    /* 0x34 */ PartnerVoidFunc syncPlayerPosition;
} WorldPartner; // size = 0x38

#define WORLD_PARTNER_EXPORT_NAME "gWorldPartner"
#define WORLD_PARTNER_ENTRY export WorldPartner gWorldPartner

extern Npc* gPartnerNpc; // wPartnerNpc
extern s32 WorldTattleInteractionID;

void partner_init_get_out(Npc*);
s32 partner_get_out(Npc*);
void partner_init_put_away(Npc* partner);
s32 partner_put_away(Npc* partner);
s32 partner_can_use_ability(void);
s32 partner_use_ability(void);
void partner_resolve_player_screen_overlap(Npc* partner);
void partner_walking_follow_player(Npc* partner);
b32 partner_can_continue_ability(s32);
s32 partner_force_player_flip_done(void);
void partner_suspend_ability_script(void);
void partner_resume_ability_script(void);
void partner_enable_input(void);
s32 partner_is_idle(Npc* partner);
b32 world_partner_can_open_menus_default(Npc* partner);
/// Optional overlay export for partners which can be dismounted.
s32 world_partner_can_dismount(void);
void partner_sync_player_position(void);
b32 partner_can_dismount(void);
