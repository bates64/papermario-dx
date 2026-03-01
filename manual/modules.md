# Modules

[TOC]

A module is a unit of dynamically linked code that can be loaded at runtime. It is compiled separately from the main game binary and appended to the ROM. At runtime, the module loader relocates the code into memory and executes it. If you are familiar with DLLs, DSOs, or RELs, modules are the same idea.

## Creating a module

A module is a directory containing source files and a `module.toml` configuration file.

```
my_module/
├── module.toml
├── main.cpp
└── build/          (generated)
```

### module.toml

| Key        | Type   | Default        | Description                                      |
|------------|--------|----------------|--------------------------------------------------|
| `name`     | string | directory name | Unique* identifier for this module               |
| `autoload` | bool   | `false`        | Load the module automatically at boot            |

\* If two modules share the same name, the one applied last overrides the earlier one.

### Source files

Module source files have access to all the game's headers:

```cpp
#include "common.h"

__attribute__((constructor))
void my_init() {
    // Runs when the module is loaded
}
```

Both C (`.c`) and C++ (`.cpp`) source files are supported.

Functions marked with `__attribute__((constructor))` run automatically when the module is loaded. Functions marked with `__attribute__((destructor))` run when the module is unloaded. C++ static initializers and destructors also work as expected.

## Building in-tree

Modules placed in the `modules/` directory of the repository are built automatically as part of the normal build.

The final ROM (`ver/us/build/papermario.z64`) includes all in-tree modules. The base ROM without modules is `ver/us/build/papermario_base.z64`.

## Building out-of-tree

For mods developed outside the repository, use `module.py`. You need a copy of dx: either the full repository after a build, or a dx release tarball.

### Build the module

From your module directory:

```sh
python3 /path/to/dx/tools/build/module.py build
```

This generates `build/<name>.module`.

### Apply to a ROM

```sh
python3 /path/to/dx/tools/build/module.py apply base.z64
```

`base.z64` should be a Paper Mario DX ROM, with or without modules.

This creates `build/<name>.z64` with your module applied. Use `-o output.z64` to specify a different output path.

Multiple modules can be applied to the same ROM sequentially. Each apply appends a new module and directory entry without modifying existing ones, unless it is named the same as an existing module, in which case
it will overwrite the existing module.

## Loading modules

```cpp
#include <dx/module.hpp>

auto& mod = Module::get("name_of_module");
```

`Module::get` loads a module by name if it isn't already loaded. Calling `Module::get` again with the same name returns the existing instance.

### Exports

Modules can export symbols that are accessible from the returned `Module&`:

```cpp
auto fn = mod.sym<void()>("my_function");
```

Note that C++ symbols are mangled. Use `extern "C"` to export with a clean name, or use the mangled name.

## How modules work

After the main ROM is built, modules are applied to it. Their data is appended and an entry is written into `moduleDirectory`, a table in the main binary.

Because modules are applied after the main build, a mod can be shipped as a set of modules and applied onto a base ROM, making mods composable. The development experience is also faster: changing a module only recompiles that module's sources, without needing to re-link the entire engine.

<div class="table-nav">

| Previous | Next |
|:---------|-----:|
|[Assets](assets.md)|[Star Rod](star-rod.md)|

</div>
