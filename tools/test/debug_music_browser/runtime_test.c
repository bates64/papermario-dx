#include "common.h"
#include "audio/audio.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

// Include the real menu so tests can inspect its retained static selection.
#include "dx/debug_menu.c"

GameStatus gTestGameStatus;
GameStatus* gGameStatusPtr = &gTestGameStatus;
static MapSettings TestMapSettings;
static s32 NamesDrawn, DisabledDrawn, StoppedDrawn;
static char DrawText[128];
static b32 HardwarePlaying;
static s32 PlaybackStarts, LoadedSong, StoppedHandle, PlayedSound, StoppedSound;

// Render calls are observed at the host boundary; this does not render N64 messages.
MSG_PTR dx_string_to_msg(MSG_PTR msg, const char* text) {
    assert(strlen(text) < sizeof(DrawText));
    strcpy(DrawText, text);
    return msg;
}

void draw_msg(s32 msgID, s32 x, s32 y, s32 opacity, s32 palette, u8 style) {
    assert(x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT);
    if (x == 50) {
        NamesDrawn++;
        assert(y >= 51 && y <= 171);
    }
    DisabledDrawn += !strcmp(DrawText, "Music is disabled");
    StoppedDrawn += !strcmp(DrawText, "Stopped");
}

s32 draw_box(
    s32 flags, WindowStyle style, s32 x, s32 y, s32 z, s32 width, s32 height, u8 opacity, u8 darkening, f32 scaleX,
    f32 scaleY, f32 rotX, f32 rotY, f32 rotZ, void (*contents)(s32, s32, s32, s32, s32, s32, s32), void* contentsArg,
    Matrix4f rotScale, s32 translateX, s32 translateY, Matrix4f out
) {
    assert(x >= 0 && y >= 0 && x + width <= SCREEN_WIDTH && y + height <= SCREEN_HEIGHT);
    return 0;
}

MapSettings* get_current_map_settings(void) {
    return &TestMapSettings;
}

// Minimal sound-driver model: completion, stop, load and play. The actual BGM
// request/transition/volume code runs from src/engine2/bgm_control.c.
AuResult snd_song_stop(s32 name) {
    StoppedHandle = name;
    HardwarePlaying = false;
    return AU_RESULT_OK;
}

AuResult snd_song_is_playing(s32 name) {
    return HardwarePlaying ? 1 : AU_RESULT_OK;
}

AuResult snd_song_load(s32 song, s32 player) {
    assert(player == 0);
    LoadedSong = song;
    return 0x534F4E47;
}

AuResult snd_song_request_play(s32 name, s32 variation) {
    assert(name == 0x534F4E47 && variation == 0);
    HardwarePlaying = true;
    PlaybackStarts++;
    return AU_RESULT_OK;
}

void snd_set_bgm_volume(VolumeLevels volume) {
}

AuResult snd_song_push_stop(s32 name) {
    assert(false && "unexpected push stop");
    return AU_RESULT_OK;
}

AuResult snd_song_request_fade_out(s32 name, s32 time, AuCallback callback) {
    assert(false && "unexpected fade out");
    return AU_RESULT_OK;
}

AuResult snd_song_request_push_fade_out(s32 name, s32 time) {
    assert(false && "unexpected push fade out");
    return AU_RESULT_OK;
}

AuResult snd_song_request_fade_in(s32 name, s32 variation, s32 time, s32 start, s32 end) {
    assert(false && "unexpected fade in");
    return AU_RESULT_OK;
}

AuResult snd_song_request_pop(s32 name) {
    assert(false && "unexpected song pop");
    return AU_RESULT_OK;
}

AuResult snd_song_request_snapshot(s32 name) {
    assert(false && "unexpected song snapshot");
    return AU_RESULT_OK;
}

void sfx_play_sound(s32 id) {
    PlayedSound = id;
}

void sfx_stop_sound(s32 id) {
    StoppedSound = id;
}

static void reset_inputs(void) {
    DebugButtonsPress = DebugButtonsRelease = 0;
    DebugHoldU.delay = DebugHoldD.delay = DebugHoldL.delay = DebugHoldR.delay = 1;
    DebugStateChanged = false;
    NamesDrawn = DisabledDrawn = StoppedDrawn = 0;
    DebugMenuState = DBM_SELECT_MUSIC;
}

static void settle_music(void) {
    for (s32 frame = 0; frame < 8 && gMusicControlData[0].state != MUSIC_STATE_IDLE; frame++) {
        bgm_update_music_control();
    }
    assert(gMusicControlData[0].state == MUSIC_STATE_IDLE);
}

static void check_same_song_restart(s32 pos, b32 finished) {
    MusicControlData* music = &gMusicControlData[0];
    const s32 oldHandle = 0x4F4C4421;

    *music = (MusicControlData) {
        .state = MUSIC_STATE_IDLE,
        .flags = MUSIC_FLAG_PLAYING,
        .requestedSongID = DebugMusicSongs[pos].songID,
        .variation = 0,
        .songName = oldHandle,
        .savedSongID = 0x45,
        .savedVariation = 1,
        .savedSongName = 0x53415645,
    };
    HardwarePlaying = !finished;
    PlaybackStarts = 0;
    StoppedHandle = 0;
    // A completed fanfare leaves the controller IDLE with PLAYING and its
    // request intact, even after the sound driver finishes.
    bgm_update_music_control();
    assert(music->state == MUSIC_STATE_IDLE && (music->flags & MUSIC_FLAG_PLAYING));
    assert(HardwarePlaying == !finished);
    // Prove a single same-song request would take the engine's early return.
    assert(bgm_set_song(0, music->requestedSongID, 0, 0, VOL_LEVEL_FULL) == 2);
    assert(music->state == MUSIC_STATE_IDLE && PlaybackStarts == 0);
    reset_inputs();
    DebugMusicPos = pos;
    DebugButtonsRelease = BUTTON_R;
    dx_debug_update_select_music();
    assert(music->state == MUSIC_STATE_STOP_CURRENT);
    assert(music->requestedSongID == DebugMusicSongs[pos].songID && music->variation == 0);
    assert(music->songName == oldHandle && (music->flags & MUSIC_FLAG_PLAYING));
    assert(music->savedSongID == 0x45 && music->savedVariation == 1 && music->savedSongName == 0x53415645);
    settle_music();
    assert(StoppedHandle == oldHandle && HardwarePlaying && PlaybackStarts == 1);
    assert(LoadedSong == DebugMusicSongs[pos].songID);
    assert(music->savedSongID == 0x45 && music->savedVariation == 1 && music->savedSongName == 0x53415645);
}

int main(int argc, char** argv) {
    s32 checks = 0;
    const s32 count = ARRAY_COUNT(DebugMusicSongs);
    s32 requestedSong;

    assert(count > 0);
    if (argc == 2 && !strcmp(argv[1], "--vanilla")) {
        assert(count == 143);
    }
    gGameStatusPtr->musicEnabled = true;
    bgm_reset_sequence_players();
    check_same_song_restart(0, false);
    checks++;
    check_same_song_restart(count - 1, true);
    checks++;
    for (s32 pos = 0; pos < count; pos++) {
        const DebugMusicEntry* entry = &DebugMusicSongs[pos];

        assert(entry->songID >= 0 && entry->songID <= 0xFF);
        assert(pos == 0 || DebugMusicSongs[pos - 1].songID < entry->songID);
        assert(strlen(entry->name) <= 22);
        for (const char* ch = entry->name; *ch; ch++) {
            assert((unsigned char) *ch < 128);
        }
        reset_inputs();
        DebugMusicPos = pos;
        DebugMusicStart = 0;
        DebugButtonsRelease = BUTTON_R;
        dx_debug_update_select_music();
        assert(gMusicControlData[0].state == MUSIC_STATE_STOP_CURRENT);
        assert(gMusicControlData[0].requestedSongID == entry->songID);
        assert(NamesDrawn > 0 && NamesDrawn <= DEBUG_MUSIC_VISIBLE_ROWS);
        assert(DebugMusicPos >= DebugMusicStart && DebugMusicPos < DebugMusicStart + DEBUG_MUSIC_VISIBLE_ROWS);
        checks++;
        reset_inputs();
        DebugButtonsPress = BUTTON_D_UP;
        dx_debug_update_select_music();
        assert(DebugMusicPos == (pos == 0 ? count - 1 : pos - 1));
        checks++;
        reset_inputs();
        DebugMusicPos = pos;
        DebugButtonsPress = BUTTON_D_DOWN;
        dx_debug_update_select_music();
        assert(DebugMusicPos == (pos == count - 1 ? 0 : pos + 1));
        checks++;
        reset_inputs();
        DebugMusicPos = pos;
        DebugButtonsPress = BUTTON_D_LEFT;
        dx_debug_update_select_music();
        assert(DebugMusicPos == MAX(0, pos - DEBUG_MUSIC_VISIBLE_ROWS));
        checks++;
        reset_inputs();
        DebugMusicPos = pos;
        DebugButtonsPress = BUTTON_D_RIGHT;
        dx_debug_update_select_music();
        assert(DebugMusicPos == MIN(count - 1, pos + DEBUG_MUSIC_VISIBLE_ROWS));
        checks++;
    }
    reset_inputs();
    DebugButtonsRelease = BUTTON_Z;
    dx_debug_update_select_music();
    assert(gMusicControlData[0].requestedSongID == AU_SONG_NONE);
    checks++;
    reset_inputs();
    DebugButtonsRelease = BUTTON_R | BUTTON_L;
    dx_debug_update_select_music();
    assert(gMusicControlData[0].requestedSongID == AU_SONG_NONE && DebugMenuState == DBM_SOUND_PLAYER);
    checks++;
    reset_inputs();
    gGameStatusPtr->musicEnabled = false;
    requestedSong = gMusicControlData[0].requestedSongID;
    dx_debug_update_select_music();
    assert(DisabledDrawn == 1 && gMusicControlData[0].requestedSongID == requestedSong);
    gGameStatusPtr->musicEnabled = true;
    checks++;
    reset_inputs();
    gMusicControlData[0].requestedSongID = AU_SONG_NONE;
    dx_debug_update_select_music();
    assert(StoppedDrawn == 1);
    checks++;
    reset_inputs();
    DebugMusicPos = count - 1;
    DebugMusicStart = MAX(0, count - DEBUG_MUSIC_VISIBLE_ROWS);
    DebugStateChanged = true;
    dx_debug_update_select_music();
    assert(DebugMusicPos == count - 1 && DebugMusicStart == MAX(0, count - DEBUG_MUSIC_VISIBLE_ROWS));
    checks++;
    for (s32 section = 0; section < 2; section++) {
        reset_inputs();
        AudioSectionMenuPos = section;
        DebugButtonsRelease = BUTTON_R;
        dx_debug_update_sound_player();
        assert(DebugMenuState == (section ? DBM_SELECT_MUSIC : DBM_SOUND_EFFECTS));
        checks++;
    }
    reset_inputs();
    DebugButtonsRelease = BUTTON_L;
    dx_debug_update_sound_player();
    assert(DebugMenuState == DBM_MAIN_MENU);
    checks++;
    reset_inputs();
    DebugButtonsRelease = BUTTON_L;
    dx_debug_update_sound_effects();
    assert(DebugMenuState == DBM_SOUND_PLAYER);
    checks++;
    reset_inputs();
    DebugButtonsRelease = BUTTON_R;
    dx_debug_update_sound_effects();
    assert(DebugMenuState == DBM_SELECT_SOUND);
    checks++;
    reset_inputs();
    DebugButtonsRelease = BUTTON_L;
    dx_debug_update_select_sound();
    assert(DebugMenuState == DBM_SOUND_EFFECTS);
    checks++;
    reset_inputs();
    DebugButtonsRelease = BUTTON_R;
    dx_debug_set_editable_num(&DebugSoundID, 0x211);
    SoundPlayerMenuPos = 0;
    dx_debug_update_select_sound();
    assert(PlayedSound == 0x211);
    checks++;
    reset_inputs();
    DebugButtonsRelease = BUTTON_R;
    SoundPlayerMenuPos = 1;
    dx_debug_update_select_sound();
    assert(StoppedSound == 0x211);
    checks++;
    printf("PASS: %ld production browser/navigation/routing/replay cases; %ld configured songs\n", checks, count);
    return 0;
}
