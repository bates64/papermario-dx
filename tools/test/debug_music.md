# Debug Music checks

After configuring DX, run the host checks in its development shell:

```sh
ninja test_debug_music
```

This generates the required headers and runs both the catalog and browser tests.
It supports modified song catalogs without requiring a full ROM build.

The browser test reads the song count from the configured build's
`audio/song_ids.h` and checks it against `audio/debug_music_catalog.h`. To use a
different build, pass its generated include directory:

```sh
python3 tools/test/debug_music_browser.py --include-dir path/to/build/include
```

For an unmodified audio catalog, run the upstream audio checks:

```sh
ninja verify_audio
```

`verify_audio` retains the audio roundtrip check and runs the browser test with
`--vanilla`, which additionally requires 143 named songs. The upstream Tangled
build already invokes this target. For additions, deletions, or a smaller
catalog, use `test_debug_music` or run the Python browser test without
`--vanilla`. Regenerate the headers after changing songs.

The catalog tests exercise added/deleted songs, short catalogs, bounded labels,
and invalid IDs. The C harness includes the production debug menu and links the
production BGM controller with real headers, AddressSanitizer, and UBSan. It
checks every configured selection and its wrap/page
boundaries, play/stop/back, retained selection, and the existing sound-effect
controls. Sound-driver stubs check same-song R replay while playing and after a
fanfare finishes but remains requested: the controller must queue a restart,
retain the old playback handle until stopped, preserve saved music, and issue a
fresh play request. These checks do not prove native playback or appearance.

The harness respects `DX_DEBUG_MENU` in `src/dx/config.h`: when it is `0`, the
browser checks print a skip message and succeed. Every run also compiles and runs
a disabled-menu variant, using a temporary forced include to override that one
switch without editing the checkout. This guards the `verify_audio` integration
even when CI builds with the debug menu enabled. Catalog and audio roundtrip
checks still run when the menu is disabled.

For native testing, use an isolated emulator profile and a fresh or copied save:

1. Load a map, press D-left, and select Sound Player with R, then Music with R.
2. Check Up at the first entry, Down at the last, and Left/Right paging at both
   ends. Check that the highlighted entry stays visible and labels fit.
3. With vanilla songs, play Toad Town (00), Normal Battle (02), Master Battle
   (2C), and Flower Fields Sunny (31). Press R again while the same song plays
   and listen for a restart without pressing Z. Stop with Z, then replay with R.
   Play a nonlooping fanfare, wait for it to finish, then press R again without
   pressing Z or selecting another song; verify the fanfare plays again.
4. For a modified catalog, verify added songs appear and deleted songs do not.
   Check the displayed total against the configured songs and repeat navigation
   and playback checks, including any catalog with fewer than nine songs.
5. Back out with L and re-enter; verify retained selection. Back out to Sound,
   play/stop coin sound 0211, and verify each back-navigation level.
6. Leave the debug menu, change maps, and enter/leave a battle. Verify normal
   music resumes under game control and the browser still works on re-entry.
