#ifndef _VERSIONING_H_
#define _VERSIONING_H_

#include "common.h"

void fio_deserialize_state();
void fio_serialize_state();

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
    /* 0x00B */ char pad_00B;
    /* 0x00C */ s16 coins;
    /* 0x00E */ s8 fortressKeyCount;
    /* 0x00F */ u8 starPieces;
    /* 0x010 */ s8 starPoints;
    /* 0x011 */ s8 unused_011;
    /* 0x012 */ s8 curPartner;
    /* 0x013 */ char pad_013;
    /* 0x014 */ VanillaPartnerData partners[12];
    /* 0x074 */ s16 keyItems[32];
    /* 0x0B4 */ s16 badges[128];
    /* 0x1B4 */ s16 invItems[10];
    /* 0x1C8 */ s16 storedItems[32];
    /* 0x208 */ s16 equippedBadges[64];
    /* 0x288 */ s8 unused_288;
    /* 0x289 */ s8 merleeSpellType;
    /* 0x28A */ s8 merleeCastsLeft;
    /* 0x28B */ char pad_28B;
    /* 0x28C */ s16 merleeTurnCount;
    /* 0x28E */ s8 maxStarPower;
    /* 0x28F */ char pad_28F;
    /* 0x290 */ s16 starPower;
    /* 0x292 */ s8 starBeamLevel;
    /* 0x293 */ char pad_293;
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
    /* 0x2BA */ char pad_2BA[2];
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
    /* 0x340 */ char pad_33E[0xEA];
} VanillaPlayerData; // size = 0x428

/// SaveData struct from unmodified Paper Mario
typedef struct VanillaSaveData {
    /* 0x0000 */ char magicString[16]; /* "Mario Story 006" string */
    /* 0x0010 */ char version[32]; /* always zero for vanilla saves */
    /* 0x0030 */ s32 crc1;
    /* 0x0034 */ s32 crc2;
    /* 0x0038 */ s32 saveSlot;
    /* 0x003C */ s32 saveCount;
    /* 0x0040 */ VanillaPlayerData player;
    /* 0x0468 */ s16 areaID;
    /* 0x046A */ s16 mapID;
    /* 0x046C */ s16 entryID;
    /* 0x046E */ char unk_46E[2];
    /* 0x0470 */ s32 enemyDefeatFlags[60][12];
    /* 0x0FB0 */ s32 globalFlags[64];
    /* 0x10B0 */ s8 globalBytes[512];
    /* 0x12B0 */ s32 areaFlags[8];
    /* 0x12D0 */ s8 areaBytes[16];
    /* 0x12E0 */ s8 debugEnemyContact;
    /* 0x12E0 */ b8 debugUnused1;
    /* 0x12E0 */ b8 debugUnused2;
    /* 0x12E0 */ b8 musicEnabled;
    /* 0x12E4 */ char unk_12E4[0x2];
    /* 0x12E6 */ Vec3s savePos;
    /* 0x12EC */ FileDisplayData metadata;
    /* 0x1304 */ char unk_1304[0x7C];
} VanillaSaveData; // size = 0x1380

#endif
