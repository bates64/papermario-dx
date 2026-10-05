#include "common.h"
#include "vars_access.h"
#include "dx/versioning.h"

void clear_saved_variables(void) {
    SaveData* saveFile = &gCurrentSaveFile;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(saveFile->globalFlags); i++) {
        saveFile->globalFlags[i] = 0;
    }

    for (i = 0; i < ARRAY_COUNT(saveFile->globalBytes); i++) {
        saveFile->globalBytes[i] = 0;
    }

    for (i = 0; i < ARRAY_COUNT(saveFile->areaFlags); i++) {
        saveFile->areaFlags[i] = 0;
    }

    for (i = 0; i < ARRAY_COUNT(saveFile->areaBytes); i++) {
        saveFile->areaBytes[i] = 0;
    }
}

void clear_area_flags(void) {
    SaveData* saveFile = &gCurrentSaveFile;
    s32 i;

    if (gGameStatusPtr->didAreaChange) {
        for (i = 0; i < ARRAY_COUNT(saveFile->areaFlags); i++) {
            saveFile->areaFlags[i] = 0;
        }

        for (i = 0; i < ARRAY_COUNT(saveFile->areaBytes); i++) {
            saveFile->areaBytes[i] = 0;
        }
    }
}

s32 clear_global_flag(s32 index) {
    s32 wordIdx;
    s32 bitIdx;
    SaveData* saveFile;
    s32 flag;

    if (index <= EVT_GAME_FLAG_CUTOFF) {
        index = EVT_INDEX_OF_GAME_FLAG(index);
    }

    wordIdx = index / 32;
    bitIdx = index % 32;

    saveFile = &gCurrentSaveFile;
    flag = saveFile->globalFlags[wordIdx] & (1 << bitIdx);

    if (flag != 0) {
        flag = 1;
    }

    saveFile->globalFlags[wordIdx] &= ~(1 << bitIdx);
    return flag;
}

s32 set_global_flag(s32 index) {
    SaveData* saveFile;
    s32 wordIdx;
    s32 bitIdx;
    s32 flag;

    if (index <= EVT_GAME_FLAG_CUTOFF) {
        index = EVT_INDEX_OF_GAME_FLAG(index);
    }

    wordIdx = index / 32;
    bitIdx = index % 32;

    saveFile = &gCurrentSaveFile;
    flag = saveFile->globalFlags[wordIdx] & (1 << bitIdx);

    if (flag != 0) {
        flag = 1;
    }

    saveFile->globalFlags[wordIdx] |= (1 << bitIdx);
    return flag;
}

s32 get_global_flag(s32 index) {
    s32 wordIdx;
    s32 bitIdx;
    s32 flag;

    if (index <= EVT_GAME_FLAG_CUTOFF) {
        index = EVT_INDEX_OF_GAME_FLAG(index);
    }

    wordIdx = index / 32;
    bitIdx = index % 32;
    flag = gCurrentSaveFile.globalFlags[wordIdx] & (1 << bitIdx);

    if (flag != 0) {
        flag = 1;
    }
    return flag;
}

s8 set_global_byte(s32 index, s32 value) {
    if (index <= EVT_GAME_BYTE_CUTOFF) {
        index = EVT_INDEX_OF_GAME_BYTE(index);
    }

    s32 ret = gCurrentSaveFile.globalBytes[index];
    gCurrentSaveFile.globalBytes[index] = value;
    return ret;
}

s32 get_global_byte(s32 index) {
    if (index <= EVT_GAME_BYTE_CUTOFF) {
        index = EVT_INDEX_OF_GAME_BYTE(index);
    }

    return gCurrentSaveFile.globalBytes[index];
}

s16 set_global_short(s32 index, s32 value) {
    if (index <= EVT_GAME_BYTE_CUTOFF) {
        index = EVT_INDEX_OF_GAME_BYTE(index);
    }

    u8 b0 = gCurrentSaveFile.globalBytes[index];
    u8 b1 = gCurrentSaveFile.globalBytes[index + 1];
    s16 ret = (b0 << 8) | b1;

    gCurrentSaveFile.globalBytes[index] = value >> 8;
    gCurrentSaveFile.globalBytes[index + 1] = value;
    return ret;
}

s16 get_global_short(s32 index) {
    if (index <= EVT_GAME_BYTE_CUTOFF) {
        index = EVT_INDEX_OF_GAME_BYTE(index);
    }

    u8 b0 = gCurrentSaveFile.globalBytes[index];
    u8 b1 = gCurrentSaveFile.globalBytes[index + 1];
    return (b0 << 8) | b1;
}

s32 set_global_word(s32 index, s32 value) {
    if (index <= EVT_GAME_BYTE_CUTOFF) {
        index = EVT_INDEX_OF_GAME_BYTE(index);
    }

    u8 b0 = gCurrentSaveFile.globalBytes[index];
    u8 b1 = gCurrentSaveFile.globalBytes[index + 1];
    u8 b2 = gCurrentSaveFile.globalBytes[index + 2];
    u8 b3 = gCurrentSaveFile.globalBytes[index + 3];
    s32 ret = ((u32) b0 << 24) | (b1 << 16) | (b2 << 8) | b3;

    gCurrentSaveFile.globalBytes[index] = value >> 24;
    gCurrentSaveFile.globalBytes[index + 1] = value >> 16;
    gCurrentSaveFile.globalBytes[index + 2] = value >> 8;
    gCurrentSaveFile.globalBytes[index + 3] = value;
    return ret;
}

s32 get_global_word(s32 index) {
    if (index <= EVT_GAME_BYTE_CUTOFF) {
        index = EVT_INDEX_OF_GAME_BYTE(index);
    }

    u8 b0 = gCurrentSaveFile.globalBytes[index];
    u8 b1 = gCurrentSaveFile.globalBytes[index + 1];
    u8 b2 = gCurrentSaveFile.globalBytes[index + 2];
    u8 b3 = gCurrentSaveFile.globalBytes[index + 3];
    return ((u32) b0 << 24) | (b1 << 16) | (b2 << 8) | b3;
}

s32 clear_area_flag(s32 index) {
    s32 wordIdx = index / 32;
    s32 bitIdx = index % 32;
    SaveData* saveFile = &gCurrentSaveFile;
    s32 flag = saveFile->areaFlags[wordIdx] & (1 << bitIdx);

    if (flag != 0) {
        flag = 1;
    }

    saveFile->areaFlags[wordIdx] &= ~(1 << bitIdx);
    return flag;
}

s32 set_area_flag(s32 index) {
    s32 wordIdx = index / 32;
    s32 bitIdx = index % 32;
    SaveData* saveFile = &gCurrentSaveFile;
    s32 flag = saveFile->areaFlags[wordIdx] & (1 << bitIdx);

    if (flag != 0) {
        flag = 1;
    }

    saveFile->areaFlags[wordIdx] |= 1 << bitIdx;
    return flag;
}

s32 get_area_flag(s32 index) {
    s32 wordIdx = index / 32;
    s32 bitIdx = index % 32;
    s32 flag = gCurrentSaveFile.areaFlags[wordIdx] & (1 << bitIdx);

    if (flag != 0) {
        flag = 1;
    }

    return flag;
}

s8 set_area_byte(s32 index, s32 value) {
    SaveData* saveFile = &gCurrentSaveFile;
    s32 ret = saveFile->areaBytes[index];

    saveFile->areaBytes[index] = value;
    return ret;
}

s32 get_area_byte(s32 index) {
    return gCurrentSaveFile.areaBytes[index];
}
