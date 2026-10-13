#ifndef _FILEMENU_H_
#define _FILEMENU_H_

#include "common.h"
#include "filemenu.h"

#define CENTER_WINDOW_X(id) (((gWindows[id].parent != WIN_NONE) \
    ? (gWindows[gWindows[id].parent].width / 2) \
    : (SCREEN_WIDTH / 2)) \
    - (gWindows[id].width / 2))

#define CENTER_WINDOW_Y(id) (((gWindows[id].parent != WIN_NONE) \
    ? (gWindows[gWindows[id].parent].height  / 2) \
    : (SCREEN_HEIGHT / 2)) \
    - (gWindows[id].height  / 2))

enum {
    FILE_MENU_MAIN          = 0, // file selection
    FILE_MENU_CONFIRM       = 1, // confirmation prompt is open
    FILE_MENU_MESSAGE       = 2, // message is displayed, e.g. "File X has been deleted."
    FILE_MENU_INPUT_NAME    = 3, // "Enter a file name!" screen
};

enum {
    FM_MAIN_SELECT_FILE         = 0, // choose which file to load
    FM_MAIN_SELECT_DELETE       = 1, // choose which file to delete
    FM_MAIN_SELECT_COPY_FROM    = 2,
    FM_MAIN_SELECT_COPY_TO      = 3,

    FM_CONFIRM_DELETE           = 0,
    FM_CONFIRM_CREATE           = 1,
    FM_CONFIRM_COPY             = 2, // unused
    FM_CONFIRM_START            = 3,

    FM_MESSAGE_DELETED          = 0,
    FM_MESSAGE_COPIED           = 1,
    FM_MESSAGE_CREATED          = 2,

    FM_INPUT_CHARSET_A          = 0,
    FM_INPUT_CHARSET_B          = 1,
};

enum {
    FM_MAIN_OPT_FILE_1          = 0,
    FM_MAIN_OPT_FILE_2          = 1,
    FM_MAIN_OPT_FILE_3          = 2,
    FM_MAIN_OPT_FILE_4          = 3,
    FM_MAIN_OPT_DELETE          = 4,
    FM_MAIN_OPT_COPY            = 5,
    FM_MAIN_OPT_CANCEL          = 6,
};

extern MenuPanel* filemenu_menus[];

extern s32 filemenu_CopyToFileIdx;
extern s32 filemenu_pressedButtons;
extern HudElemID filemenu_cursorHID;
extern s32 filemenu_heldButtons;
extern s8 filemenu_filename_pos;
extern s32 filemenu_CopyFromFileIdx;
extern s8 filemenu_currentMenu;
extern s32 filemenu_8024C09C;
extern HudElemID filemenu_cursorHIDs[1];
extern s32 filemenu_8024C0A4[3];
extern HudElemID filemenu_mainHIDs[20];
extern HudElemID filemenu_createfile_HIDs[4];
extern MSG_BIN filemenu_filename[8];

#if VERSION_PAL
extern HudElemID PauseLanguageHIDs[1];
extern s32 D_802517D4[1];
extern u16 D_802517E0[2][0x400];
extern u8 D_filemenu_8025095C[4];
#endif

WindowUpdateCallback filemenu_update_show_name_input;
WindowUpdateCallback filemenu_update_show_options_left;
WindowUpdateCallback filemenu_update_show_options_right;
WindowUpdateCallback filemenu_update_show_options_bottom;
WindowUpdateCallback filemenu_update_show_with_rotation;

WindowUpdateCallback filemenu_update_hidden_name_input;
WindowUpdateCallback filemenu_update_hidden_options_left;
WindowUpdateCallback filemenu_update_hidden_options_right;
WindowUpdateCallback filemenu_update_hidden_title;
WindowUpdateCallback filemenu_update_hidden_options_bottom;
WindowUpdateCallback filemenu_update_hidden_with_rotation;

WindowUpdateCallback filemenu_update_select_file;
WindowUpdateCallback filemenu_update_deselect_file;

WindowUpdateCallback filemenu_update_show_name_confirm;
WindowUpdateCallback filemenu_update_hidden_name_confirm;

WindowUpdateCallback main_menu_window_update;

WindowUpdateCallback filemenu_update_show_title;

void filemenu_draw_file_name(MSG_PTR, s32, s32, s32, s32, s32, s32, s32);

MenuPanelDrawContentFunc filemenu_draw_contents_title;
MenuPanelDrawContentFunc filemenu_draw_contents_stereo;
MenuPanelDrawContentFunc filemenu_draw_contents_mono;
MenuPanelDrawContentFunc filemenu_draw_contents_option_left;
MenuPanelDrawContentFunc filemenu_draw_contents_option_center;
MenuPanelDrawContentFunc filemenu_draw_contents_option_right;
MenuPanelDrawContentFunc filemenu_draw_contents_file_0_info;
MenuPanelDrawContentFunc filemenu_draw_contents_file_0_title;
MenuPanelDrawContentFunc filemenu_draw_contents_file_1_info;
MenuPanelDrawContentFunc filemenu_draw_contents_file_1_title;
MenuPanelDrawContentFunc filemenu_draw_contents_file_2_info;
MenuPanelDrawContentFunc filemenu_draw_contents_file_2_title;
MenuPanelDrawContentFunc filemenu_draw_contents_file_3_info;
MenuPanelDrawContentFunc filemenu_draw_contents_file_3_title;
MenuPanelDrawContentFunc filemenu_yesno_draw_options_contents;
MenuPanelDrawContentFunc filemenu_yesno_draw_prompt_contents;
MenuPanelDrawContentFunc filemenu_info_draw_message_contents;
MenuPanelDrawContentFunc filemenu_draw_contents_file_create_header;
MenuPanelDrawContentFunc filemenu_draw_contents_choose_name;
MenuPanelDrawContentFunc filemenu_draw_cursor;
MenuPanelDrawContentFunc filemenu_draw_contents_copy_arrow;

void filemenu_main_init(MenuPanel*);
void filemenu_main_handle_input(MenuPanel*);
void filemenu_main_update(MenuPanel*);
void filemenu_main_cleanup(MenuPanel*);
void filemenu_yesno_init(MenuPanel*);
void filemenu_yesno_handle_input(MenuPanel*);
void filemenu_yesno_update(MenuPanel*);
void filemenu_yesno_cleanup(MenuPanel*);
void filemenu_info_init(MenuPanel*);
void filemenu_info_handle_input(MenuPanel*);
void filemenu_info_update(MenuPanel*);
void filemenu_info_cleanup(MenuPanel*);
void filemenu_choose_name_init(MenuPanel*);
void filemenu_choose_name_handle_input(MenuPanel*);
void filemenu_choose_name_update(MenuPanel*);
void filemenu_choose_name_cleanup(MenuPanel*);

void filemenu_draw_message(MSG_PTR, s32, s32, s32, s32, u32);
void filemenu_draw_rect(s32 ulx, s32 uly, s32 lrx, s32 lry, s32 tileIdx, s32 uls, s32 ult, s32 dsdx, s32 dtdy);

extern WindowStyleCustom filemenu_windowStyles[];
extern u8 filemenu_createfile_gridData[];

#endif
