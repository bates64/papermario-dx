#include "battle/battle.h"
#include "hud_element.h"
#include "battle/action_cmd.h"

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

extern HudScript HES_GreenArrowDown;
extern HudScript HES_GreenArrowUp;
extern HudScript HES_HandPointer;
extern HudScript HES_HandPointDownLoop;
extern HudScript HES_HandPointLeftLoop;

extern HudScript HES_FPCost;
extern HudScript HES_FPCostReduced;
extern HudScript HES_FPCostReducedTwice;
extern HudScript HES_POWCost;
extern HudScript HES_POWCostReduced;
extern HudScript HES_POWCostReducedTwice;
extern HudScript HES_StatusFlower;
extern HudScript HES_NotEnoughFP;
extern HudScript HES_NotEnoughPOW;
extern HudScript HES_ProjectorBeam;
extern HudScript HES_ProjectorReel;
extern HudScript HES_ProjectorSpot;
extern HudScript HES_SwapArrowLeft;
extern HudScript HES_SwapArrowRight;
extern HudScript HES_SwapBackground;
extern HudScript HES_SwapZ;

extern IconHudScriptPair gItemHudScripts[];

extern s32 MenuIndexFromPartnerID[];

s16 D_802AB340[] = { 28, 40 };

s16 D_802AB344[] = { 0, -2 };

IconHudScriptPair battle_menu_ItemHudScripts = { &HES_MenuItem, &HES_MenuItemDisabled };

IconHudScriptPair battle_menu_StarPowerHudScripts = { &HES_MenuStarPower, &HES_MenuStarPowerDisabled };

IconHudScriptPair battle_menu_StarPowerMovesHudScripts[] = {
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

IconHudScriptPair battle_menu_StrategiesHudScript = { &HES_MenuStrategies, &HES_MenuStrategiesDisabled };

IconHudScriptPair DoNothingHudScripts = { &HES_MenuDoNothing, &HES_MenuDoNothingDisabled };

IconHudScriptPair FleeHudScripts = { &HES_MenuFlee, &HES_MenuFleeDisabled };

s32 BattleMenu_LeftJustMessages[] = {
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

s32 BattleMenu_CenteredMessages[] = {
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
BSS PopupMenu D_802ACCD0;
BSS s8 BattleMenuState;
BSS s8 D_802AD001;
BSS s8 BattleMenu_CurPos;
BSS s8 BattleMenu_PrevPos;
BSS s8 D_802AD004;
BSS s16 D_802AD006;
BSS s16 BattleMenuAlpha;
BSS s16 D_802AD00A;
BSS s32 D_802AD010[6];
BSS s32 D_802AD028[6];
BSS s32 D_802AD040;
BSS s32 D_802AD044;
BSS s32 D_802AD048;
BSS s32 D_802AD04C;
BSS s32 D_802AD050;
BSS s32 D_802AD054;
BSS s32 D_802AD058;
BSS s32 D_802AD05C;
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
BSS s8 battle_menu_moveState;
BSS s8 battle_menu_moveCursorPos;
BSS s8 D_802AD10A;
BSS s8 D_802AD10B;
BSS s8 battle_menu_moveScrollLine;
BSS s8 D_802AD10D;
BSS s8 D_802AD10E;
BSS s8 D_802AD10F;
BSS s16 battle_menu_moveScrollOffset;
BSS s16 D_802AD112;
BSS s16 BattleMenu_Moves_TextColor;
BSS s16 BattleMenu_Moves_TextAlpha;
BSS HudElemID BattleMenu_Moves_CursorID;
BSS HudElemID BattleMenu_Moves_UpArrowID;
BSS HudElemID BattleMenu_Moves_DownArrowID;
BSS HudElemID BattleMenu_Moves_OptionIDs[24];
BSS HudElemID BattleMenu_Moves_TitleID;
BSS HudElemID BattleMenu_Moves_OptionCostUnitIDs[24];
BSS s16 BattleMenu_Moves_PosX;
BSS s16 BattleMenu_Moves_PosY;
BSS s32 BattleMenu_Moves_OptionIndexMap[24];
BSS s32 D_802AD258;
BSS HudScript* battle_menu_moveOptionIconScripts[24];
BSS s32 battle_menu_moveOptionNames[24];
BSS s32 battle_menu_moveOptionDisplayCosts[24];
BSS s32 battle_menu_moveOptionDisplayCostReductions[24];
BSS s32 battle_menu_moveOptionDisplayCostReductionColors[24];
BSS s32 battle_menu_moveOptionBPCosts[24];
BSS s32 BattleMenu_UsingSpiritsSubmenu;
BSS s32 BattleMenu_Moves_OptionCount;
BSS s32 D_802AD4A8;
BSS s32 BattleMenu_Moves_OptionIndices[24];
BSS s32 BattleMenu_Moves_OptionEnabled[24];
BSS s32 BattleMenu_Moves_OptionDescMessages[24];
BSS s8 BattleMenu_Moves_OptionSortPriority[24];
BSS s8 BattleMenu_Moves_OptionCantUseMessages[24];
BSS s32 battle_menu_moveOptionActive;
BSS s8 BattleSubmenuStratsState;
BSS s8 StratsMenuPos;
BSS s8 OldStratsMenuPos;
BSS s8 ShowingErrorMessage;
BSS s8 D_802AD608;
BSS s8 D_802AD609;
BSS s8 StratsMenuLines;
BSS s8 D_802AD60B;
BSS s16 D_802AD60C;
BSS s16 D_802AD60E;
BSS s16 StratsErrorCode;
BSS s16 D_802AD612;
BSS s8 D_802AD614;
BSS s32 D_802AD618;
BSS HudElemID HID_GreenArrowUp;
BSS HudElemID HID_GreenArrowDown;
BSS s32 D_802AD624;

BSS s32 D_802AD628[5];
BSS s16 D_802AD63C;
BSS s16 D_802AD63E;
BSS HudScript* StratsOptionHudScript[6];
BSS s32 D_802AD658[5]; // msg IDs
BSS s32 D_802AD66C;
BSS s32 StratsMenuLastPos;

BSS s32 D_802AD678[6];
BSS b32 StratsOptionEnabled[6];
BSS s32 StratsOptionMessage[5];
BSS s32 StratsOptionError[6];
BSS s32 D_802AD6D4;

void create_battle_popup_menu(PopupMenu* popup);

void btl_menu_moves_draw_content(void* data, s32 x, s32 y);
void btl_menu_moves_show_title(void* data, s32 x, s32 y);
void btl_menu_moves_show_icon(void* data, s32 x, s32 y);
void btl_menu_moves_show_desc(void* data, s32 x, s32 y);
void btl_menu_moves_show_error(void* data, s32 x, s32 y);
void btl_menu_strats_draw_content(void* data, s32 x, s32 y);
void btl_menu_strats_show_title(void* data, s32 x, s32 y);
void btl_menu_strats_show_desc(void* data, s32 x, s32 y);
void btl_menu_strats_show_error(void* data, s32 x, s32 y);

void btl_init_menu_items(void);
void btl_check_can_change_partner(void);
void func_800F52BC(void);
void func_800F16CC(void);

void btl_init_menu_boots(void);
void btl_init_menu_hammer(void);

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

// (after submenu closed/cancelled)
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
        s32* icons1 = D_802AD010;
        s32* icons2 = D_802AD028;

        hud_element_free(icons1[i]);
        hud_element_free(icons2[i]);
    }

    hud_element_free(D_802AD040);
    hud_element_free(D_802AD044);
    hud_element_free(D_802AD048);
    hud_element_free(D_802AD04C);
    hud_element_free(D_802AD05C);
    hud_element_free(D_802AD050);
    hud_element_free(D_802AD054);
    hud_element_free(D_802AD058);
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
                D_802AD010[i] = hid = hud_element_create(BattleMenu_HudScripts[i]);
                hud_element_set_render_depth(hid, 5);
                hud_element_set_flags(hid, HUD_ELEMENT_FLAG_FILTER_TEX);
                hud_element_set_flags(hid, HUD_ELEMENT_FLAG_80);
                hud_element_set_flags(hid, HUD_ELEMENT_FLAG_DISABLED);
                hud_element_set_scale(hid, 0.75f);

                D_802AD028[i] = hid = hud_element_create(&HES_ProjectorSpot);
                hud_element_create_transform_B(hid);
                hud_element_set_render_depth(hid, 10);
                hud_element_set_flags(hid, HUD_ELEMENT_FLAG_80);
                hud_element_set_flags(hid, HUD_ELEMENT_FLAG_FILTER_TEX);
                hud_element_set_flags(hid, HUD_ELEMENT_FLAG_DISABLED);
            }

            D_802AD040 = hid = hud_element_create(&HES_ProjectorSpot);
            hud_element_create_transform_B(hid);
            hud_element_set_render_depth(hid, 7);
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_80);
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_FILTER_TEX);
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_DISABLED);

            D_802AD044 = hid = hud_element_create(&HES_ProjectorReel);
            hud_element_create_transform_B(hid);
            hud_element_set_render_depth(hid, 0);
            hud_element_set_render_pos(hid, 40, 212);
            hud_element_set_tint(hid, 0, 91, 127);
            hud_element_set_transform_rotation_pivot(hid, 16, -16);
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_80);
            hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_FILTER_TEX);
            hud_element_set_alpha(hid, 240);

            D_802AD048 = hid = hud_element_create(&HES_ProjectorReel);
            hud_element_create_transform_B(hid);
            hud_element_set_render_depth(hid, 2);
            hud_element_set_render_pos(hid, 39, 212);
            hud_element_set_tint(hid, 0, 91, 127);
            hud_element_set_transform_rotation_pivot(hid, 16, -16);
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_80);
            hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_FILTER_TEX);
            hud_element_set_alpha(hid, 240);

            D_802AD04C = hid = hud_element_create(&HES_ProjectorBeam);
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

            D_802AD05C = hid = hud_element_create(&HES_SwapBackground);
            hud_element_set_render_depth(hid, 0);
            hud_element_set_render_pos(hid, 97, 208);
            hud_element_set_tint(hid, 255, 255, 255);
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_80);
            hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_FILTER_TEX);
            hud_element_set_alpha(hid, 230);

            D_802AD050 = hid = hud_element_create(&HES_SwapZ);
            hud_element_set_render_depth(hid, 5);
            hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_FILTER_TEX);
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_80);
            hud_element_set_render_pos(hid, 94, 209);

            D_802AD054 = hid = hud_element_create(&HES_SwapArrowLeft);
            hud_element_set_render_depth(hid, 5);
            hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_FILTER_TEX);
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_80);
            hud_element_set_render_pos(hid, 81, 210);

            D_802AD058 = hid = hud_element_create(&HES_SwapArrowRight);
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
                        hid = D_802AD04C;
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
                        hid = D_802AD010[i];
                        hud_element_set_render_pos(hid, l, t);
                        hud_element_clear_flags(hid, HUD_ELEMENT_FLAG_DISABLED);

                        hid = D_802AD028[i];
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
                    hid = D_802AD040;
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
            id = D_802AD048;
            hud_element_set_transform_rotation(id, 0.0f, 0.0f, 0.0f);
            hud_element_set_alpha(id, (D_802AD006 * 254) / 255);
            hud_element_set_render_pos(id, 3940 - D_802AD00A, D_802AD00A + 212);
            func_80144238(id);
            id = D_802AD044;
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
                id = D_802AD028[i];
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
                    id = D_802AD040;
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

            id = D_802AD04C;
            hud_element_set_transform_rotation_pivot(id, 0, 0);
            hud_element_set_transform_rotation(id, 0.0f, 0.0f, -43.0f);
            hud_element_set_scale(id, scale);
            hud_element_set_transform_scale(id, 1.0f, 1.8f, 1.0f);
            hud_element_set_alpha(id, (opacity * 200) / 255);
            hud_element_set_render_pos(id, 79, 176);
            func_80144238(id);

            id = D_802AD048;
            theta = (D_802AD100 - BattleMenu_CurPos) * 28;
            scale = (BattleMenu_WheelAngle - theta) * (45.0 / 28.0);
            hud_element_set_transform_rotation(id, 0.0f, 0.0f, -scale);
            hud_element_set_transform_rotation_pivot(id, 18, -20);
            hud_element_set_scale(id, 0.95f);
            hud_element_set_alpha(id, (opacity * 254) / 255);
            hud_element_set_render_pos(id, 40 - D_802AD00A, D_802AD00A + 212);
            func_80144238(id);

            id = D_802AD044;
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
                id = D_802AD010[i];
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
                id = D_802AD05C;
                hud_element_set_alpha(id, (opacity * 200) / 255);
                hud_element_draw_clipped(id);
                id = D_802AD050;
                hud_element_set_alpha(id, opacity);
                hud_element_draw_clipped(id);
                id = D_802AD054;
                hud_element_set_alpha(id, opacity);
                hud_element_draw_clipped(id);
                id = D_802AD058;
                hud_element_set_alpha(id, opacity);
                hud_element_draw_clipped(id);
            }
            break;
    }
}

// Very similar to func_802A45D8 - maybe can be used to reduce fake matches there
void func_802A2684(void) {
    if (D_802AD4A8 >= BattleMenu_Moves_OptionCount) {
        D_802AD4A8 = BattleMenu_Moves_OptionCount - 1;
    }

    battle_menu_moveState = BTL_SUBMENU_MOVES_INIT;
    battle_menu_moveScrollLine = 0;
    battle_menu_moveCursorPos = D_802AD4A8;
    D_802AD10A = D_802AD4A8;
    D_802AD10E = BattleMenu_Moves_OptionCount;

    if (D_802AD10E > 6) {
        D_802AD10E = 6;
    }

    D_802AD10D = 6;
    if (BattleMenu_Moves_OptionCount < 6) {
        D_802AD10D = BattleMenu_Moves_OptionCount;
    }

    BattleMenu_Moves_TextAlpha = 255;
    D_802AD10F = 1;

    if (D_802AD10A < 0) {
        battle_menu_moveScrollLine = D_802AD10A;
    }
    if (D_802AD10A >= D_802AD10D) {
        battle_menu_moveScrollLine = D_802AD10A + 1 - D_802AD10E;
    }

    D_802AD10D = battle_menu_moveScrollLine + 6;
    if (D_802AD10D > BattleMenu_Moves_OptionCount) {
        D_802AD10D = BattleMenu_Moves_OptionCount;
    }

    battle_menu_moveScrollOffset = -battle_menu_moveScrollLine * 13;
    D_802AD112 = (D_802AD10A - battle_menu_moveScrollLine) * 13;
    battle_menu_moveOptionActive = 0;
}

void func_802A27D0(void) {
    battle_menu_moveState = BTL_SUBMENU_MOVES_HIDE_INIT;
}

void func_802A27E4(void) {
    s32 i;

    set_window_update(WIN_BTL_MOVES_MENU, WINDOW_UPDATE_HIDE);

    if (!BattleMenu_UsingSpiritsSubmenu) {
        set_window_update(WIN_BTL_MOVES_TITLE, WINDOW_UPDATE_HIDE);
        set_window_update(WIN_BTL_MOVES_ICON, WINDOW_UPDATE_HIDE);
    } else {
        set_window_update(WIN_BTL_SPIRITS_TITLE, WINDOW_UPDATE_HIDE);
        set_window_update(WIN_BTL_SPIRITS_ICON, WINDOW_UPDATE_HIDE);
    }

    set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_HIDE);

    for (i = 0; i < BattleMenu_Moves_OptionCount; i++) {
        hud_element_free(BattleMenu_Moves_OptionIDs[i]);
    }

    hud_element_free(BattleMenu_Moves_CursorID);
    hud_element_free(BattleMenu_Moves_UpArrowID);
    hud_element_free(BattleMenu_Moves_DownArrowID);
    hud_element_free(BattleMenu_Moves_TitleID);

    for (i = 0; i < BattleMenu_Moves_OptionCount; i++) {
        hud_element_free(BattleMenu_Moves_OptionCostUnitIDs[i]);
    }
}

void func_802A2910(void) {
    s32* moveOptionIconIDs;
    s32* moveOptionCostUnitIconIDs;
    s32 i;

    moveOptionIconIDs = BattleMenu_Moves_OptionIDs;

    for (i = 0; i < BattleMenu_Moves_OptionCount; i++) {
        hud_element_set_tint(moveOptionIconIDs[i], 255, 255, 255);
    }

    hud_element_set_tint(BattleMenu_Moves_CursorID, 255, 255, 255);
    hud_element_set_tint(BattleMenu_Moves_UpArrowID, 255, 255, 255);
    hud_element_set_tint(BattleMenu_Moves_DownArrowID, 255, 255, 255);
    hud_element_set_tint(BattleMenu_Moves_TitleID, 255, 255, 255);

    moveOptionCostUnitIconIDs = BattleMenu_Moves_OptionCostUnitIDs;

    for (i = 0; i < BattleMenu_Moves_OptionCount; i++) {
        hud_element_set_tint(moveOptionCostUnitIconIDs[i], 255, 255, 255);
    }

    hud_element_set_script(BattleMenu_Moves_CursorID, &HES_AnimatedHandPointer);
    set_window_update(WIN_BTL_MOVES_MENU, WINDOW_UPDATE_TRANSPARENT);

    if (!BattleMenu_UsingSpiritsSubmenu) {
        set_window_update(WIN_BTL_MOVES_TITLE, WINDOW_UPDATE_TRANSPARENT);
        set_window_update(WIN_BTL_MOVES_ICON, WINDOW_UPDATE_TRANSPARENT);
    } else {
        set_window_update(WIN_BTL_SPIRITS_TITLE, WINDOW_UPDATE_TRANSPARENT);
        set_window_update(WIN_BTL_SPIRITS_ICON, WINDOW_UPDATE_TRANSPARENT);
    }

    set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_SHOW);
    BattleMenu_Moves_TextColor = MSG_PAL_STANDARD;
    D_802AD10F = 1;
    BattleMenu_Moves_TextAlpha = 255;
    battle_menu_moveState = BTL_SUBMENU_MOVES_CHOOSING;
}

void func_802A2AB8(void) {
    s32* moveOptionIconIDs;
    s32* moveOptionCostUnitIconIDs;
    s32 i;

    set_window_update(WIN_BTL_MOVES_MENU, WINDOW_UPDATE_TRANSPARENT);

    if (!BattleMenu_UsingSpiritsSubmenu) {
        set_window_update(WIN_BTL_MOVES_TITLE, WINDOW_UPDATE_TRANSPARENT);
        set_window_update(WIN_BTL_MOVES_ICON, WINDOW_UPDATE_TRANSPARENT);
    } else {
        set_window_update(WIN_BTL_SPIRITS_TITLE, WINDOW_UPDATE_TRANSPARENT);
        set_window_update(WIN_BTL_SPIRITS_ICON, WINDOW_UPDATE_TRANSPARENT);
    }
    set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_SHOW);

    moveOptionIconIDs = BattleMenu_Moves_OptionIDs;

    for (i = 0; i < BattleMenu_Moves_OptionCount; i++) {
        hud_element_set_tint(moveOptionIconIDs[i], 255, 255, 255);
    }

    hud_element_set_tint(BattleMenu_Moves_CursorID, 255, 255, 255);
    hud_element_set_tint(BattleMenu_Moves_UpArrowID, 255, 255, 255);
    hud_element_set_tint(BattleMenu_Moves_DownArrowID, 255, 255, 255);
    hud_element_set_tint(BattleMenu_Moves_TitleID, 255, 255, 255);

    moveOptionCostUnitIconIDs = BattleMenu_Moves_OptionCostUnitIDs;

    for (i = 0; i < BattleMenu_Moves_OptionCount; i++) {
        hud_element_set_tint(moveOptionCostUnitIconIDs[i], 255, 255, 255);
    }

    hud_element_set_script(BattleMenu_Moves_CursorID, &HES_AnimatedHandPointer);
    BattleMenu_Moves_TextColor = MSG_PAL_STANDARD;
    D_802AD10F = 1;
    battle_menu_moveState = BTL_SUBMENU_MOVES_STATE_UNK_14;
}

void func_802A2C58(void) {
    set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_SHOW);
    battle_menu_moveState = BTL_SUBMENU_MOVES_STATE_UNK_1E;
}

s32 btl_submenu_moves_update(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    s32 moveX;
    s32 moveY;
    s32 msgWidth;
    s32 msgHeight;
    s32 msgX;
    s32 msgID;
    s32 cond;
    HudElemID hid;
    s32 i;
    s32 j;

    switch (battle_menu_moveState) {
        case BTL_SUBMENU_MOVES_INIT:
            battle_menu_moveScrollOffset = -battle_menu_moveScrollLine * 13;
            D_802AD112 = (battle_menu_moveCursorPos - battle_menu_moveScrollLine) * 13;
            BattleMenu_Moves_PosX = 20;
            BattleMenu_Moves_PosY = 68;

            for (i = 0; i < BattleMenu_Moves_OptionCount; i++) {
                BattleMenu_Moves_OptionIndexMap[i] = i;
            }

            if (!BattleMenu_UsingSpiritsSubmenu) {
                for (i = 0; i < (BattleMenu_Moves_OptionCount - 1); i++) {
                    for (j = i + 1; j < BattleMenu_Moves_OptionCount; j++) {
                        s32 temp1 = BattleMenu_Moves_OptionIndexMap[i];
                        s32 temp2 = BattleMenu_Moves_OptionIndexMap[j];

                        if (BattleMenu_Moves_OptionSortPriority[temp1] < BattleMenu_Moves_OptionSortPriority[temp2]) {
                            continue;
                        }

                        if (
                            BattleMenu_Moves_OptionSortPriority[temp1] != BattleMenu_Moves_OptionSortPriority[temp2] ||
                            (battle_menu_moveOptionDisplayCosts[temp1] >= battle_menu_moveOptionDisplayCosts[temp2]) &&
                            (battle_menu_moveOptionDisplayCosts[temp1] != battle_menu_moveOptionDisplayCosts[temp2] ||
                                battle_menu_moveOptionBPCosts[temp1] >= battle_menu_moveOptionBPCosts[temp2])
                        )
                        {
                            s32 swapTmp = BattleMenu_Moves_OptionIndexMap[i];
                            BattleMenu_Moves_OptionIndexMap[i] = BattleMenu_Moves_OptionIndexMap[j];
                            BattleMenu_Moves_OptionIndexMap[j] = swapTmp;
                        }
                    }
                }
            }

            for (i = 0; i < BattleMenu_Moves_OptionCount; i++) {
                hid = hud_element_create(battle_menu_moveOptionIconScripts[BattleMenu_Moves_OptionIndexMap[i]]);
                BattleMenu_Moves_OptionIDs[i] = hid;
                hud_element_set_scale(hid, 0.45f);
                hud_element_set_flags(hid, HUD_ELEMENT_FLAG_FILTER_TEX | HUD_ELEMENT_FLAG_80);
            }

            hid = hud_element_create(&HES_AnimatedHandPointer);
            BattleMenu_Moves_CursorID = hid;
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_DROP_SHADOW | HUD_ELEMENT_FLAG_80);
            hud_element_set_render_pos(hid, BattleMenu_Moves_PosX, BattleMenu_Moves_PosY);

            hid = hud_element_create(&HES_GreenArrowUp);
            BattleMenu_Moves_UpArrowID = hid;
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_DROP_SHADOW | HUD_ELEMENT_FLAG_80);
            hud_element_set_render_pos(hid, BattleMenu_Moves_PosX + 39, BattleMenu_Moves_PosY - 7);

            hid = hud_element_create(&HES_GreenArrowDown);
            BattleMenu_Moves_DownArrowID = hid;
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_DROP_SHADOW | HUD_ELEMENT_FLAG_80);
            hud_element_set_render_pos(hid, BattleMenu_Moves_PosX + 39, BattleMenu_Moves_PosY + 78);

            if (!BattleMenu_UsingSpiritsSubmenu) {
                hid = hud_element_create(&HES_StatusFlower);
                BattleMenu_Moves_TitleID = hid;
                hud_element_set_flags(hid, HUD_ELEMENT_FLAG_80);
            } else {
                hid = hud_element_create(&HES_MenuStarPower);
                BattleMenu_Moves_TitleID = hid;
                hud_element_set_scale(hid, 0.75f);
                hud_element_set_flags(hid, HUD_ELEMENT_FLAG_80);
            }
            hud_element_set_render_pos(hid, BattleMenu_Moves_PosX + 56, BattleMenu_Moves_PosY);

            for (i = 0; i < BattleMenu_Moves_OptionCount; i++) {
                if (!BattleMenu_UsingSpiritsSubmenu) {
                    switch (battle_menu_moveOptionDisplayCostReductionColors[i]) {
                        case 0:
                            hid = hud_element_create(&HES_FPCost);
                            BattleMenu_Moves_OptionCostUnitIDs[i] = hid;
                            break;
                        case 1:
                            hid = hud_element_create(&HES_FPCostReduced);
                            BattleMenu_Moves_OptionCostUnitIDs[i] = hid;
                            break;
                        default:
                            hid = hud_element_create(&HES_FPCostReducedTwice);
                            BattleMenu_Moves_OptionCostUnitIDs[i] = hid;
                            break;
                    }
                } else {
                    switch (battle_menu_moveOptionDisplayCostReductionColors[i]) {
                        case 0:
                            hid = hud_element_create(&HES_POWCost);
                            BattleMenu_Moves_OptionCostUnitIDs[i] = hid;
                            break;
                        case 1:
                            hid = hud_element_create(&HES_POWCostReduced);
                            BattleMenu_Moves_OptionCostUnitIDs[i] = hid;
                            break;
                        default:
                            hid = hud_element_create(&HES_POWCostReducedTwice);
                            BattleMenu_Moves_OptionCostUnitIDs[i] = hid;
                            break;
                    }
                }
                hud_element_set_flags(hid, HUD_ELEMENT_FLAG_80);
                hud_element_set_render_pos(hid, BattleMenu_Moves_PosX + 56, BattleMenu_Moves_PosY);
            }

            BattleMenu_Moves_TextColor = MSG_PAL_STANDARD;

            moveX = BattleMenu_Moves_PosX;
            moveY = BattleMenu_Moves_PosY;
            if (!BattleMenu_UsingSpiritsSubmenu) {
                set_window_properties(WIN_BTL_MOVES_MENU, moveX, moveY, 150, (D_802AD10E * 13) + 28, 0, btl_menu_moves_draw_content, NULL, -1);
                set_window_properties(WIN_BTL_MOVES_TITLE, moveX + 16, moveY - 6, 90, 16, 1, btl_menu_moves_show_title, NULL, -1);
                set_window_properties(WIN_BTL_MOVES_ICON, moveX + 114, moveY - 12, 32, 32, 1, btl_menu_moves_show_icon, NULL, -1);
            } else {
                set_window_properties(WIN_BTL_MOVES_MENU, moveX, moveY, 144, (D_802AD10E * 13) + 28, 0, btl_menu_moves_draw_content, NULL, -1);
                set_window_properties(WIN_BTL_SPIRITS_TITLE, moveX + 10, moveY - 6, 100, 16, 1, btl_menu_moves_show_title, 0, -1);
                set_window_properties(WIN_BTL_SPIRITS_ICON, moveX + 110, moveY - 12, 32, 35, 1, btl_menu_moves_show_icon, 0, -1);
            }

            set_window_properties(WIN_BTL_DESC_BOX, 20, 186, 280, 32, WINDOW_PRIORITY_20, btl_menu_moves_show_desc, NULL, -1);
            set_window_update(WIN_BTL_MOVES_MENU, WINDOW_UPDATE_SHOW);
            if (!BattleMenu_UsingSpiritsSubmenu) {
                set_window_update(WIN_BTL_MOVES_TITLE, WINDOW_UPDATE_SHOW);
                set_window_update(WIN_BTL_MOVES_ICON, WINDOW_UPDATE_SHOW);
            } else {
                set_window_update(WIN_BTL_SPIRITS_TITLE, WINDOW_UPDATE_SHOW);
                set_window_update(WIN_BTL_SPIRITS_ICON, WINDOW_UPDATE_SHOW);
            }
            set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_SHOW);

            do {
                cond = FALSE;
                if (battle_menu_moveCursorPos >= (battle_menu_moveScrollLine + D_802AD10D) - 1) {
                    battle_menu_moveScrollLine++;
                    if (battle_menu_moveScrollLine > BattleMenu_Moves_OptionCount - 6) {
                        battle_menu_moveScrollLine = BattleMenu_Moves_OptionCount - 6;
                        if (battle_menu_moveScrollLine < 0) {
                            battle_menu_moveScrollLine = 0;
                        }
                    } else {
                        cond = TRUE;
                    }
                }
            } while (cond);

            battle_menu_moveState = BTL_SUBMENU_MOVES_CHOOSING;
            D_802AD10D = battle_menu_moveScrollLine + 6;
            battle_menu_moveScrollOffset = -battle_menu_moveScrollLine * 13;
            D_802AD112 = (battle_menu_moveCursorPos - battle_menu_moveScrollLine) * 13;
            break;
        case BTL_SUBMENU_MOVES_CHOOSING:
            D_802AD10A = battle_menu_moveCursorPos;
            if (battleStatus->curButtonsHeld & (BUTTON_STICK_UP | BUTTON_Z)) {
                if (battle_menu_moveCursorPos > 0) {
                    battle_menu_moveCursorPos--;
                } else if (battleStatus->curButtonsPressed & (BUTTON_STICK_UP | BUTTON_Z)) {
                    battle_menu_moveCursorPos--;
                }
            }

            if (battleStatus->curButtonsHeld & (BUTTON_STICK_DOWN | BUTTON_R)) {
                if (battle_menu_moveCursorPos < BattleMenu_Moves_OptionCount - 1) {
                    battle_menu_moveCursorPos++;
                } else if (battleStatus->curButtonsPressed & (BUTTON_STICK_DOWN | BUTTON_R)) {
                    battle_menu_moveCursorPos++;
                }
            }

            if (battle_menu_moveCursorPos < 0) {
                battle_menu_moveCursorPos = BattleMenu_Moves_OptionCount - 1;
            }

            if (BattleMenu_Moves_OptionCount - 1 < battle_menu_moveCursorPos) {
                battle_menu_moveCursorPos = 0;
            }

            if (D_802AD10A != battle_menu_moveCursorPos) {
                hud_element_set_scale(BattleMenu_Moves_OptionIDs[D_802AD10A], 0.45f);
                sfx_play_sound(SOUND_MENU_CHANGE_SELECTION);
            }

            if (battle_menu_moveCursorPos < battle_menu_moveScrollLine + 1) {
                battle_menu_moveScrollLine--;
                if (battle_menu_moveScrollLine < 0) {
                    battle_menu_moveScrollLine = 0;
                }
            }

            if (battle_menu_moveCursorPos >= (D_802AD10D - 1)) {
                battle_menu_moveScrollLine++;
                if (battle_menu_moveScrollLine > BattleMenu_Moves_OptionCount - 6) {
                    battle_menu_moveScrollLine = BattleMenu_Moves_OptionCount - 6;
                    if (battle_menu_moveScrollLine < 0) {
                        battle_menu_moveScrollLine = 0;
                    }
                }
            }

            D_802AD10D = battle_menu_moveScrollLine + 6;
            if (battleStatus->curButtonsPressed & BUTTON_A) {
                if (BattleMenu_Moves_OptionEnabled[BattleMenu_Moves_OptionIndexMap[battle_menu_moveCursorPos]] == 1) {
                    sfx_play_sound(SOUND_MENU_NEXT);
                    battle_menu_moveState = BTL_SUBMENU_MOVES_SELECT;
                } else {
                    sfx_play_sound(SOUND_MENU_ERROR);
                    D_802AD258 = BattleMenu_Moves_OptionCantUseMessages[BattleMenu_Moves_OptionIndexMap[battle_menu_moveCursorPos]];
                    battle_menu_moveState = BTL_SUBMENU_MOVES_ERROR_INIT;
                }
                break;
            }

            if (battleStatus->curButtonsPressed & BUTTON_B) {
                sfx_play_sound(SOUND_MENU_BACK);
                func_802A27E4();
                battle_menu_moveState = BTL_SUBMENU_MOVES_CANCEL;
            }
            break;
        case BTL_SUBMENU_MOVES_SELECT:
            for (i = 0; i < BattleMenu_Moves_OptionCount; i++) {
                hid = BattleMenu_Moves_OptionIDs[i];
                hud_element_set_tint(hid, 160, 160, 160);
            }
            hud_element_set_tint(BattleMenu_Moves_CursorID, 160, 160, 160);
            hud_element_set_tint(BattleMenu_Moves_UpArrowID, 160, 160, 160);
            hud_element_set_tint(BattleMenu_Moves_DownArrowID, 160, 160, 160);
            hud_element_set_tint(BattleMenu_Moves_TitleID, 160, 160, 160);

            for (i = 0; i < BattleMenu_Moves_OptionCount; i++) {
                hid = BattleMenu_Moves_OptionCostUnitIDs[i];
                hud_element_set_tint(hid, 160, 160, 160);
            }

            hud_element_set_script(BattleMenu_Moves_CursorID, &HES_HandPointer);
            BattleMenu_Moves_TextColor = MSG_PAL_0D;
            set_window_update(WIN_BTL_MOVES_MENU, WINDOW_UPDATE_DARKENED);
            if (!BattleMenu_UsingSpiritsSubmenu) {
                set_window_update(WIN_BTL_MOVES_TITLE, WINDOW_UPDATE_DARKENED);
                set_window_update(WIN_BTL_MOVES_ICON, WINDOW_UPDATE_DARKENED);
            } else {
                set_window_update(WIN_BTL_SPIRITS_TITLE, WINDOW_UPDATE_DARKENED);
                set_window_update(WIN_BTL_SPIRITS_ICON, WINDOW_UPDATE_DARKENED);
            }
            set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_HIDE);
            if (!BattleMenu_UsingSpiritsSubmenu) {
                status_bar_stop_blinking_fp();
            } else {
                status_bar_stop_blinking_sp();
            }
            battle_menu_moveOptionActive = battle_menu_moveCursorPos;
            return BattleMenu_Moves_OptionIndexMap[battle_menu_moveCursorPos] + 1;
        case BTL_SUBMENU_MOVES_CANCEL:
            if (!BattleMenu_UsingSpiritsSubmenu) {
                status_bar_stop_blinking_fp();
            } else {
                status_bar_stop_blinking_sp();
            }
            return POPUP_RESULT_CANCEL;
        case BTL_SUBMENU_MOVES_HIDE_INIT:
            set_window_update(WIN_BTL_MOVES_MENU, WINDOW_UPDATE_HIDE);
            if (!BattleMenu_UsingSpiritsSubmenu) {
                set_window_update(WIN_BTL_MOVES_TITLE, WINDOW_UPDATE_HIDE);
                set_window_update(WIN_BTL_MOVES_ICON, WINDOW_UPDATE_HIDE);
            } else {
                set_window_update(WIN_BTL_SPIRITS_TITLE, WINDOW_UPDATE_HIDE);
                set_window_update(WIN_BTL_SPIRITS_ICON, WINDOW_UPDATE_HIDE);
            }
            set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_HIDE);
            if (!BattleMenu_UsingSpiritsSubmenu) {
                status_bar_stop_blinking_fp();
            } else {
                status_bar_stop_blinking_sp();
            }
            battle_menu_moveState = BTL_SUBMENU_MOVES_HIDE_HOLD;
            battle_menu_moveOptionActive = battle_menu_moveCursorPos;
            return BattleMenu_Moves_OptionIndexMap[battle_menu_moveCursorPos] + 1;
        case BTL_SUBMENU_MOVES_HIDE_HOLD:
            battle_menu_moveOptionActive = battle_menu_moveCursorPos;
            return BattleMenu_Moves_OptionIndexMap[battle_menu_moveCursorPos] + 1;
        case BTL_SUBMENU_MOVES_STATE_UNK_14:
            set_window_update(WIN_BTL_MOVES_MENU, WINDOW_UPDATE_SHOW);
            if (!BattleMenu_UsingSpiritsSubmenu) {
                set_window_update(WIN_BTL_MOVES_TITLE, WINDOW_UPDATE_SHOW);
                set_window_update(WIN_BTL_MOVES_ICON, WINDOW_UPDATE_SHOW);
            } else {
                set_window_update(WIN_BTL_SPIRITS_TITLE, WINDOW_UPDATE_SHOW);
                set_window_update(WIN_BTL_SPIRITS_ICON, WINDOW_UPDATE_SHOW);
            }
            set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_SHOW);
            battle_menu_moveState = BTL_SUBMENU_MOVES_CHOOSING;
            battle_menu_moveOptionActive = battle_menu_moveCursorPos;
            return BattleMenu_Moves_OptionIndexMap[battle_menu_moveCursorPos] + 1;
        case BTL_SUBMENU_MOVES_STATE_UNK_1E:
            set_window_update(WIN_BTL_MOVES_MENU, WINDOW_UPDATE_9);
            if (!BattleMenu_UsingSpiritsSubmenu) {
                set_window_update(WIN_BTL_MOVES_TITLE, WINDOW_UPDATE_9);
                set_window_update(WIN_BTL_MOVES_ICON, WINDOW_UPDATE_9);
            } else {
                set_window_update(WIN_BTL_SPIRITS_TITLE, WINDOW_UPDATE_9);
                set_window_update(WIN_BTL_SPIRITS_ICON, WINDOW_UPDATE_9);
            }
            set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_HIDE);
            battle_menu_moveState = BTL_SUBMENU_MOVES_SELECT;
            break;
        case BTL_SUBMENU_MOVES_ERROR_INIT:
            battle_menu_moveOptionActive = -1;
            battle_menu_moveState = BTL_SUBMENU_MOVES_ERROR_SHOW;
            return POPUP_RESULT_INVALID;
        case BTL_SUBMENU_MOVES_ERROR_SHOW:
            set_window_update(WIN_BTL_MOVES_MENU, WINDOW_UPDATE_HIDE);
            if (!BattleMenu_UsingSpiritsSubmenu) {
                set_window_update(WIN_BTL_MOVES_TITLE, WINDOW_UPDATE_HIDE);
                set_window_update(WIN_BTL_MOVES_ICON, WINDOW_UPDATE_HIDE);
            } else {
                set_window_update(WIN_BTL_SPIRITS_TITLE, WINDOW_UPDATE_HIDE);
                set_window_update(WIN_BTL_SPIRITS_ICON, WINDOW_UPDATE_HIDE);
            }
            set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_HIDE);

            msgID = MSG_Menus_Battle_CantSelectNow;
            if (D_802AD258 == 0) {
                if (!BattleMenu_UsingSpiritsSubmenu) {
                    msgID = MSG_Menus_NotEnoughFP;
                } else {
                    msgID = MSG_Menus_NotEnoughStarPower;
                }
            }

            msgWidth = get_msg_width(msgID, 0) + 23;
            msgHeight = D_802AB340[get_msg_lines(msgID) - 1];
            moveX = (SCREEN_WIDTH / 2) - (msgWidth / 2);
            set_window_properties(WIN_BTL_POPUP, moveX, 80, msgWidth, msgHeight, 20, btl_menu_moves_show_error, NULL, -1);
            set_window_update(WIN_BTL_POPUP, WINDOW_UPDATE_SHOW);
            D_802AD10B = 60;
            battle_menu_moveState = BTL_SUBMENU_MOVES_ERROR_DONE;
            return POPUP_RESULT_INVALID;
        case BTL_SUBMENU_MOVES_ERROR_DONE:
            if (gGameStatusPtr->pressedButtons[0] & (BUTTON_A | BUTTON_B)) {
                D_802AD10B = 0;
            }
            if (D_802AD10B != 0) {
                D_802AD10B--;
                return POPUP_RESULT_INVALID;
            }
            set_window_update(WIN_BTL_POPUP, WINDOW_UPDATE_HIDE);
            set_window_update(WIN_BTL_MOVES_MENU, WINDOW_UPDATE_SHOW);
            if (!BattleMenu_UsingSpiritsSubmenu) {
                set_window_update(WIN_BTL_MOVES_TITLE, WINDOW_UPDATE_SHOW);
                set_window_update(WIN_BTL_MOVES_ICON, WINDOW_UPDATE_SHOW);
            } else {
                set_window_update(WIN_BTL_SPIRITS_TITLE, WINDOW_UPDATE_SHOW);
                set_window_update(WIN_BTL_SPIRITS_ICON, WINDOW_UPDATE_SHOW);
            }
            set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_SHOW);
            battle_menu_moveState = BTL_SUBMENU_MOVES_CHOOSING;
            break;
    }
    return POPUP_RESULT_CHOOSING;
}

#if VERSION_IQUE
#define Y_VAR1 2
#define X_VAR1 104
#define X_VAR2 89
#else
#define Y_VAR1 0
#define X_VAR1 108
#define X_VAR2 93
#endif

void btl_menu_moves_draw_content(void* data, s32 x, s32 y) {
    s32 var_t0;
    s32 temp_f6;
    s32 xPos, yPos;
    s32 yRenderPos;
    s32 palette;
    s32 num;
    s32 v0;
    s32 a0;
    s32 idx;
    s32 id;
    s32 i;

    switch (battle_menu_moveState) {
        case -1:
        case 1:
        case 10:
        case 20:
        case 30:
        case 40:
        case 41:
            yPos = -battle_menu_moveScrollLine * 13;
            var_t0 = battle_menu_moveScrollOffset;
            temp_f6 = (yPos - var_t0) * 0.5;
            if (temp_f6 == 0) {
                var_t0 = yPos;
            } else {
                var_t0 += temp_f6;
            }
            battle_menu_moveScrollOffset = var_t0;

            xPos = x + 2;
            yPos = y + 18;
            var_t0 = yPos + 1 + (D_802AD10E * 13);
            gDPSetScissor(
                gMainGfxPos++, G_SC_NON_INTERLACE,
                xPos,
                yPos,
                x + 153,
                var_t0
            );

            xPos = x + 31;
            yPos = y + 19 + battle_menu_moveScrollOffset;

            idx = 0;
            for (i = 0; i < BattleMenu_Moves_OptionCount; i++, idx++) {
                if (i >= battle_menu_moveScrollLine - 1 && battle_menu_moveScrollLine + D_802AD10E >= i) {
                    palette = BattleMenu_Moves_TextColor;

                    if (BattleMenu_Moves_OptionEnabled[BattleMenu_Moves_OptionIndexMap[idx]] <= 0) {
                        palette = MSG_PAL_0B;
                    }

                    if (battle_menu_moveOptionNames[BattleMenu_Moves_OptionIndexMap[idx]] >= 0) {
                        draw_msg(
                            battle_menu_moveOptionNames[BattleMenu_Moves_OptionIndexMap[idx]],
                            xPos, yPos - Y_VAR1, BattleMenu_Moves_TextAlpha, palette, 1
                        );
                    }

                    if (BattleMenu_Moves_OptionEnabled[BattleMenu_Moves_OptionIndexMap[idx]] <= 0) {
                        a0 = battle_menu_moveOptionDisplayCostReductions[BattleMenu_Moves_OptionIndexMap[idx]];
                        v0 = battle_menu_moveOptionDisplayCosts[BattleMenu_Moves_OptionIndexMap[idx]];
                    } else {
                        a0 = battle_menu_moveOptionDisplayCostReductions[BattleMenu_Moves_OptionIndexMap[idx]];
                        v0 = battle_menu_moveOptionDisplayCosts[BattleMenu_Moves_OptionIndexMap[idx]];
                    }
                    num = v0 - a0;

                    if (v0 != 0 && num <= 0) {
                        num = 1;
                    }

                    if (!BattleMenu_UsingSpiritsSubmenu ) {
                        if (i == battle_menu_moveCursorPos) {
                            if (num == 0 || BattleMenu_Moves_OptionEnabled[BattleMenu_Moves_OptionIndexMap[idx]] <= 0) {
                                status_bar_stop_blinking_fp();
                            } else {
                                status_bar_start_blinking_fp();
                            }
                        }
                    } else {
                        if (i == battle_menu_moveCursorPos) {
                            if (num == 0 || BattleMenu_Moves_OptionEnabled[BattleMenu_Moves_OptionIndexMap[idx]] <= 0) {
                                status_bar_stop_blinking_sp();
                            } else {
                                a0 = battle_menu_moveOptionDisplayCosts[BattleMenu_Moves_OptionIndexMap[idx]];
                                status_bar_start_blinking_sp_bars(
                                    battle_menu_moveOptionDisplayCosts[BattleMenu_Moves_OptionIndexMap[idx]]
                                );
                            }
                        }
                    }

                    switch (battle_menu_moveOptionDisplayCostReductionColors[i]) {
                        case 0:
                            palette = MSG_PAL_STANDARD;
                            break;
                        case 1:
                            palette = MSG_PAL_37;
                            break;
                        default:
                            palette = MSG_PAL_38;
                            break;
                    }

                    if (BattleMenu_Moves_OptionEnabled[BattleMenu_Moves_OptionIndexMap[idx]] <= 0) {
                        palette = MSG_PAL_0B;
                    }

                    if (battle_menu_moveOptionDisplayCosts[BattleMenu_Moves_OptionIndexMap[idx]] != 0) {
                        id = BattleMenu_Moves_OptionCostUnitIDs[idx];

                        if (!BattleMenu_UsingSpiritsSubmenu) {
                            draw_number(
                                num, xPos + X_VAR1, yPos, DRAW_NUMBER_CHARSET_THIN, palette, BattleMenu_Moves_TextAlpha,
                                DRAW_NUMBER_STYLE_MONOSPACE | DRAW_NUMBER_STYLE_ALIGN_RIGHT
                            );
                            if (BattleMenu_Moves_OptionEnabled[BattleMenu_Moves_OptionIndexMap[idx]] <= 0) {
                                hud_element_set_script(id, &HES_NotEnoughFP);
                            }
                            yRenderPos = yPos + 7;
                            hud_element_set_render_pos(id, xPos + 116, yRenderPos);
                        } else {
                            draw_number(
                                num, xPos + X_VAR2, yPos, DRAW_NUMBER_CHARSET_THIN, palette, BattleMenu_Moves_TextAlpha,
                                DRAW_NUMBER_STYLE_MONOSPACE | DRAW_NUMBER_STYLE_ALIGN_RIGHT
                            );
                            if (BattleMenu_Moves_OptionEnabled[BattleMenu_Moves_OptionIndexMap[idx]] <= 0) {
                                hud_element_set_script(id, &HES_NotEnoughPOW);
                            }
                            yRenderPos = yPos + 7;
                            hud_element_set_render_pos(id, xPos + 102, yRenderPos);
                        }
                        hud_element_set_alpha(id, BattleMenu_Moves_TextAlpha);
                        hud_element_draw_without_clipping(id);
                    }
                }
                yPos += 13;
            }

            xPos = x + 24;
            yPos = battle_menu_moveScrollOffset + y + 24;

            idx = 0;
            for (i = 0; i < BattleMenu_Moves_OptionCount; i++, idx++) {
                if (i < battle_menu_moveScrollLine - 1) {
                    yPos += 13;
                } else if (battle_menu_moveScrollLine + D_802AD10E < i) {
                    yPos += 13;
                } else {
                    id = BattleMenu_Moves_OptionIDs[idx];
                    hud_element_set_render_pos(id, xPos, yPos);
                    hud_element_set_alpha(id, BattleMenu_Moves_TextAlpha);
                    hud_element_draw_without_clipping(id);
                    yPos += 13;
                }
            }

            yPos = (battle_menu_moveCursorPos - battle_menu_moveScrollLine) * 13;
            var_t0 = D_802AD112;
            temp_f6 = (yPos - D_802AD112) * 1.0;
            xPos = x + 10;
            if (temp_f6 == 0) {
                var_t0 = yPos;
            } else {
                var_t0 += temp_f6;
            }
            D_802AD112 = var_t0;
            yPos =  y + 26 + D_802AD112;

            id = BattleMenu_Moves_CursorID;
            hud_element_set_render_pos(id, xPos, yPos);
            hud_element_set_alpha(id, BattleMenu_Moves_TextAlpha);
            hud_element_draw_without_clipping(id);

            if (battle_menu_moveScrollLine > 0) {
                id = BattleMenu_Moves_UpArrowID;
                hud_element_set_render_pos(id, x + 72, y + 15);
                hud_element_set_alpha(id, BattleMenu_Moves_TextAlpha);
                hud_element_draw_clipped(id);
            }

            if (D_802AD10D < BattleMenu_Moves_OptionCount) {
                id = BattleMenu_Moves_DownArrowID;
                hud_element_set_render_pos(id, x + 72, y + 100);
                hud_element_set_alpha(id, BattleMenu_Moves_TextAlpha);
                hud_element_draw_clipped(id);
            }

            if (battle_menu_moveState == -1) {
                if (!BattleMenu_UsingSpiritsSubmenu) {
                    status_bar_stop_blinking_fp();
                } else {
                    status_bar_stop_blinking_sp();
                }
            }
            break;
    }
}

void btl_menu_moves_show_title(void* data, s32 x, s32 y) {
    s32 msgID;
    s32 posX;
    s32 posY;
    s32 opacity;
    s32 palette;

    if (!BattleMenu_UsingSpiritsSubmenu) {
        msgID = MSG_Menus_Abilities;
        posX = x + 16;
        posY = y + 2;
        opacity = BattleMenu_Moves_TextAlpha;
        palette = MSG_PAL_30;
    } else {
        msgID = MSG_Menus_StarSpirits;
        posX = x + 6;
        posY = y + 2;
        opacity = BattleMenu_Moves_TextAlpha;
        palette = MSG_PAL_31;
    }
    draw_msg(msgID, posX, posY, opacity, palette, DRAW_MSG_STYLE_MENU);
}

void btl_menu_moves_show_icon(void* data, s32 x, s32 y) {
    s32 icon = BattleMenu_Moves_TitleID;

    hud_element_set_render_pos(icon, x + 16, y + 15);
    hud_element_set_alpha(icon, BattleMenu_Moves_TextAlpha);
    hud_element_draw_clipped(icon);
}

void btl_menu_moves_show_desc(void* data, s32 x, s32 y) {
    switch (battle_menu_moveState) {
        case BTL_SUBMENU_MOVES_SELECT:
        case BTL_SUBMENU_MOVES_CHOOSING:
        case BTL_SUBMENU_MOVES_HIDE_INIT:
        case BTL_SUBMENU_MOVES_STATE_UNK_14:
        case BTL_SUBMENU_MOVES_STATE_UNK_1E:
            if (D_802AD10F != 0) {
                draw_msg(BattleMenu_Moves_OptionDescMessages[BattleMenu_Moves_OptionIndexMap[battle_menu_moveCursorPos]],
                            x + 8, y, BattleMenu_Moves_TextAlpha, BattleMenu_Moves_TextColor, 0);
            }
            break;
    }
}

void btl_menu_moves_show_error(void* data, s32 x, s32 y) {
    s32 posY = y;
    s32 posX;
    s32 msgID;

    posY += 6;
    posX = x + 11;

    if (D_802AD258 != 0) {
        msgID = MSG_Menus_Battle_CantSelectNow;
    } else if (!BattleMenu_UsingSpiritsSubmenu) {
        msgID = MSG_Menus_NotEnoughFP;
    } else {
        msgID = MSG_Menus_NotEnoughStarPower;
    }
    draw_msg(msgID, posX, posY + D_802AB344[get_msg_lines(msgID) - 1], 255, MSG_PAL_0F, 0);
}

void func_802A45D8(void) {
    s32 sixTemp;
    s8 temp802AD673;

    BattleSubmenuStratsState = BTL_SUBMENU_STRATS_STATE_INIT;
    StratsMenuPos = StratsMenuLastPos;
    OldStratsMenuPos = StratsMenuLastPos;
    D_802AD608 = 0;
    StratsMenuLines = D_802AD66C;

    if (StratsMenuLines > 6) {
        StratsMenuLines = 6;
    }

    D_802AD609 = sixTemp = 6;

    if (D_802AD609 > D_802AD66C) {
        D_802AD609 = D_802AD66C;
    }

    D_802AD624 = 255;
    D_802AD60B = 1;
    temp802AD673 = StratsMenuLastPos;

    if ((s8) StratsMenuLastPos < 0) {
        D_802AD608 = StratsMenuLastPos;
    }
    if ((s8) StratsMenuLastPos >= D_802AD609) {
        D_802AD608 = (temp802AD673 + 1 - StratsMenuLines);
    }

    D_802AD609 = D_802AD608 + sixTemp;
    if (D_802AD609 > D_802AD66C) {
        D_802AD609 = D_802AD66C;
    }

    D_802AD60C = -D_802AD608 * 13;
    D_802AD60E = ((s8) StratsMenuLastPos - D_802AD608) * 13;
    ShowingErrorMessage = FALSE;
    D_802AD6D4 = 0;
}

void func_802A4718(void) {
    BattleSubmenuStratsState = BTL_SUBMENU_STRATS_STATE_UNK_10;
}

void func_802A472C(void) {
    s32 i;

    set_window_update(WIN_BTL_STRATS_MENU, WINDOW_UPDATE_HIDE);
    set_window_update(WIN_BTL_STRATS_TITLE, WINDOW_UPDATE_HIDE);
    set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_HIDE);

    for (i = 0; i < D_802AD66C; i++) {
        hud_element_free(D_802AD628[i]);
    }

    hud_element_free(D_802AD618);
    hud_element_free(HID_GreenArrowUp);
    hud_element_free(HID_GreenArrowDown);
}

void func_802A47E0(void) {
    s32 i;

    for (i = 0; i < D_802AD66C; i++) {
        hud_element_set_tint(D_802AD628[i], 255, 255, 255);
    }

    hud_element_set_tint(D_802AD618, 255, 255, 255);
    hud_element_set_tint(HID_GreenArrowUp, 255, 255, 255);
    hud_element_set_tint(HID_GreenArrowDown, 255, 255, 255);
    hud_element_set_script(D_802AD618, &HES_AnimatedHandPointer);
    set_window_update(WIN_BTL_STRATS_MENU, WINDOW_UPDATE_TRANSPARENT);
    set_window_update(WIN_BTL_STRATS_TITLE, WINDOW_UPDATE_TRANSPARENT);
    set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_SHOW);
    D_802AD614 = MSG_PAL_STANDARD;
    D_802AD60B = 1;
    D_802AD624 = 255;
    BattleSubmenuStratsState = BTL_SUBMENU_STRATS_STATE_CHOOSE;
}

void func_802A48FC(void) {
    s32 i;

    set_window_update(WIN_BTL_STRATS_MENU, WINDOW_UPDATE_TRANSPARENT);
    set_window_update(WIN_BTL_STRATS_TITLE, WINDOW_UPDATE_TRANSPARENT);
    set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_SHOW);

    for (i = 0; i < D_802AD66C; i++) {
        hud_element_set_tint(D_802AD628[i], 255, 255, 255);
    }

    hud_element_set_tint(D_802AD618, 255, 255, 255);
    hud_element_set_tint(HID_GreenArrowUp, 255, 255, 255);
    hud_element_set_tint(HID_GreenArrowDown, 255, 255, 255);
    hud_element_set_script(D_802AD618, &HES_AnimatedHandPointer);
    D_802AD614 = MSG_PAL_STANDARD;
    D_802AD60B = 1;
    BattleSubmenuStratsState = BTL_SUBMENU_STRATS_STATE_UNK_20;
}

void func_802A4A10(void) {
    set_window_update(WIN_BTL_STRATS_MENU, WINDOW_UPDATE_TRANSPARENT);
    set_window_update(WIN_BTL_STRATS_TITLE, WINDOW_UPDATE_TRANSPARENT);
    set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_SHOW);
    BattleSubmenuStratsState = BTL_SUBMENU_STRATS_STATE_UNK_30;
}

s32 btl_update_strats_menu(void) {
    BattleStatus* battleStatus = &gBattleStatus;
    HudElemID hid;
    s32 x, y;
    s32 width;
    s32 msgID;
    s32 i;

    switch (BattleSubmenuStratsState) {
        case BTL_SUBMENU_STRATS_STATE_INIT:
            D_802AD63C = 20;
            D_802AD63E = 68;
            D_802AD60C = -D_802AD608 * 13;
            D_802AD60E = (StratsMenuPos - D_802AD608) * 13;

            for (i = 0; i < D_802AD66C; i++) {
                D_802AD628[i] = hid = hud_element_create(StratsOptionHudScript[i]);
                hud_element_set_scale(hid, 0.45f);
                hud_element_set_flags(hid, HUD_ELEMENT_FLAG_FILTER_TEX | HUD_ELEMENT_FLAG_80);
            }

            D_802AD618 = hid = hud_element_create(&HES_AnimatedHandPointer);
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_DROP_SHADOW | HUD_ELEMENT_FLAG_80);
            hud_element_set_render_pos(hid, D_802AD63C, D_802AD63E);

            HID_GreenArrowUp = hid = hud_element_create(&HES_GreenArrowUp);
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_DROP_SHADOW | HUD_ELEMENT_FLAG_80);
            hud_element_set_render_pos(hid, D_802AD63C + 39, D_802AD63E - 7);

            HID_GreenArrowDown = hid = hud_element_create(&HES_GreenArrowDown);
            hud_element_set_flags(hid, HUD_ELEMENT_FLAG_DROP_SHADOW | HUD_ELEMENT_FLAG_80);
            hud_element_set_render_pos(hid, D_802AD63C + 39, D_802AD63E + 78);

            D_802AD614 = MSG_PAL_STANDARD;
            x = D_802AD63C;
            y = D_802AD63E;
            set_window_properties(WIN_BTL_STRATS_MENU, x, y, 144, (StratsMenuLines * 13) + 26, 0, btl_menu_strats_draw_content, NULL, -1);
            set_window_properties(WIN_BTL_STRATS_TITLE, x + 18, y - 6, 108, 16, 1, btl_menu_strats_show_title, NULL, -1);
            x = 20;
            y = 186;
            set_window_properties(WIN_BTL_DESC_BOX, x, y, 280, 32, WINDOW_PRIORITY_20, btl_menu_strats_show_desc, NULL, -1);
            set_window_update(WIN_BTL_STRATS_MENU, WINDOW_UPDATE_SHOW);
            set_window_update(WIN_BTL_STRATS_TITLE, WINDOW_UPDATE_SHOW);
            set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_SHOW);
            BattleSubmenuStratsState = BTL_SUBMENU_STRATS_STATE_CHOOSE;
            return POPUP_RESULT_CHOOSING;
        case BTL_SUBMENU_STRATS_STATE_CHOOSE:
            if (!ShowingErrorMessage) {
                OldStratsMenuPos = StratsMenuPos;

                // only wrap selection on stick press, not when held
                if (battleStatus->curButtonsHeld & BUTTON_STICK_UP) {
                    if (StratsMenuPos > 0) {
                        StratsMenuPos--;
                    } else if (battleStatus->curButtonsPressed & BUTTON_STICK_UP) {
                        StratsMenuPos--;
                    }
                }

                if (battleStatus->curButtonsHeld & BUTTON_STICK_DOWN) {
                    if (StratsMenuPos < D_802AD66C - 1) {
                        StratsMenuPos++;
                    } else if (battleStatus->curButtonsPressed & BUTTON_STICK_DOWN) {
                        StratsMenuPos++;
                    }
                }

                // wrap the selected index
                if (StratsMenuPos < 0) {
                    StratsMenuPos = D_802AD66C - 1;
                }
                if (D_802AD66C - 1 < StratsMenuPos) {
                    StratsMenuPos = 0;
                }

                if (OldStratsMenuPos != StratsMenuPos) {
                    hud_element_set_scale(D_802AD628[OldStratsMenuPos], 0.45f);
                    sfx_play_sound(SOUND_MENU_CHANGE_SELECTION);
                }

                if (StratsMenuPos < D_802AD608) {
                    D_802AD608 = StratsMenuPos;
                }
                if (StratsMenuPos >= D_802AD609) {
                    D_802AD608 = StratsMenuPos + 1 - StratsMenuLines;
                }
                D_802AD609 = D_802AD608 + 6;
                if (D_802AD609 > D_802AD66C) {
                    D_802AD609 = D_802AD66C;
                }

                if (battleStatus->curButtonsPressed & BUTTON_A) {
                    if (StratsOptionEnabled[StratsMenuPos]) {
                        sfx_play_sound(SOUND_MENU_NEXT);
                        BattleSubmenuStratsState = BTL_SUBMENU_STRATS_STATE_SELECT;
                    } else {
                        sfx_play_sound(SOUND_MENU_ERROR);
                        BattleSubmenuStratsState = BTL_SUBMENU_STRATS_STATE_ERROR_INIT;
                        StratsErrorCode = StratsOptionError[StratsMenuPos];
                    }
                } else if (battleStatus->curButtonsPressed & BUTTON_B) {
                    sfx_play_sound(SOUND_MENU_BACK);
                    func_802A472C();
                    BattleSubmenuStratsState = BTL_SUBMENU_STRATS_STATE_CANCEL;
                }
            }
            return POPUP_RESULT_CHOOSING;
        case BTL_SUBMENU_STRATS_STATE_SELECT:
            for (i = 0; i < D_802AD66C; i++) {
                hud_element_set_tint(D_802AD628[i], 160, 160, 160);
            }
            hud_element_set_tint(D_802AD618, 160, 160, 160);
            hud_element_set_tint(HID_GreenArrowUp, 160, 160, 160);
            hud_element_set_tint(HID_GreenArrowDown, 160, 160, 160);
            hud_element_set_script(D_802AD618, &HES_HandPointer);
            D_802AD614 = MSG_PAL_0D;
            set_window_update(WIN_BTL_STRATS_MENU, WINDOW_UPDATE_DARKENED);
            set_window_update(WIN_BTL_STRATS_TITLE, WINDOW_UPDATE_DARKENED);
            set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_HIDE);
            return StratsMenuPos + 1;
        case BTL_SUBMENU_STRATS_STATE_CANCEL:
            return POPUP_RESULT_CANCEL;
        case 10:
            set_window_update(WIN_BTL_STRATS_MENU, WINDOW_UPDATE_HIDE);
            set_window_update(WIN_BTL_STRATS_TITLE, WINDOW_UPDATE_HIDE);
            set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_HIDE);
            BattleSubmenuStratsState = BTL_SUBMENU_STRATS_STATE_UNK_11;
            return StratsMenuPos + 1;
        case 11:
            return StratsMenuPos + 1;
        case 20:
            set_window_update(WIN_BTL_STRATS_MENU, WINDOW_UPDATE_SHOW);
            set_window_update(WIN_BTL_STRATS_TITLE, WINDOW_UPDATE_SHOW);
            set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_SHOW);
            BattleSubmenuStratsState = BTL_SUBMENU_STRATS_STATE_CHOOSE;
            return StratsMenuPos + 1;
        case 30:
            set_window_update(WIN_BTL_STRATS_MENU, WINDOW_UPDATE_SHOW);
            set_window_update(WIN_BTL_STRATS_TITLE, WINDOW_UPDATE_SHOW);
            set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_SHOW);
            BattleSubmenuStratsState = BTL_SUBMENU_STRATS_STATE_SELECT;
            return POPUP_RESULT_CHOOSING;
        case BTL_SUBMENU_STRATS_STATE_ERROR_INIT:
            D_802AD6D4 = -1;
            BattleSubmenuStratsState = BTL_SUBMENU_STRATS_STATE_ERROR_SHOW;
            return POPUP_RESULT_INVALID;
        case BTL_SUBMENU_STRATS_STATE_ERROR_SHOW:
            set_window_update(WIN_BTL_STRATS_MENU, WINDOW_UPDATE_HIDE);
            set_window_update(WIN_BTL_STRATS_TITLE, WINDOW_UPDATE_HIDE);
            set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_HIDE);
            switch (StratsErrorCode) {
                case 0:
                    msgID = MSG_Menus_Battle_CantSwitch2;
                    break;
                case 1:
                    msgID = MSG_Menus_Battle_CantRunAway;
                    break;
                default:
                    msgID = MSG_Menus_Battle_CantRunAway;
                    break;
            }
            width = get_msg_width(msgID, 0) + 23;
            set_window_properties(WIN_BTL_POPUP, (SCREEN_WIDTH / 2) - (width / 2), 80, width, 28, 20, btl_menu_strats_show_error, NULL, -1);
            set_window_update(WIN_BTL_POPUP, WINDOW_UPDATE_SHOW);
            D_802AD612 = 60;
            BattleSubmenuStratsState = BTL_SUBMENU_STRATS_STATE_ERROR_DONE;
            return POPUP_RESULT_INVALID;
        case BTL_SUBMENU_STRATS_STATE_ERROR_DONE:
            if (gGameStatusPtr->pressedButtons[0] & (BUTTON_A | BUTTON_B)) {
                D_802AD612 = 0;
            }
            if (D_802AD612 != 0) {
                D_802AD612--;
                return POPUP_RESULT_INVALID;
            }
            set_window_update(WIN_BTL_POPUP, WINDOW_UPDATE_HIDE);
            set_window_update(WIN_BTL_STRATS_MENU, WINDOW_UPDATE_SHOW);
            set_window_update(WIN_BTL_STRATS_TITLE, WINDOW_UPDATE_SHOW);
            set_window_update(WIN_BTL_DESC_BOX, WINDOW_UPDATE_SHOW);
            BattleSubmenuStratsState = BTL_SUBMENU_STRATS_STATE_CHOOSE;
            return POPUP_RESULT_CHOOSING;
    }
    return POPUP_RESULT_CHOOSING;
}

#if VERSION_IQUE
#define Y_VAR2 3
#else
#define Y_VAR2 0
#endif

void btl_menu_strats_draw_content(void* data, s32 x, s32 y) {
    s32 var_t0;
    s32 temp_f6;
    s32 xPos, yPos;
    s32 idx;
    s32 id;
    s32 i;

    switch (BattleSubmenuStratsState) {
        case BTL_SUBMENU_STRATS_STATE_SELECT:
        case BTL_SUBMENU_STRATS_STATE_CHOOSE:
        case BTL_SUBMENU_STRATS_STATE_UNK_10:
        case BTL_SUBMENU_STRATS_STATE_UNK_20:
        case BTL_SUBMENU_STRATS_STATE_UNK_30:
        case BTL_SUBMENU_STRATS_STATE_ERROR_INIT:
        case BTL_SUBMENU_STRATS_STATE_ERROR_SHOW:
            yPos = -D_802AD608 * 13;
            var_t0 = D_802AD60C;
            temp_f6 = (yPos - var_t0) * 0.5;
            if (temp_f6 != 0) {
                var_t0 += temp_f6;
            } else {
                var_t0 = yPos;
            }
            D_802AD60C = var_t0;

            xPos = x + 4;
            yPos = y + 18;
            var_t0 = yPos + 1 + (StratsMenuLines * 13);
            gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, xPos, yPos, x + 142, var_t0);

            xPos = x + 33;
            yPos = y + 19 + D_802AD60C;

            idx = 0;
            for (i = 0; i < D_802AD66C; i++, idx++) {
                s32 palette = D_802AD614;

                if (D_802AD678[i] == BTL_MENU_TYPE_CHANGE_PARTNER && is_ability_active(ABILITY_QUICK_CHANGE)) {
                    palette = MSG_PAL_37;
                }
                if (!StratsOptionEnabled[idx]) {
                    palette = MSG_PAL_0B;
                }
                draw_msg(D_802AD658[idx], xPos, yPos - Y_VAR2, D_802AD624, palette, DRAW_MSG_STYLE_MENU);
                yPos += 13;
            }

            xPos = x + 24;
            yPos = D_802AD60C + y + 24;

            idx = 0;
            for (i = 0; i < D_802AD66C; i++, idx++) {
                id = D_802AD628[idx];
                hud_element_set_render_pos(id, xPos, yPos);
                hud_element_set_alpha(id, D_802AD624);
                hud_element_draw_without_clipping(id);
                yPos += 13;
            }

            yPos = (StratsMenuPos - D_802AD608) * 13;
            var_t0 = D_802AD60E;
            temp_f6 = (yPos - var_t0) * 1.0;
            xPos = x + 10;
            if (temp_f6 != 0) {
                var_t0 += temp_f6;
            } else {
                var_t0 = yPos;
            }
            D_802AD60E = var_t0;
            yPos = y + 26 + D_802AD60E;

            id = D_802AD618;
            hud_element_set_render_pos(id, xPos, yPos);
            hud_element_set_alpha(id, D_802AD624);
            hud_element_draw_clipped(id);

            if (D_802AD608 > 0) {
                id = HID_GreenArrowUp;
                hud_element_set_render_pos(id, x + 67, y + 16);
                hud_element_set_alpha(id, D_802AD624);
                hud_element_draw_clipped(id);
            }
            if (D_802AD609 < D_802AD66C) {
                id = HID_GreenArrowDown;
                hud_element_set_render_pos(id, x + 67, y + 100);
                hud_element_set_alpha(id, D_802AD624);
                hud_element_draw_clipped(id);
            }
            break;
    }
}

void btl_menu_strats_show_title(void* data, s32 x, s32 y) {
    draw_msg(MSG_Menus_Strategies, x + 15, y + 2, D_802AD624, MSG_PAL_33, DRAW_MSG_STYLE_MENU);
}

void btl_menu_strats_show_desc(void* data, s32 x, s32 y) {
    switch (BattleSubmenuStratsState) {
        case BTL_SUBMENU_STRATS_STATE_SELECT:
        case BTL_SUBMENU_STRATS_STATE_CHOOSE:
        case BTL_SUBMENU_STRATS_STATE_UNK_10:
        case BTL_SUBMENU_STRATS_STATE_UNK_20:
        case BTL_SUBMENU_STRATS_STATE_UNK_30:
            if (D_802AD60B != 0) {
                draw_msg(StratsOptionMessage[StratsMenuPos], x + 8, y, D_802AD624, D_802AD614, 0);
            }
            break;
    }
}

void btl_menu_strats_show_error(void* data, s32 x, s32 y) {
    s32 msgID;
    x += 11;
    y += 6;

    switch (StratsErrorCode) {
        case 0:
            msgID = MSG_Menus_Battle_CantSwitch2;
            break;
        case 1:
            msgID = MSG_Menus_Battle_CantRunAway;
            break;
        default:
            msgID = MSG_Menus_Battle_CantRunAway;
            break;
    }
    draw_msg(msgID, x, y, 255, MSG_PAL_0F, 0);
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
