#include "common.h"
#include "npc.h"

void bgm_update_volume(void);
void bgm_set_target_volume(s16 volume);

BSS s16 MusicDefaultVolume;
BSS s16 MusicTargetVolume;
BSS s16 MusicMaxVolume;
BSS s16 MusicCurrentVolume;

MusicSettings gMusicControlData[2];

MusicSettings BlankMusicSettings = {
    .flags = 0,
    .state = 0,
    .fadeOutTime = -1,
    .fadeInTime = 0,
    .fadeStartVolume = 0,
    .fadeEndVolume = 0,
    .songID = -1,
    .variation = -1,
    .songName = -1,
    .battleSongID = 0,
    .battleVariation = 0,
    .savedSongID = 0,
    .savedVariation = 0,
    .savedSongName = 0
};

/// Lists the songs that are forced to use the variation determined by `map.songVariation & 1`.
/// @see bgm_get_map_default_variation
s32 SongsUsingVariationFlag[] = {
    SONG_SPECIAL_BATTLE,
    SONG_TUBBA_BLUBBA_BATTLE,
    SONG_JR_TROOPA_BATTLE,
    SONG_YOSHI_KIDS_FOUND,
    SONG_ITEM_UPGRADE,
    SONG_NEW_PARTNER,
};

s16 NextVolumeUpdateTimer = 0;

/// If the given song ID is present in SongsUsingVariationFlag, returns the current
/// map's `songVariation & 1` value. Otherwise, returns -1.
///
/// @see SongsUsingVariationFlag
/// @returns -1: no override; 0: override to variation 0; 1 override to variation 1
s32 bgm_get_map_default_variation(s32 songID) {
    u32 i;

    for (i = 0; i < ARRAY_COUNT(SongsUsingVariationFlag); i++) {
        if (SongsUsingVariationFlag[i] == songID) {
            MapConfig* map = &gAreas[gGameStatusPtr->areaID].maps[gGameStatusPtr->mapID];

            return map->songVariation & 1;
        }
    }

    return -1;
}

void bgm_reset_sequence_players(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gMusicControlData); i++) {
        gMusicControlData[i] = BlankMusicSettings;
    }

    MusicTargetVolume = 8;
    MusicMaxVolume = 8;
    MusicCurrentVolume = 8;
    snd_set_bgm_volume(8);
}

void bgm_reset_volume(void) {
    MusicTargetVolume = 8;
    MusicMaxVolume = 8;
}

//TODO refactor out constants
void bgm_update_music_control(void) {
    MusicSettings* music = gMusicControlData;
    s32 i = 0;
    s16 state2 = 2;
    s16 flag4 = MUSIC_SETTINGS_FLAG_4;
    s32 flags;

    for (i; i < ARRAY_COUNT(gMusicControlData); i++, music++) {
        switch (music->state) {
        case 0:
            break;
        case 1:
            if (music->flags & MUSIC_SETTINGS_FLAG_1) {
                if (music->fadeOutTime < 250) {
                    if (!(music->flags & MUSIC_SETTINGS_FLAG_4)) {
                        if (snd_song_stop(music->songName) == AU_RESULT_OK) {
                            music->state = state2;
                        }
                    } else {
                        if (snd_song_UNK_push_stop(music->songName) == AU_RESULT_OK) {
                           music->state = state2;
                        }
                    }
                } else if (!(music->flags & MUSIC_SETTINGS_FLAG_4)) {
                    if (snd_song_request_fade_out(music->songName, music->fadeOutTime, 0) == 0) {
                        music->state = state2;
                    }
                } else {
                    if (snd_song_UNK_request_push_fade_out(music->songName, 250) == AU_RESULT_OK) {
                        music->state = state2;
                    }
                }
            } else {
                if (music->flags & MUSIC_SETTINGS_FLAG_4) {
                    music->flags |= MUSIC_SETTINGS_FLAG_10;
                }
                music->flags &= ~flag4;
                music->state = 5;
            }
            break;
        case 2:
            flags = music->flags;
            music->flags &= ~flag4;
            if (flags & MUSIC_SETTINGS_FLAG_1) {
                if (snd_song_is_playing(music->songName) == AU_RESULT_OK) {
                    music->flags &= ~MUSIC_SETTINGS_FLAG_1;
                    music->state = 3;
                }
            } else {
                music->state = 5;
            }
            break;
        case 3:
            music->state = 4;
            break;
        case 4:
            music->state = 5;
            break;
        case 5:
            if (!(music->flags & MUSIC_SETTINGS_FLAG_8)) {
                if (music->songID < 0) {
                    music->state = 0;
                } else {
                    music->songName = snd_song_load(music->songID, i);
                    if (music->songName > 0xFFFFU) {
                        if ((music->flags & MUSIC_SETTINGS_FLAG_20)) {
                            snd_song_request_fade_in(music->songName, music->variation,
                                music->fadeInTime, music->fadeStartVolume, music->fadeEndVolume);
                            music->flags &= ~MUSIC_SETTINGS_FLAG_20;
                        } else {
                            bgm_set_target_volume(MusicDefaultVolume);
                        }
                        if (snd_song_request_play(music->songName, music->variation) == 0) {
                            music->flags |= MUSIC_SETTINGS_FLAG_1;
                            music->state = 0;
                        }
                    }
                }
            } else {
                if (music->flags & MUSIC_SETTINGS_FLAG_10) {
                    music->state = 0;
                    music->flags &= ~(MUSIC_SETTINGS_FLAG_10 | MUSIC_SETTINGS_FLAG_8);
                } else if (snd_song_UNK_request_pop(music->savedSongName) == 0) {
                    music->songID = music->savedSongID;
                    music->variation = music->savedVariation;
                    music->songName = music->savedSongName;
                    music->state = 0;
                    music->flags |= MUSIC_SETTINGS_FLAG_1;
                    music->flags &= ~MUSIC_SETTINGS_FLAG_8;
                }
            }
            break;
        }
    }
    bgm_update_volume();
}

s32 _bgm_set_song(s32 playerIndex, s32 songID, s32 variation, s32 fadeOutTime, s16 volume) {
    MusicSettings* musicSetting;
    s32 mapSongVariation;

    if (gGameStatusPtr->demoState != DEMO_STATE_NONE) {
        return 1;
    }

    musicSetting = &gMusicControlData[playerIndex];

    if (!gGameStatusPtr->musicEnabled) {
        snd_song_stop(musicSetting->songName);
        musicSetting->flags &= ~MUSIC_SETTINGS_FLAG_1;

        return 1;
    }

    mapSongVariation = bgm_get_map_default_variation(songID);
    if (mapSongVariation >= 0) {
        variation = mapSongVariation;
    }

    if (musicSetting->songID == songID && musicSetting->variation == variation) {
        bgm_set_target_volume(volume);

        if (musicSetting->flags & MUSIC_SETTINGS_FLAG_4) {
            func_80055B80(musicSetting->songName);
            musicSetting->flags &= ~MUSIC_SETTINGS_FLAG_4;
        }

        return 2;
    }

    MusicDefaultVolume = volume;
    musicSetting->songID = songID;
    musicSetting->variation = variation;
    musicSetting->fadeOutTime = fadeOutTime;
    musicSetting->state = 1;
    musicSetting->flags &= ~MUSIC_SETTINGS_FLAG_ENABLE_PROXIMITY_MIX;

    return 1;
}

s32 bgm_set_song(s32 playerIndex, s32 songID, s32 variation, s32 fadeOutTime, s16 volume) {
    gMusicControlData[playerIndex].flags &= ~MUSIC_SETTINGS_FLAG_8;

    return _bgm_set_song(playerIndex, songID, variation, fadeOutTime, volume);
}

s32 bgm_fade_in_song(s32 playerIndex, s32 songID, s32 variation, s32 fadeInTime, s16 fadeStartVolume, s16 fadeEndVolume) {
    MusicSettings* musicSetting;
    s32 mapSongVariation;

    if (gGameStatusPtr->demoState) {
        return 1;
    }

    musicSetting = &gMusicControlData[playerIndex];

    if (!gGameStatusPtr->musicEnabled) {
        snd_song_stop(musicSetting->songName);
        musicSetting->flags &= ~MUSIC_SETTINGS_FLAG_1;
        return 1;
    }

    mapSongVariation = bgm_get_map_default_variation(songID);
    if (mapSongVariation >= 0) {
        variation = mapSongVariation;
    }

    musicSetting->fadeInTime = fadeInTime;
    musicSetting->fadeStartVolume = fadeStartVolume;
    musicSetting->fadeEndVolume = fadeEndVolume;
    musicSetting->songID = songID;
    musicSetting->variation = variation;
    musicSetting->flags |= MUSIC_SETTINGS_FLAG_20;
    musicSetting->state = 1;
    musicSetting->flags &= ~MUSIC_SETTINGS_FLAG_ENABLE_PROXIMITY_MIX;

    return 1;
}

s32 bgm_adjust_proximity(s32 playerIndex, s32 mix, s16 state) {
    MusicSettings* musicSetting = &gMusicControlData[playerIndex];

    if (!(musicSetting->flags & MUSIC_SETTINGS_FLAG_1)) {
        return FALSE;
    }

    if (!(musicSetting->flags & MUSIC_SETTINGS_FLAG_ENABLE_PROXIMITY_MIX)) {
        return FALSE;
    }

    switch (state) {
        case MUSIC_PROXIMITY_FAR:
            snd_song_set_proximity_mix_far(musicSetting->songName, mix);
            break;
        case MUSIC_PROXIMITY_NEAR:
            snd_song_set_proximity_mix_near(musicSetting->songName, mix);
            break;
        case MUSIC_PROXIMITY_FULL:
            snd_song_set_proximity_mix_full(musicSetting->songName, mix);
            break;
    }
    return TRUE;
}

AuResult bgm_set_track_volumes(s32 playerIndex, s16 trackVolSet) {
    MusicSettings* musicSetting = &gMusicControlData[playerIndex];

    if (!(musicSetting->flags & MUSIC_SETTINGS_FLAG_1)) {
        return AU_RESULT_OK;
    }

    return snd_song_set_track_volumes(musicSetting->songName, trackVolSet);
}

AuResult bgm_clear_track_volumes(s32 playerIndex, s16 trackVolSet) {
    MusicSettings* musicSetting = &gMusicControlData[playerIndex];

    if (!(musicSetting->flags & MUSIC_SETTINGS_FLAG_1)) {
        return AU_RESULT_OK;
    }

    return snd_song_clear_track_volumes(musicSetting->songName, trackVolSet);
}

AuResult bgm_set_linked_mode(s32 playerIndex, s16 arg1) {
    MusicSettings* musicSetting = &gMusicControlData[playerIndex];

    if (!(musicSetting->flags & MUSIC_SETTINGS_FLAG_1)) {
        return AU_RESULT_OK;
    }

    return snd_song_set_linked_mode(musicSetting->songName, arg1);
}

s32 bgm_init_music_players(void) {
    bgm_set_song(0, -1, 0, 250, 8);
    bgm_set_song(1, -1, 0, 250, 8);

    return 1;
}

void bgm_quiet_max_volume(void) {
    MusicMaxVolume = 4;
}

void bgm_reset_max_volume(void) {
    MusicMaxVolume = 8;
}

void bgm_set_target_volume(s16 volume) {
    MusicTargetVolume = volume;
}

void bgm_update_volume(void) {
    s16 toVolume;

    if (NextVolumeUpdateTimer != 0) {
        NextVolumeUpdateTimer--;
        return;
    }

    toVolume = MusicTargetVolume;
    if (toVolume > MusicMaxVolume) {
        toVolume = MusicMaxVolume;
    }

    if (MusicCurrentVolume != toVolume) {
        if (MusicCurrentVolume >= toVolume) {
            MusicCurrentVolume--;
        } else {
            MusicCurrentVolume++;
        }
        snd_set_bgm_volume(MusicCurrentVolume);
        NextVolumeUpdateTimer = 3;
    }
}

s32 bgm_is_any_song_playing(void) {
    MusicSettings* settings = gMusicControlData;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gMusicControlData); i++, settings++) {
        if (!(settings->flags & MUSIC_SETTINGS_FLAG_1)) {
            continue;
        }

        if (snd_song_is_playing(settings->songName)) {
            return TRUE;
        }
    }
    return FALSE;
}

void bgm_pop_song(void) {
    MusicSettings* musicSetting = gMusicControlData;

    if (gGameStatusPtr->demoState == DEMO_STATE_NONE) {
        musicSetting->flags |= MUSIC_SETTINGS_FLAG_8;
        _bgm_set_song(0, musicSetting->savedSongID, musicSetting->savedVariation, 0, 8);
    }
}

void bgm_push_song(s32 songID, s32 variation) {
    MusicSettings* musicSetting = gMusicControlData;

    if (gGameStatusPtr->demoState == DEMO_STATE_NONE) {
        musicSetting->savedSongID = musicSetting->songID;
        musicSetting->savedVariation = musicSetting->variation;
        musicSetting->savedSongName = musicSetting->songName;
        musicSetting->flags |= MUSIC_SETTINGS_FLAG_4;
        bgm_set_song(0, songID, variation, 500, 8);
    }
}

void bgm_pop_battle_song(void) {
    MusicSettings* musicSetting = gMusicControlData;

    if (gGameStatusPtr->demoState == DEMO_STATE_NONE) {
        if (gOverrideFlags & GLOBAL_OVERRIDES_DONT_RESUME_SONG_AFTER_BATTLE) {
            gOverrideFlags &= ~GLOBAL_OVERRIDES_DONT_RESUME_SONG_AFTER_BATTLE;
        } else {
            musicSetting->flags |= MUSIC_SETTINGS_FLAG_8;
            _bgm_set_song(0, musicSetting->savedSongID, musicSetting->savedVariation, 0, 8);
            snd_ambient_resume(0, 250);
        }
    }
}

void bgm_push_battle_song(void) {
    MusicSettings* musicSetting = gMusicControlData;

    if (gGameStatusPtr->demoState == DEMO_STATE_NONE) {
        if (!(gOverrideFlags & GLOBAL_OVERRIDES_DONT_RESUME_SONG_AFTER_BATTLE)) {
            snd_ambient_pause(0, 250);
            musicSetting->savedSongID = musicSetting->songID;
            musicSetting->savedVariation = musicSetting->variation;
            musicSetting->savedSongName = musicSetting->songName;
            musicSetting->flags |= MUSIC_SETTINGS_FLAG_4;
            bgm_set_song(0, musicSetting->battleSongID, musicSetting->battleVariation, 500, 8);
        }
    }
}

void bgm_set_battle_song(s32 songID, s32 variation) {
    MusicSettings* musicSetting = gMusicControlData;

    musicSetting->battleSongID = songID;
    musicSetting->battleVariation = variation;
}

void bgm_NOOP(void) {
}
