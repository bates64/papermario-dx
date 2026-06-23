#include "common_structs.h"
#include "world/partners.h"
#include "macros.h"

#include "ld_addrs.h"
#include "npc.h"
#include "hud_element.h"

#include "partner/goombario.h"
#include "sprite/npc/WorldGoombario.h"

#include "partner/kooper.h"
#include "sprite/npc/WorldKooper.h"

#include "partner/bombette.h"
#include "sprite/npc/WorldBombette.h"

#include "partner/parakarry.h"
#include "sprite/npc/WorldParakarry.h"

#include "partner/goompa.h"
#include "sprite/npc/Goompa.h"

#include "partner/watt.h"
#include "sprite/npc/WorldWatt.h"

#include "partner/sushie.h"
#include "sprite/npc/WorldSushie.h"

#include "partner/lakilester.h"
#include "sprite/npc/WorldLakilester.h"

#include "partner/bow.h"
#include "sprite/npc/WorldBow.h"

#include "partner/goombaria.h"
#include "sprite/npc/Goombaria.h"

#include "partner/twink.h"
#include "sprite/npc/Twink.h"

typedef struct PlayerPathElement {
    /* 0x00 */ b8 isJumping;
    /* 0x01 */ PAD(3);
    /* 0x04 */ Vec3f pos;
} PlayerPathElement; // size = 0x10

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

PartnerStatus gPartnerStatus;
Npc* gPartnerNpc;

BSS s32 PartnerCommandState;
BSS PlayerPathElement PlayerMoveHistory[40];
BSS s32 PlayerMoveHistoryIndex;
BSS s32 PartnerMoveHistoryReadIndex;
BSS f32 PartnerTetherDistance;
BSS s32 PartnerCommandTransitionState;
BSS s16 PartnerFollowState;
BSS s16 PartnerForcedFollowMode;
BSS s16 PartnerFollowSubstate;
BSS s32 PartnerNpcIndex;
BSS s32 CurrentPartnerID;
BSS Evt* PartnerCurrentScript;
BSS s32 PartnerCurrentScriptID;
BSS b32 PartnerCommandPending;
BSS s32 NextPartnerID;
BSS s32 NextPartnerCommand;
BSS s32 CurPartnerCommand;
BSS WorldPartner* ActivePartner;

extern HudScript HES_Partner0;
extern HudScript HES_Goombario;
extern HudScript HES_Kooper;
extern HudScript HES_Bombette;
extern HudScript HES_Parakarry;
extern HudScript HES_Watt;
extern HudScript HES_Sushie;
extern HudScript HES_Lakilester;
extern HudScript HES_Bow;
extern HudScript HES_PartnerA;
extern HudScript HES_Partner0Disabled;
extern HudScript HES_GoombarioDisabled;
extern HudScript HES_KooperDisabled;
extern HudScript HES_BombetteDisabled;
extern HudScript HES_ParakarryDisabled;
extern HudScript HES_WattDisabled;
extern HudScript HES_SushieDisabled;
extern HudScript HES_LakilesterDisabled;
extern HudScript HES_BowDisabled;
extern HudScript HES_PartnerADisabled;

extern HudScript HES_StatusDigit0;
extern HudScript HES_StatusDigit1;
extern HudScript HES_StatusDigit2;
extern HudScript HES_StatusDigit3;
extern HudScript HES_StatusDigit4;
extern HudScript HES_StatusDigit5;
extern HudScript HES_StatusDigit6;
extern HudScript HES_StatusDigit7;
extern HudScript HES_StatusDigit8;
extern HudScript HES_StatusDigit9;
extern HudScript HES_StatusTimes;
extern HudScript HES_StatusSlash;

extern HudScript HES_StatusStar1;
extern HudScript HES_StatusStar2;
extern HudScript HES_StatusStar3;
extern HudScript HES_StatusStar4;
extern HudScript HES_StatusStar5;
extern HudScript HES_StatusStar6;
extern HudScript HES_StatusStar7;

extern HudScript HES_StatusSPIncrement1;
extern HudScript HES_StatusSPIncrement2;
extern HudScript HES_StatusSPIncrement3;
extern HudScript HES_StatusSPIncrement4;
extern HudScript HES_StatusSPIncrement5;
extern HudScript HES_StatusSPIncrement6;
extern HudScript HES_StatusSPIncrement7;

s32 partner_is_idle(Npc* partner);
b32 world_partner_can_open_menus_default(Npc* partner);
void process_partner_commands(void);
void partner_flying_follow_player(Npc*);
void partner_move_to_goal(Npc*, s32);

// Partner icons
HudScript* wPartnerHudScripts[] = {
    &HES_Partner0, &HES_Goombario, &HES_Kooper, &HES_Bombette,
    &HES_Parakarry, &HES_Partner0, &HES_Watt, &HES_Sushie,
    &HES_Lakilester, &HES_Bow, &HES_PartnerA, &HES_PartnerA,
    &HES_PartnerA, &HES_PartnerA, &HES_PartnerA, &HES_PartnerA,
};
HudScript* wDisabledPartnerHudScripts[] = {
    &HES_Partner0Disabled, &HES_GoombarioDisabled, &HES_KooperDisabled, &HES_BombetteDisabled,
    &HES_ParakarryDisabled, &HES_Partner0Disabled, &HES_WattDisabled, &HES_SushieDisabled,
    &HES_LakilesterDisabled, &HES_BowDisabled, &HES_PartnerADisabled, &HES_PartnerADisabled,
    &HES_PartnerADisabled, &HES_PartnerADisabled, &HES_PartnerADisabled, &HES_PartnerADisabled,
};
HudScript* DigitHudScripts[] = {
    &HES_StatusDigit0, &HES_StatusDigit1, &HES_StatusDigit2, &HES_StatusDigit3, &HES_StatusDigit4,
    &HES_StatusDigit5, &HES_StatusDigit6, &HES_StatusDigit7, &HES_StatusDigit8, &HES_StatusDigit9,
};
HudScript* TimesHudScript = &HES_StatusTimes;
HudScript* SlashHudScript = &HES_StatusSlash;
HudScript* SPIncrementHudScripts[] = {
    &HES_StatusSPIncrement1, &HES_StatusSPIncrement3, &HES_StatusSPIncrement2,
    &HES_StatusSPIncrement4, &HES_StatusSPIncrement5, &HES_StatusSPIncrement6, &HES_StatusSPIncrement7
};
HudScript* SPStarHudScripts[] = { &HES_StatusStar1, &HES_StatusStar3, &HES_StatusStar2, &HES_StatusStar4,
    &HES_StatusStar5, &HES_StatusStar6, &HES_StatusStar7
};

s32 StatusBarSPIncrementOffsets[] = { -1, 1, 2, 4, 5, 7, 8, 0, 0, 0 };

BSS b32 PartnerBlockedAbove;
BSS s32 PartnerMoveGoalX;
BSS s32 PartnerMoveGoalZ;
BSS s32 PartnerMoveTime;
BSS f32 PartnerMoveSpeed;
BSS f32 PartnerMoveYaw;
BSS s16 PartnerStuckTime;

WorldPartner wPartners[] = {
    [PARTNER_NONE] {
        // blank
    },
    [PARTNER_GOOMBARIO] {
        .dmaStart = &world_partner_goombario_ROM_START,
        .dmaEnd = &world_partner_goombario_ROM_END,
        .dmaDest = &world_partner_goombario_VRAM,
        .isFlying = false,
        .init = world_goombario_init,
        .takeOut = &EVS_WorldGoombario_TakeOut,
        .update = &EVS_WorldGoombario_Update,
        .useAbility = &EVS_WorldGoombario_UseAbility,
        .putAway = &EVS_WorldGoombario_PutAway,
        .idle = ANIM_WorldGoombario_Idle,
        .canUseAbility = world_goombario_can_open_menus,
        .canPlayerOpenMenus = world_goombario_can_open_menus,
        .preBattle = world_goombario_pre_battle,
    },
    [PARTNER_KOOPER] {
        .dmaStart = &world_partner_kooper_ROM_START,
        .dmaEnd = &world_partner_kooper_ROM_END,
        .dmaDest = &world_partner_kooper_VRAM,
        .isFlying = false,
        .init = world_kooper_init,
        .takeOut = &EVS_WorldKooper_TakeOut,
        .update = &EVS_WorldKooper_Update,
        .useAbility = &EVS_WorldKooper_UseAbility,
        .putAway = &EVS_WorldKooper_PutAway,
        .idle = ANIM_WorldKooper_Idle,
        .testFirstStrike = world_kooper_test_first_strike,
        .canUseAbility = partner_is_idle,
        .canPlayerOpenMenus = partner_is_idle,
        .preBattle = world_kooper_pre_battle,
        .postBattle = world_kooper_post_battle,
    },
    [PARTNER_BOMBETTE] {
        .dmaStart = &world_partner_bombette_ROM_START,
        .dmaEnd = &world_partner_bombette_ROM_END,
        .dmaDest = &world_partner_bombette_VRAM,
        .isFlying = false,
        .init = world_bombette_init,
        .takeOut = &EVS_WorldBombette_TakeOut,
        .update = &EVS_WorldBombette_Update,
        .useAbility = &EVS_WorldBombette_UseAbility,
        .putAway = &EVS_WorldBombette_PutAway,
        .idle = ANIM_WorldBombette_Idle,
        .testFirstStrike = world_bombette_test_first_strike,
        .canUseAbility = world_bombette_can_use_ability,
        .canPlayerOpenMenus = world_bombette_can_open_menus,
        .preBattle = world_bombette_pre_battle,
    },
    [PARTNER_PARAKARRY] {
        .dmaStart = &world_partner_parakarry_ROM_START,
        .dmaEnd = &world_partner_parakarry_ROM_END,
        .dmaDest = &world_partner_parakarry_VRAM,
        .isFlying = true,
        .init = world_parakarry_init,
        .takeOut = &EVS_WorldParakarry_TakeOut,
        .update = &EVS_WorldParakarry_Update,
        .useAbility = &EVS_WorldParakarry_UseAbility,
        .putAway = &EVS_WorldParakarry_PutAway,
        .idle = ANIM_WorldParakarry_Idle,
        .canPlayerOpenMenus = partner_is_idle,
        .preBattle = world_parakarry_pre_battle,
        .postBattle = world_parakarry_post_battle,
    },
    [PARTNER_GOOMPA] {
        .dmaStart = &world_partner_goompa_ROM_START,
        .dmaEnd = &world_partner_goompa_ROM_END,
        .dmaDest = &world_partner_goompa_VRAM,
        .isFlying = false,
        .init = world_goompa_init,
        .takeOut = &EVS_WorldGoompa_TakeOut,
        .update = &EVS_WorldGoompa_Update,
        .useAbility = &EVS_WorldGoompa_UseAbility,
        .putAway = &EVS_WorldGoompa_PutAway,
        .idle = ANIM_Goompa_Idle,
    },
    [PARTNER_WATT] {
        .dmaStart = &world_partner_watt_ROM_START,
        .dmaEnd = &world_partner_watt_ROM_END,
        .dmaDest = &world_partner_watt_VRAM,
        .isFlying = true,
        .init = world_watt_init,
        .takeOut = &EVS_WorldWatt_TakeOut,
        .update = &EVS_WorldWatt_Update,
        .useAbility = &EVS_WorldWatt_UseAbility,
        .putAway = &EVS_WorldWatt_PutAway,
        .idle = ANIM_WorldWatt_Idle,
        .canPlayerOpenMenus = world_partner_can_open_menus_default,
        .preBattle = world_watt_pre_battle,
        .postBattle = world_watt_post_battle,
        .onEnterMap = &EVS_WorldWatt_EnterMap,
    },
    [PARTNER_SUSHIE] {
        .dmaStart = &world_partner_sushie_ROM_START,
        .dmaEnd = &world_partner_sushie_ROM_END,
        .dmaDest = &world_partner_sushie_VRAM,
        .isFlying = false,
        .init = world_sushie_init,
        .takeOut = &EVS_WorldSushie_TakeOut,
        .update = &EVS_WorldSushie_Update,
        .useAbility = &EVS_WorldSushie_UseAbility,
        .putAway = &EVS_WorldSushie_PutAway,
        .idle = ANIM_WorldSushie_Idle,
        .canPlayerOpenMenus = world_partner_can_open_menus_default,
        .preBattle = world_sushie_pre_battle,
        .postBattle = world_sushie_post_battle,
        .onEnterMap = &EVS_WorldSushie_EnterMap,
    },
    [PARTNER_LAKILESTER] {
        .dmaStart = &world_partner_lakilester_ROM_START,
        .dmaEnd = &world_partner_lakilester_ROM_END,
        .dmaDest = &world_partner_lakilester_VRAM,
        .isFlying = true,
        .init = world_lakilester_init,
        .takeOut = &EVS_WorldLakilester_TakeOut,
        .update = &EVS_WorldLakilester_Update,
        .useAbility = &EVS_WorldLakilester_UseAbility,
        .putAway = &EVS_WorldLakilester_PutAway,
        .idle = ANIM_WorldLakilester_Idle,
        .canPlayerOpenMenus = world_partner_can_open_menus_default,
        .preBattle = world_lakilester_pre_battle,
        .postBattle = world_lakilester_post_battle,
        .onEnterMap = &EVS_WorldLakilester_EnterMap,
    },
    [PARTNER_BOW] {
        .dmaStart = &world_partner_bow_ROM_START,
        .dmaEnd = &world_partner_bow_ROM_END,
        .dmaDest = &world_partner_bow_VRAM,
        .isFlying = true,
        .init = world_bow_init,
        .takeOut = &EVS_WorldBow_TakeOut,
        .update = &EVS_WorldBow_Update,
        .useAbility = &EVS_WorldBow_UseAbility,
        .putAway = &EVS_WorldBow_PutAway,
        .idle = ANIM_WorldBow_Idle,
        .canUseAbility = partner_is_idle,
        .canPlayerOpenMenus = world_partner_can_open_menus_default,
        .preBattle = world_bow_pre_battle,
    },
    [PARTNER_GOOMBARIA] {
        .dmaStart = &world_partner_goombaria_ROM_START,
        .dmaEnd = &world_partner_goombaria_ROM_END,
        .dmaDest = &world_partner_goombaria_VRAM,
        .isFlying = false,
        .init = world_goombaria_init,
        .takeOut = &EVS_WorldGoombaria_TakeOut,
        .update = &EVS_WorldGoombaria_Update,
        .useAbility = &EVS_WorldGoombaria_UseAbility,
        .putAway = &EVS_WorldGoombaria_PutAway,
        .idle = ANIM_Goombaria_Idle,
        .canUseAbility = partner_is_idle,
        .canPlayerOpenMenus = partner_is_idle,
    },
    [PARTNER_TWINK] {
        .dmaStart = &world_partner_twink_ROM_START,
        .dmaEnd = &world_partner_twink_ROM_END,
        .dmaDest = &world_partner_twink_VRAM,
        .isFlying = true,
        .init = world_twink_init,
        .takeOut = &EVS_WorldTwink_TakeOut,
        .update = &EVS_WorldTwink_Update,
        .useAbility = &EVS_WorldTwink_UseAbility,
        .putAway = &EVS_WorldTwink_PutAway,
        .idle = ANIM_Twink_Idle,
        .canUseAbility = partner_is_idle,
        .canPlayerOpenMenus = partner_is_idle,
    },
};

Vec3f SavedPartnerPos = { 0 };

PartnerAnimations gPartnerAnimations[] = {
    [PARTNER_NONE] {
        // blank
    },
    [PARTNER_GOOMBARIO] {{
        ANIM_WorldGoombario_Still,
        ANIM_WorldGoombario_Walk,
        ANIM_WorldGoombario_Jump,
        ANIM_WorldGoombario_Fall,
        ANIM_WorldGoombario_Idle,
        ANIM_WorldGoombario_Idle,
        ANIM_WorldGoombario_Run,
        ANIM_WorldGoombario_Talk,
        ANIM_WorldGoombario_Hurt
    }},
    [PARTNER_KOOPER] {{
        ANIM_WorldKooper_Still,
        ANIM_WorldKooper_Walk,
        ANIM_WorldKooper_Jump,
        ANIM_WorldKooper_Fall,
        ANIM_WorldKooper_Still,
        ANIM_WorldKooper_Idle,
        ANIM_WorldKooper_Run,
        ANIM_WorldKooper_Talk,
        ANIM_WorldKooper_Hurt
    }},
    [PARTNER_BOMBETTE] {{
        ANIM_WorldBombette_Still,
        ANIM_WorldBombette_Walk,
        ANIM_WorldBombette_Jump,
        ANIM_WorldBombette_Fall,
        ANIM_WorldBombette_Still,
        ANIM_WorldBombette_Idle,
        ANIM_WorldBombette_Run,
        ANIM_WorldBombette_Talk,
        ANIM_WorldBombette_Hurt
    }},
    [PARTNER_PARAKARRY] {{
        ANIM_WorldParakarry_Still,
        ANIM_WorldParakarry_Walk,
        ANIM_WorldParakarry_FlyFast,
        ANIM_WorldParakarry_Walk,
        ANIM_WorldParakarry_Walk,
        ANIM_WorldParakarry_Idle,
        ANIM_WorldParakarry_Run,
        ANIM_WorldParakarry_Talk,
        ANIM_WorldParakarry_Hurt
    }},
    [PARTNER_GOOMPA] {{
        ANIM_Goompa_Still,
        ANIM_Goompa_Walk,
        ANIM_Goompa_Jump,
        ANIM_Goompa_Fall,
        ANIM_Goompa_Idle,
        ANIM_Goompa_Idle,
        ANIM_Goompa_Run,
        ANIM_Goompa_Talk,
        ANIM_Goompa_Idle
    }},
    [PARTNER_WATT] {{
        ANIM_WorldWatt_Still,
        ANIM_WorldWatt_Walk,
        ANIM_WorldWatt_Walk,
        ANIM_WorldWatt_Walk,
        ANIM_WorldWatt_Still,
        ANIM_WorldWatt_Idle,
        ANIM_WorldWatt_Run,
        ANIM_WorldWatt_Talk,
        ANIM_WorldWatt_Hurt
    }},
    [PARTNER_SUSHIE] {{
        ANIM_WorldSushie_Still,
        ANIM_WorldSushie_Walk,
        ANIM_WorldSushie_Walk,
        ANIM_WorldSushie_Walk,
        ANIM_WorldSushie_Still,
        ANIM_WorldSushie_Idle,
        ANIM_WorldSushie_Run,
        ANIM_WorldSushie_Talk,
        ANIM_WorldSushie_Hurt
    }},
    [PARTNER_LAKILESTER] {{
        ANIM_WorldLakilester_Still,
        ANIM_WorldLakilester_Walk,
        ANIM_WorldLakilester_Walk,
        ANIM_WorldLakilester_Walk,
        ANIM_WorldLakilester_Still,
        ANIM_WorldLakilester_Idle,
        ANIM_WorldLakilester_Run,
        ANIM_WorldLakilester_Talk,
        ANIM_WorldLakilester_TiredTalk
    }},
    [PARTNER_BOW] {{
        ANIM_WorldBow_Still,
        ANIM_WorldBow_Walk,
        ANIM_WorldBow_Walk,
        ANIM_WorldBow_Walk,
        ANIM_WorldBow_Still,
        ANIM_WorldBow_Idle,
        ANIM_WorldBow_Run,
        ANIM_WorldBow_Talk,
        ANIM_WorldBow_Flail
    }},
    [PARTNER_GOOMBARIA] {{
        ANIM_Goombaria_Still,
        ANIM_Goombaria_Walk,
        ANIM_Goombaria_Jump,
        ANIM_Goombaria_Fall,
        ANIM_Goombaria_Idle,
        ANIM_Goombaria_Idle,
        ANIM_Goombaria_Run,
        ANIM_Goombaria_Talk,
        ANIM_Goombaria_Idle
    }},
    [PARTNER_TWINK] {{
        ANIM_Twink_Still,
        ANIM_Twink_Idle,
        ANIM_Twink_Idle,
        ANIM_Twink_Idle,
        ANIM_Twink_Idle,
        ANIM_Twink_Idle,
        ANIM_Twink_Idle,
        ANIM_Twink_Talk,
        ANIM_Twink_Hurt
    }},
};

f32 PartnerFlyingDeltaY = 0.0f;

b32 partner_can_move_over_collider(s32 collisionID) {
    if (collisionID <= NO_COLLIDER) {
        return true;
    }

    if (collisionID & COLLISION_WITH_ENTITY_BIT) {
        switch (get_entity_type(collisionID)) {
            case ENTITY_TYPE_BLUE_SWITCH:
            case ENTITY_TYPE_RED_SWITCH:
            case ENTITY_TYPE_HUGE_BLUE_SWITCH:
            case ENTITY_TYPE_GREEN_STOMP_SWITCH:
            case ENTITY_TYPE_SIMPLE_SPRING:
            case ENTITY_TYPE_SCRIPT_SPRING:
            case ENTITY_TYPE_CHEST:
            case ENTITY_TYPE_BELLBELL_PLANT:
            case ENTITY_TYPE_TRUMPET_PLANT:
            case ENTITY_TYPE_MUNCHLESIA:
            case ENTITY_TYPE_CYMBAL_PLANT:
            case ENTITY_TYPE_PINK_FLOWER:
            case ENTITY_TYPE_SPINNING_FLOWER:
            case ENTITY_TYPE_3B:
            case ENTITY_TYPE_TWEESTER:
               return false;
        }
    }

    return true;
}

s32 partner_is_idle(Npc* partner) {
    return gPartnerStatus.partnerActionState == PARTNER_ACTION_NONE;
}

b32 world_partner_can_open_menus_default(Npc* partner) {
    return true;
}

b32 partner_can_continue_ability(s32 partnerID) {
    s32 playerActionState = gPlayerStatus.actionState;
    b32 ret = false;

    if (gPlayerStatus.flags & PS_FLAG_HIT_FIRE) {
        return false;
    }

    // any partner
    if (playerActionState == ACTION_STATE_IDLE
     || playerActionState == ACTION_STATE_WALK
     || playerActionState == ACTION_STATE_RUN
    ) {
        ret = true;
    }

    // check specific partners
    if (partnerID == PARTNER_BOW) {
        if (playerActionState == ACTION_STATE_RIDE) {
            ret = true;
        }
    } else if (partnerID == PARTNER_PARAKARRY) {
        if (playerActionState == ACTION_STATE_RIDE
         || playerActionState == ACTION_STATE_IDLE
         || playerActionState == ACTION_STATE_WALK
         || playerActionState == ACTION_STATE_RUN
        ) {
            ret = true;
        }
    }

    return ret;
}

b32 partner_is_flying(void) {
    return ActivePartner->isFlying;
}

void partner_clear_collision_flags(Npc* partner) {
    partner->flags &= ~(NPC_FLAG_COLLIDING_WITH_NPC | NPC_FLAG_COLLIDING_FORWARD_WITH_WORLD
        | NPC_FLAG_COLLIDING_WITH_WORLD | NPC_FLAG_GROUNDED | NPC_FLAG_JUMPING);
}

void create_partner_npc(void) {
    WorldPartner* partnerEntry = &wPartners[CurrentPartnerID];
    NpcBlueprint blueprint;

    ActivePartner = partnerEntry;
    dma_copy(partnerEntry->dmaStart, partnerEntry->dmaEnd, partnerEntry->dmaDest);

    blueprint.flags = NPC_FLAG_PARTNER | NPC_FLAG_IGNORE_CHAR_COLLISION;
    blueprint.initialAnim = ActivePartner->idle;
    blueprint.onUpdate = nullptr;
    blueprint.onRender = nullptr;
    PartnerNpcIndex = create_basic_npc(&blueprint);

    gPartnerNpc = get_npc_by_index(PartnerNpcIndex);

    gPartnerNpc->npcID = NPC_PARTNER;
    gPartnerNpc->collisionDiameter = 10;
    gPartnerNpc->collisionHeight = 10;

    gPartnerNpc->pos.x = NPC_DISPOSE_POS_X;
    gPartnerNpc->pos.y = NPC_DISPOSE_POS_Y;
    gPartnerNpc->pos.z = NPC_DISPOSE_POS_Z;
    gPartnerNpc->scale.x = 0.0f;
    gPartnerNpc->scale.y = 0.0f;
    gPartnerNpc->scale.z = 0.0f;

    TweesterTouchingPartner = nullptr;
}

void partner_free_npc(void) {
    free_npc_by_index(PartnerNpcIndex);
}

void process_partner_commands(void) {
    PlayerData* playerData = &gPlayerData;
    PartnerStatus* partnerStatus = &gPartnerStatus;
    PlayerStatus* playerStatus = &gPlayerStatus;

    if (partnerStatus->inputDisabledCount == 0) {
        partnerStatus->stickX = gGameStatusPtr->stickX[gGameStatusPtr->multiplayerEnabled];
        partnerStatus->stickY = gGameStatusPtr->stickY[gGameStatusPtr->multiplayerEnabled];
        partnerStatus->curButtons = gGameStatusPtr->curButtons[gGameStatusPtr->multiplayerEnabled];
        partnerStatus->pressedButtons = gGameStatusPtr->pressedButtons[gGameStatusPtr->multiplayerEnabled];
        partnerStatus->heldButtons = gGameStatusPtr->heldButtons[gGameStatusPtr->multiplayerEnabled];
    } else {
        partnerStatus->stickX = 0;
        partnerStatus->stickY = 0;
        partnerStatus->curButtons = 0;
        partnerStatus->pressedButtons = 0;
        partnerStatus->heldButtons = 0;
    }

    if (playerStatus->animFlags & PA_FLAG_INTERRUPT_USE_PARTNER) {
        playerStatus->animFlags &= ~PA_FLAG_INTERRUPT_USE_PARTNER;
        partnerStatus->pressedButtons |= (BUTTON_B | BUTTON_C_DOWN);
        playerStatus->animFlags |= PA_FLAG_FORCED_PARTNER_ABILITY_END;
    }

    if (NextPartnerCommand != PARTNER_CMD_NONE) {
        CurPartnerCommand = NextPartnerCommand;
        PartnerCommandState = 0;
        NextPartnerCommand = PARTNER_CMD_NONE;
    }

    if (CurPartnerCommand >= PARTNER_CMD_INSTA_SWITCH) {
        if (CurPartnerCommand != PARTNER_CMD_USE_ABILITY) {
            PartnerCommandTransitionState = PARTNER_SPAWN_NONE;
        }
    }

    switch (CurPartnerCommand) {
        case PARTNER_CMD_NONE:
            break;
        case PARTNER_CMD_SWITCH:
            PartnerCommandTransitionState = PARTNER_SPAWN_SWITCH;
            switch (PartnerCommandState) {
                case 0: // put away current partner
                    disable_player_input();
                    sfx_play_sound(SOUND_PARTNER_PUT_AWAY);
                    kill_script_by_ID(PartnerCurrentScriptID);
                    PartnerCurrentScript = start_script(ActivePartner->putAway, EVT_PRIORITY_14, EVT_FLAG_RUN_IMMEDIATELY);
                    PartnerCurrentScript->owner2.npc = gPartnerNpc;
                    PartnerCurrentScriptID = PartnerCurrentScript->id;
                    PartnerCurrentScript->groupFlags = EVT_GROUP_PASSIVE_NPC;
                    PartnerCommandState = 1;
                    set_time_freeze_mode(TIME_FREEZE_PARTIAL);
                    break;
                case 1: // free old partner and create new one
                    if (does_script_exist(PartnerCurrentScriptID)) {
                        break;
                    }
                    set_time_freeze_mode(TIME_FREEZE_NONE);
                    partner_free_npc();
                    playerData->curPartner = CurrentPartnerID = NextPartnerID;
                    create_partner_npc();
                    sfx_play_sound(SOUND_PARTNER_GET_OUT);
                    ActivePartner->init(gPartnerNpc);
                    PartnerCommandState = 2;
                    // fallthrough
                case 2: // take out new partner
                    PartnerCurrentScript = start_script(ActivePartner->takeOut, EVT_PRIORITY_14, EVT_FLAG_RUN_IMMEDIATELY);
                    PartnerCurrentScript->owner2.npc = gPartnerNpc;
                    PartnerCurrentScriptID = PartnerCurrentScript->id;
                    PartnerCurrentScript->groupFlags = EVT_GROUP_PASSIVE_NPC;
                    PartnerCommandState = 3;
                    set_time_freeze_mode(TIME_FREEZE_PARTIAL);
                    break;
                case 3: // resume normal partner behaviour
                    if (does_script_exist(PartnerCurrentScriptID)) {
                        break;
                    }
                    PartnerCurrentScript = start_script(ActivePartner->update, EVT_PRIORITY_14, EVT_FLAG_RUN_IMMEDIATELY);
                    PartnerCurrentScript->owner2.npc = gPartnerNpc;
                    PartnerCurrentScriptID = PartnerCurrentScript->id;
                    PartnerCurrentScript->groupFlags = EVT_GROUP_PASSIVE_NPC;
                    CurPartnerCommand = PARTNER_CMD_CLEAR;
                    enable_player_input();
                    set_time_freeze_mode(TIME_FREEZE_NONE);
                    break;
            }
            break;
        case PARTNER_CMD_INSTA_SWITCH:
            PartnerCommandTransitionState = PARTNER_SPAWN_SWITCH;
            switch (PartnerCommandState) {
                case 0:
                    kill_script_by_ID(PartnerCurrentScriptID);
                    PartnerCommandState++;
                case 1:
                    partner_free_npc();
                    playerData->curPartner = CurrentPartnerID = NextPartnerID;
                    create_partner_npc();
                    gPartnerNpc->pos.x = SavedPartnerPos.x;
                    gPartnerNpc->pos.y = SavedPartnerPos.y;
                    gPartnerNpc->pos.z = SavedPartnerPos.z;
                    gPartnerNpc->jumpVel = 0.0f;
                    gPartnerNpc->scale.x = 1.0f;
                    gPartnerNpc->scale.y = 1.0f;
                    gPartnerNpc->scale.z = 1.0f;
                    ActivePartner->init(gPartnerNpc);
                    PartnerCommandState++;
                    // fallthrough
                case 2:
                    PartnerCommandState++;
                    break;
                case 3:
                    PartnerCurrentScript = start_script(ActivePartner->update, EVT_PRIORITY_14, EVT_FLAG_RUN_IMMEDIATELY);
                    PartnerCurrentScript->owner2.npc = gPartnerNpc;
                    PartnerCurrentScriptID = PartnerCurrentScript->id;
                    PartnerCurrentScript->groupFlags = EVT_GROUP_PASSIVE_NPC;
                    CurPartnerCommand = PARTNER_CMD_CLEAR;
                    break;
            }
            break;
        case PARTNER_CMD_PUT_AWAY:
            switch (PartnerCommandState) {
                case 0: // put away current partner
                    disable_player_input();
                    sfx_play_sound(SOUND_PARTNER_PUT_AWAY);
                    kill_script_by_ID(PartnerCurrentScriptID);
                    PartnerCurrentScript = start_script(ActivePartner->putAway, EVT_PRIORITY_14, EVT_FLAG_RUN_IMMEDIATELY);
                    PartnerCurrentScript->owner2.npc = gPartnerNpc;
                    PartnerCurrentScriptID = PartnerCurrentScript->id;
                    PartnerCurrentScript->groupFlags = EVT_GROUP_PASSIVE_NPC;
                    PartnerCommandState++;
                    break;
                case 1: // free old partner and resume game
                    if (does_script_exist(PartnerCurrentScriptID)) {
                        break;
                    }
                    partner_free_npc();
                    CurPartnerCommand = PARTNER_CMD_CLEAR;
                    playerData->curPartner = CurrentPartnerID = NextPartnerID;
                    enable_player_input();
                    break;
            }
            break;
        case PARTNER_CMD_INSTA_PUT_AWAY:
            if (PartnerCommandState == 0) {
                kill_script_by_ID(PartnerCurrentScriptID);
                partner_free_npc();
                CurPartnerCommand = PARTNER_CMD_CLEAR;
                playerData->curPartner = CurrentPartnerID = NextPartnerID;
                break;
            }
            break;
        case PARTNER_CMD_TAKE_OUT:
            switch (PartnerCommandState) {
                case 0: // create the new partner
                    disable_player_input();
                    playerData->curPartner = CurrentPartnerID = NextPartnerID;
                    create_partner_npc();
                    ActivePartner->init(gPartnerNpc);
                    PartnerCommandState++;
                    // fallthrough
                case 1: // take out new partner
                    PartnerCurrentScript = start_script(ActivePartner->takeOut, EVT_PRIORITY_14, EVT_FLAG_RUN_IMMEDIATELY);
                    PartnerCurrentScript->owner2.npc = gPartnerNpc;
                    PartnerCurrentScriptID = PartnerCurrentScript->id;
                    PartnerCurrentScript->groupFlags = EVT_GROUP_PASSIVE_NPC;
                    PartnerCommandState++;
                    break;
                case 2: // resume standard partner behaviour
                    if (does_script_exist(PartnerCurrentScriptID)) {
                        break;
                    }
                    PartnerCurrentScript = start_script(ActivePartner->update, EVT_PRIORITY_14, EVT_FLAG_RUN_IMMEDIATELY);
                    PartnerCurrentScript->owner2.npc = gPartnerNpc;
                    PartnerCurrentScriptID = PartnerCurrentScript->id;
                    PartnerCurrentScript->groupFlags = EVT_GROUP_PASSIVE_NPC;
                    CurPartnerCommand = PARTNER_CMD_CLEAR;
                    enable_player_input();
                    break;
            }
            break;
        case PARTNER_CMD_INSTA_TAKE_OUT:
            PartnerCommandTransitionState = PARTNER_SPAWN_INSTA;
            switch (PartnerCommandState) {
                case 0:
                    disable_player_input();
                    playerData->curPartner = CurrentPartnerID = NextPartnerID;
                    create_partner_npc();
                    gPartnerNpc->pos.x = SavedPartnerPos.x;
                    gPartnerNpc->pos.y = SavedPartnerPos.y;
                    gPartnerNpc->pos.z = SavedPartnerPos.z;
                    gPartnerNpc->jumpVel = 0.0f;
                    gPartnerNpc->scale.x = 1.0f;
                    gPartnerNpc->scale.y = 1.0f;
                    gPartnerNpc->scale.z = 1.0f;
                    ActivePartner->init(gPartnerNpc);
                    PartnerCommandState++;
                    break;
                case 1:
                    PartnerCurrentScript = start_script(ActivePartner->update, EVT_PRIORITY_14, EVT_FLAG_RUN_IMMEDIATELY);
                    PartnerCurrentScript->owner2.npc = gPartnerNpc;
                    PartnerCurrentScriptID = PartnerCurrentScript->id;
                    PartnerCurrentScript->groupFlags = EVT_GROUP_PASSIVE_NPC;
                    CurPartnerCommand = PARTNER_CMD_CLEAR;
                    gPartnerNpc->curAnim = gPartnerAnimations[CurrentPartnerID].fly;
                    enable_player_input();
                    break;
            }
            break;
        case PARTNER_CMD_USE_ABILITY:
            switch (PartnerCommandState) {
                case 0:
                    kill_script_by_ID(PartnerCurrentScriptID);
                    PartnerCurrentScript = start_script(ActivePartner->useAbility, EVT_PRIORITY_14, EVT_FLAG_RUN_IMMEDIATELY);
                    PartnerCurrentScript->owner2.npc = gPartnerNpc;
                    PartnerCurrentScriptID = PartnerCurrentScript->id;
                    PartnerCurrentScript->groupFlags = EVT_GROUP_PASSIVE_NPC;
                    PartnerCommandState++;
                    break;
                case 1:
                    if (does_script_exist(PartnerCurrentScriptID)) {
                        break;
                    }
                    PartnerCurrentScript = start_script(ActivePartner->update, EVT_PRIORITY_14, EVT_FLAG_RUN_IMMEDIATELY);
                    PartnerCurrentScript->owner2.npc = gPartnerNpc;
                    PartnerCurrentScriptID = PartnerCurrentScript->id;
                    PartnerCurrentScript->groupFlags = EVT_GROUP_PASSIVE_NPC;
                    CurPartnerCommand = PARTNER_CMD_CLEAR;
                    break;
            }
            break;
        case PARTNER_CMD_RESET:
            PartnerCommandTransitionState = PARTNER_SPAWN_RESET;
            switch (PartnerCommandState) {
                case 0:
                    disable_player_input();
                    ActivePartner->init(gPartnerNpc);
                    PartnerCommandState++;
                    // fallthrough
                case 1:
                    PartnerCommandState++;
                    break;
                case 2:
                    if (partnerStatus->partnerActionState != 1) {
                        SavedPartnerPos.x = playerStatus->pos.x;
                        SavedPartnerPos.y = playerStatus->pos.y;
                        SavedPartnerPos.z = playerStatus->pos.z;
                        PartnerCurrentScript = start_script(ActivePartner->update, EVT_PRIORITY_14, EVT_FLAG_RUN_IMMEDIATELY);
                        PartnerCurrentScript->owner2.npc = gPartnerNpc;
                        PartnerCurrentScriptID = PartnerCurrentScript->id;
                        PartnerCurrentScript->groupFlags = EVT_GROUP_PASSIVE_NPC;
                    }
                    enable_player_input();
                    CurPartnerCommand = PARTNER_CMD_CLEAR;
                    break;
            }
            break;
        case PARTNER_CMD_ABORT:
            if (PartnerCommandState == 0) {
                if (does_script_exist(PartnerCurrentScriptID)) {
                    kill_script_by_ID(PartnerCurrentScriptID);
                }
                PartnerCommandState++;
            }
            break;
        case PARTNER_CMD_CLEAR:
            CurPartnerCommand = PARTNER_CMD_NONE;
            PartnerCommandPending = false;
            if (PartnerCommandTransitionState != PARTNER_SPAWN_SWITCH) {
                PartnerCommandTransitionState = PARTNER_SPAWN_NONE;
            }
            break;
    }
}

void switch_to_partner(s32 partnerID) {
    PlayerStatus* playerStatus = &gPlayerStatus;

    if (CurrentPartnerID != partnerID) {
        PartnerCommandPending = true;
        NextPartnerID = partnerID;

        if (CurrentPartnerID != PARTNER_NONE && partnerID != PARTNER_NONE) {
            NextPartnerCommand = PARTNER_CMD_SWITCH;
        } else if (partnerID == PARTNER_NONE) {
            NextPartnerCommand = PARTNER_CMD_PUT_AWAY;
        } else {
            NextPartnerCommand = PARTNER_CMD_TAKE_OUT;
            SavedPartnerPos.x = playerStatus->pos.x;
            SavedPartnerPos.y = playerStatus->pos.y;
            SavedPartnerPos.z = playerStatus->pos.z;
        }
    }
}

void partner_init_after_battle(s32 partnerID) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    PartnerStatus* partnerStatus = &gPartnerStatus;

    if (CurrentPartnerID != partnerID) {
        PartnerCommandPending = true;
        NextPartnerID = partnerID;
        partnerStatus->partnerActionState = 0;
        partnerStatus->shouldResumeAbility = false;

        if (CurrentPartnerID != PARTNER_NONE && partnerID != PARTNER_NONE) {
            NextPartnerCommand = PARTNER_CMD_INSTA_SWITCH;
        } else if (partnerID == PARTNER_NONE) {
            NextPartnerCommand = PARTNER_CMD_PUT_AWAY;
        } else {
            NextPartnerCommand = PARTNER_CMD_TAKE_OUT;
            SavedPartnerPos.x = playerStatus->pos.x;
            SavedPartnerPos.y = playerStatus->pos.y;
            SavedPartnerPos.z = playerStatus->pos.z;
        }
    }
}

void partner_switch_to_partner_instant(s32 partnerID) {
    if (CurrentPartnerID != partnerID) {
        PartnerCommandPending = true;
        NextPartnerID = partnerID;

        if (CurrentPartnerID != PARTNER_NONE && partnerID != PARTNER_NONE) {
            NextPartnerCommand = PARTNER_CMD_SWITCH;
        } else if (partnerID == PARTNER_NONE) {
            NextPartnerCommand = PARTNER_CMD_INSTA_PUT_AWAY;
        } else {
            NextPartnerCommand = PARTNER_CMD_INSTA_TAKE_OUT;
        }
    }
}

s32 partner_use_ability(void) {
    PartnerStatus* partnerStatus = &gPartnerStatus;

    if (!is_starting_conversation()
        && ActivePartner != nullptr
        && (ActivePartner->canUseAbility == nullptr || ActivePartner->canUseAbility(gPartnerNpc)))
    {
        if (gGameStatusPtr->multiplayerEnabled && (partnerStatus->curButtons & BUTTON_B)) {
            sfx_play_sound(SOUND_MENU_ERROR);
        } else if (CurrentPartnerID != PARTNER_NONE) {
            PartnerCommandPending = true;
            NextPartnerCommand = PARTNER_CMD_USE_ABILITY;
            process_partner_commands();
            return true;
        }
    }
    return false;
}

s32 partner_can_open_world_menus(void) {
    if (ActivePartner != nullptr
        && ActivePartner->canPlayerOpenMenus != nullptr
        && !ActivePartner->canPlayerOpenMenus(gPartnerNpc)
    ) {
        return false;
    }
    return true;
}

s32 partner_can_use_ability(void) {
    if (ActivePartner->canUseAbility != nullptr && !ActivePartner->canUseAbility(gPartnerNpc)) {
        return true;
    }
    return false;
}

void partner_reset_data(void) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    s32 currentPartner = gPlayerData.curPartner;

    mem_clear(&gPartnerStatus, sizeof(gPartnerStatus));
    get_worker(create_worker_frontUI(process_partner_commands, nullptr));

    PartnerCommandPending = true;
    NextPartnerCommand = PARTNER_CMD_RESET;
    CurrentPartnerID = currentPartner;

    if (gGameStatusPtr->keepUsingPartnerOnMapChange) {
        gPartnerStatus.partnerActionState = PARTNER_ACTION_USE;
        gGameStatusPtr->keepUsingPartnerOnMapChange = false;
    }

    ActivePartner = nullptr;
    SavedPartnerPos.x = playerStatus->pos.x;
    SavedPartnerPos.y = playerStatus->pos.y;
    SavedPartnerPos.z = playerStatus->pos.z;

    if (CurrentPartnerID == PARTNER_NONE) {
        NextPartnerCommand = PARTNER_CMD_CLEAR;
    } else {
        create_partner_npc();
        gPartnerNpc->scale.x = 1.0f;
        gPartnerNpc->scale.y = 1.0f;
        gPartnerNpc->scale.z = 1.0f;
        process_partner_commands();
    }
}

void partner_initialize_data(void) {
    PartnerStatus* partnerStatus = &gPartnerStatus;

    CurrentPartnerID = 0;
    PartnerCommandPending = false;
    NextPartnerCommand = PARTNER_CMD_NONE;
    PartnerCommandTransitionState = PARTNER_SPAWN_NONE;
    partnerStatus->actingPartner = 0;
    partnerStatus->inputDisabledCount = 0;
    partnerStatus->shouldResumeAbility = false;
    partnerStatus->partnerActionState = 0;
    partnerStatus->moveWithoutInput = false;
    ActivePartner = nullptr;
    SavedPartnerPos.x = 0;
    SavedPartnerPos.y = 0;
    SavedPartnerPos.z = 0;
}

s32 partner_test_enemy_collision(Npc* enemy) {
    if (CurrentPartnerID != PARTNER_NONE && ActivePartner->testFirstStrike != nullptr) {
        return ActivePartner->testFirstStrike(gPartnerNpc, enemy);
    }
    return false;
}

EvtScript* partner_get_enter_map_script(void) {
    WorldPartner* partner = ActivePartner;

    if (partner == nullptr) {
        return nullptr;
    }
    return partner->onEnterMap;
}

void partner_handle_before_battle(void) {
    if (CurrentPartnerID != PARTNER_NONE) {
        s32* scriptID = &PartnerCurrentScriptID;

        if (does_script_exist(*scriptID)) {
            kill_script_by_ID(*scriptID);
        }

        if (ActivePartner->preBattle != nullptr) {
            ActivePartner->preBattle(gPartnerNpc);
        }
    }
}

void partner_handle_after_battle(void) {
    PartnerStatus* partnerStatus = &gPartnerStatus;
    PlayerData* playerData = &gPlayerData;

    if (CurrentPartnerID != PARTNER_NONE) {
        if (does_script_exist(PartnerCurrentScriptID) != 0) {
            kill_script_by_ID(PartnerCurrentScriptID);
        }

        PartnerCurrentScript = start_script(ActivePartner->update, EVT_PRIORITY_14, EVT_FLAG_RUN_IMMEDIATELY);
        PartnerCurrentScript->owner2.npc = gPartnerNpc;
        PartnerCurrentScriptID = PartnerCurrentScript->id;
        PartnerCurrentScript->groupFlags = EVT_GROUP_PASSIVE_NPC;

        NextPartnerCommand = PARTNER_CMD_CLEAR;

        if (playerData->curPartner != PARTNER_WATT && partnerStatus->actingPartner == PARTNER_WATT) {
            gPlayerStatusPtr->animFlags &= ~PA_FLAG_USING_WATT;
            gPlayerStatusPtr->animFlags &= ~PA_FLAG_WATT_IN_HANDS;
            partnerStatus->actingPartner = PARTNER_NONE;
        }

        if (ActivePartner->postBattle != nullptr) {
            ActivePartner->postBattle(gPartnerNpc);
        }
    }
}

void partner_kill_ability_script(void) {
    NextPartnerCommand = PARTNER_CMD_ABORT;

    if (does_script_exist(PartnerCurrentScriptID)) {
        kill_script_by_ID(PartnerCurrentScriptID);
    }
}

void partner_suspend_ability_script(void) {
    if (CurrentPartnerID != PARTNER_NONE) {
        if (does_script_exist(PartnerCurrentScriptID)) {
            suspend_all_script(PartnerCurrentScriptID);
        }
    }
}

void partner_resume_ability_script(void) {
    if (CurrentPartnerID != PARTNER_NONE) {
        if (does_script_exist(PartnerCurrentScriptID)) {
            resume_all_script(PartnerCurrentScriptID);
        }
    }
}

void partner_walking_enable(Npc* partner, s32 val) {
    s32 i;

    partner->pos.x = SavedPartnerPos.x;
    partner->pos.y = SavedPartnerPos.y;
    partner->pos.z = SavedPartnerPos.z;

    for (i = 0; i < ARRAY_COUNT(PlayerMoveHistory); i++) {
        PlayerMoveHistory[i].pos.x = gPlayerStatus.pos.x;
        PlayerMoveHistory[i].pos.y = gPlayerStatus.pos.y;
        PlayerMoveHistory[i].pos.z = gPlayerStatus.pos.z;
        PlayerMoveHistory[i].isJumping = false;
    }

    PlayerMoveHistoryIndex = 0;
    PartnerMoveHistoryReadIndex = 0;
    if (val) {
        PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_ONCE;
    } else {
        PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
    }
    PartnerFollowState = PARTNER_MOVE_FOLLOW_PLAYER;

    switch (PartnerCommandTransitionState) {
        case PARTNER_SPAWN_RESET:
        case PARTNER_SPAWN_SWITCH:
            PartnerCommandTransitionState = PARTNER_SPAWN_NONE;
            PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
            PartnerFollowState = PARTNER_MOVE_FOLLOW_PLAYER;
            break;
        case PARTNER_SPAWN_INSTA:
            PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
            PartnerFollowState = PARTNER_MOVE_DISABLED;
            break;
    }

    PartnerFollowSubstate = 0;
    PartnerMoveTime = 16;
    PartnerTetherDistance = 40.0f;
    partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
    partner_clear_collision_flags(partner);
    partner->collisionChannel = COLLIDER_FLAG_IGNORE_PLAYER;
    partner->jumpVel = 0.0f;
    partner->flags |= NPC_FLAG_TOUCHES_GROUND | NPC_FLAG_GRAVITY | NPC_FLAG_IGNORE_CHAR_COLLISION;
    partner->jumpScale = 1.8f;
}

void partner_walking_update_player_tracking(Npc* partner) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    s32 isPlayerJumping;
    PlayerPathElement* currentSnapshot;

    if (playerStatus->flags & (PS_FLAG_FALLING | PS_FLAG_JUMPING)) {
        isPlayerJumping = (playerStatus->actionState == ACTION_STATE_LAND || playerStatus->actionState == ACTION_STATE_STEP_DOWN) ^ 1;
    } else {
        isPlayerJumping = false;
    }
    currentSnapshot = &PlayerMoveHistory[PlayerMoveHistoryIndex];
    if ((!currentSnapshot->isJumping || !isPlayerJumping) &&
        ((currentSnapshot->pos.x != playerStatus->pos.x) || (currentSnapshot->pos.y != playerStatus->pos.y)
        || (currentSnapshot->pos.z != playerStatus->pos.z))) {
        if (PartnerMoveHistoryReadIndex != PlayerMoveHistoryIndex + 1) {
            if (++PlayerMoveHistoryIndex >= ARRAY_COUNT(PlayerMoveHistory)) {
                PlayerMoveHistoryIndex = 0;
            }
            currentSnapshot = &PlayerMoveHistory[PlayerMoveHistoryIndex];
            currentSnapshot->pos.x = playerStatus->pos.x;
            currentSnapshot->pos.y = playerStatus->pos.y;
            currentSnapshot->pos.z = playerStatus->pos.z;
            currentSnapshot->isJumping = isPlayerJumping;
        }
    }
}

void partner_walking_update_motion(Npc* partner) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    PartnerStatus* partnerStatus = &gPartnerStatus;

    if (!gGameStatusPtr->multiplayerEnabled
        || playerStatus->flags & (PS_FLAG_INPUT_DISABLED | PS_FLAG_NO_STATIC_COLLISION)
        || partnerStatus->inputDisabledCount != 0
        || partnerStatus->moveWithoutInput
    ) {
        if (!(playerStatus->animFlags & PA_FLAG_OPENED_HIDDEN_PANEL)) {
            partner_walking_follow_player(partner);
        }
        if (partnerStatus->pressedButtons & (BUTTON_Z | BUTTON_B | BUTTON_C_LEFT | BUTTON_C_DOWN)) {
            partnerStatus->moveWithoutInput = false;
        }
    }

    if (PartnerFollowState != PARTNER_MOVE_DISABLED && fabsf(partner->pos.y - playerStatus->pos.y) > 1000.0f) {
        partner->pos.x = playerStatus->pos.x;
        partner->pos.y = playerStatus->pos.y;
        partner->pos.z = playerStatus->pos.z;
        partner->jumpVel = 0.0f;
        partner->jumpScale = 0.0f;
        partner->flags = partner->flags & ~PA_FLAG_OPENED_HIDDEN_PANEL;
    }

    partner_do_player_collision(partner);
    SavedPartnerPos.x = partner->pos.x;
    SavedPartnerPos.y = partner->pos.y;
    SavedPartnerPos.z = partner->pos.z;
}

void partner_walking_follow_player(Npc* partner) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    Camera* cameras = &gCameras[CAM_DEFAULT];
    s32 surfaceType;
    f32 moveHistoryX, moveHistoryY, moveHistoryZ;
    f32 x, y, z;
    f32 distance;
    f32 yaw;
    f32 temp_a3;
    f32 angle;
    PlayerPathElement* currentSnapshot;

    switch (PartnerFollowState) {
        case PARTNER_MOVE_FOLLOW_PLAYER:
            currentSnapshot = &PlayerMoveHistory[PartnerMoveHistoryReadIndex];
            moveHistoryX = currentSnapshot->pos.x;
            moveHistoryZ = currentSnapshot->pos.z;
            x = partner->pos.x;
            y = partner->pos.y;
            z = partner->pos.z;
            partner->moveSpeed = 3.0f;

            distance = dist2D(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
            if (distance >= 50.0) {
                partner->moveSpeed = !(playerStatus->animFlags & PA_FLAG_SPINNING) ? 5.0f : 7.0f;
            }
            if (PartnerTetherDistance < 20.0) {
                partner->moveSpeed = 4.0f;
            }
            partner->curAnim = gPartnerAnimations[CurrentPartnerID].run;
            if (!(partner->flags & NPC_FLAG_GROUNDED)) {
                partner->curAnim = gPartnerAnimations[CurrentPartnerID].fall;
            }
            while (true) {
                distance = dist2D(x, z, moveHistoryX, moveHistoryZ);
                yaw = atan2(x, z, moveHistoryX, moveHistoryZ);
                if (partner->moveSpeed < distance) {
                    distance = dist2D(x, z, playerStatus->pos.x, playerStatus->pos.z);
                    if (distance >= 50.0) {
                        break;
                    }
                    if (PartnerTetherDistance < distance) {
                        partner->moveSpeed = distance - PartnerTetherDistance;
                        if (partner->moveSpeed > 3.0) {
                            partner->moveSpeed = 3.0f;
                            if (PartnerTetherDistance < 20.0f) {
                                partner->moveSpeed = 4.0f;
                            }
                        } else {
                            partner->moveSpeed += 1.0;
                        }
                        break;
                    } else {
                        partner->moveSpeed = 0.0f;
                        partner->yaw = atan2(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
                    }
                }
                if (PartnerMoveHistoryReadIndex == PlayerMoveHistoryIndex) {
                    yaw = partner->yaw;
                    partner->moveSpeed = 0.0f;
                    partner->jumpScale = 0.0f;
                    PartnerFollowState = PARTNER_MOVE_IDLE_NEAR_PLAYER;
                    partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
                    break;
                } else {
                    PartnerMoveHistoryReadIndex++;
                    if (PartnerMoveHistoryReadIndex >= ARRAY_COUNT(PlayerMoveHistory)) {
                        PartnerMoveHistoryReadIndex = 0;
                    }
                    currentSnapshot = &PlayerMoveHistory[PartnerMoveHistoryReadIndex];
                    moveHistoryX = currentSnapshot->pos.x;
                    moveHistoryZ = currentSnapshot->pos.z;

                    if (fabsf(get_clamped_angle_diff(partner->yaw, atan2(partner->pos.x, partner->pos.z, moveHistoryX, moveHistoryZ))) > 90.0f) {
                        PartnerFollowState = PARTNER_MOVE_IDLE_NEAR_PLAYER;
                        break;
                    }

                    if ((partner->flags & NPC_FLAG_GROUNDED) && currentSnapshot->isJumping) {
                        PartnerFollowState = PARTNER_MOVE_BEGIN_JUMP;
                        break;
                    }
                }
            }

            if (!(partner->flags & NPC_FLAG_GROUNDED)) {
                partner->moveSpeed *= 0.5f;
            }
            partner->yaw = yaw;
            npc_move_heading(partner, partner->moveSpeed, partner->yaw);
            npc_surface_spawn_fx(partner, (partner->moveSpeed < 4.0) ? SURFACE_INTERACT_WALK : SURFACE_INTERACT_RUN);
            surfaceType = get_collider_flags(partner->curFloor);
            if (surfaceType == SURFACE_TYPE_SPIKES
                || surfaceType == SURFACE_TYPE_LAVA
                || ((partner->flags & NPC_FLAG_GROUNDED) && (partner->flags & NPC_FLAG_COLLIDING_FORWARD_WITH_WORLD))
            ) {
                if (!partner_can_move_over_collider(partner->curWall)) {
                    PartnerMoveHistoryReadIndex++;
                    if (PartnerMoveHistoryReadIndex >= ARRAY_COUNT(PlayerMoveHistory)) {
                        PartnerMoveHistoryReadIndex = 0;
                    }
                    currentSnapshot = &PlayerMoveHistory[PartnerMoveHistoryReadIndex];
                    moveHistoryX = currentSnapshot->pos.x;
                    moveHistoryZ = currentSnapshot->pos.z;
                    if (fabsf(get_clamped_angle_diff(partner->yaw, atan2(partner->pos.x, partner->pos.z, moveHistoryX, moveHistoryZ))) > 90.0f) {
                        PartnerFollowState = PARTNER_MOVE_IDLE_NEAR_PLAYER;
                        return;
                    }
                } else {
                    PartnerFollowState = PARTNER_MOVE_BEGIN_JUMP;
                    return;
                }
            }
            break;
        case PARTNER_MOVE_BEGIN_JUMP:
            surfaceType = get_collider_flags(partner->curFloor);
            if (PartnerMoveHistoryReadIndex == PlayerMoveHistoryIndex) {
                if (surfaceType == SURFACE_TYPE_SPIKES || surfaceType == SURFACE_TYPE_LAVA) {
                    moveHistoryX = partner->pos.x;
                    moveHistoryY = playerStatus->pos.y;
                    moveHistoryZ = partner->pos.z;
                    add_vec2D_polar(&moveHistoryX, &moveHistoryZ, 6.0f, atan2(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z));
                } else {
                    break;
                }
            } else {
                PartnerMoveHistoryReadIndex++;
                if (PartnerMoveHistoryReadIndex >= ARRAY_COUNT(PlayerMoveHistory)) {
                    PartnerMoveHistoryReadIndex = 0;
                }
                currentSnapshot = &PlayerMoveHistory[PartnerMoveHistoryReadIndex];
                moveHistoryX = currentSnapshot->pos.x;
                moveHistoryY = currentSnapshot->pos.y;
                moveHistoryZ = currentSnapshot->pos.z;
            }
            partner->moveToPos.x = moveHistoryX;
            partner->moveToPos.y = moveHistoryY;
            partner->moveToPos.z = moveHistoryZ;
            partner->duration = 0;
            partner->jumpScale = 3.0f;
            partner->moveSpeed = 6.0f;
            partner->planarFlyDist = dist2D(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
            partner->yaw = atan2(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
            if (partner->planarFlyDist > 50.0) {
                partner->planarFlyDist = 50.0f;
            }
            distance = partner->planarFlyDist;
            y = partner->moveToPos.y - partner->pos.y;
            if (distance < PartnerTetherDistance && !(surfaceType == SURFACE_TYPE_SPIKES || surfaceType == SURFACE_TYPE_LAVA)) {
                partner->jumpVel = 0.0f;
                partner->yaw = atan2(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
                PartnerFollowState = PARTNER_MOVE_FOLLOW_PLAYER;
                return;
            }
            partner->duration = distance / partner->moveSpeed;
            if (partner->duration < 10) {
                partner->duration = 10;
            }
            partner->moveSpeed = partner->planarFlyDist / partner->duration;
            partner->jumpVel = (y + partner->jumpScale * partner->duration * partner->duration * 0.5f) / partner->duration;
            if (partner->jumpVel > 20.0) {
                partner->jumpVel = 20.0f;
            }
            if (partner->jumpVel < 0.0) {
                partner->jumpVel = 0.0f;
            }
            if (!(surfaceType == SURFACE_TYPE_SPIKES || surfaceType == SURFACE_TYPE_LAVA)) {
                partner->curAnim = gPartnerAnimations[CurrentPartnerID].jump;
            } else {
                partner->curAnim = gPartnerAnimations[CurrentPartnerID].hurt;
            }

            partner->moveToPos.x = partner->pos.x;
            partner->moveToPos.y = partner->pos.y;
            partner->moveToPos.z = partner->pos.z;
            partner->flags |= NPC_FLAG_JUMPING;
            PartnerFollowState = PARTNER_MOVE_JUMPING;
            // fallthrough
        case PARTNER_MOVE_JUMPING:
            partner->jumpVel -= partner->jumpScale;
            partner->pos.y += partner->jumpVel;
            if (partner->jumpVel <= 0.0f) {
                partner->curAnim = gPartnerAnimations[CurrentPartnerID].fall;
            }
            if (partner->pos.y < -2000.0f) {
                partner->curAnim = gPartnerAnimations[CurrentPartnerID].fly;
                partner->flags &= ~NPC_FLAG_JUMPING;
                partner->jumpVel = 0.0f;
                partner->yaw = atan2(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
                partner->pos.x = playerStatus->pos.x;
                partner->pos.y = playerStatus->pos.y;
                partner->pos.z = playerStatus->pos.z;
                PartnerFollowState = PARTNER_MOVE_IDLE_NEAR_PLAYER;
                return;
            }
            if (partner->jumpVel <= 0.0f) {
                distance = fabsf(partner->jumpVel) + 11.0f;
                x = partner->pos.x;
                y = partner->pos.y + distance;
                z = partner->pos.z;
                if (npc_raycast_down_around(partner->collisionChannel, &x, &y, &z, &distance, partner->yaw, partner->collisionDiameter) != 0) {
                    if (distance <= fabsf(partner->jumpVel) + 22.0f) {
                        partner->curAnim = gPartnerAnimations[CurrentPartnerID].fly;
                        partner->flags &= ~NPC_FLAG_JUMPING;
                        partner->jumpVel = 0.0f;
                        partner->pos.y = y;
                        partner->yaw = atan2(x, z, playerStatus->pos.x, playerStatus->pos.z);
                        npc_surface_spawn_fx(partner, SURFACE_INTERACT_LAND);
                        PartnerFollowState = PARTNER_MOVE_FOLLOW_PLAYER;
                        distance = dist2D(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
                        if (distance < 5.0) {
                            partner->pos.x = playerStatus->pos.x;
                            partner->pos.y = playerStatus->pos.y;
                            partner->pos.z = playerStatus->pos.z;
                            add_vec2D_polar(&partner->pos.x, &partner->pos.z, 5.0f, clamp_angle((cameras[CAM_DEFAULT].curYaw + 90.0f) - playerStatus->spriteFacingAngle));
                            PartnerFollowState = PARTNER_MOVE_IDLE_NEAR_PLAYER;
                        }
                        break;
                    }
                }
            }
            npc_move_heading(partner, partner->moveSpeed, partner->yaw);
            break;
        case PARTNER_MOVE_IDLE_NEAR_PLAYER:
            currentSnapshot = &PlayerMoveHistory[PartnerMoveHistoryReadIndex];
            moveHistoryX = currentSnapshot->pos.x;
            moveHistoryZ = currentSnapshot->pos.z;
            x = partner->pos.x;
            y = partner->pos.y;
            z = partner->pos.z;
            distance = dist2D(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
            if (distance <= PartnerTetherDistance) {
                if (PartnerForcedFollowMode == PARTNER_FORCED_FOLLOW_NONE) {
                    partner->moveSpeed = 0.0f;
                    partner->jumpScale = 0.0f;
                    partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
                    if (playerStatus->actionState == ACTION_STATE_TALK) {
                        PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
                    }
                    surfaceType = get_collider_flags(partner->curFloor);
                    if (surfaceType == SURFACE_TYPE_SPIKES || surfaceType == SURFACE_TYPE_LAVA) {
                        PartnerFollowState = PARTNER_MOVE_FOLLOW_PLAYER;
                        return;
                    }
                } else {
                    temp_a3 = clamp_angle(cameras[CAM_DEFAULT].curYaw + (playerStatus->spriteFacingAngle < 180.0f ? 90.0f : -90.0f));
                    partner->moveToPos.x = playerStatus->pos.x;
                    partner->moveToPos.y = playerStatus->pos.y;
                    partner->moveToPos.z = playerStatus->pos.z;
                    add_vec2D_polar(&partner->moveToPos.x, &partner->moveToPos.z, PartnerTetherDistance - 10.0f, temp_a3);
                    yaw = atan2(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
                    distance = dist2D(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
                    partner->moveSpeed = 2.0f;
                    if (distance > 2.0f) {
                        partner->yaw = yaw;
                        partner->curAnim = gPartnerAnimations[CurrentPartnerID].run;
                        if (!(partner->flags & NPC_FLAG_COLLIDING_FORWARD_WITH_WORLD)) {
                            PartnerStuckTime = 0;
                        } else {
                            PartnerStuckTime++;
                            if (PartnerStuckTime > 10) {
                                yaw = playerStatus->targetYaw;
                                partner->moveSpeed = 0.0f;
                                partner->jumpScale = 0.0f;
                                partner->renderYaw = yaw;
                                partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
                                if (PartnerForcedFollowMode == PARTNER_FORCED_FOLLOW_ONCE || playerStatus->actionState == ACTION_STATE_TALK) {
                                    PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
                                }
                            }
                        }
                    } else {
                        yaw = atan2(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
                        partner->yaw = yaw;
                        partner->moveSpeed = 0.0f;
                        partner->jumpScale = 0.0f;
                        partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
                        if (PartnerForcedFollowMode == PARTNER_FORCED_FOLLOW_ONCE || playerStatus->actionState == ACTION_STATE_TALK) {
                            PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
                        }
                    }
                    partner->yaw = yaw;
                    npc_move_heading(partner, partner->moveSpeed, yaw);
                    npc_surface_spawn_fx(partner, (partner->moveSpeed < 4.0) ? SURFACE_INTERACT_WALK : SURFACE_INTERACT_RUN);
                    distance = 1000.0f;
                    x = partner->pos.x;
                    z = partner->pos.z;
                    y = partner->pos.y + partner->collisionHeight;
                    if (npc_raycast_down_around(partner->collisionChannel, &x, &y, &z, &distance, partner->yaw, partner->collisionDiameter) != 0) {
                        s32 surfaceType = get_collider_flags(NpcHitQueryColliderID);
                        if (surfaceType == SURFACE_TYPE_SPIKES || surfaceType == SURFACE_TYPE_LAVA) {
                            partner->yaw = clamp_angle(yaw + 180.0f);
                            npc_move_heading(partner, partner->moveSpeed, partner->yaw);
                            partner->moveSpeed = 0.0f;
                            partner->jumpScale = 0.0f;
                            partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
                            if (PartnerForcedFollowMode == PARTNER_FORCED_FOLLOW_ONCE) {
                                PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
                            } else if (playerStatus->actionState == ACTION_STATE_TALK) {
                                PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
                            }
                        } else if (!partner_can_move_over_collider(NpcHitQueryColliderID)) {
                            PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_ONCE;
                        }
                    }
                    break;
                }
            }
            distance = dist2D(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
            if (distance <= PartnerTetherDistance) {
                if (!partner_can_move_over_collider(NpcHitQueryColliderID)) {
                    PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_ONCE;
                }
            } else {
                while (true) {
                    if (currentSnapshot->isJumping) {
                        break;
                    }
                    yaw = atan2(partner->pos.x, partner->pos.z, moveHistoryX, moveHistoryZ);
                    if (fabsf(get_clamped_angle_diff(yaw, atan2(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z))) < 90.0f) {
                        break;
                    }
                    if (PartnerMoveHistoryReadIndex == PlayerMoveHistoryIndex) {
                        break;
                    }
                    PartnerMoveHistoryReadIndex++;
                    if (PartnerMoveHistoryReadIndex >= ARRAY_COUNT(PlayerMoveHistory)) {
                        PartnerMoveHistoryReadIndex = 0;
                    }
                    currentSnapshot = &PlayerMoveHistory[PartnerMoveHistoryReadIndex];
                    moveHistoryX = currentSnapshot->pos.x;
                    moveHistoryZ = currentSnapshot->pos.z;
                }
                if (!currentSnapshot->isJumping) {
                    PartnerFollowState = PARTNER_MOVE_FOLLOW_PLAYER;
                    return;
                }
                while (true) {
                    if (!currentSnapshot->isJumping) {
                        break;
                    }
                    yaw = atan2(partner->pos.x, partner->pos.z, moveHistoryX, moveHistoryZ);
                    if (fabsf(get_clamped_angle_diff(yaw, atan2(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z))) < 90.0f) {
                        break;
                    }
                    if (PartnerMoveHistoryReadIndex == PlayerMoveHistoryIndex) {
                        break;
                    }
                    PartnerMoveHistoryReadIndex++;
                    if (PartnerMoveHistoryReadIndex >= ARRAY_COUNT(PlayerMoveHistory)) {
                        PartnerMoveHistoryReadIndex = 0;
                    }
                    currentSnapshot = &PlayerMoveHistory[PartnerMoveHistoryReadIndex];
                    moveHistoryX = currentSnapshot->pos.x;
                    moveHistoryZ = currentSnapshot->pos.z;
                }
                PartnerFollowState = PARTNER_MOVE_BEGIN_JUMP;
                return;
            }
            break;
        case PARTNER_MOVE_TO_SIDE:
            switch (PartnerFollowSubstate) {
                case 0:
                    angle = clamp_angle(player_get_side_angle() + 180.0f);
                    partner->moveToPos.x = playerStatus->pos.x;
                    partner->moveToPos.y = playerStatus->pos.y;
                    partner->moveToPos.z = playerStatus->pos.z;
                    add_vec2D_polar(&partner->moveToPos.x, &partner->moveToPos.z, playerStatus->colliderDiameter, angle);
                    distance = dist2D(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
                    PartnerMoveSpeed = distance / PartnerMoveTime;
                    partner->moveSpeed = PartnerMoveSpeed;
                    partner->curAnim = gPartnerAnimations[CurrentPartnerID].anims[PartnerMoveSpeed >= 4.0 ? PARTNER_ANIM_INDEX_RUN : PARTNER_ANIM_INDEX_WALK];
                    yaw = atan2(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
                    partner->yaw = PartnerMoveYaw = yaw;
                    PartnerFollowSubstate++;
                    // fallthrough
                case 1:
                    if (PartnerMoveTime != 0) {
                        PartnerMoveTime--;
                        if (partner->jumpScale != 0.0f) {
                            partner->jumpVel -= partner->jumpScale;
                            partner->pos.y += partner->jumpVel;
                            if (partner->jumpVel <= 0.0f) {
                                partner->curAnim = gPartnerAnimations[CurrentPartnerID].fall;
                            }
                            if (partner->jumpVel <= 0.0f) {
                                distance = fabsf(partner->jumpVel) + 11.0f;
                                x = partner->pos.x;
                                y = partner->pos.y + distance;
                                z = partner->pos.z;
                                if ((npc_raycast_down_around(partner->collisionChannel, &x, &y, &z, &distance, partner->yaw, partner->collisionDiameter) != 0) && (distance <= (fabsf(partner->jumpVel) + 22.0f))) {
                                    partner->curAnim = gPartnerAnimations[CurrentPartnerID].anims[partner->moveSpeed >= 4.0 ? PARTNER_ANIM_INDEX_RUN : PARTNER_ANIM_INDEX_WALK];
                                    partner->jumpScale = 0.0f;
                                    partner->jumpVel = 0.0f;
                                    partner->pos.y = y;
                                    partner->flags &= ~NPC_FLAG_JUMPING;
                                }
                            }
                        }
                        partner->moveSpeed = PartnerMoveSpeed;
                        partner->yaw = PartnerMoveYaw;
                        npc_move_heading(partner, partner->moveSpeed, partner->yaw);
                        npc_surface_spawn_fx(partner, (partner->moveSpeed < 4.0) ? SURFACE_INTERACT_WALK : SURFACE_INTERACT_RUN);
                    } else {
                        partner_clear_player_tracking(partner);
                        partner->moveSpeed = 0.0f;
                        partner->jumpScale = 0.0f;
                        partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
                        partner->yaw = clamp_angle((cameras[CAM_DEFAULT].curYaw + 270.0f) - playerStatus->spriteFacingAngle);
                        PartnerMoveTime = 30;
                        PartnerFollowSubstate++;
                    }
                    return;
                case 2:
                    if (PartnerMoveTime != 0) {
                        PartnerMoveTime--;
                        return;
                    }
                    PartnerFollowState = PARTNER_MOVE_FOLLOW_PLAYER;
                    PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
                    PartnerFollowSubstate = 0;
            }
            break;
        case PARTNER_MOVE_TO_GOAL:
            partner_move_to_goal(partner, false);
            break;
        case PARTNER_MOVE_DISABLE_ASAP:
            if (partner->flags & NPC_FLAG_GROUNDED) {
                if (partner_can_move_over_collider(partner->curFloor)) {
                    PartnerFollowState = PARTNER_MOVE_DISABLED;
                    partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
                } else {
                    PartnerFollowState = PARTNER_MOVE_BEGIN_JUMP;
                }
                break;
            }
            partner->jumpScale = 3.0f;
            partner->jumpVel -= partner->jumpScale;
            partner->pos.y += partner->jumpVel;
            if (partner->jumpVel <= 0.0f) {
                partner->curAnim = gPartnerAnimations[CurrentPartnerID].fall;
            }
            if (partner->pos.y < -2000.0f) {
                partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
                partner->flags &= ~NPC_FLAG_JUMPING;
                partner->jumpVel = 0.0f;
                partner->yaw = atan2(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
                partner->pos.x = playerStatus->pos.x;
                partner->pos.y = playerStatus->pos.y;
                partner->pos.z = playerStatus->pos.z;
                PartnerFollowState = PARTNER_MOVE_DISABLED;
                return;
            }
            distance = fabsf(partner->jumpVel) + 11.0f;
            x = partner->pos.x;
            y = partner->pos.y + distance;
            z = partner->pos.z;
            if (npc_raycast_down_around(partner->collisionChannel, &x, &y, &z, &distance, partner->yaw, partner->collisionDiameter) != 0) {
                partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
                partner->flags &= ~NPC_FLAG_JUMPING;
                partner->jumpVel = 0.0f;
                partner->pos.y = y;
                partner->yaw = atan2(x, z, playerStatus->pos.x, playerStatus->pos.z);
                npc_surface_spawn_fx(partner, SURFACE_INTERACT_LAND);
                PartnerFollowState = PARTNER_MOVE_DISABLED;
            }
            break;
        case PARTNER_MOVE_DISABLED:
            break;
    }
}

void partner_flying_enable(Npc* partner, s32 val) {
    s32 i;

    partner->pos.x = SavedPartnerPos.x;
    partner->pos.y = SavedPartnerPos.y;
    partner->pos.z = SavedPartnerPos.z;

    for (i = 0; i < ARRAY_COUNT(PlayerMoveHistory); i++) {
        PlayerMoveHistory[i].pos.x = SavedPartnerPos.x;
        PlayerMoveHistory[i].pos.y = SavedPartnerPos.y;
        PlayerMoveHistory[i].pos.z = SavedPartnerPos.z;
        PlayerMoveHistory[i].isJumping = false;
    }

    PlayerMoveHistoryIndex = 0;
    PartnerMoveHistoryReadIndex = 0;

    if (!val) {
        PartnerFollowState = PARTNER_MOVE_FOLLOW_PLAYER;
        PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
    } else {
        switch (PartnerCommandTransitionState) {
            case PARTNER_SPAWN_NONE:
                PartnerFollowState = PARTNER_MOVE_TO_SIDE;
                PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_ONCE;
                break;
            case PARTNER_SPAWN_RESET:
            case PARTNER_SPAWN_SWITCH:
                PartnerCommandTransitionState = PARTNER_SPAWN_NONE;
                PartnerFollowState = PARTNER_MOVE_FOLLOW_PLAYER;
                PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
                break;
            case PARTNER_SPAWN_INSTA:
                PartnerFollowState = PARTNER_MOVE_DISABLED;
                PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
                break;
        }
    }

    PartnerFollowSubstate = 0;
    PartnerMoveTime = 16;
    PartnerTetherDistance = 40.0f;

    partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
    partner_clear_collision_flags(partner);
    partner->collisionChannel = COLLIDER_FLAG_IGNORE_PLAYER;
    partner->flags |= NPC_FLAG_IGNORE_CHAR_COLLISION;
    partner->flags &= ~NPC_FLAG_GRAVITY;
}

void partner_flying_update_player_tracking(Npc* partner) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    PlayerPathElement* currentSnapshot;
    f32 effectiveY = playerStatus->pos.y;
    b32 isPlayerJumping = false;

    if ((playerStatus->actionState == ACTION_STATE_HIT_LAVA) || (playerStatus->actionState == ACTION_STATE_HIT_FIRE)) {
        effectiveY = playerStatus->lastGoodPos.y + partner->collisionHeight + 5;
    }

    currentSnapshot = &PlayerMoveHistory[PlayerMoveHistoryIndex];

    if (currentSnapshot->pos.x == playerStatus->pos.x
        && currentSnapshot->pos.y == effectiveY
        && currentSnapshot->pos.z == playerStatus->pos.z
    ) {
        return;
    }

    // interesting: isPlayerJumping is always false here
    if (currentSnapshot->isJumping && isPlayerJumping) {
        return;
    }

    if (PartnerMoveHistoryReadIndex == PlayerMoveHistoryIndex + 1) {
        return;
    }

    PlayerMoveHistoryIndex++;
    if (PlayerMoveHistoryIndex >= ARRAY_COUNT(PlayerMoveHistory)) {
        PlayerMoveHistoryIndex = 0;
    }

    currentSnapshot = &PlayerMoveHistory[PlayerMoveHistoryIndex];
    currentSnapshot->pos.x = playerStatus->pos.x;
    currentSnapshot->pos.y = effectiveY;
    currentSnapshot->pos.z = playerStatus->pos.z;
    currentSnapshot->isJumping = isPlayerJumping;
}

void partner_flying_update_motion(Npc* partner) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    PartnerStatus* partnerStatus = &gPartnerStatus;
    f32 x, y, z, hitDepth;
    f32 targetY;

    if (!gGameStatusPtr->multiplayerEnabled
        || (playerStatus->flags & (PS_FLAG_INPUT_DISABLED | PS_FLAG_NO_STATIC_COLLISION))
        || partnerStatus->inputDisabledCount
        || partnerStatus->moveWithoutInput
    ) {
        if (!(playerStatus->animFlags & PA_FLAG_OPENED_HIDDEN_PANEL) || !PartnerBlockedAbove) {
            partner_flying_follow_player(partner);
        }
        if (partnerStatus->pressedButtons & (BUTTON_B | BUTTON_Z | BUTTON_C_DOWN | BUTTON_C_LEFT)) {
            partnerStatus->moveWithoutInput = false;
        }
    }

    if (PartnerFollowState != PARTNER_MOVE_DISABLED && fabsf(partner->pos.y - playerStatus->pos.y) > 1000.0f) {
        partner->pos.x = playerStatus->pos.x;
        partner->pos.y = playerStatus->pos.y;
        partner->pos.z = playerStatus->pos.z;
        partner->jumpVel = 0.0f;
        partner->jumpScale = 0.0f;
        partner->flags &= ~NPC_FLAG_JUMPING;
    }

    PartnerBlockedAbove = false;
    x = partner->pos.x;
    y = partner->pos.y + (partner->collisionHeight * 0.5f);
    z = partner->pos.z;
    hitDepth = partner->collisionHeight * 0.5f;

    if (npc_raycast_up(0, &x, &y, &z, &hitDepth)) {
        PartnerBlockedAbove = true;
        SavedPartnerPos.x = partner->pos.x;
        SavedPartnerPos.y = partner->pos.y;
        SavedPartnerPos.z = partner->pos.z;
        return;
    }

    partner_do_player_collision(partner);

    if (PartnerFollowState == PARTNER_MOVE_DISABLED) {
        SavedPartnerPos.x = partner->pos.x;
        SavedPartnerPos.y = partner->pos.y;
        SavedPartnerPos.z = partner->pos.z;
        return;
    }

    x = partner->pos.x;
    y = partner->pos.y;
    z = partner->pos.z;
    hitDepth = 1000.0f;

    if (npc_raycast_down_around(COLLIDER_FLAG_IGNORE_PLAYER, &x, &y, &z, &hitDepth, partner->yaw, partner->collisionDiameter) == 0) {
        y = playerStatus->pos.y;
    }

    if (partner->pos.y <= y + partner->collisionHeight + 2.0f) {
        if (playerStatus->curSpeed != 0.0f) {
            PartnerFlyingDeltaY = ((y + (partner->collisionHeight / 2) + 2.0f) - partner->pos.y) * 0.125f;
        } else {
            if (y < playerStatus->pos.y) {
                targetY = playerStatus->pos.y + 10.0f;
            } else {
                targetY = y + 10.0f;
            }
            PartnerFlyingDeltaY = (targetY - partner->pos.y) * 0.25f;
        }
    } else {
        if (playerStatus->pos.y + playerStatus->colliderHeight < y) {
            targetY = y + partner->collisionHeight;
            PartnerFlyingDeltaY = (targetY - partner->pos.y) * 0.125f;

            if (partner->pos.y + PartnerFlyingDeltaY <= targetY) {
                PartnerFlyingDeltaY = (targetY - partner->pos.y) * 0.25f;
            }
        } else {
            targetY = playerStatus->pos.y + playerStatus->colliderHeight + 5.0f;
            PartnerFlyingDeltaY = (targetY - partner->pos.y) * 0.0625f;
        }
    }

    partner->pos.y += PartnerFlyingDeltaY;
    SavedPartnerPos.x = partner->pos.x;
    SavedPartnerPos.y = partner->pos.y;
    SavedPartnerPos.z = partner->pos.z;
}

void partner_flying_follow_player(Npc* partner) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    Camera* camera = &gCameras[CAM_DEFAULT];
    f32 x, y, z;
    f32 distance;
    f32 yaw;
    f32 temp_a3;
    f32 temp_f0_15;
    f32 var_f12;
    f32 moveHistoryX, moveHistoryY, moveHistoryZ;
    PlayerPathElement* currentSnapshot;

    switch (PartnerFollowState) {
        case PARTNER_MOVE_FOLLOW_PLAYER:
            var_f12 = 0.0f;
            x = partner->pos.x;
            y = partner->pos.y;
            z = partner->pos.z;
            SavedPartnerPos.x = x;
            SavedPartnerPos.y = y;
            SavedPartnerPos.z = z;
            currentSnapshot = &PlayerMoveHistory[PartnerMoveHistoryReadIndex];
            moveHistoryX = currentSnapshot->pos.x;
            moveHistoryY = currentSnapshot->pos.y;
            moveHistoryZ = currentSnapshot->pos.z;
            if (PartnerTetherDistance < 20.0f) {
                var_f12 = (20.0f - PartnerTetherDistance) * 0.5f;
            }
            partner->pos.y = y + (moveHistoryY + 20.0f + var_f12 - y) * 0.125f;
            partner->moveSpeed = 3.0f;
            y = partner->pos.y;
            distance = dist2D(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
            if (distance >= 50.0) {
                if (partner->pos.y >= playerStatus->pos.y) {
                    partner->moveSpeed = distance * 0.25f;
                } else {
                    partner->moveSpeed = 8.0f;
                }
            }
            if (PartnerTetherDistance < 20.0f) {
                partner->moveSpeed = 4.0f;
            }

            while (true) {
                yaw = atan2(x, z, moveHistoryX, moveHistoryZ);
                distance = dist2D(x, z, moveHistoryX, moveHistoryZ);
                if (partner->moveSpeed < distance) {
                    if (partner->pos.y >= playerStatus->pos.y) {
                        if (partner->moveSpeed >= distance * 0.25f) {
                            partner->moveSpeed = distance * 0.25f;
                        } else {
                            partner->moveSpeed += distance * 0.0625f;
                        }
                    } else {
                        if (partner->moveSpeed > 6.0) {
                            partner->moveSpeed = 6.0f;
                        } else {
                            partner->moveSpeed += 1.0;
                        }
                    }
                    break;
                }
                if (PartnerMoveHistoryReadIndex == PlayerMoveHistoryIndex) {
                    yaw = partner->yaw;
                    partner->moveSpeed = 0.0f;
                    partner->jumpScale = 0.0f;
                    partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
                    break;
                }
                distance = dist2D(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
                if (distance <= PartnerTetherDistance) {
                    PartnerFollowState = PARTNER_MOVE_IDLE_NEAR_PLAYER;
                    yaw = partner->yaw;
                    partner->moveSpeed = 0.0f;
                    partner->jumpScale = 0.0f;
                    partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
                    break;
                }
                PartnerMoveHistoryReadIndex++;
                if (PartnerMoveHistoryReadIndex >= ARRAY_COUNT(PlayerMoveHistory)) {
                    PartnerMoveHistoryReadIndex = 0;
                }
                currentSnapshot = &PlayerMoveHistory[PartnerMoveHistoryReadIndex];
                moveHistoryX = currentSnapshot->pos.x;
                moveHistoryZ = currentSnapshot->pos.z;
            }
            partner->yaw = yaw;
            npc_move_heading(partner, partner->moveSpeed, yaw);
            if (partner->flags & NPC_FLAG_COLLIDING_FORWARD_WITH_WORLD) {
                PartnerFollowState = PARTNER_MOVE_BEGIN_JUMP;
                return;
            }
            break;
        case PARTNER_MOVE_BEGIN_JUMP:
            if (PartnerMoveHistoryReadIndex != PlayerMoveHistoryIndex) {
                PartnerMoveHistoryReadIndex++;
                if (PartnerMoveHistoryReadIndex >= ARRAY_COUNT(PlayerMoveHistory)) {
                    PartnerMoveHistoryReadIndex = 0;
                }
                currentSnapshot = &PlayerMoveHistory[PartnerMoveHistoryReadIndex];
                moveHistoryX = currentSnapshot->pos.x;
                moveHistoryY = currentSnapshot->pos.y;
                moveHistoryZ = currentSnapshot->pos.z;
                partner->moveToPos.x = moveHistoryX;
                partner->moveToPos.y = moveHistoryY;
                partner->moveToPos.z = moveHistoryZ;
                partner->duration = 0;
                partner->jumpScale = 1.3f;
                if (PartnerFollowState == PARTNER_MOVE_BEGIN_JUMP) {
                    partner->moveSpeed = 6.0f;
                }
                partner->planarFlyDist = dist2D(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
                partner->yaw = atan2(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
                if (partner->planarFlyDist > 50.0) {
                    partner->planarFlyDist = 50.0f;
                }
                distance = partner->planarFlyDist;
                y = partner->moveToPos.y - partner->pos.y;
                if (partner->planarFlyDist < y) {
                    distance = y;
                }
                if (PartnerFollowState == PARTNER_MOVE_BEGIN_JUMP) {
                    if (distance < PartnerTetherDistance) {
                        partner->jumpVel = 0.0f;
                        partner->yaw = atan2(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
                        PartnerFollowState = PARTNER_MOVE_IDLE_NEAR_PLAYER;
                        return;
                    }
                    partner->duration = distance / partner->moveSpeed;
                    if (partner->duration < 10) {
                        partner->duration = 10;
                    }
                    partner->moveSpeed = partner->planarFlyDist / partner->duration;
                } else {
                    partner->duration = 10;
                }

                partner->jumpVel = (y + (partner->jumpScale * partner->duration * partner->duration * 0.5f)) / partner->duration;
                if (partner->jumpVel > 20.0) {
                    partner->jumpVel = 20.0f;
                }
                PartnerFollowState = PARTNER_MOVE_JUMPING;
                partner->curAnim = gPartnerAnimations[CurrentPartnerID].jump;
                partner->moveToPos.x = partner->pos.x;
                partner->moveToPos.y = partner->pos.y;
                partner->moveToPos.z = partner->pos.z;
            }
            break;
        case PARTNER_MOVE_JUMPING:
            partner->jumpVel -= partner->jumpScale;
            partner->pos.y += partner->jumpVel;
            if (partner->jumpVel <= 0.0f) {
                partner->curAnim = gPartnerAnimations[CurrentPartnerID].fall;
            }
            npc_move_heading(partner, partner->moveSpeed, partner->yaw);
            if (partner->jumpVel <= 0.0f) {
                if (partner->pos.y < partner->moveToPos.y) {
                    partner->curAnim = gPartnerAnimations[CurrentPartnerID].fly;
                    partner->jumpVel = 0.0f;
                    partner->pos.y = partner->moveToPos.y;
                    partner->yaw = atan2(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
                    PartnerFollowState = PARTNER_MOVE_FOLLOW_PLAYER;
                    distance = dist2D(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
                    if (distance < PartnerTetherDistance) {
                        PartnerFollowState = PARTNER_MOVE_TO_SIDE;
                    }
                }
            }
            break;
        case PARTNER_MOVE_IDLE_NEAR_PLAYER:
            x = partner->pos.x;
            y = partner->pos.y;
            z = partner->pos.z;
            currentSnapshot = &PlayerMoveHistory[PartnerMoveHistoryReadIndex];
            moveHistoryX = currentSnapshot->pos.x;
            moveHistoryZ = currentSnapshot->pos.z;
            distance = dist2D(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
            if (distance <= PartnerTetherDistance) {
                if (PartnerForcedFollowMode == PARTNER_FORCED_FOLLOW_NONE) {
                    partner->pos.y = y + (((playerStatus->pos.y + (playerStatus->colliderHeight - partner->collisionHeight / 2)) - partner->pos.y) * 0.03125);
                    y = partner->pos.y;
                    partner->moveSpeed = 0.0f;
                    partner->jumpScale = 0.0f;
                    partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
                    if (playerStatus->actionState == ACTION_STATE_TALK) {
                        PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
                    }
                } else {
                    temp_a3 = clamp_angle(camera->curYaw + (playerStatus->spriteFacingAngle < 180.0f ? 90.0f : -90.0f));
                    partner->moveToPos.x = playerStatus->pos.x;
                    partner->moveToPos.y = playerStatus->pos.y;
                    partner->moveToPos.z = playerStatus->pos.z;
                    add_vec2D_polar(&partner->moveToPos.x, &partner->moveToPos.z, PartnerTetherDistance - 10.0f, temp_a3);
                    yaw = atan2(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
                    distance = dist2D(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
                    partner->moveSpeed = 2.0f;
                    if (distance > 2.0f) {
                        partner->yaw = yaw;
                        partner->curAnim = gPartnerAnimations[CurrentPartnerID].run;
                        if (!(partner->flags & NPC_FLAG_COLLIDING_FORWARD_WITH_WORLD)) {
                            PartnerStuckTime = 0;
                        } else {
                            PartnerStuckTime++;
                            if (PartnerStuckTime > 10) {
                                yaw = playerStatus->targetYaw;
                                partner->moveSpeed = 0.0f;
                                partner->jumpScale = 0.0f;
                                partner->renderYaw = yaw;
                                partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
                                if (PartnerForcedFollowMode == PARTNER_FORCED_FOLLOW_ONCE || playerStatus->actionState == ACTION_STATE_TALK) {
                                    PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
                                }
                            }
                        }
                    } else {
                        yaw = atan2(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
                        partner->yaw = yaw;
                        partner->moveSpeed = 0.0f;
                        partner->jumpScale = 0.0f;
                        partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
                        if (PartnerForcedFollowMode == PARTNER_FORCED_FOLLOW_ONCE || playerStatus->actionState == ACTION_STATE_TALK) {
                            PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
                        }
                    }
                    partner->yaw = yaw;
                    npc_move_heading(partner, partner->moveSpeed, yaw);
                    return;
                }
            }

            distance = dist2D(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z);
            if (!(distance <= PartnerTetherDistance)) {
                while (true) {
                    if (!currentSnapshot->isJumping) {
                        yaw = atan2(partner->pos.x, partner->pos.z, moveHistoryX, moveHistoryZ);
                        if (!(fabsf(get_clamped_angle_diff(yaw, atan2(partner->pos.x, partner->pos.z, playerStatus->pos.x, playerStatus->pos.z))) < 90.0f)) {
                            if (PartnerMoveHistoryReadIndex != PlayerMoveHistoryIndex) {
                                PartnerMoveHistoryReadIndex++;
                                if (PartnerMoveHistoryReadIndex >= ARRAY_COUNT(PlayerMoveHistory)) {
                                    PartnerMoveHistoryReadIndex = 0;
                                }
                                currentSnapshot = &PlayerMoveHistory[PartnerMoveHistoryReadIndex];
                                moveHistoryX = currentSnapshot->pos.x;
                                moveHistoryZ = currentSnapshot->pos.z;
                                continue;
                            }
                        }
                    }
                    break;
                }
                PartnerFollowState = PARTNER_MOVE_FOLLOW_PLAYER;
            }
            break;
        case PARTNER_MOVE_TO_SIDE:
            if (!(playerStatus->animFlags & PA_FLAG_CHANGING_MAP)) {
                switch (PartnerFollowSubstate) {
                    case 0:
                        temp_f0_15 = clamp_angle(player_get_side_angle() + 180.0f);
                        partner->moveToPos.x = playerStatus->pos.x;
                        partner->moveToPos.y = playerStatus->pos.y;
                        partner->moveToPos.z = playerStatus->pos.z;
                        add_vec2D_polar(&partner->moveToPos.x, &partner->moveToPos.z, playerStatus->colliderDiameter, temp_f0_15);
                        distance = dist2D(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
                        partner->moveSpeed = PartnerMoveSpeed = distance / PartnerMoveTime;
                        partner->curAnim = gPartnerAnimations[CurrentPartnerID].anims[(partner->moveSpeed < 4.0) ? PARTNER_ANIM_INDEX_WALK : PARTNER_ANIM_INDEX_RUN];
                        yaw = atan2(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
                        partner->yaw = PartnerMoveYaw = yaw;
                        PartnerFollowSubstate = 1;
                        // fallthrough
                    case 1:
                        if (PartnerMoveTime != 0) {
                            x = partner->pos.x;
                            y = partner->pos.y + partner->collisionHeight;
                            z = partner->pos.z;
                            distance = partner->collisionHeight + 1;
                            PartnerMoveTime--;
                            if (npc_raycast_down_around(COLLIDER_FLAG_IGNORE_PLAYER, &x, &y, &z, &distance, partner->yaw, partner->collisionDiameter) == 0) {
                                if (partner->collisionHeight + 5 < fabs((partner->pos.y - playerStatus->pos.y))) {
                                    partner->pos.y += (playerStatus->pos.y - partner->pos.y) / 10.0f;
                                }
                            } else {
                                partner->pos.y += (((playerStatus->pos.y + playerStatus->colliderHeight) - partner->pos.y) * 0.125f);
                            }
                            partner->moveSpeed = PartnerMoveSpeed;
                            partner->yaw = PartnerMoveYaw;
                            x = partner->pos.x;
                            y = partner->pos.y;
                            z = partner->pos.z;
                            if (npc_test_move_taller_with_slipping(0, &x, &y, &z, partner->moveSpeed, partner->yaw, partner->collisionHeight, partner->collisionDiameter)) {
                                partner->pos.x += (x - partner->pos.x) / 5.0f;
                                partner->pos.z += (z - partner->pos.z) / 5.0f;
                            } else {
                                npc_move_heading(partner, partner->moveSpeed, partner->yaw);
                            }
                            return;
                        }
                        partner_clear_player_tracking(partner);
                        partner->moveSpeed = 0.0f;
                        partner->jumpScale = 0.0f;
                        partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
                        PartnerFollowState = PARTNER_MOVE_FOLLOW_PLAYER;
                        PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
                        PartnerFollowSubstate = 0;
                        partner->yaw = clamp_angle((camera->curYaw + 270.0f) - playerStatus->spriteFacingAngle);
                }
            }
            break;
        case PARTNER_MOVE_TO_GOAL:
            partner_move_to_goal(partner, true);
            break;
        case PARTNER_MOVE_DISABLE_ASAP:
            partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
            break;
        case PARTNER_MOVE_DISABLED:
            break;
    }
}

void partner_init_put_away(Npc* partner) {
    partner->collisionChannel = COLLIDER_FLAG_IGNORE_PLAYER;
    PartnerFollowState = PARTNER_MOVE_FOLLOW_PLAYER;
    partner->flags |= NPC_FLAG_IGNORE_CHAR_COLLISION;
}

s32 partner_put_away(Npc* partner) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    f32 tempMoveToX;
    f32 tempMoveToY;
    f32 tempMoveToZ;
    f32 tempPosX;
    f32 tempPosZ;
    f32 tempPosY;
    f32 tempDuration;

    switch (PartnerFollowState){
        case PARTNER_MOVE_FOLLOW_PLAYER:
            tempMoveToX = partner->pos.x;
            tempMoveToY = partner->pos.y;
            tempMoveToZ = partner->pos.z;
            partner->flags &= ~NPC_FLAG_GRAVITY;
            partner->flags &= ~NPC_FLAG_FLYING;
            tempPosX = playerStatus->pos.x;
            partner->moveToPos.x = tempPosX;
            tempPosY = playerStatus->pos.y + (playerStatus->colliderHeight / 2);
            partner->moveToPos.y = playerStatus->pos.y + (playerStatus->colliderHeight / 2);
            tempPosZ = playerStatus->pos.z;
            SavedPartnerPos.x = tempMoveToX;
            SavedPartnerPos.y = tempMoveToY;
            SavedPartnerPos.z = tempMoveToZ;
            partner->moveSpeed = 4.0f;
            partner->jumpScale = 1.6f;
            partner->moveToPos.z = tempPosZ;
            partner->planarFlyDist = dist2D(tempMoveToX, tempMoveToZ, tempPosX, tempPosZ);
            partner->yaw = atan2(tempMoveToX, tempMoveToZ, tempPosX, tempPosZ);
            partner->duration = 15;
            partner->moveSpeed = partner->planarFlyDist / partner->duration;
            tempMoveToY = tempPosY - tempMoveToY;
            partner->jumpVel = (tempMoveToY + partner->jumpScale * partner->duration * partner->duration * 0.5f) / partner->duration;
            partner->curAnim = gPartnerAnimations[CurrentPartnerID].jump;
            enable_npc_blur(partner);
            PartnerFollowState = PARTNER_MOVE_BEGIN_JUMP;
            break;
        case PARTNER_MOVE_BEGIN_JUMP:
            partner->jumpVel -= partner->jumpScale;
            partner->pos.y += partner->jumpVel;
            if (partner->jumpVel <= 0.0f) {
                partner->curAnim = gPartnerAnimations[CurrentPartnerID].fall;
            }
            npc_move_heading(partner, partner->moveSpeed, partner->yaw);
            tempDuration = partner->duration;
            if (partner->duration > 10.0f) {
                tempDuration = 10.0f;
            }
            partner->scale.x = tempDuration / 10.0f;
            partner->scale.y = partner->scale.x;
            partner->scale.z = partner->scale.x;
            partner->duration--;
            if (partner->duration < 0) {
                PartnerFollowState = PARTNER_MOVE_JUMPING;
            }
            break;
        case PARTNER_MOVE_JUMPING:
            partner->curAnim = gPartnerAnimations[CurrentPartnerID].fly;
            partner->jumpVel = 0.0f;
            partner->pos.y = partner->moveToPos.y;
            disable_npc_blur(partner);
            return true;
    }
    return false;
}

void partner_init_get_out(Npc* npc) {
    npc->collisionChannel = COLLIDER_FLAG_IGNORE_PLAYER;
    PartnerFollowState = PARTNER_MOVE_FOLLOW_PLAYER;
    npc->flags |= NPC_FLAG_IGNORE_CHAR_COLLISION;
}

s32 partner_get_out(Npc* partner) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    Camera* camera = &gCameras[gCurrentCameraID];
    f32 x, y, z, hitDepth;
    f32 var_f0;

    f32 moveToX, moveToY, moveToZ;

    switch (PartnerFollowState) {
        case PARTNER_MOVE_FOLLOW_PLAYER:
            if (clamp_angle(playerStatus->spriteFacingAngle) < 180.0f) {
                partner->yaw = clamp_angle(camera->curYaw + 90.0f);
            } else {
                partner->yaw = clamp_angle(camera->curYaw - 90.0f);
            }
            partner->moveToPos.x = playerStatus->pos.x;
            partner->moveToPos.y = playerStatus->pos.y;
            if (ActivePartner->isFlying) {
                partner->moveToPos.y = playerStatus->pos.y;
            }
            partner->moveToPos.z = playerStatus->pos.z;
            add_vec2D_polar(&partner->moveToPos.x, &partner->moveToPos.z, playerStatus->colliderDiameter, partner->yaw);
            moveToX = partner->moveToPos.x;
            moveToY = partner->moveToPos.y;
            moveToZ = partner->moveToPos.z;
            if (!ActivePartner->isFlying) {
                x = moveToX;
                y = moveToY + partner->collisionHeight;
                z = moveToZ;
                add_vec2D_polar(&x, &z, 2.0f, gCameras[gCurrentCameraID].curYaw);
                hitDepth = 1000.0f;
                if (npc_raycast_down_around(COLLIDER_FLAG_IGNORE_PLAYER, &x, &y, &z, &hitDepth, partner->yaw, partner->collisionDiameter)) {
                    /// @bug? collider flags not properly masked with COLLIDER_FLAG_SURFACE_TYPE
                    s32 surfaceType = get_collider_flags(NpcHitQueryColliderID);

                    if ((surfaceType == SURFACE_TYPE_SPIKES || surfaceType == SURFACE_TYPE_LAVA) || (hitDepth > 100.0f)) {
                        moveToX = playerStatus->pos.x;
                        moveToY = playerStatus->pos.y;
                        moveToZ = playerStatus->pos.z;
                        add_vec2D_polar(&x, &z, 2.0f, gCameras[gCurrentCameraID].curYaw);
                    }
                } else {
                    moveToX = playerStatus->pos.x;
                    moveToY = playerStatus->pos.y;
                    moveToZ = playerStatus->pos.z;
                    add_vec2D_polar(&x, &z, 2.0f, gCameras[gCurrentCameraID].curYaw);
                }
            }

            x = partner->pos.x = playerStatus->pos.x;
            y = partner->pos.y = playerStatus->pos.y + (playerStatus->colliderHeight / 2);
            z = partner->pos.z = playerStatus->pos.z;

            partner->moveSpeed = 4.0f;
            partner->jumpScale = 1.2f;
            partner->planarFlyDist = dist2D(x, z, moveToX, moveToZ);
            partner->yaw = atan2(x, z, moveToX, moveToZ);
            partner->duration = partner->planarFlyDist / partner->moveSpeed;
            if (partner->duration < 10) {
                partner->duration = 10;
                partner->moveSpeed = partner->planarFlyDist / partner->duration;
            }
            partner->jumpVel = (moveToY - y + (partner->jumpScale * partner->duration * partner->duration * 0.5f)) /
                                    partner->duration;
            PartnerFollowState = PARTNER_MOVE_BEGIN_JUMP;
            y = moveToY - y;
            partner->curAnim = gPartnerAnimations[CurrentPartnerID].jump;
            break;
        case PARTNER_MOVE_BEGIN_JUMP:
            if (partner->jumpVel < 0.0f && npc_try_snap_to_ground(partner, fabsf(partner->jumpVel))) {
                PartnerFollowState = PARTNER_MOVE_JUMPING;
                break;
            }
            partner->jumpVel -= partner->jumpScale;
            partner->pos.y += partner->jumpVel;
            if (partner->jumpVel <= 0.0f) {
                partner->curAnim = gPartnerAnimations[CurrentPartnerID].fall;
            }
            npc_move_heading(partner, partner->moveSpeed, partner->yaw);
            npc_do_world_collision(partner);
            var_f0 = partner->duration;
            if (var_f0 > 10.0f) {
                var_f0 = 10.0f;
            }

            partner->scale.x = (10.0f - var_f0) / 10.0f;
            partner->scale.y = partner->scale.x;
            partner->scale.z = partner->scale.x;

            partner->duration--;
            if (partner->duration < 0) {
                PartnerFollowState = PARTNER_MOVE_JUMPING;
            }
            break;
        case PARTNER_MOVE_JUMPING:
            partner->pos.y = partner->moveToPos.y;
            partner->jumpVel = 0.0f;
            partner->scale.x = 1.0f;
            partner->scale.y = 1.0f;
            partner->scale.z = 1.0f;
            partner->moveToPos.x = partner->pos.x;
            partner->moveToPos.y = partner->pos.y;
            partner->moveToPos.z = partner->pos.z;
            partner->pos.x = partner->pos.x;
            partner->pos.y = playerStatus->pos.y;
            if (ActivePartner->isFlying) {
                partner->pos.y = playerStatus->pos.y;
            }
            partner->pos.z = partner->pos.z;
            partner_clear_player_tracking(partner);
            partner->pos.x = partner->moveToPos.x;
            partner->pos.y = partner->moveToPos.y;
            partner->pos.z = partner->moveToPos.z;
            if (partner->flags & NPC_FLAG_GROUNDED) {
                if (!ActivePartner->isFlying) {
                    npc_surface_spawn_fx(partner, SURFACE_INTERACT_LAND);
                }
            }
            return true;
    }
    return false;
}

void partner_disable_ai_soon(void) {
    PartnerFollowState = PARTNER_MOVE_DISABLE_ASAP;
}

void partner_disable_ai(void) {
    PartnerFollowState = PARTNER_MOVE_DISABLED;
}

void enable_partner_ai(void) {
    PartnerFollowState = PARTNER_MOVE_FOLLOW_PLAYER;
    partner_clear_player_tracking(gPartnerNpc);

    if (!ActivePartner->isFlying) {
        partner_walking_enable(gPartnerNpc, false);
    } else {
        partner_flying_enable(gPartnerNpc, false);
    }
}

void partner_set_tether_distance(f32 dist) {
    PartnerTetherDistance = dist;
}

void partner_reset_tether_distance(void) {
    PartnerTetherDistance = 40.0f;
}

void partner_set_goal_pos(s32 x, s32 z) {
    PartnerMoveGoalX = x;
    PartnerMoveGoalZ = z;
}

void partner_set_forced_follow_mode(s32 mode) {
    PartnerForcedFollowMode = mode;
}

void partner_move_to_player_side(void) {
    PartnerFollowState = PARTNER_MOVE_TO_SIDE;
    PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
    PartnerMoveTime = 10;
    PartnerFollowSubstate = 0;
}

void partner_move_to_pos(s32 posX, s32 posZ) {
    partner_set_goal_pos(posX, posZ);
    PartnerFollowState = PARTNER_MOVE_TO_GOAL;
}

void partner_reset_ai_state(void) {
    PartnerFollowState = PARTNER_MOVE_FOLLOW_PLAYER;
    PartnerForcedFollowMode = PARTNER_FORCED_FOLLOW_NONE;
    PartnerFollowSubstate = 0;
}

void partner_clear_player_tracking(Npc* partner) {
    PlayerPathElement* it = PlayerMoveHistory;
    s32 i;

    SavedPartnerPos.x = partner->pos.x;
    SavedPartnerPos.y = partner->pos.y;
    SavedPartnerPos.z = partner->pos.z;

    for (i = 0; i < ARRAY_COUNT(PlayerMoveHistory); i++, it++) {
        it->pos.x = SavedPartnerPos.x;
        it->pos.y = SavedPartnerPos.y;
        it->pos.z = SavedPartnerPos.z;
        it->isJumping = false;
    }
}

// forces the player to complete a direction flip if they are currently performing one
// the resulting camera-relative direction is returned as a boolean 'isFacingLeft'
s32 partner_force_player_flip_done(void) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    Camera* cameras = gCameras;
    s32 isFacingLeft;

    if (playerStatus->flipYaw[CAM_DEFAULT] == 0.0f) {
        if (!(playerStatus->spriteFacingAngle >= 90.0f) || !(playerStatus->spriteFacingAngle < 270.0f)) {
            isFacingLeft = true;
            playerStatus->targetYaw = clamp_angle(cameras[CAM_DEFAULT].curYaw - 90.0f);
        } else {
            isFacingLeft = false;
            playerStatus->targetYaw = clamp_angle(cameras[CAM_DEFAULT].curYaw + 90.0f);
        }
    } else if (get_clamped_angle_diff(cameras[CAM_DEFAULT].curYaw, playerStatus->targetYaw) < 0.0f) {
        isFacingLeft = true;
        playerStatus->targetYaw = clamp_angle(cameras[CAM_DEFAULT].curYaw - 90.0f);

    } else {
        isFacingLeft = false;
        playerStatus->targetYaw = clamp_angle(cameras[CAM_DEFAULT].curYaw + 90.0f);
    }

    playerStatus->curYaw = playerStatus->targetYaw;
    return isFacingLeft;
}

void partner_enable_input(void) {
    PartnerStatus* partnerStatus = &gPartnerStatus;

    partnerStatus->inputDisabledCount--;
    if (partnerStatus->inputDisabledCount < 0) {
        partnerStatus->inputDisabledCount = 0;
    }
}

void partner_disable_input(void) {
    PartnerStatus* partnerStatus = &gPartnerStatus;

    partnerStatus->inputDisabledCount++;
}

void partner_do_player_collision(Npc* partner) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    f32 playerScreenX;
    f32 playerScreenY;
    f32 playerScreenZ;
    f32 partnerScreenX;
    f32 partnerScreenY;
    f32 partnerScreenZ;
    f32 W;

    transform_point(gCameras[CAM_DEFAULT].mtxPerspective,
                    playerStatus->pos.x, playerStatus->pos.y, playerStatus->pos.z, 1.0f,
                    &playerScreenX, &playerScreenY, &playerScreenZ, &W);
    transform_point(gCameras[CAM_DEFAULT].mtxPerspective, partner->pos.x, partner->pos.y, partner->pos.z, 1.0f,
                    &partnerScreenX, &partnerScreenY, &partnerScreenZ, &W);
    playerScreenX = fabsf(playerScreenX - partnerScreenX);
    playerScreenY = fabsf(playerScreenY - partnerScreenY);
    playerScreenZ = fabsf(playerScreenZ - partnerScreenZ);
    if (playerScreenX <= (partner->collisionDiameter + playerStatus->colliderDiameter) * 0.9f &&
        playerScreenY <= partner->collisionHeight + playerStatus->colliderHeight && playerScreenZ <= 4.0)
    {
        npc_move_heading(partner, 1.0f,
                         atan2(playerStatus->pos.x, playerStatus->pos.z, partner->pos.x, partner->pos.z));
        add_vec2D_polar(&partner->pos.x, &partner->pos.z, 2.0f, gCameras[gCurrentCameraID].curYaw);
    }
}

void partner_move_to_goal(Npc* partner, s32 isFlying) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    f32 x, y, z, temp;

    switch (PartnerFollowSubstate) {
        case 0:
            PartnerFollowSubstate++;
            partner->moveToPos.y = playerStatus->pos.y;
            partner->moveToPos.x = PartnerMoveGoalX;
            partner->moveToPos.z = PartnerMoveGoalZ;
            PartnerMoveYaw = atan2(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
            partner->yaw = PartnerMoveYaw;
            add_vec2D_polar(&partner->moveToPos.x, &partner->moveToPos.z, 5.0f, PartnerMoveYaw);
            PartnerMoveTime = 18;
            temp = dist2D(partner->pos.x, partner->pos.z, partner->moveToPos.x, partner->moveToPos.z);
            partner->moveSpeed = PartnerMoveSpeed = temp / PartnerMoveTime;
            partner->curAnim = gPartnerAnimations[CurrentPartnerID].anims[
                (partner->moveSpeed >= 4.0) ? PARTNER_ANIM_INDEX_RUN : PARTNER_ANIM_INDEX_WALK];
        case 1:
            if (PartnerMoveTime != 0) {
                PartnerMoveTime--;
                if (!isFlying) {
                    if (!(partner->flags & NPC_FLAG_GROUNDED)) {
                        partner->pos.y = playerStatus->pos.y;
                    }
                    if (partner->jumpVel != 0.0f) {
                        partner->jumpVel -= partner->jumpScale;
                        partner->pos.y += partner->jumpVel;
                        if (partner->jumpVel <= 0.0f) {
                            partner->curAnim = gPartnerAnimations[CurrentPartnerID].fall;
                        }

                        if (partner->jumpVel <= 0.0f) {
                            temp = fabsf(partner->jumpVel) + partner->collisionHeight;
                            y = partner->pos.y + partner->collisionHeight;
                            x = partner->pos.x;
                            z = partner->pos.z;

                            if (npc_raycast_down_around(partner->collisionChannel, &x, &y, &z, &temp,
                                                       partner->yaw, partner->collisionDiameter) &&
                                (temp <= fabsf(partner->jumpVel) + 22.0f))
                            {
                                partner->curAnim = gPartnerAnimations[CurrentPartnerID].anims[
                                    (partner->moveSpeed >= 4.0) ? PARTNER_ANIM_INDEX_RUN : PARTNER_ANIM_INDEX_WALK];
                                partner->jumpScale = 0.0f;
                                partner->jumpVel = 0.0f;
                                partner->pos.y = y;
                                partner->flags &= ~NPC_FLAG_JUMPING;
                            }
                        }
                    }
                    partner->moveSpeed = PartnerMoveSpeed;
                    partner->yaw = PartnerMoveYaw;
                    npc_move_heading(partner, partner->moveSpeed, partner->yaw);
                    partner->curAnim = gPartnerAnimations[CurrentPartnerID].anims[
                        (partner->moveSpeed >= 4.0) ? PARTNER_ANIM_INDEX_RUN : PARTNER_ANIM_INDEX_WALK];
                    npc_do_world_collision(partner);
                } else {
                    if (fabs(partner->pos.y - playerStatus->pos.y) > 5.0) {
                        partner->pos.y += (playerStatus->pos.y - partner->pos.y) * 0.5f;
                    }
                    partner->moveSpeed = PartnerMoveSpeed;
                    partner->yaw = PartnerMoveYaw;
                    npc_move_heading(partner, partner->moveSpeed, partner->yaw);
                }

                npc_surface_spawn_fx(partner, (partner->moveSpeed < 4.0) ? SURFACE_INTERACT_WALK : SURFACE_INTERACT_RUN);
            } else {
                partner->flags &= ~NPC_FLAG_IGNORE_WORLD_COLLISION;
                partner->curAnim = gPartnerAnimations[CurrentPartnerID].idle;
                PartnerFollowSubstate++;
            }
            break;
        case 2:
            break;
    }
}

// TODO: refactor below into world, requires removing world_use_item VRAM class

extern EvtScript EVS_World_UseItem;

BSS s32 UseItemInvSlot;

s32 use_consumable(s32 invSlot) {
    Evt* script;

    UseItemInvSlot = invSlot;
    invSlot = gPlayerData.invItems[invSlot];
    dma_copy(world_use_item_ROM_START, world_use_item_ROM_END, world_use_item_VRAM);
    script = start_script(&EVS_World_UseItem, EVT_PRIORITY_1, 0);
    script->varTable[10] = invSlot;
    return script->id;
}

void remove_consumable(void) {
    gPlayerData.invItems[UseItemInvSlot] = ITEM_NONE;
    sort_consumables();
}
