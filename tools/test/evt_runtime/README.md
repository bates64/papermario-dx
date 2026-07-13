# EVT runtime tests

This test compiles the real EVT interpreter, script-list implementation, NPC lifecycle implementation, and Actor lifecycle implementation on the host with AddressSanitizer and UndefinedBehaviorSanitizer. It executes focused scripts written specifically to test VM behavior; it does not execute the game's EvtScript corpus.

The host tests exercise ordinary arithmetic, control flow, variables and flags, buffers and arrays, eval helpers, argument passing, threads, waits, lerps, jumps, and synchronous execution. Loop control is tested across nested switches, and switch control is tested across loops and lerps, including skipped blocks which were never entered. The tests also cover owned-child teardown, `ExecWait` copyback, detached finalizer spawning, Enemy and Actor owner cleanup, registered-slot rebinding, detached script survival, global shutdown quiescence, active hard-reset invalidation, blocked and suspended scripts, early resource cleanup, nested finalizers, self-kills, cyclic `KillScript` calls, and finalizer failure paths.

Run it with:

```sh
python3 tools/test/evt_runtime.py
```

The harness uses pointer-width `Bytecode` values on the host and supplies minimal stubs for unrelated game systems. It covers interpreter behavior and scheduling without claiming to emulate general N64 or game behavior.

Structural validation of the game's compiled EvtScripts is a separate build-time check. It runs as part of the normal build and can be invoked directly with `ninja evt_script_validation`.
