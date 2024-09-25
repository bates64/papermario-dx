#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include "common.h"

/// Add `itemID` to player inventory and return inventory slot in which it was placed.
/// @returns the index of the new item in the player's inventory, or -1 if there was no room
s32 add_item(s32 itemID);

/// Remove first instance of `itemID` found in player inventory.
/// @returns the index of the removed item in the player's inventory, or -1 none was found
s32 remove_item(s32 itemID);

/// Check whether player has `itemID` in their inventory.
/// @returns boolean 'does player have item?'
b32 has_item(s32 itemID);

/// Search player inventory for `itemID` and return first matching array index.
/// @returns the index of the given item in the player's inventory, or -1 if not found
s32 find_item(s32 itemID);

/// Search player inventory for `itemID` and count the number matches.
/// @returns the number of items matching `itemID`
s32 count_item(s32 itemID);

/// @returns whether the player has `itemID` as an equipped badge
b32 is_badge_equipped(s32 itemID);

/// @returns the number of consumables in player inventory
s32 get_consumables_count(void);

/// @returns the available room for consumables in player inventory
s32 get_consumables_empty(void);

/// Add `itemID` to player storage and return slot in which it was placed.
/// @returns the index of the new item in player storage, or -1 if there was no room
s32 store_item(s32 itemID);

/// @returns the number of consumables in player storage
s32 get_stored_count(void);

/// @returns the available room in player storage
s32 get_stored_empty(void);

/// @returns whether `itemID` is a Consumable
b32 item_is_consumable(s32 itemID);

/// @returns whether `itemID` is a Badge
b32 item_is_badge(s32 itemID);

/// @returns whether `itemID` is a Key Item
b32 item_is_key(s32 itemID);

/// Recover player HP
/// @param amt the amount to recover, -1 for full, -2 for full and increase max by 1 (unused)
/// @return the new HP value, after recovery has been applied
s32 recover_hp(s32 amt);

/// Recover player FP
/// @param amt the amount to recover, -1 for full, -2 for full and increase max by 1 (unused)
/// @return the new FP value, after recovery has been applied
s32 recover_fp(s32 amt);

#endif
