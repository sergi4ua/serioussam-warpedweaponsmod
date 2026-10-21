> A list of significant features included in **Serious Sam Classics Patch**. Features marked with `Steam` in the beginning exist in the official Steam patch. Some of these features can be toggled in-game.

> For thorough customization use option configs under the new menu at **Options** -> **Classics Patch**.

> For quick configuration of the patch use preset scripts under **Options** -> **Execute Addon**.

# New features

## Additions
- Modular user plugin system via additional dynamic link libraries (DLL).
  - Supported by the game, dedicated servers and engine tools (Editor, Modeler and SKA Studio).
- Serious Editor with features from Serious Engine 1.10.
  - Terrain editing mode for the semi-finished terrain system.
  - World export feature for directly porting entire levels to SE3+ engines.
- Backported EngineGUI features from Serious Engine 1.50.
- Custom entity & game logic via a global "custom mod" for more advanced features and bug fixes.
  - Custom game themes for the main menu, the console and NETRICSA.
  - Larger font in NETRICSA and the console that scales with resolution.
  - Local customization of blood & gibs.
  - Weapon viewmodel customization: position, rotation, FOV, left-handed mode and power-up particles.
- Chat commands for servers.
  - Ability to add custom chat commands via plugins.
  - Admin and operator access to the server via passwords.
  - Voting system for changing maps, kicking clients etc.
- Observer camera system for advanced spectating, high quality screenshots and camera movement recording in demos.
  - Works in demos and while observing an active game in most mods.
  - Also works in Singleplayer & Cooperative modes in vanilla game with "Custom mod libraries" turned on.

## Visuals
- `Steam` More screen resolutions of various aspect ratios (not just 4:3).
  - Ability to add custom resolutions or by manually specifying one in video options.
  - Supports any screen resolution by dynamically adding it to the list.
- Borderless window mode. "Fullscreen" switch has been replaced with "Window Mode" that includes "Window", "Borderless" and "Fullscreen" options.
- `Steam` Preservation of vertical FOV on any non-4:3 aspect ratio.
  - `Steam` Fixed mip distances and weapon viewmodel FOV on wider aspect ratios.
  - Custom FOV commands (for first person & third person view) that work across all gamemodes. Limited to the 60-110 range.
- Reworked "Wide screen" functionality that fixes HUD display on wider aspect ratios.
- Awareness of DPI scaling for the game window on modern operating systems.
- Proper rendering of SKA models (skeletal animations) in **The Second Encounter v1.07**.
- Custom heads-up display (HUD) with many fixes and features for customization, such as themes.

## User experience
- `Steam` Working server list that doesn't depend on the now defunct GameSpy master server.
  - New query manager that supports 3 different protocols: Legacy (GameSpy emulation), DarkPlaces and GameAgent (from Serious Engine 1.10).
  - Ability to dynamically replace the GameSpy master server address directly in the engine.
- Levels from other games on Serious Engine 1 (such as Nitro Family or Alpha Black Zero) can now be safely stored in the game folder without crashing the game on launch but they cannot be played.
- Content from **The First Encounter** and **Serious Sam: Revolution** can be loaded into **The Second Encounter** by specifying paths to game installations.
  - Levels from **The First Encounter** and **Serious Sam: Revolution** can be played directly through **The Second Encounter** by converting them on load.
  - Additional content from **Serious Sam: Revolution** workshop (levels, player models etc.) can also be optionally mounted.
- Separation of config options (such as `Game Options` or configs in `Advanced Options`) into groups under different option tabs for easier navigation.
- Separation of levels into manually defined level categories (such as **TFE** and **TSE** levels) for easier navigation.
- Game render in the menu background.
- `Steam` Serious Editor with support of 64-bit operating systems.
  - Original 32-bit only Serious Editor can also be launched and used properly.
- "Textbox" type for in-game config settings for convenient editing of string commands.
- "Button" type for in-game config settings for recursive opening of option configs.
- Button in the level list for toggling visibility of all levels.
- Larger font in the server browser on higher resolutions.
- Anti-flood protection system to prevent server crashing.
- In-game chat commands for the server.
- Client logging system for keeping track of all clients that have ever joined the server.
- Client restriction system for convenient banning & muting of server clients.
- Ability to load extra content from other directories on disk instead of only the root game directory.
- Ability to edit buttons of common game controls in the same menu as personal player controls.
- Ability to type characters from different ANSI code pages instead of only Latin characters in any textbox and console.

## Other changes
- Removed "Waiting for server to continue" message from demos after changing levels.
- Menu elements now scale according to the window height instead of width (which previously made everything look too big with very little gaps).
- Up to 255 characters for editing player names and teams in-game.
- Various fixes of annoying bugs.

# Disadvantages of the Steam patch
- Incomplete support for widescreen resolutions.
  - Lack of 21:9 and other resolutions.
  - Mip distance adjustments are broken.
  - Inconsistent FOV between the player view and other places for rendering 3D elements (e.g. in mods).
- No predefined list of available master servers for GameSpy replacement.
- All of the new features are always on and cannot be toggled.
- No patch for **The Second Encounter v1.05**.
