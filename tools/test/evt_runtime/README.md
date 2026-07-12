# EVT runtime tests

This test first runs the whole-project `validate_evt_us` target, structurally checking every compiled `EVS_*` script. It then compiles the real EVT interpreter and script-list implementation on the host with AddressSanitizer and UndefinedBehaviorSanitizer.

The host tests exercise ordinary arithmetic, control flow, variables and flags, buffers and arrays, eval helpers, argument passing, threads, waits, lerps, jumps, and synchronous execution. They also cover owned-child teardown, `ExecWait` copyback, detached finalizer spawning, global shutdown quiescence, hard-reset bypass, blocked and suspended scripts, early resource cleanup, nested finalizers, self-kills, cyclic `KillScript` calls, and finalizer failure paths.

Run it with:

```sh
python3 tools/test/evt_runtime.py
```

The harness uses pointer-width `Bytecode` values on the host and supplies minimal stubs for unrelated game systems. Project scripts are structurally validated but are not all executed on the host: many require loaded map or battle state, deliberately wait indefinitely, or call game APIs with engine-only preconditions. The runtime tests cover interpreter behavior and scheduling without claiming to emulate general N64 or game behavior.
