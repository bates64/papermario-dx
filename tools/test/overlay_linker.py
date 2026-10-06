#!/usr/bin/env python3
"""Check overlay symbol isolation and collision diagnostics with real MIPS objects."""

import pickle
import shutil
import struct
import subprocess
import sys
import tempfile
import unittest
from types import SimpleNamespace
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools/build"))
from overlay_impl import cmd_gen_syms, link_overlay

LINK_ADDR = 0x80000000


class OverlayLinkerTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(prefix="overlay_linker_")
        self.addCleanup(self.temp.cleanup)
        self.directory = Path(self.temp.name)
        self.compiler = shutil.which("mips-linux-gnu-gcc")
        if self.compiler is None:
            self.skipTest("mips-linux-gnu-gcc was not found on PATH")

    def compile(self, name, source, *, common=False):
        path = self.directory / f"{name}.c"
        obj = path.with_suffix(".o")
        path.write_text(source)
        subprocess.run(
            [
                self.compiler, "-c", "-EB", "-G0", "-mabi=32",
                "-mno-abicalls", "-fno-pic", "-fvisibility=hidden",
                "-fcommon" if common else "-fno-common",
                str(path), "-o", str(obj),
            ],
            check=True, capture_output=True, text=True,
        )
        return str(obj)

    def link(self, objects, *, exports=(), syms=None):
        return link_overlay(
            objects, syms or {}, LINK_ADDR,
            force_exports=exports, require_resolved=True,
        )

    def assert_collision(self, objects):
        with self.assertRaises(ValueError) as raised:
            self.link(objects)
        message = str(raised.exception)
        self.assertIn("duplicate global symbol 'shared'", message)
        for obj in objects:
            self.assertIn(obj, message)

    def test_duplicate_global_data_is_rejected(self):
        self.assert_collision([
            self.compile("first", "int shared = 1;"),
            self.compile("second", "int shared = 2;"),
        ])

    def test_duplicate_global_functions_are_rejected(self):
        self.assert_collision([
            self.compile("first", "int shared(void) { return 1; }"),
            self.compile("second", "int shared(void) { return 2; }"),
        ])

    def test_duplicate_common_data_is_rejected(self):
        self.assert_collision([
            self.compile("first", "int shared;", common=True),
            self.compile("second", "int shared;", common=True),
        ])

    def test_static_names_remain_local_to_their_object(self):
        result = self.link([
            self.compile("first", "static int shared = 1; int* first = &shared;"),
            self.compile("second", "static int shared = 2; int* second = &shared;"),
        ], exports=("first", "second"))
        exports = {name: addr for addr, name in result[1]}
        data = result[-1]
        first = struct.unpack_from(">I", data, exports["first"] - LINK_ADDR)[0]
        second = struct.unpack_from(">I", data, exports["second"] - LINK_ADDR)[0]
        self.assertNotEqual(first, second)
        self.assertEqual(struct.unpack_from(">I", data, first - LINK_ADDR)[0], 1)
        self.assertEqual(struct.unpack_from(">I", data, second - LINK_ADDR)[0], 2)

    def test_separate_overlays_can_export_the_same_name(self):
        for value in (1, 2):
            result = self.link([
                self.compile(f"actor{value}", f"int blueprint = {value};"),
            ], exports=("blueprint",))
            addr, name = result[1][0]
            self.assertEqual(name, "blueprint")
            self.assertEqual(
                struct.unpack_from(">I", result[-1], addr - LINK_ADDR)[0], value,
            )

    def test_overlay_definition_wins_over_baseline_address(self):
        result = self.link([
            self.compile("definition", "int shared = 17;"),
            self.compile("reference", "extern int shared; int* reference = &shared;"),
        ], exports=("shared", "reference"), syms={"shared": 0x80001234})
        exports = {name: addr for addr, name in result[1]}
        self.assertEqual(
            struct.unpack_from(">I", result[-1], exports["reference"] - LINK_ADDR)[0],
            exports["shared"],
        )
        self.assertNotEqual(exports["shared"], 0x80001234)

    def test_unresolved_reference_is_rejected(self):
        obj = self.compile("reference", "extern int missing; int* reference = &missing;")
        with self.assertRaisesRegex(ValueError, "unresolved symbol 'missing'"):
            self.link([obj])

    def test_old_battle_area_addresses_are_not_engine_imports(self):
        baseline = self.directory / "baseline.txt"
        baseline.write_text(
            "b_area_old_actor = 0x80218000;\n"
            "LoadBattleSection = 0x80269DE4;\n"
            "legacy_engine = 0x80001234;\n"
            "current_engine = 0x80005678;\n"
        )
        engine = self.compile("engine", "int current_engine = 1;")
        output = self.directory / "syms.pkl"
        cmd_gen_syms(SimpleNamespace(
            input=engine, symbol_files=[str(baseline)], output=str(output),
            script=str(self.directory / "syms.ld"),
        ))
        syms = pickle.loads(output.read_bytes())
        self.assertNotIn("b_area_old_actor", syms)
        self.assertNotIn("LoadBattleSection", syms)
        self.assertEqual(syms["legacy_engine"], 0x80001234)
        self.assertNotEqual(syms["current_engine"], 0x80005678)
        reference = self.compile("reference", "extern int b_area_old_actor; int* ref = &b_area_old_actor;")
        with self.assertRaisesRegex(ValueError, "unresolved symbol 'b_area_old_actor'"):
            self.link([reference], syms=syms)

    def test_local_and_engine_references_remain_distinct(self):
        result = self.link([
            self.compile("definition", "int local = 17;"),
            self.compile(
                "reference",
                "extern int local; extern int engine; "
                "int* local_reference = &local; int* engine_reference = &engine;",
            ),
        ], exports=("local", "local_reference", "engine_reference"),
            syms={"engine": 0x80001234})
        exports = {name: addr for addr, name in result[1]}
        self.assertEqual(
            struct.unpack_from(">I", result[-1], exports["local_reference"] - LINK_ADDR)[0],
            exports["local"],
        )
        self.assertEqual(
            struct.unpack_from(">I", result[-1], exports["engine_reference"] - LINK_ADDR)[0],
            0x80001234,
        )


if __name__ == "__main__":
    unittest.main()
