# Setup

This repository supports:

- [Linux](#unix)
- [macOS](#unix)
- [Windows Subsystem for Linux 2](#wsl-2)

If you encounter any issues setting up the repo, please feel free to [reach out to us on Discord](https://discord.gg/PgcMpQTzh5).

## Common

Clone the repository:
```sh
git clone https://github.com/nanaian/papermario-dx
cd papermario
```

Install pigment64 (our image-processing tool)
```sh
curl https://sh.rustup.rs -sSf | sh
cargo install pigment64
```
and make sure pigment64 is in your system path.

## Unix

Install build dependencies:
```sh
./install_deps.sh
./install_compilers.sh
```

> **NOTE:** On Mac, if you get an error that looks like
>
>```sh
>Error: Cannot install md5sha1sum because conflicting formulae are installed.
>  coreutils: because both install `md5sum` and `sha1sum` binaries
>
>Please `brew unlink coreutils` before continuing.
>```
>
>it's fine to just open `install_deps.sh` in a text editor, delete the `md5sha1sum` from the `brew install` line, and rerun it (put it back after so you don't accidentally commit it!)

Continue onto [building](#building)

## WSL 2

1. Install or upgrade to **WSL 2** following [these instructions](https://aka.ms/wsl2-install) (Ubuntu is recommended)
2. Open a WSL terminal
3. Run the following command: `sudo apt update && sudo apt upgrade && cd ~`
4. Install build dependencies:
```sh
./install_deps.sh
./install_compilers.sh
```
5. Continue with [building](#building)

If you have Visual Studio Code, you can type `code .` to open the repo within it.
`Ctrl + J` opens up a Linux terminal within VS Code.


# Building

Copy baserom into the following place:

* `ver/us/baserom.z64` (sha1: `3837f44cda784b466c9a2d99df70d77c322b97a0`)

(If you're using WSL, you can enter the Linux filesystem by opening `\\wsl$` in File Explorer; e.g. `\\wsl$\Ubuntu\home\<your username>\papermario-dx`.)

Configure the build and extract assets from the base ROM:
```sh
./configure
```

Compile the game:
```
ninja
```

The output ROM is `ver/us/build/papermario.z64` - you can run this in any N64 emulator.

Alternative, to compile _and_ run, you can use the `run` script:
```sh
./run
```
(This will search [known paths](run) for an emulator. If your emulator isn't listed, add it to the list and contribute!)

You can now begin modding.
