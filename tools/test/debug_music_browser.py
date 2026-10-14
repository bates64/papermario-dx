#!/usr/bin/env python3
"""Compile and run the debug music browser's host C regression tests."""

import argparse
import os
from pathlib import Path
import runpy
import shutil
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[2]
TEST_DIR = Path(__file__).resolve().with_suffix('')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--include-dir', type=Path, default=ROOT / 'ver/us/build/include',
                        help='Generated build include directory containing audio/song_ids.h and audio/debug_music_catalog.h')
    parser.add_argument('--vanilla', action='store_true', help='Additionally require 143 named songs')
    args = parser.parse_args()
    include_dir = args.include_dir.resolve()
    cc = shutil.which('gcc')
    if cc is None:
        parser.error('gcc was not found on PATH; run inside the development shell')

    # Validate generated data using its generator; never extract or rewrite C
    # functions. The harness includes the production sources and headers.
    generate_catalog = runpy.run_path(str(ROOT / 'tools/build/debug_music_catalog.py'))['catalog']
    expected = generate_catalog((include_dir / 'audio/song_ids.h').read_text())
    actual = (include_dir / 'audio/debug_music_catalog.h').read_text()
    if actual != expected:
        parser.error('debug_music_catalog.h is stale; rebuild the configured audio catalog')

    # Whole-program LTO drops unrelated menu/engine code before linking. Keep
    # calls uninlined: GCC otherwise mis-sizes the existing statically initialized
    # flexible-array number controls. ASan and every UBSan check remain enabled.
    flags = [
        '-std=gnu11', '-D_MIPS_SZLONG=64', '-D_LANGUAGE_C', '-DMODERN_COMPILER',
        '-DNON_MATCHING', '-DDEBUG', '-Iver/us/include', f'-I{include_dir}',
        '-Isrc', '-Iassets/us', '-include', 'common.h', '-ffunction-sections',
        '-fdata-sections', '-fno-pie', '-O1', '-fno-inline', '-flto', '-fwhole-program', '-fsanitize=address,undefined', '-g',
        '-Wno-attributes', '-Wno-builtin-declaration-mismatch', '-Wno-incompatible-pointer-types',
    ]
    with tempfile.TemporaryDirectory(prefix='debug_music_browser_', dir='/tmp') as temp_dir:
        temp = Path(temp_dir)
        objects = []
        for source in [ROOT / 'src/engine2/bgm_control.c', TEST_DIR / 'runtime_test.c']:
            obj = temp / (source.stem + '.o')
            subprocess.run([cc, '-c', *flags, str(source), '-o', str(obj)], cwd=ROOT, check=True)
            objects.append(str(obj))
        executable = temp / 'runtime_test'
        subprocess.run([cc, '-no-pie', '-O1', '-flto', '-fwhole-program', '-Wl,--gc-sections', '-fsanitize=address,undefined',
                        *objects, '-lm', '-o', str(executable)], cwd=ROOT, check=True)
        env = os.environ.copy()
        env['ASAN_OPTIONS'] = 'detect_leaks=0'
        env['UBSAN_OPTIONS'] = 'halt_on_error=1:print_stacktrace=1'
        subprocess.run([str(executable), *(['--vanilla'] if args.vanilla else [])], env=env, check=True)


if __name__ == '__main__':
    main()
