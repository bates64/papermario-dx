#!/usr/bin/env python3

from sys import argv

import msgpack


class Message:
    def __init__(self, d: dict, header_file_index: int):
        self.section = d.get("section")
        self.index = d.get("index")
        self.name = d.get("name")
        self.bytes = d["bytes"]
        self.header_file_index = header_file_index


def file_to_layer(file_index, layer_sizes):
    cumulative = 0
    for layer, size in enumerate(layer_sizes):
        cumulative += size
        if file_index < cumulative:
            return layer
    return len(layer_sizes) - 1


if __name__ == "__main__":
    if len(argv) < 3:
        print("usage: combine.py [out.bin] [out.h] [--layer-sizes SIZES] [compiled...]")
        exit(1)

    _, outfile, header_file, *rest = argv

    # Parse --layer-sizes if present
    layer_sizes = None
    if "--layer-sizes" in rest:
        idx = rest.index("--layer-sizes")
        layer_sizes = [int(x) for x in rest[idx + 1].split(",")]
        rest = rest[:idx] + rest[idx + 2 :]

    infiles = rest

    messages = []

    for i, infile in enumerate(infiles):
        with open(infile, "rb") as f:
            messages.extend(Message(msg, i) for msg in msgpack.unpack(f))

    with open(outfile, "wb") as f:
        sections = []

        for message in messages:
            if message.section is None:
                # allocate a section
                for section_idx, section in enumerate(sections):
                    if len(section) < 0xFFF:
                        break
                message.section = section_idx
            else:
                section_idx = message.section
            while len(sections) <= section_idx:
                sections.append({})
            section = sections[section_idx]

            if message.index is None:
                # Look up existing message with this name to override it
                if message.name:
                    for idx, existing in section.items():
                        if existing.name == message.name:
                            message.index = idx
                            break
                if message.index is None:
                    message.index = len(section)

            # Only allow overrides between asset stack layers
            if message.index in section:
                existing = section[message.index]

                if layer_sizes is not None:
                    msg_layer = file_to_layer(message.header_file_index, layer_sizes)
                    existing_layer = file_to_layer(
                        existing.header_file_index, layer_sizes
                    )

                    if msg_layer == existing_layer:
                        if (
                            existing.name
                            and message.name
                            and existing.name == message.name
                        ):
                            print(
                                f"error: duplicate message '{message.name}' in same layer"
                            )
                            exit(1)
                        else:
                            print(
                                f"error: multiple messages allocated to id {section_idx:02X}:{message.index:03X} in same layer"
                            )
                            exit(1)

            section[message.index] = message

        f.seek((len(sections) + 1) * 4)  # skip past table of contents

        section_offsets = []
        for section in sections:
            # convert dict into sorted list
            section = [
                msg for idx, msg in sorted(section.items(), key=lambda ele: ele[0])
            ]

            message_offsets = []
            for message in section:
                message_offsets.append(f.tell())
                f.write(message.bytes)

            section_offset = f.tell()
            section_offsets.append(section_offset)
            for offset in message_offsets:
                f.write(offset.to_bytes(4, byteorder="big"))
            f.write(section_offset.to_bytes(4, byteorder="big"))

            # padding
            while f.tell() % 0x10 != 0:
                f.write(b"\0\0\0\0")

        f.seek(0)
        for offset in section_offsets:
            f.write(offset.to_bytes(4, byteorder="big"))
        f.write(b"\0\0\0\0")

    with open(header_file, "w") as f:
        f.write(f'#pragma once\n\n#include "messages.h"\n\n')

        seen = {}
        for message in messages:
            if message.name:
                define_name = f"MSG_{message.name}"
                value = f"MESSAGE_ID(0x{message.section:02X}, 0x{message.index:03X})"
                if define_name in seen:
                    if seen[define_name] != value:
                        print(
                            f"warning: conflicting values for {define_name}: {seen[define_name]} vs {value}"
                        )
                else:
                    seen[define_name] = value
                    f.write(f"#define {define_name} {value}\n")

        f.write("\n")
