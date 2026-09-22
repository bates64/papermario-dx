#!/usr/bin/env python3

# Thin entrypoint over overlay_impl.py. This script is invoked directly by
# ninja (once per overlay, hundreds of times per build), and CPython only
# bytecode-caches imported modules, not the __main__ script - so the actual
# logic lives in overlay_impl.py, which this just imports and calls, to
# avoid re-parsing 1600+ lines on every invocation.

import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from overlay_impl import main

if __name__ == "__main__":
    main()
