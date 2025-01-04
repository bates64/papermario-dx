# Setup

[TOC]

### Prerequisites

You will need:

- A Paper Mario (USA) ROM
- A computer running Windows 11, Windows 10, macOS, or Linux

### Step 1. Install WSL (Windows only)

1. Open PowerShell in administrator mode by right-clicking and selecting "Run as administrator".
2. Type `wsl --install` and press Enter.
3. Restart your computer.
4. After restarting, an "Ubuntu" installation window will appear. Follow the instructions to set it up.

### Step 2. Install Visual Studio Code

Download and install Visual Studio Code (VSCode), a code editor that works well with DX:

[Download Visual Studio Code](https://code.visualstudio.com/)

<details>
    <summary>I prefer my editor, like neovim. Do I have to use Visual Studio Code?</summary>
    <p>
        This manual assumes you are using Visual Studio Code, but it is possible to use another editor.
        However, you will need to adapt instructions to your editor and be confident using the command line.
    </p>
    <p>
        For Step 4, to run the game, use <code>nix develop --profile .nix-profile --command ./run</code>.
    </p>
</details>

### Step 3. Run the setup script

On Windows, open WSL. On macOS, open Terminal.

Carefully type the following command and press Enter:

```sh
bash <(curl -Ls https://bates64.com/setup-dx.sh)
```

Then follow the instructions to set up DX.

<details>
    <summary>How do I set up DX in a specific directory?</summary>
    <p>
        Type <code>DX_DIR=~/my-folder</code>, then run the setup script as above.
    </p>
</details>

<details>
    <summary>It asked me for a ROM, but I don't have one!</summary>
    <p>
        You must own a copy of Paper Mario (USA) to use DX. The European and Japanese versions of the game are not currently supported.
    </p>
    <p>
        There are a variety of tools you can use to dump a backup from your own cartridge or Virtual Console copy.
        If you do have a clean NTSC-U ROM, but it is in another format, <a href="https://hack64.net/tools/swapper.php">convert it to z64</a>.
    </p>
</details>

When the script finishes successfully, it should open DX in VSCode. You can close the terminal now.

### Step 4. Build and run the game

With VSCode open, **press Ctrl+Shift+B (Cmd+Shift+B on macOS) to build the game.**

DX will automatically try to run the game in a known emulator after building. If you don't have an emulator already, I recommend using [ares](https://ares-emu.net) because it is very accurate. If you don't regularly test with ares and/or real hardware, your mod may not work correctly for others.
<!-- TODO: guide to install ares and add it to PATH, or make it part of the flake (but what about Windows?) -->

If DX did not find your emulator, you can load the ROM manually. The output ROM is located at `ver/us/build/papermario.z64`.

If you prefer real hardware, you can copy the output ROM `ver/us/build/papermario.z64` to a flashcart.

### Next steps

If you've made it this far, congratulations! You've successfully set up Paper Mario DX.

You're _almost_ ready to start making changes to the game. To do that, you need to [learn about the asset stack](manual/assets.md).

### I closed VSCode! How do I open it again?

You can reopen it by using the 'Recent' menu on the VSCode Welcome screen.

If you can't find it, you can open VSCode from a terminal. Open a terminal and run `code ~/papermario-dx`. Note that you should use WSL if you're on Windows.

### Help!!!!

If you run into any issues during setup, ask for help in the `#papermario-dx` channel in the [Star Haven Discord](https://discord.gg/star-haven).

<div class="section_buttons">

| Previous | Next |
|:---------|-----:|
|[Introduction](manual/introduction.md)|[The Asset Stack](manual/assets.md)|

</div>
