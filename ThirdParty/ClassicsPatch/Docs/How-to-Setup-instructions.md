> Various things you may want to set up before playing the game.

# Installation
Simple installation process. To insure that you're installing a correct version of the patch for your game, remember that `TFE` and `TSE` stand for games (**The First Encounter** and **The Second Encounter** respectively), while `1.05` and `1.07` stand for engine versions.

1. Download desired version of the patch (`TFE1.05_<date>.zip` or `TSE1.07_<date>.zip` for Steam).
2. Navigate to the game folder and extract contents of the ZIP archive into it.
3. Agree to replace existing files (original game files, such as DLL files, are included with an `_OG` suffix at the end of their names).
4. (Optional) Download `SE1_RevResources.gro` and put it in the game folder if you intend on playing **Revolution** levels without mounting **Revolution** itself to **The Second Encounter**, which is a very rare and specific case.

# Standalone binaries
**Serious Sam Classics Patch** supports the ability to run the game from its own `Bin` folder to not interfere with vanilla libraries or possibly replace them. All you have to do is rename the `Bin` folder inside of the downloaded build and extract it into the game folder.

But, since this patch depends on the vanilla engine, you cannot immediately run any of the executables because some libraries are missing. You can simply copy them from the vanilla `Bin` directory into your own depending on the application you intend to run:
- All executables: `Engine.dll`, `mfc42.dll` and `MSVCRT.DLL`.
  - The first library is **Serious Engine** itself, while `mfc42.dll` provides graphical user interface for **Serious Editor** and `MSVCRT.DLL` makes all applications run on your system in the first place.
  - Note that `mfc42.dll` and `MSVCRT.DLL` libraries might already be installed on your machine from previous applications, including **Visual Studio**. In which case they aren't required to be in the same folder for the applications to run.
- `DedicatedServer_Custom.exe`: No extra libraries are needed to run the servers.
- `SeriousSam_Custom.exe`, `SeriousEditor_Custom.exe`: `ogg.dll`, `vorbis.dll` and `vorbisfile.dll`.
  - All of these libraries provide support for **OGG** music playback.

# Configuration file
**Serious Sam Classics Patch** includes features that can only be customized before launching the game. For that, you can create a special config file at `Data/ClassicsPatch/Config.ini` within the game directory and add properties to it that will be used upon starting any application.

These properties can also be customized in-game under **Options** -> **Classics Patch** -> **Config properties** and automatically resaved into the file upon applying to be used the next time the game starts.

## Config file rules
Rules of these config files are of a typical **INI** file. The specifics of this format are listed below.

- Key-value pairs are contained on single lines separated by an assignment operator, like this: `key = "value"`.
  - Quotes can only be optionally used on values, in case you need to append spaces on either end of the string, otherwise all whitespaces are stripped from both keys and values.
- If the assignment operator is missing or the line is otherwise invalid, it will be skipped.
- Key-value pairs can be separated into "sections" that are defined by a line enclosed in square brackets, like this: `[section]`.
  - If no section is specified before any key-value pairs, they're added into an "unnamed" section. `[]` section is equal to it.
- If it's a boolean switch, i.e. a value that can only be **true** or **false**, the values must meet the following criteria (case insensitive):
  - Strings starting with `t`, `y`, `1` or `on` are **true**.
  - Strings starting with `f`, `n`, `0` or `of` are **false**.
  - Any other string will be ignored and a hardcoded default value will be used.

## Global properties
These properties are set under an "unnamed" section and are usable in builds for any game.

| Key | Description | Example |
| --- | --- | --- |
| `CustomMod` | Overrides custom library loading. If not disabled, it will use `Entities`, `Game` and `GameGUI` libraries with a `_Custom` suffix in the base game and mods without custom DLL files. | `CustomMod = 0` |
| `DebugPatcher` | Display actions of the function patcher in the log file (e.g. `SeriousSam_Custom.log`) for [debugging purposes](How-to-FAQ#the-game-displays-an-error-instead-of-starting). | `DebugPatcher = 1` |
| `DPIAware` | Can be used to disable DPI awareness of the game window, making it scale according to the Windows setting for a monitor. | `DPIAware = 0` |
| `ExtendedFileSystem` | Can be used to disable extensions to the file system, e.g. content loading from other directories. | `ExtendedFileSystem = 0` |
| `ExtendedInput` | Can be used to disable extensions to the input system, e.g. proper support of game controllers and Mouse Button 4 & 5. | `ExtendedInput = 0` |
| `ForceSeasonalEvent` | Forces a specific seasonal event based on the specified index. The value of `-1` lets the patch determine the current season automatically based on the current date. The value of `0` disables all seasonal events. | `ForceSeasonalEvent = 4` for the Christmas event |
| `FullAppIntegration` | Enables full integration of patch functionality into tool applications, i.e. file system extensions and 64-bit system support. Works with both vanilla tools and Steam-patched ones. | `FullAppIntegration = 1` |
| `NotifyAboutUpdates` | Toggles notifications about new patch versions upon starting the game. | `NotifyAboutUpdates = 0` |
| `MountSSRWorkshop` | Allows to load content from Steam workshop of **Serious Sam Classics: Revolution** using a path from `SSRWorkshop`. | `MountSSRWorkshop = 1` |
| `SSRWorkshop` | Specifies a path to Steam workshop of **Serious Sam Classics: Revolution** for loading its content. | `SSRWorkshop = "D:\SteamLibrary\steamapps\workshop\content\227780"` |

## The Second Encounter properties
These properties are set under an "unnamed" section and are only usable in builds for **The Second Encounter**.

| Key | Description | Example |
| --- | --- | --- |
| `MountTFE` | Allows to load content from **Serious Sam Classic: The First Encounter** using a path from `TFEDir`. | `MountTFE = 0` |
| `MountSSR` | Allows to load content from **Serious Sam Classics: Revolution** using a path from `SSRDir`. | `MountSSR = 1` |
| `TFEDir` | Specifies a path to **Serious Sam Classic: The First Encounter** for loading its content. | `TFEDir = "C:\SeriousSamTFE"` |
| `SSRDir` | Specifies a path to **Serious Sam Classics: Revolution** for loading its content. | `SSRDir = "D:\SteamLibrary\steamapps\common\Serious Sam Revolution"` |

## Steam properties
These properties are set under a `[Steam]` section.

| Key | Description | Example |
| --- | --- | --- |
| `Enable` | Establishes connection with your Steam client and notifies it that the game is running as if it was launched directly through Steam. If Steam isn't running or the game is unavailable (not owned), this feature is disabled. | `Enable = 0` |
| `ForServers` | Lets dedicated server application initialize and use Steam API, unless `Enable` is turned off. | `ForServers = 1` |
| `ForTools` | Lets Serious Editor and modeler applications initialize and use Steam API, unless `Enable` is turned off. | `ForTools = 1` |

# Loading extra content
To load extra content in your game, you can specify a list of relative and absolute paths on your hard drive with extra GRO files.

This feature is useful for when you have multiple instances of the game build but don't want to copy the same content across every game folder or when you want to organize the files instead of keeping everything in the root folder.

To do this, create a `Data/ContentDir.lst` text file within the game folder and add paths to it like this:
```
Content\
..\Storage\
D:\SeriousSamMaps\
```

- `Content\` - Loads GRO files from the 'Content' directory within the game folder.
- `..\Storage\` - Loads GRO files from a directory next to the game folder.
- `D:\SeriousSamMaps\` - Loads GRO files from a directory on some drive.

## Loading The First Encounter content
You can play **The First Encounter** content by mounting it to **The Second Encounter**.

1. Locate installation directory with **Serious Sam Classic: The First Encounter** and copy full path to it.
2. Open the aforementioned `Data/ClassicsPatch/Config.ini` and add a property to it like this: `TFEDir = "full path to TFE in quotes"`.

### Note
- If you have a localized version of **The First Encounter** and the content doesn't seem to be translated, try copying GRO packages with localization (e.g. `1_00_Texts_RUS.gro`) into **The Second Encounter** directory or any extra content directory.

## Loading Revolution content
You can play and use **Revolution** content (including from its workshop) by mounting it to **The Second Encounter**.

To mount the game:
1. Locate installation directory with **Serious Sam Classics: Revolution** and copy full path to it.
2. Open the aforementioned `Data/ClassicsPatch/Config.ini` and add a property to it like this: `SSRDir = "full path to SSR in quotes"`.

To mount workshop:
1. Locate Steam workshop directory with downloaded **Revolution** content. Relative to the Steam installation directory it should be at `(Steam)\steamapps\workshop\content\227780\`.
2. Open the aforementioned `Data/ClassicsPatch/Config.ini` and add a property to it like this: `SSRWorkshop = "full path to workshop in quotes"`.

### Note
- If you mount both **The First Encounter** and **Revolution**, the latter will take priority, replacing vanilla **The First Encounter** campaign with the one from **Revolution**.
- If you only mount **Revolution** game and leave `SSRWorkshop` property empty, it will automatically be set to `..\..\workshop\content\227780\` in order to load workshop content relative to the game folder (assuming the game is located inside the same Steam folder as workshop files).

# Custom level categories
You can create your own level categories to separate levels from one huge pile.

1. Create `Data/ClassicsPatch/LevelCategories` folder structure inside the game or the mod folder, if there isn't one already.
2. Create a new text file with a `.des` extension (e.g. `00_MyMaps.des`) and write your category name into it that will be displayed in-game (e.g. `MY COOL MAPS`).
  - You can also add optional description on the second line that will be displayed upon hovering over the category.
3. Create another text file with the same name but with a `.lst` extension (e.g. `00_MyMaps.lst`).
4. Open it with any text editor and fill it with a list of `.wld` files that the category should contain. For example:
```
Levels\MyMaps\Map01.wld
Levels\MyMaps\Map02.wld
Levels\MyMaps\Mappack_*.wld
Levels\Development\
```

### Note
- Level category lists support wildcards, e.g. `*` for matching any text and `?` for matching any character in the path to `.wld` files.
- To list all files under a specific directory, just specify the directory path (like the 4th line in the example).

# Adding custom window resolutions
You can create a list of custom resolutions for the game instead of manually typing them in inside the video options menu.

1. Create a `Data/ClassicsPatch/Resolutions.lst` text file (or copy one from the `SE1_ClassicsPatch.gro` archive).
2. Open it with any text editor and fill it with resolutions that you wish to use; one per line (e.g. `1440x720` or `1000x1000`).

### Note
- Resolutions are loaded in the exact same order they are listed in the file.
- If your native screen resolution isn't listed, it is automatically added at the end of the list by the game.
