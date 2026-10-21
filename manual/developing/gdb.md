---
title: GDB
sidebar:
  order: 2
---

[GDB][gdb] is a debugger that lets you inspect the game while it runs, trace execution, set breakpoints, step through code, and edit memory. Diorama64 has its own debugger, so you only need GDB when you work without it.

To use GDB, you need two things: a GDB server, which the emulator runs, and a GDB client that can debug MIPS code, which connects to it.

## Getting a GDB client

DX's toolchain includes a MIPS build of GDB. The first build downloads it to:

- Linux and macOS: `.dx/unix/bin/gdb`
- Windows: `.dx\windows\bin\gdb.exe`

In the Nix dev shell, it's on your `PATH` as `mips-linux-gnu-gdb`.

You can also use `gdb-multiarch`. On Ubuntu and Debian, install it with `sudo apt install -y gdb-multiarch`.

## Starting the GDB server

[The ares emulator][ares] has had GDB support for N64 since v134.

To turn on the GDB server in ares, go to **Settings > Debug** and check **Enabled**.

The bottom of the ares window then shows `GDB pending ([::1]:9123)`.

![The bottom of the ares window, showing that its GDB server is waiting on port 9123](https://github.com/Dragorn421/z64-romhack-tutorials/raw/master/debugging/gdb/media/ares_gdb_pending.png)

## Connecting the GDB client

Make sure the GDB server is running. Then:

- **VS Code**: Open a C file and press **F5**. The project's `.vscode/launch.json` runs `gdb-multiarch`. To use another GDB client, change its `miDebuggerPath`. For more help, see [Dragorn421's guide to running GDB in VS Code](https://github.com/Dragorn421/z64-romhack-tutorials/blob/master/debugging/gdb/vscode.md#running).
- **Terminal**: From the project folder, run the following command, replacing `gdb` with the path to your GDB client:

  ```sh
  gdb -ex 'set architecture mips:4300' -ex 'target remote [::1]:9123' ver/us/build/papermario.elf
  ```

  For more help, see [Dragorn421's guide to connecting to the GDB server from a terminal](https://github.com/Dragorn421/z64-romhack-tutorials/blob/master/debugging/gdb/terminal.md#connect-to-the-gdb-server).

[gdb]: https://sourceware.org/gdb/
[ares]: https://ares-emu.net/

---

This page was adapted from [Dragorn421's Ocarina of Time GDB tutorial](https://github.com/Dragorn421/z64-romhack-tutorials/blob/master/debugging/gdb/index.md).
