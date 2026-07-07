#include "common_structs.h"
#include "world/partners.h"
#include "world/partners_internal.h"
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

PartnerStatus gPartnerStatus;
Npc* gPartnerNpc;

BSS s32 PartnerNpcIndex;
BSS s32 CurrentPartnerID;
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

IconHudScriptPair wPartnerHudScripts[] = {
    { HES_Partner0,    HES_Partner0Disabled    },
    { HES_Goombario,   HES_GoombarioDisabled   },
    { HES_Kooper,      HES_KooperDisabled      },
    { HES_Bombette,    HES_BombetteDisabled    },
    { HES_Parakarry,   HES_ParakarryDisabled   },
    { HES_Partner0,    HES_Partner0Disabled    },
    { HES_Watt,        HES_WattDisabled        },
    { HES_Sushie,      HES_SushieDisabled      },
    { HES_Lakilester,  HES_LakilesterDisabled  },
    { HES_Bow,         HES_BowDisabled         },
    { HES_PartnerA,    HES_PartnerADisabled    },
    { HES_PartnerA,    HES_PartnerADisabled    },
    { HES_PartnerA,    HES_PartnerADisabled    },
    { HES_PartnerA,    HES_PartnerADisabled    },
    { HES_PartnerA,    HES_PartnerADisabled    },
    { HES_PartnerA,    HES_PartnerADisabled    },
};

HudScriptList DigitHudScripts = {
    HES_StatusDigit0, HES_StatusDigit1, HES_StatusDigit2, HES_StatusDigit3, HES_StatusDigit4,
    HES_StatusDigit5, HES_StatusDigit6, HES_StatusDigit7, HES_StatusDigit8, HES_StatusDigit9,
};

HudScriptList SPIncrementHudScripts = {
    HES_StatusSPIncrement1, HES_StatusSPIncrement3, HES_StatusSPIncrement2,
    HES_StatusSPIncrement4, HES_StatusSPIncrement5, HES_StatusSPIncrement6, HES_StatusSPIncrement7
};

HudScriptList SPStarHudScripts = { HES_StatusStar1, HES_StatusStar3, HES_StatusStar2, HES_StatusStar4,
    HES_StatusStar5, HES_StatusStar6, HES_StatusStar7
};

s32 StatusBarSPIncrementOffsets[] = { -1, 1, 2, 4, 5, 7, 8, 0, 0, 0 };

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

void partner_initialize_data(void) {
    PartnerStatus* partnerStatus = &gPartnerStatus;

    CurrentPartnerID = 0;

    init_partner_commands();

    PartnerSpawnMode = PARTNER_SPAWN_NONE;
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
        suspend_partner_commands();

        if (ActivePartner->preBattle != nullptr) {
            ActivePartner->preBattle(gPartnerNpc);
        }
    }
}

void partner_handle_after_battle(void) {
    PartnerStatus* partnerStatus = &gPartnerStatus;
    PlayerData* playerData = &gPlayerData;

    if (CurrentPartnerID != PARTNER_NONE) {
        resume_partner_commands();

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
