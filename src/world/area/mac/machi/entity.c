#include "machi.h"
#include "entity.h"

API_CALLABLE(DoNothing1) {
    return ApiStatus_DONE2;
}

API_CALLABLE(DoNothing2) {
    return ApiStatus_DONE2;
}

API_CALLABLE(DoNothing3) {
    return ApiStatus_BLOCK;
}

API_CALLABLE(FadeToBlack) {
    if (isInitialCall) {
        script->functionTemp[0] = 0;
        script->functionTemp[1] = 0;
        gOverrideFlags |= GLOBAL_OVERRIDES_MESSAGES_OVER_FRONTUI;
    }

    set_screen_overlay_params_front(OVERLAY_SCREEN_COLOR, script->functionTemp[1]);

    if (script->functionTemp[1] == 255) {
        return ApiStatus_DONE2;
    }

    script->functionTemp[1] += 10;
    if (script->functionTemp[1] > 255) {
        script->functionTemp[1] = 255;
    }

    return ApiStatus_BLOCK;
}

API_CALLABLE(UpgradePartnerRankDebug) {
    gPlayerData.partners[script->varTable[0] + 1].level++;
    script->varTable[0] = PARTNER_NONE;
    if (gPlayerData.partners[PARTNER_GOOMBARIO].level > PARTNER_RANK_ULTRA) {
        gPlayerData.partners[PARTNER_GOOMBARIO].level = PARTNER_RANK_ULTRA;
        script->varTable[0] = PARTNER_GOOMBARIO;
    }

    return ApiStatus_DONE2;
}

API_CALLABLE(FadeFromBlack) {
    if (isInitialCall) {
        script->functionTemp[0] = 0;
        script->functionTemp[1] = 255;
        gOverrideFlags |= GLOBAL_OVERRIDES_MESSAGES_OVER_FRONTUI;
    }

    set_screen_overlay_params_front(OVERLAY_SCREEN_COLOR, script->functionTemp[1]);

    if (script->functionTemp[1] == 0) {
        gOverrideFlags &= ~GLOBAL_OVERRIDES_MESSAGES_OVER_FRONTUI;
        return ApiStatus_DONE2;
    }

    script->functionTemp[1] -= 10;
    if (script->functionTemp[1] < 0) {
        script->functionTemp[1] = 0;
    }

    return ApiStatus_BLOCK;
}

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $HugeBlueSwitch_1)
    Call(MakeMarkerEntity, $GreenStompSwitch_1)
    Call(MakeMarkerEntity, $BlueSwitch_1)
    Call(MakeMarkerEntity, $RedSwitch_1)
    Call(MakeMarkerEntity, $HiddenYellowBlock_Coin_1)
    Call(MakeMarkerEntity, $MulticoinBlock_1)
    Call(MakeMarkerEntity, $BrickBlock_1)
    Call(MakeMarkerEntity, $BrickBlock_2)
    Call(MakeMarkerEntity, $BrickBlock_3)
    Call(MakeMarkerEntity, $YellowBlock_Mushroom_1)
    Call(MakeMarkerEntity, $YellowBlock_Mushroom_2)
    Call(MakeMarkerEntity, $GiantChest)
    Call(MakeMarkerEntity, $Chest)
    Call(MakeMarkerEntity, $Item_Mushroom_1)
    Call(MakeMarkerEntity, $Item_Mushroom_2)
    Call(MakeMarkerEntity, $Item_Mushroom_3)
    Call(MakeMarkerEntity, $Item_Mushroom_4)
    Call(MakeMarkerEntity, $Item_Mushroom_5)
    Return
    End
};
