> Descriptions for commands that are modifiable through the **OPTIONS** -> **CLASSICS PATCH** -> **HUD settings** menu.

> [!IMPORTANT]
> Commands beginning with `ahud_` are all part of the Advanced HUD plugin that comes with **Classics Patch**, whereas the commands beginning with `hud_` are already part of the vanilla game (or the custom mod, in some cases).

# Display options
- `hud_bShowAll` - Vanilla command for toggling visibility of the entire interface, weapon viewmodels and the crosshair (ON by default).
- `gfx_bDecoratedText` - Vanilla engine command for toggling decorations in all rendered text, such as color tags and flashing (ON by default).
- `hud_fScaling` - Vanilla command for resizing the entire interface (`1.0` by default).
> [!TIP]
> - If not using Advanced HUD in place of the vanilla interface, the value of `0.75` works nicely for 16:9 resolutions, otherwise the interface from Advanced HUD scales evenly across any aspect ratio.
> - If using Advanced HUD, the value range of the command is increased to `0.05` - `2.0` from the vanilla `0.5` - `1.2`.
- `hud_fOpacity` - Vanilla command for adjusting the opacity percentage of the entire interface (`0.9` by default).
- `ahud_iScreenEdgeX` - Set offset from horizontal edges of the screen (`5` by default).
- `ahud_iScreenEdgeY` - Set offset from vertical edges of the screen (`5` by default).

# Advanced HUD
- `ahud_bEnable` - Toggle between the vanilla interface and the plugin interface (ON by default).
  - `0` - Disabled (vanilla interface)
  - `1` - New interface in the vanilla game
  - `2` - New interface in the vanilla game and mods (may not work correctly in some mods)
- `ahud_bIconShake` - Toggle shaking of the interface icons whenever values that they represent change (ON by default).
- `ahud_fScopeAlpha` - Set opacity of the sniper scope in the 0-1 range (`1` by default).
> [!NOTE]
> Only applicable to **The Second Encounter**.
- `ahud_bScopeColoring` -  Toggle colorization of the zoom wheel based on the health level of a target (OFF by default).
> [!NOTE]
> Only applicable to **The Second Encounter**.
- `ahud_iShowPlayerPing` - Display ping of each player next to their stats in the player list (`0` by default).
  - `0` - Disabled
  - `1` - Display ping in milliseconds
  - `2` - Display ping as a signal strength
- `ahud_bDecoratedNames` - Toggle display of decorations, such as color tags, in player names (ON by default).
- `ahud_iPlayerTags` - Display tags above players in Cooperative mode that are visible from anywhere (`2` by default).
  - `0` - Disabled
  - `1` - Only marker
  - `2` - Marker and player name
  - `3` - Marker, name and relative distance
- `ahud_bTagsInDemos` - Display player tags regardless of gamemode that the demo was recorded on, such as Fragmatch (ON by default).
- `ahud_bTagsForObservers` - Display player tags regardless of gamemode while observing an active game, such as Fragmatch (ON by default).

# HUD themes
These commands can be used to customize the colors of the interface. They accept colors in the RGB format and can be specified as HEX values in the range `0x000000` - `0xFFFFFF` (no alpha channel).

- `ahud_iTheme` - Stylize the interface in a specific way (`0` by default in TFE; `2` by default in TSE).
  - `0` - **The First Encounter** theme
  - `1` - **Seriously Warped Deathmatch** theme
  - `2` - **The Second Encounter** theme
  - `3` - **Revolution** theme
- `ahud_bColorize` - Toggle custom colorization of the interface (OFF by default).
- `ahud_strColorPreset` - Helper command for loading a new preset script via `Scripts/ClassicsPatch/AdvancedHUD_ColorPreset.ini`, otherwise unused.
- `ahud_iColorBase` - Base color of the interface, e.g. borders and player stats.
- `ahud_iColorIcon` - Color of normal icons, e.g. health, armor and weapon on screen.
- `ahud_iColorNames` - Color of player names in the player list and player tags.
- `ahud_iColorWeapon` - Color of weapon icons in the weapon selection list.
- `ahud_iColorSelect` - Color of a selected element, e.g. weapon in the selection list or ammo of the current weapon in the row.
- `ahud_iColorMax` - Color of the "over top" value, e.g. health above 100.
- `ahud_iColorTop` - Color of the "top" value, e.g. health in the 50-100 range.
- `ahud_iColorMid` - Color of the "middle" value, e.g. health in the 25-49 range.
- `ahud_iColorLow` - Color of the "low" value, e.g. health and ammo close to 0.

# HUD elements
- `hud_bShowInfo` - Vanilla command for toggling visibility of the most important information on the interface, such as health, armor and current weapon (ON by default).
- `hud_bShowMessages` - Vanilla command for toggling visibility of unread NETRICSA messages (ON by default).
- `hud_iShowPlayers` - Vanilla command for toggling visibility of the player list (`-1` by default).
  - `-1` - Only in multiplayer
  - `0` - Disabled
- `hud_iSortPlayers` - Vanilla command for sorting the player list by a specific statistic (`-1` by default).
  - `-1` - Automatic sorting depending on the gamemode
  - `0` - Sorting by name
  - `1` - Sorting by health
  - `2` - Sorting by score
  - `3` - Sorting by mana
  - `4` - Sorting by kills
  - `5` - Sorting by deaths
- `hud_bShowPlayerName` - Vanilla command for toggling visibility of player names upon targeting them (ON by default)
- `hud_tmWeaponsOnScreen` - Vanilla command for adjusting how long the weapon selection list is shown for in seconds (`3.0` by default).
- `ahud_bShowAmmoRow` - Toggle display of available ammo in the bottom right corner (ON by default).
- `ahud_bShowDepletedAmmo` - Toggle display of ammunition icons even when the weapon is out of ammo (ON by default).
- `ahud_bShowHighScore` - Toggle display of high score on the top of the screen (ON by default).
- `ahud_bShowLives` - Toggle display of remaining lives (credits) above the messages in Cooperative mode (ON by default).

# Miscellaneous information
- `hud_bShowTime` - Vanilla command for toggling visibility of the current game time (OFF by default).
- `hud_bShowClock` - Vanilla command for toggling visibility of the computer clock (OFF by default).
  - `0` - Disabled
  - `1` - Enabled
  - `2` - Enabled with seconds (Advanced HUD only)
> [!NOTE]
> This command does not exist in vanilla **The First Encounter**, however it has been backported from **The Second Encounter** via the Advanced HUD plugin.
- `hud_bShowMatchInfo` - Vanilla command for displaying information about the current game (ON by default).
> [!NOTE]
> This command does not exist in vanilla **The First Encounter**, however it has been backported from **The Second Encounter** via the Advanced HUD plugin.
- `hud_bShowCoords` - Vanilla command for displaying current crosshair coordinates in the world (OFF by default).
- `hud_bShowResolution` - Vanilla command for displaying current window resolution (OFF by default).
- `hud_iStats` - Vanilla command for displaying benchmarking information (`0` by default).
  - `0` - Disabled
  - `1` - FPS
  - `2` - FPS & extended benchmark

# Network information
- `hud_bShowLatency` - Vanilla command for displaying latency to the server in milliseconds (OFF by default).
- `hud_tmLatencySnapshot` - Vanilla command for adjusting how often to update the latency counter in seconds (`1.0` by default).
- `hud_bShowNetGraph` - Vanilla command for toggling visibility of the network graph (OFF by default).
- `net_iGraphBuffer` - Vanilla command for adjusting the buffer size of the network graph (`100` by default).

# Crosshair options
- `hud_bCrosshairFixed` - Vanilla command for toggling whether the crosshair should always stay centered instead of showing its real hit point (OFF by default).
- `hud_bCrosshairColoring` - Vanilla command for toggling whether the crosshair should be colored based on the health level of the target (ON by default).
- `hud_bCrosshairGradualColoring` - Toggle gradual color change on crosshairs depending on the target's health instead of the sharp change to yellow below 60% and to red below 25% (OFF by default).
> [!IMPORTANT]
> This functionality is part of the [custom mod](Options-50-Mod-settings) and will not work in mods with their own DLL files.
- `hud_fCrosshairRatio` - Vanilla command for adjusting how much the crosshair should change in size depending on the distance from the target point (`0.5` by default).
- `hud_fCrosshairScale` - Vanilla command for adjusting the size of the crosshair (`1.0` by default).
- `hud_fCrosshairOpacity` - Vanilla command for adjusting the opacity percentage of the crosshair (`1.0` by default).
