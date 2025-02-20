// Stolen from HackerSM64

#pragma once

#include "common.h"
#include "dx/config.h"

#if defined(USE_PROFILER) && defined(PUPPYPRINT_DEBUG)
/**
 * Toggle this define to enable verbose audio profiling with Pupprprint Debug.
*/
#define AUDIO_PROFILING
#endif

/// Toggle this define to enable verbose graphics profiling.
#define GFX_PROFILING

#define OS_GET_COUNT_INLINE(x) asm volatile("mfc0 %0, $9" : "=r"(x): )

#define PROFILING_BUFFER_SIZE 64

#define AUDIO_SUBSET_ENTRIES \
    PROFILER_TIME_SUB_AUDIO_START, \
    PROFILER_TIME_SUB_AUDIO_SEQUENCES = PROFILER_TIME_SUB_AUDIO_START, \
    PROFILER_TIME_SUB_AUDIO_SEQUENCES_SCRIPT, \
    PROFILER_TIME_SUB_AUDIO_SEQUENCES_RECLAIM, \
    PROFILER_TIME_SUB_AUDIO_SEQUENCES_PROCESSING, \
    PROFILER_TIME_SUB_AUDIO_SYNTHESIS, \
    PROFILER_TIME_SUB_AUDIO_SYNTHESIS_PROCESSING, \
    PROFILER_TIME_SUB_AUDIO_SYNTHESIS_ENVELOPE_REVERB, \
    PROFILER_TIME_SUB_AUDIO_SYNTHESIS_DMA, \
    PROFILER_TIME_SUB_AUDIO_UPDATE, \
    PROFILER_TIME_SUB_AUDIO_END

#define GFX_SUBSET_ENTRIES \
    PROFILER_TIME_SUB_GFX_START, \
    PROFILER_TIME_SUB_GFX_UPDATE, \
    PROFILER_TIME_SUB_GFX__DUMMY, /* fixes entities for some reason */ \
    PROFILER_TIME_SUB_GFX_ENTITIES, \
    PROFILER_TIME_SUB_GFX_MODELS, \
    PROFILER_TIME_SUB_GFX_PLAYER, \
    PROFILER_TIME_SUB_GFX_NPCS, \
    PROFILER_TIME_SUB_GFX_WORKERS, \
    PROFILER_TIME_SUB_GFX_EFFECTS, \
    PROFILER_TIME_SUB_GFX_RENDER_TASKS, \
    PROFILER_TIME_SUB_GFX_HUD_ELEMENTS, \
    PROFILER_TIME_SUB_GFX_BACK_UI, \
    PROFILER_TIME_SUB_GFX_FRONT_UI, \
    PROFILER_TIME_SUB_GFX_END

// NOLINTNEXTLINE(readability-enum-initial-value)
enum ProfilerTime {
    PROFILER_TIME_FPS,
    PROFILER_TIME_CONTROLLERS,
    PROFILER_TIME_WORKERS,
    PROFILER_TIME_TRIGGERS,
    PROFILER_TIME_EVT,
    PROFILER_TIME_MESSAGES,
    PROFILER_TIME_HUD_ELEMENTS,
    PROFILER_TIME_STEP_GAME_MODE,
    PROFILER_TIME_ENTITIES,
#ifdef PUPPYPRINT_DEBUG
    PROFILER_TIME_PUPPYPRINT1,
    PROFILER_TIME_PUPPYPRINT2,
#endif
#ifdef GFX_PROFILING
    GFX_SUBSET_ENTRIES,
    PROFILER_TIME_GFX = PROFILER_TIME_SUB_GFX_END,
#else
    PROFILER_TIME_GFX,
#endif
#ifdef AUDIO_PROFILING
    AUDIO_SUBSET_ENTRIES,

    PROFILER_TIME_AUDIO = PROFILER_TIME_SUB_AUDIO_END,
#else
    PROFILER_TIME_AUDIO,
#endif
    PROFILER_TIME_TOTAL,
    PROFILER_TIME_RSP_GFX,
    PROFILER_TIME_RSP_AUDIO,
    PROFILER_TIME_TMEM,
    PROFILER_TIME_PIPE,
    PROFILER_TIME_CMD,

    // state_world
    PROFILE_TIME_WORLD_ENCOUNTERS,
    PROFILE_TIME_WORLD_NPCS,
    PROFILE_TIME_WORLD_PLAYER,
    PROFILE_TIME_WORLD_ITEM_ENTITIES,
    PROFILE_TIME_WORLD_EFFECTS,
    PROFILE_TIME_WORLD_CAMERAS,

    PROFILER_TIME_COUNT // Must be last!
};

enum ProfilerRSPTime {
    PROFILER_RSP_GFX,
    PROFILER_RSP_AUDIO,
    PROFILER_RSP_COUNT
};

enum ProfilerDeltaTime {
    PROFILER_DELTA_COLLISION,
#ifdef PUPPYPRINT_DEBUG
    PROFILER_DELTA_PUPPYPRINT1,
    PROFILER_DELTA_PUPPYPRINT2
#endif
};

#ifndef PUPPYPRINT_DEBUG
#define PROFILER_TIME_PUPPYPRINT1 0
#define PROFILER_TIME_PUPPYPRINT2 0
#define PROFILER_DELTA_PUPPYPRINT1 0
#define PROFILER_DELTA_PUPPYPRINT2 0
#endif

#ifdef USE_PROFILER
typedef struct {
    u32 counts[PROFILING_BUFFER_SIZE];
    u32 total;
} ProfileTimeData;
extern ProfileTimeData all_profiling_data[PROFILER_TIME_COUNT];

void profiler_update(enum ProfilerTime which, u32 delta);
void profiler_print_times();
void profiler_frame_setup();
void profiler_rsp_started(enum ProfilerRSPTime which);
void profiler_rsp_completed(enum ProfilerRSPTime which);
void profiler_rsp_resumed();
void profiler_gfx_started();
void profiler_gfx_completed();
void profiler_audio_started();
void profiler_audio_completed();
#ifdef PUPPYPRINT_DEBUG
void profiler_collision_reset();
void profiler_collision_completed();
void profiler_collision_update(u32 time);
#else
#define profiler_collision_reset()
#define profiler_collision_completed()
#define profiler_collision_update(time)
#endif
u32 profiler_get_delta(enum ProfilerDeltaTime which);
u32 profiler_get_cpu_microseconds();
u32 profiler_get_rsp_microseconds();
u32 profiler_get_rdp_microseconds();
// See profiling.c to see why profiler_rsp_yielded isn't its own function
static ALWAYS_INLINE void profiler_rsp_yielded() {
    profiler_rsp_resumed();
#define PROFILER_GET_SNAPSHOT() u32 first = osGetCount()
#define PROFILER_GET_SNAPSHOT_TYPE(type) u32 first = profiler_get_delta(type)
}
#else
#define PROFILER_GET_SNAPSHOT()
#define PROFILER_GET_SNAPSHOT_TYPE(type)
#define profiler_update(which, delta)
#define profiler_print_times()
#define profiler_frame_setup()
#define profiler_rsp_started(which)
#define profiler_rsp_completed(which)
#define profiler_rsp_resumed()
#define profiler_audio_started()
#define profiler_audio_completed()
#define profiler_rsp_yielded()
#define profiler_collision_reset()
#define profiler_collision_completed()
#define profiler_collision_update(time)
#define profiler_get_delta(which) 0
#define profiler_get_cpu_microseconds() 0
#define profiler_get_rsp_microseconds() 0
#define profiler_get_rdp_microseconds() 0
#endif

#ifdef GFX_PROFILING
#define GFX_SUBSET_SIZE PROFILER_TIME_SUB_GFX_END - PROFILER_TIME_SUB_GFX_START
extern u32 gfx_subset_starts[GFX_SUBSET_SIZE];
extern u32 gfx_subset_tallies[GFX_SUBSET_SIZE];

static ALWAYS_INLINE void profiler_gfx_subset_switch_func(enum ProfilerTime complete, enum ProfilerTime start) {
    u32 time;
    OS_GET_COUNT_INLINE(time);

    gfx_subset_tallies[complete] += time - gfx_subset_starts[complete];
    gfx_subset_starts[start] = time;
}

static ALWAYS_INLINE void profiler_gfx_subset_complete_and_switch_func(enum ProfilerTime complete1, enum ProfilerTime complete2, enum ProfilerTime start) {
    u32 time;
    OS_GET_COUNT_INLINE(time);

    gfx_subset_tallies[complete1] += time - gfx_subset_starts[complete1];
    gfx_subset_tallies[complete2] += time - gfx_subset_starts[complete2];
    gfx_subset_starts[start] = time;
}

static ALWAYS_INLINE void profiler_gfx_subset_start_shared_func(enum ProfilerTime first, enum ProfilerTime new) {
    gfx_subset_starts[new] = gfx_subset_starts[first];
}

static ALWAYS_INLINE void profiler_gfx_subset_start_func(enum ProfilerTime index) {
    OS_GET_COUNT_INLINE(gfx_subset_starts[index]);
}

static ALWAYS_INLINE void profiler_gfx_subset_complete_func(enum ProfilerTime index) {
    u32 time;
    OS_GET_COUNT_INLINE(time);

    gfx_subset_tallies[index] += time - gfx_subset_starts[index];
}

#define GFX_PROFILER_SWITCH(complete, begin) profiler_gfx_subset_switch_func(complete - PROFILER_TIME_SUB_GFX_START, begin - PROFILER_TIME_SUB_GFX_START)
#define GFX_PROFILER_COMPLETE_AND_SWITCH(complete1, complete2, begin) profiler_gfx_subset_complete_and_switch_func(complete1 - PROFILER_TIME_SUB_GFX_START, \
    complete2 - PROFILER_TIME_SUB_GFX_START, begin - PROFILER_TIME_SUB_GFX_START)
#define GFX_PROFILER_START_SHARED(first, new) profiler_gfx_subset_start_shared_func(first - PROFILER_TIME_SUB_GFX_START, new - PROFILER_TIME_SUB_GFX_START)
#define GFX_PROFILER_START(which) profiler_gfx_subset_start_func(which - PROFILER_TIME_SUB_GFX_START)
#define GFX_PROFILER_COMPLETE(which) profiler_gfx_subset_complete_func(which - PROFILER_TIME_SUB_GFX_START)
#else
enum ProfilerTimeGFXUnused {
    GFX_SUBSET_ENTRIES
};
#define GFX_PROFILER_SWITCH(complete, begin)
#define GFX_PROFILER_COMPLETE_AND_SWITCH(complete1, complete2, begin)
#define GFX_PROFILER_START_SHARED(first, new)
#define GFX_PROFILER_START(which)
#define GFX_PROFILER_COMPLETE(which)
#endif

#ifdef AUDIO_PROFILING
#define AUDIO_SUBSET_SIZE PROFILER_TIME_SUB_AUDIO_END - PROFILER_TIME_SUB_AUDIO_START
extern u32 audio_subset_starts[AUDIO_SUBSET_SIZE];
extern u32 audio_subset_tallies[AUDIO_SUBSET_SIZE];

static ALWAYS_INLINE void profiler_audio_subset_switch_func(enum ProfilerTime complete, enum ProfilerTime start) {
    u32 time;
    OS_GET_COUNT_INLINE(time);

    audio_subset_tallies[complete] += time - audio_subset_starts[complete];
    audio_subset_starts[start] = time;
}

static ALWAYS_INLINE void profiler_audio_subset_complete_and_switch_func(enum ProfilerTime complete1, enum ProfilerTime complete2, enum ProfilerTime start) {
    u32 time;
    OS_GET_COUNT_INLINE(time);

    audio_subset_tallies[complete1] += time - audio_subset_starts[complete1];
    audio_subset_tallies[complete2] += time - audio_subset_starts[complete2];
    audio_subset_starts[start] = time;
}

static ALWAYS_INLINE void profiler_audio_subset_start_shared_func(enum ProfilerTime first, enum ProfilerTime new) {
    audio_subset_starts[new] = audio_subset_starts[first];
}

static ALWAYS_INLINE void profiler_audio_subset_start_func(enum ProfilerTime index) {
    OS_GET_COUNT_INLINE(audio_subset_starts[index]);
}

static ALWAYS_INLINE void profiler_audio_subset_complete_func(enum ProfilerTime index) {
    u32 time;
    OS_GET_COUNT_INLINE(time);

    audio_subset_tallies[index] += time - audio_subset_starts[index];
}

#define AUDIO_PROFILER_SWITCH(complete, begin) profiler_audio_subset_switch_func(complete - PROFILER_TIME_SUB_AUDIO_START, begin - PROFILER_TIME_SUB_AUDIO_START)
#define AUDIO_PROFILER_COMPLETE_AND_SWITCH(complete1, complete2, begin) profiler_audio_subset_complete_and_switch_func(complete1 - PROFILER_TIME_SUB_AUDIO_START, \
    complete2 - PROFILER_TIME_SUB_AUDIO_START, begin - PROFILER_TIME_SUB_AUDIO_START)
#define AUDIO_PROFILER_START_SHARED(first, new) profiler_audio_subset_start_shared_func(first - PROFILER_TIME_SUB_AUDIO_START, new - PROFILER_TIME_SUB_AUDIO_START)

// These two are unused by the default audio profiler; left in for cases of manual profiling of smaller functions as needed
#define AUDIO_PROFILER_START(which) profiler_audio_subset_start_func(which - PROFILER_TIME_SUB_AUDIO_START)
#define AUDIO_PROFILER_COMPLETE(which) profiler_audio_subset_complete_func(which - PROFILER_TIME_SUB_AUDIO_START)
#else // AUDIO_PROFILING
// NOLINTNEXTLINE(readability-enum-initial-value)
enum ProfilerTimeAudioUnused {
    AUDIO_SUBSET_ENTRIES
};
#define AUDIO_PROFILER_SWITCH(complete, begin)
#define AUDIO_PROFILER_COMPLETE_AND_SWITCH(complete1, complete2, begin)
#define AUDIO_PROFILER_START_SHARED(first, new)

// These two are unused by the default audio profiler; left in for cases of manual profiling of smaller functions as needed
#define AUDIO_PROFILER_START(which)
#define AUDIO_PROFILER_COMPLETE(which)
#endif // AUDIO_PROFILING
