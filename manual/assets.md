# Managing Assets

### What is considered an asset?

An asset is any file containing game data that is not code. Common examples include textures, models, audio files, and images.

### Understanding the Asset Stack

DX uses a system known as the **Asset Stack** when building game assets. The asset stack allows you to safely override existing game assets without permanently modifying or deleting the original files.

To view the asset stack, open your project in Visual Studio Code and navigate to the `assets` directory. You will find these subdirectories:

- `assets/mod/` contains custom assets for your mod.
- `assets/dx/` contains assets required by DX.
- `assets/us/` contains assets extracted from your base ROM (`us` because the base ROM is the USA version).

### How Asset Priority Works

When building the game, DX looks for assets within these asset directories using the order defined by `asset_stack` in `ver/us/splat.yaml`. By default, the order will be:
1. First, it looks in `assets/mod/`
2. If the asset isn't found there, it checks `assets/dx/`
3. If still not found, it falls back to `assets/us/`

If an asset required by your modded game doesn't exist in any of these directories, DX will fail to build.

### Adding a new asset directory

To add a new asset directory, you have two options:

1. **Use the default mod directory**:\
   Place your mod's assets directly into the existing `assets/mod/` directory.

2. **Rename the default mod directory**:\
   Rename the `assets/mod/` directory to a unique name for your mod (e.g., `assets/master_quest/`) and place your assets there. If you choose this approach, you must also modify the asset_stack entry in `ver/us/splat.yaml`. Find `asset_stack` with Ctrl+F and rename `mod` to match your asset directory name.

**Never** modify anything in `assets/dx/` or `assets/us/`. Keeping your mod assets separate helps prevent conflicts between mods.

For example, for an innovative mod called *"Paper Master: Mario Quest,"* you could rename `assets/mod/` to `assets/master_quest/`. Then, place all your assets into this newly named directory.

DX automatically prioritizes assets placed in your mod directory first, then falls back to `assets/dx/`, and finally to `assets/us/`. Avoid using spaces in directory or file names to ensure compatibility.

### Overriding an asset

To override an asset, place a file with the same path in your asset directory as the asset you want to override.

For example, let's override the title screen background image! We can find this at `assets/us/mapfs/bg/title_bg.png`.

Copy that file. Then, create the directories `assets/master_quest/mapfs/bg/` and paste the file there.

Then modify the pasted file in a pixel art editing program such as [Aseprite] (paid) or [LibreSprite] (free).
[Aseprite]: https://www.aseprite.org/
[LibreSprite]: https://libresprite.github.io/#!/downloads

Finally, run the mod to see your changes.

<div class="section_buttons">

| Previous | Next |
|:---------|-----:|
|[Setup](setup.md)|[Star Rod](star-rod.md)|

</div>
