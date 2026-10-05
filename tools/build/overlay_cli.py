#!/usr/bin/env python3

# CPython doesn't bytecode-cache __main__, so keep the logic in an imported
# module.

import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from overlay_impl import main

if __name__ == "__main__":
    main()
