#!/usr/bin/env python3
"""Check browser generation against changing Star Rod song catalogs."""

import importlib.util
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[2]
spec = importlib.util.spec_from_file_location("catalog", ROOT / "tools/build/debug_music_catalog.py")
generator = importlib.util.module_from_spec(spec)
spec.loader.exec_module(generator)


class CatalogTests(unittest.TestCase):
    def test_additions_deletions_and_id_order(self):
        original = "enum SongIDs {\n SONG_TOAD_TOWN = 0x00,\n SONG_UNUSED_FANFARE = 0x4E,\n};"
        modified = "enum SongIDs {\n SONG_NEW_MOD_TRACK = 0x97,\n SONG_TOAD_TOWN = 0x00,\n};"
        self.assertIn("Unused Fanfare", generator.catalog(original))
        result = generator.catalog(modified)
        self.assertNotIn("UNUSED_FANFARE", result)
        self.assertIn('{ SONG_NEW_MOD_TRACK, "New Mod Track" }', result)
        self.assertLess(result.index("SONG_TOAD_TOWN"), result.index("SONG_NEW_MOD_TRACK"))

    def test_short_catalog(self):
        result = generator.catalog("enum SongIDs {\n SONG_ONLY_SONG = 0xFF,\n};")
        self.assertEqual(result.count("{ SONG_"), 1)

    def test_long_label_is_bounded(self):
        result = generator.catalog("enum SongIDs {\n SONG_A_VERY_LONG_CUSTOM_TRACK_FOR_TESTING = 1,\n};")
        title = result.split('"')[1]
        self.assertEqual(len(title), 22)
        self.assertTrue(title.endswith("..."))

    def test_other_enums_do_not_become_songs(self):
        result = generator.catalog("enum Other {\n SONG_FAKE = 0x99,\n};\nenum SongIDs {\n SONG_REAL = 1,\n};")
        self.assertNotIn("FAKE", result)

    def test_missing_enum_is_rejected(self):
        with self.assertRaisesRegex(ValueError, "no SongIDs enum"):
            generator.catalog("#pragma once")

    def test_empty_catalog_is_rejected(self):
        with self.assertRaisesRegex(ValueError, "no songs"):
            generator.catalog("enum SongIDs {}; ")

    def test_duplicate_ids_and_names_are_rejected(self):
        for body in ["SONG_A = 1,\nSONG_B = 1,", "SONG_A = 1,\nSONG_A = 2,"]:
            with self.subTest(body=body), self.assertRaisesRegex(ValueError, "not unique"):
                generator.catalog("enum SongIDs {\n" + body + "\n};")

    def test_out_of_range_is_rejected(self):
        with self.assertRaisesRegex(ValueError, "outside native range"):
            generator.catalog("enum SongIDs {\n SONG_INVALID = 0x100,\n};")


if __name__ == "__main__":
    unittest.main()
