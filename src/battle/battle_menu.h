#ifndef _BATTLE_MENU_H_
#define _BATTLE_MENU_H_

#include "common.h"
#include "hud_element.h"

#define UNK_MENU_DELAY 8
#define UNK_MENU_SHORT_DELAY 5

void btl_main_menu_init(void);

// btl_main_menu_hide? (after begin targeting)
void func_802A1030(void);

// (after submenu closed/cancelled)
void func_802A1050(void);

// btl_main_menu_show? (canceling targeting -> main menu)
void func_802A1078(void);

// btl_main_menu_show? (canceling targeting -> submenu)
void func_802A1098(void);

void btl_main_menu_destroy(void);

s32 btl_main_menu_update(void);
void btl_main_menu_draw(void);

s32 btl_update_strats_menu(void);

s32 can_switch_to_player(void);
s32 can_switch_to_partner(void);

void create_battle_popup_menu(PopupMenu* popup);

void func_800F52BC(void);
void func_800F16CC(void);

void func_802A2684(void);
void func_802A27D0(void);
void func_802A27E4(void);
void func_802A472C(void);
void func_802A47E0(void);
void func_802A48FC(void);
void func_802A4A10(void);

void func_802A2AB8(void);
void func_802A45D8(void);

void func_802A2910(void);
void func_802A2C58(void);

void func_802A4718(void);

void btl_check_can_change_partner(void);
void btl_init_menu_items(void);
s32 btl_submenu_moves_update(void);

extern PopupMenu D_802ACCD0;

extern s32 D_802AD628[];
extern s16 D_802AD63C;
extern s16 D_802AD63E;
extern HudScript* StratsOptionHudScript[];
extern s32 D_802AD658[]; // msg IDs
extern s32 D_802AD66C;
extern s32 StratsMenuLastPos;

extern s32 D_802AD678[];
extern s32 StratsOptionEnabled[];
extern s32 StratsOptionError[];
extern s32 StratsOptionMessage[];
extern s32 D_802AD6D4;

extern s8 BattleMenu_CurPos;
extern s8 BattleMenu_HomePos;

extern s32 PartnerNameMessages[];

extern IconHudScriptPair battle_menu_ItemHudScripts;
extern IconHudScriptPair battle_menu_StarPowerHudScripts;
extern IconHudScriptPair battle_menu_StrategiesHudScript;
extern IconHudScriptPair DoNothingHudScripts;
extern IconHudScriptPair FleeHudScripts;

extern s32 BattleMenu_LeftJustMessages[];
extern s32 BattleMenu_CenteredMessages[];

extern IconHudScriptPair PartnerHudScripts[];
extern HudScript* battle_menu_DisabledPartnerHudScripts[];

extern IconHudScriptPair battle_menu_StarPowerMovesHudScripts[];

extern HudScript HES_HandPointDownLoop;
extern HudScript HES_HandPointLeftLoop;
extern s32 BattleMenu_TargetHudElems[];

extern s32 D_802ACC60;
extern s32 BattleMenu_TargetPointerAlpha;
extern s32 BattleMenu_TargetNameOffsetX;
extern s32 BattleMenu_SwapDelay;

extern HudScript* battle_menu_moveOptionIconScripts[24];
extern s32 battle_menu_moveOptionNames[24];
extern s32 battle_menu_moveOptionDisplayCosts[24];
extern s32 battle_menu_moveOptionDisplayCostReductions[24];
extern s32 battle_menu_moveOptionDisplayCostReductionColors[24];
extern s32 battle_menu_moveOptionBPCosts[24];
extern s32 BattleMenu_UsingSpiritsSubmenu;
extern s32 BattleMenu_Moves_OptionCount;
extern s32 D_802AD4A8;
extern s32 BattleMenu_Moves_OptionIndices[24];
extern s32 BattleMenu_Moves_OptionEnabled[24];
extern s32 BattleMenu_Moves_OptionDescMessages[24];
extern s8 BattleMenu_Moves_OptionSortPriority[24];
extern s8 BattleMenu_Moves_OptionCantUseMessages[24];
extern s32 battle_menu_moveOptionActive;

extern s32 battle_menu_submenuIDs[];
extern s32 BattleMenu_OptionEnabled[];
extern s32 battle_menu_isMessageDisabled[];
extern HudScript* BattleMenu_HudScripts[];
extern s32 BattleMenu_TitleMessages[];

extern s32 BattleMenu_ShowSwapIcons;
extern s32 BattleMenu_NumOptions;

extern s32 D_802AD0A8;
extern s32 D_802AD0B0;
extern s32 D_802AD100;
extern s8 ShowingErrorMessage;

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

#endif
