# Star Rod

Star Rod is a suite of tools for editing assets.

| Tool             | Asset types |
|------------------|-------------|
| Map Editor       | Map models and collision |
| Sprite Editor    | NPC and player sprite animations |
| Globals Editor   | Item and move data |
| Message Editor   | Messages (e.g. dialogue) |
| World Map Editor | World map paths |

To open Star Rod, press Ctrl+Shift+P to open the command palette, then type "Tasks: Run Task" and press Enter, then select "Open Star Rod" from the list.

## Windows

Opening Star Rod from VSCode may not work on Windows. Instead:

- [Download the latest version of Star Rod](https://github.com/z64a/star-rod/releases/latest)
- Extract the ZIP file
- Run the `bat` file
- Select the papermario-dx folder as your project directory
    - You will need to [access the WSL filesystem](https://www.howtogeek.com/426749/how-to-access-your-linux-wsl-files-in-windows-10/) to find the folder
    - The path will be something like `\\wsl$\Ubuntu\home\yourusername\papermario-dx`

<div class="section_buttons">

| Previous                 | Next                     |
|:-------------------------|-------------------------:|
|[Assets](manual/assets.md)|[Debugging](manual/gdb.md)|

</div>
