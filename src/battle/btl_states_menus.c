#include "battle/battle.h"
#include "battle_hud_scripts.h"

extern HudScript HES_YellowArrow;

extern HudScript HES_MenuFlee;
extern HudScript HES_MenuFleeDisabled;
extern HudScript HES_MenuDefend;
extern HudScript HES_MenuDefendDisabled;
extern HudScript HES_MenuStrategies;
extern HudScript HES_MenuStrategiesDisabled;
extern HudScript HES_MenuPouch;
extern HudScript HES_MenuPouchDisabled;
extern HudScript HES_MenuDoNothing;
extern HudScript HES_MenuDoNothingDisabled;

extern HudScript HES_Kooper;
extern HudScript HES_Bombette;
extern HudScript HES_Partner0;
extern HudScript HES_Partner0Disabled;
extern HudScript HES_Goombario;
extern HudScript HES_GoombarioDisabled;
extern HudScript HES_KooperDisabled;
extern HudScript HES_BombetteDisabled;
extern HudScript HES_Parakarry;
extern HudScript HES_ParakarryDisabled;
extern HudScript HES_Bow;
extern HudScript HES_BowDisabled;
extern HudScript HES_Watt;
extern HudScript HES_WattDisabled;
extern HudScript HES_Sushie;
extern HudScript HES_SushieDisabled;
extern HudScript HES_Lakilester;
extern HudScript HES_LakilesterDisabled;
extern HudScript HES_PartnerA;
extern HudScript HES_PartnerADisabled;

extern HudScript HES_MenuBoots1;
extern HudScript HES_MenuBoots1Disabled;
extern HudScript HES_MenuBoots2;
extern HudScript HES_MenuBoots2Disabled;
extern HudScript HES_MenuBoots3;
extern HudScript HES_MenuBoots3Disabled;

extern HudScript HES_MenuHammer1;
extern HudScript HES_MenuHammer1Disabled;
extern HudScript HES_MenuHammer2;
extern HudScript HES_MenuHammer2Disabled;
extern HudScript HES_MenuHammer3;
extern HudScript HES_MenuHammer3Disabled;

extern HudScript HES_MenuItem;
extern HudScript HES_MenuItemDisabled;

extern HudScript HES_MenuStarPower;
extern HudScript HES_MenuStarPowerDisabled;

extern HudScript HES_Eldstar;
extern HudScript HES_EldstarDisabled;
extern HudScript HES_Mamar;
extern HudScript HES_MamarDisabled;
extern HudScript HES_Skolar;
extern HudScript HES_SkolarDisabled;
extern HudScript HES_Muskular;
extern HudScript HES_MuskularDisabled;
extern HudScript HES_Misstar;
extern HudScript HES_MisstarDisabled;
extern HudScript HES_Klevar;
extern HudScript HES_KlevarDisabled;
extern HudScript HES_Kalmar;
extern HudScript HES_KalmarDisabled;
extern HudScript HES_StarBeam;
extern HudScript HES_StarBeamDisabled;
extern HudScript HES_PeachBeam;
extern HudScript HES_PeachBeamDisabled;

extern HudScript HES_MoveDiamond;
extern HudScript HES_MoveDiamond_disabled;
extern HudScript HES_MoveBlueOrb;
extern HudScript HES_MoveBlueOrbDisabled;
extern HudScript HES_MoveGreenOrb;
extern HudScript HES_MoveGreenOrbDisabled;
extern HudScript HES_MoveRedOrb;
extern HudScript HES_MoveRedOrbDisabled;

extern HudScript HES_HandPointDownLoop;
extern HudScript HES_HandPointLeftLoop;

extern HudScript HES_ProjectorBeam;
extern HudScript HES_ProjectorReel;
extern HudScript HES_ProjectorSpot;
extern HudScript HES_SwapArrowLeft;
extern HudScript HES_SwapArrowRight;
extern HudScript HES_SwapBackground;
extern HudScript HES_SwapZ;

IconHudScriptPair ItemsHudScripts = { &HES_MenuItem, &HES_MenuItemDisabled };

IconHudScriptPair StarPowersHudScripts = { &HES_MenuStarPower, &HES_MenuStarPowerDisabled };

IconHudScriptPair StarPowerMovesHudScripts[] = {
    { &HES_MenuStarPower,   &HES_MenuStarPowerDisabled },
    { &HES_Eldstar,         &HES_EldstarDisabled },
    { &HES_Mamar,           &HES_MamarDisabled },
    { &HES_Skolar,          &HES_SkolarDisabled },
    { &HES_Muskular,        &HES_MuskularDisabled },
    { &HES_Misstar,         &HES_MisstarDisabled },
    { &HES_Klevar,          &HES_KlevarDisabled },
    { &HES_Kalmar,          &HES_KalmarDisabled },
    { &HES_StarBeam,        &HES_StarBeamDisabled },
    { &HES_PeachBeam,       &HES_PeachBeamDisabled },
    { &HES_MenuStarPower,   &HES_MenuStarPowerDisabled },
    { &HES_MenuStarPower,   &HES_MenuStarPowerDisabled },
};

IconHudScriptPair PartnerHudScripts[] = {
    { &HES_Partner0,        &HES_Partner0Disabled },
    { &HES_Goombario,       &HES_GoombarioDisabled },
    { &HES_Kooper,          &HES_KooperDisabled },
    { &HES_Bombette,        &HES_BombetteDisabled },
    { &HES_Parakarry,       &HES_ParakarryDisabled },
    { &HES_Partner0,        &HES_Partner0Disabled },
    { &HES_Watt,            &HES_WattDisabled },
    { &HES_Sushie,          &HES_SushieDisabled },
    { &HES_Lakilester,      &HES_LakilesterDisabled },
    { &HES_Bow,             &HES_BowDisabled },
    { &HES_PartnerA,        &HES_PartnerADisabled },
    { &HES_PartnerA,        &HES_PartnerADisabled },
    { &HES_PartnerA,        &HES_PartnerADisabled },
    { &HES_PartnerA,        &HES_PartnerADisabled },
    { &HES_PartnerA,        &HES_PartnerADisabled },
    { &HES_PartnerA,        &HES_PartnerADisabled }
};

IconHudScriptPair StrategiesHudScripts = { &HES_MenuStrategies, &HES_MenuStrategiesDisabled };

IconHudScriptPair DoNothingHudScripts = { &HES_MenuDoNothing, &HES_MenuDoNothingDisabled };

IconHudScriptPair FleeHudScripts = { &HES_MenuFlee, &HES_MenuFleeDisabled };

s32 LeftJustMenuMessages[] = {
    MSG_Menus_Jump,
    MSG_Menus_Hammer,
    MSG_Menus_Items,
    MSG_Menus_RunAway,
    MSG_Menus_Defense,
    MSG_Menus_ChangeMember,
    MSG_Menus_Abilities,
    MSG_Menus_Strategies,
    MSG_Menus_StarSpirits,
    MSG_Menus_DoNothing,
    MSG_Menus_ActLater,
    MSG_Menus_Focus,
};

s32 CenteredBattleMessages[] = {
    MSG_Menus_Jump_Centered,
    MSG_Menus_Hammer_Centered,
    MSG_Menus_Items_Centered,
    MSG_Menus_RunAway_Centered,
    MSG_Menus_Defense_Centered,
    MSG_Menus_ChangeMember_Centered,
    MSG_Menus_Abilities_Centered,
    MSG_Menus_Strategies_Centered,
    MSG_Menus_StarSpirits_Centered,
    MSG_Menus_DoNothing_Centered,
    MSG_Menus_ActLater_Centered,
    MSG_Menus_Focus_Centered,
};

BSS s32 D_802ACC60;
BSS s32 BattleMenu_TargetPointerAlpha;
BSS s32 BattleMenu_TargetNameOffsetX; // used to animate the position of the target name box
BSS s32 BattleMenu_SwapDelay; // delay before the player and partner can swap after the main menu is opened
BSS s32 BattleMenu_TargetHudElems[MAX_ENEMY_ACTORS];
BSS PopupMenu BattlePopupMenu;
BSS s8 BattleMenuState;
BSS s8 D_802AD001;
BSS s8 BattleMenu_CurPos;
BSS s8 BattleMenu_PrevPos;
BSS s8 D_802AD004;
BSS s16 D_802AD006;
BSS s16 BattleMenuAlpha;
BSS s16 D_802AD00A;
BSS s32 HID_OptionIcons[6];
BSS s32 HID_Spotlights[6];
BSS s32 HID_HighlightSpot;
BSS s32 HID_ProjectorReelA;
BSS s32 HID_ProjectorReelB;
BSS s32 HID_ProjectorBeam;
BSS s32 HID_SwapZ;
BSS s32 HID_SwapArrowLeft;
BSS s32 HID_SwapArrowRight;
BSS s32 HID_SwapBackground;
BSS s32 BattleMenu_BasePosX;
BSS s32 BattleMenu_BasePosY;
BSS s8 BattleMenuDisableMsg;
BSS s8 BattleMenu_MinIdx;
BSS s8 BattleMenu_MaxIdx;
BSS s8 BattleMenu_HomePos;
BSS f32 BattleMenu_WheelAngle;
BSS f32 D_802AD070;
BSS HudScript* BattleMenu_HudScripts[6];
BSS s32 BattleMenu_TitleMessages[6];
BSS s32 D_802AD0A8;
BSS s32 BattleMenu_NumOptions;
BSS s32 D_802AD0B0;
BSS s32 battle_menu_submenuIDs[6];
BSS s32 BattleMenu_OptionEnabled[6];
BSS s32 battle_menu_isMessageDisabled[6];
BSS s32 D_802AD100;
BSS s32 BattleMenu_ShowSwapIcons;

void btl_main_menu_init(void) {
    D_802AD006 = 255;
    BattleMenuAlpha = 255;
    BattleMenuState = BTL_MENU_STATE_CREATE;
    BattleMenuDisableMsg = -1;
}

// btl_main_menu_hide? (after begin targeting)
void func_802A1030(void) {
    D_802AD001 = 3;
    BattleMenuState = BTL_MENU_STATE_UNK_A;
}

// (after submenu closed/canceled)
void func_802A1050(void) {
    BattleMenuState = BTL_MENU_STATE_ACCEPT_INPUT;
    D_802AD006 = 255;
    BattleMenuAlpha = 255;
}

// btl_main_menu_show? (canceling targeting -> main menu)
void func_802A1078(void) {
    BattleMenuAlpha = 255;
    BattleMenuState = BTL_MENU_STATE_UNK_14;
}

// btl_main_menu_show? (canceling targeting -> submenu)
void func_802A1098(void) {
    BattleMenuAlpha = 100;
    BattleMenuState = BTL_MENU_STATE_UNK_1E;
}

void btl_main_menu_destroy(void) {
    s32 i;

    for (i = 0; i < BattleMenu_NumOptions; i++) {
        s32* icons1 = HID_OptionIcons;
        s32* icons2 = HID_Spotlights;

        hud_element_free(icons1[i]);
        hud_element_free(icons2[i]);
    }

    hud_element_free(HID_HighlightSpot);
    hud_element_free(HID_ProjectorReelA);
    hud_element_free(HID_ProjectorReelB);
    hud_element_free(HID_ProjectorBeam);
    hud_element_free(HID_SwapBackground);
    hud_element_free(HID_SwapZ);
    hud_element_free(HID_SwapArrowLeft);
    hud_element_free(HID_SwapArrowRight);
}

s32 btl_main_menu_update(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    f32 theta;
    HudElemID hid;
    s32 i;
    f32 x, y;
    s32 l, t;

    switch (BattleMenuState) {
        case BTL_MENU_STATE_CREATE:
            BattleMenu_BasePosX = 54;
            BattleMenu_BasePosY = 173;
            D_802AD070 = 0.3f;
            D_802AD004 = 0;
            BattleMenu_HomePos = D_802AD0B0;
            BattleMenu_MinIdx = 0;
            BattleMenu_MinIdx -= D_802AD0B0;
            BattleMenu_MaxIdx = BattleMenu_NumOptions - 1;
            BattleMenu_MaxIdx -= D_802AD0B0;

            for (i = 0; i < BattleMenu_NumOptions; i++) {
                HID_OptionIcons[i] = hid = hud_element_create(BattleMenu_HudScripts[i]);
                hud_element_set_render_depth(hid, 5);
                hud_element_set_flags(hid, HUD_ELEMENT_FLAG_FILTER_TEX);
                hud_element_set_flags(hid, HUD_ELEMENT_FLAG_80);
                hud_element_set_flags(hid, HUD_ELEMENT_FLAG_DISABLED);
                hud_element_set_scale(hid, 0.75f);

                HID_Spotlights[i] = hid = hud_element_create(&HES_ProjectorSpot);
                hud_element_create_transform_B(hid);
                hud_element_set_render_depth(hid, 10);
                hud_element_set_flags(hid, HUD_ELEMENT_FLAG_80);
                hud_element_set_flags(hid, HUD_ELEMENT_FLAG_FILTER_TEX);
                hud_element_set_flags(hid, HUD_ELEMENT_FLAG_DISABLED);
            }

            HID_HighlightSpot = hid = hud_element_create(&HES_ProjectorSpot);
            hud_element_create_transform_B(hid);
            hud_element_set_render_depth(hid, 7);
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_80);
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_FILTER_TEX);
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_DISABLED);

            HID_ProjectorReelA = hid = hud_element_create(&HES_ProjectorReel);
            hud_element_create_transform_B(hid);
            hud_element_set_render_depth(hid, 0);
            hud_element_set_render_pos(hid, 40, 212);
            hud_element_set_tint(hid, 0, 91, 127);
            hud_element_set_transform_rotation_pivot(hid, 16, -16);
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_80);
            hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_FILTER_TEX);
            hud_element_set_alpha(hid, 240);

            HID_ProjectorReelB = hid = hud_element_create(&HES_ProjectorReel);
            hud_element_create_transform_B(hid);
            hud_element_set_render_depth(hid, 2);
            hud_element_set_render_pos(hid, 39, 212);
            hud_element_set_tint(hid, 0, 91, 127);
            hud_element_set_transform_rotation_pivot(hid, 16, -16);
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_80);
            hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_FILTER_TEX);
            hud_element_set_alpha(hid, 240);

            HID_ProjectorBeam = hid = hud_element_create(&HES_ProjectorBeam);
            hud_element_create_transform_B(hid);
            hud_element_set_render_depth(hid, 20);
            hud_element_set_render_pos(hid, 78, 178);
            hud_element_set_tint(hid, 255, 255, 255);
            hud_element_set_transform_rotation_pivot(hid, 0, 0);
            hud_element_set_transform_rotation(hid, 0.0f, 0.0f, -45.0f);
            hud_element_set_alpha(hid, 200);
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_80);
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_FILTER_TEX);
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_DISABLED);

            HID_SwapBackground = hid = hud_element_create(&HES_SwapBackground);
            hud_element_set_render_depth(hid, 0);
            hud_element_set_render_pos(hid, 97, 208);
            hud_element_set_tint(hid, 255, 255, 255);
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_80);
            hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_FILTER_TEX);
            hud_element_set_alpha(hid, 230);

            HID_SwapZ = hid = hud_element_create(&HES_SwapZ);
            hud_element_set_render_depth(hid, 5);
            hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_FILTER_TEX);
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_80);
            hud_element_set_render_pos(hid, 94, 209);

            HID_SwapArrowLeft = hid = hud_element_create(&HES_SwapArrowLeft);
            hud_element_set_render_depth(hid, 5);
            hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_FILTER_TEX);
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_80);
            hud_element_set_render_pos(hid, 81, 210);

            HID_SwapArrowRight = hid = hud_element_create(&HES_SwapArrowRight);
            hud_element_set_render_depth(hid, 5);
            hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_FILTER_TEX);
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_80);
            hud_element_set_render_pos(hid, 102, 210);
            D_802AD00A = 100;
            D_802AD001 = 3;
            BattleMenuState = BTL_MENU_STATE_UNK_1;
            BattleMenu_WheelAngle = theta = D_802AD100 * 28;
            break;
        case BTL_MENU_STATE_UNK_1:
            D_802AD00A = (D_802AD001 * 100) / 3;

            switch (D_802AD001) {
                case 1:
                    if (D_802AD001 == 1) {
                        hid = HID_ProjectorBeam;
                        hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_DISABLED);
                    }
                default:
                    D_802AD001--;
                    break;
                case 0:
                    BattleMenu_CurPos = 0;
                    BattleMenu_PrevPos = 0;
                    BattleMenu_WheelAngle = theta = D_802AD100 * 28;
                    for (i = 0; i < BattleMenu_NumOptions; i++, theta += 28.0f) {
                        x = 0.0f;
                        y = 0.0f;
                        add_vec2D_polar(&x, &y, 87.0f, theta);

                        l = BattleMenu_BasePosX + x;
                        t = BattleMenu_BasePosY + y;
                        hid = HID_OptionIcons[i];
                        hud_element_set_render_pos(hid, l, t);
                        hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_DISABLED);

                        hid = HID_Spotlights[i];
                        hud_element_set_render_pos(hid, l, t);
                        hud_element_set_alpha(hid, 100);
                        hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_DISABLED);
                    }

                    x = 0.0f;
                    y = 0.0f;
                    theta = D_802AD100 * 28;
                    add_vec2D_polar(&x, &y, 87.0f, theta);

                    l = BattleMenu_BasePosX + x;
                    t = BattleMenu_BasePosY + y;
                    hid = HID_HighlightSpot;
                    hud_element_set_render_pos(hid, l, t);
                    hud_element_set_alpha(hid, 180);
                    hud_element_set_scale(hid, 0.85f);
                    hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_DISABLED);
                    BattleMenuState = BTL_MENU_STATE_ACCEPT_INPUT;
                    break;
            }
            break;
        case BTL_MENU_STATE_ACCEPT_INPUT:
            if (battleStatus->curButtonsPressed & BUTTON_A) {
                if (BattleMenu_OptionEnabled[BattleMenu_CurPos + BattleMenu_HomePos] == TRUE) {
                    sfx_play_sound(SOUND_MENU_NEXT);
                    BattleMenuState = BTL_MENU_STATE_OPENED_SUBMENU;
                } else {
                    sfx_play_sound(SOUND_MENU_ERROR);
                    BattleMenuDisableMsg = battle_menu_isMessageDisabled[BattleMenu_CurPos + BattleMenu_HomePos];
                    BattleMenuState = BTL_MENU_STATE_SHOW_DISABLED_POPUP;
                }
            } else {
                BattleMenu_PrevPos = BattleMenu_CurPos;
                if (D_802AD004 == 0) {
                    if ((battleStatus->curButtonsHeld & (BUTTON_STICK_LEFT | BUTTON_STICK_UP)) &&
                        BattleMenu_MinIdx < BattleMenu_CurPos)
                    {
                        BattleMenu_CurPos--;
                    }
                    if ((battleStatus->curButtonsHeld & (BUTTON_STICK_RIGHT | BUTTON_STICK_DOWN)) &&
                        BattleMenu_CurPos < BattleMenu_MaxIdx)
                    {
                        BattleMenu_CurPos++;
                    }
                }

                if (BattleMenu_PrevPos != BattleMenu_CurPos) {
                    D_802AD004 = 1;
                    sfx_play_sound(SOUND_MENU_CHANGE_TAB);
                }
            }
            break;
        case BTL_MENU_STATE_OPENED_SUBMENU:
            BattleMenuAlpha = 100;
            return BattleMenu_CurPos + BattleMenu_HomePos + 1;
        case BTL_MENU_STATE_UNK_A:
            D_802AD001 = 0;
            D_802AD006 = 0;
            BattleMenuState = BTL_MENU_STATE_UNK_B;
            return BattleMenu_CurPos + BattleMenu_HomePos + 1;
        case BTL_MENU_STATE_UNK_B:
            return BattleMenu_CurPos + BattleMenu_HomePos + 1;
        case BTL_MENU_STATE_UNK_14:
            D_802AD001 = 3;
            D_802AD006 = 255;
            BattleMenuState = BTL_MENU_STATE_ACCEPT_INPUT;
            return BattleMenu_CurPos + BattleMenu_HomePos + 1;
        case BTL_MENU_STATE_UNK_1E:
            D_802AD001 = 3;
            D_802AD006 = 255;
            BattleMenuState = BTL_MENU_STATE_OPENED_SUBMENU;
            break;
        case BTL_MENU_STATE_SHOW_DISABLED_POPUP:
            btl_show_battle_message(BattleMenuDisableMsg, 90);
            BattleMenuState = BTL_MENU_STATE_AWAIT_DISABLED_POPUP;
            break;
        case BTL_MENU_STATE_AWAIT_DISABLED_POPUP:
            if (btl_is_popup_displayed()) {
                break;
            }
            BattleMenuDisableMsg = -1;
            BattleMenuState = BTL_MENU_STATE_ACCEPT_INPUT;
            break;
    }
    return 0;
}

void btl_main_menu_draw(void) {
    s32 id;
    s32 opacity;
    f32 theta;
    s32 cond;
    f32 x, y;
    f32 scale;
    s32 i;
    s32 l, t;

    switch (BattleMenuState) {
        case BTL_MENU_STATE_UNK_1:
            func_80144218(-1);
            id = HID_ProjectorReelB;
            hud_element_set_transform_rotation(id, 0.0f, 0.0f, 0.0f);
            hud_element_set_alpha(id, (D_802AD006 * 254) / 255);
            hud_element_set_render_pos(id, 3940 - D_802AD00A, D_802AD00A + 212);
            func_80144238(id);
            id = HID_ProjectorReelA;
            hud_element_set_alpha(id, (D_802AD006 * 254) / 255);
            hud_element_set_render_pos(id, 40 - D_802AD00A, D_802AD00A + 212);
            func_80144238(id);
            break;
        case BTL_MENU_STATE_OPENED_SUBMENU:
        case BTL_MENU_STATE_ACCEPT_INPUT:
        case BTL_MENU_STATE_UNK_A:
        case BTL_MENU_STATE_UNK_14:
        case BTL_MENU_STATE_UNK_1E:
            opacity = (D_802AD006 * BattleMenuAlpha) / 255;
            func_80144218(-1);
            theta = (D_802AD100 - BattleMenu_CurPos) * 28;

            cond = FALSE;
            if (BattleMenu_WheelAngle > theta) {
                BattleMenu_WheelAngle -= D_802AD070;
                if (BattleMenu_WheelAngle < theta) {
                    BattleMenu_WheelAngle = theta;
                    cond = TRUE;
                }
            } else if (BattleMenu_WheelAngle < theta) {
                BattleMenu_WheelAngle += D_802AD070;
                if (BattleMenu_WheelAngle > theta) {
                    BattleMenu_WheelAngle = theta;
                    cond = TRUE;
                }
            } else {
                cond = TRUE;
            }

            if (!cond) {
                D_802AD070 = (D_802AD070 * (D_802AD070 + 1.0) * (D_802AD070 + 1.0));
            } else {
                D_802AD004 = 0;
                D_802AD070 = 0.3f;
            }

            theta = BattleMenu_WheelAngle;
            for (i = 0; i < BattleMenu_NumOptions; i++, theta += 28.0f) {
                x = 0.0f;
                y = 0.0f;
                add_vec2D_polar(&x, &y, 87.0f, theta);
                id = HID_Spotlights[i];
                x = BattleMenu_BasePosX + x;
                y = BattleMenu_BasePosY + y;
                hud_element_set_transform_pos(id, x, -y, 0.0f);
                hud_element_set_render_pos(id, 0, 0);
                hud_element_set_alpha(id, (opacity * 150) / 255);

                if (theta == 56.0f && cond == TRUE) {
                    hud_element_set_scale(id, 1.6f);
                } else {
                    hud_element_set_scale(id, 1.0f);
                }

                func_80144238(id);
                if (i == BattleMenu_HomePos + BattleMenu_CurPos) {
                    x = 0.0f;
                    y = 0.0f;
                    add_vec2D_polar(&x, &y, 87.0f, 56.0f);
                    x = BattleMenu_BasePosX + x;
                    y = BattleMenu_BasePosY + y;
                    id = HID_HighlightSpot;
                    hud_element_set_transform_pos(id, x, -y, 0.0f);
                    hud_element_set_render_pos(id, 0, 0);
                    hud_element_set_alpha(id, (opacity * 180) / 255);
                    hud_element_set_scale(id, 1.2f);
                    if (!cond) {
                        hud_element_set_flags(id, HUD_ELEMENT_FLAG_DISABLED);
                    } else {
                        hud_element_clear_flags(id, HUD_ELEMENT_FLAG_DISABLED);
                    }
                    func_80144238(id);
                }
            }
            theta = (D_802AD100 - BattleMenu_CurPos) * 28;
            scale = (fabsf(fabsf((BattleMenu_WheelAngle - theta) * (45.0 / 28.0)) - 22.5) / 22.5) + 0.01;
            if (cond) {
                scale = 1.0f;
            }

            id = HID_ProjectorBeam;
            hud_element_set_transform_rotation_pivot(id, 0, 0);
            hud_element_set_transform_rotation(id, 0.0f, 0.0f, -43.0f);
            hud_element_set_scale(id, scale);
            hud_element_set_transform_scale(id, 1.0f, 1.8f, 1.0f);
            hud_element_set_alpha(id, (opacity * 200) / 255);
            hud_element_set_render_pos(id, 79, 176);
            func_80144238(id);

            id = HID_ProjectorReelB;
            theta = (D_802AD100 - BattleMenu_CurPos) * 28;
            scale = (BattleMenu_WheelAngle - theta) * (45.0 / 28.0);
            hud_element_set_transform_rotation(id, 0.0f, 0.0f, -scale);
            hud_element_set_transform_rotation_pivot(id, 18, -20);
            hud_element_set_scale(id, 0.95f);
            hud_element_set_alpha(id, (opacity * 254) / 255);
            hud_element_set_render_pos(id, 40 - D_802AD00A, D_802AD00A + 212);
            func_80144238(id);

            id = HID_ProjectorReelA;
            hud_element_set_alpha(id, (opacity * 254) / 255);
            hud_element_set_render_pos(id, 40 - D_802AD00A, D_802AD00A + 212);
            hud_element_set_scale(id, 1.0f);
            func_80144238(id);

            theta = BattleMenu_WheelAngle;
            for (i = 0; i < BattleMenu_NumOptions; i++, theta += 28.0f) {
                x = 0.0f;
                y = 0.0f;
                add_vec2D_polar(&x, &y, 87.0f, theta);
                l = x = BattleMenu_BasePosX + x;
                t = y = BattleMenu_BasePosY + y;
                btl_draw_prim_quad(0, 0, 0, 0, l - 12, t - 12, 24, 24);
                id = HID_OptionIcons[i];
                hud_element_set_render_pos(id, l, t);
                hud_element_set_alpha(id, (opacity * 180) / 255);
                if (i == BattleMenu_HomePos + BattleMenu_CurPos) {
                    hud_element_set_alpha(id, opacity);
                }
                hud_element_draw_clipped(id);
            }

            if (cond) {
                l = BattleMenu_BasePosX + 20;
                t = BattleMenu_BasePosY - 34;
                btl_draw_prim_quad(0, 0, 0, 0, l + 26, t, 48, 16);
                draw_msg(BattleMenu_TitleMessages[BattleMenu_CurPos + BattleMenu_HomePos], l, t, opacity, MSG_PAL_35, 0);
            }

            if ((gBattleStatus.flags1 & BS_FLAGS1_TUTORIAL_BATTLE) || (gBattleStatus.flags2 & BS_FLAGS2_PEACH_BATTLE)) {
                BattleMenu_ShowSwapIcons = FALSE;
            }

            if (BattleMenu_ShowSwapIcons) {
                id = HID_SwapBackground;
                hud_element_set_alpha(id, (opacity * 200) / 255);
                hud_element_draw_clipped(id);
                id = HID_SwapZ;
                hud_element_set_alpha(id, opacity);
                hud_element_draw_clipped(id);
                id = HID_SwapArrowLeft;
                hud_element_set_alpha(id, opacity);
                hud_element_draw_clipped(id);
                id = HID_SwapArrowRight;
                hud_element_set_alpha(id, opacity);
                hud_element_draw_clipped(id);
            }
            break;
    }
}

s32 can_switch_to_player(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* player = battleStatus->playerActor;

    if (battleStatus->flags2 & BS_FLAGS2_PLAYER_TURN_USED) {
        return FALSE;
    } else {
        s8 debuff = player->debuff;
        s32 playerCantMove = FALSE;

        if (player->koStatus == STATUS_KEY_DAZE) {
            playerCantMove = TRUE;
        }
        if (debuff == STATUS_KEY_POISON) {
            playerCantMove = FALSE;
        }
        if (debuff == STATUS_KEY_SHRINK) {
            playerCantMove = FALSE;
        }
        if (debuff == STATUS_KEY_SLEEP) {
            playerCantMove = TRUE;
        }
        if (debuff == STATUS_KEY_FEAR) {
            playerCantMove = TRUE;
        }
        if (debuff == STATUS_KEY_DIZZY) {
            playerCantMove = TRUE;
        }
        if (debuff == STATUS_KEY_PARALYZE) {
            playerCantMove = TRUE;
        }
        if (debuff == STATUS_KEY_FROZEN) {
            playerCantMove = TRUE;
        }
        if (debuff == STATUS_KEY_STOP) {
            playerCantMove = TRUE;
        }
        if (player->stoneStatus == STATUS_KEY_STONE) {
            playerCantMove = TRUE;
        }
        if (battleStatus->outtaSightActive) {
            playerCantMove = TRUE;
        }
        return !playerCantMove;
    }
}

s32 can_switch_to_partner(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    Actor* partner = battleStatus->partnerActor;
    s8 partnerDebuff;
    s32 partnerCantMove;

    if (battleStatus->flags2 & BS_FLAGS2_PARTNER_TURN_USED || partner == PARTNER_NONE || partner->flags & ACTOR_FLAG_NO_ATTACK) {
        return FALSE;
    }

    partnerDebuff = partner->debuff;
    partnerCantMove = FALSE;

    if (partner->koStatus == STATUS_KEY_DAZE) {
        partnerCantMove = TRUE;
    }
    if (partnerDebuff == STATUS_KEY_POISON) {
        partnerCantMove = FALSE;
    }
    if (partnerDebuff == STATUS_KEY_SHRINK) {
        partnerCantMove = FALSE;
    }
    if (partnerDebuff == STATUS_KEY_SLEEP) {
        partnerCantMove = TRUE;
    }
    if (partnerDebuff == STATUS_KEY_FEAR) {
        partnerCantMove = TRUE;
    }
    if (partnerDebuff == STATUS_KEY_PARALYZE) {
        partnerCantMove = TRUE;
    }
    if (partnerDebuff == STATUS_KEY_FROZEN) {
        partnerCantMove = TRUE;
    }
    if (partnerDebuff == STATUS_KEY_STOP) {
        partnerCantMove = TRUE;
    }
    if (partner->stoneStatus == STATUS_KEY_STONE) {
        partnerCantMove = TRUE;
    }
    return !partnerCantMove;
}
