#pragma once

#include "ultra64.h"
#include "types.h"
#include "saved_byte_names.h"
#include "saved_flag_names.h"

enum StoryProgress {
    STORY_INTRO                                 = -128,
    STORY_CH0_WAKE_UP                           = -127,
    STORY_CH0_MET_INNKEEPER                     = -126,
    STORY_UNUSED_FFFFFF83                       = -125,
    STORY_CH0_MET_GOOMPA                        = -124,
    STORY_CH0_GATE_CRUSHED                      = -123,
    STORY_CH0_FELL_OFF_CLIFF                    = -122,
    STORY_CH0_GOOMPA_JOINED_PARTY               = -121,
    STORY_CH0_LOOKING_FOR_HAMMER                = -120,
    STORY_CH0_FOUND_HAMMER                      = -119,
    STORY_CH0_DEFEATED_JR_TROOPA                = -118,
    STORY_CH0_LEFT_THE_PLAYGROUND               = -117,
    STORY_UNUSED_FFFFFF8C                       = -116,
    STORY_CH0_GOOMBARIO_JOINED_PARTY            = -115,
    STORY_CH0_SMASHED_GATE_BLOCK                = -114,
    STORY_CH0_DEFEATED_GOOMBA_BROS              = -113,
    STORY_CH0_DEFEATED_GOOMBA_KING              = -112,
    STORY_CH0_FOUND_GATEHOUSE_SWITCH            = -111,
    STORY_CH0_HIT_GATEHOUSE_SWITCH              = -110,
    STORY_CH0_OPENED_BRIDGE_TO_TOAD_TOWN        = -109,
    STORY_CH0_KAMMY_RETURNED_TO_BOWSER          = -108,
    STORY_CH0_ARRIVED_AT_TOAD_TOWN              = -107,
    STORY_CH0_MET_STAR_SPIRITS                  = -106,
    STORY_CH0_BEGAN_PEACH_MISSION               = -105,
    STORY_CH0_TWINK_GAVE_LUCKY_STAR             = -104,
    STORY_CH0_RETURNED_TO_TOAD_TOWN             = -103,
    STORY_CH1_SPOKE_WITH_MERLIN                 = -102,
    STORY_CH1_TOLD_MERLIN_ABOUT_DARK_TOADS      = -101,
    STORY_CH1_MERLIN_REVEALED_KOOPA_BROS        = -100,
    STORY_CH1_KNOCKED_SWITCH_FROM_TREE          = -99,
    STORY_CH1_MADE_FIRST_BRIDGE                 = -98,
    STORY_CH1_ARRIVED_AT_KOOPA_VILLAGE          = -97,
    STORY_CH1_PROMISED_TO_HELP_KOOPER           = -96,
    STORY_CH1_FUZZY_THIEF_LEFT_TOWN             = -95,
    STORY_CH1_FUZZY_THIEF_RAN_AWAY              = -94,
    STORY_CH1_FUZZY_THIEF_HID_IN_TREE           = -93,
    STORY_CH1_KOOPER_JOINED_PARTY               = -92,
    STORY_CH1_MADE_SECOND_BRIDGE                = -91,
    STORY_CH1_ARRIVED_AT_KOOPA_FORTRESS         = -90,
    STORY_CH1_SPOTTED_BY_KOOPA_BROS             = -89,
    STORY_CH1_KOOPA_BROS_HID_KEY                = -88,
    STORY_CH1_DEFEATED_BASEMENT_GUARD           = -87,
    STORY_CH1_LOWERED_FIRST_STAIRS              = -86,
    STORY_CH1_KOOPA_BROS_SET_TRAP               = -85,
    STORY_CH1_MARIO_ACTIVATED_TRAP              = -84,
    STORY_CH1_BOMBETTE_JOINED_PARTY             = -83,
    STORY_CH1_DEFEATED_DUNGEON_GUARDS           = -82,
    STORY_CH1_LOWERED_SECOND_STAIRS             = -81,
    STORY_CH1_RAISED_SUBMERGED_STAIRS           = -80,
    STORY_CH1_KOOPA_BROS_FIRING_BLASTERS        = -79,
    STORY_CH1_DEFEATED_KOOPA_BROS               = -78,
    STORY_CH1_STAR_SPIRIT_RESCUED               = -77,
    STORY_CH1_BEGAN_PEACH_MISSION               = -76,
    STORY_CH1_STAR_SPRIT_DEPARTED               = -75,
    STORY_CH1_DEFEATED_JR_TROOPA                = -74,
    STORY_CH1_RETURNED_TO_TOAD_TOWN             = -73,
    STORY_CH2_ARRIVED_AT_MT_RUGGED              = -72,
    STORY_CH2_SPOKE_WITH_PARAKARRY              = -71,
    STORY_CH2_PARAKARRY_JOINED_PARTY            = -70,
    STORY_CH2_ARRIVED_AT_DRY_DRY_DESERT         = -69,
    STORY_CH2_ARRIVED_AT_DRY_DRY_OUTPOST        = -68,
    STORY_CH2_SHADY_MOUSE_LEFT_SHOP             = -67,
    STORY_CH2_SPOKE_WITH_SHEEK                  = -66,
    STORY_CH2_SHADY_MOUSE_ENTERED_SHOP          = -65,
    STORY_CH2_BOUGHT_SECRET_ITEMS               = -64,
    STORY_CH2_GOT_PULSE_STONE                   = -63,
    STORY_CH2_UNCOVERED_DRY_DRY_RUINS           = -62,
    STORY_CH2_DRAINED_FIRST_SAND_ROOM           = -61,
    STORY_CH2_DRAINED_SECOND_SAND_ROOM          = -60,
    STORY_CH2_GOT_SUPER_HAMMER                  = -59,
    STORY_CH2_DRAINED_THIRD_SAND_ROOM           = -58,
    STORY_CH2_SOLVED_ARTIFACT_PUZZLE            = -57,
    STORY_CH2_DEFEATED_TUTANKOOPA               = -56,
    STORY_CH2_STAR_SPIRIT_RESCUED               = -55,
    STORY_CH2_BEGAN_PEACH_MISSION               = -54,
    STORY_CH2_STAR_SPRIT_DEPARTED               = -53,
    STORY_UNUSED_FFFFFFCC                       = -52,
    STORY_CH3_SAW_BOO_ENTER_FOREST              = -51,
    STORY_CH3_INVITED_TO_BOOS_MANSION           = -50,
    STORY_CH3_ALLOWED_INTO_FOREVER_FOREST       = -49,
    STORY_CH3_ARRIVED_AT_BOOS_MANSION           = -48,
    STORY_CH3_OPENED_BOOS_MANSION_GATE          = -47,
    STORY_CH3_ENTERED_BOOS_MANSION              = -46,
    STORY_CH3_TRIGGERED_DOOR_JUMP_SCARE         = -45,
    STORY_CH3_GOT_RECORD                        = -44,
    STORY_CH3_PLAYED_THE_RECORD                 = -43,
    STORY_CH3_GOT_WEIGHT                        = -42,
    STORY_CH3_WEIGHED_DOWN_CHANDELIER           = -41,
    STORY_CH3_GOT_SUPER_BOOTS                   = -40,
    STORY_CH3_HIT_HUGE_BLUE_SWITCH              = -39,
    STORY_CH3_GOT_BOO_PORTRAIT                  = -38,
    STORY_CH3_RESTORED_BOO_PORTRAIT             = -37,
    STORY_CH3_BOW_JOINED_PARTY                  = -36,
    STORY_CH3_UNLOCKED_GUSTY_GULCH              = -35,
    STORY_CH3_ARRIVED_AT_GHOST_TOWN             = -34,
    STORY_CH3_SAW_TUBBA_EAT_BOO                 = -33,
    STORY_CH3_ARRIVED_AT_TUBBAS_MANOR           = -32,
    STORY_UNUSED_FFFFFFE1                       = -31,
    STORY_CH3_TUBBA_BEGAN_NAPPING               = -30,
    STORY_CH3_TUBBA_WOKE_UP                     = -29,
    STORY_CH3_TUBBA_SMASHED_THE_BRIDGES         = -28,
    STORY_CH3_TUBBA_CHASED_MARIO_IN_HALL        = -27,
    STORY_CH3_TUBBA_CHASED_MARIO_IN_FOYER       = -26,
    STORY_CH3_ESCAPED_TUBBAS_MANOR              = -25,
    STORY_CH3_UNLOCKED_WINDY_MILL               = -24,
    STORY_CH3_WENT_DOWN_THE_WELL                = -23,
    STORY_CH3_HEART_FLED_FIRST_TUNNEL           = -22,
    STORY_UNUSED_FFFFFFEB                       = -21,
    STORY_UNUSED_FFFFFFEC                       = -20,
    STORY_CH3_HEART_FLED_SECOND_TUNNEL          = -19,
    STORY_CH3_HEART_ESCAPED_WELL                = -18,
    STORY_CH3_HEART_ESCAPED_WINDY_MILL          = -17,
    STORY_CH3_DEFEATED_TUBBA_BLUBBA             = -16,
    STORY_CH3_STAR_SPIRIT_RESCUED               = -15,
    STORY_CH3_BEGAN_PEACH_MISSION               = -14,
    STORY_CH3_STAR_SPRIT_DEPARTED               = -13,
    STORY_CH4_FRYING_PAN_STOLEN                 = -12,
    STORY_CH4_MET_WITH_TWINK                    = -11,
    STORY_CH4_FOUND_HIDDEN_DOOR                 = -10,
    STORY_CH4_ENTERED_THE_TOY_BOX               = -9,
    STORY_CH4_GOT_STOREROOM_KEY                 = -8,
    STORY_CH4_RETURNED_STOREROOM_KEY            = -7,
    STORY_CH4_GOT_TOY_TRAIN                     = -6,
    STORY_CH4_RETURNED_TOY_TRAIN                = -5,
    STORY_CH4_GOT_FRYING_PAN                    = -4,
    STORY_CH4_GOT_TAYCE_TS_CAKE                 = -3,
    STORY_CH4_GAVE_CAKE_TO_GOURMET_GUY          = -2,
    STORY_CH4_PULLED_SWITCH_SWITCH              = -1,
    STORY_CH4_SOLVED_COLOR_PUZZLE               = 0,
    STORY_CH4_DEFEATED_LANTERN_GHOST            = 1,
    STORY_CH4_WATT_JOINED_PARTY                 = 2,
    STORY_CH4_OPENED_GENERAL_GUY_ROOM           = 3,
    STORY_CH4_DEFEATED_GENERAL_GUY              = 4,
    STORY_CH4_STAR_SPIRIT_RESCUED               = 5,
    STORY_CH4_BEGAN_PEACH_MISSION               = 6,
    STORY_CH4_STAR_SPRIT_DEPARTED               = 7,
    STORY_CH5_WHALE_MOUTH_OPEN                  = 8,
    STORY_CH5_ENTERED_WHALE                     = 9,
    STORY_CH5_DEFEATED_FUZZIPEDE                = 10,
    STORY_CH5_REACHED_LAVA_LAVA_ISLAND          = 11,
    STORY_CH5_KOLORADO_ESCAPED_FUZZIES          = 12,
    STORY_CH5_KOLORADO_ESCAPED_SPEAR_GUYS       = 13,
    STORY_CH5_YOSHI_CHILDREN_ARE_MISSING        = 14,
    STORY_CH5_SUSHIE_JOINED_PARTY               = 15,
    STORY_CH5_ALL_YOSHI_CHILDREN_RESCUED        = 16,
    STORY_CH5_GOT_JADE_RAVEN                    = 17,
    STORY_CH5_MOVED_RAVEN_STATUE                = 18,
    STORY_CH5_DEFEATED_PIRANHAS_MINIBOSS        = 19,
    STORY_CH5_REACHED_RAPHAELS_TREE             = 20,
    STORY_CH5_RAPHAEL_LEFT_NEST                 = 21,
    STORY_CH5_RAPHAEL_MOVED_ROOT                = 22,
    STORY_CH5_RAPHAEL_WAITING_FOR_MARIO         = 23,
    STORY_CH5_ZIP_LINE_READY                    = 24,
    STORY_CH5_ENTERED_MT_LAVA_LAVA              = 25,
    STORY_CH5_KOLORADO_FELL_IN_LAVA             = 26,
    STORY_CH5_LAVA_STREAM_BLOCKED               = 27,
    STORY_CH5_GOT_ULTRA_HAMMER                  = 28,
    STORY_CH5_SMASHED_ULTRA_BLOCK               = 29,
    STORY_CH5_KOLORADO_FELL_IN_PIT              = 30,
    STORY_CH5_KOLORADO_AT_DEAD_END              = 31,
    STORY_CH5_HIDDEN_PASSAGE_OPEN               = 32,
    STORY_CH5_KOLORADO_RAN_AHEAD                = 33,
    STORY_CH5_KOLORADO_IN_TREASURE_ROOM         = 34,
    STORY_CH5_DEFEATED_LAVA_PIRANHA             = 35,
    STORY_CH5_MT_LAVA_LAVA_ERUPTING             = 36,
    STORY_CH5_OPENED_ESCAPE_ROUTE               = 37,
    STORY_CH5_BEGAN_PEACH_MISSION               = 38,
    STORY_CH5_STAR_SPRIT_DEPARTED               = 39,
    STORY_CH5_TRADED_VASE_FOR_SEED              = 40,
    STORY_CH5_RETURNED_TO_TOAD_TOWN             = 41,
    STORY_CH6_FLOWER_GATE_OPEN                  = 42,
    STORY_CH6_ARRIVED_AT_FLOWER_FIELDS          = 43,
    STORY_CH6_ASKED_TO_DEFEAT_MONTY_MOLES       = 44,
    STORY_CH6_GOT_MAGICAL_BEAN                  = 45,
    STORY_CH6_GOT_FERTILE_SOIL                  = 46,
    STORY_CH6_GOT_CRYSTAL_BERRY                 = 47,
    STORY_CH6_GOT_WATER_STONE                   = 48,
    STORY_CH6_FILLED_SPRING_WITH_WATER          = 49,
    STORY_CH6_SPOKE_WITH_THE_SUN                = 50,
    STORY_CH6_LAKILESTER_JOINED_PARTY           = 51,
    STORY_CH6_DEFEATED_PUFF_PUFF_GUARDS         = 52,
    STORY_CH6_DESTROYED_PUFF_PUFF_MACHINE       = 53,
    STORY_CH6_WISTERWOOD_GAVE_HINT              = 54,
    STORY_CH6_GREW_MAGIC_BEANSTALK              = 55,
    STORY_CH6_DEFEATED_HUFF_N_PUFF              = 56,
    STORY_CH6_STAR_SPIRIT_RESCUED               = 57,
    STORY_CH6_BEGAN_PEACH_MISSION               = 58,
    STORY_CH6_STAR_SPRIT_DEPARTED               = 59,
    STORY_CH6_RETURNED_TO_TOAD_TOWN             = 60,
    STORY_CH7_INVITED_TO_STARBORN_VALLEY        = 61,
    STORY_CH7_ARRIVED_AT_SHIVER_CITY            = 62,
    STORY_CH7_MAYOR_MURDER_MYSTERY              = 63,
    STORY_CH7_SHATTERED_FROZEN_POND             = 64,
    STORY_CH7_SPOKE_WITH_HERRINGWAY             = 65,
    STORY_CH7_HERRINGWAY_AT_MAYORS_HOUSE        = 66,
    STORY_CH7_MAYOR_MURDER_SOLVED               = 67,
    STORY_CH7_DEFEATED_JR_TROOPA                = 68,
    STORY_CH7_DEFEATED_MONSTAR                  = 69,
    STORY_CH7_ARRIVED_AT_STARBORN_VALLEY        = 70,
    STORY_CH7_MERLE_APOLOGIZED                  = 71,
    STORY_CH7_GOT_SNOWMAN_SCARF                 = 72,
    STORY_CH7_GOT_SNOWMAN_BUCKET                = 73,
    STORY_CH7_UNLOCKED_SHIVER_MOUNTAIN          = 74,
    STORY_CH7_DEFEATED_FIRST_DUPLIGHOST         = 75,
    STORY_CH7_GOT_STAR_STONE                    = 76,
    STORY_CH7_RAISED_FROZEN_STAIRS              = 77,
    STORY_CH7_ARRIVED_AT_CRYSTAL_PALACE         = 78,
    STORY_CH7_DEFEATED_MIRROR_DUPLIGHOSTS       = 79,
    STORY_CH7_DEFEATED_BOMBETTE_DUPLIGHOSTS     = 80,
    STORY_CH7_DEFEATED_CLUBBAS                  = 81,
    STORY_CH7_DEFEATED_KOOPER_DUPLIGHOSTS       = 82,
    STORY_CH7_EXTENDED_PALACE_BRIDGE            = 83,
    STORY_CH7_FOUND_HIDDEN_ROOM_UNDER_STATUE    = 84,
    STORY_CH7_SOLVED_ALBINO_DINO_PUZZLE         = 85,
    STORY_CH7_DEFEATED_CRYSTAL_KING             = 86,
    STORY_CH7_STAR_SPIRIT_RESCUED               = 87,
    STORY_CH7_BEGAN_PEACH_MISSION               = 88,
    STORY_CH7_STAR_SPRIT_DEPARTED               = 89,
    STORY_CH8_OPENED_PATH_TO_STAR_WAY           = 90,
    STORY_CH8_REACHED_STAR_HAVEN                = 91,
    STORY_CH8_STAR_SHIP_ACTIVATED               = 92,
    STORY_UNUSED_0000005D                       = 93,
    STORY_CH8_REACHED_BOWSERS_CASTLE            = 94,
    STORY_CH8_REACHED_PEACHS_CASTLE             = 95,
    STORY_EPILOGUE                              = 96,
    STORY_NEVER                                 = 97,
};

enum KoopaKootFavors {
    KOOT_FAVOR_CH1_1        = 0,
    KOOT_FAVOR_CH1_2        = 1,
    KOOT_FAVOR_CH2_1        = 2,
    KOOT_FAVOR_CH2_2        = 3,
    KOOT_FAVOR_CH2_3        = 4,
    KOOT_FAVOR_CH3_1        = 5,
    KOOT_FAVOR_CH3_2        = 6,
    KOOT_FAVOR_CH3_3        = 7,
    KOOT_FAVOR_CH4_1        = 8,
    KOOT_FAVOR_CH4_2        = 9,
    KOOT_FAVOR_CH4_3        = 10,
    KOOT_FAVOR_CH5_1        = 11,
    KOOT_FAVOR_CH5_2        = 12,
    KOOT_FAVOR_CH5_3        = 13,
    KOOT_FAVOR_CH6_1        = 14,
    KOOT_FAVOR_CH6_2        = 15,
    KOOT_FAVOR_CH6_3        = 16,
    KOOT_FAVOR_CH7_1        = 17,
    KOOT_FAVOR_CH7_2        = 18,
    KOOT_FAVOR_CH7_3        = 19,
};

enum KoopaKootFavorStates {
    KOOT_FAVOR_STATE_0      = 0,
    KOOT_FAVOR_STATE_1      = 1,
    KOOT_FAVOR_STATE_2      = 2,
};

enum EncounterTriggers {
    ENCOUNTER_TRIGGER_NONE                            = 1,
    ENCOUNTER_TRIGGER_JUMP                            = 2,
    ENCOUNTER_TRIGGER_SPIN                            = 3,
    ENCOUNTER_TRIGGER_HAMMER                          = 4,
    ENCOUNTER_TRIGGER_CONVERSATION                    = 5,
    ENCOUNTER_TRIGGER_PARTNER                         = 6,
};

enum SoundOutputMode {
    SOUND_OUT_MONO                                    = 0,
    SOUND_OUT_STEREO                                  = 1,
};

#include "audio/song_ids.h"
#include "audio/sound_ids.h"

enum Abilities {
    ABILITY_DODGE_MASTER            = 0x00000000,
    ABILITY_UNUSED                  = 0x00000001,
    ABILITY_SPIKE_SHIELD            = 0x00000002,
    ABILITY_FIRST_ATTACK            = 0x00000003,
    ABILITY_HP_PLUS                 = 0x00000004,
    ABILITY_DOUBLE_DIP              = 0x00000005,
    ABILITY_MYSTERY_SCROLL          = 0x00000006,
    ABILITY_FIRE_SHIELD             = 0x00000007,
    ABILITY_PRETTY_LUCKY            = 0x00000008,
    ABILITY_HP_DRAIN                = 0x00000009,
    ABILITY_ALL_OR_NOTHING          = 0x0000000A,
    ABILITY_SLOW_GO                 = 0x0000000B,
    ABILITY_FP_PLUS                 = 0x0000000C,
    ABILITY_ICE_POWER               = 0x0000000D,
    ABILITY_FEELING_FINE            = 0x0000000E,
    ABILITY_ATTACK_FX               = 0x0000000F,
    ABILITY_MONEY_MONEY             = 0x00000010,
    ABILITY_CHILL_OUT               = 0x00000011,
    ABILITY_HAPPY_HEART             = 0x00000012,
    ABILITY_ZAP_TAP                 = 0x00000013,
    ABILITY_MEGA_RUSH               = 0x00000014,
    ABILITY_BERSERKER               = 0x00000015,
    ABILITY_RIGHT_ON                = 0x00000016,
    ABILITY_RUNAWAY_PAY             = 0x00000017,
    ABILITY_FLOWER_SAVER            = 0x00000018,
    ABILITY_PAY_OFF                 = 0x00000019,
    ABILITY_QUICK_CHANGE            = 0x0000001A,
    ABILITY_DEFEND_PLUS             = 0x0000001B,
    ABILITY_POWER_PLUS              = 0x0000001C,
    ABILITY_REFUND                  = 0x0000001D,
    ABILITY_POWER_RUSH              = 0x0000001E,
    ABILITY_CRAZY_HEART             = 0x0000001F,
    ABILITY_LAST_STAND              = 0x00000020,
    ABILITY_CLOSE_CALL              = 0x00000021,
    ABILITY_P_UP_D_DOWN             = 0x00000022,
    ABILITY_LUCKY_DAY               = 0x00000023,
    ABILITY_MEGA_HP_DRAIN           = 0x00000024,
    ABILITY_P_DOWN_D_UP             = 0x00000025,
    ABILITY_FLOWER_FANATIC          = 0x00000026,
    ABILITY_SPEEDY_SPIN             = 0x00000027,
    ABILITY_SPIN_ATTACK             = 0x00000028,
    ABILITY_I_SPY                   = 0x00000029,
    ABILITY_BUMP_ATTACK             = 0x0000002A,
    ABILITY_HEART_FINDER            = 0x0000002B,
    ABILITY_FLOWER_FINDER           = 0x0000002C,
    ABILITY_DIZZY_ATTACK            = 0x0000002D,
    ABILITY_FINAL_GOOMPA            = 0x0000002E,
    ABILITY_FINAL_BOBOMB            = 0x0000002F,
    ABILITY_DEEP_FOCUS              = 0x00000030,
    ABILITY_SUPER_FOCUS             = 0x00000031,
    ABILITY_KAIDEN                  = 0x00000032,
    ABILITY_DAMAGE_DODGE            = 0x00000033,
    ABILITY_HAPPY_FLOWER            = 0x00000034,
    ABILITY_GROUP_FOCUS             = 0x00000035,
    ABILITY_PEEKABOO                = 0x00000036,
    ABILITY_HEALTHY_HEALTHY         = 0x00000037,
};

enum Emotes {
    EMOTE_EXCLAMATION        = 0,
    EMOTE_SHOCK              = 1,
    EMOTE_QUESTION           = 2,
    EMOTE_FRUSTRATION        = 3,
    EMOTE_ELLIPSIS           = 4,
};

enum Emoters {
    EMOTER_PLAYER   = 0,
    EMOTER_NPC      = 1,
    EMOTER_POS      = 2,
};

enum EasingType {
    EASING_LINEAR                   = 0,
    EASING_QUADRATIC_IN             = 1,
    EASING_CUBIC_IN                 = 2,
    EASING_QUARTIC_IN               = 3,
    EASING_QUADRATIC_OUT            = 4,
    EASING_CUBIC_OUT                = 5,
    EASING_QUARTIC_OUT              = 6,
    EASING_COS_SLOW_OVERSHOOT       = 7,
    EASING_COS_FAST_OVERSHOOT       = 8,
    EASING_COS_BOUNCE               = 9,
    EASING_COS_IN_OUT               = 10,
    EASING_SIN_OUT                  = 11,
    EASING_COS_IN                   = 12,
};

enum SoundIDBits {
    SOUND_ID_STOP                   = 0x00008000,
    SOUND_ID_LOWER                  = 0x000063FF,
    SOUND_ID_EXT                    = 0x00004000, // sounds belonging to extended sections 8-15
    SOUND_ID_UNK                    = 0x00002000, // sounds belonging to special large section
    SOUND_ID_ADJUST                 = 0x00001000,
    SOUND_ID_TRIGGER_MASK           = 0x00000C00,
    SOUND_ID_TRIGGER_CHANGE_VOLUME  = 0x00000800,
    SOUND_ID_TRIGGER_CHANGE_SOUND   = 0x00000400,
    SOUND_ID_SECTION_MASK           = 0x00000300, // corresponds to sections 0-3 for indices < 0xC0 and 4-7 for those above (add 8 with SOUND_ID_EXT)
    SOUND_ID_INDEX_MASK             = 0x000000FF,
    SOUND_ID_UNK_INDEX_MASK         = 0x000001FF, // indices for the special large section

    SOUND_ID_UPPER_MASK             = 0x03FF0000,
    SOUND_ID_TYPE_MASK              = 0x70000000,
    SOUND_ID_TYPE_FLAG              = 0x80000000,
};

enum SoundType {
    SOUND_TYPE_LOOPING              = 0, // 0x80000000 (with SOUND_ID_TYPE_FLAG)
    SOUND_TYPE_EXIT_DOOR            = 1, // 0x90000000 (with SOUND_ID_TYPE_FLAG)
    SOUND_TYPE_ROOM_DOOR            = 2, // 0xA0000000 (with SOUND_ID_TYPE_FLAG)
    SOUND_TYPE_ALTERNATING          = 3, // 0xB0000000 (with SOUND_ID_TYPE_FLAG)
};

enum SoundIDsTyped {
    // looping sounds
    SOUND_LOOP_BOMBETTE_FUSE                    = 0x80000000,
    SOUND_LOOP_BOBOMB_FUSE                      = 0x80000001,
    SOUND_LOOP_ISK_FLIP_STAIRS                  = 0x80000002,
    SOUND_LOOP_ISK_LOWER_STAIRS                 = 0x80000003,
    SOUND_LOOP_TRD_02_LOWER_STAIRS              = 0x80000004,
    SOUND_LOOP_TRD_04_LOWER_STAIRS              = 0x80000005,
    SOUND_LOOP_TRD_FLOWING_WATER                = 0x80000006,
    SOUND_LOOP_TRD_RAISE_STAIRS                 = 0x80000007,
    SOUND_LOOP_CHEERING                         = 0x80000008,
    SOUND_LOOP_IWA10_FLOW1                      = 0x80000009,
    SOUND_LOOP_IWA_UNUSED_FLOW3                 = 0x8000000A, // #unused
    SOUND_LOOP_IWA00_FLOW3                      = 0x8000000B,
    SOUND_LOOP_IWA00_FLOW2                      = 0x8000000C,
    SOUND_LOOP_IWA01_FLOW1                      = 0x8000000D,
    SOUND_LOOP_IWA01_FLOW2                      = 0x8000000E,
    SOUND_LOOP_OBK_LOWER_CHAIN                  = 0x8000000F,
    SOUND_LOOP_MOVE_STATUE                      = 0x80000010,
    SOUND_LOOP_SENTINEL_ALARM                   = 0x80000011,
    SOUND_LOOP_QUIZ_TICKING                     = 0x80000012, // #unused
    SOUND_LOOP_AUDIENCE_MURMUR                  = 0x80000013, // #unused
    SOUND_LOOP_TOYBOX_TRAIN_GEAR                = 0x80000014, // #unused
    SOUND_LOOP_OMO_SLOT_MACHINE                 = 0x80000015,
    SOUND_LOOP_OMO_ROTATING_WHEEL               = 0x80000016,
    SOUND_LOOP_JAN_BEACH_WAVES                  = 0x80000017,
    SOUND_LOOP_MOVE_LARGE_STATUE                = 0x80000018,
    SOUND_LOOP_ZIPLINE_RIDE                     = 0x80000019,
    SOUND_LOOP_ZIPLINE_RETURN                   = 0x8000001A,
    SOUND_LOOP_TROMP_ROLL                       = 0x8000001B,
    SOUND_LOOP_JAN_SMALL_GEYSER                 = 0x8000001C,
    SOUND_LOOP_JAN_LARGE_GEYSER                 = 0x8000001D,
    SOUND_LOOP_JAN_CONSTRUCTION                 = 0x8000001E,
    SOUND_LOOP_NOTHING_1F                       = 0x8000001F, // #unused #nodata
    SOUND_LOOP_NOTHING_20                       = 0x80000020, // #unused #nodata
    SOUND_LOOP_FLO_WATER_FLOW_1                 = 0x80000021,
    SOUND_LOOP_FLO_WATER_FLOW_2                 = 0x80000022,
    SOUND_LOOP_BUBBLE_DRIFT                     = 0x80000023,
    SOUND_LOOP_FLO_RELEASE_FOUNTAIN             = 0x80000024,
    SOUND_LOOP_PUFF_PUFF_MACHINE                = 0x80000025,
    SOUND_LOOP_NOTHING_26                       = 0x80000026, // #unused #nodata
    SOUND_LOOP_TIK01_WATER                      = 0x80000027,
    SOUND_LOOP_TIK02_WATER                      = 0x80000028,
    SOUND_LOOP_TIK02_FLOW2                      = 0x80000029,
    SOUND_LOOP_TIK02_FLOW3                      = 0x8000002A,
    SOUND_LOOP_TIK03_WATER                      = 0x8000002B,
    SOUND_LOOP_TIK03_FLOW1                      = 0x8000002C,
    SOUND_LOOP_TIK05_WATER                      = 0x8000002D,
    SOUND_LOOP_TIK05_FLOW1                      = 0x8000002E,
    SOUND_LOOP_TIK06_WATER                      = 0x8000002F,
    SOUND_LOOP_TIK06_FLOW2                      = 0x80000030,
    SOUND_LOOP_TIK06_FLOW3                      = 0x80000031,
    SOUND_LOOP_TIK06_FLOW4                      = 0x80000032,
    SOUND_LOOP_TIK08_WATER                      = 0x80000033,
    SOUND_LOOP_TIK08_FLOW1                      = 0x80000034,
    SOUND_LOOP_TIK09_WATER                      = 0x80000035,
    SOUND_LOOP_TIK09_FLOW2                      = 0x80000036,
    SOUND_LOOP_TIK09_FLOW4                      = 0x80000037,
    SOUND_LOOP_TIK09_FLOW3                      = 0x80000038,
    SOUND_LOOP_TIK10_WATER                      = 0x80000039,
    SOUND_LOOP_TIK_UNUSED1_WATER                = 0x8000003A, // #unused
    SOUND_LOOP_TIK_UNUSED2_WATER                = 0x8000003B, // #unused
    SOUND_LOOP_TIK_UNUSED3_WATER                = 0x8000003C, // #unused
    SOUND_LOOP_TIK_UNUSED3_FLOW4                = 0x8000003D, // #unused
    SOUND_LOOP_TIK_UNUSED3_FLOW3                = 0x8000003E, // #unused
    SOUND_LOOP_TIK_UNUSED3_FLOW2                = 0x8000003F, // #unused
    SOUND_LOOP_SAM_STAIRS_RISE                  = 0x80000040,
    SOUND_LOOP_CHARGE_METER                     = 0x80000041,
    SOUND_LOOP_CRYSTAL_BALL_GLOW                = 0x80000042,
    SOUND_LOOP_TIK18_WATER                      = 0x80000043,
    SOUND_LOOP_TIK19_WATER                      = 0x80000044,
    SOUND_LOOP_TIK19_FLOW3                      = 0x80000045,
    SOUND_LOOP_TIK19_FLOW4                      = 0x80000046,
    SOUND_LOOP_TIK20_WATER                      = 0x80000047,
    SOUND_LOOP_TIK23_WATER                      = 0x80000048,
    SOUND_LOOP_TIK24_WATER                      = 0x80000049,
    SOUND_LOOP_WINDMILL_EXT                     = 0x8000004A,
    SOUND_LOOP_WINDMILL_GEARS                   = 0x8000004B,
    SOUND_LOOP_SHY_GUY_CROWD_1                  = 0x8000004C,
    SOUND_LOOP_SHY_GUY_CROWD_2                  = 0x8000004D,
    SOUND_LOOP_FLIGHT                           = 0x8000004E, // #unused
    SOUND_LOOP_WHALE_GEYSER                     = 0x8000004F,
    SOUND_LOOP_FLO_FILL_WATER_POOL              = 0x80000050,
    SOUND_LOOP_KPA_CHAIN_DRIVE                  = 0x80000051,
    SOUND_LOOP_KPA_FILL_WATER                   = 0x80000052,
    SOUND_LOOP_KPA_DRAIN_WATER                  = 0x80000053,
    SOUND_LOOP_KPA_FLIP_BRIDGE_PANEL            = 0x80000054, // #unused
    SOUND_LOOP_JR_TROOPA_SWIM                   = 0x80000055,
    SOUND_LOOP_KKJ_RUMBLING                     = 0x80000056,
    SOUND_LOOP_OSR_RUMBLING                     = 0x80000057,
    SOUND_LOOP_MAC_HARBOR_WATER                 = 0x80000058,
    SOUND_LOOP_OSR_FOUNTAIN_INTACT              = 0x80000059,
    SOUND_LOOP_OSR_FOUNTAIN_BROKEN              = 0x8000005A,
    SOUND_LOOP_NOK_WATER                        = 0x8000005B,
    SOUND_LOOP_TRD_WATER_EXT                    = 0x8000005C,
    SOUND_LOOP_DGB_COLLAPSE                     = 0x8000005D,
    SOUND_LOOP_SBK_RUINS_RISING                 = 0x8000005E,
    SOUND_LOOP_SBK_RUINS_WHIRLWIND              = 0x8000005F,
    SOUND_LOOP_SBK_RUINS_RISING_DISTANT         = 0x80000060,
    SOUND_LOOP_SBK_OASIS_WATER                  = 0x80000061,
    SOUND_LOOP_62                               = 0x80000062, // unused, no data
    SOUND_LOOP_STAR_SANCTUARY_FAR               = 0x80000063,
    SOUND_LOOP_STAR_SANCTUARY_NEAR              = 0x80000064,
    SOUND_LOOP_STAR_SANCTUARY_INSIDE            = 0x80000065,
    SOUND_LOOP_BOWSER_PROPELLER                 = 0x80000066,
    SOUND_LOOP_STAR_ORB_RISING                  = 0x80000067,
    SOUND_LOOP_USE_STAR_BEAM                    = 0x80000068,
    SOUND_LOOP_USE_PEACH_BEAM                   = 0x80000069,
    SOUND_LOOP_SPINNING_FLOWER                  = 0x8000006A, // doesn't loop
    SOUND_LOOP_RUMBLE                           = 0x8000006B,
    SOUND_LOOP_FIGHTING                         = 0x8000006C,
    SOUND_LOOP_KPA_ARENA_TURN_ON                = 0x8000006D, // unused
    SOUND_LOOP_KPA_ARENA_ACTIVE                 = 0x8000006E, // unused
    // exit doors
    SOUND_DOOR_OPEN                             = 0x90000000,
    SOUND_DOOR_CLOSE                            = 0x90000001,
    // room doors
    SOUND_ROOM_DOOR_OPEN                        = 0xA0000000,
    SOUND_ROOM_DOOR_CLOSE                       = 0xA0000001,
    // alternating sounds
    SOUND_SEQ_FIRE_BAR_0                        = 0xB0000000,
    SOUND_SEQ_FIRE_BAR_1                        = 0xB0000001,
    SOUND_SEQ_FIRE_BAR_2                        = 0xB0000002,
    SOUND_SEQ_FIRE_BAR_3                        = 0xB0000003,
    SOUND_SEQ_FIRE_BAR_4                        = 0xB0000004,
    SOUND_SEQ_FIRE_BAR_5                        = 0xB0000005,
    SOUND_SEQ_FIRE_BAR_6                        = 0xB0000006,
    SOUND_SEQ_FIRE_BAR_7                        = 0xB0000007,
    SOUND_SEQ_FIRE_BAR_8                        = 0xB0000008,
    SOUND_SEQ_FIRE_BAR_9                        = 0xB0000009,
    SOUND_SEQ_FIRE_BAR_DEAD                     = 0xB000000A,
    SOUND_SEQ_AI_ALERT                          = 0xB000000B,
    SOUND_SEQ_SNORE_INHALE                      = 0xB000000C,
    SOUND_SEQ_SNORE_EXHALE                      = 0xB000000D,
    SOUND_SEQ_SNAP_AWAKE                        = 0xB000000E,
    SOUND_SEQ_BOO_VANISH                        = 0xB000000F,
    SOUND_SEQ_BOO_APPEAR                        = 0xB0000010,
    SOUND_SEQ_WINDOW_OPEN                       = 0xB0000011,
    SOUND_SEQ_WINDOW_CLOSE                      = 0xB0000012,
    SOUND_SEQ_RAVEN_LEAP                        = 0xB0000013,
    SOUND_SEQ_RAVEN_FALL                        = 0xB0000014,
    SOUND_SEQ_SHOOTING_STAR_FALL                = 0xB0000015,
    SOUND_SEQ_SHOOTING_STAR_BOUNCE              = 0xB0000016,
    SOUND_SEQ_FUZZY_HOP                         = 0xB0000017,
    SOUND_SEQ_BULLET_BILL_EXPLODE               = 0xB0000018,
    SOUND_SEQ_LUIGI_STEP                        = 0xB0000019,
    SOUND_SEQ_TRAIN_CHUG                        = 0xB000001A,
    SOUND_SEQ_FINALE_BRIDGE_COLLAPSE            = 0xB000001B,
    SOUND_SEQ_FINALE_EXPLOSION                  = 0xB000001C,
    SOUND_SEQ_SHUFFLE_CARD                      = 0xB000001D,
    SOUND_SEQ_STAR_SPIRIT_APPEAR                = 0xB000001E,
    SOUND_SEQ_STAR_SPIRIT_CAST                  = 0xB000001F,
    SOUND_SEQ_UNUSED_EXPLODE                    = 0xB0000020,
    SOUND_SEQ_SHY_GUY_STEP                      = 0xB0000021,
};

enum SoundSpatializationFlags {
    SOUND_SPACE_MODE_MASK           = 0x0000FFFF,
    SOUND_SPACE_DEFAULT             = 0x00000000,
    SOUND_SPACE_WITH_DEPTH          = 0x00000001,
    SOUND_SPACE_FULL                = 0x00000002,
    SOUND_SPACE_PARAMS_MASK         = 0xFFFF0000,
    SOUND_PARAM_MUTE                = 0x00010000,
    SOUND_PARAM_CLIP_OFFSCREEN_ANY  = 0x00020000,
    SOUND_PARAM_CLIP_OFFSCREEN_X    = 0x00040000,
    SOUND_PARAM_CLIP_OFFSCREEN_Y    = 0x00080000,
    SOUND_PARAM_MOST_QUIET          = 0x00100000,
    SOUND_PARAM_MORE_QUIET          = 0x00200000,
    SOUND_PARAM_QUIET               = 0x00400000,
};

enum SoundTriggers {
    SOUND_TRIGGER_CHANGE_SOUND  = 1,
    SOUND_TRIGGER_CHANGE_VOLUME = 2,
};

typedef enum AuResult {
    AU_RESULT_OK                        = 0,
    AU_ERROR_1                          = 1,
    AU_AMBIENCE_STOP_ERROR_1            = 1,
    AU_AMBIENCE_STOP_ERROR_2            = 2,
    AU_AMBIENCE_ERROR_PLAYER_BUSY       = 1, // player already has an mseq playing
    AU_ERROR_SONG_NOT_PLAYING           = 2, // player not found for songName
    AU_AMBIENCE_ERROR_MSEQ_NOT_FOUND    = 2, // mseq not found
    AU_ERROR_NULL_SONG_NAME             = 3, // songName is nullptr
    AU_AMBIENCE_ERROR_3                 = 3,
    AU_ERROR_INVALID_SONG_DURATION      = 4, // duration out of bounds: (250,10000)
    AU_ERROR_6                          = 6,
    AU_ERROR_7                          = 7,
    AU_ERROR_11                         = 11,
    AU_ERROR_SBN_INDEX_OUT_OF_RANGE     = 101,
    AU_ERROR_SBN_FORMAT_MISMATCH        = 102,
    AU_ERROR_151                        = 151,
    AU_ERROR_201                        = 201
} AuResult;

typedef enum AuFileFormat {
    AU_FMT_BGM              = 0x10,
    AU_FMT_SEF              = 0x20,
    AU_FMT_BK               = 0x30,
    AU_FMT_PER              = 0x40,
    AU_FMT_PRG              = 0x40,
    AU_FMT_MSEQ             = 0x40
} AuFileFormat;

enum {
    MUSIC_PROXIMITY_FAR,
    MUSIC_PROXIMITY_NEAR,
    MUSIC_PROXIMITY_FULL
};

typedef enum MusicTrackVols {
    TRACK_VOLS_JAN_FULL     = 0,
    TRACK_VOLS_UNUSED_1     = 1,
    TRACK_VOLS_TIK_SHIVER   = 2,
    TRACK_VOLS_UNUSED_3     = 3,
    TRACK_VOLS_KPA_OUTSIDE  = 4,
    TRACK_VOLS_KPA_1        = 5,
    TRACK_VOLS_KPA_2        = 6,
    TRACK_VOLS_KPA_3        = 7
} MusicTrackVols;

typedef enum BGMVariation {
    BGM_VARIATION_0                 = 0,
    BGM_VARIATION_1                 = 1,
    BGM_VARIATION_2                 = 2,
    BGM_VARIATION_3                 = 3,
} BGMVariation;

/// Perceptual volume levels, 0 (mute) to 8 (max).
/// Only attenuates, never amplifies.
typedef enum VolumeLevels {
    VOL_LEVEL_MUTE      = 0,
    VOL_LEVEL_1         = 1,
    VOL_LEVEL_2         = 2,
    VOL_LEVEL_3         = 3,
    VOL_LEVEL_4         = 4,
    VOL_LEVEL_5         = 5,
    VOL_LEVEL_6         = 6,
    VOL_LEVEL_7         = 7,
    VOL_LEVEL_FULL      = 8,
} VolumeLevels;

enum Cams {
    CAM_DEFAULT      = 0,
    CAM_BATTLE       = 1,
    CAM_TATTLE       = 2,
    CAM_HUD          = 3,
};

enum CamShakeModes {
    CAM_SHAKE_CONSTANT_VERTICAL     = 0,
    CAM_SHAKE_ANGULAR_HORIZONTAL    = 1,
    CAM_SHAKE_DECAYING_VERTICAL     = 2,
};

// for use with SetBattleCamParam
enum BasicCameraParams {
    CAM_PARAM_SKIP_RECALC           = 1,
    CAM_PARAM_BOOM_LENGTH           = 2,
    CAM_PARAM_FOV_SCALE             = 3,
    CAM_PARAM_BOOM_PITCH            = 4,
    CAM_PARAM_BOOM_YAW              = 5,
    CAM_PARAM_BOOM_Y_OFFSET         = 6,
    CAM_PARAM_ZOOM_PERCENT          = 7,
};

#include "item_enum.h"

// used for chest and give item events
enum GotItemType {
    ITEM_TYPE_CONSUMABLE    = 0,
    ITEM_TYPE_KEY           = 1,
    ITEM_TYPE_BADGE         = 2,
    ITEM_TYPE_STAR_PIECE    = 3,
};

enum ItemTypeFlags {
    ITEM_TYPE_FLAG_WORLD_USABLE         = 0x0001,
    ITEM_TYPE_FLAG_BATTLE_USABLE        = 0x0002,
    ITEM_TYPE_FLAG_CONSUMABLE           = 0x0004,
    ITEM_TYPE_FLAG_KEY                  = 0x0008,
    ITEM_TYPE_FLAG_GEAR                 = 0x0020,
    ITEM_TYPE_FLAG_BADGE                = 0x0040,
    ITEM_TYPE_FLAG_FOOD_OR_DRINK        = 0x0080,
    ITEM_TYPE_FLAG_USE_DRINK_ANIMATION  = 0x0100,
    ITEM_TYPE_FLAG_ENTITY_COLLECTABLE   = 0x0200,
    ITEM_TYPE_FLAG_ENTITY_FULLSIZE      = 0x1000,
};

// both items and moves use these flags to determine what type of targets are eligible
// they are used during the construction of target lists and during the select target battle state
enum TargetFlags {
    TARGET_FLAG_SELECT_ONE              = 0x00000001, // player selects a single target
    TARGET_FLAG_2                       = 0x00000002,
    TARGET_FLAG_GROUND                  = 0x00000004, // only allow targets on the ground (row = 0)
    TARGET_FLAG_PLAYER                  = 0x00000008, // allow the player as a target, prevents enemies from being targets
    TARGET_FLAG_NOT_HIGH                = 0x00000010, // only allow targets in the first two rows (no moves use this)
    TARGET_FLAG_NOT_FLYING              = 0x00000020, // reject targets which have ACTOR_FLAG_FLYING
    TARGET_FLAG_NOT_GROUND              = 0x00000040, // reject targets on the ground (row = 0)
    TARGET_FLAG_80                      = 0x00000080, // jump, headbonk, belly flop (not read)
    TARGET_FLAG_PARTNER                 = 0x00000100, // allow the partner as a target, prevents enemies from being targets
    TARGET_FLAG_AIRLIFT                 = 0x00000400, // special case for air lift, only rejects targets on the ceiling
    TARGET_FLAG_JUMP_LIKE               = 0x00000800, // jump, headbonk, belly flop, ... and jump charge
    TARGET_FLAG_SMASH_LIKE              = 0x00001000, // smash moves
    TARGET_FLAG_NOT_BEHIND              = 0x00002000, // hammer, bombette body slam, kooper shell toss
    TARGET_FLAG_NOT_BELOW               = 0x00004000, // reject all targets below other targets
    TARGET_FLAG_PRIMARY_ONLY            = 0x00008000, // rejects all targets without ACTOR_PART_FLAG_PRIMARY_TARGET
    TARGET_FLAG_ALLOW_TARGET_ONLY       = 0x00010000, // allow targets which have ACTOR_FLAG_TARGET_ONLY
    TARGET_FLAG_TATTLE                  = 0x00020000, // special case for tattle, only rejects targets with ACTOR_FLAG_NO_TATTLE
    TARGET_FLAG_NO_CEILING              = 0x00040000, // rejects targets on the ceiling (those with ACTOR_FLAG_UPSIDE_DOWN)
    TARGET_FLAG_DIR_RIGHT               = 0x00100000, // directional filter used with CountTargets (bugged, unused)
    TARGET_FLAG_DIR_LEFT                = 0x00200000, // directional filter used with CountTargets (bugged, unused)
    TARGET_FLAG_DIR_BELOW               = 0x00400000, // directional filter used with CountTargets (bugged, unused)
    TARGET_FLAG_DIR_ABOVE               = 0x00800000, // directional filter used with CountTargets (bugged, unused)
    TARGET_FLAG_OVERRIDE                = 0x80000000, // skip choosing a target
};

enum ActorPartTargetFlags {
    ACTOR_PART_TARGET_NO_JUMP           = 0x01, // prevent any jump attacks from targeting
    ACTOR_PART_TARGET_NO_SMASH          = 0x02, // prevent any smash attacks from targeting
    ACTOR_PART_TARGET_NO_DAMAGE         = 0x04, // exempts from damage or status infliction
};

#include "audio/ambient_ids.h"

enum EncounterOutcomes {
    OUTCOME_PLAYER_WON          = 0,
    OUTCOME_PLAYER_LOST         = 1,
    OUTCOME_PLAYER_FLED         = 2,
    OUTCOME_ENEMY_FLED          = 3,
    OUTCOME_SKIP                = 4,
};

enum MerleeSpellType {
    MERLEE_SPELL_NONE           = 0,
    MERLEE_SPELL_ATK_BOOST      = 1,
    MERLEE_SPELL_DEF_BOOST      = 2,
    MERLEE_SPELL_EXP_BOOST      = 3,
    MERLEE_SPELL_COIN_BOOST     = 4,
};

enum NpcDecorationIDs {
    NPC_DECORATION_NONE                          = 0x00000000,
    NPC_DECORATION_BOWSER_AURA                   = 0x00000001,
    NPC_DECORATION_SWEAT                         = 0x00000002,
    NPC_DECORATION_SEEING_STARS                  = 0x00000003,
    NPC_DECORATION_WHITE_GLOW_FRONT              = 0x00000004,
    NPC_DECORATION_WHITE_GLOW_BEHIND             = 0x00000005,
    NPC_DECORATION_CHARGED                       = 0x00000006,
};

enum NpcPaletteAdjustments {
    NPC_PAL_ADJUST_NONE                             = 0,
    NPC_PAL_ADJUST_WATT_IDLE                        = 1,
    NPC_PAL_ADJUST_BLEND_PALETTES_UNIFORM_INTERVALS = 2,
    NPC_PAL_ADJUST_BLEND_PALETTES_VARYING_INTERVALS = 3,
    NPC_PAL_ADJUST_BLEND_DOUBLE_PALETTES            = 4,
};

enum SpeechFlags {
    SPEECH_FLAG_10              = 0x010,
    SPEECH_FLAG_HAS_OFFSET      = 0x100,
    SPEECH_FLAG_200             = 0x200,
    // different facing orientations for speaker and listener
    SPEECH_ORIENTATION_MASK     = 0xF,
    SPEECH_FACE_SPEAKER_ONLY    = 4,
    SPEECH_FACE_AWAY_FROM       = 3,
    SPEECH_FACE_LIKE_SPEAKER    = 2,
    SPEECH_FACE_LIKE_LISTENER   = 1,
    SPEECH_FACE_EACH_OTHER      = 0,
};

typedef enum HitResult {
    HIT_RESULT_BACKFIRE             = -1,
    HIT_RESULT_HIT                  = 0,
    HIT_RESULT_NICE                 = 1,
    HIT_RESULT_NO_DAMAGE            = 2,
    HIT_RESULT_NICE_NO_DAMAGE       = 3,
    HIT_RESULT_LANDED_ON_SPIKE      = 4,
    HIT_RESULT_LUCKY                = 5,
    HIT_RESULT_MISS                 = 6,
    HIT_RESULT_HIT_STATIC           = 7,
    HIT_RESULT_IMMUNE               = 8,
    HIT_RESULT_10                   = 10,
} HitResult;

typedef enum ActionResult {
    ACTION_RESULT_NONE              = 127,
    ACTION_RESULT_METER_BELOW_HALF  = -4, // certain mashing comamnds fail with this value
    ACTION_RESULT_METER_NOT_ENOUGH  = -2, // certain mashing comamnds fail with this value
    ACTION_RESULT_EARLY             = -1, // timing commands too early fail with this value
    ACTION_RESULT_FAIL              = 0,  // simple failure to complete action command
    ACTION_RESULT_SUCCESS           = 1,
} ActionResult;

typedef enum BlockResult {
    BLOCK_RESULT_NONE       = 127,
    BLOCK_RESULT_EARLY      = -1,
    BLOCK_RESULT_FAIL       = 0,
    BLOCK_RESULT_SUCCESS    = 1,
} BlockResult;

enum ActionRatings {
    ACTION_RATING_NICE              = 0, ///< sets nice hits = 1
    ACTION_RATING_MISS              = 1, ///< clears nice hits
    ACTION_RATING_LUCKY             = 2, ///< clears nice hits
    ACTION_RATING_SUPER             = 3, ///< sets nice hits = 2
    ACTION_RATING_NICE_NO_COMBO     = 4, ///< clears nice hits
    ACTION_RATING_NICE_SUPER_COMBO  = 5  ///< 'Nice' but becomes 'Super' if nice hits > 2
};

enum DamageSources {
    DMG_SRC_DEFAULT                 = 0,
    DMG_SRC_LEECH                   = 1,    // used by Baby Blooper, but not Fuzzy
    DMG_SRC_SPIN_SMASH              = 2,
    DMG_SRC_D_DOWN_POUND            = 3,
    DMG_SRC_D_DOWN_JUMP             = 4,
    DMG_SRC_TUTORIAL_GOOMBARIO      = 5,
    DMG_SRC_SHELL_TOSS              = 6,
    DMG_SRC_POWER_SHELL             = 7,
    DMG_SRC_DIZZY_SHELL             = 8,
    DMG_SRC_FIRE_SHELL              = 9,
    DMG_SRC_NEXT_SLAP_LEFT          = 10,
    DMG_SRC_NEXT_SLAP_RIGHT         = 11,
    DMG_SRC_LAST_SLAP_LEFT          = 12,
    DMG_SRC_LAST_SLAP_RIGHT         = 13,
    DMG_SRC_NEXT_FAN_SMACK_LEFT     = 14,
    DMG_SRC_NEXT_FAN_SMACK_RIGHT    = 15,
    DMG_SRC_LAST_FAN_SMACK_LEFT     = 16,
    DMG_SRC_LAST_FAN_SMACK_RIGHT    = 17,
    DMG_SRC_SPOOK                   = 18,
    DMG_SRC_ELECTRO_DASH            = 19,
    DMG_SRC_HURRICANE               = 20,
    DMG_SRC_FRIGHT_JAR              = 21,
    DMG_SRC_POW_BLOCK               = 22,
    DMG_SRC_TUBBA_SMASH             = 23,
    DMG_SRC_CRUSH                   = 24,
    DMG_SRC_CRUSH_PARTNER           = 25,
    DMG_SRC_INK_BLAST               = 26,
};

enum GearRank {
    GEAR_RANK_NONE   = -1,
    GEAR_RANK_NORMAL = 0,
    GEAR_RANK_SUPER  = 1,
    GEAR_RANK_ULTRA  = 2,
};

enum PartnerRank {
    PARTNER_RANK_NORMAL = 0,
    PARTNER_RANK_SUPER  = 1,
    PARTNER_RANK_ULTRA  = 2,
};

enum Iters {
    ITER_FIRST       = -1,
    ITER_NEXT        = 0,
    ITER_PREV        = 1,
    ITER_LAST        = 10,
    // return values
    ITER_HAS_MORE    = 0,
    ITER_NO_MORE     = -1,
};

enum ActorSoundIDs {
    ACTOR_SOUND_WALK                      = 0x00000000,
    ACTOR_SOUND_FLY                       = 0x00000001,
    ACTOR_SOUND_JUMP                      = 0x00000002,
    ACTOR_SOUND_HURT                      = 0x00000003,
    ACTOR_SOUND_WALK_INCREMENT            = 0x00000004,
    ACTOR_SOUND_FLY_INCREMENT             = 0x00000005,
};

enum ActorDecorationIDs {
    ACTOR_DECORATION_NONE                   = 0x00000000,
    ACTOR_DECORATION_GOLDEN_FLAMES          = 0x00000001,
    ACTOR_DECORATION_SWEAT                  = 0x00000002,
    ACTOR_DECORATION_SEEING_STARS           = 0x00000003,
    ACTOR_DECORATION_RED_FLAMES             = 0x00000004,
    ACTOR_DECORATION_GREY_SMOKE_TRAIL       = 0x00000005,
    ACTOR_DECORATION_FIRE_SMOKE_TRAIL       = 0x00000006,
    ACTOR_DECORATION_WHIRLWIND              = 0x00000007,
    ACTOR_DECORATION_STEAM_EMITTER          = 0x00000008,
    ACTOR_DECORATION_SPARKLES               = 0x00000009,
    ACTOR_DECORATION_BOWSER_AURA            = 0x0000000A,
    ACTOR_DECORATION_RADIAL_STAR_EMITTER    = 0x0000000B,
};

enum Phases {
    PHASE_EXECUTE_ACTION            = 0,
    PHASE_FIRST_STRIKE              = 1,
    PHASE_RUN_AWAY_START            = 3,
    PHASE_DEATH                     = 4,
    PHASE_CELEBRATE                 = 5,
    PHASE_USE_DEFEND                = 6,
    PHASE_RUN_AWAY_FAIL             = 7,
    PHASE_USE_LIFE_SHROOM           = 8,
    PHASE_PLAYER_BEGIN              = 10,
    PHASE_ENEMY_END                 = 11,
    PHASE_ENEMY_BEGIN               = 12,
    PHASE_PLAYER_END                = 13,
    PHASE_MERLEE_ATTACK_BONUS       = 20,
    PHASE_MERLEE_DEFENSE_BONUS      = 21,
    PHASE_MERLEE_EXP_BONUS          = 22,
    PHASE_PLAYER_HAPPY              = 30,
};

enum ActorClasses {
    ACTOR_CLASS_PLAYER      = 0x000,
    ACTOR_CLASS_PARTNER     = 0x100,
    ACTOR_CLASS_ENEMY       = 0x200,
    ACTOR_CLASS_MASK        = 0x700,
};

enum ActorIDs {
    ACTOR_SELF           = 0xFFFFFF81,
    ACTOR_PLAYER         = 0x00000000,
    ACTOR_PARTNER        = 0x00000100,
    ACTOR_ENEMY0         = 0x00000200,
    ACTOR_ENEMY1         = 0x00000201,
    ACTOR_ENEMY2         = 0x00000202,
    ACTOR_ENEMY3         = 0x00000203,
    ACTOR_ENEMY4         = 0x00000204,
    ACTOR_ENEMY5         = 0x00000205,
    ACTOR_ENEMY6         = 0x00000206,
    ACTOR_ENEMY7         = 0x00000207,
    ACTOR_ENEMY8         = 0x00000208,
    ACTOR_ENEMY9         = 0x00000209,
    ACTOR_ENEMY10        = 0x0000020A,
    ACTOR_ENEMY11        = 0x0000020B,
    ACTOR_ENEMY12        = 0x0000020C,
    ACTOR_ENEMY13        = 0x0000020D,
    ACTOR_ENEMY14        = 0x0000020E,
    ACTOR_ENEMY15        = 0x0000020F,
    ACTOR_ENEMY16        = 0x00000210,
    ACTOR_ENEMY17        = 0x00000211,
    ACTOR_ENEMY18        = 0x00000212,
    ACTOR_ENEMY19        = 0x00000213,
    ACTOR_ENEMY20        = 0x00000214,
    ACTOR_ENEMY21        = 0x00000215,
    ACTOR_ENEMY22        = 0x00000216,
    ACTOR_ENEMY23        = 0x00000217,
};

enum Elements {
    ELEMENT_END              = 0x00000000,
    ELEMENT_NORMAL           = 0x00000001,
    ELEMENT_FIRE             = 0x00000002,
    ELEMENT_WATER            = 0x00000003,
    ELEMENT_ICE              = 0x00000004,
    ELEMENT_MYSTERY          = 0x00000005,
    ELEMENT_MAGIC            = 0x00000007,
    ELEMENT_SMASH            = 0x00000008,
    ELEMENT_JUMP             = 0x00000009,
    ELEMENT_COSMIC           = 0x0000000A,
    ELEMENT_BLAST            = 0x0000000B,
    ELEMENT_SHOCK            = 0x0000000C,
    ELEMENT_QUAKE            = 0x0000000D,
    ELEMENT_THROW            = 0x0000000F,
};

enum Events {
    EVENT_HIT_COMBO                   = 0x00000009,
    EVENT_HIT                         = 0x0000000A,
    EVENT_SPIN_SMASH_HIT              = 0x0000000B,
    EVENT_FALL_TRIGGER                = 0x0000000C,
    EVENT_FLIP_TRIGGER                = 0x0000000D,
    EVENT_BURN_HIT                    = 0x0000000E,
    EVENT_15                          = 0x0000000F, // FLAME_HIT?
    EVENT_SPIN_SMASH_LAUNCH_HIT       = 0x00000011,
    EVENT_SHELL_CRACK_HIT             = 0x00000012,
    EVENT_STAR_BEAM                   = 0x00000013,
    EVENT_PEACH_BEAM                  = 0x00000014,
    EVENT_POWER_BOUNCE_HIT            = 0x00000015,
    EVENT_BLOW_AWAY                   = 0x00000016,
    EVENT_ZERO_DAMAGE                 = 0x00000017,
    EVENT_18                          = 0x00000018,
    EVENT_IMMUNE                      = 0x00000019,
    EVENT_BLOCK                       = 0x0000001A,
    EVENT_SPIKE_TAUNT                 = 0x0000001B,
    EVENT_BURN_TAUNT                  = 0x0000001C,
    EVENT_INVUNERABLE_TAUNT           = 0x0000001D,
    EVENT_1E                          = 0x0000001E,
    EVENT_AIR_LIFT_FAILED             = 0x0000001F,
    EVENT_DEATH                       = 0x00000020,
    EVENT_SPIN_SMASH_DEATH            = 0x00000021,
    EVENT_EXPLODE_TRIGGER             = 0x00000022,
    EVENT_23                          = 0x00000023,
    EVENT_BURN_DEATH                  = 0x00000024,
    EVENT_SPIN_SMASH_LAUNCH_DEATH     = 0x00000025,
    EVENT_SHOCK_DEATH                 = 0x00000026,
    EVENT_SPIKE_DEATH                 = 0x00000027,
    EVENT_POWER_BOUNCE_DEATH          = 0x00000028,
    EVENT_FIRE_DEATH                  = 0x00000029, // burn death copy?
    EVENT_SPIKE_CONTACT               = 0x0000002A,
    EVENT_BURN_CONTACT                = 0x0000002C,
    EVENT_SHOCK_HIT                   = 0x0000002F,
    EVENT_30                          = 0x00000030,
    EVENT_RECOVER_STATUS              = 0x00000031,
    EVENT_RECOVER_FROZEN              = 0x00000032,
    EVENT_33                          = 0x00000033,
    EVENT_RECOVER_FROM_KO             = 0x00000034,
    EVENT_END_FIRST_STRIKE            = 0x00000035,
    EVENT_LUCKY                       = 0x00000037,
    EVENT_BEGIN_FIRST_STRIKE          = 0x00000038,
    EVENT_SCARE_AWAY                  = 0x00000039,
    EVENT_BEGIN_AIR_LIFT              = 0x0000003A,
    EVENT_UP_AND_AWAY                 = 0x0000003D,
    EVENT_PUT_PARTNER_AWAY            = 0x0000003E,
    EVENT_RECEIVE_BUFF                = 0x0000003F,
    EVENT_LIFE_SHROOM_PROC            = 0x00000040,
    EVENT_REVIVE                      = 0x00000041,
    EVENT_66                          = 0x00000042,
};

enum HitSounds {
    HIT_SOUND_MISS             = 0,
    HIT_SOUND_BONES            = 1,
    HIT_SOUND_NORMAL           = 2,
    HIT_SOUND_FIRE             = 3,
    HIT_SOUND_ICE              = 4,
    HIT_SOUND_SHOCK            = 5,
};

enum ActorPaletteAdjustments {
    ACTOR_PAL_ADJUST_NONE             = 0,
    ACTOR_PAL_ADJUST_SLEEP            = 3,
    ACTOR_PAL_ADJUST_STATIC           = 4,
    ACTOR_PAL_ADJUST_FEAR             = 5,  // darker
    ACTOR_PAL_ADJUST_POISON           = 6,
    ACTOR_PAL_ADJUST_PARALYZE         = 7,
    ACTOR_PAL_ADJUST_BERSERK          = 8,
    ACTOR_PAL_ADJUST_WATT_IDLE        = 9,
    ACTOR_PAL_ADJUST_WATT_ATTACK      = 10,
    ACTOR_PAL_ADJUST_PLAYER_DEBUFF    = 12,
    ACTOR_PAL_ADJUST_PLAYER_POISON    = 13,
    ACTOR_PAL_ADJUST_BLEND_PALETTES_UNIFORM_INTERVALS = 14,
    ACTOR_PAL_ADJUST_BLEND_PALETTES_VARYING_INTERVALS = 15,
    ACTOR_PAL_ADJUST_BLEND_PALSETS    = 16,
};

enum GlowPaletteModes {
    GLOW_PAL_OFF    = 0,
    GLOW_PAL_ON     = 11,
};

enum ActorPartFlashState {
    FLASH_MODE_LIGHT    = 0,
    FLASH_MODE_MEDIUM    = 1,
    FLASH_MODE_HEAVY    = 2,
    FLASH_MODE_DISPOSE    = 3,
};

enum FlashPaletteModes {
    FLASH_PAL_OFF    = 0,
    FLASH_PAL_ON     = -1,
};

enum DoorSwing {
    DOOR_SWING_IN           = -1,
    DOOR_SWING_OUT          = 1,
};

enum VisibilityGroup {
    VIS_GROUP_0             = 0,
    VIS_GROUP_1             = 1,
    VIS_GROUP_2             = 2,
    VIS_GROUP_3             = 3,
    VIS_GROUP_4             = 4,
    VIS_GROUP_5             = 5,
    VIS_GROUP_6             = 6,
    VIS_GROUP_7             = 7,
};

enum ItemSpawnModes {
    ITEM_SPAWN_MODE_KEY                                          = 0x00000000,
    ITEM_SPAWN_MODE_DECORATION                                   = 0x00000001,
    ITEM_SPAWN_MODE_INVISIBLE                                    = 0x00000002,
    ITEM_SPAWN_MODE_TOSS_SPAWN_ALWAYS                            = 0x00000003,
    ITEM_SPAWN_MODE_BATTLE_REWARD                                = 0x00000004,
    ITEM_SPAWN_MODE_TOSS_NEVER_VANISH                            = 0x00000005,
    ITEM_SPAWN_MODE_TOSS                                         = 0x00000006,
    ITEM_SPAWN_MODE_TOSS_SPAWN_ONCE                              = 0x00000007,
    ITEM_SPAWN_MODE_TOSS_SPAWN_ONCE_NEVER_VANISH                 = 0x00000008,
    ITEM_SPAWN_MODE_TOSS_SPAWN_ALWAYS_NEVER_VANISH               = 0x00000009,
    ITEM_SPAWN_MODE_ITEM_BLOCK_ITEM                              = 0x0000000A,
    ITEM_SPAWN_MODE_ITEM_BLOCK_BADGE                             = 0x0000000B,
    ITEM_SPAWN_MODE_FALL_SPAWN_ALWAYS                            = 0x0000000C,
    ITEM_SPAWN_MODE_FALL_NEVER_VANISH                            = 0x0000000D,
    ITEM_SPAWN_MODE_FALL                                         = 0x0000000E,
    ITEM_SPAWN_MODE_FALL_SPAWN_ONCE                              = 0x0000000F,
    ITEM_SPAWN_MODE_FIXED_SPAWN_ALWAYS                           = 0x00000010,
    ITEM_SPAWN_MODE_FIXED_NEVER_VANISH                           = 0x00000011,
    ITEM_SPAWN_MODE_FIXED                                        = 0x00000012,
    ITEM_SPAWN_MODE_FIXED_SPAWN_ALWAYS_NEVER_VANISH              = 0x00000013,
    ITEM_SPAWN_MODE_ITEM_BLOCK_SPAWN_ALWAYS                      = 0x00000014,
    ITEM_SPAWN_MODE_ITEM_BLOCK_COIN                              = 0x00000015,
    ITEM_SPAWN_MODE_TOSS_HIGHER_NEVER_VANISH                     = 0x00000016,
    ITEM_SPAWN_MODE_TOSS_FADE1                                   = 0x00000017,
    ITEM_SPAWN_MODE_TOSS_FADE2                                   = 0x00000018,
    ITEM_SPAWN_MODE_TOSS_FADE3                                   = 0x00000019,
    ITEM_SPAWN_MODE_TOSS_SPAWN_ALWAYS_SMALL                      = 0x0000001A,
    ITEM_SPAWN_MODE_UNKNOWN_1B                                   = 0x0000001B,
    ITEM_SPAWN_AT_PLAYER                                         = 0x0000001C,
};

enum Locations {
    LOCATION_TOAD_TOWN                  = 0x01,
    LOCATION_TOAD_TOWN_TUNNELS          = 0x02,
    LOCATION_KOOPA_BROS_FORTRESS        = 0x07,
    LOCATION_MT_RUGGED                  = 0x08,
    LOCATION_DRY_DRY_OUTPOST            = 0x09,
    LOCATION_DRY_DRY_DESERT             = 0x0A,
    LOCATION_DRY_DRY_RUINS              = 0x0B,
    LOCATION_FOREVER_FOREST             = 0x0C,
    LOCATION_BOOS_MANSION               = 0x0D,
    LOCATION_TUBBAS_MANOR               = 0x0F,
    LOCATION_SHY_GUYS_TOYBOX            = 0x10,
    LOCATION_MT_LAVALAVA                = 0x12,
    LOCATION_CRYSTAL_PALACE             = 0x15,
    LOCATION_BOWSERS_CASTLE             = 0x16,
    LOCATION_TESTING                    = 0x17,
    LOCATION_NONE                       = 0x18,
    LOCATION_PEACH_CASTLE_GROUNDS       = 0x19,
    LOCATION_PEACHS_CASTLE              = 0x1A,
    LOCATION_SHOOTING_STAR_SUMMIT       = 0x1B,
    LOCATION_STAR_WAY                   = 0x1C,
    LOCATION_STAR_HAVEN                 = 0x1D,
    LOCATION_GOOMBA_VILLAGE             = 0x1E,
    LOCATION_GOOMBA_ROAD                = 0x1F,
    LOCATION_PLEASANT_PATH              = 0x20,
    LOCATION_KOOPA_VILLAGE              = 0x21,
    LOCATION_GUSTY_GULCH                = 0x22,
    LOCATION_WINDY_MILL                 = 0x23,
    LOCATION_JADE_JUNGLE                = 0x24,
    LOCATION_YOSHIS_VILLAGE             = 0x25,
    LOCATION_FLOWER_FIELDS              = 0x26,
    LOCATION_CLOUDY_CLIMB               = 0x27,
    LOCATION_SHIVER_CITY                = 0x28,
    LOCATION_SHIVER_SNOWFIELD           = 0x29,
    LOCATION_STARBORN_VALLEY            = 0x2A,
    LOCATION_SHIVER_MOUNTAIN            = 0x2B,
    LOCATION_MARIOS_HOUSE               = 0x2C,
};

typedef enum ScreenTransition {
    TRANSITION_STANDARD                 = 0,    // fade to/from black
    TRANSITION_TOY_TRAIN                = 1,    // similar to TRANSITION_STANDARD, but fade applies to whole screen
    TRANSITION_END_DEMO_SCENE_BLACK     = 2,    // rapidly fade to black
    TRANSITION_END_DEMO_SCENE_WHITE     = 3,    // slow fade to white -> rapid fade in from white
    TRANSITION_BEGIN_OR_END_GAME        = 4,    // slow fade to/from black
    TRANSITION_OUTRO_END_SCENE          = 5,    // slow fade to/from black
    TRANSITION_BEGIN_OR_END_CHAPTER     = 6,    // white fade in/out; standard transition for entering kmr_22 (Begin Chapter) or leaving kmr_23 (End of Chapter)
    TRANSITION_SLOW_FADE_TO_WHITE       = 7,    // slow fade to/from white
    TRANSITION_ENTER_WORLD              = 8,    // black Mario stencil in/out
    TRANSITION_MARIO_WHITE              = 9,    // white Mario stencil -> white fade in; used in post ch5 scene, fading to Save and Continue? screen
    TRANSITION_MARIO_BLACK              = 10,   // black Mario stencil -> black fade in; used after Goombaria finds Mario and he wakes up in the inn
    TRANSITION_AFTER_SAVE_PROMPT        = 11,   // white fade out -> white star stencil
    TRANSITION_END_PEACH_INTERLUDE      = 12,   // white star stencil -> white Mario stencil
    TRANSITION_PEACH_CAPTURED           = 13,   // black star stencil -> black fade in
    TRANSITION_GET_STAR_CARD            = 14,   // used for entering kmr_23 (Get Star Card / End Chapter)
    TRANSITION_END_CHAPTER_INTERRUPTED  = 15,   // white fade out -> white Mario stencil; used in kzn_19 for Ch5
    TRANSITION_SLOW_BLUR_MOTION         = 16,   // unused?
} ScreenTransition;

enum ScreenLayer {
    SCREEN_LAYER_FRONT              = 0,
    SCREEN_LAYER_BACK               = 1,
};

typedef enum ScreenOverlayType {
    OVERLAY_NONE                    = -1,
    OVERLAY_SCREEN_COLOR            = 0,
    OVERLAY_VIEWPORT_COLOR          = 1,
    OVERLAY_TYPE_2                  = 2,
    OVERLAY_VIEWPORT_SPOTLIGHT      = 3,
    OVERLAY_VIEWPORT_MARIO          = 4,
    OVERLAY_VIEWPORT_STAR           = 5,
    OVERLAY_SCREEN_SPOTLIGHT        = 6,
    OVERLAY_SCREEN_MARIO            = 7,
    OVERLAY_SCREEN_STAR             = 8,
    OVERLAY_TYPE_9                  = 9,
    OVERLAY_START_BATTLE            = 10,
    OVERLAY_WORLD_DARKNESS          = 11,
    OVERLAY_BLUR                    = 12,
    OVERLAY_BATTLE_DARKNESS         = 13,
    OVERLAY_INTRO_1                 = 14,
    OVERLAY_INTRO_2                 = 15,
} ScreenOverlayType;

enum DoorSounds {
    DOOR_SOUNDS_BASIC               = 0,
    DOOR_SOUNDS_METAL               = 1,
    DOOR_SOUNDS_LARGE               = 2,
    DOOR_SOUNDS_CREAKY              = 3,
    DOOR_SOUNDS_GATE                = 4,
    DOOR_SOUNDS_DOOR                = 5,
    DOOR_SOUNDS_UNUSED              = 6,
};

#include "sprite/sprite_shading_profiles.h"

enum LightSourceFlags {
    LIGHT_SOURCE_DISABLED           = 0,
    LIGHT_SOURCE_ENABLED            = 1,
    LIGHT_SOURCE_LINEAR_FALLOFF     = 4,
    LIGHT_SOURCE_QUADRATIC_FALLOFF  = 8,
};

enum ActionStates {
    ACTION_STATE_IDLE                           = 0x00000000,
    ACTION_STATE_WALK                           = 0x00000001,
    ACTION_STATE_RUN                            = 0x00000002,
    // all states above are considered locomotion states
    ACTION_STATE_JUMP                           = 0x00000003,
    ACTION_STATE_BOUNCE                         = 0x00000004,  ///< Used with Kooper
    ACTION_STATE_HOP                            = 0x00000005,  ///< Released A before apex of jump
    ACTION_STATE_LAUNCH                         = 0x00000006,  ///< Shy Guy Toybox jack-in-the-boxes
    ACTION_STATE_LANDING_ON_SWITCH              = 0x00000007,  ///< Small red/blue ! switches
    ACTION_STATE_FALLING                        = 0x00000008,
    ACTION_STATE_STEP_DOWN                      = 0x00000009,
    ACTION_STATE_LAND                           = 0x0000000A,
    ACTION_STATE_STEP_DOWN_LAND                 = 0x0000000B,
    // Following action states prohibit movement (see set_action_state())
    ACTION_STATE_TALK                           = 0x0000000C,  ///< Reading signs doesn't count
    ACTION_STATE_SPIN_JUMP                      = 0x0000000D,
    ACTION_STATE_SPIN_POUND                     = 0x0000000E,
    ACTION_STATE_TORNADO_JUMP                   = 0x0000000F,
    ACTION_STATE_TORNADO_POUND                  = 0x00000010,
    ACTION_STATE_SLIDING                        = 0x00000011,
    ACTION_STATE_HAMMER                         = 0x00000012,
    ACTION_STATE_13                             = 0x00000013,
    ACTION_STATE_PUSHING_BLOCK                  = 0x00000014,
    ACTION_STATE_HIT_FIRE                       = 0x00000015,  ///< Causes Mario to fly up and take damage. Used for fire bars.
    ACTION_STATE_KNOCKBACK                      = 0x00000016,  // some kind of knockback, does no damage
    ACTION_STATE_HIT_LAVA                       = 0x00000017,
    ACTION_STATE_STEP_UP_PEACH                  = 0x00000018,
    ACTION_STATE_USE_SNEAKY_PARASOL             = 0x00000019,
    ACTION_STATE_SPIN                           = 0x0000001A,
    ACTION_STATE_ENEMY_FIRST_STRIKE             = 0x0000001B,
    ACTION_STATE_RAISE_ARMS                     = 0x0000001C,
    ACTION_STATE_USE_SPINNING_FLOWER            = 0x0000001D,
    ACTION_STATE_USE_MUNCHLESIA                 = 0x0000001E,  ///< Set by the jan_09 squishy flower entity; throws the player in the air.
    ACTION_STATE_USE_TWEESTER                   = 0x0000001F,
    ACTION_STATE_BOUNCE_OFF_SWITCH              = 0x00000020,  ///< Small red/blue ! switches
    ACTION_STATE_RIDE                           = 0x00000021,
    ACTION_STATE_STEP_UP                        = 0x00000022,
    ACTION_STATE_23                             = 0x00000023,
    ACTION_STATE_24                             = 0x00000024,
    ACTION_STATE_INVALID_25                     = 0x00000025,
    ACTION_STATE_USE_SPRING                     = 0x00000026,
};

enum JumpSubstate {
    JUMP_SUBSTATE_0                 = 0,
    JUMP_SUBSTATE_1                 = 1,
};

enum TweesterPartnerStates {
    TWEESTER_PARTNER_INIT       = 0,
    TWEESTER_PARTNER_ATTRACT    = 1,
    TWEESTER_PARTNER_HOLD       = 2,
    TWEESTER_PARTNER_RELEASE    = 3,
};

enum LandOnSwitchSubstate {
    LANDING_ON_SWITCH_SUBSTATE_0    = 0,
    LANDING_ON_SWITCH_SUBSTATE_1    = 1,
    LANDING_ON_SWITCH_SUBSTATE_2    = 2,
};

enum PeachFlags {
    PEACH_FLAG_IS_PEACH             = 0x01,
    PEACH_FLAG_DISGUISED            = 0x02,
    PEACH_FLAG_HAS_PARASOL          = 0x04,
    PEACH_FLAG_BLOCK_NEXT_DISGUISE  = 0x08, // next attempt to copy an NPC with parasol will fail
    PEACH_FLAG_DEPRESSED            = 0x10
};

enum PeachBakingItems {
    PEACH_BAKING_NONE                   = 0,
    PEACH_BAKING_CREAM                  = 1,
    PEACH_BAKING_STRAWBERRY             = 2,
    PEACH_BAKING_BUTTER                 = 3,
    PEACH_BAKING_CLEANSER               = 4,
    PEACH_BAKING_WATER                  = 5,
    PEACH_BAKING_MILK                   = 6,
    PEACH_BAKING_FLOUR                  = 7,
    PEACH_BAKING_EGG                    = 8,
    PEACH_BAKING_COMPLETE_CAKE          = 9,
    PEACH_BAKING_CAKE_BOWL              = 10,
    PEACH_BAKING_CAKE_MIXED             = 11,
    PEACH_BAKING_CAKE_PAN               = 12,
    PEACH_BAKING_CAKE_BATTER            = 13,
    PEACH_BAKING_CAKE_BARE              = 14,
    PEACH_BAKING_SALT                   = 15,
    PEACH_BAKING_SUGAR                  = 16,
    PEACH_BAKING_CAKE_WITH_ICING        = 17,
    PEACH_BAKING_CAKE_WITH_BERRIES      = 18,
};

enum PeachDisguises {
    PEACH_DISGUISE_NONE                 = 0,
    PEACH_DISGUISE_KOOPATROL            = 1,
    PEACH_DISGUISE_HAMMER_BROS          = 2,
    PEACH_DISGUISE_CLUBBA               = 3,
};

// Requires decimals
enum NpcIDs {
    NPC_SELF            = -1,
    NPC_PLAYER          = -2,
    NPC_PARTNER         = -4,
    NPC_BTL_MERLEE      = -10,
    NPC_BTL_COMPANION   = 0, // used for Peach in intro Bowser fight and Kolorado in Lava Piranha fight
    NPC_BTL_SPIRIT      = 100,
};

enum ShadowType {
    SHADOW_VARYING_CIRCLE       = 0,
    SHADOW_VARYING_SQUARE       = 1,
    SHADOW_FIXED_CIRCLE         = 2,
    SHADOW_FIXED_SQUARE         = 3,
    SHADOW_VARYING_ALT_CIRCLE   = 4, // unused?
    SHADOW_FIXED_ALT_CIRCLE     = 5, // unused?
};

enum EntityTypes {
    ENTITY_TYPE_SHADOW                  =   0x01,
    ENTITY_TYPE_2                       =   0x02,
    ENTITY_TYPE_PADLOCK                 =   0x03,
    ENTITY_TYPE_PADLOCK_RED_FRAME       =   0x04,
    ENTITY_TYPE_PADLOCK_RED_FACE        =   0x05,
    ENTITY_TYPE_PADLOCK_BLUE_FACE       =   0x06,
    ENTITY_TYPE_BLUE_SWITCH             =   0x07,
    ENTITY_TYPE_RED_SWITCH              =   0x08,
    ENTITY_TYPE_HUGE_BLUE_SWITCH        =   0x09,
    ENTITY_TYPE_GREEN_STOMP_SWITCH      =   0x0A,
    ENTITY_TYPE_MULTI_TRIGGER_BLOCK     =   0x0B,
    ENTITY_TYPE_PUSH_BLOCK              =   0x0C,
    ENTITY_TYPE_BRICK_BLOCK             =   0x0D,
    ENTITY_TYPE_MULTI_COIN_BRICK        =   0x0E,
    ENTITY_TYPE_YELLOW_BLOCK            =   0x0F,
    ENTITY_TYPE_SINGLE_TRIGGER_BLOCK    =   0x10,
    ENTITY_TYPE_HIDDEN_YELLOW_BLOCK     =   0x11,
    ENTITY_TYPE_HIDDEN_RED_BLOCK        =   0x12,
    ENTITY_TYPE_INACTIVE_BLOCK          =   0x13,
    ENTITY_TYPE_RED_BLOCK               =   0x14,
    ENTITY_TYPE_HAMMER1_BLOCK           =   0x15,
    ENTITY_TYPE_HAMMER2_BLOCK           =   0x16,
    ENTITY_TYPE_HAMMER3_BLOCK           =   0x17,
    ENTITY_TYPE_HAMMER1_BLOCK_TINY      =   0x18,
    ENTITY_TYPE_HAMMER2_BLOCK_TINY      =   0x19,
    ENTITY_TYPE_HAMMER3_BLOCK_TINY      =   0x1A,
    ENTITY_TYPE_HEALING_BLOCK           =   0x1B,
    ENTITY_TYPE_1C                      =   0x1C,
    ENTITY_TYPE_1D                      =   0x1D,
    ENTITY_TYPE_1E                      =   0x1E,
    ENTITY_TYPE_HEALING_BLOCK_FRAME     =   0x1F,
    ENTITY_TYPE_SAVE_POINT              =   0x20,
    ENTITY_TYPE_POW_BLOCK               =   0x21,
    ENTITY_TYPE_SUPER_BLOCK             =   0x22,
    ENTITY_TYPE_ULTRA_BLOCK             =   0x23,
    ENTITY_TYPE_WOODEN_CRATE            =   0x24,
    ENTITY_TYPE_BOARDED_FLOOR           =   0x25,
    ENTITY_TYPE_BOMBABLE_ROCK           =   0x26,
    ENTITY_TYPE_BLUE_WARP_PIPE          =   0x2B,
    ENTITY_TYPE_SIMPLE_SPRING           =   0x2E,
    ENTITY_TYPE_SCRIPT_SPRING           =   0x2F,
    ENTITY_TYPE_HIDDEN_PANEL            =   0x30,
    ENTITY_TYPE_STAR_BOX_LAUNCHER       =   0x31,
    ENTITY_TYPE_CHEST                   =   0x32,
    ENTITY_TYPE_SIGNPOST                =   0x33,
    ENTITY_TYPE_RED_ARROW_SIGNS         =   0x34,
    ENTITY_TYPE_BELLBELL_PLANT          =   0x35,
    ENTITY_TYPE_TRUMPET_PLANT           =   0x36,
    ENTITY_TYPE_MUNCHLESIA              =   0x37,
    ENTITY_TYPE_CYMBAL_PLANT            =   0x38,
    ENTITY_TYPE_PINK_FLOWER             =   0x39,
    ENTITY_TYPE_SPINNING_FLOWER         =   0x3A,
    ENTITY_TYPE_3B                      =   0x3B,
    ENTITY_TYPE_TWEESTER                =   0x3C,
    ENTITY_TYPE_HEALING_BLOCK_CONTENT   =   0x3F,
    ENTITY_TYPE_SUPER_BLOCK_HIT_EFFECT  =   0x41,
    ENTITY_TYPE_ULTRA_BLOCK_HIT_EFFECT  =   0x42,
    ENTITY_TYPE_RESET_MUNCHLESIA        =   0x43,
    ENTITY_TYPE_MUNCHLESIA_GRAB         =   0x44,
    ENTITY_TYPE_MUNCHLESIA_ENVELOP      =   0x45,
    ENTITY_TYPE_MUNCHLESIA_BEGIN_CHEW   =   0x46,
    ENTITY_TYPE_MUNCHLESIA_CHEWING      =   0x47,
    ENTITY_TYPE_MUNCHLESIA_SPIT_OUT     =   0x48,
    ENTITY_TYPE_MUNCHLESIA_RESET1       =   0x49,
    ENTITY_TYPE_MUNCHLESIA_RESET2       =   0x4A
};

// Entity
enum EntityFlags {
    ENTITY_FLAG_HIDDEN                                      = 0x00000001,
    ENTITY_FLAG_DRAW_IF_CLOSE_HIDE_MODE1                    = 0x00000002,
    ENTITY_FLAG_HAS_DYNAMIC_SHADOW                          = 0x00000004,
    ENTITY_FLAG_HAS_ANIMATED_MODEL                          = 0x00000008,
    ENTITY_FLAG_SKIP_UPDATE_TRANSFORM_MATRIX                = 0x00000010,
    ENTITY_FLAG_DISABLE_COLLISION                           = 0x00000020,
    ENTITY_FLAG_CONTINUOUS_COLLISION                        = 0x00000040,
    ENTITY_FLAG_80                                          = 0x00000080,
    ENTITY_FLAG_HAS_SHADOW                                  = 0x00000100,
    ENTITY_FLAG_FIXED_SHADOW_SIZE                           = 0x00000200,
    ENTITY_FLAG_400                                         = 0x00000400,
    ENTITY_FLAG_CIRCULAR_SHADOW                             = 0x00000800,
    ENTITY_FLAG_SHOWS_INSPECT_PROMPT                        = 0x00001000,
    ENTITY_FLAG_ALWAYS_FACE_CAMERA                          = 0x00002000,
    ENTITY_FLAG_4000                                        = 0x00004000,
    ENTITY_FLAG_8000                                        = 0x00008000,
    ENTITY_FLAG_DETECTED_COLLISION                          = 0x00010000,
    ENTITY_FLAG_PARTNER_COLLISION                           = 0x00020000,
    ENTITY_FLAG_DRAW_IF_CLOSE_HIDE_MODE2                    = 0x00040000,
    ENTITY_FLAG_IGNORE_DISTANCE_CULLING                     = 0x00080000,
    ENTITY_FLAG_USED                                        = 0x00100000,
    ENTITY_FLAG_200000                                      = 0x00200000,
    ENTITY_FLAG_SHADOW_POS_DIRTY                            = 0x00400000,
    ENTITY_FLAG_DARK_SHADOW                                 = 0x00800000,
    ENTITY_FLAG_BOUND_SCRIPT_DIRTY                          = 0x01000000,
    ENTITY_FLAG_2000000                                     = 0x02000000,
    ENTITY_FLAG_PENDING_FULL_DELETE                         = 0x04000000,
    ENTITY_FLAG_8000000                                     = 0x08000000,
    ENTITY_FLAG_FADING_AWAY                                 = 0x10000000,
    ENTITY_FLAG_PENDING_INSTANCE_DELETE                     = 0x20000000,
    ENTITY_FLAG_SKIP_UPDATE                                 = 0x40000000,
    ENTITY_FLAG_CREATED                                     = 0x80000000,
};

enum EntityCollisionFlags {
    ENTITY_COLLISION_PLAYER_TOUCH_FLOOR                     = 0x00000001,
    ENTITY_COLLISION_FLAG_02                                = 0x00000002,
    ENTITY_COLLISION_PLAYER_TOUCH_CEILING                   = 0x00000004,
    ENTITY_COLLISION_PLAYER_TOUCH_WALL                      = 0x00000008,
    ENTITY_COLLISION_PLAYER_PUSHING_AGAINST                 = 0x00000010,
    ENTITY_COLLISION_FLAG_20                                = 0x00000020,
    ENTITY_COLLISION_PLAYER_HAMMER                          = 0x00000040,
    ENTITY_COLLISION_PARTNER                                = 0x00000080,
    ENTITY_COLLISION_PLAYER_LAST_FLOOR                      = 0x00000100
};

enum EntityHideMode {
    ENTITY_HIDE_MODE_0      = 0,
    ENTITY_HIDE_MODE_1      = 1,
    ENTITY_HIDE_MODE_2      = 2,
};

typedef enum PushGridOccupant {
    PUSH_GRID_EMPTY         = 0,
    PUSH_GRID_BLOCK         = 1,
    PUSH_GRID_OBSTRUCTION   = 2,
    PUSH_GRID_OUT_OF_BOUNDS = 3
} PushGridOccupant;

enum TriggerFlags {
    TRIGGER_ACTIVE              = 0x00000001,
    TRIGGER_ACTIVATED           = 0x00000002,
    TRIGGER_FORCE_ACTIVATE      = 0x00000010,
    TRIGGER_WALL_PUSH           = 0x00000040,
    TRIGGER_FLOOR_TOUCH         = 0x00000080,
    TRIGGER_WALL_PRESS_A        = 0x00000100,
    TRIGGER_FLOOR_JUMP          = 0x00000200,
    TRIGGER_WALL_TOUCH          = 0x00000400,
    TRIGGER_FLOOR_PRESS_A       = 0x00000800,
    TRIGGER_WALL_HAMMER         = 0x00001000,
    TRIGGER_FLAG_2000           = 0x00002000,
    TRIGGER_FLAG_4000           = 0x00004000,
    TRIGGER_FLAG_8000           = 0x00008000,
    TRIGGER_GAME_FLAG_SET       = 0x00010000,
    TRIGGER_AREA_FLAG_SET       = 0x00020000,
    TRIGGER_CEILING_TOUCH       = 0x00040000,
    TRIGGER_FLOOR_ABOVE         = 0x00080000,
    TRIGGER_POINT_BOMB          = 0x00100000,
    TRIGGER_SCRIPT_BOUND        = 0x01000000
};

enum ItemEntityFlags {
    ITEM_ENTITY_FLAG_CAM0                       = 0x00000001,
    ITEM_ENTITY_FLAG_CAM1                       = 0x00000002,
    ITEM_ENTITY_FLAG_CAM2                       = 0x00000004,
    ITEM_ENTITY_FLAG_CAM3                       = 0x00000008,
    ITEM_ENTITY_FLAG_10                         = 0x00000010,
    ITEM_ENTITY_FLAG_HIDDEN                     = 0x00000040, // do not render; player cant pickup
    ITEM_ENTITY_FLAG_JUST_SPAWNED               = 0x00000080,
    ITEM_ENTITY_FLAG_AUTO_COLLECT               = 0x00000100,
    ITEM_ENTITY_FLAG_NEVER_VANISH               = 0x00000200,
    ITEM_ENTITY_FLAG_SAVE_ON_TOUCH              = 0x00000400, // sets bound game flag when the item is touched
    ITEM_ENTITY_FLAG_SAVE_ON_INIT               = 0x00000800,
    ITEM_ENTITY_FLAG_1000                       = 0x00001000,
    ITEM_ENTITY_FLAG_NO_GRAVITY                 = 0x00002000,
    ITEM_ENTITY_RESIZABLE                       = 0x00004000,
    ITEM_ENTITY_FLAG_8000                       = 0x00008000,
    ITEM_ENTITY_FLAG_TOSS_LOWER                 = 0x00010000,
    ITEM_ENTITY_FLAG_ODD_SPAWN_PARITY           = 0x00020000, // every other item entity spawned will have this set
    ITEM_ENTITY_FLAG_FULLSIZE                   = 0x00040000,
    ITEM_ENTITY_FLAG_TRANSPARENT                = 0x00080000,
    ITEM_ENTITY_FLAG_INVISIBLE                  = 0x00100000, // spawned with ITEM_SPAWN_MODE_INVISIBLE
    ITEM_ENTITY_FLAG_PARTNER_COLLECTING         = 0x00200000,
    ITEM_ENTITY_FLAG_400000                     = 0x00400000,
    ITEM_ENTITY_FLAG_800000                     = 0x00800000,
    ITEM_ENTITY_FLAG_TOSS_HIGHER                = 0x01000000,
    ITEM_ENTITY_FLAG_2000000                    = 0x02000000,
    ITEM_ENTITY_FLAG_4000000                    = 0x04000000,
    ITEM_ENTITY_FLAG_HIDING                     = 0x08000000,
    ITEM_ENTITY_FLAG_NO_MOTION                  = 0x10000000,
    ITEM_ENTITY_FLAG_DONE_FALLING               = 0x20000000,
    ITEM_ENTITY_FLAG_ANGLE_RELATIVE_VELOCITY    = 0x40000000,
    ITEM_ENTITY_FLAG_SAVE_ON_RECEIPT            = 0x80000000, // sets bound game flag only when the item is placed in player inventory
};

// governs item behavior after spawning until being picked up
enum ItemPhysicsStates {
    ITEM_PHYSICS_STATE_INIT      = 0x0,
    ITEM_PHYSICS_STATE_ALIVE     = 0x1, //
    ITEM_PHYSICS_STATE_DEAD      = 0x2, // item is vanished or fallen out of the world
    ITEM_PHYSICS_STATE_TOUCH     = 0x3, // player has touched the item
    ITEM_PHYSICS_STATE_04        = 0x4,
    ITEM_PHYSICS_STATE_PICKUP    = 0xA, // item will begin pickup, physics state is invalid after this
};

// governs the process of picking up an item
enum ItemPickupStates {
    // these states comprise the typical progression for item pickup
    ITEM_PICKUP_STATE_INIT                  = 0x0,
    ITEM_PICKUP_STATE_AWAIT_VALID_STATE     = 0x1,
    ITEM_PICKUP_STATE_SHOW_GOT_ITEM         = 0x2,
    ITEM_PICKUP_STATE_HIDE_GOT_ITEM         = 0x3, // wait for window closing animations to finish
    ITEM_PICKUP_STATE_DONE                  = 0x9,
    // next three states are used for tutorials which trigger on item pickup
    ITEM_PICKUP_STATE_CHECK_TUTORIALS       = 0x4,
    ITEM_PICKUP_STATE_SHOW_TUTORIAL         = 0x5,
    ITEM_PICKUP_STATE_AWAIT_TUTORIAL        = 0x6,
    // remaining states occur when inventory is full and an item needs to be throw away
    ITEM_PICKUP_STATE_SHOW_TOO_MANY         = 0xA, // show 'cant carry more items'; open throw away popup on state exit
    ITEM_PICKUP_STATE_HIDE_TOO_MANY         = 0xB, // wait for window closing animations to finish
    ITEM_PICKUP_STATE_AWAIT_THROW_AWAY      = 0xC, // choosing
    ITEM_PICKUP_STATE_SHOW_THREW_AWAY       = 0xD, // you threw away X window
    ITEM_PICKUP_STATE_HIDE_THREW_AWAY       = 0xE, // wait for window closing animations to finish
    ITEM_PICKUP_STATE_THROW_AWAY_DONE       = 0xF,
};

enum ItemPickupFlags {
    ITEM_PICKUP_FLAG_NO_SOUND           = 0x01,
    ITEM_PICKUP_FLAG_NO_ANIMS           = 0x02,
    ITEM_PICKUP_FLAG_UNKNOWN            = 0x04,
    ITEM_PICKUP_FLAG_1_COIN             = 0x10,
    ITEM_PICKUP_FLAG_3_STAR_PIECES      = 0x20,
    ITEM_PICKUP_FLAG_UNIQUE             = 0x40,
};

// Worker
enum WorkerFlags {
    WORKER_FLAG_1                       = 0x00000001,
    WORKER_FLAG_SKIP_DRAW_UNTIL_UPDATE  = 0x00000002,
    WORKER_FLAG_FRONT_UI                = 0x00000004,
    WORKER_FLAG_BACK_UI                 = 0x00000008,
};

enum Buttons {
    BUTTON_C_RIGHT      = 0x00000001,
    BUTTON_C_LEFT       = 0x00000002,
    BUTTON_C_DOWN       = 0x00000004,
    BUTTON_C_UP         = 0x00000008,
    BUTTON_R            = 0x00000010,
    BUTTON_L            = 0x00000020,
    BUTTON_D_RIGHT      = 0x00000100,
    BUTTON_D_LEFT       = 0x00000200,
    BUTTON_D_DOWN       = 0x00000400,
    BUTTON_D_UP         = 0x00000800,
    BUTTON_START        = 0x00001000,
    BUTTON_Z            = 0x00002000,
    BUTTON_B            = 0x00004000,
    BUTTON_A            = 0x00008000,
    BUTTON_STICK_UP     = 0x00010000,
    BUTTON_STICK_DOWN   = 0x00020000,
    BUTTON_STICK_LEFT   = 0x00040000,
    BUTTON_STICK_RIGHT  = 0x00080000,
};

// only used with RemovePlayerBuffs
enum PlayerBuffs {
    PLAYER_BUFF_ALL             = 0x0FFFFFFF,
    PLAYER_BUFF_JUMP_CHARGE     = 0x00000001,
    PLAYER_BUFF_HAMMER_CHARGE   = 0x00000002,
    PLAYER_BUFF_STONE           = 0x00000008,
    PLAYER_BUFF_HUSTLE          = 0x00000010,
    PLAYER_BUFF_STATIC          = 0x00000020,
    PLAYER_BUFF_TRANSPARENT     = 0x00000040,
    PLAYER_BUFF_CLOUD_NINE      = 0x00000080,
    PLAYER_BUFF_TURBO_CHARGE    = 0x00000100,
    PLAYER_BUFF_WATER_BLOCK     = 0x00000200,
    PLAYER_BUFF_PARTNER_GLOWING = 0x00010000,
};

// Player.debuff
// Partner.debuff
enum StatusKeys {
    STATUS_END                      = 0x00000000,
    STATUS_KEY_NORMAL               = 0x00000001,
    STATUS_KEY_DEFAULT              = 0x00000002,
    STATUS_KEY_UNUSED               = 0x00000003,
    STATUS_KEY_DIZZY                = 0x00000004,
    STATUS_KEY_PARALYZE             = 0x00000005,
    STATUS_KEY_SLEEP                = 0x00000006,
    STATUS_KEY_FROZEN               = 0x00000007,
    STATUS_KEY_STOP                 = 0x00000008,
    STATUS_KEY_POISON               = 0x00000009,
    STATUS_KEY_SHRINK               = 0x0000000A,
    STATUS_KEY_STATIC               = 0x0000000B,
    STATUS_KEY_STONE                = 0x0000000C,
    STATUS_KEY_KO                   = 0x0000000D,
    STATUS_KEY_TRANSPARENT          = 0x0000000E,
    STATUS_KEY_0F                   = 0x0000000F,
    STATUS_KEY_BERSERK              = 0x00000010,
    STATUS_KEY_11                   = 0x00000011,
    STATUS_KEY_INACTIVE             = 0x00000012,
    STATUS_KEY_INACTIVE_BERSERK     = 0x00000013,
    STATUS_KEY_14                   = 0x00000014, // probably STATUS_KEY_INACTIVE_FROZEN
    STATUS_KEY_INACTIVE_SLEEP       = 0x00000015,
    STATUS_KEY_INACTIVE_WEARY       = 0x00000016,
    STATUS_KEY_17                   = 0x00000017,
    STATUS_KEY_INACTIVE_DIZZY       = 0x00000018,
    STATUS_KEY_HUSTLE               = 0x00000019,
    STATUS_KEY_DANGER               = 0x0000001A,
    STATUS_KEY_1B                   = 0x0000001B,
    STATUS_KEY_THINKING             = 0x0000001C,
    STATUS_KEY_WEARY                = 0x0000001D,
    STATUS_KEY_1E                   = 0x0000001E,
    STATUS_TURN_MOD_DEFAULT         = 0x0000001F,
    STATUS_TURN_MOD_SLEEP           = 0x00000020,
    STATUS_TURN_MOD_STATIC          = 0x00000021,
    STATUS_TURN_MOD_FROZEN          = 0x00000022,
    STATUS_TURN_MOD_UNUSED          = 0x00000023,
    STATUS_TURN_MOD_DIZZY           = 0x00000024,
    STATUS_TURN_MOD_POISON          = 0x00000025,
    STATUS_TURN_MOD_PARALYZE        = 0x00000026,
    STATUS_TURN_MOD_SHRINK          = 0x00000027,
    STATUS_TURN_MOD_STONE           = 0x00000028,
    STATUS_TURN_MOD_STOP            = 0x00000029,
};

enum StatusFlags {
    STATUS_FLAG_SLEEP           = 0x00001000,
    STATUS_FLAG_STATIC          = 0x00002000,
    STATUS_FLAG_FROZEN          = 0x00004000,
    STATUS_FLAG_UNUSED          = 0x00008000, // an unused 'disabling' status like sleep, paralyze, or dizzy
    STATUS_FLAG_PARALYZE        = 0x00010000,
    STATUS_FLAG_POISON          = 0x00020000,
    STATUS_FLAG_DIZZY           = 0x00040000,
    STATUS_FLAG_SHRINK          = 0x00080000,
    STATUS_FLAG_STONE           = 0x00100000,
    STATUS_FLAG_STOP            = 0x00200000,
    STATUS_FLAG_FEAR            = 0x00400000,
    STATUS_FLAG_KO              = 0x01000000,
    STATUS_FLAG_GLOWING         = 0x02000000,
    STATUS_FLAG_TRANSPARENT     = 0x04000000,
    STATUS_FLAG_ATTACK_BOOST    = 0x08000000,
    STATUS_FLAG_DEFENSE_BOOST   = 0x10000000,
    STATUS_FLAG_CHILL_OUT       = 0x20000000,
    STATUS_FLAG_RIGHT_ON        = 0x40000000,
    STATUS_FLAG_USE_DURATION    = 0x80000000, // indicates the status being inflicted should derive duration from BattleStatus::statusDuration
};

// general combination of flags for checking if an enemy is immobilized
#define STATUS_FLAGS_IMMOBILIZED \
     (STATUS_FLAG_SLEEP \
    | STATUS_FLAG_FROZEN \
    | STATUS_FLAG_UNUSED \
    | STATUS_FLAG_PARALYZE \
    | STATUS_FLAG_DIZZY \
    | STATUS_FLAG_STONE \
    | STATUS_FLAG_STOP)

// common set of flags used in checks throughout Dojo fights
#define STATUS_FLAGS_DOJO \
     (STATUS_FLAG_SLEEP \
    | STATUS_FLAG_PARALYZE \
    | STATUS_FLAG_DIZZY \
    | STATUS_FLAG_STONE \
    | STATUS_FLAG_STOP)

enum DamageTypes {
    DAMAGE_TYPE_FIRE                       = 0x00000002,
    DAMAGE_TYPE_WATER                      = 0x00000004,
    DAMAGE_TYPE_ICE                        = 0x00000008,
    DAMAGE_TYPE_MAGIC                      = 0x00000010,
    DAMAGE_TYPE_SHOCK                      = 0x00000020,
    DAMAGE_TYPE_SMASH                      = 0x00000040,
    DAMAGE_TYPE_JUMP                       = 0x00000080,
    DAMAGE_TYPE_COSMIC                     = 0x00000100,
    DAMAGE_TYPE_BLAST                      = 0x00000200,
    DAMAGE_TYPE_POW                        = 0x00000400,
    DAMAGE_TYPE_QUAKE                      = 0x00000800,
    DAMAGE_TYPE_FEAR                       = 0x00001000,
    DAMAGE_TYPE_DEATH                      = 0x00002000,
    DAMAGE_TYPE_4000                       = 0x00004000,
    DAMAGE_TYPE_AIR_LIFT                   = 0x00008000,
    DAMAGE_TYPE_SPINY_SURGE                = 0x00010000,
    DAMAGE_TYPE_SHELL_CRACK                = 0x00020000,
    DAMAGE_TYPE_THROW                      = 0x00040000,
    DAMAGE_TYPE_POWER_BOUNCE               = 0x00100000,
    DAMAGE_TYPE_QUAKE_HAMMER               = 0x00200000,
    DAMAGE_TYPE_REMOVE_BUFFS               = 0x00400000,
    DAMAGE_TYPE_PEACH_BEAM                 = 0x00800000,
    DAMAGE_TYPE_MULTI_BOUNCE               = 0x01000000,
    DAMAGE_TYPE_UNBLOCKABLE                = 0x02000000,
    DAMAGE_TYPE_SPIN_SMASH                 = 0x04000000,
    DAMAGE_TYPE_IGNORE_DEFENSE             = 0x08000000,
    DAMAGE_TYPE_NO_CONTACT                 = 0x10000000,
    DAMAGE_TYPE_MULTIPLE_POPUPS            = 0x20000000, // part of an attack that hits multiple opponents
    DAMAGE_TYPE_STATUS_ALWAYS_HITS         = 0x40000000,
    DAMAGE_TYPE_TRIGGER_LUCKY              = 0x80000000,
};

enum PartnerIDs {
    PARTNER_NONE                = 0x00000000,
    PARTNER_GOOMBARIO           = 0x00000001,
    PARTNER_KOOPER              = 0x00000002,
    PARTNER_BOMBETTE            = 0x00000003,
    PARTNER_PARAKARRY           = 0x00000004,
    PARTNER_GOOMPA              = 0x00000005,
    PARTNER_WATT                = 0x00000006,
    PARTNER_SUSHIE              = 0x00000007,
    PARTNER_LAKILESTER          = 0x00000008,
    PARTNER_BOW                 = 0x00000009,
    PARTNER_GOOMBARIA           = 0x0000000A,
    PARTNER_TWINK               = 0x0000000B,
};

enum EventSupressFlags {
    SUPPRESS_EVENT_SPIKY_TOP        = 0x1,
    SUPPRESS_EVENT_EXPLODE_CONTACT  = 0x2,
    SUPPRESS_EVENT_SPIKY_FRONT      = 0x4,
    SUPPRESS_EVENT_SHOCK_CONTACT    = 0x8,
    SUPPRESS_EVENT_BURN_CONTACT     = 0x10,
    SUPPRESS_EVENT_ALT_SPIKY        = 0x80,
    SUPPRESS_EVENT_FLAG_200         = 0x200,    // unused?
    SUPPRESS_EVENT_ALL              = 0xFFFF,
    SUPPRESS_EVENT_FLAG_10000       = 0x10000,  // usage is a bug?
};

// combination used for hammer-based attacks
#define SUPPRESS_EVENTS_HAMMER \
      SUPPRESS_EVENT_SPIKY_TOP \
    | SUPPRESS_EVENT_SHOCK_CONTACT \
    | SUPPRESS_EVENT_BURN_CONTACT

// combination used for mostly for kooper's attacks
#define SUPPRESS_EVENTS_KOOPER_TEST \
      SUPPRESS_EVENT_SPIKY_FRONT \
    | SUPPRESS_EVENT_BURN_CONTACT

// combination used for mostly for kooper's attacks
#define SUPPRESS_EVENTS_KOOPER_DAMAGE \
      SUPPRESS_EVENT_SPIKY_TOP \
    | SUPPRESS_EVENT_EXPLODE_CONTACT \
    | SUPPRESS_EVENT_SPIKY_FRONT \
    | SUPPRESS_EVENT_SHOCK_CONTACT \
    | SUPPRESS_EVENT_BURN_CONTACT \
    | SUPPRESS_EVENT_ALT_SPIKY

enum PartnerActions {
    PARTNER_ACTION_NONE             = 0, // generic state
    PARTNER_ACTION_USE              = 1, // generic state
    PARTNER_ACTION_KOOPER_GATHER    = 1,
    PARTNER_ACTION_KOOPER_TOSS      = 2,
    PARTNER_ACTION_BOMBETTE_LIT     = 1, // fuse lit and walking, equal to PARTNER_ACTION_USE
    PARTNER_ACTION_BOMBETTE_BLAST   = 2, // several frames during a blast, during which bombetteExplosionPos is valid
    PARTNER_ACTION_BOMBETTE_RECOVER = 3, // recovering after a blast
    PARTNER_ACTION_PARAKARRY_HOVER  = 1,
    PARTNER_ACTION_WATT_SHINE       = 1,
    PARTNER_ACTION_LAKILESTER_1     = 1,
};

enum PartnerForcedFollowModes {
    PARTNER_FORCED_FOLLOW_NONE      = 0,
    PARTNER_FORCED_FOLLOW_HOLD      = 1,
    PARTNER_FORCED_FOLLOW_ONCE      = 2,
};

/// See [`gAreas`].
enum Areas {
    AREA_KMR,
    AREA_MAC,
    AREA_TIK,
    AREA_KGR,
    AREA_KKJ,
    AREA_HOS,
    AREA_NOK,
    AREA_TRD,
    AREA_IWA,
    AREA_DRO,
    AREA_SBK,
    AREA_ISK,
    AREA_MIM,
    AREA_OBK,
    AREA_ARN,
    AREA_DGB,
    AREA_OMO,
    AREA_JAN,
    AREA_KZN,
    AREA_FLO,
    AREA_SAM,
    AREA_PRA,
    AREA_KPA,
    AREA_OSR,
    AREA_END,
    AREA_MGM,
    AREA_GV,
    AREA_TST,
};

enum NpcPalSwapState {
    NPC_PALSWAP_HOLDING_A           = 0,
    NPC_PALSWAP_FROM_A_TO_B         = 1,
    NPC_PALSWAP_HOLDING_B           = 2,
    NPC_PALSWAP_FROM_B_TO_A         = 3,
};

enum NpcFlags {
    NPC_FLAG_ENABLED                        = 0x00000001, // Does nothing aside from making npc->flags != 0
    NPC_FLAG_INVISIBLE                      = 0x00000002, // NPC will not be drawn or cause surface effects while moving
    NPC_FLAG_INACTIVE                       = 0x00000004, // NPC will not render, move, or have collisions with other NPCs. They may still be interacted with.
    NPC_FLAG_FLYING                         = 0x00000008, // Not really flying, disables snap-to-group collision check and enabled terrain height following in FlyingAI.
    NPC_FLAG_HAS_SHADOW                     = 0x00000010, // Set by default and by enable_npc_shadow
    NPC_FLAG_NO_SHADOW_RAYCAST              = 0x00000020, // Shadows are tied to NPC position instead of raycasting below the NPC
    NPC_FLAG_IGNORE_WORLD_COLLISION         = 0x00000040,
    NPC_FLAG_UPSIDE_DOWN                    = 0x00000080, // Render NPCs upside-down
    NPC_FLAG_IGNORE_CHAR_COLLISION          = 0x00000100, // Ignores collision with player and other NPCs.
    NPC_FLAG_GRAVITY                        = 0x00000200, // Enables gravity. Does nothing if NPC_FLAG_JUMPING is set.
    NPC_FLAG_DONT_UPDATE_SHADOW_Y           = 0x00000400, // When shadow raycasting is off, only X and Z update as NPC moves
    NPC_FLAG_JUMPING                        = 0x00000800,
    NPC_FLAG_GROUNDED                       = 0x00001000, // Touching the ground
    NPC_FLAG_COLLIDING_WITH_WORLD           = 0x00002000, // Colliding with world in front or to the sides of the NPC
    NPC_FLAG_COLLIDING_FORWARD_WITH_WORLD   = 0x00004000, // Colliding with world directly in front of NPC
    NPC_FLAG_IGNORE_ENTITY_COLLISION        = 0x00008000,
    NPC_FLAG_DIRTY_SHADOW                   = 0x00010000, // Set if shadow is dirty (needs to be repositioned etc.)
    NPC_FLAG_REFLECT_WALL                   = 0x00020000, // Mirror rendering across z=0
    NPC_FLAG_IGNORE_CAMERA_FOR_YAW          = 0x00040000, // Do not adjust renderYaw to face the camera
    NPC_FLAG_REFLECT_FLOOR                  = 0x00080000, // Mirror rendering across y=0
    NPC_FLAG_MOTION_BLUR                    = 0x00100000, // Gives motion blur effect as NPC moves. Set by enable_npc_blur
    NPC_FLAG_FLIP_INSTANTLY                 = 0x00200000, // Flip instantly when changing facing direction
    NPC_FLAG_TOUCHES_GROUND                 = 0x00400000, // Can cause effects to play when touching special surface types
    NPC_FLAG_HIDING                         = 0x00800000,
    NPC_FLAG_HAS_NO_SPRITE                  = 0x01000000,
    NPC_FLAG_COLLIDING_WITH_NPC             = 0x02000000,
    NPC_FLAG_PARTNER                        = 0x04000000,
    NPC_FLAG_WORLD_COLLISION_DIRTY          = 0x08000000,
    NPC_FLAG_USE_INSPECT_ICON               = 0x10000000, // Approaching this NPC will cause a red ! to appear.
    NPC_FLAG_RAYCAST_TO_INTERACT            = 0x20000000, // Intended to require a line of sight raycast before conversations can be triggered. Seems bugged.
    NPC_FLAG_USES_PLAYER_AUX_SPRITE         = 0x40000000, // This NPC uses the player sprite system, rather than NPC. Used for Peach as an NPC.
    NPC_FLAG_SUSPENDED                      = 0x80000000,
};

enum PlayerStatusFlags {
    PS_FLAG_AIRBORNE                         = 0x0000000E,
    PS_FLAG_HAS_REFLECTION                   = 0x00000001,
    PS_FLAG_JUMPING                          = 0x00000002,
    PS_FLAG_FALLING                          = 0x00000004,
    PS_FLAG_FLYING                           = 0x00000008,
    PS_FLAG_SLIDING                          = 0x00000010,
    /* Paused either via the start menu, or through another menu that causes a pause (like the item menu) */
    PS_FLAG_PAUSED                           = 0x00000020,
    PS_FLAG_NO_CHANGE_PARTNER                = 0x00000040,
    PS_FLAG_NO_PARTNER_USAGE                 = 0x00000080,
    /* Prevents opening menus that would require a game-time pause (start menu, item menu, etc) */
    PS_FLAG_PAUSE_DISABLED                   = 0x00000100,
    /* Doing either a spin jump or a tornado jump */
    PS_FLAG_SPECIAL_JUMP                     = 0x00000200,
    /* Landing from either a spin jump or a tornado jump */
    PS_FLAG_SPECIAL_LAND                     = 0x00000400,
    /* Burning from touching a fire hazard of some kind */
    PS_FLAG_HIT_FIRE                         = 0x00000800,
    PS_FLAG_NO_STATIC_COLLISION              = 0x00001000,
    PS_FLAG_INPUT_DISABLED                   = 0x00002000,
    /* Indicates that Mario's lateral movement is currently commandeered by a cutscene or script */
    PS_FLAG_CUTSCENE_MOVEMENT                = 0x00004000,
    /* Either outta sight with Bow, or temporarily damage boosted - makes Mario ignore fire bars */
    PS_FLAG_HAZARD_INVINCIBILITY             = 0x00008000,
    /* Spinning either through pressing Z or the tornado jump - causes a ghost trail to render */
    PS_FLAG_SPINNING                         = 0x00020000,
    /* Slows Mario's physics and animations to half speed - responsible for the dramatic slowdown when starting an encounter by jumping on an enemy.
       Also stops Mario from successfully completing a hammer. */
    PS_FLAG_ENTERING_BATTLE                  = 0x00040000,
    /* Occurs after hitting a heart block - temporarily prevents encounters from starting */
    PS_FLAG_ARMS_RAISED                      = 0x00080000,
    /* Stops Mario's sprite yaw from being adjusted, usually so a cutscene can do it instead. */
    PS_FLAG_ROTATION_LOCKED                  = 0x00100000,
    /* Forces Mario's sprite to either face exactly left or right, without transitioning. */
    PS_FLAG_NO_FLIPPING                      = 0x00200000,
    /* Prevents Mario from moving laterally */
    PS_FLAG_MOVEMENT_LOCKED                  = 0x00400000, //TODO misnamed
    /* Stops Mario from air steering or using a special jump during a scripted fall */
    PS_FLAG_SCRIPTED_FALL                    = 0x00800000,
    /* Not fully sure about this one, but appears to mark the frame that the check for what to hammer occurs */
    PS_FLAG_HAMMER_CHECK                     = 0x01000000,
    PS_FLAG_HAS_CONVERSATION_NPC             = 0x02000000,
    PS_FLAG_CAMERA_DOESNT_FOLLOW             = 0x04000000,
    /* Mario just interacted with something (usually cleared on the same frame) */
    PS_FLAG_INTERACTED                       = 0x08000000,
    /* Makes Mario face forwards, used when talking to NPCs, or when on Lakilester */
    PS_FLAG_FACE_FORWARD                     = 0x10000000,
    /* Freezes physics and animations - is usually reset at the start of a frame so often does nothing */
    PS_FLAG_TIME_STOPPED                     = 0x20000000,
    /* Indicates that Mario needs his sprite redrawn */
    PS_FLAG_SPRITE_REDRAW                    = 0x40000000,
    PS_FLAG_ACTION_STATE_CHANGED             = 0x80000000,
};

/// See [`PlayerStatus::animFlags`].
enum PlayerStatusAnimFlags {
    /* Whether Mario is in the process of using Watt (but isn't necessarily holding them yet) */
    PA_FLAG_USING_WATT                       = 0x00000001,
    /* Whether Watt is actually in Mario's hands at the moment */
    PA_FLAG_WATT_IN_HANDS                    = 0x00000002,
    PA_FLAG_INTERRUPT_USE_PARTNER            = 0x00000004, ///< forces actions with bow, parakarry, watt, and lakilester to end (sushie not tested)
    PA_FLAG_FORCE_USE_PARTNER                = 0x00000008, ///< triggers partner use when set
    PA_FLAG_INTERACT_PROMPT_AVAILABLE        = 0x00000010, ///< ! prompt
    PA_FLAG_SPEECH_PROMPT_AVAILABLE          = 0x00000020, ///< (...) prompt
    PA_FLAG_PULSE_STONE_VISIBLE              = 0x00000040, ///< The pulse stone icon is being shown
    PA_FLAG_USING_PULSE_STONE                = 0x00000080,
    PA_FLAG_ISPY_VISIBLE                     = 0x00000100, ///< The I Spy icon is being shown
    PA_FLAG_RAISED_ARMS                      = 0x00000200, ///< Sets action state to ACTION_STATE_RAISE_ARMS on idle
    PA_FLAG_SHIVERING                        = 0x00000400,
    PA_FLAG_OPENED_HIDDEN_PANEL              = 0x00000800,
    PA_FLAG_USING_PEACH_PHYSICS              = 0x00001000,
    PA_FLAG_INVISIBLE                        = 0x00002000,
    PA_FLAG_8BIT_MARIO                       = 0x00004000,
    PA_FLAG_NPC_COLLIDED                     = 0x00008000,
    PA_FLAG_SPINNING                         = 0x00010000,
    /* Began an encounter by spinning into an enemy with the Dizzy Attack badge on */
    PA_FLAG_DIZZY_ATTACK_ENCOUNTER           = 0x00020000,
    PA_FLAG_INTERRUPT_SPIN                   = 0x00040000,
    /* When Mario is in a transition to a new map, either through a loading zone or pipe */
    PA_FLAG_CHANGING_MAP                     = 0x00100000,
    /* Occurs after PA_FLAG_FORCE_USE_PARTNER. Some partners - namely Bow and Lakilester, unset this immediately.
       Not sure why - seems like it might contribute to being unable to *stop* using your partner during a cutscene. */
    PA_FLAG_PARTNER_USAGE_FORCED             = 0x00200000,
    PA_FLAG_RIDING_PARTNER                   = 0x00400000,
    PA_FLAG_ABORT_PUSHING_BLOCK              = 0x00800000,
    /* Changes how Mario is rendered. Seems to be intended to make Mario's depth render properly when using Bow behind a switch (two translucent objects on top of eachother), but it doesn't actually work. */
    PA_FLAG_MAP_HAS_SWITCH                   = 0x01000000,
    /* Usually, if Mario falls for too long, he eventually gets reset to his last safe position. This prevents that. Used by some scripts. */
    PA_FLAG_NO_OOB_RESPAWN                   = 0x10000000,
    /* This allows dismounting from Lakilester, even if in a precarious situation (like over spikes, lava, or water). */
    PA_FLAG_DISMOUNTING_ALLOWED              = 0x20000000,
    /* This flag is set when partner usage was interrupted by a script, and it prevents menu sounds (like the error sound) from playing for script-initiated player actions */
    PA_FLAG_FORCED_PARTNER_ABILITY_END       = 0x40000000,
    /* This one's really weird. Seems to have something to do with the direction Mario is facing, but I'm not sure what it's actually supposed to be achieving. */
    PA_FLAG_80000000                         = 0x80000000,
};

enum PopupType {
    POPUP_MENU_USE_ITEM             = 0x0,
    POPUP_MENU_SWITCH_PARTNER       = 0x1,
    POPUP_MENU_THROW_AWAY_ITEM      = 0x2,
    POPUP_MENU_TRADE_FOR_BADGE      = 0x3,
    POPUP_MENU_UPGRADE_PARTNER      = 0x4,
    POPUP_MENU_SELL_ITEM            = 0x5,
    POPUP_MENU_CHECK_ITEM           = 0x6,
    POPUP_MENU_CLAIM_ITEM           = 0x7,
    POPUP_MENU_READ_LETTER          = 0x8,
    POPUP_MENU_TAKE_FROM_CHEST      = 0x9,
    POPUP_MENU_READ_DIARY_PAGE      = 0xA,
    POPUP_MENU_READ_POSTCARD        = 0xB,
    POPUP_MENU_USEKEY               = 0xC,
    POPUP_MENU_POST_OFFICE          = 0xD,
    POPUP_MENU_DOUBLE_DIP           = 100,
    POPUP_MENU_TRIPLE_DIP           = 200,
};

enum PopupState {
    POPUP_STATE_INIT                        = 0,
    POPUP_STATE_CHOOSING                    = 1,
    POPUP_STATE_10                          = 10,
    POPUP_STATE_11                          = 11,
    POPUP_STATE_20                          = 20,
    POPUP_STATE_ALREADY_HAVE_PARTNER_BEGIN  = 30,
    POPUP_STATE_ALREADY_HAVE_PARTNER_SHOW   = 31,
    POPUP_STATE_ALREADY_HAVE_PARTNER_AWAIT  = 32,
    POPUP_STATE_CANCEL_DIP                  = 100,
    POPUP_STATE_CANCEL_DIP_AWAIT_CHOICE     = 101,
    POPUP_STATE_CANCEL_DIP_ACCEPT           = 102,
    POPUP_STATE_CANCEL_DIP_DECLINE          = 103,
    POPUP_STATE_104                         = 104,
    POPUP_STATE_105                         = 105,
    POPUP_STATE_CHOSE_WORLD                 = -1,
    POPUP_STATE_CHOSE_BATTLE                = -2,
    POPUP_STATE_MINUS_3                     = -3,
    POPUP_STATE_MINUS_4                     = -4,
    POPUP_STATE_MINUS_5                     = -5,
    POPUP_STATE_CHOSE_SWAP                  = -6,
    POPUP_STATE_MINUS_7                     = -7,
    POPUP_STATE_MINUS_8                     = -8,
};

enum PopupResult {
    POPUP_RESULT_INVALID    = -1,
    POPUP_RESULT_SWAP_MENU  = -2,
    POPUP_RESULT_CHOOSING   = 0,
    POPUP_RESULT_CANCEL     = 255,
};

enum WindowPriority {
    WINDOW_PRIORITY_0               = 0,
    WINDOW_PRIORITY_1               = 1,
    WINDOW_PRIORITY_10              = 10,
    WINDOW_PRIORITY_19              = 19,
    WINDOW_PRIORITY_20              = 20,
    WINDOW_PRIORITY_21              = 21,
    WINDOW_PRIORITY_64              = 64,
};

enum RenderModeIndex {
    // RM1 modes
    RENDER_MODE_IDX_00 = 0x00,
    RENDER_MODE_IDX_01 = 0x01,
    RENDER_MODE_IDX_02 = 0x02,
    RENDER_MODE_IDX_03 = 0x03,
    RENDER_MODE_IDX_04 = 0x04,
    RENDER_MODE_IDX_05 = 0x05,
    RENDER_MODE_IDX_06 = 0x06,
    RENDER_MODE_IDX_07 = 0x07,
    RENDER_MODE_IDX_08 = 0x08,
    RENDER_MODE_IDX_09 = 0x09,
    RENDER_MODE_IDX_0A = 0x0A,
    RENDER_MODE_IDX_0B = 0x0B,
    RENDER_MODE_IDX_0C = 0x0C,
    RENDER_MODE_IDX_0D = 0x0D,
    RENDER_MODE_IDX_0E = 0x0E,
    RENDER_MODE_IDX_0F = 0x0F,
    // RM2 modes
    RENDER_MODE_IDX_10 = 0x10,
    RENDER_MODE_IDX_11 = 0x11,
    RENDER_MODE_IDX_12 = 0x12,
    RENDER_MODE_IDX_13 = 0x13,
    RENDER_MODE_IDX_14 = 0x14,
    RENDER_MODE_IDX_15 = 0x15,
    RENDER_MODE_IDX_16 = 0x16,
    RENDER_MODE_IDX_17 = 0x17,
    RENDER_MODE_IDX_18 = 0x18,
    RENDER_MODE_IDX_19 = 0x19,
    RENDER_MODE_IDX_1A = 0x1A,
    RENDER_MODE_IDX_1B = 0x1B,
    RENDER_MODE_IDX_1C = 0x1C,
    RENDER_MODE_IDX_1D = 0x1D,
    RENDER_MODE_IDX_1E = 0x1E,
    // RM3 modes
    RENDER_MODE_IDX_1F = 0x1F,
    RENDER_MODE_IDX_20 = 0x20,
    RENDER_MODE_IDX_21 = 0x21,
    RENDER_MODE_IDX_22 = 0x22,
    RENDER_MODE_IDX_23 = 0x23,
    RENDER_MODE_IDX_24 = 0x24,
    RENDER_MODE_IDX_25 = 0x25,
    RENDER_MODE_IDX_26 = 0x26,
    RENDER_MODE_IDX_27 = 0x27,
    RENDER_MODE_IDX_28 = 0x28,
    RENDER_MODE_IDX_29 = 0x29,
    RENDER_MODE_IDX_2A = 0x2A,
    RENDER_MODE_IDX_2B = 0x2B,
    RENDER_MODE_IDX_2C = 0x2C,
    RENDER_MODE_IDX_2D = 0x2D,
    RENDER_MODE_IDX_2E = 0x2E,
    RENDER_MODE_IDX_2F = 0x2F,
    RENDER_MODE_IDX_30 = 0x30,
    RENDER_MODE_IDX_31 = 0x31,
    RENDER_MODE_IDX_32 = 0x32,
    RENDER_MODE_IDX_33 = 0x33,
    RENDER_MODE_IDX_34 = 0x34,
    RENDER_MODE_IDX_35 = 0x35,
    RENDER_MODE_IDX_36 = 0x36,
    // cloud render modes
    RENDER_MODE_IDX_37 = 0x37,
    RENDER_MODE_IDX_38 = 0x38,
    RENDER_MODE_IDX_39 = 0x39,
    RENDER_MODE_IDX_3A = 0x3A,
    RENDER_MODE_IDX_3B = 0x3B,
    RENDER_MODE_IDX_3C = 0x3C,
};

// predefined configurations for RDP geometry and render modes
// though these are called "render modes", they do not strictly correspond to the RDP render modes (as supplied to gDPSetRenderMode)
enum RenderMode {
    // opaque render modes
    RENDER_MODE_SURF_SOLID_AA_ZB_LAYER0          = 0x00,
    RENDER_MODE_SURFACE_OPA                      = 0x01,
    RENDER_MODE_02_UNUSED                        = 0x02,
    RENDER_MODE_SURFACE_OPA_NO_AA                = 0x03,
    RENDER_MODE_SURFACE_OPA_NO_ZB                = 0x04,
    RENDER_MODE_DECAL_OPA                        = 0x05,
    RENDER_MODE_06_UNUSED                        = 0x06,
    RENDER_MODE_DECAL_OPA_NO_AA                  = 0x07,
    RENDER_MODE_08_UNUSED                        = 0x08,
    RENDER_MODE_INTERSECTING_OPA                 = 0x09,
    RENDER_MODE_0A_UNUSED                        = 0x0A,
    RENDER_MODE_0B_UNUSED                        = 0x0B,
    RENDER_MODE_0C_UNUSED                        = 0x0C,
    RENDER_MODE_ALPHATEST                        = 0x0D,
    RENDER_MODE_0E_UNUSED                        = 0x0E,
    RENDER_MODE_ALPHATEST_ONESIDED               = 0x0F,
    RENDER_MODE_ALPHATEST_NO_ZB                  = 0x10,
    RENDER_MODES_LAST_OPAQUE                     = RENDER_MODE_ALPHATEST_NO_ZB,
    // translucent render modes
    RENDER_MODE_SURFACE_XLU_LAYER1               = 0x11,
    RENDER_MODE_12_UNUSED                        = 0x12,
    RENDER_MODE_SURFACE_XLU_NO_AA                = 0x13,
    RENDER_MODE_SURFACE_XLU_NO_ZB                = 0x14,
    RENDER_MODE_SURFACE_XLU_ZB_ZUPD              = 0x15,
    RENDER_MODE_SURFACE_XLU_LAYER2               = 0x16,
    RENDER_MODE_17_UNUSED                        = 0x17,
    RENDER_MODE_18_UNUSED                        = 0x18,
    RENDER_MODE_19_UNUSED                        = 0x19,
    RENDER_MODE_DECAL_XLU                        = 0x1A,
    RENDER_MODE_1B_UNUSED                        = 0x1B,
    RENDER_MODE_DECAL_XLU_NO_AA                  = 0x1C,
    RENDER_MODE_1D_UNUSED                        = 0x1D,
    RENDER_MODE_DECAL_XLU_AHEAD                  = 0x1E, // special case RENDER_MODE_DECAL_XLU for rendering in front of others
    RENDER_MODE_1F_UNUSED                        = 0x1F,
    RENDER_MODE_SHADOW                           = 0x20,
    RENDER_MODE_21_UNUSED                        = 0x21,
    RENDER_MODE_SURFACE_XLU_LAYER3               = 0x22,
    RENDER_MODE_23_UNUSED                        = 0x23,
    RENDER_MODE_24_UNUSED                        = 0x24,
    RENDER_MODE_25_UNUSED                        = 0x25,
    RENDER_MODE_INTERSECTING_XLU                 = 0x26,
    RENDER_MODE_27_UNUSED                        = 0x27,
    // unusual render modes
    RENDER_MODE_PASS_THROUGH                     = 0x28, // no render mode is set, only geometry modes are initialized
    RENDER_MODE_SURFACE_XLU_AA_ZB_ZUPD           = 0x29,
    RENDER_MODE_SURFACE_OPA_NO_ZB_BEHIND         = 0x2A,
    RENDER_MODE_ALPHATEST_NO_ZB_BEHIND           = 0x2B,
    RENDER_MODE_SURFACE_XLU_NO_ZB_BEHIND         = 0x2C,
    RENDER_MODE_CLOUD_NO_ZCMP                    = 0x2D,
    RENDER_MODE_CLOUD                            = 0x2E,
    RENDER_MODE_CLOUD_NO_ZB                      = 0x2F,
};

enum RenderTaskFlags {
    RENDER_TASK_FLAG_ENABLED        = 0x01,
    RENDER_TASK_FLAG_REFLECT_FLOOR  = 0x02,
    RENDER_TASK_FLAG_20             = 0x20,
};

// same as ActorPartFlags, kept separate for clarity
enum ActorFlags {
    ACTOR_FLAG_INVISIBLE                    = 0x00000001, ///< Actor is not rendered.
    ACTOR_FLAG_NO_SHADOW                    = 0x00000004, ///< Hide shadow.
    ACTOR_FLAG_LOW_PRIORITY_TARGET          = 0x00000010, // only usable with ACTOR_FLAG_TARGET_ONLY, treats the target's sort position as off-stage to the right
    ACTOR_FLAG_MINOR_TARGET                 = 0x00000040, // ignored by moves using TARGET_FLAG_PRIMARY_ONLY (unused)
    ACTOR_FLAG_NO_TATTLE                    = 0x00000080,
    ACTOR_FLAG_FLYING                       = 0x00000200, ///< Quake Hammer can't hit.
    ACTOR_FLAG_FLIPPED                      = 0x00000400, ///< Actor has been flipped over.
    ACTOR_FLAG_UPSIDE_DOWN                  = 0x00000800, ///< HP bar offset below actor (e.g. Swooper when upside-down).
    ACTOR_FLAG_TYPE_CHANGED                 = 0x00001000, ///< Indicates actors type has changed, triggers recheck for if HP bar should be shown based on tattle status.
    ACTOR_FLAG_DAMAGE_IMMUNE                = 0x00002000, // prevents hits from items, chill out, and up & away
    ACTOR_FLAG_TARGET_ONLY                  = 0x00004000, ///< Battle ends even if undefeated. No turn.
    ACTOR_FLAG_HALF_HEIGHT                  = 0x00008000,
    ACTOR_FLAG_SKIP_TURN                    = 0x00010000,
    ACTOR_FLAG_NO_HEALTH_BAR                = 0x00040000, // Health bar is not shown for this actor type
    ACTOR_FLAG_HEALTH_BAR_HIDDEN            = 0x00080000, // Health bar is temporarily hidden
    ACTOR_FLAG_NO_ATTACK                    = 0x00200000, ///< Skip attack turn.
    ACTOR_FLAG_NO_DMG_APPLY                 = 0x00400000, ///< Damage is not applied to actor HP.
    ACTOR_FLAG_NO_DMG_POPUP                 = 0x02000000, ///< Hide damage popup.
    ACTOR_FLAG_USING_IDLE_ANIM              = 0x04000000,
    ACTOR_FLAG_SHOW_STATUS_ICONS            = 0x08000000,
    ACTOR_FLAG_BLUR_ENABLED                 = 0x10000000,
    ACTOR_FLAG_NO_INACTIVE_ANIM             = 0x20000000, // only used for player Actor
};

// same as ActorFlags, kept separate for clarity
enum ActorPartFlags {
    ACTOR_PART_FLAG_INVISIBLE               = 0x00000001,
    ACTOR_PART_FLAG_NO_DECORATIONS          = 0x00000002,
    ACTOR_PART_FLAG_NO_SHADOW               = 0x00000004,
    ACTOR_PART_FLAG_DEFAULT_TARGET          = 0x00000008, // Part will be the default selected target for player.
    ACTOR_PART_FLAG_IGNORE_BELOW_CHECK      = 0x00000020, // ignore below check while targeting
    ACTOR_PART_FLAG_MINOR_TARGET            = 0x00000040, // ignored by moves using TARGET_FLAG_PRIMARY_ONLY (unused)
    ACTOR_PART_FLAG_NO_TATTLE               = 0x00000080,
    ACTOR_PART_FLAG_TRANSPARENT             = 0x00000100,
    ACTOR_PART_FLAG_DAMAGE_IMMUNE           = 0x00002000, ///< electrified Plays extra hurt SFX?
    ACTOR_PART_FLAG_TARGET_ONLY             = 0x00004000, // Has no effect on ActorPart. Use the ACTOR_FLAG on Actor instead.
    ACTOR_PART_FLAG_NO_TARGET               = 0x00020000, ///< Cannot be targeted.
    ACTOR_PART_FLAG_USE_ABSOLUTE_POSITION   = 0x00100000,
    ACTOR_PART_FLAG_PRIMARY_TARGET          = 0x00800000, // Multi-target attacks will target this part of an Actor with multiple parts.
    ACTOR_PART_FLAG_HAS_PAL_EFFECT          = 0x01000000,
    ACTOR_PART_FLAG_NO_STATUS_ANIMS         = 0x20000000, // Do not update idle animation based on Actor status
    ACTOR_PART_FLAG_SKIP_SHOCK_EFFECT       = 0x40000000, // Do not apply a shock effect to this ActorPart when its Actor is shocked
    ACTOR_PART_FLAG_SKIP_MOVEMENT_ALLOC     = 0x80000000, // Do not allocate ActorPartMovement for this ActorPart
};

enum ActorEventFlags {
    ACTOR_EVENT_FLAGS_NONE                  = 0x00000000,
    ACTOR_EVENT_FLAG_FIREY                  = 0x00000002, ///< Player takes burn damage upon contact.
    ACTOR_EVENT_FLAG_ICY                    = 0x00000008, ///< No known effect, but is used.
    ACTOR_EVENT_FLAG_SPIKY_TOP              = 0x00000010, ///< Player takes spike damage from jump attacks.
    ACTOR_EVENT_FLAG_ILLUSORY               = 0x00000020, ///< Player attacks pass through and miss.
    ACTOR_EVENT_FLAG_ELECTRIFIED            = 0x00000080, ///< Player takes shock damage upon contact.
    ACTOR_EVENT_FLAG_MONSTAR                = 0x00000100, ///< Set by Monstar, but has no effect
    ACTOR_EVENT_FLAG_EXPLODE_ON_IGNITION    = 0x00000200, ///< Blast and fire attacks trigger an explosion.
    ACTOR_EVENT_FLAG_FIRE_EXPLODE           = 0x00000400, ///< Fire attacks trigger an explosion, used only by bullet/bombshell bills.
    ACTOR_EVENT_FLAG_BURIED                 = 0x00000800, ///< Actor can only by hit by quake-element attacks.
    ACTOR_EVENT_FLAG_FLIPABLE               = 0x00001000, ///< Actor can be flipped; triggered by jump and quake attacks.
    ACTOR_EVENT_FLAG_EXTREME_DEFENSE        = 0x00002000, ///< Actor has 127 extra defense during damage calculation, unaffected by IGNORE_DEFENSE.
    ACTOR_EVENT_FLAG_GROUNDABLE             = 0x00004000, ///< Actor can be knocked down from flight; triggered by jump attacks.
    ACTOR_EVENT_FLAG_EXPLODE_ON_CONTACT     = 0x00008000, ///< Attacks that contact will trigger an explosion.
    ACTOR_EVENT_FLAG_SPIKY_FRONT            = 0x00010000, ///< Player takes spike damage from hammer attacks.
    ACTOR_EVENT_FLAG_ENCHANTED              = 0x00040000, ///< Actor glows and listens for the Star Beam event.
    ACTOR_EVENT_FLAG_STAR_ROD_ENCHANTED     = 0x00080000, ///< Actor glows and listens for Star Beam and Peach Beam events.
    ACTOR_EVENT_FLAG_POWER_BOUNCE           = 0x00100000, ///< Actor listens for Power Bounce events.
    ACTOR_EVENT_FLAG_ALT_SPIKY              = 0x00200000, ///< Additional spiky quality associated with Pokeys and Spinies
    ACTOR_EVENT_FLAG_ATTACK_CHARGED         = 0x00400000, ///< Actor has charged an attack that can be removed with Star Beam.
    ACTOR_EVENT_FLAG_RIDING_BROOMSTICK      = 0x00800000, ///< Actor is on Magikoopa Broomstick, effect seems to be redundant.
};

enum PartnerWishAnims {
    PARTNER_WISH_ANIM_WALK          = 0,
    PARTNER_WISH_ANIM_PRAY          = 1,
    PARTNER_WISH_ANIM_UNUSED        = 2,
    PARTNER_WISH_ANIM_RETURN        = 3,
    PARTNER_WISH_ANIM_IDLE          = 4,
};

enum PartnerAnimIndices {
    PARTNER_ANIM_INDEX_STILL      = 0x0,
    PARTNER_ANIM_INDEX_WALK       = 0x1,
    PARTNER_ANIM_INDEX_JUMP       = 0x2,
    PARTNER_ANIM_INDEX_FALL       = 0x3,
    PARTNER_ANIM_INDEX_FLY        = 0x4,
    PARTNER_ANIM_INDEX_IDLE       = 0x5,
    PARTNER_ANIM_INDEX_RUN        = 0x6,
    PARTNER_ANIM_INDEX_TALK       = 0x7,
    PARTNER_ANIM_INDEX_HURT       = 0x8,
};

enum AnyPartnerAnims {
    PARTNER_ANIM_STILL      = 0x101,
    PARTNER_ANIM_WALK       = 0x102,
    PARTNER_ANIM_JUMP       = 0x103,
    PARTNER_ANIM_FALL       = 0x104,
    PARTNER_ANIM_FLY        = 0x105,
    PARTNER_ANIM_IDLE       = 0x106,
    PARTNER_ANIM_RUN        = 0x107,
    PARTNER_ANIM_TALK       = 0x108,
    PARTNER_ANIM_HURT       = 0x109,
};

enum EnemyAnimIndices {
    ENEMY_ANIM_INDEX_IDLE         = 0,
    ENEMY_ANIM_INDEX_WALK         = 1,
    ENEMY_ANIM_INDEX_RUN          = 2,
    ENEMY_ANIM_INDEX_CHASE        = 3,
    ENEMY_ANIM_INDEX_JUMP         = 4,
    ENEMY_ANIM_INDEX_UNUSED       = 5,
    ENEMY_ANIM_INDEX_DEATH        = 6,
    ENEMY_ANIM_INDEX_HIT          = 7,
};

enum AnyEnemyAnims {
    ENEMY_ANIM_IDLE         = 0x201,
    ENEMY_ANIM_WALK         = 0x202,
    ENEMY_ANIM_RUN          = 0x203,
    ENEMY_ANIM_CHASE        = 0x204,
    ENEMY_ANIM_JUMP         = 0x205,
    ENEMY_ANIM_5            = 0x206,
    ENEMY_ANIM_DEATH        = 0x207,
    ENEMY_ANIM_HIT          = 0x208,
    ENEMY_ANIM_8            = 0x209,
    ENEMY_ANIM_9            = 0x20A,
    ENEMY_ANIM_A            = 0x20B,
    ENEMY_ANIM_B            = 0x20C,
    ENEMY_ANIM_C            = 0x20D,
    ENEMY_ANIM_D            = 0x20E,
    ENEMY_ANIM_E            = 0x20F,
    ENEMY_ANIM_F            = 0x210,
};

enum FirstStrikeType {
    FIRST_STRIKE_NONE           = 0,
    FIRST_STRIKE_PLAYER         = 1,
    FIRST_STRIKE_ENEMY          = 2,
};

enum TimeFreezeMode {
    TIME_FREEZE_NONE            = 0,
    TIME_FREEZE_PARTIAL         = 1,
    TIME_FREEZE_FULL            = 2,
    TIME_FREEZE_POPUP_MENU      = 3,
    TIME_FREEZE_EXIT            = 4,
};

enum ActionCommand {
    ACTION_COMMAND_NONE                      = 0x00000000,
    ACTION_COMMAND_JUMP                      = 0x00000001,
    ACTION_COMMAND_SMASH                     = 0x00000002,
    ACTION_COMMAND_FLEE                      = 0x00000003,
    ACTION_COMMAND_BREAK_FREE                = 0x00000004,
    ACTION_COMMAND_WHIRLWIND                 = 0x00000005,
    ACTION_COMMAND_STOP_LEECH                = 0x00000006,
    ACTION_COMMAND_UNUSED_FLEE               = 0x00000007,
    ACTION_COMMAND_DIZZY_SHELL               = 0x00000008,
    ACTION_COMMAND_FIRE_SHELL                = 0x00000009,
    ACTION_COMMAND_UNUSED_MASH_A             = 0x0000000A,
    ACTION_COMMAND_BOMB                      = 0x0000000B,
    ACTION_COMMAND_BODY_SLAM                 = 0x0000000C,
    ACTION_COMMAND_AIR_LIFT                  = 0x0000000D,
    ACTION_COMMAND_AIR_RAID                  = 0x0000000E,
    ACTION_COMMAND_SQUIRT                    = 0x0000000F,
    ACTION_COMMAND_POWER_SHOCK               = 0x00000010,
    ACTION_COMMAND_MEGA_SHOCK                = 0x00000011,
    ACTION_COMMAND_SMACK                     = 0x00000012,
    ACTION_COMMAND_SPINY_SURGE               = 0x00000013,
    ACTION_COMMAND_HURRICANE                 = 0x00000014,
    ACTION_COMMAND_SPOOK                     = 0x00000015,
    ACTION_COMMAND_THREE_CHANCES             = 0x00000016,
    ACTION_COMMAND_TIDAL_WAVE                = 0x00000017,
};

enum HazardType {
    HAZARD_TYPE_NONE        = 0,
    HAZARD_TYPE_LAVA        = 1,
    HAZARD_TYPE_SPIKES      = 2,
    HAZARD_TYPE_FIRE_BAR    = 3,
};

enum DamageIntensityRange {
    DAMAGE_INTENSITY_LIGHT      = 0,    // 0-3
    DAMAGE_INTENSITY_MEDIUM     = 1,    // 4-6
    DAMAGE_INTENSITY_HEAVY      = 2,    // 7-9
    DAMAGE_INTENSITY_EXTREME    = 3,    // 10+
    DAMAGE_INTENSITY_UNUSED     = 4,    // unused
};

enum EffectInstanceFlags {
    FX_INSTANCE_FLAG_ENABLED            = 0x00000001,
    FX_INSTANCE_FLAG_BATTLE             = 0x00000004, // effect was created during battle
    FX_INSTANCE_FLAG_HAS_UPDATED        = 0x00000008, // has run update at least once
    FX_INSTANCE_FLAG_DISMISS            = 0x00000010, // effect should perform cleanup and self-delete
};

enum EffectSharedDataFlags {
    FX_SHARED_DATA_LOADED       = 0x00000001,
    FX_SHARED_DATA_CAN_FREE     = 0x00000002,
};

#include "move_enum.h"

enum GameContext {
    CONTEXT_WORLD       = 0,
    CONTEXT_BATTLE      = 1,
    CONTEXT_PAUSE       = 2,
};

enum DemoState {
    DEMO_STATE_NONE         = 0,
    DEMO_STATE_ACTIVE       = 1,
    DEMO_STATE_CHANGE_MAP   = 2,
    DEMO_STATE_4            = 4,
    DEMO_STATE_DONE         = 5,
};

enum DemoFlags {
    DEMO_BTL_FLAG_ENABLED           = 0x01,
    DEMO_BTL_FLAG_PARTNER_ACTING    = 0x02,
    DEMO_BTL_FLAG_ENEMY_ACTING      = 0x04,
    DEMO_BTL_FLAG_10                = 0x10,
    DEMO_BTL_FLAG_20                = 0x20,
    DEMO_BTL_FLAG_40                = 0x40,
};

enum IntroParts {
    INTRO_PART_0            = 0,
    INTRO_PART_1            = 1,
    INTRO_PART_5            = 5,
    INTRO_PART_100          = 100,
    INTRO_PART_NONE         = -1,
};

enum MapLoadType {
    LOAD_FROM_MAP           = 0,
    LOAD_FROM_FILE_SELECT   = 1,
};

enum BattleStatusFlags1 {
    BS_FLAGS1_ACTORS_VISIBLE                = 0x00000001,
    BS_FLAGS1_MENU_OPEN                     = 0x00000002,
    BS_FLAGS1_TATTLE_OPEN                   = 0x00000004,
    BS_FLAGS1_SHOW_PLAYER_DECORATIONS       = 0x00000008, // enables effects for Frozen, Water Block, and Cloud Nine to appear and follow the player
    // Enables attack bonuses like Power Plus and Merlee ATK boost.
    // Almost always used with TestTarget functions when not called with DAMAGE_TYPE_TRIGGER_LUCKY.
    BS_FLAGS1_INCLUDE_POWER_UPS             = 0x00000010,
    // Current hit may trigger special events on the target (other than hit/death/immune)
    // These include FLIP_TRIGGER, FALL_TRIGGER, BURN_HIT, SPIN_SMASH_HIT, etc.
    // This has no bearing on contact hazard events which affect the attacker like SPIKE_CONTACT or BURN_CONTACT.
    BS_FLAGS1_TRIGGER_EVENTS                = 0x00000020,
    BS_FLAGS1_NICE_HIT                      = 0x00000040,
    BS_FLAGS1_NO_RATING                     = 0x00000080, // prevents 'Nice!' or 'Super!' messages from appearing
    BS_FLAGS1_EXECUTING_MOVE                = 0x00000100,
    BS_FLAGS1_SUPER_HIT                     = 0x00000200, // only works for partners and items, NOT player hits
    BS_FLAGS1_FORCE_IMMUNE_HIT              = 0x00000800,
    BS_FLAGS1_AUTO_SUCCEED_ACTION           = 0x00001000,
    BS_FLAGS1_2000                          = 0x00002000,
    BS_FLAGS1_4000                          = 0x00004000,
    BS_FLAGS1_FREE_ACTION_COMMAND           = 0x00008000,
    BS_FLAGS1_10000                         = 0x00010000,
    BS_FLAGS1_DISABLE_CELEBRATION           = 0x00020000,
    BS_FLAGS1_BATTLE_FLED                   = 0x00040000, // used both when the player flees sucessfully or an enemy flees
    BS_FLAGS1_PARTNER_ACTING                = 0x00080000,
    BS_FLAGS1_PLAYER_IN_BACK                = 0x00100000,
    BS_FLAGS1_YIELD_TURN                    = 0x00200000, // moves end either when their script is finished or this flag is set by calling YieldTurn
    BS_FLAGS1_PLAYER_DEFENDING              = 0x00400000,
    BS_FLAGS1_NO_GAME_OVER                  = 0x00800000, // don’t game over on loss
    BS_FLAGS1_STAR_POINTS_DROPPED           = 0x01000000,
    BS_FLAGS1_TUTORIAL_BATTLE               = 0x02000000, // prevent player from swapping to/from partner
    BS_FLAGS1_HUSTLED                       = 0x04000000,
    BS_FLAGS1_SORT_ENEMIES_BY_POSX          = 0x08000000, // enemy turn order ignores priority; sorts bases on x position instead
    BS_FLAGS1_HAMMER_CHARGED                = 0x10000000,
    BS_FLAGS1_JUMP_CHARGED                  = 0x20000000,
    BS_FLAGS1_GOOMBARIO_CHARGED             = 0x40000000,
    BS_FLAGS1_ATK_BLOCKED                   = 0x80000000,
};

enum BattleStatusFlags2 {
    BS_FLAGS2_AWARDING_STAR_POINTS          = 0x00000001, // star points move to the center of the screen
    BS_FLAGS2_PLAYER_TURN_USED              = 0x00000002, // set after player has used their action for this turn
    BS_FLAGS2_PARTNER_TURN_USED             = 0x00000004, // set after partner has used their action for this turn
    BS_FLAGS2_OVERRIDE_INACTIVE_PLAYER      = 0x00000008, // override inactive player animations and effects
    BS_FLAGS2_OVERRIDE_INACTIVE_PARTNER     = 0x00000010, // override inactive partner animations and effects
    BS_FLAGS2_CAN_FLEE                      = 0x00000020,
    BS_FLAGS2_PEACH_BATTLE                  = 0x00000040,
    BS_FLAGS2_STORED_TURBO_CHARGE_TURN      = 0x00000100, // prevents turbo charge turns from decrementing on begin player turn
    BS_FLAGS2_DOING_JUMP_TUTORIAL           = 0x00000200,
    BS_FLAGS2_FINAL_BOWSER_PART_1           = 0x00000400, // no other use for this flag, purpose unknown
    BS_FLAGS2_NO_TARGET_AVAILABLE           = 0x00001000,
    BS_FLAGS2_IGNORE_DARKNESS               = 0x00004000,
    BS_FLAGS2_HIDE_BUFF_COUNTERS            = 0x00010000, // hide turn counters for partner buffs (Cloud Nine, Water Block, etc)
    BS_FLAGS2_NO_PLAYER_PAL_ADJUST          = 0x00100000,
    BS_FLAGS2_IS_FIRST_STRIKE               = 0x01000000,
    BS_FLAGS2_DONT_STOP_MUSIC               = 0x02000000, // don't stop playing the current song when the battle ends
    BS_FLAGS2_HAS_DRAINED_HP                = 0x04000000,
    BS_FLAGS2_HAS_RUSH                      = 0x08000000,
    BS_FLAGS2_DROP_WHACKA_BUMP              = 0x10000000,
};

enum BattleStatusReflectionFlags {
    BS_REFLECT_FLOOR    = 1,
};

enum BattleStates {
    BATTLE_STATE_INVALID                    = -1,   // may have been part of a debug state at some point, unused
    BATTLE_STATE_NONE                       = 0,
    BATTLE_STATE_START                      = 1,
    BATTLE_STATE_FIRST_STRIKE               = 2,
    BATTLE_STATE_PARTNER_FIRST_STRIKE       = 3,
    BATTLE_STATE_ENEMY_FIRST_STRIKE         = 4,
    BATTLE_STATE_BEGIN_TURN                 = 5,
    BATTLE_STATE_END_TURN                   = 6,
    BATTLE_STATE_BEGIN_PLAYER_TURN          = 7,
    BATTLE_STATE_BEGIN_PARTNER_TURN         = 8,
    BATTLE_STATE_TRANSFER_TURN              = 9,
    BATTLE_STATE_SWITCH_TO_PLAYER           = 10,
    BATTLE_STATE_SWITCH_TO_PARTNER          = 11,
    BATTLE_STATE_PREPARE_MENU               = 12,
    BATTLE_STATE_PLAYER_MENU                = 13,
    BATTLE_STATE_PARTNER_MENU               = 14,
    BATTLE_STATE_PEACH_MENU                 = 15,
    BATTLE_STATE_TWINK_MENU                 = 16,
    BATTLE_STATE_SELECT_TARGET              = 17,
    BATTLE_STATE_PLAYER_MOVE                = 18,
    BATTLE_STATE_PARTNER_MOVE               = 19,
    BATTLE_STATE_NEXT_ENEMY                 = 20,
    BATTLE_STATE_ENEMY_MOVE                 = 21,
    BATTLE_STATE_END_PLAYER_TURN            = 22,
    BATTLE_STATE_END_PARTNER_TURN           = 23,
    BATTLE_STATE_RUN_AWAY                   = 24,
    BATTLE_STATE_DEFEND                     = 25,
    BATTLE_STATE_VICTORY                    = 26,
    BATTLE_STATE_DEFEAT                     = 27,
    BATTLE_STATE_CHANGE_PARTNER             = 29,
    BATTLE_STATE_END_TRAINING_BATTLE        = 30,
    BATTLE_STATE_END_BATTLE                 = 32,
    BATTLE_STATE_CELEBRATION                = 33,
    BATTLE_STATE_END_DEMO_BATTLE            = 35,
};

enum BattleMessages {
    BTL_MSG_MERLEE_ATK_UP                           = 0x00,
    BTL_MSG_MERLEE_DEF_UP                           = 0x01,
    BTL_MSG_MERLEE_EXP_UP                           = 0x02,
    BTL_MSG_MERLEE_DONE                             = 0x03,
    BTL_MSG_CHARGE_HAMMER                           = 0x04,
    BTL_MSG_CHARGE_HAMMER_MORE                      = 0x05,
    BTL_MSG_CHARGE_JUMP                             = 0x06,
    BTL_MSG_CHARGE_JUMP_MORE                        = 0x07,
    BTL_MSG_CANT_CHARGE                             = 0x08,
    BTL_MSG_ENEMY_MISSED                            = 0x09,
    BTL_MSG_PLAYER_DAZED                            = 0x0A,
    BTL_MSG_PLAYER_ASLEEP                           = 0x0B,
    BTL_MSG_PLAYER_FROZEN                           = 0x0C,
    BTL_MSG_PLAYER_POISONED                         = 0x0D,
    BTL_MSG_PLAYER_SHRUNK                           = 0x0E,
    BTL_MSG_PLAYER_PARALYZED                        = 0x0F,
    BTL_MSG_PLAYER_CHARGED                          = 0x10,
    BTL_MSG_PLAYER_TRANSPARENT                      = 0x11,
    BTL_MSG_ENEMY_DAZED                             = 0x12,
    BTL_MSG_ENEMY_ASLEEP                            = 0x13,
    BTL_MSG_ENEMY_FROZEN                            = 0x14,
    BTL_MSG_ENEMY_POISONED                          = 0x15,
    BTL_MSG_ENEMY_SHRUNK                            = 0x16,
    BTL_MSG_ENEMY_PARALYZED                         = 0x17,
    BTL_MSG_ENEMY_ELECTRIFIED                       = 0x18,
    BTL_MSG_ENEMY_CANT_MOVE                         = 0x19,
    BTL_MSG_STAR_POWER_RECHARGED                    = 0x1A,
    BTL_MSG_STAR_POWER_MAXED                        = 0x1B,
    BTL_MSG_STAR_POWER_FILLED                       = 0x1C,
    BTL_MSG_ATTACK_UP                               = 0x1D,
    BTL_MSG_DEFENCE_UP                              = 0x1E,
    BTL_MSG_HEAL_ONE                                = 0x1F,
    BTL_MSG_HEAL_ALL                                = 0x20,
    BTL_MSG_ENEMY_TRANSPARENT                       = 0x21,
    BTL_MSG_ENEMY_CHARGED                           = 0x22,
    BTL_MSG_PARTNER_INJURED                         = 0x23,
    BTL_MSG_CHARGE_GOOMBARIO                        = 0x24,
    BTL_MSG_CHARGE_GOOMBARIO_MORE                   = 0x25,
    BTL_MSG_WATER_BLOCK_BEGIN                       = 0x26,
    BTL_MSG_WATER_BLOCK_END                         = 0x27,
    BTL_MSG_CLOUD_NINE_BEGIN                        = 0x28,
    BTL_MSG_CLOUD_NINE_END                          = 0x29,
    BTL_MSG_TURBO_CHARGE_BEGIN                      = 0x2A,
    BTL_MSG_TURBO_CHARGE_END                        = 0x2B,
    BTL_MSG_CHILL_OUT_BEGIN                         = 0x2C,
    BTL_MSG_UNUSED_CLOUD_NINE                       = 0x2D,
    BTL_MSG_FIRST_ACTION_TIP                        = 0x2E,
    BTL_MSG_ACTION_TIP_PRESS_BEFORE_LANDING         = 0x2E, // jump moves, Sky Dive
    BTL_MSG_ACTION_TIP_HOLD_LEFT_TIMED              = 0x2F, // hammer moves, Belly Flop, Shell Toss
    BTL_MSG_ACTION_TIP_PRESS_BEFORE_STRIKE          = 0x30, // Headbonk and Multibonk
    BTL_MSG_ACTION_TIP_MASH_BUTTON                  = 0x31, // Dizzy Shell, Power Shock, Air Lift, Bombette's moves
    BTL_MSG_ACTION_TIP_MASH_LEFT                    = 0x32, // Fire Shell, Air Raid, Spiny Surge, Bow's moves
    BTL_MSG_ACTION_TIP_HOLD_LEFT_AIM                = 0x33, // Shell Shot
    BTL_MSG_ACTION_TIP_UNUSED_1                     = 0x34, // unused
    BTL_MSG_ACTION_TIP_UNUSED_2                     = 0x35, // unused
    BTL_MSG_ACTION_TIP_PRESS_BUTTONS_SHOWN          = 0x36, // Tidal Wave
    BTL_MSG_ACTION_TIP_NOT_USED_1                   = 0x37, // unused, special message
    BTL_MSG_ACTION_TIP_PRESS_WITH_TIMING            = 0x38, // Turbo Charge, Water Block, Cloud Nine
    BTL_MSG_ACTION_TIP_NOT_USED_2                   = 0x39, // unused, special message
    BTL_MSG_ACTION_TIP_MASH_BOTH                    = 0x3A, // Mega Shock and Hurricane
    BTL_MSG_ACTION_TIP_UNUSED_3                     = 0x3B, // unused
    BTL_MSG_ACTION_TIP_HOLD_THEN_TAP                = 0x3C, // Squirt
    BTL_MSG_ACTION_TIP_HOLD_THEN_RELEASE            = 0x3D, // Body Slam and Electro Dash
    BTL_MSG_ACTION_TIP_MOVE_TO_AIM                  = 0x3E, // Spiny Flip
    BTL_MSG_ACTION_TIP_UNUSED_4                     = 0x3F, // unused
    BTL_MSG_ACTION_TIP_BREAK_FREE                   = 0x40, // unused
    BTL_MSG_ACTION_TIP_REDUCE_DAMAGE                = 0x41, // unused
    BTL_MSG_ACTION_TIP_NOT_USED_3                   = 0x42, // Earthquake Jump
    BTL_MSG_LAST_ACTION_TIP                         = 0x42,
    BTL_MSG_NO_JUMP_TARGET                          = 0x43,
    BTL_MSG_NO_HAMMER_TARGET                        = 0x44,
    BTL_MSG_NO_ITEM_TARGET                          = 0x45,
    BTL_MSG_46                                      = 0x46,
    BTL_MSG_47                                      = 0x47,
    BTL_MSG_CANT_SELECT_NOW                         = 0x48,
    BTL_MSG_HAMMER_DISABLED_1                       = 0x49,
    BTL_MSG_HAMMER_DISABLED_2                       = 0x4A,
    BTL_MSG_HAMMER_DISABLED_3                       = 0x4B,
    BTL_MSG_JUMP_DISABLED_1                         = 0x4C,
    BTL_MSG_JUMP_DISABLED_2                         = 0x4D,
    BTL_MSG_JUMP_DISABLED_3                         = 0x4E,
    BTL_MSG_ITEMS_DISABLED                          = 0x4F,
    BTL_MSG_CANT_SWITCH                             = 0x50,
    BTL_MSG_CANT_MOVE                               = 0x51,
    BTL_MSG_CANT_SWITCH_UNUSED                      = 0x52,
    BTL_MSG_CANT_MOVE_UNUSED                        = 0x53,
    BTL_MSG_CANT_SELECT_NOW_ALT                     = 0x54,
};

// states after INIT are different for each type of battle message
enum BattleMessageStates {
    // generic INIT state shared by all message types
    BTL_MSG_STATE_INIT                  = 0,
    // states for popup messages like BTL_MSG_MERLEE_ATK_UP or BTL_MSG_ENEMY_ASLEEP
    BTL_MSG_STATE_POPUP_PRE_DELAY       = 1,
    BTL_MSG_STATE_POPUP_DELAY           = 2,
    BTL_MSG_STATE_POPUP_POST_DELAY      = 3,
    BTL_MSG_STATE_POPUP_DISPOSE         = 4,
    // states for action tip messages
    BTL_MSG_STATE_ACTION_TIP_DELAY      = 1,
    BTL_MSG_STATE_ACTION_TIP_DISPOSE    = 2,
    // states for error messages like BTL_MSG_NO_JUMP_TARGET or BTL_MSG_CANT_SELECT_NOW
    BTL_MSG_STATE_ERROR_PRE_DELAY       = 1,
    BTL_MSG_STATE_ERROR_DELAY           = 2,
    BTL_MSG_STATE_ERROR_POST_DELAY      = 3,
    BTL_MSG_STATE_ERROR_DISPOSE         = 4,
    // states for command disable notifications like BTL_MSG_ITEMS_DISABLED
    BTL_MSG_STATE_DISABLED_DELAY        = 1,
};

enum BattleMenuIndex {
    BTL_MENU_IDX_MAIN               = 0,
    BTL_MENU_IDX_JUMP               = 1,
    BTL_MENU_IDX_SMASH              = 2,
    BTL_MENU_IDX_ITEMS              = 3,
    BTL_MENU_IDX_DIP                = 4,
    BTL_MENU_IDX_PARTNER            = 5,
    BTL_MENU_IDX_STAR_POWER         = 6,
    BTL_MENU_IDX_STRATEGY           = 7,
    // partners only
    BTL_MENU_IDX_ABILITY            = 1,
    BTL_MENU_IDX_PARTNER_ITEM       = 4,
};

enum BattleMenuTypes {
    BTL_MENU_TYPE_INVALID           = -1,
    BTL_MENU_TYPE_JUMP              = 0,
    BTL_MENU_TYPE_SMASH             = 1,
    BTL_MENU_TYPE_ITEMS             = 2,
    BTL_MENU_TYPE_RUN_AWAY          = 3,
    BTL_MENU_TYPE_DEFEND            = 4,
    BTL_MENU_TYPE_CHANGE_PARTNER    = 5,
    BTL_MENU_TYPE_ABILITY           = 6,
    BTL_MENU_TYPE_STRATEGIES        = 7,
    BTL_MENU_TYPE_STAR_POWERS       = 8,
    BTL_MENU_TYPE_DO_NOTHING        = 9,
    BTL_MENU_TYPE_ACT_LATER         = 10,
    BTL_MENU_TYPE_PARTNER_FOCUS     = 11,
};

enum BattleMenuDisableFlags {
    BTL_MENU_ENABLED_JUMP           = 1 << BTL_MENU_TYPE_JUMP,
    BTL_MENU_ENABLED_SMASH          = 1 << BTL_MENU_TYPE_SMASH,
    BTL_MENU_ENABLED_ITEMS          = 1 << BTL_MENU_TYPE_ITEMS,
    BTL_MENU_ENABLED_ABILITIES      = 1 << BTL_MENU_TYPE_ABILITY,
    BTL_MENU_ENABLED_STRATEGIES     = 1 << BTL_MENU_TYPE_STRATEGIES,
    BTL_MENU_ENABLED_STAR_POWERS    = 1 << BTL_MENU_TYPE_STAR_POWERS,
    BTL_MENU_ENABLED_PARTNER_FOCUS  = 1 << BTL_MENU_TYPE_PARTNER_FOCUS,
};

enum BattleRumbleModes {
    BTL_RUMBLE_STOP                 = 0,
    BTL_RUMBLE_LONG                 = 1,
    BTL_RUMBLE_HIT_MIN              = 2,
    BTL_RUMBLE_HIT_LIGHT            = 3,
    BTL_RUMBLE_HIT_HEAVY            = 4,
    BTL_RUMBLE_HIT_EXTREME          = 5,
    BTL_RUMBLE_HIT_MAX              = 6,
    BTL_RUMBLE_PLAYER_MIN           = 7,
    BTL_RUMBLE_PLAYER_LIGHT         = 8,
    BTL_RUMBLE_PLAYER_HEAVY         = 9,
    BTL_RUMBLE_PLAYER_EXTREME       = 10,
    BTL_RUMBLE_PLAYER_MAX           = 11,
};

enum DebugEnemyContactModes {
    DEBUG_CONTACT_NONE              = 0, // contact with enemies behaves normally
    DEBUG_CONTACT_CANT_TOUCH        = 1, // enemies pass through the player and cannot start battles
    DEBUG_CONTACT_DIE_ON_TOUCH      = 2, // enemies die on contact in the overworld
    DEBUG_CONTACT_DIE_IN_BATTLE     = 3, // all enemies wll die during BATTLE_STATE_BEGIN_TURN
    DEBUG_CONTACT_AUTO_FLEE         = 4, // the player flees during BATTLE_STATE_BEGIN_TURN
};

enum DebugScriptstModes {
    DEBUG_SCRIPTS_NONE              = 0,
    DEBUG_SCRIPTS_NO_UPDATE         = 1,
    DEBUG_SCRIPTS_BLOCK_FUNC_DONE   = 2,
};

enum PlayerBasicJump {
    PLAYER_BASIC_JUMP_0         = 0,
    PLAYER_BASIC_JUMP_1         = 1,
    PLAYER_BASIC_JUMP_2         = 2,
    PLAYER_BASIC_JUMP_3         = 3,
    PLAYER_BASIC_JUMP_4         = 4,
};

enum PlayerSuperJump {
    PLAYER_SUPER_JUMP_0         = 0,
    PLAYER_SUPER_JUMP_1         = 1,
    PLAYER_SUPER_JUMP_2         = 2,
    PLAYER_SUPER_JUMP_3         = 3,
    PLAYER_SUPER_JUMP_4         = 4,
    PLAYER_SUPER_JUMP_5         = 5,
    PLAYER_SUPER_JUMP_6         = 6,
};

enum PlayerUltraJump {
    PLAYER_ULTRA_JUMP_0         = 0,
    PLAYER_ULTRA_JUMP_1         = 1,
    PLAYER_ULTRA_JUMP_2         = 2,
    PLAYER_ULTRA_JUMP_3         = 3,
    PLAYER_ULTRA_JUMP_4         = 4,
};

enum GlobalOverrides {
    GLOBAL_OVERRIDES_DISABLE_RENDER_WORLD           = 0x00000002,
    GLOBAL_OVERRIDES_DISABLE_DRAW_FRAME             = 0x00000008,
    GLOBAL_OVERRIDES_MESSAGES_OVER_FRONTUI          = 0x00000010,
    GLOBAL_OVERRIDES_SOFT_RESET                     = 0x00000020, // unused but functional
    GLOBAL_OVERRIDES_40                             = 0x00000040,
    GLOBAL_OVERRIDES_ENABLE_FLOOR_REFLECTION        = 0x00000080,
    GLOBAL_OVERRIDES_DISABLE_BATTLES                = 0x00000100,
    GLOBAL_OVERRIDES_200                            = 0x00000200,
    GLOBAL_OVERRIDES_400                            = 0x00000400,
    GLOBAL_OVERRIDES_800                            = 0x00000800,
    GLOBAL_OVERRIDES_PREV_DISABLE_BATTLES           = 0x00001000,
    GLOBAL_OVERRIDES_PREV_200                       = 0x00002000,
    GLOBAL_OVERRIDES_PREV_400                       = 0x00004000,
    GLOBAL_OVERRIDES_PREV_800                       = 0x00008000,
    GLOBAL_OVERRIDES_WINDOWS_OVER_CURTAINS          = 0x00010000,
    GLOBAL_OVERRIDES_DONT_RESUME_SONG_AFTER_BATTLE  = 0x00020000,
    GLOBAL_OVERRIDES_DISABLE_MENUS                  = 0x00040000,
    GLOBAL_OVERRIDES_MESSAGES_OVER_CURTAINS         = 0x00100000,
    GLOBAL_OVERRIDES_CANT_PICK_UP_ITEMS             = 0x00200000,
};

#define MODEL_FLAGS_MASK_FFF0  (\
      MODEL_FLAG_USES_CUSTOM_GFX \
    | MODEL_FLAG_20 \
    | MODEL_FLAG_IGNORE_FOG \
    | MODEL_FLAG_HAS_LOCAL_VERTEX_COPY \
    | MODEL_FLAG_BILLBOARD \
    | MODEL_FLAG_DO_BOUNDS_CULLING \
    | MODEL_FLAG_HAS_TRANSFORM \
    | MODEL_FLAG_HAS_TEX_PANNER \
    | MODEL_FLAG_MATRIX_DIRTY \
    | MODEL_FLAG_IGNORE_MATRIX \
    | MODEL_FLAG_UNUSED_4000 \
    | MODEL_FLAG_UNUSED_8000)

enum ModelFlags {
    MODEL_FLAG_VALID                    = 0x0001,
    MODEL_FLAG_HIDDEN                   = 0x0002,
    MODEL_FLAG_INACTIVE                 = 0x0004,
    MODEL_FLAG_TRANSFORM_GROUP_MEMBER   = 0x0008,
    MODEL_FLAG_USES_CUSTOM_GFX          = 0x0010,
    MODEL_FLAG_20                       = 0x0020,
    MODEL_FLAG_IGNORE_FOG               = 0x0040,
    MODEL_FLAG_HAS_LOCAL_VERTEX_COPY    = 0x0080,
    MODEL_FLAG_BILLBOARD                = 0x0100, // rotate to face the camera
    MODEL_FLAG_DO_BOUNDS_CULLING        = 0x0200,
    MODEL_FLAG_HAS_TRANSFORM            = 0x0400,
    MODEL_FLAG_HAS_TEX_PANNER           = 0x0800,
    MODEL_FLAG_MATRIX_DIRTY             = 0x1000, // transform matrix changed and combined matrix needs to be recalculated
    MODEL_FLAG_IGNORE_MATRIX            = 0x2000, // set until dirty combined matrix has been recalculated
    MODEL_FLAG_UNUSED_4000              = 0x4000,
    MODEL_FLAG_UNUSED_8000              = 0x8000,
};

enum ModelGroupVisibility {
    MODEL_GROUP_HIDDEN          = 0,
    MODEL_GROUP_VISIBLE         = 1,
    MODEL_GROUP_OTHERS_HIDDEN   = 2,
    MODEL_GROUP_OTHERS_VISIBLE  = 3,
};

enum ApplyTintTarget {
    APPLY_TINT_MODELS = 0,
    APPLY_TINT_GROUPS = 1,
    APPLY_TINT_BG     = 2,
};

enum TintMode {
    ENV_TINT_UNCHANGED  = -1,
    // no additional tint is applied (model is still be affected by world fog)
    ENV_TINT_NONE       = 0,
    // additional fog which 'shrouds' the world during certain scenes
    ENV_TINT_SHROUD     = 1,
    // adds depth-based tint using fog, overriding the world fog for affected models
    ENV_TINT_DEPTH      = 2,
    // this mode remaps each color channel range from [0, 255] -> [min, max],
    // setting a new white point and black point for the scene.
    // the new max values are stored in PRIMITIVE and the new min values in ENV
    ENV_TINT_REMAP      = 3,
};

enum TexPanner {
    //select pan unit
    TEX_PANNER_0    = 0x0,
    TEX_PANNER_1    = 0x1,
    TEX_PANNER_2    = 0x2,
    TEX_PANNER_3    = 0x3,
    TEX_PANNER_4    = 0x4,
    TEX_PANNER_5    = 0x5,
    TEX_PANNER_6    = 0x6,
    TEX_PANNER_7    = 0x7,
    TEX_PANNER_8    = 0x8,
    TEX_PANNER_9    = 0x9,
    TEX_PANNER_A    = 0xA,
    TEX_PANNER_B    = 0xB,
    TEX_PANNER_C    = 0xC,
    TEX_PANNER_D    = 0xD,
    TEX_PANNER_E    = 0xE,
    TEX_PANNER_F    = 0xF,
    // select texture component
    TEX_PANNER_MAIN = 0,
    TEX_PANNER_AUX  = 1,
};

enum CustomGfxUnit {
    CUSTOM_GFX_NONE = -1,
    CUSTOM_GFX_0    = 0x00,
    CUSTOM_GFX_1    = 0x01,
    CUSTOM_GFX_2    = 0x02,
    CUSTOM_GFX_3    = 0x03,
    CUSTOM_GFX_4    = 0x04,
    CUSTOM_GFX_5    = 0x05,
    CUSTOM_GFX_6    = 0x06,
    CUSTOM_GFX_7    = 0x07,
    CUSTOM_GFX_8    = 0x08,
    CUSTOM_GFX_9    = 0x09,
    CUSTOM_GFX_A    = 0x0A,
    CUSTOM_GFX_B    = 0x0B,
    CUSTOM_GFX_C    = 0x0C,
    CUSTOM_GFX_D    = 0x0D,
    CUSTOM_GFX_E    = 0x0E,
    CUSTOM_GFX_F    = 0x0F,
};

enum CopiedVtxUnit {
    VTX_COPY_0      = 0x0,
    VTX_COPY_1      = 0x1,
    VTX_COPY_2      = 0x2,
    VTX_COPY_3      = 0x3,
    VTX_COPY_4      = 0x4,
    VTX_COPY_5      = 0x5,
    VTX_COPY_6      = 0x6,
    VTX_COPY_7      = 0x7,
    VTX_COPY_8      = 0x8,
    VTX_COPY_9      = 0x9,
    VTX_COPY_A      = 0xA,
    VTX_COPY_B      = 0xB,
    VTX_COPY_C      = 0xC,
    VTX_COPY_D      = 0xD,
    VTX_COPY_E      = 0xE,
    VTX_COPY_F      = 0xF,
};

enum ModelAnimUnit {
    MDL_ANIMATOR_0  = 0x0,
    MDL_ANIMATOR_1  = 0x1,
    MDL_ANIMATOR_2  = 0x2,
    MDL_ANIMATOR_3  = 0x3,
    MDL_ANIMATOR_4  = 0x4,
    MDL_ANIMATOR_5  = 0x5,
    MDL_ANIMATOR_6  = 0x6,
    MDL_ANIMATOR_7  = 0x7,
    MDL_ANIMATOR_8  = 0x8,
    MDL_ANIMATOR_9  = 0x9,
    MDL_ANIMATOR_A  = 0xA,
    MDL_ANIMATOR_B  = 0xB,
    MDL_ANIMATOR_C  = 0xC,
    MDL_ANIMATOR_D  = 0xD,
    MDL_ANIMATOR_E  = 0xE,
    MDL_ANIMATOR_F  = 0xF,
};

enum MapRoomFlags {
    ROOM_FLAGS_VISGROUP_MASK                = 0xF000,
    ROOM_FLAGS_MASK                         = 0x0F00,
    ROOM_FLAGS_DOOR_TYPE_MASK               = 0x00FF,
    ROOM_DOOR_RIGHT_HINGE_OPENS_OUT         = 0, // left --> center (hinge on right)
    ROOM_DOOR_RIGHT_HINGE_OPENS_IN          = 1, // center --> left
    ROOM_DOOR_LEFT_HINGE_OPENS_OUT          = 2, // right --> center (hinge on left)
    ROOM_DOOR_LEFT_HINGE_OPENS_IN           = 3, // center --> right
    ROOM_DOOR_STRAIGHT_THROUGH              = 4, // center --> center
    ROOM_LARGE_DOOR_RIGHT_HINGE_OPENS_OUT   = 5, // deep left  --> center     (hinge on right)
    ROOM_LARGE_DOOR_RIGHT_HINGE_OPENS_IN    = 6, // center     --> deep left
    ROOM_LARGE_DOOR_LEFT_HINGE_OPENS_OUT    = 7, // deep right --> center     (hinge on left)
    ROOM_FLAG_CUSTOM_ANIM_OPEN_DOOR         = 0x100,
    ROOM_FLAG_CUSTOM_ANIM_WALL_ROT          = 0x200,
    ROOM_FLAG_CUSTOM_ANIM_DROP_DOOR         = 0x400,
    ROOM_FLAG_EXIT_DOOR_DROPS               = 0x800, // for internal use
};

enum MapRoomNotifications {
    // dispatched to listener script during interactions with the room door
    ROOM_UPDATE_ENTER_BEGIN     = 0,
    ROOM_UPDATE_ENTER_DONE      = 1,
    ROOM_UPDATE_EXIT_BEGIN      = 2,
    ROOM_UPDATE_EXIT_END        = 3,
    // when handling ROOM_UPDATE_ENTER_BEGIN, listener may return this to cancel the door opening. useful for locked doors.
    ROOM_UPDATE_REQUEST_CANCEL  = -1,
    // anim move door updates
    ROOM_MOVE_DOOR_ENTER_OPEN   = 0,
    ROOM_MOVE_DOOR_ENTER_CLOSE  = 1,
    ROOM_MOVE_DOOR_EXIT_OPEN    = 2,
    ROOM_MOVE_DOOR_EXIT_CLOSE   = 3,
    // anim move walls update
    ROOM_MOVE_WALL_OPEN         = 0,
    ROOM_MOVE_WALL_1            = 1, // unused
    ROOM_MOVE_WALL_2            = 2, // unused
    ROOM_MOVE_WALL_CLOSE        = 3,
    // anim drop droor updates
    ROOM_DROP_DOOR_ENTER        = 0,
    ROOM_DROP_DOOR_1            = 1, // unused
    ROOM_DROP_DOOR_2            = 2, // unused
    ROOM_DROP_DOOR_EXIT         = 3,
};

enum EnemyFlags {
    ENEMY_FLAG_PASSIVE                  = 0x00000001, // Not hostile; collision does not trigger battle
    ENEMY_FLAG_UNUSED_2                 = 0x00000002, // Unused
    ENEMY_FLAG_DO_NOT_KILL              = 0x00000004, // Enemy will not be killed after being defeated in battle
    ENEMY_FLAG_ENABLE_HIT_SCRIPT        = 0x00000008,
    ENEMY_FLAG_FLED                     = 0x00000010,
    ENEMY_FLAG_DISABLE_AI               = 0x00000020, // Disable movement AI and collision (idle animation plays)
    ENEMY_FLAG_PROJECTILE               = 0x00000040,
    ENEMY_FLAG_DONT_UPDATE_SHADOW_Y     = 0x00000080,
    ENEMY_FLAG_IGNORE_WORLD_COLLISION   = 0x00000100,
    ENEMY_FLAG_IGNORE_PLAYER_COLLISION  = 0x00000200,
    ENEMY_FLAG_IGNORE_ENTITY_COLLISION  = 0x00000400,
    ENEMY_FLAG_FLYING                   = 0x00000800, // Corresponds with NPC_FLAG_FLYING, name seems incorrect?
    ENEMY_FLAG_GRAVITY                  = 0x00001000,
    ENEMY_FLAG_NO_SHADOW_RAYCAST        = 0x00002000,
    ENEMY_FLAG_HAS_NO_SPRITE            = 0x00004000,
    ENEMY_FLAG_USE_INSPECT_ICON         = 0x00008000, // Corresponds with NPC_FLAG_USE_INSPECT_ICON
    ENEMY_FLAG_RAYCAST_TO_INTERACT      = 0x00010000, // Intended to require a line of sight raycast before conversations can be triggered. Seems bugged. Corresponds with NPC_FLAG_RAYCAST_TO_INTERACT
    ENEMY_FLAG_USE_PLAYER_SPRITE        = 0x00020000, // Used for Peach NPCs
    ENEMY_FLAG_NO_DELAY_AFTER_FLEE      = 0x00040000,
    ENEMY_FLAG_DONT_SUSPEND_SCRIPTS     = 0x00080000, // Do not suspend ai/aux scripts when aiSuspendTime != 0
    ENEMY_FLAG_SKIP_BATTLE              = 0x00100000,
    ENEMY_FLAG_ACTIVE_WHILE_OFFSCREEN   = 0x00200000,
    ENEMY_FLAG_DO_NOT_AUTO_FACE_PLAYER  = 0x00400000,
    ENEMY_FLAG_NO_DROPS                 = 0x00800000, // Do not drop hearts, flowers, or coins on defeat
    ENEMY_FLAG_IGNORE_TOUCH             = 0x01000000,
    ENEMY_FLAG_IGNORE_JUMP              = 0x02000000,
    ENEMY_FLAG_IGNORE_HAMMER            = 0x04000000,
    ENEMY_FLAG_CANT_INTERACT            = 0x08000000, // Makes passive NPCs non-interactable. Hostile NPCs are always non-interactible.
    ENEMY_FLAG_IGNORE_PARTNER           = 0x10000000,
    ENEMY_FLAG_IGNORE_SPIN              = 0x20000000,
    ENEMY_FLAG_BEGIN_WITH_CHASING       = 0x40000000, // Starts in state AI_STATE_CHASE_INIT instead of AI_STATE_WANDER_INIT on spawn or AI resume
    ENEMY_FLAG_SUSPENDED                = 0x80000000,
};

#define BASE_PASSIVE_FLAGS \
    ( ENEMY_FLAG_PASSIVE \
    | ENEMY_FLAG_IGNORE_WORLD_COLLISION \
    | ENEMY_FLAG_IGNORE_ENTITY_COLLISION \
    | ENEMY_FLAG_FLYING \
    )

#define COMMON_PASSIVE_FLAGS \
    ( BASE_PASSIVE_FLAGS \
    | ENEMY_FLAG_ENABLE_HIT_SCRIPT \
    )

// used with Enemy::aiFlags
enum EnemyAIFlags {
    AI_FLAG_1                           = 0x00000001,
    AI_FLAG_CANT_DETECT_PLAYER          = 0x00000002,
    AI_FLAG_SUSPEND                     = 0x00000004,
    AI_FLAG_SKIP_EMOTE_AFTER_FLEE       = 0x00000008,
    AI_FLAG_SKIP_IDLE_ANIM_AFTER_FLEE   = 0x00000010,
    AI_FLAG_OUTSIDE_TERRITORY           = 0x00000020,
    AI_FLAG_NEEDS_HEADING               = 0x00000040,
    AI_FLAG_CAN_RESUME_PATROL           = 0x00000080,
};

enum EnemyActionFlags {
    AI_ACTION_JUMP_WHEN_SEE_PLAYER          = 0x01, // enemy hops when detecting the player
    AI_ACTION_NO_FIRST_STRIKE               = 0x02, // prevents enemy from first-striking; only implemented for flying enemy AI
    AI_ACTION_CHASE_REQUIRES_PATH           = 0x04, // enemy will only continue chasing the player while an unobstructed path to the player exists
    AI_ACTION_NO_SPIN_REACTION              = 0x08, // enemy will not spin around when a battle is initiated with the player's spin move
    AI_ACTION_LOOK_AROUND_DURING_LOITER     = 0x10, // enemy will randomly look left and right while loitering
    AI_ACTION_MUTE_OFFSCREEN                = 0x20, // enemy AI will not produce sounds when offscreen
};

enum EnemyDetectFlags {
    AI_DETECT_SIGHT                 = 0x01, // enemy requires line of sight for detecting the player
    AI_DETECT_MOTION_SENSITIVE      = 0x02, // enemy will have an easier time detecting a moving player
};

enum DetectVolumeFlags {
    AI_DETECT_FLAG_IGNORE_HIDING      = 0x01, // bow and sushi dont prevent enemy detection
    AI_DETECT_FLAG_IGNORE_ELEVATION   = 0x02, // vertical size of detection volume is ignored
};

enum MusicSettingsFlags {
    MUSIC_SETTINGS_FLAG_1                 = 0x00000001,
    MUSIC_SETTINGS_FLAG_ENABLE_PROXIMITY_MIX   = 0x00000002,
    MUSIC_SETTINGS_FLAG_4                 = 0x00000004,
    MUSIC_SETTINGS_FLAG_8                 = 0x00000008,
    MUSIC_SETTINGS_FLAG_10                = 0x00000010,
    MUSIC_SETTINGS_FLAG_20                = 0x00000020,
};

// the lower byte of ColliderFlags
enum SurfaceType {
    SURFACE_TYPE_DEFAULT            = 0,
    SURFACE_TYPE_WATER              = 1,
    SURFACE_TYPE_SPIKES             = 2,
    SURFACE_TYPE_LAVA               = 3,
    SURFACE_TYPE_DOCK_WALL          = 4,
    SURFACE_TYPE_SLIDE              = 5,
    SURFACE_TYPE_FLOWERS            = 6,
    SURFACE_TYPE_CLOUD              = 7, ///< used with clouds in flo_19 and flo_21
    SURFACE_TYPE_SNOW               = 8,
    SURFACE_TYPE_HEDGES             = 9, ///< used within hedge maze in flo_11
    SURFACE_TYPE_INVALID            = -1,
};

typedef enum SurfaceInteractMode {
    SURFACE_INTERACT_WALK       = 0,
    SURFACE_INTERACT_RUN        = 1,
    SURFACE_INTERACT_LAND       = 2,
} SurfaceInteractMode;

// flags that can be set on colliders
// passed into collision queries to selectively ignore certain types of objects or colliders
enum ColliderFlags {
    COLLIDER_FLAGS_UPPER_MASK           = 0x7FFFFE00, // map data dumper needs this to be first
    COLLIDER_FLAGS_SURFACE_TYPE_MASK    = 0x000000FF,
    COLLIDER_FLAG_SAFE_FLOOR            = 0x00000100,
    COLLIDER_FLAG_IGNORE_SHELL          = 0x00008000, // colliders marked with this flag are not solid for shells
    COLLIDER_FLAG_IGNORE_PLAYER         = 0x00010000, // colliders marked with this flag are not solid for player or partners
    COLLIDER_FLAG_IGNORE_NPC            = 0x00020000, // colliders marked with this flag are not solid for npcs or item entities
    COLLISION_IGNORE_ENTITIES           = 0x00040000, // used for collision queries, not set for colliders
    COLLIDER_FLAG_DOCK_WALL             = 0x00080000,
    COLLISION_ONLY_ENTITIES             = 0x00100000, // used for collision queries, not set for colliders
    COLLIDER_FLAG_HAS_MODEL_PARENT      = 0x80000000
};

enum ColliderFlagsModifyMode {
    MODIFY_COLLIDER_FLAGS_SET_BITS       = 0,
    MODIFY_COLLIDER_FLAGS_CLEAR_BITS     = 1,
    MODIFY_COLLIDER_FLAGS_SET_VALUE      = 2,
    MODIFY_COLLIDER_FLAGS_SET_SURFACE    = 3,
};

enum PlayerCollisionTests {
    PLAYER_COLLISION_0          = 0,
    PLAYER_COLLISION_1          = 1,
    PLAYER_COLLISION_2          = 2,
    PLAYER_COLLISION_HAMMER     = 3,
    PLAYER_COLLISION_4          = 4,
};

enum CameraFlags {
    CAMERA_FLAG_INITIALIZED         = 0x00000001,
    CAMERA_FLAG_DISABLED            = 0x00000002,
    CAMERA_FLAG_LEAD_PLAYER         = 0x00000004,
    CAMERA_FLAG_SHAKING             = 0x00000008,
    CAMERA_FLAG_ORTHO               = 0x00000010,
    CAMERA_FLAG_NO_DRAW             = 0x00000080,
    CAMERA_FLAG_RENDER_ENTITIES     = 0x00000200,
    CAMERA_FLAG_RENDER_MODELS       = 0x00000400,
    CAMERA_FLAG_SUPRESS_LEADING     = 0x00001000,
};

enum CameraMoveFlags {
    CAMERA_MOVE_IGNORE_PLAYER_Y     = 0x00000001,
    CAMERA_MOVE_NO_INTERP_Y         = 0x00000002,
    CAMERA_MOVE_ACCEL_INTERP_Y      = 0x00000004,
};

enum CameraUpdateMode {
    // simple camera based on lookAtEye and lookAtObj with no blending or interpolation
    // control this camera by directly setting these positions
    // has no other control parameters
    CAM_UPDATE_MINIMAL              = 0,

    // this camera uses a set of control parameters to calculate its target lookAtObj and lookAtEye positions,
    // then interpolates current positions toward those targets, moving up to half the remaining distance each frame
    // the ultimate target is given by lookAtObjTarget
    // mostly used for CAM_HUD
    CAM_UPDATE_INTERP_POS           = 2,

    // this camera samples camera zones below its targetPos and derives control parameters from their settings,
    // interpolating its control parameters when changing zones. these control parameters determine the camera
    // position and orientation just like other camera modes.
    // note that this code does NOT directly reference the player position in any manner, it is only concerned
    // with the camera's targetPos, which must be assigned elsewhere.
    // this is the camera used during world gameplay
    CAM_UPDATE_FROM_ZONE            = 3,

    // this camera uses a set of control parameters to calculate its lookAtObj and lookAtEye positions,
    // which are only updated if skipRecalc = false
    // the ultimate target is given by lookAtObjTarget, with an offset given by targetPos (?!)
    // in practice, this is used for CAM_BATTLE and CAM_TATTLE, with skipRecalc almost always set to false
    CAM_UPDATE_NO_INTERP            = 6,

    // this camera tracks lookAtObjTarget in a circular region centered on targetPos. the camera does not update
    // unless lookAtObjTarget is greater than a minimum distance from targetPos to prevent wild movements.
    CAM_UPDATE_UNUSED_RADIAL        = 1,

    // this camera tracks targetPos, clamped within the rectangular region given by ± xLimit and ± zLimit
    // y-position is drawn from lookAtObjTarget
    // does not use easing or interpolation
    CAM_UPDATE_UNUSED_CONFINED      = 4,

    // this camera tracks player position and adds basic 'leading' in the x-direction only
    // camera yaw is fixed at zero and the lead direction is determined by player world yaw
    // thus, this only works for '2D' style maps where left is -x and right is +x
    CAM_UPDATE_UNUSED_LEADING       = 5,

    // this mode is completely unused in vanilla; it doesn't even have a case in update_cameras
    // seems to be based on CAM_UPDATE_NO_INTERP (the one used for battle cam)
    // tracks a point 400 units ahead of player position in the z-direction and 60 units above
    // defaults to a relatively short boom length and no pitch angle, resulting in a head-on direct view
    // CAM_UPDATE_UNUSED_AHEAD,
};

enum CameraControlType {
    // Camera follows the player, using a fixed yaw position.
    // Uses: A/B as 2D points
    // Yaw is defined by the line segment AB
    // flag 0 = free forward movement (follow player)
    // flag 1 = lock forward movement (must intersect B)
    CAM_CONTROL_FIXED_ORIENTATION   = 0,

    // Camera faces toward or away from a point with the player in the center of the frame.
    // Use a negative boom length to look away from a point.
    // flag 1 = Constrain to Fixed Radius
    CAM_CONTROL_LOOK_AT_POINT       = 1,

    // Camera is contrained to a point along the line segment BC.
    // Use these near exits to stop camera movement.
    // Uses: A/B/C as 2D points
    // The target position is found by projecting player position onto BC along a line orthogonal to AB.
    // If posA == posB, AB is ignored and the projection axis will be along a line orthogonal to BC with
    // the resulting position being the closest point on BC to the player.
    // flag 1 = Freeze Camera Position
    CAM_CONTROL_CONSTRAIN_TO_LINE   = 2,

    // Follows the player using whatever yaw value the camera initially possessed.
    CAM_CONTROL_FOLLOW_PLAYER       = 3,

    // Both position and yaw are fixed.
    CAM_CONTROL_FIXED_POS_AND_ORIENTATION       = 4,

    // Look Toward Point, Constrain to Line
    // flag 1 = Freeze Target at Point
    CAM_CONTROL_LOOK_AT_POINT_CONSTAIN_TO_LINE  = 5,

    // Camera position is contrained to a line segment, with yaw perpendicular to the line segment.
    // flag 1 = Disable Forward Motion
    CAM_CONTROL_CONSTAIN_BETWEEN_POINTS         = 6,
};

enum BattleCamPreset {
    BTL_CAM_RESET                           = 0x00,
    BTL_CAM_INTERRUPT                       = 0x01, // forces camera motion to end
    BTL_CAM_DEFAULT                         = 0x02, // wide shot of the entire arena
    BTL_CAM_VIEW_ENEMIES                    = 0x03, // broad focus on enemy side of the field
    BTL_CAM_RETURN_HOME                     = 0x04,
    BTL_CAM_ACTOR_TARGET_MIDPOINT           = 0x05, // focus on midpoint between subject actor and its target
    BTL_CAM_ACTOR_PART                      = 0x06, // unused
    BTL_CAM_ACTOR_GOAL_SIMPLE               = 0x07,
    BTL_CAM_ACTOR_SIMPLE                    = 0x08, // same as BTL_CAM_ACTOR, but does not change boom pitch, yaw, or y-offset
    BTL_CAM_SLOW_DEFAULT                    = 0x09, // unused, same as BTL_CAM_DEFAULT but takes 4x as long
    BTL_CAM_MIDPOINT_CLOSE                  = 0x0A,
    BTL_CAM_MIDPOINT_NORMAL                 = 0x0B,
    BTL_CAM_MIDPOINT_FAR                    = 0x0C, // unused
    BTL_CAM_ACTOR_CLOSE                     = 0x0D, // focus on a targeted actor, closer than normal
    BTL_CAM_ACTOR                           = 0x0E, // focus on a targeted actor using typical distance
    BTL_CAM_ACTOR_FAR                       = 0x0F, // focus on a targeted actor, further away than normal
    BTL_CAM_ACTOR_GOAL_NEAR                 = 0x10, // unused, focus on a targeted actor's goal, closer than normal
    BTL_CAM_ACTOR_GOAL                      = 0x11, // unused, focus on a targeted actor's goal, using typical distance
    BTL_CAM_ACTOR_GOAL_FAR                  = 0x12, // unused, focus on a targeted actor's goal, further away than normal
    BTL_CAM_REPOSITION                      = 0x13, // generic reposition, lerp to target parameters over the next 20 frames
    BTL_CAM_FOLLOW_ACTOR_Y                  = 0x14, // unused
    BTL_CAM_FOLLOW_ACTOR_POS                = 0x15, // unused
    BTL_CAM_PLAYER_ENTRY                    = 0x16,
    BTL_CAM_VICTORY                         = 0x17, // closeup on party while star points are tallied
    BTL_CAM_PLAYER_DIES                     = 0x18, // closeup on player dying
    BTL_CAM_PLAYER_FLEE                     = 0x19, // closeup on player while running away
    BTL_CAM_PLAYER_ATTACK_APPROACH          = 0x1A,
    BTL_CAM_PLAYER_PRE_JUMP_FINISH          = 0x1B,
    BTL_CAM_PLAYER_PRE_ULTRA_JUMP_FINISH    = 0x1C,
    BTL_CAM_PLAYER_MISTAKE                  = 0x1D, // player missed a jump or hammer acion command
    BTL_CAM_PLAYER_HIT_SPIKE                = 0x1E, // player hurt via spike contact
    BTL_CAM_PLAYER_HIT_HAZARD               = 0x1F, // player hurt via burn or shock contact
    BTL_CAM_PLAYER_CHARGE_UP                = 0x20,
    BTL_CAM_PLAYER_STATUS_AFFLICTED         = 0x21,
    BTL_CAM_PLAYER_JUMP_MIDAIR              = 0x22, // move through the air with the player mid-jump
    BTL_CAM_PLAYER_JUMP_FINISH              = 0x23, // after a sucessful action command
    BTL_CAM_PLAYER_JUMP_FINISH_CLOSE        = 0x24, // unused
    BTL_CAM_PLAYER_SUPER_JUMP_MIDAIR        = 0x25, // alternate BTL_CAM_PLAYER_JUMP_MIDAIR associated with an unused script for Super Jump
    BTL_CAM_PLAYER_ULTRA_JUMP_MIDAIR        = 0x26, // alternate BTL_CAM_PLAYER_JUMP_MIDAIR associated with an unused script for Ultra Jump
    BTL_CAM_PLAYER_UNUSED_ULTRA_JUMP        = 0x27, // unused camera for followup hit of unused script for Ultra Jump
    BTL_CAM_PLAYER_MULTIBOUNCE              = 0x28,
    BTL_CAM_PRESET_UNUSED_29                = 0x29, // unused
    BTL_CAM_PRESET_UNUSED_2A                = 0x2A, // unused
    BTL_CAM_PLAYER_AIM_HAMMER               = 0x2B,
    BTL_CAM_PLAYER_HAMMER_STRIKE            = 0x2C,
    BTL_CAM_PRESET_UNUSED_2D                = 0x2D, // unused, alterative to BTL_CAM_PLAYER_HAMMER_QUAKE
    BTL_CAM_PLAYER_HAMMER_QUAKE             = 0x2E, // slowly pan over the enemy side
    BTL_CAM_PARTNER_APPROACH                = 0x2F, // used by Goombario and Watt (power shock only)
    BTL_CAM_CLOSER_PARTNER_APPROACH         = 0x30,
    BTL_CAM_PRESET_UNUSED_31                = 0x31, // unused
    BTL_CAM_GOOMBARIO_BONK_FOLLOWUP_1       = 0x32, // goombario pre-jump 1
    BTL_CAM_PARTNER_MISTAKE                 = 0x33,
    BTL_CAM_PARTNER_MIDAIR                  = 0x34,
    BTL_CAM_GOOMBARIO_BONK_FOLLOWUP_2       = 0x35, // goombario pre-jump 2
    BTL_CAM_PARTNER_INJURED                 = 0x36, // closeup on partner after being injured
    BTL_CAM_PARTNER_GOOMPA                  = 0x37, // focus on Goompa speaking or Goombario charging
    BTL_CAM_PRESET_UNUSED_38                = 0x38, // unused
    BTL_CAM_PRESET_UNUSED_39                = 0x39, // unused
    BTL_CAM_PRESET_UNUSED_3A                = 0x3A, // unused
    BTL_CAM_PARTNER_CLOSE_UP                = 0x3B, // close focus on partner, used when kooper or sushie are charging an attack
    BTL_CAM_PRESET_UNUSED_3C                = 0x3C, // unused
    BTL_CAM_PARTNER_HIT_SPIKE               = 0x3D, // partner hurt via spike contact
    BTL_CAM_PARTNER_HIT_HAZARD              = 0x3E, // partner hurt via burn or shock contact
    BTL_CAM_ENEMY_APPROACH                  = 0x3F, // (very common)
    BTL_CAM_PRESET_UNUSED_40                = 0x40, // unused
    BTL_CAM_SLOWER_DEFAULT                  = 0x41, // unused, same as BTL_CAM_DEFAULT but takes slightly longer
    BTL_CAM_ENEMY_DIVE                      = 0x42, // used just before contact from dive attacks (paragoomba, para jr troopa, etc)
    BTL_CAM_PRESET_UNUSED_43                = 0x43, // unused
    BTL_CAM_PRESET_UNUSED_44                = 0x44, // unused
    BTL_CAM_PLAYER_WISH                     = 0x45, // used for Focus and Star Spirit wishing
    BTL_CAM_PRESET_UNUSED_46                = 0x46, // unused
    BTL_CAM_PRESET_UNUSED_47                = 0x47, // unused
    BTL_CAM_PRESET_UNUSED_48                = 0x48, // unused
    BTL_CAM_STAR_SPIRIT                     = 0x49,
};

enum BattleCamTargetAdjustX {
    BTL_CAM_XADJ_NONE       = 0, // use actor X
    BTL_CAM_XADJ_AVG        = 1, // use average
};

enum BattleCamTargetAdjustY {
    BTL_CAM_YADJ_SLIGHT     = -2, // target y position is weighted 75% actor and 25% target:
    BTL_CAM_YADJ_TARGET     = -1, // use target Y
    BTL_CAM_YADJ_NONE       = 0, // use actor Y
    BTL_CAM_YADJ_AVG        = 1, // target y position is weighted 66% actor and 33% target:
};

enum ModelAnimatorFlags {
    MODEL_ANIMATOR_FLAG_CAM_0             = 0x00000001,
    MODEL_ANIMATOR_FLAG_CAM_1             = 0x00000002,
    MODEL_ANIMATOR_FLAG_CAM_2             = 0x00000004,
    MODEL_ANIMATOR_FLAG_CAM_3             = 0x00000008,
    MODEL_ANIMATOR_FLAG_ENABLED           = 0x00000010,
    MODEL_ANIMATOR_FLAG_20                = 0x00000020,
    MODEL_ANIMATOR_FLAG_UPDATE_PENDING    = 0x00000040,
    MODEL_ANIMATOR_FLAG_HIDDEN            = 0x00000080,
    MODEL_ANIMATOR_FLAG_FLIP_Z            = 0x00000100,
    MODEL_ANIMATOR_FLAG_FLIP_Y            = 0x00000200,
    MODEL_ANIMATOR_FLAG_FLIP_X            = 0x00000400,
    MODEL_ANIMATOR_FLAG_800               = 0x00000800,
    MODEL_ANIMATOR_FLAG_HAS_MODEL         = 0x00001000,
    MODEL_ANIMATOR_FLAG_2000              = 0x00002000,
    MODEL_ANIMATOR_FLAG_4000              = 0x00004000,
    MODEL_ANIMATOR_FLAG_MESH              = 0x00008000,
    MODEL_ANIMATOR_FLAG_CULL_BACK         = 0x00010000,
    MODEL_ANIMATOR_FLAG_NO_FLIP           = 0x00020000,
    MODEL_ANIMATOR_FLAG_FREEZE_ANIMATION  = 0x00040000,
    MODEL_ANIMATOR_FLAG_80000             = 0x00080000,
    MODEL_ANIMATOR_FLAG_100000            = 0x00100000,
    MODEL_ANIMATOR_FLAG_200000            = 0x00200000,
    MODEL_ANIMATOR_FLAG_400000            = 0x00400000,
    MODEL_ANIMATOR_FLAG_800000            = 0x00800000,
    MODEL_ANIMATOR_FLAG_1000000           = 0x01000000,
    MODEL_ANIMATOR_FLAG_2000000           = 0x02000000,
    MODEL_ANIMATOR_FLAG_4000000           = 0x04000000,
    MODEL_ANIMATOR_FLAG_8000000           = 0x08000000,
    MODEL_ANIMATOR_FLAG_10000000          = 0x10000000,
    MODEL_ANIMATOR_FLAG_20000000          = 0x20000000,
    MODEL_ANIMATOR_FLAG_40000000          = 0x40000000,
    MODEL_ANIMATOR_FLAG_80000000          = 0x80000000,
};

enum ShopFlags {
    SHOP_FLAG_SHOWING_ITEM_INFO         = 0x1,
    SHOP_FLAG_INTERACT_SCRIPT_RUNNING   = 0x8,
};

enum {
    SHOP_MSG_BUY_CONFIRM        = 0x00,
    SHOP_MSG_NOT_ENOUGH_COINS   = 0x01,
    SHOP_MSG_NOT_ENOUGH_ROOM    = 0x02,
    SHOP_MSG_BUY_THANK_YOU      = 0x03,
    SHOP_MSG_GREETING           = 0x04,
    SHOP_MSG_INSTRUCTIONS       = 0x05,
    SHOP_MSG_NOTHING_TO_SELL    = 0x06,
    SHOP_MSG_SELL_WHICH         = 0x07,
    SHOP_MSG_SELL_CONFIRM       = 0x08,
    SHOP_MSG_SELL_CANCEL        = 0x09,
    SHOP_MSG_SELL_MORE          = 0x0A,
    SHOP_MSG_SELL_THANKS        = 0x0B,
    SHOP_MSG_NOTHING_TO_CHECK   = 0x0C,
    SHOP_MSG_NO_CHECK_ROOM      = 0x0D,
    SHOP_MSG_CHECK_WHICH        = 0x0E,
    SHOP_MSG_CHECK_ACCEPTED     = 0x0F,
    SHOP_MSG_CHECK_MORE         = 0x10,
    SHOP_MSG_NOTHING_TO_CLAIM   = 0x11,
    SHOP_MSG_NO_CLAIM_ROOM      = 0x12,
    SHOP_MSG_CLAIM_WHICH        = 0x13,
    SHOP_MSG_CLAIM_ACCEPTED     = 0x14,
    SHOP_MSG_CLAIM_MORE         = 0x15,
    SHOP_MSG_FAREWELL           = 0x16,
};

enum {
    SHOP_BUY_RESULT_NOT_ENOUGH_COINS    = 0,
    SHOP_BUY_RESULT_OK                  = 1,
    SHOP_BUY_RESULT_2                   = 2,
    SHOP_BUY_RESULT_CANCEL              = 3,
    SHOP_BUY_RESULT_4                   = 4,
    SHOP_BUY_RESULT_NOT_ENOUGH_ROOM     = 5,
};

enum EncounterFlags {
    ENCOUNTER_FLAG_NONE                 = 0x00000000,
    ENCOUNTER_FLAG_THUMBS_UP            = 0x00000001, ///< Mario will do a 'thumbs up' animation after winning
    ENCOUNTER_FLAG_CANT_SKIP_WIN_DELAY  = 0x00000002,
    ENCOUNTER_FLAG_SKIP_FLEE_DROPS      = 0x00000004,
};

enum WindowFlags {
    WINDOW_FLAG_INITIALIZED             = 0x00000001,
    WINDOW_FLAG_FPUPDATE_CHANGED        = 0x00000002,
    WINDOW_FLAG_HIDDEN                  = 0x00000004, ///< Updated but not rendered
    WINDOW_FLAG_INITIAL_ANIMATION       = 0x00000008,
    WINDOW_FLAG_HAS_CHILDREN            = 0x00000010,
    WINDOW_FLAG_DISABLED                = 0x00000020, ///< Not updated or rendered
    WINDOW_FLAG_40                      = 0x00000040,
};

enum DrawFlags {
    DRAW_FLAG_ROTSCALE                  = 0x00000001,
    DRAW_FLAG_ANIMATED_BACKGROUND       = 0x00000002,
    DRAW_FLAG_NO_CLIP                   = 0x00000004,
    DRAW_FLAG_CULL_BACK                 = 0x00000008,
};

enum EntityModelFlags {
    ENTITY_MODEL_FLAG_CAM0              = 0x00000001,
    ENTITY_MODEL_FLAG_CAM1              = 0x00000002,
    ENTITY_MODEL_FLAG_CAM2              = 0x00000004,
    ENTITY_MODEL_FLAG_CAM3              = 0x00000008,
    ENTITY_MODEL_FLAG_ENABLED           = 0x00000010,
    ENTITY_MODEL_FLAG_HIDDEN            = 0x00000020,
    ENTITY_MODEL_FLAG_40                = 0x00000040,
    ENTITY_MODEL_FLAG_80                = 0x00000080,
    ENTITY_MODEL_FLAG_100               = 0x00000100,
    ENTITY_MODEL_FLAG_REFLECT           = 0x00000200,
    ENTITY_MODEL_FLAG_USE_IMAGE         = 0x00000400,
    ENTITY_MODEL_FLAG_FOG_DISABLED      = 0x00000800,
    ENTITY_MODEL_FLAG_1000              = 0x00001000,
    ENTITY_MODEL_FLAG_2000              = 0x00002000,
    ENTITY_MODEL_FLAG_4000              = 0x00004000,
    ENTITY_MODEL_FLAG_8000              = 0x00008000,
    ENTITY_MODEL_FLAG_10000             = 0x00010000,
    ENTITY_MODEL_FLAG_DISABLE_SCRIPT    = 0x00020000,
    ENTITY_MODEL_FLAG_40000             = 0x00040000,
    ENTITY_MODEL_FLAG_80000             = 0x00080000,
    ENTITY_MODEL_FLAG_100000            = 0x00100000,
    ENTITY_MODEL_FLAG_200000            = 0x00200000,
    ENTITY_MODEL_FLAG_400000            = 0x00400000,
    ENTITY_MODEL_FLAG_800000            = 0x00800000,
    ENTITY_MODEL_FLAG_1000000           = 0x01000000,
    ENTITY_MODEL_FLAG_2000000           = 0x02000000,
    ENTITY_MODEL_FLAG_4000000           = 0x04000000,
    ENTITY_MODEL_FLAG_8000000           = 0x08000000,
    ENTITY_MODEL_FLAG_10000000          = 0x10000000,
    ENTITY_MODEL_FLAG_20000000          = 0x20000000,
    ENTITY_MODEL_FLAG_40000000          = 0x40000000,
    ENTITY_MODEL_FLAG_80000000          = 0x80000000,
};

enum TempSetZoneEnabledFlags {
    TEMP_SET_ZONE_ENABLED_FLAG_1                 = 0x00000001,
    TEMP_SET_ZONE_ENABLED_FLAG_2                 = 0x00000002,
    TEMP_SET_ZONE_ENABLED_FLAG_4                 = 0x00000004,
    TEMP_SET_ZONE_ENABLED_FLAG_8                 = 0x00000008,
    TEMP_SET_ZONE_ENABLED_FLAG_10                = 0x00000010,
    TEMP_SET_ZONE_ENABLED_FLAG_20                = 0x00000020,
    TEMP_SET_ZONE_ENABLED_FLAG_40                = 0x00000040,
    TEMP_SET_ZONE_ENABLED_FLAG_80                = 0x00000080,
    TEMP_SET_ZONE_ENABLED_FLAG_100               = 0x00000100,
    TEMP_SET_ZONE_ENABLED_FLAG_200               = 0x00000200,
    TEMP_SET_ZONE_ENABLED_FLAG_400               = 0x00000400,
    TEMP_SET_ZONE_ENABLED_FLAG_800               = 0x00000800,
    TEMP_SET_ZONE_ENABLED_FLAG_1000              = 0x00001000,
    TEMP_SET_ZONE_ENABLED_FLAG_2000              = 0x00002000,
    TEMP_SET_ZONE_ENABLED_FLAG_4000              = 0x00004000,
    TEMP_SET_ZONE_ENABLED_FLAG_8000              = 0x00008000,
    TEMP_SET_ZONE_ENABLED_FLAG_10000             = 0x00010000,
    TEMP_SET_ZONE_ENABLED_FLAG_20000             = 0x00020000,
    TEMP_SET_ZONE_ENABLED_FLAG_40000             = 0x00040000,
    TEMP_SET_ZONE_ENABLED_FLAG_80000             = 0x00080000,
    TEMP_SET_ZONE_ENABLED_FLAG_100000            = 0x00100000,
    TEMP_SET_ZONE_ENABLED_FLAG_200000            = 0x00200000,
    TEMP_SET_ZONE_ENABLED_FLAG_400000            = 0x00400000,
    TEMP_SET_ZONE_ENABLED_FLAG_800000            = 0x00800000,
    TEMP_SET_ZONE_ENABLED_FLAG_1000000           = 0x01000000,
    TEMP_SET_ZONE_ENABLED_FLAG_2000000           = 0x02000000,
    TEMP_SET_ZONE_ENABLED_FLAG_4000000           = 0x04000000,
    TEMP_SET_ZONE_ENABLED_FLAG_8000000           = 0x08000000,
    TEMP_SET_ZONE_ENABLED_FLAG_10000000          = 0x10000000,
    TEMP_SET_ZONE_ENABLED_FLAG_20000000          = 0x20000000,
    TEMP_SET_ZONE_ENABLED_FLAG_40000000          = 0x40000000,
    TEMP_SET_ZONE_ENABLED_FLAG_80000000          = 0x80000000,
};

enum ModelTransformGroupFlags {
    TRANSFORM_GROUP_FLAG_VALID                  = 0x00000001,
    TRANSFORM_GROUP_FLAG_HIDDEN                 = 0x00000002, // update, but do not render
    TRANSFORM_GROUP_FLAG_INACTIVE               = 0x00000004,
    TRANSFORM_GROUP_FLAG_HAS_TRANSFORM          = 0x00000400,
    TRANSFORM_GROUP_FLAG_MATRIX_DIRTY           = 0x00001000,
    TRANSFORM_GROUP_FLAG_IGNORE_MATRIX          = 0x00002000, // set until dirty matrix has been recalculated
};

enum NpcDropFlags {
    NPC_DROP_FLAG_80                = 0x80,
};

enum ImgFXRenderResult {
    IMGFX_RENDER_RESULT_NO          = 0,
    IMGFX_RENDER_RESULT_DONE        = 1,
    IMGFX_RENDER_RESULT_HOLDING     = 2,
};

enum ImgFXStateFlags {
    IMGFX_FLAG_VALID                = 0x00000001,
    IMGFX_FLAG_G_CULL_BACK          = 0x00000002,
    IMGFX_FLAG_G_CULL_FRONT         = 0x00000004,
    IMGFX_FLAG_UNUSED_A             = 0x00000008, // no remaining effect
    IMGFX_FLAG_SKIP_GFX_SETUP       = 0x00000010,
    IMGFX_FLAG_SKIP_TEX_SETUP       = 0x00000020,
    IMGFX_FLAG_NO_ZBUFFER           = 0x00000040,
    IMGFX_FLAG_LOOP_ANIM            = 0x00000080,
    IMGFX_FLAG_REVERSE_ANIM         = 0x00000100, // fold animation plays backwards (from end to start)
    IMGFX_FLAG_ANIM_INIT            = 0x00000200,
    IMGFX_FLAG_ALPHA_CVG            = 0x00000400,
    IMGFX_FLAG_HOLD_DONE            = 0x00000800, // hold on the final frame when finished, prevents auto-disposal
    IMGFX_FLAG_ANIM_DONE            = 0x00001000,
    IMGFX_FLAG_USE_LIGHTING         = 0x00002000,
    IMGFX_FLAG_HOLDING              = 0x00004000,
    IMGFX_FLAG_UNUSED_B             = 0x00008000,
    IMGFX_FLAG_NO_FILTERING         = 0x00010000,
    IMGFX_FLAG_FORCE_CLEAR          = 0x00020000,
    IMGFX_FLAG_UNUSED_C             = 0x00040000,
    IMGFX_FLAG_AS_SPRITE            = 0x00080000,
    IMGFX_FLAG_SPRITE_SHADING       = 0x00100000, // allow sprite shading, even if for a non-sprite imgfx
};

typedef enum ImgFXType {
    IMGFX_CLEAR                     = 0x0,
    IMGFX_UNK_1                     = 0x1,    // unused?
    IMGFX_UNK_2                     = 0x2,    // unused?
    IMGFX_RESET                     = 0x3,    // after goomba 'sticker' ambush in kmr_09 unfurls. might be to force-terminate ANIM.
    IMGFX_SET_WAVY                  = 0x4,    // Kolorado when injured and Sushie when underwater (* note: Sushie fold rendering is bugged and only occurs *before* going underwater)
    IMGFX_SET_ANIM                  = 0x5,
    IMGFX_SET_COLOR                 = 0x6,    // modulate color (args: R, G, B)
    IMGFX_SET_ALPHA                 = 0x7,    // modulate alpha (args: A)
    IMGFX_SET_TINT                  = 0x8,    // modulate color+alpha (args: R, G, B, A)
    IMGFX_SET_WHITE_FADE            = 0x9,
    IMGFX_SET_CREDITS_FADE          = 0xA,
    IMGFX_COLOR_BUF_SET_MULTIPLY    = 0xB,
    IMGFX_COLOR_BUF_SET_MODULATE    = 0xC,    // used for color cycling on Monstar's outline
    IMGFX_HOLOGRAM                  = 0xD,    // ghostly star spirits and merlar (args: ???, staticAmt, ???, alphaAmt)
    IMGFX_FILL_COLOR                = 0xE,    // used to create boss silhouettes in chapter introduction sceens
    IMGFX_OVERLAY                   = 0xF,
    IMGFX_OVERLAY_XLU               = 0x10,   // unused?
    IMGFX_ALLOC_COLOR_BUF           = 0x11,   // (args: count) creates buffer to set color of 'count' vertices
} ImgFXType;

typedef enum ImgFXAnim {
    IMGFX_ANIM_SHOCK                   = 0x00, // used for Goombaria and Goompapa when Kammy drops the hammer block
    IMGFX_ANIM_SHIVER                  = 0x01, // used when Goombaria gives Mario a kiss
    IMGFX_ANIM_VERTICAL_PIPE_CURL      = 0x02, // vertical pipe curl
    IMGFX_ANIM_HORIZONTAL_PIPE_CURL    = 0x03, // horizontal pipe curl
    IMGFX_ANIM_STARTLE                 = 0x04, // used when Koopa Bros are surprised by Mario
    IMGFX_ANIM_FLUTTER_DOWN            = 0x05, // player falling like paper
    IMGFX_ANIM_UNFURL                  = 0x06, // used by Goomba 'stickers' that ambush Mario in area_kmr
    IMGFX_ANIM_GET_IN_BED              = 0x07, // Mario gets into bed
    IMGFX_ANIM_SPIRIT_CAPTURE          = 0x08, // Eldstar being captured
    IMGFX_ANIM_UNUSED_1                = 0x09, // unused
    IMGFX_ANIM_UNUSED_2                = 0x0A, // unused
    IMGFX_ANIM_UNUSED_3                = 0x0B, // unused
    IMGFX_ANIM_TUTANKOOPA_GATHER       = 0x0C, // tutankoopa 3
    IMGFX_ANIM_TUTANKOOPA_SWIRL_2      = 0x0D, // tutankoopa 2
    IMGFX_ANIM_TUTANKOOPA_SWIRL_1      = 0x0E, // tutankoopa 1
    IMGFX_ANIM_SHUFFLE_CARDS           = 0x0F, // merlee spell-casting card shuffle
    IMGFX_ANIM_FLIP_CARD_1             = 0x10, // merlee spell-casting card flip 1
    IMGFX_ANIM_FLIP_CARD_2             = 0x11, // merlee spell-casting card flip 2
    IMGFX_ANIM_FLIP_CARD_3             = 0x12, // merlee spell-casting card flip 3
    IMGFX_ANIM_CYMBAL_CRUSH            = 0x13, // used when Mario is crushed in a Cymbal Plant
} ImgFXAnim;

typedef enum ImgFXRenderType {
    IMGFX_RENDER_DEFAULT               = 0x00,
    IMGFX_RENDER_MULTIPLY_RGB          = 0x01,
    IMGFX_RENDER_MULTIPLY_ALPHA        = 0x02,
    IMGFX_RENDER_MULTIPLY_RGBA         = 0x03,
    IMGFX_RENDER_MODULATE_PRIM_RGB     = 0x04,
    IMGFX_RENDER_MODULATE_PRIM_RGBA    = 0x05,
    IMGFX_RENDER_MULTIPLY_SHADE_RGB    = 0x06,
    IMGFX_RENDER_MULTIPLY_SHADE_ALPHA  = 0x07,
    IMGFX_RENDER_MULTIPLY_SHADE_RGBA   = 0x08,
    IMGFX_RENDER_MODULATE_SHADE_RGB    = 0x09,
    IMGFX_RENDER_MODULATE_SHADE_RGBA   = 0x0A,
    IMGFX_RENDER_ANIM                  = 0x0B,
    IMGFX_RENDER_HOLOGRAM              = 0x0C,
    IMGFX_RENDER_COLOR_FILL            = 0x0D,
    IMGFX_RENDER_OVERLAY_RGB           = 0x0E,
    IMGFX_RENDER_OVERLAY_RGBA          = 0x0F,
    IMGFX_RENDER_UNUSED                = 0x10,
} ImgFXRenderType;

enum ImgFXRenderModeFlags {
    IMGFX_RENDER_NO_OVERRIDE      = 1,
};

typedef enum ImgFXMeshType {
    IMGFX_MESH_DEFAULT                 = 0x0,
    IMGFX_MESH_GRID_WAVY               = 0x1,
    IMGFX_MESH_ANIMATED                = 0x2,
    IMGFX_MESH_GRID_UNUSED             = 0x3,
    IMGFX_MESH_STRIP                   = 0x4,
} ImgFXMeshType;

enum ImgFXHologramTypes {
    IMGFX_HOLOGRAM_NOISE               = 0,
    IMGFX_HOLOGRAM_DITHER              = 1,
    IMGFX_HOLOGRAM_THRESHOLD           = 2,
};

enum SpriteCompImgFXFlags {
    SPR_IMGFX_FLAG_ENABLED              = 0x10000000, // when set, sprites will render through ImgFx
    SPR_IMGFX_FLAG_MASK                 = 0xF0000000,
};

enum SpriteShadingFlags {
    SPR_SHADING_FLAG_ENABLED            = 1,
    SPR_SHADING_FLAG_SET_VIEWPORT       = 2, // never set
};

enum MoveType {
    MOVE_TYPE_NONE          = 0,
    MOVE_TYPE_HAMMER        = 1,
    MOVE_TYPE_JUMP          = 2,
    MOVE_TYPE_3             = 3,
    MOVE_TYPE_ITEMS         = 4,
    MOVE_TYPE_SWITCH        = 5,
    MOVE_TYPE_6             = 6,
    MOVE_TYPE_ATTACK_UP     = 7,
    MOVE_TYPE_DEFENSE_UP    = 8,
    MOVE_TYPE_9             = 9,
    MOVE_TYPE_STAR_POWER    = 10,
    MOVE_TYPE_PARTNER       = 11
};

enum BattleMenuStatus {
    BATTLE_SUBMENU_STATUS_ENABLED           = 1,
    BATTLE_SUBMENU_STATUS_NOT_ENOUGH_FP     = 0,
    BATTLE_SUBMENU_STATUS_NO_TARGETS        = -1,
    BATTLE_SUBMENU_STATUS_NO_TARGETS_2      = -2, // TODO: determine difference, probably uses a different error message
};

enum DictionaryIndex {
    DICTIONARY_KEY   = 0,
    DICTIONARY_VALUE = 1,
    DICTIONARY_SIZE,
};

enum WindowID {
    WIN_NONE                                = -1,
    WIN_UNUSED_0                            = 0,
    WIN_BTL_MOVES_MENU                      = 1,
    WIN_BTL_MOVES_TITLE                     = 2,
    WIN_BTL_MOVES_ICON                      = 3,
    WIN_BTL_SPIRITS_TITLE                   = 4,
    WIN_BTL_SPIRITS_ICON                    = 5,
    WIN_BTL_STRATS_MENU                     = 6,
    WIN_BTL_STRATS_TITLE                    = 7,
    WIN_BTL_DESC_BOX                        = 8, // strats and level up menus
    WIN_BTL_POPUP                           = 9,
    WIN_SHOP_ITEM_NAME                      = 10,
    WIN_SHOP_ITEM_DESC                      = 11,
    WIN_PICKUP_HEADER                       = 12,
    WIN_UNUSED_13                           = 13, // unused
    WIN_POPUP_CONTENT                       = 14,
    WIN_POPUP_TITLE_A                       = 15,
    WIN_POPUP_COST                          = 16,
    WIN_POPUP_TITLE_B                       = 17, // brown box used for "Throw away an item" and certain popup titles
    WIN_PARTNER_COST                        = 18,
    WIN_POPUP_DESC                          = 19,
    WIN_CURRENCY_COUNTER                    = 20,
    WIN_POPUP_PROMPT                        = 21,
    WIN_PAUSE_MAIN                          = 22,
    WIN_PAUSE_DECRIPTION                    = 23,
    WIN_FILES_CURSOR                        = 23, // same as previous
    WIN_PAUSE_TUTORIAL                      = 24,
    WIN_FILES_COPYARROW                     = 24, // same as previous
    WIN_PAUSE_TAB_STATS                     = 25,
    WIN_PAUSE_TAB_BADGES                    = 26,
    WIN_PAUSE_TAB_ITEMS                     = 27,
    WIN_PAUSE_TAB_PARTY                     = 28,
    WIN_PAUSE_TAB_SPIRITS                   = 29,
    WIN_PAUSE_TAB_MAP                       = 30,
    WIN_PAUSE_STATS                         = 31,
    WIN_PAUSE_BADGES                        = 32,
    WIN_PAUSE_ITEMS                         = 33,
    WIN_PAUSE_PARTNERS                      = 34,
    WIN_PAUSE_PARTNERS_TITLE                = 35,
    WIN_PAUSE_PARTNERS_MOVELIST             = 36,
    WIN_PAUSE_PARTNERS_MOVELIST_TITLE       = 37,
    WIN_PAUSE_PARTNERS_MOVELIST_FLOWER      = 38,
    WIN_PAUSE_SPIRITS                       = 39,
    WIN_PAUSE_SPIRITS_TITLE                 = 40,
    WIN_PAUSE_MAP                           = 41,
    WIN_PAUSE_MAP_TITLE                     = 42,
    WIN_PAUSE_TAB_INVIS                     = 43,
    WIN_PAUSE_CURSOR                        = 44,
    WIN_FILES_MAIN                          = 44, // same as previous
    WIN_FILES_TITLE                         = 45,
    WIN_FILES_CONFIRM_PROMPT                = 46,
    WIN_FILES_MESSAGE                       = 47,
    WIN_FILES_INPUT_FIELD                   = 48,
    WIN_FILES_INPUT_KEYBOARD                = 49,
    WIN_FILES_CONFIRM_OPTIONS               = 50,
    WIN_FILES_STEREO                        = 51,
    WIN_FILES_MONO                          = 52,
    WIN_FILES_OPTION_LEFT                   = 53,
    WIN_FILES_OPTION_CENTER                 = 54,
    WIN_FILES_OPTION_RIGHT                  = 55,
    WIN_FILES_SLOT1_BODY                    = 56,
    WIN_FILES_SLOT2_BODY                    = 57,
    WIN_FILES_SLOT3_BODY                    = 58,
    WIN_FILES_SLOT4_BODY                    = 59,
    WIN_FILES_SLOT1_TITLE                   = 60,
    WIN_FILES_SLOT2_TITLE                   = 61,
    WIN_FILES_SLOT3_TITLE                   = 62,
    WIN_FILES_SLOT4_TITLE                   = 63,
};

enum SimpleWindowUpdateID {
    WINDOW_UPDATE_SHOW              = 1,
    WINDOW_UPDATE_HIDE              = 2,
    WINDOW_UPDATE_HIER_UPDATE       = 3,
    WINDOW_UPDATE_DARKENED          = 4,
    WINDOW_UPDATE_TRANSPARENT       = 5,
    WINDOW_UPDATE_OPAQUE            = 6,
    WINDOW_UPDATE_SHOW_TRANSPARENT  = 7,
    WINDOW_UPDATE_SHOW_DARKENED     = 8,
    WINDOW_UPDATE_9                 = 9,
};

enum WindowGroups {
    WINDOW_GROUP_ALL = 0,
    WINDOW_GROUP_BATTLE = 1,
    WINDOW_GROUP_PAUSE = 2,
    WINDOW_GROUP_FILES = 3,
};

enum RushFlags {
    RUSH_FLAG_NONE  = 0,
    RUSH_FLAG_MEGA  = 1,
    RUSH_FLAG_POWER = 2,
};

enum FileMenuMessages {
    /*  0 */ FILE_MESSAGE_NONE,
    /*  1 */ FILE_MESSAGE_SELECT_FILE_TO_START,        // Select file to start:[End]
    /*  2 */ FILE_MESSAGE_SELECT_FILE_TO_DELETE,       // Select file to delete:[End]
#if !VERSION_PAL
    /*  3 */ FILE_MESSAGE_SELECT_FILE_TO_SAVE,         // Select file to save[End]
#endif
    /*  4 */ FILE_MESSAGE_COPY_WHICH_FILE,             // Copy which file?[End]
    /*  5 */ FILE_MESSAGE_COPY_TO_WHICH_FILE,          // Copy to which file?[End]
    /*  6 */ FILE_MESSAGE_NEW,                         // NEW[End]
    /*  7 */ FILE_MESSAGE_LEVEL,                       // Level[End]
    /*  8 */ FILE_MESSAGE_PLAY_TIME,                   // Play Time[End]
    /*  9 */ FILE_MESSAGE_DELETE_FILE,                 // Delete File[End]
    /* 10 */ FILE_MESSAGE_CANCEL,                      // Cancel[End]
    /* 11 */ FILE_MESSAGE_COPY_FILE,                   // Copy File[End]
    /* 12 */ FILE_MESSAGE_FIRST_PLAY,                  // First Play[End]
    /* 13 */ FILE_MESSAGE_PERIOD_13,                   // .[End]
    /* 14 */ FILE_MESSAGE_YES,                         // Yes[End]
    /* 15 */ FILE_MESSAGE_NO,                          // No[End]
    /* 16 */ FILE_MESSAGE_DELETE,                      // Delete[End]
    /* 17 */ FILE_MESSAGE_OVERRIDE_TO_NEW_DATA,        // Override to New Data[End]
    /* 18 */ FILE_MESSAGE_SAVE_OK,                     // Save OK?[End]
    /* 19 */ FILE_MESSAGE_FILE_NAME_IS,                // File name is :[End]
    /* 20 */ FILE_MESSAGE_PERIOD_20,                   // .[End]
    /* 21 */ FILE_MESSAGE_OK,                          // OK?[End]
    /* 22 */ FILE_MESSAGE_FILE_22,                     // File[End]
    /* 23 */ FILE_MESSAGE_WILL_BE_DELETED,             // will be deleted.[End]
    /* 24 */ FILE_MESSAGE_OK_TO_COPY_TO_THIS_FILE,     // OK to copy to this file?[End]
    /* 25 */ FILE_MESSAGE_START_GAME_WITH,             // Start game with[End]
    /* 26 */ FILE_MESSAGE_FILE_26,                     // File[End]
    /* 27 */ FILE_MESSAGE_HAS_BEEN_DELETED,            // has been deleted.[End]
    /* 28 */ FILE_MESSAGE_28,                          // [End]
    /* 29 */ FILE_MESSAGE_COPY_FROM,                   // Copy from[End]
    /* 30 */ FILE_MESSAGE_TO,                          // to[End]
    /* 31 */ FILE_MESSAGE_HAS_BEEN_CREATED,            // has been created.[End]
#if VERSION_PAL
    // TODO: determine where these new entries should be placed
    FILE_MESSAGE_PAL_UNK1,
    FILE_MESSAGE_PAL_UNK2,
#endif
    /* 32 */ FILE_MESSAGE_ENTER_A_FILE_NAME,           // Enter a file name![End]
    /* 33 */ FILE_MESSAGE_QUESTION,                    // ?[End]
    /* 34 */ FILE_MESSAGE_PERIOD_34,                   // .[End]
#if VERSION_PAL
    FILE_MESSAGE_PAL_UNK3,
#endif
};

// specifically used with draw_msg, not to be confused with MsgStyles
enum DrawMsgStyleFlags {
    DRAW_MSG_STYLE_MENU             = 1, // slightly higher baseline with smaller fullspace widths
    DRAW_MSG_STYLE_WAVY             = 2,
    DRAW_MSG_STYLE_RAINBOW          = 4,
    DRAW_MSG_STYLE_DROP_SHADOW      = 8,
};

// used with draw_number
enum DrawNumberStyleFlags {
    DRAW_NUMBER_STYLE_ALIGN_RIGHT       = 1, ///< drawn to the left of posX
    DRAW_NUMBER_STYLE_MONOSPACE         = 2,
    DRAW_NUMBER_STYLE_MONOSPACE_RIGHT   = 3, // combination of MONOSPACE and ALIGN_RIGHT
    DRAW_NUMBER_STYLE_DROP_SHADOW       = 4,
};

enum DrawNumberCharsets {
    DRAW_NUMBER_CHARSET_NORMAL = 0,
    DRAW_NUMBER_CHARSET_THIN   = 1,
};

enum MsgPalettes {
    MSG_PAL_WHITE                   = 0x00,
    MSG_PAL_TEAL                    = 0x01,
    MSG_PAL_BLUE                    = 0x02,
    MSG_PAL_GREEN                   = 0x03,
    MSG_PAL_LIME                    = 0x04,
    MSG_PAL_YELLOW                  = 0x05,
    MSG_PAL_ORANGE                  = 0x06,
    MSG_PAL_RED                     = 0x07,
    MSG_PAL_PURPLE                  = 0x08,
    MSG_PAL_PINK                    = 0x09,
    MSG_PAL_STANDARD                = 0x0A,
    MSG_PAL_0B                      = 0x0B,
    MSG_PAL_0C                      = 0x0C,
    MSG_PAL_0D                      = 0x0D,
    MSG_PAL_0E                      = 0x0E,
    MSG_PAL_0F                      = 0x0F,
    MSG_PAL_10                      = 0x10,
    MSG_PAL_11                      = 0x11,
    MSG_PAL_12                      = 0x12,
    MSG_PAL_13                      = 0x13,
    MSG_PAL_14                      = 0x14,
    MSG_PAL_15                      = 0x15,
    MSG_PAL_16                      = 0x16,
    MSG_PAL_17                      = 0x17,
    MSG_PAL_18                      = 0x18,
    MSG_PAL_19                      = 0x19,
    MSG_PAL_1A                      = 0x1A,
    MSG_PAL_1B                      = 0x1B,
    MSG_PAL_1C                      = 0x1C,
    MSG_PAL_1D                      = 0x1D,
    MSG_PAL_1E                      = 0x1E,
    MSG_PAL_1F                      = 0x1F,
    MSG_PAL_20                      = 0x20,
    MSG_PAL_21                      = 0x21,
    MSG_PAL_22                      = 0x22,
    MSG_PAL_23                      = 0x23,
    MSG_PAL_24                      = 0x24,
    MSG_PAL_25                      = 0x25,
    MSG_PAL_26                      = 0x26,
    MSG_PAL_27                      = 0x27,
    MSG_PAL_28                      = 0x28,
    MSG_PAL_29                      = 0x29,
    MSG_PAL_2A                      = 0x2A,
    MSG_PAL_2B                      = 0x2B,
    MSG_PAL_2C                      = 0x2C,
    MSG_PAL_2D                      = 0x2D,
    MSG_PAL_2E                      = 0x2E,
    MSG_PAL_2F                      = 0x2F,
    MSG_PAL_30                      = 0x30,
    MSG_PAL_31                      = 0x31,
    MSG_PAL_32                      = 0x32,
    MSG_PAL_33                      = 0x33,
    MSG_PAL_34                      = 0x34,
    MSG_PAL_35                      = 0x35,
    MSG_PAL_36                      = 0x36,
    MSG_PAL_37                      = 0x37,
    MSG_PAL_38                      = 0x38,
    MSG_PAL_39                      = 0x39,
    MSG_PAL_3A                      = 0x3A,
    MSG_PAL_3B                      = 0x3B,
    MSG_PAL_3C                      = 0x3C,
    MSG_PAL_3D                      = 0x3D,
    MSG_PAL_3E                      = 0x3E,
    MSG_PAL_3F                      = 0x3F,
    MSG_PAL_40                      = 0x40,
    MSG_PAL_41                      = 0x41,
    MSG_PAL_42                      = 0x42,
    MSG_PAL_43                      = 0x43,
    MSG_PAL_44                      = 0x44,
    MSG_PAL_45                      = 0x45,
    MSG_PAL_46                      = 0x46,
    MSG_PAL_47                      = 0x47,
    MSG_PAL_48                      = 0x48,
    MSG_PAL_49                      = 0x49,
    MSG_PAL_4A                      = 0x4A,
    MSG_PAL_4B                      = 0x4B,
    MSG_PAL_4C                      = 0x4C,
    MSG_PAL_4D                      = 0x4D,
    MSG_PAL_4E                      = 0x4E,
    MSG_PAL_4F                      = 0x4F,
    MSG_PAL_50                      = 0x50
};

enum MsgChars {
#if VERSION_JP
    // Variant 0 - Hiragana, Katakana, Numeric, Fullwidth Symbols
    MSG_CHAR_HIRAGANA_A             = 0x00,
    MSG_CHAR_HIRAGANA_I             = 0x01,
    MSG_CHAR_HIRAGANA_U             = 0x02,
    MSG_CHAR_HIRAGANA_E             = 0x03,
    MSG_CHAR_HIRAGANA_O             = 0x04,
    MSG_CHAR_HIRAGANA_KA            = 0x05,
    MSG_CHAR_HIRAGANA_KI            = 0x06,
    MSG_CHAR_HIRAGANA_KU            = 0x07,
    MSG_CHAR_HIRAGANA_KE            = 0x08,
    MSG_CHAR_HIRAGANA_KO            = 0x09,
    MSG_CHAR_HIRAGANA_SA            = 0x0A,
    MSG_CHAR_HIRAGANA_SI            = 0x0B,
    MSG_CHAR_HIRAGANA_SU            = 0x0C,
    MSG_CHAR_HIRAGANA_SE            = 0x0D,
    MSG_CHAR_HIRAGANA_SO            = 0x0E,
    MSG_CHAR_HIRAGANA_TA            = 0x0F,
    MSG_CHAR_HIRAGANA_TI            = 0x10,
    MSG_CHAR_HIRAGANA_TU            = 0x11,
    MSG_CHAR_HIRAGANA_TE            = 0x12,
    MSG_CHAR_HIRAGANA_TO            = 0x13,
    MSG_CHAR_HIRAGANA_NA            = 0x14,
    MSG_CHAR_HIRAGANA_NI            = 0x15,
    MSG_CHAR_HIRAGANA_NU            = 0x16,
    MSG_CHAR_HIRAGANA_NE            = 0x17,
    MSG_CHAR_HIRAGANA_NO            = 0x18,
    MSG_CHAR_HIRAGANA_HA            = 0x19,
    MSG_CHAR_HIRAGANA_HI            = 0x1A,
    MSG_CHAR_HIRAGANA_HU            = 0x1B,
    MSG_CHAR_HIRAGANA_HE            = 0x1C,
    MSG_CHAR_HIRAGANA_HO            = 0x1D,
    MSG_CHAR_HIRAGANA_MA            = 0x1E,
    MSG_CHAR_HIRAGANA_MI            = 0x1F,
    MSG_CHAR_HIRAGANA_MU            = 0x20,
    MSG_CHAR_HIRAGANA_ME            = 0x21,
    MSG_CHAR_HIRAGANA_MO            = 0x22,
    MSG_CHAR_HIRAGANA_YA            = 0x23,
    MSG_CHAR_HIRAGANA_YU            = 0x24,
    MSG_CHAR_HIRAGANA_YO            = 0x25,
    MSG_CHAR_HIRAGANA_RA            = 0x26,
    MSG_CHAR_HIRAGANA_RI            = 0x27,
    MSG_CHAR_HIRAGANA_RU            = 0x28,
    MSG_CHAR_HIRAGANA_RE            = 0x29,
    MSG_CHAR_HIRAGANA_RO            = 0x2A,
    MSG_CHAR_HIRAGANA_WA            = 0x2B,
    MSG_CHAR_HIRAGANA_WO            = 0x2C,
    MSG_CHAR_HIRAGANA_N             = 0x2D,
    MSG_CHAR_HIRAGANA_VU            = 0x2E,
    MSG_CHAR_HIRAGANA_GA            = 0x2F,
    MSG_CHAR_HIRAGANA_GI            = 0x30,
    MSG_CHAR_HIRAGANA_GU            = 0x31,
    MSG_CHAR_HIRAGANA_GE            = 0x32,
    MSG_CHAR_HIRAGANA_GO            = 0x33,
    MSG_CHAR_HIRAGANA_ZA            = 0x34,
    MSG_CHAR_HIRAGANA_ZI            = 0x35,
    MSG_CHAR_HIRAGANA_ZU            = 0x36,
    MSG_CHAR_HIRAGANA_ZE            = 0x37,
    MSG_CHAR_HIRAGANA_ZO            = 0x38,
    MSG_CHAR_HIRAGANA_DA            = 0x39,
    MSG_CHAR_HIRAGANA_DI            = 0x3A,
    MSG_CHAR_HIRAGANA_DU            = 0x3B,
    MSG_CHAR_HIRAGANA_DE            = 0x3C,
    MSG_CHAR_HIRAGANA_DO            = 0x3D,
    MSG_CHAR_HIRAGANA_BA            = 0x3E,
    MSG_CHAR_HIRAGANA_BI            = 0x3F,
    MSG_CHAR_HIRAGANA_BU            = 0x40,
    MSG_CHAR_HIRAGANA_BE            = 0x41,
    MSG_CHAR_HIRAGANA_BO            = 0x42,
    MSG_CHAR_HIRAGANA_PA            = 0x43,
    MSG_CHAR_HIRAGANA_PI            = 0x44,
    MSG_CHAR_HIRAGANA_PU            = 0x45,
    MSG_CHAR_HIRAGANA_PE            = 0x46,
    MSG_CHAR_HIRAGANA_PO            = 0x47,
    MSG_CHAR_HIRAGANA_SMALL_A       = 0x48,
    MSG_CHAR_HIRAGANA_SMALL_I       = 0x49,
    MSG_CHAR_HIRAGANA_SMALL_U       = 0x4A,
    MSG_CHAR_HIRAGANA_SMALL_E       = 0x4B,
    MSG_CHAR_HIRAGANA_SMALL_O       = 0x4C,
    MSG_CHAR_HIRAGANA_SMALL_TU      = 0x4D,
    MSG_CHAR_HIRAGANA_SMALL_YA      = 0x4E,
    MSG_CHAR_HIRAGANA_SMALL_YU      = 0x4F,
    MSG_CHAR_HIRAGANA_SMALL_YO      = 0x50,
    MSG_CHAR_KATAKANA_A             = 0x51,
    MSG_CHAR_KATAKANA_I             = 0x52,
    MSG_CHAR_KATAKANA_U             = 0x53,
    MSG_CHAR_KATAKANA_E             = 0x54,
    MSG_CHAR_KATAKANA_O             = 0x55,
    MSG_CHAR_KATAKANA_KA            = 0x56,
    MSG_CHAR_KATAKANA_KI            = 0x57,
    MSG_CHAR_KATAKANA_KU            = 0x58,
    MSG_CHAR_KATAKANA_KE            = 0x59,
    MSG_CHAR_KATAKANA_KO            = 0x5A,
    MSG_CHAR_KATAKANA_SA            = 0x5B,
    MSG_CHAR_KATAKANA_SI            = 0x5C,
    MSG_CHAR_KATAKANA_SU            = 0x5D,
    MSG_CHAR_KATAKANA_SE            = 0x5E,
    MSG_CHAR_KATAKANA_SO            = 0x5F,
    MSG_CHAR_KATAKANA_TA            = 0x60,
    MSG_CHAR_KATAKANA_TI            = 0x61,
    MSG_CHAR_KATAKANA_TU            = 0x62,
    MSG_CHAR_KATAKANA_TE            = 0x63,
    MSG_CHAR_KATAKANA_TO            = 0x64,
    MSG_CHAR_KATAKANA_NA            = 0x65,
    MSG_CHAR_KATAKANA_NI            = 0x66,
    MSG_CHAR_KATAKANA_NU            = 0x67,
    MSG_CHAR_KATAKANA_NE            = 0x68,
    MSG_CHAR_KATAKANA_NO            = 0x69,
    MSG_CHAR_KATAKANA_HA            = 0x6A,
    MSG_CHAR_KATAKANA_HI            = 0x6B,
    MSG_CHAR_KATAKANA_HU            = 0x6C,
    MSG_CHAR_KATAKANA_HE            = 0x6D,
    MSG_CHAR_KATAKANA_HO            = 0x6E,
    MSG_CHAR_KATAKANA_MA            = 0x6F,
    MSG_CHAR_KATAKANA_MI            = 0x70,
    MSG_CHAR_KATAKANA_MU            = 0x71,
    MSG_CHAR_KATAKANA_ME            = 0x72,
    MSG_CHAR_KATAKANA_MO            = 0x73,
    MSG_CHAR_KATAKANA_YA            = 0x74,
    MSG_CHAR_KATAKANA_YU            = 0x75,
    MSG_CHAR_KATAKANA_YO            = 0x76,
    MSG_CHAR_KATAKANA_RA            = 0x77,
    MSG_CHAR_KATAKANA_RI            = 0x78,
    MSG_CHAR_KATAKANA_RU            = 0x79,
    MSG_CHAR_KATAKANA_RE            = 0x7A,
    MSG_CHAR_KATAKANA_RO            = 0x7B,
    MSG_CHAR_KATAKANA_WA            = 0x7C,
    MSG_CHAR_KATAKANA_WO            = 0x7D,
    MSG_CHAR_KATAKANA_N             = 0x7E,
    MSG_CHAR_KATAKANA_VU            = 0x7F,
    MSG_CHAR_KATAKANA_GA            = 0x80,
    MSG_CHAR_KATAKANA_GI            = 0x81,
    MSG_CHAR_KATAKANA_GU            = 0x82,
    MSG_CHAR_KATAKANA_GE            = 0x83,
    MSG_CHAR_KATAKANA_GO            = 0x84,
    MSG_CHAR_KATAKANA_ZA            = 0x85,
    MSG_CHAR_KATAKANA_ZI            = 0x86,
    MSG_CHAR_KATAKANA_ZU            = 0x87,
    MSG_CHAR_KATAKANA_ZE            = 0x88,
    MSG_CHAR_KATAKANA_ZO            = 0x89,
    MSG_CHAR_KATAKANA_DA            = 0x8A,
    MSG_CHAR_KATAKANA_DI            = 0x8B,
    MSG_CHAR_KATAKANA_DU            = 0x8C,
    MSG_CHAR_KATAKANA_DE            = 0x8D,
    MSG_CHAR_KATAKANA_DO            = 0x8E,
    MSG_CHAR_KATAKANA_BA            = 0x8F,
    MSG_CHAR_KATAKANA_BI            = 0x90,
    MSG_CHAR_KATAKANA_BU            = 0x91,
    MSG_CHAR_KATAKANA_BE            = 0x92,
    MSG_CHAR_KATAKANA_BO            = 0x93,
    MSG_CHAR_KATAKANA_PA            = 0x94,
    MSG_CHAR_KATAKANA_PI            = 0x95,
    MSG_CHAR_KATAKANA_PU            = 0x96,
    MSG_CHAR_KATAKANA_PE            = 0x97,
    MSG_CHAR_KATAKANA_PO            = 0x98,
    MSG_CHAR_KATAKANA_SMALL_A       = 0x99,
    MSG_CHAR_KATAKANA_SMALL_I       = 0x9A,
    MSG_CHAR_KATAKANA_SMALL_U       = 0x9B,
    MSG_CHAR_KATAKANA_SMALL_E       = 0x9C,
    MSG_CHAR_KATAKANA_SMALL_O       = 0x9D,
    MSG_CHAR_KATAKANA_SMALL_TU      = 0x9E,
    MSG_CHAR_KATAKANA_SMALL_YA      = 0x9F,
    MSG_CHAR_KATAKANA_SMALL_YU      = 0xA0,
    MSG_CHAR_KATAKANA_SMALL_YO      = 0xA1,
    MSG_CHAR_PROLONGED_SOUND        = 0xA2,
    MSG_CHAR_TILDE                  = 0xA3,
    MSG_CHAR_LONGDASH_0             = 0xA4,
    MSG_CHAR_LONGDASH_1             = 0xA5,
    MSG_CHAR_LONGDASH_2             = 0xA6,
    MSG_CHAR_DIGIT_0                = 0xA7,
    MSG_CHAR_DIGIT_1                = 0xA8,
    MSG_CHAR_DIGIT_2                = 0xA9,
    MSG_CHAR_DIGIT_3                = 0xAA,
    MSG_CHAR_DIGIT_4                = 0xAB,
    MSG_CHAR_DIGIT_5                = 0xAC,
    MSG_CHAR_DIGIT_6                = 0xAD,
    MSG_CHAR_DIGIT_7                = 0xAE,
    MSG_CHAR_DIGIT_8                = 0xAF,
    MSG_CHAR_DIGIT_9                = 0xB0,
    MSG_CHAR_UP                     = 0xB1,
    MSG_CHAR_DOWN                   = 0xB2,
    MSG_CHAR_LEFT                   = 0xB3,
    MSG_CHAR_RIGHT                  = 0xB4,
    MSG_CHAR_EXCLAMATION            = 0xB5,
    MSG_CHAR_QUESTION               = 0xB6,
    MSG_CHAR_PLUS                   = 0xB7,
    MSG_CHAR_MINUS                  = 0xB8,
    MSG_CHAR_FORWARDSLASH           = 0xB9,
    MSG_CHAR_PERIOD                 = 0xBA,
    MSG_CHAR_AND                    = 0xBB,
    MSG_CHAR_HASH                   = 0xBC,
    MSG_CHAR_HEART                  = 0xBD,
    MSG_CHAR_STAR                   = 0xBE,
    MSG_CHAR_LPAREN                 = 0xBF,
    MSG_CHAR_RPAREN                 = 0xC0,
    MSG_CHAR_TLBRACKET              = 0xC1,
    MSG_CHAR_BRBRACKET              = 0xC2,
    MSG_CHAR_MIDDLE_DOT             = 0xC3,
    MSG_CHAR_HIRAGANA_SMALL_N       = 0xC4,
    MSG_CHAR_KATAKANA_SMALL_N       = 0xC5,
    MSG_CHAR_KANJI_C6               = 0xC6,
    MSG_CHAR_KANJI_C7               = 0xC7,

    // Variant 1 - Latin Alphabet
    MSG_CHAR_UPPER_A                = 0x00,
    MSG_CHAR_UPPER_B                = 0x01,
    MSG_CHAR_UPPER_C                = 0x02,
    MSG_CHAR_UPPER_D                = 0x03,
    MSG_CHAR_UPPER_E                = 0x04,
    MSG_CHAR_UPPER_F                = 0x05,
    MSG_CHAR_UPPER_G                = 0x06,
    MSG_CHAR_UPPER_H                = 0x07,
    MSG_CHAR_UPPER_I                = 0x08,
    MSG_CHAR_UPPER_J                = 0x09,
    MSG_CHAR_UPPER_K                = 0x0A,
    MSG_CHAR_UPPER_L                = 0x0B,
    MSG_CHAR_UPPER_M                = 0x0C,
    MSG_CHAR_UPPER_N                = 0x0D,
    MSG_CHAR_UPPER_O                = 0x0E,
    MSG_CHAR_UPPER_P                = 0x0F,
    MSG_CHAR_UPPER_Q                = 0x10,
    MSG_CHAR_UPPER_R                = 0x11,
    MSG_CHAR_UPPER_S                = 0x12,
    MSG_CHAR_UPPER_T                = 0x13,
    MSG_CHAR_UPPER_U                = 0x14,
    MSG_CHAR_UPPER_V                = 0x15,
    MSG_CHAR_UPPER_W                = 0x16,
    MSG_CHAR_UPPER_X                = 0x17,
    MSG_CHAR_UPPER_Y                = 0x18,
    MSG_CHAR_UPPER_Z                = 0x19,
    MSG_CHAR_LOWER_Z                = 0x1A,

    // Variant 2 - Kanji (Chinese) characters
    MSG_CHAR_KANJI_00               = 0x00,
    MSG_CHAR_KANJI_01               = 0x01,
    MSG_CHAR_KANJI_02               = 0x02,
    MSG_CHAR_KANJI_03               = 0x03,
    MSG_CHAR_KANJI_04               = 0x04,
    MSG_CHAR_KANJI_05               = 0x05,
    MSG_CHAR_KANJI_06               = 0x06,
    MSG_CHAR_KANJI_07               = 0x07,
    MSG_CHAR_KANJI_08               = 0x08,
    MSG_CHAR_KANJI_09               = 0x09,
    MSG_CHAR_KANJI_0A               = 0x0A,
    MSG_CHAR_KANJI_0B               = 0x0B,
    MSG_CHAR_KANJI_0C               = 0x0C,
    MSG_CHAR_KANJI_0D               = 0x0D,
    MSG_CHAR_KANJI_0E               = 0x0E,
    MSG_CHAR_KANJI_0F               = 0x0F,
    MSG_CHAR_KANJI_10               = 0x10,
    MSG_CHAR_KANJI_11               = 0x11,
    MSG_CHAR_KANJI_12               = 0x12,
    MSG_CHAR_KANJI_13               = 0x13,
    MSG_CHAR_KANJI_14               = 0x14,
    MSG_CHAR_KANJI_15               = 0x15,
    MSG_CHAR_KANJI_16               = 0x16,
    MSG_CHAR_KANJI_17               = 0x17,
    MSG_CHAR_KANJI_18               = 0x18,
    MSG_CHAR_KANJI_19               = 0x19,
    MSG_CHAR_KANJI_1A               = 0x1A,
    MSG_CHAR_KANJI_1B               = 0x1B,
    MSG_CHAR_KANJI_1C               = 0x1C,
    MSG_CHAR_KANJI_1D               = 0x1D,
    MSG_CHAR_KANJI_1E               = 0x1E,
    MSG_CHAR_KANJI_1F               = 0x1F,
    MSG_CHAR_KANJI_20               = 0x20,
    MSG_CHAR_KANJI_21               = 0x21,
    MSG_CHAR_KANJI_22               = 0x22,
    MSG_CHAR_KANJI_23               = 0x23,
    MSG_CHAR_KANJI_24               = 0x24,
    MSG_CHAR_KANJI_25               = 0x25,
    MSG_CHAR_KANJI_26               = 0x26,
    MSG_CHAR_KANJI_27               = 0x27,
    MSG_CHAR_KANJI_28               = 0x28,
    MSG_CHAR_KANJI_29               = 0x29,
    MSG_CHAR_KANJI_2A               = 0x2A,
    MSG_CHAR_KANJI_2B               = 0x2B,
    MSG_CHAR_KANJI_2C               = 0x2C,
    MSG_CHAR_KANJI_2D               = 0x2D,
    MSG_CHAR_KANJI_2E               = 0x2E,
    MSG_CHAR_KANJI_2F               = 0x2F,
    MSG_CHAR_KANJI_30               = 0x30,
    MSG_CHAR_KANJI_31               = 0x31,
    MSG_CHAR_KANJI_32               = 0x32,
    MSG_CHAR_KANJI_33               = 0x33,
    MSG_CHAR_KANJI_34               = 0x34,
    MSG_CHAR_KANJI_35               = 0x35,
    MSG_CHAR_KANJI_36               = 0x36,
    MSG_CHAR_KANJI_37               = 0x37,
    MSG_CHAR_KANJI_38               = 0x38,
    MSG_CHAR_KANJI_39               = 0x39,
    MSG_CHAR_KANJI_3A               = 0x3A,
    MSG_CHAR_KANJI_3B               = 0x3B,
    MSG_CHAR_KANJI_3C               = 0x3C,
    MSG_CHAR_KANJI_3D               = 0x3D,
    MSG_CHAR_KANJI_3E               = 0x3E,
    MSG_CHAR_KANJI_3F               = 0x3F,
    MSG_CHAR_KANJI_40               = 0x40,
    MSG_CHAR_KANJI_41               = 0x41,
    MSG_CHAR_KANJI_42               = 0x42,
    MSG_CHAR_KANJI_43               = 0x43,
    MSG_CHAR_KANJI_44               = 0x44,
    MSG_CHAR_KANJI_45               = 0x45,
    MSG_CHAR_KANJI_46               = 0x46,
    MSG_CHAR_KANJI_47               = 0x47,
    MSG_CHAR_KANJI_48               = 0x48,
    MSG_CHAR_KANJI_49               = 0x49,
    MSG_CHAR_KANJI_4A               = 0x4A,
    MSG_CHAR_KANJI_4B               = 0x4B,
    MSG_CHAR_KANJI_4C               = 0x4C,
    MSG_CHAR_KANJI_4D               = 0x4D,
    MSG_CHAR_KANJI_4E               = 0x4E,
    MSG_CHAR_KANJI_4F               = 0x4F,
    MSG_CHAR_KANJI_50               = 0x50,
    MSG_CHAR_KANJI_51               = 0x51,
    MSG_CHAR_KANJI_52               = 0x52,
    MSG_CHAR_KANJI_53               = 0x53,
    MSG_CHAR_KANJI_54               = 0x54,
    MSG_CHAR_KANJI_55               = 0x55,
    MSG_CHAR_KANJI_56               = 0x56,
    MSG_CHAR_KANJI_57               = 0x57,
    MSG_CHAR_KANJI_58               = 0x58,
    MSG_CHAR_KANJI_59               = 0x59,
    MSG_CHAR_KANJI_5A               = 0x5A,
    MSG_CHAR_KANJI_5B               = 0x5B,
    MSG_CHAR_KANJI_5C               = 0x5C,
    MSG_CHAR_KANJI_5D               = 0x5D,
    MSG_CHAR_KANJI_5E               = 0x5E,
    MSG_CHAR_KANJI_5F               = 0x5F,
    MSG_CHAR_KANJI_60               = 0x60,
    MSG_CHAR_CIRCLE                 = 0x61,
    MSG_CHAR_CROSS                  = 0x62,
    MSG_CHAR_KANJI_63               = 0x63,
    MSG_CHAR_KANJI_64               = 0x64,
    MSG_CHAR_KANJI_65               = 0x65,
    MSG_CHAR_KANJI_66               = 0x66,
    MSG_CHAR_KANJI_67               = 0x67,
    MSG_CHAR_KANJI_68               = 0x68,
    MSG_CHAR_KANJI_69               = 0x69,
    MSG_CHAR_NOTE                   = 0x6A,
    MSG_CHAR_KANJI_6B               = 0x6B,
    MSG_CHAR_KANJI_6C               = 0x6C,
    MSG_CHAR_KANJI_6D               = 0x6D,
    MSG_CHAR_KANJI_6E               = 0x6E,
    MSG_CHAR_KANJI_6F               = 0x6F,
    MSG_CHAR_KANJI_70               = 0x70,
    MSG_CHAR_KANJI_71               = 0x71,
    MSG_CHAR_KANJI_72               = 0x72,
    MSG_CHAR_KANJI_73               = 0x73,
    MSG_CHAR_KANJI_74               = 0x74,
    MSG_CHAR_KANJI_75               = 0x75,
    MSG_CHAR_KANJI_76               = 0x76,
    MSG_CHAR_KANJI_77               = 0x77,
    MSG_CHAR_LOWER_X                = 0x78,

    // Variant 3 - N64 Button Icons
    MSG_CHAR_BUTTON_A               = 0x00,
    MSG_CHAR_BUTTON_B               = 0x01,
    MSG_CHAR_BUTTON_START           = 0x02,
    MSG_CHAR_BUTTON_C_UP            = 0x03,
    MSG_CHAR_BUTTON_C_DOWN          = 0x04,
    MSG_CHAR_BUTTON_C_LEFT          = 0x05,
    MSG_CHAR_BUTTON_C_RIGHT         = 0x06,
    MSG_CHAR_BUTTON_Z               = 0x07,
    MSG_CHAR_BUTTON_L               = 0x08,
    MSG_CHAR_BUTTON_R               = 0x09,
#else
    MSG_CHAR_NOTE                   = 0x00,
    MSG_CHAR_EXCLAMTION             = 0x01,
    MSG_CHAR_BACKSLASH              = 0x02,
    MSG_CHAR_HASH                   = 0x03,
    MSG_CHAR_DOLLAR                 = 0x04,
    MSG_CHAR_PERCENT                = 0x05,
    MSG_CHAR_AND                    = 0x06,
    MSG_CHAR_APOSTROPHE             = 0x07,
    MSG_CHAR_LPAREN                 = 0x08,
    MSG_CHAR_RPAREN                 = 0x09,
    MSG_CHAR_TIMES                  = 0x0A,
    MSG_CHAR_PLUS                   = 0x0B,
    MSG_CHAR_COMMA                  = 0x0C,
    MSG_CHAR_MINUS                  = 0x0D,
    MSG_CHAR_PERIOD                 = 0x0E,
    MSG_CHAR_FORWARDSLASH           = 0x0F,
    MSG_CHAR_DIGIT_0                = 0x10,
    MSG_CHAR_DIGIT_1                = 0x11,
    MSG_CHAR_DIGIT_2                = 0x12,
    MSG_CHAR_DIGIT_3                = 0x13,
    MSG_CHAR_DIGIT_4                = 0x14,
    MSG_CHAR_DIGIT_5                = 0x15,
    MSG_CHAR_DIGIT_6                = 0x16,
    MSG_CHAR_DIGIT_7                = 0x17,
    MSG_CHAR_DIGIT_8                = 0x18,
    MSG_CHAR_DIGIT_9                = 0x19,
    MSG_CHAR_COLON                  = 0x1A,
    MSG_CHAR_SEMICOLON              = 0x1B,
    MSG_CHAR_LESS_THAN              = 0x1C,
    MSG_CHAR_EQUAL                  = 0x1D,
    MSG_CHAR_GREATER_THAN           = 0x1E,
    MSG_CHAR_QUESTION               = 0x1F,
    MSG_CHAR_AT                     = 0x20,
    MSG_CHAR_UPPER_A                = 0x21,
    MSG_CHAR_UPPER_B                = 0x22,
    MSG_CHAR_UPPER_C                = 0x23,
    MSG_CHAR_UPPER_D                = 0x24,
    MSG_CHAR_UPPER_E                = 0x25,
    MSG_CHAR_UPPER_F                = 0x26,
    MSG_CHAR_UPPER_G                = 0x27,
    MSG_CHAR_UPPER_H                = 0x28,
    MSG_CHAR_UPPER_I                = 0x29,
    MSG_CHAR_UPPER_J                = 0x2A,
    MSG_CHAR_UPPER_K                = 0x2B,
    MSG_CHAR_UPPER_L                = 0x2C,
    MSG_CHAR_UPPER_M                = 0x2D,
    MSG_CHAR_UPPER_N                = 0x2E,
    MSG_CHAR_UPPER_O                = 0x2F,
    MSG_CHAR_UPPER_P                = 0x30,
    MSG_CHAR_UPPER_Q                = 0x31,
    MSG_CHAR_UPPER_R                = 0x32,
    MSG_CHAR_UPPER_S                = 0x33,
    MSG_CHAR_UPPER_T                = 0x34,
    MSG_CHAR_UPPER_U                = 0x35,
    MSG_CHAR_UPPER_V                = 0x36,
    MSG_CHAR_UPPER_W                = 0x37,
    MSG_CHAR_UPPER_X                = 0x38,
    MSG_CHAR_UPPER_Y                = 0x39,
    MSG_CHAR_UPPER_Z                = 0x3A,
    MSG_CHAR_LBRACKET               = 0x3B,
    MSG_CHAR_YEN                    = 0x3C,
    MSG_CHAR_RBRACKET               = 0x3D,
    MSG_CHAR_CARET                  = 0x3E,
    MSG_CHAR_UNDERSCORE             = 0x3F,
    MSG_CHAR_BACKTICK               = 0x40,
    MSG_CHAR_LOWER_A                = 0x41,
    MSG_CHAR_LOWER_B                = 0x42,
    MSG_CHAR_LOWER_C                = 0x43,
    MSG_CHAR_LOWER_D                = 0x44,
    MSG_CHAR_LOWER_E                = 0x45,
    MSG_CHAR_LOWER_F                = 0x46,
    MSG_CHAR_LOWER_G                = 0x47,
    MSG_CHAR_LOWER_H                = 0x48,
    MSG_CHAR_LOWER_I                = 0x49,
    MSG_CHAR_LOWER_J                = 0x4A,
    MSG_CHAR_LOWER_K                = 0x4B,
    MSG_CHAR_LOWER_L                = 0x4C,
    MSG_CHAR_LOWER_M                = 0x4D,
    MSG_CHAR_LOWER_N                = 0x4E,
    MSG_CHAR_LOWER_O                = 0x4F,
    MSG_CHAR_LOWER_P                = 0x50,
    MSG_CHAR_LOWER_Q                = 0x51,
    MSG_CHAR_LOWER_R                = 0x52,
    MSG_CHAR_LOWER_S                = 0x53,
    MSG_CHAR_LOWER_T                = 0x54,
    MSG_CHAR_LOWER_U                = 0x55,
    MSG_CHAR_LOWER_V                = 0x56,
    MSG_CHAR_LOWER_W                = 0x57,
    MSG_CHAR_LOWER_X                = 0x58,
    MSG_CHAR_LOWER_Y                = 0x59,
    MSG_CHAR_LOWER_Z                = 0x5A,
    MSG_CHAR_LCURLY                 = 0x5B,
    MSG_CHAR_PIPE                   = 0x5C,
    MSG_CHAR_RCURLY                 = 0x5D,
    MSG_CHAR_TILDA                  = 0x5E,
    MSG_CHAR_DEGREE                 = 0x5F,
    MSG_CHAR_UPPER_A_GRAVE          = 0x60,
    MSG_CHAR_UPPER_A_ACUTE          = 0x61,
    MSG_CHAR_UPPER_A_CIRCUMFLEX     = 0x62,
    MSG_CHAR_UPPER_A_UMLAUT         = 0x63,
    MSG_CHAR_UPPER_C_CEDILLA        = 0x64,
    MSG_CHAR_UPPER_E_GRAVE          = 0x65,
    MSG_CHAR_UPPER_E_ACUTE          = 0x66,
    MSG_CHAR_UPPER_E_CIRCUMFLEX     = 0x67,
    MSG_CHAR_UPPER_E_UMLAUT         = 0x68,
    MSG_CHAR_UPPER_I_GRAVE          = 0x69,
    MSG_CHAR_UPPER_I_ACUTE          = 0x6A,
    MSG_CHAR_UPPER_I_CIRCUMFLEX     = 0x6B,
    MSG_CHAR_UPPER_I_UMLAUT         = 0x6C,
    MSG_CHAR_UPPER_N_TILDE          = 0x6D,
    MSG_CHAR_UPPER_O_GRAVE          = 0x6E,
    MSG_CHAR_UPPER_O_ACUTE          = 0x6F,
    MSG_CHAR_UPPER_O_CIRCUMFLEX     = 0x70,
    MSG_CHAR_UPPER_O_UMLAUT         = 0x71,
    MSG_CHAR_UPPER_U_GRAVE          = 0x72,
    MSG_CHAR_UPPER_U_ACUTE          = 0x73,
    MSG_CHAR_UPPER_U_CIRCUMFLEX     = 0x74,
    MSG_CHAR_UPPER_U_UMLAUT         = 0x75,
    MSG_CHAR_SHARP_S                = 0x76,
    MSG_CHAR_LOWER_A_GRAVE          = 0x77,
    MSG_CHAR_LOWER_A_ACUTE          = 0x78,
    MSG_CHAR_LOWER_A_CIRCUMFLEX     = 0x79,
    MSG_CHAR_LOWER_A_UMLAUT         = 0x7A,
    MSG_CHAR_LOWER_C_CEDILLA        = 0x7B,
    MSG_CHAR_LOWER_E_GRAVE          = 0x7C,
    MSG_CHAR_LOWER_E_ACUTE          = 0x7D,
    MSG_CHAR_LOWER_E_CIRCUMFLEX     = 0x7E,
    MSG_CHAR_LOWER_E_UMLAUT         = 0x7F,
    MSG_CHAR_LOWER_I_GRAVE          = 0x80,
    MSG_CHAR_LOWER_I_ACUTE          = 0x81,
    MSG_CHAR_LOWER_I_CIRCUMFLEX     = 0x82,
    MSG_CHAR_LOWER_I_UMLAUT         = 0x83,
    MSG_CHAR_LOWER_N_TILDE          = 0x84,
    MSG_CHAR_LOWER_O_GRAVE          = 0x85,
    MSG_CHAR_LOWER_O_ACUTE          = 0x86,
    MSG_CHAR_LOWER_O_CIRCUMFLEX     = 0x87,
    MSG_CHAR_LOWER_O_UMLAUT         = 0x88,
    MSG_CHAR_LOWER_U_GRAVE          = 0x89,
    MSG_CHAR_LOWER_U_ACUTE          = 0x8A,
    MSG_CHAR_LOWER_U_CIRCUMFLEX     = 0x8B,
    MSG_CHAR_LOWER_U_UMLAUT         = 0x8C,
    MSG_CHAR_INVERTED_EXCLAMTION    = 0x8D,
    MSG_CHAR_INVERTED_QUESTION      = 0x8E,
    MSG_CHAR_FEM_ORDINAL            = 0x8F,
    MSG_CHAR_HEART                  = 0x90,
    MSG_CHAR_STAR                   = 0x91,
    MSG_CHAR_UP                     = 0x92,
    MSG_CHAR_DOWN                   = 0x93,
    MSG_CHAR_LEFT                   = 0x94,
    MSG_CHAR_RIGHT                  = 0x95,
    MSG_CHAR_CIRCLE                 = 0x96,
    MSG_CHAR_CROSS                  = 0x97,
    MSG_CHAR_BUTTON_A               = 0x98,
    MSG_CHAR_BUTTON_B               = 0x99,
    MSG_CHAR_BUTTON_L               = 0x9A,
    MSG_CHAR_BUTTON_R               = 0x9B,
    MSG_CHAR_BUTTON_Z               = 0x9C,
    MSG_CHAR_BUTTON_C_UP            = 0x9D,
    MSG_CHAR_BUTTON_C_DOWN          = 0x9E,
    MSG_CHAR_BUTTON_C_LEFT          = 0x9F,
    MSG_CHAR_BUTTON_C_RIGHT         = 0xA0,
    MSG_CHAR_BUTTON_START           = 0xA1,
    MSG_CHAR_DOUBLE_QUOTE_OPEN      = 0xA2,
    MSG_CHAR_DOUBLE_QUOTE_CLOSE     = 0xA3,
    MSG_CHAR_SINGLE_QUOTE_OPEN      = 0xA4,
    MSG_CHAR_SINGLE_QUOTE_CLOSE     = 0xA5,
    // 0xA6 to 0xEF are unused
#endif

#if VERSION_IQUE
    // All US characters are in the rom, but their range is used for multibyte characters
    MSG_CHAR_MULTIBYTE_FIRST        = 0x5F,
    MSG_CHAR_MULTIBYTE_LAST         = 0x8F,
    MSG_CHAR_ZH_START               = 0xA6,
    MSG_CHAR_ZH_RANK                = 0x33F, // 勋
    MSG_CHAR_ZH_CHAPTER             = 0x340, // 章
#endif

    MSG_CHAR_UNK_C3                 = 0xC3,

    MSG_CHAR_MENU_SPACE             = 0xC6,
    MSG_CHAR_MENU_USE_CHARSET_B     = 0xC7,
    MSG_CHAR_MENU_USE_CHARSET_A     = 0xC8,
    MSG_CHAR_MENU_BACK              = 0xC9,
    MSG_CHAR_MENU_END               = 0xCA,

    // special character codes used when reading from the source buffer
    MSG_CHAR_READ_ENDL              = 0xF0,
    MSG_CHAR_READ_WAIT              = 0xF1,
    MSG_CHAR_READ_PAUSE             = 0xF2,
    MSG_CHAR_READ_VARIANT0          = 0xF3,
    MSG_CHAR_READ_VARIANT1          = 0xF4,
    MSG_CHAR_READ_VARIANT2          = 0xF5,
    MSG_CHAR_READ_VARIANT3          = 0xF6,
    MSG_CHAR_READ_SPACE             = 0xF7,
    MSG_CHAR_READ_FULL_SPACE        = 0xF8,
    MSG_CHAR_READ_HALF_SPACE        = 0xF9,
    MSG_CHAR_READ_UNK_CHAR_FA       = 0xFA,
    MSG_CHAR_READ_NEXT              = 0xFB,
    MSG_CHAR_READ_STYLE             = 0xFC,
    MSG_CHAR_READ_END               = 0xFD,
    // 0xFE unused
    MSG_CHAR_READ_FUNCTION          = 0xFF,

    // special character codes used when writing to the print buffer
    MSG_CONTROL_CHAR                = 0xF0,
    MSG_CHAR_PRINT_ENDL             = 0xF0,
    MSG_CHAR_PRINT_VARIANT0         = 0xF1,
    MSG_CHAR_PRINT_VARIANT1         = 0xF2,
    MSG_CHAR_PRINT_VARIANT2         = 0xF3,
    MSG_CHAR_PRINT_VARIANT3         = 0xF4,
    MSG_CHAR_PRINT_SPACE            = 0xF5,
    MSG_CHAR_PRINT_FULL_SPACE       = 0xF6,
    MSG_CHAR_PRINT_HALF_SPACE       = 0xF7,
    MSG_CHAR_PRINT_STYLE            = 0xF8,
    MSG_CHAR_PRINT_UNK_CHAR_FA      = 0xF9,
    MSG_CHAR_PRINT_NEXT             = 0xFA,
    MSG_CHAR_PRINT_END              = 0xFB,
    // FC unused
    // FD unused
    // FE unused
    MSG_CHAR_PRINT_FUNCTION         = 0xFF
};

enum MsgFunctionCodes {
    // function codes used when reading from the source buffer
    MSG_READ_FUNC_FONT                   = 0x00,
    MSG_READ_FUNC_VARIANT                = 0x01,
    MSG_READ_FUNC_SET_FRAME_PALETTE      = 0x02,
    MSG_READ_FUNC_RESET_GFX              = 0x03,
    MSG_READ_FUNC_YIELD                  = 0x04,
    MSG_READ_FUNC_COLOR                  = 0x05,
    MSG_READ_FUNC_NO_SKIP                = 0x06,
    MSG_READ_FUNC_INPUT_OFF              = 0x07,
    MSG_READ_FUNC_INPUT_ON               = 0x08,
    MSG_READ_FUNC_DELAY_OFF              = 0x09,
    MSG_READ_FUNC_DELAY_ON               = 0x0A,
    MSG_READ_FUNC_SPACING                = 0x0B,
    MSG_READ_FUNC_SCROLL                 = 0x0C,
    MSG_READ_FUNC_SIZE                   = 0x0D,
    MSG_READ_FUNC_SIZE_RESET             = 0x0E,
    MSG_READ_FUNC_SPEED                  = 0x0F,
    MSG_READ_FUNC_SET_X                  = 0x10,
    MSG_READ_FUNC_SET_Y                  = 0x11,
    MSG_READ_FUNC_RIGHT                  = 0x12,
    MSG_READ_FUNC_DOWN                   = 0x13,
    MSG_READ_FUNC_UP                     = 0x14,
    MSG_READ_FUNC_INLINE_IMAGE           = 0x15,
    MSG_READ_FUNC_ANIM_SPRITE            = 0x16,
    MSG_READ_FUNC_ITEM_ICON              = 0x17,
    MSG_READ_FUNC_IMAGE                  = 0x18,
    MSG_READ_FUNC_HIDE_IMAGE             = 0x19,
    MSG_READ_FUNC_ANIM_DELAY             = 0x1A,
    MSG_READ_FUNC_ANIM_LOOP              = 0x1B,
    MSG_READ_FUNC_ANIM_DONE              = 0x1C,
    MSG_READ_FUNC_SET_CURSOR             = 0x1D,
    MSG_READ_FUNC_CURSOR                 = 0x1E,
    MSG_READ_FUNC_END_CHOICE             = 0x1F,
    MSG_READ_FUNC_SET_CANCEL             = 0x20,
    MSG_READ_FUNC_OPTION                 = 0x21,
    MSG_READ_FUNC_SAVE_POS               = 0x22,
    MSG_READ_FUNC_RESTORE_POS            = 0x23,
    MSG_READ_FUNC_SAVE_COLOR             = 0x24,
    MSG_READ_FUNC_RESTORE_COLOR          = 0x25,
    MSG_READ_FUNC_START_FX               = 0x26,
    MSG_READ_FUNC_END_FX                 = 0x27,
    MSG_READ_FUNC_VAR                    = 0x28,
    MSG_READ_FUNC_CENTER_X               = 0x29,
    MSG_READ_FUNC_SET_REWIND             = 0x2A,
    MSG_READ_FUNC_ENABLE_CDOWN_NEXT      = 0x2B,
    MSG_READ_FUNC_CUSTOM_VOICE           = 0x2C,
    MSG_READ_FUNC_VOLUME                 = 0x2E,
    MSG_READ_FUNC_VOICE                  = 0x2F,
    // function codes used when writing to the print buffer
    MSG_PRINT_FUNC_FONT                  = 0x00,
    MSG_PRINT_FUNC_VARIANT               = 0x01,
    MSG_PRINT_FUNC_SET_FRAME_PALETTE     = 0x16,
    MSG_PRINT_RESET_GFX                  = 0x17,
    MSG_PRINT_FUNC_COLOR                 = 0x04,
    MSG_PRINT_FUNC_SPACING               = 0x05,
    MSG_PRINT_FUNC_SCROLL                = 0xFA,
    MSG_PRINT_FUNC_SIZE                  = 0x06,
    MSG_PRINT_FUNC_SIZE_RESET            = 0x07,
    MSG_PRINT_FUNC_SET_X                 = 0x08,
    MSG_PRINT_FUNC_SET_Y                 = 0x09,
    MSG_PRINT_FUNC_RIGHT                 = 0x0A,
    MSG_PRINT_FUNC_DOWN                  = 0x0B,
    MSG_PRINT_FUNC_UP                    = 0x0C,
    MSG_PRINT_FUNC_INLINE_IMAGE          = 0x0E,
    MSG_PRINT_FUNC_ANIM_SPRITE           = 0x0F,
    MSG_PRINT_FUNC_ITEM_ICON             = 0x10,
    MSG_PRINT_FUNC_ANIM_DELAY            = 0x11,
    MSG_PRINT_FUNC_ANIM_LOOP             = 0x12,
    MSG_PRINT_FUNC_ANIM_DONE             = 0x13,
    MSG_PRINT_FUNC_CURSOR                = 0x14,
    MSG_PRINT_FUNC_OPTION                = 0x15,
    MSG_PRINT_FUNC_SAVE_POS              = 0x18,
    MSG_PRINT_FUNC_RESTORE_POS           = 0x19,
    MSG_PRINT_FUNC_SAVE_COLOR            = 0x1A,
    MSG_PRINT_FUNC_RESTORE_COLOR         = 0x1B,
    MSG_PRINT_FUNC_START_FX              = 0x1C,
    MSG_PRINT_FUNC_END_FX                = 0x1D,
    MSG_PRINT_FUNC_CENTER_X              = 0x1E
};

enum MsgEffectCodes {
    MSG_FX_SHAKE                    = 0x00,
    MSG_FX_WAVE                     = 0x01,
    MSG_FX_NOISE_OUTLINE            = 0x02,
    MSG_FX_STATIC                   = 0x03,
    MSG_FX_BLUR                     = 0x05,
    MSG_FX_RAINBOW                  = 0x06,
    MSG_FX_DITHER_FADE              = 0x07,
    MSG_FX_GLOBAL_WAVE              = 0x08,
    MSG_FX_GLOBAL_RAINBOW           = 0x09,
    MSG_FX_RISE_PRINT               = 0x0A,
    MSG_FX_GROW_PRINT               = 0x0B,
    MSG_FX_SIZE_JITTER              = 0x0C,
    MSG_FX_SIZE_WAVE                = 0x0D,
    MSG_FX_DROP_SHADOW              = 0x0E
};

enum MsgEffectFlags {
    MSG_FX_FLAG_SHAKE               = 0x00001,
    MSG_FX_FLAG_WAVE                = 0x00002,
    MSG_FX_FLAG_NOISE_OUTLINE       = 0x00004,
    MSG_FX_FLAG_BLUR                = 0x00020,
    MSG_FX_FLAG_RAINBOW             = 0x00040,
    MSG_FX_FLAG_DITHER_FADE         = 0x00080,
    MSG_FX_FLAG_GLOBAL_WAVE         = 0x00200,
    MSG_FX_FLAG_GLOBAL_RAINBOW      = 0x00400,
    MSG_FX_FLAG_RISE_PRINT          = 0x00800,
    MSG_FX_FLAG_GROW_PRINT          = 0x01000,
    MSG_FX_FLAG_SIZE_JITTER         = 0x02000,
    MSG_FX_FLAG_SIZE_WAVE           = 0x04000,
    MSG_FX_FLAG_DROP_SHADOW         = 0x08000,
    MSG_FX_FLAG_STATIC              = 0x10000
};

enum MsgStyles {
    MSG_STYLE_NONE                  = 0x0,
    MSG_STYLE_RIGHT                 = 0x1,
    MSG_STYLE_LEFT                  = 0x2,
    MSG_STYLE_CENTER                = 0x3,
    MSG_STYLE_TATTLE                = 0x4,
    MSG_STYLE_CHOICE                = 0x5,
    MSG_STYLE_INSPECT               = 0x6,
    MSG_STYLE_SIGN                  = 0x7,
    MSG_STYLE_LAMPPOST              = 0x8,
    MSG_STYLE_POSTCARD              = 0x9,
    MSG_STYLE_POPUP                 = 0xA,
    MSG_STYLE_B                     = 0xB,
    MSG_STYLE_UPGRADE               = 0xC,
    MSG_STYLE_NARRATE               = 0xD,
    MSG_STYLE_EPILOGUE              = 0xE,
    MSG_STYLE_F                     = 0xF
};

enum MsgFonts {
    MSG_FONT_NORMAL                 = 0,
    MSG_FONT_MENU                   = 1,
    MSG_FONT_2                      = 2,
    MSG_FONT_TITLE                  = 3,
    MSG_FONT_SUBTITLE               = 4,
};

enum MsgVoices {
    MSG_VOICE_NORMAL                = 0,
    MSG_VOICE_BOWSER                = 1,
    MSG_VOICE_STAR                  = 2
};

enum MsgPrintModeFlags {
    MSG_PRINT_FLAG_1                = 0x001,
    MSG_PRINT_FLAG_2                = 0x002,
    MSG_PRINT_FLAG_10               = 0x010,
    MSG_PRINT_FLAG_20               = 0x020,
    MSG_PRINT_FLAG_40               = 0x040,
    MSG_PRINT_FLAG_80               = 0x080,
    MSG_PRINT_FLAG_100              = 0x100,
};

enum MsgStateFlags {
    MSG_STATE_FLAG_1                = 0x000001,
    MSG_STATE_FLAG_2                = 0x000002,
    MSG_STATE_FLAG_4                = 0x000004,
    MSG_STATE_FLAG_10               = 0x000010,
    MSG_STATE_FLAG_20               = 0x000020,
    MSG_STATE_FLAG_40               = 0x000040,
    MSG_STATE_FLAG_SPEAKING         = 0x000080, // determines animation of speaker (talk vs idle)
    MSG_STATE_FLAG_PRINT_QUICKLY    = 0x000100,
    MSG_STATE_FLAG_400              = 0x000400,
    MSG_STATE_FLAG_800              = 0x000800,
    MSG_STATE_FLAG_1000             = 0x001000,
    MSG_STATE_FLAG_4000             = 0x004000,
    MSG_STATE_FLAG_8000             = 0x008000,
    MSG_STATE_FLAG_10000            = 0x010000,
    MSG_STATE_FLAG_20000            = 0x020000,
    MSG_STATE_FLAG_40000            = 0x040000,
    MSG_STATE_FLAG_80000            = 0x080000,
    MSG_STATE_FLAG_100000           = 0x100000,
    MSG_STATE_FLAG_800000           = 0x800000,
};

enum MsgDelayFlags {
    MSG_DELAY_FLAG_1                = 0x000001,
    MSG_DELAY_FLAG_2                = 0x000002,
    MSG_DELAY_FLAG_4                = 0x000004,
};

enum MsgWindowStates {
    MSG_WINDOW_STATE_DONE               = 0x0,
    MSG_WINDOW_STATE_INIT               = 0x1,
    MSG_WINDOW_STATE_OPENING            = 0x2,
    MSG_WINDOW_STATE_CLOSING            = 0x3,
    MSG_WINDOW_STATE_PRINTING           = 0x4,
    MSG_WINDOW_STATE_WAITING            = 0x5,
    MSG_WINDOW_STATE_SCROLLING          = 0x6,
    MSG_WINDOW_STATE_WAITING_FOR_CHOICE = 0x7,
    MSG_WINDOW_STATE_SCROLLING_BACK     = 0x8,
    MSG_WINDOW_STATE_VIEWING_PREV       = 0x9,
    MSG_WINDOW_STATE_A                  = 0xA,
    MSG_WINDOW_STATE_B                  = 0xB,
    MSG_WINDOW_STATE_C                  = 0xC,
    MSG_WINDOW_STATE_D                  = 0xD,
    MSG_WINDOW_STATE_E                  = 0xE,
};

enum BackgroundFlags {
    BACKGROUND_FLAG_TEXTURE                 = 0x01,
    BACKGROUND_FLAG_FOG                     = 0x02,
    BACKGROUND_RENDER_STATE_BEGIN_PAUSED    = 0x10,
    BACKGROUND_RENDER_STATE_FILTER_PAUSED   = 0x20,
    BACKGROUND_RENDER_STATE_SHOW_PAUSED     = 0x30,
    BACKGROUND_RENDER_STATE_MASK            = 0xF0,
};

enum EncounterStates {
    ENCOUNTER_STATE_NONE                = 0,
    ENCOUNTER_STATE_CREATE              = 1,
    ENCOUNTER_STATE_NEUTRAL             = 2,
    ENCOUNTER_STATE_PRE_BATTLE          = 3,
    ENCOUNTER_STATE_CONVERSATION        = 4,
    ENCOUNTER_STATE_POST_BATTLE         = 5,
};

enum BattleTransitionStates {
    BATTLE_TRANSITION_STATE_LOADING     = -1,
    BATTLE_TRANSITION_STATE_STARTED     = 0,
    BATTLE_TRANSITION_STATE_COMPLETE    = 1,
};

enum EncounterCreateSubStates {
    ENCOUNTER_SUBSTATE_CREATE_INIT                      = 0,
    ENCOUNTER_SUBSTATE_CREATE_RUN_INIT_SCRIPT           = 1,
    ENCOUNTER_SUBSTATE_CREATE_RUN_AI                    = 2,
};

enum EncounterNeutralSubStates {
    ENCOUNTER_SUBSTATE_NEUTRAL                          = 0,
};

enum EncounterPreBattleSubStates {
    ENCOUNTER_SUBSTATE_PRE_BATTLE_INIT                  = 0,
    ENCOUNTER_SUBSTATE_PRE_BATTLE_LOAD                  = 1,
    ENCOUNTER_SUBSTATE_PRE_BATTLE_AUTO_WIN              = 2,
    ENCOUNTER_SUBSTATE_PRE_BATTLE_SKIP                  = 3,
};

enum EncounterConversationSubStates {
    ENCOUNTER_SUBSTATE_CONVERSATION_INIT                = 0,
    ENCOUNTER_SUBSTATE_CONVERSATION_END                 = 1,
};

enum EncounterPostBattleSubStates {
    ENCOUNTER_SUBSTATE_POST_BATTLE_INIT                 = 0,
    ENCOUNTER_SUBSTATE_POST_BATTLE_WON_FADE_IN          = 2,
    ENCOUNTER_SUBSTATE_POST_BATTLE_WON_KILL             = 3,
    ENCOUNTER_SUBSTATE_POST_BATTLE_WON_RESUME           = 4,
    ENCOUNTER_SUBSTATE_POST_BATTLE_WON_CHECK_MERLEE     = 10,
    ENCOUNTER_SUBSTATE_POST_BATTLE_PLAY_NPC_DEFEAT      = 11,
    ENCOUNTER_SUBSTATE_POST_BATTLE_FLED_INIT            = 100,
    ENCOUNTER_SUBSTATE_POST_BATTLE_FLED_FADE_IN         = 101,
    ENCOUNTER_SUBSTATE_POST_BATTLE_FLED_RESUME          = 102,
    ENCOUNTER_SUBSTATE_POST_BATTLE_FLED_DELAY           = 103, // delay before battle can be retriggered
    ENCOUNTER_SUBSTATE_POST_BATTLE_LOST_INIT            = 200,
    ENCOUNTER_SUBSTATE_POST_BATTLE_LOST_FADE_IN         = 201,
    ENCOUNTER_SUBSTATE_POST_BATTLE_LOST_RESUME          = 202,
    ENCOUNTER_SUBSTATE_POST_BATTLE_LOST_DELAY           = 203,
    ENCOUNTER_SUBSTATE_POST_BATTLE_SKIP                 = 300,
    ENCOUNTER_SUBSTATE_POST_BATTLE_ENEMY_FLED_INIT      = 400,
    ENCOUNTER_SUBSTATE_POST_BATTLE_ENEMY_FLED_FADE_IN   = 401,
    ENCOUNTER_SUBSTATE_POST_BATTLE_ENEMY_FLED_RESUME    = 402,
};

enum PlayerSpriteSets {
    PLAYER_SPRITES_MARIO_WORLD          = 0,
    PLAYER_SPRITES_MARIO_REFLECT_FLOOR  = 1,
    PLAYER_SPRITES_COMBINED_EPILOGUE    = 2,
    PLAYER_SPRITES_MARIO_PARADE         = 3,
    PLAYER_SPRITES_PEACH_WORLD          = 4,
    PLAYER_SPRITES_MARIO_BATTLE         = 5,
    PLAYER_SPRITES_PEACH_BATTLE         = 6,
};

enum BattleDarknessMode {
    BTL_DARKNESS_MODE_0     = 0,
    BTL_DARKNESS_MODE_1     = 1,
    BTL_DARKNESS_MODE_2     = 2,
    BTL_DARKNESS_MODE_3     = 3,
};

enum BattleDarknessState {
    BTL_DARKNESS_STATE_LOCKED       = -2,
    BTL_DARKNESS_STATE_DARK         = -1,
    BTL_DARKNESS_STATE_NONE         = 0,
    BTL_DARKNESS_STATE_WATT_BASED   = 1,
};

enum WindowStyles {
    WINDOW_STYLE_0      = 0,
    WINDOW_STYLE_1      = 1,
    WINDOW_STYLE_2      = 2,
    WINDOW_STYLE_3      = 3,
    WINDOW_STYLE_4      = 4,
    WINDOW_STYLE_5      = 5,
    WINDOW_STYLE_6      = 6,
    WINDOW_STYLE_7      = 7,
    WINDOW_STYLE_8      = 8,
    WINDOW_STYLE_9      = 9,
    WINDOW_STYLE_10     = 10,
    WINDOW_STYLE_11     = 11,
    WINDOW_STYLE_12     = 12,
    WINDOW_STYLE_13     = 13,
    WINDOW_STYLE_14     = 14,
    WINDOW_STYLE_15     = 15,
    WINDOW_STYLE_16     = 16,
    WINDOW_STYLE_17     = 17,
    WINDOW_STYLE_18     = 18,
    WINDOW_STYLE_19     = 19,
    WINDOW_STYLE_20     = 20,
    WINDOW_STYLE_21     = 21,
    WINDOW_STYLE_22     = 22,
    WINDOW_STYLE_MAX    = 22,
};

enum ThreadIDs {
    THREAD_ID_PI        = 0,
    THREAD_ID_CRASH     = 2,
    THREAD_ID_AUDIO     = 3, // also = NU_MAIN_THREAD_ID
};

// LANGUAGE_DEFAULT as 0 will be the first index into several arrays containing data based on the current language.
// For non-PAL versions, this will be the first and only index.
#define LANGUAGE_DEFAULT 0
enum Language {
    LANGUAGE_EN = 0,
    LANGUAGE_DE = 1,
    LANGUAGE_FR = 2,
    LANGUAGE_ES = 3,
};

enum IdleScriptState {
    IDLE_SCRIPT_DISABLE = 0,
    IDLE_SCRIPT_ENABLE  = 1,
    IDLE_SCRIPT_RESTART = -1,
};

enum BlurState {
    ACTOR_BLUR_DISABLE  = 0,
    ACTOR_BLUR_ENABLE   = 1,
    ACTOR_BLUR_RESET    = -1,
};

enum LandingCamAdjustMode {
    LANDING_CAM_NEVER_ADJUST  = 0,
    LANDING_CAM_CHECK_SURFACE = 1,  // allow landing cam unless the surface is lava
    LANDING_CAM_ALWAYS_ADJUST = 2,
};
