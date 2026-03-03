/// @file overlay.h
/// @brief Dynamically-linked code overlays.
///
/// Overlays allow loading and unloading code at runtime at any address.
///
/// Overlays are compiled separately from the main binary and appended to the ROM.
///
/// All public (non-static) symbols in an overlay are exported and accessible
/// via #ovl_sym(). Overlay code can transparently call functions and
/// access variables in the main binary with no special provisions.
///
/// Overlays are identified by name. Loading the same name twice returns the
/// cached instance.
///
/// Usage:
///
///     Overlay* mod = ovl_load("my_module", OVL_ACTOR);
///     void (*fn)(void) = ovl_sym(mod, "my_function");
///     fn();
///
/// C++ symbols are mangled. Use `extern "C"` to export with a clean name.

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

/// Returns a pointer to the exported symbol with the given name.
void* ovl_sym(const Overlay* mod, const char* name);

/// Searches all loaded overlays for the symbol name nearest to `addr`.
const char* ovl_resolve_addr(u32 addr, const char** outOverlayName,
                             u32* outDebugRomStart, u32* outDebugRomEnd,
                             u32* outOverlayBase);

#ifdef __cplusplus
}
#endif
