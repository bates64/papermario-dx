#pragma once

#include "common.h"
#include "audio.h"

#ifdef _LANGUAGE_C_PLUS_PLUS
extern "C" {
#endif

/// Largest encoded BGM the engine's playback buffer holds.
#define MAMAR_BGM_MAX_SIZE 0x5000

/// MamarReady's value once the game has booted. Memory holds leftover values
/// until then, so a flag alone could read as set.
#define MAMAR_READY 0x4D414D52 // 'MAMR'

enum MamarTrackMute {
    MAMAR_TRACK_PLAY,
    MAMAR_TRACK_MUTE,
    /// Silences every track that isn't soloed.
    MAMAR_TRACK_SOLO,
};

// Mamar, the music editor, plays songs it's editing by writing these through
// an emulator, finding each by name in the ELF:
//   1. Wait for MamarReady to be MAMAR_READY, without writing anything:
//      writing memory while the game boots can stop it booting.
//   2. Set MamarEnabled. The game switches to GAME_MODE_MAMAR, where it only
//      plays Mamar's song, and points MamarBGM at a buffer of
//      MAMAR_BGM_MAX_SIZE bytes.
//   3. Write the encoded BGM there, then MamarBGMSize, MamarVariation, and
//      MamarBankSong.
//   4. Increment MamarRequest to play it from its start.
// The other inputs take effect on the next frame.

extern b32 MamarEnabled;
extern u32 MamarReady;
extern u8* MamarBGM;
extern s32 MamarBGMSize;
extern s32 MamarVariation;
/// ID of the song whose auxiliary banks Mamar's song loads, or -1 for none.
extern s32 MamarBankSong;
extern u32 MamarRequest;
extern b32 MamarPaused;
extern s32 MamarAmbience;
extern s32 MamarTrackMute[16];

/// Tempo of the song playing in hundredths of a beat per minute, written by
/// the game every frame.
extern s32 MamarTempo;

void dx_mamar_update(void);
b32 dx_mamar_load_song(BGMHeader* bgmFile, BGMPlayer* player, AuResult* result);

void state_init_mamar(void);
void state_step_mamar(void);
void state_drawUI_mamar(void);

#ifdef _LANGUAGE_C_PLUS_PLUS
} // extern "C"
#endif
