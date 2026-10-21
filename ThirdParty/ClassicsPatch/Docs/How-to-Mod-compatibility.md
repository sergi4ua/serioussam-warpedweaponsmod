> **Serious Sam Classics Patch** supports all mods for the vanilla game. But there are also new features available for modders, who wish to utilize the new executable and its features.

> The API includes features that can be utilized either through traditional mods (by modifying `Entities` or `Game` libraries) or by user plugins for different purposes.

> Features described here can be used anywhere whenever you wish to interact with the core API.

# Patch detection
If you simply would like to know whether your mod is being played through Classics Patch or not (for example, to disable local FOV adjustments because of the patch adjustments), you can try checking for the presence of the legacy `CoreAPI` symbol like this:

```cpp
CShellSymbol *pssAPI = _pShell->GetSymbol("CoreAPI", TRUE);
BOOL bUsingClassicsPatch = (pssAPI != NULL);
```

If you'd like to additionally check for patch versions starting from [1.9](../releases/tag/1.9) that introduce a new API, use new `ClassicsPatchAPI` symbol name instead of `CoreAPI`. That way you will also be able to hook the new interface (see below).

# API utilization
You can utilize patch functionality in your own mod or user plugins by using the [Classics Patch API](../../API).

Simply link the `lib/classicscore.lib` library to your project and include `include/classicspatch_api.h` header to any source file in order to use new functions.

If you are unable to link the library directly or you aren't sure whether your mod is even being played through Classics Patch or not (as to avoid creating an unnecessary library dependency), you can get access to the virtual interface through the game shell like this:

```cpp
// Define these globally somehow for the ease of use
BOOL _bClassicsPatch = FALSE;
IClassicsPatchAPI *_pPatchAPI = NULL;

// NOTE: This function is called upon starting the mod for the first time, so it's an ideal place to check for the patch
void CGame::InitInternal(void)
{
  // Check if any Classics Patch version is present
  CShellSymbol *pssAPI = _pShell->GetSymbol("CoreAPI", TRUE);
  _bClassicsPatch = (pssAPI != NULL);

  // Retrieve Classics Patch interface for versions 1.9 and newer
  pssAPI = _pShell->GetSymbol("ClassicsPatchAPI", TRUE);

  if (pssAPI != NULL) {
    _pPatchAPI = (IClassicsPatchAPI *)pssAPI->ss_pvValue;
  }

  // ...the rest of the function...
};
```

Then you can utilize the virtual interface anywhere like this:

```cpp
if (_pPatchAPI != NULL) {
  // _pPatchAPI-> ...

  // EXAMPLE: Report Classics Patch version
  CPrintF("Running Classics Patch v%s\n", _pPatchAPI->Core()->GetVersionName());
}
```

## API verification
Before using the API, you might also want to make sure that your mod isn't using the API that's too new, otherwise this may lead to crashes.

If you're linking the library directly, the code would look like this:

```cpp
// Verify API version to prevent old patch versions from crashing the game due to the lack of needed functionality
ClassicsPatchErrMsg strError;

if (ClassicsPatchAPI_Verify(&strError) != k_EVerifyAPIResult_OK) {
  // Avoid API usage
  _pPatchAPI = NULL;

  CPrintF("Cannot utilize virtual interface of Classics Patch: %s\n", strError);
}
```

However, if you're using a virtual interface from the shell, it becomes a bit trickier, since `ClassicsPatchAPI_Verify()` cannot be called directly.

This code should be added right after setting the `_pPatchAPI` pointer:

```cpp
ClassicsPatchGlobalFunctions patchFunctions;

if (ClassicsPatch_GetGlobalFunctionsFromModule(&patchFunctions)) {
  // Verify API version to prevent old patch versions from crashing the game due to the lack of needed functionality
  ClassicsPatchErrMsg strError;

  if (patchFunctions._Verify(&strError) != k_EVerifyAPIResult_OK) {
    // Avoid API usage
    _pPatchAPI = NULL;

    CPrintF("Cannot utilize virtual interface of Classics Patch: %s\n", strError);
  }

} else {
  // Avoid API usage if the version verification cannot be performed
  _pPatchAPI = NULL;
  CPrintF("Cannot verify API version of Classics Patch\n");
}
```

# Interaction via config files
If you don't have access to the code for whatever reason, you can modify patch behavior by creating configuration files that will be automatically loaded by the patch.

## Modifiable data
These properties can be set in `Data/ClassicsPatch/ModData.ini` config file to toggle specific patch functionality, in case you intend to implement your own workarounds for players without Classics Patch, or to fix existing closed-source mods.

| Key | Description | Example |
| --- | --- | --- |
| `AdjustFOV` | Adjusts FOV of any `CPerspectiveProjection3D` to rely on vertical FOV instead of horizontal one. That includes player view and weapon viewmodels. | `AdjustFOV = 0` |
| `AdjustAR` | Sets `dp_fWideAdjustment` variable for the `CDrawPort` that's used for rendering the world and anything on top of it depending on its aspect ratio (e.g. for fixing HUD overlapping on 16:9 resolutions). | `AdjustAR = 0` |
| `ProperTextScaling` | Adapts menu text (on labels, buttons etc.) to selected aspect ratio of the resolution by scaling it relative to the screen height instead of width. | `ProperTextScaling = 0` |
| `MenuTextScale` | Additional multiplication of menu text scale. In case it appears too big or too small in the patch, as opposed to vanilla. | `MenuTextScale = 0.75` |

## Custom level categories
You can create your own level categories to separate levels from one huge pile.

[See the instructions on the other page here.](How-to-Setup-instructions#Custom-level-categories)

## Custom difficulties
You can configure which difficulties the mod can have by creating configs similar to level categories.

1. Create `Data/ClassicsPatch/Difficulties` folder structure inside the game or the mod folder, if there isn't one already.
2. Create a new text file with a `.des` extension (e.g. `01_SuperEasy.des`) and write your difficulty name into it that will be displayed in-game (e.g. `Super Easy`).
  - You can also add optional description on the second line that will be displayed upon hovering over the difficulty.
3. Create another text file with the same name but with an `.ini` extension (e.g. `01_SuperEasy.ini`).
4. Open it with any text editor and set any of the variables listed below.

| Key | Description | Example |
| --- | --- | --- |
| `Level` | Difficulty level that will be passed into the `gam_iStartDifficulty` console command. Standard difficulties range from `-1` to `5` (from **Tourist** to **Mental**). | `Level = -1` |
| `UnlockCommand` | Console command that needs to be set to `1` in order to display this difficulty. Standard **Mental** difficulty uses `sam_bMentalActivated` command. | `UnlockCommand = ""` |
| `Flash` | Toggle name flashing in the singleplayer difficulty list. This is enabled for the standard **Mental** difficulty. | `Flash = 1` |
