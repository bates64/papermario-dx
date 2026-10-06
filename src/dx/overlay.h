#pragma once

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Overlay Overlay;

#define OVL_NAME_MAX 64

#define EFFECT_OVERLAY_SLOT_COUNT 16
#define EFFECT_OVERLAY_SLOT_SIZE 0x1000

#define MAP_OVERLAY_SLOT_SIZE 0x27FF0
#define BATTLE_PARTNER_OVERLAY_SLOT_SIZE 0x5000
#define ACTION_COMMAND_OVERLAY_SLOT_SIZE 0x3000
#define BATTLE_SCRIPT_OVERLAY_SLOT_SIZE 0x4000
#define BATTLE_MENU_OVERLAY_SLOT_SIZE 0x10000

typedef enum {
    OVL_EFFECT,         ///< `effects/*` -- loaded into a fixed-size slot pool
    OVL_MAP,            ///< `world/area/*/*` -- only one loaded at a time
    OVL_ACTION,         ///< `world/action/*` -- only one loaded at a time
    OVL_PARTNER,        ///< `world/partner/*`
    OVL_BATTLE_AREA,    ///< `battle/area/*` -- formation tables, retained through battle teardown
    OVL_STAGE,          ///< `battle/stage/*` -- retained through battle teardown
    OVL_ACTOR,          ///< `battle/actor/*`
    OVL_BATTLE_PARTNER, ///< `battle/partner/*` -- only one loaded at a time
    OVL_ACTION_CMD,     ///< `battle/action_cmd/*` -- only one loaded at a time
    OVL_BATTLE_SCRIPT,  ///< `battle/move/*` -- only one loaded at a time
    OVL_BATTLE_MENU,    ///< battle menu implementation
    OVL_ENTITY,         ///< `entity/*` -- retained for the current map
    OVL_NUM_TYPES,
} OverlayType;

/// Load an overlay by name, or return a cached instance if already loaded.
///
/// When you are done with this overlay, you must call #ovl_unload or #ovl_unload_type.
///
/// ## Panics
/// - No overlay named `name` exists for the given `type`.
/// - All overlay slots are occupied.
/// - The overlay data is corrupt.
__attribute__((returns_nonnull))
Overlay* ovl_load(const char* name, OverlayType type);

/// Enumerate the ROM catalog without loading overlays. Names are copied to the caller.
s32 ovl_get_count(OverlayType type);
b32 ovl_get_name(OverlayType type, s32 index, char name[OVL_NAME_MAX]);

/// Unload an overlay. No-op if not loaded.
void ovl_unload(Overlay* ovl);

/// Unload all overlays of a given type.
void ovl_unload_type(OverlayType type);

/// Restore a fixed overlay whose RAM image was overwritten externally.
///
/// This reloads the overlay into its existing address without invoking the
/// overwritten image's destructors or changing its descriptor identity.
void ovl_restore_type(OverlayType type);

/// Look up an exported symbol by name. Returns nullptr if not found.
void* ovl_import(const Overlay* ovl, const char* name);

/// Look up a declared symbol using its C name and function/data type.
#define OVL_IMPORT_SYMBOL(overlay, symbol) \
    ((__typeof__(&(symbol)))ovl_import((overlay), #symbol))

/// Searches all loaded overlays for the symbol nearest to `addr`.
/// Returns an empty string (not nullptr) if the address is in an overlay but has
/// no matching export, so the caller can still use the debug symbol table.
/// Returns nullptr if the address is not in any loaded overlay.
const char* ovl_resolve_addr(u32 addr, const char** outOverlayName,
                             u32* outDebugRomStart, u32* outDebugRomEnd,
                             u32* outOverlayBase);

#ifdef __cplusplus
}
#endif
