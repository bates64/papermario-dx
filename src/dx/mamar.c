#include "dx/mamar.h"
#include "audio/core.h"
#include "audio/private.h"
#include "game_modes.h"
#include <string.h>

BSS b32 MamarEnabled;
BSS u32 MamarReady;
BSS u8* MamarBGM;
BSS s32 MamarBGMSize;
BSS s32 MamarVariation;
s32 MamarBankSong = -1;
BSS u32 MamarRequest;
BSS b32 MamarPaused;
s32 MamarAmbience = AMBIENT_SILENCE;
BSS s32 MamarTrackMute[16];
BSS s32 MamarTempo;

/// The request the playing song answers.
BSS static u32 PlayingRequest;
/// Which of two song IDs Mamar's song plays as, alternating so that
/// bgm_set_song treats each request as a new song. Both load Mamar's BGM.
BSS static s32 PlayingSongID;
BSS static b32 IsPlaying;
BSS static b32 IsSongPaused;

b32 dx_mamar_load_song(BGMHeader* bgmFile, BGMPlayer* player, AuResult* result) {
    InitSongEntry* bankSong;
    AuGlobals* globals = gSoundGlobals;
    s32 i;

    if (get_game_mode() != GAME_MODE_MAMAR || MamarBGM == nullptr) {
        return false;
    }

    if (au_bgm_player_is_active(player)) {
        *result = AU_ERROR_201;
        return true;
    }

    memcpy(bgmFile, MamarBGM, CLAMP(MamarBGMSize, 0, MAMAR_BGM_MAX_SIZE));

    if (MamarBankSong >= 0 && MamarBankSong < globals->songListLength) {
        bankSong = &globals->songList[MamarBankSong];

        for (i = 0; i < ARRAY_COUNT(bankSong->bkFileIndex); i++) {
            u16 bkFileIndex = bankSong->bkFileIndex[i];

            if (bkFileIndex != 0) {
                SBNFileEntry* bkFileEntry = &globals->sbnFileList[bkFileIndex];

                if ((bkFileEntry->data >> 0x18) == AU_FMT_BK) {
                    au_load_aux_bank((bkFileEntry->offset & 0xFFFFFF) + globals->baseRomOffset, i);
                }
            }
        }
    }

    player->songID = PlayingSongID;
    player->bgmFile = bgmFile;
    player->bgmFileIndex = 0;
    *result = bgmFile->name;
    return true;
}

static void update_track_mutes(void) {
    b32 isAnySolo = false;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(MamarTrackMute); i++) {
        if (MamarTrackMute[i] == MAMAR_TRACK_SOLO) {
            isAnySolo = true;
        }
    }

    for (i = 0; i < ARRAY_COUNT(MamarTrackMute); i++) {
        b32 isAudible;

        switch (MamarTrackMute[i]) {
            case MAMAR_TRACK_SOLO:
                isAudible = true;
                break;
            case MAMAR_TRACK_MUTE:
                isAudible = false;
                break;
            default:
                isAudible = !isAnySolo;
                break;
        }

        au_bgm_set_prox_mix_fade(gBGMPlayerA, &gBGMPlayerA->tracks[i], isAudible ? AU_MAX_VOLUME_8 : 0, 0);
    }
}

void dx_mamar_update(void) {
    s32 mode = get_game_mode();

    // The general heap is created during startup.
    if (mode == GAME_MODE_STARTUP) {
        return;
    }

    MamarReady = MAMAR_READY;

    if (MamarEnabled && mode != GAME_MODE_MAMAR) {
        set_game_mode(GAME_MODE_MAMAR);
    }
}

void state_init_mamar(void) {
    if (MamarBGM == nullptr) {
        MamarBGM = general_heap_malloc(MAMAR_BGM_MAX_SIZE);
    }

    PlayingRequest = MamarRequest;
    IsPlaying = false;
    bgm_set_song(0, -1, 0, 0, 8);
}

void state_step_mamar(void) {
    MusicControlData* music = &gMusicControlData[0];

    // A song requested while paused waits until Mamar unpauses. Starting it and
    // then pausing it can pause the song it replaces instead, leaving it playing.
    if (MamarRequest != PlayingRequest && !MamarPaused) {
        PlayingRequest = MamarRequest;
        PlayingSongID = PlayingSongID == 0 ? 1 : 0;
        IsPlaying = true;
        IsSongPaused = false;
    }

    if (IsPlaying) {
        bgm_set_song(0, PlayingSongID, MamarVariation, 0, 8);
    }

    // Pausing fails until the song has started, so keep trying.
    if (IsPlaying && MamarPaused != IsSongPaused && (music->flags & MUSIC_FLAG_PLAYING)) {
        AuResult result =
            MamarPaused ? snd_song_request_pause(music->songName) : snd_song_request_unpause(music->songName);

        if (result == AU_RESULT_OK) {
            IsSongPaused = MamarPaused;
        }
    }

    play_ambient_sounds(MamarPaused ? AMBIENT_SILENCE : MamarAmbience, 0);
    update_track_mutes();
    MamarTempo = gBGMPlayerA->masterTempo * 100 / BGM_TEMPO_SCALE;
}

void state_drawUI_mamar(void) {
}
