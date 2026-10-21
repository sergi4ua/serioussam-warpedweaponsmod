> **Serious Sam Classics Patch** includes its own console/shell commands for manipulating or toggling new features.

# Common
- `PatchInfo()` - Display information about the patch. Includes release version number.
- `IncludeScript(CTString)` - Useful function for scripting that can execute scripts files specified in a string variable (because `include` command doesn't support variables).
- `UpdateShadows()` - Locally updates shadow maps in a world that's currently being played, in case they are broken after loading into it instead of starting fresh.
- `ClearConsole()` - Clear the entire console log in-game.
- `inp_JoystickInfo()` - Display information about currently connected joysticks and game controllers.
- `inp_afAxisValues[AXIS_CT]` - Array of constants that contains values of current input axes in-game. Takes an index from `0` to `AXIS_CT - 1`, or optionally one of the constants (engine-defined):
  - `0` / `AXIS_NONE` - The very first axis. Should always be set to `0.0` and it's always used as a dummy axis.
  - `1` / `AXIS_M1_X` - Horizontal mouse movement.
  - `2` / `AXIS_M1_Y` - Vertical mouse movement.
  - `3` / `AXIS_M1_Z` - Scroll wheel power that reaches `0.0` over time. Scrolling up adds a number; scrolling down subtracts it.
  - `4` / `AXIS_M2_X` - Horizontal movement of the "second mouse".
  - `5` / `AXIS_M2_Y` - Vertical movement of the "second mouse".
  - `8` / `AXIS_JOY_CT` - Maximum amount of joysticks (gamepads) supported by the engine.
  - `6` / `AXIS_PER_JOY` - Maximum axes per joystick (gamepad) supported by the engine. The axes are named XYZRUV.
  - `6` / `AXIS_JOY_1` - Very first axis of the very first joystick (defined as `1 + 3 + 2`, i.e. a "none" axis, the first mouse axes and the second mouse axes). Subsequent joysticks can be indexed by using a `AXIS_JOY_1 + AXIS_PER_JOY * n` formula, where `n` is an index of the joystick (from `0` to `AXIS_JOY_CT - 1`).
  - `54` / `AXIS_CT` - Maximum amount of input axes supported by the engine (the size of the array).

# World converters
Commands for converting worlds from one format to another within the game.

> [!WARNING]
> These commands are **not multiplayer synchronized** and may lead to desynchronizations, unless all clients on the server use them with the exact same values!

- `sam_bUsePlaceholderResources` - Allow automatic substitution of missing models, textures and sounds with placeholders.
  - `0` - Disabled
  - `1` - Enabled only for missing resources
  - `2` - Enabled for all resources, regardless of their existence (experimental)
- `sam_iWantedWorldFormat` - Force worlds to be loaded in a specific level format.
  - `-1` - Disabled
  - `0` - **The First Encounter** level format
  - `1` - **The Second Encounter** level format
  - `2` - **Serious Sam Revolution** level format
  - `3` - **Serious Engine 1.50** level format
- `sam_strWorldConverters` - List of world converters separated by a semi-colon (`;`) to apply in a specific order upon loading a world.
  - **Example:** `"tfe"` - does a full **The First Encounter** -> **The Second Encounter** conversion.
  - **Example:** `"ssr;reinit"` - does a full **Revolution** -> **The Second Encounter** conversion with a subsequent reinitialization of all logical entities.
- `wld_ListConverters()` - Display a list of available world converters and which level formats they belong to for use in the `sam_strWorldConverters` command.

# Voting system
Commands for configuring the map pool.

- `VoteMapPool()` - Displays currently loaded pool of maps available for voting.
- `VoteMapAdd(CTString)` - Adds new world file to the map pool.
- `VoteMapRemove(INDEX)` - Removes map under a specific index from the pool (starting from `1`).
- `VoteMapLoad(CTString)` - Loads a completely new map pool from a text file.
> [!NOTE]
> It should be a list of `.wld` files each on a separate line with paths relative to the game directory (e.g. `Levels\LevelsMP\Deathmatch\RedStation.wld`).
> Paths can be prefixed with `TFE:` or `TSE:` (without spaces afterwards) to determine whether or not to load them in **The First Encounter** and **The Second Encounter** respectively. Useful for map pools that can be shared between different games.

# Plugins
Commands for working with external plugins.

- `ListPlugins()` - Display all currently loaded plugin modules.
- `EnablePlugin(INDEX)` - Enable plugin under some index.
  - Example: `EnablePlugin(0)` - Enables plugin under the first index.
- `DisablePlugin(INDEX)` - Disable plugin under some index.
  - Example: `DisablePlugin(0)` - Disables plugin under the first index.
- `GetPluginIndex(CTString)` - Retrieves index of a plugin by its display name (from metadata) for use in `EnablePlugin()` and `DisablePlugin()`.
  - Example: `DisablePlugin(GetPluginIndex("Server Utilities"))` - Disables Server Utilities plugin to prevent it from modifying entities upon starting the game.

# Game client
Commands that can be used in the game executable from **Classics Patch**.

- `Restart()` - Restarts the game client and reloads the current mod, if possible.
- `ListLevels(CTString)` - Lists world files under the `Levels` directory using a wildcard string.
  - Example: `ListLevels("MyMaps/*")` - Lists all world files under `Levels/MyMaps` directory within the game.
- `StartMap(CTString)` - Starts new game on a specified map under the `Levels` directory.
  - Example: `StartMap("01_Hatshepsut")` - Starts the first level of **The First Encounter** campaign.
- `cmd_iGoToMarker` - PlayerMarker to teleport the player to after loading a map using `StartMap()` (`0` by default).
- `cmd_bServer` - Starts a multiplayer game after loading a map using `StartMap()` (`0` by default).

# Dedicated servers
Commands that can be used in the dedicated server application from **Classics Patch**.

- `ded_strForceLevelChange` - Forcefully changes level of the current round for a dedicated server to the specified world file. Similar to `RestartGame()` but without advancing the round.

# Client log
- `ClientLog(INDEX, INDEX)` - Display log of clients that have ever joined the server by their client identity index. These indices are used in other commands.
  - The first index is used for displaying information about a specific client identity (starting from `0`).
  - The second index is used for displaying information about a specific character of a specific client identity (starting from `1`).
- `ClientLogDelete(INDEX, INDEX)` - Delete client identity (starting from `0`) from the log altogether (if character index is `-1`) or only a specific character (starting from `1`).
- `ClientLogSave()` - Manually resave client log into the file after modifying it (done automatically after stopping any launched game).
- `ClientLogLoad()` - Manually reload client log from the file (for undoing any modifications since launching the game).

# Hidden commands
These commands are not marked with a "user" flag, meaning that autocompletion will not work on them and they won't be publicly listed. To call them, you have to type them in full on your own.

The reason why they're hidden is so normal users don't accidentally call them because their function is very specific and they are present mostly for debugging purposes.

- `ResaveConfigProperties()` - Resave config properties into `Data/ClassicsPatch/Config.ini` file after setting them.
- `ListPatches()` - Display all available function patches under their respective indices.
- `EnablePatch(INDEX)` - Set function patch under some index.
  - Example: `EnablePatch(0)` - Sets patch under the first index.
- `DisablePatch(INDEX)` - Remove function patch under some index.
  - Example: `DisablePatch(0)` - Removes patch under the first index.
- `GetFuncPatch(CTString)` - Retrieves index of a function patch by its assigned name for use in `EnablePatch()` and `DisablePatch()`.
  - Example: `DisablePatch(GetFuncPatch("CDrawPort::BlendScreen()"))` - Disables patch that controls red screen on damage.
