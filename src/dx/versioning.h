#pragma once

#include "common.h"

void fio_deserialize_state();
void fio_serialize_state();

/// What the game shows when it powers on. Set by the debug menu's Quick Save
/// and tools/save_file.py, and reset to BOOT_TO_DEFAULT by a normal save.
enum BootTo {
    BOOT_TO_DEFAULT     = 0, ///< As dx/config.h says, with DX_SKIP_LOGOS and DX_SKIP_STORY
    BOOT_TO_LOGOS       = 1,
    BOOT_TO_INTRO       = 2, ///< The story book, from the IntroParts value in SaveGlobals::bootScene
    BOOT_TO_DEMO        = 3, ///< The attract demo, from the index into DemoScenes in SaveGlobals::bootScene
    BOOT_TO_TITLE       = 4,
    BOOT_TO_FILE_SELECT = 5,
    BOOT_TO_RECORD      = 6, ///< Start as gSaveBootRecord says
};

typedef struct SaveGlobals {
    /* 0x00 */ char magicString[16]; // "Mario Story 006" string
    /* 0x10 */ char version[32]; // always zero for vanilla globals
    /* 0x30 */ s32 crc1;
    /* 0x34 */ s32 crc2;
    /* 0x38 */ s32 useMonoSound;
    /* 0x3C */ u32 lastFileSelected;
    /* 0x40 */ u8 bootTo; // see BootTo
    /* 0x41 */ u8 bootScene;
    /* 0x42 */ u8 reserved[62]; // unused
} SaveGlobals; // size = 0x80

/// Where play starts when the game boots into a SaveBootRecord.
enum BootStart {
    BOOT_START_SAVED    = 0, ///< Where the base file was saved
    BOOT_START_ENTRANCE = 1, ///< At SaveBootRecord::entryID of SaveBootRecord::map
    BOOT_START_BATTLE   = 2, ///< In the battle SaveBootRecord describes, from the base file's map
};

/// What happens when a battle started by a SaveBootRecord ends.
enum BootBattleEnd {
    BOOT_BATTLE_END_RETURN  = 0, ///< Return to the map, as after any battle
    BOOT_BATTLE_END_RESTART = 1, ///< Start the same battle again
};

/// How the game starts when SaveGlobals::bootTo is BOOT_TO_RECORD: which file
/// to load, or a new game, and where. It's stored beside the globals, so tools
/// can edit it without touching the player's files.
typedef struct SaveBootRecord {
    /* 0x00 */ s32 crc1;
    /* 0x04 */ s32 crc2;
    /* 0x08 */ s8 baseSlot; ///< The file to load, or -1 for a new game, saved to the first empty file
    /* 0x09 */ u8 start; // see BootStart
    /* 0x0A */ u8 onBattleEnd; // see BootBattleEnd
    /* 0x0B */ PAD(1);
    /* 0x0C */ s16 entryID;
    /* 0x0E */ PAD(2);
    /* 0x10 */ char map[32]; ///< For BOOT_START_ENTRANCE, such as "kmr_20"
    /* 0x30 */ char battleArea[32]; ///< The battle area overlay, such as "kmr_part_1"
    /* 0x50 */ char battle[64]; ///< A battle's formation in the area, such as "goomba_2"; empty for #actor alone
    /* 0x90 */ char stage[32]; ///< The stage overlay; empty for the battle's own, or the area's first battle's
    /* 0xB0 */ char actor[32]; ///< With no #battle, the actor to fight alone, such as "bob_omb" or "koopa_bros:red"
    /* 0xD0 */ PAD(0x30);
} SaveBootRecord; // size = 0x100

extern SaveBootRecord gSaveBootRecord;

typedef struct VanillaSaveFileSummary {
    /* 0x00 */ s32 timePlayed;
    /* 0x04 */ u8 spiritsRescued;
    /* 0x05 */ PAD(1);
    /* 0x06 */ s8 level;
    /* 0x07 */ MSG_BIN filename[8];
    /* 0x0F */ PAD(9);
} VanillaSaveFileSummary; // size = 0x18

/// PartnerData struct from unmodified Paper Mario
typedef struct VanillaPartnerData {
    /* 0x00 */ u8 enabled;
    /* 0x01 */ s8 level;
    /* 0x02 */ s16 unk_02[3];
} VanillaPartnerData; // size = 0x08

/// PlayerData struct from unmodified Paper Mario
typedef struct VanillaPlayerData {
    /* 0x000 */ s8 bootsLevel;
    /* 0x001 */ s8 hammerLevel;
    /* 0x002 */ s8 curHP;
    /* 0x003 */ s8 curMaxHP;
    /* 0x004 */ s8 hardMaxHP;
    /* 0x005 */ s8 curFP;
    /* 0x006 */ s8 curMaxFP;
    /* 0x007 */ s8 hardMaxFP;
    /* 0x008 */ s8 maxBP;
    /* 0x009 */ s8 level;
    /* 0x00A */ b8 hasActionCommands;
    /* 0x00B */ PAD(1);
    /* 0x00C */ s16 coins;
    /* 0x00E */ s8 fortressKeyCount;
    /* 0x00F */ u8 starPieces;
    /* 0x010 */ s8 starPoints;
    /* 0x011 */ s8 unused_011;
    /* 0x012 */ s8 curPartner;
    /* 0x013 */ PAD(1);
    /* 0x014 */ VanillaPartnerData partners[12];
    /* 0x074 */ s16 keyItems[32];
    /* 0x0B4 */ s16 badges[128];
    /* 0x1B4 */ s16 invItems[10];
    /* 0x1C8 */ s16 storedItems[32];
    /* 0x208 */ s16 equippedBadges[64];
    /* 0x288 */ s8 unused_288;
    /* 0x289 */ s8 merleeSpellType;
    /* 0x28A */ s8 merleeCastsLeft;
    /* 0x28B */ PAD(1);
    /* 0x28C */ s16 merleeTurnCount;
    /* 0x28E */ s8 maxStarPower;
    /* 0x28F */ PAD(1);
    /* 0x290 */ s16 starPower;
    /* 0x292 */ s8 starBeamLevel;
    /* 0x293 */ PAD(1);
    /* 0x294 */ u16 actionCommandAttempts;
    /* 0x296 */ u16 actionCommandSuccesses;
    /* 0x298 */ u16 hitsTaken;
    /* 0x29A */ u16 hitsBlocked;
    /* 0x29C */ u16 playerFirstStrikes;
    /* 0x29E */ u16 enemyFirstStrikes;
    /* 0x2A0 */ u16 powerBounces;
    /* 0x2A2 */ u16 battlesCount;
    /* 0x2A4 */ u16 battlesWon;
    /* 0x2A6 */ u16 fleeAttempts;
    /* 0x2A8 */ u16 battlesFled;
    /* 0x2AA */ u16 trainingsDone;
    /* 0x2AC */ s32 walkingStepsTaken;
    /* 0x2B0 */ s32 runningStepsTaken;
    /* 0x2B4 */ u32 totalCoinsEarned;
    /* 0x2B8 */ s16 idleFrameCounter;
    /* 0x2BA */ PAD(2);
    /* 0x2BC */ u32 frameCounter;
    /* 0x2C0 */ u16 quizzesAnswered;
    /* 0x2C2 */ u16 quizzesCorrect;
    /* 0x2C4 */ s32 partnerUnlockedTime[12];
    /* 0x2F4 */ s32 partnerUsedTime[12];
    /* 0x324 */ s32 tradeEventStartTime;
    /* 0x328 */ s32 droTreeHintTime;
    /* 0x32C */ u16 starPiecesCollected;
    /* 0x32E */ u16 jumpGamePlays;
    /* 0x330 */ u32 jumpGameTotal;
    /* 0x334 */ u16 jumpGameRecord;
    /* 0x336 */ u16 smashGamePlays;
    /* 0x338 */ u32 smashGameTotal;
    /* 0x33C */ u16 smashGameRecord;
    /* 0x33E */ PAD(0xEA);
} VanillaPlayerData; // size = 0x428

/// SaveData struct from unmodified Paper Mario
typedef struct VanillaSaveData {
    /* 0x0000 */ char magicString[16]; // "Mario Story 006" string
    /* 0x0010 */ char version[32]; // always zero for vanilla saves
    /* 0x0030 */ s32 crc1;
    /* 0x0034 */ s32 crc2;
    /* 0x0038 */ s32 saveSlot;
    /* 0x003C */ s32 saveCount;
    /* 0x0040 */ VanillaPlayerData player;
    /* 0x0468 */ s16 areaID;
    /* 0x046A */ s16 mapID;
    /* 0x046C */ s16 entryID;
    /* 0x046E */ PAD(2);
    /* 0x0470 */ s32 enemyDefeatFlags[60][12];
    /* 0x0FB0 */ s32 globalFlags[64];
    /* 0x10B0 */ s8 globalBytes[512];
    /* 0x12B0 */ s32 areaFlags[8];
    /* 0x12D0 */ s8 areaBytes[16];
    /* 0x12E0 */ s8 debugEnemyContact;
    /* 0x12E1 */ b8 debugUnused1;
    /* 0x12E2 */ b8 debugUnused2;
    /* 0x12E3 */ b8 musicEnabled;
    /* 0x12E4 */ PAD(2);
    /* 0x12E6 */ Vec3s savePos;
    /* 0x12EC */ VanillaSaveFileSummary summary;
    /* 0x1304 */ PAD(0x7C);
} VanillaSaveData; // size = 0x1380

typedef struct SaveFileSummary {
    /* 0x00 */ s32 timePlayed;
    /* 0x04 */ u8 spiritsRescued;
    /* 0x05 */ PAD(1);
    /* 0x06 */ s8 level;
    /* 0x07 */ MSG_BIN filename[8];
    /* 0x0F */ PAD(9);
} SaveFileSummary; // size = 0x18

typedef struct SaveData {
    /* 0x0000 */ char magicString[16]; /* "Mario Story 006" string */
    /* 0x0010 */ char modName[28]; /* always non-null for DX saves */
    /* 0x002C */ s8 majorVersion;
    /* 0x002D */ s8 minorVersion;
    /* 0x002E */ s8 patchVersion;
    /* 0x002F */ PAD(1);
    /* 0x0030 */ s32 crc1;
    /* 0x0034 */ s32 crc2;
    /* 0x0038 */ s32 saveSlot;
    /* 0x003C */ s32 saveCount;
    /* 0x0040 */ PlayerData player;
    /* 0x0468 */ u32 mapHash;
    /* 0x046C */ s16 entryID;
    /* 0x046E */ PAD(2);
    /* 0x0470 */ s32 enemyDefeatFlags[60][12];
    /* 0x0FB0 */ s32 globalFlags[64];
    /* 0x10B0 */ s8 globalBytes[512];
    /* 0x12B0 */ s32 areaFlags[8];
    /* 0x12D0 */ s8 areaBytes[16];
    /* 0x12E0 */ s8 debugEnemyContact;
    /* 0x12E1 */ b8 debugUnused1;
    /* 0x12E2 */ b8 debugUnused2;
    /* 0x12E3 */ b8 musicEnabled;
    /* 0x12E4 */ PAD(2);
    /* 0x12E6 */ Vec3s savePos;
    /* 0x12EC */ SaveFileSummary summary;
    /* 0x1304 */ PAD(0x7C);
} SaveData; // size = 0x1380

extern SaveData gCurrentSaveFile;

typedef struct SaveSlotMetadata {
    /* 0x00 */ char modName[28]; /* always non-null for DX saves */
    /* 0x1C */ b8 hasData;
    /* 0x1D */ b8 validData;
    /* 0x1E */ PAD(2);
} SaveSlotMetadata; // size = 0x20
