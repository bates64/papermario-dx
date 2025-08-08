# Introduction

Welcome to the **Paper Mario DX manual**.
This manual will guide you through the process of creating mods for Paper Mario (N64) using DX.

With DX, you have the power to modify any aspect of Paper Mario, including modifying the game engine itself.

## Important terminology

<details>
    <summary>What is a ROM?</summary>
    The N64 console stores games on cartridges. A ROM is a file that contains the data from one of these cartridges.
    The Paper Mario (USA) ROM contains all of the game - including the code, graphics, and sound. There are also
    other Paper Mario ROMs for different regions, such as Europe and Japan, but DX only supports the USA version.
</details>

<details>
    <summary>What is modding? What is a ROM hack?</summary>
    <p>
        Modding is the process of modifying a video game to change its behavior or appearance.
        A mod is a file or set of files that changes the game in some way.
    </p>
    <p>
        A ROM hack is a mod that modifies a game's ROM file. ROM hacks are usually distributed as patches
        that can be applied to a clean ROM to create a modified version of the game.
    </p>
    <p>
        For our purposes, the terms "ROM hack" and "mod" refer to the same thing: the completed product of modding.
    </p>
</details>

<details>
    <summary>What do "decompilation" and "decomp" mean?</summary>
    <p>
        Decompilation is the process of converting a compiled program (in this case, Paper Mario) back into a
        human-readable form (source code). Among other things, this makes modding much, much easier.
        You can learn more about video game decompilation on <a href="https://wiki.decomp.dev/">Decompedia</a>.
    </p>
    <p>
        Paper Mario DX is based ontop of <a href="https://papermar.io">the Paper Mario decompilation</a>, also
        known as <b>the decomp</b>.
        <b>Decomp modding</b> refers to the process of creating mods using the decomp.
    </p>
</details>

<details>
    <summary>How does DX compare with Star Rod Classic?</summary>
    <p>
        Star Rod Classic is a modding tool for Paper Mario that was used to create many popular mods.
        DX is a newer tool that is more powerful, but also more complex.
    </p>
    <p>
        Star Rod Classic requires you to write assembly code to do anything complicated. With DX, you can write C code.
    </p>
    <p>
        To edit map geometry and preview messages, you can use
        <a href="https://github.com/z64a/star-rod/releases/latest">Star Rod</a> with DX.
        Open Star Rod and select your mod folder as the project directory.
        Star Rod Classic is not compatible with DX.
    </p>
</details>

## Compatibility

<details>
    <summary>What kind of computer do I need to use DX?</summary>
    To make mods with DX, you will need a computer with one of the following operating systems:
    <ul>
        <li>Windows 11</li> <!-- WSL installed by default -->
        <li>Windows 10</li>
        <li>macOS</li>
        <li>Linux</li>
    </ul>
</details>

<details>
    <summary>Can I play DX mods on my N64?</summary>
    <p>
        You can play DX mods on N64 hardware using a flashcart such as
        an <a href="https://n64brew.dev/wiki/Everdrive_64">Everdrive 64</a>
        or a <a href="https://summercart64.dev/">SummerCart64</a>.
        You will also require an <b>expansion pak</b>.
    </p>
    <p>
        DX outputs an NTSC region ROM in big endian format (`.z64`). Transfer this file to your flashcart to play.
    </p>
</details>

<details>
    <summary>Can I share ROMs built with DX with others?</summary>
    <p>
        <b>No! Never share ROMs with others.</b> Sharing ROMs may be considered an act of piracy.
    </p>
    <p>
        Instead, <b>share a patch file</b>. A patch file is a description of the <i>changes</i> between the Paper Mario
        base ROM and the ROM built by DX.
    </p>
    <p>
        DX will automatically generate a `.bps` patch file for you. The people you share
        the patch file with can use <a href="https://hack64.net/tools/patcher.php">a web patching tool</a> to obtain a
        ROM that they can play.
    </p>
</details>

<div class="section_buttons">

| Previous | Next |
|:---------|-----:|
|[Main page](../README.md)|[Setup](setup.md)|

</div>
