// Named native songs in SongIDs order; omit the unnamed duplicate slots.
// Included by debug_menu.c after the shared menu drawing/input helpers.
typedef struct DebugMusicEntry {
    s32 songID;
    const char* name;
} DebugMusicEntry;

static const DebugMusicEntry DebugMusicSongs[] = {
    { SONG_TOAD_TOWN, "Toad Town" },
    { SONG_NORMAL_BATTLE, "Normal Battle" },
    { SONG_SPECIAL_BATTLE, "Special Battle" },
    { SONG_JR_TROOPA_BATTLE, "Jr. Troopa Battle" },
    { SONG_FINAL_BOWSER_BATTLE, "Final Bowser Battle" },
    { SONG_GOOMBA_KING_BATTLE, "Goomba King Battle" },
    { SONG_KOOPA_BROS_BATTLE, "Koopa Bros Battle" },
    { SONG_FAKE_BOWSER_BATTLE, "Fake Bowser Battle" },
    { SONG_TUTANKOOPA_BATTLE, "Tutankoopa Battle" },
    { SONG_TUBBA_BLUBBA_BATTLE, "Tubba Blubba Battle" },
    { SONG_GENERAL_GUY_BATTLE, "General Guy Battle" },
    { SONG_LAVA_PIRANHA_BATTLE, "Lava Piranha Battle" },
    { SONG_HUFF_N_PUFF_BATTLE, "Huff N' Puff Battle" },
    { SONG_CRYSTAL_KING_BATTLE, "Crystal King Battle" },
    { SONG_GOOMBA_VILLAGE, "Goomba Village" },
    { SONG_PLEASANT_PATH, "Pleasant Path" },
    { SONG_FUZZY_ATTACK, "Fuzzy Attack" },
    { SONG_KOOPA_VILLAGE, "Koopa Village" },
    { SONG_KOOPA_FORTRESS, "Koopa Fortress" },
    { SONG_DRY_DRY_OUTPOST, "Dry Dry Outpost" },
    { SONG_MT_RUGGED, "Mt Rugged" },
    { SONG_DRY_DRY_DESERT, "Dry Dry Desert" },
    { SONG_DRY_DRY_RUINS, "Dry Dry Ruins" },
    { SONG_RUINS_BASEMENT, "Ruins Basement" },
    { SONG_FOREVER_FOREST, "Forever Forest" },
    { SONG_BOOS_MANSION, "Boo's Mansion" },
    { SONG_CHEERFUL_BOOS_MANSION, "Cheerful Boo's Mansion" },
    { SONG_GUSTY_GULCH, "Gusty Gulch" },
    { SONG_TUBBAS_MANOR, "Tubba's Manor" },
    { SONG_TUBBA_ESCAPE, "Tubba Escape" },
    { SONG_SHY_GUY_TOYBOX, "Shy Guy Toybox" },
    { SONG_TOYBOX_TRAIN, "Toybox Train" },
    { SONG_CREEPY_TOYBOX, "Creepy Toybox" },
    { SONG_JADE_JUNGLE, "Jade Jungle" },
    { SONG_DEEP_JUNGLE, "Deep Jungle" },
    { SONG_YOSHIS_VILLAGE, "Yoshi's Village" },
    { SONG_YOSHIS_PANIC, "Yoshi's Panic" },
    { SONG_RAPHAEL_RAVEN, "Raphael Raven" },
    { SONG_MT_LAVALAVA, "Mt Lavalava" },
    { SONG_VOLCANO_ESCAPE, "Volcano Escape" },
    { SONG_STAR_WAY_OPENS, "Star Way Opens" },
    { SONG_MASTER_BATTLE, "Master Battle" },
    { SONG_RADIO_ISLAND_SOUNDS, "Radio Island Sounds" },
    { SONG_RADIO_HOT_HITS, "Radio Hot Hits" },
    { SONG_RADIO_GOLDEN_OLDIES, "Radio Golden Oldies" },
    { SONG_FLOWER_FIELDS_CLOUDY, "Flower Fields Cloudy" },
    { SONG_FLOWER_FIELDS_SUNNY, "Flower Fields Sunny" },
    { SONG_CLOUDY_CLIMB, "Cloudy Climb" },
    { SONG_PUFF_PUFF_MACHINE, "Puff Puff Machine" },
    { SONG_SUN_TOWER_CLOUDY, "Sun Tower Cloudy" },
    { SONG_SUN_TOWER_SUNNY, "Sun Tower Sunny" },
    { SONG_CRYSTAL_PALACE, "Crystal Palace" },
    { SONG_SHIVER_CITY, "Shiver City" },
    { SONG_PENGUIN_MYSTERY, "Penguin Mystery" },
    { SONG_SHIVER_SNOWFIELD, "Shiver Snowfield" },
    { SONG_SHIVER_MOUNTAIN, "Shiver Mountain" },
    { SONG_STARBORN_VALLEY, "Starborn Valley" },
    { SONG_MERLAR_THEME, "Merlar Theme" },
    { SONG_MAIL_CALL, "Mail Call" },
    { SONG_PEACHS_CASTLE_PARTY, "Peach's Castle Party" },
    { SONG_CHAPTER_END, "Chapter End" },
    { SONG_CHAPTER_START, "Chapter Start" },
    { SONG_ITEM_UPGRADE, "Item Upgrade" },
    { SONG_PHONOGRAPH_MUSIC, "Phonograph Music" },
    { SONG_TUTANKOOPA_THEME, "Tutankoopa Theme" },
    { SONG_KAMMY_KOOPA_THEME, "Kammy Koopa Theme" },
    { SONG_JR_TROOPA_THEME, "Jr. Troopa Theme" },
    { SONG_BULLET_BILL_ASSAULT, "Bullet Bill Assault" },
    { SONG_MONTY_MOLE_ASSAULT, "Monty Mole Assault" },
    { SONG_SHY_GUY_INVASION, "Shy Guy Invasion" },
    { SONG_TOAD_TOWN_TUNNELS, "Toad Town Tunnels" },
    { SONG_WHALE_THEME, "Whale Theme" },
    { SONG_FOREVER_FOREST_WARNING, "Forever Forest Warning" },
    { SONG_YOSHI_KIDS_FOUND, "Yoshi Kids Found" },
    { SONG_UNUSED_FANFARE, "Unused Fanfare" },
    { SONG_GOOMBA_KING_THEME, "Goomba King Theme" },
    { SONG_KOOPA_BROS_INTERLUDE, "Koopa Bros Interlude" },
    { SONG_KOOPA_BROS_THEME, "Koopa Bros Theme" },
    { SONG_TUTANKOOPA_WARNING, "Tutankoopa Warning" },
    { SONG_TUTANKOOPA_REVEALED, "Tutankoopa Revealed" },
    { SONG_TUBBA_BLUBBA_THEME, "Tubba Blubba Theme" },
    { SONG_GENERAL_GUY_THEME, "General Guy Theme" },
    { SONG_LAVA_PIRANHA_THEME, "Lava Piranha Theme" },
    { SONG_HUFF_N_PUFF_THEME, "Huff N' Puff Theme" },
    { SONG_CRYSTAL_KING_THEME, "Crystal King Theme" },
    { SONG_BLOOPER_THEME, "Blooper Theme" },
    { SONG_MINIBOSS_BATTLE, "Miniboss Battle" },
    { SONG_MONSTAR_THEME, "Monstar Theme" },
    { SONG_CLUB64, "Club 64" },
    { SONG_UNUSED_OPENING, "Unused Opening" },
    { SONG_BOWSERS_CASTLE_FALLS, "Bowser's Castle Falls" },
    { SONG_STAR_HAVEN, "Star Haven" },
    { SONG_SHOOTING_STAR_SUMMIT, "Shooting Star Summit" },
    { SONG_STARSHIP_THEME, "Starship Theme" },
    { SONG_STAR_SANCTUARY, "Star Sanctuary" },
    { SONG_BOWSERS_CASTLE, "Bowser's Castle" },
    { SONG_BOWSERS_CASTLE_CAVES, "Bowser's Castle Caves" },
    { SONG_BOWSER_THEME, "Bowser Theme" },
    { SONG_BOWSER_BATTLE, "Bowser Battle" },
    { SONG_PEACH_WISHES, "Peach Wishes" },
    { SONG_FILE_SELECT, "File Select" },
    { SONG_MAIN_THEME, "Main Theme" },
    { SONG_BOWSER_ATTACKS, "Bowser Attacks" },
    { SONG_MARIO_FALLS, "Mario Falls" },
    { SONG_PEACH_APPEARS, "Peach Appears" },
    { SONG_THE_END, "The End" },
    { SONG_RECOVERED_STAR_ROD, "Recovered Star Rod" },
    { SONG_TWINK_THEME, "Twink Theme" },
    { SONG_STIRRING_CAKE, "Stirring Cake" },
    { SONG_GOURMET_GUY_FREAKOUT, "Gourmet Guy Freakout" },
    { SONG_PRISONER_PEACH_THEME, "Prisoner Peach Theme" },
    { SONG_PEACH_MISSION, "Peach Mission" },
    { SONG_PEACH_SNEAKING, "Peach Sneaking" },
    { SONG_PEACH_CAUGHT, "Peach Caught" },
    { SONG_PEACH_QUIZ_INTRO, "Peach Quiz Intro" },
    { SONG_STAR_SPIRIT_THEME, "Star Spirit Theme" },
    { SONG_PENGUIN_WHODUNIT, "Penguin Whodunit" },
    { SONG_PENGUIN_WAKES_UP, "Penguin Wakes Up" },
    { SONG_MAGIC_BEANSTALK, "Magic Beanstalk" },
    { SONG_MERLEE_SPELL, "Merlee Spell" },
    { SONG_LAKILESTER_THEME, "Lakilester Theme" },
    { SONG_GOOMBA_BROS_RETREAT, "Goomba Bros Retreat" },
    { SONG_SUNSHINE_RETURNS, "Sunshine Returns" },
    { SONG_RIDING_THE_RAILS, "Riding The Rails" },
    { SONG_RIDING_THE_WHALE, "Riding The Whale" },
    { SONG_NEW_PARTNER, "New Partner" },
    { SONG_DRY_DRY_RUINS_APPEAR, "Dry Dry Ruins Appear" },
    { SONG_CANDY_CANES, "Candy Canes" },
    { SONG_PLAYROOM, "Playroom" },
    { SONG_MOUSTAFA_THEME, "Moustafa Theme" },
    { SONG_GAME_OVER, "Game Over" },
    { SONG_TAKING_REST, "Taking Rest" },
    { SONG_FLOWER_NPC_THEME, "Flower NPC Theme" },
    { SONG_FLOWER_GATE_APPEARS, "Flower Gate Appears" },
    { SONG_BATTLE_END, "Battle End" },
    { SONG_POP_DIVA_SONG, "Pop Diva Song" },
    { SONG_BOO_MINIGAME, "Boo Minigame" },
    { SONG_LEVEL_UP, "Level Up" },
    { SONG_PARADE_DAY, "Parade Day" },
    { SONG_PARADE_NIGHT, "Parade Night" },
    { SONG_MARIO_BROS_HOUSE, "Mario Bros. House" },
    { SONG_INTRO_STORY, "Intro Story" },
    { SONG_NEW_PARTNER_JP, "New Partner (JP)" },
};

#define DEBUG_MUSIC_VISIBLE_ROWS 9
static s32 DebugMusicPos = 0;
static s32 DebugMusicStart = 0;

void dx_debug_update_select_music() {
    s32 count = ARRAY_COUNT(DebugMusicSongs);
    s32 row;
    char fmtBuf[48];

    if (DebugStateChanged) {
        DebugMusicPos = MAX(0, MIN(DebugMusicPos, count - 1));
        DebugMusicStart = MAX(0, MIN(DebugMusicStart, count - DEBUG_MUSIC_VISIBLE_ROWS));
    }
    DebugMusicPos = dx_debug_menu_nav_1D_vertical(DebugMusicPos, 0, count - 1, false);
    if (NAV_LEFT) {
        DebugMusicPos = MAX(0, DebugMusicPos - DEBUG_MUSIC_VISIBLE_ROWS);
    } else if (NAV_RIGHT) {
        DebugMusicPos = MIN(count - 1, DebugMusicPos + DEBUG_MUSIC_VISIBLE_ROWS);
    }
    if (DebugMusicPos < DebugMusicStart) {
        DebugMusicStart = DebugMusicPos;
    } else if (DebugMusicPos >= DebugMusicStart + DEBUG_MUSIC_VISIBLE_ROWS) {
        DebugMusicStart = DebugMusicPos - DEBUG_MUSIC_VISIBLE_ROWS + 1;
    }

    if (RELEASED(BUTTON_L)) {
        DebugMenuState = DBM_SOUND_PLAYER;
        return;
    } else if (RELEASED(BUTTON_Z)) {
        bgm_set_song(0, AU_SONG_NONE, 0, 0, VOL_LEVEL_FULL);
    } else if (RELEASED(BUTTON_R)) {
        // Use the normal BGM transition, without touching the battle's saved song.
        bgm_set_song(0, DebugMusicSongs[DebugMusicPos].songID, 0, 0, VOL_LEVEL_FULL);
    }

    dx_debug_draw_box(16, 26, 288, 205, WINDOW_STYLE_20, 240);
    sprintf(fmtBuf, "Music   %ld / %ld", DebugMusicPos + 1, count);
    dx_debug_draw_ascii(fmtBuf, MSG_PAL_YELLOW, 26, 32);
    for (row = 0; row < DEBUG_MUSIC_VISIBLE_ROWS && DebugMusicStart + row < count; row++) {
        s32 index = DebugMusicStart + row;
        s32 color = index == DebugMusicPos ? HighlightColor : DefaultColor;

        sprintf(fmtBuf, "%02lX", DebugMusicSongs[index].songID);
        dx_debug_draw_ascii(fmtBuf, color, 26, 51 + row * RowHeight);
        dx_debug_draw_ascii(DebugMusicSongs[index].name, color, 50, 51 + row * RowHeight);
    }
    if (!gGameStatusPtr->musicEnabled) {
        dx_debug_draw_ascii("Music is disabled", MSG_PAL_YELLOW, 26, 188);
    } else if (gMusicControlData[0].requestedSongID < 0) {
        dx_debug_draw_ascii("Stopped", HoverColor, 26, 188);
    } else {
        sprintf(fmtBuf, "Selected song: %02lX", gMusicControlData[0].requestedSongID);
        dx_debug_draw_ascii(fmtBuf, HoverColor, 26, 188);
    }
    dx_debug_draw_ascii("R Play   Z Stop   L Back", DefaultColor, 26, 203);
    dx_debug_draw_ascii("Left/Right Page", DefaultColor, 26, 217);
}
