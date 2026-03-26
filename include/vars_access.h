#ifndef _VARS_ACCESS_H_
#define _VARS_ACCESS_H_

#include "common.h"

/// Set value of saved game byte. `index` can be either a global byte reference (`GB_*`) or index.
/// Returns previous value of the saved byte.
s8 set_global_byte(s32 index, s32 value);

/// Get value of saved game byte. `index` can be either a global byte reference (`GB_*`) or index.
/// Returns value of the saved byte.
s32 get_global_byte(s32 index);

/// Store a short in two consecutive saved game bytes. `index` can be either a global byte
/// reference (`GB_*`) or index to the lowest byte.
/// Returns previous value of the saved short.
s16 set_global_short(s32 index, s32 value);

/// Retrieve a short from two consecutive saved game bytes. `index` can be either a global byte
/// reference (`GB_*`) or index to the lowest byte.
/// Returns value of the saved short.
s16 get_global_short(s32 index);

/// Store a word in four consecutive saved game bytes. `index` can be either a global byte
/// reference (`GB_*`) or index to the lowest byte.
/// Returns previous value of the saved word.
s32 set_global_word(s32 index, s32 value);

/// Retrieve a word from four consecutive saved game bytes. `index` can be either a global byte
/// reference (`GB_*`) or index to the lowest byte.
/// Returns value of the saved word.
s32 get_global_word(s32 index);

s32 set_global_flag(s32 index);
s32 clear_global_flag(s32 index);
s32 get_global_flag(s32 index);

s8 set_area_byte(s32 index, s32 value);
s32 get_area_byte(s32 index);
s32 set_area_flag(s32 index);
s32 clear_area_flag(s32 index);
s32 get_area_flag(s32 index);

#endif
