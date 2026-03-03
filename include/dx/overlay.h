/// @file overlay.h
/// @brief Dynamically-linked code overlays.
///
/// Overlays allow loading and unloading code at runtime at any address.
///
/// Overlays are compiled separately from the main binary and appended to the ROM.
///
/// Symbols marked with the `export` macro are accessible via #ovl_import().
/// Overlay code can transparently call functions and access variables in the
/// main binary with no special provisions.
///
/// Overlays are identified by name. Loading the same name twice returns the
/// cached instance.
///
/// Usage:
///
///     Overlay* ovl = ovl_load("my_overlay", OVL_ACTOR);
///     void (*fn)(void) = ovl_import(ovl, "my_function");
///     fn();

#pragma once

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Overlay Overlay;

typedef enum {
    OVL_ACTOR, ///< `assets/*/battle/actor/*`
    OVL_NUM_TYPES,
} OverlayType;

/// Load an overlay by name, or return a cached instance if already loaded.
Overlay* ovl_load(const char* name, OverlayType type);

/// Unload an overlay.
void ovl_unload(Overlay* mod);

/// Unload all overlays of a given type.
void ovl_unload_type(OverlayType type);

/// Look up an exported symbol by name. Returns nullptr if not found.
void* ovl_import(const Overlay* mod, const char* name);

/// Searches all loaded overlays for the symbol name nearest to `addr`.
const char* ovl_resolve_addr(u32 addr, const char** outOverlayName,
                             u32* outDebugRomStart, u32* outDebugRomEnd,
                             u32* outOverlayBase);

#ifdef __cplusplus
}
#endif
