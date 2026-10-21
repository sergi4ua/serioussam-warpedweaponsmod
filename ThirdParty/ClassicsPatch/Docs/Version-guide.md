> A unified & simplified changelog of all release versions of **Serious Sam Classics Patch**, including their patches for easier understanding of what has been added in each version.

- Releases since **1.2**: https://github.com/SamClassicPatch/SuperProject/releases
- Releases before **1.2**: https://github.com/SamClassicPatch/GameExecutable/releases

# 1.9 ~ 1.9.4 - "Taking Back Control"
Improved support of game controllers using SDL, game controller input in menu & NETRICSA and some reworked game menu functionality.

- Refactoring of the project that merges all code into a single repository.
- Extended input functionality via a new "Extended Input" extension:
  - Made **Mouse Button 4** and **Mouse Button 5** work properly.
  - Renamed all controller buttons & axes from generic joystick names to actions of an Xbox-like controller.
  - Allowed controller axes to be bound as regular buttons.
- Aliased new `ocam_` commands using old `cam_` commands in Game library.
- New system for taking global game screenshots akin to Steam with support of various file formats.
- Added gameplay extension for toggling fast movement while holding a knife in Cooperative mode.
- Replaced hardcoded "Video Options" & "Audio Options" menus with custom option configs.
  - Addition of custom screen resolutions using a list file.
- Allowed using controllers for navigating the game menu and NETRICSA.
- Completely remade "Advanced Joystick Setup" menu.
- Added proper scrollbars on the right side of the menu to replace old "Page Up" and "Page Down" buttons.
- Added startup notifications about current seasonal events.
- Changes to option configs:
  - Added `BigFill` type to the `Slider:` property that creates big fill bars.
  - Added `Button` type for creating clickable buttons that recursively open another option config.
  - Added `KeyBind` type for creating options for binding key identifiers.
  - Added `AutoValue:` property for automatic configuration of the option based on the specified variable.
  - Added `RealTime:` property for allowing config options to apply their values in real time.
  - Convenient drop-down lists for `Toggle` config options with more than 2 values (similar to Serious Sam HD).
- Options for the observer camera and a "photo mode" button in the in-game pause menu.
- Up to 17 custom level categories.
- Allowed `ModelHolder2` entities to be visible at any distance by toggling their MIP fade-out using `gfx_bAdjustModelHolderMipFactor`.
- Allowed customizing viewmodels more thoroughly and per separate weapon type.
- Redesigned and rewritten API for modders.
- Default control presets for game controllers in slots 1-4.
- Fixes of old bugs:
  - Prevented lens flares from rendering through everything in the menu background.
  - Made the patch treat `ClassicsPatchMod` mod as vanilla game, like `SeriousSam`.
  - Prevented texture mapping on selected brush polygons resetting to the mapping of the first selected polygon in Serious Editor.
  - Fixed crashes from worlds that are prefixed with a number 1-15 in TSE without mounting TFE.
  - Fixed choppy rendering of the menu, the console and NETRICSA from accumulating too much CPU time.
- New "extension" plugins for decoupling optional patch functionality into separate plugins.
- Reworked and improved world converters.
- Implemented Squirrel scripting language via a new "Scripting Engine" extension (unfinished experimental feature).
- Fatal error upon starting Classics Patch on the incorrect game build.
- Official support for Italian localization of the patch.

# 1.8 - "Steamy Observation"
Extended support of levels from **Revolution**, observer camera system, voting system and extra features for Steam players.

- Separate switches in the patch config for toggling mounting of each game directory.
- Experimental command for automatically replacing missing resources with placeholders.
- Observer camera system (a.k.a. "OCAM") for advanced spectating, high quality screenshots and camera movement recording in demos.
  - Works in demos and while observing an active game in most mods.
  - Also works in Singleplayer & Cooperative modes in vanilla game with "Custom mod libraries" turned on.
- Steam-exclusive features:
  - Automatic game pause upon opening Steam overlay mid-game.
  - Ability to take high quality screenshots using observer camera.
  - Ability to join the same server via a friend by using "Join game" button.
- Built custom Entities library for **The First Encounter v1.05** and **The Second Encounter v1.05**.
- New entity pack that implements missing entities: new enemies from Alpha and Revolution, new entities from Revolution and terrain entity for TSE v1.07.
- "Monster" Arachnoid and new projectile types for levels from Revolution.
- Commands for extra scaling of big fonts in console and NETRICSA.
- Put the same restrictions on the vanilla FOV command in Deathmatch and fixed Sniper Rifle overriding custom FOV.
- Ability to edit buttons of common game controls in the same menu as personal player controls.
- Added "Extreme" option to rendering preferences in video options for setting best possible graphics.
- Allowed typing characters from different ANSI code pages instead of only Latin characters in any textbox and console.
- Voting system via chat commands for players and observers to use. Map changing, client kicking & muting, round skipping.
- New built-in extension packets: world changing, session property modification, gameplay extension modification.
- New buttons for undocumented Serious Editor features for exporting entities and their placements in **Serious Engine 2+** ASCII formats.
- Tags above players that display their names and relative distance to them for Advanced HUD plugin.
- Implemented "packet" and "timer" events for plugins.
- Steamworks SDK updated to v1.59.

# 1.7 ~ 1.7.2 - "Compatibility Mode"
Support for most content from **Revolution**, better support for tools & mods and introduction of gameplay extensions.

- Support for content from **Serious Sam: Revolution** in **The Second Encounter**:
  - Mounting of Revolution game files.
  - Mounting of content from Revolution's Steam Workshop.
  - Dynamic conversion of Revolution worlds in Serious Editor and from inside the game.
- Full integration of patch functionality into tool applications (including vanilla/unpatched executables):
  - Extra content directories.
  - 64-bit system support.
- Gameplay extensions for customizing gameplay experience:
  - Elimination of the slowdown bug after 4096 in-game seconds.
  - Customization of the player movement and gravity.
- Detection of specific seasonal events that can be used for cosmetic purposes.
- Local customization of blood & gibs.
- Weapon viewmodel customization: position, rotation, FOV, left-handed mode and power-up particles.
- Enhanced compatibility with TFE levels in TSE.
- "Serious Jump" powerup for Revolution levels.
- New options for filtering levels in the list: by world format and by display title.
- Support for server administrators and server operators that can log in during the game.
- Draggable slider gadgets in the menu.
- Automatic loading of the patch upon loading the Classics Patch mod from vanilla game.
- Support for vanilla master server functionality and replacement of hardcoded GameSpy master server with Legacy.
- Preset scripts under "Execute addon" for automatic configuration of the patch.

# 1.6 ~ 1.6.2 - "Anniversary Update"
Improvements to the features from "Platinum Edition" and extended server & gameplay manipulation.

- Built a custom mod that directly replaces vanilla logic.
  - Text in NETRICSA scales with larger resolutions.
  - Support for custom game themes in the menu, console and NETRICSA.
  - Ability to display advanced observer view windows on the side rather than over the main view.
- Level categories for separating one huge level list into smaller groups.
- GUID masking of player characters to prevent clients from stealing them.
- Built-in extension packets for extended entity manipulation.
- Option to make patched servers exclusive to clients that run the same version of the patch.
- Customizable connection setting.
- A separate config file for customizing patch behavior before initializing the engine.
- Fixed broken shadows after loading a game.
- Automatic checks for new patch updates.
- New "listener" and "demo" events for user plugins.

# 1.5 ~ 1.5.1 - "Platinum Edition"
Unification of both classic games under **The Second Encounter**.

- Support for content from **The First Encounter** in **The Second Encounter**:
  - Mounting of TFE game files.
  - Dynamic conversion of TFE worlds from inside the game.
- Ability to load GRO files from extra content directories outside the game.
- Plugin that reworks and improves the HUD and adds customizable themes: TFE, Warped, TSE and Revolution.
- More characters per line in the console with dynamic scaling depending on the resolution.
- New "game" and "world" events for user plugins.

# 1.4 ~ 1.4.2 - "Modernization"
Native resolution support and a number of convenient features.

- Fixed rendering of SKA models in fog & haze in **The Second Encounter v1.07**.
- Support for in-game chat commands.
- Client logging system that keeps track of all clients that have ever connected to the server.
  - Client restriction system that allows banning and muting clients.
- DPI awareness for the game window.
- "Textbox" setting type for modifying string properties and an optional "Hidden:" parameter.
- Button in the level selection list for toggling visibility of all world files.
- EngineGUI library changes from Serious Engine 1.50.
- Local auto-kill and item creation cheats.
- Larger font in the server browser for larger resolutions.
- Official support for Russian localization of the patch.

# 1.3 ~ 1.3.1 - "Modular Modding"
Improved API for user plugins and extended server control.

- Patched Serious Editor executable with 64-bit support and features from 1.10.
- Plugin with useful server utilities for customizing the world.
- Protection against multiplayer packet flood.
- Protection against split-screen clients.
- Custom rendering support in plugins for Serious Modeler and Serious SKA Studio.
- Networking events for plugins using custom packets.

# 1.2 - "A Fresh Start"
Major refactoring of the project with support for more projects outside of the game executable.

- Modular user plugin system via DLLs for the game & engine tools.
- Executable patch for the dedicated server.

# 1.1 ~ 1.1.2 - "Multilayered Multiplayer"
Patched executable for each relevant game version with various improvements.

- Additional executables for v1.05 games (TFE and TSE).
- New options menu for customizing the patch.
- Separation of config options into groups under different option tabs.
- Local server cheats that work across any gamemode and any mod.
- Custom FOV command for the third person view.
- Patch API for modders.

# 1.0 ~ 1.0.3
The first patch release, specifically for **The Second Encounter v1.07**.

- Support for a variety of widescreen resolutions separated by aspect ratios. Additional adjustments for widescreen resolutions:
  - FOV & mip adjustments.
  - Scaling of menu elements.
  - HUD adjustments.
- Custom FOV command that works in all gamemodes.
- Borderless window mode.
- Working server list with 3 different protocols: Legacy (GameSpy), DarkPlaces, GameAgent.
- Game render in the menu background.
- Toggleable red screen on damage.
- Removal of "Waiting for server to continue" message from demos.
