> Answers to frequently asked questions and notes about **Serious Sam Classics Patch**.

## Which games are supported?
The patch supports all latest versions of Serious Sam games on Serious Engine 1:
- **Serious Sam: The First Encounter v1.05** (including Steam and GOG versions)
  - Build archives starting with `TFE1.05`.
- **Serious Sam: The Second Encounter v1.05**
  - Build archives starting with `TSE1.05`.
- **Serious Sam: The Second Encounter v1.07** (including Steam and GOG versions)
  - Build archives starting with `TSE1.07`.

## How to launch the game with the patch?
Classics Patch can be launched by either using executables that ship with it (filenames ending with `_Custom.exe`, e.g. `SeriousSam_Custom.exe`) or by starting the *"Serious Sam \[Classics Patch]"* mod from the **Mods** menu in-game.

Alternatively, you can make the game start with the patch automatically by choosing one of the following ways.

### Launch argument
The easiest way is to force the game to start the Classics Patch mod.

**Steam:**
1. Right click on the game -> **Properties** -> **General**.
2. Enter `+game ClassicsPatchMod` in the "Launch options" field.

**Windows:**
1. Locate a shortcut to the game (or create a new one).
2. Right click on the shortcut -> **Properties** -> **Shortcut**.
3. Add `+game ClassicsPatchMod` at the end of the "Target" field (after the path to the executable).

### Replacing the executable
The most reliable way is to replace the game executable with the patch one.

1. Navigate to the game's installation directory (in Steam: right click on a game -> **Manage** -> **Browse local files**; or inside `steamapps/common` within the Steam library folder).
2. Go to the `Bin` folder and backup original `SeriousSam.exe` file somewhere.
3. Rename `SeriousSam_Custom.exe` into `SeriousSam.exe`.

After that Steam or any shortcut to the game will start the patch instead of the vanilla game. The same can be done to `SeriousEditor.exe`.

## How to uninstall the patch?
You don't really have to uninstall anything because all vanilla executable files still work as intended.

To know whether or not you're still playing with the patch, type `PatchInfo()` into console to verify it. You can also type `ListPlugins()` to see which plugins are loaded. Such commands don't exist in vanilla games.

The patch still replaces a couple of files, which need to be removed in order to **truly** uninstall the patch. These files are:
- `Bin/EngineGUI.dll` - This primarily implements the patch into the tools, i.e. Serious Editor, Serious Modeler and Serious SKA Studio.
  - The original library is bundled with the patch as `EngineGUI_OG.dll`. Rename it to `EngineGUI.dll` to restore it.
- `Bin/Shaders.dll` - This fixes issues related to rendering of SKA models and its shaders for **The Second Encounter v1.07**. If you start the vanilla game, this library will still take effect as soon as at least one SKA model is loaded in any way. It won't actually add any patch-related features, only fix rendering of SKA models.
  - The original library is bundled with the patch as `Shaders_OG.dll`. Rename it to `Shaders.dll` to restore it.

Other files that you may also want to remove are:
- Within the `Bin` directory:
  - Base modules: `ClassicsCore.dll`.
  - Custom mod: `ClassicsExtras_Custom.dll`, `Entities_Custom.dll`, `GameGUI_Custom.dll`, `Game_Custom.dll`.
  - Executable files: `DedicatedServer_Custom.exe`, `SeriousEditor_Custom.exe`, `SeriousSam_Custom.exe`.
  - Plugins: Any `.dll` file in the `Plugins` folder (or the folder in its entirety).
  - Third party libraries: `SDL3.dll`, `steam_api.dll`.
- Within the game directory:
  - Patch resources: `SE1_ClassicsPatch.gro`, `SE1_RevResources.gro`.
  - User files and configs: `Data/ClassicsPatch` folder (optional, vanilla game ignores them).

## I'm getting "Wrong CRC", "Invalid DIFF stream" and similar errors when connecting to any server!
These can happen quite frequenty because of many different reasons.

Let's look at the things that may cause these errors upon connection and how they can be solved.

### 1. Mismatching game resources
Even without Classics Patch, most of the time these errors happen when some game resources have been modified in a way that makes them conflict with vanilla resources. This includes model replacements (e.g. new weapon models) and modifications of standard world files (e.g. `Levels/LevelsMP/1_1_Palenque.wld`).

**To solve this:**
- Remove all of the conflicting resources (and GRO archives containing them).
- Restore original game files either from backups, your installation disc or by verifying integrity of game files in **Steam**.
- Unsubscribe from content in **Serious Sam: Revolution** workshop that may create resource conflicts, in case all clients intend to play new levels from there.

### 2. Mounting Revolution content
If you're certain that it's not an issue with mismatching game resources *and* you're also able to connect to servers normally without using Classics Patch, then it must be because of mounted game installations.

**To solve this:**
- Unmount **Revolution** and restart the game.
- Unmount **Revolution workshop** and restart the game.

### 3. Custom mod inconsistency
If you plan on playing levels from **Serious Sam: Revolution** with someone else, you may not be able to connect because client's "Custom mod libraries" setting mismatches the server one. It is recommended to enable `CustomMod` in config properties in order to experience **Revolution** levels to their fullest.

**To solve this:**
- All clients need to make sure that their "Custom mod libraries" setting matches the server host. If not, they must toggle it, restart the game, and then try connecting to the server again.

### 4. NoCRC list inconsistency
In some rare cases you might get "Wrong CRC check" error upon connecting to a server even if it's none of the issues above.  
This could potentially happen because of the mismatching `Data/NoCRC.lst` file or because of the complete absence of it.

If you keep getting errors on connection and somehow don't have this file in your game directory, try creating it (or opening it if it's already there) and make it contain **only** these entries:
```
*.dll
*.wav
*.des
*.txt
*.fnt
*.tex
*.lst
*.tbn
*.ogg
*.mp3
```

## Does it fix issues with VSync, refresh rate and other graphical wackiness?
Unforunately, no. These issues arise from something deep inside the engine itself. And even if it's somehow possible to fix them from the outside, it will require too much effort. Plus, I'm no expert in this field.

## I've installed one of the patch localizations but most text is still in English!
That's because included localization files only translate text of **Classics Patch**. If you need official localization files for the **game itself**, you can find them in this archive: [`DreamyCecil/SE1-Localization`](https://github.com/DreamyCecil/SE1-Localization?tab=readme-ov-file#serious-sam-localizations)

## The patch supposedly fixed the "slowdown bug" but I'm still experiencing it. Why?
The slowdown bug is fixed by using new gameplay extension called "Fix Timers". It is enabled by default for all new games started with the patch.  
The only bug it doesn't fix is the firerate of the Minor Bio-mechanoid (blue Walker enemy) because its internal timer logic there differs from the rest of the entities.

If you join a vanilla multiplayer server or load an old save file that was created without the patch, the gameplay extensions will be disabled on that run for compatibility reasons.

If you wish to fix the slowdown bug on your old pre-patch save, run these console commands to enable the gameplay extension:
```
pck_GameplayExtNumber("Enable", 1.0);
pck_GameplayExtNumber("FixTimers", 1.0);
```

## Why is The First Encounter campaign from Revolution and not from the original game?
Because **Serious Sam: Revolution** takes priority over **The First Encounter** when both games are mounted.

To solve this, unmount **Revolution** in config properties and restart the game. Workshop can remain mounted.

Currently I don't know how to prioritize **The First Encounter** campaign over the **Revolution** one.

## What is the "custom mod"?
"Custom mod" is a term used for a set of libraries that come with the patch:
- `Entities_Custom.dll`
- `Game_Custom.dll`
- `GameGUI_Custom.dll`
- `ClassicsExtras_Custom.dll` (entity pack with extra entities)

This custom mod implements new features for vanilla gameplay, including (but not limited to): Game themes, Revolution enemies, TFE keys, player movement customization using **gameplay extensions**, big fonts in console & computer.

When custom mod is active, it means that these libraries take effect over vanilla ones (e.g. `EntitiesMP.dll` and `GameMP.dll`), just like when you're playing a mod with custom libraries in its Bin folder.

- You can optionally disable usage of the custom mod in favor of vanilla entity & game logic. Though it's only recommended in case something is causing issues in multiplayer games.
- When you're playing a mod with its own libraries, the custom mod is always disabled because its logic isn't compatible with the mod.

## What are "Gameplay extensions"?
It's right there in the name. A set of new options for customizing gameplay experience in exchange for compatibility with vanilla.

When gameplay extensions are enabled ("Enable extensions" setting or `gex_bEnable` command), it makes launched servers, saved games and recorded demos unplayable without the patch. All clients have to install the same version of the patch as the server in order to play together.

## Why are there no new weapons or other features from Revolution?
Because implementing them to work seamlessly with the original logic is very tricky and may lead to incompatibility with some vanilla content and servers.

Ideally, I would love to create another mod that comes with the patch that adds all the missing content from **Revolution** to allow you to play all the mounted content properly but I already have two different `Entities` libraries to maintain inside the patch itself (for vanilla TFE and TSE), so I don't really feel like developing another mod parallel to this.

Ultimately, this patch isn't meant to completely replace **Serious Sam Revolution** but rather simply improve the original classic versions.

## How to allow players with other versions of the patch (or without the patch) to join my patched server?
Go to "Server options" menu before starting your server and configure your server to be vanilla compatible:
- "Server options" section -> set "Forbid vanilla clients" to "No"
- "Gameplay extensions" section -> set "Enable extensions" to "No"

Equivalent commands for a dedicated server config:
```
ser_bForbidVanilla = 0;
gex_bEnable = 0;
```

## The blood is a different color now. Is this a bug?
No, it's not a bug. It's a feature that is triggered during specific "seasonal events". The game displays a one-time notification for any new event whenever it starts.

If you do not wish to partake in these events (which were mainly created for fun and extra variety), you can disable them using the following commands:
- Disable automatic colorization of blood and gibs during the events: `gam_iCustomBloodTheme = 1`
- Disable seasonal events altogether (requires game restart): `cfg_iForceSeasonalEvent = 0`

Both of these commands can be toggled using existing settings under the **Classics Patch** options menu.

## How to change player's field of view in multiplayer?
If you wish to change player's FOV in any gamemode, you can use new `sam_fCustomFOV` and `sam_fThirdPersonFOV` commands instead of `plr_fFOV`.

These commands have a smaller FOV range than the vanilla command, so if you still want to have a closer zoom in Cooperative gamemode, set the commands above to `-1` and keep using the `plr_fFOV` command instead.

## Heads-up display is too big!
If HUD elements seem too big and overlap with other elements, consider scaling the HUD down using the `hud_fScaling` command. The value of `0.75` is usually good enough, even for 21:9 resolutions.

## Why are there so many settings and commands? It's confusing!
I want to give players as much freedom to customize their game and experience as possible. You don't have to use every single command. If you don't need extended customization of the patch, you can use quick setup scripts under **Options** -> **Execute Addon** in-game.

This is what happens when a programmer does UI/UX design.

## The game displays an error instead of starting!
If you get an error that says something along the lines of *"Cannot set function patch..."* upon game start, first make sure that you've installed the patch for the right game version. You can see the engine version of the game in the top right corner in the main menu (typically `v1.05` or `v1.07`).

There are a couple of things you can try to solve it:
1. Restart your machine.
2. Locate `SeriousSam_Custom.exe`, right click on it and go to "Properties" -> "Compatibility" tab. Change the state of the "Disable fullscreen optimizations" checkbox and press OK.

If the error persists, you might want to report it. Set `DebugPatcher` property to `1` in the patch config file and run the game again. This will display patcher actions in the log file (e.g. `SeriousSam_Custom.log`) in the root game directory. You can upload the log file when you [submit a new issue](../issues).
