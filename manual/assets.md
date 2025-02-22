# The Asset Stack

DX uses a system called the Asset Stack when building assets. It allows you to override game assets with your own custom assets.

<details>
    <summary>What is an asset?</summary>
    An asset is a file of game data, as opposed to a code file. Examples of assets include textures, models, and audio files.
</details>

If you're familiar with LayeredFS from the Nintendo Switch modding scene, the Asset Stack behaves similarly.

### How it works

In Visual Studio Code, click on the `assets` directory in the Explorer. You should see these subdirectories:

- `assets/dx/` contains assets from DX.
- `assets/us/` contains assets split from your base ROM (`us` because the base ROM is the USA version).

When building assets, DX will look in `assets/dx/` first. If it doesn't find the asset there, it will look in `assets/us/`.

For example, when building the asset `crash_screen/font.png`, DX will look for `assets/dx/crash_screen/font.png`. If that file does not exist, it will look in `assets/us/crash_screen/font.png`. If it still doesn't find the file, DX will fail to build.

### Adding a new asset directory

To add a new asset directory, create a new directory in `assets/` and place your assets there. **You should create a new asset directory for your mod.** This will prevent conflicts between mods. **Never** modify anything in `assets/dx/` or `assets/us/`.

For example, to add a new asset directory for your innovative mod "Paper Master: Mario Quest," right-click on the `assets` directory and select "New Folder". Name the folder `master_quest` (or whatever you like).

You can now place assets in `assets/master_quest/`, but DX will not use them. Note: do not use spaces in directory or file names.

To tell DX to prioritise your new asset directory, open the file `ver/us/splat.yaml`. Find the `asset_stack` list with Ctrl+F and **prepend** your new asset directory to the list.

```yaml
asset_stack:
  - master_quest
  - dx
  - us
```

Now, when building assets, DX will look in `assets/master_quest/` first, then `assets/dx/`, and finally `assets/us/`.

### Overriding an asset

To override an asset, place a file with the same path in your asset directory as the asset you want to override.

For example, let's override the title screen background image! We can find this at `assets/us/mapfs/bg/title_bg.png`.

Copy that file. Then, create the directories `assets/master_quest/mapfs/bg/` and paste the file there.

Then modify the pasted file in a pixel art editing program such as [Aseprite] (paid) or [LibreSprite] (free).
[Aseprite]: https://www.aseprite.org/
[LibreSprite]: https://libresprite.github.io/#!/downloads

Finally, run the mod to see your changes.

<div class="section_buttons">

| Previous                |                             Next |
|:------------------------|---------------------------------:|
|[Setup](manual/setup.md) |[Star Rod](manual/star-rod.md)    |

</div>
