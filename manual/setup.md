# Setup

[TOC]

### Prerequisites

You will need:

- A Paper Mario (USA) ROM
- A computer running Windows 11, Windows 10, macOS, or Linux
- [Visual Studio Code](https://code.visualstudio.com/Download)

<details>
    <summary>I don't have a ROM! Can I still use DX?</summary>
    <p>
        You must own a copy of Paper Mario (USA) to use DX. The European and Japanese versions of the game are not currently supported.
    </p>
    <p>
        There are a variety of tools you can use to dump a backup from your own cartridge or Virtual Console copy.
        If you do have a clean NTSC-U ROM, but it is in another format, <a href="https://hack64.net/tools/swapper.php">convert it to z64</a>.
    </p>
</details>

<details>
    <summary>I prefer my editor, like neovim. Do I have to use Visual Studio Code?</summary>
    <p>
        This guide assumes you are using Visual Studio Code.
        If you are using another editor, you will need to be smart enough to adapt the instructions to your editor.
    </p>
    <p>
        To build the game in the terminal, enter a <code>nix-shell</code> then do <code>./run</code>.
    </p>
</details>

### Windows 10 users only

If you're on Windows 10, please set up Windows Subsystem for Linux:

1. Install or upgrade to **WSL 2** following [these instructions](https://aka.ms/wsl2-install) (Ubuntu is recommended)
2. Open a WSL terminal
3. Run the following command: `sudo apt update && sudo apt upgrade && cd ~`

If you're on Windows 11, you can skip this step. If you're on an earlier version of Windows, you'll need to use a virtual machine or dual-boot Linux.

This step is necessary because DX uses a variety of tools that only work on Linux/macOS that don't work on Windows natively. WSL provides a Linux environment that can run these tools without any performance penalty.

### Open a terminal

- On Windows, open the WSL terminal you installed earlier. (Do **not** use the Command Prompt or PowerShell.)
- On macOS, open Terminal.
- On Linux, open your terminal emulator of choice.

You should see some sort of prompt, for instance, `user@hostname:~$`. This is where you will type commands and press Enter to run them.

Don't be scared by the terminal - it's just a way to interact with your computer using text commands. You can copy and paste commands from this guide. Use Ctrl+Shift+V to paste into the terminal. **After completing setup, you won't need to use the terminal anymore.**

### Install Nix and Cachix

Nix is a package manager that DX uses to manage its dependencies.

Run the following command in your terminal by typing it in and pressing Enter. You can also paste it with Ctrl+Shift+V.

```sh
bash <(curl -L https://nixos.org/nix/install)
```

Run the following command to install Cachix:

```sh
nix-env -iA cachix -f https://cachix.org/api/v1/install
```

Then, tell Cachix to use the `papermario-dx` cache:

```sh
cachix use papermario-dx
```

The cache allows Nix to download tools that are needed to build DX, rather than building them from scratch. This will save you a lot of time.

### Clone the repository

Run both the following commands in your terminal:

```sh
git clone https://github.com/bates64/papermario-dx
cd papermario-dx
```

This will copy Paper Mario DX into a directory (folder) called `~/papermario-dx`. In future, you can type `cd ~/papermario-dx` to navigate here.

### Open Visual Studio Code

This command will open Visual Studio Code in the `papermario-dx` directory:

```sh
code .
```

Later, you can open DX again in Visual Studio Code by using the 'Recent' menu on the Welcome screen, or by running `code ~/papermario-dx` in the terminal.

### Copy the base ROM to the correct location

In Visual Studio Code, click on the `ver` folder, then the `us` folder. Drag and drop your ROM into this folder. Rename the file to `baserom.z64`.

### Run the game

Press Ctrl+Shift+B (Cmd+Shift+B on macOS) to build the game. This can take a while (more than 5 minutes) the first time you do it depending on how fast your computer is.

DX will automatically try to run the game in a known emulator after building. If you don't have an emulator already, I recommend using [ares](https://ares-emu.net) because it is very accurate. If you don't regularly test with ares and/or real hardware, your mod may not work correctly for others.

If you prefer real hardware, you can copy the output ROM `ver/us/build/papermario.z64` to a flashcart.

### Next steps

If you've made it this far, congratulations! You've successfully set up Paper Mario DX.

You're _almost_ ready to start making changes to the game. To do that, you need to [learn about the asset stack](manual/assets.md).

### Help!!!!

If you run into any issues during setup, ask for help in the `#papermario-dx` channel in the [Star Haven Discord](https://discord.gg/star-haven).

<div class="section_buttons">

| Previous | Next |
|:---------|-----:|
|[Introduction](manual/introduction.md)|[The Asset Stack](manual/assets.md)|

</div>
