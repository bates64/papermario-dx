#include "common.h"
#include "hud_element.h"
#include "message_ids.h"

#if !VERSION_JP
#define MSG_PartnerDesc_Goombaria_Battle 0
#define MSG_PartnerDesc_Goombaria_World 0
#define MSG_PartnerDesc_Goompa_Battle 0
#define MSG_PartnerDesc_Goompa_World 0
#define MSG_PartnerDesc_Twink_Battle 0
#define MSG_PartnerDesc_Twink_World 0
#endif

// "change partner" menu position -> partnerID
s32 PartnerIDFromMenuIndex[] = {
    PARTNER_NONE,
    PARTNER_GOOMBARIO,
    PARTNER_KOOPER,
    PARTNER_BOMBETTE,
    PARTNER_PARAKARRY,
    PARTNER_BOW,
    PARTNER_WATT,
    PARTNER_SUSHIE,
    PARTNER_LAKILESTER,
    PARTNER_GOOMPA,
    PARTNER_GOOMBARIA,
    PARTNER_TWINK
};

// partnerID -> "change partner" menu position
s32 MenuIndexFromPartnerID[] = {
    [PARTNER_NONE]          0,
    [PARTNER_GOOMBARIO]     1,
    [PARTNER_KOOPER]        2,
    [PARTNER_BOMBETTE]      3,
    [PARTNER_PARAKARRY]     4,
    [PARTNER_GOOMPA]        0,
    [PARTNER_WATT]          6,
    [PARTNER_SUSHIE]        7,
    [PARTNER_LAKILESTER]    8,
    [PARTNER_BOW]           5,
    [PARTNER_GOOMBARIA]     0,
    [PARTNER_TWINK]         0,
};

PartnerPopupProperties gPartnerPopupProperties[] = {
    [PARTNER_NONE] {
        (s32) "なし",
        0,
        MSG_NONE,
        MSG_NONE,
    },
    [PARTNER_GOOMBARIO] {
        MSG_Menus_Party_Goombario,
        2,
        MSG_PartnerDesc_Goombario_World,
        MSG_PartnerDesc_Goombario_Battle,
    },
    [PARTNER_KOOPER] {
        MSG_Menus_Party_Kooper,
        3,
        MSG_PartnerDesc_Kooper_World,
        MSG_PartnerDesc_Kooper_Battle,
    },
    [PARTNER_BOMBETTE] {
        MSG_Menus_Party_Bombette,
        4,
        MSG_PartnerDesc_Bombette_World,
        MSG_PartnerDesc_Bombette_Battle,
    },
    [PARTNER_PARAKARRY] {
        MSG_Menus_Party_Parakarry,
        5,
        MSG_PartnerDesc_Parakarry_World,
        MSG_PartnerDesc_Parakarry_Battle,
    },
    [PARTNER_GOOMPA] {
        MSG_Menus_Party_Goompa,
        1,
        MSG_PartnerDesc_Goompa_World,
        MSG_PartnerDesc_Goompa_Battle,
    },
    [PARTNER_WATT] {
        MSG_Menus_Party_Watt,
        7,
        MSG_PartnerDesc_Watt_World,
        MSG_PartnerDesc_Watt_Battle,
    },
    [PARTNER_SUSHIE] {
        MSG_Menus_Party_Sushie,
        8,
        MSG_PartnerDesc_Sushie_World,
        MSG_PartnerDesc_Sushie_Battle,
    },
    [PARTNER_LAKILESTER] {
        MSG_Menus_Party_Lakilester,
        9,
        MSG_PartnerDesc_Lakilester_World,
        MSG_PartnerDesc_Lakilester_Battle,
    },
    [PARTNER_BOW] {
        MSG_Menus_Party_Bow,
        6,
        MSG_PartnerDesc_Bow_World,
        MSG_PartnerDesc_Bow_Battle,
    },
    [PARTNER_GOOMBARIA] {
        MSG_Menus_Party_Goombaria,
        1,
        MSG_PartnerDesc_Goombaria_World,
        MSG_PartnerDesc_Goombaria_Battle,
    },
    [PARTNER_TWINK] {
        MSG_Menus_Party_Twink,
        1,
        MSG_PartnerDesc_Twink_World,
        MSG_PartnerDesc_Twink_Battle,
    }
};

extern HudScript HES_Partner0;
extern HudScript HES_Goombario;
extern HudScript HES_Kooper;
extern HudScript HES_Bombette;
extern HudScript HES_Parakarry;
extern HudScript HES_Watt;
extern HudScript HES_Sushie;
extern HudScript HES_Lakilester;
extern HudScript HES_Partner9;
extern HudScript HES_Bow;
extern HudScript HES_PartnerA;
extern HudScript HES_PartnerB;
extern HudScript HES_Partner0Disabled;
extern HudScript HES_GoombarioDisabled;
extern HudScript HES_KooperDisabled;
extern HudScript HES_BombetteDisabled;
extern HudScript HES_ParakarryDisabled;
extern HudScript HES_WattDisabled;
extern HudScript HES_SushieDisabled;
extern HudScript HES_LakilesterDisabled;
extern HudScript HES_Partner9Disabled;
extern HudScript HES_BowDisabled;
extern HudScript HES_PartnerADisabled;
extern HudScript HES_PartnerBDisabled;

IconHudScriptPair gPartnerIconHudScripts[] = {
    { .enabled = &HES_Partner0, .disabled = &HES_Partner0Disabled },
    { .enabled = &HES_Goombario, .disabled = &HES_GoombarioDisabled },
    { .enabled = &HES_Kooper, .disabled = &HES_KooperDisabled },
    { .enabled = &HES_Bombette, .disabled = &HES_BombetteDisabled },
    { .enabled = &HES_Parakarry, .disabled = &HES_ParakarryDisabled },
    { .enabled = &HES_Bow, .disabled = &HES_BowDisabled },
    { .enabled = &HES_Watt, .disabled = &HES_WattDisabled },
    { .enabled = &HES_Sushie, .disabled = &HES_SushieDisabled },
    { .enabled = &HES_Lakilester, .disabled = &HES_LakilesterDisabled },
    { .enabled = &HES_Partner9, .disabled = &HES_Partner9Disabled },
    { .enabled = &HES_PartnerA, .disabled = &HES_PartnerADisabled },
    { .enabled = &HES_PartnerB, .disabled = &HES_PartnerBDisabled },
    { .enabled = &HES_PartnerB, .disabled = &HES_PartnerBDisabled },
};
