# Debugging

[gdb] is a debugger that allows inspecting programs while they're running, tracing execution, placing breakpoints, stepping through code, and editing memory.

To use gdb, you'll need gdb-multiarch, a gdb server and a gdb client.

## Installing gdb-multiarch

- Ubuntu and derivatives: `sudo apt install -y gdb-multiarch`
- macOS: [run Ubuntu in a container and install it there](https://github.com/l2iterative/gdb0/blob/main/gdb_macOS_arm.md)

## gdb server

[The ares emulator][ares] has had gdb support for N64 since v134.

To enable ares' gdb server, go to **Settings > Debug** and check **Enabled**.

The following message will appear at the bottom of the ares window: `GDB pending ([::1]:9123)`

![](https://github.com/Dragorn421/z64-romhack-tutorials/raw/master/debugging/gdb/media/ares_gdb_pending.png)

## gdb client

Make sure the gdb server is running. Then:

- **VSCode**: Open a C file and press **F5**. [More...](https://github.com/Dragorn421/z64-romhack-tutorials/blob/master/debugging/gdb/vscode.md#running)
- **Terminal**: Start `gdb-multiarch` and enter `target remote [::1]:9123`. [More...](https://github.com/Dragorn421/z64-romhack-tutorials/blob/master/debugging/gdb/terminal.md#connect-to-the-gdb-server)

## Overlays

TODO: migrate [overlay support](https://github.com/Dragorn421/z64-romhack-tutorials/blob/master/debugging/gdb/gdb_and_z64_overlays.md) to dx

[gdb]: https://sourceware.org/gdb/
[ares]: https://ares-emu.net/

---

This page was adapted from [Dragorn421's oot gdb tutorial](https://github.com/Dragorn421/z64-romhack-tutorials/blob/master/debugging/gdb/index.md).

<div class="section_buttons">

| Previous                     | Next                                 |
|:-----------------------------|-------------------------------------:|
|[Star Rod](manual/star-rod.md)|[GitHub Actions](manual/gh-actions.md)|

</div>
