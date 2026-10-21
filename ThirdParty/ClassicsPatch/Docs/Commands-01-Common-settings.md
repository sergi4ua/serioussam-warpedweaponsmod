> Descriptions for commands that are modifiable through the **OPTIONS** -> **CLASSICS PATCH** -> **Common patch settings** menu.

# Steam commands
Special commands for dynamically toggling Steam features. These can be found under "Config properties" options instead.

- `steam_bAllowJoin` - Allow your friends to join the same server that you're currently connected to (and aren't hosting) by using "Join game" button in the friend list (ON by default).
- `steam_bUseWebBrowser` - Allow opening specific in-game links in Steam's web browser via Steam Overlay (ON by default).
- `steam_bHookScreenshots` - Hook Steam screenshot functionality to allow taking custom screenshots from within the game instead of capturing the entire game window (ON by default).
- `steam_iDebugOutput` - Display debug information about interactions with Steam (`0` by default).
  - `0` - Disabled
  - `1` - Only single actions/callbacks
  - `2` - All interactions in real time

# Gameplay options
- `sam_bUseVerticalFOV` - Adjust FOV of any 3D projection (e.g. player view) according to the aspect ratio of the game window, including proper mip distances and weapon viewmodels (ON by default).
> [!TIP]
> If set to `2`, it only fixes vertical FOV while viewing through player's eyes and the third person camera but **not** an external camera or some other entity.
- `sam_fCustomFOV` - Set custom FOV for the player view regardless of gamemode in the 60-110 range (`-1` by default).
- `sam_fThirdPersonFOV` - Set custom FOV specifically for the player's third person view in the 60-110 range (`-1` by default).
- `plr_fFOV` - Vanilla command for changing field of view in Cooperative mode in the 10-170 range (`90` by default).

- `axs_bRedScreenOnDamage` - Toggle screen reddening upon taking damage (ON by default).
> [!IMPORTANT]
> This functionality is part of the **Accessibility** plugin and will not work if the plugin isn't loaded.
- `gam_bAutoUpdateShadows` - Automatically update shadow maps upon loading into games or playing demos (ON by default).
  - Useful for fixing broken shadows in certain cases but may introduce a momentary lag.

### Mod options
The following functionality is part of the [custom mod](Options-50-Mod-settings) and will not work in mods that have their own DLL files or if the custom mod is disabled in the vanilla game:

- `gam_bDisableLocalPrediction` - Toggle local player prediction to eliminate player jittering while playing on servers (using non-LAN connection setting) with latency below 50ms (`-1` by default).
  - `-1` - Automatic (disables local prediction when latency goes below 50ms)
  - `0` - Enable local prediction (vanilla logic)
  - `1` - Disable local prediction

- `gam_iCustomBloodColor` - Custom client-side color for blood particles, stains and flesh (`0xFF0000FF` - red by default).
- `gam_iCustomBloodTheme` - Custom client-side theming for blood and gibs (`0` by default).
  - `0` - Automatically changes based on seasonal events; defaults to `1` otherwise
  - `1` - Simple coloring using `gam_iCustomBloodColor`
  - `2` - Forced color override using `gam_iCustomBloodColor`; uses brighter texture for the gibs
  - `3` - Hippie mode with flowers and fruit from the vanilla game
  - `4` - Party mode
  - `5` - Christmas mode

# Query manager
- `ms_bVanillaQuery` Keep using vanilla query manager but replace hardcoded GameSpy master server with Legacy master server (OFF by default).
> [!NOTE]
> This essentially returns master server functionality from the vanilla game but changes internal master server from `master.gamespy.com` to the value from `ms_strLegacyMS` command (only up to 18 characters). This might be more stable in certain cases compared to the patch's query manager but doesn't allow using master server protocols other than Legacy.
- `ms_iProtocol` - Which master server protocol to use (`MS_LEGACY` by default).
  - `0` / `MS_LEGACY` - Legacy master server protocol (GameSpy replacement).
  - `1` / `MS_DARKPLACES` - DarkPlaces protocol.
  - `2` / `MS_GAMEAGENT` - GameAgent protocol (from SE1.10).
- `ms_strLegacyMS` - Master server IP to use for Legacy master server (`333networks.com` by default).

# Custom connection setting
These commands affect the configuration of the "Classics Patch preset" connection setting that comes with **Classics Patch**.

- `cli_bCustomPrediction` - Toggle prediction of movable entities; equivalent to vanilla `cli_bPrediction` (ON by default).
- `cli_iCustomBufferActions` - Set amount of actions to buffer; equivalent to vanilla `cli_iBufferActions` (`2` by default).
- `cli_iCustomMinBPS` - Set minimum bytes per second that can be sent; equivalent to vanilla `cli_iMinBPS`. More = better (`50000`, i.e. 50 kB by default).
- `cli_iCustomMaxBPS` - Set maximum bytes per second that can be sent; equivalent to vanilla `cli_iMaxBPS`. More = better (`100000`, i.e. 100 kB by default).

> [!NOTE]
> After changing these settings in-game, the connection preset must be reloaded manually through **OPTIONS** -> **NETWORK CONNECTION** in order for the new values to take effect.

# Global screenshots
- `sam_iScreenshotFormat` - File format for asynchronously saving screenshots that have been taken using the "Take screenshot" key (`0` by default).
  - `0` - PNG format
  - `1` - JPG format with 100% quality
  - `2` - TGA format

# Extra commands
Relevant functionality that isn't usable or configurable via these options.

- `sam_bCheckFOV` - Display currently set horizontal and vertical FOV during the game for debugging purposes.
- `ms_strGameAgentMS` - Master server IP to use for GameAgent (`333networks.com` by default).
- `ms_strDarkPlacesMS` - Master server IP to use for DarkPlaces (`192.168.1.4` by default).
- `ms_bDebugOutput` - Display debug information while interacting with the master server (OFF by default).
