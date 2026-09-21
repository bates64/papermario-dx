#!/usr/bin/env python3

# Runs sccache with credentials for the shared build cache, written by
# configure.py to build/sccache_env.json. Kept out of the ninja command line
# itself so the credentials never end up in build.ninja or
# compile_commands.json.

import json
import os
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent.parent
ENV_FILE = ROOT / "build" / "sccache_env.json"

env = os.environ.copy()
if ENV_FILE.exists():
    env.update(json.loads(ENV_FILE.read_text()))

os.execvpe("sccache", ["sccache"] + sys.argv[1:], env)
