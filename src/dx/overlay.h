#pragma once

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Overlay Overlay;

typedef enum {
    OVL_ACTOR, ///< `battle/actor/*`
    OVL_MAP,   ///< `world/area_*/*/` -- only one loaded at a time
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

/// Unload an overlay. No-op if not loaded.
void ovl_unload(Overlay* ovl);

/// Unload all overlays of a given type.
void ovl_unload_type(OverlayType type);

/// Look up an exported symbol by name. Returns nullptr if not found.
void* ovl_import(const Overlay* ovl, const char* name);

/// Searches all loaded overlays for the symbol nearest to `addr`.
/// Returns an empty string (not NULL) if the address is in an overlay but has
/// no matching export, so the caller can still use the debug symbol table.
/// Returns nullptr if the address is not in any loaded overlay.
const char* ovl_resolve_addr(u32 addr, const char** outOverlayName,
                             u32* outDebugRomStart, u32* outDebugRomEnd,
                             u32* outOverlayBase);

#ifdef __cplusplus
}
#endif
