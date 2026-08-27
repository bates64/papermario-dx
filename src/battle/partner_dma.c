
#include "common.h"
#include "battle/partner.h"
#include "dx/overlay.h"

static const char* BattlePartnerOverlayNames[] = {
    [PARTNER_NONE]       = nullptr,
    [PARTNER_GOOMBARIO]  = "goombario",
    [PARTNER_KOOPER]     = "kooper",
    [PARTNER_BOMBETTE]   = "bombette",
    [PARTNER_PARAKARRY]  = "parakarry",
    [PARTNER_GOOMPA]     = "goompa",
    [PARTNER_WATT]       = "watt",
    [PARTNER_SUSHIE]     = "sushie",
    [PARTNER_LAKILESTER] = "lakilester",
    [PARTNER_BOW]        = "bow",
    [PARTNER_GOOMBARIA]  = nullptr,
    [PARTNER_TWINK]      = "twink",
};

static Overlay* LoadedBattlePartnerOverlay;
static const BattlePartner* LoadedBattlePartner;

Overlay* get_battle_partner_overlay(void) {
    return LoadedBattlePartnerOverlay;
}

void unload_battle_partner(void) {
    ASSERT_MSG(gBattleStatus.partnerActor == nullptr,
               "Cannot unload a battle partner overlay while its actor is alive");
    ovl_unload(LoadedBattlePartnerOverlay);
    LoadedBattlePartnerOverlay = nullptr;
    LoadedBattlePartner = nullptr;
}

const BattlePartner* load_battle_partner(s32 partnerID) {
    const char* overlayName;

    ASSERT_MSG((u32)partnerID < ARRAY_COUNT(BattlePartnerOverlayNames),
               "Invalid battle partner ID %d", (int)partnerID);
    overlayName = BattlePartnerOverlayNames[partnerID];
    ASSERT_MSG(overlayName != nullptr, "Partner ID %d has no battle overlay", (int)partnerID);

    unload_battle_partner();
    LoadedBattlePartnerOverlay = ovl_load(overlayName, OVL_BATTLE_PARTNER);
    LoadedBattlePartner = ovl_import(LoadedBattlePartnerOverlay, BATTLE_PARTNER_EXPORT_NAME);
    ASSERT_MSG(LoadedBattlePartner != nullptr,
               "Battle partner overlay '%s' has no %s export",
               overlayName, BATTLE_PARTNER_EXPORT_NAME);
    ASSERT_MSG(LoadedBattlePartner->id == partnerID,
               "Battle partner overlay '%s' has ID %d, expected %d",
               overlayName, (int)LoadedBattlePartner->id, (int)partnerID);
    ASSERT_MSG(LoadedBattlePartner->blueprint != nullptr,
               "Battle partner overlay '%s' has no actor blueprint", overlayName);
    ASSERT_MSG(LoadedBattlePartner->blueprint->partCount > 0,
               "Battle partner overlay '%s' has an empty actor blueprint", overlayName);
    ASSERT_MSG(LoadedBattlePartner->blueprint->partsData != nullptr,
               "Battle partner overlay '%s' has no actor parts", overlayName);
    ASSERT_MSG(LoadedBattlePartner->blueprint->initScript != nullptr,
               "Battle partner overlay '%s' has no actor init script", overlayName);
    ASSERT_MSG(LoadedBattlePartner->blueprint->statusTable != nullptr,
               "Battle partner overlay '%s' has no actor status table", overlayName);

    return LoadedBattlePartner;
}
