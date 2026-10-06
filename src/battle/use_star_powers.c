#include "common.h"
#include "battle/battle.h"
#include "battle/script_module.h"
#include "sprite/player.h"

#include "sprite/npc/WorldGoombario.h"
#include "sprite/npc/BattleGoombario.h"
#include "sprite/npc/BattleKooper.h"
#include "sprite/npc/BattleBombette.h"
#include "sprite/npc/BattleParakarry.h"
#include "sprite/npc/BattleWatt.h"
#include "sprite/npc/BattleSushie.h"
#include "sprite/npc/BattleLakilester.h"
#include "sprite/npc/BattleBow.h"

#define STAR_POWER_SCRIPT(name) { "battle_move_" name, BATTLE_SCRIPT_KIND_STAR_POWER, 0 }

static const BattleScriptRef StarPowersTable[] = {
    STAR_POWER_SCRIPT("focus"),
    STAR_POWER_SCRIPT("refresh"),
    STAR_POWER_SCRIPT("lullaby"),
    STAR_POWER_SCRIPT("star_storm"),
    STAR_POWER_SCRIPT("chill_out"),
    STAR_POWER_SCRIPT("smooch"),
    STAR_POWER_SCRIPT("time_out"),
    STAR_POWER_SCRIPT("up_and_away"),
    STAR_POWER_SCRIPT("star_beam"),
    STAR_POWER_SCRIPT("peach_beam"),
    STAR_POWER_SCRIPT("peach_focus"),
    STAR_POWER_SCRIPT("peach_focus_alt"),
};

s32 PartnerWishAnims[][5] = {
    [PARTNER_NONE] {
        [PARTNER_WISH_ANIM_WALK]    ANIM_Mario1_UsePower,
        [PARTNER_WISH_ANIM_PRAY]    ANIM_Mario1_Pray,
        [PARTNER_WISH_ANIM_UNUSED]  ANIM_Mario1_LookUp,
        [PARTNER_WISH_ANIM_RETURN]  ANIM_Mario1_Run,
        [PARTNER_WISH_ANIM_IDLE]    0,
    },
    [PARTNER_GOOMBARIO] {
        [PARTNER_WISH_ANIM_WALK]    ANIM_BattleGoombario_Run,
        [PARTNER_WISH_ANIM_PRAY]    ANIM_BattleGoombario_CloseEyes,
        [PARTNER_WISH_ANIM_UNUSED]  ANIM_BattleGoombario_CloseEyes,
        [PARTNER_WISH_ANIM_RETURN]  ANIM_BattleGoombario_Run,
        [PARTNER_WISH_ANIM_IDLE]    ANIM_BattleGoombario_Idle,
    },
    [PARTNER_KOOPER] {
        [PARTNER_WISH_ANIM_WALK]    ANIM_BattleKooper_Run,
        [PARTNER_WISH_ANIM_PRAY]    ANIM_BattleKooper_Pray,
        [PARTNER_WISH_ANIM_UNUSED]  ANIM_BattleKooper_Pray,
        [PARTNER_WISH_ANIM_RETURN]  ANIM_BattleKooper_Run,
        [PARTNER_WISH_ANIM_IDLE]    ANIM_BattleKooper_Idle,
    },
   [PARTNER_BOMBETTE] {
        [PARTNER_WISH_ANIM_WALK]    ANIM_BattleBombette_Run,
        [PARTNER_WISH_ANIM_PRAY]    ANIM_BattleBombette_Sleep,
        [PARTNER_WISH_ANIM_UNUSED]  ANIM_BattleBombette_Sleep,
        [PARTNER_WISH_ANIM_RETURN]  ANIM_BattleBombette_Run,
        [PARTNER_WISH_ANIM_IDLE]    ANIM_BattleBombette_Idle,
    },
    [PARTNER_PARAKARRY] {
        [PARTNER_WISH_ANIM_WALK]    ANIM_BattleParakarry_Run,
        [PARTNER_WISH_ANIM_PRAY]    ANIM_BattleParakarry_Pray,
        [PARTNER_WISH_ANIM_UNUSED]  ANIM_BattleParakarry_Pray,
        [PARTNER_WISH_ANIM_RETURN]  ANIM_BattleParakarry_Run,
        [PARTNER_WISH_ANIM_IDLE]    ANIM_BattleParakarry_Idle,
    },
    [PARTNER_GOOMPA] {
        // no data
    },
    [PARTNER_WATT] {
        [PARTNER_WISH_ANIM_WALK]    ANIM_BattleWatt_Run,
        [PARTNER_WISH_ANIM_PRAY]    ANIM_BattleWatt_Sleep,
        [PARTNER_WISH_ANIM_UNUSED]  ANIM_BattleWatt_Sleep,
        [PARTNER_WISH_ANIM_RETURN]  ANIM_BattleWatt_Run,
        [PARTNER_WISH_ANIM_IDLE]    ANIM_BattleWatt_Idle,
    },
    [PARTNER_SUSHIE] {
        [PARTNER_WISH_ANIM_WALK]    ANIM_BattleSushie_Run,
        [PARTNER_WISH_ANIM_PRAY]    ANIM_BattleSushie_Pray,
        [PARTNER_WISH_ANIM_UNUSED]  ANIM_BattleSushie_Pray,
        [PARTNER_WISH_ANIM_RETURN]  ANIM_BattleSushie_Run,
        [PARTNER_WISH_ANIM_IDLE]    ANIM_BattleSushie_Idle,
    },
    [PARTNER_LAKILESTER] {
        [PARTNER_WISH_ANIM_WALK]    ANIM_BattleLakilester_Run,
        [PARTNER_WISH_ANIM_PRAY]    ANIM_BattleLakilester_Pray,
        [PARTNER_WISH_ANIM_UNUSED]  ANIM_BattleLakilester_Pray,
        [PARTNER_WISH_ANIM_RETURN]  ANIM_BattleLakilester_Run,
        [PARTNER_WISH_ANIM_IDLE]    ANIM_BattleLakilester_Idle,
    },
    [PARTNER_BOW] {
        [PARTNER_WISH_ANIM_WALK]    ANIM_BattleBow_Run,
        [PARTNER_WISH_ANIM_PRAY]    ANIM_BattleBow_Pray,
        [PARTNER_WISH_ANIM_UNUSED]  ANIM_BattleBow_Pray,
        [PARTNER_WISH_ANIM_RETURN]  ANIM_BattleBow_Run,
        [PARTNER_WISH_ANIM_IDLE]    ANIM_BattleBow_Idle,
    },
};

API_CALLABLE(LoadStarPowerScript) {
    BattleStatus* battleStatus = &gBattleStatus;
    PlayerData* playerData = &gPlayerData;
    s16 starPowerIdx;

    playerData->starPower -= gMoveTable[battleStatus->selectedMoveID].costFP * SP_PER_BAR;
    starPowerIdx = battleStatus->moveArgument;
    ASSERT_MSG((u32)starPowerIdx < ARRAY_COUNT(StarPowersTable),
               "Invalid star power index %d", (int)starPowerIdx);
    script->varTablePtr[0] = load_battle_script(&StarPowersTable[starPowerIdx]);
    return ApiStatus_DONE2;
}
