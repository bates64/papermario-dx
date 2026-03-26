#!/usr/bin/env python3

import subprocess
import sys
from pathlib import Path

if __name__ == "__main__":
    argv = sys.argv[1:]
    cross = argv.pop(0)
    crc_tool = argv.pop(0)
    in_file = argv.pop(0)
    out_file = argv.pop(0)
    debug_flags = argv

    subprocess.check_call(
        [f"{cross}objcopy", in_file, out_file, "-O", "binary"] + debug_flags
    )
    subprocess.check_call(
        [sys.executable, "tools/build/append_symbol_table.py", out_file]
    )
    subprocess.check_call([crc_tool, out_file])
