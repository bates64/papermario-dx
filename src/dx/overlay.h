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

/// Searches all loaded overlays for the symbol name nearest to `addr`.
const char* ovl_resolve_addr(u32 addr, const char** outOverlayName,
                             u32* outDebugRomStart, u32* outDebugRomEnd,
                             u32* outOverlayBase);

#ifdef __cplusplus
}
#endif
