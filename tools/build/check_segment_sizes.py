from sys import argv
import json
import subprocess
import sys

# Checks each segment-size pair in JSON object are valid for the given ELF.
# usage: python3 check_segment_sizes.py <elf> <json>

argv.pop(0)  # python3
elf_path = argv.pop(0)
jsonstr = argv.pop(0)


def read_elf():
    result = subprocess.run(["mips64-elf-nm", elf_path], stdout=subprocess.PIPE)
    lines = result.stdout.decode().split("\n")
    symbols = {}
    for line in lines:
        splitted = line.split(" ")
        if len(splitted) == 3:
            address, kind, symbol = splitted
            if symbol.endswith("_VRAM") or symbol.endswith("_VRAM_END"):
                symbols[symbol] = int(address, 16)
    return symbols


segment_size_map = json.loads(jsonstr)
symbols = read_elf()

fail = False
for segment_name, max_size in segment_size_map.items():
    start_address = symbols[segment_name + "_VRAM"]
    end_address = symbols[segment_name + "_VRAM_END"]
    true_size = end_address - start_address
    if true_size > max_size:
        size_diff = true_size - max_size
        print(
            f"\033[31msegment '{segment_name}' is oversized!\033[0m (size is {true_size:X}; +{size_diff:X} compared to max size {max_size:X})",
            file=sys.stderr,
        )
        fail = True
if fail:
    print(
        "help: segment(s) are too big to fit in their overlay(s). to fix this, write less code/data, or modify the engine and splat.yaml to increase the limit",
        file=sys.stderr,
    )
    exit(1)
else:
    print("ok")
