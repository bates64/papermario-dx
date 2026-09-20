#include "common_structs.h"
#include "world/partners.h"
#include "world/partners_internal.h"
#include "macros.h"

#include "dx/overlay.h"
#include "npc.h"
#include "hud_element.h"

#include "sprite/npc/WorldGoombario.h"

#include "sprite/npc/WorldKooper.h"

#include "sprite/npc/WorldBombette.h"

#include "sprite/npc/WorldParakarry.h"

#include "sprite/npc/Goompa.h"

#include "sprite/npc/WorldWatt.h"

#include "sprite/npc/WorldSushie.h"

#include "sprite/npc/WorldLakilester.h"

#include "sprite/npc/WorldBow.h"

#include "sprite/npc/Goombaria.h"

#include "sprite/npc/Twink.h"

PartnerStatus gPartnerStatus;
Npc* gPartnerNpc;

BSS s32 PartnerNpcIndex;
BSS s32 CurrentPartnerID;
BSS WorldPartner* ActivePartner;
BSS s32 WorldTattleInteractionID;
static Overlay* ActivePartnerOverlay;

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

static const char* WorldPartnerOverlayNames[] = {
    [PARTNER_GOOMBARIO]  = "world_partner_goombario",
    [PARTNER_KOOPER]     = "world_partner_kooper",
    [PARTNER_BOMBETTE]   = "world_partner_bombette",
    [PARTNER_PARAKARRY]  = "world_partner_parakarry",
    [PARTNER_GOOMPA]     = "world_partner_goompa",
    [PARTNER_WATT]       = "world_partner_watt",
    [PARTNER_SUSHIE]     = "world_partner_sushie",
    [PARTNER_LAKILESTER] = "world_partner_lakilester",
    [PARTNER_BOW]        = "world_partner_bow",
    [PARTNER_GOOMBARIA]  = "world_partner_goombaria",
    [PARTNER_TWINK]      = "world_partner_twink",
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

void partner_sync_player_position(void) {
    if (ActivePartner != nullptr && ActivePartner->syncPlayerPosition != nullptr) {
        ActivePartner->syncPlayerPosition();
    }
}

b32 partner_can_dismount(void) {
    __typeof__(&world_partner_can_dismount) canDismount;

    if (ActivePartnerOverlay == nullptr) {
        return false;
    }

    canDismount = OVL_IMPORT_SYMBOL(ActivePartnerOverlay, world_partner_can_dismount);
    return canDismount != nullptr && canDismount();
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

void unload_world_partner(void) {
    ovl_unload(ActivePartnerOverlay);
    ActivePartnerOverlay = nullptr;
    ActivePartner = nullptr;
}

void create_partner_npc(void) {
    const char* overlayName;
    NpcBlueprint blueprint;

    ASSERT_MSG(CurrentPartnerID > PARTNER_NONE && CurrentPartnerID < ARRAY_COUNT(WorldPartnerOverlayNames),
               "Invalid world partner ID %d", (int)CurrentPartnerID);
    overlayName = WorldPartnerOverlayNames[CurrentPartnerID];
    ASSERT_MSG(overlayName != nullptr, "World partner ID %d has no overlay", (int)CurrentPartnerID);

    ActivePartnerOverlay = ovl_load(overlayName, OVL_PARTNER);
    ActivePartner = ovl_import(ActivePartnerOverlay, WORLD_PARTNER_EXPORT_NAME);
    ASSERT_MSG(ActivePartner != nullptr, "World partner overlay '%s' has no %s export",
               overlayName, WORLD_PARTNER_EXPORT_NAME);

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
    unload_world_partner();
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
    ActivePartnerOverlay = nullptr;
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
